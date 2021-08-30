#define _Z64HDR_DISABLE_FABSF_ASM_ 1
#include "ootmain.h" 

Gfx butterflypatch[] = {
    gsSPTexture(0x8000, 0x7A00, 0, G_TX_RENDERTILE, G_ON),
    gsDPLoadTextureBlock(0x06000000, G_IM_FMT_IA, G_IM_SIZ_8b, 
        24, 48, 0, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP, 
        5, 6,
        G_TX_NOLOD, G_TX_NOLOD),
};
