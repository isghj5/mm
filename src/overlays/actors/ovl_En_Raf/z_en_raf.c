#include "z_en_raf.h"

#define FLAGS 0x08000000

#define THIS ((EnRaf*)thisx)

void EnRaf_Init(Actor* thisx, GlobalContext* globalCtx);
void EnRaf_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnRaf_Update(Actor* thisx, GlobalContext* globalCtx);
void EnRaf_Draw(Actor* thisx, GlobalContext* globalCtx);

#if 0
const ActorInit En_Raf_InitVars = {
    ACTOR_EN_RAF,
    ACTORCAT_PROP,
    FLAGS,
    OBJECT_RAF,
    sizeof(EnRaf),
    (ActorFunc)EnRaf_Init,
    (ActorFunc)EnRaf_Destroy,
    (ActorFunc)EnRaf_Update,
    (ActorFunc)EnRaf_Draw,
};


// static ColliderCylinderInit sCylinderInit = {
static ColliderCylinderInit D_80A18EE0 = {
    { COLTYPE_NONE, AT_ON | AT_TYPE_ENEMY, AC_NONE, OC1_ON | OC1_TYPE_ALL, OC2_TYPE_1, COLSHAPE_CYLINDER, },
    { ELEMTYPE_UNK0, { 0xF7CFFFFF, 0x04, 0x10 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_NORMAL, BUMP_NONE, OCELEM_ON, },
    { 50, 10, -10, { 0, 0, 0 } },
};


// static DamageTable sDamageTable = {
static DamageTable D_80A1939C = {
    /* Deku Nut       */ DMG_ENTRY(0, 0xF),
    /* Deku Stick     */ DMG_ENTRY(0, 0xF),
    /* Horse trample  */ DMG_ENTRY(0, 0x0),
    /* Explosives     */ DMG_ENTRY(1, 0xE),
    /* Zora boomerang */ DMG_ENTRY(0, 0xF),
    /* Normal arrow   */ DMG_ENTRY(0, 0xF),
    /* UNK_DMG_0x06   */ DMG_ENTRY(0, 0x0),
    /* Hookshot       */ DMG_ENTRY(0, 0xF),
    /* Goron punch    */ DMG_ENTRY(0, 0xF),
    /* Sword          */ DMG_ENTRY(0, 0xF),
    /* Goron pound    */ DMG_ENTRY(0, 0xF),
    /* Fire arrow     */ DMG_ENTRY(0, 0xF),
    /* Ice arrow      */ DMG_ENTRY(0, 0xF),
    /* Light arrow    */ DMG_ENTRY(0, 0xF),
    /* Goron spikes   */ DMG_ENTRY(0, 0xF),
    /* Deku spin      */ DMG_ENTRY(0, 0xF),
    /* Deku bubble    */ DMG_ENTRY(0, 0xF),
    /* Deku launch    */ DMG_ENTRY(0, 0xF),
    /* UNK_DMG_0x12   */ DMG_ENTRY(0, 0xF),
    /* Zora barrier   */ DMG_ENTRY(0, 0xF),
    /* Normal shield  */ DMG_ENTRY(0, 0x0),
    /* Light ray      */ DMG_ENTRY(0, 0x0),
    /* Thrown object  */ DMG_ENTRY(0, 0xF),
    /* Zora punch     */ DMG_ENTRY(0, 0xF),
    /* Spin attack    */ DMG_ENTRY(0, 0xF),
    /* Sword beam     */ DMG_ENTRY(0, 0x0),
    /* Normal Roll    */ DMG_ENTRY(0, 0xF),
    /* UNK_DMG_0x1B   */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1C   */ DMG_ENTRY(0, 0x0),
    /* Unblockable    */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1E   */ DMG_ENTRY(0, 0x0),
    /* Powder Keg     */ DMG_ENTRY(0, 0xF),
};


extern ColliderCylinderInit D_80A18EE0;
extern DamageTable D_80A1939C;
#endif

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Raf_0x80A16D40/func_80A16D40.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Raf_0x80A16D40/func_80A16D6C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Raf_0x80A16D40/EnRaf_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Raf_0x80A16D40/EnRaf_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Raf_0x80A16D40/func_80A17060.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Raf_0x80A16D40/func_80A1712C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Raf_0x80A16D40/func_80A171D8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Raf_0x80A16D40/func_80A17414.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Raf_0x80A16D40/func_80A17464.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Raf_0x80A16D40/func_80A17530.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Raf_0x80A16D40/func_80A175E4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Raf_0x80A16D40/func_80A17848.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Raf_0x80A16D40/func_80A178A0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Raf_0x80A16D40/func_80A179C8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Raf_0x80A16D40/func_80A17C6C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Raf_0x80A16D40/func_80A17D14.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Raf_0x80A16D40/func_80A17D54.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Raf_0x80A16D40/func_80A17DDC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Raf_0x80A16D40/func_80A17E1C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Raf_0x80A16D40/func_80A18080.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Raf_0x80A16D40/func_80A180B4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Raf_0x80A16D40/EnRaf_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Raf_0x80A16D40/func_80A1859C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Raf_0x80A16D40/EnRaf_Draw.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Raf_0x80A16D40/func_80A18A90.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Raf_0x80A16D40/func_80A18B8C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Raf_0x80A16D40/func_80A18DA0.asm")
