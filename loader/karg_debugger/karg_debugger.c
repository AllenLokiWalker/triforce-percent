/* Optional debugger
To run:
load to 0xA0402000
set fp_postcmd to 0x80402000
set f_postcmd_enable to 1
*/


#include "../karg_common/karg_common.c"

typedef struct {
	u8  sprintf_buffer[ 1024 ];
	raw_input_t pad_last; // 6 bytes
	u8  f_init;
	u8  current_page;
	u32 memview_addr;
	u32 memview_addr_offset;
	u32 memview_nybble;
	u8  memview_mode;
	u8  memview_blinker;
	u8  f_blank_screen;
	u8  f_input_disable;
	u32 random;
	u8  padmode;
} __attribute__((packed)) debugger_globals_t;

#include "ascii.c"

#define _fp_one 4096
#define _stick_scale_x 5655
#define _stick_scale_y 5655

typedef struct {
	volatile float x, y, z;
} vector_t;

extern vector_t link_vel;
extern volatile float link_speed;
extern volatile s16 link_health;
extern volatile u8  b_button_slot;

extern debugger_globals_t dgvars;

inline void print_pad( raw_input_t pad, u16 x, u16 y );
void print_pad( raw_input_t pad, u16 x, u16 y ) {
	u16 bits, i;
	bits = pad.b1; bits <<= 8; bits |= pad.b2;
	for( i = 0; i < 16; ++i ) {
		if( bits & 1 ) draw_button( x, y, i );
		x += 8;
		bits >>= 1;
	}
	_printf( x, y, "%4i %4i", pad.s.x, pad.s.y );
}

u32 random( void ) {
	return dgvars.random = 1103515245U * dgvars.random + 24691U;
}

void clear_cs( void ) {
	extern volatile void* cutscene_pointer;
	const u32 null_cs[] = {0,0};
	asm("cutscene_pointer = 0xA01CA208");
	cutscene_pointer = (void*)&null_cs;
}

