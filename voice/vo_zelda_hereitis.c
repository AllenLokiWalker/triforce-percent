// "include/z64.h"

AdpcmBook vo_zelda_hereitisBook = {
	.order       = 2,
	.npredictors = 4,
	.book        = {
		   939,  -232,   488,  -227,   279,  -173,   171,  -121,
		  -506,  1064,  -495,   610,  -377,   373,  -265,   236,
		  -910,  -599,    10,   273,   175,    -6,   -82,   -51,
		  1347,   -23,  -614,  -394,    14,   184,   115,    -6,
		 -1517,  -236,  1087,   344,  -751,  -371,   499,   352,
		   318, -1467,  -464,  1014,   501,  -673,  -476,   425,
		  -855, -1129, -1133, -1025,  -881,  -735,  -603,  -489,
		  2704,  2715,  2456,  2110,  1761,  1444,  1172,   944,
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
