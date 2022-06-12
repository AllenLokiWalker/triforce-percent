// "include/z64.h"

AdpcmBook botw_step_stone_l1Book = {
	.order       = 2,
	.npredictors = 4,
	.book        = {
		  -138,   -66,   -23,    -6,    -2,     0,     0,     0,
		   984,   335,    95,    23,     5,     1,     0,     0,
		  -664,  -798,  -743,  -634,  -521,  -420,  -336,  -267,
		  2461,  2292,  1956,  1607,  1296,  1036,   825,   655,
		   172,   129,   111,    95,    81,    68,    58,    50,
		  1540,  1330,  1129,   960,   817,   695,   591,   502,
		 -1502, -2548, -3219, -3590, -3727, -3688, -3520, -3264,
		  3473,  4388,  4894,  5081,  5027,  4798,  4450,  4027,
	},
};

AdpcmLoop botw_step_stone_l1Loop = {
	.start  = 0,
	.end    = 6491,
	.count  = 0,
	.unk_0C = {
		0x0, 0x0, 0x0, 0x0
	},
};

SoundFontSample botw_step_stone_l1Sample = {
	.codec     = 0,
	.medium    = 0,
	.unk_bit26 = 0,
	.unk_bit25 = 0,
	.size      = 3654,
	.loop      = &botw_step_stone_l1Loop,
	.book      = &botw_step_stone_l1Book,
};

SoundFontSound botw_step_stone_l1Sound = {
	.sample = &botw_step_stone_l1Sample,
	.tuning = 1.000000f
};
