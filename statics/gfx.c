#include "ootmain.h"
#include "gfx.h"

// Scene Draw Config 32
void Patched_CoSSceneDrawConfig(GlobalContext* globalCtx) {
    u32 gameplayFrames = globalCtx->gameplayFrames;

    //OPEN_DISPS(globalCtx->state.gfxCtx, "", 0);

    // Platform waterfall side animation
    gSPSegment(POLY_XLU_DISP++, 0x08, Gfx_TexScroll(globalCtx->state.gfxCtx, 0, (gameplayFrames * 2) % 256, 64, 64));

    gDPPipeSync(POLY_OPA_DISP++);
    gDPSetEnvColor(POLY_OPA_DISP++, 128, 128, 128, 128);

    // Platform water floor animation
    gSPSegment(POLY_OPA_DISP++, 0x0A,
               Gfx_TwoTexScroll(globalCtx->state.gfxCtx, 0, 127 - gameplayFrames % 128, (gameplayFrames * 1) % 128, 32,
                                32, 1, gameplayFrames % 128, (gameplayFrames * 1) % 128, 32, 32));

    // Chamber background animation
    gSPSegment(POLY_XLU_DISP++, 0x09,
               Gfx_TwoTexScroll(globalCtx->state.gfxCtx, 0, 127 - (gameplayFrames * 1) % 128,
                                (gameplayFrames * 1) % 256, 32, 64, 1, 0, 0, 32, 128));

    gDPPipeSync(POLY_OPA_DISP++);
    gDPSetEnvColor(POLY_OPA_DISP++, 128, 128, 128, 128);

    gDPPipeSync(POLY_XLU_DISP++);
    gDPSetEnvColor(POLY_XLU_DISP++, 128, 128, 128, 128);

    // Fade out light rays when the player gets close
    {
        // Displaylist containg the color sets for each light ray
        static Gfx rayDL[6 * 2];
        // Position of each light ray
        static const Vec3s rayPos[] = {
            { -419, 215, -725 }, // Saria
            { 419, 394, -725 },  // Darunia
            { 838, 569, 0 },     // Ruto
            { 419, 744, 725 },   // Nabooru
            { -419, 918, 725 },  // Impa
            { -840, 1092, 0 },   // Sheik
        };
        Player* player = PLAYER;
        s32 i; // used for indexing the loop
        s32 j; // used for indexing the displaylist

        #define RANGE_LOW  300  // distance in which the ray is fully faded
        #define RANGE_HIGH 800 // distance in which the ray begins to fade out
        #define ALPHA_FULL (255.0f * 0.6f) 

        for (i = 0, j = 0; i < 6; i++, j += 2) {
            // xz distance between the player and the current light ray
            f32 distance =
                sqrtf(SQ(player->actor.world.pos.x - rayPos[i].x) + SQ(player->actor.world.pos.z - rayPos[i].z));
            u8 alpha;

            if (distance <= RANGE_LOW) {
                // Light ray is fully faded out
                alpha = 0;
            } else if (distance > RANGE_LOW && distance < RANGE_HIGH) {
                // Get alpha value for partially faded out light ray
                alpha = ALPHA_FULL * ((distance - RANGE_LOW) / (f32)(RANGE_HIGH - RANGE_LOW));
            } else {
                // Light ray is fully faded in
                alpha = ALPHA_FULL;
            }

            // Write the displaylist now that we know the alpha that we want
            gDPSetPrimColor(&rayDL[j], 0, 0, 255, 255, 255, alpha);
            gSPEndDisplayList(&rayDL[j + 1]);
        }

        // Segment B for the light rays
        gSPSegment(POLY_OPA_DISP++, 0x0B, rayDL);
    }

    //CLOSE_DISPS(globalCtx->state.gfxCtx, "", 0);
}

u32 Patched_GetSpaceSize(GlobalContext* globalCtx){
    if (globalCtx->sceneNum == SCENE_GANON_DEMO
            && gSaveContext.sceneSetupIndex != 4) {
        return 1177600;
    } else if (globalCtx->sceneNum == SCENE_JYASINBOSS
            || globalCtx->sceneNum == SCENE_GANON_BOSS) {
        return 1075200;
    } else if (globalCtx->sceneNum == SCENE_KENJYANOMA
            || globalCtx->sceneNum == SCENE_KOKIRI_HOME5){
        //Chamber of Sages or testing CoS
        return 1250000;
    }
    return 1024000;
}

extern void Object_InitBank(GlobalContext* globalCtx, ObjectContext* objectCtx);
extern void Object_InitBank_AfterSpaceSize();

void Patched_ObjectInitBank(){
    asm(".set noat\n .set noreorder\n"
	//Starting at 800813D4 + 0x10
    //a0 = globalCtx, a1 = objectCtx
    "jal     Patched_GetSpaceSize\n"
    "sw      $a1, 0x0004($sp)\n"
    "lw      $a2, 0x0004($sp)\n"
    "or      $a3, $v0, $zero\n"
    "addiu   $a0, $zero, 0x0013\n"
    "j       Object_InitBank_AfterSpaceSize\n"
    "addiu   $v1, $zero, 0x0003\n"
    //Requirements after: a2 = objectCtx, v1 = 3, a0 = 0x13, a3 = spaceSize
    ".set at\n .set reorder");
}

typedef void (*SceneDrawConfig)(GlobalContext* globalCtx);

extern SceneDrawConfig sceneDrawConfigJumpTable[0x35];

void Statics_GfxCodePatches(){
    sceneDrawConfigJumpTable[0x20] = Patched_CoSSceneDrawConfig;
    bcopy((void*)Patched_ObjectInitBank, (void*)Object_InitBank + 4*4, 7*4);
}
