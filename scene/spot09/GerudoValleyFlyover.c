#include "ultra64.h"
#include "z64.h"
#include "macros.h"
#include "command_macros_base.h"
#include "z64cutscene_commands.h"

#include "GerudoValleyFlyover.h"

s32 GerudoValleyFlyover[] = {
	CS_BEGIN_CUTSCENE(4, 5000),
	CS_TERMINATOR(86, 200, 201),
	CS_TEXT_LIST(2),
		CS_TEXT_DISPLAY_TEXTBOX(0x0F20, 20, 90, 0x0000, 0x0000, 0x0000),
		CS_TEXT_DISPLAY_TEXTBOX(0x0F21, 110, 180, 0x0000, 0x0000, 0x0000),
	CS_CAM_POS_LIST(0, 331),
		CS_CAM_POS(0, 0, 0, 0x42700000, 729, 30, -4377, 0),
		CS_CAM_POS(0, 0, 0, 0x42700000, 610, -36, -4302, 0),
		CS_CAM_POS(0, 0, 0, 0x42700000, 126, -779, -2499, 0),
		CS_CAM_POS(0, 0, 0, 0x42700000, 161, -1672, -2441, 0),
		CS_CAM_POS(0, 0, 0, 0x42700000, 203, -2082, -2316, 0),
		CS_CAM_POS(0, 0, 0, 0x42700000, 50, -1959, -1643, 0),
		CS_CAM_POS(0, 0, 0, 0x42700000, 59, -1946, 1281, 0),
		CS_CAM_POS(0, 0, 0, 0x42700000, 238, -2969, 2091, 0),
		CS_CAM_POS(0, 0, 0, 0x42700000, 583, -2616, 3391, 0),
		CS_CAM_POS(-1, 0, 0, 0x0, 0, 0, 0, 0),
	CS_CAM_FOCUS_POINT_LIST(0, 360),
		CS_CAM_FOCUS_POINT(0, 0, 50, 0x42700000, 713, 46, -4322, 0),
		CS_CAM_FOCUS_POINT(0, 0, 50, 0x42700000, 597, -45, -4245, 0),
		CS_CAM_FOCUS_POINT(0, 0, 40, 0x42700000, 117, -811, -2450, 0),
		CS_CAM_FOCUS_POINT(0, 0, 10, 0x42700000, 153, -1727, -2420, 0),
		CS_CAM_FOCUS_POINT(0, 0, 10, 0x42700000, 195, -2073, -2258, 0),
		CS_CAM_FOCUS_POINT(0, 0, 40, 0x42700000, 42, -1928, -1593, 0),
		CS_CAM_FOCUS_POINT(0, 0, 60, 0x42700000, 50, -1974, 1332, 0),
		CS_CAM_FOCUS_POINT(0, 0, 40, 0x42700000, 253, -2994, 2142, 0),
		CS_CAM_FOCUS_POINT(0, 0, 30, 0x42700000, 611, -2657, 3424, 0),
		CS_CAM_FOCUS_POINT(-1, 0, 0, 0x0, 0, 0, 0, 0),
	CS_END(),
};

