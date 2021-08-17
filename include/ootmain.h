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
#define POLY_OPA_DISP gGlobalContext.state.gfxCtx->polyOpa.p
#define POLY_XLU_DISP gGlobalContext.state.gfxCtx->polyXlu.p

#define CHECK_NPC_ACTION(slot, num) \
	(globalCtx->csCtx.state != 0) \
	&& (globalCtx->csCtx.npcActions[slot] != NULL) \
	&& (globalCtx->csCtx.npcActions[slot]->action == num)

extern Gfx gActorXluSetup[3]; //D_80116280

#define WORKING_BUNNYHOOD_VAR gSaveContext.itemGetInf[0x2]
#define WORKING_BUNNYHOOD_BIT 0x0001
#define WORKING_GERUDOMASK_VAR gSaveContext.itemGetInf[0x2]
#define WORKING_GERUDOMASK_BIT 0x0002
#define NABOORU_CONTINUE_VAR gSaveContext.infTable[0x16]
#define NABOORU_CONTINUE_BIT 0x0100

#define Actor_IsTalking func_8002F194
#define Message_ShouldAdvance func_80106BC8
#define MESSAGE_ADVANCE_EVENT ((func_8010BDBC(&globalCtx->msgCtx) == 5) && (Message_ShouldAdvance(globalCtx) != 0))
#define MESSAGE_ADVANCE_CHOICE ((func_8010BDBC(&globalCtx->msgCtx) == 4) && (Message_ShouldAdvance(globalCtx) != 0))

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


#endif /* ! _OOTMAIN_H_INCLUDED_ */
