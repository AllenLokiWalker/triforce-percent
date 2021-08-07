#include "ootmain.h"
#include "statics.h"

#include "../loader/fast_loader/fast_loader.h"
#include "../loader/debugger/debugger.h"
#include "interface.h"
#include "message.h"
#include "anime.h"
#include "ocarina.h"
#include "audio.h"
#include "gfx.h"

static u8 sIsLiveRun = 0;

void Statics_SetGameState(){
    //Set some event flags
    //TODO disable Kaepora Gaebora in Lost Woods (or everywhere)
    //TODO set flags for have picked up item drops before (magic jar, deku
    //seeds/nuts, etc.)
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
    gSaveContext.eventChkInf[0x9] |= 0xF; //Rescued carpenters (not get arrested by Gerudos)
    gSaveContext.itemGetInf[0x2] |= 0x0478; //Obtained Mask of Truth, all trading masks
    gSaveContext.itemGetInf[0x3] |= 0x8F00; //Obtained Mask of Truth, sold all masks
    //TODO remove for final version
    WORKING_BUNNYHOOD_VAR |= WORKING_BUNNYHOOD_BIT;
    WORKING_GERUDOMASK_VAR |= WORKING_GERUDOMASK_BIT;
    //Set up Adult Link inventory to not have the Master Sword
    gSaveContext.adultEquips.buttonItems[0] = 0x3D; //ITEM_SWORD_BGS
    gSaveContext.adultEquips.buttonItems[1] = 0xFF; //ITEM_NONE
    gSaveContext.adultEquips.buttonItems[2] = 0x02; //ITEM_BOMB
    gSaveContext.adultEquips.buttonItems[3] = 0x08; //ITEM_OCARINA_TIME
    gSaveContext.adultEquips.cButtonSlots[0] = 0xFF; //SLOT_NONE
    gSaveContext.adultEquips.cButtonSlots[1] = 0x02; //SLOT_BOMB
    gSaveContext.adultEquips.cButtonSlots[2] = 0x07; //SLOT_OCARINA
    gSaveContext.adultEquips.equipment = 0x1103;
    gSaveContext.bgsFlag = 1; //Giant's Knife -> Biggoron Sword
    gSaveContext.swordHealth = 8;
    //Give magic
    gSaveContext.magicAcquired = 1;
    gSaveContext.magicLevel = 2;
    gSaveContext.magic = 0x60;
    gSaveContext.unk_13F4 = 0x60;
    gSaveContext.doubleMagic = 1;
}

void Statics_RomhackLoadAll();

void Statics_OneTimeRomhackOnly(){
    Statics_RomhackLoadAll();
    //Entrance cutscene table 0x800EFD04 entry 17 (originally Inside Jabu)
    //Entrance 0x9C, age 2, flag 0, segment offset 0x02000130 (from 0x17 cutscene command in scene)
    //WRITE 8 0x800EFD8C 0x00 0x9C 0x02 0x00 0x02 0x00 0x01 0x30
    *((u32*)0x800EFD8C) = 0x009C0200;
    *((u32*)0x800EFD90) = 0x020002E4;
}

void Statics_OneTime(){
    Statics_SetGameState();
	Statics_InterfaceCodePatches();
    Statics_MessageCodePatches();
    Statics_AnimeCodePatches(sIsLiveRun);
    Statics_OcarinaCodePatches();
    Statics_AudioCodePatches(sIsLiveRun);
    Statics_GfxCodePatches();
    osWritebackDCache(0, 0x4000);
    osInvalICache(0, 0x4000);
    if(!sIsLiveRun){
        Statics_OneTimeRomhackOnly();
    }
}

