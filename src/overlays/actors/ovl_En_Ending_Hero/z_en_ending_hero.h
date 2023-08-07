#ifndef Z_EN_ENDING_HERO_H
#define Z_EN_ENDING_HERO_H

#include "global.h"

struct EnEndingHero;

typedef void (*EnEndingHeroActionFunc)(struct EnEndingHero*, PlayState*);

typedef struct EnEndingHero {
    /* 0x000 */ Actor actor;
    /* 0x144 */ SkelAnime skelAnime;
    /* 0x188 */ Vec3s jointTable[15];
    /* 0x1E2 */ Vec3s morphTable[15];
    /* 0x23C */ EnEndingHeroActionFunc actionFunc;
    /* 0x240 */ s16 unk240;
    /* 0x242 */ s16 unk242;
    /* 0x244 */ u16 unk244;
} EnEndingHero; // size = 0x248

#endif // Z_EN_ENDING_HERO_H
