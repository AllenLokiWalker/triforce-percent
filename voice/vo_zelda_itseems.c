// "include/z64.h"

AdpcmBook vo_zelda_itseemsBook = {
	.order       = 2,
	.npredictors = 4,
	.book        = {
		 -1282,   135,   788,  -168,  -476,   156,   281,  -127,
		  -216, -1259,   268,   760,  -248,  -450,   203,   260,
		  -147,  -121,   -90,   -65,   -47,   -35,   -25,   -18,
		  1691,  1249,   910,   662,   481,   350,   255,   185,
		 -1046,  -563,   230,   412,   104,  -154,  -136,     5,
		  1103,  -451,  -806,  -204,   302,   267,   -10,  -142,
		  -865, -1192, -1276, -1254, -1188, -1107, -1023,  -941,
		  2821,  3020,  2969,  2813,  2621,  2421,  2228,  2046,
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
