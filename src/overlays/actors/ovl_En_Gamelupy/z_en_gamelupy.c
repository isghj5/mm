#include "z_en_gamelupy.h"

#define FLAGS 0x00000010

#define THIS ((EnGamelupy*)thisx)

void EnGamelupy_Init(Actor* thisx, GlobalContext* globalCtx);
void EnGamelupy_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnGamelupy_Update(Actor* thisx, GlobalContext* globalCtx);
void EnGamelupy_Draw(Actor* thisx, GlobalContext* globalCtx);

#if 0
const ActorInit En_Gamelupy_InitVars = {
    ACTOR_EN_GAMELUPY,
    ACTORCAT_PROP,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(EnGamelupy),
    (ActorFunc)EnGamelupy_Init,
    (ActorFunc)EnGamelupy_Destroy,
    (ActorFunc)EnGamelupy_Update,
    (ActorFunc)EnGamelupy_Draw,
};


// static ColliderCylinderInit sCylinderInit = {
static ColliderCylinderInit D_80AF6CF0 = {
    { COLTYPE_NONE, AT_NONE, AC_NONE, OC1_ON | OC1_NO_PUSH | OC1_TYPE_PLAYER, OC2_TYPE_2, COLSHAPE_CYLINDER, },
    { ELEMTYPE_UNK4, { 0x00000000, 0x00, 0x00 }, { 0x00000000, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_NONE, OCELEM_ON, },
    { 10, 30, 0, { 0, 0, 0 } },
};


extern ColliderCylinderInit D_80AF6CF0;
#endif

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Gamelupy_0x80AF6760/EnGamelupy_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Gamelupy_0x80AF6760/EnGamelupy_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Gamelupy_0x80AF6760/func_80AF6854.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Gamelupy_0x80AF6760/func_80AF6944.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Gamelupy_0x80AF6760/func_80AF6958.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Gamelupy_0x80AF6760/func_80AF6994.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Gamelupy_0x80AF6760/func_80AF69A8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Gamelupy_0x80AF6760/func_80AF6A38.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Gamelupy_0x80AF6760/func_80AF6A78.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Gamelupy_0x80AF6760/func_80AF6B40.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Gamelupy_0x80AF6760/EnGamelupy_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Gamelupy_0x80AF6760/EnGamelupy_Draw.asm")
