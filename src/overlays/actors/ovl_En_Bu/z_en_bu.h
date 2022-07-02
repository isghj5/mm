#ifndef Z_EN_BU_H
#define Z_EN_BU_H

#include "global.h"
  #include "objects/object_box/object_box.h"


struct EnBu;

typedef void (*EnBuActionFunc)(struct EnBu*, GlobalContext*);

typedef struct EnBu {
    /* 0x000 */ DynaPolyActor dyna;
    /* 0x144 */ EnBuActionFunc actionFunc;
                SkelAnime skelAnime;
                Vec3s jointTable[OBJECT_BOX_CHEST_LIMB_MAX];
                Vec3s morphTable[OBJECT_BOX_CHEST_LIMB_MAX];
                s8 status;

} EnBu; // size = 0x190

extern const ActorInit En_Bu_InitVars;

#endif // Z_EN_BU_H
