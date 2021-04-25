#include "ultra64.h"
#include "z64.h"
#include "macros.h"
#include "TriforceRoom_scene.h"

#include "segment_symbols.h"
#include "command_macros_base.h"
#include "z64cutscene_commands.h"
#include "variables.h"

SCmdSoundSettings TriforceRoom_scene_header00_cmd00 = { 0x15, 0x00, 0x00, 0x00, 0x00, 0x00, 0x13, 0x1F };

SCmdRoomList TriforceRoom_scene_header00_cmd01 = { 0x04, 1, (u32)&TriforceRoom_scene_roomList };

SCmdMiscSettings TriforceRoom_scene_header00_cmd02 = { 0x19, 0x00, 0x0E };

SCmdColHeader TriforceRoom_scene_header00_cmd03 = { 0x03, 0x00, (u32)&TriforceRoom_collisionHeader };

SCmdEntranceList TriforceRoom_scene_header00_cmd04 = { 0x06, 0x00, (u32)&TriforceRoom_scene_header00_entranceList };

SCmdSpecialFiles TriforceRoom_scene_header00_cmd05 = { 0x07, 0x00, 0x0002 };

SCmdSpawnList TriforceRoom_scene_header00_cmd06 = { 0x00, 1, (u32)&TriforceRoom_scene_header00_startPositionList };

SCmdSkyboxSettings TriforceRoom_scene_header00_cmd07 = { 0x11, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01 };

SCmdLightSettingList TriforceRoom_scene_header00_cmd08 = { 0x0F, 1, (u32)&TriforceRoom_scene_header00_lightSettings };

SCmdCutsceneData TriforceRoom_scene_header00_cmd09 = { 0x17, 0x00, (u32)&TriforceRoom_scene_header00_cutscene };

SCmdEndMarker TriforceRoom_scene_header00_cmd10 = { 0x14, 0x00, 0x00 };


ActorEntry TriforceRoom_scene_header00_startPositionList[] = {
	{ ACTOR_PLAYER, 0, -48, 460, 0, 32768, 0, 0x0FFF },
};

RomFile TriforceRoom_scene_roomList[] = {
	{ (u32)_TriforceRoom_room_0SegmentRomStart, (u32)_TriforceRoom_room_0SegmentRomEnd },
};

EntranceEntry TriforceRoom_scene_header00_entranceList[1] = {
	{ 0, 0 },
};

LightSettings TriforceRoom_scene_header00_lightSettings[1] = {
	{ 57, 64, 117, 73, 73, 73, 134, 130, 219, 183, 183, 183, 70, 107, 133, 196, 182, 175, 0x07e1, 12800 },
};

u32 TriforceRoom_polygonTypes[] = {
	 0x00000000, 0x00000000,
};

CollisionPoly TriforceRoom_polygons[] = {
	{ 0x0000, 0x0000, 0x0001, 0x0002, 0x0000, 0x0000, 0x7fff, 0xff42 },
	{ 0x0000, 0x0003, 0x0004, 0x0005, 0x0000, 0x0000, 0x7fff, 0xff9b },
	{ 0x0000, 0x0006, 0x0007, 0x0004, 0x0000, 0x7fff, 0x0000, 0x000a },
	{ 0x0000, 0x0005, 0x0008, 0x0003, 0x0000, 0x7fff, 0x0000, 0x0000 },
	{ 0x0000, 0x0009, 0x000a, 0x0007, 0x0000, 0x0000, 0x7fff, 0xff7d },
	{ 0x0000, 0x000b, 0x000c, 0x000a, 0x0000, 0x7fff, 0x0000, 0x0014 },
	{ 0x0000, 0x000d, 0x000e, 0x0001, 0x0000, 0x7fff, 0x0000, 0x0028 },
	{ 0x0000, 0x000f, 0x0010, 0x000c, 0x0000, 0x0000, 0x7fff, 0xff60 },
	{ 0x0000, 0x0011, 0x0002, 0x0010, 0x0000, 0x7fff, 0x0000, 0x001e },
	{ 0x0000, 0x0012, 0x0013, 0x000e, 0x0000, 0x0000, 0x7fff, 0xff25 },
	{ 0x0000, 0x0014, 0x0015, 0x0013, 0x0000, 0x7fff, 0x0000, 0x0032 },
	{ 0x0000, 0x0013, 0x0015, 0x0016, 0x0000, 0x7fff, 0x0000, 0x0032 },
	{ 0x0000, 0x0014, 0x0017, 0x0015, 0x0000, 0x7fff, 0x0000, 0x0032 },
	{ 0x0000, 0x0014, 0x0018, 0x0017, 0x0000, 0x7fff, 0x0000, 0x0032 },
	{ 0x0000, 0x0000, 0x000d, 0x0001, 0x0000, 0x0000, 0x7fff, 0xff42 },
	{ 0x0000, 0x0003, 0x0006, 0x0004, 0x0000, 0x0000, 0x7fff, 0xff9b },
	{ 0x0000, 0x0006, 0x0009, 0x0007, 0x0000, 0x7fff, 0x0000, 0x000a },
	{ 0x0000, 0x0005, 0x0019, 0x0008, 0x0000, 0x7fff, 0x0000, 0x0000 },
	{ 0x0000, 0x0009, 0x000b, 0x000a, 0x0000, 0x0000, 0x7fff, 0xff7d },
	{ 0x0000, 0x000b, 0x000f, 0x000c, 0x0000, 0x7fff, 0x0000, 0x0014 },
	{ 0x0000, 0x000d, 0x0012, 0x000e, 0x0000, 0x7fff, 0x0000, 0x0028 },
	{ 0x0000, 0x000f, 0x0011, 0x0010, 0x0000, 0x0000, 0x7fff, 0xff60 },
	{ 0x0000, 0x0011, 0x0000, 0x0002, 0x0000, 0x7fff, 0x0000, 0x001e },
	{ 0x0000, 0x0012, 0x0014, 0x0013, 0x0000, 0x0000, 0x7fff, 0xff25 },
};

