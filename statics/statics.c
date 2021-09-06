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
#include "ossan_related.h"
#include "../scene/TriforceRoom/TriforceRoom_scene.h"

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
    gSaveContext.inf_table    [0x0] |= 1 << 0x0; //Greeted by Saria
    */
    gSaveContext.eventChkInf[0x9] |= 0xF; //Rescued carpenters (not get arrested by Gerudos)
    gSaveContext.eventChkInf[0xA] |= 0x0011; //Entered Hyrule Field and Zora's Domain
    gSaveContext.eventChkInf[0xB] |= 0x010C; //Entered Gerudo Valley, Gerudo's Fortress, Desert Colossus
    gSaveContext.eventChkInf[0xC] |= 0x0002; //Spoke to Saria on Lost Woods Bridge
    gSaveContext.itemGetInf[0x2] |= 0x0478; //Obtained Mask of Truth, all trading masks
    gSaveContext.itemGetInf[0x3] |= 0x8F00; //Obtained Mask of Truth, sold all masks
    //TODO TESTING
    LONGOFTIME_VAR |= LONGOFTIME_BIT;
    WORKING_BUNNYHOOD_VAR |= WORKING_BUNNYHOOD_BIT;
    OVERTUREOFSAGES_VAR |= OVERTUREOFSAGES_BIT;
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

extern void* DemoTerminatorTable[];
extern void DemoTerminatorReturn();
#define TERMINATOR_RETURN asm(".set noat\n .set noreorder\nj DemoTerminatorReturn\nnop\n.set at\n .set reorder")

void Statics_TerminatorNabooruToDesertColossus(){
    //gGlobalContext.nextEntranceIndex = 0x0127;
    gGlobalContext.sceneLoadFlag = 0x14;
    //gSaveContext.cutsceneIndex = 0xFFF0;
    gGlobalContext.fadeTransition = 3;
    TERMINATOR_RETURN;
}

void Statics_TerminatorReturnToNabooru(){
    gGlobalContext.nextEntranceIndex = 0x04A7;
    gGlobalContext.sceneLoadFlag = 0x14;
    gSaveContext.cutsceneIndex = 0;
    gGlobalContext.fadeTransition = 3;
    TERMINATOR_RETURN;
}

void Statics_TerminatorTriforceToEnding(){
    gGlobalContext.nextEntranceIndex = 0x03FC;
    gGlobalContext.sceneLoadFlag = 0x14;
    gSaveContext.cutsceneIndex = 0;
    gGlobalContext.fadeTransition = 3;
    TERMINATOR_RETURN;
}

#define NUM_PATCH_TERMINATOR 3
static const struct { u8 index; void (*function)(); } DemoTerminatorPatchTable[NUM_PATCH_TERMINATOR] = {
    {0x4F, Statics_TerminatorNabooruToDesertColossus},
    {0x50, Statics_TerminatorReturnToNabooru},
    {0x51, Statics_TerminatorTriforceToEnding},
};

void Statics_PatchDemoTerminator(){
    for(int i=0; i<NUM_PATCH_TERMINATOR; ++i){
        //Jump table starts at 1
        DemoTerminatorTable[DemoTerminatorPatchTable[i].index - 1] = 
            (void*)DemoTerminatorPatchTable[i].function;
    }
}

void PatchEntranceTable4(u16 entryIdx, const EntranceTableEntry *contents)
{
    gFakeEntranceTable[entryIdx+0] = *contents;
    gFakeEntranceTable[entryIdx+1] = *contents;
    gFakeEntranceTable[entryIdx+2] = *contents;
    gFakeEntranceTable[entryIdx+3] = *contents;
}

void Statics_PatchRoutingToSages(){
    //Bolero of Fire to Death Mountain Crater -> Overture of Sages to Chamber of the Sages
    static const EntranceTableEntry bolero_to_crater_entry = {
        .scene = SCENE_KENJYANOMA,
        .spawn = 0, .keepMusic = 0, .titleCard = 1, .transitionIn = 7, .transitionOut = 7
    };
    PatchEntranceTable4(0x04F6, &bolero_to_crater_entry);
}

