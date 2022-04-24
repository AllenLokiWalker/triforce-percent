// "include/z64.h"

AdpcmBook vo_link_isshoniBook = {
	.order       = 2,
	.npredictors = 4,
	.book        = {
		 -1374,   327,   844,  -420,  -467,   393,   220,  -316,
		  -487, -1258,   626,   695,  -586,  -327,   471,   108,
		   257,   186,   167,   145,   126,   109,    95,    83,
		  1485,  1333,  1153,  1003,   872,   758,   659,   573,
		 -1237,  -956,     9,   585,   446,    -8,  -276,  -208,
		  1582,   -15,  -968,  -739,    14,   457,   345,   -10,
		 -1233, -1925, -2262, -2372, -2340, -2225, -2064, -1882,
		  3197,  3757,  3939,  3887,  3696,  3428,  3126,  2815,
	},
};

AdpcmLoop vo_link_isshoniLoop = {
	.start  = 0,
	.end    = 67806,
	.count  = 0,
	.unk_0C = {
		0x0, 0x0, 0x0, 0x0
	},
};

SoundFontSample vo_link_isshoniSample = {
	.codec     = 0,
	.medium    = 0,
	.unk_bit26 = 0,
	.unk_bit25 = 0,
	.size      = 38142,
	.loop      = &vo_link_isshoniLoop,
	.book      = &vo_link_isshoniBook,
};

SoundFontSound vo_link_isshoniSound = {
	.sample = &vo_link_isshoniSample,
	.tuning = 1.000000f
};
