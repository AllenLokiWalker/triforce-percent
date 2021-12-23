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
		 -1223,    -34,    730,     40,   -435,    -36,    259,     28, 
		    56,  -1222,    -67,    728,     60,   -433,    -48,    258, 
		   437,    277,    268,    229,    202,    177,    155,    136, 
		  1297,   1258,   1073,    947,    829,    727,    637,    558, 
		 -1085,   -828,    -57,    395,    332,     44,   -142,   -132, 
		  1563,    107,   -746,   -626,    -82,    269,    249,     47, 
		 -1081,  -1606,  -1817,  -1853,  -1795,  -1689,  -1564,  -1433, 
		  3044,   3443,   3511,   3401,   3201,   2963,   2715,   2471, 
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

