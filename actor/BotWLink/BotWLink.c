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
	(1 << BOTWLINKMESH_LOTNCFC_LIMB) | \
	(1 << BOTWLINKMESH_LTHIGH_LIMB) | \
	(1 << BOTWLINKMESH_LOTNCBL_LIMB) | \
	(1 << BOTWLINKMESH_LOTNCFL_LIMB) | \
	(1 << BOTWLINKMESH_RTHIGH_LIMB) | \
	(1 << BOTWLINKMESH_LOTNCBR_LIMB) | \
	(1 << BOTWLINKMESH_LOTNCFR_LIMB))

#define FLAG_NO_LOWLEGS (1 << 0)
#define FLAG_NO_LOWERBODY (1 << 1)
#define FLAG_USE_SLERP (1 << 2)

static const s8 limbToPhysMap[BOTWLINKMESH_NUM_LIMBS] = {
	-1, -1, -1, //root, root, hips
	7, //lotncbc
	10, //lotncfc
	-1, -1, -1, //lthigh, lcalf, lfoot
	6, //lotncbl
	9, //lotncfl
	-1, //rthigh
	8, //lotncbr
	11, //lotncfr
	-1, -1, -1, -1, //rcalf, rfoot, torso, head
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

static const HairPhysLimits tunicFrontLimits = {{-32.0f, -32.0f, -32.0f}, { 32.0f,  32.0f,  32.0f}};
static const HairPhysLimits tunicBackLimits  = {{-32.0f, -32.0f, -32.0f}, { 32.0f,  32.0f,  32.0f}};
static const HairPhysLimits bangsLimits      = {{-16.0f, -16.0f, -16.0f}, { 16.0f,  16.0f,  16.0f}};
static const HairPhysLimits ponytailLimits   = {{-64.0f, -64.0f, -64.0f}, { 64.0f,  64.0f,  64.0f}};
static       HairPhysLimits tasselLLimits    = {{-0.15f,   0.0f, -0.05f}, { 0.0f, 0.0f, 0.0f}};
static       HairPhysLimits tasselRLimits    = {{ 0.15f,   0.0f, -0.05f}, { 0.0f, 0.0f, 0.0f}};
static const HairPhysBasic  tunicBasic    =  {1.0f,1.0f,      8.0f, 0.1f,  0.3f, 0.97f, 10.0f};
static const HairPhysBasic  bangsBasic    =  {0.004f,250.0f,  3.0f, 1.2f,  1.0f, 0.70f,  1.5f};
static const HairPhysBasic  ponytailBasic =  {0.002f,500.0f,  2.0f, 1.0f,  1.0f, 0.85f,  3.0f};
static const HairPhysBasic  tasselsBasic  =  {0.002f,500.0f,  3.0f, 30.0f, 1.0f, 0.97f,  0.0f};
static const HairPhysDouble tasselsLDouble= {{0.001f,999.9f,  2.0f, 30.0f, 1.0f, 0.97f,  0.0f}, ACTOR_SCALE, &tasselLLimits};
static const HairPhysDouble tasselsRDouble= {{0.001f,999.9f,  2.0f, 30.0f, 1.0f, 0.97f,  0.0f}, ACTOR_SCALE, &tasselRLimits};
static const HairPhysConnection tunicConns[] = {
	{1, 0.1f}, {0, 0.1f}, {2, 0.1f}, {1, 0.1f}, 
	{4, 0.1f}, {3, 0.1f}, {5, 0.1f}, {4, 0.1f}
};
static const HairPhysConstants physc[NUM_PHYS] = {
	/*ponytail*/{0, &ponytailBasic, &ponytailLimits, NULL, NULL, NULL},
	/*bangs1*/  {0, &bangsBasic, &bangsLimits, NULL, NULL, NULL},
	/*bangs2*/  {0, &bangsBasic, &bangsLimits, NULL, NULL, NULL},
	/*bangs3*/  {0, &bangsBasic, &bangsLimits, NULL, NULL, NULL},
	/*ltassels*/{1, &tasselsBasic, &tasselLLimits, &tasselsLDouble, NULL, NULL},
	/*rtassels*/{1, &tasselsBasic, &tasselRLimits, &tasselsRDouble, NULL, NULL},
	/*lotncfl*/ {2, &tunicBasic, &tunicFrontLimits, NULL, &tunicConns[0], NULL},
	/*lotncfc*/ {2, &tunicBasic, &tunicFrontLimits, NULL, &tunicConns[1], &tunicConns[2]},
	/*lotncfr*/ {2, &tunicBasic, &tunicFrontLimits, NULL, &tunicConns[3], NULL},
	/*lotncbl*/ {2, &tunicBasic, &tunicBackLimits , NULL, &tunicConns[4], NULL},
	/*lotncbc*/ {2, &tunicBasic, &tunicBackLimits , NULL, &tunicConns[5], &tunicConns[6]},
	/*lotncbr*/ {2, &tunicBasic, &tunicBackLimits , NULL, &tunicConns[7], NULL},
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
	float windMag;
	u32 flags;
	u8 timer;
	u8 editState;
	float *editPtr;
} Entity;

static const char * const editNames[4] = {
	"LX", "LZ", "RX", "RZ"
};
static void setEditPtr(Entity *en){
	if(en->editState == 0){
		en->editPtr = &tasselLLimits.neg.x;
	}else if(en->editState == 1){
		en->editPtr = &tasselLLimits.neg.z;
	}else if(en->editState == 2){
		en->editPtr = &tasselRLimits.neg.x;
	}else{
		en->editState = 3;
		en->editPtr = &tasselRLimits.neg.z;
	}
	Debugger_Printf("%s %f", editNames[en->editState], *en->editPtr);
}

static void init(Entity *en, GlobalContext *globalCtx) {
	//General setup
	Rupees_ChangeBy(4);
	en->flags = 0;
	en->editState = 0;
	setEditPtr(en);
	Actor_SetScale(&en->actor, ACTOR_SCALE);
	//Components setup
	ActorShape_Init(&en->actor.shape, 0.0f, ActorShadow_DrawCircle, 30.0f);
	SkelAnime_InitFlex(globalCtx, &en->skelAnime, &BotWLinkMesh, &BotWLinkMeshHeadmoveAnim, 
		en->jointTable, en->morphTable, BOTWLINKMESH_NUM_LIMBS);
	//Physics initialization
	s32 c = 0;
	for(s32 i=0; i<4; ++i) en->physStates[c++] = &en->physSimple[i];
	for(s32 i=0; i<2; ++i) en->physStates[c++] = &en->physDouble[i];
	for(s32 i=0; i<6; ++i) en->physStates[c++] = &en->physTunic[i];
	for(c=0; c<12; ++c) HairPhys_Init(en->physStates[c], &physc[c]);
	en->windMag = 1.0f;
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
			BotWLink_VO(en, VO_LINK_TAKUSAN);
			BotWLink_SetAnim(en, &BotWLinkMeshIdleAnim, ANIMMODE_LOOP, -8.0f);
		}else if((CTRLR_PRESS & BTN_DRIGHT)){
			BotWLink_VO(en, VO_LINK_DAIJINA);
			BotWLink_SetAnim(en, &BotWLinkMeshHeadmoveAnim, ANIMMODE_LOOP, -8.0f);
		}else if((CTRLR_PRESS & BTN_DUP)){
			en->flags ^= FLAG_USE_SLERP;
		}else if((CTRLR_RAW & BTN_CLEFT)){
			en->actor.shape.rot.y += 0x200;
		}else if((CTRLR_RAW & BTN_CRIGHT)){
			en->actor.shape.rot.y -= 0x200;
		}
	}else if((CTRLR_RAW & BTN_R)){
		if((CTRLR_RAW & BTN_CLEFT)){
			*en->editPtr -= 0.05f;
			setEditPtr(en);
		}else if((CTRLR_RAW & BTN_CRIGHT)){
			*en->editPtr += 0.05f;
			setEditPtr(en);
		}else if((CTRLR_PRESS & BTN_CUP)){
			--en->editState;
			setEditPtr(en);
		}else if((CTRLR_PRESS & BTN_CDOWN)){
			++en->editState;
			setEditPtr(en);
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
	if((en->flags & FLAG_USE_SLERP)) Patched_MorphUseSlerp(1);
	s32 animFinished = SkelAnime_Update(&en->skelAnime);
	Patched_MorphUseSlerp(0);
	if(animFinished){
		BotWLink_SetAnim(en, &BotWLinkMeshHeadmoveAnim, ANIMMODE_LOOP, -8.0f);
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
	u32 limbMask = 1 << limbIndex;
	if(((en->flags & FLAG_NO_LOWLEGS) && (limbMask & LIMB_IS_LOWLEGS)) ||
		((en->flags & FLAG_NO_LOWERBODY) && (limbMask & LIMB_IS_LOWERBODY))){
		*dList = NULL;
		return false;
	}
	s8 p = limbToPhysMap[limbIndex];
	if(p >= 0) HairPhys_Update(en->physStates[p], &physc[p], pos, rot, en->windMag);
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
