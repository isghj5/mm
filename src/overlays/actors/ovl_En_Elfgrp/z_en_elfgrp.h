#ifndef Z_EN_ELFGRP_H
#define Z_EN_ELFGRP_H

#include "global.h"

struct EnElfgrp;

typedef void (*EnElfgrpActionFunc)(struct EnElfgrp*, PlayState*);

#define ENELFGRP_GET(thisx) ((thisx)->params & 0xF)
#define ENELFGRP_GET_FE00(thisx) (((thisx)->params & 0xFE00) >> 9)

typedef enum {
    /* 0 */ ENELFGRP_0,
    /* 2 */ ENELFGRP_1,
    /* 2 */ ENELFGRP_2,
    /* 3 */ ENELFGRP_3,
    /* 4 */ ENELFGRP_4
} EnElfgrpParam;

typedef struct EnElfgrp {
    /* 0x000 */ Actor actor;
    /* 0x144 */ s16 unk_144;
    /* 0x146 */ u8 unk_146;
    /* 0x147 */ u8 unk_147;
    /* 0x148 */ s8 unk_148;
    /* 0x14A */ u16 unk_14A;
    /* 0x14C */ EnElfgrpActionFunc actionFunc;
} EnElfgrp; // size = 0x150

#endif // Z_EN_ELFGRP_H
