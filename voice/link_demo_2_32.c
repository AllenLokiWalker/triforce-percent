AdpcmLoop link_demo_2_32Loop = {
	.start = 0,
	.end = 74721,
	.count = 0x00000000,
	.origSpls = 0x00000000,
};

AdpcmBook link_demo_2_32Book = {
	.order = 2,
	.npredictors = 4,
	.book = {
		 -1414,   -321,    903,    426,   -527,   -414,    270,    347, 
		   465,  -1308,   -617,    763,    599,   -391,   -502,    156, 
		   623,    342,    377,    311,    285,    251,    225,    200, 
		  1124,   1240,   1022,    938,    826,    739,    657,    585, 
		 -1278,  -1004,      9,    634,    492,     -9,   -314,   -241, 
		  1608,    -15,  -1015,   -788,     15,    503,    386,    -11, 
		 -1050,  -1531,  -1695,  -1688,  -1594,  -1460,  -1312,  -1166, 
		  2987,   3308,   3294,   3110,   2848,   2560,   2275,   2007, 
	},
};

AudioBankSample link_demo_2_32Sample = {
	.codec = 0,
	.medium = 0,
	.unk_bit26 = 0,
	.unk_bit25 = 0,
	.size = 42039,
	.sampleAddr = link_demo_2_32Table,
	.loop = &link_demo_2_32Loop,
	.book = &link_demo_2_32Book,
};