void Statics_SetUpRouting(){
    //Gerudo's Fortress to Thieves' Hideout -> scene not changed, but disabled title card
    static const EntranceTableEntry return_to_nabooru_entry = {
        .scene = SCENE_GERUDOWAY, 
        .spawn = 8, .keepMusic = 0, .titleCard = 0, .transitionIn = 5, .transitionOut = 5
    };
    PatchEntranceTable4(0x04A7, &return_to_nabooru_entry);
    //Zora's Domain to Lake Hylia -> Zora's Domain to Unicorn Fountain
    static const EntranceTableEntry zoras_to_lake_entry = {
        .scene = SCENE_UNICORNFOUNTAIN, 
        .spawn = 0, .keepMusic = 0, .titleCard = 1, .transitionIn = 4, .transitionOut = 4
    };
    PatchEntranceTable4(0x0560, &zoras_to_lake_entry);
    //Lake Hylia to Zora's Domain -> scene not changed, but transition changed
    //Used for Unicorn Fountain to Zora's Domain
    static const EntranceTableEntry lake_to_zoras_entry = {
        .scene = SCENE_SPOT06, 
        .spawn = 4, .keepMusic = 0, .titleCard = 1, .transitionIn = 4, .transitionOut = 4
    };
    PatchEntranceTable4(0x0328, &lake_to_zoras_entry);
    //TODO edit Zora's spawn location to be in front of the exit
    //Kakariko Village to Granny's Potion Shop -> Kakariko Village to Kakariko Village turnaround
    static const EntranceTableEntry kakariko_to_granny_entry = {
        .scene = SCENE_SPOT01, 
        .spawn = 7, .keepMusic = 1, .titleCard = 0, .transitionIn = 0x20, .transitionOut = 0x20
    };
    PatchEntranceTable4(0x0072, &kakariko_to_granny_entry);
    if((OVERTUREOFSAGES_VAR & OVERTUREOFSAGES_BIT)){
        Statics_PatchRoutingToSages();
    }
    //Granny's Potion Shop to Kakariko Village -> Chamber of the Sages to Triforce Room
    static const EntranceTableEntry granny_to_kakariko_entry = {
        .scene = SCENE_TRIFORCEROOM,
        .spawn = 0, .keepMusic = 0, .titleCard = 0, .transitionIn = 1, .transitionOut = 2
    };
    PatchEntranceTable4(0x034D, &granny_to_kakariko_entry);
    static const EntranceCutsceneTableEntry spirit_boss_entry = {
        .entrance = 0x034D, .age = 2, .eventChkFlag = TRIFORCE_ROOM_ENTRANCE_CS_EVENTCHKFLAG, 
        .segAddr = TriforceRoom_scene_header00_cutscene
    };
    gEntranceCutsceneTable[30] = spirit_boss_entry;
    //Goron City to Goron Shop -> Goron City to Goron City turnaround
    static const EntranceTableEntry gcity_to_gshop_entry = {
        .scene = SCENE_SPOT18,
        .spawn = 2, .keepMusic = 1, .titleCard = 0, .transitionIn = 5, .transitionOut = 5
    };
    PatchEntranceTable4(0x037C, &gcity_to_gshop_entry);
    //Goron Shop to Goron City -> Triforce Room to Ending
    static const EntranceTableEntry gshop_to_gcity_entry = {
        .scene = SCENE_ENDING,
        .spawn = 0, .keepMusic = 0, .titleCard = 0, .transitionIn = 7, .transitionOut = 7
    };
    PatchEntranceTable4(0x03FC, &gshop_to_gcity_entry);
    //Graveyard to Dampe's Hut -> Graveyard to Graveyard turnaround
    static const EntranceTableEntry graveyard_to_hut_entry = {
        .scene = SCENE_SPOT02,
        .spawn = 2, .keepMusic = 1, .titleCard = 0, .transitionIn = 5, .transitionOut = 5
    };
    PatchEntranceTable4(0x030D, &graveyard_to_hut_entry);
}

