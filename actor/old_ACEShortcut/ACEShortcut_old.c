#include "ootmain.h"

// Actor Information
#define ACT_ID                  1
#define OBJ_ID                  1

// framebuffer GFX stuff
#ifndef __ASCII_C
#define __ASCII_C

#define game_framebuffer (*((u16**)0x8011F56C))

#define _letter_width  6
#define _letter_height 8

// each byte is a 6px scanline at 1bpp
const u8 ascii_letters[ 768 ] = {
	 0, 0, 0, 0, 0, 0, 0, 0,
	 8,28,28, 8, 8, 0, 8, 0,
	20,20,20, 0, 0, 0, 0, 0,
	20,20,62,20,62,20,20, 0,
	 8,30,32,28, 2,60,24, 0,
	 0,50,36, 8,16,18,38, 0,
	 8,20, 8,42,36,36,26, 0,
	 8, 8, 4, 0, 0, 0, 0, 0,
	 8,16,32,32,32,16, 8, 0,
	16, 8, 4, 4, 4, 8,16, 0,
	 0,20, 8,62, 8,20, 0, 0,
	 0, 4, 4,31, 4, 4, 0, 0,
	 0, 0, 0, 0, 0, 8, 8,16,
	 0, 0, 0,30, 0, 0, 0, 0,
	 0, 0, 0, 0, 0, 8, 8, 0,
	 0, 1, 2, 4, 8,16,32, 0,
	28,34,38,42,50,50,28, 0,
	 8,24,40, 8, 8, 8,62, 0,
	28,34, 2,12,24,34,62, 0,
	28,34, 2,12, 2,34,28, 0,
	 4,12,20,36,62, 4,14, 0,
	62,32,32,60, 2,34,28, 0,
	12,16,32,60,34,34,28, 0,
	62,34, 4, 8,16,16,16, 0,
	28,34,34,28,34,34,28, 0,
	28,34,34,30, 2, 2,28, 0,
	 0, 8, 8, 0, 0, 8, 8, 0,
	 0, 8, 8, 0, 0, 8, 8,16,
	 4, 8,16,32,16, 8, 4, 0,
	 0, 0,62, 0, 0,62, 0, 0,
	16, 8, 4, 2, 4, 8,16, 0,
	28,34, 2, 4, 8, 0, 8, 0,
	28,34,46,42,46,32,28, 0,
	 8,20,34,34,62,34,34, 0,
	60,18,18,28,18,18,60, 0,
	12,18,32,32,32,18,12, 0,
	60,18,18,18,18,18,60, 0,
	62,18,16,28,16,18,62, 0,
	62,18,16,28,16,16,56, 0,
	12,18,32,32,38,18,14, 0,
	34,34,34,62,34,34,34, 0,
	28, 8, 8, 8, 8, 8,28, 0,
	14, 4, 4, 4,36,36,24, 0,
	50,20,20,24,20,20,51, 0,
	56,16,16,16,16,18,62, 0,
	34,54,42,42,34,34,34, 0,
	34,50,42,38,34,34,34, 0,
	28,34,34,34,34,34,28, 0,
	60,18,18,28,16,16,56, 0,
	28,34,34,34,34,42,28, 3,
	60,18,18,28,24,20,50, 0,
	28,34,32,28, 2,34,28, 0,
	62,42, 8, 8, 8, 8,28, 0,
	34,34,34,34,34,34,28, 0,
	34,34,34,34,34,20, 8, 0,
	34,34,34,42,42,42,20, 0,
	34,20,20, 8,20,20,34, 0,
	34,34,20, 8, 8, 8,28, 0,
	62,34, 4, 8,16,34,62, 0,
	56,32,32,32,32,32,56, 0,
	32,32,16, 8, 4, 2, 1, 0,
	56, 8, 8, 8, 8, 8,56, 0,
	 8,20,34,34, 0, 0, 0, 0,
	 0, 0, 0, 0, 0, 0, 0,63,
	 8, 8, 4, 0, 0, 0, 0, 0,
	 0, 0,28, 2,30,34,31, 0,
	48,16,16,20,26,18,44, 0,
	 0, 0,28,34,32,34,28, 0,
	 6, 2, 2,26,38,38,27, 0,
	 0, 0,28,34,62,32,28, 0,
	12,18,16,56,16,16,56, 0,
	 0, 0,26,34,34,30, 2,60,
	48,16,20,26,18,18,50, 0,
	 8, 0,24, 8, 8, 8,28, 0,
	 2, 0, 6, 2, 2,34,34,28,
	48,16,18,20,24,20,18, 0,
	24, 8, 8, 8, 8, 8,28, 0,
	 0, 0,52,42,42,42,42, 0,
	 0, 0,44,50,34,34,34, 0,
	 0, 0,28,34,34,34,28, 0,
	 0, 0,60,18,18,28,16,56,
	 0, 0,26,36,36,28, 4,14,
	 0, 0,54,26,16,16,56, 0,
	 0, 0,30,32,28, 2,60, 0,
	16,16,60,16,16,18,12, 0,
	 0, 0,34,34,34,38,26, 0,
	 0, 0,34,34,34,20, 8, 0,
	 0, 0,34,42,42,42,20, 0,
	 0, 0,34,20, 8,20,34, 0,
	 0, 0,34,34,34,30, 2,60,
	 0, 0,62, 4, 8,16,62, 0,
	 6, 8, 8,48, 8, 8, 6, 0,
	 8, 8, 8, 0, 8, 8, 8, 0,
	48, 8, 8, 6, 8, 8,48, 0,
	18,44, 0, 0, 0, 0, 0, 0,
	 0, 8,20,34,34,34,62, 0
};

