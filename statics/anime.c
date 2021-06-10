#include "z64structs.h"
#include "z64funcs.h"
#include "anime.h"

static void *MaybeSeg2RAM(void *ptr){
    if((u32)ptr & 0x80000000) return ptr;
    return (void*)zh_seg2ram((u32)ptr);
}

extern z64_animation_entry_t* AnimationContext_AddEntry(void *animCtx, s32 type);
extern void AnimationContext_SetLoadFrame(z64_global_t* globalCtx, 
    z64_animation_entry_link_t* animation, s32 frame, s32 limbCount, vec3s_t* frameTable);

extern u32 _link_animetionSegmentRomStart[1];

static void Patched_SetLoadFrame(z64_global_t* globalCtx, 
    z64_animation_entry_link_t* animation, s32 frame, s32 limbCount, vec3s_t* frameTable) 
{
    z64_animation_entry_link_t* linkAnimHeader = MaybeSeg2RAM(animation);
    u32 animStepSize = sizeof(vec3s_t) * limbCount + 2;
    z64_animation_entry_t* entry = AnimationContext_AddEntry((u8*)globalCtx + 0x10B20, 0);
    if (entry == NULL) return;
    
    //zh_draw_debug_text(globalCtx, 0xFF8000FF, 1, 1, "%2d %08X", frame, linkAnimHeader->anim);
    
    osCreateMesgQueue(&entry->types.type0.msgQueue, &entry->types.type0.msg, 1);
    
    if(linkAnimHeader->anim & 0x80000000){
        //Animation is in RAM
        bcopy((void*)(((s32)linkAnimHeader->anim | 0x80000000) + (animStepSize * frame)), 
            frameTable, animStepSize);
        osSendMesg(&entry->types.type0.msgQueue, (OSMesg)0, 0);
    }else{
        //Animation is in ROM
        DmaMgr_SendRequest2(&entry->types.type0.req, frameTable,
            (u32)&_link_animetionSegmentRomStart
            + (linkAnimHeader->anim & 0x00FFFFFF)
            + (animStepSize * frame),
            animStepSize, 0, &entry->types.type0.msgQueue, 0);
    }
}

extern s16 Animation_GetLength(void *animation);
extern s16 Animation_GetLastFrame(void *animation);
extern s16 Animation_GetLength2(void *animation);
extern s16 Animation_GetLastFrame2(void *animation);

static s16 Patched_GetLengthOrLastFrame(void *animation, s16 minus){
    z64_anim_header_init_t *anim = MaybeSeg2RAM(animation);
    return anim->frame_count - minus;
}

//Animation table
//z64_animation_entry_link_t linkAnimPatchTable[...] = {...};
#include "../anim/anim.c"

//Testing
z64_animation_entry_link_t testAnimHeader = { { 40, 0 }, 0x0701E340 };

typedef struct {
    //If positive, passes ptr to function in table D_80854AA4 (debug) indexed
    //by value. 
    //1: just stops Link. 
    //2: also sets Y to 0, changes to anim, play once at full speed, -6 morph
    //3: same as 2 but 2/3 speed and -8 morph
    //4: same as 3 but looping
    //5: once, 2/3 speed, -8 morph, sets moveFlags to 0x1C
    //6: once, full speed, flags 0x9C
    //
    //If negative (-1), calls func. If zero, does nothing.
    /* 0x00 */ s8 type; 
    /* 0x04 */ union {
        void* ptr;
        void (*func)(z64_global_t*, z64_player_t*, void*);
    };
} link_action_entry_t; // size = 0x08

