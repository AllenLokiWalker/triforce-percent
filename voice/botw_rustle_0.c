// "include/z64.h"

AdpcmBook botw_rustle_0Book = {
	.order       = 2,
	.npredictors = 4,
	.book        = {
		  -508,  -320,   -75,    32,    39,    16,     1,    -4,
		  1288,   302,  -130,  -157,   -66,    -3,    15,    10,
		 -1034, -1336, -1205,  -883,  -533,  -243,   -45,    65,
		  2647,  2387,  1749,  1055,   481,    89,  -128,  -210,
		  -311,  -280,  -204,  -141,   -95,   -64,   -43,   -29,
		  1840,  1342,   926,   628,   424,   285,   192,   129,
		  -506,  -598,  -584,  -543,  -499,  -456,  -417,  -381,
		  2424,  2364,  2200,  2020,  1848,  1689,  1543,  1410,
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
