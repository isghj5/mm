#ifndef Z_EN_PO_SISTERS_H
#define Z_EN_PO_SISTERS_H

#include "global.h"

struct EnPoSisters;

typedef void (*EnPoSistersActionFunc)(struct EnPoSisters*, GlobalContext*);

#define PO_SISTER_LIMB_COUNT 0xC

typedef struct EnPoSisters {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ SkelAnime skelAnime;
    /* 0x0188 */ EnPoSistersActionFunc actionFunc;
    /* 0x018C */ u8 sisterType;
    /* 0x018D */ u8 unk18D; // 0xA shifted type?
    /* 0x018E */ u8 unk18E;
    /* 0x018F */ u8 unk18F;
    /* 0x0190 */ u8 unk190;
    /* 0x0191 */ u8 unk191;
    /* 0x0192 */ s16 unk192;
    /* 0x0194 */ s16 unk194; // timer?
    /* 0x0196 */ Vec3s limbDrawTbl[PO_SISTER_LIMB_COUNT];
    /* 0x01DE */ Vec3s transitionDrawTable[PO_SISTER_LIMB_COUNT];
    /* 0x0226 */ Color_RGBA8 unkColor226; 
    /* 0x022C */ f32 unk22C; 
    /* 0x0230 */ f32 unk230; 
    /* 0x0234 */ f32 unk234; 
    /* 0x0238 */ char unk238[0x4]; 
    /* 0x023C */ f32 unk23C; // read but not set? what 
    /* 0x0240 */ char unk240[0xAC]; 
    /* 0x02EC */ f32 unk2EC; 
    /* 0x02F0 */ f32 unk2F0; 
    /* 0x02F4 */ f32 unk2F4; 
    /* 0x02F8 */ LightNode* lightNode; 
    /* 0x02FC */ LightInfo lightInfo; 
    ///* 0x0300 */ char unk300[0xC]; 
    /* 0x030C */ ColliderCylinder collider; 
    /* 0x0358 */ char unk358[0x20C];
} EnPoSisters; // size = 0x398

extern const ActorInit En_Po_Sisters_InitVars;

#endif // Z_EN_PO_SISTERS_H
