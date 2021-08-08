#include "ootmain.h"
#include "sages_objs.h"

static const u16 DepObjectNums[] = {
	0xA7, 0xBC, 0x9D, 0xCA, 0xB3, 0x87, 0x8A
};

//NPC action numbers: 39, 43, 41, 42, 40, 44, 31
static const u8 NPCActionSlot[] = {
	0, 4, 2, 3, 1, 5, 6
};

static const float ShadowSize[] = {
	50.0f, 20.0f, 30.0f, 30.0f, 25.0f, 30.0f, 25.0f
};

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

static FlexSkeletonHeader *const SkelHeader[] = {
	&RlSkel, &SaSkel, &DuSkel, &Ru2Skel, &NbSkel, &ImSkel, NULL
};

static AnimationHeader *const AnimIdle[] = {
	&RlAnimIdle, &SaAnimIdle, &DuAnimIdle, &Ru2AnimIdle, &NbAnimIdle, &ImAnimIdle, NULL
};

static AnimationHeader *const AnimBlessing[] = {
	&RlAnimBlessing, &SaAnimBlessing, &DuAnimBlessing, &Ru2AnimBlessing,
	&NbAnimBlessing, &ImAnimBlessing, NULL
};

static AnimationHeader *const AnimBlessingIdle[] = {
	&RlAnimBlsIdle, &SaAnimBlsIdle, &DuAnimBlsIdle, NULL, &NbAnimBlsIdle, &ImAnimBlsIdle, NULL
};

static void *const EyeTextures[7][3] = {
	{&RlEyeOpen,  &RlEyeHalf,  &RlEyeClosed},
	{&SaEyeOpen,  &SaEyeHalf,  &SaEyeClosed},
	{&DuEyeOpen,  &DuEyeHalf,  &DuEyeClosed},
	{&Ru2EyeOpen, &Ru2EyeHalf, &Ru2EyeClosed},
	{&NbEyeOpen,  &NbEyeHalf,  &NbEyeClosed},
	{&ImEyeOpen,  &ImEyeHalf,  &ImEyeClosed},
	{NULL, NULL, NULL}
};

#define SAGE_STATE_GONE 0
#define SAGE_STATE_APPEARING 1
#define SAGE_STATE_IDLE 2
#define SAGE_STATE_BLESSING 3
#define SAGE_STATE_BLESSING_IDLE 4

#define FADEIN_SPEED 16

#define PARAM ((u16)en->actor.params)

typedef struct {
	Actor actor;
	SkelAnime skelAnime;
	ColliderCylinder collider;
    Vec3s jointTable[MAX_LIMBS];
    Vec3s morphTable[MAX_LIMBS];
	s32 objBankIndex;
	u8 initted;
	u8 state;
	u8 drawConfig;
	u8 eyeTextureIndex;
	u8 mouthTextureIndex;
	u8 alpha;
	u8 blinkTimer;
} Entity;

static void init(Entity *en, GlobalContext *globalCtx) {
	en->initted = 0;
	if(PARAM >= 1){
		Actor_Kill(&en->actor);
		return;
	}
	en->objBankIndex = Object_GetIndex(&globalCtx->objectCtx, DepObjectNums[PARAM]);
	ActorShape_Init(&en->actor.shape, 0.0f, ActorShadow_DrawCircle, ShadowSize[PARAM]);
	Collider_InitCylinder(globalCtx, &en->collider);
    Collider_SetCylinderType1(globalCtx, &en->collider, &en->actor, &sCylinderInit);
	en->state = SAGE_STATE_GONE;
	en->drawConfig = 0;
	en->eyeTextureIndex = 0;
	en->mouthTextureIndex = 0;
	en->alpha = 0;
	en->blinkTimer = 0;
}

static s32 finishInit(Entity *en, GlobalContext *globalCtx) {
	//Set object
	if(!Object_IsLoaded(&globalCtx->objectCtx, en->objBankIndex)) return 0;
	en->actor.objBankIndex = en->objBankIndex;
	Actor_SetObjectDependency(globalCtx, &en->actor);
	//Set up skelanime
	SkelAnime_InitFlex(globalCtx, &en->skelAnime, SkelHeader[PARAM], AnimIdle[PARAM], 
		en->jointTable, en->morphTable, NumLimbs[PARAM]);
	//Done
	en->initted = 1;
	return 1;
}

