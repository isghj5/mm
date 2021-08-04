#include "z_en_pm.h"

#define FLAGS 0x00000039

#define THIS ((EnPm*)thisx)

void EnPm_Init(Actor* thisx, GlobalContext* globalCtx);
void EnPm_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnPm_Update(Actor* thisx, GlobalContext* globalCtx);
void EnPm_Draw(Actor* thisx, GlobalContext* globalCtx);

#if 0
const ActorInit En_Pm_InitVars = {
    ACTOR_EN_PM,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_MM,
    sizeof(EnPm),
    (ActorFunc)EnPm_Init,
    (ActorFunc)EnPm_Destroy,
    (ActorFunc)EnPm_Update,
    (ActorFunc)EnPm_Draw,
};


// static ColliderCylinderInit sCylinderInit = {
static ColliderCylinderInit D_80AFB790 = {
    { COLTYPE_HIT1, AT_NONE, AC_NONE, OC1_ON | OC1_TYPE_ALL, OC2_TYPE_1, COLSHAPE_CYLINDER, },
    { ELEMTYPE_UNK1, { 0x00000000, 0x00, 0x00 }, { 0x00000000, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_NONE, OCELEM_ON, },
    { 14, 62, 0, { 0, 0, 0 } },
};


// static ColliderSphereInit sSphereInit = {
static ColliderSphereInit D_80AFB7BC = {
    { COLTYPE_NONE, AT_NONE, AC_NONE, OC1_ON | OC1_TYPE_ALL, OC2_TYPE_1, COLSHAPE_SPHERE, },
    { ELEMTYPE_UNK0, { 0x00000000, 0x00, 0x00 }, { 0x00000000, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_NONE, OCELEM_ON, },
    { 0, { { 0, 0, 0 }, 26 }, 100 },
};


// sColChkInfoInit
static CollisionCheckInfoInit2 D_80AFB7E8 = { 0, 0, 0, 0, MASS_IMMOVABLE };


extern ColliderCylinderInit D_80AFB790;
extern ColliderSphereInit D_80AFB7BC;
extern CollisionCheckInfoInit2 D_80AFB7E8;
#endif

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Pm_0x80AF7B40/func_80AF7B40.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Pm_0x80AF7B40/func_80AF7BAC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Pm_0x80AF7B40/func_80AF7CB0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Pm_0x80AF7B40/func_80AF7D60.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Pm_0x80AF7B40/func_80AF7DC4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Pm_0x80AF7B40/func_80AF7E6C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Pm_0x80AF7B40/func_80AF7E98.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Pm_0x80AF7B40/func_80AF7F68.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Pm_0x80AF7B40/func_80AF8040.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Pm_0x80AF7B40/func_80AF80F4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Pm_0x80AF7B40/func_80AF8170.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Pm_0x80AF7B40/func_80AF81E8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Pm_0x80AF7B40/func_80AF8348.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Pm_0x80AF7B40/func_80AF8478.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Pm_0x80AF7B40/func_80AF8540.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Pm_0x80AF7B40/func_80AF86F0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Pm_0x80AF7B40/func_80AF87C4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Pm_0x80AF7B40/func_80AF8890.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Pm_0x80AF7B40/func_80AF898C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Pm_0x80AF7B40/func_80AF8AC8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Pm_0x80AF7B40/func_80AF8BA8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Pm_0x80AF7B40/func_80AF8C68.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Pm_0x80AF7B40/func_80AF8D84.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Pm_0x80AF7B40/func_80AF8DD4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Pm_0x80AF7B40/func_80AF8ED4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Pm_0x80AF7B40/func_80AF9008.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Pm_0x80AF7B40/func_80AF91E8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Pm_0x80AF7B40/func_80AF94AC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Pm_0x80AF7B40/func_80AF95E8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Pm_0x80AF7B40/func_80AF98A0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Pm_0x80AF7B40/func_80AF992C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Pm_0x80AF7B40/func_80AF9A0C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Pm_0x80AF7B40/func_80AF9AB0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Pm_0x80AF7B40/func_80AF9B54.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Pm_0x80AF7B40/func_80AF9BF8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Pm_0x80AF7B40/func_80AF9D04.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Pm_0x80AF7B40/func_80AF9E7C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Pm_0x80AF7B40/func_80AFA170.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Pm_0x80AF7B40/func_80AFA334.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Pm_0x80AF7B40/func_80AFA438.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Pm_0x80AF7B40/func_80AFA4D0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Pm_0x80AF7B40/func_80AFA5FC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Pm_0x80AF7B40/func_80AFA724.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Pm_0x80AF7B40/EnPm_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Pm_0x80AF7B40/EnPm_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Pm_0x80AF7B40/EnPm_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Pm_0x80AF7B40/func_80AFAA04.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Pm_0x80AF7B40/func_80AFAA44.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Pm_0x80AF7B40/func_80AFABAC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Pm_0x80AF7B40/EnPm_Draw.asm")
