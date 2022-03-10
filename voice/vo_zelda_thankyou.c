AdpcmLoop vo_zelda_thankyouLoop = {
	.start = 0,
	.end = 123755,
	.count = 0x00000000,
	.origSpls = 0x00000000,
};

AdpcmBook vo_zelda_thankyouBook = {
	.order = 2,
	.npredictors = 4,
	.book = {
		 -1050,   -118,    525,    120,   -256,    -90,    121,     60, 
		   231,  -1024,   -234,    499,    176,   -236,   -117,    108, 
		  -304,   -266,   -189,   -126,    -83,    -54,    -35,    -23, 
		  1797,   1274,    851,    558,    364,    237,    154,    100, 
		  -387,   -167,      1,     32,     14,      0,     -3,     -1, 
		   884,     -5,   -170,    -72,      1,     14,      6,      0, 
		 -1145,  -1733,  -1980,  -2025,  -1956,  -1825,  -1667,  -1500, 
		  3098,   3539,   3621,   3497,   3263,   2980,   2682,   2390, 
	},
};

AudioBankSample vo_zelda_thankyouSample = {
	.codec = 0,
	.medium = 0,
	.unk_bit26 = 0,
	.unk_bit25 = 0,
	.size = 69615,
	.sampleAddr = vo_zelda_thankyouTable,
	.loop = &vo_zelda_thankyouLoop,
	.book = &vo_zelda_thankyouBook,
};

