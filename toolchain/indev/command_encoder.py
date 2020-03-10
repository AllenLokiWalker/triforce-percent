#!/bin/python3
# -*- coding: utf-8 -*-
# public domain

import os, sys, struct, binascii

def big_endian_32( n ):
	return ( (n>>24)&0xFF, (n>>16)&0xFF, (n>>8)&0xFF, n&0xFF )
def big_endian_16( n ):
	return ( (n>>8)&0xFF, n&0xFF )
def big_endian_str( s ):
	t = big_endian_32( int( s, 0 ) )
	return ( t[0], t[1], t[2], t[3] )

polls = 4
pads_len = 48 * ( polls // 4 )
data_len = 45 * ( polls // 4 )
command_len = data_len - 5
command_pos = data_len - 1
print( "data_len = " + str(data_len) + " | command_len = " + str(command_len) )

def command_to_bitstream( _command ):
	split = _command.split( ' ' )
	name = split[0].lower()
	data = split[1:]
	
	cmd_buf = []
	out_buf = []
	command = 0
	
	# load_data_pointer 0xdeadbeef
	# *                 Address
	if name == 'load_data_pointer':
		cmd_buf.extend( big_endian_str( data[0] ) )
		cmd_buf.extend( [0] * ( command_len - len(cmd_buf) ) ) # padding
		command = 1
	
	# load_bytes_to_data_pointer 1,2,3,4,5,6,7,8,9,0xA,0xB,0o14,0xD,0b1110...
	# *                          Data...
	# * If less than (command_len) bytes are given, zeros will be appended to fill the space
	# * If more than (command_len) bytes are given, the extra bytes will be ignored
	if name == 'load_bytes_to_data_pointer':
		data = data[0].split(',')
		cmd_buf.extend( [ int(i,0) & 0xFF for i in data[:command_len] ] )
		cmd_buf.extend( [0] * ( command_len - len(cmd_buf) ) ) # padding
		command = 2
	
	# load_bytes 0xdeadbeef 4,2,3,1,3,3,7,0,0,7,64,32,16,8,4,2,1...
	# *          Address    Data...
	# * If more than (command_len - 5) bytes are given, the extra bytes will be ignored
	if name == 'load_bytes':
		cmd_buf.extend( big_endian_str( data[0] ) ) # put address
		nums = data[1].split(',')
		cmd_buf.extend([ len(nums) & 0xFF ]) # put length
		cmd_buf.extend( [ int(i,0) & 0xFF for i in nums[:command_len-5] ] ) # put data
		cmd_buf.extend( [0] * ( command_len - len(cmd_buf) ) ) # padding
		command = 3
	
	# load_byte_x_times 0xdeadbeef 0xabadbabe 0x42
	# *                 Address    Length     Data
	if name == 'load_byte_x_times':
		cmd_buf.extend( big_endian_str( data[0] ) ) # put address
		cmd_buf.extend( big_endian_str( data[1] ) ) # put length
		cmd_buf.extend([ int(data[2],0)&0xFF ]) #       put data
		cmd_buf.extend( [0] * ( command_len - len(cmd_buf) ) ) # padding
		command = 4
	
	# dma_data 0xdeadbeef 0xabadbabe 0x31337
	# *        VRAM addr  VROM addr  length
	# Call DmaMgr_SendRequest0 with arguments
	if name == 'dma_data':
		cmd_buf.extend( big_endian_str( data[0] ) ) # put vram addr
		cmd_buf.extend( big_endian_str( data[1] ) ) # put vrom addr
		cmd_buf.extend( big_endian_str( data[2] ) ) # put length
		cmd_buf.extend( [0] * ( command_len - len(cmd_buf) ) ) # padding
		command = 5
	
	# execute_instructions 0xdeadbeef,0xdeadbeef,...
	# *             machine code
	if name == 'execute_instructions':
		for instruction in data[0].split(',')[:command_len//4]:
			cmd_buf.extend( big_endian_str( instruction ) )
		cmd_buf.extend( [0] * ( command_len - len(cmd_buf) ) ) # padding
		command = 6
	
	# call_address 0xdeadbeef
	# *            adress to call
	if name == 'call_address':
		cmd_buf.extend( big_endian_str( data[0] ) )
		cmd_buf.extend( [0] * ( command_len - len(cmd_buf) ) ) # padding
		command = 7
	
	# set_repeated_code_address 0xdeadbeef
	# *                         Address
	if name == 'set_repeated_code_address':
		cmd_buf.extend( big_endian_str( data[0] ) )
		cmd_buf.extend( [0] * ( command_len - len(cmd_buf) ) ) # padding
		command = 8
	
	cmd_buf.extend([ command & 0xFF ])
	crc = binascii.crc32( bytes(cmd_buf) ) & 0xFFFFFFFF
	
	out_buf.extend( big_endian_32( crc ) )
	out_buf.extend( cmd_buf )
	return bytes( out_buf )
#

def bytes_to_bitstream( buf ):
	n = 0
	r = [0] * pads_len
	i = 0
	while i < data_len:
		n <<= 8
		n  |= buf[ i ]
		i += 1
	i = pads_len
	while i > 0:
		i -= 4
		r[i+3] = n & 0xFF; n >>= 8;
		r[i+2] = n & 0xFF; n >>= 8;
		r[i+1] = n & 0x3F; n >>= 6;
		r[i  ] = n & 0xFF; n >>= 8;
	return bytes(r)

if __name__ == '__main__':
	hr = 0
	raw = 0
	hx = 1
	if len( sys.argv ) == 1:
		print( "Usage: hyperspeed_command_encoder <input file> <options>" )
		print( "options:" )
		print( "-raw     : output as raw bitstream" )
		print( "-hex     : output as hexadecimal data (default)" )
		print( "-polls:N : specify number of controller polls" )
		print( "         : (should be a multiple of 4)" )
		exit()
	#
	
	for v in sys.argv:
		v = v.lower()
		if v == '-human':
			hr = 1
			raw = 0
			hx = 0
		if v == '-raw':
			raw = 1
			hr = 0
			hx = 0
		if v == '-hex':
			hx = 1
			raw = 0
			hr = 0
		if '-polls' in v:
			polls = int(v.split(':')[1],0)
			pads_len = 48 * ( polls // 4 )
			data_len = 45 * ( polls // 4 )
			command_len = data_len - 5
			command_pos = data_len - 1
	
	fp = open( sys.argv[ 1 ], 'r' )
	cmds = fp.readlines()
	fp.close()
	del fp
	
	for c in cmds:
		if len(c) > 0:
			if c[0] != '#':
				data = command_to_bitstream( c.split('#')[0] )
				bits = bytes_to_bitstream( data )
				if raw:
					print(repr(bits))
				if hx:
					for c in bits:
						sys.stdout.write( "{0:02x} ".format(c) )
					sys.stdout.write('\n')
				if hr:
					bitstream_to_buttons( bits )
#

'''
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
'''

