#include "ootmain.h"
#include "../BotWActors.h"
#include "BotWLinkMesh.h"
#include "BotWLinkMeshIdleAnim.h"
#include "BotWLinkMeshLinksdialogAnim.h"
#include "BotWLinkMeshLookatitselfAnim.h"
#include "BotWLinkMeshLookstozeldaAnim.h"
#include "BotWLinkMeshModerate_walkAnim.h"
#include "BotWLinkMeshModerate_walk_lookingaroundAnim.h"
#include "BotWLinkMeshTakeszeldahandAnim.h"
#include "BotWLinkMeshTurnleftAnim.h"
#include "BotWLinkMeshTurnrightAnim.h"
#include "BotWLinkMeshTex.h"

// Actor Information
#define OBJ_ID 122 // primary object dependency
#define ACTIONNUM 17
#define ACTIONSLOT 0
#define ACTOR_SCALE 0.035f

#define LIMB_IS_LOWLEGS ( \
	(1 << BOTWLINKMESH_LCALF_LIMB) | \
	(1 << BOTWLINKMESH_LFOOT_LIMB) | \
	(1 << BOTWLINKMESH_RCALF_LIMB) | \
	(1 << BOTWLINKMESH_RFOOT_LIMB))
#define LIMB_IS_LOWERBODY ( LIMB_IS_LOWLEGS | \
	(1 << BOTWLINKMESH_LOTNCBC_LIMB) | \
	(1 << BOTWLINKMESH_LOTNCBL_LIMB) | \
	(1 << BOTWLINKMESH_LOTNCBR_LIMB) | \
	(1 << BOTWLINKMESH_LOTNCFC_LIMB) | \
	(1 << BOTWLINKMESH_LOTNCFL_LIMB) | \
	(1 << BOTWLINKMESH_LOTNCFR_LIMB) | \
	(1 << BOTWLINKMESH_LTHIGH_LIMB) | \
	(1 << BOTWLINKMESH_RTHIGH_LIMB))

#define FLAG_NO_LOWLEGS (1 << 0)
#define FLAG_NO_LOWERBODY (1 << 1)

static const s8 limbToPhysMap[BOTWLINKMESH_NUM_LIMBS] = {
	-1, -1, -1, //root, root, hips
	10, //lotncbc
	9, //lotncbl
	11, //lotncbr
	7, //lotncfc
	6, //lotncfl
	8, //lotncfr
	-1, -1, -1, -1, -1, -1, -1, -1, //lthigh, lcalf, lfoot, rthigh, rcalf, rfoot, torso, head
	1, //bangs1
	2, //bangs2
	3, //bangs3
	-1, -1, //jaw, lmouth
	4, //ltassels
	0, //ponytail
	-1, //rmouth
	5, //rtassels
	-1, -1, -1, -1 //luparm, lloarm, ruparm, rloarm
};
#define NUM_PHYS 12

