#ifndef Z_EN_TEST2_H
#define Z_EN_TEST2_H

#include "global.h"

struct EnTest2;

typedef struct EnTest2 {
    /* 0x000 */ Actor actor;
    /* 0x144 */ AnimatedMaterial* animMat;
} EnTest2; // size = 0x148

typedef enum {
    /* 0xB */ EN_TEST2_PARAMS_B = 0xB,
    /* 0xC */ EN_TEST2_PARAMS_C
} EnTest2_Params;

extern const ActorInit En_Test2_InitVars;

#endif // Z_EN_TEST2_H
