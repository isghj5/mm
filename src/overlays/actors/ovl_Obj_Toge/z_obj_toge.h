#ifndef Z_OBJ_TOGE_H
#define Z_OBJ_TOGE_H

#include "global.h"

struct ObjToge;

typedef void (*ObjTogeActionFunc)(struct ObjToge*, PlayState*);

// Actor params bitfields:
//   bits 0-7:   Path index from play->setupPathList (0xFF = no path, kills itself)
//   bits 8-10:  Speed index (0-7), selects target speed from D_809A4CDC[]
//   bits 11-13: Delay index (0-7), selects delay in frames from D_809A4CFC[]
//   bit 14:     Variant flag: 0 = sliding, 1 = stationary hitbox zone
//   bit 15:     Unknown
#define OBJTOGE_GET_PATH_INDEX(thisx) ((thisx)->params & 0xFF)
#define OBJTOGE_GET_SPEED(thisx) (((thisx)->params >> 8) & 7)
#define OBJTOGE_GET_DELAY(thisx) (((thisx)->params >> 0xB) & 7)
#define OBJTOGE_GET_4000(thisx) (((thisx)->params >> 0xE) & 1)

#define OBJTOGE_PATH_INDEX_NONE 0xFF

typedef struct ObjToge {
    /* 0x000 */ Actor actor;
    /* 0x144 */ ColliderCylinder collider;
    /* 0x190 */ ObjTogeActionFunc actionFunc;
    /* 0x194 */ s32 pathPointTarget; // Which path endpoint to move toward: 0 or 1. Flips on wall hit or angle deviation.
    /* 0x198 */ Vec3f pathPoints[2]; // The two path endpoints. unk_198[0] is the starting position, unk_198[1] is the target.
    /* 0x1B0 */ s16 spinRot; // Accumulated rotation for the spinning blade visual effect. Maxes at 0x1770.
    /* 0x1B2 */ s16 delayTimer; // Countdown before the trap starts moving. Starts at D_809A4CFC[params bits 11-13].
    /* 0x1B4 */ u8 unk_1B4; // true if this is the hitbox variant (OBJTOGE_GET_4000 == 1). false for sliding variant.
    /* 0x1B8 */ f32 unk_1B8; // Center X of the rectangular damage zone (midpoint of the two path endpoints).
    /* 0x1BC */ f32 unk_1BC; // Center Z of the rectangular damage zone.
    /* 0x1C0 */ f32 unk_1C0; // Half-width of the damage zone in the rotated X axis. = home.rot.z * 7.5f.
    /* 0x1C4 */ f32 unk_1C4; // Half-width of the damage zone in the rotated Z axis. = half the distance between endpoints.
    /* 0x1C8 */ f32 unk_1C8; // Cosine of the yaw angle between the two path endpoints. Used for point-in-rectangle test.
    /* 0x1CC */ f32 unk_1CC; // Sine of the yaw angle between the two path endpoints. Used for point-in-rectangle test.
} ObjToge; // size = 0x1D0

#endif // Z_OBJ_TOGE_H
