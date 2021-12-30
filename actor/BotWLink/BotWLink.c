#include "ootmain.h"
#include "BotWLinkMesh.h"
#include "BotWLinkMeshIdleAnim.h"
#include "BotWLinkMeshBobokuwaAnim.h"
#include "BotWLinkMeshHeadmoveAnim.h"
#include "../loader/debugger/debugger.h"
#include "../statics/hairphys.h"
#include "../statics/statics.h"
#include "../statics/anime.h"

// Actor Information
#define OBJ_ID 122 // primary object dependency
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
static const HairPhysLimits tasselLLimits    = {{-0.15f,   0.0f, -0.05f}, { 0.0f, 0.0f, 0.0f}};
static const HairPhysLimits tasselRLimits    = {{ 0.15f,   0.0f, -0.05f}, { 0.0f, 0.0f, 0.0f}};
static       HairPhysLimits tunicFLLimits    = {{ 0.00f,   0.0f, -0.02f}, { 0.0f, 0.0f, 0.0f}};
static       HairPhysLimits tunicFCLimits    = {{ 0.00f,   0.0f, -0.02f}, { 0.0f, 0.0f, 0.0f}};
static       HairPhysLimits tunicFRLimits    = {{ 0.00f,   0.0f, -0.02f}, { 0.0f, 0.0f, 0.0f}};
static       HairPhysLimits tunicBLLimits    = {{ 0.00f,   0.0f,  0.02f}, { 0.0f, 0.0f, 0.0f}};
static       HairPhysLimits tunicBCLimits    = {{ 0.00f,   0.0f,  0.02f}, { 0.0f, 0.0f, 0.0f}};
static       HairPhysLimits tunicBRLimits    = {{ 0.00f,   0.0f,  0.02f}, { 0.0f, 0.0f, 0.0f}};
static const HairPhysBasic  bangsBasic    =  {0.004f,250.0f,  3.0f,  1.2f, 1.00f, 0.70f, 1.500f};
static const HairPhysBasic  ponytailBasic =  {0.002f,500.0f,  2.0f,  1.0f, 1.00f, 0.85f, 3.000f};
static const HairPhysBasic  tasselsBasic  =  {0.002f,500.0f,  3.0f, 70.0f, 0.04f, 0.97f, 0.007f};
static const HairPhysDouble tasselsLDouble= {{0.001f,999.9f,  2.0f, 70.0f, 0.12f, 0.97f, 0.015f}, &tasselLLimits};
static const HairPhysDouble tasselsRDouble= {{0.001f,999.9f,  2.0f, 70.0f, 0.12f, 0.97f, 0.015f}, &tasselRLimits};
static const HairPhysBasic  tunicBasic    =  {0.004f,250.0f,  3.0f, 70.0f, 0.12f, 0.92f, 0.015f};
static const HairPhysTunic  tunicTunic    =  {4.0f, 0.01f};
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
	/*lotncbl*/ {2, &tunicBasic, &tunicBLLimits , NULL, &tunicTunic},
	/*lotncbc*/ {2, &tunicBasic, &tunicBCLimits , NULL, &tunicTunic},
	/*lotncbr*/ {2, &tunicBasic, &tunicBRLimits , NULL, &tunicTunic},
};

typedef struct {
	Actor actor;
	SkelAnime skelAnime;
	Vec3s jointTable[BOTWLINKMESH_NUM_LIMBS];
	Vec3s morphTable[BOTWLINKMESH_NUM_LIMBS];
	HairPhysSimpleState physSimple[4];
	HairPhysDoubleState physDouble[2];
	HairPhysTunicState physTunic[6];
	void *physStates[12];
	float windX, windZ;
	u32 flags;
	u8 timer;
} Entity;

static void init(Entity *en, GlobalContext *globalCtx) {
	//General setup
	Rupees_ChangeBy(4);
	en->flags = 0;
	Actor_SetScale(&en->actor, ACTOR_SCALE);
	//Components setup
	ActorShape_Init(&en->actor.shape, 0.0f, ActorShadow_DrawCircle, 30.0f); //TODO not working?
	SkelAnime_InitFlex(globalCtx, &en->skelAnime, &BotWLinkMesh, &BotWLinkMeshIdleAnim, 
		en->jointTable, en->morphTable, BOTWLINKMESH_NUM_LIMBS);
	//Physics initialization
	s32 c = 0;
	for(s32 i=0; i<4; ++i) en->physStates[c++] = &en->physSimple[i];
	for(s32 i=0; i<2; ++i) en->physStates[c++] = &en->physDouble[i];
	for(s32 i=0; i<6; ++i) en->physStates[c++] = &en->physTunic[i];
	for(c=0; c<12; ++c) HairPhys_Init(en->physStates[c], &physc[c]);
	en->physTunic[0].conn1 = &en->physTunic[1];
	en->physTunic[1].conn1 = &en->physTunic[0];
	en->physTunic[1].conn2 = &en->physTunic[2];
	en->physTunic[2].conn1 = &en->physTunic[1];
	en->physTunic[3].conn1 = &en->physTunic[4];
	en->physTunic[4].conn1 = &en->physTunic[3];
	en->physTunic[4].conn2 = &en->physTunic[5];
	en->physTunic[5].conn1 = &en->physTunic[4];
	en->windX = 0.707f;
	en->windZ = -0.707f;
}

