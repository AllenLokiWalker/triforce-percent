// "include/z64.h"

AdpcmBook botw_rustle_2Book = {
	.order       = 2,
	.npredictors = 4,
	.book        = {
		  -207,   -89,   -18,     1,     2,     1,     0,     0,
		   885,   175,   -14,   -24,    -9,    -1,     0,     0,
		 -1073, -1325, -1072,  -629,  -215,    65,   193,   204,
		  2528,  2046,  1201,   409,  -124,  -368,  -389,  -287,
		   -88,   -68,   -49,   -35,   -25,   -18,   -13,    -9,
		  1591,  1149,   825,   591,   424,   304,   218,   157,
		  -620,  -763,  -752,  -695,  -628,  -562,  -502,  -448,
		  2521,  2484,  2295,  2073,  1857,  1659,  1480,  1320,
	},
};

AdpcmLoop botw_rustle_2Loop = {
	.start  = 0,
	.end    = 8555,
	.count  = 0,
	.unk_0C = {
		0x0, 0x0, 0x0, 0x0
	},
};

SoundFontSample botw_rustle_2Sample = {
	.codec     = 0,
	.medium    = 0,
	.unk_bit26 = 0,
	.unk_bit25 = 0,
	.size      = 4816,
	.loop      = &botw_rustle_2Loop,
	.book      = &botw_rustle_2Book,
};

SoundFontSound botw_rustle_2Sound = {
	.sample = &botw_rustle_2Sample,
	.tuning = 1.000000f
};
