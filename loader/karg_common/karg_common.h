#ifndef __karg_common_h
#define __karg_common_h

typedef unsigned long long u64;
typedef          long long s64;
typedef unsigned int u32;
typedef          int s32;
typedef unsigned short u16;
typedef          short s16;
typedef unsigned char u8;
typedef          char s8;
#define NULL ((void*)0)

#define POLLS 8
#define _data_len ( 45 * ( (POLLS) / 4 ) )
#define _command_len ( (_data_len) - 5 )
#define huge_t_size 23 /* ceiling( ( 30 bits * 3 pads * 8 polls ) / 32 )*/

typedef union {
	u8 bytes[ 6 ];
	struct __attribute__((packed)) {
		u8 b1, b2, x, y;
		u16 status;
	};
	struct __attribute__((packed)) {
		s8 b1, b2, x, y;
		u16 status;
	} s;
	struct __attribute__((packed)) {
		u8 a :1;
		u8 b :1;
		u8 z :1;
		u8 s :1;
		u8 du:1;
		u8 dd:1;
		u8 dl:1;
		u8 dr:1;
		u8 reset:1;
		u8 unused:1;
		u8 l :1;
		u8 r :1;
		u8 cu:1;
		u8 cd:1;
		u8 cl:1;
		u8 cr:1;
		u8 x, y;
		u16 status;
	} buttons;
} __attribute__((packed)) raw_input_t;
// 6 bytes long

typedef struct {
	u8 unused1[ 656 ];
	raw_input_t pads[ 4 ];
	u8 unused2[ 10 ];
	u8 rumble_enable[ 4 ];
	u8 rumble_counter[ 4 ];
	u8 unused3[ 418 ];
	u8 rumble_off_frames;
	u8 rumble_on_frames;
	u8 unused4[ 10 ];
} __attribute__((packed)) padmgr_t;

// Command format:
// 4 poll format: struct { u32 crc32; u8 data[40]; u8 command_id; }
// 8 poll format: struct { u32 crc32; u8 data[85]; u8 command_id; }

typedef union {
	struct __attribute__((packed)) {
		u32 crc;
		union __attribute__((packed)) {
			u8 bytes[ _command_len ];
			
			// Command 1: Load 81 bytes to given address
			// Command 2: Load up to 80 bytes to given address
			struct __attribute__((packed)) {
				u8* address;
				u8  data[ _command_len - 5 ];
				u8  length; // Is last data byte when run as command 1
			} cmd01;
			
			// Command 3: Load X counts of byte Y to specified address
			struct __attribute__((packed)) {
				u8* address;
				u32 length;
				u8  byte;
				u8  padding[ _command_len - 9 ];
			} cmd03;
			
			// Command 4: DMA data
			struct __attribute__((packed)) {
				void* vram;
				void* vrom;
				u32 size;
				u8  padding[ _command_len - 12 ];
			} cmd04;
			
			// Command 5: Call command data as code (call data itself)
			struct __attribute__((packed)) {
				u8  instructions[ _command_len ];
			} cmd05;
			
			// Command 6: Call specified address with no args
			struct __attribute__((packed)) {
				void(*function_pointer)(void);
				u8  padding[ _command_len - 4 ];
			} cmd06;
			
		};
		u8 id;
	} command;
	u8 bytes[ _data_len ];
} __attribute__((packed)) out_data_t;

typedef struct {
	u32 crc_table[ 256 ]; // 1024 bytes
	out_data_t out;
	u8 padding[ 128 - sizeof(out_data_t) ];
	void(*fp_precmd)(void);
	void(*fp_postcmd)(void);
	u8 f_precmd_enable;
	u8 f_postcmd_enable;
} __attribute__((packed)) globals_t;

//char(*__kaboom)[sizeof(globals_t)] = 1; // print size of something at compile time

typedef struct {
	u32 blocks[ huge_t_size ];
} huge_t;

extern globals_t gvars;
extern padmgr_t  padmgr;

extern void osContStartReadData( void* queue );
extern void osRecvMesg( void* queue, void* msg, u32 to_block ); // msg = NULL, to_block = yes
extern void osContGetReadData( raw_input_t* input_data );
extern void DmaMgr_SendRequest0( void* vram_addr, void* vrom_addr, u32 size );

//for disabling and re-enabling interrupts in critical code
extern s32 __osDisableInt(); //80005130
extern void __osRestoreInt(s32 i); //800051A0
//cache clearing

// 0x80003440. addr is weird, it's a cache line address not a normal address.
// Just set addr to 0 and size to >= 0x2000 to write back the whole cache.
extern void osWritebackDCache(void* addr, s32 size);

//0x800041A0. Same deal with addr. Set addr to 0 and size to >= 0x4000 to invalidate the whole cache.
extern void osInvalICache(void* addr, s32 size);


#endif

