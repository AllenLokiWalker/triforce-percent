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
		   620,    340,    374,    308,    282,    248,    221,    196, 
		  1123,   1235,   1017,    931,    818,    730,    648,    576, 
		 -1279,  -1004,      9,    634,    492,     -9,   -315,   -241, 
		  1609,    -15,  -1016,   -789,     15,    504,    387,    -11, 
		 -1054,  -1540,  -1708,  -1703,  -1609,  -1474,  -1326,  -1178, 
		  2992,   3318,   3308,   3125,   2864,   2576,   2289,   2019, 
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

