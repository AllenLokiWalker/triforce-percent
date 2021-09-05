#include "ultra64.h"
#include "z64.h"
#include "macros.h"
#include "EndingDemo_scene.h"

#include "segment_symbols.h"
#include "command_macros_base.h"
#include "z64cutscene_commands.h"
#include "variables.h"

SCmdBase EndingDemo_scene_header00[] = {
	SCENE_CMD_SOUND_SETTINGS(0x00, 0x0F, 0x22),
	SCENE_CMD_ROOM_LIST(1, &EndingDemo_scene_roomList),
	SCENE_CMD_MISC_SETTINGS(0x00, 0x00),
	SCENE_CMD_COL_HEADER(&EndingDemo_collisionHeader),
	SCENE_CMD_ENTRANCE_LIST(&EndingDemo_scene_header00_entranceList),
	SCENE_CMD_SPECIAL_FILES(0x00, 0x0002),
	SCENE_CMD_SPAWN_LIST(1, &EndingDemo_scene_header00_startPositionList),
	SCENE_CMD_SKYBOX_SETTINGS(0x01, 0x00, 0x00),
	SCENE_CMD_ENV_LIGHT_SETTINGS(4, &EndingDemo_scene_header00_lightSettings),
	SCENE_CMD_CUTSCENE_DATA(&Something),
	SCENE_CMD_END(),
};

ActorEntry EndingDemo_scene_header00_startPositionList[] = {
	{ ACTOR_PLAYER, 0, 0, 0, 0, 0, 0, 0x0FFF },
};

RomFile EndingDemo_scene_roomList[] = {
	{ (u32)_EndingDemo_room_0SegmentRomStart, (u32)_EndingDemo_room_0SegmentRomEnd },
};

EntranceEntry EndingDemo_scene_header00_entranceList[] = {
	{ 0, 0 },
};

LightSettings EndingDemo_scene_header00_lightSettings[4] = {
	{ 0x46, 0x2D, 0x39, 0x49, 0x49, 0x49, 0xB4, 0x9A, 0x8A, 0xB7, 0xB7, 0xB7, 0x14, 0x14, 0x3C, 0x8C, 0x78, 0x64, 0x07E1, 0x3200 },
	{ 0x69, 0x5A, 0x5A, 0x49, 0x49, 0x49, 0xFF, 0xFF, 0xF0, 0xB7, 0xB7, 0xB7, 0x32, 0x32, 0x5A, 0x64, 0x64, 0x78, 0x07E4, 0x3200 },
	{ 0x78, 0x5A, 0x00, 0x49, 0x49, 0x49, 0xFA, 0x87, 0x32, 0xB7, 0xB7, 0xB7, 0x1E, 0x1E, 0x3C, 0x78, 0x46, 0x32, 0x07E3, 0x3200 },
	{ 0x28, 0x46, 0x64, 0x49, 0x49, 0x49, 0x14, 0x14, 0x23, 0xB7, 0xB7, 0xB7, 0x32, 0x32, 0x64, 0x00, 0x00, 0x1E, 0x07E0, 0x3200 },
};

u32 EndingDemo_polygonTypes[] = {
	 0x00000000, 0x00000000,
};

CollisionPoly EndingDemo_polygons[] = {
	{ 0x0000, 0x0000, 0x0001, 0x0002, 0x0000, 0x7fff, 0x0000, 0x0000 },
	{ 0x0000, 0x0000, 0x0002, 0x0003, 0x0000, 0x7fff, 0x0000, 0x0000 },
};

Vec3s EndingDemo_vertices[4] = {
	{ -32, 0, 32 },
	{ 32, 0, 32 },
	{ 32, 0, -32 },
	{ -32, 0, -32 },
};

CollisionHeader EndingDemo_collisionHeader = { -32, 0, -32, 32, 0, 32, 4, EndingDemo_vertices, 2, EndingDemo_polygons, EndingDemo_polygonTypes, 0, 0, 0 };

s32 Something[] = {
	CS_BEGIN_CUTSCENE(5, 300),
	CS_TEXT_LIST(2),
		CS_TEXT_DISPLAY_TEXTBOX(0x0E06, 120, 180, 0x0000, 0xFFFF, 0xFFFF),
		CS_TEXT_DISPLAY_TEXTBOX(0x0E07, 200, 290, 0x0000, 0x0000, 0x0000),
	CS_TIME_LIST(1),
		CS_TIME(1, 0, 1, 4, 0, 0),
	CS_CAM_POS_LIST(0, 81),
		CS_CAM_POS(0, 0, 0, 0x42700000, -22, 40, 34, 0),
		CS_CAM_POS(0, 0, 0, 0x42700000, -22, 40, 34, 0),
		CS_CAM_POS(0, 0, 0, 0x42700000, -22, 40, 34, 0),
		CS_CAM_POS(0, 0, 0, 0x42700000, -22, 40, 34, 0),
		CS_CAM_POS(-1, 0, 0, 0x0, 0, 0, 0, 0),
	CS_CAM_FOCUS_POINT_LIST(0, 100),
		CS_CAM_FOCUS_POINT(0, 0, 20, 0x42700000, 10, 51, -12, 0),
		CS_CAM_FOCUS_POINT(0, 0, 20, 0x42700000, 10, 51, -12, 0),
		CS_CAM_FOCUS_POINT(0, 0, 20, 0x42700000, 10, 51, -12, 0),
		CS_CAM_FOCUS_POINT(0, 0, 20, 0x42700000, 10, 51, -12, 0),
		CS_CAM_FOCUS_POINT(-1, 0, 0, 0x0, 0, 0, 0, 0),
	CS_PLAYER_ACTION_LIST(3),
		CS_PLAYER_ACTION(0x31, 0, 60, 0x0, 0x0, 0x0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
		CS_PLAYER_ACTION(0x4F, 60, 80, 0x0, 0x0, 0x0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
		CS_PLAYER_ACTION(0x50, 80, 1000, 0x0, 0x0, 0x0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
	CS_END(),
};

