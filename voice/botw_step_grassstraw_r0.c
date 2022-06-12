// "include/z64.h"

AdpcmBook botw_step_grassstraw_r0Book = {
	.order       = 2,
	.npredictors = 4,
	.book        = {
		    23,    -8,     3,    -1,     0,     0,     0,     0,
		  -704,   265,   -99,    37,   -14,     5,    -2,     1,
		   293,    65,    57,    22,    13,     6,     3,     2,
		   458,   395,   154,    91,    42,    22,    11,     6,
		  -208,     0,    21,     0,    -2,     0,     0,     0,
		    -4,  -208,     1,    21,     0,    -2,     0,     0,
		   364,   225,   203,   165,   138,   115,    95,    79,
		  1263,  1143,   929,   776,   644,   535,   444,   369,
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
