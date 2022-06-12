// "include/z64.h"

AdpcmBook vo_zelda_linkBook = {
	.order       = 2,
	.npredictors = 4,
	.book        = {
		 -1054,  1325, -1123,   730,  -340,    51,   110,  -165,
		 -2575,  2183, -1419,   660,  -100,  -214,   321,  -293,
		  -182,  -154,  -114,   -83,   -60,   -43,   -31,   -22,
		  1731,  1281,   928,   671,   484,   350,   252,   182,
		    53,    15,     6,     2,     1,     0,     0,     0,
		   571,   212,    74,    26,     9,     3,     1,     0,
		  -829, -1109, -1148, -1088,  -991,  -886,  -784,  -691,
		  2740,  2838,  2689,  2449,  2189,  1938,  1707,  1500,
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
