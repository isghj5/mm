#ifndef Z_EN_MA_YTS_H
#define Z_EN_MA_YTS_H

#include "global.h"
#include "objects/object_ma1/object_ma1.h"

struct EnMaYts;

typedef void (*EnMaYtsActionFunc)(struct EnMaYts*, PlayState*);

typedef struct EnMaYts {
    /* 0x000 */ Actor actor;
    /* 0x144 */ SkelAnime skelAnime;
    /* 0x188 */ EnMaYtsActionFunc actionFunc;
    /* 0x18C */ ColliderCylinder collider;
    /* 0x1D8 */ struct_800BD888_arg1 unk_1D8;
    ///* 0x200 */ s32 unk_200; // Set, but not used
    /* 0x204 */ Vec3s jointTable[ROMANI_LIMB_MAX];
    ///* 0x28E */ char unk_28E[0x6];
    /* 0x294 */ Vec3s morphTable[ROMANI_LIMB_MAX];
    ///* 0x31E */ char unk_31E[0x8];
    /* 0x31? */ u8 typeExt;
    /* 0x31? */ u8 randomTextIndex;
                //s16 curTextId; 
    /* 0x326 */ s16 blinkTimer;
    /* 0x328 */ s16 overrideEyeTexIndex; // If non-zero, then this index will be used instead of eyeTexIndex
    /* 0x32A */ s16 eyeTexIndex;
    /* 0x32C */ s16 unk_32C; // flag?
    /* 0x32E */ s16 mouthTexIndex;
    /* 0x330 */ s16 type;
    ///* 0x332 */ char unk_332[0x2];
    /* 0x334 */ s16 endCreditsFlag;
    /* 0x336 */ s16 hasBow;
    /* 0x338 */ u16 textId; // DUMB of course it had one
    /* 0x33A */ s16 watchdogTimer;
} EnMaYts; // size = 0x33C

extern const ActorInit En_Ma_Yts_InitVars;

// parse type? weird
#define EN_MA_YTS_PARSE_TYPE(actor) ((((actor)->params)&0xF000) >> 12)
#define EN_MA_YTS_PARAM(enMaYtsType) ((enMaYtsType) << 12)
#define EN_MA_YTS2_DIALOGUE_WATCHDOG(this) ((this)->watchdogTimer) 

typedef enum {
    /* 0 */ MA_YTS_TYPE_BARN,
    /* 1 */ MA_YTS_TYPE_SITTING,
    /* 2 */ MA_YTS_TYPE_SLEEPING,
    /* 3 */ MA_YTS_TYPE_ENDCREDITS,
    /* 4 */ MA_YTS_TYPE_SINGING // new
} EnMaYtsType;

// for some reason all vanilla types have 0xXXFF in their thing and the code doesnt use it
typedef enum {
    /*   0 */ MAYTS_EMPTY,
    /*   1 */ MAYTS_BOX,
    /*   2 */ MAYTS_2,
    /* 0xF */ MAYTS_VANILLA = 0xF
} EnMaYtsTypeExt;

#define EN_MA_YTS_TYPEEXT(actor) ((actor)->params & 0xF)

// unused week event reg settings we can use to detect already spoken to
#define ROMANI_SET_NEWEVENT gSaveContext.save.weekEventReg[21] |= 0x10
#define ROMANI_GET_NEWEVENT gSaveContext.save.weekEventReg[21] &= 0x10

/**
 * MA_YTS_TYPE_BARN: In the barn, accompanying Cremia. Cremia's actor will handle her dialogue if spoken to.
 * MA_YTS_TYPE_SITTING: Having dinner or looking after the ranch.
 * MA_YTS_TYPE_SLEEPING: Sleeping. Can be seen in the second night in her house if the player failed the alien invasion.
 * MA_YTS_TYPE_ENDCREDITS: Used in the end credits sequence.
 */

#endif // Z_EN_MA_YTS_H