static const HairPhysLimits bangsLimits      = {{-16.0f, -16.0f, -16.0f}, { 16.0f,  16.0f,  16.0f}};
static const HairPhysLimits ponytailLimits   = {{-64.0f, -64.0f, -64.0f}, { 64.0f,  64.0f,  64.0f}};
static const HairPhysLimits tasselLLimits    = {{-3.0f, 0.05f, -1.0f}, {0.0f, 0.0f, 0.0f}};
static const HairPhysLimits tasselRLimits    = {{ 3.0f, 0.05f, -1.0f}, {0.0f, 0.0f, 0.0f}};
static       HairPhysLimits tunicFLLimits    = {{-1.0f,  0.1f, -4.0f}, {0.0f, 0.0f, 0.0f}};
static       HairPhysLimits tunicFCLimits    = {{ 0.0f,  0.1f, -4.0f}, {0.0f, 0.0f, 0.0f}};
static       HairPhysLimits tunicFRLimits    = {{ 1.0f,  0.1f, -4.0f}, {0.0f, 0.0f, 0.0f}};
static       HairPhysLimits tunicBLLimits    = {{-1.0f,  0.1f,  4.0f}, {0.0f, 0.0f, 0.0f}};
static       HairPhysLimits tunicBCLimits    = {{ 0.0f,  0.1f,  4.0f}, {0.0f, 0.0f, 0.0f}};
static       HairPhysLimits tunicBRLimits    = {{ 1.0f,  0.1f,  4.0f}, {0.0f, 0.0f, 0.0f}};
static const HairPhysBasic  bangsBasic    =  {0.004f,250.0f,  3.0f,  1.2f, 1.00f, 0.70f, 1.500f, 0};
static const HairPhysBasic  ponytailBasic =  {0.002f,500.0f,  2.0f,  1.0f, 1.00f, 0.85f, 3.000f, 0};
static const HairPhysBasic  tasselsBasic  =  {0.002f,500.0f,  3.0f, 80.0f, 0.02f, 0.97f, 0.010f, 1};
static const HairPhysDouble tasselsLDouble= {{0.001f,999.9f,  2.0f, 80.0f, 0.07f, 0.97f, 0.015f, 1}, &tasselLLimits};
static const HairPhysDouble tasselsRDouble= {{0.001f,999.9f,  2.0f, 80.0f, 0.07f, 0.97f, 0.015f, 1}, &tasselRLimits};
static const HairPhysBasic  tunicBasic    =  {0.002f,500.0f,  5.0f,100.0f, 0.10f, 0.92f, 0.015f, 2};
static const HairPhysTunic  tunicTunic    =  {4.0f, 0.05f};
static const HairPhysConstants physc[NUM_PHYS] = {
	/*ponytail*/{0, &ponytailBasic, &ponytailLimits, NULL, NULL},
	/*bangs1*/  {0, &bangsBasic, &bangsLimits, NULL, NULL},
	/*bangs2*/  {0, &bangsBasic, &bangsLimits, NULL, NULL},
	/*bangs3*/  {0, &bangsBasic, &bangsLimits, NULL, NULL},
	/*ltassels*/{1, &tasselsBasic, &tasselLLimits, &tasselsLDouble, NULL},
	/*rtassels*/{1, &tasselsBasic, &tasselRLimits, &tasselsRDouble, NULL},
	/*lotncfl*/ {2, &tunicBasic, &tunicFLLimits, NULL, &tunicTunic},
	/*lotncfc*/ {2, &tunicBasic, &tunicFCLimits, NULL, &tunicTunic},
	/*lotncfr*/ {2, &tunicBasic, &tunicFRLimits, NULL, &tunicTunic},
	/*lotncbl*/ {2, &tunicBasic, &tunicBLLimits, NULL, &tunicTunic},
	/*lotncbc*/ {2, &tunicBasic, &tunicBCLimits, NULL, &tunicTunic},
	/*lotncbr*/ {2, &tunicBasic, &tunicBRLimits, NULL, &tunicTunic},
};

static void *const EyeTextures[3] = {
	&BotWLinkEye0Tex, &BotWLinkEye1Tex, &BotWLinkEye2Tex
};

typedef struct {
	BotWActor botw;
	Vec3s jointTable[BOTWLINKMESH_NUM_LIMBS];
	Vec3s morphTable[BOTWLINKMESH_NUM_LIMBS];
	HairPhysSimpleState physSimple[4];
	HairPhysDoubleState physDouble[2];
	HairPhysTunicState physTunic[6];
	void *physStates[NUM_PHYS];
} Entity;

