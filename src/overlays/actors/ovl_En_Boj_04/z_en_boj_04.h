#ifndef Z_EN_BOJ_04_H
#define Z_EN_BOJ_04_H

#include "global.h"

struct EnBoj04;

#define GROTTO_SPAWNER_OBJ_ID(thisx) thisx->home.rot.x

typedef struct EnBoj04 {
    /* 0x000 */ Actor actor;
    ///* 0x144 */ u16 objectId
} EnBoj04;

#endif // Z_EN_BOJ_04_H
