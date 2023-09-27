#ifndef Z_EN_GOROIWA_H
#define Z_EN_GOROIWA_H

#include "global.h"

struct EnGoroiwa;

typedef void (*EnGoroiwaActionFunc)(struct EnGoroiwa*, PlayState*);
typedef s32 (*EnGoroiwaUnkFunc)(struct EnGoroiwa*);

#define ENGOROIWA_GET_COLOR(thisx) (((thisx)->params >> 0xE) & 3)
#define ENGOROIWA_GET_3000(thisx) (((thisx)->params >> 0xC) & 3)
#define ENGOROIWA_GET_400(thisx) (((thisx)->params >> 0xA) & 1)
#define ENGOROIWA_GET_LOOPMODE(thisx) (((thisx)->params >> 0x8) & 3)
#define ENGOROIWA_GET_PATH(thisx) ((thisx)->params & 0xFF)

#define ENGOROIWA_GET_ROT_Y(thisx) ((thisx)->home.rot.y)
// TODO add X back into this name
#define ENGOROIWA_GET_ROT_ROLLINGSFX_UPPER(this) ((this)->actor.home.rot.x) >> 1 & 3
#define ENGOROIWA_GET_ROT_ROLLINGSFX_LOWER(this) ((this)->actor.home.rot.x & 0x1)
#define ENGOROIWA_GET_ROT_Z_3(this) ((this)->actor.home.rot.z & 3)

typedef enum {
    /* 0 */ ENGOROIWA_LOOPMODE_ONEWAY,
    /* 1 */ ENGOROIWA_LOOPMODE_ONEWAY_BREAK,
    /* 3 */ ENGOROIWA_LOOPMODE_ROUNDTRIP = 3
} EnGoroiwaLoopMode;

typedef enum {
    /* 0 */ ENGOROIWA_400_0,
    /* 1 */ ENGOROIWA_400_1
} EnGoroiwaParam400;

typedef enum {
    /* 0 */ ENGOROIWA_3000_0,
    /* 1 */ ENGOROIWA_3000_1,
    /* 2 */ ENGOROIWA_3000_2
} EnGoroiwaParam3000;

typedef enum {
    /* 0 */ ENGOROIWA_COLOR_SILVERROCK, // unused in MM
    /* 1 */ ENGOROIWA_COLOR_REDROCK,
    /* 2 */ ENGOROIWA_COLOR_SNOWBALL
} EnGoroiwaColors;

// state flags
#define ENGOROIWA_STATE_INWATER 0x20

typedef struct {
    /* 0x00 */ Vec3f unk_00;
    /* 0x0C */ f32 unk_0C;
    /* 0x10 */ f32 unk_10;
    /* 0x14 */ f32 unk_14;
    /* 0x18 */ f32 unk_18;
    /* 0x1C */ s16 unk_1C;
    /* 0x1E */ s16 unk_1E;
    /* 0x20 */ s16 unk_20;
    /* 0x22 */ s16 unk_22;
    /* 0x24 */ s16 unk_24;
    /* 0x26 */ s16 unk_26;
    /* 0x28 */ CollisionPoly* unk_28;
    /* 0x2C */ u8 unk_2C;
    /* 0x2D */ u8 unk_2D;
} EnGoroiwaStruct; // size = 0x30

typedef struct EnGoroiwa {
    /* 0x000 */ Actor actor;
    /* 0x144 */ ColliderJntSph collider;
    /* 0x164 */ ColliderJntSphElement colliderElements[1];
    /* 0x1A4 */ EnGoroiwaActionFunc actionFunc;
    /* 0x1A8 */ Vec3f unk_1A8;
    /* 0x1B4 */ Vec3f unk_1B4;
    /* 0x1C0 */ f32 unk_1C0;
    /* 0x1C4 */ f32 rollRotSpeed;
    /* 0x1C8 */ s16 timer; // might be multi-user
    /* 0x1CA */ s16 bounceCount;
    /* 0x1CC */ s16 unk_1CC;
    /* 0x1CE */ s16 unk_1CE;
    /* 0x1D0 */ Vec3s* curPathPoints;
    /* 0x1D4 */ s16 endWaypoint;
    /* 0x1D6 */ s16 currentWaypoint;
    /* 0x1D8 */ s16 nextWaypoint;
    /* 0x1DA */ s16 pathDirection;
    /* 0x1DC */ f32 unk_1DC; // scale * 500ish
    /* 0x1E0 */ f32 unk_1E0;
    /* 0x1E4 */ s8 rollingSFXUpperIndex; // pulled from home.rot.x, the & 1 bit is pulled jit 
    // also updates speed
    /* 0x1E5 */ u8 stateFlags; // cpy from oot
    /* 0x1E6 */ s8 unk_1E6;
    /* 0x1E7 */ s8 unk_1E7;
    /* 0x1E8 */ EnGoroiwaStruct unk_1E8[2];
    /* 0x248 */ s32 effectIndex;
} EnGoroiwa; // size = 0x24C

#endif // Z_EN_GOROIWA_H
