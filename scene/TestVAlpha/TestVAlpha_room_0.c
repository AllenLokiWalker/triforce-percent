#include "ultra64.h"
#include "z64.h"
#include "macros.h"
#include "TestVAlpha_room_0.h"

#include "segment_symbols.h"
#include "command_macros_base.h"
#include "z64cutscene_commands.h"
#include "variables.h"
#include "TestVAlpha_scene.h"

SCmdBase TestVAlpha_room_0_header00[] = {
	SCENE_CMD_ECHO_SETTINGS(0x00),
	SCENE_CMD_ROOM_BEHAVIOR(0x00, 0x00, false, false),
	SCENE_CMD_SKYBOX_DISABLES(false, false),
	SCENE_CMD_TIME_SETTINGS(0xFF, 0xFF, 10),
	SCENE_CMD_MESH(&TestVAlpha_room_0_meshHeader),
	SCENE_CMD_END(),
};

MeshHeader0 TestVAlpha_room_0_meshHeader = { {0}, 1, (u32)&TestVAlpha_room_0_meshDListEntry, (u32)&(TestVAlpha_room_0_meshDListEntry) + sizeof(TestVAlpha_room_0_meshDListEntry) };

MeshEntry0 TestVAlpha_room_0_meshDListEntry[1] = {
	{ (u32)TestVAlpha_room_0_entry_0_opaque, (u32)TestVAlpha_room_0_entry_0_transparent },
};

Gfx TestVAlpha_room_0_entry_0_opaque[] = {
	gsSPDisplayList(TestVAlpha_dl_Floor_mesh_layer_Opaque),
	gsSPEndDisplayList(),
};

Gfx TestVAlpha_room_0_entry_0_transparent[] = {
	gsSPDisplayList(TestVAlpha_dl_Walls_mesh_layer_Transparent),
	gsSPEndDisplayList(),
};

