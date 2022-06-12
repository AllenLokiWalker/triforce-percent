// "include/z64.h"

AdpcmBook botw_step_stone_r1Book = {
	.order       = 2,
	.npredictors = 4,
	.book        = {
		  -203,  -124,   -55,   -22,    -8,    -3,    -1,     0,
		  1249,   559,   217,    77,    25,     8,     2,     1,
		  -881, -1090,  -970,  -731,  -488,  -289,  -148,   -58,
		  2534,  2255,  1700,  1134,   671,   343,   136,    21,
		  -141,  -121,   -94,   -72,   -55,   -42,   -32,   -25,
		  1754,  1360,  1044,   800,   613,   469,   360,   276,
		  -616,  -784,  -813,  -798,  -771,  -741,  -711,  -682,
		  2606,  2700,  2652,  2562,  2462,  2362,  2265,  2172,
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
