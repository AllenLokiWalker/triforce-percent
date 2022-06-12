// "include/z64.h"

AdpcmBook botw_step_grassstraw_r0Book = {
	.order       = 2,
	.npredictors = 4,
	.book        = {
		    24,    -8,     3,    -1,     0,     0,     0,     0,
		  -703,   265,   -99,    37,   -14,     5,    -2,     1,
		   288,    65,    55,    22,    13,     6,     3,     2,
		   465,   393,   154,    90,    42,    22,    11,     6,
		  -201,     1,    20,     0,    -2,     0,     0,     0,
		    -5,  -201,     1,    20,     0,    -2,     0,     0,
		   366,   225,   204,   166,   138,   115,    95,    79,
		  1260,  1141,   928,   775,   642,   534,   443,   368,
	},
};

AdpcmLoop botw_step_grassstraw_r0Loop = {
	.start  = 0,
	.end    = 10204,
	.count  = 0,
	.unk_0C = {
		0x0, 0x0, 0x0, 0x0
	},
};

SoundFontSample botw_step_grassstraw_r0Sample = {
	.codec     = 0,
	.medium    = 0,
	.unk_bit26 = 0,
	.unk_bit25 = 0,
	.size      = 5742,
	.loop      = &botw_step_grassstraw_r0Loop,
	.book      = &botw_step_grassstraw_r0Book,
};

SoundFontSound botw_step_grassstraw_r0Sound = {
	.sample = &botw_step_grassstraw_r0Sample,
	.tuning = 1.000000f
};
