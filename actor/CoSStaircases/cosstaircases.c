#include "ootmain.h"
#include "SariaStair.h"
#include "SariaStairCollision.h"
#include "DaruniaStair.h"
#include "DaruniaStairCollision.h"
#include "TriforceStair.h"
#include "TriforceStairCollision.h"

// Actor Information
#define OBJ_ID 17 // primary object dependency
#define MIN_ALPHA_COLLISION 0x20

#define COSS_FLAG_INITTED 1
#define COSS_FLAG_ACTIVE 2
#define COSS_FLAG_COLLISION 4

typedef struct {
	DynaPolyActor dyna;
	Gfx *dlist;
	u16 frame;
	u8 alpha;
	u8 flags;
} Entity;

#define COLLISION_OFF() func_8003EBF8(globalCtx, &globalCtx->colCtx.dyna, en->dyna.bgId)
#define COLLISION_ON()  func_8003EC50(globalCtx, &globalCtx->colCtx.dyna, en->dyna.bgId)

static void init(Entity *en, GlobalContext *globalCtx) {
	CollisionHeader* colHeaderSegmented;
	CollisionHeader* colHeaderVRAM;
	en->flags = 0;
	if(en->dyna.actor.params == 0){
		en->dlist = SariaStair;
		colHeaderSegmented = &SariaStairCollision_collisionHeader;
	}else if(en->dyna.actor.params <= 2){
		en->dlist = DaruniaStair;
		colHeaderSegmented = &DaruniaStairCollision_collisionHeader;
	}else if(en->dyna.actor.params == 6){
		en->dlist = TriforceStair;
		colHeaderSegmented = &TriforceStairCollision_collisionHeader;
	}else{
		Actor_Kill(&en->dyna.actor);
		return;
	}
	DynaPolyActor_Init(&en->dyna, DPM_UNK);
	CollisionHeader_GetVirtual(colHeaderSegmented, &colHeaderVRAM);
    en->dyna.bgId = DynaPoly_SetBgActor(globalCtx, 
		&globalCtx->colCtx.dyna, &en->dyna.actor, colHeaderVRAM);
	//COLLISION_OFF();
	Actor_SetScale(&en->dyna.actor, 0.1f);
	en->frame = 0;
	en->alpha = 0;
	en->flags = COSS_FLAG_INITTED;
}

static void destroy(Entity *en, GlobalContext *globalCtx) {
	if(!(en->flags & COSS_FLAG_INITTED)) return;
	DynaPoly_DeleteBgActor(globalCtx, &globalCtx->colCtx.dyna, en->dyna.bgId);
}

static void update(Entity *en, GlobalContext *globalCtx) {
	++en->alpha;
	if(en->alpha >= MIN_ALPHA_COLLISION && !(en->flags & COSS_FLAG_COLLISION)){
		//COLLISION_ON();
		en->flags |= COSS_FLAG_COLLISION;
	}else if(en->alpha < MIN_ALPHA_COLLISION && (en->flags & COSS_FLAG_COLLISION)){
		//COLLISION_OFF();
		en->flags &= ~COSS_FLAG_COLLISION;
	}
}

static void draw(Entity *en, GlobalContext *globalCtx) {
	if(en->alpha == 0) return;
	gDPSetEnvColor(POLY_XLU_DISP++, 0xFF, 0xFF, 0xFF, en->alpha);
	Gfx_DrawDListXlu(globalCtx, en->dlist);
}

const ActorInit init_vars = {
	.id = 0xDEAD, .padding = 0xBEEF, // <-- magic values, do not change
	.category = ACTORCAT_PROP,
	.flags = 0x00000030,
	.objectId = OBJ_ID,
	.instanceSize = sizeof(Entity),
	.init = (ActorFunc)init,
	.destroy = (ActorFunc)destroy,
	.update = (ActorFunc)update,
	.draw = (ActorFunc)draw
};
