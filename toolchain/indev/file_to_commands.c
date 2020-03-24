// public domain

// build: cc -Wall -O2 file_to_commands.c -o file_to_commands

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>

#define POLLS 8
#define _data_len ( 45 * ( (POLLS) / 4 ) )
#define _command_len ( (_data_len) - 5 )
#define _data_load_len ( _command_len - 4 )


size_t fsize( FILE* fp ){
	size_t prev, fs;
	if( fp == NULL ) return 0;
	prev = ftell( fp );
	fseek( fp, 0L, SEEK_END );
	fs = ftell( fp );
	fseek( fp, prev, SEEK_SET );
	return fs;
}

int main( int argc, char** argv ) {
	uint8_t* buf;
	FILE* fp;
	long size;
	uint32_t dest_address;
	
	if( argc != 3 ) {
		puts( "usage: file_to_command 0x<dest_address> <file>" );
		return 0;
	}
	
	sscanf( argv[1], "%x", &dest_address );
	
	fp = fopen( argv[2], "rb" );
	if( !fp ) return 0;
	size = fsize( fp );
	
	buf = (uint8_t*)malloc( sizeof(uint8_t) * size );
	if( !buf ) {
		fclose( fp );
		return 0;
	}
	fread( buf, sizeof(uint8_t), size, fp );
	fclose( fp ); fp = NULL;
	
	{
	long bytes_left;
	uint8_t* pos;
	bytes_left = size;
	pos = buf;
	while( bytes_left > 0 ) {
		int i; long len;
		len = bytes_left;
		if( len > _data_load_len ) len = _data_load_len;
		printf( "load_bytes 0x%08x ", dest_address );
		
		for( i = 0; i < (len - 1); ++i ) {
			printf( "%u,", *pos );
			++pos;
			++dest_address;
			--bytes_left;
		}
		printf( "%u\n", *pos );
		++pos;
		++dest_address;
		--bytes_left;
	}
	}
	free( buf );
	
	return 0;	
}

