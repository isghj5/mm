#include "z_en_ge1.h"

#define FLAGS 0x00000009

#define THIS ((EnGe1*)thisx)

void EnGe1_Init(Actor* thisx, GlobalContext* globalCtx);
void EnGe1_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnGe1_Update(Actor* thisx, GlobalContext* globalCtx);
void EnGe1_Draw(Actor* thisx, GlobalContext* globalCtx);

#if 0
const ActorInit En_Ge1_InitVars = {
    ACTOR_EN_GE1,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_GE1,
    sizeof(EnGe1),
    (ActorFunc)EnGe1_Init,
    (ActorFunc)EnGe1_Destroy,
    (ActorFunc)EnGe1_Update,
    (ActorFunc)EnGe1_Draw,
};


// static ColliderCylinderInit sCylinderInit = {
static ColliderCylinderInit D_809464D0 = {
    { COLTYPE_NONE, AT_NONE, AC_ON | AC_TYPE_ENEMY, OC1_ON | OC1_TYPE_ALL, OC2_TYPE_1, COLSHAPE_CYLINDER, },
    { ELEMTYPE_UNK0, { 0x00000000, 0x00, 0x00 }, { 0x01000202, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_ON, },
    { 20, 40, 0, { 0, 0, 0 } },
};


extern ColliderCylinderInit D_809464D0;
#endif

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ge1_0x80945650/EnGe1_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ge1_0x80945650/EnGe1_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ge1_0x80945650/func_809457EC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ge1_0x80945650/func_80945924.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ge1_0x80945650/func_80945A00.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ge1_0x80945650/func_80945A9C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ge1_0x80945650/func_80945B60.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ge1_0x80945650/func_80945C50.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ge1_0x80945650/func_80945CAC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ge1_0x80945650/func_80945CE4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ge1_0x80945650/EnGe1_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ge1_0x80945650/func_80946190.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ge1_0x80945650/func_80946238.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ge1_0x80945650/func_80946368.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ge1_0x80945650/EnGe1_Draw.asm")
