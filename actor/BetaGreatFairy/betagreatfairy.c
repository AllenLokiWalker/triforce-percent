#include <z64ovl/oot/u10.h>
#include "obj.h"

// Actor Information
#define OBJ_ID 0x00A // primary object dependency (change if needed)

#define CYCLE_PERIOD 60
#define CYCLE_HEIGHT 10.0f
#define FLOAT_CENTER_HEIGHT 60.0f

typedef struct {
	z64_actor_t actor;
	s16 cycle_frames;
} entity_t;

static void init(entity_t *en, z64_global_t *global) {
	z_actor_set_scale(&en->actor, 0.085f);
	en->cycle_frames = 0;
}

static void dest(entity_t *en, z64_global_t *global) {
	
}

static void play(entity_t *en, z64_global_t *global) {
	float y = CYCLE_HEIGHT * z_sinf((float)en->cycle_frames * 
		(2.0f * 3.14159f / (float)CYCLE_PERIOD));
	en->actor.pos.z = en->actor.pos_init.z - 30.0f;
	en->actor.pos.y = en->actor.pos_init.y + y + FLOAT_CENTER_HEIGHT;
	en->actor.rot.x = 0xE00;
	++en->cycle_frames;
	if(en->cycle_frames >= CYCLE_PERIOD) en->cycle_frames = 0;
}

static void draw(entity_t *en, z64_global_t *global) {
	draw_dlist_opa(global, DL_BETAGREATFAIRY);
	draw_dlist_xlu(global, DL_BETAGREATFAIRY_FLOWER);
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
