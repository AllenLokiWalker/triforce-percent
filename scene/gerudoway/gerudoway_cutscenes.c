#include "ultra64.h"
#include "z64.h"
#include "macros.h"
#include "command_macros_base.h"
#include "z64cutscene_commands.h"

#include "gerudoway_cutscenes.h"

s32 Something[] = {
	CS_BEGIN_CUTSCENE(3, 100),
	CS_TERMINATOR(1, 2, 3),
	CS_TEXT_LIST(1),
		CS_TEXT_NONE(1, 4),
	CS_FADE_BGM_LIST(1),
		CS_FADE_BGM(12345, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0),
	CS_END(),
};

s32 SomethingElse[] = {
	CS_BEGIN_CUTSCENE(5, 3),
	CS_TERMINATOR(1, 4, 2),
	CS_TEXT_LIST(3),
		CS_TEXT_LEARN_SONG(0x0000, 0, 1, 0x0000),
		CS_TEXT_DISPLAY_TEXTBOX(0x0000, 0, 1, 0x0000, 0x0000, 0x0000),
		CS_TEXT_NONE(0, 1),
	CS_LIGHTING_LIST(0),
	CS_SCENE_TRANS_FX(3, 2, 3),
	CS_CMD_09_LIST(1),
		CS_CMD_09(0, 0, 1, 0x00, 0x00, 0x00, 0, 0),
	CS_END(),
};

