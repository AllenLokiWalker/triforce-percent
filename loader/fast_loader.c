#include "fast_loader.h"

// entry point
void fl_init() __attribute__((section(".start"))){
	// generate CRC table
	u32 r, i; u8 counter;
	for(i = 0; i < 256; ++i) {
		r = i;
		for(counter = 0; counter < 8; ++counter)
			r = ((r & 1) ? 0 : 0xEDB88320) ^ (r >> 1);
		fl_gvars.crc_table[i] = r ^ 0xFF000000;
	}
	
	// patch padmgr to call run() every frame
	*((u32*)0x800A2640) = 0x0C000000 | ((((u32)fl_run) >> 2) & 0x03FFFFFF); // construct jal to run() (also disable zeroing of pad 4)
	*((u32*)0x800A2644) = 0x8FA4002C; // first argument is address to queue
	
	return;
}

// called by padmgr
void fl_run(void* queue) {
	// Draw green bar in the corner
	const u64 green64 = 0x7c107c107c107c1ULL;
	(*((volatile u64**)0x8011F56C))[1286] = green64; // shifted two pixels to the right of the "real" one
	(*((volatile u64**)0x8011F56C))[1287] = green64; // due to longword alignment
	
	// Poll controllers
	u32 i;
	
	for(i = 0; i < (POLLS); ++i) {
		raw_input_t* pad_data;
		
		// try to preserve the original pad input as polled by the original code
		if(!i) { // the first time, use pad data from the original game poll
			pad_data = &padmgr.pads[0];
		} else { // afterwards, poll the pads ourselves, and discard data for pad 1
			bzero(fl_gvars.pad_data, 24);
			pad_data = fl_gvars.pad_data;
			osContStartReadData(queue);
			osRecvMesg(queue, NULL, 1);
			osContGetReadData(pad_data); // actually get the pad data
		}
		
		fl_huge_push_data(&fl_gvars.huge, pad_data[1].b1, 8);
		fl_huge_push_data(&fl_gvars.huge, pad_data[1].b2, 6);
		fl_huge_push_data(&fl_gvars.huge, pad_data[1].x,  8);
		fl_huge_push_data(&fl_gvars.huge, pad_data[1].y,  8);
		fl_huge_push_data(&fl_gvars.huge, pad_data[2].b1, 8);
		fl_huge_push_data(&fl_gvars.huge, pad_data[2].b2, 6);
		fl_huge_push_data(&fl_gvars.huge, pad_data[2].x,  8);
		fl_huge_push_data(&fl_gvars.huge, pad_data[2].y,  8);
		fl_huge_push_data(&fl_gvars.huge, pad_data[3].b1, 8);
		fl_huge_push_data(&fl_gvars.huge, pad_data[3].b2, 6);
		fl_huge_push_data(&fl_gvars.huge, pad_data[3].x,  8);
		fl_huge_push_data(&fl_gvars.huge, pad_data[3].y,  8);
	}
	
	if(fl_gvars.fp_precmd) fl_gvars.fp_precmd();
	
	i = DATA_LEN;
	while(i > 0) {
		--i;
		fl_gvars.out.bytes[i] = fl_huge_pop_data(&fl_gvars.huge, 8);
	}
	
	// CRC everything except for the CRC itself
	u8 rumble_result;
	if(fl_crc_data(fl_gvars.out.command.bytes, DATA_LEN - 4) != fl_gvars.out.command.crc) {
		rumble_result = RUMBLE_CRCFAIL;
	} else {
		rumble_result = RUMBLE_VALID;
		switch(fl_gvars.out.command.id) {
			
			case 1: //   fixed 81 byte size
			case 2: { // up to 80 byte size
				int i, len;
				len = fl_gvars.out.command.id == 1 ? COMMAND_LEN - 4 : fl_gvars.out.command.cmd01.length;
				for(i = 0; i < len; ++i)
					*(fl_gvars.out.command.cmd01.address++) = fl_gvars.out.command.cmd01.data[i];
			} break;
			
			case 3: { // load X counts of byte Y to specified address
				while(fl_gvars.out.command.cmd03.length > 0) {
					*(fl_gvars.out.command.cmd03.address++) = fl_gvars.out.command.cmd03.byte;
					--fl_gvars.out.command.cmd03.length;
				}
			} break;
			
			case 4: { // DMA uncompressed data
				DmaMgr_SendRequest0(
					fl_gvars.out.command.cmd04.vram,
					fl_gvars.out.command.cmd04.vrom,
					fl_gvars.out.command.cmd04.size
				);
			} break;
			
			case 5: { // DMA compressed data
				Yaz0_Decompress(
					fl_gvars.out.command.cmd04.vrom,
					fl_gvars.out.command.cmd04.vram,
					fl_gvars.out.command.cmd04.size
				);
			} break;
			
			case 6: { // Treat command data as instructions and jump to them (can execute `2.5 * POLLS` instructions)
				osWritebackDCache(NULL, 0x4000);
				osInvalICache(NULL, 0x4000);
				((void(*)(void))&fl_gvars.out.command.cmd06.instructions)();
			} break;
			
			case 7: { // Call specified address
				fl_gvars.out.command.cmd07.function_pointer(
					fl_gvars.out.command.cmd07.a0,
					fl_gvars.out.command.cmd07.a1,
					fl_gvars.out.command.cmd07.a2,
					fl_gvars.out.command.cmd07.a3,
				);
			} break;
			
			default: { //NOP
				rumble_result = RUMBLE_NOP;
			} break;
		}
	}
	fl_rumble_message(rumble_result);
	
	if(fl_gvars.fp_postcmd) fl_gvars.fp_postcmd();
	
	// zero pads 1 and 3 ourselves
	bzero(&padmgr.pads[1], 6);
	bzero(&padmgr.pads[3], 6);
	
	return;
}