Vtx TestVAlpha_dl_Floor_mesh_layer_Opaque_vtx_0[143] = {
	{{{1438, -120, -1079},0, {1008, 112},{0x0, 0x7F, 0x0, 0xFF}}},
	{{{1438, -120, -1438},0, {1008, -16},{0x0, 0x7F, 0x0, 0xFF}}},
	{{{1079, -120, -1438},0, {880, -16},{0x0, 0x7F, 0x0, 0xFF}}},
	{{{1079, -120, -1079},0, {880, 112},{0x0, 0x7F, 0x0, 0xFF}}},
	{{{719, -120, -1438},0, {752, -16},{0x0, 0x7F, 0x0, 0xFF}}},
	{{{719, -120, -1079},0, {752, 112},{0x0, 0x7F, 0x0, 0xFF}}},
	{{{360, -120, -1438},0, {624, -16},{0x0, 0x7F, 0x0, 0xFF}}},
	{{{360, -120, -1079},0, {624, 112},{0x0, 0x7F, 0x0, 0xFF}}},
	{{{0, -120, -1438},0, {496, -16},{0x0, 0x7F, 0x0, 0xFF}}},
	{{{0, -120, -1079},0, {496, 112},{0x0, 0x7F, 0x0, 0xFF}}},
	{{{-360, -120, -1438},0, {368, -16},{0x0, 0x7F, 0x0, 0xFF}}},
	{{{-360, -120, -1079},0, {368, 112},{0x0, 0x7F, 0x0, 0xFF}}},
	{{{-719, -120, -1438},0, {240, -16},{0x0, 0x7F, 0x0, 0xFF}}},
	{{{-719, -120, -1079},0, {240, 112},{0x0, 0x7F, 0x0, 0xFF}}},
	{{{-1079, -120, -1438},0, {112, -16},{0x0, 0x7F, 0x0, 0xFF}}},
	{{{-1079, -120, -1079},0, {112, 112},{0x0, 0x7F, 0x0, 0xFF}}},
	{{{-1079, -120, -1079},0, {112, 112},{0x0, 0x7F, 0x0, 0xFF}}},
	{{{-1079, -120, -1438},0, {112, -16},{0x0, 0x7F, 0x0, 0xFF}}},
	{{{-1438, -120, -1438},0, {-16, -16},{0x0, 0x7F, 0x0, 0xFF}}},
	{{{-1438, -120, -1079},0, {-16, 112},{0x0, 0x7F, 0x0, 0xFF}}},
	{{{-1079, -120, -719},0, {112, 240},{0x0, 0x7F, 0x0, 0xFF}}},
	{{{-1438, -120, -719},0, {-16, 240},{0x0, 0x7F, 0x0, 0xFF}}},
	{{{-1079, -120, -360},0, {112, 368},{0x0, 0x7F, 0x0, 0xFF}}},
	{{{-1438, -120, -360},0, {-16, 368},{0x0, 0x7F, 0x0, 0xFF}}},
	{{{-1079, -120, 0},0, {112, 496},{0x0, 0x7F, 0x0, 0xFF}}},
	{{{-1438, -120, 0},0, {-16, 496},{0x0, 0x7F, 0x0, 0xFF}}},
	{{{-1079, -120, 360},0, {112, 624},{0x0, 0x7F, 0x0, 0xFF}}},
	{{{-1438, -120, 360},0, {-16, 624},{0x0, 0x7F, 0x0, 0xFF}}},
	{{{-1079, -120, 719},0, {112, 752},{0x0, 0x7F, 0x0, 0xFF}}},
	{{{-1438, -120, 719},0, {-16, 752},{0x0, 0x7F, 0x0, 0xFF}}},
	{{{-1079, -120, 1079},0, {112, 880},{0x0, 0x7F, 0x0, 0xFF}}},
	{{{-1438, -120, 1079},0, {-16, 880},{0x0, 0x7F, 0x0, 0xFF}}},
	{{{-1079, -120, 1438},0, {112, 1008},{0x0, 0x7F, 0x0, 0xFF}}},
	{{{-1079, -120, 1079},0, {112, 880},{0x0, 0x7F, 0x0, 0xFF}}},
	{{{-1438, -120, 1079},0, {-16, 880},{0x0, 0x7F, 0x0, 0xFF}}},
	{{{-1438, -120, 1438},0, {-16, 1008},{0x0, 0x7F, 0x0, 0xFF}}},
	{{{-719, -120, 1438},0, {240, 1008},{0x0, 0x7F, 0x0, 0xFF}}},
	{{{-719, -120, 1079},0, {240, 880},{0x0, 0x7F, 0x0, 0xFF}}},
	{{{-360, -120, 1438},0, {368, 1008},{0x0, 0x7F, 0x0, 0xFF}}},
	{{{-360, -120, 1079},0, {368, 880},{0x0, 0x7F, 0x0, 0xFF}}},
	{{{0, -120, 1438},0, {496, 1008},{0x0, 0x7F, 0x0, 0xFF}}},
	{{{0, -120, 1079},0, {496, 880},{0x0, 0x7F, 0x0, 0xFF}}},
	{{{360, -120, 1438},0, {624, 1008},{0x0, 0x7F, 0x0, 0xFF}}},
	{{{360, -120, 1079},0, {624, 880},{0x0, 0x7F, 0x0, 0xFF}}},
	{{{719, -120, 1438},0, {752, 1008},{0x0, 0x7F, 0x0, 0xFF}}},
	{{{719, -120, 1079},0, {752, 880},{0x0, 0x7F, 0x0, 0xFF}}},
	{{{1079, -120, 1438},0, {880, 1008},{0x0, 0x7F, 0x0, 0xFF}}},
	{{{1079, -120, 1079},0, {880, 880},{0x0, 0x7F, 0x0, 0xFF}}},
	{{{1438, -120, 1438},0, {1008, 1008},{0x0, 0x7F, 0x0, 0xFF}}},
	{{{1079, -120, 1079},0, {880, 880},{0x0, 0x7F, 0x0, 0xFF}}},
	{{{1079, -120, 1438},0, {880, 1008},{0x0, 0x7F, 0x0, 0xFF}}},
	{{{1438, -120, 1079},0, {1008, 880},{0x0, 0x7F, 0x0, 0xFF}}},
	{{{1079, -120, 719},0, {880, 752},{0x0, 0x7F, 0x0, 0xFF}}},
	{{{1438, -120, 719},0, {1008, 752},{0x0, 0x7F, 0x0, 0xFF}}},
	{{{1079, -120, 360},0, {880, 624},{0x0, 0x7F, 0x0, 0xFF}}},
	{{{1438, -120, 360},0, {1008, 624},{0x0, 0x7F, 0x0, 0xFF}}},
	{{{1079, -120, 0},0, {880, 496},{0x0, 0x7F, 0x0, 0xFF}}},
	{{{1438, -120, 0},0, {1008, 496},{0x0, 0x7F, 0x0, 0xFF}}},
	{{{1079, -120, -360},0, {880, 368},{0x0, 0x7F, 0x0, 0xFF}}},
	{{{1438, -120, -360},0, {1008, 368},{0x0, 0x7F, 0x0, 0xFF}}},
	{{{1079, -120, -719},0, {880, 240},{0x0, 0x7F, 0x0, 0xFF}}},
	{{{1438, -120, -719},0, {1008, 240},{0x0, 0x7F, 0x0, 0xFF}}},
	{{{1079, -120, -1079},0, {880, 112},{0x0, 0x7F, 0x0, 0xFF}}},
	{{{1438, -120, -1079},0, {1008, 112},{0x0, 0x7F, 0x0, 0xFF}}},
	{{{719, -120, -1079},0, {752, 112},{0x0, 0x7F, 0x0, 0xFF}}},
	{{{1079, -120, -719},0, {880, 240},{0x0, 0x7F, 0x0, 0xFF}}},
	{{{1079, -120, -1079},0, {880, 112},{0x0, 0x7F, 0x0, 0xFF}}},
	{{{719, -120, -719},0, {752, 240},{0x0, 0x7F, 0x0, 0xFF}}},
	{{{360, -120, -1079},0, {624, 112},{0x0, 0x7F, 0x0, 0xFF}}},
	{{{360, -120, -719},0, {624, 240},{0x0, 0x7F, 0x0, 0xFF}}},
	{{{0, -120, -1079},0, {496, 112},{0x0, 0x7F, 0x0, 0xFF}}},
	{{{0, -120, -719},0, {496, 240},{0x0, 0x7F, 0x0, 0xFF}}},
	{{{-360, -120, -1079},0, {368, 112},{0x0, 0x7F, 0x0, 0xFF}}},
	{{{-360, -120, -719},0, {368, 240},{0x0, 0x7F, 0x0, 0xFF}}},
	{{{-719, -120, -1079},0, {240, 112},{0x0, 0x7F, 0x0, 0xFF}}},
	{{{-719, -120, -719},0, {240, 240},{0x0, 0x7F, 0x0, 0xFF}}},
	{{{-1079, -120, -1079},0, {112, 112},{0x0, 0x7F, 0x0, 0xFF}}},
	{{{-1079, -120, -719},0, {112, 240},{0x0, 0x7F, 0x0, 0xFF}}},
	{{{-719, -120, -360},0, {240, 368},{0x0, 0x7F, 0x0, 0xFF}}},
	{{{-1079, -120, -360},0, {112, 368},{0x0, 0x7F, 0x0, 0xFF}}},
	{{{-719, -120, 0},0, {240, 496},{0x0, 0x7F, 0x0, 0xFF}}},
	{{{-719, -120, -360},0, {240, 368},{0x0, 0x7F, 0x0, 0xFF}}},
	{{{-1079, -120, -360},0, {112, 368},{0x0, 0x7F, 0x0, 0xFF}}},
	{{{-1079, -120, 0},0, {112, 496},{0x0, 0x7F, 0x0, 0xFF}}},
	{{{-719, -120, 360},0, {240, 624},{0x0, 0x7F, 0x0, 0xFF}}},
	{{{-1079, -120, 360},0, {112, 624},{0x0, 0x7F, 0x0, 0xFF}}},
	{{{-719, -120, 719},0, {240, 752},{0x0, 0x7F, 0x0, 0xFF}}},
	{{{-1079, -120, 719},0, {112, 752},{0x0, 0x7F, 0x0, 0xFF}}},
	{{{-719, -120, 1079},0, {240, 880},{0x0, 0x7F, 0x0, 0xFF}}},
	{{{-1079, -120, 1079},0, {112, 880},{0x0, 0x7F, 0x0, 0xFF}}},
	{{{-360, -120, 1079},0, {368, 880},{0x0, 0x7F, 0x0, 0xFF}}},
	{{{-360, -120, 719},0, {368, 752},{0x0, 0x7F, 0x0, 0xFF}}},
	{{{0, -120, 1079},0, {496, 880},{0x0, 0x7F, 0x0, 0xFF}}},
	{{{0, -120, 719},0, {496, 752},{0x0, 0x7F, 0x0, 0xFF}}},
	{{{360, -120, 1079},0, {624, 880},{0x0, 0x7F, 0x0, 0xFF}}},
	{{{360, -120, 719},0, {624, 752},{0x0, 0x7F, 0x0, 0xFF}}},
	{{{360, -120, 1079},0, {624, 880},{0x0, 0x7F, 0x0, 0xFF}}},
	{{{719, -120, 1079},0, {752, 880},{0x0, 0x7F, 0x0, 0xFF}}},
	{{{360, -120, 719},0, {624, 752},{0x0, 0x7F, 0x0, 0xFF}}},
	{{{719, -120, 719},0, {752, 752},{0x0, 0x7F, 0x0, 0xFF}}},
	{{{1079, -120, 1079},0, {880, 880},{0x0, 0x7F, 0x0, 0xFF}}},
	{{{1079, -120, 719},0, {880, 752},{0x0, 0x7F, 0x0, 0xFF}}},
	{{{719, -120, 360},0, {752, 624},{0x0, 0x7F, 0x0, 0xFF}}},
	{{{1079, -120, 360},0, {880, 624},{0x0, 0x7F, 0x0, 0xFF}}},
	{{{719, -120, 0},0, {752, 496},{0x0, 0x7F, 0x0, 0xFF}}},
	{{{1079, -120, 0},0, {880, 496},{0x0, 0x7F, 0x0, 0xFF}}},
	{{{719, -120, -360},0, {752, 368},{0x0, 0x7F, 0x0, 0xFF}}},
	{{{1079, -120, -360},0, {880, 368},{0x0, 0x7F, 0x0, 0xFF}}},
	{{{719, -120, -719},0, {752, 240},{0x0, 0x7F, 0x0, 0xFF}}},
	{{{1079, -120, -719},0, {880, 240},{0x0, 0x7F, 0x0, 0xFF}}},
	{{{360, -120, -719},0, {624, 240},{0x0, 0x7F, 0x0, 0xFF}}},
	{{{360, -120, -360},0, {624, 368},{0x0, 0x7F, 0x0, 0xFF}}},
	{{{0, -120, -719},0, {496, 240},{0x0, 0x7F, 0x0, 0xFF}}},
	{{{360, -120, -360},0, {624, 368},{0x0, 0x7F, 0x0, 0xFF}}},
	{{{360, -120, -719},0, {624, 240},{0x0, 0x7F, 0x0, 0xFF}}},
	{{{0, -120, -360},0, {496, 368},{0x0, 0x7F, 0x0, 0xFF}}},
	{{{-360, -120, -719},0, {368, 240},{0x0, 0x7F, 0x0, 0xFF}}},
	{{{-360, -120, -360},0, {368, 368},{0x0, 0x7F, 0x0, 0xFF}}},
	{{{-719, -120, -719},0, {240, 240},{0x0, 0x7F, 0x0, 0xFF}}},
	{{{-719, -120, -360},0, {240, 368},{0x0, 0x7F, 0x0, 0xFF}}},
	{{{-360, -120, 0},0, {368, 496},{0x0, 0x7F, 0x0, 0xFF}}},
	{{{-719, -120, 0},0, {240, 496},{0x0, 0x7F, 0x0, 0xFF}}},
	{{{-360, -120, 360},0, {368, 624},{0x0, 0x7F, 0x0, 0xFF}}},
	{{{-719, -120, 360},0, {240, 624},{0x0, 0x7F, 0x0, 0xFF}}},
	{{{-360, -120, 719},0, {368, 752},{0x0, 0x7F, 0x0, 0xFF}}},
	{{{-719, -120, 719},0, {240, 752},{0x0, 0x7F, 0x0, 0xFF}}},
	{{{0, -120, 719},0, {496, 752},{0x0, 0x7F, 0x0, 0xFF}}},
	{{{0, -120, 360},0, {496, 624},{0x0, 0x7F, 0x0, 0xFF}}},
	{{{360, -120, 719},0, {624, 752},{0x0, 0x7F, 0x0, 0xFF}}},
	{{{0, -120, 360},0, {496, 624},{0x0, 0x7F, 0x0, 0xFF}}},
	{{{0, -120, 719},0, {496, 752},{0x0, 0x7F, 0x0, 0xFF}}},
	{{{360, -120, 360},0, {624, 624},{0x0, 0x7F, 0x0, 0xFF}}},
	{{{719, -120, 719},0, {752, 752},{0x0, 0x7F, 0x0, 0xFF}}},
	{{{719, -120, 360},0, {752, 624},{0x0, 0x7F, 0x0, 0xFF}}},
	{{{360, -120, 0},0, {624, 496},{0x0, 0x7F, 0x0, 0xFF}}},
	{{{719, -120, 0},0, {752, 496},{0x0, 0x7F, 0x0, 0xFF}}},
	{{{360, -120, -360},0, {624, 368},{0x0, 0x7F, 0x0, 0xFF}}},
	{{{719, -120, -360},0, {752, 368},{0x0, 0x7F, 0x0, 0xFF}}},
	{{{0, -120, -360},0, {496, 368},{0x0, 0x7F, 0x0, 0xFF}}},
	{{{0, -120, 0},0, {496, 496},{0x0, 0x7F, 0x0, 0xFF}}},
	{{{-360, -120, -360},0, {368, 368},{0x0, 0x7F, 0x0, 0xFF}}},
	{{{-360, -120, 0},0, {368, 496},{0x0, 0x7F, 0x0, 0xFF}}},
	{{{-360, -120, 360},0, {368, 624},{0x0, 0x7F, 0x0, 0xFF}}},
};

