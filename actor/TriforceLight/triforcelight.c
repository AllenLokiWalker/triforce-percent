#include <z64ovl/oot/u10.h>
#include "obj.h"

// Actor Information
#define OBJ_ID 5 // primary object dependency

#define OPEN_DELAY 60
#define ANIM_LEN 50

typedef struct {
	z64_actor_t actor;
	z64_skelanime_t skelanime;
	u8 state, frame;
} entity_t;

static void init(entity_t *en, z64_global_t *global) {
	z_actor_set_scale(&en->actor, 1.8f);
	z_skelanime_init(global, true, &en->skelanime, SKEL_LIGHT,
		ANIM_LIGHTANIM);
	en->state = 0;
	en->frame = 0;
}

static void dest(entity_t *en, z64_global_t *global) {
	
}

static void play(entity_t *en, z64_global_t *global) {
    if(en->frame < OPEN_DELAY){
        z_skelanime_change_anim(&en->skelanime, ANIM_LIGHTANIM, 1.0f,
			0.0f, 0, 0, 0.0f);
	}else if(en->frame == OPEN_DELAY){
		en->state = 1;
	}else if(en->frame == OPEN_DELAY + ANIM_LEN - 1){
		en->state = 2;
	}
	if(en->state < 2) ++en->frame;
}

static void draw(entity_t *en, z64_global_t *global) {
	if(en->state < 2){
		z_skelanime_update_anim(&en->skelanime);
	}
	z_skelanime_draw(global, true, &en->actor, &en->skelanime, NULL, NULL);
}

const z64_actor_init_t init_vars = {
	.number = 0xDEAD, .padding = 0xBEEF, // <-- magic values, do not change
	.type = OVLTYPE_PROP,
	.room = 0x00,
	.flags = 0x00000010,
	.object = OBJ_ID,
	.instance_size = sizeof(entity_t),
	.init = init,
	.dest = dest,
	.main = play,
	.draw = draw
};
