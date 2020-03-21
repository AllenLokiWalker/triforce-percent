#ifndef __Z_FUNCTIONS_H__
#define __Z_FUNCTIONS_H__
 
 #include "common.h"

//Low-level system

//for disabling and re-enabling interrupts in critical code
extern s32 __osDisableInt(); //80005130
extern void __osRestoreInt(s32 i); //800051A0

//Addr is weird, it's a cache line address not a normal address.
//Just set addr to 0 and size to >= 0x2000 to write back the whole cache.
extern void osWritebackDCache(void* addr, s32 size); //80003440
//Set addr to 0 and size to >= 0x4000 to invalidate the whole cache.
extern void osInvalICache(void* addr, s32 size); //800041A0

extern void bzero(void* addr, s32 size); //80002E80

//OS

// msg = NULL, to_block = yes
extern void osRecvMesg(void* queue, void* msg, u32 to_block); //80002030
extern void osSetThreadPri(void* thread, s32 pri); //80004480

//DMA

extern void Yaz0_Decompress(u32 vrom_addr, u32 vram_addr, u32 rom_size); //80001254
extern void DmaMgr_DMARomToRam(u32 vrom_addr, u32 vram_addr, u32 size); //8000085C
extern void DmaMgr_SendRequest0(u32 vram_addr, u32 vrom_addr, u32 size); //80001AA0

//Padmgr

extern void osContStartReadData(void* queue); //800D0160
extern void osContGetReadData(void* input_data); //800D01E4


#endif //__Z_FUNCTIONS_H__
