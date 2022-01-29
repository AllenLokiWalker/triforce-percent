#include "ootmain.h"
#include "BotWZeldaMesh.h"
#include "../loader/debugger/debugger.h"
#include "../statics/hairphys.h"
#include "../statics/statics.h"
#include "../statics/anime.h"

// Actor Information
#define OBJ_ID 125 // primary object dependency
#define ACTOR_SCALE 0.035f

typedef struct {
	Actor actor;
} Entity;

static void init(Entity *en, GlobalContext *globalCtx) {
	//General setup
	Rupees_ChangeBy(7);
	Actor_SetScale(&en->actor, ACTOR_SCALE);
	//Components setup
	ActorShape_Init(&en->actor.shape, 0.0f, ActorShadow_DrawCircle, 30.0f); //TODO not working?
}

static void destroy(Entity *en, GlobalContext *globalCtx) {
	//
}

static void update(Entity *en, GlobalContext *globalCtx) {
	//
}

s32 BotWZelda_OverrideLimbDraw(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, void* thisx) {
	//Entity *en = (Entity*)thisx;
	return false;
}

void BotWZelda_PostLimbDraw(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3s* rot, void* thisx) {
	//Entity *en = (Entity*)thisx;
	(void)0;
}

static void draw(Entity *en, GlobalContext *globalCtx) {
	func_80093D18(globalCtx->state.gfxCtx);
	Gfx_DrawDListOpa(globalCtx, BotWZeldaMesh);
	func_80093D18(globalCtx->state.gfxCtx);
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
