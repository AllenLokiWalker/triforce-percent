#include "fast_loader.h"

#define RUMBLE_CRCFAIL 1
#define RUMBLE_Q_FALSE 2
#define RUMBLE_Q_TRUE 3
#define RUMBLE_INVALID 4
#define RUMBLE_NOP 5
#define RUMBLE_VALID 6


typedef struct {
	u8 unused1[656];
	raw_input_t pads[4];
	u8 unused2[10];
	u8 rumble_enable[4];
	u8 rumble_counter[4];
	u8 unused3[418];
	u8 rumble_off_frames;
	u8 rumble_on_frames;
	u8 unused4[10];
} __attribute__((packed)) padmgr_t;

extern padmgr_t padmgr;

#define POLLS 8
#define DATA_LEN (45 * ((POLLS) / 4))
#define COMMAND_LEN ((DATA_LEN) - 5)
#define HUGE_T_SIZE 23 /* ceiling((30 bits * 3 pads * 8 polls) / 32)*/

// Command format:
// 4 poll format: struct { u32 crc32; u8 data[40]; u8 command_id; }
// 8 poll format: struct { u32 crc32; u8 data[85]; u8 command_id; }
typedef union {
	struct {
		u32 crc;
		union {
			u8 bytes[COMMAND_LEN];
			
			// Command 1: Load 81 bytes to given address
			// Command 2: Load up to 80 bytes to given address
			struct {
				u8* address;
				u8  data[COMMAND_LEN - 5];
				u8  length; // Is last data byte when run as command 1
			} cmd01;
			
			// Command 3: Load X counts of byte Y to specified address
			struct {
				u8* address;
				u32 length;
				u8  byte;
				u8  padding[COMMAND_LEN - 9];
			} cmd03;
			
			// Command 4: DMA uncompressed data
			// Command 5: DMA compressed data
			struct {
				u32 vram;
				u32 vrom;
				u32 size;
				u8  padding[COMMAND_LEN - 12];
			} cmd04;
			
			// Command 6: Call command data as code
			//No need for a separate struct--just call `bytes`
			
			// Command 7: Call specified address with up to 4 args
			struct {
				void(*function_pointer)(s32 a0, s32 a1, s32 a2, s32 a3);
				s32 a0;
				s32 a1;
				s32 a2;
				s32 a3;
				u8  padding[COMMAND_LEN - 20];
			} cmd07;
			
		};
		u8 id;
	} command;
	u8 bytes[DATA_LEN];
} out_data_t;

static out_data_t out_data;

typedef struct {
	u32 blocks[HUGE_T_SIZE];
} huge_t;

static huge_t huge_data;

//Other data

static raw_input_t pad_data[4];
static u32 crc_table[256]; // 1024 bytes
void(*fp_precmd)(void);
void(*fp_postcmd)(void);

//Function prototypes

void fl_init();
static void fl_run(void* queue);
static void fl_rumble_message(u32 bits);
static u32 fl_crc_data(void* data, u32 size);
static int fl_huge_push_data(huge_t* n, u32 bits, u32 amount);
static u32 fl_huge_pop_data(huge_t* n, u32 amount);


// entry point
__attribute__((section(".start"))) void fl_init() {
	// generate CRC table
	u32 r, i; u8 counter;
	for(i = 0; i < 256; ++i) {
		r = i;
		for(counter = 0; counter < 8; ++counter)
			r = ((r & 1) ? 0 : 0xEDB88320) ^ (r >> 1);
		crc_table[i] = r ^ 0xFF000000;
	}
	
	// patch padmgr to call run() every frame
	*((u32*)0x800A2640) = 0x0C000000 | ((((u32)fl_run) >> 2) & 0x03FFFFFF); // construct jal to run() (also disable zeroing of pad 4)
	*((u32*)0x800A2644) = 0x8FA4002C; // first argument is address to queue
	
	// PadMgr_RumbleControl will only poll other controllers for rumble paks
	// if it hasn't attempted to send a rumble message to another controller
	// on the same frame. Since we're messing with the rumble pack sending
	// so that messages are sent every frame, once one controller is successfully
	// polled it'll get messages every frame and then no other controllers will
	// be polled for rumble pak. So, patch out the check so it will always
	// poll for rumble paks even if other rumble paks have been accessed this frame.
	// Line "if (!triedRumbleComm) {" in decomp
	// Instruction  B3E824 800C7684 16A00052   bnez  $s5, .L800C77D0 in Debug ROM
	// Instruction         800A21E4            bne    s3, $zero, lbl_800A22C0 in 1.0
	*((u32*)0x800A21E4) = 0;
	
	return;
}

