#ifndef Z_OBJ_PZLBLOCK_H
#define Z_OBJ_PZLBLOCK_H

#include "global.h"

struct ObjPzlblock;

typedef void (*ObjPzlblockActionFunc)(struct ObjPzlblock*, PlayState*);

#define OBJPZLBLOCK_GET_SWITCH_FLAG(thisx) ((thisx)->params & 0x7F)
#define OBJPZLBLOCK_GET_COLOR(thisx) (((thisx)->params >> 8) & 7)
#define OBJPZLBLOCK_GET_ALT_OBJ(thisx) (((thisx)->params >> 0xC) & 1)
#define OBJPZLBLOCK_GET_ROTZ(thisx) ((thisx)->home.rot.z & 0x7)
#define OBJPZLBLOCK_GET_ROTX(thisx) ((thisx)->home.rot.x & 0xF)

typedef struct ObjPzlblock {
    /* 0x000 */ DynaPolyActor dyna;
    /* 0x15C */ ObjPzlblockActionFunc actionFunc;
    /* 0x160 */ s32 updBgCheckInfoFlags;
    /* 0x164 */ f32* unk_164; // points at rotZ or rotX
    /* 0x168 */ f32 unk_168; // the old rotation at 164 with an added range?
    /* 0x16C */ s16 unk_16C;
    /* 0x16E */ s16 unk_16E[4];
    /* 0x176 */ s16 unk_176;
    /* 0x178 */ s16 unk_178;
    /* 0x17A */ s8 objectSlot;
} ObjPzlblock; // size = 0x17C

#endif // Z_OBJ_PZLBLOCK_H
