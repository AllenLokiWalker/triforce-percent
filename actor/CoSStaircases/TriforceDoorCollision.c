#include "ultra64.h"
#include "z64.h"
#include "macros.h"

u32 TriforceDoorCollision_polygonTypes[] = {
	 0x00000000, 0x00000000,
};

CollisionPoly TriforceDoorCollision_polygons[] = {
	{ 0x0000, 0x0000, 0x0001, 0x0002, 0x7fff, 0x0000, 0x0000, 0x0539 },
	{ 0x0000, 0x0001, 0x0002, 0x0003, 0x7fff, 0x0000, 0x0000, 0x0539 },
};

Vec3s TriforceDoorCollision_vertices[4] = {
	{ -1337, -432, 1111 },
	{ -1337, -432, -1260 },
	{ -1337, 2130, 1111 },
	{ -1337, 2130, -1260 },
};

CollisionHeader TriforceDoorCollision_collisionHeader = { -1337, -432, -1260, -1337, 2130, 1111, 4, TriforceDoorCollision_vertices, 2, TriforceDoorCollision_polygons, TriforceDoorCollision_polygonTypes, 0, 0, 0 };

