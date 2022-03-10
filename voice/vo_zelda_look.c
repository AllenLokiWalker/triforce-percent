AdpcmLoop vo_zelda_lookLoop = {
	.start = 0,
	.end = 30409,
	.count = 0x00000000,
	.origSpls = 0x00000000,
};

AdpcmBook vo_zelda_lookBook = {
	.order = 2,
	.npredictors = 4,
	.book = {
		    64,     36,     23,     14,      9,      5,      3,      2, 
		  1166,    728,    451,    279,    173,    107,     66,     41, 
		  -979,  -1198,   -998,   -649,   -318,    -79,     56,    106, 
		  2507,   2089,   1359,    665,    165,   -116,   -221,   -215, 
		  -918,   -827,   -334,     70,    213,    160,     49,    -28, 
		  1846,    745,   -156,   -474,   -358,   -110,     62,    105, 
		 -1357,  -2182,  -2611,  -2754,  -2701,  -2519,  -2264,  -1972, 
		  3294,   3942,   4158,   4077,   3804,   3417,   2977,   2525, 
	},
};

AudioBankSample vo_zelda_lookSample = {
	.codec = 0,
	.medium = 0,
	.unk_bit26 = 0,
	.unk_bit25 = 0,
	.size = 17109,
	.sampleAddr = vo_zelda_lookTable,
	.loop = &vo_zelda_lookLoop,
	.book = &vo_zelda_lookBook,
};

