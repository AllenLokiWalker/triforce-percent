#include "ultra64.h"
#include "global.h"

s16 BotWLinkMeshReachdownAnimFrameData[49] = {
	0x0000, 0x03ae, 0x4000, 0x8000, 0xffff, 0x0138, 0xbfff, 0xc0b1, 0xfd03, 0x41dd, 0x0125, 0xc233, 0x0798, 0xc5d3, 0x04c0, 0x825b, 
	0xbb4d, 0xfb1e, 0x3fdf, 0x00e7, 0xbe6b, 0x0b69, 0xc792, 0xfb97, 0x7bed, 0xc245, 0x804e, 0xff57, 0x0e8c, 0xfb9f, 0xf9fd, 0x7fff, 
	0xbb21, 0x5cde, 0x921b, 0x9beb, 0x6de4, 0xca45, 0x3852, 0x5159, 0xf77d, 0x7b35, 0x1035, 0x37d8, 0x3295, 0xafe6, 0xf703, 0x1e56, 
	0x1841, };

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
	{ 0x001f, 0x0000, 0x0000, },
	{ 0x001f, 0x0000, 0x0000, },
	{ 0x0020, 0x0004, 0x0000, },
	{ 0x0021, 0x0000, 0x0004, },
	{ 0x0006, 0x0022, 0x0004, },
	{ 0x001f, 0x0000, 0x0000, },
	{ 0x0023, 0x0000, 0x0000, },
	{ 0x0006, 0x0024, 0x0004, },
	{ 0x001f, 0x0000, 0x0000, },
	{ 0x0025, 0x0026, 0x0027, },
	{ 0x0028, 0x0029, 0x002a, },
	{ 0x002b, 0x002c, 0x002d, },
	{ 0x002e, 0x002f, 0x0030, },
};

AnimationHeader BotWLinkMeshReachdownAnim = { { 2 }, BotWLinkMeshReachdownAnimFrameData, BotWLinkMeshReachdownAnimJointIndices, 49 };

