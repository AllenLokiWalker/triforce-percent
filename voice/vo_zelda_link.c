AdpcmLoop vo_zelda_linkLoop = {
	.start = 0,
	.end = 19566,
	.count = 0x00000000,
	.origSpls = 0x00000000,
};

AdpcmBook vo_zelda_linkBook = {
	.order = 2,
	.npredictors = 4,
	.book = {
		  -267,    -31,     31,      8,     -3,     -1,      0,      0, 
		   236,   -240,    -58,     25,     10,     -2,     -2,      0, 
		  -652,   -563,   -278,    -60,     36,     51,     32,     12, 
		  1767,    872,    189,   -114,   -159,   -101,    -36,      1, 
		   466,    279,    273,    227,    198,    170,    147,    127, 
		  1226,   1200,    998,    871,    748,    646,    557,    481, 
		  -821,  -1089,  -1114,  -1041,   -934,   -821,   -714,   -618, 
		  2716,   2780,   2597,   2329,   2048,   1781,   1541,   1329, 
	},
};

AudioBankSample vo_zelda_linkSample = {
	.codec = 0,
	.medium = 0,
	.unk_bit26 = 0,
	.unk_bit25 = 0,
	.size = 11007,
	.sampleAddr = vo_zelda_linkTable,
	.loop = &vo_zelda_linkLoop,
	.book = &vo_zelda_linkBook,
};

