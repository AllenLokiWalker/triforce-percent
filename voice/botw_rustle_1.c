// "include/z64.h"

AdpcmBook botw_rustle_1Book = {
	.order       = 2,
	.npredictors = 4,
	.book        = {
		  -230,   -95,   -13,     5,     4,     1,     0,     0,
		   845,   118,   -46,   -32,    -8,     0,     1,     0,
		 -1126, -1421, -1173,  -699,  -236,    86,   238,   254,
		  2584,  2133,  1270,   430,  -156,  -434,  -461,  -343,
		  -189,  -154,  -109,   -75,   -51,   -35,   -24,   -16,
		  1675,  1182,   813,   556,   380,   260,   178,   121,
		  -698,  -884,  -882,  -816,  -733,  -650,  -574,  -506,
		  2594,  2588,  2395,  2152,  1909,  1686,  1485,  1306,
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
