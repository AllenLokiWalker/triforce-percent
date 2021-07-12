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

static void init(Entity *en, GlobalContext *global) {
	Actor_SetScale(&en->actor, 1.8f);
	SkelAnime_Init(global, false, &en->skelanime, SKEL_TRIFORCECHEST,
		ANIM_CHESTOPENING);
	en->state = 0;
	en->frame = 0;
}

static void destroy(Entity *en, GlobalContext *global) {
	
}

static void update(Entity *en, GlobalContext *global) {
    if(en->frame < OPEN_DELAY){
        Animation_Change(&en->skelanime, ANIM_CHESTOPENING, 1.0f,
			0.0f, 0, 0, 0.0f);
	}else if(en->frame == OPEN_DELAY){
		en->state = 1;
	}else if(en->frame == OPEN_DELAY + ANIM_LEN - 1){
		en->state = 2;
	}
	if(en->state < 2) ++en->frame;
}

static void draw(Entity *en, GlobalContext *global) {
	if(en->state < 2){
		SkelAnime_Update(&en->skelanime);
	}
	SkelAnime_Draw(global, false, &en->actor, &en->skelanime, NULL, NULL);
}

const ActorInit init_vars = {
	.id = 0xDEAD, .padding = 0xBEEF, // <-- magic values, do not change
	.category = ACTORCAT_PROP,
	.flags = 0x00000010,
	.objectId = OBJ_ID,
	.instanceSize = sizeof(Entity),
	.init = init,
	.destroy = destroy,
	.update = update,
	.draw = draw
};
