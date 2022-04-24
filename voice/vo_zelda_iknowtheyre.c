// "include/z64.h"

AdpcmBook vo_zelda_iknowtheyreBook = {
	.order       = 2,
	.npredictors = 4,
	.book        = {
		  -362,   318,  -215,   133,   -79,    46,   -26,    15,
		 -1800,  1221,  -755,   448,  -261,   150,   -86,    49,
		   343,   177,   149,   106,    80,    59,    44,    32,
		  1057,   888,   635,   476,   352,   261,   194,   144,
		 -1213,  -284,   651,   321,  -310,  -263,   122,   184,
		   480, -1100,  -542,   524,   444,  -206,  -311,    49,
		  -774,  -994,  -983,  -885,  -765,  -646,  -540,  -449,
		  2628,  2599,  2341,  2022,  1709,  1429,  1188,   984,
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
