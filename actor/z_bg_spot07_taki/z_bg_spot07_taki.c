/*
 * File: z_bg_spot07_taki.c
 * Overlay: ovl_Bg_Spot07_Taki
 * Description: Zora's Domain Waterfall and Ice
 * Triforce% ice melting magic courtesy of z64me <z64.me>
 * TODO @zel don't forget about that fancy camera angle magic and improved steam particles 8)
 */

#include "ootmain.h"
#include "z_bg_spot07_taki.h"
#include "particles.h"

/* original functions */
static void BgSpot07Taki_Init(Actor* thisx, GlobalContext* globalCtx);
static void BgSpot07Taki_Destroy(Actor* thisx, GlobalContext* globalCtx);
static void BgSpot07Taki_Update(Actor* thisx, GlobalContext* globalCtx);
static void BgSpot07Taki_Draw(Actor* thisx, GlobalContext* globalCtx);

/* Triforce% functions */
static float GetThawRatio(BgSpot07Taki* this);
static u8 GetWaterFadeAlpha(BgSpot07Taki* this);
static u8 GetIceFadeAlpha(BgSpot07Taki* this);
static u8 GetFrozenWaterfallFadeAlpha(BgSpot07Taki* this);
static u8 Triforce_DisablePrimColor(void *dlist);
static void Triforce_ToggleCaustics(BgSpot07Taki* this, enum caustics mode);
static void Triforce_SpawnSoundActor(BgSpot07Taki* this, GlobalContext* globalCtx);

/* for hackishly patching the object file */
static void FastPrim(Gfx *p, u8 r, u8 g, u8 b, u8 a);
static void FastXluMode(Gfx *p);
static void FastXluModeTextureAlpha(Gfx *p, int stride);

const ActorInit init_vars = {
	.id = 0xDEAD, .padding = 0xBEEF, // <-- magic values, do not change
	.category = ACTORCAT_BG,
	.flags = FLAGS,
	.objectId = OBJECT_SPOT07_OBJECT,
	.instanceSize = sizeof(BgSpot07Taki),
	.init = (ActorFunc)BgSpot07Taki_Init,
	.destroy = (ActorFunc)BgSpot07Taki_Destroy,
	.update = (ActorFunc)BgSpot07Taki_Update,
	.draw = (ActorFunc)BgSpot07Taki_Draw
};

/* this is shared by all instances */
static struct
{
	u8 nonzero; /* XXX must be first */
	u8 caustics;
	u8 thawed;
	u32 thawing;
	struct
	{
		u8 water;
		u8 ice;
		u8 frozenWaterfall;
	} maxOpacity;
} g = {-1};


static void Triforce_WaterfallFadeIn(BgSpot07Taki* this)
{
	/* alpha value of each waterfall vertex, used for fade-in */
	static const u8 vertexAlpha[] = {
		127, 127, 127, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
		255, 255, 255, 250, 250, 250, 250, 250, 250, 255, 0, 255, 0, 0, 0, 0, 255,
		0, 0, 0, 0, 255, 0, 0, 255, 255, 0, 0, 255, 0, 0, 0, 0, 255, 202, 164, 127,
		164, 202, 202, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 0, 0
	};
	u8 *v = SEGMENTED_TO_VIRTUAL(0x06000000);
	int i;
	float f = GetThawRatio(this);
	
	for (i = 0; i < sizeof(vertexAlpha); ++i, v += 16)
	{
		v[15] = vertexAlpha[i] * f;
	}
}

static InitChainEntry sInitChain[] = {
	ICHAIN_VEC3F_DIV1000(scale, 100, ICHAIN_STOP),
};

static void Triforce_SpawnSoundActor(BgSpot07Taki* this, GlobalContext* globalCtx)
{
	Actor *wow;
	Vec3f pos;
	u16 var;
	if (IS_MAIN_ROOM)
		var = 0x0003, pos = (Vec3f){-189, 17, -941};
	else
		var = 0x0000, pos = (Vec3f){652, 857, -1691};
	
	/* don't spawn if already exists */
	this->dyna.actor.world.pos = pos;
	wow = Actor_FindNearby(globalCtx, &this->dyna.actor, ACTOR_EN_RIVER_SOUND, ACTORCAT_BG, 10);
	this->dyna.actor.world.pos = this->dyna.actor.home.pos;
	if (wow)
		return;
	
	Actor_Spawn(
		&globalCtx->actorCtx
		, globalCtx
		, ACTOR_EN_RIVER_SOUND
		, pos.x, pos.y, pos.z
		, 0, 0, 0
		, var
	);
}

