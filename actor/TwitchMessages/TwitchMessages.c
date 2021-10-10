#include "ootmain.h" 
#include "../../loader/fast_loader/fast_loader.h"

__attribute__((aligned(16))) static const u64 username_font[] = {
    #include "../../textures/username_font.i4.inc"
};

#define UNAME_TEX_COLS 128
#define FRAMES_FADE 20

#define MSG_POS_EXTENT_X 1000.0f
#define MSG_POS_EXTENT_Y 300.0f
#define MSG_POS_EXTENT_Z 300.0f
#define MSG_SCALE 1.5f

static const u16 char_starts[64] = {
    0, 
    //underscore and numbers
    6, 15, 21, 29, 38, 48, 55, 64, 72, 81, 90,
    //uppercase
    100, 109, 119, 128, 136, 144, 154, 164, 168, 175, 184, 191, 203,
    213, 223, 231, 241, 250, 259, 268, 277, 286, 300, 309, 318, 327,
    //lowercase
    335, 343, 351, 359, 367, 372, 380, 388, 391, 396, 404, 408, 420,
    428, 436, 444, 452, 457, 464, 469, 477, 484, 496, 503, 511, 518
};

static const u16 casing_widths[4] = {
    100, 120, 140, 160 //TODO
};

#define EXCLAM_WIDTH 5

static const Color_RGB8 uname_colors[16] = {
    {0x00, 0x00, 0xFF}, //0: Blue
    {0xFF, 0x7F, 0x50}, //1: Coral
    {0x1E, 0x90, 0xFF}, //2: DodgerBlue
    {0x00, 0xFF, 0x7F}, //3: SpringGreen
    {0x9A, 0xCD, 0x32}, //4: YellowGreen
    {0x00, 0x80, 0x00}, //5: Green
    {0xFF, 0x45, 0x00}, //6: OrangeRed
    {0xFF, 0x00, 0x00}, //7: Red
    {0xDA, 0xA5, 0x20}, //8: GoldenRod
    {0xFF, 0x69, 0xB4}, //9: HotPink
    {0x5F, 0x9E, 0xA0}, //A: CadetBlue
    {0x2E, 0x8B, 0x57}, //B: SeaGreen
    {0xD2, 0x69, 0x1E}, //C: Chocolate
    {0x8A, 0x2B, 0xE2}, //D: BlueViolet
    {0xB2, 0x22, 0x22}, //E: Firebrick
    {0xFF, 0xFF, 0xFF}  //F: White
};

#define G_CC_UNAME 0, 0, 0, PRIMITIVE, TEXEL0, 0, PRIMITIVE, 0

static const Gfx uname_setup_dl[] = {
    gsSPLoadGeometryMode(G_ZBUFFER),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_UNAME, G_CC_UNAME),
    gsDPSetOtherMode(G_AD_DISABLE | G_CD_DISABLE | G_CK_NONE | G_TC_FILT
        | G_TF_BILERP | G_TT_NONE | G_TL_TILE | G_TD_CLAMP
        | G_TP_PERSP | G_CYC_1CYCLE | G_PM_NPRIMITIVE,
        G_AC_NONE | G_ZS_PIXEL | 
        AA_EN | Z_CMP | Z_UPD | IM_RD | CVG_DST_CLAMP | ZMODE_OPA | FORCE_BL |
        GBL_c1(G_BL_CLR_IN, G_BL_A_IN, G_BL_CLR_MEM, G_BL_1MA) |
        GBL_c2(G_BL_CLR_IN, G_BL_A_IN, G_BL_CLR_MEM, G_BL_1MA)),
    gsSPEndDisplayList(),
};

#define RAM_END 0x80800000
#define UNAME_TEX_SZ (UNAME_TEX_COLS * sizeof(u64))
#define UNAME_TEX_BEGIN (RAM_END - MAX_TWITCH_MESSAGES * UNAME_TEX_SZ)
#define VTX_EACH_SZ (4 * sizeof(Vtx))
#define VTX_PERMSG_SZ (5 * VTX_EACH_SZ)
#define VTX_BEGIN (UNAME_TEX_BEGIN - MAX_TWITCH_MESSAGES * VTX_PERMSG_SZ)

