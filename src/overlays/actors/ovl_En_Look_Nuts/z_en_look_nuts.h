#ifndef Z_EN_LOOK_NUTS_H
#define Z_EN_LOOK_NUTS_H

#include <global.h>

struct EnLookNuts;

typedef void (*EnLookNutsActionFunc)(struct EnLookNuts*, GlobalContext*);

#define LOOKNUTS_LIMB_COUNT 11

typedef struct EnLookNuts {
    /* 0x000 */ Actor actor;
    /* 0x144 */ SkelAnime skelAnime;
    ///* 0x188 */ char unk144[0x100];
    /* 0x188 */ Vec3s limbDrawTbl[LOOKNUTS_LIMB_COUNT];
    /* 0x1CA */ Vec3s transitionDrawTable[LOOKNUTS_LIMB_COUNT];
    /* 0x20C */ EnLookNutsActionFunc actionFunc;
    ///* 0x210 */ char unk210[0xA];
    /* 0x210 */ s32 unk210;
    /* 0x214 */ s16 unk214;
    /* 0x21A */ u16 unk21A;
    /* 0x21C */ s16 unk21C;
    /* 0x21E */ s16 switchFlag;
    /* 0x220 */ s16 paramsCopy2;
    /* 0x222 */ s16 unk222;
    /* 0x224 */ s16 unk224;
    /* 0x226 */ s16 unk226;
    /* 0x228 */ char unk228[0x1A];
    /* 0x244 */ ColliderCylinder collider;
    ///* 0x144 */ char unk144[0x14C];
} EnLookNuts; // size = 0x290

extern const ActorInit En_Look_Nuts_InitVars;

#endif // Z_EN_LOOK_NUTS_H