void Statics_RomhackLoadAll();

void Statics_OneTimeRomhackOnly(){
    Statics_RomhackLoadAll();
}

void Statics_OneTime(){
    Statics_SetGameState();
	Statics_InterfaceCodePatches();
    Statics_MessageCodePatches();
    Statics_AnimeCodePatches(sIsLiveRun);
    Statics_OcarinaCodePatches();
    Statics_AudioCodePatches(sIsLiveRun);
    Statics_GfxCodePatches();
    Statics_PatchDemoTerminator();
    Statics_SetUpRouting();
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
    const float radius = 80.0f;
    Player *player = PLAYER;
    if(gGlobalContext.sceneNum != 0x5B){ //not in Lost Woods
        if(sWoodsState == 1 && sWoodsCount < 4){
             if(sWoodsTarget == sWoodsPath[sWoodsCount]){
                 ++sWoodsCount;
             }else{
                 sWoodsCount = 0;
             }
             //if(sIsLiveRun) Debugger_Printf("sWoodsCount %d", sWoodsCount);
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
            BETAKOKIRI_SPAWNED_VAR |= BETAKOKIRI_SPAWNED_BIT;
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
            //Statics_AnimeTest(1);
            //give child an adult item
            //INV_CONTENT(ITEM_TRADE_CHILD) = ITEM_ODD_POTION;
            Statics_SetGameState();
        }else if((CTRLR_PRESS & BTN_DLEFT)){
            //Press L+DL for frog
            func_8010B680(&gGlobalContext, 0x0901, NULL); //textbox_begin
        }else if((CTRLR_PRESS & BTN_DRIGHT)){
            //Press L+DR for....
            //animation test
            //Statics_AnimeTest(0);
            //race test
            gSaveContext.eventInf[1] |= 1;
            gSaveContext.timer2State = -30;
        }else if((CTRLR_PRESS & BTN_DUP)){
            //Kill Link (sorry)
            gSaveContext.health = 0;
        }
    }
}

void Statics_PatchShop(){
    GlobalContext* globalCtx = &gGlobalContext;
    if(globalCtx->sceneNum != SCENE_SHOP1) return;
    //Get actor and overlay
    Actor* ossanActor = globalCtx->actorCtx.actorLists[ACTORCAT_NPC].head;
    while(ossanActor != NULL){
        if(ossanActor->id == ACTOR_EN_OSSAN) break;
        ossanActor = ossanActor->next;
    }
    if(ossanActor == NULL) return;
    EnOssan* ossan = (EnOssan*)ossanActor;
    void* ossanOverlay = gActorOverlayTable[ACTOR_EN_OSSAN].loadedRamAddr;
    if(ossanOverlay == NULL) return;
    //Check logic
    if(!(LOOKING_FOR_BUTTERFLY_VAR & LOOKING_FOR_BUTTERFLY_BIT)) return;
    if(globalCtx->msgCtx.unk_E2F8 == 0x009C){ //textId
        SHOP_HAS_BUTTERFLY_VAR |= SHOP_HAS_BUTTERFLY_BIT;
    }
    if(!(SHOP_HAS_BUTTERFLY_VAR & SHOP_HAS_BUTTERFLY_BIT)) return;
    //Change store item
    ShopItem* sShopkeeperStores = (ShopItem*)(ossanOverlay + 0x58F0);
    ShopItem* butterflyEntry = &sShopkeeperStores[4*8+3];
    if(butterflyEntry->shopItemIndex != SI_BUTTERFLY){
        if(ossan->shelfSlots[3] == NULL){
            //Link actor update ran before ossan actor init
            butterflyEntry->shopItemIndex = SI_BUTTERFLY;
        }else if(ossan->shelves != NULL){
            //Make sure shelves are loaded, otherwise don't do this until next frame
            butterflyEntry->shopItemIndex = SI_BUTTERFLY;
            Actor_Kill(&ossan->shelfSlots[3]->actor);
            ossan->shelfSlots[3] = (EnGirlA*)Actor_Spawn(
                &globalCtx->actorCtx, globalCtx, ACTOR_EN_GIRLA,
                ossan->shelves->actor.world.pos.x + butterflyEntry->xOffset,
                ossan->shelves->actor.world.pos.y + butterflyEntry->yOffset,
                ossan->shelves->actor.world.pos.z + butterflyEntry->zOffset,
                ossan->shelves->actor.shape.rot.x,
                ossan->shelves->actor.shape.rot.y + 0xEAAC,
                ossan->shelves->actor.shape.rot.z,
                SI_BUTTERFLY);
        }
    }
}

