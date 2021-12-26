#include "ootmain.h"
#include "hairphys.h"
#include "../loader/debugger/debugger.h"

static float dt = 0.05f;
//static float fps = 20.0f;

void HairPhys_InitSimple(HairPhysSimpleState *s, const HairPhysConstants *c){
    s->r.x = s->r.y = s->r.z = 0.0f;
    s->v.x = s->v.y = s->v.z = 0.0f;
}

void HairPhys_InitDouble(HairPhysDoubleState *s, const HairPhysConstants *c){
    //TODO;
}

void HairPhys_InitTunic(HairPhysTunicState *s, const HairPhysConstants *c){
    //TODO;
}

void HairPhys_UpdateSimple(HairPhysSimpleState *s, const HairPhysConstants *c,
        Vec3f *lPos, Vec3s *lRot, float windMag){
	const HairPhysBasic *b = c->b;
	const HairPhysLimits *lim = c->lim;
    Vec3f force; force.x = 0.0f; force.y = 0.0f; force.z = 0.0f;
    //Restore force, proportional to negative distance from 0. This is a
    //spring force, not gravity, so it isn't proportional to mass.
    force.x -= b->restoreforce * s->r.x;
    force.y -= b->restoreforce * s->r.y;
    force.z -= b->restoreforce * s->r.z;
    //Wind force, just random centered.
    force.x += (windMag * b->windpush) * (Rand_ZeroOne() - 0.5f);
    force.y += (windMag * b->windpush) * (Rand_ZeroOne() - 0.5f);
    force.z += (windMag * b->windpush) * (Rand_ZeroOne() - 0.5f);
    //Dampen velocity
    s->v.x *= b->dampening;
    s->v.y *= b->dampening;
    s->v.z *= b->dampening;
    //dv = f / m * dt
    s->v.x += force.x * b->oneovermass * dt;
    s->v.y += force.y * b->oneovermass * dt;
    s->v.z += force.z * b->oneovermass * dt;
    //dx = v * dt
    s->r.x += s->v.x * dt;
    s->r.y += s->v.y * dt;
    s->r.z += s->v.z * dt;
    //Limits
    if(s->r.x < lim->neg.x){ s->r.x = lim->neg.x; s->v.x = 0.0f; }
    if(s->r.x > lim->pos.x){ s->r.x = lim->pos.x; s->v.x = 0.0f; }
    if(s->r.y < lim->neg.y){ s->r.y = lim->neg.y; s->v.y = 0.0f; }
    if(s->r.y > lim->pos.y){ s->r.y = lim->pos.y; s->v.y = 0.0f; }
    if(s->r.z < lim->neg.z){ s->r.z = lim->neg.z; s->v.z = 0.0f; }
    if(s->r.z > lim->pos.z){ s->r.z = lim->pos.z; s->v.z = 0.0f; }
    //Result
    lRot->x += s->r.x * HAIRPHYS_UNITROT;
    lRot->y += s->r.y * HAIRPHYS_UNITROT;
    lRot->z += s->r.z * HAIRPHYS_UNITROT * b->yawmult;
}

void HairPhys_UpdateDouble(HairPhysDoubleState *s, const HairPhysConstants *c,
        Vec3f *lPos, Vec3s *lRot, float windMag){
    /*
    //Vec3f boneHead;
    //Matrix_MultVec3f(pos, boneHead);
    PhysDoubleState *s = &en->physDouble[iim];
    const PhysDouble *dbl = phys[b].dbl;
    Vec3f fulcrum;
    Vec3f boneposoffset;
    boneposoffset.x = pos->x;
    boneposoffset.y = pos->y + b->len;
    boneposoffset.z = pos->z;
    Matrix_MultVec3f(boneposoffset, fulcrum);
    */
}

void HairPhys_UpdateTunic(HairPhysTunicState *s, const HairPhysConstants *c,
        Vec3f *lPos, Vec3s *lRot, float windMag){
    //TODO;
}

typedef void (*HairPhysInitFunc)(void *s, const HairPhysConstants *c);
typedef void (*HairPhysUpdateFunc)(void *s, const HairPhysConstants *c, 
        Vec3f *lPos, Vec3s *lRot, float windMag);
static const HairPhysInitFunc initFuncs[3] = {
    (HairPhysInitFunc)HairPhys_InitSimple,
    (HairPhysInitFunc)HairPhys_InitDouble,
    (HairPhysInitFunc)HairPhys_InitTunic
};
static const HairPhysUpdateFunc updateFuncs[3] = {
    (HairPhysUpdateFunc)HairPhys_UpdateSimple,
    (HairPhysUpdateFunc)HairPhys_UpdateDouble,
    (HairPhysUpdateFunc)HairPhys_UpdateTunic
};

void HairPhys_Init(void *s, const HairPhysConstants *c){
    if(c->mode >= 3) return;
    initFuncs[c->mode](s, c);
}

void HairPhys_Update(void *s, const HairPhysConstants *c, Vec3f *lPos, 
    Vec3s *lRot, float windMag){
    if(c->mode >= 3) return;
    updateFuncs[c->mode](s, c, lPos, lRot, windMag);
}
