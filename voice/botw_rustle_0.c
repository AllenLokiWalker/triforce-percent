// "include/z64.h"

AdpcmBook botw_rustle_0Book = {
	.order       = 2,
	.npredictors = 4,
	.book        = {
		  -509,  -321,   -75,    32,    39,    17,     1,    -4,
		  1290,   303,  -130,  -157,   -67,    -3,    15,    10,
		 -1032, -1334, -1203,  -883,  -534,  -245,   -48,    62,
		  2646,  2387,  1751,  1059,   486,    94,  -123,  -207,
		  -311,  -279,  -203,  -140,   -95,   -64,   -43,   -29,
		  1839,  1341,   926,   628,   424,   285,   192,   129,
		  -504,  -597,  -582,  -542,  -498,  -456,  -417,  -381,
		  2424,  2364,  2201,  2022,  1851,  1693,  1547,  1414,
	},
};

AdpcmLoop botw_rustle_0Loop = {
	.start  = 0,
	.end    = 8160,
	.count  = 0,
	.unk_0C = {
		0x0, 0x0, 0x0, 0x0
	},
};

SoundFontSample botw_rustle_0Sample = {
	.codec     = 0,
	.medium    = 0,
	.unk_bit26 = 0,
	.unk_bit25 = 0,
	.size      = 4590,
	.loop      = &botw_rustle_0Loop,
	.book      = &botw_rustle_0Book,
};

SoundFontSound botw_rustle_0Sound = {
	.sample = &botw_rustle_0Sample,
	.tuning = 1.000000f
};