void Statics_MoveOddPotionToChild(){
    if(gSaveContext.inventory.items[SLOT_TRADE_ADULT] == ITEM_ODD_POTION){
        gSaveContext.inventory.items[SLOT_TRADE_ADULT] = ITEM_NONE;
        gSaveContext.inventory.items[SLOT_TRADE_CHILD] = ITEM_ODD_POTION;
    }
}

void Statics_FixWaterSpawn(){
    InterfaceContext *interfaceCtx = &gGlobalContext.interfaceCtx;
    if(gGlobalContext.sceneNum == SCENE_UNICORNFOUNTAIN){
        interfaceCtx->restrictions.hGauge = interfaceCtx->restrictions.bButton =
        interfaceCtx->restrictions.aButton = interfaceCtx->restrictions.bottles =
        interfaceCtx->restrictions.tradeItems = interfaceCtx->restrictions.hookshot =
        interfaceCtx->restrictions.ocarina = interfaceCtx->restrictions.warpSongs =
        interfaceCtx->restrictions.sunsSong = interfaceCtx->restrictions.farores =
        interfaceCtx->restrictions.dinsNayrus = interfaceCtx->restrictions.all = 0;
    }
}

//static u8 exitOcarinaMode = 0;

void Statics_Player_Update(){
    //Patch overwrote this
    if(PLAYER->unk_A73 != 0) PLAYER->unk_A73--;
    //Custom content
    Statics_TestShortcuts();
    Statics_LostWoods();
    Statics_PatchShop();
    Statics_MoveOddPotionToChild();
    Statics_FixWaterSpawn();
    //
    /*
    if(exitOcarinaMode){
        if(sIsLiveRun) Debugger_Printf("Trying to exit ocarina");
        globalCtx->msgCtx.unk_E3EE = 4; //Link exit ocarina mode
        if(!(PLAYER->stateFlags2 & 0x3800000)) exitOcarinaMode = 0; //Has been exited
    }
    */
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
    //if(sIsLiveRun) Debugger_Printf("Registering %08X size %d type %d", ram_addr, size, type);
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
    if(!(LONGOFTIME_VAR & LONGOFTIME_BIT)) return;
    //Don't time travel if playing Song of Time at ocarina prompt
    //unk_E3EE == ocarina_mode == 0x104C6 == unk_15_2[0] except u16 not char
    //unk_E3F0 == ocarina_no == 0x104C8 == unk_15_2[2] except u16
    //unk_E40E == 0x104E6 == unk_104E4[2] except s16
    //if(*((u16*)&(gGlobalContext.unk_15_2[0])) >= 2) return;
    if(gGlobalContext.sceneNum == SCENE_TOKINOMA || gGlobalContext.sceneNum == SCENE_GERUDOWAY){
        return; //in Temple of Time or Thieves' Hideout
    }
    if((gSaveContext.eventInf[1] & 1)){
        //Timer 2 (Running Man race) is active
        if(LINK_IS_CHILD){
            gSaveContext.timer2Value = -10; //10 seconds to time 0
        }else{
            //gCounterDigit0Tex = 02003040, size of each digit is 0x80
            //Want to stay in bounds in segment 2. Over 1:30 should be plenty of
            //time to get across Hyrule Field, even without the Bunny Hood
            gSaveContext.timer2Value = -96;
        }
    }
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

void Statics_GiveLongOfTime(){
    LONGOFTIME_VAR |= LONGOFTIME_BIT;
    Ocarina_GiveLongOfTime();
}

void Statics_GiveOvertureOfSages(){
    OVERTUREOFSAGES_VAR |= OVERTUREOFSAGES_BIT;
    Ocarina_GiveOvertureOfSages();
    Statics_PatchRoutingToSages();
}

#define WSRSTATE_NOTTRY 0
#define WSRSTATE_SUCCESS 1
#define WSRSTATE_FAILURE 2

static s32 Statics_GetWarpSacredRealmState(){
    GlobalContext *globalCtx = &gGlobalContext;
    if(globalCtx->msgCtx.unk_E3EC != 1) return WSRSTATE_NOTTRY; //Bolero of Fire played
    if(!(OVERTUREOFSAGES_VAR & OVERTUREOFSAGES_BIT)) return WSRSTATE_NOTTRY;
    if(globalCtx->sceneNum != SCENE_TOKINOMA) return WSRSTATE_FAILURE;
    static const Vec3f masterSwordPos = {-1.0f, 68.0f, 0.0f};
    Vec3f playerPos = PLAYER->actor.world.pos;
    float sqDistFromMS = SQ(playerPos.x - masterSwordPos.x) 
        + SQ(playerPos.y - masterSwordPos.y) + SQ(playerPos.z - masterSwordPos.z);
    if(sqDistFromMS > 2500.0f) return WSRSTATE_FAILURE;
    return WSRSTATE_SUCCESS;
}

s32 Statics_CantWarpToSacredRealm(){
    GlobalContext *globalCtx = &gGlobalContext;
    Player *player = PLAYER;
    player->csMode = 0;
    player->stateFlags1 &= ~0x20000000;
    s32 wsrstate = Statics_GetWarpSacredRealmState();
    if(wsrstate != WSRSTATE_FAILURE) return 0;
    func_800ED858(0); //disable ocarina
    globalCtx->msgCtx.unk_E3EE = 4; //Link exit ocarina mode
    Message_Close(globalCtx);
    //exitOcarinaMode = 1;
    /*
    player->prevCsMode = 1;
    player->csMode = 0;
    player->unk_664 = NULL;
    player->stateFlags1 &= ~0x700F8081;
    player->stateFlags2 &= ~0x8082000;
    player->stateFlags3 &= ~0x80;
    globalCtx->mainCamera.unk_14C |= 8;
    */
    //func_8010B680(globalCtx, 0x0D30, NULL); //Message_Start
    return 1;
}

void* Statics_SpawnWarpActor(){
    GlobalContext *globalCtx = &gGlobalContext;
    u16 actor = ACTOR_DEMO_KANKYO;
    u16 params = 0xF;
    if(Statics_GetWarpSacredRealmState() == WSRSTATE_SUCCESS){
        actor = ACTOR_DEMO_EFFECT;
        params = 0xF;
        Flags_SetEnv(globalCtx, 1);
    }
    return Actor_Spawn(&globalCtx->actorCtx, globalCtx, actor, 0.0f, 0.0f, 0.0f, 0, 0, 0, params);
}

void Statics_Ge2DialogueGet(){
    asm(".set noat\n .set noreorder\n"
    "lui   $t0, %hi(gSaveContext)\n"
    "addiu $t1, $t0, %lo(gSaveContext)\n"
    "lbu   $t2, 0x0F24($t1)\n"
    "srl   $t3, $t2, 6\n"
    "addiu $t5, $t3, 0x0B50\n"
    "jr $ra\n"
    "sh    $t5, 0x010E($s0)\n"
    ".set at\n .set reorder");
}

void Statics_Ge2DialogueUpdate(){
    asm(".set noat\n .set noreorder\n"
    "lh    $t6, 0x001C($s0)\n" //what we replaced
    "lui   $t0, %hi(gSaveContext)\n"
    "addiu $t1, $t0, %lo(gSaveContext)\n"
    "lbu   $t2, 0x0F24($t1)\n"
    "addiu $t3, $t2, 0x0040\n"
    "jr $ra\n"
    "sb    $t3, 0x0F24($t1)\n"
    ".set at\n .set reorder");
}
