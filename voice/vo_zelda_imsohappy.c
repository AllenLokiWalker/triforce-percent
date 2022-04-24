// "include/z64.h"

AdpcmBook vo_zelda_imsohappyBook = {
	.order       = 2,
	.npredictors = 4,
	.book        = {
		  -993,  1245, -1078,   746,  -413,   155,     6,   -83,
		 -2566,  2222, -1539,   850,  -319,   -13,   171,  -208,
		  -751,  -542,  -116,   115,   126,    48,   -11,   -26,
		  1478,   315,  -314,  -342,  -132,    30,    70,    40,
		 -1414,  -260,   928,   351,  -576,  -348,   333,   302,
		   377, -1344,  -508,   834,   504,  -483,  -437,   253,
		  -668,  -818,  -782,  -691,  -590,  -496,  -415,  -346,
		  2506,  2398,  2117,  1808,  1521,  1271,  1059,   882,
	},
};

AdpcmLoop vo_zelda_imsohappyLoop = {
	.start  = 0,
	.end    = 61440,
	.count  = 0,
	.unk_0C = {
		0x0, 0x0, 0x0, 0x0
	},
};

SoundFontSample vo_zelda_imsohappySample = {
	.codec     = 0,
	.medium    = 0,
	.unk_bit26 = 0,
	.unk_bit25 = 0,
	.size      = 34560,
	.loop      = &vo_zelda_imsohappyLoop,
	.book      = &vo_zelda_imsohappyBook,
};

SoundFontSound vo_zelda_imsohappySound = {
	.sample = &vo_zelda_imsohappySample,
	.tuning = 1.000000f
};
