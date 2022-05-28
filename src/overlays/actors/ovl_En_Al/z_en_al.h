#ifndef Z_EN_AL_H
#define Z_EN_AL_H

#include "global.h"

struct EnAl;

typedef void (*EnAlActionFunc)(struct EnAl*, GlobalContext*);
typedef s32 (*EnAlUnkFunc)(struct EnAl*, GlobalContext*);
typedef void (*EnAlUnkFunc2)(struct EnAl*, GlobalContext*);

typedef struct EnAl {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ SkelAnime skelAnime;
    /* 0x0188 */ EnAlActionFunc actionFunc;
    /* 0x018C */ EnAlUnkFunc2 unkFuncPtr;
    /* 0x0190 */ MtxF limbMatrixes[6];
    /* 0x0310 */ ColliderCylinder unk_310;
    /* 0x035C */ u8 lastScheduleResult;
    /* 0x0360 */ s32* dataArrayPtr; // points at our data, but what is it doing? gets passed to unk function out of actor
    /* 0x0364 */ s32 unk_364;
    /* 0x0368 */ Actor* actorPtr; // can be gorman or toto, or postman, actor talking to?
    /* 0x036C */ Vec3f unk_36C;
    /* 0x0378 */ Vec3s limb16Rot;
    /* 0x037E */ Vec3s jointTable[27];
    /* 0x0420 */ Vec3s morphTable[27];
    /* 0x04C2 */ u16 flags;
    /* 0x04C4 */ u16 lastTextId;
    /* 0x04C8 */ f32 animationSpeed;
    /* 0x04CC */ UNK_TYPE1 unk4CC[8];
    /* 0x04D4 */ f32 unk_4D4; // gets passed to a function that expects a radius... but what kind
    /* 0x04D8 */ UNK_TYPE1 unk4D8[4];
    /* 0x04DC */ s16 unk_4DC; // pitch rot?
    /* 0x04DE */ s16 unk_4DE; // yaw rot?
    /* 0x04E0 */ s16 unk_4E0; // based on a register and daySpeed..?
    /* 0x04E2 */ s16 stateTimer; // func_80BDEE5C
    /* 0x04E4 */ s16 unk_4E4;
    /* 0x04E6 */ s16 unk_4E6;
    /* 0x04E8 */ s16 unk_4E8;
    /* 0x04EA */ s16 unk_4EA;
    /* 0x04EC */ EnAlUnkFunc unk_4EC;
    /* 0x04F0 */ s32 unk_4F0;
    /* 0x04F4 */ s32 unk_4F4;
    /* 0x04F8 */ s32 animationId;
    /* 0x04FC */ UNK_TYPE1 unk4FC[4];
} EnAl; // size = 0x500

extern const ActorInit En_Al_InitVars;

#endif // Z_EN_AL_H
