// "include/z64.h"

AdpcmBook botw_step_grassstraw_l1Book = {
	.order       = 2,
	.npredictors = 4,
	.book        = {
		   -78,    24,    -4,     0,     0,     0,     0,     0,
		  -630,   116,   -12,    -1,     1,     0,     0,     0,
		   408,    82,    98,    36,    27,    13,     8,     4,
		   413,   491,   182,   134,    63,    40,    21,    12,
		  -373,   -28,    66,    10,   -11,    -3,     2,     1,
		   152,  -362,   -55,    62,    15,   -10,    -3,     2,
		   625,   319,   353,   277,   249,   212,   184,   159,
		  1045,  1158,   910,   817,   695,   604,   520,   450,
	},
};

AdpcmLoop botw_step_grassstraw_l1Loop = {
	.start  = 0,
	.end    = 10465,
	.count  = 0,
	.unk_0C = {
		0x0, 0x0, 0x0, 0x0
	},
};

SoundFontSample botw_step_grassstraw_l1Sample = {
	.codec     = 0,
	.medium    = 0,
	.unk_bit26 = 0,
	.unk_bit25 = 0,
	.size      = 5896,
	.loop      = &botw_step_grassstraw_l1Loop,
	.book      = &botw_step_grassstraw_l1Book,
};

SoundFontSound botw_step_grassstraw_l1Sound = {
	.sample = &botw_step_grassstraw_l1Sample,
	.tuning = 1.000000f
};
