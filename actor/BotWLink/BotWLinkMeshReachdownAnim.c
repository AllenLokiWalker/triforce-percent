#include "ultra64.h"
#include "global.h"

s16 BotWLinkMeshReachdownAnimFrameData[68] = {
	0x0000, 0x03ae, 0x4000, 0x8000, 0xffff, 0x0138, 0xbfff, 0xc0b1, 0xfd03, 0x41dd, 0x0125, 0xc233, 0x0798, 0xc5d3, 0x04c0, 0x825b, 
	0xbb4d, 0xfb1e, 0x3fdf, 0x00e7, 0xbe6b, 0x0b69, 0xc792, 0xfb97, 0x7bed, 0xbfe3, 0x8058, 0x0003, 0x1104, 0xfb51, 0xf9b2, 0x7819, 
	0xff55, 0xffce, 0x77a2, 0x019f, 0xffc9, 0xbc09, 0x01d5, 0xff0f, 0x5d8b, 0x000d, 0xfffb, 0xc243, 0x909a, 0xff09, 0x6bad, 0x0070, 
	0x0a43, 0x9beb, 0xc27c, 0x6f30, 0x012b, 0x75a4, 0x03c2, 0x0cf1, 0xc3d3, 0x3718, 0x4afa, 0xf78f, 0x7b3a, 0x0f6b, 0x35f4, 0x359d, 
	0xae21, 0xf72c, 0x1e4d, 0x18f8, };

JointIndex BotWLinkMeshReachdownAnimJointIndices[30] = {
	{ 0x0000, 0x0001, 0x0000, },
	{ 0x0002, 0x0000, 0x0003, },
	{ 0x0004, 0x0005, 0x0000, },
	{ 0x0006, 0x0000, 0x0003, },
	{ 0x0006, 0x0000, 0x0003, },
	{ 0x0006, 0x0000, 0x0003, },
	{ 0x0006, 0x0000, 0x0003, },
	{ 0x0006, 0x0000, 0x0003, },
	{ 0x0006, 0x0000, 0x0003, },
	{ 0x0007, 0x0008, 0x0009, },
	{ 0x000a, 0x000b, 0x000c, },
	{ 0x000d, 0x000e, 0x000f, },
	{ 0x0010, 0x0011, 0x0012, },
	{ 0x0013, 0x0014, 0x0015, },
	{ 0x0016, 0x0017, 0x0018, },
	{ 0x0019, 0x001a, 0x001b, },
	{ 0x001c, 0x001d, 0x001e, },
	{ 0x001f, 0x0020, 0x0021, },
	{ 0x0022, 0x0023, 0x0024, },
	{ 0x0025, 0x0026, 0x0027, },
	{ 0x0028, 0x0029, 0x002a, },
	{ 0x002b, 0x002c, 0x002d, },
	{ 0x002e, 0x002f, 0x0030, },
	{ 0x0031, 0x0004, 0x0000, },
	{ 0x0032, 0x0033, 0x0034, },
	{ 0x0035, 0x0036, 0x0037, },
	{ 0x0038, 0x0039, 0x003a, },
	{ 0x003b, 0x003c, 0x003d, },
	{ 0x003e, 0x003f, 0x0040, },
	{ 0x0041, 0x0042, 0x0043, },
};

AnimationHeader BotWLinkMeshReachdownAnim = { { 2 }, BotWLinkMeshReachdownAnimFrameData, BotWLinkMeshReachdownAnimJointIndices, 68 };
