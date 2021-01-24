#include "statics.h"
#include "../fast_loader/fast_loader.h"
//#include "../debugger/debugger.h"

#include <z64ovl/oot/u10.h>

#include "interface.h"

#define CTRLR_RAW gGlobalContext.common.input[0].raw
#define CTRLR_PRESS gGlobalContext.common.input[0].pad_pressed
#define PLAYER ((z64_player_t*)gGlobalContext.actor_ctxt.actor_list[OVLTYPE_PLAYER].first)

extern z64_global_t gGlobalContext;
extern z64_save_context_t gSaveContext;

extern void bzero(void* addr, s32 size);
extern void osWritebackDCache(void* addr, s32 size);
extern void osInvalICache(void* addr, s32 size);

extern void Audio_FadeOut(u16 frames);

void Patched_LoadItemIconMain(z64_global_t *global, u16 button, u16 num){
    InterfaceContext *interfaceCtx = (InterfaceContext*)&global->if_ctxt;
    u32 rom = 0x007BD000; //icon_item_static
    u8 *ram = interfaceCtx->icon_itemSegment + button * 0x1000;
    u32 *image = (u32*)ram;
    u32 size = 0x1000;
    u8 item = gSaveContext.equips.button_items[button];
    s8 x, y;
    
    if(item >= 0xF0){
        //Empty/no item, clear texture
        bzero(ram, size);
        return;
    }else if(item >= 0x66 && item <= 0x79){
        item -= 0x66;
        size = 0x900;
        rom = 0x00846000; //icon_item_24_static
    }else if(item >= 0x5A){
        item = 0x35; //if invalid item, default to Frog
    }
    rom += item * size;
    
    if(num == 0){
        DmaMgr_SendRequest1(ram, rom, size, 0);
    }else{
        DmaRequest *request = ((num == 1) ? &interfaceCtx->dmaRequest_160 : &interfaceCtx->dmaRequest_180);
        osCreateMesgQueue(&interfaceCtx->loadQueue, &interfaceCtx->loadMsg, OS_MESG_BLOCK);
        DmaMgr_SendRequest2(request, ram, rom, size, 0, &interfaceCtx->loadQueue, 0);
        osRecvMesg(&interfaceCtx->loadQueue, NULL, OS_MESG_BLOCK);
    }
    
    if(size == 0x1000) return;
    
    //Recenter icon from 24x24 to 32x32.
    for(y=31; y>=0; --y){
        for(x=31; x>=0; --x){
            u32 pixel = 0;
            if(x>=4 && x<28 && y>=4 && y<28){
                pixel = image[24*(y-4) + (x-4)];
            }
            image[32*y+x] = pixel;
        }
    }
}

void Patched_LoadAllItemIcons(){
    Patched_LoadItemIconMain(&gGlobalContext, 0, 0);
    Patched_LoadItemIconMain(&gGlobalContext, 1, 0);
    Patched_LoadItemIconMain(&gGlobalContext, 2, 0);
    Patched_LoadItemIconMain(&gGlobalContext, 3, 0);
}

void Patched_LoadItemIcon1(z64_global_t *global, u16 button){
    Patched_LoadItemIconMain(global, button, 1);
}

void Patched_LoadItemIcon2(z64_global_t *global, u16 button){
    Patched_LoadItemIconMain(global, button, 2);
}

s32 *Patched_EquipEffectTexLoad(s32 *dl, s32 dummy, PauseContext *pauseCtx){
    s32 gDPLoadBlockW1, gDPSetTileW0, gDPSetTileSizeW1;
    u16 item = pauseCtx->equipTargetItem;
    if(item >= 0x66 && item <= 0x79){
        //24x24 icon
        gDPLoadBlockW1 = 0x0723F0AB;
        gDPSetTileW0 = 0xF5180C00;
        gDPSetTileSizeW1 = 0x0005C05C;
    }else{
        //32x32 icon
        gDPLoadBlockW1 = 0x073FF080;
        gDPSetTileW0 = 0xF5181000;
        gDPSetTileSizeW1 = 0x0007C07C;
    }
    //gDPSetTextureImage
    dl[0x0] = 0xFD180000;
    dl[0x1] = gItemIcons[item];
    //gDPSetTile
    dl[0x2] = 0xF5180000;
    dl[0x3] = 0x07000000;
    //gDPLoadSync
    dl[0x4] = 0xE6000000;
    dl[0x5] = 0;
    //gDPLoadBlock
    dl[0x6] = 0xF3000000;
    dl[0x7] = gDPLoadBlockW1;
    //gDPPipeSync
    dl[0x8] = 0xE7000000;
    dl[0x9] = 0;
    //gDPSetTile
    dl[0xA] = gDPSetTileW0;
    dl[0xB] = 0;
    //gDPSetTileSize
    dl[0xC] = 0xF2000000;
    dl[0xD] = gDPSetTileSizeW1;
    return dl + 0xE;
}

