#include "ootmain.h"
#include "BotWLinkMesh.h"
#include "BotWLinkMeshIdleAnim.h"
#include "BotWLinkMeshBobokuwaAnim.h"
#include "../loader/debugger/debugger.h"

// Actor Information
#define OBJ_ID 122 // primary object dependency
#define SHADOW_SIZE 30.0f

#define LIMB_IS_LOWLEGS ( \
	(1 << BOTWLINKMESH_LCALF_LIMB) | \
	(1 << BOTWLINKMESH_LFOOT_LIMB) | \
	(1 << BOTWLINKMESH_RCALF_LIMB) | \
	(1 << BOTWLINKMESH_RFOOT_LIMB))
#define LIMB_IS_LOWERBODY ( LIMB_IS_LOWLEGS | \
	(1 << BOTWLINKMESH_LOTNCBC_LIMB) | \
	(1 << BOTWLINKMESH_LOTNCFC_LIMB) | \
	(1 << BOTWLINKMESH_LTHIGH_LIMB) | \
	(1 << BOTWLINKMESH_LOTNCBL_LIMB) | \
	(1 << BOTWLINKMESH_LOTNCFL_LIMB) | \
	(1 << BOTWLINKMESH_RTHIGH_LIMB) | \
	(1 << BOTWLINKMESH_LOTNCBR_LIMB) | \
	(1 << BOTWLINKMESH_LOTNCFR_LIMB))

#define FLAG_NO_LOWLEGS (1 << 0)
#define FLAG_NO_LOWERBODY (1 << 1)

static const s8 limbToPhysMap[BOTWLINKMESH_NUM_LIMBS] = {
	-1, -1, -1, //root, root, hips
	0, //lotncbc
	1, //lotncfc
	-1, -1, -1, //lthigh, lcalf, lfoot
	2, //lotncbl
	3, //lotncfl
	-1, //rthigh
	4, //lotncbr
	5, //lotncfr
	-1, -1, -1, -1, //rcalf, rfoot, torso, head
	6, //bangs1
	7, //bangs2
	8, //bangs3
	-1, -1, //jaw, lmouth
	9, //ltassels
	10, //ponytail
	-1, //rmouth
	11, //rtassels
	-1, -1, -1, -1 //luparm, lloarm, ruparm, rloarm
};
#define NUM_PHYS 12

typedef struct {
	float mass;
	float oneovermass;
	float len;
	float restoreforce;
	float yawmult;
	float dampening;
	float windpush;
} PhysBasic;

typedef struct {
	Vec3f neg;
	Vec3f pos;
} PhysLimits;

typedef struct {
	float mass;
	float len;
	const PhysLimits *lim;
} PhysDouble;

typedef struct {
	u8 index;
	float force;
} PhysConnection;

typedef struct {
	u8 mode; // 0 simple, 1 double, 2 tunic
	u8 indexInMode;
	const PhysBasic *b;
	const PhysLimits *lim;
	const PhysDouble *dbl;
	const PhysConnection *conn1;
	const PhysConnection *conn2;
} PhysConstants;