#define NUM_ORIG_LINK_ACTIONS 0x67
#define NUM_CUSTOM_LINK_ACTIONS 0x12
extern link_action_entry_t linkActionInitTable[NUM_ORIG_LINK_ACTIONS];
link_action_entry_t linkActionInitPatchTable[NUM_ORIG_LINK_ACTIONS+NUM_CUSTOM_LINK_ACTIONS] = {
    //Original
    {0, NULL}, {0, NULL}, {0, NULL}, {0, NULL}, {0, NULL}, {0, NULL}, {0, NULL}, {0, NULL}, 
    {0, NULL}, {0, NULL}, {0, NULL}, {0, NULL}, {0, NULL}, {0, NULL}, {0, NULL}, {0, NULL}, 
    {0, NULL}, {0, NULL}, {0, NULL}, {0, NULL}, {0, NULL}, {0, NULL}, {0, NULL}, {0, NULL}, 
    {0, NULL}, {0, NULL}, {0, NULL}, {0, NULL}, {0, NULL}, {0, NULL}, {0, NULL}, {0, NULL}, 
    {0, NULL}, {0, NULL}, {0, NULL}, {0, NULL}, {0, NULL}, {0, NULL}, {0, NULL}, {0, NULL}, 
    {0, NULL}, {0, NULL}, {0, NULL}, {0, NULL}, {0, NULL}, {0, NULL}, {0, NULL}, {0, NULL}, 
    {0, NULL}, {0, NULL}, {0, NULL}, {0, NULL}, {0, NULL}, {0, NULL}, {0, NULL}, {0, NULL}, 
    {0, NULL}, {0, NULL}, {0, NULL}, {0, NULL}, {0, NULL}, {0, NULL}, {0, NULL}, {0, NULL}, 
    {0, NULL}, {0, NULL}, {0, NULL}, {0, NULL}, {0, NULL}, {0, NULL}, {0, NULL}, {0, NULL}, 
    {0, NULL}, {0, NULL}, {0, NULL}, {0, NULL}, {0, NULL}, {0, NULL}, {0, NULL}, {0, NULL}, 
    {0, NULL}, {0, NULL}, {0, NULL}, {0, NULL}, {0, NULL}, {0, NULL}, {0, NULL}, {0, NULL}, 
    {0, NULL}, {0, NULL}, {0, NULL}, {0, NULL}, {0, NULL}, {0, NULL}, {0, NULL}, {0, NULL}, 
    {0, NULL}, {0, NULL}, {0, NULL}, {0, NULL}, {0, NULL}, {0, NULL}, {0, NULL},
    //Patched
    {3, &linkAnimPatchTable[0]},
    {3, &linkAnimPatchTable[1]},
    {7, &testAnimHeader}, 
    {0, NULL}, {0, NULL}, {0, NULL}, {0, NULL}, {0, NULL}, {0, NULL}, {0, NULL}, {0, NULL}, 
    {0, NULL}, {0, NULL}, {0, NULL}, {0, NULL}, {0, NULL}, {0, NULL}, {0, NULL},
};
extern link_action_entry_t linkActionRunTable[NUM_ORIG_LINK_ACTIONS];
link_action_entry_t linkActionRunPatchTable[NUM_ORIG_LINK_ACTIONS+NUM_CUSTOM_LINK_ACTIONS] = {
    //Original
    {0, NULL}, {0, NULL}, {0, NULL}, {0, NULL}, {0, NULL}, {0, NULL}, {0, NULL}, {0, NULL}, 
    {0, NULL}, {0, NULL}, {0, NULL}, {0, NULL}, {0, NULL}, {0, NULL}, {0, NULL}, {0, NULL}, 
    {0, NULL}, {0, NULL}, {0, NULL}, {0, NULL}, {0, NULL}, {0, NULL}, {0, NULL}, {0, NULL}, 
    {0, NULL}, {0, NULL}, {0, NULL}, {0, NULL}, {0, NULL}, {0, NULL}, {0, NULL}, {0, NULL}, 
    {0, NULL}, {0, NULL}, {0, NULL}, {0, NULL}, {0, NULL}, {0, NULL}, {0, NULL}, {0, NULL}, 
    {0, NULL}, {0, NULL}, {0, NULL}, {0, NULL}, {0, NULL}, {0, NULL}, {0, NULL}, {0, NULL}, 
    {0, NULL}, {0, NULL}, {0, NULL}, {0, NULL}, {0, NULL}, {0, NULL}, {0, NULL}, {0, NULL}, 
    {0, NULL}, {0, NULL}, {0, NULL}, {0, NULL}, {0, NULL}, {0, NULL}, {0, NULL}, {0, NULL}, 
    {0, NULL}, {0, NULL}, {0, NULL}, {0, NULL}, {0, NULL}, {0, NULL}, {0, NULL}, {0, NULL}, 
    {0, NULL}, {0, NULL}, {0, NULL}, {0, NULL}, {0, NULL}, {0, NULL}, {0, NULL}, {0, NULL}, 
    {0, NULL}, {0, NULL}, {0, NULL}, {0, NULL}, {0, NULL}, {0, NULL}, {0, NULL}, {0, NULL}, 
    {0, NULL}, {0, NULL}, {0, NULL}, {0, NULL}, {0, NULL}, {0, NULL}, {0, NULL}, {0, NULL}, 
    {0, NULL}, {0, NULL}, {0, NULL}, {0, NULL}, {0, NULL}, {0, NULL}, {0, NULL},
    //Patched
    {11, NULL},
    {11, NULL},
    {11, NULL},
    {0, NULL}, {0, NULL}, {0, NULL}, {0, NULL}, {0, NULL}, {0, NULL}, {0, NULL}, {0, NULL}, 
    {0, NULL}, {0, NULL}, {0, NULL}, {0, NULL}, {0, NULL}, {0, NULL}, {0, NULL},
};

