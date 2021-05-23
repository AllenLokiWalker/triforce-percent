#include <z64ovl/oot/u10.h>
#include "obj.h"

// Actor Information
#define OBJ_ID 0x00A // primary object dependency (change if needed)

typedef struct {
	z64_actor_t actor;
	u8 todo;
} entity_t;

static void init(entity_t *en, z64_global_t *global) {
	z_actor_set_scale(&en->actor, 1.0f);
}

static void dest(entity_t *en, z64_global_t *global) {
	
}

static void play(entity_t *en, z64_global_t *global) {
	
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
