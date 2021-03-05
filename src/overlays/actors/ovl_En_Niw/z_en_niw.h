#ifndef Z_EN_NIW_H
#define Z_EN_NIW_H

#include <global.h>

struct EnNiw;

typedef void (*EnNiwActionFunc)(struct EnNiw*, GlobalContext*);

typedef struct EnNiw {
    /* 0x000 */ Actor actor;
    ///* 0x144 */ char unk_144[0x678];
    /* 0x144 */ SkelAnime skelanime;
    /* 0x188 */ Vec3s limbDrawTbl[0x10];
    /* 0x1E8 */ Vec3s transitionDrawtable[0x10]; //16 in oot
    
    /* 0x248 */ EnNiwActionFunc* actionFunc;
    /* 0x24C */ u16 unk24C;// used in func_808922D0
    /* 0x250 */ u16 unk250;
    /* 0x252 */ u16 unk252;
    /* 0x254 */ u16 unk254;
    /* 0x256 */ u16 unk256;
    /* 0x258 */ s16 unk258;
    /* 0x25A */ s16 unk25A;
    /* 0x25C */ s16 unk25C;
    /* 0x25E */ s16 unk25E;
    /* 0x260 */ s16 unk260;
    /* 0x262 */ s16 unk262;
    /* 0x264 */ f32 unk264; // used in func_808922D0
    /* 0x268 */ f32 unk268; // used in func_808922D0
    /* 0x26C */ f32 unk26C; // used in func_808922D0
    /* 0x278 */ f32 unk278; // used in func_808922D0
    /* 0x27C */ f32 unk27C; // used in func_808922D0
    /* 0x280 */ f32 unk280; // used in func_808922D0
    /* 0x280 */ f32 unk284; // used in func_808922D0
    /* 0x28C */ s16 unk28C; // used in EnNiw_Update
    /* 0x28E */ u16 unk28E;
    /* 0x290 */ s16 unk290;
    /* 0x292 */ u16 unk292[0x5];
    /* 0x2A2 */ s16 paramsCopy;
    /* 0x2A4 */ Vec3f unk2A4; // this actors starting position
    /* 0x2B0 */ Vec3f unk2B0;// this actors starting position
    /* 0x2BC */ Vec3f unk2BC; // init
    /* 0x2C8 */ u16 unk2C8[10];
    /* 0x2E8 */ s16 unk2E8;
    /* 0x2EC */ u16 unk2EC[0x8];
    /* 0x308 */ f32 unk308; // init 10f
    /* 0x30C */ s16 unk30C; //unused?
    /* 0x310 */ ColCylinder collider;
} EnNiw; // size = 0x7BC

extern const ActorInit En_Niw_InitVars;

extern SkeletonHeader D_6002530;
extern AnimationHeader D_60000E8;

extern f32 D_80893500;
extern f32 D_80893504;
extern f32 D_80893508;

#endif // Z_EN_NIW_H
