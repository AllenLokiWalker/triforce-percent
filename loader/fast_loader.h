#ifndef __FAST_LOADER_H__
#define __FAST_LOADER_H__

#include "common.h"

typedef union {
	u8 bytes[6];
	struct {
		u8 b1, b2, x, y;
		u16 status;
	};
	struct {
		s8 b1, b2, x, y;
		u16 status;
	} s;
	struct {
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
} raw_input_t;
// 6 bytes long

typedef struct {
	u8 unused1[656];
	raw_input_t pads[4];
	u8 unused2[10];
	u8 rumble_enable[4];
	u8 rumble_counter[4];
	u8 unused3[418];
	u8 rumble_off_frames;
	u8 rumble_on_frames;
	u8 unused4[10];
} __attribute__((packed)) padmgr_t;


#define POLLS 8
#define DATA_LEN (45 * ((POLLS) / 4))
#define COMMAND_LEN ((DATA_LEN) - 5)
#define HUGE_T_SIZE 23 /* ceiling((30 bits * 3 pads * 8 polls) / 32)*/

// Command format:
// 4 poll format: struct { u32 crc32; u8 data[40]; u8 command_id; }
// 8 poll format: struct { u32 crc32; u8 data[85]; u8 command_id; }
typedef union {
	struct {
		u32 crc;
		union {
			u8 bytes[COMMAND_LEN];
			
			// Command 1: Load 81 bytes to given address
			// Command 2: Load up to 80 bytes to given address
			struct {
				u8* address;
				u8  data[COMMAND_LEN - 5];
				u8  length; // Is last data byte when run as command 1
			} cmd01;
			
			// Command 3: Load X counts of byte Y to specified address
			struct {
				u8* address;
				u32 length;
				u8  byte;
				u8  padding[COMMAND_LEN - 9];
			} cmd03;
			
			// Command 4: DMA uncompressed data
			// Command 5: DMA compressed data
			struct {
				void* vram;
				void* vrom;
				u32 size;
				u8  padding[COMMAND_LEN - 12];
			} cmd04;
			
			// Command 6: Call command data as code
			//No need for a separate struct--just call `bytes`
			
			// Command 7: Call specified address with up to 4 args
			struct {
				void(*function_pointer)(void);
				u32 a0;
				u32 a1;
				u32 a2;
				u32 a3;
				u8  padding[COMMAND_LEN - 20];
			} cmd07;
			
		};
		u8 id;
	} command;
	u8 bytes[DATA_LEN];
} out_data_t;

typedef struct {
	u32 blocks[HUGE_T_SIZE];
} huge_t;

typedef struct {
	void(*fp_precmd)(void);
	void(*fp_postcmd)(void);
	u32 dummy1, dummy2;
	u32 crc_table[256]; // 1024 bytes
	raw_input_t pad_data[4];
	huge_t huge; //23*4 bytes
	out_data_t out;
} fl_globals_t;

//char(*__kaboom)[sizeof(fl_globals_t)] = 1; // print size of something at compile time


#define RUMBLE_CRCFAIL 1
#define RUMBLE_NOP 5
#define RUMBLE_VALID 6

extern fl_globals_t gvars;
extern padmgr_t  padmgr;


void init();
void run(void* queue);
int huge_push_data(huge_t* n, u32 bits, u32 amount);
u32 huge_pop_data(huge_t* n, u32 amount);
void rumble_message(u32 bits);


#endif //__FAST_LOADER_H__
