AdpcmLoop vo_zelda_thankyouLoop = {
	.start = 0,
	.end = 123904,
	.count = 0x00000000,
	.origSpls = 0x00000000,
};

AdpcmBook vo_zelda_thankyouBook = {
	.order = 2,
	.npredictors = 4,
	.book = {
		 -1298,   1835,  -1769,   1336,   -766,    235,    154,   -366, 
		 -2894,   2790,  -2107,   1208,   -371,   -242,    577,   -662, 
		   126,     66,     43,     27,     17,     10,      6,      4, 
		  1080,    695,    433,    271,    169,    106,     66,     41, 
		  -909,   -189,    364,    160,   -128,    -98,     36,     51, 
		   427,   -820,   -360,    289,    220,    -82,   -115,     13, 
		  -934,  -1305,  -1395,  -1352,  -1252,  -1131,  -1007,   -890, 
		  2859,   3058,   2964,   2743,   2478,   2208,   1952,   1717, 
	},
};

AudioBankSample vo_zelda_thankyouSample = {
	.codec = 0,
	.medium = 0,
	.unk_bit26 = 0,
	.unk_bit25 = 0,
	.size = 69696,
	.sampleAddr = vo_zelda_thankyouTable,
	.loop = &vo_zelda_thankyouLoop,
	.book = &vo_zelda_thankyouBook,
};

