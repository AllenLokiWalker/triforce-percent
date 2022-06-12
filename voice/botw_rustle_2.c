// "include/z64.h"

AdpcmBook botw_rustle_2Book = {
	.order       = 2,
	.npredictors = 4,
	.book        = {
		  -207,   -89,   -18,     1,     2,     1,     0,     0,
		   884,   175,   -14,   -24,    -9,    -1,     0,     0,
		 -1074, -1327, -1076,  -634,  -219,    62,   191,   204,
		  2530,  2052,  1209,   417,  -118,  -365,  -389,  -289,
		   -88,   -68,   -49,   -35,   -25,   -18,   -13,    -9,
		  1592,  1149,   825,   592,   425,   305,   219,   157,
		  -614,  -754,  -743,  -686,  -620,  -556,  -497,  -444,
		  2516,  2477,  2288,  2069,  1855,  1659,  1482,  1323,
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
