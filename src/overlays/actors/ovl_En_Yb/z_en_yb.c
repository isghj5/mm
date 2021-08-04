#include "z_en_yb.h"

#define FLAGS 0x02000019

#define THIS ((EnYb*)thisx)

void EnYb_Init(Actor* thisx, GlobalContext* globalCtx);
void EnYb_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnYb_Update(Actor* thisx, GlobalContext* globalCtx);
void EnYb_Draw(Actor* thisx, GlobalContext* globalCtx);

#if 0
const ActorInit En_Yb_InitVars = {
    ACTOR_EN_YB,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_YB,
    sizeof(EnYb),
    (ActorFunc)EnYb_Init,
    (ActorFunc)EnYb_Destroy,
    (ActorFunc)EnYb_Update,
    (ActorFunc)EnYb_Draw,
};


// static ColliderCylinderInit sCylinderInit = {
static ColliderCylinderInit D_80BFB2B0 = {
    { COLTYPE_NONE, AT_NONE, AC_ON | AC_TYPE_ENEMY, OC1_ON | OC1_TYPE_ALL, OC2_TYPE_1, COLSHAPE_CYLINDER, },
    { ELEMTYPE_UNK0, { 0x00000000, 0x00, 0x00 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_ON, },
    { 20, 40, 0, { 0, 0, 0 } },
};


extern ColliderCylinderInit D_80BFB2B0;
#endif

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Yb_0x80BFA100/EnYb_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Yb_0x80BFA100/EnYb_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Yb_0x80BFA100/func_80BFA2FC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Yb_0x80BFA100/func_80BFA350.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Yb_0x80BFA100/func_80BFA444.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Yb_0x80BFA100/func_80BFA5CC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Yb_0x80BFA100/func_80BFA634.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Yb_0x80BFA100/func_80BFA67C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Yb_0x80BFA100/func_80BFA6E0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Yb_0x80BFA100/func_80BFA710.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Yb_0x80BFA100/func_80BFA730.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Yb_0x80BFA100/func_80BFA868.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Yb_0x80BFA100/func_80BFA91C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Yb_0x80BFA100/func_80BFA9D4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Yb_0x80BFA100/func_80BFAB4C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Yb_0x80BFA100/func_80BFABF0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Yb_0x80BFA100/func_80BFAC88.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Yb_0x80BFA100/func_80BFAE80.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Yb_0x80BFA100/EnYb_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Yb_0x80BFA100/func_80BFB074.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Yb_0x80BFA100/func_80BFB0E0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Yb_0x80BFA100/EnYb_Draw.asm")
