#include "ootmain.h"
#include "TestCelShadingMesh.h"
#include "TestCelShadingMoveAnim.h"

// Actor Information
#define OBJ_ID 121 // primary object dependency
#define NUM_LIMBS 4

typedef struct {
	Actor actor;
	SkelAnime skelAnime;
	Vec3s jointTable[NUM_LIMBS];
	Vec3s morphTable[NUM_LIMBS];
} Entity;

static void init(Entity *en, GlobalContext *globalCtx) {
	Actor_SetScale(&en->actor, 0.1f);
	SkelAnime_InitFlex(globalCtx, &en->skelAnime, &TestCelShadingMesh,
		&TestCelShadingMoveAnim, en->jointTable, en->morphTable, NUM_LIMBS);
	Rupees_ChangeBy(7);
}

static void destroy(Entity *en, GlobalContext *globalCtx) {
	SkelAnime_Free(&en->skelAnime, globalCtx);
}

static void update(Entity *en, GlobalContext *globalCtx) {
	SkelAnime_Update(&en->skelAnime);
}

s32 TCS_OverrideLimbDraw(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, void* thisx) {
	return false;
}

void TCS_PostLimbDraw(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3s* rot, void* thisx) {
	(void)0;
}

static void draw(Entity *en, GlobalContext *globalCtx) {
	func_80093D18(globalCtx->state.gfxCtx);
	SkelAnime_DrawFlexOpa(globalCtx, en->skelAnime.skeleton, en->skelAnime.jointTable,
		en->skelAnime.dListCount, TCS_OverrideLimbDraw, TCS_PostLimbDraw, en);
	//gSPClearGeometryMode(POLY_OPA_DISP++, G_CELSHADING); //no need if running setup DL below
	func_80093D18(globalCtx->state.gfxCtx);
}

const ActorInitExplPad init_vars = {
	.id = 0xDEAD, .padding = 0xBEEF, // <-- magic values, do not change
	.category = ACTORCAT_PROP,
	.flags = 0x00000030,
	.objectId = OBJ_ID,
	.instanceSize = sizeof(Entity),
	.init = (ActorFunc)init,
	.destroy = (ActorFunc)destroy,
	.update = (ActorFunc)update,
	.draw = (ActorFunc)draw
};
