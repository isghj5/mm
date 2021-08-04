#include "z_en_mushi2.h"

#define FLAGS 0x00000010

#define THIS ((EnMushi2*)thisx)

void EnMushi2_Init(Actor* thisx, GlobalContext* globalCtx);
void EnMushi2_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnMushi2_Update(Actor* thisx, GlobalContext* globalCtx);
void EnMushi2_Draw(Actor* thisx, GlobalContext* globalCtx);

#if 0
const ActorInit En_Mushi2_InitVars = {
    ACTOR_EN_MUSHI2,
    ACTORCAT_ITEMACTION,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(EnMushi2),
    (ActorFunc)EnMushi2_Init,
    (ActorFunc)EnMushi2_Destroy,
    (ActorFunc)EnMushi2_Update,
    (ActorFunc)EnMushi2_Draw,
};


// static ColliderJntSphElementInit sJntSphElementsInit[1] = {
static ColliderJntSphElementInit D_80A6B950[1] = {
    {
        { ELEMTYPE_UNK0, { 0x00000000, 0x00, 0x00 }, { 0x00000000, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_NONE, OCELEM_ON, },
        { 0, { { 0, 0, 0 }, 5 }, 100 },
    },
};

// static ColliderJntSphInit sJntSphInit = {
static ColliderJntSphInit D_80A6B974 = {
    { COLTYPE_NONE, AT_NONE, AC_NONE, OC1_ON | OC1_TYPE_PLAYER | OC1_TYPE_1, OC2_TYPE_1, COLSHAPE_JNTSPH, },
    1, D_80A6B950, // sJntSphElementsInit,
};


// static InitChainEntry sInitChain[] = {
static InitChainEntry D_80A6BA04[] = {
    ICHAIN_VEC3F_DIV1000(scale, 10, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneForward, 700, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneScale, 20, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneDownward, 20, ICHAIN_STOP),
};


extern ColliderJntSphElementInit D_80A6B950[1];
extern ColliderJntSphInit D_80A6B974;
extern InitChainEntry D_80A6BA04[];
#endif

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Mushi2_0x80A687A0/func_80A687A0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Mushi2_0x80A687A0/func_80A68808.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Mushi2_0x80A687A0/func_80A68860.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Mushi2_0x80A687A0/func_80A68910.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Mushi2_0x80A687A0/func_80A68A78.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Mushi2_0x80A687A0/func_80A68B3C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Mushi2_0x80A687A0/func_80A68B6C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Mushi2_0x80A687A0/func_80A68BA0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Mushi2_0x80A687A0/func_80A68BC8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Mushi2_0x80A687A0/func_80A68C5C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Mushi2_0x80A687A0/func_80A68CE4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Mushi2_0x80A687A0/func_80A68DD4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Mushi2_0x80A687A0/func_80A68ED8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Mushi2_0x80A687A0/func_80A68F24.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Mushi2_0x80A687A0/func_80A68F9C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Mushi2_0x80A687A0/func_80A690C4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Mushi2_0x80A687A0/func_80A691EC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Mushi2_0x80A687A0/func_80A69388.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Mushi2_0x80A687A0/func_80A69424.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Mushi2_0x80A687A0/func_80A69468.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Mushi2_0x80A687A0/func_80A6958C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Mushi2_0x80A687A0/func_80A6969C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Mushi2_0x80A687A0/func_80A697C4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Mushi2_0x80A687A0/func_80A699E4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Mushi2_0x80A687A0/func_80A69AA8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Mushi2_0x80A687A0/func_80A69ADC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Mushi2_0x80A687A0/func_80A69CE0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Mushi2_0x80A687A0/func_80A69D3C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Mushi2_0x80A687A0/func_80A69EE4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Mushi2_0x80A687A0/func_80A69F5C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Mushi2_0x80A687A0/func_80A6A024.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Mushi2_0x80A687A0/func_80A6A058.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Mushi2_0x80A687A0/func_80A6A094.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Mushi2_0x80A687A0/func_80A6A0D8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Mushi2_0x80A687A0/EnMushi2_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Mushi2_0x80A687A0/EnMushi2_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Mushi2_0x80A687A0/func_80A6A300.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Mushi2_0x80A687A0/func_80A6A36C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Mushi2_0x80A687A0/func_80A6A508.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Mushi2_0x80A687A0/func_80A6A5C0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Mushi2_0x80A687A0/func_80A6A794.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Mushi2_0x80A687A0/func_80A6A824.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Mushi2_0x80A687A0/func_80A6A984.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Mushi2_0x80A687A0/func_80A6A9E4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Mushi2_0x80A687A0/func_80A6AAA4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Mushi2_0x80A687A0/func_80A6AB08.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Mushi2_0x80A687A0/func_80A6AE14.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Mushi2_0x80A687A0/func_80A6AE7C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Mushi2_0x80A687A0/func_80A6B078.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Mushi2_0x80A687A0/func_80A6B0D8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Mushi2_0x80A687A0/EnMushi2_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Mushi2_0x80A687A0/EnMushi2_Draw.asm")
