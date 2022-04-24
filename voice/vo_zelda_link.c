// "include/z64.h"

AdpcmBook vo_zelda_linkBook = {
	.order       = 2,
	.npredictors = 4,
	.book        = {
		 -1110,  1439, -1264,   858,  -427,    88,   117,  -200,
		 -2655,  2331, -1582,   787,  -163,  -216,   368,  -360,
		   166,   113,    90,    70,    55,    43,    34,    27,
		  1393,  1114,   870,   682,   535,   419,   328,   257,
		  -236,   -41,    20,     8,    -1,    -1,     0,     0,
		   356,  -174,   -71,     8,    10,     1,    -1,     0,
		  -807, -1056, -1066,  -980,  -863,  -745,  -635,  -538,
		  2682,  2706,  2487,  2191,  1890,  1612,  1367,  1155,
	},
};

AdpcmLoop vo_zelda_linkLoop = {
	.start  = 0,
	.end    = 20480,
	.count  = 0,
	.unk_0C = {
		0x0, 0x0, 0x0, 0x0
	},
};

SoundFontSample vo_zelda_linkSample = {
	.codec     = 0,
	.medium    = 0,
	.unk_bit26 = 0,
	.unk_bit25 = 0,
	.size      = 11520,
	.loop      = &vo_zelda_linkLoop,
	.book      = &vo_zelda_linkBook,
};

SoundFontSound vo_zelda_linkSound = {
	.sample = &vo_zelda_linkSample,
	.tuning = 1.000000f
};
