#include "ultra64.h"
#include "z64.h"
#include "macros.h"
#include "command_macros_base.h"
#include "z64cutscene_commands.h"

#include "HauntedWastelandFlyover.h"

s32 HauntedWastelandFlyover[] = {
	CS_BEGIN_CUTSCENE(4, 5000),
	CS_TERMINATOR(92, 240, 241),
	CS_TEXT_LIST(2),
		CS_TEXT_DISPLAY_TEXTBOX(0x0F80, 60, 130, 0x0000, 0x0000, 0x0000),
		CS_TEXT_DISPLAY_TEXTBOX(0x0F81, 150, 220, 0x0000, 0x0000, 0x0000),
	CS_CAM_POS_LIST(0, 621),
		CS_CAM_POS(0, 0, 0, 0x42700000, -925, 294, -2156, 0),
		CS_CAM_POS(0, 0, 0, 0x42700000, -858, 294, -2156, 0),
		CS_CAM_POS(0, 0, 0, 0x42700000, 4672, 275, -2186, 0),
		CS_CAM_POS(0, 0, 0, 0x42700000, 4739, 275, -2186, 0),
		CS_CAM_POS(-1, 0, 0, 0x0, 0, 0, 0, 0),
	CS_CAM_FOCUS_POINT_LIST(0, 640),
		CS_CAM_FOCUS_POINT(0, 0, 40, 0x42700000, -869, 294, -2156, 0),
		CS_CAM_FOCUS_POINT(0, 0, 280, 0x42700000, -802, 294, -2156, 0),
		CS_CAM_FOCUS_POINT(0, 0, 280, 0x42700000, 4728, 275, -2186, 0),
		CS_CAM_FOCUS_POINT(0, 0, 20, 0x42700000, 4795, 275, -2186, 0),
		CS_CAM_FOCUS_POINT(-1, 0, 0, 0x0, 0, 0, 0, 0),
	CS_END(),
};

