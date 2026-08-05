#ifndef Z_EN_CNE_01_H
#define Z_EN_CNE_01_H

#include "global.h"
#include "z_en_hy_code.h"
#include "assets/objects/object_cne/object_cne.h"

struct EnCne01;

typedef void (*EnCne01ActionFunc)(struct EnCne01*, PlayState*);

#define ENCNE01_GET_PATH_INDEX(thisx) (((thisx)->params & 0x7E00) >> 9)
#define ENCNE01_PATH_INDEX_NONE 0x3F

typedef enum {
    CNE_TYPE_VENESA = 0,
    CNE_TYPE_ORANGE = 1
} EncCneTypes;

typedef struct EnCne01 {
    /* 0x000 */ Actor actor;
    /* 0x144 */ EnCne01ActionFunc actionFunc;
    /* 0x148 */ EnCne01ActionFunc prevActionFunc;
    /* 0x14C */ ColliderCylinder collider;
    /* 0x198 */ SkelAnime skelAnime;
    /* 0x1D8 */ s16 limbRotTableY[HYLIAN_YOUNG_WOMAN_LIMB_MAX];
    /* 0x1F8 */ s16 limbRotTableZ[HYLIAN_YOUNG_WOMAN_LIMB_MAX];
    /* 0x218 */ Vec3s jointTable[HYLIAN_YOUNG_WOMAN_LIMB_MAX];
    /* 0x278 */ Vec3s morphTable[HYLIAN_YOUNG_WOMAN_LIMB_MAX];
    /* 0x2D8 */ Vec3f bodyPartsPos[HYLIAN_YOUNG_WOMAN_LIMB_MAX];
    /* 0x394 */ Vec3s trackTarget;
    /* 0x39A */ Vec3s headRot;
    /* 0x3A0 */ Vec3s torsoRot;
    ///* 0x3A6 */ Path* path;
    /* 0x3AA */ s16 inMsgState3;
    /* 0x3AC */ s16 headObjIndex;
    /* 0x3AE */ s16 textId;
    /* 0x3B0 */ s16 stateFlags;
    /* 0x3B2 */ s16 dialogueTimer;
    /* 0x3B4 */ Actor* moonPtr;
    /* 0x3B8 */ AnimationHeader* defaultAnim;
    /* 0x3BC */ AnimationHeader* curAnim;
    ///* 0x3C0 */ UNK_TYPE1 unk_3C0[0x25C];
} EnCne01; // size = 0x61C

#endif // Z_EN_CNE_01_H
