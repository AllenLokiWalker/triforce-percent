#ifndef __karg_common_c
#define __karg_common_c

#include "karg_common.h"

void _memset( void* data, u8 value, u32 size ) {
	while( size ) {
		*((u8*)data++) = value;
		--size;
	}
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

#endif

