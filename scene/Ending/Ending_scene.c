#include "ultra64.h"
#include "z64.h"
#include "macros.h"
#include "Ending_scene.h"

#include "segment_symbols.h"
#include "command_macros_base.h"
#include "z64cutscene_commands.h"
#include "variables.h"

SCmdBase Ending_scene_header00[] = {
	SCENE_CMD_ALTERNATE_HEADER_LIST(&Ending_scene_alternateHeaders),
	SCENE_CMD_SOUND_SETTINGS(0x00, 0x12, 0x7F),
	SCENE_CMD_ROOM_LIST(1, &Ending_scene_roomList),
	SCENE_CMD_MISC_SETTINGS(0x00, 0x0E),
	SCENE_CMD_COL_HEADER(&Ending_collisionHeader),
	SCENE_CMD_ENTRANCE_LIST(&Ending_scene_header00_entranceList),
	SCENE_CMD_SPECIAL_FILES(0x00, 0x0002),
	SCENE_CMD_SPAWN_LIST(1, &Ending_scene_header00_startPositionList),
	SCENE_CMD_SKYBOX_SETTINGS(0x01, 0x00, 0x00),
	SCENE_CMD_ENV_LIGHT_SETTINGS(4, &Ending_scene_header00_lightSettings),
	SCENE_CMD_CUTSCENE_DATA(&FinaleCS),
	SCENE_CMD_END(),
};

SCmdBase* Ending_scene_alternateHeaders[] = {
	0,
	0,
	0,
	Ending_scene_header04,
};

ActorEntry Ending_scene_header00_startPositionList[] = {
	{ ACTOR_PLAYER, -346, 34, 66, 0, 9102, 0, 0x00FF },
};

extern u8 _Ending_room_0SegmentRomStart[];
extern u8 _Ending_room_0SegmentRomEnd[];

RomFile Ending_scene_roomList[] = {
	{ (u32)_Ending_room_0SegmentRomStart, (u32)_Ending_room_0SegmentRomEnd },
};

EntranceEntry Ending_scene_header00_entranceList[] = {
	{ 0, 0 },
};

LightSettings Ending_scene_header00_lightSettings[4] = {
	{ 0x1E, 0x21, 0x46, 0x49, 0x49, 0x49, 0xB4, 0x9A, 0x8A, 0xB7, 0xB7, 0xB7, 0x14, 0x14, 0x3C, 0x8C, 0x78, 0x64, 0x07E1, 0x3200 },
	{ 0x69, 0x5A, 0x5A, 0x49, 0x49, 0x49, 0xFF, 0xFF, 0xF0, 0xB7, 0xB7, 0xB7, 0x32, 0x32, 0x5A, 0x64, 0x64, 0x78, 0x07E4, 0x3200 },
	{ 0x78, 0x5A, 0x00, 0x49, 0x49, 0x49, 0xFA, 0x87, 0x32, 0xB7, 0xB7, 0xB7, 0x1E, 0x1E, 0x3C, 0x78, 0x46, 0x32, 0x07E3, 0x3200 },
	{ 0x28, 0x46, 0x64, 0x49, 0x49, 0x49, 0x14, 0x14, 0x23, 0xB7, 0xB7, 0xB7, 0x32, 0x32, 0x64, 0x00, 0x00, 0x1E, 0x07E0, 0x3200 },
};

SCmdBase Ending_scene_header04[] = {
	SCENE_CMD_SOUND_SETTINGS(0x00, 0x1E, 0),
	SCENE_CMD_ROOM_LIST(1, &Ending_scene_roomList),
	SCENE_CMD_MISC_SETTINGS(0x00, 0x0E),
	SCENE_CMD_COL_HEADER(&Ending_collisionHeader),
	SCENE_CMD_ENTRANCE_LIST(&Ending_scene_header04_entranceList),
	SCENE_CMD_SPECIAL_FILES(0x00, 0x0002),
	SCENE_CMD_SPAWN_LIST(1, &Ending_scene_header04_startPositionList),
	SCENE_CMD_SKYBOX_SETTINGS(0x01, 0x00, 0x00),
	SCENE_CMD_ENV_LIGHT_SETTINGS(4, &Ending_scene_header04_lightSettings),
	SCENE_CMD_END(),
};

ActorEntry Ending_scene_header04_startPositionList[] = {
	{ ACTOR_PLAYER, -346, 34, 66, 0, 9102, 0, 0x00FF },
};

EntranceEntry Ending_scene_header04_entranceList[] = {
	{ 0, 0 },
};

LightSettings Ending_scene_header04_lightSettings[4] = {
	{ 0x8F, 0x6E, 0x82, 0x49, 0x49, 0x49, 0xDB, 0xCC, 0xC2, 0xB7, 0xB7, 0xB7, 0x4F, 0x4F, 0x85, 0xC4, 0xB6, 0xAF, 0x07E1, 0x3200 },
	{ 0x8F, 0x6E, 0x82, 0x49, 0x49, 0x49, 0xDB, 0xCC, 0xC2, 0xB7, 0xB7, 0xB7, 0x4F, 0x4F, 0x85, 0xC4, 0xB6, 0xAF, 0x07E1, 0x3200 },
	{ 0x8F, 0x6E, 0x82, 0x49, 0x49, 0x49, 0xDB, 0xCC, 0xC2, 0xB7, 0xB7, 0xB7, 0x4F, 0x4F, 0x85, 0xC4, 0xB6, 0xAF, 0x07E1, 0x3200 },
	{ 0x8F, 0x6E, 0x82, 0x49, 0x49, 0x49, 0xDB, 0xCC, 0xC2, 0xB7, 0xB7, 0xB7, 0x4F, 0x4F, 0x85, 0xC4, 0xB6, 0xAF, 0x07E1, 0x3200 },
};

SurfaceType Ending_polygonTypes[] = {
	{ 0x00000000, 0x00000000 },
	{ 0x00000000, 0x00000002 },
	{ 0x00000000, 0x00000005 },
};

