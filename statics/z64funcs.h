#ifndef __TF_Z64FUNCS_H__
#define __TF_Z64FUNCS_H__

#include <z64ovl/oot/u10.h>
#include "z64structs.h"

extern void DmaMgr_SendRequest2(DmaRequest *req, u8 *dest, u32 rom, u32 size, 
    s32 unk, OSMesgQueue *queue, s32 unk2);

extern void Audio_FadeOut(u16 frames);
extern void Audio_PlaySoundGeneral(u16 sfxId, void* a1, u8 a2, void* a3, void* a4, void* a5);


#endif //__TF_Z64FUNCS_H__
