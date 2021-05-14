#ifndef Z_EN_DRS_H
#define Z_EN_DRS_H

#include <global.h>

typedef void (*EnDrsActionFunc)(struct EnDrs*, GlobalContext*);

struct EnDrs;

typedef struct EnDrs {
    /* 0x000 */ Actor actor;
    /* 0x144 */ SkelAnime skelAnime;
    /* 0x188 */ EnDrsActionFunc actionFunc;
    /* 0x18C */ ColliderCylinder collider;
    /* 0x1D8 */ Vec3s limbDrawTable[0x4];
    /* 0x1F0 */ Vec3s transitionDrawTable[0x4];
    /* 0x208 */ s8 moonMaskObjId;
} EnDrs; // size = 0x20C

extern const ActorInit En_Drs_InitVars;

extern AnimationHeader object_drs_posing_anim[];
extern SkeletonHeader object_drs_skeleton[];
extern Gfx object_drs_dlist[];

#endif // Z_EN_DRS_H