Vec3s TriforceRoom_vertices[26] = {
	{ -103, -30, 190 },
	{ 103, -40, 190 },
	{ 103, -30, 190 },
	{ -103, 0, 101 },
	{ 103, -10, 101 },
	{ 103, 0, 101 },
	{ -103, -10, 101 },
	{ 103, -10, 131 },
	{ -103, 0, -56 },
	{ -103, -10, 131 },
	{ 103, -20, 131 },
	{ -103, -20, 131 },
	{ 103, -20, 160 },
	{ -103, -40, 190 },
	{ 103, -40, 219 },
	{ -103, -20, 160 },
	{ 103, -30, 160 },
	{ -103, -30, 160 },
	{ -103, -40, 219 },
	{ 103, -50, 219 },
	{ -103, -50, 219 },
	{ 275, -50, 649 },
	{ 275, -50, 219 },
	{ -275, -50, 649 },
	{ -275, -50, 219 },
	{ 103, 0, -56 },
};

CollisionHeader TriforceRoom_collisionHeader = { -275, -50, -56, 275, 0, 649, 26, TriforceRoom_vertices, 24, TriforceRoom_polygons, TriforceRoom_polygonTypes, 0, 0, 0 };

// clang-format off
s32 TriforceRoom_scene_header00_cutscene[] = {
	CS_BEGIN_CUTSCENE(9, 542),
	CS_PLAYER_ACTION_LIST(6),
		CS_PLAYER_ACTION(0x0001, 0, 50, 0x0, 0xffff8000, 0x0, 0, -49, 442, 0, 0, 62, 0, 0, 0),
		CS_PLAYER_ACTION(0x0034, 50, 90, 0x0, 0xffff8000, 0x0, 0, 0, 62, 0, 0, 62, 0, 0, 0),
		CS_PLAYER_ACTION(0x004B, 90, 310, 0x0, 0xffff8000, 0x0, 0, 0, 62, 0, 0, 62, 0, 0, 0),
		CS_PLAYER_ACTION(0x004E, 310, 410, 0x0, 0xffff8000, 0x0, 0, 0, 62, 0, 0, 62, 0, 0, 0),
		CS_PLAYER_ACTION(0x0007, 410, 420, 0x0, 0xffff8000, 0x0, 0, 0, 62, 0, 0, 62, 0, 0, 0),
		CS_PLAYER_ACTION(0x0008, 420, 540, 0x0, 0x0, 0x0, 0, 0, 62, 0, 0, 62, 0, 0, 0),
	CS_CAM_POS_LIST(0, 286),
		CS_CAM_POS(0, 0, 0, 0x42960000, 481, -46, 287, 0),
		CS_CAM_POS(0, 0, 0, 0x42960000, 270, -47, 364, 0),
		CS_CAM_POS(0, 0, 0, 0x42820000, -148, -40, 418, 0),
		CS_CAM_POS(0, 0, 0, 0x42820000, -267, 62, 367, 0),
		CS_CAM_POS(0, 0, 0, 0x42820000, -267, 64, 290, 0),
		CS_CAM_POS(0, 0, 0, 0x42820000, -268, 73, 215, 0),
		CS_CAM_POS(0, 0, 0, 0x42820000, -268, 85, 128, 0),
		CS_CAM_POS(0, 0, 0, 0x42820000, -265, 98, 42, 0),
		CS_CAM_POS(-1, 0, 0, 0x0, 0, 0, 0, 0),
	CS_CAM_POS_LIST(175, 356),
		CS_CAM_POS(0, 0, 0, 0x42700000, 43, 84, 61, 0),
		CS_CAM_POS(0, 0, 0, 0x42700000, 32, 84, 22, 0),
		CS_CAM_POS(0, 0, 0, 0x42700000, -43, 84, 27, 0),
		CS_CAM_POS(0, 0, 0, 0x42700000, -47, 84, 68, 0),
		CS_CAM_POS(-1, 0, 0, 0x0, 0, 0, 0, 0),
	CS_CAM_POS_LIST(230, 541),
		CS_CAM_POS(0, 0, 0, 0x42700000, -156, 99, 283, 0),
		CS_CAM_POS(0, 0, 0, 0x42700000, -223, 87, 209, 0),
		CS_CAM_POS(0, 0, 0, 0x42700000, -257, 87, 96, 0),
		CS_CAM_POS(0, 0, 0, 0x42700000, -227, 89, -2, 0),
		CS_CAM_POS(0, 0, 0, 0x42700000, -158, 94, -75, 0),
		CS_CAM_POS(0, 0, 0, 0x42700000, -69, 93, -87, 0),
		CS_CAM_POS(0, 0, 0, 0x42700000, 0, 91, -85, 0),
		CS_CAM_POS(-1, 0, 0, 0x0, 0, 0, 0, 0),
	CS_CAM_POS_LIST(407, 492),
		CS_CAM_POS(0, 0, 0, 0x428c0000, 0, -44, 936, 0),
		CS_CAM_POS(0, 0, 0, 0x428c0000, 0, -44, 617, 0),
		CS_CAM_POS(0, 0, 0, 0x428c0000, 0, -44, 420, 0),
		CS_CAM_POS(0, 0, 0, 0x425c0000, 0, 96, 367, 0),
		CS_CAM_POS(0, 0, 0, 0x42700000, 0, 116, 247, 0),
		CS_CAM_POS(0, 0, 0, 0x42700000, 0, 117, -14, 0),
		CS_CAM_POS(-1, 0, 0, 0x0, 0, 0, 0, 0),
	CS_CAM_FOCUS_POINT_LIST(0, 305),
		CS_CAM_FOCUS_POINT(0, 0, 20, 0x42960000, -1, 28, 56, 0),
		CS_CAM_FOCUS_POINT(0, 0, 25, 0x42960000, -1, 28, 56, 0),
		CS_CAM_FOCUS_POINT(0, 0, 40, 0x42820000, 3, 81, 34, 0),
		CS_CAM_FOCUS_POINT(0, 0, 30, 0x42820000, -1, 102, 25, 0),
		CS_CAM_FOCUS_POINT(0, 0, 40, 0x42820000, -3, 115, 16, 0),
		CS_CAM_FOCUS_POINT(0, 0, 55, 0x42820000, 0, 129, 15, 0),
		CS_CAM_FOCUS_POINT(0, 0, 55, 0x42820000, 0, 148, 17, 0),
		CS_CAM_FOCUS_POINT(0, 0, 20, 0x42820000, 0, 149, 16, 0),
		CS_CAM_FOCUS_POINT(-1, 0, 0, 0x0, 0, 0, 0, 0),
	CS_CAM_FOCUS_POINT_LIST(175, 375),
		CS_CAM_FOCUS_POINT(0, 0, 20, 0x42700000, 3, 81, 61, 0),
		CS_CAM_FOCUS_POINT(0, 0, 70, 0x42700000, 2, 81, 61, 0),
		CS_CAM_FOCUS_POINT(0, 0, 70, 0x42700000, 0, 81, 61, 0),
		CS_CAM_FOCUS_POINT(0, 0, 20, 0x42700000, 0, 81, 63, 0),
		CS_CAM_FOCUS_POINT(-1, 0, 0, 0x0, 0, 0, 0, 0),
	CS_CAM_FOCUS_POINT_LIST(230, 560),
		CS_CAM_FOCUS_POINT(0, 0, 20, 0x42700000, 15, 139, 38, 0),
		CS_CAM_FOCUS_POINT(0, 0, 60, 0x42700000, 13, 133, 33, 0),
		CS_CAM_FOCUS_POINT(0, 0, 60, 0x42700000, 7, 114, 31, 0),
		CS_CAM_FOCUS_POINT(0, 0, 50, 0x42700000, 7, 98, 27, 0),
		CS_CAM_FOCUS_POINT(0, 0, 50, 0x42700000, 6, 93, 29, 0),
		CS_CAM_FOCUS_POINT(0, 0, 50, 0x42700000, 6, 88, 25, 0),
		CS_CAM_FOCUS_POINT(0, 0, 20, 0x42700000, 6, 88, 27, 0),
		CS_CAM_FOCUS_POINT(-1, 0, 0, 0x0, 0, 0, 0, 0),
	CS_CAM_FOCUS_POINT_LIST(407, 511),
		CS_CAM_FOCUS_POINT(0, 0, 20, 0x428c0000, 0, -44, 870, 0),
		CS_CAM_FOCUS_POINT(0, 0, 20, 0x428c0000, 0, -39, 551, 0),
		CS_CAM_FOCUS_POINT(0, 0, 12, 0x428c0000, 0, -39, 354, 0),
		CS_CAM_FOCUS_POINT(0, 0, 7, 0x425c0000, 0, 78, 301, 0),
		CS_CAM_FOCUS_POINT(0, 0, 5, 0x42700000, 0, 97, 181, 0),
		CS_CAM_FOCUS_POINT(0, 0, 20, 0x42700000, 0, 98, -80, 0),
		CS_CAM_FOCUS_POINT(-1, 0, 0, 0x0, 0, 0, 0, 0),
	CS_END(),
};
// clang-format on
