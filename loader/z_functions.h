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

//DMA

extern void DmaMgr_SendRequest0(void* vram_addr, void* vrom_addr, s32 size); //80001AA0
extern void Yaz0_Decompress(void* vrom_addr, void* vram_addr, s32 rom_size); //80001254

//Padmgr

extern void osContStartReadData(void* queue); //800D0160
extern void osContGetReadData(raw_input_t* input_data); //800D01E4


#endif //__Z_FUNCTIONS_H__
