#include "z_en_nimotsu.h"

#define FLAGS 0x00000010

#define THIS ((EnNimotsu*)thisx)

void EnNimotsu_Init(Actor* thisx, GlobalContext* globalCtx);
void EnNimotsu_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnNimotsu_Update(Actor* thisx, GlobalContext* globalCtx);
void EnNimotsu_Draw(Actor* thisx, GlobalContext* globalCtx);

#if 0
const ActorInit En_Nimotsu_InitVars = {
    ACTOR_EN_NIMOTSU,
    ACTORCAT_PROP,
    FLAGS,
    OBJECT_BOJ,
    sizeof(EnNimotsu),
    (ActorFunc)EnNimotsu_Init,
    (ActorFunc)EnNimotsu_Destroy,
    (ActorFunc)EnNimotsu_Update,
    (ActorFunc)EnNimotsu_Draw,
};


// static ColliderCylinderInit sCylinderInit = {
static ColliderCylinderInit D_80BE1FB0 = {
    { COLTYPE_NONE, AT_NONE, AC_NONE, OC1_ON | OC1_TYPE_ALL, OC2_TYPE_2, COLSHAPE_CYLINDER, },
    { ELEMTYPE_UNK4, { 0x00000000, 0x00, 0x00 }, { 0x00000000, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_NONE, OCELEM_ON, },
    { 10, 30, 0, { 0, 0, 0 } },
};


extern ColliderCylinderInit D_80BE1FB0;
#endif

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Nimotsu_0x80BE1C80/func_80BE1C80.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Nimotsu_0x80BE1C80/EnNimotsu_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Nimotsu_0x80BE1C80/EnNimotsu_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Nimotsu_0x80BE1C80/EnNimotsu_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Nimotsu_0x80BE1C80/EnNimotsu_Draw.asm")