#define unitRot 256.0f
static const PhysBasic tunicBasic    = {1.0f,1.0f,      8.0f, 0.1f,  0.3f, 0.97f, 10.0f};
static const PhysBasic bangsBasic    = {0.0025f,400.0f, 3.0f, 1.2f,  1.0f, 0.70f,  1.5f};
static const PhysBasic ponytailBasic = {0.002f,500.0f,  2.0f, 1.0f,  1.0f, 0.85f,  3.0f};
static const PhysBasic tasselsBasic  = {0.2f,0.5f,      3.0f, 0.02f, 5.0f, 0.99f, 40.0f};
static const PhysLimits tunicFrontLimits = {{-32.0f, -32.0f, -32.0f}, { 32.0f,  32.0f,  32.0f}};
static const PhysLimits tunicBackLimits  = {{-32.0f, -32.0f, -32.0f}, { 32.0f,  32.0f,  32.0f}};
static const PhysLimits bangsLimits      = {{-16.0f, -16.0f, -16.0f}, { 16.0f,  16.0f,  16.0f}};
static const PhysLimits ponytailLimits   = {{-64.0f, -64.0f, -64.0f}, { 64.0f,  64.0f,  64.0f}};
static const PhysLimits tassels1Limits   = {{-32.0f, -32.0f, -32.0f}, { 32.0f,  32.0f,  32.0f}};
static const PhysLimits tassels2Limits   = {{-32.0f, -32.0f, -32.0f}, { 32.0f,  32.0f,  32.0f}};
static const PhysDouble tasselsDouble = {2.0f, 3.0f, &tassels2Limits};
static const PhysConnection tunicConns[] = {
	{2, 0.1f}, {4, 0.1f}, 
	{3, 0.1f}, {5, 0.1f},
	{0, 0.1f}, {0, 0.1f}, {1, 0.1f}, {1, 0.1f}
};
static const PhysConstants physc[NUM_PHYS] = {
	/*lotncbc*/ {2, 0, &tunicBasic, &tunicBackLimits , NULL, &tunicConns[0], &tunicConns[1]},
	/*lotncfc*/ {2, 1, &tunicBasic, &tunicFrontLimits, NULL, &tunicConns[2], NULL},
	/*lotncbl*/ {2, 2, &tunicBasic, &tunicBackLimits , NULL, &tunicConns[3], NULL},
	/*lotncfl*/ {2, 3, &tunicBasic, &tunicFrontLimits, NULL, &tunicConns[4], &tunicConns[5]},
	/*lotncbr*/ {2, 4, &tunicBasic, &tunicBackLimits , NULL, &tunicConns[6], NULL},
	/*lotncfr*/ {2, 5, &tunicBasic, &tunicFrontLimits, NULL, &tunicConns[7], NULL},
	/*bangs1*/  {0, 1, &bangsBasic, &bangsLimits, NULL, NULL, NULL},
	/*bangs2*/  {0, 2, &bangsBasic, &bangsLimits, NULL, NULL, NULL},
	/*bangs3*/  {0, 3, &bangsBasic, &bangsLimits, NULL, NULL, NULL},
	/*ltassels*/{1, 0, &tasselsBasic, &tassels1Limits, &tasselsDouble, NULL, NULL},
	/*ponytail*/{0, 0, &ponytailBasic, &ponytailLimits, NULL, NULL, NULL},
	/*rtassels*/{1, 1, &tasselsBasic, &tassels1Limits, &tasselsDouble, NULL, NULL}
};

typedef struct {
	Vec3f r; //rotation
	Vec3f v; //angular velocity
} PhysSimpleState;

typedef struct {
	Vec3f lastFulcrum;
	Vec3f com1; //center of mass
	Vec3f com2;
	Vec3f vel1;
	Vec3f vel2;
	s16 rot;
	s16 rv;
} PhysDoubleState;

typedef struct {
	float todo;
} PhysTunicState;

/*
static ColliderCylinderInitType1 sCylinderInit = {
    { COLTYPE_HIT0, AT_NONE, AC_NONE, OC1_ON | OC1_TYPE_PLAYER, COLSHAPE_CYLINDER, },
    { ELEMTYPE_UNK0, { 0x00000000, 0x00, 0x00 }, { 0x00000000, 0x00, 0x00 },
        TOUCH_NONE, BUMP_NONE, OCELEM_ON, },
    { 25, 80, 0, { 0, 0, 0 } },
};
*/

typedef struct {
	Actor actor;
	SkelAnime skelAnime;
	ColliderCylinder collider;
	Vec3s jointTable[BOTWLINKMESH_NUM_LIMBS];
	Vec3s morphTable[BOTWLINKMESH_NUM_LIMBS];
	PhysSimpleState physSimple[4];
	PhysDoubleState physDouble[2];
	PhysTunicState physTunic[6];
	float windMag;
	u32 flags;
	//u32 lastflags;
	u8 timer;
} Entity;

static void init(Entity *en, GlobalContext *globalCtx) {
	Actor_SetScale(&en->actor, 0.035f);
	/*
	ActorShape_Init(&en->actor.shape, 0.0f, ActorShadow_DrawCircle, SHADOW_SIZE);
	Collider_InitCylinder(globalCtx, &en->collider);
    Collider_SetCylinderType1(globalCtx, &en->collider, &en->actor, &sCylinderInit);
	*/
	SkelAnime_InitFlex(globalCtx, &en->skelAnime, &BotWLinkMesh, &BotWLinkMeshIdleAnim, 
		en->jointTable, en->morphTable, BOTWLINKMESH_NUM_LIMBS);
	Rupees_ChangeBy(4);
	en->flags = 0;
	//Physics initialization
	bzero(&en->physSimple, 4*sizeof(PhysSimpleState) + 2*sizeof(PhysDoubleState) + 6*sizeof(PhysTunicState));
	en->windMag = 1.0f;
}

