#include "z64structs.h"
#include "z64funcs.h"
#include "anime.h"

extern z64_animation_entry_t* AnimationContext_AddEntry(void *animCtx, s32 type);
extern void AnimationContext_SetLoadFrame(z64_global_t* globalCtx, 
    z64_animation_entry_link_t* animation, s32 frame, s32 limbCount, vec3s_t* frameTable);

extern u32 _link_animetionSegmentRomStart[1];

static void Patched_SetLoadFrame(z64_global_t* globalCtx, 
    z64_animation_entry_link_t* animation, s32 frame, s32 limbCount, vec3s_t* frameTable) 
{
    z64_animation_entry_link_t* linkAnimHeader = (void*)zh_seg2ram((u32)animation);
    u32 animStepSize = sizeof(vec3s_t) * limbCount + 2;
    
    z64_animation_entry_t* entry = AnimationContext_AddEntry((u8*)globalCtx + 0x10B20, 0);
    if (entry == NULL) return;
    
    osCreateMesgQueue(&entry->types.type0.msgQueue, &entry->types.type0.msg, 1);
    
    if(linkAnimHeader->anim & 0x80000000){
        //Animation is in RAM
        bcopy((void*)((s32)linkAnimHeader->anim + (animStepSize * frame)), 
            frameTable, animStepSize);
        osSendMesg(&entry->types.type0.msgQueue, (OSMesg)0, 0);
    }else{
        DmaMgr_SendRequest2(&entry->types.type0.req, frameTable,
            (u32)&_link_animetionSegmentRomStart
            + (linkAnimHeader->anim & 0x00FFFFFF)
            + (animStepSize * frame),
            animStepSize, 0, &entry->types.type0.msgQueue, 0);
    }
}

//Animation table
//z64_animation_entry_link_t linkAnimPatchTable[...] = {...};
#include "../anim/anim.c"

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
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0
};

typedef struct {
    //If positive, passes ptr to function in table D_80854AA4 (debug) indexed
    //by value. 
    //1: just stops Link. 
    //2: also sets Y to 0, changes to anim, play once at full speed, -6 morph
    //3: same as 2 but 2/3 speed and -8 morph
    //4: same as 3 but looping
    //5: same as 4 but sets moveFlags to 0x1C
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
    {2, &linkAnimPatchTable[0]},
    {0, NULL}, 
    {0, NULL}, {0, NULL}, {0, NULL}, {0, NULL}, {0, NULL}, {0, NULL}, {0, NULL}, {0, NULL}, 
    {0, NULL}, {0, NULL}, {0, NULL}, {0, NULL}, {0, NULL}, {0, NULL}, {0, NULL}, {0, NULL}, 
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
    {0, NULL}, {0, NULL}, {0, NULL}, {0, NULL}, {0, NULL}, {0, NULL}, {0, NULL}, {0, NULL}, 
    {0, NULL}, {0, NULL}, {0, NULL}, {0, NULL}, {0, NULL}, {0, NULL}, {0, NULL}, {0, NULL}, 
    {0, NULL}, {0, NULL}, 
};

extern void Player_RAM_START();
extern void Player_START();

static void *PlayerVRAMtoRAM(void *ptr){
    return ptr - (void*)Player_START + (void*)Player_RAM_START;
}

void Statics_Player_Init(){
    static u32 alreadyrun = 0;
    if(alreadyrun) return;
    alreadyrun = 1;
    //Patch overwrote 
    //globalCtx->shootingGalleryStatus = globalCtx->bombchuBowlingStatus = 0;
    //so we have to do that
    ((u8*)&gGlobalContext)[0x11E5C] = 0;
    ((u8*)&gGlobalContext)[0x11E5D] = 0;
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

void Statics_AnimeCodePatches(){
    //Patch Link animation loader
    *( (u32*)AnimationContext_SetLoadFrame   ) = JUMPINSTR(Patched_SetLoadFrame);
	*(((u32*)AnimationContext_SetLoadFrame)+1) = 0;
    //Load animations from extra ROM file to RAM
    //TODO romhack only
    z_file_load(&animFileInfo);
}

typedef s32 (*Player_SetUpCutscene_t)(z64_global_t *, z64_actor_t *, s32);
extern s32 Player_SetUpCutscene(z64_global_t *globalCtx, z64_actor_t *actor, s32 csMode);

void Statics_AnimeTest(){
    Player_SetUpCutscene_t fp = (Player_SetUpCutscene_t)PlayerVRAMtoRAM(&Player_SetUpCutscene);
    fp(&gGlobalContext, NULL, NUM_ORIG_CS_ACTIONS);
}
