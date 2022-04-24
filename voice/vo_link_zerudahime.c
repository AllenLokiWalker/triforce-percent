// "include/z64.h"

AdpcmBook vo_link_zerudahimeBook = {
	.order       = 2,
	.npredictors = 4,
	.book        = {
		 -1270,   376,   676,  -433,  -291,   354,    76,  -242,
		  -606, -1090,   698,   469,  -572,  -122,   390,   -40,
		  -168,  -126,   -81,   -50,   -31,   -19,   -12,    -7,
		  1538,   987,   615,   381,   236,   146,    90,    56,
		  1220,   356,   830,   454,   627,   453,   506,   417,
		   597,  1394,   762,  1053,   761,   849,   701,   710,
		 -1167, -1771, -2024, -2065, -1982, -1833, -1654, -1467,
		  3109,  3554,  3625,  3479,  3218,  2904,  2575,  2256,
	},
};

AdpcmLoop vo_link_zerudahimeLoop = {
	.start  = 0,
	.end    = 56986,
	.count  = 0,
	.unk_0C = {
		0x0, 0x0, 0x0, 0x0
	},
};

SoundFontSample vo_link_zerudahimeSample = {
	.codec     = 0,
	.medium    = 0,
	.unk_bit26 = 0,
	.unk_bit25 = 0,
	.size      = 32058,
	.loop      = &vo_link_zerudahimeLoop,
	.book      = &vo_link_zerudahimeBook,
};

SoundFontSound vo_link_zerudahimeSound = {
	.sample = &vo_link_zerudahimeSample,
	.tuning = 1.000000f
};
