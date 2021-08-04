#include "z_en_scopenuts.h"

#define FLAGS 0x00000039

#define THIS ((EnScopenuts*)thisx)

void EnScopenuts_Init(Actor* thisx, GlobalContext* globalCtx);
void EnScopenuts_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnScopenuts_Update(Actor* thisx, GlobalContext* globalCtx);
void EnScopenuts_Draw(Actor* thisx, GlobalContext* globalCtx);

#if 0
const ActorInit En_Scopenuts_InitVars = {
    ACTOR_EN_SCOPENUTS,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_DNT,
    sizeof(EnScopenuts),
    (ActorFunc)EnScopenuts_Init,
    (ActorFunc)EnScopenuts_Destroy,
    (ActorFunc)EnScopenuts_Update,
    (ActorFunc)EnScopenuts_Draw,
};


// static ColliderCylinderInit sCylinderInit = {
static ColliderCylinderInit D_80BCCB40 = {
    { COLTYPE_NONE, AT_NONE, AC_ON | AC_TYPE_PLAYER, OC1_ON | OC1_TYPE_ALL, OC2_HIT_PLAYER, COLSHAPE_JNTSPH, },
    { ELEMTYPE_UNK0, { 0x00000000, 0x00, 0x00 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_ON, },
    { 27, 32, 0, { 0, 0, 0 } },
};


// static InitChainEntry sInitChain[] = {
static InitChainEntry D_80BCCCF0[] = {
    ICHAIN_U8(targetMode, 0, ICHAIN_CONTINUE),
    ICHAIN_F32(targetArrowOffset, 30, ICHAIN_STOP),
};


extern ColliderCylinderInit D_80BCCB40;
extern InitChainEntry D_80BCCCF0[];
#endif

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Scopenuts_0x80BCABF0/func_80BCABF0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Scopenuts_0x80BCABF0/func_80BCAC40.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Scopenuts_0x80BCABF0/func_80BCAD64.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Scopenuts_0x80BCABF0/func_80BCAE78.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Scopenuts_0x80BCABF0/func_80BCAF0C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Scopenuts_0x80BCABF0/func_80BCAFA8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Scopenuts_0x80BCABF0/func_80BCB078.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Scopenuts_0x80BCABF0/func_80BCB1C8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Scopenuts_0x80BCABF0/func_80BCB230.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Scopenuts_0x80BCABF0/func_80BCB4DC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Scopenuts_0x80BCABF0/func_80BCB52C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Scopenuts_0x80BCABF0/func_80BCB6D0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Scopenuts_0x80BCABF0/func_80BCB90C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Scopenuts_0x80BCABF0/func_80BCB980.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Scopenuts_0x80BCABF0/func_80BCBA00.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Scopenuts_0x80BCABF0/func_80BCBC60.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Scopenuts_0x80BCABF0/func_80BCBD28.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Scopenuts_0x80BCABF0/func_80BCBF0C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Scopenuts_0x80BCABF0/func_80BCBFFC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Scopenuts_0x80BCABF0/func_80BCC288.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Scopenuts_0x80BCABF0/func_80BCC2AC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Scopenuts_0x80BCABF0/func_80BCC448.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Scopenuts_0x80BCABF0/EnScopenuts_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Scopenuts_0x80BCABF0/EnScopenuts_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Scopenuts_0x80BCABF0/EnScopenuts_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Scopenuts_0x80BCABF0/func_80BCC828.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Scopenuts_0x80BCABF0/func_80BCC9CC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Scopenuts_0x80BCABF0/func_80BCC9E4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Scopenuts_0x80BCABF0/EnScopenuts_Draw.asm")
