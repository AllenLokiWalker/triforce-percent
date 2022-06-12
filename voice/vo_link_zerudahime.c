// "include/z64.h"

AdpcmBook vo_link_zerudahimeBook = {
	.order       = 2,
	.npredictors = 4,
	.book        = {
		 -1169,   332,   573,  -352,  -227,   265,    54,  -167,
		  -581, -1004,   617,   398,  -465,   -95,   292,   -29,
		  -567,  -649,  -586,  -491,  -399,  -321,  -257,  -205,
		  2344,  2116,  1773,  1443,  1161,   929,   742,   592,
		   722,   268,   354,   225,   208,   157,   131,   104,
		   759,  1003,   639,   591,   444,   373,   295,   241,
		 -1412, -2329, -2871, -3133, -3191, -3106, -2927, -2689,
		  3380,  4166,  4545,  4629,  4507,  4247,  3902,  3512,
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
