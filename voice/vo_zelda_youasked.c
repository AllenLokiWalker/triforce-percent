AdpcmLoop vo_zelda_youaskedLoop = {
	.start = 0,
	.end = 52359,
	.count = 0x00000000,
	.origSpls = 0x00000000,
};

AdpcmBook vo_zelda_youaskedBook = {
	.order = 2,
	.npredictors = 4,
	.book = {
		 -1298,   -334,    736,    401,   -363,   -348,    140,    257, 
		   527,  -1162,   -634,    573,    549,   -222,   -405,     36, 
		   278,    152,    120,     86,     63,     46,     34,     25, 
		  1119,    889,    637,    468,    342,    250,    183,    134, 
		 -1326,  -1328,   -472,    387,    693,    444,     -4,   -292, 
		  2052,    730,   -598,  -1071,   -686,      6,    450,    447, 
		 -1018,  -1469,  -1614,  -1599,  -1505,  -1377,  -1239,  -1103, 
		  2955,   3247,   3216,   3027,   2770,   2492,   2220,   1965, 
	},
};

AudioBankSample vo_zelda_youaskedSample = {
	.codec = 0,
	.medium = 0,
	.unk_bit26 = 0,
	.unk_bit25 = 0,
	.size = 29457,
	.sampleAddr = vo_zelda_youaskedTable,
	.loop = &vo_zelda_youaskedLoop,
	.book = &vo_zelda_youaskedBook,
};

