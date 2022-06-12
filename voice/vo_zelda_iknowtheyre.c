// "include/z64.h"

AdpcmBook vo_zelda_iknowtheyreBook = {
	.order       = 2,
	.npredictors = 4,
	.book        = {
		  -485,   198,    34,   -61,    17,     8,    -7,     1,
		  -837,  -143,   257,   -71,   -32,    30,    -5,    -5,
		  -336,  -305,  -221,  -151,  -101,   -67,   -44,   -29,
		  1858,  1350,   920,   614,   406,   268,   176,   116,
		  -807,  -338,   176,   207,    17,   -74,   -38,    13,
		   858,  -447,  -526,   -44,   189,    96,   -34,   -52,
		  -902, -1253, -1343, -1314, -1234, -1136, -1035,  -937,
		  2845,  3050,  2985,  2804,  2580,  2350,  2129,  1922,
	},
};

AdpcmLoop vo_zelda_iknowtheyreLoop = {
	.start  = 0,
	.end    = 168960,
	.count  = 0,
	.unk_0C = {
		0x0, 0x0, 0x0, 0x0
	},
};

SoundFontSample vo_zelda_iknowtheyreSample = {
	.codec     = 0,
	.medium    = 0,
	.unk_bit26 = 0,
	.unk_bit25 = 0,
	.size      = 95040,
	.loop      = &vo_zelda_iknowtheyreLoop,
	.book      = &vo_zelda_iknowtheyreBook,
};

SoundFontSound vo_zelda_iknowtheyreSound = {
	.sample = &vo_zelda_iknowtheyreSample,
	.tuning = 1.000000f
};
