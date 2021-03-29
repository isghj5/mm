#ifndef Z_EN_KAKASI_H
#define Z_EN_KAKASI_H

#include <global.h>

struct EnKakasi;

typedef void (*EnKakasiActionFunc)(struct EnKakasi*, GlobalContext*);

typedef struct EnKakasi {
    /* 0x000 */ Actor actor;
    ///* 0x144 */ char unk_144[0x15C];
    /* 0x144 */ u32* unk144; 
    /* 0x148 */ EnKakasiActionFunc actionFunc; // another function pointer?
    /* 0x14C */ SkelAnime skelanime;
    /* 0x190 */ s16 unk190;
    /* 0x192 */ s16 unk192; 
    /* 0x194 */ s16 unk194; 
    /* 0x196 */ u16 unk196; 
    /* 0x198 */ s16 unk198;
    /* 0x19A */ UNK_TYPE1 unk19A[0x6]; // padding
    /* 0x1A0 */ s32 unk1A0;
    /* 0x1A4 */ s32 unk1A4;
    /* 0x1A8 */ s32 unk1A8;
    /* 0x1AC */ s16 unk1AC;
    /* 0x1AE */ s16 unk1AE[3]; //cutscene index? next cutscene?
    ///* 0x1B0 */ s16 unk1B0; // padding
    ///* 0x1B2 */ s16 unk1B2; // padding
    /* 0x1B4 */ f32 unk1B4; 
    /* 0x1B8 */ f32 unk1B8;
    /* 0x1BC */ Vec3f unk1BC;
    /* 0x1C8 */ UNK_TYPE1 unk1C8[0x3C]; // padding
    /* 0x204 */ s16 unk204;
    /* 0x208 */ s16 unk206;
    /* 0x208 */ s16 unk208;// camera?
    /* 0x20A */ s16 unk20A;//padd
    /* 0x20C */ f32 unk20C;
    /* 0x210 */ f32 unk210;//padd
    /* 0x214 */ Vec3f unk214;
    /* 0x220 */ Vec3f unk220; //func_80970740
    /* 0x22C */ Vec3f unk22C; //actor home copied to here
    /* 0x238 */ Vec3f unk238;
    /* 0x244 */ Vec3f unk244;
    /* 0x250 */ f32 unk250;
    /* 0x254 */ ColliderCylinder* collider; // collision init

} EnKakasi; // size = 0x2A0

extern const ActorInit En_Kakasi_InitVars;

extern u32 D_06000214;
extern u32 D_060065B0;

#endif // Z_EN_KAKASI_H
