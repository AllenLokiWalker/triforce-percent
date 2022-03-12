#include "ultra64.h"
#include "z64.h"
#include "macros.h"
#include "command_macros_base.h"
#include "z64cutscene_commands.h"

s32 spot04cspatch[] = {
	CS_TERMINATOR(80, 530, 540),
	CS_TEXT_LIST(2),
		CS_TEXT_DISPLAY_TEXTBOX(0x0B67, 20, 1000, 0x0000, 0x0000, 0x0000),
		CS_TEXT_DISPLAY_TEXTBOX(0x0B67, 20, 1000, 0x0000, 0x0000, 0x0000),
	CS_END(),
};