CollisionPoly Ending_polygons[] = {
	{ 0x0000, 0x0000, 0x0001, 0x0002, 0x0000, 0x7fff, 0x0000, 0x0032 },
	{ 0x0000, 0x0003, 0x0004, 0x0005, 0xe1aa, 0x5ad0, 0x54f4, 0x0094 },
	{ 0x0000, 0x0003, 0x0005, 0x0006, 0xe4c8, 0x5336, 0x5d60, 0x009e },
	{ 0x0000, 0x0007, 0x0004, 0x0005, 0xd4b4, 0x5b85, 0x4e51, 0x0093 },
	{ 0x0000, 0x0008, 0x0003, 0x0009, 0x3f94, 0x6173, 0x3559, 0x0083 },
	{ 0x0000, 0x000a, 0x000b, 0x000c, 0x19b5, 0x7cd1, 0xf3fd, 0x0034 },
	{ 0x0000, 0x0008, 0x000d, 0x000e, 0x63c1, 0x47ba, 0x23e4, 0x00ad },
	{ 0x0000, 0x0008, 0x0009, 0x000e, 0x6747, 0x4870, 0x15af, 0x00b2 },
	{ 0x0000, 0x000f, 0x0010, 0x0011, 0xfffa, 0x7fff, 0xfffd, 0x0032 },
	{ 0x0000, 0x0012, 0x0013, 0x000d, 0x268a, 0x7878, 0xec59, 0x0065 },
	{ 0x0000, 0x0014, 0x0012, 0x0013, 0x1b94, 0x7899, 0xdf23, 0x0062 },
	{ 0x0000, 0x0015, 0x0016, 0x0017, 0x0000, 0x7fff, 0x0000, 0xffdd },
	{ 0x0000, 0x0018, 0x000c, 0x000b, 0xffff, 0x7fff, 0x0000, 0x000b },
	{ 0x0000, 0x000d, 0x0019, 0x0015, 0x5212, 0x56de, 0x2dda, 0x0090 },
	{ 0x0000, 0x001a, 0x0019, 0x0017, 0x870a, 0xe275, 0x1da7, 0xfe3d },
	{ 0x0000, 0x0019, 0x0015, 0x0017, 0x1531, 0x766f, 0x2bb0, 0xffd9 },
	{ 0x0000, 0x001b, 0x0018, 0x0019, 0xb544, 0xd826, 0x5ff9, 0xfe29 },
	{ 0x0000, 0x0012, 0x0008, 0x000d, 0x2834, 0x7759, 0xe91d, 0x0068 },
	{ 0x0000, 0x001c, 0x000b, 0x0019, 0x0b83, 0x7a6e, 0xdc78, 0x007e },
	{ 0x0000, 0x001b, 0x001a, 0x0019, 0xb3c6, 0xc760, 0x55d5, 0xfe3d },
	{ 0x0000, 0x001d, 0x001e, 0x000c, 0xc633, 0xe0a7, 0x6dd2, 0xfe51 },
	{ 0x0000, 0x001e, 0x000a, 0x000c, 0x2130, 0x7b99, 0xfd6d, 0x000b },
	{ 0x0000, 0x001f, 0x0018, 0x000c, 0xf416, 0x0786, 0x7f39, 0xfe01 },
	{ 0x0000, 0x0010, 0x0020, 0x0011, 0xfffe, 0x7fff, 0xfffe, 0x0032 },
	{ 0x0000, 0x0013, 0x000d, 0x0019, 0x0d5e, 0x7f36, 0xfb4a, 0x0038 },
	{ 0x0000, 0x001d, 0x001f, 0x000c, 0xf1a0, 0x099e, 0x7ed4, 0xfe03 },
	{ 0x0000, 0x0021, 0x001d, 0x001f, 0xe2f1, 0xa451, 0x5476, 0xfe52 },
	{ 0x0000, 0x0022, 0x001d, 0x001e, 0x0bcc, 0xc92c, 0x730f, 0xfdc9 },
	{ 0x0000, 0x0023, 0x0022, 0x001d, 0xeea3, 0x9a13, 0x4b74, 0xfe5e },
	{ 0x0000, 0x0023, 0x0021, 0x001d, 0xeed9, 0x9a16, 0x4b86, 0xfe5e },
	{ 0x0000, 0x0021, 0x0024, 0x001a, 0xa6e8, 0xad57, 0x282c, 0xfe63 },
	{ 0x0000, 0x0021, 0x001b, 0x001a, 0xb7ef, 0xb9b6, 0x4f0f, 0xfe4f },
	{ 0x0000, 0x0025, 0x0026, 0x0021, 0xe668, 0xb458, 0x6406, 0xfe60 },
	{ 0x0000, 0x0025, 0x0021, 0x0024, 0xa14a, 0xb754, 0x2e2e, 0xfe67 },
	{ 0x0000, 0x0021, 0x001b, 0x001f, 0xd835, 0xaa1d, 0x562a, 0xfe4d },
	{ 0x0000, 0x0026, 0x0023, 0x0021, 0xedcd, 0xc7b0, 0x717f, 0xfe7f },
	{ 0x0000, 0x0026, 0x0023, 0x0027, 0x50af, 0x9cf3, 0xf811, 0xfe6e },
	{ 0x0000, 0x0025, 0x0026, 0x0027, 0x55ee, 0xa127, 0xfe0a, 0xfe6b },
	{ 0x0000, 0x0025, 0x0027, 0x0028, 0x4631, 0xb987, 0xaf6f, 0xfefc },
	{ 0x0000, 0x0027, 0x0028, 0x0029, 0x3916, 0xa43d, 0xbb69, 0xfed5 },
	{ 0x0000, 0x0027, 0x002a, 0x0029, 0x3231, 0xa0ec, 0xba8b, 0xfeda },
	{ 0x0000, 0x0023, 0x0027, 0x002a, 0x4aff, 0x9892, 0xf821, 0xfe6d },
	{ 0x0000, 0x0028, 0x002b, 0x0029, 0x1343, 0xae97, 0x9f1f, 0xfed8 },
	{ 0x0000, 0x0029, 0x002b, 0x002c, 0x169a, 0xc968, 0x8e74, 0xfec8 },
	{ 0x0000, 0x002a, 0x0029, 0x002d, 0x4265, 0xbafb, 0xab13, 0xfeba },
	{ 0x0000, 0x0029, 0x002c, 0x002d, 0x12a7, 0xc3a4, 0x90ad, 0xfecd },
	{ 0x0000, 0x000e, 0x0015, 0x0016, 0x0407, 0x7fe6, 0xfccd, 0xffee },
	{ 0x0000, 0x0018, 0x000b, 0x0019, 0x01cd, 0x7ff3, 0x0313, 0x0001 },
	{ 0x0000, 0x0002, 0x002e, 0x0000, 0x0004, 0x7fff, 0xfff7, 0x0032 },
	{ 0x0000, 0x002b, 0x002c, 0x002f, 0xc17f, 0xd846, 0x979a, 0xfed0 },
	{ 0x0000, 0x0030, 0x002f, 0x0031, 0xf6d9, 0xff31, 0x8055, 0xff23 },
	{ 0x0000, 0x0002, 0x0032, 0x002e, 0xfff4, 0x7fff, 0xfff6, 0x0032 },
	{ 0x0000, 0x0033, 0x0030, 0x002f, 0x2011, 0xe30c, 0x8783, 0xff8f },
	{ 0x0000, 0x002b, 0x0033, 0x002f, 0xc09b, 0xd4af, 0x9996, 0xfed2 },
	{ 0x0000, 0x0030, 0x0034, 0x0031, 0x971b, 0xdce9, 0xbf95, 0xfe58 },
	{ 0x0000, 0x0024, 0x0030, 0x0034, 0xac62, 0xa924, 0xd505, 0xfe90 },
	{ 0x0000, 0x0035, 0x0033, 0x0030, 0x1c77, 0xc335, 0x9304, 0xff7f },
	{ 0x0000, 0x0035, 0x0024, 0x0030, 0xa7f9, 0xac36, 0xd7d1, 0xfe8a },
	{ 0x0000, 0x0025, 0x0035, 0x0024, 0xa2fe, 0xb87c, 0xccd3, 0xfe9c },
	{ 0x0000, 0x0028, 0x0035, 0x0033, 0xdbe1, 0xbb2d, 0x9a4d, 0xfef9 },
	{ 0x0000, 0x0025, 0x0035, 0x0028, 0xd9e7, 0xc569, 0x94c3, 0xff0d },
	{ 0x0000, 0x0034, 0x0017, 0x0016, 0x9b9e, 0xc17d, 0x30fe, 0xfe69 },
	{ 0x0000, 0x0034, 0x0031, 0x0016, 0xa5eb, 0xc582, 0xba5f, 0xfe83 },
	{ 0x0000, 0x0024, 0x001a, 0x0034, 0x9aec, 0xb6bf, 0x1c4d, 0xfe5e },
	{ 0x0000, 0x001a, 0x0034, 0x0017, 0x88a6, 0xe588, 0x25ed, 0xfe33 },
	{ 0x0000, 0x001e, 0x0036, 0x000f, 0x0000, 0x7fff, 0x0006, 0x0032 },
	{ 0x0000, 0x0014, 0x001c, 0x0013, 0x1410, 0x7cfe, 0xed0f, 0x004d },
	{ 0x0000, 0x001c, 0x0013, 0x0019, 0x0a06, 0x7f52, 0xf775, 0x0037 },
	{ 0x0000, 0x0037, 0x000e, 0x0016, 0x044e, 0x7eae, 0xee2b, 0xffed },
	{ 0x0000, 0x0028, 0x002b, 0x0033, 0xcb99, 0xaa45, 0xb0b3, 0xfee8 },
	{ 0x0000, 0x0006, 0x0009, 0x0037, 0x0f2b, 0x7e50, 0x0e1c, 0x0022 },
	{ 0x0000, 0x0003, 0x0006, 0x0009, 0x4995, 0x4383, 0x5013, 0x00a0 },
	{ 0x0000, 0x0038, 0x0039, 0x000f, 0x0004, 0x7fff, 0x0004, 0x0032 },
	{ 0x0000, 0x0009, 0x0037, 0x000e, 0x34e9, 0x70e7, 0xe30d, 0x0048 },
	{ 0x0000, 0x002a, 0x0001, 0x002d, 0x4790, 0xc217, 0xa9ce, 0xfeaf },
	{ 0x0000, 0x0001, 0x0007, 0x002d, 0xfdac, 0x7e51, 0x1492, 0x003c },
	{ 0x0000, 0x0007, 0x0005, 0x002d, 0x0fe0, 0x7dc2, 0x11cc, 0x0016 },
	{ 0x0000, 0x002a, 0x0000, 0x0001, 0x67fe, 0xb703, 0xf072, 0xfe21 },
	{ 0x0000, 0x003a, 0x0000, 0x002e, 0x0007, 0x7fff, 0xfffe, 0x0032 },
	{ 0x0000, 0x0001, 0x003b, 0x0002, 0x0000, 0x7fff, 0x0000, 0x0032 },
	{ 0x0000, 0x0039, 0x003a, 0x002e, 0x0006, 0x7fff, 0x0002, 0x0032 },
	{ 0x0000, 0x0007, 0x0004, 0x003c, 0x00bb, 0x7fff, 0xff22, 0x0031 },
	{ 0x0000, 0x003b, 0x0007, 0x003d, 0x0004, 0x7fff, 0xff75, 0x0032 },
	{ 0x0000, 0x0036, 0x0038, 0x000f, 0x0001, 0x7fff, 0x0006, 0x0032 },
	{ 0x0000, 0x001c, 0x000a, 0x000b, 0x1a9d, 0x7c11, 0xef27, 0x0043 },
	{ 0x0000, 0x0039, 0x002e, 0x000f, 0x0004, 0x7fff, 0x0003, 0x0032 },
	{ 0x0000, 0x0006, 0x0005, 0x002c, 0x0059, 0x7fff, 0x0004, 0x0006 },
	{ 0x0000, 0x003d, 0x003e, 0x003b, 0x0000, 0x7fff, 0x0000, 0x0032 },
	{ 0x0000, 0x003c, 0x003d, 0x0007, 0x00bb, 0x7fff, 0xff22, 0x0031 },
	{ 0x0000, 0x0022, 0x001e, 0x0036, 0x08ab, 0xc7ce, 0x72ad, 0xfdcf },
	{ 0x0000, 0x0022, 0x003f, 0x0036, 0x059b, 0xc8f9, 0x736f, 0xfdd4 },
	{ 0x0000, 0x003f, 0x0036, 0x0038, 0x1cfe, 0xf058, 0x7bb0, 0xfd83 },
	{ 0x0000, 0x0006, 0x0037, 0x002f, 0x0820, 0x7fb6, 0xfd22, 0x0003 },
	{ 0x0000, 0x0040, 0x003a, 0x0039, 0x7b14, 0x0d98, 0x206c, 0xfd67 },
	{ 0x0000, 0x003f, 0x0039, 0x0038, 0x53f9, 0xf934, 0x605e, 0xfd27 },
	{ 0x0000, 0x003f, 0x0040, 0x0039, 0x6312, 0xdb52, 0x4847, 0xfd2f },
	{ 0x0000, 0x0041, 0x0000, 0x003a, 0x67ed, 0xbec7, 0xdb89, 0xfe43 },
	{ 0x0000, 0x0041, 0x0040, 0x003a, 0x6825, 0xc946, 0xcd91, 0xfe66 },
	{ 0x0000, 0x0042, 0x0041, 0x0040, 0x4d00, 0x9c19, 0xea35, 0xfe63 },
	{ 0x0000, 0x0042, 0x003f, 0x0040, 0x4fe7, 0xaec0, 0x3a4b, 0xfd82 },
	{ 0x0000, 0x0043, 0x0042, 0x0041, 0x36be, 0x9000, 0xe2f5, 0xfeb2 },
	{ 0x0000, 0x0043, 0x0042, 0x0022, 0x0164, 0x953d, 0x4699, 0xfe45 },
	{ 0x0000, 0x0042, 0x0022, 0x003f, 0x0e95, 0xa2bd, 0x5673, 0xfdfe },
	{ 0x0000, 0x0023, 0x0043, 0x0041, 0x3857, 0x906c, 0xe470, 0xfeaa },
	{ 0x0000, 0x0023, 0x0043, 0x0022, 0x0b34, 0x98eb, 0x4b0d, 0xfe25 },
	{ 0x0000, 0x0023, 0x0041, 0x002a, 0x3789, 0x9072, 0xe2c2, 0xfeb0 },
	{ 0x0000, 0x0041, 0x002a, 0x0000, 0x6afa, 0xbc9e, 0xec01, 0xfe1c },
	{ 0x0000, 0x0005, 0x002d, 0x002c, 0xfff4, 0x7fff, 0x0046, 0x0007 },
	{ 0x0000, 0x0011, 0x0020, 0x001c, 0x1cf9, 0x7c68, 0xf7ce, 0x002a },
	{ 0x0000, 0x0011, 0x001c, 0x000a, 0x23ea, 0x78e1, 0xea07, 0x004b },
	{ 0x0000, 0x000f, 0x0011, 0x001e, 0xfffb, 0x7fff, 0x0003, 0x0032 },
	{ 0x0000, 0x0011, 0x001e, 0x000a, 0x3d26, 0x6f4e, 0xeffb, 0x001b },
	{ 0x0000, 0x002f, 0x0037, 0x0031, 0x0ac1, 0x7f7e, 0xfc34, 0x0008 },
	{ 0x0000, 0x0044, 0x003e, 0x003d, 0x0000, 0x7fff, 0x0000, 0x0032 },
	{ 0x0000, 0x0020, 0x0014, 0x001c, 0x0eab, 0x7df3, 0xee85, 0x004c },
	{ 0x0000, 0x001b, 0x001f, 0x0018, 0xcaa0, 0xd597, 0x6c55, 0xfe13 },
	{ 0x0000, 0x0032, 0x0044, 0x002e, 0x0020, 0x7fff, 0xffd0, 0x0032 },
	{ 0x0000, 0x000d, 0x000e, 0x0015, 0x554e, 0x500f, 0x33f0, 0x0092 },
	{ 0x0000, 0x0044, 0x0032, 0x003e, 0x0000, 0x7fff, 0x0000, 0x0032 },
	{ 0x0000, 0x002c, 0x0006, 0x002f, 0x085e, 0x7fba, 0x0061, 0x0009 },
	{ 0x0000, 0x0001, 0x0007, 0x003b, 0xffdf, 0x7fff, 0xff96, 0x0033 },
	{ 0x0000, 0x0037, 0x0031, 0x0016, 0x0a0b, 0x7f95, 0xfda2, 0x0008 },
	{ 0x0000, 0x0045, 0x0046, 0x0047, 0x0000, 0x7fff, 0x0000, 0x008a },
	{ 0x0000, 0x0047, 0x0048, 0x0049, 0x0000, 0x7fff, 0x0000, 0x008a },
	{ 0x0000, 0x0049, 0x004a, 0x004b, 0x0000, 0x7fff, 0x0000, 0x008a },
	{ 0x0000, 0x004b, 0x004c, 0x004d, 0x0000, 0x7fff, 0x0000, 0x008a },
	{ 0x0000, 0x0049, 0x004b, 0x004d, 0x0000, 0x7fff, 0x0000, 0x008a },
	{ 0x0000, 0x004e, 0x0045, 0x0047, 0x0000, 0x7fff, 0x0000, 0x008a },
	{ 0x0000, 0x004f, 0x004e, 0x0047, 0x0000, 0x7fff, 0x0000, 0x008a },
	{ 0x0000, 0x0049, 0x004d, 0x0050, 0x0000, 0x7fff, 0x0000, 0x008a },
	{ 0x0000, 0x0050, 0x004f, 0x0047, 0xffff, 0x7fff, 0xffff, 0x008a },
	{ 0x0000, 0x0047, 0x0049, 0x0050, 0x0000, 0x7fff, 0x0000, 0x008a },
	{ 0x0001, 0x004b, 0x004a, 0x0014, 0x5247, 0x0000, 0x9df2, 0x0098 },
	{ 0x0001, 0x004a, 0x0014, 0x0012, 0x5247, 0x0000, 0x9df2, 0x0098 },
	{ 0x0001, 0x004b, 0x0014, 0x0051, 0x9df2, 0x0000, 0xadb9, 0x00b3 },
	{ 0x0001, 0x004b, 0x004c, 0x0051, 0x9df2, 0x0000, 0xadb9, 0x00b3 },
	{ 0x0001, 0x004d, 0x004c, 0x0051, 0xadb9, 0x0000, 0x620e, 0xffbd },
	{ 0x0001, 0x004d, 0x0051, 0x0052, 0xadb9, 0x0000, 0x620e, 0xffbd },
	{ 0x0001, 0x0051, 0x0053, 0x0054, 0x620e, 0x0000, 0x5247, 0xff4d },
	{ 0x0001, 0x0051, 0x0055, 0x0053, 0x620e, 0x0000, 0x5247, 0xff4d },
	{ 0x0001, 0x0051, 0x0054, 0x0056, 0xadb9, 0x0000, 0x620e, 0xffbd },
	{ 0x0001, 0x0052, 0x0051, 0x0056, 0xadb9, 0x0000, 0x620e, 0xffbd },
	{ 0x0001, 0x0056, 0x0057, 0x0058, 0x620e, 0x0000, 0x5247, 0xff63 },
	{ 0x0001, 0x0056, 0x0059, 0x0057, 0x620e, 0x0000, 0x5247, 0xff63 },
	{ 0x0001, 0x0056, 0x0058, 0x005a, 0xadb9, 0x0000, 0x620e, 0xffbd },
	{ 0x0001, 0x0052, 0x0056, 0x005a, 0xadb9, 0x0000, 0x620e, 0xffbd },
	{ 0x0001, 0x005a, 0x005b, 0x005c, 0x620e, 0x0000, 0x5247, 0xff78 },
	{ 0x0001, 0x005a, 0x005d, 0x005b, 0x620e, 0x0000, 0x5247, 0xff78 },
	{ 0x0001, 0x005a, 0x005c, 0x005e, 0xadb9, 0x0000, 0x620e, 0xffbd },
	{ 0x0001, 0x0052, 0x005a, 0x005e, 0xadb9, 0x0000, 0x620e, 0xffbd },
	{ 0x0001, 0x005e, 0x005f, 0x0060, 0x620e, 0x0000, 0x5247, 0xff8d },
	{ 0x0001, 0x005e, 0x0061, 0x005f, 0x620e, 0x0000, 0x5247, 0xff8d },
	{ 0x0001, 0x005e, 0x0060, 0x0062, 0xadb9, 0x0000, 0x620e, 0xffbd },
	{ 0x0001, 0x0052, 0x005e, 0x0062, 0xadb9, 0x0000, 0x620e, 0xffbd },
	{ 0x0001, 0x0062, 0x0063, 0x0064, 0x620e, 0x0000, 0x5247, 0xffa2 },
	{ 0x0001, 0x0062, 0x0065, 0x0063, 0x620e, 0x0000, 0x5247, 0xffa2 },
	{ 0x0001, 0x0062, 0x0064, 0x0066, 0xadb9, 0x0000, 0x620e, 0xffbd },
	{ 0x0001, 0x0052, 0x0062, 0x0066, 0xadb9, 0x0000, 0x620e, 0xffbd },
	{ 0x0001, 0x0067, 0x0066, 0x0068, 0x818d, 0x0000, 0x13e0, 0xffce },
	{ 0x0001, 0x0067, 0x0052, 0x0066, 0x818d, 0x0000, 0x13e0, 0xffce },
	{ 0x0001, 0x0069, 0x0068, 0x006a, 0x9df2, 0x0000, 0xadb9, 0xffd8 },
	{ 0x0001, 0x0069, 0x0067, 0x0068, 0x9df2, 0x0000, 0xadb9, 0xffd8 },
	{ 0x0001, 0x004f, 0x0067, 0x0069, 0x9df2, 0x0000, 0xadb9, 0xffd8 },
	{ 0x0001, 0x004f, 0x0050, 0x0067, 0x9df2, 0x0000, 0xadb9, 0xffd8 },
	{ 0x0001, 0x0050, 0x0052, 0x0067, 0x818d, 0x0000, 0x13e0, 0xffce },
	{ 0x0001, 0x0050, 0x004d, 0x0052, 0x818d, 0x0000, 0x13e0, 0xffce },
	{ 0x0001, 0x004e, 0x0069, 0x006b, 0xfd9d, 0x0000, 0x8006, 0xffce },
	{ 0x0001, 0x004e, 0x004f, 0x0069, 0xfd9d, 0x0000, 0x8006, 0xffce },
	{ 0x0001, 0x004e, 0x006b, 0x0055, 0x5247, 0x0000, 0x9df2, 0xffbd },
	{ 0x0001, 0x004e, 0x0045, 0x0055, 0x5247, 0x0000, 0x9df2, 0xffbd },
	{ 0x0001, 0x0069, 0x006a, 0x006c, 0xfd9d, 0x0000, 0x8006, 0xffce },
	{ 0x0001, 0x0069, 0x006b, 0x006c, 0xfd9d, 0x0000, 0x8006, 0xffce },
	{ 0x0001, 0x0055, 0x006b, 0x0059, 0x5247, 0x0000, 0x9df2, 0xffbd },
	{ 0x0001, 0x006b, 0x0065, 0x006c, 0x5247, 0x0000, 0x9df2, 0xffbd },
	{ 0x0001, 0x006b, 0x0059, 0x005d, 0x5247, 0x0000, 0x9df2, 0xffbd },
	{ 0x0001, 0x006b, 0x0061, 0x0065, 0x5247, 0x0000, 0x9df2, 0xffbd },
	{ 0x0001, 0x006b, 0x005d, 0x0061, 0x5247, 0x0000, 0x9df2, 0xffbd },
	{ 0x0001, 0x0046, 0x0045, 0x003c, 0x9df2, 0x0000, 0xadb9, 0x00b3 },
	{ 0x0001, 0x0045, 0x003c, 0x0055, 0x9df2, 0x0000, 0xadb9, 0x00b3 },
	{ 0x0001, 0x0047, 0x0046, 0x003c, 0xadb9, 0x0000, 0x620e, 0x0099 },
	{ 0x0001, 0x0047, 0x003c, 0x0004, 0xadb9, 0x0000, 0x620e, 0x0099 },
	{ 0x0001, 0x0047, 0x0004, 0x0003, 0xd4f4, 0x0000, 0x788b, 0x00a0 },
	{ 0x0001, 0x0047, 0x0048, 0x0003, 0xd4f4, 0x0000, 0x788b, 0x00a0 },
	{ 0x0001, 0x0049, 0x0048, 0x0008, 0x620e, 0x0000, 0x5247, 0x0090 },
	{ 0x0001, 0x0048, 0x0008, 0x0003, 0x620e, 0x0000, 0x5247, 0x0090 },
	{ 0x0001, 0x004a, 0x0049, 0x0012, 0x6f3d, 0x0000, 0xc0ad, 0x009f },
	{ 0x0001, 0x0049, 0x0012, 0x0008, 0x6f3d, 0x0000, 0xc0ad, 0x009f },
	{ 0x0001, 0x0065, 0x0060, 0x005f, 0x0000, 0x7fff, 0x0000, 0x000a },
	{ 0x0001, 0x0065, 0x006c, 0x0063, 0x5247, 0x0000, 0x9df2, 0xffbd },
	{ 0x0001, 0x0061, 0x0065, 0x005f, 0x5247, 0x0000, 0x9df2, 0xffbd },
	{ 0x0001, 0x005d, 0x0061, 0x005b, 0x5247, 0x0000, 0x9df2, 0xffbd },
	{ 0x0001, 0x0059, 0x005d, 0x0057, 0x5247, 0x0000, 0x9df2, 0xffbd },
	{ 0x0001, 0x0055, 0x0059, 0x0053, 0x5247, 0x0000, 0x9df2, 0xffbd },
	{ 0x0001, 0x0061, 0x005c, 0x005b, 0x0000, 0x7fff, 0x0000, 0x0014 },
	{ 0x0001, 0x005d, 0x0058, 0x0057, 0x0000, 0x7fff, 0x0000, 0x001e },
	{ 0x0001, 0x0053, 0x0056, 0x0054, 0x0000, 0x7fff, 0x0000, 0x0028 },
	{ 0x0001, 0x0066, 0x0064, 0x0063, 0x0000, 0x7fff, 0x0000, 0x0000 },
	{ 0x0001, 0x0010, 0x0044, 0x0014, 0x0000, 0x7fff, 0x0000, 0x0032 },
	{ 0x0001, 0x0065, 0x0062, 0x0060, 0x0000, 0x7fff, 0x0000, 0x000a },
	{ 0x0001, 0x0061, 0x005e, 0x005c, 0x0000, 0x7fff, 0x0000, 0x0014 },
	{ 0x0001, 0x005d, 0x005a, 0x0058, 0x0000, 0x7fff, 0x0000, 0x001e },
	{ 0x0001, 0x0053, 0x0059, 0x0056, 0x0000, 0x7fff, 0x0000, 0x0028 },
	{ 0x0001, 0x0063, 0x006c, 0x0066, 0x0000, 0x7fff, 0x0000, 0x0000 },
	{ 0x0001, 0x006c, 0x006a, 0x0066, 0x0000, 0x7fff, 0x0000, 0x0000 },
	{ 0x0001, 0x006a, 0x0068, 0x0066, 0x0000, 0x7fff, 0x0000, 0x0000 },
	{ 0x0001, 0x0010, 0x000f, 0x002e, 0xfffb, 0x7fff, 0xfffc, 0x0032 },
	{ 0x0001, 0x0044, 0x003d, 0x003c, 0x0000, 0x7fff, 0x0000, 0x0032 },
	{ 0x0001, 0x0010, 0x002e, 0x0044, 0xfffb, 0x7fff, 0xfffc, 0x0032 },
	{ 0x0001, 0x0014, 0x0020, 0x0010, 0x0000, 0x7fff, 0x0000, 0x0032 },
	{ 0x0001, 0x0044, 0x003c, 0x0014, 0x0000, 0x7fff, 0x0000, 0x0032 },
	{ 0x0001, 0x0032, 0x006d, 0x006e, 0xadb9, 0x0000, 0x620e, 0x0051 },
	{ 0x0001, 0x0032, 0x003e, 0x006e, 0xadb9, 0x0000, 0x620e, 0x0051 },
	{ 0x0001, 0x0002, 0x006f, 0x006d, 0x620e, 0x0000, 0x5247, 0xfe6d },
	{ 0x0001, 0x0002, 0x0032, 0x006d, 0x620e, 0x0000, 0x5247, 0xfe6d },
	{ 0x0001, 0x003e, 0x006e, 0x0070, 0x9df2, 0x0000, 0xadb9, 0x0130 },
	{ 0x0001, 0x003e, 0x003b, 0x0070, 0x9df2, 0x0000, 0xadb9, 0x0130 },
	{ 0x0001, 0x003b, 0x0070, 0x006f, 0x5247, 0x0000, 0x9df2, 0xff4d },
	{ 0x0001, 0x003b, 0x0002, 0x006f, 0x5247, 0x0000, 0x9df2, 0xff4d },
	{ 0x0001, 0x006f, 0x0070, 0x006e, 0x0000, 0x7fff, 0x0000, 0x002e },
	{ 0x0001, 0x006f, 0x006e, 0x006d, 0x0000, 0x7fff, 0x0000, 0x002e },
	{ 0x0001, 0x0071, 0x0072, 0x0073, 0xadb9, 0x0000, 0x620e, 0xff4d },
	{ 0x0001, 0x0071, 0x0074, 0x0073, 0xadb9, 0x0000, 0x620e, 0xff4d },
	{ 0x0001, 0x0075, 0x0076, 0x0072, 0x620e, 0x0000, 0x5247, 0xfe6d },
	{ 0x0001, 0x0075, 0x0071, 0x0072, 0x620e, 0x0000, 0x5247, 0xfe6d },
	{ 0x0001, 0x0074, 0x0073, 0x0077, 0x9df2, 0x0000, 0xadb9, 0x0130 },
	{ 0x0001, 0x0074, 0x0078, 0x0077, 0x9df2, 0x0000, 0xadb9, 0x0130 },
	{ 0x0001, 0x0078, 0x0077, 0x0076, 0x5247, 0x0000, 0x9df2, 0x0050 },
	{ 0x0001, 0x0078, 0x0075, 0x0076, 0x5247, 0x0000, 0x9df2, 0x0050 },
	{ 0x0001, 0x0076, 0x0077, 0x0073, 0x0000, 0x7fff, 0x0000, 0x002e },
	{ 0x0001, 0x0076, 0x0073, 0x0072, 0x0000, 0x7fff, 0x0000, 0x002e },
	{ 0x0002, 0xe079, 0x007a, 0x007b, 0x0000, 0x7fff, 0x0000, 0x0041 },
	{ 0x0002, 0xe079, 0x007b, 0x007c, 0x0000, 0x7fff, 0x0000, 0x0041 },
	{ 0x0002, 0xe07d, 0x007e, 0x007b, 0x0000, 0x7fff, 0x0000, 0x0041 },
	{ 0x0002, 0xe07d, 0x007b, 0x007a, 0x0000, 0x7fff, 0x0000, 0x0041 },
	{ 0x0002, 0xe07f, 0x007a, 0x0079, 0x0000, 0x7fff, 0x0000, 0x0041 },
	{ 0x0002, 0xe07f, 0x0079, 0x0080, 0x0000, 0x7fff, 0x0000, 0x0041 },
	{ 0x0002, 0xe07f, 0x0081, 0x007d, 0x0000, 0x7fff, 0x0000, 0x0041 },
	{ 0x0002, 0xe07f, 0x007d, 0x007a, 0x0000, 0x7fff, 0x0000, 0x0041 },
};

