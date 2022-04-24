// "include/z64.h"

AdpcmBook vo_zelda_thankyouBook = {
	.order       = 2,
	.npredictors = 4,
	.book        = {
		 -1282,  1799, -1720,  1287,  -728,   215,   154,  -351,
		 -2873,  2747, -2055,  1162,  -344,  -246,   560,  -632,
		   127,    67,    43,    27,    17,    11,     7,     4,
		  1079,   696,   434,   272,   170,   107,    67,    42,
		  -909,  -189,   364,   160,  -128,   -98,    36,    51,
		   427,  -820,  -360,   289,   220,   -82,  -115,    13,
		  -935, -1305, -1396, -1353, -1252, -1131, -1008,  -891,
		  2860,  3058,  2965,  2745,  2479,  2209,  1953,  1719,
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
