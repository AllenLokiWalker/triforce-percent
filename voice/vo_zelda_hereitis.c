AdpcmLoop vo_zelda_hereitisLoop = {
	.start = 0,
	.end = 24733,
	.count = 0x00000000,
	.origSpls = 0x00000000,
};

AdpcmBook vo_zelda_hereitisBook = {
	.order = 2,
	.npredictors = 4,
	.book = {
		 -1547,   -165,   1150,    248,   -842,   -277,    607,    274, 
		   219,  -1523,   -328,   1115,    367,   -803,   -363,    568, 
		  -962,  -1039,   -670,   -235,     61,    176,    161,     92, 
		  2211,   1425,    500,   -129,   -375,   -344,   -195,    -49, 
		 -1157,   -549,    393,    497,     13,   -274,   -138,     90, 
		   971,   -696,   -879,    -24,    486,    244,   -159,   -213, 
		  -848,  -1153,  -1216,  -1175,  -1094,  -1000,   -906,   -818, 
		  2784,   2936,   2837,   2641,   2415,   2188,   1975,   1778, 
	},
};

AudioBankSample vo_zelda_hereitisSample = {
	.codec = 0,
	.medium = 0,
	.unk_bit26 = 0,
	.unk_bit25 = 0,
	.size = 13914,
	.sampleAddr = vo_zelda_hereitisTable,
	.loop = &vo_zelda_hereitisLoop,
	.book = &vo_zelda_hereitisBook,
};

