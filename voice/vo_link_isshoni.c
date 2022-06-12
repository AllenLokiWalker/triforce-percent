// "include/z64.h"

AdpcmBook vo_link_isshoniBook = {
	.order       = 2,
	.npredictors = 4,
	.book        = {
		 -1311,   277,   781,  -342,  -427,   309,   208,  -242,
		  -432, -1220,   534,   668,  -483,  -326,   378,   129,
		  -521,  -570,  -491,  -392,  -304,  -232,  -177,  -134,
		  2240,  1929,  1540,  1194,   914,   696,   529,   401,
		 -1182,  -872,    38,   531,   370,   -34,  -238,  -156,
		  1511,   -67,  -921,  -641,    58,   413,   271,   -38,
		 -1362, -2225, -2731, -2984, -3060, -3016, -2895, -2725,
		  3347,  4108,  4487,  4602,  4536,  4353,  4098,  3802,
	},
};

AdpcmLoop vo_link_isshoniLoop = {
	.start  = 0,
	.end    = 67806,
	.count  = 0,
	.unk_0C = {
		0x0, 0x0, 0x0, 0x0
	},
};

SoundFontSample vo_link_isshoniSample = {
	.codec     = 0,
	.medium    = 0,
	.unk_bit26 = 0,
	.unk_bit25 = 0,
	.size      = 38142,
	.loop      = &vo_link_isshoniLoop,
	.book      = &vo_link_isshoniBook,
};

SoundFontSound vo_link_isshoniSound = {
	.sample = &vo_link_isshoniSample,
	.tuning = 1.000000f
};
