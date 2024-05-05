#ifndef Z_EN_BOJ_04_H
#define Z_EN_BOJ_04_H

#include "global.h"

struct EnBoj04;

// no point in using an even bigger memory required
#define GROTTO_SPAWNER_OBJ_ID(thisx) thisx->home.rot.x
#define GROTTO_SPAWNER_GROTTO_DATA(thisx) thisx->home.rot.z

typedef struct EnBoj04 {
    /* 0x000 */ Actor actor;
} EnBoj04;

#endif // Z_EN_BOJ_04_H
