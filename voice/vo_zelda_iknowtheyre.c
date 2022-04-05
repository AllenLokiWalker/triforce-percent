AdpcmLoop vo_zelda_iknowtheyreLoop = {
	.start = 0,
	.end = 168960,
	.count = 0x00000000,
	.origSpls = 0x00000000,
};

AdpcmBook vo_zelda_iknowtheyreBook = {
	.order = 2,
	.npredictors = 4,
	.book = {
		  -379,    339,   -233,    146,    -88,     51,    -30,     17, 
		 -1833,   1262,   -791,    474,   -278,    161,    -93,     53, 
		   343,    177,    148,    106,     79,     59,     44,     32, 
		  1056,    887,    633,    475,    351,    260,    193,    143, 
		 -1213,   -284,    651,    321,   -310,   -263,    122,    184, 
		   480,  -1100,   -542,    524,    444,   -206,   -311,     49, 
		  -774,   -993,   -981,   -884,   -763,   -645,   -540,   -449, 
		  2627,   2597,   2340,   2021,   1708,   1429,   1187,    984, 
	},
};

AudioBankSample vo_zelda_iknowtheyreSample = {
	.codec = 0,
	.medium = 0,
	.unk_bit26 = 0,
	.unk_bit25 = 0,
	.size = 95040,
	.sampleAddr = vo_zelda_iknowtheyreTable,
	.loop = &vo_zelda_iknowtheyreLoop,
	.book = &vo_zelda_iknowtheyreBook,
};

