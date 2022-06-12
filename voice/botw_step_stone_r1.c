// "include/z64.h"

AdpcmBook botw_step_stone_r1Book = {
	.order       = 2,
	.npredictors = 4,
	.book        = {
		  -205,  -125,   -56,   -22,    -8,    -3,    -1,     0,
		  1253,   562,   218,    78,    26,     8,     2,     1,
		  -882, -1093,  -974,  -736,  -492,  -293,  -151,   -61,
		  2537,  2261,  1709,  1143,   680,   350,   141,    24,
		  -149,  -128,   -99,   -76,   -58,   -44,   -34,   -26,
		  1760,  1363,  1044,   798,   609,   466,   356,   272,
		  -615,  -782,  -810,  -796,  -769,  -739,  -709,  -680,
		  2605,  2698,  2650,  2560,  2461,  2361,  2264,  2171,
	},
};

AdpcmLoop botw_step_stone_r1Loop = {
	.start  = 0,
	.end    = 8059,
	.count  = 0,
	.unk_0C = {
		0x0, 0x0, 0x0, 0x0
	},
};

SoundFontSample botw_step_stone_r1Sample = {
	.codec     = 0,
	.medium    = 0,
	.unk_bit26 = 0,
	.unk_bit25 = 0,
	.size      = 4536,
	.loop      = &botw_step_stone_r1Loop,
	.book      = &botw_step_stone_r1Book,
};

SoundFontSound botw_step_stone_r1Sound = {
	.sample = &botw_step_stone_r1Sample,
	.tuning = 1.000000f
};
