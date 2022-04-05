AdpcmLoop vo_zelda_hereitisLoop = {
	.start = 0,
	.end = 25600,
	.count = 0x00000000,
	.origSpls = 0x00000000,
};

AdpcmBook vo_zelda_hereitisBook = {
	.order = 2,
	.npredictors = 4,
	.book = {
		   964,   -233,    510,   -233,    296,   -181,    183,   -129, 
		  -494,   1083,   -494,    629,   -384,    389,   -275,    250, 
		  -910,   -599,     10,    273,    175,     -6,    -82,    -51, 
		  1347,    -23,   -614,   -394,     14,    184,    115,     -6, 
		 -1517,   -236,   1087,    344,   -751,   -371,    499,    352, 
		   318,  -1467,   -464,   1015,    501,   -673,   -476,    425, 
		  -855,  -1129,  -1134,  -1026,   -881,   -735,   -603,   -489, 
		  2704,   2716,   2457,   2110,   1761,   1444,   1172,    945, 
	},
};

AudioBankSample vo_zelda_hereitisSample = {
	.codec = 0,
	.medium = 0,
	.unk_bit26 = 0,
	.unk_bit25 = 0,
	.size = 14400,
	.sampleAddr = vo_zelda_hereitisTable,
	.loop = &vo_zelda_hereitisLoop,
	.book = &vo_zelda_hereitisBook,
};

