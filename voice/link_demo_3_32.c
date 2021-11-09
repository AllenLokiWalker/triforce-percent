AdpcmLoop link_demo_3_32Loop = {
	.start = 0,
	.end = 82921,
	.count = 0x00000000,
	.origSpls = 0x00000000,
};

AdpcmBook link_demo_3_32Book = {
	.order = 2,
	.npredictors = 4,
	.book = {
		 -1223,    -27,    730,     33,   -435,    -29,    259,     23, 
		    46,  -1222,    -55,    729,     49,   -434,    -39,    258, 
		   404,    260,    247,    210,    184,    160,    139,    121, 
		  1318,   1252,   1065,    932,    810,    705,    614,    534, 
		 -1100,   -827,    -30,    422,    333,     23,   -161,   -134, 
		  1539,     56,   -785,   -620,    -44,    300,    249,     26, 
		 -1085,  -1614,  -1828,  -1865,  -1808,  -1703,  -1577,  -1445, 
		  3048,   3451,   3522,   3414,   3216,   2978,   2729,   2484, 
	},
};

AudioBankSample link_demo_3_32Sample = {
	.codec = 0,
	.medium = 0,
	.unk_bit26 = 0,
	.unk_bit25 = 0,
	.size = 46647,
	.sampleAddr = link_demo_3_32Table,
	.loop = &link_demo_3_32Loop,
	.book = &link_demo_3_32Book,
};

