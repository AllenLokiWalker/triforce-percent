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

polls = 8
pads_len = 48 * ( polls // 4 )
data_len = 45 * ( polls // 4 )
command_len = data_len - 5
command_pos = data_len - 1
print( "data_len = " + str(data_len) + " | command_len = " + str(command_len) )

last_address = 0

def command_to_bitstream( _command ):
	global last_address
	split = _command.split( ' ' )
	name = split[0].lower()
	data = split[1:]
	
	cmd_buf = []
	out_buf = []
	command = 0
	
	# load_bytes <address> <data>
	# ex. "load_bytes 0x80402000 39,189,255,200,175,176,0,36,60,16,128,65,38,16,64,0,..."
	# * if  < 81 bytes are given, command 2 will be used
	# * if == 81 bytes are given, command 1 will be used
	# * if  > 81 bytes are given, extra bytes are ignored
	# * data can be given in any base that int(x,0) supports
	if name == 'load_bytes':
		cmd_buf.extend( big_endian_str( data[0] ) ) # put address
		nums = data[1].split(',')
		nums_len = len(nums)
		
		if nums_len > 81: nums_len = 81
		if nums_len < 81: # command 2
			for i in range(80):
				if i < nums_len:
					cmd_buf.extend([int( nums[i] ,0)])
				else:
					cmd_buf.extend([0])
			cmd_buf.extend([ nums_len & 0xFF ]) # put length
			command = 2
		elif nums_len == 81: # command 1
			for i in range(81):
				if i < nums_len:
					cmd_buf.extend([int( nums[i] ,0)])
				else:
					cmd_buf.extend([0])
			command = 1
	#
	
	# load_byte_x_times 0xdeadbeef 0xabadbabe 0x42
	# *                 Address    Length     Data
	if name == 'load_byte_x_times':
		cmd_buf.extend( big_endian_str( data[0] ) ) # put address
		cmd_buf.extend( big_endian_str( data[1] ) ) # put length
		cmd_buf.extend([ int(data[2],0)&0xFF ]) #       put data
		cmd_buf.extend( [0] * ( command_len - len(cmd_buf) ) ) # padding
		command = 3
	
	# dma_data 0xdeadbeef 0xabadbabe 0x31337
	# *        VRAM addr  VROM addr  length
	# Call DmaMgr_SendRequest0 with arguments
	if name == 'dma_data':
		cmd_buf.extend( big_endian_str( data[0] ) ) # put vram addr
		cmd_buf.extend( big_endian_str( data[1] ) ) # put vrom addr
		cmd_buf.extend( big_endian_str( data[2] ) ) # put length
		cmd_buf.extend( [0] * ( command_len - len(cmd_buf) ) ) # padding
		command = 4
	
	# call_data_itself 0xdeadbeef,0xdeadbeef,...
	# *             machine code
	if name == 'call_data_itself':
		for instruction in data[0].split(',')[:command_len//4]:
			cmd_buf.extend( big_endian_str( instruction ) )
		cmd_buf.extend( [0] * ( command_len - len(cmd_buf) ) ) # padding
		command = 5
	
	# call_address 0xdeadbeef
	# *            adress to call
	if name == 'call_address':
		cmd_buf.extend( big_endian_str( data[0] ) )
		cmd_buf.extend( [0] * ( command_len - len(cmd_buf) ) ) # padding
		command = 6
	
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
	f_raw = False
	f_hex = True
	if len( sys.argv ) == 1:
		print( "Usage: hyperspeed_command_encoder <input file> <options>" )
		print( "options:" )
		print( "-raw     : output as raw bitstream" )
		print( "-hex     : output as hexadecimal data (default)" )
		print( "-polls:N : specify number of controller polls" )
		print( "           (should be a multiple of 4)" )
		exit()
	#
	
	for v in sys.argv:
		v = v.lower()
		if v == '-raw':
			f_raw = True
		if v == '-hex':
			f_hex = True
		if '-polls' in v:
			polls = int(v.split(':')[1],0)
			pads_len = 48 * ( polls // 4 )
			data_len = 45 * ( polls // 4 )
			command_len = data_len - 5
			command_pos = data_len - 1
	
	fp = open( sys.argv[ 1 ], 'r' )
	cmds = fp.read().split('\n')
	fp.close()
	del fp
	
	for c in cmds:
		if len(c) > 0:
			if c[0] != '#':
				data = command_to_bitstream( c.split('#')[0] )
				bits = bytes_to_bitstream( data )
				if f_raw:
					print(repr(bits))
				if f_hex:
					for c in bits:
						#sys.stdout.write( "0x{0:02x},".format(c) )
						sys.stdout.write( "{0:02x}".format(c) )
					sys.stdout.write('\n')
#

