// "include/z64.h"

AdpcmBook vo_zelda_youaskedBook = {
	.order       = 2,
	.npredictors = 4,
	.book        = {
		  -941,   -23,   432,    21,  -198,   -14,    91,     9,
		    50,  -940,   -46,   431,    31,  -197,   -19,    90,
		  -651,  -676,  -496,  -301,  -155,   -66,   -19,     1,
		  2128,  1562,   947,   488,   206,    59,    -4,   -23,
		 -1148,  -784,   108,   513,   290,   -89,  -224,  -103,
		  1399,  -192,  -915,  -518,   159,   399,   183,   -98,
		 -1179, -1811, -2104, -2191, -2155, -2051, -1911, -1756,
		  3147,  3656,  3807,  3746,  3564,  3321,  3052,  2778,
	},
};

AdpcmLoop vo_zelda_youaskedLoop = {
	.start  = 0,
	.end    = 53248,
	.count  = 0,
	.unk_0C = {
		0x0, 0x0, 0x0, 0x0
	},
};

SoundFontSample vo_zelda_youaskedSample = {
	.codec     = 0,
	.medium    = 0,
	.unk_bit26 = 0,
	.unk_bit25 = 0,
	.size      = 29952,
	.loop      = &vo_zelda_youaskedLoop,
	.book      = &vo_zelda_youaskedBook,
};

SoundFontSound vo_zelda_youaskedSound = {
	.sample = &vo_zelda_youaskedSample,
	.tuning = 1.000000f
};
