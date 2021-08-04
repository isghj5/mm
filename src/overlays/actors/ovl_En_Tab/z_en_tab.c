#include "z_en_tab.h"

#define FLAGS 0x00000039

#define THIS ((EnTab*)thisx)

void EnTab_Init(Actor* thisx, GlobalContext* globalCtx);
void EnTab_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnTab_Update(Actor* thisx, GlobalContext* globalCtx);
void EnTab_Draw(Actor* thisx, GlobalContext* globalCtx);

#if 0
const ActorInit En_Tab_InitVars = {
    ACTOR_EN_TAB,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_TAB,
    sizeof(EnTab),
    (ActorFunc)EnTab_Init,
    (ActorFunc)EnTab_Destroy,
    (ActorFunc)EnTab_Update,
    (ActorFunc)EnTab_Draw,
};


// static ColliderCylinderInit sCylinderInit = {
static ColliderCylinderInit D_80BE1A98 = {
    { COLTYPE_HIT1, AT_NONE, AC_NONE, OC1_ON | OC1_TYPE_ALL, OC2_TYPE_1, COLSHAPE_CYLINDER, },
    { ELEMTYPE_UNK1, { 0x00000000, 0x00, 0x00 }, { 0x00000000, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_NONE, OCELEM_ON, },
    { 14, 62, 0, { 0, 0, 0 } },
};


// sColChkInfoInit
static CollisionCheckInfoInit2 D_80BE1AC4 = { 0, 0, 0, 0, MASS_IMMOVABLE };


extern ColliderCylinderInit D_80BE1A98;
extern CollisionCheckInfoInit2 D_80BE1AC4;
#endif

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Tab_0x80BE04E0/func_80BE04E0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Tab_0x80BE04E0/func_80BE0590.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Tab_0x80BE04E0/func_80BE05BC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Tab_0x80BE04E0/func_80BE0620.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Tab_0x80BE04E0/func_80BE0664.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Tab_0x80BE04E0/func_80BE06DC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Tab_0x80BE04E0/func_80BE0778.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Tab_0x80BE04E0/func_80BE07A0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Tab_0x80BE04E0/func_80BE09A8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Tab_0x80BE04E0/func_80BE0A98.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Tab_0x80BE04E0/func_80BE0C04.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Tab_0x80BE04E0/func_80BE0D38.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Tab_0x80BE04E0/func_80BE0D60.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Tab_0x80BE04E0/func_80BE0E04.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Tab_0x80BE04E0/func_80BE0F04.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Tab_0x80BE04E0/func_80BE0FC4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Tab_0x80BE04E0/func_80BE1060.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Tab_0x80BE04E0/func_80BE10BC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Tab_0x80BE04E0/func_80BE1224.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Tab_0x80BE04E0/func_80BE127C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Tab_0x80BE04E0/func_80BE1348.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Tab_0x80BE04E0/EnTab_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Tab_0x80BE04E0/EnTab_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Tab_0x80BE04E0/EnTab_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Tab_0x80BE04E0/func_80BE1648.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Tab_0x80BE04E0/func_80BE16B4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Tab_0x80BE04E0/func_80BE1704.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Tab_0x80BE04E0/EnTab_Draw.asm")
