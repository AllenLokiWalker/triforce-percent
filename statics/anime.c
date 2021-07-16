#include "ootmain.h"
#include "anime.h"
#include "statics.h"

static void *MaybeSeg2RAM(void *ptr){
    if((u32)ptr & 0x80000000) return ptr;
    return SEGMENTED_TO_VIRTUAL(ptr);
}

extern AnimationEntry* AnimationContext_AddEntry(AnimationContext *animCtx, s32 type);

static void Patched_SetLoadFrame(GlobalContext* globalCtx, 
    LinkAnimationHeader* animation, s32 frame, s32 limbCount, Vec3s* frameTable) 
{
    LinkAnimationHeader* linkAnimHeader = MaybeSeg2RAM(animation);
    u32 animStepSize = sizeof(Vec3s) * limbCount + 2;
    AnimationEntry* entry = AnimationContext_AddEntry(&globalCtx->animationCtx, 0);
    if (entry == NULL) return;
    
    //zh_draw_debug_text(globalCtx, 0xFF8000FF, 1, 1, "%2d %08X", frame, linkAnimHeader->anim);
    
    osCreateMesgQueue(&entry->data.load.msgQueue, &entry->data.load.msg, 1);
    
    if(linkAnimHeader->segment & 0x80000000){
        //Animation is in RAM
        bcopy((void*)(((s32)linkAnimHeader->segment | 0x80000000) + (animStepSize * frame)), 
            frameTable, animStepSize);
        osSendMesg(&entry->data.load.msgQueue, (OSMesg)0, 0);
    }else{
        //Animation is in ROM
        DmaMgr_SendRequest2((DmaRequest*)&entry->data.load.req, (u32)frameTable,
            (u32)&_link_animetionSegmentRomStart
            + (linkAnimHeader->segment & 0x00FFFFFF)
            + (animStepSize * frame),
            animStepSize, 0, &entry->data.load.msgQueue, 0);
    }
}

/*
extern s16 Animation_GetLength2(AnimationHeaderCommon *animation);
extern s16 Animation_GetLastFrame2(AnimationHeaderCommon *animation);
*/

static s16 Patched_GetLengthOrLastFrame(AnimationHeaderCommon *animation, s16 minus){
    AnimationHeaderCommon *anim = MaybeSeg2RAM(animation);
    return anim->frameCount - minus;
}

//Animation table
//LinkAnimationHeader linkAnimPatchTable[...] = {...};
#include "../anim/anim.c"

//Testing
LinkAnimationHeader testAnimHeader = { { 40 }, 0x0701E340 };

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
        void (*func)(GlobalContext*, Player*, void*);
    };
} LinkActionEntry; // size = 0x08

