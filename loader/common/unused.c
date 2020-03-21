 

void _memset( void* data, u8 value, u32 size ) {
	while( size ) {
		*((u8*)data++) = value;
		--size;
	}
}
