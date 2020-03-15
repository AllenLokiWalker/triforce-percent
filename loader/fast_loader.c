
#include "karg_common/karg_common.c"

void init( void ) __attribute__((section(".start")));
void run( void* queue );

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
	
	// patch padmgr to call run() every frame
	*((u32*)0x800A2640) = 0x0C000000 | ( ( ((u32)run) >> 2 ) & 0x03FFFFFF ); // construct jal to run() (also disable zeroing of pad 4)
	*((u32*)0x800A2644) = 0x8FA4002C; // first argument is address to queue
	
	return;
}

int huge_push_data( huge_t* n, u32 bits, u32 amount );
u32 huge_pop_data( huge_t* n, u32 amount );
void rumble_message( u32 bits );

// called by padmgr
void run( void* queue ) {
	// Draw green bar in the corner
	const u64 green64 = 0x7c107c107c107c1ULL;
	(*((volatile u64**)0x8011F56C))[1286] = green64; // shifted two pixels to the right of the "real" one
	(*((volatile u64**)0x8011F56C))[1287] = green64; // due to longword alignment
	
	// Poll controllers
	{
	huge_t temp2;
	u32 i;
	
	for( i = 0; i < (POLLS); ++i ) {
		raw_input_t* pad_data;
		u8 temp_data[24];
		
		// try to preserve the original pad input as polled by the original code
		if( !i ) { // the first time, use pad data from the original game poll
			pad_data = (raw_input_t*)(&padmgr.pads[0]);
		} else { // afterwards, poll the pads ourselves, and discard data for pad 1
			_memset( temp_data, 0, 24 );
			pad_data = (raw_input_t*)temp_data;
			osContStartReadData( queue );
			osRecvMesg( queue, NULL, 1 );
			osContGetReadData( pad_data ); // actually get the pad data
		}
		
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
	
	if( gvars.f_precmd_enable ) gvars.fp_precmd();
	
	i = _data_len;
	while( i > 0 ) {
		--i;
		gvars.out.bytes[ i ] = huge_pop_data( &temp2, 8 );
	}
	osWritebackDCache(NULL, 0x4000);
	osInvalICache(NULL, 0x4000);
	}
	
	// CRC everything except for the CRC itself
	if( crc_data( gvars.out.command.bytes, _data_len - 4 ) != gvars.out.command.crc ) {
		// the CRC is wrong
		rumble_message( 1 );
	} else {
		// the CRC is correct
		rumble_message( 2 ); // ack
		
		switch( gvars.out.command.id ) {
			
			case 1: //   fixed 81 byte size
			case 2: { // up to 80 byte size
				int i, len;
				len = gvars.out.command.id == 1 ? _command_len - 4 : gvars.out.command.cmd01.length;
				for( i = 0; i < len; ++i )
					*(gvars.out.command.cmd01.address++) = gvars.out.command.cmd01.data[ i ];
			} break;
			
			case 3: { // load X counts of byte Y to specified address
				while( gvars.out.command.cmd03.length > 0 ) {
					*(gvars.out.command.cmd03.address++) = gvars.out.command.cmd03.byte;
					--gvars.out.command.cmd03.length;
				}
			} break;
			
			case 4: { // DMA that I'm not sure if this would actually work or not but whatever
				DmaMgr_SendRequest0(
					gvars.out.command.cmd04.vram,
					gvars.out.command.cmd04.vrom,
					gvars.out.command.cmd04.size
				);
			} break;
			
			case 5: { // Treat command data as instructions and jump to them (can execute `2.5 * POLLS` instructions)
				((void(*)(void))&gvars.out.command.cmd05.instructions)();
			} break;
			
			case 6: { // Call specified address
				gvars.out.command.cmd06.function_pointer();
			} break;
			
			default: break; // NOP
		}
	}
	
	if( gvars.f_postcmd_enable ) gvars.fp_postcmd();
	
	// zero pads 1 and 3 ourselves
	_memset( &padmgr.pads[1], 0, 6 );
	_memset( &padmgr.pads[3], 0, 6 );
	
	return;
}

void rumble_message( u32 bits ) {
	int i;
	padmgr.rumble_on_frames = 0xF0; // ???
	for( i = 1; i < 4; ++i ) {
		padmgr.rumble_counter[ i ] = 2;
		padmgr.rumble_enable[ i ] = bits & 1;
		bits >>= 1;
	}	
}

int huge_shift_up( huge_t* n, u32 amount ) {
	u32 i;
	for( i = 0; i < ( huge_t_size - 1 ); ++i ) {
		n->blocks[ i ] <<= amount;
		n->blocks[ i ]  |= ( n->blocks[ i + 1 ] >> ( 32 - amount ) );
	}
	n->blocks[ i ] <<= amount;
	return 1;
}

int huge_shift_down( huge_t* n, u32 amount ) {
	u32 i;
	for( i = huge_t_size - 1; i > 0; --i ) {
		n->blocks[ i ] >>= amount;
		n->blocks[ i ]  |= ( n->blocks[ i - 1 ] << ( 32 - amount ) );
	}
	n->blocks[ i ] >>= amount;
	return 1;
}

int huge_push_data( huge_t* n, u32 bits, u32 amount ) {
	huge_shift_up( n, amount );
	n->blocks[ huge_t_size - 1 ] |= ( bits & ( ~( 0xFFFFFFFF << amount ) ) );
	return 0;
}

u32 huge_pop_data( huge_t* n, u32 amount ) {
	u32 mask, r;
	mask = 0xFFFFFFFF; mask <<= amount; mask = ~mask;
	r = n->blocks[ huge_t_size - 1 ];
	r &= mask;
	huge_shift_down( n, amount );
	return (u32)r;
}

