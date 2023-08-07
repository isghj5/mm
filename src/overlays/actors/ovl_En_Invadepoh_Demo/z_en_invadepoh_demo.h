#ifndef Z_EN_INVADEPOH_DEMO_H
#define Z_EN_INVADEPOH_DEMO_H

#include "global.h"

struct EnInvadepohDemo;

typedef void (*EnInvadepohDemoActionFunc)(struct EnInvadepohDemo*, PlayState*);

typedef struct EnInvadepohDemo {
    /* 0x000 */ Actor actor;
    /* 0x144 */ EnInvadepohDemoActionFunc actionFunc;
    /* 0x148 */ char unk_148[0x180];
} EnInvadepohDemo; // size = 0x2C8

#endif // Z_EN_INVADEPOH_DEMO_H
