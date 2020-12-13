#include <z64ovl/oot/u10.h>
#include "obj.h"

// Actor Information
#define OBJ_ID 5 // primary object dependency (change if needed)

typedef struct {
	z64_actor_t actor;
	z64_skelanime_t skelanime;
	u8 state, frame;
} entity_t;

static void init(entity_t *en, z64_global_t *global) {
	z_actor_set_scale(&en->actor, 1.7f);
	z_skelanime_init(global, true, &en->skelanime, SKEL_TRIFORCECHEST,
		ANIM_CHESTOPENING);
	en->state = 0;
	en->frame = 0;
	z_skelanime_change_anim(&en->skelanime, ANIM_CHESTOPENING, 0.25f,
		0.0f, 0, 0, 0.0f);
}

static void dest(entity_t *en, z64_global_t *global) {
	
}

static void play(entity_t *en, z64_global_t *global) {
	if(en->frame == 40){
		en->state = 1;
	}else if(en->frame == 79){
		en->state = 2;
	}else if(en->frame == 128){
		en->state = 0;
		en->frame = 0;
		z_skelanime_change_anim(&en->skelanime, ANIM_CHESTOPENING, 0.25f,
			0.0f, 0, 0, 0.0f);
	}
	//if(en->state < 2) 
	++en->frame;
}

static void draw(entity_t *en, z64_global_t *global) {
	if(en->state == 1){
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
