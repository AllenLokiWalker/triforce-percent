AdpcmLoop vo_zelda_iknowtheyreLoop = {
	.start = 0,
	.end = 168056,
	.count = 0x00000000,
	.origSpls = 0x00000000,
};

AdpcmBook vo_zelda_iknowtheyreBook = {
	.order = 2,
	.npredictors = 4,
	.book = {
		 -1259,   -164,    752,    199,   -436,   -179,    245,    142, 
		   267,  -1224,   -324,    710,    292,   -398,   -231,    215, 
		   716,    270,    352,    228,    209,    159,    133,    106, 
		   774,   1008,    651,    599,    454,    381,    303,    247, 
		  -813,   -711,   -300,     20,    136,    111,     43,     -6, 
		  1792,    756,    -50,   -343,   -281,   -110,     16,     57, 
		  -769,  -1006,  -1027,   -966,   -878,   -786,   -698,   -618, 
		  2679,   2736,   2573,   2338,   2093,   1859,   1646,   1456, 
	},
};

AudioBankSample vo_zelda_iknowtheyreSample = {
	.codec = 0,
	.medium = 0,
	.unk_bit26 = 0,
	.unk_bit25 = 0,
	.size = 94536,
	.sampleAddr = vo_zelda_iknowtheyreTable,
	.loop = &vo_zelda_iknowtheyreLoop,
	.book = &vo_zelda_iknowtheyreBook,
};

