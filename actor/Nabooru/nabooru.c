#include "ootmain.h"
#include "object_nb.h"

#define DEP_OBJECT_NUM 0xB3
#define NPC_ACTION_NUM 40
#define NPC_ACTION_SLOT 1
#define SHADOW_SIZE 25.0f
#define NUM_LIMBS 19
#define NB_LIMB_TORSO 0x08
#define NB_LIMB_HEAD 0x0F

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
	u8 eyeTextureIndex;
	u8 blinkTimer;
	s16 timer;
	Actor *guardActor;
} Entity;

static void update_Init(Entity *en, GlobalContext *globalCtx);
static void update_Talk1(Entity *en, GlobalContext *globalCtx);
static void update_TalkGuards(Entity *en, GlobalContext *globalCtx);
static void update_WaitGuards(Entity *en, GlobalContext *globalCtx);
static void update_Talk2(Entity *en, GlobalContext *globalCtx);
static void update_Reload(Entity *en, GlobalContext *globalCtx);
static void update_Talk3(Entity *en, GlobalContext *globalCtx);
static void update_Refused(Entity *en, GlobalContext *globalCtx);
static void update_Teach1(Entity *en, GlobalContext *globalCtx);
static void update_Teach2(Entity *en, GlobalContext *globalCtx);