// entry point
void run( void ) __attribute__((section(".start")));
void run( void ) {
	if( !dgvars.f_init ) {
		dgvars.memview_addr = 0xA0400000;
		dgvars.f_init = 1;
	}
	
	if( dgvars.f_blank_screen )
		draw_rectangle( 20, 64, 20+230, 64+104, color_black );
	
	_printf( 20, 64, "Page %u", dgvars.current_page );
	
	// before menu code is run
	
	if( dgvars.padmode == 1 ) {
		s32 t;
		t = padmgr.pads[0].s.x; t *= _stick_scale_x; t /= _fp_one; padmgr.pads[0].s.x = t;
		t = padmgr.pads[0].s.y; t *= _stick_scale_y; t /= _fp_one; padmgr.pads[0].s.y = t;
	}
	if( dgvars.padmode == 2 ) {
		int sx, sy;
		sx = padmgr.pads[0].buttons.z;
		padmgr.pads[0].buttons.z = padmgr.pads[0].buttons.l;
		padmgr.pads[0].buttons.l = sx;
		sx = padmgr.pads[0].s.x;
		sy = padmgr.pads[0].s.y;
		padmgr.pads[0].x = 0;
		padmgr.pads[0].y = 0;
		if( padmgr.pads[0].buttons.dl ) padmgr.pads[0].x = 129;
		if( padmgr.pads[0].buttons.dr ) padmgr.pads[0].x = 127;
		if( padmgr.pads[0].buttons.du ) padmgr.pads[0].y = 127;
		if( padmgr.pads[0].buttons.dd ) padmgr.pads[0].y = 129;
		padmgr.pads[0].buttons.dl = sx < -30;
		padmgr.pads[0].buttons.dr = sx >  30;
		padmgr.pads[0].buttons.du = sy >  30;
		padmgr.pads[0].buttons.dd = sy < -30;
	}
	
	// menu code
	if( !dgvars.pad_last.buttons.dl && padmgr.pads[0].buttons.dl )
		--dgvars.current_page;
	if( !dgvars.pad_last.buttons.dr && padmgr.pads[0].buttons.dr )
		++dgvars.current_page;
	
	dgvars.f_input_disable = 0;
	switch( dgvars.current_page ) {
		
		case  1: { // print pads
			_puts( "pad data:", 20, 72 );
			print_pad( padmgr.pads[0], 20,  80 );
			print_pad( padmgr.pads[1], 20,  88 );
			print_pad( padmgr.pads[2], 20,  96 );
			print_pad( padmgr.pads[3], 20, 104 );
		} break;
		
		case  2: { // print raw pad data
			print_string_and_bytes( 20, 72, "raw pad data:", padmgr.pads, 24, 12 );
		} break;
		
		case  3: { // print command output data
			print_string_and_bytes( 20, 72, "command data:", &gvars.out.bytes, _data_len, 12 );
		} break;
		
		case  4:
		case  5: { // memory viewer/editor
			const u16 cursor_colors[ 2 ] = { color_black, color_new(31,0,0) };
			if( dgvars.current_page == 4 ) {
				int adder;
				// toggle edit mode
				if( !dgvars.pad_last.buttons.b && padmgr.pads[0].buttons.b ) {
					dgvars.memview_mode = !dgvars.memview_mode;
					dgvars.memview_nybble = 0;
				}
				// select previous nybble
				if( !dgvars.pad_last.buttons.cl && padmgr.pads[0].buttons.cl ) {
					if( dgvars.memview_mode ) {
						if( dgvars.memview_nybble >= 4 ) {
							if( dgvars.memview_addr_offset > 0 ) {
								dgvars.memview_nybble = 0;
								--dgvars.memview_addr_offset;
							}
						} else dgvars.memview_nybble += 4;
					} else {
						dgvars.memview_nybble += dgvars.memview_nybble < 28 ? 4 : 0;
						dgvars.memview_addr_offset = 0;
					}
				}
				// select next nybble
				if( !dgvars.pad_last.buttons.cr && padmgr.pads[0].buttons.cr ) {
					if( dgvars.memview_nybble > 0 ) dgvars.memview_nybble -= 4;
					else if( dgvars.memview_mode ) {
						++dgvars.memview_addr_offset;
						dgvars.memview_nybble = 4;
					}
				}
				adder = 0;
				if( !dgvars.pad_last.buttons.cu && padmgr.pads[0].buttons.cu ) adder =  1;
				if( !dgvars.pad_last.buttons.cd && padmgr.pads[0].buttons.cd ) adder = -1;
				
				if( adder ) {
					if( dgvars.memview_mode ) { // memory
						u8 temp, num, mask;
						mask = 0xF << dgvars.memview_nybble;
						temp = *((volatile u8*)(dgvars.memview_addr+dgvars.memview_addr_offset));
						num = temp; num += adder << dgvars.memview_nybble; num &= mask; temp &= ~mask; temp |= num;
						*((volatile u8*)(dgvars.memview_addr+dgvars.memview_addr_offset)) = temp;
					} else { // address
						u32 temp, num, mask;
						mask = 0xF << dgvars.memview_nybble;
						temp = dgvars.memview_addr;
						num = temp; num += adder << dgvars.memview_nybble; num &= mask; temp &= ~mask; temp |= num;
						dgvars.memview_addr = temp;
					}
				}
				dgvars.f_input_disable = 1;
			}
			
			// draw editor cursor
			if( dgvars.memview_mode ) {
				u32 x;
				u16 offset_x, offset_y;
				offset_x = ( dgvars.memview_addr_offset & 15 ) * 14;
				offset_y = ( ( dgvars.memview_addr_offset >> 4 ) *  8 ) + 80;
				x = 20; x += _letter_width; x -= (dgvars.memview_nybble >> 2)*_letter_width; x += offset_x;
				draw_rectangle( x, offset_y, x + _letter_width, offset_y + _letter_height, cursor_colors[ (dgvars.memview_blinker >> 5) & 1 ] );
			} else {
				u32 x;
				x = 20; x += 16 * _letter_width; x -= (dgvars.memview_nybble >> 2)*_letter_width;
				draw_rectangle( x, 72, x + _letter_width, 72 + _letter_height, cursor_colors[ (dgvars.memview_blinker >> 5) & 1 ] );
			}
			// draw values
			_printf( 20, 72, "Address: %08X", dgvars.memview_addr );
			print_bytes( 20, 80, (void*)dgvars.memview_addr, 16*5, 16 );
			
			++dgvars.memview_blinker;
		} break;
		
		case  6: {
			// press c-up to levitate
			if( padmgr.pads[0].buttons.cu ) { link_vel.y = 7.5f; padmgr.pads[0].buttons.cu = 0; };
			if( padmgr.pads[0].buttons.dd ) link_vel.y = -15.0f;
			//if( pad_last.buttons.l ) link_speed = 40.0f;
			_puts( "Velocity:", 20, 72 );
			_printf( 20,  80, "X %.3f", link_vel.x );
			_printf( 20,  88, "Y %.3f", link_vel.y );
			_printf( 20,  96, "Z %.3f", link_vel.z );
			_printf( 20, 104, "Speed %.3f", link_speed );
		} break;
		
		case  7: {
			if( !dgvars.pad_last.buttons.cr && padmgr.pads[0].buttons.cr ) dgvars.f_blank_screen = 1;
			if( !dgvars.pad_last.buttons.cl && padmgr.pads[0].buttons.cl ) dgvars.f_blank_screen = 0;
			_printf( 20, 72, "Blank screen: %u", dgvars.f_blank_screen );
			dgvars.f_input_disable = 1;
		} break;
		
		
		case  8: {
			if( padmgr.pads[0].buttons.cu ) link_health = 0;
			if( padmgr.pads[0].buttons.cl ) b_button_slot = 0x2C;
			if( padmgr.pads[0].buttons.cr ) clear_cs();
			_puts( "C-up: kill Link\nC-left: SOLD OUT on B\nC-right: clear cutscene pointer", 20, 72 );
			dgvars.f_input_disable = 1;
		} break;
		
		case  9: { // change FPS divider
			if( !dgvars.pad_last.buttons.cl && padmgr.pads[0].buttons.cl )
				*((volatile s8*)0xA01C6FA1) -= ( *((volatile s8*)0xA01C6FA1) == 1 ) ? 2 : 1;
			if( !dgvars.pad_last.buttons.cr && padmgr.pads[0].buttons.cr )
				*((volatile s8*)0xA01C6FA1) += ( *((volatile s8*)0xA01C6FA1) == -1 ) ? 2 : 1;
			_printf( 20, 72, "FPS divider: %i", *((volatile s8*)0xA01C6FA1) );
			dgvars.f_input_disable = 1;
		} break;
		
		case 10: { // change pad mode
			if( !dgvars.pad_last.buttons.cl && padmgr.pads[0].buttons.cl )
				--dgvars.padmode;
			if( !dgvars.pad_last.buttons.cr && padmgr.pads[0].buttons.cr )	
				++dgvars.padmode;
			_printf( 20, 72, "pad mode: %u", dgvars.padmode );
			dgvars.f_input_disable = 1;
		} break;
		
		default: break;
	}
	
	dgvars.pad_last = padmgr.pads[ 0 ];
	
	if( dgvars.padmode == 3 ) {
		padmgr.pads[0].b1 = ( random() >> 24 ) & 0xEF;
		padmgr.pads[0].b2 = random() >> 26;
		padmgr.pads[0].x  = random() >> 24;
		padmgr.pads[0].y  = random() >> 24;
	}
	
	if( dgvars.f_input_disable ) _memset( padmgr.pads, 0, 4 );
	return;
}

