#include "ultra64.h"
#include "z64.h"
#include "macros.h"
#include "UnicornFountain_scene.h"

#include "segment_symbols.h"
#include "command_macros_base.h"
#include "z64cutscene_commands.h"
#include "variables.h"

SCmdSoundSettings UnicornFountain_scene_header00_cmd00 = { 0x15, 0x00, 0x00, 0x00, 0x00, 0x00, 0x13, 0x28 };

SCmdRoomList UnicornFountain_scene_header00_cmd01 = { 0x04, 1, (u32)&UnicornFountain_scene_roomList };

SCmdMiscSettings UnicornFountain_scene_header00_cmd02 = { 0x19, 0x00, 0x07 };

SCmdColHeader UnicornFountain_scene_header00_cmd03 = { 0x03, 0x00, (u32)&UnicornFountain_collisionHeader };

SCmdEntranceList UnicornFountain_scene_header00_cmd04 = { 0x06, 0x00, (u32)&UnicornFountain_scene_header00_entranceList };

SCmdSpecialFiles UnicornFountain_scene_header00_cmd05 = { 0x07, 0x00, 0x0002 };

SCmdSpawnList UnicornFountain_scene_header00_cmd06 = { 0x00, 1, (u32)&UnicornFountain_scene_header00_startPositionList };

SCmdSkyboxSettings UnicornFountain_scene_header00_cmd07 = { 0x11, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01 };

SCmdLightSettingList UnicornFountain_scene_header00_cmd08 = { 0x0F, 1, (u32)&UnicornFountain_scene_header00_lightSettings };

SCmdCutsceneData UnicornFountain_scene_header00_cmd09 = { 0x17, 0x00, (u32)&UnicornFountain_scene_header00_cutscene };

SCmdEndMarker UnicornFountain_scene_header00_cmd10 = { 0x14, 0x00, 0x00 };


ActorEntry UnicornFountain_scene_header00_startPositionList[] = {
	{ ACTOR_PLAYER, 0, 22, -25, 0, 32768, 0, 0x0FFF },
};

RomFile UnicornFountain_scene_roomList[] = {
	{ (u32)_UnicornFountain_room_0SegmentRomStart, (u32)_UnicornFountain_room_0SegmentRomEnd },
};

EntranceEntry UnicornFountain_scene_header00_entranceList[1] = {
	{ 0, 0 },
};

LightSettings UnicornFountain_scene_header00_lightSettings[1] = {
	{ 62, 99, 143, 73, 73, 73, 219, 216, 170, 183, 183, 183, 21, 104, 133, 184, 177, 196, 0x07e1, 12800 },
};

u32 UnicornFountain_polygonTypes[] = {
	 0x00000000, 0x00000000,
};

