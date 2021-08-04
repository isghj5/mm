#ifndef Z_EN_TORCH2_H
#define Z_EN_TORCH2_H

#include <global.h>

struct EnTorch2;

typedef struct EnTorch2 {
    /* 0x000 */ Actor actor;
    /* 0x144 */ ColliderCylinder collider;
    /* 0x190 */ u8 state;
    /* 0x191 */ u8 framesUntilNextState;
    /* 0x192 */ s16 alpha;
} EnTorch2; // size = 0x194

typedef enum {
    TORCH2_PARAM_HUMAN,
    TORCH2_PARAM_GORON,
    TORCH2_PARAM_ZORA,
    TORCH2_PARAM_DEKU,
    TORCH2_PARAM_FIERCE_DEITY,
} EnTorch2Param;

typedef enum {
    TORCH2_STATE_INITIALIZED,
    TORCH2_STATE_FADING_IN,
    TORCH2_STATE_SOLID,
    TORCH2_STATE_IDLE,
    TORCH2_STATE_DYING,
} EnTorch2State;

extern const ActorInit En_Torch2_InitVars;

#endif // Z_EN_TORCH2_H
