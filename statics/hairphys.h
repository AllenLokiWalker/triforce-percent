#ifndef _HAIRPHYS_H_
#define _HAIRPHYS_H_ 

typedef struct {
    float mass;
    float oneovermass;
    float len;
    float restoreforce;
    float yawmult;
    float dampening;
    float windpush;
} HairPhysBasic;

typedef struct {
    Vec3f neg;
    Vec3f pos;
} HairPhysLimits;

typedef struct {
    HairPhysBasic b;
    float actorscale;
    const HairPhysLimits *lim;
} HairPhysDouble;

typedef struct {
    u8 index;
    float force;
} HairPhysConnection;

typedef struct {
    u8 mode; // 0 simple, 1 double, 2 tunic
    const HairPhysBasic *b;
    const HairPhysLimits *lim;
    const HairPhysDouble *dbl;
    const HairPhysConnection *conn1;
    const HairPhysConnection *conn2;
} HairPhysConstants;

#define HAIRPHYS_UNITROT 256.0f

typedef struct {
    Vec3f r; //rotation
    Vec3f v; //angular velocity
} HairPhysSimpleState;

typedef struct {
    Vec3f pos;
    Vec3f vel;
    Vec3f fnext; //Force from next segment on last frame
} HairPhysDSegState;

typedef struct {
    HairPhysDSegState s1, s2;
    u8 initted;
} HairPhysDoubleState;

typedef struct {
    float todo;
} HairPhysTunicState;

void HairPhys_Init(void *s, const HairPhysConstants *c);
void HairPhys_Update(void *s, const HairPhysConstants *c, Vec3f *lPos, 
    Vec3s *lRot, float windX, float windZ);

#endif //_HAIRPHYS_H_
