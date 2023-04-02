#ifndef Z_CUBE
#define Z_CUBE

#include "global.h"

struct CUBE;

typedef void (*CUBEActionFunc)(struct CUBE*, PlayState*);

typedef struct EnTagObj {
    /* 0x000 */ DynaPolyActor dyna;
    /* 0x15C */ CUBEActionFunc actionFunc;
    /* 0x160 */ s32 timer;
} CUBE; // size = 0x198

#endif // Z_CUBE
