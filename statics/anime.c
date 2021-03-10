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
    z64_animation_entry_link_t* linkAnimHeader = zh_seg2ram((u32)animation);
    u32 ram = frameTable;
    u32 animStepSize = sizeof(vec3s_t) * limbCount + 2;
    
    z64_animation_entry_t* entry = AnimationContext_AddEntry((u8*)globalCtx + 0x10B20, 0);
    if (entry == NULL) return;
    
    osCreateMesgQueue(&entry->types.type0.msgQueue, &entry->types.type0.msg, 1);
    
    if(linkAnimHeader->anim & 0x80000000){
        //Animation is in RAM
        bcopy(linkAnimHeader->anim + (animStepSize * frame), ram, animStepSize);
        osSendMesg(&entry->types.type0.msgQueue, (OSMesg)0, 0);
    }else{
        DmaMgr_SendRequest2(&entry->types.type0.req, ram,
            (u32)&_link_animetionSegmentRomStart
            + (linkAnimHeader->anim & 0x00FFFFFF)
            + (animStepSize * frame),
            animStepSize, 0, &entry->types.type0.msgQueue, 0);
    }
}

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

//Animation table
//const z64_animation_entry_link_t linkAnimPatchTable[...] = {...};
#include "../anim/anim.c"

static DmaRequest animFileInfo = { 0xDEADBEEF, &anim_START, 0x04206969, 0, 0, NULL, 0 };

void Statics_AnimeCodePatches(){
    //Patch Link animation loader
    *( (u32*)AnimationContext_SetLoadFrame   ) = JUMPINSTR(Patched_SetLoadFrame);
	*(((u32*)AnimationContext_SetLoadFrame)+1) = 0;
    //Load animations from extra ROM file to RAM
    //TODO romhack only
    z_file_load(&animFileInfo);
}