static void destroy(Entity *en, GlobalContext *globalCtx) {
	Collider_DestroyCylinder(globalCtx, &en->collider);
	if(en->initted) SkelAnime_Free(&en->skelAnime, globalCtx);
}

static void updateEyes(Entity *en){
	if(en->blinkTimer == 0){
		en->blinkTimer = Rand_S16Offset(60, 60);
	}else{
		--en->blinkTimer;
	}
	en->eyeTextureIndex = (en->blinkTimer < 3) ? en->blinkTimer : 0;
}

static void update(Entity *en, GlobalContext *globalCtx) {
	if(!en->initted){
		if(!finishInit(en, globalCtx)) return;
	}
	updateEyes(en);
	s32 animDone = SkelAnime_Update(&en->skelAnime);
	if(en->state == SAGE_STATE_GONE){
		if(CHECK_NPC_ACTION(NPCActionSlot[PARAM], 1)){
			en->state = SAGE_STATE_APPEARING;
			en->drawConfig = 2;
			en->alpha = 0;
		}
	}else if(en->state == SAGE_STATE_APPEARING){
		s32 temp = en->alpha;
		temp += FADEIN_SPEED;
		if(temp >= 255){
			en->state = SAGE_STATE_IDLE;
			en->alpha = 255;
			en->drawConfig = 1;
		}
	}else if(en->state == SAGE_STATE_IDLE){
		if(CHECK_NPC_ACTION(NPCActionSlot[PARAM], 2)){
			en->state = SAGE_STATE_BLESSING;
			Animation_Change(&en->skelAnime, AnimBlessing[PARAM], 1.0f, 0.0f,
				Animation_GetLastFrame(AnimBlessing[PARAM]), ANIMMODE_ONCE, -4.0f);
		}
	}else if(en->state == SAGE_STATE_BLESSING){
		if(animDone){
			en->state = SAGE_STATE_BLESSING_IDLE;
			if(AnimBlessingIdle[PARAM] != NULL){
				Animation_Change(&en->skelAnime, AnimBlessingIdle[PARAM], 1.0f, 0.0f,
					Animation_GetLastFrame(AnimBlessingIdle[PARAM]), ANIMMODE_LOOP, 0.0f);
			}
		}
	}else if(en->state == SAGE_STATE_BLESSING_IDLE){
		(void)0;
	}
}

static void draw(Entity *en, GlobalContext *globalCtx) {
	if(en->drawConfig == 0) return;
	Gfx **gfx;
	s32 setupCmdIdx;
	if(en->drawConfig == 2){
		gfx = &POLY_XLU_DISP;
		setupCmdIdx = 0;
		func_80093D84(globalCtx->state.gfxCtx);
	}else{
		gfx = &POLY_OPA_DISP;
		setupCmdIdx = 2; //Skips actual setup, just end DL
		func_80093D18(globalCtx->state.gfxCtx);
	}
	void *seg08Tex, *seg09Tex, *seg0ATex = NULL;
	seg08Tex = EyeTextures[PARAM][en->eyeTextureIndex];
	seg09Tex = seg08Tex;
	if(PARAM == 1){
		seg0ATex = &SaMouthClosed;
	}else if(PARAM == 2){
		seg09Tex = &DuMouthGrinning;
		seg0ATex = &DuNoseSerious;
	}
	gSPSegment((*gfx)++, 0x08, SEGMENTED_TO_VIRTUAL(seg08Tex));
    gSPSegment((*gfx)++, 0x09, SEGMENTED_TO_VIRTUAL(seg09Tex));
	if(seg0ATex != NULL){
    	gSPSegment((*gfx)++, 0x0A, SEGMENTED_TO_VIRTUAL(seg0ATex));
	}
    gDPSetEnvColor((*gfx)++, 0, 0, 0, en->alpha);
    gSPSegment((*gfx)++, 0x0C, &gActorXluSetup[setupCmdIdx]);
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