static inline u64 *GetMessageTexture(u16 m) {
    return (u64*)(UNAME_TEX_BEGIN + m * UNAME_TEX_SZ);
}

static inline Vtx *GetMessageVerts(u16 m) {
    return (Vtx*)(VTX_BEGIN + m * VTX_PERMSG_SZ);
}

static inline void SetupRectangle(Vtx *verts, s16 basex, s16 basey, s16 basez, s16 sx, s16 sy){
    for(s32 i=0; i<4; ++i){
        verts[i].v.ob[0] = basex;
        verts[i].v.ob[1] = basey;
        verts[i].v.ob[2] = basez;
        verts[i].v.tc[0] = -16;
        verts[i].v.tc[1] = -16;
    }
    verts[1].v.ob[0] += sx;
    verts[3].v.ob[0] += sx;
    verts[2].v.ob[1] += sy;
    verts[3].v.ob[1] += sy;
    verts[1].v.tc[1] += sx * 32;
    verts[3].v.tc[1] += sx * 32;
    verts[2].v.tc[0] += sy * 32;
    verts[3].v.tc[0] += sy * 32;
}

static void SetUpMessage(u16 m, TwitchMessage *msg) {
    msg->rgb = uname_colors[msg->flags & 0xF];
    msg->a = 0xFF;
    
    u64 *tex = GetMessageTexture(m);
    s32 byte = 0;
    s32 ch = 0;
    s32 texcol = 0;
    while(byte < 19){
        u32 temp = msg->uname_encoded[byte++];
        temp |= (u32)msg->uname_encoded[byte++] << 8; //will overread on the last
        temp |= (u32)msg->uname_encoded[byte++] << 16; //but that's okay
        for(s32 ingrp=0; ingrp<4; ++ingrp){
            u8 c = temp & 0x3F;
            temp >>= 6;
            if(ch >= 25) break;
            ++ch;
            if(c == 0){
                //end of message
                byte = 100;
                break;
            }
            --c; //0-62
            //Copy character to texture.
            //Texture is stored flipped so the bytes of each column are consecutive.
            //Conveniently one column is one u64.
            u16 c_start = char_starts[c];
            u16 c_end = char_starts[c+1];
            u16 cols = c_end - c_start;
            if(texcol + cols > UNAME_TEX_COLS){
                byte = 100; //exit outer loop too
                break;
            }
            bcopy(&username_font[c_start], &tex[texcol], cols * sizeof(u64));
            texcol += cols;
        }
    }
    if(texcol < UNAME_TEX_COLS){
        bzero(&tex[texcol], (UNAME_TEX_COLS-texcol) * sizeof(u64));
    }
    
    Vtx *verts = GetMessageVerts(m);
    s16 basex = (Rand_ZeroOne() - 0.5f) * MSG_POS_EXTENT_X;
    s16 basey = (Rand_ZeroOne() - 0.5f) * MSG_POS_EXTENT_Y;
    s16 basez = (Rand_ZeroOne() - 0.5f) * MSG_POS_EXTENT_Z;
    
    s16 x = 0;
    if((msg->badges & 0x1F)){
        SetupRectangle(verts, basex + x, basey, basez, 16, 16);
        x += 18;
    }
    if((msg->badges & 0x60)){
        SetupRectangle(verts + 4, basex + x, basey, basez, 16, 16);
        x += 18;
    }
    SetupRectangle(verts + 8, basex + x, basey, basez, 128, 16);
    x += texcol;
    s16 w = casing_widths[(msg->flags & 0x30) >> 4];
    SetupRectangle(verts + 12, basex + x, basey, basez, w, 16);
    x += w;
    u8 e = (msg->flags & 0xC0) >> 6;
    if(e){
        SetupRectangle(verts + 16, basex + x, basey, basez, e * EXCLAM_WIDTH, 16);
    }
}

