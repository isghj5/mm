#include "z_en_dg.h"

#define FLAGS 0x00800019

#define THIS ((EnDg*)thisx)

void EnDg_Init(Actor* thisx, GlobalContext* globalCtx);
void EnDg_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnDg_Update(Actor* thisx, GlobalContext* globalCtx);
void EnDg_Draw(Actor* thisx, GlobalContext* globalCtx);

#if 0
const ActorInit En_Dg_InitVars = {
    ACTOR_EN_DG,
    ACTORCAT_ENEMY,
    FLAGS,
    OBJECT_DOG,
    sizeof(EnDg),
    (ActorFunc)EnDg_Init,
    (ActorFunc)EnDg_Destroy,
    (ActorFunc)EnDg_Update,
    (ActorFunc)EnDg_Draw,
};


// static ColliderCylinderInit sCylinderInit = {
static ColliderCylinderInit D_8098C304 = {
    { COLTYPE_NONE, AT_ON | AT_TYPE_ENEMY, AC_ON | AC_TYPE_PLAYER, OC1_ON | OC1_TYPE_ALL, OC2_TYPE_1, COLSHAPE_CYLINDER, },
    { ELEMTYPE_UNK1, { 0xF7CFFFFF, 0x04, 0x00 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_ON, },
    { 13, 19, 0, { 0, 0, 0 } },
};


// sColChkInfoInit
static CollisionCheckInfoInit2 D_8098C330 = { 0, 0, 0, 0, 1 };


// static DamageTable sDamageTable = {
static DamageTable D_8098C33C = {
    /* Deku Nut       */ DMG_ENTRY(0, 0x0),
    /* Deku Stick     */ DMG_ENTRY(0, 0x0),
    /* Horse trample  */ DMG_ENTRY(0, 0x0),
    /* Explosives     */ DMG_ENTRY(0, 0x0),
    /* Zora boomerang */ DMG_ENTRY(0, 0x0),
    /* Normal arrow   */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x06   */ DMG_ENTRY(0, 0x0),
    /* Hookshot       */ DMG_ENTRY(0, 0x0),
    /* Goron punch    */ DMG_ENTRY(0, 0x0),
    /* Sword          */ DMG_ENTRY(0, 0x0),
    /* Goron pound    */ DMG_ENTRY(0, 0x0),
    /* Fire arrow     */ DMG_ENTRY(0, 0x0),
    /* Ice arrow      */ DMG_ENTRY(0, 0x0),
    /* Light arrow    */ DMG_ENTRY(0, 0x0),
    /* Goron spikes   */ DMG_ENTRY(0, 0x0),
    /* Deku spin      */ DMG_ENTRY(0, 0x0),
    /* Deku bubble    */ DMG_ENTRY(0, 0x0),
    /* Deku launch    */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x12   */ DMG_ENTRY(0, 0x0),
    /* Zora barrier   */ DMG_ENTRY(0, 0x0),
    /* Normal shield  */ DMG_ENTRY(0, 0x0),
    /* Light ray      */ DMG_ENTRY(0, 0x0),
    /* Thrown object  */ DMG_ENTRY(0, 0x0),
    /* Zora punch     */ DMG_ENTRY(0, 0x0),
    /* Spin attack    */ DMG_ENTRY(0, 0x0),
    /* Sword beam     */ DMG_ENTRY(0, 0x0),
    /* Normal Roll    */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1B   */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1C   */ DMG_ENTRY(0, 0x0),
    /* Unblockable    */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1E   */ DMG_ENTRY(0, 0x0),
    /* Powder Keg     */ DMG_ENTRY(0, 0x0),
};


// static InitChainEntry sInitChain[] = {
static InitChainEntry D_8098C45C[] = {
    ICHAIN_F32(uncullZoneForward, 1000, ICHAIN_STOP),
};


extern ColliderCylinderInit D_8098C304;
extern CollisionCheckInfoInit2 D_8098C330;
extern DamageTable D_8098C33C;
extern InitChainEntry D_8098C45C[];
#endif

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dg_0x80989140/func_80989140.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dg_0x80989140/func_80989204.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dg_0x80989140/func_8098933C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dg_0x80989140/func_80989418.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dg_0x80989140/func_809895B4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dg_0x80989140/func_80989674.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dg_0x80989140/func_80989864.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dg_0x80989140/func_80989974.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dg_0x80989140/func_809899C8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dg_0x80989140/func_80989A08.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dg_0x80989140/func_80989A48.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dg_0x80989140/func_80989A9C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dg_0x80989140/func_80989ADC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dg_0x80989140/func_80989BF8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dg_0x80989140/func_80989D38.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dg_0x80989140/func_80989E18.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dg_0x80989140/func_80989FC8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dg_0x80989140/func_8098A064.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dg_0x80989140/func_8098A1B4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dg_0x80989140/func_8098A234.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dg_0x80989140/func_8098A468.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dg_0x80989140/func_8098A55C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dg_0x80989140/func_8098A618.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dg_0x80989140/func_8098A70C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dg_0x80989140/func_8098A89C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dg_0x80989140/func_8098A938.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dg_0x80989140/func_8098AAAC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dg_0x80989140/func_8098AB48.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dg_0x80989140/func_8098AC34.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dg_0x80989140/func_8098AE58.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dg_0x80989140/func_8098AF44.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dg_0x80989140/func_8098AF98.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dg_0x80989140/func_8098B004.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dg_0x80989140/func_8098B198.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dg_0x80989140/func_8098B28C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dg_0x80989140/func_8098B390.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dg_0x80989140/func_8098B464.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dg_0x80989140/func_8098B560.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dg_0x80989140/func_8098B88C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dg_0x80989140/func_8098BA64.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dg_0x80989140/func_8098BB10.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dg_0x80989140/func_8098BBEC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dg_0x80989140/func_8098BC54.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dg_0x80989140/EnDg_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dg_0x80989140/EnDg_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dg_0x80989140/EnDg_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dg_0x80989140/func_8098BFB8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dg_0x80989140/func_8098BFD4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dg_0x80989140/EnDg_Draw.asm")
