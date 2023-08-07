#ifndef Z_EN_FG_H
#define Z_EN_FG_H

#include "global.h"

struct EnFg;

typedef void (*EnFgActionFunc)(struct EnFg*, PlayState*);

// Based on the envColor data. Related to params but mostly unused.
typedef enum {
    /* 0 */ FG_YELLOW,
    /* 1 */ FG_CYAN,
    /* 2 */ FG_PINK,
    /* 3 */ FG_BLUE,
    /* 4 */ FG_WHITE,
    /* 5 */ FG_BLACK // All frogs are blackened when hit by an explosion
} FrogType;

typedef enum {
    /* 0 */ FG_DMGEFFECT_NONE,
    /* 1 */ FG_DMGEFFECT_EXPLOSION, // Bomb or bombchu, not powderkeg
    /* 2 */ FG_DMGEFFECT_DEKUSTICK,
    /* 3 */ FG_DMGEFFECT_HOOKSHOT,
    /* 4 */ FG_DMGEFFECT_ARROW,
    /* 5 */ FG_DMGEFFECT_ICEARROW
} FrogDamageEffect;

typedef struct {
    /* 0x00 */ u8 type;
    /* 0x01 */ u8 timer;
    /* 0x04 */ f32 xyScale;
    /* 0x08 */ UNK_TYPE1 unk_08[0xC];
    /* 0x14 */ Vec3f pos;
    /* 0x20 */ Vec3f unk_20; // Likely acceleration, set to 0 but unused
    /* 0x2C */ Vec3f velocity;
    /* 0x38 */ UNK_TYPE1 unk_38[0x4];
} EnFgEffectDust; // size = 0x3C

typedef struct EnFg {
    /* 0x000 */ Actor actor;
    /* 0x144 */ EnFgActionFunc actionFunc;
    /* 0x148 */ SkelAnime skelAnime;
    /* 0x18C */ ColliderCylinder collider;
    /* 0x1D8 */ Vec3s jointTable[24];
    /* 0x268 */ Vec3s morphTable[24];
    /* 0x2F8 */ s16 timer;
    /* 0x2FA */ s16 bounceCounter;
    /* 0x2FC */ EnFgEffectDust dustEffect[10];
} EnFg; // size = 0x554

#endif // Z_EN_FG_H
