#ifndef Z_EN_DEKUNUTS_H
#define Z_EN_DEKUNUTS_H

#include "global.h"
#include "objects/object_dekunuts/object_dekunuts.h"

struct EnDekunuts;

typedef void (*EnDekunutsActionFunc)(struct EnDekunuts*, PlayState*);

#define ENDEKUNUTS_GET_FF00(thisx) (((thisx)->params >> 8) & 0xFF);

// evasive leaves its dekuflower when it takes a hit and runs, shoots straight
//   evasive is never used in MM left over from OOT
// regular spits in an arc, takes one hit then dies

typedef enum MadscrubType {
    /* 0x0 */ MADSCRUB_TYPE_EVASIVE, // todo need better names for types
    /* 0x1 */ MADSCRUB_TYPE_PASSIVE, // watches you during butler race
    /* 0x2 */ MADSCRUB_TYPE_REGULAR,
    /* 0xFF*/ MADSCRUB_TYPE_FF = 0xFF, // only vanilla type
};

typedef enum MadscrubType2 {
    /* 0x0 */ MADSCRUB_TYPE2_0,
    /* 0x1 */ MADSCRUB_TYPE2_1,
    /* 0x2 */ MADSCRUB_TYPE2_2,
    /* 0xFF*/ MADSCRUB_TYPE2_FF = 0xFF, // only vanilla type
};

typedef struct EnDekunuts {
    /* 0x000 */ Actor actor;
    /* 0x144 */ SkelAnime skelAnime;
    /* 0x188 */ EnDekunutsActionFunc actionFunc;
    /* 0x18C */ u8 walkingSfxToggle;
    /* 0x18D */ u8 timer18D;
    /* 0x18E */ u8 drawDmgEffType;
    /* 0x190 */ s16 timer; // might be a union
    /* 0x192 */ s16 escapeDirection; // when running away from the player
    /* 0x194 */ s16 paramsUpperByte; // todo figure out
    /* 0x196 */ Vec3s jointTable[DEKU_SCRUB_LIMB_MAX];
    /* 0x1D2 */ Vec3s morphTable[DEKU_SCRUB_LIMB_MAX];
    /* 0x210 */ f32 drawDmgEffAlpha;
    /* 0x214 */ f32 drawDmgEffScale;
    /* 0x218 */ f32 drawDmgEffFrozenSteamScale;
    /* 0x21C */ Vec3f limbPos[8];
    /* 0x27C */ ColliderCylinder collider;
} EnDekunuts; // size = 0x2C8

#endif // Z_EN_DEKUNUTS_H
