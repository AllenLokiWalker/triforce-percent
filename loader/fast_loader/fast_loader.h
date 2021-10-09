#ifndef __FAST_LOADER_H__
#define __FAST_LOADER_H__

extern void (*fp_precmd)(void);
extern void (*fp_postcmd)(void);
extern s32 fl_disable_green_bar;
extern u32 last_fl_count;
extern u32 avg_fl_count;

#endif //__FAST_LOADER_H__