void Statics_InventoryEditor(){
    //Press L on pause menu to toggle inventory editor
    //The "press" variable doesn't quite work right because this is run on the
    //VI, not in sync with the game loop. So we have to keep our own press flag.
    //Also, the game already has code to press L to turn OFF the inventory
    //editor, which conflicts with this. This is why this is convoluted.
    static u8 sLPress = 0;
    static u16 sInvEditorLastState = 0;
    if(!sLPress){
        if((CTRLR_RAW & BTN_L)){
            sLPress = 1;
            if(!sInvEditorLastState && gGlobalContext.pauseCtx.state){
                gGlobalContext.pauseCtx.debugState = 1;
            }
        }
    }else{
        if(!(CTRLR_RAW & BTN_L)){
            sLPress = 0;
        }
    }
    sInvEditorLastState = gGlobalContext.pauseCtx.debugState;
}

void Statics_LostWoods(){
    static s8 sWoodsState = 0, sWoodsTarget = -1, sWoodsCount = 0;
    static const float sWoodsTargetX[3] = {0.0f, 793.0f, 269.0f}; //north, south, west
    static const float sWoodsTargetZ[3] = {-530.0f, 546.0f, -795.0f};
    static const s8 sWoodsPath[4] = {0, 2, 1, 2};
    const float radius = 55.0f;
    Player *player = PLAYER;
    if(gGlobalContext.sceneNum != 0x5B){ //not in Lost Woods
        if(sWoodsState == 1 && sWoodsCount < 4){
             if(sWoodsTarget == sWoodsPath[sWoodsCount]){
                 ++sWoodsCount;
             }else{
                 sWoodsCount = 0;
             }
             sWoodsState = 0;
        }
        return;
    }
    //In Lost Woods
    if(sWoodsCount == 4){
        if(sWoodsState < 20){
            ++sWoodsState;
        }else if(sWoodsState == 20){
            Audio_PlayActorSound2(&(player->actor), 0x4802);
            ++sWoodsState;
        }
    }else{
        sWoodsState = 1;
    }
    sWoodsTarget = -1;
    float x = player->actor.world.pos.x;
    float z = player->actor.world.pos.z;
    for(s32 i=0; i<3; ++i){
        float tx = sWoodsTargetX[i] - x;
        float tz = sWoodsTargetZ[i] - z;
        if(tx * tx + tz * tz < radius * radius){
            sWoodsTarget = i;
            break;
        }
    }
    /*
    zh_draw_debug_text(&gGlobalContext, 0xFF8000FF, 1, 1, "s %d t %d c %d %f %f", 
        sWoodsState, sWoodsTarget, sWoodsCount, x, z);
    */
}

void Statics_Player_PatchedRunning(Player* this, f32 arg1, s16 arg2){
    u16 speed = 0x0226;
    if(WearingWorkingBunnyHood()){
        speed = 0x044C;
        arg1 *= 1.5f;
    }
    R_RUN_SPEED_LIMIT = speed;
    Math_AsymStepToF(&this->linearVelocity, arg1, REG(19) / 100.0f, 1.5f);
    Math_ScaledStepToS(&this->currentYaw, arg2, REG(27));
}

extern float linkJumpYSpeed; //D_808535E8 == 808514A8

void Statics_Player_BunnyHood_YSpeed(){
    Player *player = PLAYER;
    if(player->stateFlags1 & 0x8000000) {
        linkJumpYSpeed = 0.5f;
    }else if(WearingWorkingBunnyHood()){
        linkJumpYSpeed = 1.25f;
    }else{
        linkJumpYSpeed = 1.0f;
    }
}

void Statics_TestShortcuts(){
    //Test/Debugging
    if((CTRLR_RAW & BTN_L)){
        if((CTRLR_PRESS & BTN_DDOWN)){
            //Press L+DD for...
            //clip below the ice in Zora's Domain
            //PLAYER->actor.pos.y -= 80.0f;
            //animation test
            Statics_AnimeTest(1);
        }else if((CTRLR_PRESS & BTN_DLEFT)){
            //Press L+DL for frog
            func_8010B680(&gGlobalContext, 0x0901, NULL); //textbox_begin
        }else if((CTRLR_PRESS & BTN_DRIGHT)){
            //Press L+DR for animation test
            Statics_AnimeTest(0);
        }else if((CTRLR_PRESS & BTN_DUP)){
            //Kill Link (sorry)
            gSaveContext.health = 0;
        }
    }
}

