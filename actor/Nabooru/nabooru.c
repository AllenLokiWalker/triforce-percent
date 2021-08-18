#include "ootmain.h"
#include "object_nb.h"

#define DEP_OBJECT_NUM 0xB3
#define NPC_ACTION_NUM 40
#define NPC_ACTION_SLOT 1
#define SHADOW_SIZE 25.0f
#define NUM_LIMBS 19
#define NB_LIMB_TORSO 0x08
#define NB_LIMB_HEAD 0x0F

#define NB_STATE_INIT 0
#define NB_STATE_TURN 1
#define NB_STATE_TALK1 2
#define NB_STATE_WAIT_GUARDS 3
#define NB_STATE_TALK2 4
#define NB_STATE_RELOAD 5
#define NB_STATE_TALK3 6
#define NB_STATE_REFUSED 7

static ColliderCylinderInitType1 sCylinderInit = {
    { COLTYPE_HIT0, AT_NONE, AC_NONE, OC1_ON | OC1_TYPE_PLAYER, COLSHAPE_CYLINDER, },
    { ELEMTYPE_UNK0, { 0x00000000, 0x00, 0x00 }, { 0x00000000, 0x00, 0x00 },
        TOUCH_NONE, BUMP_NONE, OCELEM_ON, },
    { 20, 80, 0, { 0, 0, 0 } },
};

static void *const EyeTextures[3] = {
	&gNabooruEyeOpenTex,  &gNabooruEyeHalfTex,  &gNabooruEyeClosedTex
};

typedef struct {
	Actor actor;
	SkelAnime skelAnime;
	ColliderCylinder collider;
    Vec3s jointTable[NUM_LIMBS];
    Vec3s morphTable[NUM_LIMBS];
	struct_80034A14_arg1 turnInfo;
	u8 initted;
	u8 state;
	u8 eyeTextureIndex;
	u8 blinkTimer;
	s16 timer;
} Entity;

static void init(Entity *en, GlobalContext *globalCtx) {
	en->initted = 0;
	if(en->actor.params != 0){
		Actor_Kill(&en->actor);
		return;
	}
	AnimationHeader *anim;
	if((NABOORU_CONTINUE_VAR & NABOORU_CONTINUE_BIT)){
		NABOORU_CONTINUE_VAR &= ~NABOORU_CONTINUE_BIT;
		en->state = NB_STATE_RELOAD;
		anim = &gNabooruSittingCrossLeggedLookingUpRightAnim;
	}else{
		en->state = NB_STATE_INIT;
		anim = &gNabooruSittingCrossLeggedAnim;
	}
	en->eyeTextureIndex = 0;
	en->blinkTimer = 0;
	en->timer = 0;
	en->actor.textId = 0x0B60;
	ActorShape_Init(&en->actor.shape, 0.0f, ActorShadow_DrawCircle, SHADOW_SIZE);
	Collider_InitCylinder(globalCtx, &en->collider);
    Collider_SetCylinderType1(globalCtx, &en->collider, &en->actor, &sCylinderInit);
	SkelAnime_InitFlex(globalCtx, &en->skelAnime, &gNabooruSkel, anim, 
		en->jointTable, en->morphTable, NUM_LIMBS);
	en->initted = 1;
}

static void destroy(Entity *en, GlobalContext *globalCtx) {
	if(!en->initted) return;
	Collider_DestroyCylinder(globalCtx, &en->collider);
	SkelAnime_Free(&en->skelAnime, globalCtx);
}

static void updateEyes(Entity *en){
	if(en->blinkTimer == 0){
		en->blinkTimer = Rand_S16Offset(60, 60);
	}else{
		--en->blinkTimer;
	}
	en->eyeTextureIndex = (en->blinkTimer < 3) ? en->blinkTimer : 0;
}

/*
static void updateTurnInfo(Entity *en, GlobalContext *globalCtx){
	en->turnInfo.unk_18 = PLAYER->actor.world.pos; //focusPos
	en->turnInfo.unk_14 = kREG(16) + 9.0f; //eyeHeight
	func_80034A14(&en->actor, &en->turnInfo, kREG(17) + 0xC, 2);
}
*/

