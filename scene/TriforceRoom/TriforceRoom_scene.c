#include "ultra64.h"
#include "z64.h"
#include "macros.h"
#include "TriforceRoom_scene.h"

#include "segment_symbols.h"
#include "command_macros_base.h"
#include "z64cutscene_commands.h"
#include "variables.h"

SCmdBase TriforceRoom_scene_header00[] = {
	SCENE_CMD_SOUND_SETTINGS(0x00, 0x13, 0x71),
	SCENE_CMD_ROOM_LIST(1, &TriforceRoom_scene_roomList),
	SCENE_CMD_MISC_SETTINGS(0x00, 0x0E),
	SCENE_CMD_COL_HEADER(&TriforceRoom_collisionHeader),
	SCENE_CMD_ENTRANCE_LIST(&TriforceRoom_scene_header00_entranceList),
	SCENE_CMD_SPECIAL_FILES(0x00, 0x0002),
	SCENE_CMD_SPAWN_LIST(1, &TriforceRoom_scene_header00_startPositionList),
	SCENE_CMD_SKYBOX_SETTINGS(0x00, 0x00, 0x01),
	SCENE_CMD_ENV_LIGHT_SETTINGS(2, &TriforceRoom_scene_header00_lightSettings),
	SCENE_CMD_CUTSCENE_DATA(&TriforceRoom_scene_header00_cutscene),
	SCENE_CMD_END(),
};

ActorEntry TriforceRoom_scene_header00_startPositionList[] = {
	{ ACTOR_PLAYER, 0, -48, 460, 0, 32768, 0, 0x0FFF },
};

extern u8 _TriforceRoom_room_0SegmentRomStart[];
extern u8 _TriforceRoom_room_0SegmentRomEnd[];

RomFile TriforceRoom_scene_roomList[] = {
	{ (u32)_TriforceRoom_room_0SegmentRomStart, (u32)_TriforceRoom_room_0SegmentRomEnd },
};

EntranceEntry TriforceRoom_scene_header00_entranceList[] = {
	{ 0, 0 },
};

LightSettings TriforceRoom_scene_header00_lightSettings[2] = {
	{ 0x39, 0x40, 0x75, 0x49, 0x49, 0x49, 0x86, 0x82, 0xDB, 0xB7, 0xB7, 0xB7, 0x46, 0x6B, 0x85, 0x7D, 0x7C, 0xA7, 0x7BCF, 0x3200 },
	{ 0x3C, 0x3E, 0x8F, 0x49, 0x49, 0x49, 0xDF, 0xD9, 0xA1, 0xB7, 0xB7, 0xB7, 0x45, 0x67, 0x85, 0xC0, 0xB0, 0x65, 0x3FA2, 0x3200 },
};

u32 TriforceRoom_polygonTypes[] = {
	 0x00000000, 0x00000000,
};