Vec3s Ending_vertices[130] = {
	{ 583, -50, 190 },
	{ 554, -50, -5 },
	{ 424, -50, 122 },
	{ -35, -50, -182 },
	{ 61, -50, -148 },
	{ 83, -6, -186 },
	{ -33, -6, -221 },
	{ 263, -50, -36 },
	{ -185, -50, -3 },
	{ -205, -3, -65 },
	{ 126, -36, 444 },
	{ -12, -11, 414 },
	{ 37, -11, 518 },
	{ -213, -33, 39 },
	{ -236, 26, -12 },
	{ 331, -50, 365 },
	{ 164, -50, 225 },
	{ 135, -50, 383 },
	{ -135, -50, 86 },
	{ -169, -34, 114 },
	{ 39, -50, 231 },
	{ -375, 35, 202 },
	{ -550, 35, -19 },
	{ -430, 35, 228 },
	{ -158, -11, 500 },
	{ -399, -3, 316 },
	{ -390, -90, 267 },
	{ -149, -114, 464 },
	{ 73, -38, 348 },
	{ 159, -150, 543 },
	{ 189, -50, 587 },
	{ -47, -109, 516 },
	{ 109, -50, 290 },
	{ -196, -307, 251 },
	{ 258, -188, 515 },
	{ 249, -341, 305 },
	{ -322, -263, 61 },
	{ -61, -603, 61 },
	{ 136, -428, 244 },
	{ 239, -332, 85 },
	{ 17, -313, -125 },
	{ 176, -110, -264 },
	{ 491, -144, 9 },
	{ -40, -110, -307 },
	{ -27, -6, -354 },
	{ 222, -6, -312 },
	{ 417, -50, 262 },
	{ -293, 11, -201 },
	{ -366, -94, -195 },
	{ -406, 21, -193 },
	{ 361, -50, 197 },
	{ -271, -95, -170 },
	{ -484, -69, -16 },
	{ -229, -313, -37 },
	{ 326, -50, 577 },
	{ -266, 11, -123 },
	{ 488, -50, 539 },
	{ 575, -50, 463 },
	{ 620, -50, 293 },
	{ 348, -50, 58 },
	{ 235, -50, -2 },
	{ 305, -50, 57 },
	{ 285, -50, 134 },
	{ 496, -140, 526 },
	{ 609, -140, 370 },
	{ 496, -188, 188 },
	{ 465, -259, 403 },
	{ 370, -292, 354 },
	{ 250, -50, 122 },
	{ 180, -138, 64 },
	{ 235, -138, -2 },
	{ 61, -138, -148 },
	{ -35, -138, -182 },
	{ -185, -138, -3 },
	{ -135, -138, 86 },
	{ 39, -138, 231 },
	{ 94, -138, 166 },
	{ -43, -138, 51 },
	{ 43, -138, -51 },
	{ -10, -138, -50 },
	{ -51, -138, -2 },
	{ 94, -50, 166 },
	{ -43, -50, 51 },
	{ 180, -40, 64 },
	{ 94, -40, 166 },
	{ 180, -50, 64 },
	{ 78, -40, 152 },
	{ 164, -30, 50 },
	{ 78, -30, 152 },
	{ 164, -40, 50 },
	{ 62, -30, 139 },
	{ 147, -20, 36 },
	{ 62, -20, 139 },
	{ 147, -30, 36 },
	{ 45, -20, 125 },
	{ 131, -10, 23 },
	{ 45, -10, 125 },
	{ 131, -20, 23 },
	{ 29, -10, 112 },
	{ 115, 0, 9 },
	{ 29, 0, 112 },
	{ 115, -10, 9 },
	{ -43, 0, 51 },
	{ -51, -50, -2 },
	{ -51, 0, -2 },
	{ -10, -50, -50 },
	{ -10, 0, -50 },
	{ 43, -50, -51 },
	{ 43, 0, -51 },
	{ 361, -46, 197 },
	{ 285, -46, 134 },
	{ 424, -46, 122 },
	{ 348, -46, 58 },
	{ 194, -50, 396 },
	{ 194, -46, 396 },
	{ 118, -46, 332 },
	{ 118, -50, 332 },
	{ 257, -50, 320 },
	{ 257, -46, 320 },
	{ 181, -46, 257 },
	{ 181, -50, 257 },
	{ -110, -65, -92 },
	{ -9, -65, -8 },
	{ 89, -65, -125 },
	{ -12, -65, -209 },
	{ 149, -65, 125 },
	{ 247, -65, 8 },
	{ -107, -65, 109 },
	{ -208, -65, 24 },
	{ 51, -65, 242 },
};

