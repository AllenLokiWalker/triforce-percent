// "include/z64.h"

AdpcmBook botw_step_stone_l1Book = {
	.order       = 2,
	.npredictors = 4,
	.book        = {
		  -132,   -63,   -22,    -6,    -2,     0,     0,     0,
		   981,   338,    99,    25,     6,     1,     0,     0,
		  -659,  -791,  -738,  -631,  -520,  -422,  -339,  -271,
		  2459,  2293,  1962,  1618,  1311,  1053,   843,   673,
		   170,   128,   110,    93,    79,    67,    57,    48,
		  1537,  1323,  1121,   951,   807,   684,   580,   492,
		 -1502, -2547, -3218, -3589, -3727, -3688, -3521, -3266,
		  3473,  4388,  4894,  5082,  5029,  4801,  4454,  4032,
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
