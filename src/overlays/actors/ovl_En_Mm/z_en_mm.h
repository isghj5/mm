#ifndef Z_EN_MM_H
#define Z_EN_MM_H

#include <global.h>

struct EnMm;

typedef void (*EnMmActionFunc)(struct EnMm*, GlobalContext*);

typedef struct EnMm {
    /* 0x000 */ Actor actor;
    ///* 0x144 */ char unk_144[0x678];
    /* 0x144 */ ColliderCylinder collider;
    /* 0x190 */ s16 xRot;
    /* 0x190 */ s16 padding ;
    /* 0x194 */ EnMmActionFunc actionFunc;
    
} EnMm; // size = 0x198

extern Gfx D_04055628[]; // displaylist

extern f32 D_80966380; // velocity modifier used in func_80965DB4

extern const ActorInit En_Mm_InitVars;


#endif // Z_EN_MM_H
