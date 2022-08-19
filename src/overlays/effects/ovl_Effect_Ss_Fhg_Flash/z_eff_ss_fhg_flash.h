#ifndef _Z64_EFFECT_SS_FHG_FLASH_H_
#define _Z64_EFFECT_SS_FHG_FLASH_H_

#include "global.h"

typedef enum {
    /* 0x00 */ FHGFLASH_LIGHTBALL,
    /* 0x01 */ FHGFLASH_SHOCK
} FhgFlashType;

typedef enum {
    /* 0x00 */ FHGFLASH_LIGHTBALL_GREEN,
    /* 0x01 */ FHGFLASH_LIGHTBALL_LIGHTBLUE,
    /* 0x02 */ FHGFLASH_LIGHTBALL_RED,
    /* 0x03 */ FHGFLASH_LIGHTBALL_YELLOW,
    /* 0x04 */ FHGFLASH_LIGHTBALL_BLUE,
    /* 0x05 */ FHGFLASH_LIGHTBALL_PURPLE,
    /* 0x06 */ FHGFLASH_LIGHTBALL_ORANGE,
    /* 0x07 */ FHGFLASH_LIGHTBALL_WHITE1,
    /* 0x08 */ FHGFLASH_LIGHTBALL_WHITE2
} FhgFlashLightBallParam;

typedef enum {
    /* 0x00 */ FHGFLASH_SHOCK_NO_ACTOR,
    /* 0x01 */ FHGFLASH_SHOCK_PLAYER,
    /* 0x02 */ FHGFLASH_SHOCK_GOHT_2,
    /* 0x03 */ FHGFLASH_SHOCK_GOHT_3,
    /* 0x04 */ FHGFLASH_SHOCK_GOHT_4,
    /* 0x05 */ FHGFLASH_SHOCK_GOHT_5,
    /* 0x06 */ FHGFLASH_SHOCK_GOHT_6
} FhgFlashLightningParam;

typedef struct {
    /* 0x00 */ Vec3f pos;
    /* 0x0C */ Vec3f velocity;
    /* 0x18 */ Vec3f accel;
    /* 0x24 */ s16 scale;
    /* 0x26 */ u8 params;
    /* 0x28 */ Actor* actor;
    /* 0x2C */ u8 type;
} EffectSsFhgFlashInitParams; // size = 0x30

extern const EffectSsInit Effect_Ss_Fhg_Flash_InitVars;

#endif
