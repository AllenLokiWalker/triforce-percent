#include <z64ovl/oot/u10.h>
#include "obj.h"
#include "lighting.h"

// Actor Information
#define OBJ_ID 4 // primary object dependency (change if needed)

#define TRIFORCE_POWER 0
#define TRIFORCE_WISDOM 1
#define TRIFORCE_COURAGE 2

#define TFCOLOR_R 255
#define TFCOLOR_G 217
#define TFCOLOR_B 100

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
	  57,  88,  95,  60,  10,  60, 10, 57,  0
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
   64,64, 128, 128, 128, 128, 128,128,  1, 64
};
static const int8_t states_brightness[] = {
  -30,-30, 60,  60,  60,  60,  60, 60,  0, 60
};

static const uint8_t smoothtable[] = {
	0x00, 0x0A, 0x1C, 0x48, 0x80, 0xB8, 0xE4, 0xF6, 0xFF
};
static const int16_t pieces_rot[] = {
	1200, -870, 0,
	-570, 0, -1070,
	0, 1337, 580
};

typedef struct {
	z64_actor_t actor;
	uint8_t state, frame, totalframes;
	z64_light_node_t *lightnode;
	z64_light_t light;
	uint8_t initambient[3];
} entity_t;

static void setpos(entity_t *en, float x, float y, float z){
	en->actor.pos.x = x;
	en->actor.pos.y = y;
	en->actor.pos.z = z;
	if(en->actor.variable == 0){
		en->light.lightn.light2.x = (int16_t)x;
		en->light.lightn.light2.y = (int16_t)y - 12;
		en->light.lightn.light2.z = (int16_t)z + 4;
	}
}

static void rotcombine(int16_t *r, int16_t tbl, int32_t framesleft){
	int32_t rremain = (int32_t)(*r);
	if(tbl > 0 && rremain > 0){
		rremain = -0x10000 + rremain;
	}else if(tbl < 0 && rremain < 0){
		rremain = 0x10000 + rremain;
	}
	int32_t d = rremain / framesleft;
	if(framesleft > 3){
		//Do a little more than needed; will automatically slow down the
		//last few frames.
		//d += d >> 1;
		d <<= 1;
	}
	*r -= d;
}

static uint8_t interpambient(uint8_t init, uint8_t tfcolor, int16_t brightness){
	return (uint8_t)((((int32_t)init * (int32_t)(128 - brightness)) 
		+ ((int32_t)tfcolor * (int32_t)brightness)) >> 7);
}

static void init(entity_t *en, z64_global_t *global) {
	if(en->actor.variable == 0){
		z_lights_init_pos_0(&en->light, 0, 0, 0, TFCOLOR_R, TFCOLOR_G, TFCOLOR_B, 2000);
		en->lightnode = z_lights_insert(global, &global->lighting, &en->light);
		en->initambient[0] = global->lighting.ambient[0];
		en->initambient[1] = global->lighting.ambient[1];
		en->initambient[2] = global->lighting.ambient[2];
	}
	en->state = 0;
	en->frame = 0;
	en->totalframes = 0;
	setpos(en, 0.0f, 0.0f, 0.0f);
}

static void dest(entity_t *en, z64_global_t *global) {
	if(en->actor.variable == 0){
		z_lights_kill(global, &global->lighting, en->lightnode);
	}
}

static void play(entity_t *en, z64_global_t *global) {
	float x, y, s, brightness, lastx, lasty, lasts, lastbrightness;
	int16_t variable = en->actor.variable;
	if(variable >= 3) variable = 0;
	uint8_t state = en->state;
	uint8_t frame = en->frame;
	uint8_t frames = states_frames[state];
	if(frames == 0) frames = 1;
	uint8_t mode = states_mode[state];
	//Position, Scale, Brightness
	lastx = (float)states_lowpieces_x[state];
	lasty = (float)states_lowpieces_y[state];
	lasts = (float)states_scale[state];
	lastbrightness = (float)states_brightness[state];
	x = (float)states_lowpieces_x[state+1]; //End of current state
	y = (float)states_lowpieces_y[state+1];
	s = (float)states_scale[state+1];
	brightness = (float)states_brightness[state+1];
	if(variable == TRIFORCE_COURAGE){
		lastx = -lastx;
		x = -x;
	}else if(variable == TRIFORCE_POWER){
		lastx = 0.0f;
		x = 0.0f;
		lasty = (float)states_highpiece_y[state];
		y = (float)states_highpiece_y[state+1];
	}
	float m = 1.0f;
	if(mode >= STATE_MODE_SMOOTH){
		//Interpolate parameters
		m = (float)((uint32_t)frame << 3) / (float)frames;
		uint32_t smoothidx = (uint32_t)m;
		m -= (float)smoothidx; //fpart
		float smoothstart = (float)smoothtable[smoothidx];
		float smoothend = (float)smoothtable[smoothidx+1];
		m = (smoothend - smoothstart) * m + smoothstart;
		m *= 0.00390625f; //1/256
	}
	x = (x - lastx) * m + lastx;
	y = (y - lasty) * m + lasty;
	s = (s - lasts) * m + lasts;
	brightness = (brightness - lastbrightness) * m + lastbrightness;
	if(y < 40.0f || brightness < 0.0f) brightness = 0.0f;
	float z = (state == STATE_LINK) ? 50.0f : 0.0f;
	setpos(en, x, y, z);
	actor_set_scale(&en->actor, s * 2.5f * 0.0078125f); //1/128
	if(variable == 0){
		int16_t b16 = (int16_t)brightness;
		// global->lighting.ambient[0] = 255; //interpambient(en->initambient[0], TFCOLOR_R, b16);
		// global->lighting.ambient[1] = 0; //interpambient(en->initambient[1], TFCOLOR_G, b16);
		// global->lighting.ambient[2] = 0; //interpambient(en->initambient[2], TFCOLOR_B, b16);
		GlobalContext_Env_t *galias = (GlobalContext_Env_t*)global;
		// if(galias->envCtx.numLightSettings > 0){
		// 	galias->envCtx.lightSettingsList[0].ambientClrR = 255;
		// 	galias->envCtx.lightSettingsList[0].ambientClrG = 0;
		// 	galias->envCtx.lightSettingsList[0].ambientClrB = 0;
		// }
		galias->envCtx.screenfadeEnable = 1;
		galias->envCtx.screenfadeColor[0] = TFCOLOR_R;
		galias->envCtx.screenfadeColor[1] = TFCOLOR_G;
		galias->envCtx.screenfadeColor[2] = TFCOLOR_B;
		galias->envCtx.screenfadeColor[3] = b16 >> 2;
		en->light.lightn.light2.intensity = b16 << 4;
	}
	//Rotation
	const int16_t *rottable = &pieces_rot[3*variable];
	if(state == STATE_RISE || state == STATE_WAIT0){
		//Free rotation
		en->actor.rot.x += *rottable++;
		en->actor.rot.y += *rottable++;
		en->actor.rot.z += *rottable;
	}else if(state == STATE_COMBINE){
		//Rotate back to upright
		int32_t framesleft = frames - frame;
		rotcombine(&en->actor.rot.x, *rottable++, framesleft);
		rotcombine(&en->actor.rot.y, *rottable++, framesleft);
		rotcombine(&en->actor.rot.z, *rottable, framesleft);
	}else{
		//No rotation
		en->actor.rot.x = 0;
		en->actor.rot.y = 0;
		en->actor.rot.z = 0;
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
	++en->totalframes;
}

static void draw(entity_t *en, z64_global_t *global) {
	draw_dlist_opa(global, DL_TFPIECE);
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
