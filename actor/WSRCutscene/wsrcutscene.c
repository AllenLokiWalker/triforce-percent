#include "ootmain.h"
#include "tokinoma_cs.c"
#include "../../statics/statics.h"

typedef struct {
	Actor actor;
	u8 mode;
	u8 timer;
} Entity;

static void init(Entity *en, GlobalContext *globalCtx) {
	en->mode = 1;
	en->timer = 0;
	if(globalCtx->sceneNum != SCENE_TOKINOMA) en->mode = 0;
	static const Vec3f masterSwordPos = {-1.0f, 68.0f, 0.0f};
    Vec3f playerPos = PLAYER->actor.world.pos;
    float sqDistFromMS = SQ(playerPos.x - masterSwordPos.x) 
        + SQ(playerPos.y - masterSwordPos.y) + SQ(playerPos.z - masterSwordPos.z);
    if(sqDistFromMS > 2500.0f) en->mode = 0;
	if(!en->mode){
		gSaveContext.unk_13EE = 50; //try to make interface back to normal
	    Interface_ChangeAlpha(gSaveContext.unk_13EE);
	}else{
		globalCtx->csCtx.segment = &WarpToSacredRealmCS;
		gSaveContext.cutsceneTrigger = 1;
	}
}

static void destroy(Entity *en, GlobalContext *globalCtx) {}

static void update(Entity *en, GlobalContext *globalCtx){
	if(!en->mode){
		if(en->timer == 3){
			func_8010B680(globalCtx, 0x0D30, NULL); //Message_Start
			Actor_Kill(&en->actor);
		}
	}
	++en->timer;
}

static void draw(Entity *en, GlobalContext *globalCtx) {}

const ActorInit init_vars = {
	.id = 0xDEAD, .padding = 0xBEEF, // <-- magic values, do not change
	.category = ACTORCAT_BG,
	.flags = 0x00000010,
	.objectId = GAMEPLAY_KEEP,
	.instanceSize = sizeof(Entity),
	.init = (ActorFunc)init,
	.destroy = (ActorFunc)destroy,
	.update = (ActorFunc)update,
	.draw = (ActorFunc)draw
};