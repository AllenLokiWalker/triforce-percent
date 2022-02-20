#include "ootmain.h"

#define FLAG_INVISIBLE (1 << 8)
#define FLAG_EYESCLOSED (1 << 9)
#define FLAG_DELAYROT (1 << 10)

typedef struct {
    Actor actor;
	SkelAnime skelAnime;
	u32 flags;
    s16 actionnum;
	u16 actionframe;
	u16 sfx;
	u8 sfxframe;
	u8 eyeTextureIndex;
	u8 eyeState;
	u8 blinkTimer;
	AnimationHeader *anim;
	AnimationHeader *anim_whendone;
	f32 morph_whendone;
	float windX, windZ;
} BotWActor;

typedef void (*BotWCSActionFunc)(BotWActor *botw, GlobalContext* globalCtx);

typedef struct {
    AnimationHeader *anim;
    f32 morph;
    AnimationHeader *anim_whendone;
    f32 morph_whendone;
    u16 flags_set;
    u16 flags_clear;
    u16 sfx;
    u8 sfxframe;
    BotWCSActionFunc func;
} BotWCSActionDef;
 
static inline void BotWActor_Init(BotWActor *botw, GlobalContext *globalCtx, 
        FlexSkeletonHeader *skel, AnimationHeader *initAnim,
        Vec3s *jointTable, Vec3s *morphTable, s32 numLimbs, f32 scale) {
    botw->flags = 0;
    botw->actionnum = -1;
	botw->actionframe = 0;
    botw->sfx = 0;
	botw->eyeTextureIndex = 0;
    botw->eyeState = 0;
	botw->blinkTimer = 0;
    botw->anim = &initAnim;
	botw->anim_whendone = NULL;
	botw->windX = 0.707f;
	botw->windZ = -0.707f;
	Actor_SetScale(&botw->actor, scale);
    SkelAnime_InitFlex(globalCtx, &botw->skelAnime, skel, initAnim, 
		jointTable, morphTable, numLimbs);
    ActorShape_Init(&botw->actor.shape, 0.0f, ActorShadow_DrawCircle, 30.0f); //TODO not working?
}

static inline void BotWActor_Destroy(BotWActor *botw, GlobalContext *globalCtx) {
    SkelAnime_Free(&botw->skelAnime, globalCtx);
}

static inline void BotWActor_VO(BotWActor *botw, u16 sfx) {
    static f32 VoiceFreqScale = 1.0f;
    static f32 VoiceVol = 0.99f;
    static u32 VoiceReverbAdd = 0;
    Audio_PlaySoundGeneral(sfx, &botw->actor.projectedPos, 4, 
		&VoiceFreqScale, &VoiceVol,	(f32*)&VoiceReverbAdd);
}

static inline void BotWActor_SetAnim(BotWActor *botw, AnimationHeader *anim, u8 mode, f32 morphFrames) {
	Animation_Change(&botw->skelAnime, anim, 1.0f, 0.0f, 
		Animation_GetLastFrame(anim), mode, morphFrames);
}

static void BotWActor_UpdateEyes(BotWActor *botw){
	if((botw->flags & FLAG_EYESCLOSED) && (botw->eyeState == 0 || botw->eyeState == 3)){
		botw->eyeState = 1; //Start closing eyes
	}else if(!(botw->flags & FLAG_EYESCLOSED) && (botw->eyeState == 1 || botw->eyeState == 2)){
		botw->eyeState = 3; //Start opening eyes
	}
	if(botw->eyeState == 1){
		++botw->blinkTimer;
		botw->eyeTextureIndex = 1;
		if(botw->blinkTimer > 5){
			botw->eyeState = 2;
		}
	}else if(botw->eyeState == 2){
		botw->eyeTextureIndex = 2;
	}else if(botw->eyeState == 3){
		++botw->blinkTimer;
		botw->eyeTextureIndex = 1;
		if(botw->blinkTimer > 5){
			botw->eyeState = 0;
			botw->blinkTimer = 20;
		}
	}else{
		if(botw->blinkTimer == 0){
			botw->blinkTimer = Rand_S16Offset(60, 60);
		}else{
			--botw->blinkTimer;
		}
		botw->eyeTextureIndex = (botw->blinkTimer < 3) ? botw->blinkTimer : 0;
	}
}

