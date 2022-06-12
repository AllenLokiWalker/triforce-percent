// "include/z64.h"

AdpcmBook botw_step_grassstraw_l1Book = {
	.order       = 2,
	.npredictors = 4,
	.book        = {
		   -80,    25,    -5,     0,     0,     0,     0,     0,
		  -637,   119,   -12,    -1,     1,     0,     0,     0,
		   408,    84,    98,    37,    27,    13,     8,     4,
		   420,   494,   185,   136,    65,    40,    21,    12,
		  -362,   -26,    62,     9,   -10,    -2,     2,     1,
		   146,  -351,   -51,    58,    13,    -9,    -3,     1,
		   632,   321,   358,   281,   254,   216,   188,   162,
		  1041,  1162,   912,   822,   700,   609,   526,   455,
	},
};

AdpcmLoop botw_step_grassstraw_l1Loop = {
	.start  = 0,
	.end    = 10465,
	.count  = 0,
	.unk_0C = {
		0x0, 0x0, 0x0, 0x0
	},
};

SoundFontSample botw_step_grassstraw_l1Sample = {
	.codec     = 0,
	.medium    = 0,
	.unk_bit26 = 0,
	.unk_bit25 = 0,
	.size      = 5896,
	.loop      = &botw_step_grassstraw_l1Loop,
	.book      = &botw_step_grassstraw_l1Book,
};

SoundFontSound botw_step_grassstraw_l1Sound = {
	.sample = &botw_step_grassstraw_l1Sample,
	.tuning = 1.000000f
};
