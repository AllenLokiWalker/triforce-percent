AdpcmLoop vo_link_isshoniLoop = {
	.start = 0,
	.end = 67806,
	.count = 0x00000000,
	.origSpls = 0x00000000,
};

AdpcmBook vo_link_isshoniBook = {
	.order = 2,
	.npredictors = 4,
	.book = {
		 -1374,    327,    844,   -420,   -467,    393,    220,   -316, 
		  -487,  -1258,    626,    695,   -586,   -327,    471,    108, 
		   274,    200,    182,    160,    141,    124,    110,     97, 
		  1495,   1365,   1196,   1056,    930,    820,    723,    638, 
		 -1230,   -948,      8,    576,    439,     -8,   -270,   -203, 
		  1579,    -13,   -959,   -731,     13,    449,    338,     -9, 
		 -1241,  -1943,  -2288,  -2403,  -2373,  -2257,  -2094,  -1908, 
		  3205,   3774,   3963,   3915,   3723,   3454,   3148,   2833, 
	},
};

AudioBankSample vo_link_isshoniSample = {
	.codec = 0,
	.medium = 0,
	.unk_bit26 = 0,
	.unk_bit25 = 0,
	.size = 38142,
	.sampleAddr = vo_link_isshoniTable,
	.loop = &vo_link_isshoniLoop,
	.book = &vo_link_isshoniBook,
};