#define NUM_ORIG_CS_ACTIONS 0x4E
#define NUM_CUSTOM_CS_ACTIONS 0x12
extern s8 csActionToLinkActionTable[NUM_ORIG_CS_ACTIONS];
s8 csActionToLinkActionPatchTable[NUM_ORIG_CS_ACTIONS+NUM_CUSTOM_CS_ACTIONS] = {
    //Original
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    //Custom
    NUM_ORIG_LINK_ACTIONS,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,
};

extern void Player_RAM_START();
extern void Player_START();

static void *PlayerVRAMtoRAM(void *ptr){
    return ptr - (void*)Player_START + (void*)Player_RAM_START;
}

void Statics_Player_Init(){
    static u32 alreadyrun = 0;
    //Patch overwrote 
    //globalCtx->shootingGalleryStatus = globalCtx->bombchuBowlingStatus = 0;
    //so we have to do that
    ((u8*)&gGlobalContext)[0x11E5C] = 0;
    ((u8*)&gGlobalContext)[0x11E5D] = 0;
    if(alreadyrun) return;
    alreadyrun = 1;
    //Copy original, relocated, animation tables to patch tables in statics.
    bcopy(PlayerVRAMtoRAM(csActionToLinkActionTable), csActionToLinkActionPatchTable, 
        sizeof(s8) * NUM_ORIG_CS_ACTIONS);
    bcopy(PlayerVRAMtoRAM(linkActionInitTable), linkActionInitPatchTable,
        sizeof(link_action_entry_t) * NUM_ORIG_LINK_ACTIONS);
    bcopy(PlayerVRAMtoRAM(linkActionRunTable), linkActionRunPatchTable,
        sizeof(link_action_entry_t) * NUM_ORIG_LINK_ACTIONS);
}

extern u32 anim_START;
static DmaRequest animFileInfo = { 0xDEADBEEF, &anim_START, 0x04206969, 0, 0, 0, 0 };

void Statics_AnimeCodePatches(u8 isLiveRun){
    //Patch Link animation loader
    *( (u32*)AnimationContext_SetLoadFrame   ) = JUMPINSTR(Patched_SetLoadFrame);
	*(((u32*)AnimationContext_SetLoadFrame)+1) = 0;
    *( (u32*)Animation_GetLength       ) = JUMPINSTR(Patched_GetLengthOrLastFrame);
	*(((u32*)Animation_GetLength    )+1) = 0x34050000; //ori a1, zero, 0x0000
    *( (u32*)Animation_GetLastFrame    ) = JUMPINSTR(Patched_GetLengthOrLastFrame);
	*(((u32*)Animation_GetLastFrame )+1) = 0x34050001; //ori a1, zero, 0x0001
    // *( (u32*)Animation_GetLength2      ) = JUMPINSTR(Patched_GetLengthOrLastFrame);
	// *(((u32*)Animation_GetLength2   )+1) = 0x34050000; //ori a1, zero, 0x0000
    // *( (u32*)Animation_GetLastFrame2   ) = JUMPINSTR(Patched_GetLengthOrLastFrame);
	// *(((u32*)Animation_GetLastFrame2)+1) = 0x34050001; //ori a1, zero, 0x0001
    if(!isLiveRun){
        //Load animations from extra ROM file to RAM
        z_file_load(&animFileInfo);
    }
}

typedef s32 (*Player_SetUpCutscene_t)(z64_global_t *, z64_actor_t *, s32);
extern s32 Player_SetUpCutscene(z64_global_t *globalCtx, z64_actor_t *actor, s32 csMode);

void Statics_AnimeTest(s32 a){
    Player_SetUpCutscene_t fp = (Player_SetUpCutscene_t)PlayerVRAMtoRAM(&Player_SetUpCutscene);
    s32 action = 0;
    if(a < 0){
        action = 13;
    }else{
        action = a + NUM_ORIG_LINK_ACTIONS;
    }
    fp(&gGlobalContext, NULL, action);
}
