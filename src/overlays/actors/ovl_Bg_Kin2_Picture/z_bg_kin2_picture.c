#include "z_bg_kin2_picture.h"

#define FLAGS 0x00000000

#define THIS ((BgKin2Picture*)thisx)

void BgKin2Picture_Init(Actor* thisx, GlobalContext* globalCtx);
void BgKin2Picture_Destroy(Actor* thisx, GlobalContext* globalCtx);
void BgKin2Picture_Update(Actor* thisx, GlobalContext* globalCtx);
void BgKin2Picture_Draw(Actor* thisx, GlobalContext* globalCtx);

#if 0
const ActorInit Bg_Kin2_Picture_InitVars = {
    ACTOR_BG_KIN2_PICTURE,
    ACTORCAT_PROP,
    FLAGS,
    OBJECT_KIN2_OBJ,
    sizeof(BgKin2Picture),
    (ActorFunc)BgKin2Picture_Init,
    (ActorFunc)BgKin2Picture_Destroy,
    (ActorFunc)BgKin2Picture_Update,
    (ActorFunc)BgKin2Picture_Draw,
};


// static ColliderTrisElementInit sTrisElementsInit[2] = {
static ColliderTrisElementInit D_80B6F990[2] = {
    {
        { ELEMTYPE_UNK4, { 0x00000000, 0x00, 0x00 }, { 0x000138B0, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_NONE, },
        { { { -20.0f, 53.29999923706055f, 9.0f }, { -20.0f, 3.0f, 9.0f }, { 20.0f, 3.0f, 9.0f } } },
    },
    {
        { ELEMTYPE_UNK4, { 0x00000000, 0x00, 0x00 }, { 0x000138B0, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_NONE, },
        { { { -20.0f, 53.29999923706055f, 9.0f }, { 20.0f, 3.0f, 9.0f }, { 20.0f, 53.29999923706055f, 9.0f } } },
    },
};

// static ColliderTrisInit sTrisInit = {
static ColliderTrisInit D_80B6FA08 = {
    { COLTYPE_NONE, AT_NONE, AC_ON | AC_TYPE_PLAYER, OC1_NONE, OC2_NONE, COLSHAPE_TRIS, },
    2, D_80B6F990, // sTrisElementsInit,
};


// static InitChainEntry sInitChain[] = {
static InitChainEntry D_80B6FA24[] = {
    ICHAIN_F32_DIV1000(gravity, -2000, ICHAIN_CONTINUE),
    ICHAIN_F32_DIV1000(minVelocityY, -20000, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneForward, 4000, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneScale, 100, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneDownward, 100, ICHAIN_CONTINUE),
    ICHAIN_VEC3F_DIV1000(scale, 100, ICHAIN_STOP),
};


extern ColliderTrisElementInit D_80B6F990[2];
extern ColliderTrisInit D_80B6FA08;
extern InitChainEntry D_80B6FA24[];
#endif

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Kin2_Picture_0x80B6EFA0/func_80B6EFA0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Kin2_Picture_0x80B6EFA0/func_80B6EFEC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Kin2_Picture_0x80B6EFA0/func_80B6F098.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Kin2_Picture_0x80B6EFA0/BgKin2Picture_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Kin2_Picture_0x80B6EFA0/BgKin2Picture_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Kin2_Picture_0x80B6EFA0/func_80B6F4C0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Kin2_Picture_0x80B6EFA0/func_80B6F4D4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Kin2_Picture_0x80B6EFA0/func_80B6F5A4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Kin2_Picture_0x80B6EFA0/func_80B6F5B8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Kin2_Picture_0x80B6EFA0/func_80B6F61C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Kin2_Picture_0x80B6EFA0/func_80B6F640.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Kin2_Picture_0x80B6EFA0/func_80B6F708.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Kin2_Picture_0x80B6EFA0/func_80B6F72C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Kin2_Picture_0x80B6EFA0/func_80B6F8F8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Kin2_Picture_0x80B6EFA0/func_80B6F90C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Kin2_Picture_0x80B6EFA0/BgKin2Picture_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Kin2_Picture_0x80B6EFA0/BgKin2Picture_Draw.asm")