#define NUM_ORIG_LINK_ACTIONS 0x67
#define NUM_CUSTOM_LINK_ACTIONS 0x12
extern LinkActionEntry linkActionInitTable[NUM_ORIG_LINK_ACTIONS];
LinkActionEntry linkActionInitPatchTable[NUM_ORIG_LINK_ACTIONS+NUM_CUSTOM_LINK_ACTIONS] = {
    //Original
    {0,{NULL}},{0,{NULL}},{0,{NULL}},{0,{NULL}},{0,{NULL}},{0,{NULL}},{0,{NULL}},{0,{NULL}},
    {0,{NULL}},{0,{NULL}},{0,{NULL}},{0,{NULL}},{0,{NULL}},{0,{NULL}},{0,{NULL}},{0,{NULL}},
    {0,{NULL}},{0,{NULL}},{0,{NULL}},{0,{NULL}},{0,{NULL}},{0,{NULL}},{0,{NULL}},{0,{NULL}},
    {0,{NULL}},{0,{NULL}},{0,{NULL}},{0,{NULL}},{0,{NULL}},{0,{NULL}},{0,{NULL}},{0,{NULL}},
    {0,{NULL}},{0,{NULL}},{0,{NULL}},{0,{NULL}},{0,{NULL}},{0,{NULL}},{0,{NULL}},{0,{NULL}},
    {0,{NULL}},{0,{NULL}},{0,{NULL}},{0,{NULL}},{0,{NULL}},{0,{NULL}},{0,{NULL}},{0,{NULL}},
    {0,{NULL}},{0,{NULL}},{0,{NULL}},{0,{NULL}},{0,{NULL}},{0,{NULL}},{0,{NULL}},{0,{NULL}},
    {0,{NULL}},{0,{NULL}},{0,{NULL}},{0,{NULL}},{0,{NULL}},{0,{NULL}},{0,{NULL}},{0,{NULL}},
    {0,{NULL}},{0,{NULL}},{0,{NULL}},{0,{NULL}},{0,{NULL}},{0,{NULL}},{0,{NULL}},{0,{NULL}},
    {0,{NULL}},{0,{NULL}},{0,{NULL}},{0,{NULL}},{0,{NULL}},{0,{NULL}},{0,{NULL}},{0,{NULL}},
    {0,{NULL}},{0,{NULL}},{0,{NULL}},{0,{NULL}},{0,{NULL}},{0,{NULL}},{0,{NULL}},{0,{NULL}},
    {0,{NULL}},{0,{NULL}},{0,{NULL}},{0,{NULL}},{0,{NULL}},{0,{NULL}},{0,{NULL}},{0,{NULL}},
    {0,{NULL}},{0,{NULL}},{0,{NULL}},{0,{NULL}},{0,{NULL}},{0,{NULL}},{0,{NULL}},
    //Patched
    {3, {&linkAnimPatchTable[0]}},
    {3, {&linkAnimPatchTable[1]}},
    {7, {&testAnimHeader}}, 
    {0,{NULL}},{0,{NULL}},{0,{NULL}},{0,{NULL}},{0,{NULL}},{0,{NULL}},{0,{NULL}},{0,{NULL}},
    {0,{NULL}},{0,{NULL}},{0,{NULL}},{0,{NULL}},{0,{NULL}},{0,{NULL}},{0,{NULL}},
};
extern LinkActionEntry linkActionRunTable[NUM_ORIG_LINK_ACTIONS];
LinkActionEntry linkActionRunPatchTable[NUM_ORIG_LINK_ACTIONS+NUM_CUSTOM_LINK_ACTIONS] = {
    //Original
    {0,{NULL}},{0,{NULL}},{0,{NULL}},{0,{NULL}},{0,{NULL}},{0,{NULL}},{0,{NULL}},{0,{NULL}},
    {0,{NULL}},{0,{NULL}},{0,{NULL}},{0,{NULL}},{0,{NULL}},{0,{NULL}},{0,{NULL}},{0,{NULL}},
    {0,{NULL}},{0,{NULL}},{0,{NULL}},{0,{NULL}},{0,{NULL}},{0,{NULL}},{0,{NULL}},{0,{NULL}},
    {0,{NULL}},{0,{NULL}},{0,{NULL}},{0,{NULL}},{0,{NULL}},{0,{NULL}},{0,{NULL}},{0,{NULL}},
    {0,{NULL}},{0,{NULL}},{0,{NULL}},{0,{NULL}},{0,{NULL}},{0,{NULL}},{0,{NULL}},{0,{NULL}},
    {0,{NULL}},{0,{NULL}},{0,{NULL}},{0,{NULL}},{0,{NULL}},{0,{NULL}},{0,{NULL}},{0,{NULL}},
    {0,{NULL}},{0,{NULL}},{0,{NULL}},{0,{NULL}},{0,{NULL}},{0,{NULL}},{0,{NULL}},{0,{NULL}},
    {0,{NULL}},{0,{NULL}},{0,{NULL}},{0,{NULL}},{0,{NULL}},{0,{NULL}},{0,{NULL}},{0,{NULL}},
    {0,{NULL}},{0,{NULL}},{0,{NULL}},{0,{NULL}},{0,{NULL}},{0,{NULL}},{0,{NULL}},{0,{NULL}},
    {0,{NULL}},{0,{NULL}},{0,{NULL}},{0,{NULL}},{0,{NULL}},{0,{NULL}},{0,{NULL}},{0,{NULL}},
    {0,{NULL}},{0,{NULL}},{0,{NULL}},{0,{NULL}},{0,{NULL}},{0,{NULL}},{0,{NULL}},{0,{NULL}},
    {0,{NULL}},{0,{NULL}},{0,{NULL}},{0,{NULL}},{0,{NULL}},{0,{NULL}},{0,{NULL}},{0,{NULL}},
    {0,{NULL}},{0,{NULL}},{0,{NULL}},{0,{NULL}},{0,{NULL}},{0,{NULL}},{0,{NULL}},
    //Patched
    {11, {NULL}},
    {11, {NULL}},
    {11, {NULL}},
    {0,{NULL}},{0,{NULL}},{0,{NULL}},{0,{NULL}},{0,{NULL}},{0,{NULL}},{0,{NULL}},{0,{NULL}},
    {0,{NULL}},{0,{NULL}},{0,{NULL}},{0,{NULL}},{0,{NULL}},{0,{NULL}},{0,{NULL}},
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
        sizeof(LinkActionEntry) * NUM_ORIG_LINK_ACTIONS);
    bcopy(PlayerVRAMtoRAM(linkActionRunTable), linkActionRunPatchTable,
        sizeof(LinkActionEntry) * NUM_ORIG_LINK_ACTIONS);
}

void Statics_AnimeRegisterStaticData(void* ram_addr){
    for(s32 i=0; i<(sizeof(linkAnimPatchTable)/sizeof(linkAnimPatchTable[0])); ++i){
        linkAnimPatchTable[i].segment += (u32)ram_addr;
    }
}

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
}

typedef s32 (*Player_SetUpCutscene_t)(GlobalContext *, Actor *, s32);
extern s32 Player_SetUpCutscene(GlobalContext *globalCtx, Actor *actor, s32 csMode);

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
