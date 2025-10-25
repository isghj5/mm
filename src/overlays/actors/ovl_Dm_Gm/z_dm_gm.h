#ifndef Z_DM_GM_H
#define Z_DM_GM_H

#include "global.h"
#include "assets/objects/object_an1/object_an1.h"

struct DmGm;

typedef void (*DmGmActionFunc)(struct DmGm*, PlayState*);

#define DMGM_STATE_LOST_ATTENTION (1 << 0)
#define DMGM_STATE_FACE_TARGET    (1 << 1)

#define ENAN_STATE_8                (1 << 3) // path related
#define ENAN_STATE_REACHED_PATH_END (1 << 4)
#define ENAN_STATE_ENGAGED          (1 << 5)
#define ENAN_STATE_IGNORE_GRAVITY   (1 << 6)
#define ENAN_STATE_FACE_TARGET      (1 << 7)
#define ENAN_STATE_UPDATE_EYES      (1 << 8)
#define ENAN_STATE_LOST_ATTENTION   (1 << 9)
#define ENAN_STATE_TALKING          (1 << 10)
#define ENAN_STATE_DRAW_TRAY        (1 << 11)
#define ENAN_STATE_DRAW_UMBRELLA    (1 << 12)
#define ENAN_STATE_DRAW_BROOM       (1 << 13)
#define ENAN_STATE_DRAW_KAFEIS_MASK (1 << 14)
#define ENAN_STATE_DRAW_CHOPSTICKS  (1 << 15)


typedef struct DmGm {
    /* 0x000 */ Actor actor;
    /* 0x144 */ SkelAnime skelAnime;
    /* 0x188 */ DmGmActionFunc actionFunc;
    /* 0x18C */ Vec3f headComputedPos;
    /* 0x18C */ Vec3f torsoComputedPos;
    /* 0x1A4 */ Vec3s headComputedRot;
    /* 0x1A4 */ Vec3s torsoComputedRot;
    /* 0x1B0 */ Vec3s jointTable[ANJU1_LIMB_MAX];
    /* 0x22E */ Vec3s morphTable[ANJU1_LIMB_MAX];
    ///* 0x2AC */ s8 an4ObjectSlot;
    ///* 0x2AD */ s8 msmoObjectSlot;
    /* 0x2AE */ u16 stateFlags;
    /* 0x2B0 */ u8 cueId;
    // free realistate
    /* 0x2B4 */ Actor* lookAtActor;
    /* 0x2B8 */ s16 eyeTexIndex;
    /* 0x2B8 */ s16 mouthTexIndex;
    /* 0x2BA */ s16 eyeTimer;
    /* 0x2BC */ s16 loseAttentionTimer;
    /* 0x2BE */ s16 headRotZ;
    /* 0x2C0 */ s16 headRotY;
    /* 0x2C2 */ s16 torsoRotZ;
    /* 0x2C4 */ s16 torsoRotY;
    /* 0x2C8 */ s32 animIndex;
    /* 0x2CC */ s32 prevAnimIndex;
    /* 0x2D0 */ s32 isCutscenePlaying;
    /* 0x2D4 */ s32 didAnimChangeInCs;

    // pulled from EnAn as needed
    s16 savedFaceIndex;
    s16 faceIndex;
    s16 forceDraw; // does what? schedule override?
    ColliderCylinder collider;


} DmGm; // size = 0x2D8

#endif // Z_DM_GM_H
