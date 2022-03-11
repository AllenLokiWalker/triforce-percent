#ifndef Z_DEMO_HOLY_H
#define Z_DEMO_HOLY_H

struct EnHolyLight;

typedef void (*UpdateFunc)(struct EnHolyLight*, GlobalContext*, f32);

typedef enum HolyLightMode {
    HLYLGT_MD_FADEIN,
    HLYLGT_MD_GLOW,
    HLYLGT_MD_GLOW_SILENT,
    HLYLGT_MD_FADEOUT,
    HLYLGT_MD_MAX
} HolyLightMode;

typedef struct EnHolyLight {
    Actor actor;
    UpdateFunc update;
    Vec3f spawnPos;
    f32 scaleFactor;
    f32 periodFactor;
    Color_RGBA8 primColor;
    Color_RGBA8 envColor;
    Vec3i startPos;
    Vec3i endPos;
    s16 startFrame;
    s16 endFrame;
    s16 currentFrame; // This is only used during cycle mode.  Otherwise the current frame inside csCtx will be used.
    HolyLightMode mode;
    u8 actorSlot;
    u8 sound;
} EnHolyLight; // size = 0x03A8

#endif