Gfx TestVAlpha_dl_Floor_mesh_layer_Opaque_tri_0[] = {
	gsSPVertex(TestVAlpha_dl_Floor_mesh_layer_Opaque_vtx_0 + 0, 16, 0),
	gsSP1Triangle(0, 1, 2, 0),
	gsSP1Triangle(3, 0, 2, 0),
	gsSP1Triangle(3, 2, 4, 0),
	gsSP1Triangle(5, 3, 4, 0),
	gsSP1Triangle(5, 4, 6, 0),
	gsSP1Triangle(7, 5, 6, 0),
	gsSP1Triangle(7, 6, 8, 0),
	gsSP1Triangle(9, 7, 8, 0),
	gsSP1Triangle(9, 8, 10, 0),
	gsSP1Triangle(11, 9, 10, 0),
	gsSP1Triangle(11, 10, 12, 0),
	gsSP1Triangle(13, 11, 12, 0),
	gsSP1Triangle(13, 12, 14, 0),
	gsSP1Triangle(15, 13, 14, 0),
	gsSPVertex(TestVAlpha_dl_Floor_mesh_layer_Opaque_vtx_0 + 16, 16, 0),
	gsSP1Triangle(0, 1, 2, 0),
	gsSP1Triangle(0, 2, 3, 0),
	gsSP1Triangle(4, 0, 3, 0),
	gsSP1Triangle(4, 3, 5, 0),
	gsSP1Triangle(6, 4, 5, 0),
	gsSP1Triangle(6, 5, 7, 0),
	gsSP1Triangle(8, 6, 7, 0),
	gsSP1Triangle(8, 7, 9, 0),
	gsSP1Triangle(10, 8, 9, 0),
	gsSP1Triangle(10, 9, 11, 0),
	gsSP1Triangle(12, 10, 11, 0),
	gsSP1Triangle(12, 11, 13, 0),
	gsSP1Triangle(14, 12, 13, 0),
	gsSP1Triangle(14, 13, 15, 0),
	gsSPVertex(TestVAlpha_dl_Floor_mesh_layer_Opaque_vtx_0 + 32, 16, 0),
	gsSP1Triangle(0, 1, 2, 0),
	gsSP1Triangle(0, 2, 3, 0),
	gsSP1Triangle(4, 1, 0, 0),
	gsSP1Triangle(4, 5, 1, 0),
	gsSP1Triangle(6, 5, 4, 0),
	gsSP1Triangle(6, 7, 5, 0),
	gsSP1Triangle(8, 7, 6, 0),
	gsSP1Triangle(8, 9, 7, 0),
	gsSP1Triangle(10, 9, 8, 0),
	gsSP1Triangle(10, 11, 9, 0),
	gsSP1Triangle(12, 11, 10, 0),
	gsSP1Triangle(12, 13, 11, 0),
	gsSP1Triangle(14, 13, 12, 0),
	gsSP1Triangle(14, 15, 13, 0),
	gsSPVertex(TestVAlpha_dl_Floor_mesh_layer_Opaque_vtx_0 + 48, 16, 0),
	gsSP1Triangle(0, 1, 2, 0),
	gsSP1Triangle(0, 3, 1, 0),
	gsSP1Triangle(1, 3, 4, 0),
	gsSP1Triangle(3, 5, 4, 0),
	gsSP1Triangle(4, 5, 6, 0),
	gsSP1Triangle(5, 7, 6, 0),
	gsSP1Triangle(6, 7, 8, 0),
	gsSP1Triangle(7, 9, 8, 0),
	gsSP1Triangle(8, 9, 10, 0),
	gsSP1Triangle(9, 11, 10, 0),
	gsSP1Triangle(10, 11, 12, 0),
	gsSP1Triangle(11, 13, 12, 0),
	gsSP1Triangle(12, 13, 14, 0),
	gsSP1Triangle(13, 15, 14, 0),
	gsSPVertex(TestVAlpha_dl_Floor_mesh_layer_Opaque_vtx_0 + 64, 16, 0),
	gsSP1Triangle(0, 1, 2, 0),
	gsSP1Triangle(3, 1, 0, 0),
	gsSP1Triangle(3, 0, 4, 0),
	gsSP1Triangle(5, 3, 4, 0),
	gsSP1Triangle(6, 5, 4, 0),
	gsSP1Triangle(7, 5, 6, 0),
	gsSP1Triangle(7, 6, 8, 0),
	gsSP1Triangle(9, 7, 8, 0),
	gsSP1Triangle(10, 9, 8, 0),
	gsSP1Triangle(11, 9, 10, 0),
	gsSP1Triangle(11, 10, 12, 0),
	gsSP1Triangle(11, 12, 13, 0),
	gsSP1Triangle(14, 11, 13, 0),
	gsSP1Triangle(15, 14, 13, 0),
	gsSPVertex(TestVAlpha_dl_Floor_mesh_layer_Opaque_vtx_0 + 80, 16, 0),
	gsSP1Triangle(0, 1, 2, 0),
	gsSP1Triangle(0, 2, 3, 0),
	gsSP1Triangle(4, 0, 3, 0),
	gsSP1Triangle(5, 4, 3, 0),
	gsSP1Triangle(6, 4, 5, 0),
	gsSP1Triangle(6, 5, 7, 0),
	gsSP1Triangle(8, 6, 7, 0),
	gsSP1Triangle(9, 8, 7, 0),
	gsSP1Triangle(10, 6, 8, 0),
	gsSP1Triangle(10, 11, 6, 0),
	gsSP1Triangle(10, 12, 11, 0),
	gsSP1Triangle(12, 13, 11, 0),
	gsSP1Triangle(14, 13, 12, 0),
	gsSP1Triangle(14, 15, 13, 0),
	gsSPVertex(TestVAlpha_dl_Floor_mesh_layer_Opaque_vtx_0 + 96, 16, 0),
	gsSP1Triangle(0, 1, 2, 0),
	gsSP1Triangle(1, 3, 2, 0),
	gsSP1Triangle(4, 3, 1, 0),
	gsSP1Triangle(4, 5, 3, 0),
	gsSP1Triangle(3, 5, 6, 0),
	gsSP1Triangle(6, 5, 7, 0),
	gsSP1Triangle(6, 7, 8, 0),
	gsSP1Triangle(7, 9, 8, 0),
	gsSP1Triangle(8, 9, 10, 0),
	gsSP1Triangle(10, 9, 11, 0),
	gsSP1Triangle(10, 11, 12, 0),
	gsSP1Triangle(11, 13, 12, 0),
	gsSP1Triangle(14, 10, 12, 0),
	gsSP1Triangle(14, 15, 10, 0),
	gsSPVertex(TestVAlpha_dl_Floor_mesh_layer_Opaque_vtx_0 + 112, 16, 0),
	gsSP1Triangle(0, 1, 2, 0),
	gsSP1Triangle(3, 1, 0, 0),
	gsSP1Triangle(3, 0, 4, 0),
	gsSP1Triangle(5, 3, 4, 0),
	gsSP1Triangle(5, 4, 6, 0),
	gsSP1Triangle(5, 6, 7, 0),
	gsSP1Triangle(8, 5, 7, 0),
	gsSP1Triangle(8, 7, 9, 0),
	gsSP1Triangle(10, 8, 9, 0),
	gsSP1Triangle(11, 10, 9, 0),
	gsSP1Triangle(11, 12, 10, 0),
	gsSP1Triangle(13, 12, 11, 0),
	gsSP1Triangle(12, 14, 10, 0),
	gsSP1Triangle(14, 15, 10, 0),
	gsSPVertex(TestVAlpha_dl_Floor_mesh_layer_Opaque_vtx_0 + 128, 15, 0),
	gsSP1Triangle(0, 1, 2, 0),
	gsSP1Triangle(0, 3, 1, 0),
	gsSP1Triangle(4, 3, 0, 0),
	gsSP1Triangle(4, 5, 3, 0),
	gsSP1Triangle(3, 5, 6, 0),
	gsSP1Triangle(5, 7, 6, 0),
	gsSP1Triangle(6, 7, 8, 0),
	gsSP1Triangle(8, 7, 9, 0),
	gsSP1Triangle(10, 6, 8, 0),
	gsSP1Triangle(11, 6, 10, 0),
	gsSP1Triangle(11, 10, 12, 0),
	gsSP1Triangle(11, 12, 13, 0),
	gsSP1Triangle(1, 11, 13, 0),
	gsSP1Triangle(14, 1, 13, 0),
	gsSP1Triangle(3, 11, 1, 0),
	gsSP1Triangle(3, 6, 11, 0),
	gsSPEndDisplayList(),
};

