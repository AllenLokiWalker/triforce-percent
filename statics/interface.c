#include "ootmain.h"
#include "interface.h"

extern void Construct_Icon_Start();
extern void Construct_Icon_Target();

extern void InterfaceEffectTex_Start();
extern void InterfaceEffectTex_Target();

extern void KaleidoScope_UpdateEquipAnim(GlobalContext *globalCtx);

extern s16 sEquipAnimState;
extern s16 sEquipAnimTimer;
extern s16 sEquipAnimNumFrames;

extern Vec3f sSoundParam1;
extern float sSoundParam34;
extern float sSoundParam5;

extern u8 sSubscreenButtonStates[30];

static const u64 TexButterfly[] = {
    #include "../textures/butterfly_bottle.rgba32.inc"
};

void Patched_LoadItemIconMain(GlobalContext *globalCtx, u16 button, u16 num){
    InterfaceContext *interfaceCtx = (InterfaceContext*)&globalCtx->interfaceCtx;
    u32 rom = 0x007BD000; //icon_item_static
    u8 *ram = interfaceCtx->iconItemSegment + button * 0x1000;
    u32 *image = (u32*)ram;
    u32 size = 0x1000;
    u8 item = gSaveContext.equips.buttonItems[button];
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
    
    if(item == ITEM_BIG_POE){
        bcopy(TexButterfly, ram, size);
    }else if(num == 0){
        DmaMgr_SendRequest1(ram, rom, size);
    }else{
        DmaRequest *request = ((num == 1) ? &interfaceCtx->dmaRequest_160 : &interfaceCtx->dmaRequest_180);
        osCreateMesgQueue(&interfaceCtx->loadQueue, &interfaceCtx->loadMsg, OS_MESG_BLOCK);
        DmaMgr_SendRequest2(request, (u32)ram, rom, size, 0, &interfaceCtx->loadQueue, 0);
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

void Patched_LoadItemIcon1(GlobalContext *globalCtx, u16 button){
    Patched_LoadItemIconMain(globalCtx, button, 1);
}

void Patched_LoadItemIcon2(GlobalContext *globalCtx, u16 button){
    Patched_LoadItemIconMain(globalCtx, button, 2);
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
    dl[0x1] = (s32)gItemIcons[item];
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
    PauseContext *pauseCtx = &gGlobalContext.pauseCtx;
    if(!pauseCtx->state) return;
    
    //Enable C buttons on Quest Status subscreen
	//Have to set once every time the pause menu overlay gets reloaded
	if(pauseCtx->state >= 4 && pauseCtx->state <= 11 && sSubscreenButtonStates[3*5+1] == 0xFF){
		sSubscreenButtonStates[3*5+1] = 0;
		sSubscreenButtonStates[3*5+2] = 0;
		sSubscreenButtonStates[3*5+3] = 0;
	}
    
    if(pauseCtx->debugState || pauseCtx->pageIndex != 2) return;
    
    u8 item = pauseCtx->cursorItem[2];
    if(item >= 0x66 && item <= 0x79 && //actually has item, not empty
            (CTRLR_PRESS & (BTN_CLEFT | BTN_CDOWN | BTN_CRIGHT))){
        //Equipping a Quest Status item
        if((CTRLR_PRESS & BTN_CLEFT)){
            pauseCtx->equipTargetCBtn = 0;
        }else if((CTRLR_PRESS & BTN_CDOWN)){
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
        Audio_PlaySoundGeneral(NA_SE_SY_DECIDE,
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
