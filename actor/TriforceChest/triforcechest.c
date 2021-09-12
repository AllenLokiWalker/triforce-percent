#include "ootmain.h"
#include "obj.h"

// Actor Information
#define OBJ_ID 5 // primary object dependency (change if needed)

#define OPEN_DELAY 60
#define ANIM_LEN 50

typedef struct {
	Actor actor;
	SkelAnime skelanime;
	u8 state, frame;
} Entity;

static void init(Entity *en, GlobalContext *globalCtx) {
	Actor_SetScale(&en->actor, 1.8f);
	SkelAnime_Init(globalCtx, &en->skelanime, (SkeletonHeader*)SKEL_TRIFORCECHEST,
		(AnimationHeader*)ANIM_CHESTOPENING, NULL, NULL, 0);
	en->state = 0;
	en->frame = 0;
}

static void destroy(Entity *en, GlobalContext *globalCtx) {
	
}

static void update(Entity *en, GlobalContext *globalCtx) {
    if(en->frame < OPEN_DELAY){
        Animation_Change(&en->skelanime, (AnimationHeader*)ANIM_CHESTOPENING,
			1.0f, 0.0f, 0.0f, 0, 0.0f);
	}else if(en->frame == OPEN_DELAY){
		en->state = 1;
	}else if(en->frame == OPEN_DELAY + ANIM_LEN - 1){
		en->state = 2;
	}
	if(en->state < 2) ++en->frame;
}

static void draw(Entity *en, GlobalContext *globalCtx) {
	if(en->state < 2){
		SkelAnime_Update(&en->skelanime);
	}
	SkelAnime_DrawOpa(globalCtx, en->skelanime.skeleton, en->skelanime.jointTable,
		NULL, NULL, &en->actor);
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
