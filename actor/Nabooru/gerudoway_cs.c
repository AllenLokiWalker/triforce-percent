#include "ultra64.h"
#include "z64.h"
#include "macros.h"
#include "command_macros_base.h"
#include "z64cutscene_commands.h"

#include "gerudoway_cs.h"

s32 NabooruPanAway[] = {
	CS_BEGIN_CUTSCENE(4, 184),
	CS_TERMINATOR(79, 182, 183),
	CS_TEXT_LIST(1),
		CS_TEXT_DISPLAY_TEXTBOX(0x0B66, 5, 181, 0x0000, 0x0000, 0x0000),
	CS_CAM_POS_LIST(0, 321),
		CS_CAM_POS(0, 0, 0, 0x42700000, 1997, 44, -657, 0),
		CS_CAM_POS(0, 0, 0, 0x42700000, 1997, 44, -657, 0),
		CS_CAM_POS(0, 0, 0, 0x42700000, 2106, 77, -606, 0),
		CS_CAM_POS(0, 0, 0, 0x42700000, 2244, 9, -708, 0),
		CS_CAM_POS(0, 0, 0, 0x42700000, 2201, 20, -701, 0),
		CS_CAM_POS(-1, 0, 0, 0x0, 0, 0, 0, 0),
	CS_CAM_FOCUS_POINT_LIST(0, 340),
		CS_CAM_FOCUS_POINT(0, 0, 20, 0x42700000, 1950, 39, -686, 0),
		CS_CAM_FOCUS_POINT(0, 0, 100, 0x42700000, 1950, 39, -686, 0),
		CS_CAM_FOCUS_POINT(0, 0, 80, 0x42700000, 1950, 39, -686, 0),
		CS_CAM_FOCUS_POINT(0, 0, 100, 0x42700000, 1950, 88, -686, 0),
		CS_CAM_FOCUS_POINT(0, 0, 20, 0x42700000, 1950, 88, -686, 0),
		CS_CAM_FOCUS_POINT(-1, 0, 0, 0x0, 0, 0, 0, 0),
	CS_END(),
};
