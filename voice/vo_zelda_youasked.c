// "include/z64.h"

AdpcmBook vo_zelda_youaskedBook = {
	.order       = 2,
	.npredictors = 4,
	.book        = {
		   972,   200,   502,   199,   279,   152,   164,   106,
		   422,  1059,   419,   589,   320,   345,   223,   210,
		 -1194, -1155,  -423,   264,   502,   332,    29,  -166,
		  1982,   725,  -453,  -861,  -570,   -49,   284,   304,
		 -1273,  -334,   704,   393,  -335,  -332,   121,   238,
		   538, -1132,  -631,   538,   534,  -195,  -383,    20,
		  -920, -1282, -1373, -1337, -1247, -1137, -1024,  -917,
		  2854,  3057,  2978,  2777,  2532,  2281,  2041,  1820,
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