void Statics_Player_Update(){
    //Patch overwrote this
    if(PLAYER->unk_A73 != 0) PLAYER->unk_A73--;
    //Custom content
    Statics_TestShortcuts();
    Statics_LostWoods();
}

static u8 sOneTime = 0;

void Statics_Update(){
    if(!sOneTime){
        Statics_OneTime();
        sOneTime = 1;
    }
    Statics_InventoryEditor();
    Statics_HandleEquipMedallionsToC();
}

__attribute__((section(".start"))) void Statics_Init(){
    fp_precmd = Statics_Update;
    sOneTime = 0;
    sIsLiveRun = 1;
    //Zero bootstrapper 3/4 data at 0x80700000 in case the bss section of some
    //static code ends up there and needs to assume it's zeroed (probably won't
    //happen). Bootstrapper 4 is currently 88 bytes plus 4 for address counter.
    bzero((void*)0x80700000, 256);
}

static void* malloc_addr = (void*)0x80410000;

void* Statics_StaticDataMalloc(u32 size){
    void* ret = malloc_addr;
    malloc_addr = (void*)(((u32)malloc_addr + size + 15) & ~15);
    return ret;
}

void Statics_RegisterStaticData(void* ram_addr, s32 type_and_size, 
        s32 data1, s32 data2){
    u32 size = type_and_size & 0x00FFFFFF;
    u8 type = type_and_size >> 24;
    if(sIsLiveRun){
        Debugger_Printf("Registering %08X size %d type %d", ram_addr, size, type);
    }
    if(type == 0){
        Statics_AnimeRegisterStaticData(ram_addr);
    }else if(type >= 1 && type <= 3){
        Statics_AudioRegisterStaticData(ram_addr, size, type, data1, data2);
    }
}

//Data here is the four parameters to RegisterInjectedFile
#define MAX_STATICDATA 32
static s32 romhackFileInfo[4*MAX_STATICDATA] = { 
    0xDEADBEEF, 0x04206969, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1
};

void Statics_RomhackLoadAll(){
    for(s32 i=0; i<MAX_STATICDATA; ++i){
        s32 addr = romhackFileInfo[4*i];
        if(addr == 0) break;
        s32 type_and_size = romhackFileInfo[4*i+1];
        u32 size = type_and_size & 0x00FFFFFF;
        void* target = Statics_StaticDataMalloc(size);
        DmaRequest req;
        req.vromAddr = addr;
        req.dramAddr = target;
        req.size = size;
        req.filename = NULL;
        req.line = 0;
        req.unk_14 = 0;
        req.notifyQueue = NULL;
        DmaMgr_ProcessMsg(&req);
        Statics_RegisterStaticData(target, type_and_size, 
            romhackFileInfo[4*i+2], romhackFileInfo[4*i+3]);
    }
}

void Statics_TimeTravel(){
    //Don't time travel if playing Song of Time at ocarina prompt
    //unk_E3EE == ocarina_mode == 0x104C6 == unk_15_2[0] except u16 not char
    //unk_E3F0 == ocarina_no == 0x104C8 == unk_15_2[2] except u16
    //unk_E40E == 0x104E6 == unk_104E4[2] except s16
    //if(*((u16*)&(gGlobalContext.unk_15_2[0])) >= 2) return;
    if(gGlobalContext.sceneNum == 0x43) return; //in Temple of Time
    //Time travel
    gGlobalContext.linkAgeOnLoad = gSaveContext.linkAge ^ 1;
    //gGlobalContext.unk_1D_ = 1; //unk_11DE9 not sure? next variable after link_age
    gSaveContext.respawnFlag = -2;
    gGlobalContext.sceneLoadFlag = 0x14;
    gGlobalContext.nextEntranceIndex = gSaveContext.entranceIndex;
    //gSaveContext.next_day_time = gSaveContext.day_time;
    gGlobalContext.fadeTransition = 0x2C;
    gSaveContext.nextTransition = 5;
    /*
    Audio_FadeOut(30);
    gSaveContext.seq_index = 0xFF;
    gSaveContext.night_seq_index = 0xFF;
    */
}