typedef struct {
    Actor actor;
} Entity;

static void init(Entity *en, GlobalContext *globalCtx) {
    bzero((void*)VTX_BEGIN, UNAME_TEX_BEGIN - VTX_BEGIN);
}

static void destroy(Entity *en, GlobalContext *globalCtx) {}

static void update(Entity *en, GlobalContext *globalCtx){
    for(s32 m=0; m<MAX_TWITCH_MESSAGES; ++m){
        TwitchMessage *msg = &twitch_msg_buf[m];
        if(msg->timer == 0xFF){
            msg->timer = 1;
            SetUpMessage(m, msg);
        }else if(msg->timer != 0){
            ++msg->timer;
            if(msg->timer >= FRAMES_FADE) msg->timer = 0;
            msg->a = ((float)(FRAMES_FADE - msg->timer) / (float)FRAMES_FADE) * 255.0f;
        }
    }
}


static void draw(Entity *en, GlobalContext *globalCtx) {
    Matrix_Translate(en->actor.world.pos.x, en->actor.world.pos.y,
        en->actor.world.pos.z, MTXMODE_NEW);
    Matrix_RotateRPY(0, en->actor.shape.rot.y + 0x8000, 0, MTXMODE_APPLY);
    Matrix_RotateRPY(0, 0, 0x8000, MTXMODE_APPLY);
    Matrix_Scale(MSG_SCALE, MSG_SCALE, MSG_SCALE, MTXMODE_APPLY);
    gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx, "", 0),
        G_MTX_MODELVIEW | G_MTX_LOAD);
    //Cull messages not on screen
    for(s32 m=0; m<MAX_TWITCH_MESSAGES; ++m){
        TwitchMessage *msg = &twitch_msg_buf[m];
        if(msg->timer == 0 || msg->timer == 0xFF){
            msg->culled = 1;
            continue;
        }
        msg->culled = 0;
        /*
        Vtx *verts = GetMessageVerts(m);
        Vec3f pos, screenpos; float screenscale;
        pos.x = verts[0].v.ob[0]; pos.y = verts[0].v.ob[1]; pos.z = verts[0].v.ob[2];
        Math_GetProjectionPos(globalCtx, &pos, &screenpos, &screenscale);
        msg->culled = (screenpos.z <= 0.0f 
            || fabsf(screenpos.x * screenscale) >= 1.2f
            || fabsf(screenpos.y * screenscale) >= 1.2f);
        */
    }
    //Usernames
    gSPDisplayList(POLY_OPA_DISP++, uname_setup_dl);
    for(s32 m=0; m<MAX_TWITCH_MESSAGES; ++m){
        TwitchMessage *msg = &twitch_msg_buf[m];
        if(msg->culled) continue;
        gDPSetPrimColor(POLY_OPA_DISP++, 0, 0, msg->rgb.r, msg->rgb.g, msg->rgb.b, msg->a);
        gDPLoadMultiBlock_4b(POLY_OPA_DISP++, GetMessageTexture(m),
            0, G_TX_RENDERTILE, G_IM_FMT_I, 16, UNAME_TEX_COLS, 0,
            G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, 
            G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
        gSPVertex(POLY_OPA_DISP++, GetMessageVerts(m) + 8, 4, 0);
        gSP2Triangles(POLY_OPA_DISP++, 0, 1, 2, 0, 2, 1, 3, 0);
    }
}

const ActorInitExplPad init_vars = {
	.id = 0xDEAD, .padding = 0xBEEF, // <-- magic values, do not change
	.category = ACTORCAT_BG,
	.flags = 0x00000030,
	.objectId = OBJECT_GAMEPLAY_KEEP,
	.instanceSize = sizeof(Entity),
	.init = (ActorFunc)init,
	.destroy = (ActorFunc)destroy,
	.update = (ActorFunc)update,
	.draw = (ActorFunc)draw
};