// called by padmgr
static void fl_run(void* queue) {
	// Draw green bar in the corner
	const u64 green64 = 0x7c107c107c107c1ULL;
	(*((volatile u64**)0x8011F56C))[1286] = green64; // shifted two pixels to the right of the "real" one
	(*((volatile u64**)0x8011F56C))[1287] = green64; // due to longword alignment
	
	// Poll controllers
	u32 i;
	
	for(i = 0; i < (POLLS); ++i) {
		raw_input_t* p;
		
		// try to preserve the original pad input as polled by the original code
		if(!i) { // the first time, use pad data from the original game poll
			p = &padmgr.pads[0];
		} else { // afterwards, poll the pads ourselves, and discard data for pad 1
			bzero(pad_data, 24);
			p = pad_data;
			osContStartReadData(queue);
			osRecvMesg(queue, NULL, 1);
			osContGetReadData(p); // actually get the pad data
		}
		
		fl_huge_push_data(&huge_data, p[1].b1, 8);
		fl_huge_push_data(&huge_data, p[1].b2, 6);
		fl_huge_push_data(&huge_data, p[1].x,  8);
		fl_huge_push_data(&huge_data, p[1].y,  8);
		fl_huge_push_data(&huge_data, p[2].b1, 8);
		fl_huge_push_data(&huge_data, p[2].b2, 6);
		fl_huge_push_data(&huge_data, p[2].x,  8);
		fl_huge_push_data(&huge_data, p[2].y,  8);
		fl_huge_push_data(&huge_data, p[3].b1, 8);
		fl_huge_push_data(&huge_data, p[3].b2, 6);
		fl_huge_push_data(&huge_data, p[3].x,  8);
		fl_huge_push_data(&huge_data, p[3].y,  8);
	}
	
	if(fp_precmd) fp_precmd();
	
	i = DATA_LEN;
	while(i > 0) {
		--i;
		out_data.bytes[i] = fl_huge_pop_data(&huge_data, 8);
	}
	
	// CRC everything except for the CRC itself
	u8 rumble_result;
	if(out_data.command.id == 0){
		rumble_result = RUMBLE_NOP;
	} else if(fl_crc_data(out_data.command.bytes, DATA_LEN - 4) != out_data.command.crc) {
		rumble_result = RUMBLE_CRCFAIL;
	} else {
		rumble_result = RUMBLE_VALID;
		switch(out_data.command.id) {
			
			case 1: //   fixed 81 byte size
			case 2: { // up to 80 byte size
				int i, len;
				len = out_data.command.id == 1 ? COMMAND_LEN - 4 : out_data.command.cmd01.length;
				for(i = 0; i < len; ++i)
					*(out_data.command.cmd01.address++) = out_data.command.cmd01.data[i];
			} break;
			
			case 3: { // load X counts of byte Y to specified address
				while(out_data.command.cmd03.length > 0) {
					*(out_data.command.cmd03.address++) = out_data.command.cmd03.byte;
					--out_data.command.cmd03.length;
				}
			} break;
			
			case 4: { // DMA uncompressed data
				DmaMgr_SendRequest0(
					out_data.command.cmd04.vram,
					out_data.command.cmd04.vrom,
					out_data.command.cmd04.size
				);
			} break;
			
			case 5: { // DMA compressed data
				Yaz0_Decompress(
					out_data.command.cmd04.vrom,
					out_data.command.cmd04.vram,
					out_data.command.cmd04.size
				);
			} break;
			
			case 6: { // Treat command data as instructions and jump to them (can execute `2.5 * POLLS` instructions)
				osWritebackDCache(NULL, 0x4000);
				osInvalICache(NULL, 0x4000);
				((void(*)(void))&out_data.command.bytes)();
			} break;
			
			case 7: { // Call specified address
				out_data.command.cmd07.function_pointer(
					out_data.command.cmd07.a0,
					out_data.command.cmd07.a1,
					out_data.command.cmd07.a2,
					out_data.command.cmd07.a3
				);
			} break;
			
			default: {
				rumble_result = RUMBLE_INVALID;
			} break;
		}
	}
	fl_rumble_message(rumble_result);
	
	if(fp_postcmd) fp_postcmd();
	
	// zero pads 1 and 3 ourselves
	bzero(&padmgr.pads[1], 6);
	bzero(&padmgr.pads[3], 6);
	
	return;
}

static void fl_rumble_message(u32 bits) {
	int i;
	padmgr.rumble_on_frames = 0xF0; // ???
	for(i = 1; i < 4; ++i) {
		padmgr.rumble_counter[i] = 2;
		padmgr.rumble_enable[i] = bits & 1;
		bits >>= 1;
	}	
}

static u32 fl_crc_data(void* data, u32 size) {
	u32 state;
	state = 0U;
	while(size) {
		state = crc_table[(state & 0xFF) ^ *((u8*)data)] ^ (state >> 8);
		++data;
		--size;
	}
	return state;
}

static int fl_huge_shift_up(huge_t* n, u32 amount) {
	u32 i;
	for(i = 0; i < (HUGE_T_SIZE - 1); ++i) {
		n->blocks[i] <<= amount;
		n->blocks[i]  |= (n->blocks[i + 1] >> (32 - amount));
	}
	n->blocks[i] <<= amount;
	return 1;
}

static int fl_huge_shift_down(huge_t* n, u32 amount) {
	u32 i;
	for(i = HUGE_T_SIZE - 1; i > 0; --i) {
		n->blocks[i] >>= amount;
		n->blocks[i]  |= (n->blocks[i - 1] << (32 - amount));
	}
	n->blocks[i] >>= amount;
	return 1;
}

static int fl_huge_push_data(huge_t* n, u32 bits, u32 amount) {
	fl_huge_shift_up(n, amount);
	n->blocks[HUGE_T_SIZE - 1] |= (bits & (~(0xFFFFFFFF << amount)));
	return 0;
}

static u32 fl_huge_pop_data(huge_t* n, u32 amount) {
	u32 mask, r;
	mask = 0xFFFFFFFF; mask <<= amount; mask = ~mask;
	r = n->blocks[HUGE_T_SIZE - 1];
	r &= mask;
	fl_huge_shift_down(n, amount);
	return (u32)r;
}
