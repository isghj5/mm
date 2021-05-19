#ifndef Z_EN_TG_H
#define Z_EN_TG_H

#include <global.h>

typedef void (*EnTgActionFunc)(struct EnTg*, GlobalContext*);

struct EnTg;

#define ENTG_LIMBCOUNT 0x15
#define ENTG_PARTICLECOUNT 10

typedef struct EnTgParticle {
    /* 00 */ u8 unk0;
    /* 01 */ u8 unk1;
    /* 04 */ f32 unk4;
    /* 08 */ char unk8[0xC];
    /* 14 */ Vec3f unk14;
    /* 20 */ Vec3f unk20;
    /* 2C */ Vec3f unk2C;
    /* 38 */ u8 unk38[4];
} EnTgParticle; // size = 0x3C

typedef struct EnTg {
    /* 0x000 */ Actor actor;
    /* 0x144 */ EnTgActionFunc actionFunc;
    /* 0x148 */ SkelAnime anime;
    /* 0x18C */ ColliderCylinder collider;
    /* 0x1D8 */ char unk1D8[0x18];
    /* 0x1F0 */ Vec3s limbDrawTbl[ENTG_LIMBCOUNT];
    /* 0x26E */ Vec3s transitionDrawTbl[ENTG_LIMBCOUNT];
    /* 0x2EC */ s16 unk2EC;
    /* 0x2F0 */ EnTgParticle particles[ENTG_PARTICLECOUNT];
    ///* 0x300 */ char unk300[0x200];
} EnTg; // size = 0x548

extern const ActorInit En_Tg_InitVars;

extern SkeletonHeader D_0600B2B0[];

#endif // Z_EN_TG_H
