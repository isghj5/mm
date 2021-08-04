#include "z_en_knight.h"

#define FLAGS 0x00000035

#define THIS ((EnKnight*)thisx)

void EnKnight_Init(Actor* thisx, GlobalContext* globalCtx);
void EnKnight_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnKnight_Update(Actor* thisx, GlobalContext* globalCtx);
void EnKnight_Draw(Actor* thisx, GlobalContext* globalCtx);

#if 0
// static DamageTable sDamageTable = {
static DamageTable D_809BDB04 = {
    /* Deku Nut       */ DMG_ENTRY(0, 0x1),
    /* Deku Stick     */ DMG_ENTRY(1, 0xF),
    /* Horse trample  */ DMG_ENTRY(0, 0x0),
    /* Explosives     */ DMG_ENTRY(1, 0xF),
    /* Zora boomerang */ DMG_ENTRY(0, 0x1),
    /* Normal arrow   */ DMG_ENTRY(3, 0xF),
    /* UNK_DMG_0x06   */ DMG_ENTRY(0, 0x0),
    /* Hookshot       */ DMG_ENTRY(0, 0xF),
    /* Goron punch    */ DMG_ENTRY(1, 0xF),
    /* Sword          */ DMG_ENTRY(1, 0xF),
    /* Goron pound    */ DMG_ENTRY(0, 0xD),
    /* Fire arrow     */ DMG_ENTRY(1, 0x2),
    /* Ice arrow      */ DMG_ENTRY(1, 0x3),
    /* Light arrow    */ DMG_ENTRY(2, 0x4),
    /* Goron spikes   */ DMG_ENTRY(1, 0xF),
    /* Deku spin      */ DMG_ENTRY(0, 0x1),
    /* Deku bubble    */ DMG_ENTRY(2, 0xF),
    /* Deku launch    */ DMG_ENTRY(1, 0xF),
    /* UNK_DMG_0x12   */ DMG_ENTRY(0, 0x0),
    /* Zora barrier   */ DMG_ENTRY(0, 0xA),
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


// static DamageTable sDamageTable = {
static DamageTable D_809BDB24 = {
    /* Deku Nut       */ DMG_ENTRY(0, 0x0),
    /* Deku Stick     */ DMG_ENTRY(1, 0xF),
    /* Horse trample  */ DMG_ENTRY(0, 0x0),
    /* Explosives     */ DMG_ENTRY(1, 0xF),
    /* Zora boomerang */ DMG_ENTRY(1, 0xF),
    /* Normal arrow   */ DMG_ENTRY(3, 0xF),
    /* UNK_DMG_0x06   */ DMG_ENTRY(0, 0x0),
    /* Hookshot       */ DMG_ENTRY(0, 0xF),
    /* Goron punch    */ DMG_ENTRY(1, 0xF),
    /* Sword          */ DMG_ENTRY(1, 0xF),
    /* Goron pound    */ DMG_ENTRY(1, 0xF),
    /* Fire arrow     */ DMG_ENTRY(1, 0x2),
    /* Ice arrow      */ DMG_ENTRY(1, 0x3),
    /* Light arrow    */ DMG_ENTRY(2, 0x4),
    /* Goron spikes   */ DMG_ENTRY(1, 0xF),
    /* Deku spin      */ DMG_ENTRY(1, 0xF),
    /* Deku bubble    */ DMG_ENTRY(2, 0xF),
    /* Deku launch    */ DMG_ENTRY(2, 0xF),
    /* UNK_DMG_0x12   */ DMG_ENTRY(0, 0x0),
    /* Zora barrier   */ DMG_ENTRY(0, 0xA),
    /* Normal shield  */ DMG_ENTRY(0, 0x0),
    /* Light ray      */ DMG_ENTRY(1, 0xD),
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


// static ColliderJntSphElementInit sJntSphElementsInit[1] = {
static ColliderJntSphElementInit D_809BDB44[1] = {
    {
        { ELEMTYPE_UNK2, { 0xF7CFFFFF, 0x00, 0x08 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_ON, },
        { 0, { { 0, 0, 0 }, 27 }, 100 },
    },
};

// static ColliderJntSphInit sJntSphInit = {
static ColliderJntSphInit D_809BDB8C = {
    { COLTYPE_METAL, AT_ON | AT_TYPE_ENEMY, AC_ON | AC_HARD | AC_TYPE_PLAYER, OC1_ON | OC1_TYPE_PLAYER, OC2_TYPE_1, COLSHAPE_JNTSPH, },
    1, D_809BDB44, // sJntSphElementsInit,
};


// static ColliderJntSphElementInit sJntSphElementsInit[1] = {
static ColliderJntSphElementInit D_809BDB68[1] = {
    {
        { ELEMTYPE_UNK2, { 0xF7CFFFFF, 0x00, 0x10 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_ON, },
        { 0, { { 0, 0, 0 }, 32 }, 100 },
    },
};

// static ColliderJntSphInit sJntSphInit = {
static ColliderJntSphInit D_809BDB9C = {
    { COLTYPE_METAL, AT_ON | AT_TYPE_ENEMY, AC_ON | AC_HARD | AC_TYPE_PLAYER, OC1_ON | OC1_TYPE_PLAYER, OC2_TYPE_1, COLSHAPE_JNTSPH, },
    1, D_809BDB68, // sJntSphElementsInit,
};


// static ColliderJntSphElementInit sJntSphElementsInit[1] = {
static ColliderJntSphElementInit D_809BDBAC[1] = {
    {
        { ELEMTYPE_UNK2, { 0xF7CFFFFF, 0x00, 0x08 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_ON, },
        { 0, { { 0, 0, 0 }, 27 }, 100 },
    },
};

// static ColliderJntSphInit sJntSphInit = {
static ColliderJntSphInit D_809BDBD0 = {
    { COLTYPE_METAL, AT_ON | AT_TYPE_ENEMY, AC_ON | AC_HARD | AC_TYPE_PLAYER, OC1_ON | OC1_TYPE_PLAYER, OC2_TYPE_1, COLSHAPE_JNTSPH, },
    1, D_809BDBAC, // sJntSphElementsInit,
};


// static ColliderJntSphElementInit sJntSphElementsInit[2] = {
static ColliderJntSphElementInit D_809BDBE0[2] = {
    {
        { ELEMTYPE_UNK3, { 0xF7CFFFFF, 0x00, 0x08 }, { 0xF7EFFFFF, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_NORMAL, BUMP_ON | BUMP_HOOKABLE, OCELEM_ON, },
        { 0, { { 0, 0, 0 }, 15 }, 100 },
    },
    {
        { ELEMTYPE_UNK3, { 0xF7CFFFFF, 0x00, 0x08 }, { 0xF7EFFFFF, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_NORMAL, BUMP_ON | BUMP_HOOKABLE, OCELEM_ON, },
        { 1, { { 0, 0, 0 }, 17 }, 100 },
    },
};

// static ColliderJntSphInit sJntSphInit = {
static ColliderJntSphInit D_809BDC28 = {
    { COLTYPE_HIT3, AT_ON | AT_TYPE_ENEMY, AC_ON | AC_TYPE_PLAYER, OC1_ON | OC1_TYPE_PLAYER | OC1_TYPE_1, OC2_TYPE_1, COLSHAPE_JNTSPH, },
    2, D_809BDBE0, // sJntSphElementsInit,
};


// static ColliderCylinderInit sCylinderInit = {
static ColliderCylinderInit D_809BDC38 = {
    { COLTYPE_METAL, AT_ON | AT_TYPE_ENEMY, AC_ON | AC_HARD | AC_TYPE_PLAYER, OC1_ON | OC1_TYPE_ALL, OC2_TYPE_1, COLSHAPE_CYLINDER, },
    { ELEMTYPE_UNK3, { 0xF7CFFFFF, 0x00, 0x10 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_ON, },
    { 15, 20, -10, { 0, 0, 0 } },
};


// static ColliderCylinderInit sCylinderInit = {
static ColliderCylinderInit D_809BDC64 = {
    { COLTYPE_HIT3, AT_ON | AT_TYPE_ALL, AC_ON | AC_TYPE_PLAYER | AC_TYPE_ENEMY | AC_TYPE_OTHER, OC1_ON | OC1_TYPE_ALL, OC2_TYPE_1, COLSHAPE_CYLINDER, },
    { ELEMTYPE_UNK3, { 0xF7CFFFFF, 0x00, 0x00 }, { 0xF7FFFFFF, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_ON, },
    { 20, 40, 0, { 0, 0, 0 } },
};


const ActorInit En_Knight_InitVars = {
    ACTOR_EN_KNIGHT,
    ACTORCAT_BOSS,
    FLAGS,
    OBJECT_KNIGHT,
    sizeof(EnKnight),
    (ActorFunc)EnKnight_Init,
    (ActorFunc)EnKnight_Destroy,
    (ActorFunc)EnKnight_Update,
    (ActorFunc)EnKnight_Draw,
};


extern DamageTable D_809BDB04;
extern DamageTable D_809BDB24;
extern ColliderJntSphElementInit D_809BDB44[1];
extern ColliderJntSphInit D_809BDB8C;
extern ColliderJntSphElementInit D_809BDB68[1];
extern ColliderJntSphInit D_809BDB9C;
extern ColliderJntSphElementInit D_809BDBAC[1];
extern ColliderJntSphInit D_809BDBD0;
extern ColliderJntSphElementInit D_809BDBE0[2];
extern ColliderJntSphInit D_809BDC28;
extern ColliderCylinderInit D_809BDC38;
extern ColliderCylinderInit D_809BDC64;
#endif

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Knight_0x809B20F0/func_809B20F0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Knight_0x809B20F0/func_809B21F4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Knight_0x809B20F0/func_809B22CC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Knight_0x809B20F0/EnKnight_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Knight_0x809B20F0/EnKnight_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Knight_0x809B20F0/func_809B2DD0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Knight_0x809B20F0/func_809B2F54.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Knight_0x809B20F0/func_809B316C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Knight_0x809B20F0/func_809B31E8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Knight_0x809B20F0/func_809B329C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Knight_0x809B20F0/func_809B331C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Knight_0x809B20F0/func_809B3394.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Knight_0x809B20F0/func_809B33F0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Knight_0x809B20F0/func_809B35BC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Knight_0x809B20F0/func_809B3618.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Knight_0x809B20F0/func_809B37C8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Knight_0x809B20F0/func_809B3834.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Knight_0x809B20F0/func_809B389C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Knight_0x809B20F0/func_809B3958.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Knight_0x809B20F0/func_809B3A7C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Knight_0x809B20F0/func_809B3B94.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Knight_0x809B20F0/func_809B3CD0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Knight_0x809B20F0/func_809B3DAC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Knight_0x809B20F0/func_809B3E9C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Knight_0x809B20F0/func_809B3F0C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Knight_0x809B20F0/func_809B4024.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Knight_0x809B20F0/func_809B40E8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Knight_0x809B20F0/func_809B41D8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Knight_0x809B20F0/func_809B41F8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Knight_0x809B20F0/func_809B42B8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Knight_0x809B20F0/func_809B4308.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Knight_0x809B20F0/func_809B47EC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Knight_0x809B20F0/func_809B4880.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Knight_0x809B20F0/func_809B4BFC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Knight_0x809B20F0/func_809B4C58.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Knight_0x809B20F0/func_809B4E84.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Knight_0x809B20F0/func_809B4ED8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Knight_0x809B20F0/func_809B4F90.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Knight_0x809B20F0/func_809B5058.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Knight_0x809B20F0/func_809B51DC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Knight_0x809B20F0/func_809B52E8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Knight_0x809B20F0/func_809B5634.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Knight_0x809B20F0/func_809B5698.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Knight_0x809B20F0/func_809B58D4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Knight_0x809B20F0/func_809B592C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Knight_0x809B20F0/func_809B59FC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Knight_0x809B20F0/func_809B5B08.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Knight_0x809B20F0/func_809B5D38.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Knight_0x809B20F0/func_809B5D54.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Knight_0x809B20F0/func_809B5E90.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Knight_0x809B20F0/func_809B5ED0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Knight_0x809B20F0/func_809B5FA8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Knight_0x809B20F0/func_809B601C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Knight_0x809B20F0/func_809B631C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Knight_0x809B20F0/func_809B638C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Knight_0x809B20F0/func_809B6528.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Knight_0x809B20F0/func_809B6574.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Knight_0x809B20F0/func_809B6764.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Knight_0x809B20F0/func_809B6C04.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Knight_0x809B20F0/func_809B6C54.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Knight_0x809B20F0/func_809B6D38.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Knight_0x809B20F0/func_809B6D94.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Knight_0x809B20F0/func_809B6EC8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Knight_0x809B20F0/func_809B6F40.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Knight_0x809B20F0/func_809B7190.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Knight_0x809B20F0/func_809B71DC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Knight_0x809B20F0/func_809B7708.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Knight_0x809B20F0/func_809B7778.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Knight_0x809B20F0/func_809B78A4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Knight_0x809B20F0/func_809B7950.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Knight_0x809B20F0/func_809B842C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Knight_0x809B20F0/func_809B8458.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Knight_0x809B20F0/func_809B9A18.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Knight_0x809B20F0/func_809B9D24.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Knight_0x809B20F0/func_809B9E00.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Knight_0x809B20F0/func_809B9F8C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Knight_0x809B20F0/func_809BA058.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Knight_0x809B20F0/func_809BA0CC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Knight_0x809B20F0/func_809BA940.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Knight_0x809B20F0/func_809BA978.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Knight_0x809B20F0/EnKnight_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Knight_0x809B20F0/func_809BC2C4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Knight_0x809B20F0/func_809BC67C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Knight_0x809B20F0/func_809BC720.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Knight_0x809B20F0/func_809BC8B4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Knight_0x809B20F0/func_809BCA80.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Knight_0x809B20F0/func_809BCAD8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Knight_0x809B20F0/func_809BCB54.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Knight_0x809B20F0/func_809BCB78.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Knight_0x809B20F0/EnKnight_Draw.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Knight_0x809B20F0/func_809BD1AC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Knight_0x809B20F0/func_809BD260.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Knight_0x809B20F0/func_809BD29C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Knight_0x809B20F0/func_809BD490.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Knight_0x809B20F0/func_809BD858.asm")
