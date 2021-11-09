AdpcmLoop link_demo_1_32Loop = {
	.start = 0,
	.end = 75814,
	.count = 0x00000000,
	.origSpls = 0x00000000,
};

AdpcmBook link_demo_1_32Book = {
	.order = 2,
	.npredictors = 4,
	.book = {
		 -1520,    428,   1007,   -601,   -578,    609,    257,   -524, 
		  -577,  -1357,    811,    779,   -821,   -346,    707,     58, 
		   949,    444,    647,    508,    537,    487,    477,    448, 
		   957,   1396,   1096,   1159,   1050,   1028,    967,    928, 
		  -586,   -169,    119,     82,    -10,    -27,     -5,      6, 
		   590,   -415,   -288,     36,     93,     17,    -22,    -11, 
		  -940,  -1340,  -1478,  -1493,  -1449,  -1381,  -1304,  -1224, 
		  2919,   3222,   3253,   3158,   3010,   2841,   2668,   2500, 
	},
};

AudioBankSample link_demo_1_32Sample = {
	.codec = 0,
	.medium = 0,
	.unk_bit26 = 0,
	.unk_bit25 = 0,
	.size = 42651,
	.sampleAddr = link_demo_1_32Table,
	.loop = &link_demo_1_32Loop,
	.book = &link_demo_1_32Book,
};

