AdpcmLoop vo_zelda_imsohappyLoop = {
	.start = 0,
	.end = 61440,
	.count = 0x00000000,
	.origSpls = 0x00000000,
};

AdpcmBook vo_zelda_imsohappyBook = {
	.order = 2,
	.npredictors = 4,
	.book = {
		 -1038,   1327,  -1171,    824,   -461,    171,     15,   -106, 
		 -2619,   2310,  -1626,    909,   -338,    -29,    208,   -251, 
		  -746,   -537,   -115,    113,    123,     48,    -11,    -25, 
		  1475,    316,   -310,   -338,   -131,     29,     68,     39, 
		 -1414,   -260,    928,    351,   -576,   -348,    333,    302, 
		   377,  -1344,   -508,    834,    504,   -483,   -437,    253, 
		  -673,   -824,   -789,   -697,   -595,   -500,   -418,   -348, 
		  2510,   2404,   2122,   1812,   1523,   1272,   1059,    880, 
	},
};

AudioBankSample vo_zelda_imsohappySample = {
	.codec = 0,
	.medium = 0,
	.unk_bit26 = 0,
	.unk_bit25 = 0,
	.size = 34560,
	.sampleAddr = vo_zelda_imsohappyTable,
	.loop = &vo_zelda_imsohappyLoop,
	.book = &vo_zelda_imsohappyBook,
};