CollisionPoly UnicornFountain_polygons[] = {
	{ 0x0000, 0x0000, 0x0001, 0x0002, 0x0000, 0x7fff, 0x0000, 0x001e },
	{ 0x0000, 0x0000, 0x0002, 0x0003, 0x0000, 0x7fff, 0x0000, 0x001e },
	{ 0x0000, 0x0000, 0x0003, 0x0004, 0x0000, 0x7fff, 0x0000, 0x001e },
	{ 0x0000, 0x0000, 0x0004, 0x0005, 0x0000, 0x7fff, 0x0000, 0x001e },
	{ 0x0000, 0x0000, 0x0005, 0x0006, 0x0000, 0x7fff, 0x0000, 0x001e },
	{ 0x0000, 0x0000, 0x0006, 0x0007, 0x0000, 0x7fff, 0x0000, 0x001e },
	{ 0x0000, 0x0000, 0x0007, 0x0008, 0x0000, 0x7fff, 0x0000, 0x001e },
	{ 0x0000, 0x0000, 0x0008, 0x0009, 0x0000, 0x7fff, 0x0000, 0x001e },
	{ 0x0000, 0x0000, 0x0009, 0x000a, 0x0000, 0x7fff, 0x0000, 0x001e },
	{ 0x0000, 0x0000, 0x000a, 0x000b, 0x0000, 0x7fff, 0x0000, 0x001e },
	{ 0x0000, 0x000c, 0x000d, 0x000e, 0xffcc, 0x798d, 0x281e, 0x0156 },
	{ 0x0000, 0x000c, 0x000e, 0x000f, 0x0000, 0x79a2, 0x27dd, 0x0154 },
	{ 0x0000, 0x0010, 0x0011, 0x000d, 0xebab, 0x7980, 0x22c4, 0x0137 },
	{ 0x0000, 0x0010, 0x000d, 0x000c, 0xebd5, 0x798b, 0x22b4, 0x0136 },
	{ 0x0000, 0x0012, 0x0013, 0x0011, 0xdd40, 0x798f, 0x1401, 0x00df },
	{ 0x0000, 0x0012, 0x0011, 0x0010, 0xdcde, 0x7975, 0x13f3, 0x00e0 },
	{ 0x0000, 0x0014, 0x0015, 0x0013, 0xd823, 0x79a2, 0x0000, 0x006a },
	{ 0x0000, 0x0014, 0x0013, 0x0012, 0xd7c2, 0x7982, 0xffb4, 0x0069 },
	{ 0x0000, 0x000f, 0x000e, 0x0016, 0x13f2, 0x7998, 0x22a7, 0x0135 },
	{ 0x0000, 0x000f, 0x0016, 0x0017, 0x13ed, 0x798f, 0x22cc, 0x0137 },
	{ 0x0000, 0x0017, 0x0016, 0x0018, 0x22b5, 0x798b, 0x142d, 0x00e1 },
	{ 0x0000, 0x0017, 0x0018, 0x0019, 0x22b4, 0x798b, 0x142b, 0x00e1 },
	{ 0x0000, 0x0019, 0x0018, 0x001a, 0x281e, 0x798d, 0x0034, 0x006c },
	{ 0x0000, 0x0019, 0x001a, 0x001b, 0x27dd, 0x79a2, 0x0000, 0x006a },
	{ 0x0000, 0x001b, 0x001a, 0x001c, 0x2286, 0x79a5, 0xec21, 0xfff6 },
	{ 0x0000, 0x001b, 0x001c, 0x001d, 0x22e6, 0x798c, 0xec2f, 0xfff7 },
	{ 0x0000, 0x001d, 0x001c, 0x001e, 0x1441, 0x798d, 0xdd5e, 0xffa0 },
	{ 0x0000, 0x001d, 0x001e, 0x001f, 0x1417, 0x7998, 0xdd6e, 0xffa0 },
	{ 0x0000, 0x001f, 0x001e, 0x0020, 0x0000, 0x7989, 0xd7d5, 0xff80 },
	{ 0x0000, 0x001f, 0x0020, 0x0021, 0x0000, 0x7989, 0xd7d5, 0xff80 },
	{ 0x0000, 0x0021, 0x0020, 0x0022, 0xec2c, 0x7992, 0xdd32, 0xff9f },
	{ 0x0000, 0x0021, 0x0022, 0x0023, 0xec2f, 0x798c, 0xdd1a, 0xff9e },
	{ 0x0000, 0x0023, 0x0022, 0x0015, 0xdd4b, 0x798b, 0xebd3, 0xfff4 },
	{ 0x0000, 0x0023, 0x0015, 0x0014, 0xdd74, 0x79a7, 0xec37, 0xfff6 },
	{ 0x0000, 0x0000, 0x0023, 0x0014, 0xff31, 0x7fff, 0xff89, 0x001c },
	{ 0x0000, 0x0000, 0x0014, 0x0001, 0xff30, 0x7fff, 0xff83, 0x001c },
	{ 0x0000, 0x0001, 0x0014, 0x0012, 0xff10, 0x7fff, 0xfffe, 0x001f },
	{ 0x0000, 0x0001, 0x0012, 0x0002, 0xff0e, 0x7fff, 0xfffc, 0x001f },
	{ 0x0000, 0x0002, 0x0012, 0x0010, 0xff2f, 0x7fff, 0x0076, 0x0022 },
	{ 0x0000, 0x0002, 0x0010, 0x0003, 0xff31, 0x7fff, 0x0077, 0x0022 },
	{ 0x0000, 0x0003, 0x0010, 0x000c, 0xff88, 0x7fff, 0x00ce, 0x0024 },
	{ 0x0000, 0x0003, 0x000c, 0x0004, 0xff83, 0x7fff, 0x00ce, 0x0024 },
	{ 0x0000, 0x0004, 0x000c, 0x000f, 0x0000, 0x7fff, 0x00ef, 0x0024 },
	{ 0x0000, 0x0004, 0x000f, 0x0005, 0xfffc, 0x7fff, 0x00f2, 0x0024 },
	{ 0x0000, 0x0005, 0x000f, 0x0017, 0x0077, 0x7fff, 0x00d0, 0x0024 },
	{ 0x0000, 0x0005, 0x0017, 0x0006, 0x0074, 0x7fff, 0x00d5, 0x0024 },
	{ 0x0000, 0x0006, 0x0017, 0x0019, 0x00d0, 0x7fff, 0x0079, 0x0022 },
	{ 0x0000, 0x0006, 0x0019, 0x0007, 0x00d0, 0x7fff, 0x0077, 0x0022 },
	{ 0x0000, 0x0007, 0x0019, 0x001b, 0x00ef, 0x7fff, 0x0000, 0x001f },
	{ 0x0000, 0x0007, 0x001b, 0x0008, 0x00f2, 0x7fff, 0x0004, 0x001f },
	{ 0x0000, 0x0008, 0x001b, 0x001d, 0x00d1, 0x7fff, 0xff8a, 0x001c },
	{ 0x0000, 0x0008, 0x001d, 0x0009, 0x00d3, 0x7fff, 0xff8b, 0x001c },
	{ 0x0000, 0x0009, 0x001d, 0x001f, 0x0078, 0x7fff, 0xff31, 0x001a },
	{ 0x0000, 0x0009, 0x001f, 0x000a, 0x007b, 0x7fff, 0xff31, 0x001a },
	{ 0x0000, 0x000a, 0x001f, 0x0021, 0x0000, 0x7fff, 0xff11, 0x0019 },
	{ 0x0000, 0x000a, 0x0021, 0x000b, 0x0004, 0x7fff, 0xff0e, 0x0019 },
	{ 0x0000, 0x000b, 0x0021, 0x0023, 0xff8a, 0x7fff, 0xff2f, 0x001a },
	{ 0x0000, 0x000b, 0x0023, 0x0000, 0xff89, 0x7fff, 0xff31, 0x001a },
	{ 0x0000, 0x0024, 0x0025, 0x0026, 0x0000, 0xdc70, 0x7af6, 0x0291 },
	{ 0x0000, 0x0027, 0x0028, 0x0029, 0x9542, 0xdd79, 0xc25f, 0xfe48 },
	{ 0x0000, 0x002a, 0x002b, 0x002c, 0x6ab9, 0xdd65, 0xc262, 0xfe4b },
	{ 0x0000, 0x0024, 0x002d, 0x0025, 0x0000, 0xdc70, 0x7af6, 0x0291 },
	{ 0x0000, 0x0027, 0x002e, 0x0028, 0x9542, 0xdd79, 0xc25f, 0xfe48 },
	{ 0x0000, 0x002a, 0x002f, 0x002b, 0x6ab9, 0xdd65, 0xc262, 0xfe4b },
	{ 0x0000, 0x0030, 0x0027, 0x0029, 0xc00e, 0xfab0, 0x6ec1, 0x0285 },
	{ 0x0000, 0x0027, 0x0031, 0x002e, 0x0000, 0x7fff, 0x0000, 0xffeb },
	{ 0x0000, 0x0032, 0x0033, 0x002f, 0x4048, 0xf944, 0x6e7c, 0x0286 },
	{ 0x0000, 0x0034, 0x0035, 0x002d, 0x8023, 0xfa14, 0x0000, 0xfff3 },
	{ 0x0000, 0x0030, 0x0036, 0x0031, 0x6eda, 0x0000, 0x4000, 0x01a8 },
	{ 0x0000, 0x0036, 0x0037, 0x0028, 0x402b, 0xfab4, 0x915f, 0xfd66 },
	{ 0x0000, 0x0025, 0x0038, 0x0039, 0x7fdd, 0xfa14, 0x0000, 0xfff7 },
	{ 0x0000, 0x0039, 0x003a, 0x003b, 0x0000, 0x0000, 0x8000, 0xfd33 },
	{ 0x0000, 0x003c, 0x002c, 0x002b, 0xc015, 0xf96f, 0x914c, 0xfd63 },
	{ 0x0000, 0x003d, 0x003e, 0x003c, 0x9126, 0x0000, 0x4000, 0x01a4 },
	{ 0x0000, 0x003c, 0x002a, 0x002c, 0x0000, 0x7fff, 0x0000, 0xffeb },
	{ 0x0000, 0x0035, 0x0025, 0x002d, 0x0000, 0xd9d2, 0x7a2c, 0x028d },
	{ 0x0000, 0x0024, 0x003b, 0x003a, 0x0000, 0x7fff, 0x0000, 0xffeb },
	{ 0x0000, 0x0028, 0x003f, 0x0029, 0x9670, 0xd8f1, 0xc30d, 0xfe4d },
	{ 0x0000, 0x0033, 0x002b, 0x002f, 0x6987, 0xd8cd, 0xc313, 0xfe50 },
	{ 0x0000, 0x002a, 0x003e, 0x002f, 0x3ff2, 0xfaad, 0x6ec1, 0x0288 },
	{ 0x0000, 0x003e, 0x0032, 0x002f, 0x3fa4, 0xfa12, 0x6ee6, 0x0289 },
	{ 0x0000, 0x002b, 0x0040, 0x003d, 0xbfae, 0xfae5, 0x9174, 0xfd64 },
	{ 0x0000, 0x003d, 0x003c, 0x002b, 0xc060, 0xfa12, 0x9118, 0xfd62 },
	{ 0x0000, 0x0024, 0x003a, 0x002d, 0x8023, 0xfa0e, 0x0000, 0xfff3 },
	{ 0x0000, 0x003a, 0x0034, 0x002d, 0x8023, 0xfa12, 0x0002, 0xfff3 },
	{ 0x0000, 0x0039, 0x003b, 0x0025, 0x7fdd, 0xfa12, 0x0002, 0xfff7 },
	{ 0x0000, 0x003b, 0x0026, 0x0025, 0x7fdd, 0xfa0e, 0x0000, 0xfff7 },
	{ 0x0000, 0x0029, 0x003f, 0x0041, 0xbfdd, 0xf970, 0x6e94, 0x0284 },
	{ 0x0000, 0x0041, 0x0030, 0x0029, 0xc05e, 0xfa12, 0x6ee7, 0x0286 },
	{ 0x0000, 0x002e, 0x0031, 0x0028, 0x3feb, 0xf974, 0x914b, 0xfd65 },
	{ 0x0000, 0x0031, 0x0036, 0x0028, 0x3fa2, 0xfa12, 0x9119, 0xfd64 },
	{ 0x0000, 0x0027, 0x0030, 0x0031, 0x0000, 0x7fff, 0x0000, 0xffeb },
	{ 0x0000, 0x0030, 0x0041, 0x0036, 0x6eda, 0x0000, 0x4000, 0x01a8 },
	{ 0x0000, 0x0039, 0x0034, 0x003a, 0x0000, 0x0000, 0x8000, 0xfd33 },
	{ 0x0000, 0x003d, 0x0032, 0x003e, 0x9126, 0x0000, 0x4000, 0x01a4 },
	{ 0x0000, 0x003c, 0x003e, 0x002a, 0x0000, 0x7fff, 0x0000, 0xffeb },
	{ 0x0000, 0x0035, 0x0038, 0x0025, 0x0000, 0xd9d2, 0x7a2c, 0x028d },
	{ 0x0000, 0x0024, 0x0026, 0x003b, 0x0000, 0x7fff, 0x0000, 0xffeb },
	{ 0x0000, 0x0028, 0x0037, 0x003f, 0x9670, 0xd8f1, 0xc30d, 0xfe4d },
	{ 0x0000, 0x0033, 0x0040, 0x002b, 0x6986, 0xd8cd, 0xc313, 0xfe50 },
	{ 0x0000, 0x0042, 0x0043, 0x0044, 0x94fe, 0xde96, 0x3dc8, 0x0133 },
	{ 0x0000, 0x0045, 0x0046, 0x0047, 0x6b02, 0xde96, 0x3dc8, 0x0137 },
	{ 0x0000, 0x0048, 0x0049, 0x004a, 0x6cf3, 0x179e, 0x3ee7, 0x016e },
	{ 0x0000, 0x004b, 0x004c, 0x004d, 0x0000, 0x077c, 0x8038, 0xfd03 },
	{ 0x0000, 0x0048, 0x004e, 0x004f, 0x6cf3, 0x179e, 0xc119, 0xfe84 },
	{ 0x0000, 0x004f, 0x004b, 0x0050, 0x0000, 0x179e, 0x8233, 0xfd0d },
	{ 0x0000, 0x0051, 0x004b, 0x0052, 0x930d, 0x179e, 0xc119, 0xfe80 },
	{ 0x0000, 0x004c, 0x004a, 0x0053, 0x6ea9, 0x077c, 0xc01c, 0xfe80 },
	{ 0x0000, 0x0054, 0x0055, 0x0049, 0x0000, 0x077c, 0x7fc8, 0x02ef },
	{ 0x0000, 0x0056, 0x0049, 0x0057, 0x0000, 0x179e, 0x7dcd, 0x02e2 },
	{ 0x0000, 0x0052, 0x004d, 0x0058, 0x9157, 0x077c, 0xc01c, 0xfe7c },
	{ 0x0000, 0x0051, 0x0054, 0x0056, 0x930d, 0x179e, 0x3ee7, 0x016b },
	{ 0x0000, 0x0059, 0x0052, 0x0058, 0x9157, 0x077c, 0x3fe4, 0x0172 },
	{ 0x0000, 0x0044, 0x0046, 0x005a, 0x0000, 0xdc5e, 0x7af1, 0x0299 },
	{ 0x0000, 0x0045, 0x005b, 0x005c, 0x6a78, 0xdc5e, 0xc288, 0xfe54 },
	{ 0x0000, 0x005d, 0x005b, 0x005e, 0x0000, 0xde96, 0x8470, 0xfce9 },
	{ 0x0000, 0x005e, 0x0042, 0x005d, 0x9588, 0xdc5e, 0xc288, 0xfe51 },
	{ 0x0000, 0x004a, 0x0055, 0x0053, 0x6ea9, 0x077c, 0x3fe4, 0x0176 },
	{ 0x0000, 0x0042, 0x005f, 0x0043, 0x94fe, 0xde96, 0x3dc8, 0x0133 },
	{ 0x0000, 0x0045, 0x005a, 0x0046, 0x6b02, 0xde96, 0x3dc8, 0x0137 },
	{ 0x0000, 0x0048, 0x0057, 0x0049, 0x6cf3, 0x179e, 0x3ee7, 0x016e },
	{ 0x0000, 0x004b, 0x004e, 0x004c, 0x0000, 0x077c, 0x8038, 0xfd03 },
	{ 0x0000, 0x0048, 0x004a, 0x004e, 0x6cf3, 0x179e, 0xc119, 0xfe84 },
	{ 0x0000, 0x004f, 0x004e, 0x004b, 0x0000, 0x179e, 0x8233, 0xfd0d },
	{ 0x0000, 0x0051, 0x0050, 0x004b, 0x930d, 0x179e, 0xc119, 0xfe80 },
	{ 0x0000, 0x004c, 0x004e, 0x004a, 0x6ea9, 0x077c, 0xc01c, 0xfe80 },
	{ 0x0000, 0x0054, 0x0059, 0x0055, 0x0000, 0x077c, 0x7fc8, 0x02ef },
	{ 0x0000, 0x0056, 0x0054, 0x0049, 0x0000, 0x179e, 0x7dcd, 0x02e2 },
	{ 0x0000, 0x0052, 0x004b, 0x004d, 0x9157, 0x077c, 0xc01c, 0xfe7c },
	{ 0x0000, 0x0051, 0x0052, 0x0054, 0x930d, 0x179e, 0x3ee7, 0x016b },
	{ 0x0000, 0x0059, 0x0054, 0x0052, 0x9157, 0x077c, 0x3fe4, 0x0172 },
	{ 0x0000, 0x0044, 0x0043, 0x0046, 0x0000, 0xdc5e, 0x7af1, 0x0299 },
	{ 0x0000, 0x0045, 0x0047, 0x005b, 0x6a78, 0xdc5e, 0xc288, 0xfe54 },
	{ 0x0000, 0x005d, 0x005c, 0x005b, 0x0000, 0xde96, 0x8470, 0xfce9 },
	{ 0x0000, 0x005e, 0x005f, 0x0042, 0x9588, 0xdc5e, 0xc288, 0xfe51 },
	{ 0x0000, 0x004a, 0x0049, 0x0055, 0x6ea9, 0x077c, 0x3fe4, 0x0176 },
	{ 0x0000, 0x005a, 0x0060, 0x0061, 0x0000, 0x739c, 0xc90f, 0xfecc },
	{ 0x0000, 0x0044, 0x005a, 0x0061, 0x0000, 0x739c, 0xc90f, 0xfecc },
	{ 0x0000, 0x0062, 0x0044, 0x0061, 0x3455, 0x70d7, 0xe1c9, 0xff5f },
	{ 0x0000, 0x0042, 0x0044, 0x0062, 0x3455, 0x70d7, 0xe1c9, 0xff5f },
	{ 0x0000, 0x005d, 0x0042, 0x0062, 0x2f95, 0x739c, 0x1b79, 0x00b6 },
	{ 0x0000, 0x0063, 0x005d, 0x0062, 0x2f95, 0x739c, 0x1b79, 0x00b6 },
	{ 0x0000, 0x005a, 0x0064, 0x0060, 0xcbab, 0x70d7, 0xe1c9, 0xff5d },
	{ 0x0000, 0x005a, 0x0045, 0x0064, 0xcbab, 0x70d7, 0xe1c9, 0xff5d },
	{ 0x0000, 0x005c, 0x0065, 0x0064, 0xd06b, 0x739c, 0x1b79, 0x00b4 },
	{ 0x0000, 0x0045, 0x005c, 0x0064, 0xd06b, 0x739c, 0x1b79, 0x00b4 },
	{ 0x0000, 0x005c, 0x005d, 0x0065, 0x0000, 0x70d7, 0x3c6e, 0x0178 },
	{ 0x0000, 0x005d, 0x0063, 0x0065, 0x0000, 0x70d7, 0x3c6e, 0x0178 },
	{ 0x0000, 0x0048, 0x004f, 0x0057, 0x0000, 0x7fff, 0x0000, 0xffe5 },
	{ 0x0000, 0x004f, 0x0056, 0x0057, 0x0000, 0x7fff, 0x0000, 0xffe5 },
	{ 0x0000, 0x0050, 0x0051, 0x0056, 0x0000, 0x7fff, 0x0000, 0xffe5 },
	{ 0x0000, 0x004f, 0x0050, 0x0056, 0x0000, 0x7fff, 0x0000, 0xffe5 },
	{ 0x0000, 0x0053, 0x0055, 0x0060, 0x0000, 0x7fff, 0x0000, 0x0002 },
	{ 0x0000, 0x0064, 0x0053, 0x0060, 0x0000, 0x7fff, 0x0000, 0x0002 },
	{ 0x0000, 0x0064, 0x0065, 0x0053, 0x0000, 0x7fff, 0x0000, 0x0002 },
	{ 0x0000, 0x0065, 0x004c, 0x0053, 0x0000, 0x7fff, 0x0000, 0x0002 },
	{ 0x0000, 0x0065, 0x0063, 0x004c, 0x0000, 0x7fff, 0x0000, 0x0002 },
	{ 0x0000, 0x0063, 0x004d, 0x004c, 0x0000, 0x7fff, 0x0000, 0x0002 },
	{ 0x0000, 0x004d, 0x0063, 0x0058, 0x0000, 0x7fff, 0x0000, 0x0002 },
	{ 0x0000, 0x0063, 0x0062, 0x0058, 0x0000, 0x7fff, 0x0000, 0x0002 },
	{ 0x0000, 0x0058, 0x0062, 0x0061, 0x0000, 0x7fff, 0x0000, 0x0002 },
	{ 0x0000, 0x0059, 0x0058, 0x0061, 0x0000, 0x7fff, 0x0000, 0x0002 },
	{ 0x0000, 0x0055, 0x0061, 0x0060, 0x0000, 0x7fff, 0x0000, 0x0002 },
	{ 0x0000, 0x0055, 0x0059, 0x0061, 0x0000, 0x7fff, 0x0000, 0x0002 },
	{ 0x0000, 0x0066, 0x0067, 0x0068, 0x802a, 0x0000, 0xf987, 0x0066 },
	{ 0x0000, 0x0069, 0x0068, 0x006a, 0x0000, 0x7fff, 0x0000, 0xffec },
	{ 0x0000, 0x0069, 0x0066, 0x0068, 0x0000, 0x7fff, 0x0000, 0xffec },
	{ 0x0000, 0x0067, 0x006b, 0x006c, 0x0000, 0x8063, 0xf60a, 0x00bb },
	{ 0x0000, 0x0067, 0x006c, 0x006d, 0x0000, 0x8063, 0xf60a, 0x00bb },
	{ 0x0000, 0x006d, 0x006c, 0x0069, 0x7fd9, 0x0000, 0xf9cc, 0x006b },
	{ 0x0000, 0x006d, 0x0069, 0x006a, 0x7fd9, 0x0000, 0xf9cc, 0x006b },
	{ 0x0000, 0x0066, 0x006b, 0x0067, 0x802a, 0x0000, 0xf987, 0x0066 },
	{ 0x0000, 0x0068, 0x006e, 0x006f, 0x0000, 0x7fff, 0x0000, 0xffec },
	{ 0x0000, 0x0068, 0x006f, 0x006a, 0x0000, 0x7fff, 0x0000, 0xffec },
	{ 0x0000, 0x0070, 0x006d, 0x006a, 0x7fff, 0x0000, 0x0000, 0x0066 },
	{ 0x0000, 0x0070, 0x006a, 0x006f, 0x7fff, 0x0000, 0x0000, 0x0066 },
	{ 0x0000, 0x0071, 0x0067, 0x006d, 0x0000, 0x8000, 0x0000, 0x00b4 },
	{ 0x0000, 0x0071, 0x006d, 0x0070, 0x0000, 0x8000, 0x0000, 0x00b4 },
	{ 0x0000, 0x0067, 0x0071, 0x006e, 0x8000, 0x0000, 0x0000, 0x0062 },
	{ 0x0000, 0x0067, 0x006e, 0x0068, 0x8000, 0x0000, 0x0000, 0x0062 },
	{ 0x0000, 0x006e, 0x0072, 0x0073, 0x0000, 0x7fff, 0x0000, 0xffec },
	{ 0x0000, 0x006e, 0x0073, 0x006f, 0x0000, 0x7fff, 0x0000, 0xffec },
	{ 0x0000, 0x0072, 0x0074, 0x0075, 0x0000, 0x7fff, 0x0000, 0xffec },
	{ 0x0000, 0x0072, 0x0075, 0x0073, 0x0000, 0x7fff, 0x0000, 0xffec },
	{ 0x0000, 0x0076, 0x0070, 0x006f, 0x7fff, 0x0000, 0x0000, 0x0066 },
	{ 0x0000, 0x0076, 0x006f, 0x0073, 0x7fff, 0x0000, 0x0000, 0x0066 },
	{ 0x0000, 0x0071, 0x0077, 0x0072, 0x8000, 0x0000, 0x0000, 0x0062 },
	{ 0x0000, 0x0071, 0x0072, 0x006e, 0x8000, 0x0000, 0x0000, 0x0062 },
	{ 0x0000, 0x0077, 0x0071, 0x0070, 0x0000, 0x8000, 0x0000, 0x00b4 },
	{ 0x0000, 0x0077, 0x0070, 0x0076, 0x0000, 0x8000, 0x0000, 0x00b4 },
	{ 0x0000, 0x0077, 0x0074, 0x0072, 0x8000, 0x0000, 0x0000, 0x0062 },
	{ 0x0000, 0x0078, 0x0077, 0x0076, 0x0000, 0x8000, 0x0000, 0x00b4 },
	{ 0x0000, 0x0075, 0x0076, 0x0073, 0x7fff, 0x0000, 0x0000, 0x0066 },
	{ 0x0000, 0x0077, 0x0079, 0x0074, 0x8000, 0x0000, 0x0000, 0x0062 },
	{ 0x0000, 0x0075, 0x0078, 0x0076, 0x7fff, 0x0000, 0x0000, 0x0066 },
	{ 0x0000, 0x0078, 0x0079, 0x0077, 0x0000, 0x8000, 0x0000, 0x00b4 },
	{ 0x0000, 0x001c, 0x007a, 0x001e, 0x409e, 0xffe9, 0x9182, 0xfeed },
	{ 0x0000, 0x007a, 0x007b, 0x001e, 0x40e6, 0x0000, 0x91ac, 0xfeed },
	{ 0x0000, 0x001c, 0x007c, 0x007a, 0x4056, 0x0000, 0x9158, 0xfeeb },
	{ 0x0000, 0x0020, 0x007d, 0x0022, 0xc0a2, 0x0000, 0x90c9, 0xfee7 },
	{ 0x0000, 0x007d, 0x007e, 0x0022, 0xc0a2, 0x0000, 0x90c9, 0xfee7 },
	{ 0x0000, 0x0020, 0x007f, 0x007d, 0xc0a2, 0x0000, 0x90c9, 0xfee7 },
	{ 0x0000, 0x0080, 0x007f, 0x0081, 0x0000, 0x0000, 0x8000, 0xfe85 },
	{ 0x0000, 0x0081, 0x0082, 0x0080, 0x0000, 0x0000, 0x8000, 0xfe85 },
	{ 0x0000, 0x0082, 0x007b, 0x0080, 0x0000, 0x0000, 0x8000, 0xfe85 },
	{ 0x0000, 0x0022, 0x0083, 0x0015, 0x9158, 0x0000, 0xbfaa, 0xfff9 },
	{ 0x0000, 0x0022, 0x007e, 0x0083, 0x9158, 0x0000, 0xbfaa, 0xfff9 },
	{ 0x0000, 0x0083, 0x0084, 0x0015, 0x9158, 0x0000, 0xbfaa, 0xfff9 },
	{ 0x0000, 0x0015, 0x0085, 0x0013, 0x8000, 0x0000, 0x0000, 0x0172 },
	{ 0x0000, 0x0085, 0x0086, 0x0013, 0x8000, 0x0000, 0x0000, 0x0172 },
	{ 0x0000, 0x0015, 0x0084, 0x0085, 0x8000, 0x0000, 0x0000, 0x0172 },
	{ 0x0000, 0x0013, 0x0087, 0x0011, 0x9110, 0x0028, 0x3fda, 0x02e7 },
	{ 0x0000, 0x0013, 0x0086, 0x0087, 0x90c9, 0x0000, 0x3f5e, 0x02e5 },
	{ 0x0000, 0x0087, 0x0088, 0x0011, 0x9158, 0x0000, 0x4056, 0x02eb },
	{ 0x0000, 0x0011, 0x0089, 0x000d, 0xbf62, 0x0017, 0x6e7e, 0x03f9 },
	{ 0x0000, 0x0089, 0x008a, 0x000d, 0xbfaa, 0x0000, 0x6ea8, 0x03fa },
	{ 0x0000, 0x0011, 0x0088, 0x0089, 0xbf1a, 0x0000, 0x6e54, 0x03f8 },
	{ 0x0000, 0x000d, 0x008b, 0x000e, 0xff5b, 0xffd2, 0x7fff, 0x0460 },
	{ 0x0000, 0x000d, 0x008a, 0x008b, 0x0000, 0x0000, 0x7fff, 0x0460 },
	{ 0x0000, 0x008b, 0x008c, 0x000e, 0xfeb5, 0x0000, 0x7ffe, 0x0460 },
	{ 0x0000, 0x000e, 0x008d, 0x0016, 0x3fda, 0xffd8, 0x6ef0, 0x03fd },
	{ 0x0000, 0x000e, 0x008c, 0x008d, 0x4056, 0x0000, 0x6ea8, 0x03fb },
	{ 0x0000, 0x008d, 0x008e, 0x0016, 0x3f5e, 0x0000, 0x6f37, 0x03fe },
	{ 0x0000, 0x0016, 0x008f, 0x0018, 0x6ea8, 0x0000, 0x4056, 0x02ec },
	{ 0x0000, 0x0016, 0x008e, 0x008f, 0x6ea8, 0x0000, 0x4056, 0x02ec },
	{ 0x0000, 0x008f, 0x0090, 0x0018, 0x6ea8, 0x0000, 0x4056, 0x02ec },
	{ 0x0000, 0x0018, 0x0091, 0x001a, 0x7fff, 0xffd3, 0x00a5, 0x0178 },
	{ 0x0000, 0x0018, 0x0090, 0x0091, 0x7fff, 0x0000, 0x0000, 0x0173 },
	{ 0x0000, 0x0091, 0x0092, 0x001a, 0x7ffe, 0x0000, 0x0148, 0x017b },
	{ 0x0000, 0x001a, 0x0093, 0x001c, 0x6ef0, 0xffd8, 0xc026, 0xfffe },
	{ 0x0000, 0x001a, 0x0092, 0x0093, 0x6ea8, 0x0000, 0xbfaa, 0xfffb },
	{ 0x0000, 0x0093, 0x007c, 0x001c, 0x6f37, 0x0000, 0xc0a2, 0x0000 },
};

