#include "interface.h"
#include "statics_int.h"

typedef struct {
    u8 dummy[0x20];
} DmaRequest;

typedef struct {
    u8 dummy1[0x138];
    /* 0x0138 */ u8*    icon_itemSegment;
    u8 dummy2[0x160 - 0x13C];
    /* 0x0160 */ DmaRequest dmaRequest_160;
    /* 0x0180 */ DmaRequest dmaRequest_180;
    /* 0x01A0 */ char   unk_1A0[0x20];
    /* 0x01C0 */ OSMesgQueue loadQueue;
    /* 0x01D8 */ OSMesg loadMsg;
    u8 dummy3[0x270 - 0x1DC];
} InterfaceContext; // size = 0x270

extern void DmaMgr_SendRequest2(DmaRequest *req, u8 *dest, u32 rom, u32 size, 
    s32 unk, OSMesgQueue *queue, s32 unk2);

extern void Interface_LoadItemIcon1(z64_global_t *globalCtx, u16 button);
extern void Interface_LoadItemIcon2(z64_global_t *globalCtx, u16 button);

extern void Construct_Icon_Start();
extern void Construct_Icon_Target();

typedef struct {
    /* 0x0000 */ u8 dummy[0x128];
    /* 0x0128 */ u8*    unk_128;
    /* 0x012C */ u8*    unk_12C;
    /* 0x0130 */ u8*    unk_130;
    /* 0x0134 */ u8*    unk_134;
    /* 0x0138 */ u8*    unk_138;
    /* 0x013C */ u8*    unk_13C;
    /* 0x0140 */ char   unk_140[0x04];
    /* 0x0144 */ Vtx*   vtx_144;
    /* 0x0148 */ Vtx*   vtx_148;
    /* 0x014C */ Vtx*   vtx_14C;
    /* 0x0150 */ Vtx*   vtx_150;
    /* 0x0154 */ char   unk_154[0x04];
    /* 0x0158 */ Vtx*   vtx_158;
    /* 0x015C */ char   unk_15C[0x0C];
    /* 0x0168 */ Vtx*   vtx_168;
    /* 0x016C */ Vtx*   vtx_16C;
    /* 0x0170 */ char   unk_170[0x24];
    /* 0x0194 */ u8*    unk_194;
    /* 0x0198 */ char   unk_198[0x20];
    /* 0x01B8 */ OSMesgQueue loadQueue;
    /* 0x01D0 */ OSMesg loadMsg;
    /* 0x01D4 */ u16    state;
    /* 0x01D6 */ u16    flag;
    /* 0x01D8 */ float  eye[3];
    /* 0x01E4 */ u16    unk_1E4;
    /* 0x01E6 */ u16    mode;
    /* 0x01E8 */ u16    kscpPos; // "kscp_pos"; basically the page index (0=SELECT ITEM; 1=MAP; 2=QUEST STATUS; 3=EQUIPMENT)
    /* 0x01EA */ u16    unk_1EA;
    /* 0x01EC */ u16    unk_1EC;
    /* 0x01EE */ char   unk_1EE[0x02];
    /* 0x01F0 */ f32    unk_1F0;
    /* 0x01F4 */ f32    unk_1F4;
    /* 0x01F8 */ f32    unk_1F8;
    /* 0x01FC */ f32    unk_1FC;
    /* 0x0200 */ f32    unk_200;
    /* 0x0204 */ f32    unk_204;
    /* 0x0208 */ u16    unk_208;
    /* 0x020A */ char   unk_20A[0x0A];
    /* 0x0214 */ s16    stickRelX;
    /* 0x0216 */ s16    stickRelY;
    /* 0x0218 */ s16    cursorSlot[5]; //"cursor"
    /* 0x0222 */ s16    cursorX[5]; //"cur_xpt"
    /* 0x022C */ s16    cursorY[5]; //"cur_ypt"
    /* 0x0236 */ s16    unk_236;
    /* 0x0238 */ s16    cursorSpecialPos; //"key_angle"
    /* 0x023A */ s16    unk_23A;
    /* 0x023C */ u16    unk_23C;
    /* 0x023E */ u16    cursorItem[4];
    /* 0x0246 */ u16    cursorSlotCopy[4];
    /* 0x024E */ u16    equipTargetItem;
    /* 0x0250 */ u16    equipTargetSlot;
    /* 0x0252 */ u16    equipTargetCBtn;
    /* 0x0254 */ s16    equipAnimX;
    /* 0x0256 */ s16    equipAnimY;
    /* 0x0258 */ s16    equipAnimAlpha;
    /* 0x025A */ s16    unk_25A;
    /* 0x025C */ u16    unk_25C;
    /* 0x025E */ u16    unk_25E;
    /* 0x0260 */ s16    unk_260;
    /* 0x0262 */ s16    unk_262;
    /* 0x0264 */ s16    unk_264;
    /* 0x0266 */ u8     unk_266[20];
    /* 0x027A */ u8     unk_27A;
    /* 0x027C    SkelAnime skelAnime; */
} PauseContext; // size = 0x2C0

extern s16 sEquipAnimState;
extern s16 sEquipAnimTimer;
extern s16 sEquipAnimNumFrames;

extern u32 sSoundParam1;
extern float sSoundParam34;
extern float sSoundParam5;

extern void Audio_PlaySoundGeneral(u16 sfxId, void* a1, u8 a2, void* a3, void* a4, void* a5);
//extern void KaleidoScope_UpdateEquipAnim(z64_global_t *global);

extern u8 sSubscreenButtonStates[30];

extern s32 gItemIcons[100]; //size actually unknown, doesn't matter

extern void InterfaceEffectTex_Start();
extern void InterfaceEffectTex_Target();


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

void Statics_InterfaceCodePatches(){
    //
    *( (u32*)Interface_LoadItemIcon1   ) = JUMPINSTR(Patched_LoadItemIcon1);
	*(((u32*)Interface_LoadItemIcon1)+1) = 0;
    *( (u32*)Interface_LoadItemIcon2   ) = JUMPINSTR(Patched_LoadItemIcon2);
	*(((u32*)Interface_LoadItemIcon2)+1) = 0;
    //At beginning of z_construct item icon loading, jal Patched_LoadAllItemIcons
    *( (u32*)Construct_Icon_Start   ) = JALINSTR(Patched_LoadAllItemIcons);
	*(((u32*)Construct_Icon_Start)+1) = 0;
    //After returning, jump to end of icon loading
    *(((u32*)Construct_Icon_Start)+2) = JUMPINSTR(Construct_Icon_Target);
    *(((u32*)Construct_Icon_Start)+3) = 0;
    //
    //Equip item animation patch
    *( (u32*)InterfaceEffectTex_Start   ) = JALINSTR(Patched_EquipEffectTexLoad);
    *(((u32*)InterfaceEffectTex_Start)+1) = 0x8E8402B0; //lw a0, 0x02B0(s4)
    *(((u32*)InterfaceEffectTex_Start)+2) = JUMPINSTR(InterfaceEffectTex_Target);
    *(((u32*)InterfaceEffectTex_Start)+3) = 0xAE8202B0; //sw v0, 0x02B0(s4)
}
