// "include/z64.h"

AdpcmBook botw_rustle_1Book = {
	.order       = 2,
	.npredictors = 4,
	.book        = {
		  -231,   -95,   -13,     5,     4,     1,     0,     0,
		   845,   118,   -47,   -33,    -8,     0,     1,     0,
		 -1121, -1414, -1170,  -703,  -246,    74,   228,   247,
		  2584,  2139,  1284,   450,  -135,  -417,  -452,  -342,
		  -189,  -155,  -109,   -75,   -51,   -35,   -24,   -16,
		  1676,  1182,   813,   556,   380,   259,   177,   121,
		  -696,  -883,  -882,  -818,  -736,  -655,  -580,  -512,
		  2596,  2593,  2404,  2165,  1926,  1705,  1506,  1329,
	},
};

AdpcmLoop botw_rustle_1Loop = {
	.start  = 0,
	.end    = 7688,
	.count  = 0,
	.unk_0C = {
		0x0, 0x0, 0x0, 0x0
	},
};

SoundFontSample botw_rustle_1Sample = {
	.codec     = 0,
	.medium    = 0,
	.unk_bit26 = 0,
	.unk_bit25 = 0,
	.size      = 4330,
	.loop      = &botw_rustle_1Loop,
	.book      = &botw_rustle_1Book,
};

SoundFontSound botw_rustle_1Sound = {
	.sample = &botw_rustle_1Sample,
	.tuning = 1.000000f
};