static void BgSpot07Taki_Init(Actor* thisx, GlobalContext* globalCtx) {
	BgSpot07Taki* this = THIS;
	CollisionHeader* colHeader = NULL;
	
	//TODO
	globalCtx->actorCtx.flags.chest &= ~(1 << FLAG_THAWED);

	DynaPolyActor_Init(&this->dyna, DPM_PLAYER);
	Actor_ProcessInitChain(&this->dyna.actor, sInitChain);
	this->gl = globalCtx;
	if (!g.thawed)
	{
		g.maxOpacity.water = Triforce_DisablePrimColor(DLIST_WATER_MAIN);
		Triforce_DisablePrimColor(DLIST_WATER_CHAMBER);
		g.maxOpacity.ice = Triforce_DisablePrimColor(DLIST_ICE_MAIN);
		Triforce_DisablePrimColor(DLIST_ICE_CHAMBER);
		g.maxOpacity.frozenWaterfall = Triforce_DisablePrimColor(DLIST_ICE_WATERFALL);
		Triforce_DisablePrimColor(DLIST_ICE_WATERFALL_EDGE);
	}
	if (LINK_IS_ADULT)
	{
		if (FLAG_THAWED_GET)
		{
			g.thawing = true;
			g.thawed = true;
			Triforce_SpawnSoundActor(this, globalCtx);
		}
		else
		{
			/* disable caustics in case someone revisits Zora's Domain
			 * on a save where Zora's Domain hasn't been thawed yet,
			 * or dies without saving
			 */
			Triforce_ToggleCaustics(this, CAUSTICS_DISABLE);
			this->hasDynaPoly = true;
			if (IS_MAIN_ROOM) {
				CollisionHeader_GetVirtual(COLL_MAIN, &colHeader);
			} else {
				CollisionHeader_GetVirtual(COLL_CHAMBER, &colHeader);
			}
			this->dyna.bgId = DynaPoly_SetBgActor(globalCtx, &globalCtx->colCtx.dyna,
				&this->dyna.actor, colHeader);
		}
	}
	else
	{
		g.thawing = true;
		g.thawed = true;
	}
}

static void BgSpot07Taki_Destroy(Actor* thisx, GlobalContext* globalCtx) {
	BgSpot07Taki* this = THIS;
	
	if (this->hasDynaPoly)
		DynaPoly_DeleteBgActor(globalCtx, &globalCtx->colCtx.dyna, this->dyna.bgId);
}

static void Triforce_TestShouldThaw(BgSpot07Taki* this, GlobalContext* globalCtx)
{
	if (!g.thawing)
	{
		static int wait = -1;
		if (wait < 0) wait = 0;
		/* activation logic */
		if (!wait
			&& func_80043590(&this->dyna) /* Link is standing on ice */
			&& Actor_Find(&globalCtx->actorCtx, ACTOR_MAGIC_FIRE, ACTORCAT_ITEMACTION) 
			/* used Din's Fire */
		)
		{
			wait = 30;
		}
		
		if (wait && !(--wait))
		{
			g.thawing = globalCtx->gameplayFrames;
			Audio_PlayActorSound2(&PLAYER->actor, NA_SE_EV_ICE_MELT);
		}
		return;
	}
	if (FLAG_THAWED_GET)
		Triforce_ToggleCaustics(this, CAUSTICS_ENABLE);
	if (g.thawed)
		return;
	
	if (g.thawing)
	{
		static int ok = -1;
		static float wow = -1;
		
		if (ok < 0)
		{
			ok = 1;
			wow = 1;
		}
		
		if (ok < 0)
			return;
		
		if (!(ok & 3))
		{
			Vec3f pos = PLAYER->actor.world.pos;
			sDustPrimColor.g = sDustPrimColor.b = (1.0 - wow) * (250 / 2);
			sDustPrimColor.g += 127;
			sDustPrimColor.b *= 2;
			sDustEnvColor.g = sDustPrimColor.g / 2;
			sDustEnvColor.b = sDustPrimColor.b / 2;
			func_80890B8C(&pos, globalCtx, wow * 0.5f, 2.0);
			wow -= 0.1f;
			if (wow <= 0)
				ok = -1;
		}
		++ok;
	}
	
	if ((globalCtx->gameplayFrames - g.thawing) == THAW_TIME / 2)
	{
		Triforce_SpawnSoundActor(this, globalCtx);
		FLAG_THAWED_SET;
	}
	if ((globalCtx->gameplayFrames - g.thawing) >= THAW_TIME)
	{
		g.thawed = true;
		if (this->hasDynaPoly)
		{
			DynaPoly_DeleteBgActor(globalCtx, &globalCtx->colCtx.dyna, this->dyna.bgId);
			this->hasDynaPoly = false;
		}
	}
}

static void BgSpot07Taki_Update(Actor* thisx, GlobalContext* globalCtx) {
	BgSpot07Taki* this = THIS;
	
	Triforce_TestShouldThaw(this, globalCtx);
}

