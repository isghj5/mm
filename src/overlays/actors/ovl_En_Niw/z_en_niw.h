#ifndef Z_EN_NIW_H
#define Z_EN_NIW_H

#include <global.h>

struct EnNiw;

typedef void (*EnNiwActionFunc)(struct EnNiw*, GlobalContext*);

typedef struct {
    /* 0x0000 */ u8 type;
    /* 0x0004 */ Vec3f pos;
    /* 0x0010 */ Vec3f vel;
    /* 0x001C */ Vec3f accel;
    /* 0x0028 */ s16 life;
    /* 0x002A */ s16 unk_2A;
    /* 0x002C */ f32 scale;
    /* 0x0030 */ f32 unk_30;
    /* 0x0034 */ u8 timer;
} EnNiwFeather; // size = 0x0038

typedef struct EnNiw {
    /* 0x000 */ Actor actor;
    ///* 0x144 */ char unk_144[0x678];
    /* 0x144 */ SkelAnime skelanime;
    /* 0x188 */ Vec3s limbDrawTbl[0x10];
    /* 0x1E8 */ Vec3s transitionDrawtable[0x10];
    /* 0x248 */ EnNiwActionFunc* actionFunc;

    /* 0x24C */ u16 unk24C;// used in func_808922D0
    /* 0x24E */ u16 unk24E; // pad
    /* 0x250 */ s16 unk250;
    /* 0x252 */ s16 unk252;// used by func_80892248
    /* 0x254 */ s16 unk254; // changed in func_808917F8 unsure
    /* 0x256 */ u16 unk256; //sfxtimer?
    /* 0x258 */ s16 unk258;
    /* 0x25A */ s16 unk25A;
    /* 0x25C */ s16 unk25C;
    /* 0x25E */ s16 unk25E;
    /* 0x260 */ s16 unk260;
    /* 0x262 */ s16 unk262;
    /* 0x264 */ f32 unk264; // used in func_808922D0
    /* 0x268 */ f32 unk268; // used in func_808922D0
    /* 0x26C */ f32 unk26C; // used in func_808922D0
    /* 0x270 */ u8  unk279[0x8]; // pad
    /* 0x278 */ f32 unk278; // used in func_808922D0
    /* 0x27C */ f32 unk27C; // used in func_808922D0
    /* 0x280 */ f32 unk280; // used in func_808922D0
    /* 0x284 */ f32 unk284; // used in func_808922D0
    /* 0x288 */ u8  unk288[0x4]; // pad
    /* 0x28C */ s16 unk28C; // used in EnNiw_Update
    /* 0x28E */ u16 unk28E;
    /* 0x290 */ s16 unk290;
    /* 0x292 */ u8  unk292[0x8]; // pad
    /* 0x29C */ s16 unk29A; // changed by func_808917F8
    /* 0x29C */ u16 unk29C; // changed by func_80892248
    /* 0x29E */ s16 unk29E; // func_80891D78 
    /* 0x2A0 */ u16 unk2A0; // pad
    /* 0x2A2 */ s16 paramsCopy;
    /* 0x2A4 */ Vec3f unk2A4; // this actors starting position
    /* 0x2B0 */ Vec3f unk2B0;// this actors starting position
    /* 0x2BC */ Vec3f unk2BC; // init
    /* 0x2C8 */ u8  unk2C8[0x20]; // pad
    /* 0x2E8 */ s16 unk2E8;
    /* 0x2EA */ u16 unk2EA; // pad
    /* 0x2EC */ u16 unk2EC; // used in func_80891D78 
    /* 0x2EE */ u8  unk2EE[0x12]; // pad
    /* 0x300 */ f32 unk300; // used func_808917F8
    /* 0x304 */ f32 unk304; 
    /* 0x308 */ f32 unk308; // init 10f
    /* 0x30C */ s16 unk30C; //unused?
    /* 0x310 */ ColCylinder collider;
    /* 0x35C */ EnNiwFeather feathers[0x14];

} EnNiw; // size = 0x7BC

extern const ActorInit En_Niw_InitVars;

extern SkeletonHeader D_6002530;
extern AnimationHeader D_60000E8;

extern f32 D_80893500;
extern f32 D_80893504;
extern f32 D_80893508;

extern f32 D_8089354C;

extern f32 D_80893490; // used by func_808917F8

extern f32 D_80893564; //used by func_808922D0
extern f32 D_80893568; //used by func_808922D0

extern f32 D_80893584; //used in func_808930FC
extern f32 D_80893580;
extern f32 D_80893588;

extern f32 D_80893558;
extern f32 D_8089355C;
extern f32 D_80893560;

#endif // Z_EN_NIW_H
