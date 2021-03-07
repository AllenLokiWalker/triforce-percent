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

static void *customAnimData;

void Statics_RegisterAnimDataAddress(void *addr){
    customAnimData = addr;
}

void Statics_AnimeCodePatches(){
    *( (u32*)AnimationContext_SetLoadFrame   ) = JUMPINSTR(Patched_SetLoadFrame);
	*(((u32*)AnimationContext_SetLoadFrame)+1) = 0;
}
