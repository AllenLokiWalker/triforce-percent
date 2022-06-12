// "include/z64.h"

AdpcmBook botw_step_stone_r0Book = {
	.order       = 2,
	.npredictors = 4,
	.book        = {
		  -182,   -75,   -15,     1,     2,     1,     0,     0,
		   845,   167,    -6,   -17,    -7,    -1,     0,     0,
		  -827,  -924,  -699,  -409,  -175,   -30,    37,    53,
		  2289,  1733,  1013,   433,    75,   -91,  -132,  -111,
		  -228,  -170,  -101,   -56,   -30,   -16,    -9,    -5,
		  1522,   902,   501,   271,   146,    78,    42,    22,
		    45,    41,    38,    35,    33,    31,    28,    26,
		  1855,  1725,  1603,  1490,  1385,  1287,  1196,  1111,
	},
};

AdpcmLoop botw_step_stone_r0Loop = {
	.start  = 0,
	.end    = 11459,
	.count  = 0,
	.unk_0C = {
		0x0, 0x0, 0x0, 0x0
	},
};

SoundFontSample botw_step_stone_r0Sample = {
	.codec     = 0,
	.medium    = 0,
	.unk_bit26 = 0,
	.unk_bit25 = 0,
	.size      = 6454,
	.loop      = &botw_step_stone_r0Loop,
	.book      = &botw_step_stone_r0Book,
};

SoundFontSound botw_step_stone_r0Sound = {
	.sample = &botw_step_stone_r0Sample,
	.tuning = 1.000000f
};
