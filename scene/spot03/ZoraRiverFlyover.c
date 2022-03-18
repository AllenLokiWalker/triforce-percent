#include "ultra64.h"
#include "z64.h"
#include "macros.h"
#include "command_macros_base.h"
#include "z64cutscene_commands.h"

#include "ZoraRiverFlyover.h"

s32 ZoraRiverFlyover[] = {
	CS_BEGIN_CUTSCENE(2, 5000),
	CS_TERMINATOR(89, 270, 271),
	CS_TEXT_LIST(2),
		CS_TEXT_DISPLAY_TEXTBOX(0x0F50, 50, 110, 0x0000, 0x0000, 0x0000),
		CS_TEXT_DISPLAY_TEXTBOX(0x0X51, 130, 190, 0x0000, 0x0000, 0x0000),
	CS_END(),
};

