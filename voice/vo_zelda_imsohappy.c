// "include/z64.h"

AdpcmBook vo_zelda_imsohappyBook = {
	.order       = 2,
	.npredictors = 4,
	.book        = {
		  -902,   296,   300,  -229,   -57,   119,   -14,   -48,
		  -673,  -681,   520,   129,  -271,    32,   109,   -50,
		  -642,  -615,  -387,  -177,   -48,     9,    24,    20,
		  1960,  1233,   565,   154,   -30,   -77,   -64,   -37,
		 -1417,  -511,   796,   640,  -319,  -558,    20,   393,
		   739, -1150,  -926,   462,   807,   -28,  -568,  -185,
		  -723,  -932,  -945,  -889,  -811,  -731,  -656,  -586,
		  2639,  2676,  2516,  2297,  2071,  1857,  1661,  1484,
	},
};

AdpcmLoop vo_zelda_imsohappyLoop = {
	.start  = 0,
	.end    = 61440,
	.count  = 0,
	.unk_0C = {
		0x0, 0x0, 0x0, 0x0
	},
};

SoundFontSample vo_zelda_imsohappySample = {
	.codec     = 0,
	.medium    = 0,
	.unk_bit26 = 0,
	.unk_bit25 = 0,
	.size      = 34560,
	.loop      = &vo_zelda_imsohappyLoop,
	.book      = &vo_zelda_imsohappyBook,
};

SoundFontSound vo_zelda_imsohappySound = {
	.sample = &vo_zelda_imsohappySample,
	.tuning = 1.000000f
};