static void init(Entity *en, GlobalContext *globalCtx) {
    Statics_EnableLagCorr(1);
	BotWActor_Init(&en->botw, globalCtx, &BotWLinkMesh, &BotWLinkMeshIdleAnim,
		en->jointTable, en->morphTable, BOTWLINKMESH_NUM_LIMBS, ACTOR_SCALE);
	//Physics initialization
	s32 c = 0;
	for(s32 i=0; i<4; ++i) en->physStates[c++] = &en->physSimple[i];
	for(s32 i=0; i<2; ++i) en->physStates[c++] = &en->physDouble[i];
	for(s32 i=0; i<6; ++i) en->physStates[c++] = &en->physTunic[i];
	for(c=0; c<NUM_PHYS; ++c) HairPhys_Init(en->physStates[c], &physc[c]);
	en->physTunic[0].conn1 = &en->physTunic[1];
	en->physTunic[1].conn1 = &en->physTunic[0];
	en->physTunic[1].conn2 = &en->physTunic[2];
	en->physTunic[2].conn1 = &en->physTunic[1];
	en->physTunic[3].conn1 = &en->physTunic[4];
	en->physTunic[4].conn1 = &en->physTunic[3];
	en->physTunic[4].conn2 = &en->physTunic[5];
	en->physTunic[5].conn1 = &en->physTunic[4];
}

static void destroy(Entity *en, GlobalContext *globalCtx) {
	BotWActor_Destroy(&en->botw, globalCtx);
	Statics_EnableLagCorr(0);
}

#define VO_LINK_ZERUDAHIME NA_SE_EN_GANON_LAUGH
#define VO_LINK_ISSHONI NA_SE_EN_GANON_VOICE_DEMO

static void BotWLink_DialogCallback(BotWActor *botw, GlobalContext *globalCtx) {
	Entity *en = (Entity*)botw;
	if(en->botw.actionframe == 80) BotWActor_VO(&en->botw, VO_LINK_ISSHONI);
}

typedef struct {
	u8 dummy[0x178];
	s16 shrinkTimer;
} FakeDemoEffect;

static void BotWLink_TimeWarpCallback(BotWActor *botw, GlobalContext *globalCtx) {
	Entity *en = (Entity*)botw;
	if(en->botw.actionframe == 0) Actor_Spawn(&globalCtx->actorCtx, globalCtx,
		ACTOR_DEMO_EFFECT, en->botw.actor.world.pos.x, en->botw.actor.world.pos.y,
		en->botw.actor.world.pos.z, 0, 0, 0, 0x0019);
	Actor *tw_actor = Actor_Find(&globalCtx->actorCtx, ACTOR_DEMO_EFFECT, ACTORCAT_BG);
	if(tw_actor == NULL) return;
	FakeDemoEffect *de = (FakeDemoEffect*)tw_actor;
	if(de->shrinkTimer >= 20 && de->shrinkTimer <= 60 && (globalCtx->gameplayFrames & 1)){
		--de->shrinkTimer;
	}
}

#define NACTIONDEFS 11
static const BotWCSActionDef ActionDefs[NACTIONDEFS] = {
	/*0*/{NULL, 0.0f, NULL, 0.0f,
			FLAG_INVISIBLE, 0, 0, 0, NULL},
	/*1*/{&BotWLinkMeshIdleAnim, 0.0f, NULL, 0.0f,
			0, 0, 0, 0, NULL},
	/*2*/{&BotWLinkMeshModerate_walkAnim, -8.0f, NULL, 0.0f,
			0, 0, 0, 0, NULL},
	/*3*/{&BotWLinkMeshLookatitselfAnim, -8.0f, &BotWLinkMeshIdleAnim, -8.0f,
			0, 0, 0, 0, NULL},
	/*4*/{&BotWLinkMeshTurnleftAnim, -8.0f, &BotWLinkMeshIdleAnim, -8.0f,
			FLAG_DELAYROT, 0, 0, 0, NULL},
	/*5*/{&BotWLinkMeshTurnrightAnim, -8.0f, &BotWLinkMeshIdleAnim, -8.0f,
			FLAG_DELAYROT, 0, 0, 0, NULL},
	/*6*/{&BotWLinkMeshLookstozeldaAnim, -8.0f, &BotWLinkMeshIdleAnim, -8.0f,
			0, 0, 0, 0, NULL},
	/*7*/{&BotWLinkMeshLinksdialogAnim, -8.0f, &BotWLinkMeshIdleAnim, -8.0f,
			0, 0, VO_LINK_ZERUDAHIME, 5, BotWLink_DialogCallback},
	/*8*/{&BotWLinkMeshTakeszeldahandAnim, -8.0f, NULL, 0.0f,
			0, 0, 0, 0, NULL},
	/*9*/{NULL, 0.0f, NULL, 0.0f,
			FLAG_INVISIBLE, 0, 0, 0, BotWLink_TimeWarpCallback},
	/*A*/{&BotWLinkMeshModerate_walk_lookingaroundAnim, -8.0f, NULL, 0.0f,
			0, 0, 0, 0, NULL},
};

