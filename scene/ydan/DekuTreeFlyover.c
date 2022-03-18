#include "ultra64.h"
#include "z64.h"
#include "macros.h"
#include "command_macros_base.h"
#include "z64cutscene_commands.h"

#include "DekuTreeFlyover.h"

s32 DekuTreeFlyover[] = {
	CS_BEGIN_CUTSCENE(4, 5000),
	CS_TERMINATOR(87, 140, 141),
	CS_TEXT_LIST(2),
		CS_TEXT_DISPLAY_TEXTBOX(0x0F30, 10, 70, 0x0000, 0x0000, 0x0000),
		CS_TEXT_DISPLAY_TEXTBOX(0x0F31, 95, 140, 0x0000, 0x0000, 0x0000),
	CS_CAM_POS_LIST(0, 261),
		CS_CAM_POS(0, 0, 0, 0x42700000, 0, 883, 8, 0),
		CS_CAM_POS(0, 0, 0, 0x42c80000, 3, 881, 8, 0),
		CS_CAM_POS(0, 0, 0, 0x42c80000, 5, 835, 8, 0),
		CS_CAM_POS(0, 0, 0, 0x42c80000, 2, 782, 14, 0),
		CS_CAM_POS(0, 0, 0, 0x42c80000, 1, 731, 9, 0),
		CS_CAM_POS(0, 0, 0, 0x42c80000, 7, 679, 7, 0),
		CS_CAM_POS(0, 0, 0, 0x42700000, 7, 674, 6, 0),
		CS_CAM_POS(-1, 0, 0, 0x0, 0, 0, 0, 0),
	CS_CAM_FOCUS_POINT_LIST(0, 300),
		CS_CAM_FOCUS_POINT(0, 0, 20, 0x42700000, 0, 883, -48, 0),
		CS_CAM_FOCUS_POINT(0, 0, 40, 0x42c80000, 3, 881, -48, 0),
		CS_CAM_FOCUS_POINT(0, 0, 40, 0x42c80000, 61, 835, 7, 0),
		CS_CAM_FOCUS_POINT(0, 0, 40, 0x42c80000, 6, 782, 69, 0),
		CS_CAM_FOCUS_POINT(0, 0, 40, 0x42c80000, -55, 731, 9, 0),
		CS_CAM_FOCUS_POINT(0, 0, 40, 0x42c80000, 6, 679, -49, 0),
		CS_CAM_FOCUS_POINT(0, 0, 40, 0x42700000, 6, 674, -50, 0),
		CS_CAM_FOCUS_POINT(-1, 0, 0, 0x0, 0, 0, 0, 0),
	CS_END(),
};

