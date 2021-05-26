#include <z64ovl/oot/u10.h>
#include <z64ovl/z64ovl_helpers.h>
#include "obj.h"

extern s32 UnicornFountain_scene_header00_cutscene[];

// Actor Information
#define OBJ_ID 0x00A // primary object dependency (change if needed)
#define SWITCH_FLAG 0x20
#define NPC_ACTION_SLOT 5

#define RISE_FRAMES 40

#define SPIRAL_ROTATIONS 5
#define LEAN_FORWARD 0x1000
#define LEAN_RATIO 0.1f
#define CYCLE_PERIOD 60
#define CYCLE_HEIGHT 10.0f
#define FLOAT_CENTER_HEIGHT 60.0f

#define SCALE_TINY 0.001f
#define SCALE_MAIN 0.085f

#define CHECK_NPC_ACTION(num) \
	(global->cutscene.state != 0) \
	&& (global->cutscene.npc_action[NPC_ACTION_SLOT] != NULL) \
	&& (global->cutscene.npc_action[NPC_ACTION_SLOT]->action == num)

typedef struct {
	z64_actor_t actor;
	u8 state;
	u8 frames;
} entity_t;

static void init(entity_t *en, z64_global_t *global) {
	en->state = 0;
}

static void dest(entity_t *en, z64_global_t *global) {
	
}

static void play(entity_t *en, z64_global_t *global) {
	if(z_flags_switch_get(global, SWITCH_FLAG)){
		z_flags_switch_unset(global, SWITCH_FLAG);
		global->cutscene.ptr = (void*)zh_seg2ram((u32)(&UnicornFountain_scene_header00_cutscene));
		((z64_save_context_t*)(void*)Z64GL_SAVE_CONTEXT)->cutscene_trigger = 1;
	}
	en->actor.pos = en->actor.pos_init;
	en->actor.rot.x = 0; en->actor.rot.y = 0; en->actor.rot.z = 0;
	if(en->state == 0){
		//Away, waiting for NPC action
		z_actor_set_scale(&en->actor, SCALE_TINY);
		en->actor.pos.y -= 1000.0f;
		if(CHECK_NPC_ACTION(1)){
			++en->state;
			en->frames = 0;
		}
	}else if(en->state == 2){
		//Floating, waiting for NPC action
		z_actor_set_scale(&en->actor, SCALE_MAIN);
		float y = CYCLE_HEIGHT * z_sinf((float)en->frames * 
			(2.0f * 3.14159f / (float)CYCLE_PERIOD));
		en->actor.pos.z -= 30.0f;
		en->actor.pos.y += y + FLOAT_CENTER_HEIGHT;
		en->actor.rot.x = LEAN_FORWARD;
		++en->frames;
		if(en->frames >= CYCLE_PERIOD) en->frames = 0;
		if(CHECK_NPC_ACTION(2)){
			++en->state;
			en->frames = 0;
		}
	}else if(en->state == 1 || en->state == 3){
		//Rising or Falling
		if(en->frames == 0){
			z_actor_play_sfx(&(en->actor), 0x6858);
		}else if(en->state == 3 && en->frames == RISE_FRAMES - 1){
			z_actor_play_sfx(&(en->actor), 0x2880);
		}
		float ratio = (float)en->frames / (float)RISE_FRAMES;
		if(en->state == 1) ratio = 1.0f - ratio;
		float scale = ratio * (SCALE_TINY - SCALE_MAIN) + SCALE_MAIN;
		z_actor_set_scale(&en->actor, scale);
		float rot = (ratio * ratio) * SPIRAL_ROTATIONS * 0x10000;
		en->actor.rot.y = (s16)((s32)rot & 0xFFFF);
		if(en->state == 1) en->actor.rot.y = -en->actor.rot.y;
		if(ratio < LEAN_RATIO){
			float leanratio = 1.0f - (ratio / LEAN_RATIO);
			en->actor.rot.x = (s16)((float)LEAN_FORWARD * ratio);
		}
		en->actor.pos.y = ratio * (en->actor.pos_init.y - FLOAT_CENTER_HEIGHT) + FLOAT_CENTER_HEIGHT;
		++en->frames;
		if(en->frames == RISE_FRAMES){
			en->frames = 0;
			en->state = (en->state + 1) & 3;
		}
	}
}

static void draw(entity_t *en, z64_global_t *global) {
	draw_dlist_opa(global, DL_BETAGREATFAIRY);
	draw_dlist_xlu(global, DL_BETAGREATFAIRY_FLOWER);
}

const z64_actor_init_t init_vars = {
	.number = 0xDEAD, .padding = 0xBEEF, // <-- magic values, do not change
	.type = OVLTYPE_PROP,
	.room = 0x00,
	.flags = 0x00000010,
	.object = OBJ_ID,
	.instance_size = sizeof(entity_t),
	.init = init,
	.dest = dest,
	.main = play,
	.draw = draw
};
