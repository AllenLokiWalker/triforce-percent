// "include/z64.h"

AdpcmBook botw_step_stone_r0Book = {
	.order       = 2,
	.npredictors = 4,
	.book        = {
		  -187,   -77,   -14,     1,     2,     1,     0,     0,
		   840,   157,   -12,   -19,    -7,    -1,     0,     0,
		  -824,  -920,  -696,  -407,  -174,   -31,    36,    52,
		  2287,  1729,  1011,   433,    77,   -88,  -130,  -109,
		  -220,  -162,   -97,   -54,   -30,   -16,    -9,    -5,
		  1514,   900,   503,   275,   150,    81,    44,    24,
		    39,    35,    33,    30,    28,    26,    24,    23,
		  1862,  1732,  1610,  1497,  1391,  1293,  1202,  1118,
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
