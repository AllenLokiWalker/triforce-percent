#include "statics.h"
#include "../fast_loader/fast_loader.h"
//#include "../debugger/debugger.h"

#include <z64ovl/oot/u10.h>

extern void bzero(void* addr, s32 size);
extern void osWritebackDCache(void* addr, s32 size);
extern void osInvalICache(void* addr, s32 size);

extern z64_global_t gGlobalContext;
extern z64_save_context_t gSaveContext;

#define CTRLR_RAW gGlobalContext.common.input[0].raw
#define CTRLR_PRESS gGlobalContext.common.input[0].pad_pressed
#define PLAYER ((z64_player_t*)gGlobalContext.actor_ctxt.actor_list[OVLTYPE_PLAYER].first)

#define JUMPINSTR(func) (0x08000000 | ((((u32)func)>>2) & 0x03FFFFFF))
#define JALINSTR(func)  (0x0C000000 | ((((u32)func)>>2) & 0x03FFFFFF))

#include "interface.c"
#include "message.c"

void Statics_ApplyCodePatches(){
    static u8 sCodePatched = 0;
    if(sCodePatched) return;
	Statics_InterfaceCodePatches();
    Statics_MessageCodePatches();
    osWritebackDCache(0, 0x4000);
    osInvalICache(0, 0x4000);
    sCodePatched = 1;
}

void Statics_Update(){
    static u8 sLPress = 0;
    static u8 sInvEditorLastState = 0;
    //
    Statics_ApplyCodePatches();
    //Press L on pause menu to toggle inventory editor
    //The "press" variable doesn't quite work right because this is run on the
    //VI, not in sync with the game loop. So we have to keep our own press flag.
    //Also, the game already has code to press L to turn OFF the inventory
    //editor, which conflicts with this. This is why this is convoluted.
    if(!sLPress){
        if(CTRLR_RAW.l){
            sLPress = 1;
            if(!sInvEditorLastState && gGlobalContext.pause_ctxt.state){
                gGlobalContext.pause_ctxt.unk_02_[1] = 1;
            }
        }
    }else{
        if(!CTRLR_RAW.l){
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
    gSaveContext.inf_table    [0x0] |= 1 << 0x0; //Greeted by Saria
    */
    //Set up Adult Link inventory to not have the Master Sword
    if(gSaveContext.adult_equips.button_items[0] == 0xFF){
        //Adult has empty B button, so this was not run yet
        gSaveContext.adult_equips.button_items[0] = 0x3D; //ITEM_SWORD_BGS
        gSaveContext.adult_equips.button_items[1] = 0xFF; //ITEM_NONE
        gSaveContext.adult_equips.button_items[2] = 0x02; //ITEM_BOMB
        gSaveContext.adult_equips.button_items[3] = 0x08; //ITEM_OCARINA_TIME
        gSaveContext.adult_equips.c_button_slots[0] = 0xFF; //SLOT_NONE
        gSaveContext.adult_equips.c_button_slots[1] = 0x02; //SLOT_BOMB
        gSaveContext.adult_equips.c_button_slots[2] = 0x07; //SLOT_OCARINA
        gSaveContext.adult_equips.equipment = 0x1103;
        //Giant's Knife -> Biggoron Sword
        gSaveContext.bgs_flag = 1;
        gSaveContext.bgs_hits_left = 8;
    }
    //Give magic
    gSaveContext.magic_acquired = 1;
    gSaveContext.magic_level = 2;
    gSaveContext.magic = 0x60;
    gSaveContext.unk_13F4 = 0x60;
    gSaveContext.double_magic = 1;
    //Equip Quest Status subscreen items to C
    Statics_HandleEquipMedallionsToC();
    //Press L+DD to clip below the ice in Zora's Domain
    if(CTRLR_RAW.l && (CTRLR_PRESS & INPUT_D_DOWN)){
        PLAYER->actor.pos.y -= 80.0f;
    }
}

__attribute__((section(".start"))) void Statics_Init(){
    fp_precmd = Statics_Update;
}

extern void Audio_FadeOut(u16 frames);

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
