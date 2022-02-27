/*
 * File: z_demo_holy.c
 * Overlay: ovl_En_HolyLight
 * Description: Holy Light for BotW Zelda
 * Author: MNGoldenEagle
 */

#include "ootmain.h"
#include "z_demo_holy.h"
#include "holy_light_gfx.h"

#define OBJ_ID 126
#define FLAGS ((1 << 4) | (1 << 5) | (1 << 19) | (1 << 22) | (1 << 25) | (1 << 27))

#define  BRIGHT_RANGE ((280.0f - 150.0f) / 2.0f)
#define BRIGHT_OFFSET ((280.0f + 150.0f) / 2.0f)
#define     DIM_RANGE ((255.0f - 50.0f) / 2.0f)
#define    DIM_OFFSET ((255.0f + 50.0f) / 2.0f)
#define  OFFSET_RANGE ((255.0f - 90.0f) / 2.0f)
#define OFFSET_OFFSET ((255.0f + 90.0f) / 2.0f)
#define    FADE_RANGE (255.0f / 2.0f)

void HolyLight_Init(Actor* thisx, GlobalContext* globalCtx);
void HolyLight_Destroy(Actor* thisx, GlobalContext* globalCtx);
void HolyLight_Update(Actor* thisx, GlobalContext* globalCtx);
void HolyLight_Draw(Actor* thisx, GlobalContext* globalCtx);
void Update_WaitForCutscene(EnHolyLight* this, GlobalContext* globalCtx, f32 currentFrame);
void Update_FadeIn(EnHolyLight* this, GlobalContext* globalCtx, f32 currentFrame);
void Update_Glow(EnHolyLight* this, GlobalContext* globalCtx, f32 currentFrame);
void Update_FadeOut(EnHolyLight* this, GlobalContext* globalCtx, f32 currentFrame);
//void Update_Cycle(EnHolyLight* this, GlobalContext* globalCtx, f32 unused);
//void ChangeCycle(EnHolyLight* this, bool firstCycle);

//static Vec3f KiraVelocity = { 0.0f, 3.0f, 0.0f };
//static Vec3f KiraAccel = { 0.0f, -1.0f, 0.0f };
/*
static u16 CycleFramePoints[3][2] = {
    { 0, 80 },
    { 80, 200 },
    { 200, 280 }
};
*/

void HolyLight_Init(Actor* thisx, GlobalContext* globalCtx) {
    EnHolyLight* this = (EnHolyLight*)thisx;

    this->lightNode = LightContext_InsertLight(globalCtx, &globalCtx->lightCtx, &this->lightInfo);
    Lights_PointNoGlowSetInfo(&this->lightInfo, this->actor.home.pos.x, this->actor.home.pos.y + 125, this->actor.home.pos.z,
                            255, 255, 255, 50);
    //if (this->actor.params >= 0 && this->actor.params < ARRAY_COUNT(globalCtx->csCtx.npcActions)) {
        this->actorSlot = this->actor.params;
        this->update = &Update_WaitForCutscene;
        this->actor.draw = NULL;
        this->scaleFactor = 0.0f;
        /*
    } else {
        this->actorSlot = -1;
        this->update = &Update_Cycle;
        ChangeCycle(this, true);
    }
    */
}

void HolyLight_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    EnHolyLight* this = (EnHolyLight*)thisx;

    LightContext_RemoveLight(globalCtx, &globalCtx->lightCtx, this->lightNode);
}

void Update_WaitForCutscene(EnHolyLight* this, GlobalContext* globalCtx, f32 currentFrame) {
    if (globalCtx->csCtx.state != 0 && globalCtx->csCtx.npcActions[this->actorSlot] != NULL) {
        CsCmdActorAction* action = globalCtx->csCtx.npcActions[this->actorSlot];
        if (action->endFrame < globalCtx->csCtx.frames) {
            return;
        }
        this->startFrame = action->startFrame;
        this->endFrame = action->endFrame;
        this->periodFactor = 10.0f / ((action->endFrame - action->startFrame) * M_PI);
        this->actor.draw = &HolyLight_Draw;
        switch (action->action) {
            case HLYLGT_MD_FADEIN:
                this->update = &Update_FadeIn;
                Update_FadeIn(this, globalCtx, currentFrame);
                break;
            case HLYLGT_MD_GLOW:
                this->update = &Update_Glow;
                Update_Glow(this, globalCtx, currentFrame);
                break;
            case HLYLGT_MD_FADEOUT:
                this->update = &Update_FadeOut;
                Update_FadeOut(this, globalCtx, currentFrame);
                break;
            default:
                // Whoops!
                this->actor.draw = NULL;
                return;
        }
    }
}

