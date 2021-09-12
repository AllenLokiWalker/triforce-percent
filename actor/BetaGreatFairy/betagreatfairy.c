#include "ootmain.h"
#include "obj.h"
#include "../../statics/statics.h"

extern s32 UnicornFountain_scene_header00_cutscene[];

// Actor Information
#define OBJ_ID 0x00A // primary object dependency (change if needed)
#define SWITCH_FLAG 0x20
#define FAIRY_SLOT 5

#define RISE_FRAMES 40

#define SPIRAL_ROTATIONS 4
#define LEAN_FORWARD 0x1000
#define LEAN_SHIFT_Z 30.0f
#define LEAN_RATIO 0.15f
#define CYCLE_PERIOD 60.0f
#define CYCLE_HEIGHT 10.0f
#define FLOAT_CENTER_HEIGHT 60.0f

#define SCALE_TINY 0.001f
#define SCALE_MAIN 0.085f

typedef struct {
	Actor actor;
	u8 state;
	u8 frames;
	float lastFloatY;
} Entity;

static void init(Entity *en, GlobalContext *globalCtx) {
	en->state = 0;
}

static void destroy(Entity *en, GlobalContext *globalCtx) {
	
}

static void update(Entity *en, GlobalContext *globalCtx) {
	if(Flags_GetSwitch(globalCtx, SWITCH_FLAG)){
		Flags_UnsetSwitch(globalCtx, SWITCH_FLAG);
		globalCtx->csCtx.segment = SEGMENTED_TO_VIRTUAL(&UnicornFountain_scene_header00_cutscene);
		gSaveContext.cutsceneTrigger = 1;
	}
	en->actor.world.pos = en->actor.home.pos;
	en->actor.shape.rot.x = 0; en->actor.shape.rot.y = 0; en->actor.shape.rot.z = 0;
	if(en->state == 0){
		//Away, waiting for NPC action
		Actor_SetScale(&en->actor, SCALE_TINY);
		en->actor.world.pos.y -= 1000.0f;
		en->lastFloatY = FLOAT_CENTER_HEIGHT;
		if(CHECK_NPC_ACTION(FAIRY_SLOT, 1)){
			Statics_GiveOvertureOfSages();
			en->frames = 0;
			++en->state;
		}
	}else if(en->state == 2){
		//Floating, waiting for NPC action
		Actor_SetScale(&en->actor, SCALE_MAIN);
		float y = CYCLE_HEIGHT * sinf((float)en->frames * 
			(2.0f * 3.14159f / CYCLE_PERIOD));
		en->actor.world.pos.z -= LEAN_SHIFT_Z;
		en->actor.world.pos.y += y + FLOAT_CENTER_HEIGHT;
		en->lastFloatY = en->actor.world.pos.y;
		en->actor.shape.rot.x = LEAN_FORWARD;
		++en->frames;
		if(en->frames >= CYCLE_PERIOD) en->frames = 0;
		if(CHECK_NPC_ACTION(FAIRY_SLOT, 2)){
			en->frames = 0;
			++en->state;
		}
	}else if(en->state == 1 || en->state == 3){
		//Rising or Falling
		if(en->frames == 0){
			Audio_PlayActorSound2(&(en->actor), NA_SE_VO_FR_LAUGH_0);
		}else if(en->frames == 1){
			Audio_PlayActorSound2(&(en->actor), en->state == 3 ? 
				NA_SE_EV_GREAT_FAIRY_VANISH : NA_SE_EV_GREAT_FAIRY_APPEAR);
		}
		float ratio = (float)en->frames / (float)RISE_FRAMES;
		if(en->state == 1) ratio = 1.0f - ratio;
		float scale = ratio * (SCALE_TINY - SCALE_MAIN) + SCALE_MAIN;
		Actor_SetScale(&en->actor, scale);
		en->actor.world.pos.y += (1.0f - ratio) * en->lastFloatY;
		float rot = (ratio * ratio) * SPIRAL_ROTATIONS * 0x10000;
		en->actor.shape.rot.y = (s16)((s32)rot & 0xFFFF);
		if(en->state == 1) en->actor.shape.rot.y = -en->actor.shape.rot.y;
		if(ratio < LEAN_RATIO){
			float leanratio = 1.0f - (ratio / LEAN_RATIO);
			en->actor.shape.rot.x = (s16)((float)LEAN_FORWARD * leanratio);
			en->actor.world.pos.z -= leanratio * LEAN_SHIFT_Z;
		}
		++en->frames;
		if(en->frames == RISE_FRAMES){
			en->frames = 0;
			en->state = (en->state + 1) & 3;
		}
	}
}

static void draw(Entity *en, GlobalContext *globalCtx) {
	Gfx_DrawDListOpa(globalCtx, (Gfx*)DL_BETAGREATFAIRY);
	Gfx_DrawDListXlu(globalCtx, (Gfx*)DL_BETAGREATFAIRY_FLOWER);
}

const ActorInitExplPad init_vars = {
	.id = 0xDEAD, .padding = 0xBEEF, // <-- magic values, do not change
	.category = ACTORCAT_PROP,
	.flags = 0x00000010,
	.objectId = OBJ_ID,
	.instanceSize = sizeof(Entity),
	.init = (ActorFunc)init,
	.destroy = (ActorFunc)destroy,
	.update = (ActorFunc)update,
	.draw = (ActorFunc)draw
};
