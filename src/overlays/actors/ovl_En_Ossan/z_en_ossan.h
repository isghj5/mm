#ifndef Z_EN_OSSAN_H
#define Z_EN_OSSAN_H

#include <global.h>

#include "overlays/actors/ovl_En_GirlA/z_en_girla.h"

struct EnOssan;

typedef void (*EnOssanActionFunc)(struct EnOssan*, GlobalContext*);
typedef void (*EnOssanBlinkFunc)(struct EnOssan*);

typedef struct EnOssan {
    /* 0x000 */ Actor actor;
    /* 0x144 */ SkelAnime skelAnime;
    /* 0x188 */ EnOssanActionFunc actionFunc;
    /* 0x18C */ EnOssanActionFunc tmpActionFunc; // Used to restore back to correct browsing function
    /* 0x190 */ ColliderCylinder collider;
    /* 0x1DC */ s16 delayTimer;
    /* 0x1DE */ s8 objIndex;
    /* 0x1E0 */ s16 eyeTexIndex;
    /* 0x1E2 */ s16 blinkTimer;
    /* 0x1E4 */ EnOssanBlinkFunc blinkFunc;
    /* 0x1E8 */ EnGirlA* items[8];
    /* 0x208 */ s32 stickAccumX;
    /* 0x20C */ s32 stickAccumY;
    /* 0x210 */ u8 moveHorizontal;
    /* 0x211 */ u8 moveVertical;
    /* 0x214 */ f32 cursorX;
    /* 0x218 */ f32 cursorY;
    /* 0x21C */ f32 cursorZ;
    /* 0x220 */ u32 cursorColorR;
    /* 0x224 */ u32 cursorColorG;
    /* 0x228 */ u32 cursorColorB;
    /* 0x22C */ u32 cursorColorA;
    /* 0x230 */ f32 cursorAnimTween;
    /* 0x234 */ u8 cursorAnimState;
    /* 0x235 */ u8 drawCursor;
    /* 0x236 */ u8 cursorIdx;
    /* 0x238 */ StickDirectionPrompt stickLeftPrompt;
    /* 0x270 */ StickDirectionPrompt stickRightPrompt;
    /* 0x2A8 */ f32 arrowAnimTween;
    /* 0x2AC */ f32 stickAnimTween;
    /* 0x2B0 */ u8 arrowAnimState;
    /* 0x2B1 */ u8 stickAnimState;
    /* 0x2B4 */ f32 shopItemSelectedTween;
    /* 0x2B8 */ s16 lookToShopkeeperCutscene;
    /* 0x2BA */ s16 lookToLeftShelfCutscene;
    /* 0x2BC */ s16 lookToRightShelfCutscene;
    /* 0x2BE */ s16 lookToShopKeeperFromShelfCutscene;
    /* 0x2C0 */ s16 cutscene;
    /* 0x2C2 */ s16 cutsceneState;
    /* 0x2C4 */ u16 textId;
    /* 0x2C6 */ Vec3s headRot;
    /* 0x2CC */ Vec3s unk2CC; // Set but never used
    /* 0x2D2 */ s16 limbRotTableY[19];
    /* 0x2F8 */ s16 limbRotTableZ[19];
    /* 0x31E */ Vec3s limbDrawTbl[19];
    /* 0x390 */ Vec3s transitionDrawTbl[19];
    /* 0x402 */ s16 animationIdx;
    /* 0x404 */ Vec3s headRotPartTimeWorker;
    /* 0x40A */ u16 flags;
} EnOssan; // size = 0x40C

/* Note: 
* Items on shelves are indexed as:
* 7 5  3 1
* 6 4  2 0 
*/    

typedef enum {
    /* 0 */ ENOSSAN_CURIOSITY_SHOP_MAN,
    /* 1 */ ENOSSAN_PART_TIME_WORKER
} EnOssanWorker;

typedef enum {
    /* 0 */ ENOSSAN_CUTSCENESTATE_STOPPED,
    /* 1 */ ENOSSAN_CUTSCENESTATE_WAITING,
    /* 2 */ ENOSSAN_CUTSCENESTATE_PLAYING
} EnOssanCutsceneState;

extern const ActorInit En_Ossan_InitVars;

#endif // Z_EN_OSSAN_H
