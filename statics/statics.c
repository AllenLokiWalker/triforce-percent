#include "z64structs.h"
#include "z64funcs.h"
#include "statics.h"

#include "../loader/fast_loader/fast_loader.h"
#include "interface.h"
#include "message.h"
#include "anime.h"

static u8 sIsLiveRun = 0;

/*
void Statics_ActorVarsFail(z64_actor_init_t* actor_init){
    *((u32*)0x807FFFF0) = actor_init->instance_size;
    *((u32*)0x807FFFF4) = (u32)actor_init->init;
    *((u32*)0x807FFFF8) = (u32)actor_init->main;
    *((u32*)0x807FFFFC) = (u32)actor_init->draw;
}
*/

void Statics_ApplyCodePatches(){
    static u8 sCodePatched = 0;
    if(sCodePatched) return;
    //TODO
    //Entrance cutscene table 0x800EFD04 entry 17 (originally Inside Jabu)
    //Entrance 0x9C, age 2, flag 0, segment offset 0x02000130 (from 0x17 cutscene command in scene)
    //WRITE 8 0x800EFD8C 0x00 0x9C 0x02 0x00 0x02 0x00 0x01 0x30
    *((u32*)0x800EFD8C) = 0x009C0200;
    *((u32*)0x800EFD90) = 0x020002E4;
    //TODO crash if actor fails to load, so we can see which part is failing
    //*((u32*)0x800251F4) = 0x8C000001; //lw $zero, 0x0001($zero) (crash)
    //*((u32*)0x8002529C) = 0x8C000001;
    //*((u32*)0x800252C4) = 0x8C000001; <- it's this one
    //*((u32*)0x800252BC) = JALINSTR(Statics_ActorVarsFail);
    //*((u32*)0x800252C0) = 0x00032025; //or a0, $zero, v0
    //
	Statics_InterfaceCodePatches();
    Statics_MessageCodePatches();
    Statics_AnimeCodePatches(sIsLiveRun);
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
    //Test/Debugging
    if(CTRLR_RAW.l && (CTRLR_PRESS & INPUT_D_DOWN)){
        //Press L+DD to clip below the ice in Zora's Domain
        //PLAYER->actor.pos.y -= 80.0f;
        Statics_AnimeTest(1);
    }
    if(CTRLR_RAW.l && (CTRLR_PRESS & INPUT_D_LEFT)){
        //Press L+DL for frog
        textbox_begin(&gGlobalContext, 0x0901, NULL);
    }
    if(CTRLR_RAW.l && (CTRLR_PRESS & INPUT_D_RIGHT)){
        //Press L+DR for animation test
        Statics_AnimeTest(0);
    }
}

__attribute__((section(".start"))) void Statics_Init(){
    fp_precmd = Statics_Update;
    sIsLiveRun = 1;
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
