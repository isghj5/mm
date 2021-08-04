#include "z_en_tanron3.h"

#define FLAGS 0x00000035

#define THIS ((EnTanron3*)thisx)

void EnTanron3_Init(Actor* thisx, GlobalContext* globalCtx);
void EnTanron3_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnTanron3_Update(Actor* thisx, GlobalContext* globalCtx);
void EnTanron3_Draw(Actor* thisx, GlobalContext* globalCtx);

#if 0
const ActorInit En_Tanron3_InitVars = {
    ACTOR_EN_TANRON3,
    ACTORCAT_BOSS,
    FLAGS,
    OBJECT_BOSS03,
    sizeof(EnTanron3),
    (ActorFunc)EnTanron3_Init,
    (ActorFunc)EnTanron3_Destroy,
    (ActorFunc)EnTanron3_Update,
    (ActorFunc)EnTanron3_Draw,
};


// static ColliderCylinderInit sCylinderInit = {
static ColliderCylinderInit D_80BB9750 = {
    { COLTYPE_HIT3, AT_ON | AT_TYPE_ENEMY, AC_ON | AC_TYPE_PLAYER, OC1_ON | OC1_TYPE_ALL, OC2_TYPE_1, COLSHAPE_CYLINDER, },
    { ELEMTYPE_UNK3, { 0xF7CFFFFF, 0x00, 0x02 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_ON, },
    { 7, 10, -5, { 0, 0, 0 } },
};


extern ColliderCylinderInit D_80BB9750;
#endif

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Tanron3_0x80BB85A0/func_80BB85A0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Tanron3_0x80BB85A0/EnTanron3_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Tanron3_0x80BB85A0/EnTanron3_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Tanron3_0x80BB85A0/func_80BB87D4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Tanron3_0x80BB85A0/func_80BB897C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Tanron3_0x80BB85A0/func_80BB8A48.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Tanron3_0x80BB85A0/func_80BB91D4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Tanron3_0x80BB85A0/func_80BB9288.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Tanron3_0x80BB85A0/func_80BB9308.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Tanron3_0x80BB85A0/EnTanron3_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Tanron3_0x80BB85A0/func_80BB95FC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Tanron3_0x80BB85A0/EnTanron3_Draw.asm")
