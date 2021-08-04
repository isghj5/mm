#include "z_en_rz.h"

#define FLAGS 0x00000009

#define THIS ((EnRz*)thisx)

void EnRz_Init(Actor* thisx, GlobalContext* globalCtx);
void EnRz_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnRz_Update(Actor* thisx, GlobalContext* globalCtx);
void EnRz_Draw(Actor* thisx, GlobalContext* globalCtx);

#if 0
const ActorInit En_Rz_InitVars = {
    ACTOR_EN_RZ,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_RZ,
    sizeof(EnRz),
    (ActorFunc)EnRz_Init,
    (ActorFunc)EnRz_Destroy,
    (ActorFunc)EnRz_Update,
    (ActorFunc)EnRz_Draw,
};


// static ColliderCylinderInit sCylinderInit = {
static ColliderCylinderInit D_80BFCCF4 = {
    { COLTYPE_NONE, AT_NONE, AC_ON | AC_TYPE_ENEMY, OC1_ON | OC1_TYPE_ALL, OC2_TYPE_1, COLSHAPE_CYLINDER, },
    { ELEMTYPE_UNK0, { 0x00000000, 0x00, 0x00 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_ON, },
    { 20, 40, 0, { 0, 0, 0 } },
};


extern ColliderCylinderInit D_80BFCCF4;
#endif

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Rz_0x80BFB480/EnRz_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Rz_0x80BFB480/func_80BFB780.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Rz_0x80BFB480/func_80BFB864.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Rz_0x80BFB480/func_80BFB9E4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Rz_0x80BFB480/func_80BFBA1C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Rz_0x80BFB480/func_80BFBA50.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Rz_0x80BFB480/func_80BFBB44.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Rz_0x80BFB480/func_80BFBC78.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Rz_0x80BFB480/func_80BFBCEC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Rz_0x80BFB480/func_80BFBD54.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Rz_0x80BFB480/func_80BFBDA0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Rz_0x80BFB480/func_80BFBDFC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Rz_0x80BFB480/EnRz_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Rz_0x80BFB480/func_80BFBE70.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Rz_0x80BFB480/func_80BFBFAC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Rz_0x80BFB480/func_80BFC058.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Rz_0x80BFB480/func_80BFC078.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Rz_0x80BFB480/func_80BFC19C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Rz_0x80BFB480/func_80BFC214.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Rz_0x80BFB480/func_80BFC270.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Rz_0x80BFB480/func_80BFC2F4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Rz_0x80BFB480/func_80BFC36C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Rz_0x80BFB480/func_80BFC3F8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Rz_0x80BFB480/func_80BFC608.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Rz_0x80BFB480/func_80BFC674.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Rz_0x80BFB480/func_80BFC728.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Rz_0x80BFB480/func_80BFC7E0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Rz_0x80BFB480/func_80BFC8AC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Rz_0x80BFB480/func_80BFC8F8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Rz_0x80BFB480/EnRz_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Rz_0x80BFB480/func_80BFCAD0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Rz_0x80BFB480/EnRz_Draw.asm")
