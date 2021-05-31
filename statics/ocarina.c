#include "z64structs.h"
#include "z64funcs.h"
#include "ocarina.h"

typedef struct {
    u8 num_notes;
    s8 notes[8];
} detectable_song_t;

extern detectable_song_t DetectableSongs[13]; //extra is short scarecrow's song

typedef struct {
    s8 note;
    u16 time;
    u8 volume;
    u8 vibrato;
    s8 pitch;
} canon_song_cmd_t;

typedef struct {
    canon_song_cmd_t cmds[20];
} canon_song_t;

extern canon_song_t CanonSongs[14]; //extra 2 are short scarecrow's song and minigame song

// Overture of Sages
static const detectable_song_t OvertureOfSages_Det = {
    6,
    4, 1, 0, 2, 3, 4,
    -1, -1
};
static const canon_song_t OvertureOfSages_Canon = {{
    {0xE, 30, 100, 0, 0},
    {0xE, 30, 100, 4, 0},
    {0x5, 30, 100, 0, 0},
    {0x2, 30, 100, 0, 0},
    {0x2, 27, 100, 4, 0},
    { -1,  3,   0, 0, 0},
    {0x9, 30, 100, 0, 0},
    {0xB, 30, 100, 0, 0},
    {0xE, 30, 100, 0, 0},
    {0xE, 30, 100, 4, 0},
    { -1, 60,   0, 0, 0}
}};

/*
Instruments:
0 - none
1 - ocarina (0x34)
2 - Malon (0x55)
3 - Impa (whistle) (0x56)
4 - harp (0x59)
5 - accordion (0x53)
6 - pan flute (0x52)
7 - hack - sparkle_bell (0x40)
8 - ocarina (0x34)
Line 15739 in oot_1.0U_seq0.mus has the instrument IDs, and there's two extras
set ocarina instrument = func_800C2C90 (1.0) = func_800ED858 (DBG)
*/

void Statics_OcarinaCodePatches(){
    bcopy(&OvertureOfSages_Det, &DetectableSongs[1], sizeof(detectable_song_t));
    bcopy(&OvertureOfSages_Canon, &CanonSongs[1], sizeof(canon_song_t));
    //800DEF90: instruction for setting a0 to instrument for Sheik songs teach
    *((u8*)0x800DEF93) = 0x07;
}