static void FastPrim(Gfx *p, u8 r, u8 g, u8 b, u8 a)
{
	gDPSetPrimColor(p++, 0, 0, r, g, b, a);
}

static void FastXluMode(Gfx *p)
{
	gDPSetCombineLERP(p++, TEXEL0, 0, SHADE, 0, 0, 0, 0, 1, 
		COMBINED, 0, PRIMITIVE, 0, COMBINED, 0, PRIMITIVE, 0);
	gDPSetRenderMode(p++, AA_EN | Z_CMP | Z_UPD | IM_RD | CLR_ON_CVG | CVG_DST_WRAP | ZMODE_XLU | FORCE_BL 
		| GBL_c1(G_BL_CLR_FOG, G_BL_A_SHADE, G_BL_CLR_IN, G_BL_1MA), G_RM_AA_ZB_XLU_SURF2);
}

static void FastXluModeTextureAlpha(Gfx *p, int stride)
{
	u32 pOld = (u32)p;
	gDPSetCombineLERP(p++, TEXEL0, 0, SHADE, 0, TEXEL0, 0, PRIMITIVE, 0, 
		COMBINED, 0, PRIMITIVE, 0, 0, 0, 0, COMBINED);
	if (stride)
	{
		p = (void*)(pOld + stride * 8);
	}
	gDPSetRenderMode(p++, AA_EN | Z_CMP | Z_UPD | IM_RD | CLR_ON_CVG | CVG_DST_WRAP | ZMODE_XLU | FORCE_BL 
		| GBL_c1(G_BL_CLR_FOG, G_BL_A_SHADE, G_BL_CLR_IN, G_BL_1MA), G_RM_AA_ZB_XLU_SURF2);
}

static void BgSpot07Taki_Draw(Actor* thisx, GlobalContext* globalCtx) {
	BgSpot07Taki* this = THIS;
	u32 frames;
	
	//OPEN_DISPS(globalCtx->state.gfxCtx, "../z_bg_spot07_taki.c", 169);
	frames = globalCtx->gameplayFrames;

	gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx, "../z_bg_spot07_taki.c", 191),
		G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
	
    func_80093D84(globalCtx->state.gfxCtx);
	
	gSPSegment(
		POLY_XLU_DISP++
		, 0x08
		, Gfx_TwoTexScroll(
			globalCtx->state.gfxCtx
			, 0, ((frames * -1) & 0x7F), ((frames * 1) & 0x7F), 32, 32
			, 1, ((frames * 1) & 0x7F), ((frames * 1) & 0x7F), 32, 32
		)
	);

	if (LINK_IS_CHILD || g.thawing) {
		gDPSetEnvColor(POLY_XLU_DISP++, 255, 255, 255, 128);
		gDPSetPrimColor(POLY_XLU_DISP++, 0, 0, 255, 255, 255, GetWaterFadeAlpha(this));
		if (IS_MAIN_ROOM) {
			gSPSegment(
				POLY_XLU_DISP++
				, 0x09
				, Gfx_TwoTexScroll(
					globalCtx->state.gfxCtx
					, 0, ((frames * -1) & 0x7F), ((frames * -3) & 0xFF), 64, 64
					, 1, ((frames * 1) & 0x7F), ((frames * -3) & 0xFF), 64, 64
				)
			);
			gSPSegment(
				POLY_XLU_DISP++
				, 0x0A
				, Gfx_TwoTexScroll(
					globalCtx->state.gfxCtx
					, 0, frames * 0, ((frames * 3) & 0x1FF), 32, 128
					, 1, frames * 0, ((frames * 3) & 0x1FF), 32, 128
				)
			);
			Triforce_WaterfallFadeIn(this);
			gSPDisplayList(POLY_XLU_DISP++, DLIST_WATER_MAIN);
		} else {
			gSPSegment(
				POLY_XLU_DISP++
				, 0x09
				, Gfx_TwoTexScroll(
					globalCtx->state.gfxCtx
					, 0, frames * 0, ((frames * -1) & 0x7F), 32, 32
					, 1, frames * 0, ((frames * -1) & 0x7F), 32, 32
				)
			);
			gSPSegment(
				POLY_XLU_DISP++
				, 0x0A
				, Gfx_TwoTexScroll(
					globalCtx->state.gfxCtx
					, 0, frames * 0, ((frames * 3) & 0x1FF), 32, 128
					, 1, frames * 0, ((frames * 3) & 0x1FF), 32, 128
				)
			);
			gSPDisplayList(POLY_XLU_DISP++, DLIST_WATER_CHAMBER);
		}
	}
	if (LINK_IS_ADULT && !g.thawed) {
		u8 wa = GetFrozenWaterfallFadeAlpha(this);
		
    	func_80093D84(globalCtx->state.gfxCtx);
		gDPSetAlphaCompare(POLY_XLU_DISP++, G_AC_THRESHOLD);
		
		gDPSetPrimColor(POLY_XLU_DISP++, 0, 0, 255, 255, 255, GetIceFadeAlpha(this));
		if (IS_MAIN_ROOM) {
			FastPrim(PRIM_ICE_MAIN_RING, -1, -1, -1, wa);
			FastXluModeTextureAlpha(SETCOMBINE_ICE_MAIN_RING, 0);
			gSPDisplayList(POLY_XLU_DISP++, DLIST_ICE_MAIN);
		} else {
			FastPrim(PRIM_ICE_CHAMBER_EDGE, -1, -1, -1, wa);
			FastXluModeTextureAlpha(SETCOMBINE_ICE_CHAMBER_EDGE, 5);
			gSPDisplayList(POLY_XLU_DISP++, DLIST_ICE_CHAMBER);
		}
		
		gDPSetPrimColor(POLY_XLU_DISP++, 0, 0, 255, 255, 255, wa);
		if (IS_MAIN_ROOM) {
			FastXluMode(SETCOMBINE_ICE_WATERFALL);
			gSPDisplayList(POLY_XLU_DISP++, DLIST_ICE_WATERFALL);
		} else {
			FastXluMode(SETCOMBINE_ICE_WATERFALL_EDGE);
			gSPDisplayList(POLY_XLU_DISP++, DLIST_ICE_WATERFALL_EDGE);
		}
	}
	//CLOSE_DISPS(globalCtx->state.gfxCtx, "../z_bg_spot07_taki.c", 272);
}

