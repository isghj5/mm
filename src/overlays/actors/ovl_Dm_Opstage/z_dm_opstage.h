#ifndef Z_DM_OPSTAGE_H
#define Z_DM_OPSTAGE_H

#include "global.h"

#define DMOPSTAGE_GET_TYPE(thisx) (((thisx)->params & 0xF))
#define DMOPSTAGE_GET_SUPERTYPE(thisx) (((thisx)->params & 0xF0) >> 4)
#define DMOPSTAGE_GET_ACTORACTION(thisx) (((thisx)->params >> 8) & 0xFF)

struct DmOpstage;

typedef void (*DmOpstageActionFunc)(struct DmOpstage*, GlobalContext*);

// todo organize this
typedef struct DmOpstage {
    /* 0x000 */ DynaPolyActor dyna;
    ///* 0x15C */ UNK_TYPE1 pad_15C[0x44];
    /* 0x15C */ ColliderCylinder collider; // new, give real trees a real collider
    /* 0x1A8 */ DmOpstageActionFunc actionFunc;
    ///* 0x1A4 */ Vec3f pos;
    /* 0x1AC */ u8 type;
    /* 0x1AD */ u8 dropType;
} DmOpstage; // size = 0x1B0

typedef enum {
    /* 0 */ DMOPSTAGE_TYPE_FLOOR,
    /* 1 */ DMOPSTAGE_TYPE_ROOT_TREE,
    /* 2 */ DMOPSTAGE_TYPE_CUT_TREE,
    /* 3 */ DMOPSTAGE_TYPE_STRAIGHT_TREE,
} DmOpStageTypes;

typedef enum {
    /* 0 */ DMOPSTAGE_SUPERTYPE_NONE,
    /* 1 */ DMOPSTAGE_SUPERTYPE_NODROP, // collider only
    /* 2 */ DMOPSTAGE_SUPERTYPE_FAIRY,
    /* 3 */ DMOPSTAGE_SUPERTYPE_DROPTABLE,
} DmOpStageSuperTypes;

extern const ActorInit Dm_Opstage_InitVars;

#endif // Z_DM_OPSTAGE_H
