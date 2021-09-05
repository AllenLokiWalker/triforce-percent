#include "ultra64.h"
#include "z64.h"
#include "macros.h"
#include "EndingDemo_room_0.h"

#include "segment_symbols.h"
#include "command_macros_base.h"
#include "z64cutscene_commands.h"
#include "variables.h"
#include "EndingDemo_scene.h"

SCmdBase EndingDemo_room_0_header00[] = {
	SCENE_CMD_ECHO_SETTINGS(0x00),
	SCENE_CMD_ROOM_BEHAVIOR(0x00, 0x00, false, false),
	SCENE_CMD_SKYBOX_DISABLES(false, false),
	SCENE_CMD_TIME_SETTINGS(0xFF, 0xFF, 10),
	SCENE_CMD_MESH(&EndingDemo_room_0_meshHeader),
	SCENE_CMD_END(),
};

MeshHeader0 EndingDemo_room_0_meshHeader = { {0}, 1, (u32)&EndingDemo_room_0_meshDListEntry, (u32)&(EndingDemo_room_0_meshDListEntry) + sizeof(EndingDemo_room_0_meshDListEntry) };

MeshEntry0 EndingDemo_room_0_meshDListEntry[1] = {
	{ (u32)EndingDemo_room_0_entry_0_opaque, (u32)0 },
};

Gfx EndingDemo_room_0_entry_0_opaque[] = {
	gsSPDisplayList(EndingDemo_dl_Floor_mesh_layer_Opaque),
	gsSPEndDisplayList(),
};

Vtx EndingDemo_dl_Floor_mesh_layer_Opaque_vtx_0[4] = {
	{{{-32, 0, 32},0, {-16, 1008},{0x0, 0x7F, 0x0, 0xFF}}},
	{{{32, 0, 32},0, {1008, 1008},{0x0, 0x7F, 0x0, 0xFF}}},
	{{{32, 0, -32},0, {1008, -16},{0x0, 0x7F, 0x0, 0xFF}}},
	{{{-32, 0, -32},0, {-16, -16},{0x0, 0x7F, 0x0, 0xFF}}},
};

Gfx EndingDemo_dl_Floor_mesh_layer_Opaque_tri_0[] = {
	gsSPVertex(EndingDemo_dl_Floor_mesh_layer_Opaque_vtx_0 + 0, 4, 0),
	gsSP1Triangle(0, 1, 2, 0),
	gsSP1Triangle(0, 2, 3, 0),
	gsSPEndDisplayList(),
};

Gfx mat_EndingDemo_dl_f3d_material_layerOpaque[] = {
	gsDPPipeSync(),
	gsDPSetCombineLERP(0, 0, 0, SHADE, 0, 0, 0, 1, COMBINED, 0, PRIMITIVE, 0, 0, 0, 0, COMBINED),
	gsSPSetGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
	gsSPClearGeometryMode(G_CULL_FRONT | G_TEXTURE_GEN | G_TEXTURE_GEN_LINEAR),
	gsSPSetOtherMode(G_SETOTHERMODE_H, 4, 20, G_AD_NOISE | G_CD_MAGICSQ | G_CK_NONE | G_TC_FILT | G_TF_BILERP | G_TL_TILE | G_TD_CLAMP | G_TP_PERSP | G_CYC_2CYCLE | G_PM_NPRIMITIVE),
	gsSPSetOtherMode(G_SETOTHERMODE_L, 0, 32, G_AC_NONE | G_ZS_PIXEL | G_RM_FOG_SHADE_A | G_RM_AA_ZB_OPA_SURF2),
	gsSPTexture(65535, 65535, 0, 0, 1),
	gsDPSetPrimColor(0, 0, 96, 187, 254, 255),
	gsSPEndDisplayList(),
};

Gfx EndingDemo_dl_Floor_mesh_layer_Opaque[] = {
	gsSPDisplayList(mat_EndingDemo_dl_f3d_material_layerOpaque),
	gsSPDisplayList(EndingDemo_dl_Floor_mesh_layer_Opaque_tri_0),
	gsSPEndDisplayList(),
};

