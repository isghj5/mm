#include "z_bg_kin2_bombwall.h"

#define FLAGS 0x10000010

#define THIS ((BgKin2Bombwall*)thisx)

void BgKin2Bombwall_Init(Actor* thisx, GlobalContext* globalCtx);
void BgKin2Bombwall_Destroy(Actor* thisx, GlobalContext* globalCtx);
void BgKin2Bombwall_Update(Actor* thisx, GlobalContext* globalCtx);
void BgKin2Bombwall_Draw(Actor* thisx, GlobalContext* globalCtx);

#if 0
const ActorInit Bg_Kin2_Bombwall_InitVars = {
    ACTOR_BG_KIN2_BOMBWALL,
    ACTORCAT_BG,
    FLAGS,
    OBJECT_KIN2_OBJ,
    sizeof(BgKin2Bombwall),
    (ActorFunc)BgKin2Bombwall_Init,
    (ActorFunc)BgKin2Bombwall_Destroy,
    (ActorFunc)BgKin2Bombwall_Update,
    (ActorFunc)BgKin2Bombwall_Draw,
};


// static ColliderCylinderInit sCylinderInit = {
static ColliderCylinderInit D_80B6E6F0 = {
    { COLTYPE_NONE, AT_NONE, AC_ON | AC_TYPE_PLAYER, OC1_NONE, OC2_NONE, COLSHAPE_CYLINDER, },
    { ELEMTYPE_UNK0, { 0x00000000, 0x00, 0x00 }, { 0x00000008, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_NONE, },
    { 60, 60, 0, { 0, 0, 0 } },
};


// static InitChainEntry sInitChain[] = {
static InitChainEntry D_80B6E748[] = {
    ICHAIN_F32(uncullZoneForward, 4000, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneScale, 200, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneDownward, 300, ICHAIN_CONTINUE),
    ICHAIN_VEC3F_DIV1000(scale, 1000, ICHAIN_STOP),
};


extern ColliderCylinderInit D_80B6E6F0;
extern InitChainEntry D_80B6E748[];
#endif

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Kin2_Bombwall_0x80B6E020/func_80B6E020.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Kin2_Bombwall_0x80B6E020/func_80B6E090.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Kin2_Bombwall_0x80B6E020/BgKin2Bombwall_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Kin2_Bombwall_0x80B6E020/BgKin2Bombwall_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Kin2_Bombwall_0x80B6E020/func_80B6E4B8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Kin2_Bombwall_0x80B6E020/func_80B6E4CC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Kin2_Bombwall_0x80B6E020/func_80B6E544.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Kin2_Bombwall_0x80B6E020/func_80B6E558.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Kin2_Bombwall_0x80B6E020/func_80B6E5F8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Kin2_Bombwall_0x80B6E020/func_80B6E614.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Kin2_Bombwall_0x80B6E020/BgKin2Bombwall_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Kin2_Bombwall_0x80B6E020/BgKin2Bombwall_Draw.asm")
