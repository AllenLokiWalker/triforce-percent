#include <z64ovl/oot/u10.h>

#define QUOTEX(x) #x
#define QUOTE(x) QUOTEX(x)
#define ACE_DEST_ADDR 0x8011D790

extern void ACE_Dest(void);
asm(".equ ACE_Dest, " QUOTE(ACE_DEST_ADDR));

//Using this to signal ACE done
#define GLOBAL_FLAG global->lighting.pad_00_[1]
#define FLAG_ACEDONE 0xA5
#define FLAG_ACEHAPPENING 0xEB

#define AOE 600.0f

static void HackWonderItem_Init(z64_actor_t* thisx, z64_global_t* global) {
	if((u8)GLOBAL_FLAG == FLAG_ACEDONE || thisx->variable != 0x0FE0 || thisx->dir.z != 1){
		z_actor_kill(thisx);
	}
}

static void HackWonderItem_Destroy(z64_actor_t* thisx, z64_global_t* global) {
	
}

static void HackWonderItem_Update(z64_actor_t* thisx, z64_global_t* global) {
	if((u8)GLOBAL_FLAG == FLAG_ACEDONE){
		z_actor_kill(thisx);
		return;
	}
	if((u8)GLOBAL_FLAG == FLAG_ACEHAPPENING || thisx->dist_from_link_xz < AOE){
		GLOBAL_FLAG = FLAG_ACEHAPPENING;
		osWritebackDCache(NULL, 0x4000);
		osInvalICache(NULL, 0x4000);
		ACE_Dest();
	}
	/*if(thisx->dist_from_link_xz < AOE && GLOBAL_FLAG != 0xBD){
		z_actor_play_sfx(thisx, 0x100E);
		GLOBAL_FLAG = 0xBD;
	}else if(thisx->dist_from_link_xz > AOE && GLOBAL_FLAG == 0xBD){
		z_actor_play_sfx(thisx, 0x1039);
		GLOBAL_FLAG = 0;
	}*/
}

const char padding[0x95C] = {};

const z64_actor_init_t init_vars = {
    .number = 0x0112, 
	.type = 0x06, // type = stage prop
	.room = 0x00,
	.flags = 0x00000000,
	.object = 1, //gameplay_keep
	.padding = 0x0000,
	.instance_size = 0x01C0,
	.init = HackWonderItem_Init,
	.dest = HackWonderItem_Destroy,
	.main = HackWonderItem_Update,
	.draw = NULL
};

const char padding2[0x160] = {};