Vtx TestVAlpha_dl_Walls_mesh_layer_Transparent_vtx_0[44] = {
	{{{-112, -120, -24},0, {1008, 1008},{0x0, 0xFF, 0x2D, 0x0}}},
	{{{-479, 2, -24},0, {-16, -16},{0x0, 0x1A, 0xFF, 0xFF}}},
	{{{-479, -120, -24},0, {-16, 1008},{0xFF, 0x0, 0x10, 0x0}}},
	{{{-112, 2, -24},0, {1008, -16},{0xFF, 0x0, 0xA, 0x0}}},
	{{{-67, -120, -626},0, {1008, 1008},{0x0, 0x1A, 0xFF, 0x0}}},
	{{{-524, 2, -198},0, {-16, -16},{0x0, 0x1A, 0xFF, 0xFF}}},
	{{{-524, -120, -198},0, {-16, 1008},{0x0, 0x1A, 0xFF, 0x0}}},
	{{{-67, 2, -626},0, {1008, -16},{0x0, 0x1A, 0xFF, 0xFF}}},
	{{{639, -120, -131},0, {1008, 1008},{0xFF, 0x0, 0xA, 0xFF}}},
	{{{363, 2, -693},0, {-16, -16},{0xFF, 0x0, 0xA, 0x0}}},
	{{{363, -120, -693},0, {-16, 1008},{0xFF, 0x0, 0xA, 0xFF}}},
	{{{639, 2, -131},0, {1008, -16},{0xFF, 0x0, 0xA, 0x0}}},
	{{{338, -120, 643},0, {1008, 1008},{0x0, 0xFF, 0x2D, 0x0}}},
	{{{612, 2, 278},0, {-16, -16},{0x0, 0xFF, 0x2D, 0xFF}}},
	{{{612, -120, 278},0, {-16, 1008},{0x0, 0xFF, 0x2D, 0xFF}}},
	{{{338, 2, 643},0, {1008, -16},{0x0, 0xFF, 0x2D, 0x0}}},
	{{{18, -120, 663},0, {1008, 1008},{0xFF, 0x0, 0xD2, 0xFF}}},
	{{{-191, 2, 258},0, {-16, -16},{0x0, 0x0, 0x0, 0xFF}}},
	{{{-191, -120, 258},0, {-16, 1008},{0x0, 0xF1, 0xFF, 0x0}}},
	{{{18, 2, 663},0, {1008, -16},{0xFF, 0xEC, 0x0, 0x0}}},
	{{{-1182, -120, 30},0, {1008, 1008},{0x0, 0x0, 0x0, 0xFF}}},
	{{{-864, 2, 1253},0, {-16, -16},{0x0, 0x0, 0x0, 0x0}}},
	{{{-864, -120, 1253},0, {-16, 1008},{0x0, 0x0, 0x0, 0x0}}},
	{{{-1182, 2, 30},0, {1008, -16},{0xFF, 0xFF, 0xFF, 0xFF}}},
	{{{-889, -120, -956},0, {1008, 1008},{0xFF, 0x0, 0xD2, 0x0}}},
	{{{-1083, 2, -543},0, {-16, -16},{0x0, 0x0, 0x0, 0x0}}},
	{{{-1083, -120, -543},0, {-16, 1008},{0x0, 0xF1, 0xFF, 0xFF}}},
	{{{-889, 2, -956},0, {1008, -16},{0xFF, 0xEC, 0x0, 0xFF}}},
	{{{142, -120, 1181},0, {1008, 1008},{0x0, 0xFF, 0x2D, 0x0}}},
	{{{1139, 2, 978},0, {-16, -16},{0x0, 0x1A, 0xFF, 0xFF}}},
	{{{1139, -120, 978},0, {-16, 1008},{0xFF, 0x0, 0x10, 0xFF}}},
	{{{142, 2, 1181},0, {1008, -16},{0xFF, 0x0, 0xA, 0x0}}},
	{{{-827, -120, 1119},0, {1008, 1008},{0x0, 0xFF, 0x2D, 0xFF}}},
	{{{-416, 2, 1315},0, {-16, -16},{0x0, 0xFF, 0x2D, 0x0}}},
	{{{-416, -120, 1315},0, {-16, 1008},{0x0, 0xFF, 0x2D, 0x0}}},
	{{{-827, 2, 1119},0, {1008, -16},{0x0, 0xFF, 0x2D, 0xFF}}},
	{{{1093, -120, 361},0, {1008, 1008},{0x0, 0x1A, 0xFF, 0xFF}}},
	{{{1088, 2, -265},0, {-16, -16},{0x0, 0x1A, 0xFF, 0x0}}},
	{{{1088, -120, -265},0, {-16, 1008},{0x0, 0x1A, 0xFF, 0x0}}},
	{{{1093, 2, 361},0, {1008, -16},{0x0, 0x1A, 0xFF, 0xFF}}},
	{{{280, -120, -1136},0, {1008, 1008},{0xFF, 0x0, 0xA, 0xFF}}},
	{{{-331, 2, -1275},0, {-16, -16},{0xFF, 0x0, 0xA, 0xFF}}},
	{{{-331, -120, -1275},0, {-16, 1008},{0xFF, 0x0, 0xA, 0x0}}},
	{{{280, 2, -1136},0, {1008, -16},{0xFF, 0x0, 0xA, 0x0}}},
};

