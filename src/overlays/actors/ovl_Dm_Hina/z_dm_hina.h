#ifndef Z_DM_HINA_H
#define Z_DM_HINA_H

#include "global.h"

struct DmHina;

typedef void (*DmHinaActionFunc)(struct DmHina*, PlayState*);

typedef struct DmHina {
    /* 0x000 */ Actor actor;
    /* 0x144 */ DmHinaActionFunc actionFunc;
    /* 0x148 */ char unk_148[0x10];
    /* 0x158 */ f32 unk_158;
    /* 0x15C */ f32 unk_15C;
    /* 0x160 */ char unk_160[0x24];
} DmHina; // size = 0x184

#endif // Z_DM_HINA_H
