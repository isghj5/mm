#ifndef Z_EN_BU_H
#define Z_EN_BU_H

#include "global.h"
  #include "objects/object_box/object_box.h"


struct EnBu;

typedef void (*EnBuActionFunc)(struct EnBu*, GlobalContext*);

#define MIMIC_FLAGS(this) ((this)->dyna.actor.home.rot.z)

typedef enum {
  /* 0 */ MIMIC_FLAG_CLEAR,
  /* 1 */ MIMIC_FLAG_PREVIOUSLY_NOTICED, // attention grabbed no longer asleep
  /* 2 */ MIMIC_FLAG_PREVIOUSLY_LAUGHED,


} MimicFlags;

typedef struct EnBu {
    /* 0x000 */ DynaPolyActor dyna;
    /* 0x144 */ EnBuActionFunc actionFunc;
                SkelAnime skelAnime;
                Vec3s jointTable[OBJECT_BOX_CHEST_LIMB_MAX];
                Vec3s morphTable[OBJECT_BOX_CHEST_LIMB_MAX];
                ColliderCylinder collider;
                s16 stateTimer;
                s8 alpha;

} EnBu; // size = 0x???

extern const ActorInit En_Bu_InitVars;

#endif // Z_EN_BU_H