Gfx TestVAlpha_dl_Walls_mesh_layer_Transparent_tri_0[] = {
	gsSPVertex(TestVAlpha_dl_Walls_mesh_layer_Transparent_vtx_0 + 0, 16, 0),
	gsSP1Triangle(0, 1, 2, 0),
	gsSP1Triangle(0, 3, 1, 0),
	gsSP1Triangle(4, 5, 6, 0),
	gsSP1Triangle(4, 7, 5, 0),
	gsSP1Triangle(8, 9, 10, 0),
	gsSP1Triangle(8, 11, 9, 0),
	gsSP1Triangle(12, 13, 14, 0),
	gsSP1Triangle(12, 15, 13, 0),
	gsSPVertex(TestVAlpha_dl_Walls_mesh_layer_Transparent_vtx_0 + 16, 16, 0),
	gsSP1Triangle(0, 1, 2, 0),
	gsSP1Triangle(0, 3, 1, 0),
	gsSP1Triangle(4, 5, 6, 0),
	gsSP1Triangle(4, 7, 5, 0),
	gsSP1Triangle(8, 9, 10, 0),
	gsSP1Triangle(8, 11, 9, 0),
	gsSP1Triangle(12, 13, 14, 0),
	gsSP1Triangle(12, 15, 13, 0),
	gsSPVertex(TestVAlpha_dl_Walls_mesh_layer_Transparent_vtx_0 + 32, 12, 0),
	gsSP1Triangle(0, 1, 2, 0),
	gsSP1Triangle(0, 3, 1, 0),
	gsSP1Triangle(4, 5, 6, 0),
	gsSP1Triangle(4, 7, 5, 0),
	gsSP1Triangle(8, 9, 10, 0),
	gsSP1Triangle(8, 11, 9, 0),
	gsSPEndDisplayList(),
};

