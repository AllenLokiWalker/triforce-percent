#include "ootmain.h"
#include "BotWLinkMesh.h"
#include "BotWLinkMeshIdleAnim.h"
#include "BotWLinkMeshBobokuwaAnim.h"
#include "../loader/debugger/debugger.h"

// Actor Information
#define OBJ_ID 122 // primary object dependency
#define SHADOW_SIZE 30.0f

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
	Vec3s jointTable[BOTWLINKMESH_NUM_LIMBS];
	Vec3s morphTable[BOTWLINKMESH_NUM_LIMBS];
	u32 flags;
	u32 lastflags; //debug only
	u8 timer;
} Entity;

static void init(Entity *en, GlobalContext *globalCtx) {
	Actor_SetScale(&en->actor, 0.035f);
	/*
	ActorShape_Init(&en->actor.shape, 0.0f, ActorShadow_DrawCircle, SHADOW_SIZE);
	Collider_InitCylinder(globalCtx, &en->collider);
    Collider_SetCylinderType1(globalCtx, &en->collider, &en->actor, &sCylinderInit);
	*/
	SkelAnime_InitFlex(globalCtx, &en->skelAnime, &BotWLinkMesh, &BotWLinkMeshIdleAnim, 
		en->jointTable, en->morphTable, BOTWLINKMESH_NUM_LIMBS);
	Rupees_ChangeBy(4);
	en->flags = 0;
}

static void destroy(Entity *en, GlobalContext *globalCtx) {
	SkelAnime_Free(&en->skelAnime, globalCtx);
}

/*
SkinMatrix_Vec3fMtxFMultXYZW(&globalCtx->mf_11D60, &actor->world.pos, &actor->projectedPos,
	&actor->projectedW);
if (func_800314B0(globalCtx, actor)) {
   actor->flags |= 0x40;
} else {
   actor->flags &= ~0x40;
}
func_800314B0 = func_800314D4(globalCtx, actor, &actor->projectedPos, actor->projectedW);
actor->uncullZoneForward = 1000.0f;
actor->uncullZoneScale = 350.0f;
actor->uncullZoneDownward = 700.0f;
//X: scale
//Y: bottom downward, top scale
//Z: bottom scale, top forward + scale
void func_8002BE04(GlobalContext* globalCtx, Vec3f* arg1, Vec3f* arg2, f32* arg3) {
   SkinMatrix_Vec3fMtxFMultXYZW(&globalCtx->mf_11D60, arg1, arg2, arg3);
   *arg3 = (*arg3 < 1.0f) ? 1.0f : (1.0f / *arg3);
}
*/

static bool uncullObject(GlobalContext* globalCtx, Vec3f *center, float xsize, 
	float yBelow, float yAbove, float zBehind, float zFar){
	//Based on func_800314D4
	Vec3f screen;
	float screen_w;
	func_8002BE04(globalCtx, center, &screen, &screen_w);
	//Debugger_Printf("%f %f %f", screen.x * screen_w, screen.y * screen_w, screen.z);
	return (screen.z > -zBehind) &&
		(screen.z < zFar) &&
		((fabsf(screen.x) - xsize) * screen_w < 1.0f) &&
		((screen.y + yAbove) * screen_w > -1.0f) &&
		((screen.y - yBelow) * screen_w < 1.0f);
}

static f32 VoiceFreqScale = 1.0f;
static f32 VoiceVol = 1.5f;
static u32 VoiceReverbAdd = 0;

/*
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
*/

static void update(Entity *en, GlobalContext *globalCtx) {
	//updateVoice(en, globalCtx);
	if(!(CTRLR_RAW & (BTN_R | BTN_L)) && (CTRLR_PRESS & BTN_DLEFT)){
		en->timer = 1;
		Animation_Change(&en->skelAnime, &BotWLinkMeshBobokuwaAnim, 1.0f, 0.0f, 
			Animation_GetLastFrame(&BotWLinkMeshBobokuwaAnim), ANIMMODE_ONCE, -4.0f);
	}
	if(en->timer > 0){
		if(en->timer == 5){
			Audio_PlaySoundGeneral(NA_SE_EN_GANON_LAUGH, &en->actor.projectedPos, 4, 
				&VoiceFreqScale, &VoiceVol, (f32*)&VoiceReverbAdd);
			en->timer = 0;
		}else{
			++en->timer;
		}
	}
	s32 animFinished = SkelAnime_Update(&en->skelAnime);
	if(animFinished){
		Animation_Change(&en->skelAnime, &BotWLinkMeshIdleAnim, 1.0f, 0.0f, 
			Animation_GetLastFrame(&BotWLinkMeshIdleAnim), ANIMMODE_LOOP, -8.0f);
	}
	/*
	if((CTRLR_RAW & BTN_R)){
		if((CTRLR_PRESS & BTN_DLEFT)){
			en->flags ^= FLAG_NO_LOWLEGS;
		}else if((CTRLR_PRESS & BTN_DDOWN)){
			en->flags ^= FLAG_NO_LOWERBODY;
		}
	}
	*/
	en->lastflags = en->flags;
	en->flags &= ~(FLAG_NO_LOWLEGS | FLAG_NO_LOWERBODY);
	Vec3f pos = en->actor.world.pos;
	pos.y += 20.0f;
	if(!uncullObject(globalCtx, &pos, 12.0f, 80.0f, 0.0f, 15.0f, 1000.0f)) en->flags |= FLAG_NO_LOWLEGS;
	pos = en->actor.world.pos;
	pos.y += 31.0f;
	if(!uncullObject(globalCtx, &pos, 15.0f, 100.0f, 0.0f, 15.0f, 1000.0f)) en->flags |= FLAG_NO_LOWERBODY;
	/*
	if(en->lastflags != en->flags){
		Debugger_Printf("calves %s legs %s", 
			(en->flags & FLAG_NO_LOWLEGS) ? "off" : "on",
			(en->flags & FLAG_NO_LOWERBODY) ? "off" : "on");
	}
	*/
}

s32 BotWLink_OverrideLimbDraw(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, void* thisx) {
	Entity *en = (Entity*)thisx;
	if(((en->flags & FLAG_NO_LOWLEGS) && ((1 << limbIndex) & LIMB_IS_LOWLEGS)) ||
		((en->flags & FLAG_NO_LOWERBODY) && ((1 << limbIndex) & LIMB_IS_LOWERBODY))){
		*dList = NULL;
		return false;
	}
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