static void destroy(Entity *en, GlobalContext *globalCtx) {
	SkelAnime_Free(&en->skelAnime, globalCtx);
}

/*
SkinMatrix_Vec3fMtxFMultXYZW(&globalCtx->mf_11D60, &actor->world.pos, &actor->projectedPos,
	&actor->projectedW);
if (func_800314B0(globalCtx, actor)) {
   actor->flags |= 0x40;
} else {
   actor->flags &= ~0x40;
}
func_800314B0 = func_800314D4(globalCtx, actor, &actor->projectedPos, actor->projectedW);
actor->uncullZoneForward = 1000.0f;
actor->uncullZoneScale = 350.0f;
actor->uncullZoneDownward = 700.0f;
//X: scale
//Y: bottom downward, top scale
//Z: bottom scale, top forward + scale
void func_8002BE04(GlobalContext* globalCtx, Vec3f* arg1, Vec3f* arg2, f32* arg3) {
   SkinMatrix_Vec3fMtxFMultXYZW(&globalCtx->mf_11D60, arg1, arg2, arg3);
   *arg3 = (*arg3 < 1.0f) ? 1.0f : (1.0f / *arg3);
}
*/

static bool uncullObject(GlobalContext* globalCtx, Vec3f *center, float xsize, 
	float yBelow, float yAbove, float zBehind, float zFar){
	//Based on func_800314D4
	Vec3f screen;
	float screen_w;
	func_8002BE04(globalCtx, center, &screen, &screen_w);
	//Debugger_Printf("%f %f %f", screen.x * screen_w, screen.y * screen_w, screen.z);
	return (screen.z > -zBehind) &&
		(screen.z < zFar) &&
		((fabsf(screen.x) - xsize) * screen_w < 1.0f) &&
		((screen.y + yAbove) * screen_w > -1.0f) &&
		((screen.y - yBelow) * screen_w < 1.0f);
}

static f32 VoiceFreqScale = 1.0f;
static f32 VoiceVol = 1.5f;
static u32 VoiceReverbAdd = 0;

/*
static void updateVoice(Entity *en, GlobalContext *globalCtx) {
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
*/

static void update(Entity *en, GlobalContext *globalCtx) {
	//updateVoice(en, globalCtx);
	if(!(CTRLR_RAW & (BTN_R | BTN_L)) && (CTRLR_PRESS & BTN_DLEFT)){
		en->timer = 1;
		Animation_Change(&en->skelAnime, &BotWLinkMeshBobokuwaAnim, 1.0f, 0.0f, 
			Animation_GetLastFrame(&BotWLinkMeshBobokuwaAnim), ANIMMODE_ONCE, -4.0f);
	}
	if(en->timer > 0){
		if(en->timer == 5){
			Audio_PlaySoundGeneral(NA_SE_EN_GANON_LAUGH, &en->actor.projectedPos, 4, 
				&VoiceFreqScale, &VoiceVol, (f32*)&VoiceReverbAdd);
			en->timer = 0;
		}else{
			++en->timer;
		}
	}
	s32 animFinished = SkelAnime_Update(&en->skelAnime);
	if(animFinished){
		Animation_Change(&en->skelAnime, &BotWLinkMeshIdleAnim, 1.0f, 0.0f, 
			Animation_GetLastFrame(&BotWLinkMeshIdleAnim), ANIMMODE_LOOP, -8.0f);
	}
	/*
	if((CTRLR_RAW & BTN_R)){
		if((CTRLR_PRESS & BTN_DLEFT)){
			en->flags ^= FLAG_NO_LOWLEGS;
		}else if((CTRLR_PRESS & BTN_DDOWN)){
			en->flags ^= FLAG_NO_LOWERBODY;
		}
	}
	*/
	//en->lastflags = en->flags;
	en->flags &= ~(FLAG_NO_LOWLEGS | FLAG_NO_LOWERBODY);
	Vec3f pos = en->actor.world.pos;
	pos.y += 20.0f;
	if(!uncullObject(globalCtx, &pos, 12.0f, 80.0f, 0.0f, 15.0f, 1000.0f)) en->flags |= FLAG_NO_LOWLEGS;
	pos = en->actor.world.pos;
	pos.y += 31.0f;
	if(!uncullObject(globalCtx, &pos, 15.0f, 100.0f, 0.0f, 15.0f, 1000.0f)) en->flags |= FLAG_NO_LOWERBODY;
	/*
	if(en->lastflags != en->flags){
		Debugger_Printf("calves %s legs %s", 
			(en->flags & FLAG_NO_LOWLEGS) ? "off" : "on",
			(en->flags & FLAG_NO_LOWERBODY) ? "off" : "on");
	}
	*/
}

