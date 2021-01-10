#include "statics.h"
#include "../fast_loader/fast_loader.h"
//#include "../debugger/debugger.h"

#include <z64ovl/oot/u10.h>

extern z64_global_t gGlobalContext;
extern z64_save_context_t gSaveContext;

extern void Audio_FadeOut(u16 frames);

u8 sLPress = 0;
u8 sInvEditorLastState = 0;

void Statics_Update(){
    //Press L on pause menu to toggle inventory editor
    //The "press" variable doesn't quite work right because this is run on the
    //VI, not in sync with the game loop. So we have to keep our own press flag.
    if(!sLPress){
        if(gGlobalContext.common.input[0].raw.l){
            sLPress = 1;
            if(!sInvEditorLastState && gGlobalContext.pause_ctxt.state){
                gGlobalContext.pause_ctxt.unk_02_[1] = 1;
            }
        }
    }else{
        if(!gGlobalContext.common.input[0].raw.l){
            sLPress = 0;
        }
    }
    sInvEditorLastState = gGlobalContext.pause_ctxt.unk_02_[1];
    //Set some event flags
    /*
    gSaveContext.event_chk_inf[0x0] |= 1 << 0x7; //Obtained Kokiri's Emerald & Deku Tree Dead
    gSaveContext.event_chk_inf[0x1] |= 1 << 0x7; //Great Deku Tree is Dead
    gSaveContext.event_chk_inf[0x1] |= 1 << 0x9; //Obtained Kokiri's Emerald
    gSaveContext.event_chk_inf[0x4] |= 1 << 0x3; //Obtained Ocarina of Time
    gSaveContext.event_chk_inf[0x8] |= 1 << 0x0; //Zelda Fled Hyrule Castle
    gSaveContext.event_chk_inf[0x8] |= 1 << 0x2; //Bridge Unlocked (After Zelda Escape Cutscene)
    gSaveContext.event_chk_inf[0xA] |= 1 << 0x9; //Learned Song of Time
    gSaveContext.event_chk_inf[0xC] |= 1 << 0x1; //Spoke to Saria on Lost Woods Bridge
    */
    gSaveContext.inf_table    [0x0] |= 1 << 0x0; //Greeted by Saria
}

__attribute__((section(".start"))) void Statics_Init(){
    fp_precmd = Statics_Update;
}

void Statics_TimeTravel(){
    //Don't time travel if playing Song of Time at ocarina prompt
    //unk_E3EE == ocarina_mode == 0x104C6 == unk_15_2[0] except u16 not char
    //unk_E3F0 == ocarina_no == 0x104C8 == unk_15_2[2] except u16
    //unk_E40E == 0x104E6 == unk_104E4[2] except s16
    //if(*((u16*)&(gGlobalContext.unk_15_2[0])) >= 2) return;
    if(gGlobalContext.scene_index == 0x43) return; //in Temple of Time
    //Time travel
    gGlobalContext.link_age = gSaveContext.link_age ^ 1;
    //gGlobalContext.unk_1D_ = 1; //unk_11DE9 not sure? next variable after link_age
    gSaveContext.respawn_flag = -2;
    gGlobalContext.scene_load_flag = 0x14;
    gGlobalContext.entrance_index = gSaveContext.entrance_index;
    //gSaveContext.next_day_time = gSaveContext.day_time;
    gGlobalContext.fadeout_transition = 0x2C;
    gSaveContext.next_transition = 5;
    /*
    Audio_FadeOut(30);
    gSaveContext.seq_index = 0xFF;
    gSaveContext.night_seq_index = 0xFF;
    */
}
