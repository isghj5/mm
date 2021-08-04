#include "z_bg_fire_wall.h"

#define FLAGS 0x00000000

#define THIS ((BgFireWall*)thisx)

void BgFireWall_Init(Actor* thisx, GlobalContext* globalCtx);
void BgFireWall_Destroy(Actor* thisx, GlobalContext* globalCtx);
void BgFireWall_Update(Actor* thisx, GlobalContext* globalCtx);

#if 0
const ActorInit Bg_Fire_Wall_InitVars = {
    ACTOR_BG_FIRE_WALL,
    ACTORCAT_BG,
    FLAGS,
    OBJECT_FWALL,
    sizeof(BgFireWall),
    (ActorFunc)BgFireWall_Init,
    (ActorFunc)BgFireWall_Destroy,
    (ActorFunc)BgFireWall_Update,
    (ActorFunc)NULL,
};


// static ColliderCylinderInit sCylinderInit = {
static ColliderCylinderInit D_809ACC60 = {
    { COLTYPE_NONE, AT_ON | AT_TYPE_ENEMY, AC_NONE, OC1_ON | OC1_TYPE_PLAYER, OC2_TYPE_2, COLSHAPE_CYLINDER, },
    { ELEMTYPE_UNK0, { 0x20000000, 0x01, 0x04 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_NONE, BUMP_NONE, OCELEM_ON, },
    { 34, 85, 0, { 0, 0, 0 } },
};


// sColChkInfoInit
static CollisionCheckInfoInit D_809ACC8C = { 1, 80, 100, MASS_IMMOVABLE };


extern ColliderCylinderInit D_809ACC60;
extern CollisionCheckInfoInit D_809ACC8C;
#endif

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Fire_Wall_0x809AC4B0/BgFireWall_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Fire_Wall_0x809AC4B0/BgFireWall_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Fire_Wall_0x809AC4B0/func_809AC5C0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Fire_Wall_0x809AC4B0/func_809AC638.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Fire_Wall_0x809AC4B0/func_809AC68C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Fire_Wall_0x809AC4B0/func_809AC6C0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Fire_Wall_0x809AC4B0/func_809AC760.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Fire_Wall_0x809AC4B0/func_809AC7F8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Fire_Wall_0x809AC4B0/func_809AC970.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Fire_Wall_0x809AC4B0/BgFireWall_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Fire_Wall_0x809AC4B0/func_809ACB28.asm")
