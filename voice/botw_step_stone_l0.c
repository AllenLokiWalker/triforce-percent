// "include/z64.h"

AdpcmBook botw_step_stone_l0Book = {
	.order       = 2,
	.npredictors = 4,
	.book        = {
		   327,    97,    81,    39,    24,    14,     8,     4,
		   605,   506,   246,   153,    85,    49,    28,    16,
		  -486,  -513,  -426,  -328,  -245,  -181,  -133,   -97,
		  2162,  1795,  1382,  1032,   761,   559,   409,   299,
		   479,   312,   316,   279,   256,   232,   211,   192,
		  1336,  1350,  1193,  1094,   993,   903,   821,   747,
		 -1062, -1575, -1783, -1825, -1780, -1692, -1584, -1470,
		  3035,  3436,  3518,  3432,  3261,  3053,  2833,  2615,
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