const u8 hex_to_ascii[] = {'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};

#define color_new( r, g, b ) ( (u16)((((u16)(r))<<11)|(((u16)(g))<<6)|(((u16)(b))<<1)|1) )

// screen bounds:
// 4 <= X <= 316
// 1 <= Y <= 237

inline void put_pixel( u32 x, u32 y, u16 color );
void put_pixel( u32 x, u32 y, u16 color ) {
	x += 4; // account for overscan
	y += 1;
	if( x > 316 ) return;
	if( y > 237 ) return;
	y *= 320;
	y += x;
	game_framebuffer[ y ] = color;
}

// Print letter to the screen, with a shadow
// c is u16 as it gets multiplied by 8
void print_char( u16 c, u16 x, u16 y, u16 color ) {
	u8 i, j, scanline;
	if( c < ' ' || c > 127 ) c = '?';
	c -= ' ';
	c <<= 3;
	for( i = 0; i < 8; ++i ) {
		scanline = ascii_letters[ c + i ];
		for( j = 0; j < 6; ++j ) {
			if( scanline & 32 ) {
				//put_pixel( x + j + 1, y + i + 1, 0 ); // draw dropshadow
				put_pixel( x + j, y + i, color );
			}
			scanline <<= 1;
		}
	}
}

void print_string( u8* str, u16 x, u16 y ) {
	u16 xstart;
	xstart = x;
	while( *str != '\0' ) {
		if( *str == '\n' ) {
			x = xstart;
			y += _letter_height;
		} else {
			print_char( *str, x, y, 0xFFFF );
			x += _letter_width;
		}
		++str;
	}
}

extern s32 _sprintf( u8* dest, const char* format, ...);
asm( ".equ _sprintf, 0x800CE7B4" );

#define _printf( x, y, format, ...) {u8 __temp__[192];_sprintf(__temp__,(format),__VA_ARGS__);print_string(__temp__,(x),(y));}

// from openbsd
u8* n_strcat( u8* str, u8* append ) {
	u8* save;
	save = str;
	for(;*str;++str);
	while( ( *str++ = *append++ ) != '\0' );
	return save;
}

void bytes_to_str( u8* str, u32 l_str, u8* bytes, u32 l_bytes ) {
	u32 current_byte, current_char;
	current_char = 0;
	for( current_byte = 0; current_byte < l_bytes; ++current_byte ) {
		if( current_char < l_str )
			str[ current_char++ ] = hex_to_ascii[ bytes[ current_byte ] >> 4 ];
		if( current_char < l_str )
			str[ current_char++ ] = hex_to_ascii[ bytes[ current_byte ] & 15 ];
		if( current_char < l_str )
			str[ current_char++ ] = ' ';
	}
}

void print_bytes( u16 x, u16 y, u8* bytes, u16 amount, u16 per_line ) {
	u16 xstart, i, j;
	xstart = x;
	j = 0;
	for( i = 0; i < amount; ++i ) {
		u8 c;
		c = bytes[ i ];
		print_char( hex_to_ascii[ c >> 4 ], x, y, 0xFFFF ); x += _letter_width;
		print_char( hex_to_ascii[ c & 15 ], x, y, 0xFFFF ); x += _letter_width; x += 2;
		++j;
		
		if( j >= per_line ) {
			x = xstart; j = 0;
			y += _letter_height;
		}
	}
}

void print_string_and_bytes( u16 x, u16 y, u8* str, u8* bytes, u16 amount, u16 per_line ) {
	print_string( str, x, y );
	y += _letter_height;
	print_bytes( x, y, bytes, amount, per_line );
}

void print_color( u16 x, u16 y, u16 color ) {
	u8 c, i;
	for( i = 0; i < 3; ++i ) {
		c = color >> 11;
		print_char( hex_to_ascii[ c >> 1 ], x, y, (c&1)?65535:44395 );
		x += _letter_width;
		color <<= 5;
	}
}

#endif

// Actor Structure
typedef struct {
	Actor actor;
} Entity;

#define QUOTEX(x) #x
#define QUOTE(x) QUOTEX(x)
//#define SEED_ROTATION_ADDR 0x801FC000
#define SEED_ROTATION_ADDR 0x801C7E64

extern void seed_rotation( void );
asm( ".equ seed_rotation, " QUOTE(SEED_ROTATION_ADDR) );

static void create( Entity* entity, GlobalContext* global ) {
	*(u32*)SEED_ROTATION_ADDR = 0x080475E4; // seed angle = J 0x8011D790
}

#define AOE 600.0f

static void step( Entity* entity, GlobalContext* global ) {
	_printf( 16, 56, "Distance to AOE:%.3f", (entity->actor.dist_from_link_xz) - AOE );
	_printf( 16, 64, "Seed angle:%08X", *(u32*)SEED_ROTATION_ADDR ); // big endian :)
	_printf( 16, 72, "Pads:%08X - %08X -", *(u32*)0x8011D790, *(u32*)0x8011D79C);
	
	if( entity->actor.dist_from_link_xz < AOE )
		seed_rotation();
}

static void draw( Entity* entity, GlobalContext* global ) {
	
}

static void destroy( Entity* entity, GlobalContext* global ) {
	
}

/* .data */
const ActorInit init_vars = {
	.id = 0xDEAD, .padding = 0xBEEF, // <-- magic values, do not change
	.category = ACTORCAT_PROP,
	.flags = 0x00000011, // enable Z targetting
	.objectId = OBJ_ID,
	.instanceSize = sizeof(Entity),
	.init = create,
	.destroy = destroy,
	.main = step,
	.draw = draw
};
