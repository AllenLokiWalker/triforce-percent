AdpcmLoop vo_zelda_youaskedLoop = {
	.start = 0,
	.end = 53248,
	.count = 0x00000000,
	.origSpls = 0x00000000,
};

AdpcmBook vo_zelda_youaskedBook = {
	.order = 2,
	.npredictors = 4,
	.book = {
		   957,    193,    486,    188,    265,    142,    152,     97, 
		   414,   1040,    404,    567,    303,    326,    208,    194, 
		 -1198,  -1164,   -430,    263,    507,    339,     33,   -167, 
		  1990,    735,   -450,   -867,   -580,    -56,    285,    309, 
		 -1275,   -337,    705,    396,   -334,   -335,    120,    240, 
		   541,  -1132,   -636,    537,    538,   -192,   -386,     18, 
		  -912,  -1267,  -1355,  -1318,  -1229,  -1120,  -1010,   -904, 
		  2846,   3043,   2961,   2759,   2516,   2267,   2030,   1811, 
	},
};

AudioBankSample vo_zelda_youaskedSample = {
	.codec = 0,
	.medium = 0,
	.unk_bit26 = 0,
	.unk_bit25 = 0,
	.size = 29952,
	.sampleAddr = vo_zelda_youaskedTable,
	.loop = &vo_zelda_youaskedLoop,
	.book = &vo_zelda_youaskedBook,
};

