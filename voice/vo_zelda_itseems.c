AdpcmLoop vo_zelda_itseemsLoop = {
	.start = 0,
	.end = 119189,
	.count = 0x00000000,
	.origSpls = 0x00000000,
};

AdpcmBook vo_zelda_itseemsBook = {
	.order = 2,
	.npredictors = 4,
	.book = {
		 -1383,     33,    934,    -45,   -630,     45,    424,    -41, 
		   -49,  -1382,     66,    932,    -67,   -628,     60,    423, 
		   388,    211,    189,    143,    113,     89,     70,     55, 
		  1115,    995,    753,    598,    468,    368,    289,    227, 
		 -1166,   -802,    112,    534,    303,    -95,   -238,   -110, 
		  1409,   -197,   -938,   -533,    168,    419,    192,   -106, 
		  -795,  -1051,  -1082,  -1023,   -934,   -838,   -746,   -662, 
		  2709,   2788,   2637,   2406,   2159,   1922,   1705,   1509, 
	},
};

AudioBankSample vo_zelda_itseemsSample = {
	.codec = 0,
	.medium = 0,
	.unk_bit26 = 0,
	.unk_bit25 = 0,
	.size = 67050,
	.sampleAddr = vo_zelda_itseemsTable,
	.loop = &vo_zelda_itseemsLoop,
	.book = &vo_zelda_itseemsBook,
};

