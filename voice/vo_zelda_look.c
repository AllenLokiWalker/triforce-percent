// "include/z64.h"

AdpcmBook vo_zelda_lookBook = {
	.order       = 2,
	.npredictors = 4,
	.book        = {
		 -1217,  1697, -1642,  1280,  -809,   367,   -31,  -175,
		 -2855,  2763, -2154,  1361,  -617,    51,   295,  -442,
		  -953, -1064,  -746,  -338,   -31,   123,   152,   112,
		  2288,  1603,   726,    66,  -264,  -326,  -241,  -118,
		  -216,  -129,   -54,   -19,    -5,    -1,     0,     0,
		  1223,   514,   178,    52,    12,     2,     0,     0,
		 -1183, -1786, -2014, -2010, -1872, -1667, -1436, -1206,
		  3093,  3488,  3481,  3242,  2886,  2486,  2088,  1717,
	},
};

AdpcmLoop vo_zelda_lookLoop = {
	.start  = 0,
	.end    = 30720,
	.count  = 0,
	.unk_0C = {
		0x0, 0x0, 0x0, 0x0
	},
};

SoundFontSample vo_zelda_lookSample = {
	.codec     = 0,
	.medium    = 0,
	.unk_bit26 = 0,
	.unk_bit25 = 0,
	.size      = 17280,
	.loop      = &vo_zelda_lookLoop,
	.book      = &vo_zelda_lookBook,
};

SoundFontSound vo_zelda_lookSound = {
	.sample = &vo_zelda_lookSample,
	.tuning = 1.000000f
};
