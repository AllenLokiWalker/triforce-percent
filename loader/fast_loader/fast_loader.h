#ifndef __FAST_LOADER_H__
#define __FAST_LOADER_H__

extern void (*fp_precmd)(void);
extern void (*fp_postcmd)(void);
extern s32 fl_disable_green_bar;
extern u32 last_fl_count;
extern u32 avg_fl_count;

typedef struct {
    //Old version: 85 bytes / 4 messages per packet = 21 bytes / packet
    u8 flags; // 4: username color, 2: casing, 2: exclamation qty
    u8 badges; // 1: X, 2: channel badge, 5: global badge
    u8 uname_encoded[19]; //25x 6-bit chars -> 19 bytes
    /*
    //New version: 85 bytes / 3 messages per packet = 28 bytes / packet
    u8 flags1; // 2: content, 2: casing, 4: username color
    //content: 0: text only, 1: emotes, 2: text then emotes, 3: emotes then text
    u8 flags2; // 3: emote qty, 3: emote, 2: channel badge
    u8 flags3; // 3: exclamation qty, 5: global badge
    u8 uname_encoded[19]; //25x 6-bit chars -> 19 bytes
    */
    u8 timer;
    u8 culled;
    Color_RGB8 rgb;
    u8 a;
    Vec3f center;
} TwitchMessage;

#define MAX_TWITCH_MESSAGES 128

extern TwitchMessage twitch_msg_buf[MAX_TWITCH_MESSAGES];

#endif //__FAST_LOADER_H__
