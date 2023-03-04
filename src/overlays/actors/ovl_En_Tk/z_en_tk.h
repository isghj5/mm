#ifndef Z_EN_TK_H
#define Z_EN_TK_H

#include "global.h"
#include "objects/object_tk/object_tk.h"
#include "overlays/actors/ovl_En_Bigpo/z_en_bigpo.h"

struct EnTk;

typedef void (*EnTkActionFunc)(struct EnTk*, PlayState*);
typedef void (*EnTkWalkingFunc)(struct EnTk*, PlayState*);

#define DAMPE_GET_TYPE(thisx) ((thisx)->params & 0xF)
#define DAMPE_GET_SWITCH_FLAGS(thisx) (((thisx)->params >> 4) & 0x7F)
#define DAMPE_GET_PATH_INDEX(thisx) ((((thisx)->params >> 0xB) & 0x1F) & 0xFF)

typedef enum {
  /* 0 */ DAMPE_TYPE_DIG_GAME_NPC,
  /* 1 */ DAMPE_TYPE_RUNNING, // after bigpo, cutscene run away
  /* 2 */ DAMPE_TYPE_HIDING, // after bigpo, hiding under bed
  /* 3 */ DAMPE_TYPE_DIG_GAME_SPOT,
  /* 4 */ DAMPE_TYPE_OUTSIDE_NPC,
} DampeType;

#define TKFLAGS1_UNK_00 0
#define TKFLAGS1_UNK_01 (1 << 0)
#define TKFLAGS1_UNK_02 (1 << 1)
#define TKFLAGS1_UNK_04 (1 << 2)
#define TKFLAGS1_UNK_08 (1 << 3)
#define TKFLAGS1_UNK_10 (1 << 4)
#define TKFLAGS1_UNK_20 (1 << 5)
#define TKFLAGS1_UNK_40 (1 << 6)
#define TKFLAGS1_UNK_80 (1 << 7)

// used during big po dig minigame?
#define TKFLAGS2_UNK_00  0
#define TKFLAGS2_RIDING_ELEVATOR  (1 << 0)
#define TKFLAGS2_UNK_02   (1 << 1)
#define TKFLAGS2_UNK_04   (1 << 2)
#define TKFLAGS2_UNK_08   (1 << 3)
#define TKFLAGS2_UNK_10   (1 << 4)
#define TKFLAGS2_UNK_20   (1 << 5)
#define TKFLAGS2_UNK_40   (1 << 6)
#define TKFLAGS2_UNK_80   (1 << 7)
#define TKFLAGS2_UNK_100  (1 << 8)
#define TKFLAGS2_STOPPED  (1 << 9)
#define TKFLAGS2_UNK_400  (1 << 10)
#define TKFLAGS2_UNK_800  (1 << 11)
#define TKFLAGS2_UNK_1000 (1 << 12)
#define TKFLAGS2_UNK_2000 (1 << 13)
#define TKFLAGS2_UNK_4000 (1 << 14)
#define TKFLAGS2_UNK_8000 (1 << 15)

// state of dampe digging
typedef enum {
  /* 0 */ DAMPE_DIG_GAME_STATE_IDLE,
  /* 1 */ DAMPE_DIG_GAME_STATE_WALKING,
  /* 2 */ DAMPE_DIG_GAME_STATE_FOUND_DIG_SPOT,
  /* 3 */ DAMPE_DIG_GAME_STATE_FOUND_FLAME,
  /* 4 */ DAMPE_DIG_GAME_STATE_FOUND_NOTHING,
} DampeDigGameState;

// state of dampe moving during the game
typedef enum {
  /* -1 */ DAMPE_DIG_GAME_MOVING_STATE_PRE = -1, // default before the game starts
  /*  0 */ DAMPE_DIG_GAME_MOVING_STATE_STANDING = 0,
  /*  1 */ DAMPE_DIG_GAME_MOVING_STATE_FOLLOWING,
  /*  2 */ DAMPE_DIG_GAME_MOVING_STATE_LOST,
  /*  3 */ DAMPE_DIG_GAME_MOVING_STATE_RIDING_ELEVATOR,
} DampeDigGameMovingState;

typedef struct EnTk {
    /* 0x000 */ Actor actor;
    /* 0x144 */ SkelAnime skelAnime;
    /* 0x188 */ EnTkActionFunc actionFunc;
    /* 0x18C */ ColliderCylinder collider;
    /* 0x1D8 */ Vec3s jointTable[DAMPE_LIMB_MAX];
    /* 0x244 */ Vec3s morphTable[DAMPE_LIMB_MAX];
    /* 0x2B0 */ s8 type;
    /* 0x2B1 */ s8 switchFlag;
    /* 0x2B4 */ Vec3f unk_2B4;
    /* 0x2C0 */ s16 unk_2C0; // second eye state thing
    /* 0x2C2 */ s16 eyeState;
    /* 0x2C4 */ s16 blinkTimer;
    /* 0x2C6 */ s16 unk_2C6; // index for 2C8
    /* 0x2C8 */ UNK_TYPE1 unk2C8[0x2];
    /* 0x2CA */ u16 tkFlags2;
    /* 0x2CC */ s16 unk_2CC;
    /* 0x2D0 */ s32 digGameMovingState;
    /* 0x2D4 */ s32 animIndex;
    /* 0x2D8 */ f32 unk_2D8;
    /* 0x2DC */ f32 unk_2DC;
    /* 0x2E0 */ s32 unk_2E0;
    /* 0x2E4 */ s16 bigpoFlameFoundCount;
    /* 0x2E6 */ u16 textId;
    /* 0x2E8 */ s16 bigpoRunCutsceneTimer;
    /* 0x2EC */ Vec3f unk_2EC;
    /* 0x2F8 */ Vec3s unk_2F8;
    /* 0x300 */ Vec3f unk_300; // pos of something
    /* 0x30C */ EnTkWalkingFunc followActionFunc; // Dig for bigpo minigame
    /* 0x310 */ s16 digGameState;
    /* 0x312 */ s16 cutscenes[2];
    /* 0x316 */ s16 unk_316; // might be shiver timer
    /* 0x318 */ s16 unk_318; // set to zero, set to spin, draws right before skeleton??
    /* 0x31A */ s16 skullRotZ;
    /* 0x31C */ s16 skullRotY;
    /* 0x320 */ f32 curAnimFrame;
    /* 0x324 */ Vec3f unk_324[6];
    /* 0x36C */ s32 unk_36C;
    /* 0x370 */ UNK_TYPE1 unk370[0x58];
    /* 0x3C8 */ Path* timePath;
    /* 0x3CC */ u8 scheduleResult;
    /* 0x3CE */ u16 tkFlags;
    /* 0x3D0 */ s32 timePathTimeSpeed;
    /* 0x3D4 */ Vec3f timePathTargetPos;
    /* 0x3E0 */ f32 timePathProgress;
    /* 0x3E4 */ s32 timePathTotalTime;
    /* 0x3E8 */ s32 timePathWaypointTime;
    /* 0x3EC */ s32 timePathWaypoint;
    /* 0x3F0 */ s32 timePathElapsedTime;
} EnTk; // size = 0x3F4

#endif // Z_EN_TK_H
