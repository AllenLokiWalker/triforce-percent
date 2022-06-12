// "include/z64.h"

AdpcmBook botw_step_grassstraw_l0Book = {
	.order       = 2,
	.npredictors = 4,
	.book        = {
		    49,   -18,     8,    -3,     1,    -1,     0,     0,
		  -746,   322,  -135,    57,   -24,    10,    -4,     2,
		   276,    71,    55,    24,    14,     7,     4,     2,
		   525,   411,   176,   101,    50,    26,    13,     7,
		  -276,   -13,    37,     4,    -5,    -1,     1,     0,
		    99,  -271,   -26,    35,     5,    -5,    -1,     1,
		   673,   323,   376,   286,   261,   219,   191,   164,
		   982,  1144,   872,   794,   667,   581,   498,   430,
	},
};

AdpcmLoop botw_step_grassstraw_l0Loop = {
	.start  = 0,
	.end    = 10308,
	.count  = 0,
	.unk_0C = {
		0x0, 0x0, 0x0, 0x0
	},
};

SoundFontSample botw_step_grassstraw_l0Sample = {
	.codec     = 0,
	.medium    = 0,
	.unk_bit26 = 0,
	.unk_bit25 = 0,
	.size      = 5806,
	.loop      = &botw_step_grassstraw_l0Loop,
	.book      = &botw_step_grassstraw_l0Book,
};

SoundFontSound botw_step_grassstraw_l0Sound = {
	.sample = &botw_step_grassstraw_l0Sample,
	.tuning = 1.000000f
};
