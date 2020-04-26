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
extern s32 _sprintf(char* dest, const char* format, ...); //800CE7B4

//OS

#define OS_STATE_STOPPED          1
#define OS_STATE_RUNNABLE         2
#define OS_STATE_RUNNING          4
#define OS_STATE_WAITING          8

typedef s32     OSPri;
typedef s32     OSId;

typedef struct
{
  u64	    at, v0, v1, a0, a1, a2, a3,
		t0, t1, t2, t3, t4, t5, t6, t7,
		s0, s1, s2, s3, s4, s5, s6, s7,
		t8, t9, gp, sp, s8, ra, lo, hi;
  u32   sr, pc, cause, badvaddr, rcp;
  u32   fpcsr;
  union
  {
    float           fp32[32];
    double          fp64[16];
  };
                                              /* 0x01D8 */
} __OSThreadContext;

typedef struct OSThread_s OSThread;
struct OSThread_s
{
  OSThread         *next;                     /* 0x0000 */
  OSPri             priority;                 /* 0x0004 */
  OSThread        **queue;                    /* 0x0008 */
  OSThread         *tlnext;                   /* 0x000C */
  u16               state;                    /* 0x0010 */
  u16               flags;                    /* 0x0012 */
  OSId              id;                       /* 0x0014 */
  s32               fp;                       /* 0x0018 */
  __OSThreadContext context;                  /* 0x001C */
                                              /* 0x01F4 */
};

// msg = NULL, to_block = 1
extern void osRecvMesg(void* queue, void* msg, u32 to_block); //80002030
extern void osSetThreadPri(OSThread* thread, OSPri pri); //80004480

//DMA

extern void Yaz0_Decompress(u32 vrom_addr, u32 vram_addr, u32 rom_size); //80001254
extern void DmaMgr_DMARomToRam(u32 vrom_addr, u32 vram_addr, u32 size); //8000085C
extern void DmaMgr_SendRequest0(u32 vram_addr, u32 vrom_addr, u32 size); //80001AA0

//Padmgr

typedef union {
	u8 bytes[6];
	u8 halves[3];
	struct {
		u8 b1, b2, x, y;
		u16 status;
	};
	struct {
		s8 b1, b2, x, y;
		u16 status;
	} s;
	struct {
		u8 a :1;
		u8 b :1;
		u8 z :1;
		u8 s :1;
		u8 du:1;
		u8 dd:1;
		u8 dl:1;
		u8 dr:1;
		u8 reset:1;
		u8 unused:1;
		u8 l :1;
		u8 r :1;
		u8 cu:1;
		u8 cd:1;
		u8 cl:1;
		u8 cr:1;
		u8 x, y;
		u16 status;
	} buttons;
} raw_input_t;

extern void osContStartReadData(void* queue); //800D0160
extern void osContGetReadData(void* input_data); //800D01E4

// Graphics

extern volatile u16* volatile framebuffer16;
extern volatile u64* volatile framebuffer64;


#endif //__Z_FUNCTIONS_H__
