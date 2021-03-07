
void DmaMgr_SendRequest2(void *req, u32 ram, u32 rom, u32 size, u32 unk0,
    OSMesgQueue *queue, OSMesg msg);

z64_animation_entry_t* AnimationContext_AddEntry(void *animCtx, s32 type);

extern u32 _link_animetionSegmentRomStart[1];
extern u32 link_animetion_segment[1];

void AnimationContext_SetLoadFrame_Patched(z64_global_t* globalCtx, 
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
            + (linkAnimHeader->anim - (u32)&link_animetion_segment)
            + (animStepSize * frame),
            animStepSize, 0, &entry->types.type0.msgQueue, 0);
    }
}
