// "include/z64.h"

AdpcmBook botw_step_grassstraw_r1Book = {
	.order       = 2,
	.npredictors = 4,
	.book        = {
		   -25,    10,    -3,     1,     0,     0,     0,     0,
		  -794,   282,  -100,    35,   -12,     4,    -2,     1,
		   344,    62,    69,    23,    16,     7,     4,     2,
		   370,   411,   136,    94,    40,    23,    11,     6,
		  -369,     1,    66,    -1,   -12,     0,     2,     0,
		    -8,  -369,     3,    66,    -1,   -12,     0,     2,
		   690,   355,   415,   333,   311,   272,   244,   217,
		  1052,  1231,   987,   922,   806,   725,   644,   575,
	},
};

AdpcmLoop botw_step_grassstraw_r1Loop = {
	.start  = 0,
	.end    = 9053,
	.count  = 0,
	.unk_0C = {
		0x0, 0x0, 0x0, 0x0
	},
};

SoundFontSample botw_step_grassstraw_r1Sample = {
	.codec     = 0,
	.medium    = 0,
	.unk_bit26 = 0,
	.unk_bit25 = 0,
	.size      = 5094,
	.loop      = &botw_step_grassstraw_r1Loop,
	.book      = &botw_step_grassstraw_r1Book,
};

SoundFontSound botw_step_grassstraw_r1Sound = {
	.sample = &botw_step_grassstraw_r1Sample,
	.tuning = 1.000000f
};
