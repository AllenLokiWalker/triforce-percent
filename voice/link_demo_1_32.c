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
		   966,    443,    660,    512,    546,    492,    483,    454, 
		   940,   1398,   1085,   1157,   1043,   1025,    962,    925, 
		  -573,   -168,    111,     80,     -8,    -25,     -5,      5, 
		   600,   -398,   -284,     28,     88,     18,    -19,    -11, 
		  -977,  -1411,  -1572,  -1597,  -1557,  -1486,  -1404,  -1319, 
		  2958,   3295,   3348,   3263,   3116,   2943,   2765,   2589, 
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

