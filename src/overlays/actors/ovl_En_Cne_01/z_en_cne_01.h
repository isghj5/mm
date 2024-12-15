#ifndef Z_EN_CNE_01_H
#define Z_EN_CNE_01_H

#include "z_en_hy_code.h"

struct EnCne01;

typedef void (*EnCne01ActionFunc)(struct EnCne01*, PlayState*);

#define ENCNE01_GET_PATH_INDEX(thisx) (((thisx)->params & 0x7E00) >> 9)

#define ENCNE01_PATH_INDEX_NONE 0x3F

typedef struct EnCne01 {
    /* 0x000 */ EnHy enHy;
    /* 0x3EC */ UNK_TYPE1 unk_3EC[0x230];
} EnCne01; // size = 0x61C

#endif // Z_EN_CNE_01_H
