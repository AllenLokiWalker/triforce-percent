// "include/z64.h"

AdpcmBook botw_step_grassstraw_r1Book = {
	.order       = 2,
	.npredictors = 4,
	.book        = {
		   -26,    10,    -4,     1,     0,     0,     0,     0,
		  -798,   285,  -101,    36,   -13,     4,    -2,     1,
		   345,    63,    70,    23,    16,     7,     4,     2,
		   372,   413,   138,    95,    40,    23,    11,     6,
		  -365,     2,    65,    -1,   -12,     0,     2,     0,
		    -9,  -365,     3,    65,    -1,   -12,     0,     2,
		   690,   354,   414,   332,   310,   271,   244,   217,
		  1053,  1231,   987,   922,   806,   725,   644,   575,
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
