// "include/z64.h"

AdpcmBook botw_step_stone_l0Book = {
	.order       = 2,
	.npredictors = 4,
	.book        = {
		   325,    96,    80,    39,    24,    13,     8,     4,
		   608,   505,   246,   153,    84,    49,    28,    16,
		  -481,  -506,  -419,  -322,  -240,  -177,  -130,   -95,
		  2154,  1784,  1370,  1022,   753,   552,   403,   295,
		   478,   312,   315,   279,   255,   232,   211,   192,
		  1337,  1351,  1194,  1095,   993,   904,   822,   747,
		 -1062, -1573, -1780, -1821, -1774, -1683, -1573, -1458,
		  3034,  3432,  3510,  3420,  3245,  3034,  2811,  2590,
	},
};

AdpcmLoop botw_step_stone_l0Loop = {
	.start  = 0,
	.end    = 6709,
	.count  = 0,
	.unk_0C = {
		0x0, 0x0, 0x0, 0x0
	},
};

SoundFontSample botw_step_stone_l0Sample = {
	.codec     = 0,
	.medium    = 0,
	.unk_bit26 = 0,
	.unk_bit25 = 0,
	.size      = 3780,
	.loop      = &botw_step_stone_l0Loop,
	.book      = &botw_step_stone_l0Book,
};

SoundFontSound botw_step_stone_l0Sound = {
	.sample = &botw_step_stone_l0Sample,
	.tuning = 1.000000f
};
