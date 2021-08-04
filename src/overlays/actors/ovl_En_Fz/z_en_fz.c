#include "z_en_fz.h"

#define FLAGS 0x00000015

#define THIS ((EnFz*)thisx)

void EnFz_Init(Actor* thisx, GlobalContext* globalCtx);
void EnFz_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnFz_Update(Actor* thisx, GlobalContext* globalCtx);
void EnFz_Draw(Actor* thisx, GlobalContext* globalCtx);

#if 0
const ActorInit En_Fz_InitVars = {
    ACTOR_EN_FZ,
    ACTORCAT_ENEMY,
    FLAGS,
    OBJECT_FZ,
    sizeof(EnFz),
    (ActorFunc)EnFz_Init,
    (ActorFunc)EnFz_Destroy,
    (ActorFunc)EnFz_Update,
    (ActorFunc)EnFz_Draw,
};


// static ColliderCylinderInit sCylinderInit = {
static ColliderCylinderInit D_809346F8 = {
    { COLTYPE_NONE, AT_ON | AT_TYPE_ENEMY, AC_ON | AC_TYPE_PLAYER, OC1_ON | OC1_TYPE_ALL, OC2_HIT_PLAYER, COLSHAPE_JNTSPH, },
    { ELEMTYPE_UNK0, { 0xF7CFFFFF, 0x00, 0x00 }, { 0xF7CFEFDD, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_NORMAL, BUMP_ON | BUMP_HOOKABLE, OCELEM_ON, },
    { 30, 80, 0, { 0, 0, 0 } },
};


// static ColliderCylinderInit sCylinderInit = {
static ColliderCylinderInit D_80934724 = {
    { COLTYPE_METAL, AT_NONE, AC_ON | AC_HARD | AC_TYPE_PLAYER, OC1_NONE, OC2_HIT_PLAYER, COLSHAPE_JNTSPH, },
    { ELEMTYPE_UNK0, { 0xF7CFFFFF, 0x00, 0x00 }, { 0x00001022, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_NONE, },
    { 35, 80, 0, { 0, 0, 0 } },
};


// static ColliderCylinderInit sCylinderInit = {
static ColliderCylinderInit D_80934750 = {
    { COLTYPE_NONE, AT_ON | AT_TYPE_ENEMY, AC_NONE, OC1_NONE, OC2_HIT_PLAYER, COLSHAPE_JNTSPH, },
    { ELEMTYPE_UNK0, { 0x20000000, 0x02, 0x04 }, { 0x00000000, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_NORMAL, BUMP_NONE, OCELEM_NONE, },
    { 20, 30, -15, { 0, 0, 0 } },
};


// static DamageTable sDamageTable = {
static DamageTable D_8093477C = {
    /* Deku Nut       */ DMG_ENTRY(0, 0x0),
    /* Deku Stick     */ DMG_ENTRY(0, 0xD),
    /* Horse trample  */ DMG_ENTRY(0, 0x0),
    /* Explosives     */ DMG_ENTRY(2, 0xF),
    /* Zora boomerang */ DMG_ENTRY(0, 0x0),
    /* Normal arrow   */ DMG_ENTRY(0, 0xD),
    /* UNK_DMG_0x06   */ DMG_ENTRY(2, 0xF),
    /* Hookshot       */ DMG_ENTRY(3, 0xF),
    /* Goron punch    */ DMG_ENTRY(2, 0xF),
    /* Sword          */ DMG_ENTRY(1, 0xF),
    /* Goron pound    */ DMG_ENTRY(3, 0xF),
    /* Fire arrow     */ DMG_ENTRY(2, 0x2),
    /* Ice arrow      */ DMG_ENTRY(0, 0x0),
    /* Light arrow    */ DMG_ENTRY(2, 0x4),
    /* Goron spikes   */ DMG_ENTRY(1, 0xF),
    /* Deku spin      */ DMG_ENTRY(0, 0x0),
    /* Deku bubble    */ DMG_ENTRY(0, 0x0),
    /* Deku launch    */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x12   */ DMG_ENTRY(0, 0x0),
    /* Zora barrier   */ DMG_ENTRY(0, 0x0),
    /* Normal shield  */ DMG_ENTRY(0, 0x0),
    /* Light ray      */ DMG_ENTRY(0, 0xE),
    /* Thrown object  */ DMG_ENTRY(1, 0xF),
    /* Zora punch     */ DMG_ENTRY(1, 0xF),
    /* Spin attack    */ DMG_ENTRY(1, 0xF),
    /* Sword beam     */ DMG_ENTRY(0, 0x0),
    /* Normal Roll    */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1B   */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1C   */ DMG_ENTRY(0, 0x0),
    /* Unblockable    */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1E   */ DMG_ENTRY(0, 0x0),
    /* Powder Keg     */ DMG_ENTRY(1, 0xF),
};


// static InitChainEntry sInitChain[] = {
static InitChainEntry D_8093479C[] = {
    ICHAIN_S8(hintId, 59, ICHAIN_CONTINUE),
    ICHAIN_U8(targetMode, 2, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneForward, 1400, ICHAIN_CONTINUE),
    ICHAIN_F32(targetArrowOffset, 30, ICHAIN_STOP),
};


extern ColliderCylinderInit D_809346F8;
extern ColliderCylinderInit D_80934724;
extern ColliderCylinderInit D_80934750;
extern DamageTable D_8093477C;
extern InitChainEntry D_8093479C[];
#endif

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fz_0x80932490/EnFz_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fz_0x80932490/EnFz_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fz_0x80932490/func_80932784.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fz_0x80932490/func_809328A4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fz_0x80932490/func_809328F4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fz_0x80932490/func_80932AE8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fz_0x80932490/func_80932AF4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fz_0x80932490/func_80932BD4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fz_0x80932490/func_80932C98.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fz_0x80932490/func_80933014.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fz_0x80932490/func_809330D4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fz_0x80932490/func_80933104.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fz_0x80932490/func_80933184.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fz_0x80932490/func_809331F8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fz_0x80932490/func_80933248.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fz_0x80932490/func_80933274.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fz_0x80932490/func_80933324.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fz_0x80932490/func_80933368.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fz_0x80932490/func_809333A4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fz_0x80932490/func_809333D8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fz_0x80932490/func_80933414.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fz_0x80932490/func_80933444.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fz_0x80932490/func_80933480.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fz_0x80932490/func_809334B8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fz_0x80932490/func_809336C0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fz_0x80932490/func_80933760.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fz_0x80932490/func_80933790.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fz_0x80932490/func_809337D4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fz_0x80932490/func_8093389C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fz_0x80932490/func_809338E0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fz_0x80932490/func_80933AF4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fz_0x80932490/func_80933B38.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fz_0x80932490/func_80933B48.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fz_0x80932490/EnFz_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fz_0x80932490/EnFz_Draw.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fz_0x80932490/func_80934018.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fz_0x80932490/func_809340BC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fz_0x80932490/func_80934178.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fz_0x80932490/func_80934464.asm")
