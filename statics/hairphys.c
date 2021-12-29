#include "ootmain.h"
#include "hairphys.h"
#include "../loader/debugger/debugger.h"

static float dt = 0.05f;
static float fps = 20.0f;

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

static void DoubleSegment(HairPhysDSegState *ss, const HairPhysBasic *b, 
        const HairPhysLimits *lim, const Vec3f *newFulcrum, Vec3f *prevFNext){
    Vec3f force, vel1, vel2, pos1, pos2, dp;
    float d, mag;
    //Initialize force to fnext
    force.x = ss->fnext.x;
    force.y = ss->fnext.y;
    force.z = ss->fnext.z;
    //Gravity
    force.y -= b->restoreforce * b->mass;
    //Wind (ignored for now)
    //TODO
    //Dampen velocity (applied to true old velocity)
    ss->vel.x *= b->dampening;
    ss->vel.y *= b->dampening;
    ss->vel.z *= b->dampening;
    //Updated velocity due to forces
    vel1.x = ss->vel.x + force.x * b->oneovermass * dt;
    vel1.y = ss->vel.y + force.y * b->oneovermass * dt;
    vel1.z = ss->vel.z + force.z * b->oneovermass * dt;
    //Updated position due to this velocity
    pos1.x = ss->pos.x + vel1.x * dt;
    pos1.y = ss->pos.y + vel1.y * dt;
    pos1.z = ss->pos.z + vel1.z * dt;
    //Fix this position so it's the right distance from the new fulcrum
    dp.x = pos1.x - newFulcrum->x;
    dp.y = pos1.y - newFulcrum->y;
    dp.z = pos1.z - newFulcrum->z;
    d = 1.0f / sqrtf(dp.x * dp.x + dp.y * dp.y + dp.z * dp.z);
    dp.x *= d;
    dp.y *= d;
    dp.z *= d;
    pos2.x = newFulcrum->x + b->len * dp.x;
    pos2.y = newFulcrum->y + b->len * dp.y;
    pos2.z = newFulcrum->z + b->len * dp.z;
    //Correct the velocity so as actually to be between pos0 and pos2
    vel2.x = (pos2.x - ss->pos.x) * fps;
    vel2.y = (pos2.y - ss->pos.y) * fps;
    vel2.z = (pos2.z - ss->pos.z) * fps;
    if(prevFNext != NULL){
        //Compute the force needed to change the velocity from vel0 to vel2,
        //minus the force which was actually exerted by other things,
        //and inverted because this would be the force on this mass through
        //the rod, but we want the force on the other mass
        prevFNext->x = force.x - (vel2.x - ss->vel.x) * fps * b->mass;
        prevFNext->y = force.y - (vel2.y - ss->vel.y) * fps * b->mass;
        prevFNext->z = force.z - (vel2.z - ss->vel.z) * fps * b->mass;
    }
    //Rotate (project and then fix the scale so the speed stays the same) the
    //velocity to be perpendicular to the rod based on the end state
    mag = sqrtf(vel2.x * vel2.x + vel2.y * vel2.y + vel2.z * vel2.z);
    d = vel2.x * dp.x + vel2.y * dp.y + vel2.z * dp.z;
    vel2.x -= d * dp.x;
    vel2.y -= d * dp.y;
    vel2.z -= d * dp.z; //projection, but have lost speed
    d = sqrtf(vel2.x * vel2.x + vel2.y * vel2.y + vel2.z * vel2.z);
    mag /= d;
    vel2.x *= mag;
    vel2.y *= mag;
    vel2.z *= mag;
    //Store results
    ss->pos.x = pos2.x;
    ss->pos.y = pos2.y;
    ss->pos.z = pos2.z;
    ss->vel.x = vel2.x;
    ss->vel.y = vel2.y;
    ss->vel.z = vel2.z;
}

void HairPhys_UpdateDouble(HairPhysDoubleState *s, const HairPhysConstants *c,
        Vec3f *lPos, Vec3s *lRot, float windMag){
    const HairPhysDouble *dbl = c->dbl;
    float as = 1.0f / dbl->actorscale;
    //Current hair attachment point--fulcrum of first segment
    Vec3f fulcrum;
    Vec3f temp;
    temp.x = lPos->x;
    temp.y = lPos->y + c->b->len * as;
    temp.z = lPos->z;
    Matrix_MultVec3f(&temp, &fulcrum);
    //Get global Y rotation to use as center for hair twist. Assuming there is
    //only one scale factor of dbl->actorscale applied globally.
    //TODO The order of the matrix components is desynced between decomp and
    //z64hdr; when z64hdr is updated, this will have to be fixed.
    s16 twist;
    MtxF *cmf = Matrix_GetCurrent();
    if(cmf->yx * as < 1.0f && cmf->yx * as > -1.0f){
        //These values should all be scaled up by as, but they are only used in
        //asin2, which is scale invariant
        twist = Math_Atan2S(cmf->xx, -cmf->zx);
    }else{
        twist = Math_Atan2S(cmf->zz, cmf->zy);
        if(cmf->yx < 0.0f) twist = -twist;
    }
    //Segment 1
    DoubleSegment(&s->s1, c->b, c->lim, &fulcrum, NULL);
    //Segment 2
    DoubleSegment(&s->s2, &dbl->b, dbl->lim, &s->s1.pos, &s->s1.fnext);
    //Convert to limb position and rotation
    //We want the transformations to be applied to each vertex in this order:
    //global Y (twist)
    //global X (s2)
    //global Z (s2)
    //actor scale
    //translation (s1)
    //Transformations are constructed on the stack in reverse order.
    //The Matrix_JointPosition call taking lPos and lRot will apply X, Y, Z, T
    //(of course constructing them in the reverse order). However, we need Y
    //first, and we can't insert a transformation after that call, so we have
    //to use that call only for the Y rotation, and do the other transforms
    //ourselves.
    Matrix_Translate(s->s1.pos.x, s->s1.pos.y, s->s1.pos.z, MTXMODE_NEW);
    Matrix_Scale(dbl->actorscale, dbl->actorscale, dbl->actorscale, MTXMODE_APPLY);
    //Convert relative position to rotation
    Vec3f dp; float k, l;
    dp.x = s->s2.pos.x - s->s1.pos.x;
    dp.y = s->s2.pos.y - s->s1.pos.z;
    dp.z = s->s2.pos.z - s->s1.pos.z;
    l = dbl->b.len;
    k = sqrtf(l * l - dp.x * dp.x);
    Matrix_RotateRPY(
        Math_Atan2S(-dp.y, -dp.z), //not sure about signs
        0,
        Math_Atan2S(-k, -dp.x), //not sure about signs
        MTXMODE_APPLY);
    lPos->x = 0.0f;
    lPos->y = 0.0f;
    lPos->z = 0.0f;
    lRot->x = 0;
    lRot->y = twist + 0x8000;
    lRot->z = 0;
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
