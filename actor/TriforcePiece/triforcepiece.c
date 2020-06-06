#include <z64ovl/oot/u10.h>
#include "obj.h"

// Actor Information
#define OBJ_ID 0x010A // primary object dependency (change if needed)

#define TRIFORCE_POWER 0
#define TRIFORCE_WISDOM 1
#define TRIFORCE_COURAGE 2

#define STATE_START 0
#define STATE_RISE 1
#define STATE_WAIT0 2
#define STATE_COMBINE 3
#define STATE_WAIT1 4
#define STATE_SINK 5
#define STATE_WAIT2 6
#define STATE_DISAP 7
#define STATE_LINK 8
#define FSM_STATES 9

#define STATE_MODE_LAST 0
#define STATE_MODE_IMM 1
#define STATE_MODE_SMOOTH 2
static const uint8_t states_mode[] = {
	   1,   2,   2,   2,   2,  2,   2,  1,  0
};
// -- ST  RIS   W0  CMB   W1  SNK  W2  DS  LK
static const uint8_t states_frames[] = {
	  50,  90, 100,  60,  10,  60, 10, 60,  0
};
//These have an extra value at the beginning so we can interpolate from last
//to current without worrying about crashes
static const uint8_t states_highpiece_y[] = {
	0, 0, 125, 125, 117, 117,  87, 87,  0, 86
};
static const uint8_t states_lowpieces_y[] = {
	0, 0,  85,  85,  95,  95,  65, 65,  0, 75
};
// -- ST  RIS   W0  CMB   W1  SNK  W2  DS  LK
static const uint8_t states_lowpieces_x[] = {
	0, 0,  25,  25,  12,  12,  12, 12, 12,  6
};
static const uint8_t states_scale[] = {
   64,64, 128, 128, 128, 128, 128,128,128, 64
};

static const uint8_t smoothtable[] = {
	0x00, 0x0A, 0x1C, 0x48, 0x80, 0xB8, 0xE4, 0xF6, 0xFF
};
static const int16_t pieces_rot[] = {
	1200, -870, 0,
	-570, 0, -1070,
	0, 1337, 420 // :lenny_face:
};

typedef struct {
	z64_actor_t actor;
	uint8_t state, frame;
} entity_t;

static void setpos(entity_t *en, float x, float y, float z){
	en->actor.pos_2.x = x;
	en->actor.pos_2.y = y;
	en->actor.pos_2.z = z;
}

static void rotcombine(int16_t *r, int16_t tbl, int32_t framesleft){
	int32_t rremain = (int32_t)(*r);
	if(tbl > 0 && rremain > 0){
		rremain = 0x10000 - rremain;
	}else if(tbl < 0 && rremain < 0){
		rremain = -0x10000 - rremain;
	}
	int32_t d = rremain / framesleft;
	if(framesleft > 10){
		//Do a little more than needed; will automatically slow down the
		//last few frames.
		d += d >> 3;
	}
	*r -= d;
}

static void init(entity_t *en, z64_global_t *global) {
	/*
	en->state = 0;
	en->frame = 0;
	setpos(en, 0.0f, 0.0f, 0.0f);
	*/
}

static void dest(entity_t *en, z64_global_t *global) {
	//do nothing
}

static void play(entity_t *en, z64_global_t *global) {
	/*
	float x, y, s, lastx, lasty, lasts;
	int16_t variable = en->actor.variable;
	if(variable >= 3) variable = 0;
	uint8_t state = en->state;
	uint8_t frame = en->frame;
	uint8_t frames = states_frames[state];
	if(frames == 0) frames = 1;
	uint8_t mode = states_mode[state];
	//Position && Scale
	lastx = (float)states_lowpieces_x[state];
	lasty = (float)states_lowpieces_y[state];
	lasts = (float)states_scale[state];
	x = (float)states_lowpieces_x[state+1]; //End of current state
	y = (float)states_lowpieces_y[state+1];
	s = (float)states_scale[state+1];
	if(variable == TRIFORCE_COURAGE){
		lastx = -lastx;
		x = -x;
	}else if(variable == TRIFORCE_POWER){
		lastx = 0.0f;
		x = 0.0f;
		lasty = (float)states_highpiece_y[state];
		y = (float)states_highpiece_y[state+1];
	}
	if(mode >= STATE_MODE_SMOOTH){
		//Interpolate position && scale
		float m = (float)((uint32_t)frame << 3) / (float)frames;
		uint32_t smoothidx = (uint32_t)m;
		m -= (float)smoothidx; //fpart
		float smoothstart = (float)smoothtable[smoothidx];
		float smoothend = (float)smoothtable[smoothidx+1];
		m = (smoothend - smoothstart) * m + smoothstart;
		m *= 0.00390625f; //1/256
		x = (x - lastx) * m + lastx;
		y = (y - lasty) * m + lasty;
		s = (s - lasts) * m + lasts;
	}
	float z = (state == STATE_LINK) ? 50.0f : 0.0f;
	setpos(en, x, y, z);
	actor_set_scale(&en->actor, s * 2.5f * 0.0078125f); //1/128
	//Rotation
	const int16_t *rottable = &pieces_rot[3*variable];
	if(state == STATE_RISE || state == STATE_WAIT0){
		//Free rotation
		en->actor.rot_2.x += *rottable++;
		en->actor.rot_2.y += *rottable++;
		en->actor.rot_2.z += *rottable;
	}else if(state == STATE_COMBINE){
		//Rotate back to upright
		int32_t framesleft = frames - frame;
		rotcombine(&en->actor.rot_2.x, *rottable++, framesleft);
		rotcombine(&en->actor.rot_2.y, *rottable++, framesleft);
		rotcombine(&en->actor.rot_2.z, *rottable, framesleft);
	}else{
		//No rotation
		en->actor.rot_2.x = 0;
		en->actor.rot_2.y = 0;
		en->actor.rot_2.z = 0;
	}
	//Increment
	if(mode != STATE_MODE_LAST){
		++frame;
		if(frame >= frames){
			frame = 0;
			en->state = state+1;
		}
		en->frame = frame;
	}
	*/
}

static void draw(entity_t *en, z64_global_t *global) {
	/*
	draw_dlist_opa(global, DL_TFPIECE);
	*/
}

const z64_actor_init_t init_vars = {
	.number = 0xDEAD, .padding = 0xBEEF, // <-- magic values, do not change
	.type = 0x06, // type = stage prop
	.room = 0x00,
	.flags = 0x00000010,
	.object = OBJ_ID,
	.instance_size = sizeof(entity_t),
	.init = init,
	.dest = dest,
	.main = play,
	.draw = draw
};
