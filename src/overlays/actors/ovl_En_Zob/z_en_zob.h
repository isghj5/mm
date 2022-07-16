#ifndef Z_EN_ZOB_H
#define Z_EN_ZOB_H

#include "global.h"
#include "objects/object_zob/object_zob.h"

struct EnZob;

typedef void (*EnZobActionFunc)(struct EnZob*, PlayState*);

#define ENZOB_GET_TYPE(thisx) ((thisx)->params & 0xF)

enum {
    /* 0x1 */ ZOB_TYPE_1 = 1, // on stage in hall
    /* 0x2 */ ZOB_TYPE_2, // playing bass in mikau's healing cutscene
    /* 0xF */ ZOB_TYPE_F = 0xF, // in his room
} ZobType;

typedef struct EnZob {
    /* 0x000 */ Actor actor;
    /* 0x144 */ SkelAnime skelAnime;
    /* 0x188 */ Vec3s jointTable[24];
    /* 0x218 */ Vec3s morphTable[24];
    /* 0x2A8 */ ColliderCylinder collider;
    /* 0x2F4 */ u16 unk_2F4; // flaaaaags but of course
    /* 0x2F6 */ Vec3s unk_2F6;
    /* 0x2FC */ Vec3s unk_2FC;
    /* 0x302 */ s16 curAnimationIndex;
    /* 0x304 */ u16 unk_304; // related to next animation?
    /* 0x306 */ s16 unk_306[4];
    /* 0x30E */ s16 unk_30E;
    /* 0x310 */ s16 unk_310;
    /* 0x312 */ s16 unk_312;
    /* 0x314 */ EnZobActionFunc actionFunc;
} EnZob; // size = 0x318

extern const ActorInit En_Zob_InitVars;

#endif // Z_EN_ZOB_H