static void destroy(Entity *en, GlobalContext *globalCtx) {
	SkelAnime_Free(&en->skelAnime, globalCtx);
}

#define VO_LINK_BOBOKUWA 0
#define VO_LINK_TAKUSAN 1
#define VO_LINK_DAIJINA 2
static const u16 voiceSfxMap[] = {
	NA_SE_EN_GANON_LAUGH,
	NA_SE_EN_GANON_VOICE_DEMO,
	NA_SE_EN_GANON_THROW
};
static f32 VoiceFreqScale = 1.0f;
static f32 VoiceVol = 1.5f;
static u32 VoiceReverbAdd = 0;
static void BotWLink_VO(Entity *en, u16 linkVO){
	Audio_PlaySoundGeneral(voiceSfxMap[linkVO], &en->actor.projectedPos, 4, 
		&VoiceFreqScale, &VoiceVol,	(f32*)&VoiceReverbAdd);
}

static void BotWLink_SetAnim(Entity *en, AnimationHeader *anim, u8 mode, f32 morphFrames){
	Animation_Change(&en->skelAnime, anim, 1.0f, 0.0f, 
		Animation_GetLastFrame(anim), mode, morphFrames);
}

static void update(Entity *en, GlobalContext *globalCtx) {
	if(!(CTRLR_RAW & (BTN_R | BTN_L))){
		if((CTRLR_PRESS & BTN_DLEFT)){
			en->timer = 1;
			BotWLink_SetAnim(en, &BotWLinkMeshBobokuwaAnim, ANIMMODE_ONCE, -4.0f);
		}else if((CTRLR_PRESS & BTN_DDOWN)){
			//BotWLink_VO(en, VO_LINK_TAKUSAN);
			BotWLink_SetAnim(en, &BotWLinkMeshIdleAnim, ANIMMODE_LOOP, -8.0f);
		}else if((CTRLR_PRESS & BTN_DRIGHT)){
			//BotWLink_VO(en, VO_LINK_DAIJINA);
			BotWLink_SetAnim(en, &BotWLinkMeshHeadmoveAnim, ANIMMODE_LOOP, -8.0f);
		}else if((CTRLR_RAW & BTN_CLEFT)){
			en->actor.shape.rot.y += 0x200;
		}else if((CTRLR_RAW & BTN_CRIGHT)){
			en->actor.shape.rot.y -= 0x200;
		}
	}
	
	if(en->timer > 0){
		if(en->timer == 5){
			BotWLink_VO(en, VO_LINK_BOBOKUWA);
			en->timer = 0;
		}else{
			++en->timer;
		}
	}
	s32 animFinished = SkelAnime_Update(&en->skelAnime);
	if(animFinished){
		BotWLink_SetAnim(en, &BotWLinkMeshIdleAnim, ANIMMODE_LOOP, -8.0f);
	}
	en->flags &= ~(FLAG_NO_LOWLEGS | FLAG_NO_LOWERBODY);
	Vec3f pos = en->actor.world.pos;
	pos.y += 20.0f;
	if(!Statics_UncullObject(globalCtx, &pos, 12.0f, 80.0f, 0.0f, 15.0f, 1000.0f))
		en->flags |= FLAG_NO_LOWLEGS;
	pos = en->actor.world.pos;
	pos.y += 31.0f;
	if(!Statics_UncullObject(globalCtx, &pos, 15.0f, 100.0f, 0.0f, 15.0f, 1000.0f))
		en->flags |= FLAG_NO_LOWERBODY;
}

s32 BotWLink_OverrideLimbDraw(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, void* thisx) {
	Entity *en = (Entity*)thisx;
	s8 p = limbToPhysMap[limbIndex];
	u32 limbMask = 1 << limbIndex;
	if(((en->flags & FLAG_NO_LOWLEGS) && (limbMask & LIMB_IS_LOWLEGS)) ||
		((en->flags & FLAG_NO_LOWERBODY) && (limbMask & LIMB_IS_LOWERBODY))){
		*dList = NULL;
		if(p >= 0) HairPhys_UpdateCulled(en->physStates[p], &physc[p]);
		return false;
	}
	//if(limbIndex == BOTWLINKMESH_LOTNCFL_LIMB 
	//	|| limbIndex == BOTWLINKMESH_LTASSELS_LIMB) HairPhys_SetDebug(1);
	if(p >= 0) HairPhys_Update(en->physStates[p], &physc[p], pos, rot,
		en->windX, en->windZ, ACTOR_SCALE);
	//HairPhys_SetDebug(0);
	return false;
}

void BotWLink_PostLimbDraw(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3s* rot, void* thisx) {
	(void)0;
}

static void draw(Entity *en, GlobalContext *globalCtx) {
	func_80093D18(globalCtx->state.gfxCtx);
	SkelAnime_DrawFlexOpa(globalCtx, en->skelAnime.skeleton, en->skelAnime.jointTable,
		en->skelAnime.dListCount, BotWLink_OverrideLimbDraw, BotWLink_PostLimbDraw, en);
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
