#ifndef __FAST_LOADER_H__
#define __FAST_LOADER_H__

extern void (*fp_precmd)(void);
extern void (*fp_postcmd)(void);
extern s32 fl_disable_green_bar;
extern u32 last_fl_count;
extern u32 avg_fl_count;

typedef struct {
    u8 flags;
    u8 badges;
    u8 uname_encoded[19];
    u8 timer;
    u8 culled;
    Color_RGB8 rgb;
    u8 a;
} TwitchMessage;

#define MAX_TWITCH_MESSAGES 128

extern TwitchMessage twitch_msg_buf[MAX_TWITCH_MESSAGES];

#endif //__FAST_LOADER_H__
