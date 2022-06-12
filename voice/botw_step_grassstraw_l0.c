// "include/z64.h"

AdpcmBook botw_step_grassstraw_l0Book = {
	.order       = 2,
	.npredictors = 4,
	.book        = {
		    45,   -17,     7,    -3,     1,    -1,     0,     0,
		  -750,   320,  -134,    56,   -23,    10,    -4,     2,
		   260,    69,    51,    22,    13,     6,     3,     2,
		   544,   405,   177,    99,    49,    25,    13,     7,
		  -259,   -11,    32,     3,    -4,    -1,     0,     0,
		    90,  -255,   -23,    31,     4,    -4,    -1,     0,
		   685,   326,   385,   292,   268,   225,   197,   169,
		   975,  1150,   874,   801,   674,   589,   506,   438,
	},
};

AdpcmLoop botw_step_grassstraw_l0Loop = {
	.start  = 0,
	.end    = 10308,
	.count  = 0,
	.unk_0C = {
		0x0, 0x0, 0x0, 0x0
	},
};

SoundFontSample botw_step_grassstraw_l0Sample = {
	.codec     = 0,
	.medium    = 0,
	.unk_bit26 = 0,
	.unk_bit25 = 0,
	.size      = 5806,
	.loop      = &botw_step_grassstraw_l0Loop,
	.book      = &botw_step_grassstraw_l0Book,
};

SoundFontSound botw_step_grassstraw_l0Sound = {
	.sample = &botw_step_grassstraw_l0Sample,
	.tuning = 1.000000f
};