s32 BotWLink_OverrideLimbDraw(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, void* thisx) {
	Entity *en = (Entity*)thisx;
	u32 limbMask = 1 << limbIndex;
	if(((en->flags & FLAG_NO_LOWLEGS) && (limbMask & LIMB_IS_LOWLEGS)) ||
		((en->flags & FLAG_NO_LOWERBODY) && (limbMask & LIMB_IS_LOWERBODY))){
		*dList = NULL;
		return false;
	}
	s8 p = limbToPhysMap[limbIndex];
	if(p < 0) return false;
	u8 mode = physc[p].mode;
	u8 iim = physc[p].indexInMode;
	const PhysBasic *b = physc[p].b;
	const PhysLimits *lim = physc[p].lim;
	float dt = 0.05f;
	//Vec3f boneHead;
	//Matrix_MultVec3f(pos, boneHead);
	float rand1 = Rand_ZeroOne();
	float rand2 = Rand_ZeroOne();
	float rand3 = Rand_ZeroOne();
	if(mode == 0){
		//Simple
		PhysSimpleState *s = &en->physSimple[iim];
		Vec3f force; force.x = 0.0f; force.y = 0.0f; force.z = 0.0f;
		//Restore force, proportional to negative distance from 0. This is a
		//spring force, not gravity, so it isn't proportional to mass.
		force.x -= b->restoreforce * s->r.x;
		force.y -= b->restoreforce * s->r.y;
		force.z -= b->restoreforce * s->r.z;
		//Wind force, just random centered.
		force.x += (en->windMag * b->windpush) * (rand1 - 0.5f);
		force.y += (en->windMag * b->windpush) * (rand2 - 0.5f);
		force.z += (en->windMag * b->windpush) * (rand3 - 0.5f);
		//Dampen velocity
		s->v.x *= b->dampening;
		s->v.y *= b->dampening;
		s->v.z *= b->dampening;
		//dv = f / m * dt
		s->v.x += force.x * b->oneovermass * dt;
		s->v.y += force.y * b->oneovermass * dt;
		s->v.z += force.z * b->oneovermass * dt;
		//dx = v * dt
		s->r.x += s->v.x * dt;
		s->r.y += s->v.y * dt;
		s->r.z += s->v.z * dt;
		//Limits
		if(s->r.x < lim->neg.x){ s->r.x = lim->neg.x; s->v.x = 0.0f; }
		if(s->r.x > lim->pos.x){ s->r.x = lim->pos.x; s->v.x = 0.0f; }
		if(s->r.y < lim->neg.y){ s->r.y = lim->neg.y; s->v.y = 0.0f; }
		if(s->r.y > lim->pos.y){ s->r.y = lim->pos.y; s->v.y = 0.0f; }
		if(s->r.z < lim->neg.z){ s->r.z = lim->neg.z; s->v.z = 0.0f; }
		if(s->r.z > lim->pos.z){ s->r.z = lim->pos.z; s->v.z = 0.0f; }
		//Result
		rot->x += s->r.x * unitRot;
		rot->y += s->r.y * unitRot;
		rot->z += s->r.z * unitRot * b->yawmult;
	}else if(mode == 1){
		//Double
		/*
		PhysDoubleState *s = &en->physDouble[iim];
		const PhysDouble *dbl = phys[b].dbl;
		Vec3f fulcrum;
		Vec3f boneposoffset;
		boneposoffset.x = pos->x;
		boneposoffset.y = pos->y + b->len;
		boneposoffset.z = pos->z;
		Matrix_MultVec3f(boneposoffset, fulcrum);
		*/
	}else{
		//Tunic
		//PhysTunicState *s = &en->physTunic[iim];
		
	}
	return false;
}

void BotWLink_PostLimbDraw(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3s* rot, void* thisx) {
	(void)0;
}

static void draw(Entity *en, GlobalContext *globalCtx) {
	func_80093D18(globalCtx->state.gfxCtx);
	SkelAnime_DrawFlexOpa(globalCtx, en->skelAnime.skeleton, en->skelAnime.jointTable,
		en->skelAnime.dListCount, BotWLink_OverrideLimbDraw, BotWLink_PostLimbDraw, en);
	func_80093D18(globalCtx->state.gfxCtx);
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
