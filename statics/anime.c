#include "z64structs.h"
#include "z64funcs.h"
#include "anime.h"

z64_animation_entry_t* AnimationContext_AddEntry(void *animCtx, s32 type);

extern u32 _link_animetionSegmentRomStart[1];
extern u32 link_animetion_segment[1];

extern void AnimationContext_SetLoadFrame(z64_global_t* globalCtx, 
    z64_animation_entry_link_t* animation, s32 frame, s32 limbCount, vec3s_t* frameTable);

void Patched_SetLoadFrame(z64_global_t* globalCtx, 
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
//orig 1.0 pre-reloc VROM is 8085267C
s8 csActionToLinkActionPatchTable[NUM_ORIG_CS_ACTIONS+NUM_CUSTOM_CS_ACTIONS] = {
    #include "csActionToLinkActionTable.xdat"
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
};

#define NUM_ORIG_LINK_ACTIONS 103
#define NUM_CUSTOM_LINK_ACTIONS 0x12
//orig 1.0 pre-reloc VROM is 808529C8
u32 linkActionInitPatchTable[(NUM_ORIG_LINK_ACTIONS+NUM_CUSTOM_LINK_ACTIONS)*2] = {
    #include "linkActionInitTable.xdat"
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
};
//orig 1.0 pre-reloc VROM is 80852D00
u32 linkActionRunPatchTable[(NUM_ORIG_LINK_ACTIONS+NUM_CUSTOM_LINK_ACTIONS)*2] = {
    #include "linkActionRunTable.xdat"
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
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

link_action_entry_t linkCustomActionInitSrcTable[NUM_CUSTOM_LINK_ACTIONS] = {
    {2, &linkAnimPatchTable[0]},
    {0, NULL}, 
    {0, NULL}, {0, NULL}, {0, NULL}, {0, NULL}, 
    {0, NULL}, {0, NULL}, {0, NULL}, {0, NULL}, 
    {0, NULL}, {0, NULL}, {0, NULL}, {0, NULL}, 
    {0, NULL}, {0, NULL}, {0, NULL}, {0, NULL}, 
};

link_action_entry_t linkCustomActionRunSrcTable[NUM_CUSTOM_LINK_ACTIONS] = {
    {0, NULL}, {0, NULL}, {0, NULL}, {0, NULL}, 
    {0, NULL}, {0, NULL}, {0, NULL}, {0, NULL}, 
    {0, NULL}, {0, NULL}, {0, NULL}, {0, NULL}, 
    {0, NULL}, {0, NULL}, {0, NULL}, {0, NULL}, 
    {0, NULL}, {0, NULL}, 
};

extern u32 anim_START;
static DmaRequest animFileInfo = { 0xDEADBEEF, &anim_START, 0x04206969, 0, 0, 0, 0 };

void Statics_AnimeCodePatches(){
    //Patch Link animation loader
    *( (u32*)AnimationContext_SetLoadFrame   ) = JUMPINSTR(Patched_SetLoadFrame);
	*(((u32*)AnimationContext_SetLoadFrame)+1) = 0;
    //Copy src tables to path tables. They're separate because including the
    //original data in struct form would be a pain. Only a hundred bytes or so waste.
    bcopy(linkCustomActionInitSrcTable, &linkActionInitPatchTable[NUM_ORIG_LINK_ACTIONS*2],
        sizeof(link_action_entry_t) * NUM_CUSTOM_LINK_ACTIONS);
    bcopy(linkCustomActionRunSrcTable, &linkActionRunPatchTable[NUM_ORIG_LINK_ACTIONS*2],
        sizeof(link_action_entry_t) * NUM_CUSTOM_LINK_ACTIONS);
    //Load animations from extra ROM file to RAM
    //TODO romhack only
    z_file_load(&animFileInfo);
}

extern void Player_START();
extern s32 Player_SetUpCutscene(z64_global_t *globalCtx, z64_actor_t *actor, s32 csMode);
typedef s32 (*Player_SetUpCutscene_t)(z64_global_t *, z64_actor_t *, s32);

void Statics_AnimeTest(){
    Player_SetUpCutscene_t fp = (Player_SetUpCutscene_t)(
        (void*)Player_SetUpCutscene - (void*)Player_START + 
        ((ActorOverlay*)(PLAYER->actor.code_entry))->loadedRamAddr);
    fp(&gGlobalContext, NULL, NUM_ORIG_CS_ACTIONS);
}
