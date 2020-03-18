#ifndef __karg_common_h
#define __karg_common_h



extern void osContStartReadData( void* queue );
extern void osRecvMesg( void* queue, void* msg, u32 to_block ); // msg = NULL, to_block = yes
extern void osContGetReadData( raw_input_t* input_data );
extern void DmaMgr_SendRequest0( void* vram_addr, void* vrom_addr, u32 size );

//for disabling and re-enabling interrupts in critical code
extern s32 __osDisableInt(); //80005130
extern void __osRestoreInt(s32 i); //800051A0
//cache clearing

// 0x80003440. addr is weird, it's a cache line address not a normal address.
// Just set addr to 0 and size to >= 0x2000 to write back the whole cache.
extern void osWritebackDCache(void* addr, s32 size);

//0x800041A0. Same deal with addr. Set addr to 0 and size to >= 0x4000 to invalidate the whole cache.
extern void osInvalICache(void* addr, s32 size);


#endif