Gfx mat_TestVAlpha_dl_floor_mat_layerOpaque[] = {
	gsDPPipeSync(),
	gsDPSetCombineLERP(0, 0, 0, SHADE, 0, 0, 0, 1, COMBINED, 0, PRIMITIVE, 0, 0, 0, 0, COMBINED),
	gsSPSetGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
	gsSPClearGeometryMode(G_CULL_FRONT | G_TEXTURE_GEN | G_TEXTURE_GEN_LINEAR),
	gsSPSetOtherMode(G_SETOTHERMODE_H, 4, 20, G_AD_NOISE | G_CD_MAGICSQ | G_CK_NONE | G_TC_FILT | G_TF_BILERP | G_TL_TILE | G_TD_CLAMP | G_TP_PERSP | G_CYC_2CYCLE | G_PM_NPRIMITIVE),
	gsSPSetOtherMode(G_SETOTHERMODE_L, 0, 32, G_AC_NONE | G_ZS_PIXEL | G_RM_FOG_SHADE_A | G_RM_AA_ZB_OPA_SURF2),
	gsSPTexture(65535, 65535, 0, 0, 1),
	gsDPSetPrimColor(0, 0, 88, 88, 88, 255),
	gsSPEndDisplayList(),
};

Gfx mat_TestVAlpha_dl_f3d_material_layerTransparent[] = {
	gsDPPipeSync(),
	gsDPSetCombineLERP(0, 0, 0, SHADE, 0, 0, 0, SHADE, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
	gsSPSetGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_SHADING_SMOOTH),
	gsSPClearGeometryMode(G_CULL_FRONT | G_CULL_BACK | G_LIGHTING | G_TEXTURE_GEN | G_TEXTURE_GEN_LINEAR),
	gsSPSetOtherMode(G_SETOTHERMODE_H, 4, 20, G_AD_NOISE | G_CD_MAGICSQ | G_CK_NONE | G_TC_FILT | G_TF_BILERP | G_TL_TILE | G_TD_CLAMP | G_TP_PERSP | G_CYC_2CYCLE | G_PM_NPRIMITIVE),
	gsSPSetOtherMode(G_SETOTHERMODE_L, 0, 32, G_AC_NONE | G_ZS_PIXEL | G_RM_FOG_SHADE_A | G_RM_AA_ZB_XLU_SURF2),
	gsSPTexture(65535, 65535, 0, 0, 1),
	gsSPEndDisplayList(),
};

Gfx TestVAlpha_dl_Floor_mesh_layer_Opaque[] = {
	gsSPDisplayList(mat_TestVAlpha_dl_floor_mat_layerOpaque),
	gsSPDisplayList(TestVAlpha_dl_Floor_mesh_layer_Opaque_tri_0),
	gsSPEndDisplayList(),
};

Gfx TestVAlpha_dl_Walls_mesh_layer_Transparent[] = {
	gsSPDisplayList(mat_TestVAlpha_dl_f3d_material_layerTransparent),
	gsSPDisplayList(TestVAlpha_dl_Walls_mesh_layer_Transparent_tri_0),
	gsSPEndDisplayList(),
};
