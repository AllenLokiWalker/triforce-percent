#include <z64ovl/oot/u10.h>

extern void bzero(void* addr, s32 size);
extern void osWritebackDCache(void* addr, s32 size);
extern void osInvalICache(void* addr, s32 size);

extern z64_global_t gGlobalContext;
extern z64_save_context_t gSaveContext;

#define CTRLR_RAW gGlobalContext.common.input[0].raw
#define CTRLR_PRESS gGlobalContext.common.input[0].pad_pressed
#define PLAYER ((z64_player_t*)gGlobalContext.actor_ctxt.actor_list[OVLTYPE_PLAYER].first)

#define JUMPINSTR(func) (0x08000000 | ((((u32)func)>>2) & 0x03FFFFFF))
#define JALINSTR(func)  (0x0C000000 | ((((u32)func)>>2) & 0x03FFFFFF))
