#include "z_en_zo.h"

#define FLAGS 0x00000019

#define THIS ((EnZo*)thisx)

void EnZo_Init(Actor* thisx, GlobalContext* globalCtx);
void EnZo_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnZo_Update(Actor* thisx, GlobalContext* globalCtx);
void EnZo_Draw(Actor* thisx, GlobalContext* globalCtx);

#if 0
const ActorInit En_Zo_InitVars = {
    ACTOR_EN_ZO,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_ZO,
    sizeof(EnZo),
    (ActorFunc)EnZo_Init,
    (ActorFunc)EnZo_Destroy,
    (ActorFunc)EnZo_Update,
    (ActorFunc)EnZo_Draw,
};


// static ColliderCylinderInit sCylinderInit = {
static ColliderCylinderInit D_8099F4B0 = {
    { COLTYPE_HIT0, AT_NONE, AC_ON | AC_TYPE_PLAYER, OC1_ON | OC1_TYPE_ALL, OC2_TYPE_1, COLSHAPE_CYLINDER, },
    { ELEMTYPE_UNK1, { 0x00000000, 0x00, 0x00 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_ON, },
    { 18, 64, 0, { 0, 0, 0 } },
};


// sColChkInfoInit
static CollisionCheckInfoInit2 D_8099F4DC = { 0, 0, 0, 0, MASS_IMMOVABLE };


// static DamageTable sDamageTable = {
static DamageTable D_8099F4E8 = {
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


extern ColliderCylinderInit D_8099F4B0;
extern CollisionCheckInfoInit2 D_8099F4DC;
extern DamageTable D_8099F4E8;
#endif

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Zo_0x8099E790/func_8099E790.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Zo_0x8099E790/func_8099E858.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Zo_0x8099E790/func_8099E96C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Zo_0x8099E790/func_8099E9E0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Zo_0x8099E790/func_8099EA60.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Zo_0x8099E790/func_8099EBD8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Zo_0x8099E790/func_8099EC50.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Zo_0x8099E790/func_8099ED4C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Zo_0x8099E790/func_8099EE24.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Zo_0x8099E790/EnZo_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Zo_0x8099E790/EnZo_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Zo_0x8099E790/EnZo_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Zo_0x8099E790/func_8099EFF4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Zo_0x8099E790/func_8099F15C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Zo_0x8099E790/EnZo_Draw.asm")
