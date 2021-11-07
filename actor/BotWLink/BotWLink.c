#include "ootmain.h"
#include "BotWLinkMesh.h"

// Actor Information
#define OBJ_ID 122 // primary object dependency

typedef struct {
	Actor actor;
} Entity;

static void init(Entity *en, GlobalContext *globalCtx) {
	Actor_SetScale(&en->actor, 0.1f);
	Rupees_ChangeBy(4);
}

static void destroy(Entity *en, GlobalContext *globalCtx) {
	
}

static void update(Entity *en, GlobalContext *globalCtx) {
	
}

static void draw(Entity *en, GlobalContext *globalCtx) {
	func_80093D18(globalCtx->state.gfxCtx);
	Gfx_DrawDListOpa(globalCtx, BotWLinkMesh);
	func_80093D18(globalCtx->state.gfxCtx);
}

const ActorInitExplPad init_vars = {
	.id = 0xDEAD, .padding = 0xBEEF, // <-- magic values, do not change
	.category = ACTORCAT_PROP,
	.flags = 0x00000000,
	.objectId = OBJ_ID,
	.instanceSize = sizeof(Entity),
	.init = (ActorFunc)init,
	.destroy = (ActorFunc)destroy,
	.update = (ActorFunc)update,
	.draw = (ActorFunc)draw
};
