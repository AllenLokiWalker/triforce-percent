
#define TESTING 1

//#include <z64ovl/oot/u10.h>
//#include <z64ovl/helpers.h>

typedef unsigned long long u64;
typedef          long long s64;
typedef unsigned int u32;
typedef          int s32;
typedef unsigned short u16;
typedef          short s16;
typedef unsigned char u8;
typedef          char s8;
#define NULL ((void*)0U)

#define POLLS 8
#define _data_len ( 45 * ( (POLLS) / 4 ) )
#define _command_len ( (_data_len) - 5 )

typedef union {
	u8 bytes[ 6 ];
	struct __attribute__((packed)) {
		u8 b1, b2, x, y;
		u16 status;
	};
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


// Command format
// format: | 4 polls: u32 crc; u8 data[40]; u8 command; | 8 polls: u32 crc; u8 data[85]; u8 command;
typedef union {
	struct __attribute__((packed)) {
		u32 crc;
		union __attribute__((packed)) {
			u8 bytes[ _command_len ];
			
			struct __attribute__((packed)) { // Load data pointer
				u8* data_pointer;
				u8  padding[ _command_len - 4 ];
			} cmd01;
			
			struct __attribute__((packed)) { // Load data to data pointer
				u8  data[ _command_len ];
			} cmd02;
			
			struct __attribute__((packed)) { // Load N bytes to specified address
				u8* data_pointer;
				u8  length;
				u8  data[ _command_len - 5 ];
			} cmd03;
			
			struct __attribute__((packed)) { // Load X counts of byte Y to specified address
				u8* data_pointer;
				u32 length;
				u8  byte;
				u8  padding[ _command_len - 9 ];
			} cmd04;
			
			struct __attribute__((packed)) { // DMA data?
				void* vram;
				void* vrom;
				u32 size;
				u8  padding[ _command_len - 12 ];
			} cmd05;
			
			struct __attribute__((packed)) { // Treat command data as instructions and jump to them
				u8  instructions[ _command_len ];
			} cmd06;
			
			struct __attribute__((packed)) { // Jump to specified address
				void(*function_pointer)(void);
				u8  padding[ _command_len - 4 ];
			} cmd07;
			
			struct __attribute__((packed)) { // Set an address to repeatedly call
				void(*func)(void);
				u8  padding[ _command_len - 4 ];
			} cmd08;
			
		};
		u8 id;
	} command;
	u8 bytes[ _data_len ];
} __attribute__((packed)) out_data_t;

typedef struct {
	u32 crc_table[ 256 ]; // 1024 bytes
	u8  sprintf_buffer[ 1024 ];
	union {
		u8  command_buffer[ 256 ];
		out_data_t out;
	};
	u8* data_pointer;
	void(*post_interpreter_function)(void);
	u32 RANDU;
} __attribute__((packed)) globals_t;

extern globals_t gvars;
extern padmgr_t  padmgr;

extern void osContStartReadData( void* queue );
extern void osRecvMesg( void* queue, void* msg, u32 to_block ); // msg = NULL, to_block = yes
extern void osContGetReadData( raw_input_t* input_data );
extern void DmaMgr_SendRequest0( void* vram_addr, void* vrom_addr, u32 size );

u32 crc_data( void* data, u32 size );
u32 RANDU( void );
void _memset( void* data, u32 value, u32 size );

void init( void ) __attribute__((section(".start")));
void run( void* queue );

#if TESTING == 1
#include "ascii.c"
#endif

// entry point
void init( void ) {
	// generate CRC table
	u32 r, i; u8 counter;
	for( i = 0; i < 256; ++i ) {
		r = i;
		for( counter = 0; counter < 8; ++counter )
			r = ( ( r & 1 ) ? 0 : 0xEDB88320 ) ^ ( r >> 1 );
		gvars.crc_table[ i ] = r ^ 0xFF000000;
	}
	gvars.RANDU = 1;
	
	// patch padmgr to call main() every frame
	// construct jal to run()
	*((u32*)0xA00A2640) = 0x0C000000 | ( ( ((u32)run) >> 2 ) & 0x03FFFFFF );
	// first argument is address to queue
	*((u32*)0xA00A2644) = 0x8FA4002C;
	// *don't* re-order these!
	
	return;
}

#define huge_t_size (128/sizeof(u32))
typedef struct {
	u32 blocks[ huge_t_size ];
} huge_t;

void huge_clear( huge_t* n );
int huge_push_data( huge_t* n, u32 bits, u32 amount );
u32 huge_pop_data( huge_t* n, u32 amount );

void pad_sanitize( raw_input_t* bits ) {
	//const u8 dpad_encoder[16] = {0,7,3,0,5,6,4,0,1,8,2,0,0,0,0,0}; // D-pad positions: nothing | up | up-left | left | down-left | down | down-right | right | up-right
	if( bits->b2 & 0x80 ) { // this bit gets set on official N64 controllers when holding L+R+Start
		bits->b2 |= 0x30; // assume that those buttons are being held
		bits->b1 |= 0x10; // set their bits appropriately
	}
	bits->b2 &= 0x3F;
}

// called by padmgr
void run( void* queue ) {
	u32 cmd_crc;
	
	#if TESTING == 1
	print_bytes( 16, 56, (u8*)&padmgr.pads[0], 24, 12 );
	#endif
	
	// Poll controllers
	{
	huge_t temp2;
	u32 i;
	
	huge_clear( &temp2 );
	
	for( i = 0; i < (POLLS); ++i ) {
		raw_input_t* pad_data;
		u8 temp_data[24];
		// try to preserve the original pad input as polled by the original code
		
		if( !i ) { // the first time, use pad data from the original game poll
			pad_data = (raw_input_t*)(&padmgr.pads[0]);
		} else { // afterwards, poll the pads ourselves, and discard data for pad 1
			pad_data = (raw_input_t*)temp_data;
			osContStartReadData( queue );
			osRecvMesg( queue, NULL, 1 );
			osContGetReadData( pad_data ); // actually get the pad data
		}
		
		pad_sanitize( &pad_data[1] );
		pad_sanitize( &pad_data[2] );
		pad_sanitize( &pad_data[3] );
		
		huge_push_data( &temp2, pad_data[ 1 ].b1, 8 );
		huge_push_data( &temp2, pad_data[ 1 ].b2, 6 );
		huge_push_data( &temp2, pad_data[ 1 ].x,  8 );
		huge_push_data( &temp2, pad_data[ 1 ].y,  8 );
		huge_push_data( &temp2, pad_data[ 2 ].b1, 8 );
		huge_push_data( &temp2, pad_data[ 2 ].b2, 6 );
		huge_push_data( &temp2, pad_data[ 2 ].x,  8 );
		huge_push_data( &temp2, pad_data[ 2 ].y,  8 );
		huge_push_data( &temp2, pad_data[ 3 ].b1, 8 );
		huge_push_data( &temp2, pad_data[ 3 ].b2, 6 );
		huge_push_data( &temp2, pad_data[ 3 ].x,  8 );
		huge_push_data( &temp2, pad_data[ 3 ].y,  8 );
	}
	
	i = _data_len;
	while( i > 0 ) {
		--i;
		gvars.out.bytes[ i ] = huge_pop_data( &temp2, 8 );
	}
	}
	cmd_crc = crc_data( gvars.out.command.bytes, _data_len - 4 );
	
	#if TESTING == 1
	print_bytes( 16, 72, (u8*)&cmd_crc, 4, 4 );
	print_bytes( 16, 80, gvars.out.bytes, _data_len, 8 );
	#endif
	
	// CRC everything except for the CRC itself
	if( cmd_crc != gvars.out.command.crc ) {
		// the CRC is wrong
		// rumble
		padmgr.rumble_on_frames = 0xF0;
		padmgr.rumble_counter[ 1 ] = 2;
		padmgr.rumble_enable[ 1 ] = 1;
	} else {
		// the CRC is correct
		// don't rumble
		padmgr.rumble_on_frames = 0xF0; // ????
		padmgr.rumble_counter[ 1 ] = 2; // ????
		padmgr.rumble_enable[ 1 ] = 0;
		
		switch( gvars.out.command.id ) {
			// S = usable data, minus signalling data
			
			case 1: { // load data pointer
				gvars.data_pointer = gvars.out.command.cmd01.data_pointer;
				// u32 data_pointer;
			} break;
			
			case 2: { // load (_command_len) bytes to data pointer
				int i;
				for( i = 0; i < _command_len; ++i )
					*(gvars.data_pointer++) = gvars.out.command.cmd02.data[ i ];
			} break;
			
			case 3: { // load *up to* (_command_len - 5) bytes to specified address
				int i;
				if( gvars.out.command.cmd03.length > ( _command_len - 5 ) )
					gvars.out.command.cmd03.length = _command_len - 5;
				for( i = 0; i < gvars.out.command.cmd03.length; ++i )
					*(gvars.out.command.cmd03.data_pointer++) = gvars.out.command.cmd03.data[ i ];
			} break;
			
			case 4: { // load X counts of byte Y to specified address
				while( gvars.out.command.cmd04.length > 0 ) {
					*(gvars.out.command.cmd04.data_pointer++) = gvars.out.command.cmd04.byte;
					--gvars.out.command.cmd04.length;
				}
			} break;
			
			case 5: { // DMA that I'm not sure if this would actually work or not but whatever
				DmaMgr_SendRequest0(
					gvars.out.command.cmd05.vram,
					gvars.out.command.cmd05.vrom,
					gvars.out.command.cmd05.size
				);
			} break;
			
			case 6: { // Treat command data as instructions and jump to them (can execute `2.5 * POLLS` instructions)
				u32 addr;
				addr = (u32) &gvars.out.command.cmd06.instructions;
				addr += 0x20000000; // bypass cache
				((void(*)(void))addr)();
			} break;
			
			case 7: { // Call specified address
				gvars.out.command.cmd07.function_pointer();
			} break;
			
			case 8: { // Set an address to repeatedly call
				gvars.post_interpreter_function = gvars.out.command.cmd08.func;
			} break;
			
			default: break; // NOP
		}
		
		if( gvars.post_interpreter_function != NULL )
			gvars.post_interpreter_function();
	}
	
	// zero pads 1 and 3
	_memset( &padmgr.pads[1], 0, 6 );
	_memset( &padmgr.pads[3], 0, 6 );
	
	return;
}

u32 crc_data( void* data, u32 size ) {
	u32 state;
	state = 0U;
	while( size ) {
		state = gvars.crc_table[ (state & 0xFF) ^ *((u8*)data) ] ^ ( state >> 8 );
		++data;
		--size;
	}
	return state;
}

void huge_clear( huge_t* n ) {
	int i;
	if( n ) for( i = 0; i < huge_t_size; ++i ) n->blocks[ i ] = 0U;
}

int huge_shift_up( huge_t* n, u32 amount ) {
	u32 i;
	if( !n ) return 0;
	if( amount > 32 ) amount = 32;
	for( i = 0; i < ( huge_t_size - 1 ); ++i ) {
		n->blocks[ i ] <<= amount;
		n->blocks[ i ]  |= ( n->blocks[ i + 1 ] >> ( 32 - amount ) );
	}
	n->blocks[ i ] <<= amount;
	return 1;
}

int huge_shift_down( huge_t* n, u32 amount ) {
	u32 i;
	if( !n ) return 0;
	if( amount > 32 ) amount = 32;
	for( i = huge_t_size - 1; i > 0; --i ) {
		n->blocks[ i ] >>= amount;
		n->blocks[ i ]  |= ( n->blocks[ i - 1 ] << ( 32 - amount ) );
	}
	n->blocks[ i ] >>= amount;
	return 1;
}

int huge_push_data( huge_t* n, u32 bits, u32 amount ) {
	if( !n ) return 0;
	huge_shift_up( n, amount );
	n->blocks[ huge_t_size - 1 ] |= ( bits & ( ~( 0xFFFFFFFF << amount ) ) );
	return 0;
}

u32 huge_pop_data( huge_t* n, u32 amount ) {
	u32 mask, r;
	if( !n ) return 0;
	mask = 0xFFFFFFFF; mask <<= amount; mask = ~mask;
	r = n->blocks[ huge_t_size - 1 ];
	r &= mask;
	huge_shift_down( n, amount );
	return (u32)r;
}

u32 RANDU( void ) {
	gvars.RANDU = ( gvars.RANDU * 65539 ) & 0x7FFFFFFF;
	return gvars.RANDU >> 1;
}

void _memset( void* data, u32 value, u32 size ) {
	while( size ) {
		*((u8*)data++) = (u8)value;
		--size;
	}
}

