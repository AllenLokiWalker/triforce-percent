#include "ootmain.h"
#include "BotWLinkMesh.h"

// Actor Information
#define OBJ_ID 122 // primary object dependency

typedef struct {
	Actor actor;
} Entity;

static void init(Entity *en, GlobalContext *globalCtx) {
	Actor_SetScale(&en->actor, 0.035f);
	Rupees_ChangeBy(4);
}

static void destroy(Entity *en, GlobalContext *globalCtx) {
	
}

static f32 VoiceFreqScale = 1.0f;
static f32 VoiceVol = 1.5f;
static u32 VoiceReverbAdd = 0;

static void update(Entity *en, GlobalContext *globalCtx) {
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

static void draw(Entity *en, GlobalContext *globalCtx) {
	func_80093D18(globalCtx->state.gfxCtx);
	Gfx_DrawDListOpa(globalCtx, BotWLinkMesh);
	func_80093D18(globalCtx->state.gfxCtx);
}

const ActorInitExplPad init_vars = {
	.id = 0xDEAD, .padding = 0xBEEF, // <-- magic values, do not change
	.category = ACTORCAT_PROP,
	.flags = 0x00000000,
	.objectId = OBJ_ID,
	.instanceSize = sizeof(Entity),
	.init = (ActorFunc)init,
	.destroy = (ActorFunc)destroy,
	.update = (ActorFunc)update,
	.draw = (ActorFunc)draw
};
