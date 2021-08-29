#ifndef _OOTMAIN_H_INCLUDED_
#define _OOTMAIN_H_INCLUDED_
#include "z64hdr/oot_10.h"
#include "audiobank.h"

//Structs

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
    u16 textId;
    u8 typePos;
    const char* segment;
} MessageTableEntry;

// Members

#define CTRLR_RAW gGlobalContext.state.input[0].cur.button
#define CTRLR_PRESS gGlobalContext.state.input[0].press.button
#undef PLAYER
#define PLAYER ((Player*)gGlobalContext.actorCtx.actorLists[ACTORCAT_PLAYER].head)

#define JUMPINSTR(func) (0x08000000 | ((((u32)func)>>2) & 0x03FFFFFF))
#define JALINSTR(func)  (0x0C000000 | ((((u32)func)>>2) & 0x03FFFFFF))

#undef POLY_OPA_DISP
#undef POLY_XLU_DISP
#undef OVERLAY_DISP
#define POLY_OPA_DISP gGlobalContext.state.gfxCtx->polyOpa.p
#define POLY_XLU_DISP gGlobalContext.state.gfxCtx->polyXlu.p
#define OVERLAY_DISP gGlobalContext.state.gfxCtx->overlay.p

#define CHECK_NPC_ACTION(slot, num) \
	(globalCtx->csCtx.state != 0) \
	&& (globalCtx->csCtx.npcActions[slot] != NULL) \
	&& (globalCtx->csCtx.npcActions[slot]->action == num)

extern Gfx gActorXluSetup[3]; //D_80116280

#define WORKING_BUNNYHOOD_VAR gSaveContext.itemGetInf[0x2] //0x0EF5 bit 1<<0
#define WORKING_BUNNYHOOD_BIT 0x0001
#define WORKING_GERUDOMASK_VAR gSaveContext.itemGetInf[0x2] //0x0EF5 bit 1<<1
#define WORKING_GERUDOMASK_BIT 0x0002
#define SKULLKID_WILL_UPGRADE_VAR gSaveContext.itemGetInf[0x2] //0x0EF5 bit 1<<2
#define SKULLKID_WILL_UPGRADE_BIT 0x0004
#define NABOORU_CONTINUE_VAR gSaveContext.infTable[0x16] //0x0F24 bit 1<<0
#define NABOORU_CONTINUE_BIT 0x0100
#define NABOORU_DONE_VAR gSaveContext.infTable[0x16] //0x0F24 bit 1<<1
#define NABOORU_DONE_BIT 0x0200
//Using 0xF24 bits 1<<6 and 1<<7 for ge2 dialogue chooser

#define Actor_IsTalking func_8002F194
#define Actor_RequestToTalk func_8002F2F4
#define Actor_RequestToTalkInRange func_8002F2CC
#define Actor_PickUp func_8002F434
#define Message_ShouldAdvance func_80106BC8
#define MESSAGE_START func_8010B680(globalCtx, en->actor.textId, NULL)
#define MESSAGE_CONTINUE func_8010B720(globalCtx, en->actor.textId)
#define MESSAGE_ADVANCE_TYPE(n) ((func_8010BDBC(&globalCtx->msgCtx) == n) && (Message_ShouldAdvance(globalCtx) != 0))
#define MESSAGE_ADVANCE_EVENT MESSAGE_ADVANCE_TYPE(5)
#define MESSAGE_ADVANCE_CHOICE MESSAGE_ADVANCE_TYPE(4)
#define MESSAGE_ADVANCE_END MESSAGE_ADVANCE_TYPE(6)

//Functions

extern void Audio_FadeOut(u16 frames);

//Inline functions

static inline const void* InjectRomRamMap(u32 rom)
{
    return (const void*)(0x80000000 + ((s32)rom - 0x04000000));
}

static inline const u32 InjectRamRomMap(const void* ram)
{
    return ((u32)ram & 0x7FFFFFFFu) + 0x04000000u;
}

static inline s32 WearingWorkingBunnyHood(){
    return (Player_GetMask(&gGlobalContext) == PLAYER_MASK_BUNNY) 
        && (WORKING_BUNNYHOOD_VAR & WORKING_BUNNYHOOD_BIT);
}

static inline s32 WearingWorkingGerudoMask(){
    return (Player_GetMask(&gGlobalContext) == PLAYER_MASK_GERUDO) 
        && (WORKING_GERUDOMASK_VAR & WORKING_GERUDOMASK_BIT);
}

static inline void Gfx_PrintDebugTextStart(GfxPrint* printer, Gfx** prevDisplayList, Gfx** displayList, u8 r, u8 g, u8 b, u8 a, s32 x, s32 y) {
    // Branch OVERLAY_DISP to POLY_OPA_DISP
    *prevDisplayList = POLY_OPA_DISP;
    *displayList = Graph_GfxPlusOne(POLY_OPA_DISP);
    gSPDisplayList(OVERLAY_DISP++, *displayList);

    // Open Printer
    GfxPrint_Init(printer);
    GfxPrint_Open(printer, *displayList);

    // Setup printer color and position
    GfxPrint_SetColor(printer, r, g, b, a);
    GfxPrint_SetPos(printer, x, y);
}

static inline void Gfx_PrintDebugTextEnd(GfxPrint* printer, Gfx** prevDisplayList, Gfx** displayList) {
    // Close Printer
    *displayList = GfxPrint_Close(printer);
    GfxPrint_Destroy(printer);

    // Branch back
    gSPEndDisplayList(*displayList++);
    Graph_BranchDlist(*prevDisplayList, *displayList);
    POLY_OPA_DISP = *displayList;
}

#define GfxPrint_DebugPrintf(__r, __g, __b, __a, __x, __y, __fmt, ...) \
    do { \
        GfxPrint __printer; \
        Gfx* __prevDisplayList; \
        Gfx* __displayList; \
        Gfx_PrintDebugTextStart(&__printer, &__prevDisplayList, &__displayList, __r, __g, __b, __a, __x, __y); \
        GfxPrint_Printf(&__printer, __fmt, __VA_ARGS__); \
        Gfx_PrintDebugTextEnd(&__printer, &__prevDisplayList, &__displayList); \
    } while (0)


#endif /* ! _OOTMAIN_H_INCLUDED_ */
