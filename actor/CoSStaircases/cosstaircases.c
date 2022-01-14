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
	u8 timer;
	u8 alpha;
	u8 collision;
	u8 cutscene_activated;
	u8 init_timer;
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
	en->init_timer = 0;
	if((u16)en->dyna.actor.params > 9){
		Actor_Kill(&en->dyna.actor);
		return;
	}
	if(en->dyna.actor.params >= 7){
		Actor_ChangeCategory(globalCtx, &globalCtx->actorCtx, &en->dyna.actor, ACTORCAT_BG);
	}
	DynaPolyActor_Init(&en->dyna, DPM_UNK);
	Actor_SetScale(&en->dyna.actor, 0.1f);
}

static void destroy(Entity *en, GlobalContext *globalCtx) {
	if(en->collision) DestroyCollision(en, globalCtx);
}

static void update(Entity *en, GlobalContext *globalCtx) {
	if(en->init_timer < 100) ++en->init_timer;
	//Actor specific parameters
	u16 target_action;
	s32 fade_speed;
	if(en->dyna.actor.params <= 6){
		target_action = en->dyna.actor.params + 1;
	}else{
		target_action = 8;
	}
	if(en->dyna.actor.params <= 5){
		fade_speed = 6;
	}else{
		fade_speed = 8;
	}
	//Fade in or out, handle collision
	if(!en->collision && (CHECK_NPC_ACTION(STAIRS_SLOT, target_action) ||
			(en->dyna.actor.params == 0 && en->init_timer == 10 && globalCtx->csCtx.state == 0))){
		CreateCollision(en, globalCtx);
		en->state = 1;
		en->timer = 0;
	}else if(en->collision && CHECK_NPC_ACTION(STAIRS_SLOT, 0)){
		DestroyCollision(en, globalCtx);
		en->state = 3;
	}
	if(en->state == 1){
		++en->timer;
		if(en->timer >= 20){
			en->state = 2;
		}
	}
	s32 temp = en->alpha;
	if(en->state == 2){
		temp += fade_speed;
		if(temp >= 255){
			temp = 255;
			en->state = 0;
		}
	}else if(en->state == 3){
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
			en->state = 4;
		}
		if(en->state == 4){
			en->dyna.actor.world.pos.y += DOOR_OPEN_SPEED;
			if(en->dyna.actor.world.pos.y - en->dyna.actor.home.pos.y >= DOOR_OPEN_DIST){
				en->state = 5;
				Audio_PlayActorSound2(&(en->dyna.actor), NA_SE_EV_STONEDOOR_STOP);
				Actor_Kill(&en->dyna.actor);
			}else{
                Audio_PlayActorSound2(&(en->dyna.actor), NA_SE_EV_STONE_STATUE_OPEN - SFX_FLAG);
            }
		}
	}
}

static const s8 KiraType[] = { 0, 1, 1, 1, 1, 1, 2, -1, -1, -1 };
static const float KiraCtrX[] = { -305.0f,  420.0f, 0.0f };
static const float KiraCtrZ[] = { -334.0f,  454.0f, 0.0f };
static const float KiraRad[]  = {  288.0f,  600.0f, 0.0f };
static const float KiraW[]    = {  113.0f,  115.0f, 113.0f };
static const float KiraDY[]   = {   93.0f,  172.0f, 326.0f };
static const s16 KiraAngleLo[] = { 0x0000, 0x6AAA, -122 };
static const s16 KiraAngleHi[] = { 0x6800, 0x9555, -810 };
static Vec3f KiraVelocity = { 0.0f, -11.0f, 0.0f };
static Vec3f KiraAccel = { 0.0f, 1.0f, 0.0f };
static Color_RGBA8 KiraPrimColor = { 170, 255, 255, 255 };
static Color_RGBA8 KiraEnvColor = { 0, 120, 255, 0 };
#define KIRA_ABOVE 60.0f

static void draw(Entity *en, GlobalContext *globalCtx) {
	s8 kType = KiraType[en->dyna.actor.params];
    if(kType >= 0 && (en->state == 1 || en->state == 2)){
		float syr = Math_SinS(en->dyna.actor.shape.rot.y);
		float cyr = Math_CosS(en->dyna.actor.shape.rot.y);
        Vec3f pos0 = en->dyna.actor.world.pos;
		pos0.x += cyr * KiraCtrX[kType] + syr * KiraCtrZ[kType];
		pos0.z += cyr * KiraCtrZ[kType] - syr * KiraCtrX[kType];
		pos0.y += KIRA_ABOVE;
		s32 nspawn = en->alpha < 160 ? 3 : en->alpha < 220 ? 2 : 1;
		for(s32 i=0; i<nspawn; ++i){
			Vec3f pos = pos0;
			float along = Rand_ZeroOne();
			float across = Rand_ZeroOne();
			pos.y += along * KiraDY[kType];
			s16 angle = -en->dyna.actor.shape.rot.y + KiraAngleLo[kType] 
				+ (s16)((float)((s16)(KiraAngleHi[kType] - KiraAngleLo[kType])) * along);
			float dw = (across - 0.5f) * KiraW[kType];
			if(kType == 2){
				pos.z += dw;
				pos.x += angle;
			}else{
				float r = KiraRad[kType] + dw;
				pos.x -= r * Math_SinS(angle);
				pos.z += r * Math_CosS(angle);
			}
			EffectSsKiraKira_SpawnFocused(globalCtx, &pos, &KiraVelocity, &KiraAccel,
				&KiraPrimColor, &KiraEnvColor, 6000, 10);
		}
    }
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
