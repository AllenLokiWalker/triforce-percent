#include "z64hdr/oot_10.h"

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

#define CTRLR_RAW gGlobalContext.common.input[0].raw
#define CTRLR_PRESS gGlobalContext.common.input[0].pad_pressed
#undef PLAYER
#define PLAYER ((Player*)gGlobalContext.actorCtx.actorLists[ACTORCAT_PLAYER].head)

#define JUMPINSTR(func) (0x08000000 | ((((u32)func)>>2) & 0x03FFFFFF))
#define JALINSTR(func)  (0x0C000000 | ((((u32)func)>>2) & 0x03FFFFFF))

//Functions

extern void Audio_FadeOut(u16 frames);

//Inline functions

static inline const void* InjectRomRamMap(u32 rom)
{
    return (const void*)(0x80000000 + ((s32)rom - 0x04000000));
}
