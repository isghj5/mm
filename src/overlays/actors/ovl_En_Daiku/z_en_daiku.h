#ifndef Z_EN_DAIKU_H
#define Z_EN_DAIKU_H

#include "global.h"
#include "objects/object_daiku/object_daiku.h"

struct EnDaiku;

typedef void (*EnDaikuActionFunc)(struct EnDaiku*, PlayState*);

#define ENDAIKU_GET_TYPE(thisx) ((thisx)->params & 0xFF);
#define ENDAIKU_GET_PATH_INDEX(thisx) (((thisx)->params >> 8) & 0xFF)
#define ENDAIKU_PATH_INDEX_NONE 0x3F

typedef enum {
    /* 0 */ DAIKU_TYPE_MAYOR_MEETING,
    /* 1 */ DAIKU_TYPE_1,
    /* 2 */ DAIKU_TYPE_2,
    /* 3 */ DAIKU_TYPE_WALKING
} EnDaikuType;

typedef struct EnDaiku {
    /* 0x000 */ Actor actor;
    /* 0x144 */ SkelAnime skelAnime;
    /* 0x188 */ Vec3s jointTable[OBJECT_DAIKU_LIMB_MAX];
    /* 0x1EE */ Vec3s morphTable[OBJECT_DAIKU_LIMB_MAX];
    /* 0x254 */ EnDaikuActionFunc actionFunc;
    /* 0x258 */ Path* path;
    /* 0x25C */ s16 pathPointIndex;
    /* 0x25E */ s16 unk_25E; // limb rotation based
    /* 0x260 */ s16 unk_260; // limb rotation based
    ///* 0x262 */ UNK_TYPE1 unk_262[0x2]; // unused
      /* 0x262 */ s8 randomChoice;
      /* 0x263 */ s8 randomThing2;
    /* 0x264 */ s16 unk_264; // limb rotation based
    /* 0x266 */ s16 unk_266; // limb rotation based
    /* 0x268 */ UNK_TYPE1 unk_268[0x4];
    /* 0x26C */ Vec3f pathNextPointPos;
    /* 0x278 */ s32 type;
    /* 0x27C */ s16 unusedTimer27C;
    /* 0x27E */ s16 mayorOfficeSkeletonUpdateTimer;
    /* 0x280 */ s16 unusedYaw280; // written but never read
    /* 0x282 */ s16 yawToNextPathPoint;
    /* 0x284 */ f32 animEndFrame;
    /* 0x288 */ s16 pathIndex;
    /* 0x28A */ s16 unusedBool28A;
    /* 0x28C */ s16 unk_28C;
    /* 0x28E */ UNK_TYPE1 unk_28E[0xE];
    /* 0x29C */ ColliderCylinder collider;
} EnDaiku; // size = 0x2E8

#endif // Z_EN_DAIKU_H
