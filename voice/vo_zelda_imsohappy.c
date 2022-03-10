AdpcmLoop vo_zelda_imsohappyLoop = {
	.start = 0,
	.end = 61221,
	.count = 0x00000000,
	.origSpls = 0x00000000,
};

AdpcmBook vo_zelda_imsohappyBook = {
	.order = 2,
	.npredictors = 4,
	.book = {
		 -1379,     -9,    929,     12,   -626,    -12,    421,     11, 
		    13,  -1379,    -18,    929,     18,   -625,    -16,    421, 
		  -566,   -433,   -174,    -13,     38,     33,     14,      2, 
		  1564,    629,     48,   -137,   -118,    -52,     -7,      9, 
		 -1495,   -652,    806,    828,   -227,   -703,   -141,    452, 
		   894,  -1104,  -1135,    311,    964,    194,   -619,   -412, 
		  -812,  -1055,  -1049,   -945,   -811,   -680,   -561,   -460, 
		  2661,   2645,   2382,   2046,   1714,   1415,   1159,    945, 
	},
};

AudioBankSample vo_zelda_imsohappySample = {
	.codec = 0,
	.medium = 0,
	.unk_bit26 = 0,
	.unk_bit25 = 0,
	.size = 34443,
	.sampleAddr = vo_zelda_imsohappyTable,
	.loop = &vo_zelda_imsohappyLoop,
	.book = &vo_zelda_imsohappyBook,
};

