#include "z_en_sellnuts.h"

#define FLAGS 0x00000039

#define THIS ((EnSellnuts*)thisx)

void EnSellnuts_Init(Actor* thisx, GlobalContext* globalCtx);
void EnSellnuts_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnSellnuts_Update(Actor* thisx, GlobalContext* globalCtx);
void EnSellnuts_Draw(Actor* thisx, GlobalContext* globalCtx);

#if 0
const ActorInit En_Sellnuts_InitVars = {
    ACTOR_EN_SELLNUTS,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_DNT,
    sizeof(EnSellnuts),
    (ActorFunc)EnSellnuts_Init,
    (ActorFunc)EnSellnuts_Destroy,
    (ActorFunc)EnSellnuts_Update,
    (ActorFunc)EnSellnuts_Draw,
};


// static ColliderCylinderInit sCylinderInit = {
static ColliderCylinderInit D_80ADD964 = {
    { COLTYPE_NONE, AT_NONE, AC_ON | AC_TYPE_PLAYER, OC1_ON | OC1_TYPE_ALL, OC2_HIT_PLAYER, COLSHAPE_JNTSPH, },
    { ELEMTYPE_UNK0, { 0x00000000, 0x00, 0x00 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_ON, },
    { 27, 32, 0, { 0, 0, 0 } },
};


// static InitChainEntry sInitChain[] = {
static InitChainEntry D_80ADDB00[] = {
    ICHAIN_U8(targetMode, 0, ICHAIN_CONTINUE),
    ICHAIN_F32(targetArrowOffset, 30, ICHAIN_STOP),
};


extern ColliderCylinderInit D_80ADD964;
extern InitChainEntry D_80ADDB00[];
#endif

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Sellnuts_0x80ADADD0/func_80ADADD0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Sellnuts_0x80ADADD0/func_80ADAE64.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Sellnuts_0x80ADADD0/func_80ADAFC0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Sellnuts_0x80ADADD0/func_80ADB040.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Sellnuts_0x80ADADD0/func_80ADB08C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Sellnuts_0x80ADADD0/func_80ADB0D8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Sellnuts_0x80ADADD0/func_80ADB254.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Sellnuts_0x80ADADD0/func_80ADB4F4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Sellnuts_0x80ADADD0/func_80ADB544.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Sellnuts_0x80ADADD0/func_80ADB924.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Sellnuts_0x80ADADD0/func_80ADBAB8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Sellnuts_0x80ADADD0/func_80ADBBEC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Sellnuts_0x80ADADD0/func_80ADBC60.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Sellnuts_0x80ADADD0/func_80ADBCE4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Sellnuts_0x80ADADD0/func_80ADBD64.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Sellnuts_0x80ADADD0/func_80ADBE80.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Sellnuts_0x80ADADD0/func_80ADBFA0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Sellnuts_0x80ADADD0/func_80ADC034.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Sellnuts_0x80ADADD0/func_80ADC118.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Sellnuts_0x80ADADD0/func_80ADC2CC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Sellnuts_0x80ADADD0/func_80ADC37C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Sellnuts_0x80ADADD0/func_80ADC580.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Sellnuts_0x80ADADD0/func_80ADC5A4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Sellnuts_0x80ADADD0/func_80ADC6D0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Sellnuts_0x80ADADD0/func_80ADC7B4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Sellnuts_0x80ADADD0/func_80ADC8C4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Sellnuts_0x80ADADD0/func_80ADCA64.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Sellnuts_0x80ADADD0/func_80ADCC04.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Sellnuts_0x80ADADD0/func_80ADCD3C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Sellnuts_0x80ADADD0/func_80ADCE4C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Sellnuts_0x80ADADD0/func_80ADCFE8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Sellnuts_0x80ADADD0/EnSellnuts_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Sellnuts_0x80ADADD0/EnSellnuts_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Sellnuts_0x80ADADD0/EnSellnuts_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Sellnuts_0x80ADADD0/func_80ADD4E0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Sellnuts_0x80ADADD0/func_80ADD7B4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Sellnuts_0x80ADADD0/func_80ADD7CC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Sellnuts_0x80ADADD0/EnSellnuts_Draw.asm")