Vec3s UnicornFountain_vertices[148] = {
	{ 83, -30, -664 },
	{ 115, -30, -717 },
	{ 116, -30, -779 },
	{ 85, -30, -833 },
	{ 32, -30, -865 },
	{ -30, -30, -866 },
	{ -85, -30, -836 },
	{ -116, -30, -782 },
	{ -117, -30, -720 },
	{ -87, -30, -666 },
	{ -33, -30, -634 },
	{ 29, -30, -633 },
	{ 68, -29, -1002 },
	{ 100, 10, -1120 },
	{ -99, 10, -1121 },
	{ -68, -29, -1002 },
	{ 185, -29, -934 },
	{ 271, 10, -1020 },
	{ 252, -29, -816 },
	{ 370, 10, -848 },
	{ 251, -29, -681 },
	{ 370, 10, -649 },
	{ -271, 10, -1022 },
	{ -185, -29, -935 },
	{ -371, 10, -850 },
	{ -253, -29, -818 },
	{ -372, 10, -651 },
	{ -253, -29, -683 },
	{ -273, 10, -479 },
	{ -186, -29, -565 },
	{ -102, 10, -379 },
	{ -69, -29, -497 },
	{ 98, 10, -379 },
	{ 66, -29, -497 },
	{ 270, 10, -477 },
	{ 184, -29, -564 },
	{ -14, 21, -678 },
	{ 9, 2, -684 },
	{ 10, 21, -678 },
	{ -79, 21, -790 },
	{ -63, 2, -807 },
	{ -74, 2, -788 },
	{ 74, 21, -790 },
	{ 58, 2, -807 },
	{ 62, 21, -811 },
	{ -13, 2, -684 },
	{ -67, 21, -811 },
	{ 69, 2, -788 },
	{ -45, 21, -771 },
	{ -33, 21, -791 },
	{ 39, -30, -773 },
	{ 60, -30, -785 },
	{ -12, -30, -717 },
	{ -12, -30, -694 },
	{ -34, -30, -789 },
	{ -55, -30, -801 },
	{ 7, -30, -694 },
	{ 7, -30, -717 },
	{ -14, 21, -717 },
	{ 10, 21, -717 },
	{ 29, 21, -791 },
	{ 30, -30, -789 },
	{ 40, 21, -771 },
	{ -64, -30, -785 },
	{ 50, -30, -801 },
	{ -44, -30, -773 },
	{ -80, 14, -768 },
	{ -32, -2, -693 },
	{ -34, 14, -688 },
	{ 76, 14, -768 },
	{ 27, -2, -693 },
	{ 71, -2, -767 },
	{ 2, 27, -760 },
	{ 1, 14, -754 },
	{ 5, 14, -760 },
	{ -6, 14, -766 },
	{ 2, -2, -767 },
	{ -6, -2, -767 },
	{ 1, 14, -766 },
	{ 0, 27, -763 },
	{ -4, 27, -763 },
	{ -6, 27, -760 },
	{ -9, 14, -760 },
	{ 6, -2, -760 },
	{ -6, 14, -754 },
	{ 2, -2, -753 },
	{ -4, 27, -756 },
	{ 0, 27, -756 },
	{ -10, -2, -760 },
	{ -6, -2, -753 },
	{ 30, 14, -688 },
	{ 41, -2, -819 },
	{ 44, 14, -823 },
	{ -48, 14, -823 },
	{ -45, -2, -819 },
	{ -75, -2, -767 },
	{ 15, -2, -722 },
	{ -19, -2, -722 },
	{ -43, -2, -764 },
	{ -26, -2, -793 },
	{ 39, -2, -764 },
	{ 22, -2, -793 },
	{ 74, 20, 567 },
	{ 98, 180, 93 },
	{ 98, 20, 93 },
	{ -79, 20, 567 },
	{ -102, 20, 93 },
	{ 74, 143, 567 },
	{ -79, 143, 567 },
	{ -102, 180, 93 },
	{ 98, 20, 21 },
	{ -102, 20, 21 },
	{ -102, 180, 21 },
	{ 98, 180, 21 },
	{ 98, 20, -259 },
	{ -102, 20, -259 },
	{ 98, 20, -379 },
	{ -102, 20, -379 },
	{ -102, 180, -259 },
	{ 98, 180, -259 },
	{ -102, 180, -379 },
	{ 98, 180, -379 },
	{ -187, 369, -429 },
	{ -102, 369, -379 },
	{ -273, 369, -479 },
	{ 184, 369, -428 },
	{ 270, 369, -477 },
	{ 98, 369, -379 },
	{ -2, 369, -379 },
	{ 98, 210, -379 },
	{ -102, 210, -379 },
	{ 320, 369, -563 },
	{ 370, 369, -649 },
	{ 370, 369, -749 },
	{ 370, 369, -848 },
	{ 321, 369, -934 },
	{ 271, 369, -1020 },
	{ 186, 369, -1070 },
	{ 100, 369, -1120 },
	{ 0, 369, -1120 },
	{ -99, 369, -1121 },
	{ -185, 369, -1071 },
	{ -271, 369, -1022 },
	{ -321, 369, -936 },
	{ -371, 369, -850 },
	{ -371, 369, -751 },
	{ -372, 369, -651 },
	{ -322, 369, -565 },
};

