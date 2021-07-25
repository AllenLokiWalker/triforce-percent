#ifndef _Z_EN_GE1_H_
#define _Z_EN_GE1_H_

#include "ootmain.h"

struct EnGe1;

/* animations */
extern AnimationHeader gGerudoWhiteIdleAnim;
extern AnimationHeader gGerudoWhiteClapAnim;
extern AnimationHeader gGerudoWhiteDismissiveAnim;
asm("gGerudoWhiteIdleAnim       = 0x06000228");
asm("gGerudoWhiteClapAnim       = 0x0600a048");
asm("gGerudoWhiteDismissiveAnim = 0x0600a498");

/* skeleton */
extern FlexSkeletonHeader gGerudoWhiteSkel;
asm("gGerudoWhiteSkel = 0x06000330");

/* animated eye textures */
#define gGerudoWhiteEyeOpenTex    0x06000708
#define gGerudoWhiteEyeHalfTex    0x06000f08
#define gGerudoWhiteEyeClosedTex  0x06001708
/*extern u64 *gGerudoWhiteEyeOpenTex;
extern u64 *gGerudoWhiteEyeHalfTex;
extern u64 *gGerudoWhiteEyeClosedTex;
asm("gGerudoWhiteEyeOpenTex   = 0x06000708");
asm("gGerudoWhiteEyeHalfTex   = 0x06000f08");
asm("gGerudoWhiteEyeClosedTex = 0x06001708");*/

/* hairstyles */
#define gGerudoWhiteHairstyleStraightFringeDL  0x06009430
#define gGerudoWhiteHairstyleSpikyDL           0x06009690
#define gGerudoWhiteHairstyleBobDL             0x06009198
/*extern Gfx *gGerudoWhiteHairstyleStraightFringeDL;
extern Gfx *gGerudoWhiteHairstyleSpikyDL;
extern Gfx *gGerudoWhiteHairstyleBobDL;
asm("gGerudoWhiteHairstyleStraightFringeDL = 0x06009430");
asm("gGerudoWhiteHairstyleSpikyDL          = 0x06009690");
asm("gGerudoWhiteHairstyleBobDL            = 0x06009198");*/

typedef void (*EnGe1AnimFunc)(struct EnGe1*);
typedef void (*EnGe1ActionFunc)(struct EnGe1*, GlobalContext*);

typedef enum {
    /* 0x00 */ GE1_TYPE_GATE_GUARD,
    /* 0x01 */ GE1_TYPE_GATE_OPERATOR,
    /* 0x04 */ GE1_TYPE_NORMAL = 4,
    /* 0x05 */ GE1_TYPE_VALLEY_FLOOR,
    /* 0x45 */ GE1_TYPE_HORSEBACK_ARCHERY = 0x45,
    /* 0x46 */ GE1_TYPE_TRAINING_GROUNDS_GUARD
} EnGe1Type;

typedef enum {
    /* 00 */ GE1_LIMB_NONE,
    /* 01 */ GE1_LIMB_WAIST,
    /* 02 */ GE1_LIMB_L_THIGH,
    /* 03 */ GE1_LIMB_L_LOWER_LEG,
    /* 04 */ GE1_LIMB_L_FOOT,
    /* 05 */ GE1_LIMB_R_THIGH,
    /* 06 */ GE1_LIMB_R_LOWER_LEG,
    /* 07 */ GE1_LIMB_R_FOOT,
    /* 08 */ GE1_LIMB_TORSO,
    /* 09 */ GE1_LIMB_L_UPPER_ARM,
    /* 10 */ GE1_LIMB_L_FOREARM,
    /* 11 */ GE1_LIMB_L_HAND,
    /* 12 */ GE1_LIMB_R_UPPER_ARM,
    /* 13 */ GE1_LIMB_R_FOREARM,
    /* 14 */ GE1_LIMB_R_HAND,
    /* 15 */ GE1_LIMB_HEAD,
    /* 16 */ GE1_LIMB_MAX
} EnGe1Limb;

typedef struct EnGe1 {
    /* 0x0000 */ Actor actor;
    /* 0x014C */ ColliderCylinder collider;
    /* 0x0198 */ SkelAnime skelAnime;
    /* 0x01DC */ Vec3s jointTable[GE1_LIMB_MAX];
    /* 0x023C */ Vec3s morphTable[GE1_LIMB_MAX];
    /* 0x029C */ Vec3s headRot;
    /* 0x02A2 */ Vec3s unk_2A2;
    /* 0x02A8 */ s16 eyeIndex;
    /* 0x02AA */ s16 blinkTimer;
    /* 0x02AC */ u16 stateFlags;
    /* 0x02AE */ u8 hairstyle;
    /* 0x02AF */ u8 cutsceneTimer;
    /* 0x02B0 */ AnimationHeader* animation;
    /* 0x02B4 */ EnGe1ActionFunc actionFunc;
    /* 0x02B8 */ EnGe1AnimFunc animFunc;
    Actor *fence;
    u32 fenceDrop;
    float fencePrevY[2];
    u8 fenceLowered;
} EnGe1; // size = 0x02BC

#endif

