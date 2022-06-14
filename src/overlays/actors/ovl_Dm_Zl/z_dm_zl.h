#ifndef Z_DM_ZL_H
#define Z_DM_ZL_H

#include "global.h"

struct DmZl;

typedef void (*DmZlActionFunc)(struct DmZl*, GlobalContext*);

typedef struct DmZl {
    /* 0x000 */ Actor actor;
    /* 0x144 */ SkelAnime skelAnime;
    ///* 0x188 */ UNK_TYPE1 pad188[0xD8]; // unused by DmZl
    /* 0x0218 */ Vec3s jointTable[18];
    /* 0x0284 */ Vec3s morphTable[18];
    /* 0x260 */ DmZlActionFunc actionFunc;
    /* 0x0194 */ ColliderCylinder collider;
    ///* 0x264 */ UNK_TYPE1 pad264[0x4C]; // unused by DmZl
    /* 0x2B0 */ s16 animationIndex;
    /* 0x2B2 */ u8 eyeTextureIndexLeft;
    /* 0x2B3 */ u8 eyeTextureIndexRight;
    /* 0x2B4 */ u8 mouthTextureIndex;
    /* 0x2B5 */ u8 nextEyeState;   // used to control eye state, but not set by our actor, outside of actor?
    /* 0x2B6 */ u8 nextMouthState; // used to control mouth state, but not set by our actor, outside of actor?
    /* 0x2B8 */ s16 blinkTimer;
    /* 0x2BA */ s16 unused2BA; // init to 0, unread/unchanged by DmZl after
    /* 0x2BC */ UNK_TYPE1 pad2BC[0x18]; // unused by DmZl
    /* 0x??? */ Vec3s headRot;
    /* 0x??? */ Vec3s chestRot;
} DmZl; // size = 0x2D4

extern const ActorInit Dm_Zl_InitVars;

// vanilla params are 0x0000, never checked or used
#define DMZL_TYPE_SOT_CUTCSENE 0

#endif // Z_DM_ZL_H
