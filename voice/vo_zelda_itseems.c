AdpcmLoop vo_zelda_itseemsLoop = {
	.start = 0,
	.end = 119808,
	.count = 0x00000000,
	.origSpls = 0x00000000,
};

AdpcmBook vo_zelda_itseemsBook = {
	.order = 2,
	.npredictors = 4,
	.book = {
		 -1394,     28,    948,    -38,   -644,     39,    438,    -35, 
		   -41,  -1393,     56,    947,    -57,   -643,     52,    437, 
		   688,    269,    336,    222,    200,    153,    127,    101, 
		   801,   1001,    660,    594,    454,    377,    300,    244, 
		 -1091,   -757,     56,    442,    277,    -44,   -178,   -100, 
		  1421,   -106,   -830,   -520,     82,    334,    188,    -48, 
		  -719,   -923,   -933,   -874,   -794,   -713,   -636,   -566, 
		  2629,   2657,   2488,   2261,   2029,   1811,   1613,   1435, 
	},
};

AudioBankSample vo_zelda_itseemsSample = {
	.codec = 0,
	.medium = 0,
	.unk_bit26 = 0,
	.unk_bit25 = 0,
	.size = 67392,
	.sampleAddr = vo_zelda_itseemsTable,
	.loop = &vo_zelda_itseemsLoop,
	.book = &vo_zelda_itseemsBook,
};