static void init(Entity *en, GlobalContext *globalCtx) {
	en->initted = 0;
	if(en->actor.params != 0){
		Actor_Kill(&en->actor);
		return;
	}
	if((NABOORU_CONTINUE_VAR & NABOORU_CONTINUE_BIT)){
		NABOORU_CONTINUE_VAR &= ~NABOORU_CONTINUE_BIT;
		en->actor.update = (ActorFunc)update_Reload;
		en->actor.textId = 0x0B68;
	}else{
		en->actor.update = (ActorFunc)update_Init;
		en->actor.textId = 0x0B60;
	}
	en->eyeTextureIndex = 0;
	en->blinkTimer = 0;
	en->timer = 0;
	ActorShape_Init(&en->actor.shape, 0.0f, ActorShadow_DrawCircle, SHADOW_SIZE);
	Collider_InitCylinder(globalCtx, &en->collider);
    Collider_SetCylinderType1(globalCtx, &en->collider, &en->actor, &sCylinderInit);
	SkelAnime_InitFlex(globalCtx, &en->skelAnime, &gNabooruSkel, &gNabooruSittingCrossLeggedAnim, 
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

static Actor *FindGuard(Actor *nabooru, GlobalContext *globalCtx){
	Actor* actor = globalCtx->actorCtx.actorLists[ACTORCAT_NPC].head;
    while (actor != NULL) {
        if(actor->id == ACTOR_EN_GE2 && actor->world.pos.x > nabooru->world.pos.x){
			return actor;
		}
		actor = actor->next;
    }
    return NULL;
}

static void updateTurnInfo(Entity *en, GlobalContext *globalCtx, s32 mode){
	if(mode < 0) return;
	f32 eyeHeight;
	Actor *target;
	if(mode == 1){
		if(en->guardActor == NULL) return;
		target = en->guardActor;
		eyeHeight = 120.0f;
	}else{
		target = &PLAYER->actor;
		eyeHeight = kREG(16) + 9.0f;
	}
	en->turnInfo.unk_18 = target->world.pos; //focusPos
	en->turnInfo.unk_14 = eyeHeight; //eyeHeight
	func_80034A14(&en->actor, &en->turnInfo, kREG(17) + 0xC, 2);
}

static s32 updateCommon(Entity *en, GlobalContext *globalCtx, s32 guard) {
	Collider_UpdateCylinder(&en->actor, &en->collider);
    CollisionCheck_SetOC(globalCtx, &globalCtx->colChkCtx, &en->collider.base);
	Actor_UpdateBgCheckInfo(globalCtx, &en->actor, 75.0f, 30.0f, 30.0f, 5);
	updateEyes(en);
	updateTurnInfo(en, globalCtx, guard);
	return SkelAnime_Update(&en->skelAnime);
}

static void update_Init(Entity *en, GlobalContext *globalCtx){
	updateCommon(en, globalCtx, -1);
	if(Actor_IsTalking(&en->actor, globalCtx)){
		//MESSAGE_START;
		en->actor.update = (ActorFunc)update_Talk1;
	}else{
		Actor_RequestToTalk(&en->actor, globalCtx);
	}
}

static void update_Talk1(Entity *en, GlobalContext *globalCtx){
	updateCommon(en, globalCtx, 0);
	if(MESSAGE_ADVANCE_EVENT){
		en->actor.update = (ActorFunc)update_TalkGuards;
		en->actor.textId = 0x0B61;
		en->guardActor = FindGuard(&en->actor, globalCtx);
		MESSAGE_CONTINUE;
	}
}

static void update_TalkGuards(Entity *en, GlobalContext *globalCtx){
	updateCommon(en, globalCtx, 1);
	if(MESSAGE_ADVANCE_EVENT){
		en->actor.update = (ActorFunc)update_WaitGuards;
		en->timer = 0;
	}
}

static void update_WaitGuards(Entity *en, GlobalContext *globalCtx){
	updateCommon(en, globalCtx, 1);
	if(en->timer == 50){
		en->timer = 0;
		en->actor.update = (ActorFunc)update_Talk2;
		en->actor.textId = 0x0B62;
		MESSAGE_CONTINUE;
	}else{
		++en->timer;
	}
}

static void update_Talk2(Entity *en, GlobalContext *globalCtx){
	updateCommon(en, globalCtx, 0);
	if(en->timer >= 0) ++en->timer;
	if(en->timer == 20){
		//TODO trigger Link surprised action
		en->timer = -1;
	}
	if(MESSAGE_ADVANCE_EVENT){
		if(en->actor.textId == 0x0B66){
			//gGlobalContext.nextEntranceIndex = 0x0127;
			gGlobalContext.sceneLoadFlag = 0x14;
			//gSaveContext.cutsceneIndex = 0xFFF0;
			gGlobalContext.fadeTransition = 3;
			NABOORU_CONTINUE_VAR |= NABOORU_CONTINUE_BIT;
		}else{
			++en->actor.textId;
			MESSAGE_CONTINUE;
		}
	}
}

static void update_Reload(Entity *en, GlobalContext *globalCtx){
	updateCommon(en, globalCtx, 0);
	if(en->timer == 0){
		static const Vec3f reloadLinkPos = {1904.0f, 0.0f, -688.0f};
		static const Vec3s reloadLinkRot = {0, 0x5555, 0};
		PLAYER->actor.world.pos = reloadLinkPos;
		PLAYER->actor.world.rot = reloadLinkRot;
		PLAYER->actor.shape.rot = reloadLinkRot;
	}
	if(Actor_IsTalking(&en->actor, globalCtx)){
		en->actor.update = (ActorFunc)update_Talk3;
	}else{
		en->actor.flags |= 0x10000; //auto talk
		Actor_RequestToTalkInRange(&en->actor, globalCtx, 1000.0f);
		/*
		PLAYER->targetActor = &en->actor;
	    PLAYER->targetActorDistance = en->actor.xzDistToPlayer;
	    PLAYER->exchangeItemId = EXCH_ITEM_NONE;
		*/
	}
	++en->timer;
}

static void update_Talk3(Entity *en, GlobalContext *globalCtx){
	updateCommon(en, globalCtx, 0);
	if(MESSAGE_ADVANCE_EVENT){
		++en->actor.textId;
		MESSAGE_CONTINUE;
	}else if(MESSAGE_ADVANCE_CHOICE){
		if(globalCtx->msgCtx.choiceIndex == 0) {
			func_8010BD58(globalCtx, 12); //Teach Song of Time
			en->timer = 0;
			en->actor.update = (ActorFunc)update_Teach1;
		}else{
			en->actor.textId = 0x0B6B;
			MESSAGE_CONTINUE;
			en->actor.update = (ActorFunc)update_Refused;
		}
	}
}

static void update_Refused(Entity *en, GlobalContext *globalCtx){
	updateCommon(en, globalCtx, 0);
	if (MESSAGE_ADVANCE_EVENT){
		en->actor.textId = 0x0B6A;
		MESSAGE_CONTINUE;
		en->actor.update = (ActorFunc)update_Talk3;
	}
}

static void update_Teach1(Entity *en, GlobalContext *globalCtx){
	updateCommon(en, globalCtx, 0);
	if(en->timer == 390){
		func_8010BD58(globalCtx, 25); //Learn Song of Time
		en->actor.update = (ActorFunc)update_Teach2;
	}else{
		++en->timer;
	}
}

static void update_Teach2(Entity *en, GlobalContext *globalCtx){
	updateCommon(en, globalCtx, 0);
	if(func_8010BDBC(&globalCtx->msgCtx) == 0){
		//TODO learn song cutscene
		en->actor.update = (ActorFunc)update_Init;
	}
}

s32 Nabooru_OverrideLimbDraw(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, void* thisx) {
	Entity *en = (Entity*)thisx;
	if(limbIndex == NB_LIMB_TORSO){
		rot->x += en->turnInfo.unk_0E.y;
		rot->y -= en->turnInfo.unk_0E.x;
	}else if(limbIndex == NB_LIMB_HEAD){
		rot->x += en->turnInfo.unk_08.y;
		rot->z += en->turnInfo.unk_08.x;
	}
	return false;
}

void Nabooru_PostLimbDraw(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3s* rot, void* thisx) {
	Entity *en = (Entity*)thisx;

    if (limbIndex == NB_LIMB_HEAD) {
        Vec3f nbHeadBoneOriginToHeadCenter = { 0.0f, 10.0f, 0.0f };
        Vec3f nbHeadCenterOut;

        Matrix_MultVec3f(&nbHeadBoneOriginToHeadCenter, &nbHeadCenterOut);
        en->actor.focus.pos.x = nbHeadCenterOut.x;
        en->actor.focus.pos.y = nbHeadCenterOut.y;
        en->actor.focus.pos.z = nbHeadCenterOut.z;
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
	.update = (ActorFunc)update_Init,
	.draw = (ActorFunc)draw
};
