#include "z_en_gm.h"

#define FLAGS 0x00000019

#define THIS ((EnGm*)thisx)

void EnGm_Init(Actor* thisx, GlobalContext* globalCtx);
void EnGm_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnGm_Update(Actor* thisx, GlobalContext* globalCtx);
void EnGm_Draw(Actor* thisx, GlobalContext* globalCtx);

#if 0
const ActorInit En_Gm_InitVars = {
    ACTOR_EN_GM,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_IN2,
    sizeof(EnGm),
    (ActorFunc)EnGm_Init,
    (ActorFunc)EnGm_Destroy,
    (ActorFunc)EnGm_Update,
    (ActorFunc)EnGm_Draw,
};


// static ColliderCylinderInit sCylinderInit = {
static ColliderCylinderInit D_80951C5C = {
    { COLTYPE_HIT1, AT_NONE, AC_NONE, OC1_ON | OC1_TYPE_ALL, OC2_TYPE_1, COLSHAPE_CYLINDER, },
    { ELEMTYPE_UNK1, { 0x00000000, 0x00, 0x00 }, { 0x00000000, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_NONE, OCELEM_ON, },
    { 14, 62, 0, { 0, 0, 0 } },
};


// static ColliderSphereInit sSphereInit = {
static ColliderSphereInit D_80951C88 = {
    { COLTYPE_NONE, AT_NONE, AC_NONE, OC1_ON | OC1_TYPE_ALL, OC2_TYPE_1, COLSHAPE_SPHERE, },
    { ELEMTYPE_UNK0, { 0x00000000, 0x00, 0x00 }, { 0x00000000, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_NONE, OCELEM_ON, },
    { 0, { { 0, 0, 0 }, 20 }, 100 },
};


// sColChkInfoInit
static CollisionCheckInfoInit2 D_80951CB4 = { 0, 0, 0, 0, MASS_IMMOVABLE };


extern ColliderCylinderInit D_80951C5C;
extern ColliderSphereInit D_80951C88;
extern CollisionCheckInfoInit2 D_80951CB4;
#endif

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Gm_0x8094DEE0/func_8094DEE0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Gm_0x8094DEE0/func_8094DF90.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Gm_0x8094DEE0/func_8094DFF8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Gm_0x8094DEE0/func_8094E054.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Gm_0x8094DEE0/func_8094E0F8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Gm_0x8094DEE0/func_8094E1DC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Gm_0x8094DEE0/func_8094E278.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Gm_0x8094DEE0/func_8094E2D0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Gm_0x8094DEE0/func_8094E454.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Gm_0x8094DEE0/func_8094E4D0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Gm_0x8094DEE0/func_8094E52C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Gm_0x8094DEE0/func_8094E69C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Gm_0x8094DEE0/func_8094EA34.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Gm_0x8094DEE0/func_8094EB1C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Gm_0x8094DEE0/func_8094EDBC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Gm_0x8094DEE0/func_8094EE84.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Gm_0x8094DEE0/func_8094EFC4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Gm_0x8094DEE0/func_8094F074.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Gm_0x8094DEE0/func_8094F0E0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Gm_0x8094DEE0/func_8094F2E8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Gm_0x8094DEE0/func_8094F3D0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Gm_0x8094DEE0/func_8094F4EC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Gm_0x8094DEE0/func_8094F53C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Gm_0x8094DEE0/func_8094F7D0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Gm_0x8094DEE0/func_8094F904.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Gm_0x8094DEE0/func_8094FAC4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Gm_0x8094DEE0/func_8094FCC4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Gm_0x8094DEE0/func_8094FD88.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Gm_0x8094DEE0/func_8094FE10.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Gm_0x8094DEE0/func_8094FF04.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Gm_0x8094DEE0/func_80950088.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Gm_0x8094DEE0/func_80950120.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Gm_0x8094DEE0/func_809501B8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Gm_0x8094DEE0/func_80950280.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Gm_0x8094DEE0/func_80950388.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Gm_0x8094DEE0/func_809503F8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Gm_0x8094DEE0/func_80950490.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Gm_0x8094DEE0/func_80950690.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Gm_0x8094DEE0/func_80950804.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Gm_0x8094DEE0/func_8095097C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Gm_0x8094DEE0/func_80950C24.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Gm_0x8094DEE0/func_80950CDC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Gm_0x8094DEE0/func_80950DB8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Gm_0x8094DEE0/func_80950F2C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Gm_0x8094DEE0/EnGm_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Gm_0x8094DEE0/EnGm_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Gm_0x8094DEE0/EnGm_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Gm_0x8094DEE0/func_809513AC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Gm_0x8094DEE0/func_809514BC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Gm_0x8094DEE0/func_80951594.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Gm_0x8094DEE0/EnGm_Draw.asm")