static inline void BotWActor_Update(BotWActor *botw, GlobalContext *globalCtx, 
		const BotWCSActionDef *ActionDefs, s32 nActionDefs, s32 actionSlot) {
	++botw->actionframe;
    CsCmdActorAction *action = globalCtx->csCtx.npcActions[actionSlot];
	bool actionValid = (globalCtx->csCtx.state != 0) && (action != NULL) && (action->action < nActionDefs);
	if(actionValid){
		const BotWCSActionDef *def = &ActionDefs[action->action];
		if(action->action != botw->actionnum){
			botw->actionnum = action->action;
			botw->actionframe = 0;
			if(def->anim != NULL && def->anim != botw->anim){
				BotWActor_SetAnim(botw, def->anim, 
					def->anim_whendone == NULL ? ANIMMODE_LOOP : ANIMMODE_ONCE, def->morph);
				botw->anim = def->anim;
				botw->anim_whendone = def->anim_whendone;
				botw->morph_whendone = def->morph_whendone;
			}
			if(def->sfx != 0){
				botw->sfx = def->sfx;
				botw->sfxframe = def->sfxframe;
			}
		}
		botw->flags &= ~(u32)(def->flags_clear | FLAG_INVISIBLE | FLAG_DELAYROT);
		botw->flags |= def->flags_set;
		f32 frac = (f32)(globalCtx->csCtx.frames - action->startFrame) / (f32)(action->endFrame - action->startFrame);
		if(frac < 0.0f) frac = 0.0f;
		if(frac > 1.0f) frac = 1.0f;
		f32 finv = 1.0f - frac;
		botw->actor.world.pos.x = finv * (f32)action->startPos.x + frac * (f32)action->endPos.x;
		botw->actor.world.pos.y = finv * (f32)action->startPos.y + frac * (f32)action->endPos.y;
		botw->actor.world.pos.z = finv * (f32)action->startPos.z + frac * (f32)action->endPos.z;
		s16 drot = botw->actor.shape.rot.y - action->rot.y;
        const s16 minrot = 0x100;
		if(drot < 0) drot = -drot;
		if((botw->flags & FLAG_DELAYROT)){
			(void)0; //don't rotate
		}else if(drot <= minrot){
			botw->actor.shape.rot.y = action->rot.y;
		}else{
			drot >>= 3;
			if(drot < minrot) drot = minrot;
			Math_StepToAngleS(&botw->actor.shape.rot.y, action->rot.y, drot);
		}
		if(def->func != NULL) def->func(botw, globalCtx);
	}
	BotWActor_UpdateEyes(botw);
	s32 animFinished = SkelAnime_Update(&botw->skelAnime);
	if(animFinished){
		if(botw->anim_whendone != NULL){
			BotWActor_SetAnim(botw, botw->anim_whendone, ANIMMODE_LOOP, botw->morph_whendone);
			botw->anim = botw->anim_whendone;
			botw->anim_whendone = NULL;
		}
		if(actionValid && (botw->flags & FLAG_DELAYROT)){
			botw->actor.shape.rot.y = action->rot.y;
		}
	}
	if(botw->sfx != 0 && (u16)botw->sfxframe == botw->actionframe){
		BotWActor_VO(botw, botw->sfx);
		botw->sfx = 0;
	}
}

static inline void BotWActor_DrawMain(BotWActor *botw, GlobalContext *globalCtx,
		void *const *EyeTextures, OverrideLimbDrawOpa overrideLimbDraw, PostLimbDrawOpa postLimbDraw) {
	func_80093D18(globalCtx->state.gfxCtx);
	void *seg08Tex = EyeTextures[botw->eyeTextureIndex];
	gSPSegment(POLY_OPA_DISP++, 0x08, SEGMENTED_TO_VIRTUAL(seg08Tex));
	SkelAnime_DrawFlexOpa(globalCtx, botw->skelAnime.skeleton, botw->skelAnime.jointTable,
		botw->skelAnime.dListCount, overrideLimbDraw, postLimbDraw, botw);
	func_80093D18(globalCtx->state.gfxCtx);
}
