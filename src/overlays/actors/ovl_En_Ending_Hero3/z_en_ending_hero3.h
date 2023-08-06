#ifndef Z_EN_ENDING_HERO3_H
#define Z_EN_ENDING_HERO3_H

#include "global.h"

struct EnEndingHero3;

typedef void (*EnEndingHero3ActionFunc)(struct EnEndingHero3*, PlayState*);

typedef struct EnEndingHero3 {
    /* 0x000 */ Actor actor;
    /* 0x144 */ SkelAnime skelAnime;
    /* 0x188 */ Vec3s jointTable[17];
    /* 0x1EE */ Vec3s morphTable[17];
    /* 0x254 */ EnEndingHero3ActionFunc actionFunc;
    /* 0x258 */ u16 unk258;
} EnEndingHero3; // size = 0x25C

#endif // Z_EN_ENDING_HERO3_H
