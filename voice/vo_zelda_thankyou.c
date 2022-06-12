// "include/z64.h"

AdpcmBook vo_zelda_thankyouBook = {
	.order       = 2,
	.npredictors = 4,
	.book        = {
		 -1292,  1819, -1746,  1312,  -745,   222,   157,  -361,
		 -2884,  2769, -2080,  1182,  -353,  -249,   573,  -650,
		  -291,  -210,  -110,   -49,   -20,    -7,    -3,    -1,
		  1476,   774,   348,   141,    52,    18,     5,     1,
		  -760,  -113,   265,    81,   -86,   -43,    26,    20,
		   304,  -715,  -219,   232,   116,   -69,   -53,    18,
		 -1011, -1461, -1612, -1610, -1531, -1418, -1295, -1171,
		  2960,  3268,  3262,  3102,  2874,  2623,  2373,  2136,
	},
};

AdpcmLoop vo_zelda_thankyouLoop = {
	.start  = 0,
	.end    = 123904,
	.count  = 0,
	.unk_0C = {
		0x0, 0x0, 0x0, 0x0
	},
};

SoundFontSample vo_zelda_thankyouSample = {
	.codec     = 0,
	.medium    = 0,
	.unk_bit26 = 0,
	.unk_bit25 = 0,
	.size      = 69696,
	.loop      = &vo_zelda_thankyouLoop,
	.book      = &vo_zelda_thankyouBook,
};

SoundFontSound vo_zelda_thankyouSound = {
	.sample = &vo_zelda_thankyouSample,
	.tuning = 1.000000f
};