static const BotWFixRotAnimDef FixRotAnimDefs[] = {
	{ BOTWLINKMESH_HIPS_LIMB, 2, 1 },
	{ BOTWLINKMESH_TORSO_LIMB, 2, 1 },
	{ -1, 0, 0 }
};

static void update(Entity *en, GlobalContext *globalCtx) {
	BotWActor_Update(&en->botw, globalCtx, ActionDefs, NACTIONDEFS, ACTIONSLOT,
		FixRotAnimDefs);
}

s32 BotWLink_OverrideLimbDraw(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, void* thisx) {
	Entity *en = (Entity*)thisx;
	s8 p = limbToPhysMap[limbIndex];
	u32 limbMask = 1 << limbIndex;
	if(((en->botw.flags & FLAG_NO_LOWLEGS) && (limbMask & LIMB_IS_LOWLEGS)) ||
		((en->botw.flags & FLAG_NO_LOWERBODY) && (limbMask & LIMB_IS_LOWERBODY)) ||
		(en->botw.flags & FLAG_INVISIBLE)){
		*dList = NULL;
		if(p >= 0) HairPhys_UpdateCulled(en->physStates[p], &physc[p]);
		return false;
	}
	if(p >= 0) HairPhys_Update(en->physStates[p], &physc[p], pos, rot,
		en->botw.windX, en->botw.windZ, ACTOR_SCALE, false);
	if(limbIndex == BOTWLINKMESH_LTHIGH_LIMB || limbIndex == BOTWLINKMESH_RTHIGH_LIMB){
		bool isl = (limbIndex == BOTWLINKMESH_LTHIGH_LIMB);
		s16 r = rot->y;
		const float convert = 4.0f / 0x2000;
		float d = (float)r * convert;
		(isl ? &tunicFLLimits : &tunicFRLimits)->neg.y = 0.2f + d;
		(isl ? &tunicBLLimits : &tunicBRLimits)->neg.y = 0.1f - d;
		tunicFCLimits.neg.y = 0.5f * (tunicFLLimits.neg.y + tunicFRLimits.neg.y);
		tunicBCLimits.neg.y = 0.5f * (tunicBLLimits.neg.y + tunicBRLimits.neg.y);
	}
	return false;
}

void BotWLink_PostLimbDraw(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3s* rot, void* thisx) {
	//Entity *en = (Entity*)thisx;
	(void)0;
}

static void draw(Entity *en, GlobalContext *globalCtx) {
	//
	en->botw.flags &= ~(FLAG_NO_LOWLEGS | FLAG_NO_LOWERBODY);
	Vec3f pos = en->botw.actor.world.pos;
	pos.y += 20.0f;
	if(!Statics_UncullObject(globalCtx, &pos, 12.0f, 80.0f, 0.0f, 15.0f, 1000.0f))
		en->botw.flags |= FLAG_NO_LOWLEGS;
	pos = en->botw.actor.world.pos;
	pos.y += 31.0f;
	if(!Statics_UncullObject(globalCtx, &pos, 15.0f, 100.0f, 0.0f, 15.0f, 1000.0f))
	en->botw.flags |= FLAG_NO_LOWERBODY;
	//
	BotWActor_DrawMain(&en->botw, globalCtx, EyeTextures, BotWLink_OverrideLimbDraw, BotWLink_PostLimbDraw);
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
