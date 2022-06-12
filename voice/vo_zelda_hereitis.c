// "include/z64.h"

AdpcmBook vo_zelda_hereitisBook = {
	.order       = 2,
	.npredictors = 4,
	.book        = {
		 -1290,    72,   808,   -91,  -504,    85,   312,   -71,
		  -115, -1283,   144,   800,  -135,  -496,   113,   306,
		  -852,  -901,  -598,  -258,   -23,    82,    97,    68,
		  2165,  1437,   619,    56,  -198,  -233,  -164,   -76,
		 -1369,  -541,   702,   639,  -217,  -513,   -57,   320,
		   809, -1050,  -955,   325,   767,    86,  -479,  -246,
		  -924, -1297, -1402, -1381, -1304, -1206, -1103, -1003,
		  2873,  3105,  3059,  2889,  2672,  2444,  2222,  2013,
	},
};

AdpcmLoop vo_zelda_hereitisLoop = {
	.start  = 0,
	.end    = 25600,
	.count  = 0,
	.unk_0C = {
		0x0, 0x0, 0x0, 0x0
	},
};

SoundFontSample vo_zelda_hereitisSample = {
	.codec     = 0,
	.medium    = 0,
	.unk_bit26 = 0,
	.unk_bit25 = 0,
	.size      = 14400,
	.loop      = &vo_zelda_hereitisLoop,
	.book      = &vo_zelda_hereitisBook,
};

SoundFontSound vo_zelda_hereitisSound = {
	.sample = &vo_zelda_hereitisSample,
	.tuning = 1.000000f
};