CollisionHeader Ending_collisionHeader = {
	-550,
	-603,
	-354,
	620,
	35,
	587,
	130,
	Ending_vertices,
	238,
	Ending_polygons,
	Ending_polygonTypes,
	0,
	0,
	0
};

s32 FinaleCS[] = {
	CS_BEGIN_CUTSCENE(34, 3444),
	CS_TERMINATOR(81, 3400, 3444),
	CS_PLAY_BGM_LIST(3),
		CS_PLAY_BGM(0x0073 + 1, 1275, 1, 0, 0, 0, 0, 0, 0, 0, 0),
		CS_PLAY_BGM(0x0074 + 1, 1820, 1, 0, 0, 0, 0, 0, 0, 0, 0),
		CS_PLAY_BGM(0x0075 + 1, 2985, 1, 0, 0, 0, 0, 0, 0, 0, 0),
	CS_SCENE_TRANS_FX(5, 0, 20),
	CS_SCENE_TRANS_FX(11, 3382, 3386),
	CS_TEXT_LIST(11),
		CS_TEXT_DISPLAY_TEXTBOX(0x0E10, 1454, 1489, 0x0000, 0x0000, 0x0000),
		CS_TEXT_DISPLAY_TEXTBOX(0x0E11, 1484, 1574, 0x0000, 0x0000, 0x0000),
		CS_TEXT_DISPLAY_TEXTBOX(0x0E12, 1569, 1620, 0x0000, 0x0000, 0x0000),
		CS_TEXT_DISPLAY_TEXTBOX(0x0E13, 1636, 1760, 0x0000, 0x0000, 0x0000),
		CS_TEXT_DISPLAY_TEXTBOX(0x0E14, 1795, 1799, 0x0000, 0x0000, 0x0000),
		CS_TEXT_DISPLAY_TEXTBOX(0x0E15, 1801, 1827, 0x0000, 0x0000, 0x0000),
		CS_TEXT_DISPLAY_TEXTBOX(0x0E16, 2309, 2355, 0x0000, 0x0000, 0x0000),
		CS_TEXT_DISPLAY_TEXTBOX(0x0E17, 2380, 2410, 0x0000, 0x0000, 0x0000),
		CS_TEXT_DISPLAY_TEXTBOX(0x0E18, 2827, 2915, 0x0000, 0x0000, 0x0000),
		CS_TEXT_DISPLAY_TEXTBOX(0x0E20, 2949, 2980, 0x0000, 0x0000, 0x0000),
		CS_TEXT_DISPLAY_TEXTBOX(0x0E21, 2997, 3055, 0x0000, 0x0000, 0x0000),
	CS_TIME_LIST(1),
		CS_TIME(1, 1244, 1245, 8, 0, 0),
	CS_FADE_BGM_LIST(1),
		CS_FADE_BGM(0x0000, 1135, 1170, 0, 0, 0, 0, 0, 0, 0, 0),
	CS_CAM_POS_LIST(0, 551),
		CS_CAM_POS(0, 0, 0, 0x42340000, 21, 50, 17, 0),
		CS_CAM_POS(0, 0, 0, 0x42340000, 21, 50, 17, 0),
		CS_CAM_POS(0, 0, 0, 0x42700000, 116, 61, 97, 0),
		CS_CAM_POS(0, 0, 0, 0x42700000, 213, 43, 188, 0),
		CS_CAM_POS(0, 0, 0, 0x42700000, 323, -6, 324, 0),
		CS_CAM_POS(0, 0, 0, 0x42700000, 443, -11, 483, 0),
		CS_CAM_POS(0, 0, 0, 0x42700000, 444, -11, 485, 0),
		CS_CAM_POS(-1, 0, 0, 0x0, 0, 0, 0, 0),
	CS_CAM_POS_LIST(220, 653),
		CS_CAM_POS(0, 0, 0, 0x42700000, -977, 456, 944, 0),
		CS_CAM_POS(0, 0, 0, 0x42700000, -892, 419, 944, 0),
		CS_CAM_POS(0, 0, 0, 0x42700000, 9, 95, 1394, 0),
		CS_CAM_POS(0, 0, 0, 0x42700000, 525, 38, 1238, 0),
		CS_CAM_POS(0, 0, 0, 0x42700000, 618, 15, 645, 0),
		CS_CAM_POS(0, 0, 0, 0x42700000, 321, 2, 267, 0),
		CS_CAM_POS(0, 0, 0, 0x42700000, 375, 10, 171, 0),
		CS_CAM_POS(0, 0, 0, 0x42700000, 290, 29, 72, 0),
		CS_CAM_POS(-1, 0, 0, 0x0, 0, 0, 0, 0),
	CS_CAM_POS_LIST(490, 1349),
		CS_CAM_POS(0, 0, 0, 0x42200000, 278, -41, 233, 0),
		CS_CAM_POS(0, 0, 0, 0x42200000, 278, -41, 233, 0),
		CS_CAM_POS(0, 0, 0, 0x42200000, 278, -41, 233, 0),
		CS_CAM_POS(0, 0, 0, 0x42200000, 278, -41, 233, 0),
		CS_CAM_POS(0, 0, 0, 0x42700000, 244, 0, 205, 0),
		CS_CAM_POS(0, 0, 0, 0x42700000, 264, 2, 222, 0),
		CS_CAM_POS(0, 0, 0, 0x42700000, 267, 2, 142, 0),
		CS_CAM_POS(0, 0, 0, 0x42700000, 180, 4, 151, 0),
		CS_CAM_POS(0, 0, 0, 0x42700000, 184, 6, 241, 0),
		CS_CAM_POS(0, 0, 0, 0x42700000, 234, 6, 261, 0),
		CS_CAM_POS(0, 0, 0, 0x42480000, 321, 1, 335, 0),
		CS_CAM_POS(0, 0, 0, 0x42480000, 338, -1, 470, 0),
		CS_CAM_POS(0, 0, 0, 0x42480000, 256, 8, 512, 0),
		CS_CAM_POS(0, 0, 0, 0x42480000, 196, 7, 453, 0),
		CS_CAM_POS(0, 0, 0, 0x41f00000, 196, 7, 453, 0),
		CS_CAM_POS(0, 0, 0, 0x41f00000, 196, 7, 453, 0),
		CS_CAM_POS(0, 0, 0, 0x41f00000, 196, 7, 453, 0),
		CS_CAM_POS(0, 0, 0, 0x41f00000, 196, 7, 453, 0),
		CS_CAM_POS(-1, 0, 0, 0x0, 0, 0, 0, 0),
	CS_CAM_POS_LIST(1243, 1784),
		CS_CAM_POS(0, 0, 0, 0x42700000, 416, 5, 367, 0),
		CS_CAM_POS(0, 0, 0, 0x42700000, 416, 5, 367, 0),
		CS_CAM_POS(0, 0, 0, 0x42700000, 416, 5, 367, 0),
		CS_CAM_POS(0, 0, 0, 0x42700000, 416, 5, 367, 0),
		CS_CAM_POS(0, 0, 0, 0x42700000, 402, 5, 376, 0),
		CS_CAM_POS(0, 0, 0, 0x42500000, 348, -1, 364, 0),
		CS_CAM_POS(0, 0, 0, 0x42340000, 384, -1, 310, 0),
		CS_CAM_POS(0, 0, 0, 0x42340000, 384, -1, 310, 0),
		CS_CAM_POS(0, 0, 0, 0x42340000, 384, -1, 310, 0),
		CS_CAM_POS(-1, 0, 0, 0x0, 0, 0, 0, 0),
	CS_CAM_POS_LIST(1622, 1873),
		CS_CAM_POS(0, 0, 0, 0x42700000, 454, 6, 369, 0),
		CS_CAM_POS(0, 0, 0, 0x42700000, 454, 6, 369, 0),
		CS_CAM_POS(0, 0, 0, 0x42700000, 454, 6, 369, 0),
		CS_CAM_POS(0, 0, 0, 0x42700000, 464, 6, 353, 0),
		CS_CAM_POS(0, 0, 0, 0x42700000, 462, 0, 325, 0),
		CS_CAM_POS(0, 0, 0, 0x42700000, 434, -20, 302, 0),
		CS_CAM_POS(0, 0, 0, 0x42700000, 434, -20, 302, 0),
		CS_CAM_POS(0, 0, 0, 0x42700000, 434, -20, 302, 0),
		CS_CAM_POS(-1, 0, 0, 0x0, 0, 0, 0, 0),
	CS_CAM_POS_LIST(1800, 1881),
		CS_CAM_POS(0, 0, 0, 0x42340000, 445, -17, 424, 0),
		CS_CAM_POS(0, 0, 0, 0x42340000, 445, -17, 424, 0),
		CS_CAM_POS(0, 0, 0, 0x42340000, 445, -17, 424, 0),
		CS_CAM_POS(0, 0, 0, 0x42340000, 445, -17, 424, 0),
		CS_CAM_POS(-1, 0, 0, 0x0, 0, 0, 0, 0),
	CS_CAM_POS_LIST(1830, 2661),
		CS_CAM_POS(0, 0, 0, 0x42700000, 161, 76, -314, 0),
		CS_CAM_POS(0, 0, 0, 0x42700000, 300, -59, -82, 0),
		CS_CAM_POS(0, 0, 0, 0x42700000, 902, 127, 486, 0),
		CS_CAM_POS(0, 0, 0, 0x42700000, 286, 127, 724, 0),
		CS_CAM_POS(0, 0, 0, 0x42700000, -189, 127, 997, 0),
		CS_CAM_POS(-1, 0, 0, 0x0, 0, 0, 0, 0),
	CS_CAM_POS_LIST(2295, 2376),
		CS_CAM_POS(0, 0, 0, 0x42500000, 385, -12, 310, 0),
		CS_CAM_POS(0, 0, 0, 0x42500000, 385, -12, 310, 0),
		CS_CAM_POS(0, 0, 0, 0x42500000, 385, -12, 310, 0),
		CS_CAM_POS(0, 0, 0, 0x42500000, 385, -12, 310, 0),
		CS_CAM_POS(-1, 0, 0, 0x0, 0, 0, 0, 0),
	CS_CAM_POS_LIST(2424, 3165),
		CS_CAM_POS(0, 0, 0, 0x42700000, 1255, 128, 141, 0),
		CS_CAM_POS(0, 0, 0, 0x42700000, 773, 129, 429, 0),
		CS_CAM_POS(0, 0, 0, 0x42700000, 291, 131, 716, 0),
		CS_CAM_POS(0, 0, 0, 0x42700000, -191, 133, 1004, 0),
		CS_CAM_POS(-1, 0, 0, 0x0, 0, 0, 0, 0),
	CS_CAM_POS_LIST(2764, 2985),
		CS_CAM_POS(0, 0, 0, 0x42340000, 416, 0, 390, 0),
		CS_CAM_POS(0, 0, 0, 0x42340000, 416, 0, 390, 0),
		CS_CAM_POS(0, 0, 0, 0x42340000, 392, 0, 418, 0),
		CS_CAM_POS(0, 0, 0, 0x42340000, 392, 0, 418, 0),
		CS_CAM_POS(0, 0, 0, 0x42340000, 392, 0, 418, 0),
		CS_CAM_POS(-1, 0, 0, 0x0, 0, 0, 0, 0),
	CS_CAM_POS_LIST(2920, 3131),
		CS_CAM_POS(0, 0, 0, 0x42200000, 479, 6, 365, 0),
		CS_CAM_POS(0, 0, 0, 0x42200000, 479, 6, 365, 0),
		CS_CAM_POS(0, 0, 0, 0x42200000, 479, 6, 365, 0),
		CS_CAM_POS(0, 0, 0, 0x42200000, 448, 5, 370, 0),
		CS_CAM_POS(0, 0, 0, 0x42200000, 448, 5, 370, 0),
		CS_CAM_POS(0, 0, 0, 0x42200000, 448, 5, 370, 0),
		CS_CAM_POS(-1, 0, 0, 0x0, 0, 0, 0, 0),
	CS_CAM_POS_LIST(3081, 3472),
		CS_CAM_POS(0, 0, 0, 0x42340000, 459, 0, 435, 0),
		CS_CAM_POS(0, 0, 0, 0x42340000, 459, 0, 435, 0),
		CS_CAM_POS(0, 0, 0, 0x42340000, 459, 0, 435, 0),
		CS_CAM_POS(0, 0, 0, 0x42340000, 470, 0, 456, 0),
		CS_CAM_POS(0, 0, 0, 0x42480000, 522, 0, 532, 0),
		CS_CAM_POS(0, 0, 0, 0x425c0000, 672, -1, 732, 0),
		CS_CAM_POS(0, 0, 0, 0x42700000, 916, -4, 1049, 0),
		CS_CAM_POS(0, 0, 0, 0x42700000, 2105, -5, 2969, 0),
		CS_CAM_POS(0, 0, 0, 0x42700000, 2105, -5, 2969, 0),
		CS_CAM_POS(0, 0, 0, 0x42700000, 2105, -5, 2969, 0),
		CS_CAM_POS(-1, 0, 0, 0x0, 0, 0, 0, 0),
	CS_CAM_FOCUS_POINT_LIST(0, 570),
		CS_CAM_FOCUS_POINT(0, 0, 20, 0x42340000, 12, 35, 10, 0),
		CS_CAM_FOCUS_POINT(0, 0, 90, 0x42340000, 12, 35, 10, 0),
		CS_CAM_FOCUS_POINT(0, 0, 45, 0x42700000, 78, 39, 65, 0),
		CS_CAM_FOCUS_POINT(0, 0, 40, 0x42700000, 172, 40, 152, 0),
		CS_CAM_FOCUS_POINT(0, 0, 35, 0x42700000, 283, -5, 285, 0),
		CS_CAM_FOCUS_POINT(0, 0, 300, 0x42700000, 411, -4, 439, 0),
		CS_CAM_FOCUS_POINT(0, 0, 20, 0x42700000, 412, -5, 441, 0),
		CS_CAM_FOCUS_POINT(-1, 0, 0, 0x0, 0, 0, 0, 0),
	CS_CAM_FOCUS_POINT_LIST(220, 702),
		CS_CAM_FOCUS_POINT(0, 0, 20, 0x42700000, 60, 7, 56, 0),
		CS_CAM_FOCUS_POINT(0, 0, 37, 0x42700000, 60, 7, 56, 0),
		CS_CAM_FOCUS_POINT(0, 0, 75, 0x42700000, 60, 7, 56, 0),
		CS_CAM_FOCUS_POINT(0, 0, 45, 0x42700000, 60, 7, 56, 0),
		CS_CAM_FOCUS_POINT(0, 0, 45, 0x42700000, 60, 7, 56, 0),
		CS_CAM_FOCUS_POINT(0, 0, 80, 0x42700000, 226, -1, 190, 0),
		CS_CAM_FOCUS_POINT(0, 0, 80, 0x42700000, 226, -1, 190, 0),
		CS_CAM_FOCUS_POINT(0, 0, 50, 0x42700000, 226, -1, 190, 0),
		CS_CAM_FOCUS_POINT(-1, 0, 0, 0x0, 0, 0, 0, 0),
	CS_CAM_FOCUS_POINT_LIST(490, 1368),
		CS_CAM_FOCUS_POINT(0, 0, 50, 0x42200000, 258, -53, 216, 0),
		CS_CAM_FOCUS_POINT(0, 0, 25, 0x42200000, 258, -53, 216, 0),
		CS_CAM_FOCUS_POINT(0, 0, 25, 0x42200000, 258, -53, 216, 0),
		CS_CAM_FOCUS_POINT(0, 0, 75, 0x42200000, 258, -53, 216, 0),
		CS_CAM_FOCUS_POINT(0, 0, 100, 0x42700000, 230, 5, 193, 0),
		CS_CAM_FOCUS_POINT(0, 0, 50, 0x42700000, 231, 1, 193, 0),
		CS_CAM_FOCUS_POINT(0, 0, 50, 0x42700000, 231, 0, 193, 0),
		CS_CAM_FOCUS_POINT(0, 0, 50, 0x42700000, 231, 0, 194, 0),
		CS_CAM_FOCUS_POINT(0, 0, 50, 0x42700000, 231, -3, 193, 0),
		CS_CAM_FOCUS_POINT(0, 0, 48, 0x42700000, 229, -8, 192, 0),
		CS_CAM_FOCUS_POINT(0, 0, 70, 0x42480000, 322, -9, 271, 0),
		CS_CAM_FOCUS_POINT(0, 0, 55, 0x42480000, 335, -5, 434, 0),
		CS_CAM_FOCUS_POINT(0, 0, 65, 0x42480000, 304, -11, 463, 0),
		CS_CAM_FOCUS_POINT(0, 0, 55, 0x42480000, 265, -4, 435, 0),
		CS_CAM_FOCUS_POINT(0, 0, 10, 0x41f00000, 262, 1, 426, 0),
		CS_CAM_FOCUS_POINT(0, 0, 20, 0x41f00000, 262, 1, 426, 0),
		CS_CAM_FOCUS_POINT(0, 0, 40, 0x41f00000, 262, 1, 426, 0),
		CS_CAM_FOCUS_POINT(0, 0, 20, 0x41f00000, 262, 1, 426, 0),
		CS_CAM_FOCUS_POINT(-1, 0, 0, 0x0, 0, 0, 0, 0),
	CS_CAM_FOCUS_POINT_LIST(1243, 1803),
		CS_CAM_FOCUS_POINT(0, 0, 20, 0x42700000, 436, 5, 354, 0),
		CS_CAM_FOCUS_POINT(0, 0, 200, 0x42700000, 436, 5, 354, 0),
		CS_CAM_FOCUS_POINT(0, 0, 40, 0x42700000, 436, 5, 354, 0),
		CS_CAM_FOCUS_POINT(0, 0, 50, 0x42700000, 436, 5, 354, 0),
		CS_CAM_FOCUS_POINT(0, 0, 50, 0x42700000, 422, 5, 363, 0),
		CS_CAM_FOCUS_POINT(0, 0, 60, 0x42500000, 379, -3, 365, 0),
		CS_CAM_FOCUS_POINT(0, 0, 50, 0x42340000, 397, -2, 330, 0),
		CS_CAM_FOCUS_POINT(0, 0, 50, 0x42340000, 397, -2, 330, 0),
		CS_CAM_FOCUS_POINT(0, 0, 20, 0x42340000, 397, -2, 330, 0),
		CS_CAM_FOCUS_POINT(-1, 0, 0, 0x0, 0, 0, 0, 0),
	CS_CAM_FOCUS_POINT_LIST(1622, 1892),
		CS_CAM_FOCUS_POINT(0, 0, 20, 0x42700000, 436, 6, 354, 0),
		CS_CAM_FOCUS_POINT(0, 0, 30, 0x42700000, 436, 6, 354, 0),
		CS_CAM_FOCUS_POINT(0, 0, 40, 0x42700000, 436, 6, 354, 0),
		CS_CAM_FOCUS_POINT(0, 0, 40, 0x42700000, 436, 6, 354, 0),
		CS_CAM_FOCUS_POINT(0, 0, 40, 0x42700000, 437, 2, 354, 0),
		CS_CAM_FOCUS_POINT(0, 0, 40, 0x42700000, 426, -5, 356, 0),
		CS_CAM_FOCUS_POINT(0, 0, 20, 0x42700000, 426, -5, 356, 0),
		CS_CAM_FOCUS_POINT(0, 0, 20, 0x42700000, 426, -5, 356, 0),
		CS_CAM_FOCUS_POINT(-1, 0, 0, 0x0, 0, 0, 0, 0),
	CS_CAM_FOCUS_POINT_LIST(1800, 1900),
		CS_CAM_FOCUS_POINT(0, 0, 20, 0x42340000, 443, -7, 387, 0),
		CS_CAM_FOCUS_POINT(0, 0, 20, 0x42340000, 443, -7, 387, 0),
		CS_CAM_FOCUS_POINT(0, 0, 20, 0x42340000, 443, -7, 387, 0),
		CS_CAM_FOCUS_POINT(0, 0, 20, 0x42340000, 443, -7, 387, 0),
		CS_CAM_FOCUS_POINT(-1, 0, 0, 0x0, 0, 0, 0, 0),
	CS_CAM_FOCUS_POINT_LIST(1830, 2680),
		CS_CAM_FOCUS_POINT(0, 0, 20, 0x42700000, 186, 81, -266, 0),
		CS_CAM_FOCUS_POINT(0, 0, 70, 0x42700000, 324, -50, -32, 0),
		CS_CAM_FOCUS_POINT(0, 0, 270, 0x42700000, 957, 138, 577, 0),
		CS_CAM_FOCUS_POINT(0, 0, 450, 0x42700000, 340, 138, 816, 0),
		CS_CAM_FOCUS_POINT(0, 0, 20, 0x42700000, -134, 138, 1088, 0),
		CS_CAM_FOCUS_POINT(-1, 0, 0, 0x0, 0, 0, 0, 0),
	CS_CAM_FOCUS_POINT_LIST(2295, 2395),
		CS_CAM_FOCUS_POINT(0, 0, 20, 0x42500000, 414, 0, 357, 0),
		CS_CAM_FOCUS_POINT(0, 0, 20, 0x42500000, 414, 0, 357, 0),
		CS_CAM_FOCUS_POINT(0, 0, 20, 0x42500000, 414, 0, 357, 0),
		CS_CAM_FOCUS_POINT(0, 0, 20, 0x42500000, 414, 0, 357, 0),
		CS_CAM_FOCUS_POINT(-1, 0, 0, 0x0, 0, 0, 0, 0),
	CS_CAM_FOCUS_POINT_LIST(2424, 3184),
		CS_CAM_FOCUS_POINT(0, 0, 20, 0x42700000, 1542, 197, 623, 0),
		CS_CAM_FOCUS_POINT(0, 0, 350, 0x42700000, 1060, 198, 911, 0),
		CS_CAM_FOCUS_POINT(0, 0, 350, 0x42700000, 579, 200, 1198, 0),
		CS_CAM_FOCUS_POINT(0, 0, 20, 0x42700000, 97, 201, 1485, 0),
		CS_CAM_FOCUS_POINT(-1, 0, 0, 0x0, 0, 0, 0, 0),
	CS_CAM_FOCUS_POINT_LIST(2764, 3004),
		CS_CAM_FOCUS_POINT(0, 0, 20, 0x42340000, 441, 0, 340, 0),
		CS_CAM_FOCUS_POINT(0, 0, 40, 0x42340000, 441, 0, 340, 0),
		CS_CAM_FOCUS_POINT(0, 0, 60, 0x42340000, 417, 0, 368, 0),
		CS_CAM_FOCUS_POINT(0, 0, 80, 0x42340000, 417, 0, 368, 0),
		CS_CAM_FOCUS_POINT(0, 0, 20, 0x42340000, 417, 0, 368, 0),
		CS_CAM_FOCUS_POINT(-1, 0, 0, 0x0, 0, 0, 0, 0),
	CS_CAM_FOCUS_POINT_LIST(2920, 3150),
		CS_CAM_FOCUS_POINT(0, 0, 20, 0x42200000, 423, 0, 371, 0),
		CS_CAM_FOCUS_POINT(0, 0, 50, 0x42200000, 423, 0, 371, 0),
		CS_CAM_FOCUS_POINT(0, 0, 50, 0x42200000, 423, 0, 371, 0),
		CS_CAM_FOCUS_POINT(0, 0, 50, 0x42200000, 392, 0, 376, 0),
		CS_CAM_FOCUS_POINT(0, 0, 20, 0x42200000, 392, 0, 376, 0),
		CS_CAM_FOCUS_POINT(0, 0, 20, 0x42200000, 392, 0, 376, 0),
		CS_CAM_FOCUS_POINT(-1, 0, 0, 0x0, 0, 0, 0, 0),
	CS_CAM_FOCUS_POINT_LIST(3081, 3491),
		CS_CAM_FOCUS_POINT(0, 0, 20, 0x42340000, 431, 0, 386, 0),
		CS_CAM_FOCUS_POINT(0, 0, 40, 0x42340000, 431, 0, 386, 0),
		CS_CAM_FOCUS_POINT(0, 0, 30, 0x42340000, 431, 0, 386, 0),
		CS_CAM_FOCUS_POINT(0, 0, 50, 0x42340000, 442, 0, 407, 0),
		CS_CAM_FOCUS_POINT(0, 0, 50, 0x42480000, 492, 0, 485, 0),
		CS_CAM_FOCUS_POINT(0, 0, 30, 0x425c0000, 639, 1, 687, 0),
		CS_CAM_FOCUS_POINT(0, 0, 50, 0x42700000, 884, 4, 1003, 0),
		CS_CAM_FOCUS_POINT(0, 0, 50, 0x42700000, 2084, 11, 2920, 0),
		CS_CAM_FOCUS_POINT(0, 0, 50, 0x42700000, 2084, 11, 2920, 0),
		CS_CAM_FOCUS_POINT(0, 0, 20, 0x42700000, 2084, 11, 2920, 0),
		CS_CAM_FOCUS_POINT(-1, 0, 0, 0x0, 0, 0, 0, 0),
	CS_NPC_ACTION_LIST(17, 16),
		CS_NPC_ACTION(0x0000, 0, 370, 0x0, 0x238e, 0x0, 227, -50, 190, 227, -50, 190, 0, 0, 0),
		CS_NPC_ACTION(0x0009, 370, 491, 0x0, 0x238e, 0x0, 227, -50, 190, 227, -50, 190, 0, 0, 0),
		CS_NPC_ACTION(0x0001, 491, 721, 0x0, 0x238e, 0x0, 227, -50, 190, 227, -50, 190, 0, 0, 0),
		CS_NPC_ACTION(0x0003, 721, 900, 0x0, 0x238e, 0x0, 227, -50, 190, 227, -50, 190, 0, 0, 0),
		CS_NPC_ACTION(0x000A, 900, 982, 0x0, 0x238e, 0x0, 227, -50, 190, 318, -50, 266, 0, 0, 0),
		CS_NPC_ACTION(0x0002, 982, 1093, 0x0, 0x5b6, 0x0, 318, -50, 266, 340, -50, 429, 0, 0, 0),
		CS_NPC_ACTION(0x0001, 1093, 1155, 0x0, 0x567, 0x0, 340, -50, 429, 340, -50, 429, 0, 0, 0),
		CS_NPC_ACTION(0x000B, 1155, 1380, 0x0, 0x5ac8, 0x0, 340, -50, 429, 340, -50, 429, 0, 0, 0),
		CS_NPC_ACTION(0x0002, 1380, 1440, 0x0, 0x5a80, 0x0, 340, -50, 429, 399, -50, 376, 0, 0, 0),
		CS_NPC_ACTION(0x0001, 1440, 1680, 0x0, 0x5a80, 0x0, 399, -50, 376, 399, -50, 376, 0, 0, 0),
		CS_NPC_ACTION(0x0005, 1680, 2320, 0x0, 0x1481, 0x0, 399, -50, 376, 398, -50, 375, 0, 0, 0),
		CS_NPC_ACTION(0x0006, 2320, 2776, 0x0, 0x1481, 0x0, 398, -50, 375, 399, -50, 376, 0, 0, 0),
		CS_NPC_ACTION(0x0004, 2776, 2944, 0x0, 0x53d3, 0x0, 399, -50, 376, 399, -50, 376, 0, 0, 0),
		CS_NPC_ACTION(0x0007, 2944, 3070, 0x0, 0x53d3, 0x0, 399, -50, 376, 399, -50, 376, 0, 0, 0),
		CS_NPC_ACTION(0x0005, 3070, 3100, 0x0, 0x1454, 0x0, 399, -50, 376, 399, -50, 376, 0, 0, 0),
		CS_NPC_ACTION(0x0008, 3100, 5000, 0x0, 0x1454, 0x0, 399, -50, 376, 399, -50, 376, 0, 0, 0),
	CS_NPC_ACTION_LIST(16, 12),
		CS_NPC_ACTION(0x0000, 0, 1244, 0x0, 0xffffd4ca, 0x0, 437, -4, 354, 437, -4, 354, 0, 0, 0),
		CS_NPC_ACTION(0x0001, 1244, 1345, 0x0, 0xffffd4ca, 0x0, 437, -4, 354, 437, -50, 354, 0, 0, 0),
		CS_NPC_ACTION(0x0001, 1345, 1360, 0x0, 0xffffd4ca, 0x0, 437, -50, 354, 437, -50, 354, 0, 0, 0),
		CS_NPC_ACTION(0x0004, 1360, 1454, 0x0, 0xffffd4ca, 0x0, 437, -50, 354, 437, -50, 354, 0, 0, 0),
		CS_NPC_ACTION(0x0005, 1454, 1623, 0x0, 0xffffd4ca, 0x0, 437, -50, 354, 437, -50, 354, 0, 0, 0),
		CS_NPC_ACTION(0x0006, 1623, 1801, 0x0, 0xffffd555, 0x0, 437, -50, 354, 437, -50, 354, 0, 0, 0),
		CS_NPC_ACTION(0x0007, 1801, 1801, 0x0, 0xffffd555, 0x0, 437, -50, 354, 437, -50, 354, 0, 0, 0),
		CS_NPC_ACTION(0x0002, 1801, 2309, 0x0, 0xffffd555, 0x0, 437, -50, 354, 437, -50, 354, 0, 0, 0),
		CS_NPC_ACTION(0x0008, 2309, 2790, 0x0, 0xffffd555, 0x0, 437, -50, 354, 437, -50, 354, 0, 0, 0),
		CS_NPC_ACTION(0x0002, 2790, 2823, 0x0, 0xffffd555, 0x0, 437, -50, 354, 437, -50, 354, 0, 0, 0),
		CS_NPC_ACTION(0x0009, 2823, 3100, 0x0, 0xffffd4ca, 0x0, 437, -50, 354, 437, -50, 354, 0, 0, 0),
		CS_NPC_ACTION(0x000A, 3100, 5000, 0x0, 0xffffd555, 0x0, 437, -50, 354, 437, -50, 354, 0, 0, 0),
	CS_NPC_ACTION_LIST(36, 4),
		CS_NPC_ACTION(0x0000, 1146, 1188, 0x0, 0x0, 0x0, 437, -50, 354, 437, -50, 354, 0, 0, 0),
		CS_NPC_ACTION(0x0001, 1188, 1260, 0x0, 0x0, 0x0, 437, -50, 354, 437, -50, 354, 0, 0, 0),
		CS_NPC_ACTION(0x0002, 1260, 1333, 0x0, 0x0, 0x0, 437, -50, 354, 437, -50, 354, 0, 0, 0),
		CS_NPC_ACTION(0x0003, 1333, 1370, 0x0, 0x0, 0x0, 437, -50, 354, 437, -50, 354, 0, 0, 0),
	CS_END(),
};