// (((ymax - ymin) / 2) * sinf((10 / ((xmax - xmin) * M_PI)) * (x - xmin) - (M_PI / 2)) + ((ymax + ymin) / 2))
void SetLightGlow(EnHolyLight* this, f32 currentFrame) {
    f32 periodFactor = this->periodFactor;
    f32 calc;

    // Bright cycle (30 frames, 225 to 255 to 225)
    calc = BRIGHT_RANGE * sinf(2.0f * periodFactor * (currentFrame - (f32)this->startFrame) - (M_PI / 2.0f)) + BRIGHT_OFFSET;
    this->lightColor.r =
     this->lightColor.g =
     this->primColor.r =
     this->primColor.g = CLAMP_MAX(calc, 255);

    // Dim cycle (60 frames, 80 to 255 to 80)
    calc = DIM_RANGE * sinf(periodFactor * (currentFrame - (f32)this->startFrame) - (M_PI / 2.0f)) + DIM_OFFSET;
    this->lightColor.b =
     this->primColor.b = CLAMP_MAX(calc, 255);

    // Offset cycle (60 frames, 100 to 255 to 100)
    this->envColor.r = OFFSET_RANGE * sinf(periodFactor * (currentFrame - (f32)this->startFrame) - (M_PI / 2.0f)) + OFFSET_OFFSET;
    this->envColor.g = OFFSET_RANGE * sinf(periodFactor * (currentFrame - (f32)this->startFrame - 4) - (M_PI / 2.0f)) + OFFSET_OFFSET;
    this->envColor.b = OFFSET_RANGE * sinf(periodFactor * (currentFrame - (f32)this->startFrame - 7) - (M_PI / 2.0f)) + OFFSET_OFFSET;

    this->lightInfo.params.point.color[0] = this->primColor.r;
    this->lightInfo.params.point.color[1] = this->primColor.g;
    this->lightInfo.params.point.color[2] = this->primColor.b;
}

void Update_FadeIn(EnHolyLight* this, GlobalContext* globalCtx, f32 currentFrame) {
    f32 calc;

    SetLightGlow(this, currentFrame);
    calc = FADE_RANGE * sinf(this->periodFactor * (currentFrame - (f32)this->startFrame) - (M_PI / 2.0f)) + FADE_RANGE;
    this->lightColor.a = this->envColor.a = this->primColor.a = CLAMP_MAX(calc, 255.0f);
    this->scaleFactor = calc / 255.0f;
    this->lightInfo.params.point.radius = calc;
}

void Update_Glow(EnHolyLight* this, GlobalContext* globalCtx, f32 currentFrame) {
    SetLightGlow(this, currentFrame);
    this->lightColor.a = this->envColor.a = this->primColor.a = 255;
}

void Update_FadeOut(EnHolyLight* this, GlobalContext* globalCtx, f32 currentFrame) {
    f32 calc;

    SetLightGlow(this, currentFrame);
    calc = FADE_RANGE * sinf(this->periodFactor * (currentFrame - (f32)this->startFrame) + (M_PI / 2.0f)) + FADE_RANGE;
    this->lightColor.a = this->envColor.a = this->primColor.a = CLAMP_MAX(calc, 255.0f);
    this->scaleFactor = calc / 255.0f;
    this->lightInfo.params.point.radius = calc;
}