void Statics_HandleEquipMedallionsToC(){
    PauseContext *pauseCtx = &gGlobalContext.pause_ctxt;
    if(!pauseCtx->state) return;
    
    //Enable C buttons on Quest Status subscreen
	//Have to set once every time the pause menu overlay gets reloaded
	if(pauseCtx->state >= 4 && pauseCtx->state <= 11 && sSubscreenButtonStates[3*5+1] == 0xFF){
		sSubscreenButtonStates[3*5+1] = 0;
		sSubscreenButtonStates[3*5+2] = 0;
		sSubscreenButtonStates[3*5+3] = 0;
	}
    
    if(pauseCtx->flag || pauseCtx->kscpPos != 2) return;
    
    u8 item = pauseCtx->cursorItem[2];
    if(item >= 0x66 && item <= 0x79 && //actually has item, not empty
            (CTRLR_PRESS & (INPUT_C_LEFT | INPUT_C_DOWN | INPUT_C_RIGHT))){
        //Equipping a Quest Status item
        if(CTRLR_PRESS & INPUT_C_LEFT){
            pauseCtx->equipTargetCBtn = 0;
        }else if(CTRLR_PRESS & INPUT_C_DOWN){
            pauseCtx->equipTargetCBtn = 1;
        }else{
            pauseCtx->equipTargetCBtn = 2;
        }
        pauseCtx->equipTargetSlot = 24 + pauseCtx->equipTargetCBtn;
        pauseCtx->equipTargetItem = item;
        pauseCtx->unk_1E4 = 3;
        pauseCtx->equipAnimX = 770; //TODO
        pauseCtx->equipAnimY = 50; //TODO
        pauseCtx->equipAnimAlpha = 255;
        sEquipAnimTimer = 0;
        sEquipAnimState = 3;
        sEquipAnimNumFrames = 10;
        Audio_PlaySoundGeneral(0x4808, //NA_SE_SY_DECIDE
            &sSoundParam1, 4, &sSoundParam34, &sSoundParam34, &sSoundParam5);
    }
}

u8 sCodePatched = 0;
u8 sLPress = 0;
u8 sInvEditorLastState = 0;

#define JUMP(func) (0x08000000 | ((((u32)func)>>2) & 0x03FFFFFF))
#define JAL(func)  (0x0C000000 | ((((u32)func)>>2) & 0x03FFFFFF))

void Statics_ApplyCodePatches(){
    if(sCodePatched) return;
    //
	*( (u32*)Interface_LoadItemIcon1   ) = JUMP(Patched_LoadItemIcon1);
	*(((u32*)Interface_LoadItemIcon1)+1) = 0;
    *( (u32*)Interface_LoadItemIcon2   ) = JUMP(Patched_LoadItemIcon2);
	*(((u32*)Interface_LoadItemIcon2)+1) = 0;
    //At beginning of z_construct item icon loading, jal Patched_LoadAllItemIcons
    *( (u32*)Construct_Icon_Start   ) = JAL(Patched_LoadAllItemIcons);
	*(((u32*)Construct_Icon_Start)+1) = 0;
    //After returning, jump to end of icon loading
    *(((u32*)Construct_Icon_Start)+2) = JUMP(Construct_Icon_Target);
    *(((u32*)Construct_Icon_Start)+3) = 0;
    //
    //Equip item animation patch
    *( (u32*)InterfaceEffectTex_Start   ) = JAL(Patched_EquipEffectTexLoad);
    *(((u32*)InterfaceEffectTex_Start)+1) = 0x8E8402B0; //lw a0, 0x02B0(s4)
    *(((u32*)InterfaceEffectTex_Start)+2) = JUMP(InterfaceEffectTex_Target);
    *(((u32*)InterfaceEffectTex_Start)+3) = 0xAE8202B0; //sw v0, 0x02B0(s4)
    //
    osWritebackDCache(0, 0x4000);
    osInvalICache(0, 0x4000);
    sCodePatched = 1;
}

void Statics_Update(){
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
