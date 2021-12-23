#include "ootmain.h"
#include "BotWLinkMesh.h"
#include "BotWLinkMeshIdleAnim.h"

// Actor Information
#define OBJ_ID 122 // primary object dependency
#define NUM_LIMBS 30
#define SHADOW_SIZE 30.0f

/*
static ColliderCylinderInitType1 sCylinderInit = {
    { COLTYPE_HIT0, AT_NONE, AC_NONE, OC1_ON | OC1_TYPE_PLAYER, COLSHAPE_CYLINDER, },
    { ELEMTYPE_UNK0, { 0x00000000, 0x00, 0x00 }, { 0x00000000, 0x00, 0x00 },
        TOUCH_NONE, BUMP_NONE, OCELEM_ON, },
    { 25, 80, 0, { 0, 0, 0 } },
};
*/

typedef struct {
	Actor actor;
	SkelAnime skelAnime;
	ColliderCylinder collider;
	Vec3s jointTable[NUM_LIMBS];
	Vec3s morphTable[NUM_LIMBS];
} Entity;

static void init(Entity *en, GlobalContext *globalCtx) {
	Actor_SetScale(&en->actor, 0.035f);
	/*
	ActorShape_Init(&en->actor.shape, 0.0f, ActorShadow_DrawCircle, SHADOW_SIZE);
	Collider_InitCylinder(globalCtx, &en->collider);
    Collider_SetCylinderType1(globalCtx, &en->collider, &en->actor, &sCylinderInit);
	*/
	SkelAnime_InitFlex(globalCtx, &en->skelAnime, &BotWLinkMesh, &BotWLinkMeshIdleAnim, 
		en->jointTable, en->morphTable, NUM_LIMBS);
	Rupees_ChangeBy(4);
}

static void destroy(Entity *en, GlobalContext *globalCtx) {
	SkelAnime_Free(&en->skelAnime, globalCtx);
}

static f32 VoiceFreqScale = 1.0f;
static f32 VoiceVol = 1.5f;
static u32 VoiceReverbAdd = 0;

static void updateVoice(Entity *en, GlobalContext *globalCtx) {
	s16 sfx = 0;
	if((CTRLR_PRESS & BTN_DLEFT)){
		sfx = NA_SE_EN_GANON_LAUGH;
	}else if((CTRLR_PRESS & BTN_DDOWN)){
		sfx = NA_SE_EN_GANON_VOICE_DEMO;
	}else if((CTRLR_PRESS & BTN_DRIGHT)){
		sfx = NA_SE_EN_GANON_THROW;
	}
	if(sfx == 0) return;
	Audio_PlaySoundGeneral(sfx, &en->actor.projectedPos, 4, &VoiceFreqScale, &VoiceVol,
		(f32*)&VoiceReverbAdd);
}

static void update(Entity *en, GlobalContext *globalCtx) {
	SkelAnime_Update(&en->skelAnime);
	updateVoice(en, globalCtx);
}

s32 BotWLink_OverrideLimbDraw(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, void* thisx) {
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
	.flags = 0x00000030,
	.objectId = OBJ_ID,
	.instanceSize = sizeof(Entity),
	.init = (ActorFunc)init,
	.destroy = (ActorFunc)destroy,
	.update = (ActorFunc)update,
	.draw = (ActorFunc)draw
};
