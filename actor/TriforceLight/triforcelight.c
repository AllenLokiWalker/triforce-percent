#include <z64ovl/oot/u10.h>
#include "obj.h"

// Actor Information
#define OBJ_ID 16 // primary object dependency

#define OPEN_DELAY 60
#define ANIM_LEN 50
#define DISAPPEAR_FRAME 380

typedef struct {
	Actor actor;
	SkelAnime skelanime;
	u8 state;
	u16 frame;
} Entity;

static void init(Entity *en, GlobalContext *global) {
	Actor_SetScale(&en->actor, 1.8f);
	SkelAnime_Init(global, true, &en->skelanime, SKEL_LIGHT,
		ANIM_LIGHTANIM);
	en->state = 0;
	en->frame = 0;
}

static void destroy(Entity *en, GlobalContext *global) {
	
}

static void update(Entity *en, GlobalContext *global) {
    if(en->frame < OPEN_DELAY){
        Animation_Change(&en->skelanime, ANIM_LIGHTANIM, 1.0f,
			0.0f, 0, 0, 0.0f);
	}else if(en->frame == OPEN_DELAY){
		en->state = 1;
	}else if(en->frame == OPEN_DELAY + ANIM_LEN - 1){
		en->state = 2;
	}else if(en->frame == DISAPPEAR_FRAME){
		en->state = 3;
	}
	if(en->state < 3) ++en->frame;
}

static void draw(Entity *en, GlobalContext *global) {
	if(en->state < 2){
		SkelAnime_Update(&en->skelanime);
	}
	if(en->state < 3){
		SkelAnime_Draw(global, true, &en->actor, &en->skelanime, NULL, NULL);
	}
}

const ActorInit init_vars = {
	.id = 0xDEAD, .padding = 0xBEEF, // <-- magic values, do not change
	.category = ACTORCAT_PROP,
	.flags = 0x00000010,
	.object = OBJ_ID,
	.instance_size = sizeof(Entity),
	.init = init,
	.destroy = destroy,
	.update = update,
	.draw = draw
};