CollisionPoly TriforceRoom_polygons[] = {
	{ 0x0000, 0x0000, 0x0001, 0x0002, 0x0000, 0x0000, 0x7fff, 0xff42 },
	{ 0x0000, 0x0003, 0x0004, 0x0005, 0x0000, 0x0000, 0x7fff, 0xff9b },
	{ 0x0000, 0x0006, 0x0007, 0x0003, 0x0000, 0x7fff, 0x0000, 0x000a },
	{ 0x0000, 0x0005, 0x0008, 0x0004, 0x0000, 0x7fff, 0x0000, 0x0000 },
	{ 0x0000, 0x0009, 0x000a, 0x0007, 0x0000, 0x0000, 0x7fff, 0xff7d },
	{ 0x0000, 0x000b, 0x000c, 0x0009, 0x0000, 0x7fff, 0x0000, 0x0014 },
	{ 0x0000, 0x000d, 0x000e, 0x0000, 0x0000, 0x7fff, 0x0000, 0x0028 },
	{ 0x0000, 0x000f, 0x0010, 0x000c, 0x0000, 0x0000, 0x7fff, 0xff60 },
	{ 0x0000, 0x0011, 0x0002, 0x000f, 0x0000, 0x7fff, 0x0000, 0x001e },
	{ 0x0000, 0x0012, 0x0013, 0x000e, 0x0000, 0x0000, 0x7fff, 0xff25 },
	{ 0x0000, 0x0014, 0x0015, 0x0012, 0x0000, 0x7fff, 0x0000, 0x0032 },
	{ 0x0000, 0x0012, 0x0015, 0x0016, 0x0000, 0x7fff, 0x0000, 0x0032 },
	{ 0x0000, 0x0014, 0x0017, 0x0015, 0x0000, 0x7fff, 0x0000, 0x0032 },
	{ 0x0000, 0x0014, 0x0018, 0x0017, 0x0000, 0x7fff, 0x0000, 0x0032 },
	{ 0x0000, 0x000d, 0x0000, 0x0001, 0x0000, 0x0000, 0x7fff, 0xff42 },
	{ 0x0000, 0x0006, 0x0003, 0x0004, 0x0000, 0x0000, 0x7fff, 0xff9b },
	{ 0x0000, 0x0006, 0x000a, 0x0007, 0x0000, 0x7fff, 0x0000, 0x000a },
	{ 0x0000, 0x0005, 0x0019, 0x0008, 0x0000, 0x7fff, 0x0000, 0x0000 },
	{ 0x0000, 0x000b, 0x0009, 0x000a, 0x0000, 0x0000, 0x7fff, 0xff7d },
	{ 0x0000, 0x000b, 0x0010, 0x000c, 0x0000, 0x7fff, 0x0000, 0x0014 },
	{ 0x0000, 0x000d, 0x0013, 0x000e, 0x0000, 0x7fff, 0x0000, 0x0028 },
	{ 0x0000, 0x0011, 0x000f, 0x0010, 0x0000, 0x0000, 0x7fff, 0xff60 },
	{ 0x0000, 0x0011, 0x0001, 0x0002, 0x0000, 0x7fff, 0x0000, 0x001e },
	{ 0x0000, 0x0014, 0x0012, 0x0013, 0x0000, 0x0000, 0x7fff, 0xff25 },
};

Vec3s TriforceRoom_vertices[26] = {
	{ 103, -40, 190 },
	{ -103, -30, 190 },
	{ 103, -30, 190 },
	{ 103, -10, 101 },
	{ -103, 0, 101 },
	{ 103, 0, 101 },
	{ -103, -10, 101 },
	{ 103, -10, 131 },
	{ -103, 0, -56 },
	{ 103, -20, 131 },
	{ -103, -10, 131 },
	{ -103, -20, 131 },
	{ 103, -20, 160 },
	{ -103, -40, 190 },
	{ 103, -40, 219 },
	{ 103, -30, 160 },
	{ -103, -20, 160 },
	{ -103, -30, 160 },
	{ 103, -50, 219 },
	{ -103, -40, 219 },
	{ -103, -50, 219 },
	{ 275, -50, 649 },
	{ 275, -50, 219 },
	{ -275, -50, 649 },
	{ -275, -50, 219 },
	{ 103, 0, -56 },
};

CollisionHeader TriforceRoom_collisionHeader = { -275, -50, -56, 275, 0, 649, 26, TriforceRoom_vertices, 24, TriforceRoom_polygons, TriforceRoom_polygonTypes, 0, 0, 0 };