static float GetThawRatio(BgSpot07Taki* this)
{
	float v;
	if (g.thawed)
		return 1;
	if (!g.thawing)
		return 0;
	v = this->gl->gameplayFrames - g.thawing;
	v /= THAW_TIME;
	if (v < 0)
		v = 0;
	if (v > 1)
		v = 1;
	return v;
}

static u8 GetWaterFadeAlpha(BgSpot07Taki* this)
{
	return GetThawRatio(this) * g.maxOpacity.water;
}

static u8 GetIceFadeAlpha(BgSpot07Taki* this)
{
	return (1.0 - GetThawRatio(this)) * g.maxOpacity.ice;
}

static u8 GetFrozenWaterfallFadeAlpha(BgSpot07Taki* this)
{
	return (1.0 - GetThawRatio(this)) * g.maxOpacity.frozenWaterfall;
}

/* disable primcolor in a display list so we can control it through code */
static u8 Triforce_DisablePrimColor(void *dlist)
{
	u8 *i;
	u8 rval = 0;
	for (i = dlist; *i != 0xdf; i += 8)
	{
		if (*i == 0xfa)
		{
			if (!rval) /* want only first primcolor alpha */
				rval = i[7];
			*(u32*)(i) = 0;
			*(u32*)(i+4) = 0;
			//Lib_MemSet(i, 8, 0);
		}
	}
	return rval;
}

/* this enables/disables the Zora's Domain water caustic effect */
static void Triforce_ToggleCaustics(BgSpot07Taki* this, enum caustics mode)
{
	u32 *v = 0;
	u32 original = 0; /* original opcode */
	static u8 caustics = CAUSTICS_DISABLE;
	if (LINK_IS_CHILD)
		return;
#ifdef _Z64HDR_OOT_DEBUG_H_
	/* func_8009E730:
	 * var = 127 - (gameplayFrames * 1) % 128;
	 * if (LINK_IS_ADULT) var = 0;
	 */
	v = (void*)(0x8009E730 + 0x54);
	original = 0x00001825; /* or v1, r0, r0 */
#elif defined(_Z64HDR_OOT_10_H_)
	/* OoT NTSC 1.0 */
	v = (void*)(0x800871B8 + 0x38);
	original = 0x00004825; /* or t1, r0, r0 */
#else
	#warning Triforce_ToggleCaustics unsupported game version
	return;
#endif
	if (!v || !original)
		return;
	if (mode == CAUSTICS_ENABLE)
	{
		/* caustics already enabled */
		if (caustics == CAUSTICS_ENABLE)
			return;
		*v = 0;
		
		/* resync with scene caustic effect */
		if (g.thawing && !g.thawed)
		{
			u32 diff = (this->gl->gameplayFrames * 1) % 128;
			g.thawing -= diff;
			this->gl->gameplayFrames -= diff;
		}
	}
	else if (mode == CAUSTICS_DISABLE)
	{
		/* restore original opcode */
		*v = original;
	}
	
	/* clear instruction cache */
	osWritebackDCache(v, 4);
	osInvalICache(v, 4);
	caustics = mode;
}