/*
void ChangeCycle(EnHolyLight* this, bool firstCycle) {
    HolyLightMode newMode = firstCycle ? HLYLGT_MD_FADEIN : (this->mode + 1) % HLYLGT_MD_MAX;
    this->mode = newMode;
    this->startFrame = CycleFramePoints[newMode][0];
    this->endFrame = CycleFramePoints[newMode][1];
    if (newMode == HLYLGT_MD_FADEIN) {
        this->currentFrame = 0;
    }
    this->periodFactor = 10.0f / ((this->endFrame - this->startFrame) * M_PI);
}

void Update_Cycle(EnHolyLight* this, GlobalContext* globalCtx, f32 unused) {
    if (this->currentFrame == this->endFrame) {
        ChangeCycle(this, false);
    }

    switch (this->mode) {
        case HLYLGT_MD_FADEIN:
            Update_FadeIn(this, globalCtx, this->currentFrame);
            break;
        case HLYLGT_MD_GLOW:
            Update_Glow(this, globalCtx, this->currentFrame);
            break;
        case HLYLGT_MD_FADEOUT:
            Update_FadeOut(this, globalCtx, this->currentFrame);
            break;
        default:
            // This shouldn't have happened!
            this->lightColor.a = this->envColor.a = this->primColor.a = 0;
            this->lightInfo.params.point.radius = 0;
    }

    this->currentFrame++;
}
*/

void HolyLight_Update(Actor* thisx, GlobalContext* globalCtx) {
    EnHolyLight* this = (EnHolyLight*)thisx;

    if (this->actorSlot < ARRAY_COUNT(globalCtx->csCtx.npcActions) && globalCtx->csCtx.frames > this->endFrame) {
        this->update = &Update_WaitForCutscene;
        this->actor.draw = NULL;
        this->startFrame = 0;
        this->endFrame = 0;
    }
    
    f32 currentFrame = globalCtx->csCtx.frames;
    this->update(this, globalCtx, currentFrame);
}

void HolyLight_Draw(Actor* thisx, GlobalContext* globalCtx) {
    EnHolyLight* this = (EnHolyLight*)thisx;
    s32 frame = globalCtx->gameplayFrames;

    //OPEN_DISPS(globalCtx->state.gfxCtx, "../z_demo_holy.c", __LINE__);
    gSPSegment(POLY_XLU_DISP++, 10, Gfx_TexScroll(globalCtx->state.gfxCtx, frame * 3, 0, 16, 32));
    gSPSegment(POLY_XLU_DISP++, 11, Gfx_TexScroll(globalCtx->state.gfxCtx, ABS(-frame), 0, 16, 32));
    gDPSetPrimColor(POLY_XLU_DISP++, 128, 128, this->primColor.r, this->primColor.g, this->primColor.b, this->primColor.a);
    gDPSetEnvColor(POLY_XLU_DISP++, this->envColor.r, this->envColor.g, this->envColor.b, 255);
    func_80093D84(globalCtx->state.gfxCtx);
    Matrix_Scale(this->scaleFactor, 2.0f, this->scaleFactor, MTXMODE_APPLY);
    gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx, "../z_demo_holy.c", __LINE__),
              G_MTX_MODELVIEW | G_MTX_LOAD | G_MTX_NOPUSH);
    gSPDisplayList(POLY_XLU_DISP++, &holyLight1);
    gDPSetPrimColor(POLY_XLU_DISP++, 128, 128, this->envColor.r, this->envColor.g, this->envColor.b, this->primColor.a);
    gSPDisplayList(POLY_XLU_DISP++, &holyLight2);
    //CLOSE_DISPS(globalCtx->state.gfxCtx, "../z_demo_holy.c", __LINE__);
}

const ActorInitExplPad init_vars = {
    .id = 0xDEAD, .padding = 0xBEEF,
    .category = ACTORCAT_PROP,
    .flags = FLAGS,
    .objectId = OBJ_ID,
    .instanceSize = sizeof(EnHolyLight),
    .init = (ActorFunc)HolyLight_Init,
    .destroy = (ActorFunc)HolyLight_Destroy,
    .update = (ActorFunc)HolyLight_Update,
    .draw = (ActorFunc)HolyLight_Draw,
};
