#include "statics.h"
#include "../fast_loader/fast_loader.h"
//#include "../debugger/debugger.h"

#include <z64ovl/oot/u10.h>

extern z64_global_t gGlobalContext;
extern z64_save_context_t gSaveContext;

extern void Audio_FadeOut(u16 frames);

u8 sLPress = 0;

void Statics_Update(){
    //Press L on pause menu to toggle inventory editor
    //The "press" variable doesn't quite work right because this is run on the
    //VI, not in sync with the game loop. So we have to keep our own press flag.
    if(!sLPress){
        if(gGlobalContext.common.input[0].raw.l){
            sLPress = 1;
            if(gGlobalContext.pause_ctxt.unk_02_[1]){
                gGlobalContext.pause_ctxt.unk_02_[1] = 0;
            /*}else if(gGlobalContext.common.input[0].raw.du){
                gGlobalContext.pause_ctxt.unk_02_[1] = 3;*/
            }else{
                gGlobalContext.pause_ctxt.unk_02_[1] = 2;
            }
        }
    }else{
        if(!gGlobalContext.common.input[0].raw.l){
            sLPress = 0;
        }
    }
}

__attribute__((section(".start"))) void Statics_Init(){
    fp_precmd = Statics_Update;
}

void Statics_TimeTravel(){
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
