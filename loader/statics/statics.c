#include "statics.h"
#include "../fast_loader/fast_loader.h"
//#include "../debugger/debugger.h"

#include <z64ovl/oot/u10.h>

extern z64_global_t gGlobalContext;
extern z64_save_context_t gSaveContext;

extern void Audio_FadeOut(u16 frames);


void Statics_Update(){
    //Press L on pause menu to toggle inventory editor
    if(/*(gGlobalContext.pause_ctxt.state > 0) && */
            (gGlobalContext.common.input[0].pad_pressed & INPUT_L_TRIGGER)){
        if(gGlobalContext.pause_ctxt.unk_02_[1]){
            gGlobalContext.pause_ctxt.unk_02_[1] = 0;
        /*}else if((gGlobalContext.common.input[0].raw.pad & INPUT_D_UP)){
            gGlobalContext.pause_ctxt.unk_02_[1] = 3;*/
        }else{
            gGlobalContext.pause_ctxt.unk_02_[1] = 2;
        }
    }
}

__attribute__((section(".start"))) void Statics_Init(){
    fp_precmd = Statics_Update;
}

void Statics_TimeTravel(){
    gGlobalContext.link_age = !gSaveContext.link_age;
    gGlobalContext.unk_1D_ = 1; //unk_11DE9 not sure? next variable after link_age
    gSaveContext.respawn_flag = -2;
    gGlobalContext.scene_load_flag = 0x14;
    gGlobalContext.entrance_index = gSaveContext.entrance_index;
    gSaveContext.next_day_time = gSaveContext.day_time;
    gGlobalContext.fadeout_transition = 0x2C;
    gSaveContext.next_transition = 5;
    Audio_FadeOut(30);
    gSaveContext.seq_index = 0xFF;
    gSaveContext.night_seq_index = 0xFF;
}
