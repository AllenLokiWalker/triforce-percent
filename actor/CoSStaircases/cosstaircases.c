#include "ootmain.h"
#include "RauruStair.h"
#include "RauruStairCollision.h"
#include "SariaStair.h"
#include "SariaStairCollision.h"
#include "SheikStair.h"
#include "SheikStairCollision.h"
#include "TriforceFadeWall.h"
#include "TriforceHallway.h"
#include "TriforceDoor.h"
#include "TriforceDoorCollision.h"

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
 
spaceSize for Object_InitBank calculations:
Adult Link object: 222 KiB
gameplay_keep: 368 KiB
gameplay_field_keep: 53 KiB
rl: 31 KiB
sa: 85 KiB
du: 74 KiB
ru2: 63 KiB
nb: 97 KiB
im: 73 KiB
xc: 115 KiB
Total without stairs: 1181 KiB
Stairs: currently 33 KiB
Total plus a bit extra: 1220 KiB -> 1250000
*/
#define STAIRS_SLOT 9 //actor number 0x8F

#define CS_ACTIVATE_RADIUS 120.0f
#define DOOR_OPEN_DIST 255.0f
#define DOOR_OPEN_SPEED 4.0f

typedef struct {
	DynaPolyActor dyna;
	u8 state;
	u8 alpha;
	u8 collision;
	u8 cutscene_activated;
} Entity;

/*
Actor parameter:
0: Rauru stairs
1-5: Saria stairs (Saria, Darunia, Ruto, Nabooru, Impa)
6: Sheik stairs
7: Triforce fade wall
8: Triforce hallway
9: Triforce door
*/

static Gfx * const DLists[] = {
	RauruStair,
	SariaStair, SariaStair, SariaStair, SariaStair, SariaStair, 
	SheikStair,
	TriforceFadeWall, TriforceHallway, TriforceDoor
};

static const u8 DListsTransparent[] = {
	1, 1, 1, 1, 1, 1, 1, 1, 0, 0
};

static CollisionHeader * const ColHeaders[] = {
	&RauruStairCollision_collisionHeader,
	&SariaStairCollision_collisionHeader,
	&SariaStairCollision_collisionHeader,
	&SariaStairCollision_collisionHeader,
	&SariaStairCollision_collisionHeader,
	&SariaStairCollision_collisionHeader,
	&SheikStairCollision_collisionHeader,
	NULL,
	NULL,
	&TriforceDoorCollision_collisionHeader,
};

extern s32 CS1Saria[];
extern s32 CS2Darunia[];
extern s32 CS3Ruto[];
extern s32 CS4Nabooru[];
extern s32 CS5Impa[];
extern s32 CS6Sheik[];

static s32 * const Cutscenes[] = {
	NULL,
	CS1Saria,
	CS2Darunia,
	CS3Ruto,
	CS4Nabooru,
	CS5Impa,
	CS6Sheik,
	NULL,
	NULL,
	NULL
};

//#define COLLISION_OFF() func_8003EBF8(globalCtx, &globalCtx->colCtx.dyna, en->dyna.bgId)
//#define COLLISION_ON()  func_8003EC50(globalCtx, &globalCtx->colCtx.dyna, en->dyna.bgId)

static void CreateCollision(Entity *en, GlobalContext *globalCtx){
	if(ColHeaders[en->dyna.actor.params] == NULL) return;
	CollisionHeader* colHeaderVRAM;
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
	if((u16)en->dyna.actor.params > 9){
		Actor_Kill(&en->dyna.actor);
		return;
	}
	DynaPolyActor_Init(&en->dyna, DPM_UNK);
	Actor_SetScale(&en->dyna.actor, 0.1f);
}

static void destroy(Entity *en, GlobalContext *globalCtx) {
	if(en->collision) DestroyCollision(en, globalCtx);
}

static void update(Entity *en, GlobalContext *globalCtx) {
	//Actor specific parameters
	u16 target_action;
	s32 fade_speed;
	if(en->dyna.actor.params <= 6){
		target_action = en->dyna.actor.params + 1;
	}else{
		target_action = 8;
	}
	if(en->dyna.actor.params <= 5){
		fade_speed = 4;
	}else{
		fade_speed = 3;
	}
	//Fade in or out, handle collision
	if(!en->collision && CHECK_NPC_ACTION(STAIRS_SLOT, target_action)){
		CreateCollision(en, globalCtx);
		en->state = 1;
	}else if(en->collision && CHECK_NPC_ACTION(STAIRS_SLOT, 0)){
		DestroyCollision(en, globalCtx);
		en->state = 2;
	}
	s32 temp = en->alpha;
	if(en->state == 1){
		temp += fade_speed;
		if(temp >= 255){
			temp = 255;
			en->state = 0;
		}
	}else if(en->state == 2){
		temp -= fade_speed;
		if(temp <= 0){
			temp = 0;
			en->state = 0;
		}
	}
	en->alpha = temp;
	//Trigger cutscenes
	if(Cutscenes[en->dyna.actor.params] != NULL
			&& !en->cutscene_activated 
			&& en->dyna.actor.xzDistToPlayer < CS_ACTIVATE_RADIUS){
		globalCtx->csCtx.segment = SEGMENTED_TO_VIRTUAL(Cutscenes[en->dyna.actor.params]);
		gSaveContext.cutsceneTrigger = 1;
		en->cutscene_activated = 1;
	}
	//Open Triforce door
	if(en->dyna.actor.params == 9){
		if(en->state == 0 && CHECK_NPC_ACTION(STAIRS_SLOT, 9)){
			en->state = 3;
			Audio_PlayActorSound2(&(en->dyna.actor), NA_SE_EV_STONE_STATUE_OPEN - SFX_FLAG);
		}
		if(en->state == 3){
			en->dyna.actor.world.pos.y += DOOR_OPEN_SPEED;
			if(en->dyna.actor.world.pos.y - en->dyna.actor.home.pos.y >= DOOR_OPEN_DIST){
				en->state = 4;
				Audio_PlayActorSound2(&(en->dyna.actor), NA_SE_EV_STONEDOOR_STOP);
				Actor_Kill(&en->dyna.actor);
			}
		}
	}
}

static void draw(Entity *en, GlobalContext *globalCtx) {
	if(en->alpha == 0) return;
	if(DListsTransparent[en->dyna.actor.params]){
		gDPSetEnvColor(POLY_XLU_DISP++, 0xFF, 0xFF, 0xFF, en->alpha);
		Gfx_DrawDListXlu(globalCtx, DLists[en->dyna.actor.params]);
	}else{
		gDPSetEnvColor(POLY_OPA_DISP++, 0xFF, 0xFF, 0xFF, en->alpha);
		Gfx_DrawDListOpa(globalCtx, DLists[en->dyna.actor.params]);
	}
}

const ActorInitExplPad init_vars = {
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
