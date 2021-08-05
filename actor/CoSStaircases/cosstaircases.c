#include "ootmain.h"
#include "SariaStair.h"
#include "SariaStairCollision.h"
#include "DaruniaStair.h"
#include "DaruniaStairCollision.h"
#include "TriforceStair.h"
#include "TriforceStairCollision.h"

// Actor Information
#define OBJ_ID 17 // primary object dependency

/*
 * a 0xA6 o 0xA7 En_Rl:   slot 0 (number 39). No rise. 2: stand, 3: pose
 * a 0xC9 o 0xBC Demo_Sa: slot 4 (number 43). Probably params 0. 1: rise, 2: stand, 3: pose
 * a 0xA8 o 0x9D Demo_Du: slot 2 (number 41). Same
 * a 0xD2 o 0xCA En_Ru2:  slot 3 (number 42). Same
 * a 0xC3 o 0xB3 En_Nb:   slot 1 (number 40). Same
 * a 0xA9 o 0x87 Demo_Im: slot 5 (number 44). Same
 * a 0x48 o 0x8A En_Xc:   slots 0 and 4
*/
#define STAIRS_SLOT 9

#define CS_ACTIVATE_RADIUS 120.0f

typedef struct {
	DynaPolyActor dyna;
	u8 state;
	u8 alpha;
	u8 collision;
	u8 cutscene_activated;
} Entity;

static Gfx * const DLists[] = {
	SariaStair,
	DaruniaStair, DaruniaStair, DaruniaStair, DaruniaStair, DaruniaStair, 
	TriforceStair
};

static CollisionHeader * const ColHeaders[] = {
	SariaStairCollision_collisionHeader,
	DaruniaStairCollision_collisionHeader,
	DaruniaStairCollision_collisionHeader,
	DaruniaStairCollision_collisionHeader,
	DaruniaStairCollision_collisionHeader,
	DaruniaStairCollision_collisionHeader,
	TriforceStairCollision_collisionHeader
};

extern s32 ChamberOfSages_scene_header00_cutscene[];
extern s32 ChamberOfSages_scene_header04_cutscene[];
extern s32 ChamberOfSages_scene_header05_cutscene[];
extern s32 ChamberOfSages_scene_header06_cutscene[];
extern s32 ChamberOfSages_scene_header07_cutscene[];
extern s32 ChamberOfSages_scene_header08_cutscene[];
extern s32 ChamberOfSages_scene_header09_cutscene[];

static s32 * const Cutscenes[] = {
	ChamberOfSages_scene_header00_cutscene,
	ChamberOfSages_scene_header04_cutscene,
	ChamberOfSages_scene_header05_cutscene,
	ChamberOfSages_scene_header06_cutscene,
	ChamberOfSages_scene_header07_cutscene,
	ChamberOfSages_scene_header08_cutscene,
	ChamberOfSages_scene_header09_cutscene
}

//#define COLLISION_OFF() func_8003EBF8(globalCtx, &globalCtx->colCtx.dyna, en->dyna.bgId)
//#define COLLISION_ON()  func_8003EC50(globalCtx, &globalCtx->colCtx.dyna, en->dyna.bgId)

static void CreateCollision(Entity *en, GlobalContext *globalCtx){
	CollisionHeader* colHeaderVRAM;
	DynaPolyActor_Init(&en->dyna, DPM_UNK);
	CollisionHeader_GetVirtual(ColHeaders[en->dyna.actor.params], &colHeaderVRAM);
    en->dyna.bgId = DynaPoly_SetBgActor(globalCtx, 
		&globalCtx->colCtx.dyna, &en->dyna.actor, colHeaderVRAM);
	en->collision = 1;
}

static void DestroyCollision(Entity *en, GlobalContext *globalCtx){
	DynaPoly_DeleteBgActor(globalCtx, &globalCtx->colCtx.dyna, en->dyna.bgId);
	en->collision = 0;
}

static void init(Entity *en, GlobalContext *globalCtx) {
	en->state = 0;
	en->alpha = 0;
	en->collision = 0;
	en->cutscene_activated = 0;
	if((u16)en->dyna.actor.params >= 7){
		Actor_Kill(&en->dyna.actor);
		return;
	}
	Actor_SetScale(&en->dyna.actor, 0.1f);
	if(en->dyna.actor.params == 0){
		CreateCollision(en, globalCtx);
	}
}

static void destroy(Entity *en, GlobalContext *globalCtx) {
	if(en->collision) DestroyCollision(en, globalCtx);
}

static void update(Entity *en, GlobalContext *globalCtx) {
	if(!en->collision && CHECK_NPC_ACTION(STAIRS_SLOT, en->dyna.actor.params + 1)){
		CreateCollision(en, globalCtx);
		en->state = 1;
	}else if(en->collision && CHECK_NPC_ACTION(STAIRS_SLOT, 0)){
		DestroyCollision(en, globalCtx);
		en->state = 2;
	}
	s32 temp = en->alpha;
	if(en->state == 1){
		temp += 4;
		if(temp >= 255){
			temp = 255;
			en->state = 0;
		}
	}else if(en->state == 2){
		temp -= 4;
		if(temp <= 0){
			temp = 0;
			en->state = 0;
		}
	}
	en->alpha = temp;
	if(!en->cutscene_activated && en->dyna.actor.xzDistToPlayer < CS_ACTIVATE_RADIUS){
		globalCtx->csCtx.segment = SEGMENTED_TO_VIRTUAL(Cutscenes[en->dyna.actor.params]);
		gSaveContext.cutsceneTrigger = 1;
		en->cutscene_activated = 1;
	}
}

static void draw(Entity *en, GlobalContext *globalCtx) {
	if(en->alpha == 0) return;
	gDPSetEnvColor(POLY_XLU_DISP++, 0xFF, 0xFF, 0xFF, en->alpha);
	Gfx_DrawDListXlu(globalCtx, DLists[en->dyna.actor.params]);
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