static void update(Entity *en, GlobalContext *globalCtx) {
	Collider_UpdateCylinder(&en->actor, &en->collider);
    CollisionCheck_SetOC(globalCtx, &globalCtx->colChkCtx, &en->collider.base);
	Actor_UpdateBgCheckInfo(globalCtx, &en->actor, 75.0f, 30.0f, 30.0f, 5);
	updateEyes(en);
	s32 animDone = SkelAnime_Update(&en->skelAnime);
	if(en->state == NB_STATE_INIT){
		if(Actor_IsTalking(&en->actor, globalCtx)){
			Animation_Change(&en->skelAnime, 
				&gNabooruSittingCrossLeggedTurningToLookUpRightTransitionAnim, 
				1.0f, 0.0f,
				Animation_GetLastFrame(
				&gNabooruSittingCrossLeggedTurningToLookUpRightTransitionAnim),
				ANIMMODE_ONCE_INTERP, -4.0f);
			en->state = NB_STATE_TURN;
		}else{
			Actor_RequestToTalk(&en->actor, globalCtx);
		}
	}else if(en->state == NB_STATE_TURN){
		if(animDone){
			Animation_Change(&en->skelAnime, 
				&gNabooruSittingCrossLeggedLookingUpRightAnim, 
				1.0f, 0.0f,
				Animation_GetLastFrame(
				&gNabooruSittingCrossLeggedLookingUpRightAnim),
				ANIMMODE_LOOP, 0.0f);
			MESSAGE_START;
			en->state = NB_STATE_TALK1;
		}
	}else if(en->state == NB_STATE_TALK1){
		if (MESSAGE_ADVANCE_EVENT){
			en->state = NB_STATE_WAIT_GUARDS;
			en->timer = 0;
		}
	}else if(en->state == NB_STATE_WAIT_GUARDS){
		if(en->timer == 40){
			en->timer = 0;
			en->state = NB_STATE_TALK2;
			en->actor.textId = 0x0B61;
			MESSAGE_CONTINUE;
		}else{
			++en->timer;
		}
	}else if(en->state == NB_STATE_TALK2){
		if(en->timer >= 0) ++en->timer;
		if(en->timer == 20){
			//TODO trigger Link surprised action
			en->timer = -1;
		} //func_80AB3DB0
		if(MESSAGE_ADVANCE_EVENT){
			if(en->actor.textId == 0x0B65){
				gGlobalContext.nextEntranceIndex = 0x0127;
			    gGlobalContext.sceneLoadFlag = 0x14;
			    gSaveContext.cutsceneIndex = 0xFFF0;
			    gGlobalContext.fadeTransition = 3;
				NABOORU_CONTINUE_VAR |= NABOORU_CONTINUE_BIT;
			}else{
				++en->actor.textId;
				MESSAGE_CONTINUE;
			}
		}
	}else if(en->state == NB_STATE_RELOAD){
		if(en->timer == 0){
			//TODO set Link position
		}else if(en->timer == 20){
			en->actor.textId = 0x0B67;
			MESSAGE_START;
			en->state = NB_STATE_TALK3;
		}
		++en->timer;
	}else if(en->state == NB_STATE_TALK3){
		if(MESSAGE_ADVANCE_EVENT){
			en->actor.textId = 0x0B68;
			MESSAGE_CONTINUE;
		}else if(MESSAGE_ADVANCE_CHOICE){
			if(globalCtx->msgCtx.choiceIndex == 0) {
				//TODO teach song
			}else{
				en->actor.textId = 0x0B69;
				MESSAGE_CONTINUE;
				en->state = NB_STATE_REFUSED;
			}
		}
	}else if(en->state == NB_STATE_REFUSED){
		if (MESSAGE_ADVANCE_EVENT){
			en->actor.textId = 0x0B68;
			MESSAGE_CONTINUE;
			en->state = NB_STATE_TALK3;
		}
	}
}

s32 Nabooru_OverrideLimbDraw(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, void* thisx) {
	//TODO
	return false;
}

void Nabooru_PostLimbDraw(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3s* rot, void* thisx) {
	Entity *en = (Entity*)thisx;

    if (limbIndex == NB_LIMB_HEAD) {
        Vec3f vec1 = { 0.0f, 10.0f, 0.0f };
        Vec3f vec2;

        Matrix_MultVec3f(&vec1, &vec2);
        en->actor.focus.pos.x = vec2.x;
        en->actor.focus.pos.y = vec2.y;
        en->actor.focus.pos.z = vec2.z;
        en->actor.focus.rot.x = en->actor.world.rot.x;
        en->actor.focus.rot.y = en->actor.world.rot.y;
        en->actor.focus.rot.z = en->actor.world.rot.z;
    }
}

static void draw(Entity *en, GlobalContext *globalCtx) {
	func_80093D18(globalCtx->state.gfxCtx);
	void *seg08Tex = EyeTextures[en->eyeTextureIndex];
	gSPSegment(POLY_OPA_DISP++, 0x08, SEGMENTED_TO_VIRTUAL(seg08Tex));
    gSPSegment(POLY_OPA_DISP++, 0x09, SEGMENTED_TO_VIRTUAL(seg08Tex));
    gDPSetEnvColor(POLY_OPA_DISP++, 0, 0, 0, 255);
    gSPSegment(POLY_OPA_DISP++, 0x0C, &gActorXluSetup[2]); //Skips actual setup, just end DL
	SkelAnime_DrawFlexOpa(globalCtx, en->skelAnime.skeleton, en->skelAnime.jointTable,
		en->skelAnime.dListCount, Nabooru_OverrideLimbDraw, Nabooru_PostLimbDraw, en);
}

const ActorInit init_vars = {
	.id = 0xDEAD, .padding = 0xBEEF, // <-- magic values, do not change
	.category = ACTORCAT_NPC,
	.flags = 0x00000019,
	.objectId = DEP_OBJECT_NUM,
	.instanceSize = sizeof(Entity),
	.init = (ActorFunc)init,
	.destroy = (ActorFunc)destroy,
	.update = (ActorFunc)update,
	.draw = (ActorFunc)draw
};
