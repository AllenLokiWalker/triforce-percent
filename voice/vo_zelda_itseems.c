// "include/z64.h"

AdpcmBook vo_zelda_itseemsBook = {
	.order       = 2,
	.npredictors = 4,
	.book        = {
		 -1394,    28,   948,   -38,  -644,    39,   438,   -35,
		   -41, -1393,    56,   947,   -57,  -643,    52,   437,
		   683,   266,   332,   218,   196,   149,   123,    98,
		   799,   995,   654,   587,   447,   370,   293,   238,
		 -1095,  -761,    56,   446,   280,   -44,  -180,  -102,
		  1424,  -105,  -834,  -524,    82,   337,   191,   -48,
		  -717,  -920,  -929,  -870,  -791,  -710,  -634,  -564,
		  2627,  2654,  2484,  2258,  2026,  1809,  1611,  1434,
	},
};

AdpcmLoop vo_zelda_itseemsLoop = {
	.start  = 0,
	.end    = 119808,
	.count  = 0,
	.unk_0C = {
		0x0, 0x0, 0x0, 0x0
	},
};

SoundFontSample vo_zelda_itseemsSample = {
	.codec     = 0,
	.medium    = 0,
	.unk_bit26 = 0,
	.unk_bit25 = 0,
	.size      = 67392,
	.loop      = &vo_zelda_itseemsLoop,
	.book      = &vo_zelda_itseemsBook,
};

SoundFontSound vo_zelda_itseemsSound = {
	.sample = &vo_zelda_itseemsSample,
	.tuning = 1.000000f
};
