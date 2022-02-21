#ifndef Z_DEMO_HOLY_H
#define Z_DEMO_HOLY_H

#include "ultra64.h"
#include "z64.h"
#include "macros.h"

struct EnHolyLight;

typedef void (*UpdateFunc)(struct EnHolyLight*, GlobalContext*, f32);

typedef enum HolyLightMode {
    HLYLGT_MD_FADEIN,
    HLYLGT_MD_GLOW,
    HLYLGT_MD_FADEOUT,
    HLYLGT_MD_MAX
} HolyLightMode;

typedef struct EnHolyLight {
    Actor actor;
    LightNode* lightNode;
    UpdateFunc update;
    f32 scaleFactor;
    f32 periodFactor;
    Color_RGBA8 primColor;
    Color_RGBA8 envColor;
    Color_RGBA8 lightColor;
    LightInfo lightInfo;
    s16 startFrame;
    s16 endFrame;
    s16 currentFrame; // This is only used during cycle mode.  Otherwise the current frame inside csCtx will be used.
    HolyLightMode mode;
    u8 actorSlot;
} EnHolyLight; // size = 0x03A8

#endif