WaterBox UnicornFountain_waterBoxes[] = {
	{ -301, -20, -1061, 602, 602, 0x00000000 },
};

CollisionHeader UnicornFountain_collisionHeader = { -372, -30, -1121, 370, 369, 567, 148, UnicornFountain_vertices, 232, UnicornFountain_polygons, UnicornFountain_polygonTypes, 0, 1, UnicornFountain_waterBoxes };

s32 UnicornFountain_scene_header00_cutscene[] = {
	CS_BEGIN_CUTSCENE(21, 1046),
	CS_TEXT_LIST(6),
		CS_TEXT_DISPLAY_TEXTBOX(0x0D20, 286, 320, 0x0000, 0x0000, 0x0000),
		CS_TEXT_DISPLAY_TEXTBOX(0x0D21, 335, 400, 0x0000, 0x0000, 0x0000),
		CS_TEXT_LEARN_SONG(3, 435, 445, 0xFFFF),
		CS_TEXT_LEARN_SONG(16, 445, 455, 0x88B),
		CS_TEXT_DISPLAY_TEXTBOX(0x0074, 990, 1000, 0x0000, 0x0000, 0x0000),
		CS_TEXT_DISPLAY_TEXTBOX(0x0D23, 1000, 1010, 0x0000, 0x0000, 0x0000),
	CS_FADE_BGM_LIST(1),
		CS_FADE_BGM(4, 400, 435, 0, 0, 0, 0, 0, 0, 0, 0),
	CS_PLAY_BGM_LIST(1),
		CS_PLAY_BGM(0x34, 455, 1, 0, 0, 0, 0, 0, 0, 0, 0),
	CS_CAM_POS_LIST(0, 336),
		CS_CAM_POS(0, 0, 0, 0x42700000, 298, 1, -748, 0),
		CS_CAM_POS(0, 0, 0, 0x42700000, 242, -11, -734, 0),
		CS_CAM_POS(0, 0, 0, 0x42700000, 143, -1, -768, 0),
		CS_CAM_POS(0, 0, 0, 0x42700000, 107, 53, -744, 0),
		CS_CAM_POS(0, 0, 0, 0x42700000, 111, 70, -659, 0),
		CS_CAM_POS(0, 0, 0, 0x42700000, 38, 79, -517, 0),
		CS_CAM_POS(0, 0, 0, 0x42700000, 38, 81, -518, 0),
		CS_CAM_POS(0, 0, 0, 0x42700000, 39, 84, -518, 0),
		CS_CAM_POS(0, 0, 0, 0x42700000, 39, 87, -519, 0),
		CS_CAM_POS(0, 0, 0, 0x42700000, 39, 83, -519, 0),
		CS_CAM_POS(-1, 0, 0, 0x0, 0, 0, 0, 0),
	CS_CAM_POS_LIST(205, 376),
		CS_CAM_POS(0, 0, 0, 0x42700000, -111, 12, -880, 0),
		CS_CAM_POS(0, 0, 0, 0x42700000, -153, 86, -779, 0),
		CS_CAM_POS(0, 0, 0, 0x42700000, -63, 152, -639, 0),
		CS_CAM_POS(0, 0, 0, 0x42700000, 64, 200, -661, 0),
		CS_CAM_POS(0, 0, 0, 0x42700000, 77, 202, -696, 0),
		CS_CAM_POS(0, 0, 0, 0x42700000, 76, 202, -699, 0),
		CS_CAM_POS(-1, 0, 0, 0x0, 0, 0, 0, 0),
	CS_CAM_POS_LIST(320, 581),
		CS_CAM_POS(0, 0, 0, 0x42700000, 318, 25, -605, 0),
		CS_CAM_POS(0, 0, 0, 0x42700000, 301, 25, -653, 0),
		CS_CAM_POS(0, 0, 0, 0x42700000, 285, 25, -707, 0),
		CS_CAM_POS(0, 0, 0, 0x42700000, 268, 25, -719, 0),
		CS_CAM_POS(0, 0, 0, 0x42700000, 268, 36, -606, 0),
		CS_CAM_POS(0, 0, 0, 0x42700000, 268, 42, -600, 0),
		CS_CAM_POS(-1, 0, 0, 0x0, 0, 0, 0, 0),
	CS_CAM_POS_LIST(435, 516),
		CS_CAM_POS(0, 0, 0, 0x42700000, 71, 162, -651, 0),
		CS_CAM_POS(0, 0, 0, 0x42700000, 71, 162, -651, 0),
		CS_CAM_POS(0, 0, 0, 0x42700000, 71, 162, -651, 0),
		CS_CAM_POS(0, 0, 0, 0x42700000, 71, 162, -651, 0),
		CS_CAM_POS(-1, 0, 0, 0x0, 0, 0, 0, 0),
	CS_CAM_POS_LIST(445, 526),
		CS_CAM_POS(0, 0, 0, 0x42700000, 78, 27, -608, 0),
		CS_CAM_POS(0, 0, 0, 0x42700000, 78, 27, -608, 0),
		CS_CAM_POS(0, 0, 0, 0x42700000, 78, 27, -608, 0),
		CS_CAM_POS(0, 0, 0, 0x42700000, 78, 27, -608, 0),
		CS_CAM_POS(-1, 0, 0, 0x0, 0, 0, 0, 0),
	CS_CAM_POS_LIST(465, 746),
		CS_CAM_POS(0, 0, 0, 0x42700000, 251, 0, -757, 0),
		CS_CAM_POS(0, 0, 0, 0x42700000, 242, 54, -761, 0),
		CS_CAM_POS(0, 0, 0, 0x42700000, 241, 186, -759, 0),
		CS_CAM_POS(0, 0, 0, 0x42700000, 143, 224, -734, 0),
		CS_CAM_POS(0, 0, 0, 0x42700000, -69, 196, -692, 0),
		CS_CAM_POS(0, 0, 0, 0x42a00000, -274, 200, -570, 0),
		CS_CAM_POS(0, 0, 0, 0x42a00000, -276, 198, -567, 0),
		CS_CAM_POS(-1, 0, 0, 0x0, 0, 0, 0, 0),
	CS_CAM_POS_LIST(623, 824),
		CS_CAM_POS(0, 0, 0, 0x42700000, -140, -1, -744, 0),
		CS_CAM_POS(0, 0, 0, 0x42700000, -119, -3, -741, 0),
		CS_CAM_POS(0, 0, 0, 0x42700000, -89, -10, -734, 0),
		CS_CAM_POS(0, 0, 0, 0x42700000, -74, 4, -734, 0),
		CS_CAM_POS(0, 0, 0, 0x42700000, -51, 22, -720, 0),
		CS_CAM_POS(0, 0, 0, 0x42700000, -26, 27, -687, 0),
		CS_CAM_POS(0, 0, 0, 0x42700000, -13, 31, -645, 0),
		CS_CAM_POS(0, 0, 0, 0x42700000, -7, 34, -622, 0),
		CS_CAM_POS(0, 0, 0, 0x42b40000, -2, 36, -596, 0),
		CS_CAM_POS(0, 0, 0, 0x42b40000, -2, 36, -596, 0),
		CS_CAM_POS(-1, 0, 0, 0x0, 0, 0, 0, 0),
	CS_CAM_POS_LIST(759, 1127),
		CS_CAM_POS(0, 0, 0, 0x42700000, -97, 2, -815, 0),
		CS_CAM_POS(0, 0, 0, 0x42700000, -81, 7, -806, 0),
		CS_CAM_POS(0, 0, 0, 0x42700000, -114, -2, -825, 0),
		CS_CAM_POS(0, 0, 0, 0x42700000, -159, 10, -852, 0),
		CS_CAM_POS(0, 0, 0, 0x42700000, -202, 26, -770, 0),
		CS_CAM_POS(0, 0, 0, 0x42700000, -151, 26, -605, 0),
		CS_CAM_POS(0, 0, 0, 0x42700000, 120, 36, -577, 0),
		CS_CAM_POS(0, 0, 0, 0x42700000, 228, 46, -764, 0),
		CS_CAM_POS(0, 0, 0, 0x42700000, 134, 26, -973, 0),
		CS_CAM_POS(0, 0, 0, 0x428c0000, -170, 0, -1027, 0),
		CS_CAM_POS(0, 0, 0, 0x428c0000, -322, 6, -737, 0),
		CS_CAM_POS(0, 0, 0, 0x428c0000, -176, 0, -527, 0),
		CS_CAM_POS(0, 0, 0, 0x42700000, 2, -15, -469, 0),
		CS_CAM_POS(0, 0, 0, 0x42700000, 115, -15, -494, 0),
		CS_CAM_POS(0, 0, 0, 0x42700000, 117, -15, -495, 0),
		CS_CAM_POS(-1, 0, 0, 0x0, 0, 0, 0, 0),
	CS_CAM_FOCUS_POINT_LIST(0, 355),
		CS_CAM_FOCUS_POINT(0, 0, 20, 0x42700000, 274, -22, -744, 0),
		CS_CAM_FOCUS_POINT(0, 0, 30, 0x42700000, 207, -34, -737, 0),
		CS_CAM_FOCUS_POINT(0, 0, 30, 0x42700000, 98, -27, -778, 0),
		CS_CAM_FOCUS_POINT(0, 0, 40, 0x42700000, 84, 53, -778, 0),
		CS_CAM_FOCUS_POINT(0, 0, 25, 0x42700000, 29, 59, -737, 0),
		CS_CAM_FOCUS_POINT(0, 0, 30, 0x42700000, -4, 41, -760, 0),
		CS_CAM_FOCUS_POINT(0, 0, 20, 0x42700000, -5, 48, -759, 0),
		CS_CAM_FOCUS_POINT(0, 0, 20, 0x42700000, -4, 169, -760, 0),
		CS_CAM_FOCUS_POINT(0, 0, 100, 0x42700000, -5, 172, -760, 0),
		CS_CAM_FOCUS_POINT(0, 0, 20, 0x42700000, -5, 168, -760, 0),
		CS_CAM_FOCUS_POINT(-1, 0, 0, 0x0, 0, 0, 0, 0),
	CS_CAM_FOCUS_POINT_LIST(205, 395),
		CS_CAM_FOCUS_POINT(0, 0, 20, 0x42700000, 1, 18, -816, 0),
		CS_CAM_FOCUS_POINT(0, 0, 40, 0x42700000, -3, 94, -787, 0),
		CS_CAM_FOCUS_POINT(0, 0, 30, 0x42700000, 0, 156, -756, 0),
		CS_CAM_FOCUS_POINT(0, 0, 30, 0x42700000, 0, 197, -725, 0),
		CS_CAM_FOCUS_POINT(0, 0, 30, 0x42700000, 1, 198, -726, 0),
		CS_CAM_FOCUS_POINT(0, 0, 20, 0x42700000, 1, 198, -727, 0),
		CS_CAM_FOCUS_POINT(-1, 0, 0, 0x0, 0, 0, 0, 0),
	CS_CAM_FOCUS_POINT_LIST(320, 640),
		CS_CAM_FOCUS_POINT(0, 0, 20, 0x42700000, 36, 25, -442, 0),
		CS_CAM_FOCUS_POINT(0, 0, 60, 0x42700000, 38, 25, -534, 0),
		CS_CAM_FOCUS_POINT(0, 0, 30, 0x42700000, 33, 25, -647, 0),
		CS_CAM_FOCUS_POINT(0, 0, 30, 0x42700000, 27, 111, -733, 0),
		CS_CAM_FOCUS_POINT(0, 0, 60, 0x42700000, 27, 170, -733, 0),
		CS_CAM_FOCUS_POINT(0, 0, 60, 0x42700000, 27, 167, -733, 0),
		CS_CAM_FOCUS_POINT(-1, 0, 0, 0x0, 0, 0, 0, 0),
	CS_CAM_FOCUS_POINT_LIST(435, 535),
		CS_CAM_FOCUS_POINT(0, 0, 20, 0x42700000, -13, 187, -756, 0),
		CS_CAM_FOCUS_POINT(0, 0, 20, 0x42700000, -13, 187, -756, 0),
		CS_CAM_FOCUS_POINT(0, 0, 20, 0x42700000, -13, 187, -756, 0),
		CS_CAM_FOCUS_POINT(0, 0, 20, 0x42700000, -13, 187, -756, 0),
		CS_CAM_FOCUS_POINT(-1, 0, 0, 0x0, 0, 0, 0, 0),
	CS_CAM_FOCUS_POINT_LIST(445, 545),
		CS_CAM_FOCUS_POINT(0, 0, 20, 0x42700000, 28, 27, -582, 0),
		CS_CAM_FOCUS_POINT(0, 0, 20, 0x42700000, 28, 27, -582, 0),
		CS_CAM_FOCUS_POINT(0, 0, 20, 0x42700000, 28, 27, -582, 0),
		CS_CAM_FOCUS_POINT(0, 0, 20, 0x42700000, 28, 27, -582, 0),
		CS_CAM_FOCUS_POINT(-1, 0, 0, 0x0, 0, 0, 0, 0),
	CS_CAM_FOCUS_POINT_LIST(465, 765),
		CS_CAM_FOCUS_POINT(0, 0, 20, 0x42700000, 306, -11, -768, 0),
		CS_CAM_FOCUS_POINT(0, 0, 30, 0x42700000, 296, 43, -773, 0),
		CS_CAM_FOCUS_POINT(0, 0, 30, 0x42700000, 296, 175, -770, 0),
		CS_CAM_FOCUS_POINT(0, 0, 30, 0x42700000, 198, 212, -746, 0),
		CS_CAM_FOCUS_POINT(0, 0, 50, 0x42700000, -15, 185, -708, 0),
		CS_CAM_FOCUS_POINT(0, 0, 100, 0x42a00000, -224, 189, -596, 0),
		CS_CAM_FOCUS_POINT(0, 0, 20, 0x42a00000, -226, 187, -593, 0),
		CS_CAM_FOCUS_POINT(-1, 0, 0, 0x0, 0, 0, 0, 0),
	CS_CAM_FOCUS_POINT_LIST(623, 843),
		CS_CAM_FOCUS_POINT(0, 0, 20, 0x42700000, -101, -28, -732, 0),
		CS_CAM_FOCUS_POINT(0, 0, 20, 0x42700000, -64, -36, -726, 0),
		CS_CAM_FOCUS_POINT(0, 0, 20, 0x42700000, -42, -31, -725, 0),
		CS_CAM_FOCUS_POINT(0, 0, 20, 0x42700000, -49, -5, -725, 0),
		CS_CAM_FOCUS_POINT(0, 0, 20, 0x42700000, -29, 12, -703, 0),
		CS_CAM_FOCUS_POINT(0, 0, 20, 0x42700000, -14, 17, -662, 0),
		CS_CAM_FOCUS_POINT(0, 0, 20, 0x42700000, -6, 25, -618, 0),
		CS_CAM_FOCUS_POINT(0, 0, 20, 0x42700000, -2, 29, -594, 0),
		CS_CAM_FOCUS_POINT(0, 0, 20, 0x42b40000, -1, 34, -582, 0),
		CS_CAM_FOCUS_POINT(0, 0, 20, 0x42b40000, -1, 35, -582, 0),
		CS_CAM_FOCUS_POINT(-1, 0, 0, 0x0, 0, 0, 0, 0),
	CS_CAM_FOCUS_POINT_LIST(759, 1176),
		CS_CAM_FOCUS_POINT(0, 0, 20, 0x42700000, -2, 28, -759, 0),
		CS_CAM_FOCUS_POINT(0, 0, 20, 0x42700000, -2, 28, -759, 0),
		CS_CAM_FOCUS_POINT(0, 0, 12, 0x42700000, -2, 28, -759, 0),
		CS_CAM_FOCUS_POINT(0, 0, 12, 0x42700000, -2, 28, -759, 0),
		CS_CAM_FOCUS_POINT(0, 0, 15, 0x42700000, -2, 28, -759, 0),
		CS_CAM_FOCUS_POINT(0, 0, 15, 0x42700000, -2, 28, -758, 0),
		CS_CAM_FOCUS_POINT(0, 0, 15, 0x42700000, 0, 28, -757, 0),
		CS_CAM_FOCUS_POINT(0, 0, 12, 0x42700000, 1, 28, -759, 0),
		CS_CAM_FOCUS_POINT(0, 0, 15, 0x42700000, 2, 28, -760, 0),
		CS_CAM_FOCUS_POINT(0, 0, 20, 0x428c0000, 1, 77, -760, 0),
		CS_CAM_FOCUS_POINT(0, 0, 21, 0x428c0000, 0, 116, -759, 0),
		CS_CAM_FOCUS_POINT(0, 0, 20, 0x428c0000, -1, 116, -759, 0),
		CS_CAM_FOCUS_POINT(0, 0, 20, 0x42700000, 4, 116, -759, 0),
		CS_CAM_FOCUS_POINT(0, 0, 100, 0x42700000, -65, 116, -757, 0),
		CS_CAM_FOCUS_POINT(0, 0, 50, 0x42700000, -63, 116, -758, 0),
		CS_CAM_FOCUS_POINT(-1, 0, 0, 0x0, 0, 0, 0, 0),
	CS_PLAYER_ACTION_LIST(4),
		CS_PLAYER_ACTION(0x0005, 0, 445, 0x0, 0xffff8000, 0x0, 0, -16, -568, 0, -16, -568, 0, 0, 0),
		CS_PLAYER_ACTION(0x0011, 445, 990, 0x0, 0xffff8000, 0x0, 0, -16, -568, 0, -16, -568, 0, 0, 0),
		CS_PLAYER_ACTION(0x003E, 990, 1000, 0x0, 0xffff8000, 0x0, 0, -16, -568, 0, -16, -568, 0, 0, 0),
		CS_PLAYER_ACTION(0x0005, 1000, 1001, 0x0, 0xffff8000, 0x0, 0, -16, -568, 0, -16, -568, 0, 0, 0),
	CS_NPC_ACTION_LIST(55, 2),
		CS_NPC_ACTION(1, 135, 1010, 0x0, 0x0, 0x0, 15, 0, 10, 15, 0, 0, 0, 0, 0),
		CS_NPC_ACTION(2, 1010, 1011, 0x0, 0x0, 0x0, 15, 0, 0, 15, 0, -10, 0, 0, 0),
	CS_END(),
};
