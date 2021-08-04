#include "z_en_slime.h"

#define FLAGS 0x00000215

#define THIS ((EnSlime*)thisx)

void EnSlime_Init(Actor* thisx, GlobalContext* globalCtx);
void EnSlime_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnSlime_Update(Actor* thisx, GlobalContext* globalCtx);
void EnSlime_Draw(Actor* thisx, GlobalContext* globalCtx);

#if 0
const ActorInit En_Slime_InitVars = {
    ACTOR_EN_SLIME,
    ACTORCAT_ENEMY,
    FLAGS,
    OBJECT_SLIME,
    sizeof(EnSlime),
    (ActorFunc)EnSlime_Init,
    (ActorFunc)EnSlime_Destroy,
    (ActorFunc)EnSlime_Update,
    (ActorFunc)EnSlime_Draw,
};


// static ColliderCylinderInit sCylinderInit = {
static ColliderCylinderInit D_80A31AF0 = {
    { COLTYPE_NONE, AT_ON | AT_TYPE_ENEMY, AC_ON | AC_TYPE_PLAYER, OC1_ON | OC1_TYPE_ALL, OC2_TYPE_1, COLSHAPE_CYLINDER, },
    { ELEMTYPE_UNK0, { 0xF7CFFFFF, 0x00, 0x04 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_HARD, BUMP_ON | BUMP_HOOKABLE, OCELEM_ON, },
    { 22, 35, 0, { 0, 0, 0 } },
};


// static DamageTable sDamageTable = {
static DamageTable D_80A31B1C = {
    /* Deku Nut       */ DMG_ENTRY(0, 0x1),
    /* Deku Stick     */ DMG_ENTRY(3, 0x0),
    /* Horse trample  */ DMG_ENTRY(1, 0x0),
    /* Explosives     */ DMG_ENTRY(1, 0x0),
    /* Zora boomerang */ DMG_ENTRY(1, 0x0),
    /* Normal arrow   */ DMG_ENTRY(1, 0x0),
    /* UNK_DMG_0x06   */ DMG_ENTRY(0, 0x0),
    /* Hookshot       */ DMG_ENTRY(0, 0xE),
    /* Goron punch    */ DMG_ENTRY(0, 0xF),
    /* Sword          */ DMG_ENTRY(1, 0x0),
    /* Goron pound    */ DMG_ENTRY(0, 0xF),
    /* Fire arrow     */ DMG_ENTRY(2, 0x0),
    /* Ice arrow      */ DMG_ENTRY(2, 0x3),
    /* Light arrow    */ DMG_ENTRY(2, 0x4),
    /* Goron spikes   */ DMG_ENTRY(1, 0x0),
    /* Deku spin      */ DMG_ENTRY(1, 0x0),
    /* Deku bubble    */ DMG_ENTRY(0, 0xF),
    /* Deku launch    */ DMG_ENTRY(2, 0x0),
    /* UNK_DMG_0x12   */ DMG_ENTRY(0, 0x1),
    /* Zora barrier   */ DMG_ENTRY(1, 0x5),
    /* Normal shield  */ DMG_ENTRY(0, 0x0),
    /* Light ray      */ DMG_ENTRY(0, 0x0),
    /* Thrown object  */ DMG_ENTRY(0, 0xF),
    /* Zora punch     */ DMG_ENTRY(1, 0x0),
    /* Spin attack    */ DMG_ENTRY(1, 0x0),
    /* Sword beam     */ DMG_ENTRY(0, 0x0),
    /* Normal Roll    */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1B   */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1C   */ DMG_ENTRY(0, 0x0),
    /* Unblockable    */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1E   */ DMG_ENTRY(0, 0x0),
    /* Powder Keg     */ DMG_ENTRY(1, 0x0),
};


// sColChkInfoInit
static CollisionCheckInfoInit D_80A31B3C = { 1, 22, 35, 60 };


// static InitChainEntry sInitChain[] = {
static InitChainEntry D_80A31B54[] = {
    ICHAIN_F32(gravity, -2, ICHAIN_CONTINUE),
    ICHAIN_F32(targetArrowOffset, 6000, ICHAIN_STOP),
};


extern ColliderCylinderInit D_80A31AF0;
extern DamageTable D_80A31B1C;
extern CollisionCheckInfoInit D_80A31B3C;
extern InitChainEntry D_80A31B54[];
#endif

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Slime_0x80A2EDA0/EnSlime_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Slime_0x80A2EDA0/EnSlime_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Slime_0x80A2EDA0/func_80A2EFAC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Slime_0x80A2EDA0/func_80A2F028.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Slime_0x80A2EDA0/func_80A2F0A8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Slime_0x80A2EDA0/func_80A2F110.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Slime_0x80A2EDA0/func_80A2F140.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Slime_0x80A2EDA0/func_80A2F180.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Slime_0x80A2EDA0/func_80A2F1A4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Slime_0x80A2EDA0/func_80A2F354.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Slime_0x80A2EDA0/func_80A2F418.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Slime_0x80A2EDA0/func_80A2F684.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Slime_0x80A2EDA0/func_80A2F6CC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Slime_0x80A2EDA0/func_80A2F8B4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Slime_0x80A2EDA0/func_80A2F8E0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Slime_0x80A2EDA0/func_80A2F9A0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Slime_0x80A2EDA0/func_80A2FA88.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Slime_0x80A2EDA0/func_80A2FB60.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Slime_0x80A2EDA0/func_80A2FBA0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Slime_0x80A2EDA0/func_80A2FD94.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Slime_0x80A2EDA0/func_80A2FE38.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Slime_0x80A2EDA0/func_80A30018.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Slime_0x80A2EDA0/func_80A30344.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Slime_0x80A2EDA0/func_80A30454.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Slime_0x80A2EDA0/func_80A304B8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Slime_0x80A2EDA0/func_80A3072C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Slime_0x80A2EDA0/func_80A30778.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Slime_0x80A2EDA0/func_80A30820.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Slime_0x80A2EDA0/func_80A30924.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Slime_0x80A2EDA0/func_80A30944.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Slime_0x80A2EDA0/func_80A309C8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Slime_0x80A2EDA0/func_80A30A20.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Slime_0x80A2EDA0/func_80A30A90.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Slime_0x80A2EDA0/func_80A30AE4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Slime_0x80A2EDA0/func_80A30BE0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Slime_0x80A2EDA0/func_80A30C2C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Slime_0x80A2EDA0/func_80A30C68.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Slime_0x80A2EDA0/func_80A30CEC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Slime_0x80A2EDA0/func_80A30F98.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Slime_0x80A2EDA0/EnSlime_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Slime_0x80A2EDA0/EnSlime_Draw.asm")