void fl_rumble_message(u32 bits) {
	int i;
	padmgr.rumble_on_frames = 0xF0; // ???
	for(i = 1; i < 4; ++i) {
		padmgr.rumble_counter[i] = 2;
		padmgr.rumble_enable[i] = bits & 1;
		bits >>= 1;
	}	
}

u32 fl_crc_data(void* data, u32 size) {
	u32 state;
	state = 0U;
	while(size) {
		state = fl_gvars.crc_table[(state & 0xFF) ^ *((u8*)data)] ^ (state >> 8);
		++data;
		--size;
	}
	return state;
}

int fl_huge_shift_up(huge_t* n, u32 amount) {
	u32 i;
	for(i = 0; i < (HUGE_T_SIZE - 1); ++i) {
		n->blocks[i] <<= amount;
		n->blocks[i]  |= (n->blocks[i + 1] >> (32 - amount));
	}
	n->blocks[i] <<= amount;
	return 1;
}

int fl_huge_shift_down(huge_t* n, u32 amount) {
	u32 i;
	for(i = HUGE_T_SIZE - 1; i > 0; --i) {
		n->blocks[i] >>= amount;
		n->blocks[i]  |= (n->blocks[i - 1] << (32 - amount));
	}
	n->blocks[i] >>= amount;
	return 1;
}

int fl_huge_push_data(huge_t* n, u32 bits, u32 amount) {
	fl_huge_shift_up(n, amount);
	n->blocks[HUGE_T_SIZE - 1] |= (bits & (~(0xFFFFFFFF << amount)));
	return 0;
}

u32 fl_huge_pop_data(huge_t* n, u32 amount) {
	u32 mask, r;
	mask = 0xFFFFFFFF; mask <<= amount; mask = ~mask;
	r = n->blocks[HUGE_T_SIZE - 1];
	r &= mask;
	fl_huge_shift_down(n, amount);
	return (u32)r;
}
