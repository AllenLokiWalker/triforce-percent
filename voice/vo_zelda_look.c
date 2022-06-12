// "include/z64.h"

AdpcmBook vo_zelda_lookBook = {
	.order       = 2,
	.npredictors = 4,
	.book        = {
		  -918,  1129,  -976,   693,  -415,   199,   -59,   -17,
		 -2517,  2176, -1546,   925,  -444,   131,    38,  -106,
		  -956, -1083,  -782,  -380,   -66,   103,   147,   119,
		  2321,  1674,   814,   141,  -220,  -315,  -255,  -141,
		  -215,  -132,   -59,   -23,    -8,    -2,    -1,     0,
		  1264,   565,   216,    74,    23,     7,     2,     0,
		 -1230, -1894, -2176, -2211, -2096, -1898, -1662, -1418,
		  3152,  3621,  3680,  3489,  3159,  2766,  2360,  1970,
	},
};

AdpcmLoop vo_zelda_lookLoop = {
	.start  = 0,
	.end    = 30720,
	.count  = 0,
	.unk_0C = {
		0x0, 0x0, 0x0, 0x0
	},
};

SoundFontSample vo_zelda_lookSample = {
	.codec     = 0,
	.medium    = 0,
	.unk_bit26 = 0,
	.unk_bit25 = 0,
	.size      = 17280,
	.loop      = &vo_zelda_lookLoop,
	.book      = &vo_zelda_lookBook,
};

SoundFontSound vo_zelda_lookSound = {
	.sample = &vo_zelda_lookSample,
	.tuning = 1.000000f
};
