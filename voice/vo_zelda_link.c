AdpcmLoop vo_zelda_linkLoop = {
	.start = 0,
	.end = 20480,
	.count = 0x00000000,
	.origSpls = 0x00000000,
};

AdpcmBook vo_zelda_linkBook = {
	.order = 2,
	.npredictors = 4,
	.book = {
		 -1256,   1737,  -1634,   1195,   -652,    170,    165,   -333, 
		 -2834,   2665,  -1950,   1064,   -277,   -270,    543,   -585, 
		   169,    115,     92,     72,     56,     44,     35,     27, 
		  1393,   1116,    873,    686,    538,    422,    332,    260, 
		  -240,    -40,     22,      8,     -1,     -1,      0,      0, 
		   339,   -184,    -70,     10,     10,      0,     -1,      0, 
		  -807,  -1057,  -1067,   -981,   -864,   -745,   -636,   -539, 
		  2683,   2707,   2488,   2193,   1891,   1613,   1368,   1156, 
	},
};

AudioBankSample vo_zelda_linkSample = {
	.codec = 0,
	.medium = 0,
	.unk_bit26 = 0,
	.unk_bit25 = 0,
	.size = 11520,
	.sampleAddr = vo_zelda_linkTable,
	.loop = &vo_zelda_linkLoop,
	.book = &vo_zelda_linkBook,
};

