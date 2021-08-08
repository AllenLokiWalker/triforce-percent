#include "ootmain.h"

/*
 * 0x0000 a 0xA6 o 0xA7 En_Rl:   slot 0 (number 39). No rise. 2: stand, 3: pose
 * 0x0001 a 0xC9 o 0xBC Demo_Sa: slot 4 (number 43). Probably params 0. 1: rise, 2: stand, 3: pose
 * 0x0002 a 0xA8 o 0x9D Demo_Du: slot 2 (number 41). Same
 * 0x0003 a 0xD2 o 0xCA En_Ru2:  slot 3 (number 42). Same
 * 0x0004 a 0xC3 o 0xB3 En_Nb:   slot 1 (number 40). Same
 * 0x0005 a 0xA9 o 0x87 Demo_Im: slot 5 (number 44). Same
 * 0x0006 a 0x48 o 0x8A En_Xc:   slots 0 and 4 --> use slot 6
*/

static const u16 DepObjectNums[] = {
	0xA7, 0xBC, 0x9D, 0xCA, 0xB3, 0x87, 0x8A
};

static const u8 NPCActionSlot[] = {
	0, 4, 2, 3, 1, 5, 6
};

static const float ShadowSize[] = {
	50.0f, 20.0f, 30.0f, 30.0f, 25.0f, 30.0f, 25.0f
};

#define SAGE_STATE_GONE 0
#define SAGE_STATE_APPEARING 1
#define SAGE_STATE_IDLE 2
#define SAGE_STATE_BLESSING 3

static ColliderCylinderInitType1 sCylinderInit = {
    { COLTYPE_HIT0, AT_NONE, AC_NONE, OC1_ON | OC1_TYPE_PLAYER, COLSHAPE_CYLINDER, },
    { ELEMTYPE_UNK0, { 0x00000000, 0x00, 0x00 }, { 0x00000000, 0x00, 0x00 },
        TOUCH_NONE, BUMP_NONE, OCELEM_ON, },
    { 25, 80, 0, { 0, 0, 0 } },
};

static const u8 NumLimbs[] = {
	11, 17, 18, 23, 19, 17, 0
};
#define MAX_LIMBS 23

static AnimationHeader *const AnimIdle[] = {
	RauruAnimIdle, SariaAnimIdle, DaruniaAnimIdle, RutoAnimIdle, NabooruAnimIdle, ImpaAnimIdle, NULL
};

static FlexSkeletonHeader *const SkelHeader[] = {
	RauruSkel, SariaSkel, DaruniaSkel, RutoSkel, NabooruSkel, ImpaSkel, NULL
};

#define PARAM ((u16)en->actor.params)

typedef struct {
	Actor actor;
	SkelAnime skelAnime;
	ColliderCylinder collider;
    Vec3s jointTable[MAX_LIMBS];
    Vec3s morphTable[MAX_LIMBS];
	s32 objBankIndex;
	u8 initted;
	u8 drawConfig;
	u8 eyeTextureIndex;
	u8 mouthTextureIndex;
	u8 alpha;
} Entity;

static Gfx * const DLists[] = {
	RauruStair,
	SariaStair, SariaStair, SariaStair, SariaStair, SariaStair, 
	SheikStair,
	TriforceFadeWall, TriforceHallway, TriforceDoor
};

static void init(Entity *en, GlobalContext *globalCtx) {
	initted = 0;
	if(PARAM >= 6){
		Actor_Kill(&en->actor);
		return;
	}
	en->objBankIndex = Object_GetIndex(&globalCtx->objectCtx, DepObjectNums[PARAM]);
	ActorShape_Init(&en->actor.shape, 0.0f, ActorShadow_DrawCircle, ShadowSize[PARAM]);
	Collider_InitCylinder(globalCtx, &en->collider);
    Collider_SetCylinderType1(globalCtx, &en->collider, en, &sCylinderInit);
	en->drawConfig = 0;
}

static s32 finishInit(Entity *en, GlobalContext *globalCtx) {
	//Set object
	if(!Object_IsLoaded(&globalCtx->objectCtx, en->objBankIndex)) return 0;
	en->actor.objBankIndex = en->objBankIndex;
	Actor_SetObjectDependency(globalCtx, &en->actor);
	//Set up skelanime
	SkelAnime_InitFlex(globalCtx, &en->skelAnime, SkelHeader[PARAM], InitAnim[PARAM], 
		en->jointTable, en->morphTable, NumLimbs[PARAM]);
	//Done
	en->initted = 1;
	return 1;
}

static void destroy(Entity *en, GlobalContext *globalCtx) {
	Collider_DestroyCylinder(globalCtx, &en->collider);
	if(en->initted) SkelAnime_Free(&en->skelAnime, globalCtx);
}

static void update(Entity *en, GlobalContext *globalCtx) {
	if(!en->initted){
		if(!finishInit(en, globalCtx)) return;
	}
}

#define GFX_PP *(*gfx)++

static void draw(Entity *en, GlobalContext *globalCtx) {
	if(en->drawConfig == 0) return;
	Gfx **gfx;
	void *unk;
	if(en->drawConfig == 2){
		gfx = &POLY_XLU_DISP;
		unk = D_80116280;
		func_80093D84(globalCtx->state.gfxCtx);
	}else{
		gfx = &POLY_OPA_DISP;
		unk = &D_80116280[2];
		func_80093D18(globalCtx->state.gfxCtx);
	}
	void *seg08Tex, *seg09Tex, *seg0ATex = NULL;
	seg08Tex = EyeTextures[PARAM][en->eyeTextureIndex];
	seg09Tex = seg08Tex;
	if(PARAM == 1){
		seg0ATex = SariaMouthTextures[en->mouthTextureIndex];
	}else if(PARAM == 2){
		seg09Tex = DaruniaMouthTextures[en->mouthTextureIndex];
		seg0ATex = &gDaruniaNoseSeriousTex;
	}
	gSPSegment(GFX_PP, 0x08, SEGMENTED_TO_VIRTUAL(seg08Tex));
    gSPSegment(GFX_PP, 0x09, SEGMENTED_TO_VIRTUAL(seg09Tex));
	if(seg0ATex != NULL){
    	gSPSegment(GFX_PP, 0x0A, SEGMENTED_TO_VIRTUAL(seg0ATex));
	}
    gDPSetEnvColor(GFX_PP, 0, 0, 0, en->alpha);
    gSPSegment(GFX_PP, 0x0C, unk);
	//Saria has an override for the ocarina hand, Nabooru for a surprised head.
	//Impa has several including rotation changes, but hopefully we don't need those.
	*gfx = SkelAnime_DrawFlex(globalCtx, en->skelAnime.skeleton, en->skelAnime.jointTable,
		en->skelAnime.dListCount, NULL, NULL, en, *gfx);
}

const ActorInit init_vars = {
	.id = 0xDEAD, .padding = 0xBEEF, // <-- magic values, do not change
	.category = ACTORCAT_PROP,
	.flags = 0x00000030,
	.objectId = OBJECT_GAMEPLAY_KEEP,
	.instanceSize = sizeof(Entity),
	.init = (ActorFunc)init,
	.destroy = (ActorFunc)destroy,
	.update = (ActorFunc)update,
	.draw = (ActorFunc)draw
};
