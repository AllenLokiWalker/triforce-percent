

static Color_RGBA8 sDustPrimColor = { 250, 250, 250, 255 };
static Color_RGBA8 sDustEnvColor = { 180, 180, 180, 255 };


s16 D_80891794[] = { 0x0000, 0x4000, 0x2000, 0x6000, 0x1000, 0x5000, 0x3000, 0x7000 };
s16 D_808917A4[] = { 0x0000, 0x003C, 0x0018, 0x0054, 0x0030, 0x000C, 0x0048, 0x0024 };


void func_808908FC(Vec3f* dest, Vec3f* src, s16 angle) {
    f32 sin = Math_SinS(angle);
    f32 cos = Math_CosS(angle);

    dest->x = (src->z * sin) + (src->x * cos);
    dest->y = src->y;
    dest->z = (src->z * cos) - (src->x * sin);
}

void func_80890B8C(Vec3f* pos, GlobalContext* globalCtx, f32 chance, f32 scale) {
	f32 cos;
	f32 sin;
	f32 xzOffset;
	Vec3f* icePos;
	s16 angle;
	s16 frames;
	s32 i;
	Vec3f dustPos;
	Vec3f dustVel;
	Vec3f dustAccel;

	frames = (s16)globalCtx->state.frames & 7;

	for (i = 0; i < 10; i++) {
		if (chance < Rand_ZeroOne()) {
			continue;
		}

		xzOffset = 42.0f * scale * (Rand_ZeroOne() + 0.5f);
		icePos = pos;
		angle = D_80891794[frames] + (i * 0x2000);
		sin = Math_SinS(angle);
		cos = Math_CosS(angle);

		dustPos.x = (xzOffset * sin) + icePos->x;
		dustPos.y = (16.0f * scale) + icePos->y;
		dustPos.z = (xzOffset * cos) + icePos->z;

		dustVel.x = ((Rand_ZeroOne() * 3.0f) - 1.0f) * sin;
		dustVel.y = 0.0f;
		dustVel.z = ((Rand_ZeroOne() * 3.0f) - 1.0f) * cos;

		dustAccel.x = 0.07f * sin;
		dustAccel.y = 0.8f;
		dustAccel.z = 0.07f * cos;

		func_8002829C(globalCtx, &dustPos, &dustVel, &dustAccel, &sDustPrimColor, &sDustEnvColor, 450.0f * scale,
					  (s16)((Rand_ZeroOne() * 40.0f) + 40.0f) * scale);
	}
}



void func_80890E00(Vec3f* pos, GlobalContext* globalCtx, f32 chance, f32 arg3) {
	static f32 D_808917B4[] = { -1.0f, 1.0f };
	Vec3f* icePos;
	s16 frames;
	Vec3f dustPos;
	Vec3f dustVel;
	Vec3f dustAccel;
	Vec3f posOffset;
	s32 i;

	frames = (s16)globalCtx->state.frames & 7;

	for (i = 0; i < 2; i++) {
		icePos = pos;

		if (chance < Rand_ZeroOne()) {
			continue;
		}

		posOffset.x = (D_808917A4[frames] + ((Rand_ZeroOne() * 12.0f) - 6.0f)) * D_808917B4[i];
		posOffset.y = 15.0f;
		posOffset.z = ((84.0f - posOffset.x) * 0.2f) + (Rand_ZeroOne() * 20.0f);

		func_808908FC(&dustPos, &posOffset, 0/*yRot*/);
		Math_Vec3f_Sum(&dustPos, icePos, &dustPos);

		dustVel.x = (Rand_ZeroOne() * 3.0f) - 1.5f;
		dustVel.y = 0.0f;
		dustVel.z = (Rand_ZeroOne() * 3.0f) - 1.5f;

		dustAccel.x = (Rand_ZeroOne() * 0.14f) - 0.07f;
		dustAccel.y = 0.8f;
		dustAccel.z = (Rand_ZeroOne() * 0.14f) - 0.07f;

		func_8002829C(globalCtx, &dustPos, &dustVel, &dustAccel, &sDustPrimColor, &sDustEnvColor, 450,
					  (Rand_ZeroOne() * 40.0f) + 40.0f);
	}
}


