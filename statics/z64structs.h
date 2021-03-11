#ifndef __TF_Z64STRUCTS_H__
#define __TF_Z64STRUCTS_H__

#include <z64ovl/oot/u10.h>
#include <z64ovl/z64ovl_helpers.h>

extern z64_global_t gGlobalContext;
extern z64_save_context_t gSaveContext;

#define CTRLR_RAW gGlobalContext.common.input[0].raw
#define CTRLR_PRESS gGlobalContext.common.input[0].pad_pressed
#define PLAYER ((z64_player_t*)gGlobalContext.actor_ctxt.actor_list[OVLTYPE_PLAYER].first)

#define JUMPINSTR(func) (0x08000000 | ((((u32)func)>>2) & 0x03FFFFFF))
#define JALINSTR(func)  (0x0C000000 | ((((u32)func)>>2) & 0x03FFFFFF))


typedef struct {
    /* 0x00 */ u32      vromAddr; // VROM address (source)
    /* 0x04 */ void*    dramAddr; // DRAM address (destination)
    /* 0x08 */ u32      size;     // File Transfer size
    /* 0x0C */ const char* filename; // Filename for debugging
    /* 0x10 */ s32      line;     // Line for debugging
    /* 0x14 */ s32      unk_14;
    /* 0x18 */ OSMesgQueue* notifyQueue; // Message queue for the notification message
    /* 0x1C */ OSMesg   notifyMsg;       // Completion notification message
} DmaRequest; // size = 0x20


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
// z64_if_ctxt_t is missing all the OS/memory structs


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
// z64_pause_ctxt_t is missing stuff


typedef enum {
    BOX_BLACK,
    BOX_WOODEN,
    BOX_BLUE,
    BOX_OCARINA,
    BOX_NONE_BOTTOM,
    BOX_NONE_NO_SHADOW,
    BOX_CREDITS = 11
} MessageBoxType;

typedef enum {
    POS_VARIABLE,
    POS_TOP,
    POS_BOTTOM,
    POS_MIDDLE
} MessageBoxPosition;

typedef struct {
    /* 0x0000 */ u32    msgOffset;
    /* 0x0004 */ u32    msgLength;
    /* 0x0008 */ u8     xy;
    /* 0x0009 */ char   unk_C[0xDC88 - 0x0009];
    /* 0xDC88 */ char   msgBuf[1064]; // size unconfirmed
} Font;

typedef struct {
    u16 textId;
    u8 typePos;
    const char* segment;
} MessageTableEntry;


typedef struct {
    /* 0x00 */ u32 vromStart;
    /* 0x04 */ u32 vromEnd;
    /* 0x08 */ void* vramStart;
    /* 0x0C */ void* vramEnd;
    /* 0x10 */ void* loadedRamAddr; // original name: "allocp"
    /* 0x14 */ void* initInfo;
    /* 0x18 */ char* name;
    /* 0x1C */ u16 allocType;
    /* 0x1E */ s8 nbLoaded; // original name: "clients"
} ActorOverlay; // size = 0x20


#endif //__TF_Z64STRUCTS_H__