s32 TriforceRoom_scene_header00_cutscene[] = {
	CS_BEGIN_CUTSCENE(14, 500),
	CS_TERMINATOR(81, 495, 499),
	CS_TEXT_LIST(1),
		CS_TEXT_DISPLAY_TEXTBOX(0x0ACE, 445, 490, 0x0000, 0x0000, 0x0000),
	CS_LIGHTING_LIST(2),
		CS_LIGHTING(2, 88, 89, 0, 0, 0, 0, 0, 0, 0, 0),
		CS_LIGHTING(1, 392, 393, 0, 0, 0, 0, 0, 0, 0, 0),
	CS_SCENE_TRANS_FX(1, 377, 382),
	CS_SCENE_TRANS_FX(5, 382, 389),
	CS_CAM_POS_LIST(0, 266),
		CS_CAM_POS(0, 0, 0, 0x42960000, 481, -41, 349, 0),
		CS_CAM_POS(0, 0, 0, 0x42960000, 281, -43, 349, 0),
		CS_CAM_POS(0, 0, 0, 0x42820000, -119, -47, 348, 0),
		CS_CAM_POS(0, 0, 0, 0x42820000, -196, 3, 308, 0),
		CS_CAM_POS(0, 0, 0, 0x42820000, -207, 23, 238, 0),
		CS_CAM_POS(0, 0, 0, 0x42820000, -172, 39, 128, 0),
		CS_CAM_POS(0, 0, 0, 0x42820000, -121, 53, 58, 0),
		CS_CAM_POS(0, 0, 0, 0x42820000, -77, 68, 17, 0),
		CS_CAM_POS(-1, 0, 0, 0x0, 0, 0, 0, 0),
	CS_CAM_POS_LIST(175, 346),
		CS_CAM_POS(0, 0, 0, 0x42700000, 31, 55, 60, 0),
		CS_CAM_POS(0, 0, 0, 0x42700000, 20, 55, 30, 0),
		CS_CAM_POS(0, 0, 0, 0x42700000, -26, 55, 31, 0),
		CS_CAM_POS(0, 0, 0, 0x42700000, -35, 54, 62, 0),
		CS_CAM_POS(-1, 0, 0, 0x0, 0, 0, 0, 0),
	CS_CAM_POS_LIST(220, 541),
		CS_CAM_POS(0, 0, 0, 0x42700000, 67, 36, 239, 0),
		CS_CAM_POS(0, 0, 0, 0x42700000, 63, 40, 183, 0),
		CS_CAM_POS(0, 0, 0, 0x42700000, 80, 46, 116, 0),
		CS_CAM_POS(0, 0, 0, 0x42700000, 133, 48, 76, 0),
		CS_CAM_POS(0, 0, 0, 0x42700000, 112, 47, 41, 0),
		CS_CAM_POS(0, 0, 0, 0x42700000, 56, 53, 34, 0),
		CS_CAM_POS(0, 0, 0, 0x42700000, 36, 52, 34, 0),
		CS_CAM_POS(-1, 0, 0, 0x0, 0, 0, 0, 0),
	CS_CAM_POS_LIST(407, 492),
		CS_CAM_POS(0, 0, 0, 0x428c0000, 0, -44, 782, 0),
		CS_CAM_POS(0, 0, 0, 0x428c0000, 0, -44, 507, 0),
		CS_CAM_POS(0, 0, 0, 0x428c0000, 0, -44, 356, 0),
		CS_CAM_POS(0, 0, 0, 0x42340000, 0, 78, 287, 0),
		CS_CAM_POS(0, 0, 0, 0x42200000, 0, 89, 153, 0),
		CS_CAM_POS(0, 0, 0, 0x42200000, 0, 98, 5, 0),
		CS_CAM_POS(-1, 0, 0, 0x0, 0, 0, 0, 0),
	CS_CAM_FOCUS_POINT_LIST(0, 285),
		CS_CAM_FOCUS_POINT(0, 0, 20, 0x42960000, -1, 28, 56, 0),
		CS_CAM_FOCUS_POINT(0, 0, 35, 0x42960000, -1, 28, 56, 0),
		CS_CAM_FOCUS_POINT(0, 0, 20, 0x42820000, 3, 57, 34, 0),
		CS_CAM_FOCUS_POINT(0, 0, 25, 0x42820000, -1, 73, 25, 0),
		CS_CAM_FOCUS_POINT(0, 0, 35, 0x42820000, -1, 83, 0, 0),
		CS_CAM_FOCUS_POINT(0, 0, 50, 0x42820000, 0, 88, -1, 0),
		CS_CAM_FOCUS_POINT(0, 0, 60, 0x42820000, 0, 91, -1, 0),
		CS_CAM_FOCUS_POINT(0, 0, 20, 0x42820000, 0, 94, -1, 0),
		CS_CAM_FOCUS_POINT(-1, 0, 0, 0x0, 0, 0, 0, 0),
	CS_CAM_FOCUS_POINT_LIST(175, 365),
		CS_CAM_FOCUS_POINT(0, 0, 20, 0x42700000, 2, 50, 62, 0),
		CS_CAM_FOCUS_POINT(0, 0, 65, 0x42700000, 1, 50, 62, 0),
		CS_CAM_FOCUS_POINT(0, 0, 65, 0x42700000, -1, 50, 62, 0),
		CS_CAM_FOCUS_POINT(0, 0, 20, 0x42700000, 0, 50, 62, 0),
		CS_CAM_FOCUS_POINT(-1, 0, 0, 0x0, 0, 0, 0, 0),
	CS_CAM_FOCUS_POINT_LIST(220, 560),
		CS_CAM_FOCUS_POINT(0, 0, 20, 0x42700000, 0, 95, 13, 0),
		CS_CAM_FOCUS_POINT(0, 0, 40, 0x42700000, 0, 92, 13, 0),
		CS_CAM_FOCUS_POINT(0, 0, 40, 0x42700000, 1, 87, 13, 0),
		CS_CAM_FOCUS_POINT(0, 0, 40, 0x42700000, 1, 79, 23, 0),
		CS_CAM_FOCUS_POINT(0, 0, 40, 0x42700000, 0, 58, 24, 0),
		CS_CAM_FOCUS_POINT(0, 0, 120, 0x42700000, 0, 55, 31, 0),
		CS_CAM_FOCUS_POINT(0, 0, 20, 0x42700000, 0, 54, 37, 0),
		CS_CAM_FOCUS_POINT(-1, 0, 0, 0x0, 0, 0, 0, 0),
	CS_CAM_FOCUS_POINT_LIST(407, 511),
		CS_CAM_FOCUS_POINT(0, 0, 20, 0x428c0000, 0, -44, 715, 0),
		CS_CAM_FOCUS_POINT(0, 0, 20, 0x428c0000, 0, -39, 441, 0),
		CS_CAM_FOCUS_POINT(0, 0, 12, 0x428c0000, 0, -39, 289, 0),
		CS_CAM_FOCUS_POINT(0, 0, 7, 0x42340000, 0, 59, 221, 0),
		CS_CAM_FOCUS_POINT(0, 0, 5, 0x42200000, 0, 71, 86, 0),
		CS_CAM_FOCUS_POINT(0, 0, 20, 0x42200000, 0, 80, -62, 0),
		CS_CAM_FOCUS_POINT(-1, 0, 0, 0x0, 0, 0, 0, 0),
	CS_PLAYER_ACTION_LIST(6),
		CS_PLAYER_ACTION(0x0001, 0, 50, 0x0, 0xffff8000, 0x0, 0, -49, 442, 0, 0, 47, 0, 0, 0),
		CS_PLAYER_ACTION(0x0034, 50, 90, 0x0, 0xffff8000, 0x0, 0, 0, 47, 0, 0, 55, 0, 0, 0),
		CS_PLAYER_ACTION(0x004B, 90, 335, 0x0, 0xffff8000, 0x0, 0, 0, 55, 0, 0, 55, 0, 0, 0),
		CS_PLAYER_ACTION(0x004E, 335, 410, 0x0, 0xffff8000, 0x0, 0, 0, 55, 0, 0, 55, 0, 0, 0),
		CS_PLAYER_ACTION(0x0007, 410, 420, 0x0, 0xffff8000, 0x0, 0, 0, 55, 0, 0, 55, 0, 0, 0),
		CS_PLAYER_ACTION(0x0008, 420, 540, 0x0, 0x0, 0x0, 0, 0, 55, 0, 0, 55, 0, 0, 0),
	CS_END(),
};
