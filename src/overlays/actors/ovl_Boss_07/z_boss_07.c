#include "z_boss_07.h"

#define FLAGS 0x00000035

#define THIS ((Boss07*)thisx)

void Boss07_Init(Actor* thisx, GlobalContext* globalCtx);
void Boss07_Destroy(Actor* thisx, GlobalContext* globalCtx);
void Boss07_Update(Actor* thisx, GlobalContext* globalCtx);
void Boss07_Draw(Actor* thisx, GlobalContext* globalCtx);

#if 0
// static DamageTable sDamageTable = {
static DamageTable D_80A07980 = {
    /* Deku Nut       */ DMG_ENTRY(0, 0x0),
    /* Deku Stick     */ DMG_ENTRY(1, 0xF),
    /* Horse trample  */ DMG_ENTRY(0, 0x0),
    /* Explosives     */ DMG_ENTRY(2, 0xF),
    /* Zora boomerang */ DMG_ENTRY(1, 0xF),
    /* Normal arrow   */ DMG_ENTRY(1, 0xF),
    /* UNK_DMG_0x06   */ DMG_ENTRY(0, 0x0),
    /* Hookshot       */ DMG_ENTRY(0, 0x0),
    /* Goron punch    */ DMG_ENTRY(1, 0xF),
    /* Sword          */ DMG_ENTRY(1, 0xF),
    /* Goron pound    */ DMG_ENTRY(1, 0xF),
    /* Fire arrow     */ DMG_ENTRY(2, 0x2),
    /* Ice arrow      */ DMG_ENTRY(2, 0x3),
    /* Light arrow    */ DMG_ENTRY(2, 0x4),
    /* Goron spikes   */ DMG_ENTRY(1, 0xF),
    /* Deku spin      */ DMG_ENTRY(1, 0xF),
    /* Deku bubble    */ DMG_ENTRY(1, 0xF),
    /* Deku launch    */ DMG_ENTRY(1, 0xF),
    /* UNK_DMG_0x12   */ DMG_ENTRY(0, 0x0),
    /* Zora barrier   */ DMG_ENTRY(0, 0x0),
    /* Normal shield  */ DMG_ENTRY(0, 0x0),
    /* Light ray      */ DMG_ENTRY(0, 0x0),
    /* Thrown object  */ DMG_ENTRY(1, 0xF),
    /* Zora punch     */ DMG_ENTRY(1, 0xF),
    /* Spin attack    */ DMG_ENTRY(2, 0xF),
    /* Sword beam     */ DMG_ENTRY(2, 0x9),
    /* Normal Roll    */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1B   */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1C   */ DMG_ENTRY(0, 0x0),
    /* Unblockable    */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1E   */ DMG_ENTRY(0, 0x0),
    /* Powder Keg     */ DMG_ENTRY(2, 0xF),
};


// static DamageTable sDamageTable = {
static DamageTable D_80A079A0 = {
    /* Deku Nut       */ DMG_ENTRY(0, 0x0),
    /* Deku Stick     */ DMG_ENTRY(1, 0xF),
    /* Horse trample  */ DMG_ENTRY(0, 0x0),
    /* Explosives     */ DMG_ENTRY(1, 0xC),
    /* Zora boomerang */ DMG_ENTRY(1, 0xF),
    /* Normal arrow   */ DMG_ENTRY(1, 0xF),
    /* UNK_DMG_0x06   */ DMG_ENTRY(0, 0x0),
    /* Hookshot       */ DMG_ENTRY(0, 0x0),
    /* Goron punch    */ DMG_ENTRY(1, 0xE),
    /* Sword          */ DMG_ENTRY(1, 0xE),
    /* Goron pound    */ DMG_ENTRY(1, 0xF),
    /* Fire arrow     */ DMG_ENTRY(2, 0x2),
    /* Ice arrow      */ DMG_ENTRY(2, 0x3),
    /* Light arrow    */ DMG_ENTRY(2, 0x4),
    /* Goron spikes   */ DMG_ENTRY(1, 0xF),
    /* Deku spin      */ DMG_ENTRY(1, 0xF),
    /* Deku bubble    */ DMG_ENTRY(1, 0xF),
    /* Deku launch    */ DMG_ENTRY(1, 0xF),
    /* UNK_DMG_0x12   */ DMG_ENTRY(0, 0x0),
    /* Zora barrier   */ DMG_ENTRY(0, 0xA),
    /* Normal shield  */ DMG_ENTRY(0, 0x0),
    /* Light ray      */ DMG_ENTRY(0, 0x0),
    /* Thrown object  */ DMG_ENTRY(1, 0xF),
    /* Zora punch     */ DMG_ENTRY(1, 0xF),
    /* Spin attack    */ DMG_ENTRY(1, 0xD),
    /* Sword beam     */ DMG_ENTRY(2, 0x9),
    /* Normal Roll    */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1B   */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1C   */ DMG_ENTRY(0, 0x0),
    /* Unblockable    */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1E   */ DMG_ENTRY(0, 0x0),
    /* Powder Keg     */ DMG_ENTRY(4, 0xC),
};


// static DamageTable sDamageTable = {
static DamageTable D_80A079C0 = {
    /* Deku Nut       */ DMG_ENTRY(0, 0x0),
    /* Deku Stick     */ DMG_ENTRY(1, 0xE),
    /* Horse trample  */ DMG_ENTRY(0, 0x0),
    /* Explosives     */ DMG_ENTRY(1, 0xC),
    /* Zora boomerang */ DMG_ENTRY(1, 0xF),
    /* Normal arrow   */ DMG_ENTRY(1, 0xF),
    /* UNK_DMG_0x06   */ DMG_ENTRY(0, 0x0),
    /* Hookshot       */ DMG_ENTRY(0, 0x0),
    /* Goron punch    */ DMG_ENTRY(1, 0xE),
    /* Sword          */ DMG_ENTRY(1, 0xE),
    /* Goron pound    */ DMG_ENTRY(1, 0xF),
    /* Fire arrow     */ DMG_ENTRY(2, 0x2),
    /* Ice arrow      */ DMG_ENTRY(2, 0x3),
    /* Light arrow    */ DMG_ENTRY(2, 0x4),
    /* Goron spikes   */ DMG_ENTRY(1, 0xE),
    /* Deku spin      */ DMG_ENTRY(1, 0xE),
    /* Deku bubble    */ DMG_ENTRY(1, 0xF),
    /* Deku launch    */ DMG_ENTRY(1, 0xE),
    /* UNK_DMG_0x12   */ DMG_ENTRY(0, 0x0),
    /* Zora barrier   */ DMG_ENTRY(0, 0xA),
    /* Normal shield  */ DMG_ENTRY(0, 0x0),
    /* Light ray      */ DMG_ENTRY(0, 0x0),
    /* Thrown object  */ DMG_ENTRY(1, 0xF),
    /* Zora punch     */ DMG_ENTRY(1, 0xE),
    /* Spin attack    */ DMG_ENTRY(1, 0xD),
    /* Sword beam     */ DMG_ENTRY(2, 0x9),
    /* Normal Roll    */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1B   */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1C   */ DMG_ENTRY(0, 0x0),
    /* Unblockable    */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1E   */ DMG_ENTRY(0, 0x0),
    /* Powder Keg     */ DMG_ENTRY(2, 0xC),
};


// static DamageTable sDamageTable = {
static DamageTable D_80A079E0 = {
    /* Deku Nut       */ DMG_ENTRY(0, 0x0),
    /* Deku Stick     */ DMG_ENTRY(1, 0xF),
    /* Horse trample  */ DMG_ENTRY(0, 0x0),
    /* Explosives     */ DMG_ENTRY(2, 0xE),
    /* Zora boomerang */ DMG_ENTRY(1, 0xF),
    /* Normal arrow   */ DMG_ENTRY(1, 0xF),
    /* UNK_DMG_0x06   */ DMG_ENTRY(0, 0x0),
    /* Hookshot       */ DMG_ENTRY(0, 0x0),
    /* Goron punch    */ DMG_ENTRY(1, 0xE),
    /* Sword          */ DMG_ENTRY(1, 0xE),
    /* Goron pound    */ DMG_ENTRY(1, 0xF),
    /* Fire arrow     */ DMG_ENTRY(2, 0x2),
    /* Ice arrow      */ DMG_ENTRY(2, 0x3),
    /* Light arrow    */ DMG_ENTRY(2, 0x4),
    /* Goron spikes   */ DMG_ENTRY(1, 0xF),
    /* Deku spin      */ DMG_ENTRY(1, 0xF),
    /* Deku bubble    */ DMG_ENTRY(1, 0xF),
    /* Deku launch    */ DMG_ENTRY(1, 0xF),
    /* UNK_DMG_0x12   */ DMG_ENTRY(0, 0x0),
    /* Zora barrier   */ DMG_ENTRY(0, 0x0),
    /* Normal shield  */ DMG_ENTRY(0, 0x0),
    /* Light ray      */ DMG_ENTRY(0, 0x0),
    /* Thrown object  */ DMG_ENTRY(1, 0xF),
    /* Zora punch     */ DMG_ENTRY(1, 0xF),
    /* Spin attack    */ DMG_ENTRY(1, 0xD),
    /* Sword beam     */ DMG_ENTRY(2, 0x9),
    /* Normal Roll    */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1B   */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1C   */ DMG_ENTRY(0, 0x0),
    /* Unblockable    */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1E   */ DMG_ENTRY(0, 0x0),
    /* Powder Keg     */ DMG_ENTRY(2, 0xE),
};


// static DamageTable sDamageTable = {
static DamageTable D_80A07A00 = {
    /* Deku Nut       */ DMG_ENTRY(0, 0x0),
    /* Deku Stick     */ DMG_ENTRY(1, 0xD),
    /* Horse trample  */ DMG_ENTRY(1, 0xE),
    /* Explosives     */ DMG_ENTRY(1, 0xB),
    /* Zora boomerang */ DMG_ENTRY(1, 0xF),
    /* Normal arrow   */ DMG_ENTRY(1, 0xF),
    /* UNK_DMG_0x06   */ DMG_ENTRY(0, 0x0),
    /* Hookshot       */ DMG_ENTRY(1, 0xE),
    /* Goron punch    */ DMG_ENTRY(1, 0xE),
    /* Sword          */ DMG_ENTRY(1, 0xD),
    /* Goron pound    */ DMG_ENTRY(0, 0x0),
    /* Fire arrow     */ DMG_ENTRY(1, 0xE),
    /* Ice arrow      */ DMG_ENTRY(1, 0xE),
    /* Light arrow    */ DMG_ENTRY(1, 0xE),
    /* Goron spikes   */ DMG_ENTRY(1, 0xC),
    /* Deku spin      */ DMG_ENTRY(1, 0xF),
    /* Deku bubble    */ DMG_ENTRY(1, 0xF),
    /* Deku launch    */ DMG_ENTRY(1, 0xF),
    /* UNK_DMG_0x12   */ DMG_ENTRY(0, 0x0),
    /* Zora barrier   */ DMG_ENTRY(0, 0x0),
    /* Normal shield  */ DMG_ENTRY(1, 0xD),
    /* Light ray      */ DMG_ENTRY(1, 0xD),
    /* Thrown object  */ DMG_ENTRY(1, 0xE),
    /* Zora punch     */ DMG_ENTRY(1, 0xE),
    /* Spin attack    */ DMG_ENTRY(1, 0xA),
    /* Sword beam     */ DMG_ENTRY(1, 0xA),
    /* Normal Roll    */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1B   */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1C   */ DMG_ENTRY(0, 0x0),
    /* Unblockable    */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1E   */ DMG_ENTRY(0, 0x0),
    /* Powder Keg     */ DMG_ENTRY(2, 0xB),
};


const ActorInit Boss_07_InitVars = {
    ACTOR_BOSS_07,
    ACTORCAT_BOSS,
    FLAGS,
    OBJECT_BOSS07,
    sizeof(Boss07),
    (ActorFunc)Boss07_Init,
    (ActorFunc)Boss07_Destroy,
    (ActorFunc)Boss07_Update,
    (ActorFunc)Boss07_Draw,
};


// static ColliderJntSphElementInit sJntSphElementsInit[11] = {
static ColliderJntSphElementInit D_80A07A40[11] = {
    {
        { ELEMTYPE_UNK3, { 0xF7CFFFFF, 0x00, 0x10 }, { 0xF7CEFFFE, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_ON, },
        { 0, { { 0, 0, 0 }, 20 }, 100 },
    },
    {
        { ELEMTYPE_UNK3, { 0xF7CFFFFF, 0x00, 0x10 }, { 0xF7CEFFFE, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_ON, },
        { 1, { { 0, 0, 0 }, 30 }, 100 },
    },
    {
        { ELEMTYPE_UNK3, { 0xF7CFFFFF, 0x00, 0x10 }, { 0xF7CEFFFE, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_ON, },
        { 1, { { 0, 0, 0 }, 25 }, 100 },
    },
    {
        { ELEMTYPE_UNK3, { 0xF7CFFFFF, 0x00, 0x10 }, { 0xF7CEFFFE, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_ON, },
        { 1, { { 0, 0, 0 }, 15 }, 100 },
    },
    {
        { ELEMTYPE_UNK3, { 0xF7CFFFFF, 0x00, 0x10 }, { 0xF7CEFFFE, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_ON, },
        { 1, { { 0, 0, 0 }, 15 }, 100 },
    },
    {
        { ELEMTYPE_UNK3, { 0xF7CFFFFF, 0x00, 0x10 }, { 0xF7CEFFFE, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_ON, },
        { 1, { { 0, 0, 0 }, 15 }, 100 },
    },
    {
        { ELEMTYPE_UNK3, { 0xF7CFFFFF, 0x00, 0x10 }, { 0xF7CEFFFE, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_ON, },
        { 1, { { 0, 0, 0 }, 15 }, 100 },
    },
    {
        { ELEMTYPE_UNK3, { 0xF7CFFFFF, 0x00, 0x10 }, { 0xF7CEFFFE, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_ON, },
        { 1, { { 0, 0, 0 }, 15 }, 150 },
    },
    {
        { ELEMTYPE_UNK3, { 0xF7CFFFFF, 0x00, 0x10 }, { 0xF7CEFFFE, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_ON, },
        { 1, { { 0, 0, 0 }, 15 }, 150 },
    },
    {
        { ELEMTYPE_UNK3, { 0xF7CFFFFF, 0x00, 0x10 }, { 0xF7CEFFFE, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_ON, },
        { 1, { { 0, 0, 0 }, 15 }, 150 },
    },
    {
        { ELEMTYPE_UNK3, { 0xF7CFFFFF, 0x00, 0x10 }, { 0xF7CEFFFE, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_ON, },
        { 1, { { 0, 0, 0 }, 15 }, 150 },
    },
};

// static ColliderJntSphInit sJntSphInit = {
static ColliderJntSphInit D_80A07BCC = {
    { COLTYPE_HIT3, AT_ON | AT_TYPE_ENEMY, AC_ON | AC_TYPE_PLAYER, OC1_ON | OC1_TYPE_PLAYER, OC2_TYPE_1, COLSHAPE_JNTSPH, },
    11, D_80A07A40, // sJntSphElementsInit,
};


// static ColliderCylinderInit sCylinderInit = {
static ColliderCylinderInit D_80A07BDC = {
    { COLTYPE_METAL, AT_ON | AT_TYPE_ENEMY, AC_ON | AC_TYPE_PLAYER, OC1_ON | OC1_TYPE_ALL, OC2_TYPE_1, COLSHAPE_CYLINDER, },
    { ELEMTYPE_UNK2, { 0xF7CFFFFF, 0x00, 0x10 }, { 0xF7CEFFFE, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_ON, },
    { 80, 200, 0, { 0, 0, 0 } },
};


// static ColliderJntSphElementInit sJntSphElementsInit[1] = {
static ColliderJntSphElementInit D_80A07C08[1] = {
    {
        { ELEMTYPE_UNK3, { 0xF7CFFFFF, 0x04, 0x10 }, { 0xF7CEFFFE, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_HARD, BUMP_ON, OCELEM_ON, },
        { 0, { { 0, 0, 0 }, 36 }, 200 },
    },
};

// static ColliderJntSphInit sJntSphInit = {
static ColliderJntSphInit D_80A07C2C = {
    { COLTYPE_HIT3, AT_ON | AT_TYPE_ENEMY, AC_ON | AC_TYPE_PLAYER, OC1_ON | OC1_TYPE_PLAYER, OC2_TYPE_1, COLSHAPE_JNTSPH, },
    1, D_80A07C08, // sJntSphElementsInit,
};


// static ColliderQuadInit sQuadInit = {
static ColliderQuadInit D_80A07C3C = {
    { COLTYPE_METAL, AT_ON | AT_TYPE_ENEMY, AC_ON | AC_HARD | AC_TYPE_PLAYER, OC1_ON | OC1_TYPE_ALL, OC2_TYPE_1, COLSHAPE_QUAD, },
    { ELEMTYPE_UNK2, { 0xF7CFFFFF, 0x04, 0x00 }, { 0xF7CEFFFE, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_ON, },
    { { { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } } },
};


// static ColliderQuadInit sQuadInit = {
static ColliderQuadInit D_80A07C8C = {
    { COLTYPE_HIT3, AT_ON | AT_TYPE_ENEMY, AC_ON | AC_TYPE_PLAYER, OC1_ON | OC1_TYPE_ALL, OC2_TYPE_1, COLSHAPE_QUAD, },
    { ELEMTYPE_UNK2, { 0xF7CFFFFF, 0x04, 0x10 }, { 0xF7CEFFFE, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_ON, },
    { { { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } } },
};


// static ColliderJntSphElementInit sJntSphElementsInit[11] = {
static ColliderJntSphElementInit D_80A07CDC[11] = {
    {
        { ELEMTYPE_UNK3, { 0xF7CFFFFF, 0x00, 0x10 }, { 0xF7CEFFFE, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_ON, },
        { 0, { { 0, 0, 0 }, 25 }, 100 },
    },
    {
        { ELEMTYPE_UNK3, { 0xF7CFFFFF, 0x00, 0x10 }, { 0xF7CEFFFE, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_ON, },
        { 1, { { 0, 0, 0 }, 40 }, 100 },
    },
    {
        { ELEMTYPE_UNK3, { 0xF7CFFFFF, 0x00, 0x10 }, { 0xF7CEFFFE, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_ON, },
        { 1, { { 0, 0, 0 }, 0 }, 0 },
    },
    {
        { ELEMTYPE_UNK3, { 0xF7CFFFFF, 0x00, 0x10 }, { 0xF7CEFFFE, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_ON, },
        { 1, { { 0, 0, 0 }, 15 }, 100 },
    },
    {
        { ELEMTYPE_UNK3, { 0xF7CFFFFF, 0x00, 0x10 }, { 0xF7CEFFFE, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_ON, },
        { 1, { { 0, 0, 0 }, 15 }, 100 },
    },
    {
        { ELEMTYPE_UNK3, { 0xF7CFFFFF, 0x00, 0x10 }, { 0xF7CEFFFE, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_ON, },
        { 1, { { 0, 0, 0 }, 15 }, 100 },
    },
    {
        { ELEMTYPE_UNK3, { 0xF7CFFFFF, 0x00, 0x10 }, { 0xF7CEFFFE, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_ON, },
        { 1, { { 0, 0, 0 }, 15 }, 100 },
    },
    {
        { ELEMTYPE_UNK3, { 0xF7CFFFFF, 0x00, 0x10 }, { 0xF7CEFFFE, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_ON, },
        { 1, { { 0, 0, 0 }, 15 }, 150 },
    },
    {
        { ELEMTYPE_UNK3, { 0xF7CFFFFF, 0x00, 0x10 }, { 0xF7CEFFFE, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_ON, },
        { 1, { { 0, 0, 0 }, 15 }, 150 },
    },
    {
        { ELEMTYPE_UNK3, { 0xF7CFFFFF, 0x00, 0x10 }, { 0xF7CEFFFE, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_ON, },
        { 1, { { 0, 0, 0 }, 15 }, 150 },
    },
    {
        { ELEMTYPE_UNK3, { 0xF7CFFFFF, 0x00, 0x10 }, { 0xF7CEFFFE, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_ON, },
        { 1, { { 0, 0, 0 }, 15 }, 150 },
    },
};

// static ColliderJntSphInit sJntSphInit = {
static ColliderJntSphInit D_80A07E68 = {
    { COLTYPE_HIT3, AT_ON | AT_TYPE_ENEMY, AC_ON | AC_TYPE_PLAYER, OC1_ON | OC1_TYPE_PLAYER, OC2_TYPE_1, COLSHAPE_JNTSPH, },
    11, D_80A07CDC, // sJntSphElementsInit,
};


// static ColliderCylinderInit sCylinderInit = {
static ColliderCylinderInit D_80A07E78 = {
    { COLTYPE_NONE, AT_ON | AT_TYPE_ENEMY, AC_ON | AC_TYPE_PLAYER, OC1_ON | OC1_TYPE_ALL, OC2_TYPE_1, COLSHAPE_CYLINDER, },
    { ELEMTYPE_UNK0, { 0xF7CFFFFF, 0x04, 0x10 }, { 0x00300000, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_ON, },
    { 15, 30, -15, { 0, 0, 0 } },
};


// static ColliderCylinderInit sCylinderInit = {
static ColliderCylinderInit D_80A07EA4 = {
    { COLTYPE_METAL, AT_ON | AT_TYPE_ENEMY, AC_ON | AC_TYPE_PLAYER, OC1_ON | OC1_TYPE_ALL, OC2_TYPE_1, COLSHAPE_CYLINDER, },
    { ELEMTYPE_UNK0, { 0xF7CFFFFF, 0x04, 0x10 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_NORMAL, BUMP_ON | BUMP_HOOKABLE, OCELEM_ON, },
    { 50, 100, -50, { 0, 0, 0 } },
};


// static ColliderCylinderInit sCylinderInit = {
static ColliderCylinderInit D_80A07ED0 = {
    { COLTYPE_METAL, AT_ON | AT_TYPE_ENEMY, AC_ON | AC_HARD | AC_TYPE_PLAYER, OC1_ON | OC1_TYPE_ALL, OC2_TYPE_1, COLSHAPE_CYLINDER, },
    { ELEMTYPE_UNK0, { 0xF7CFFFFF, 0x04, 0x10 }, { 0xF7FFFFFF, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_NORMAL, BUMP_ON | BUMP_HOOKABLE, OCELEM_ON, },
    { 40, 20, 15, { 0, 0, 0 } },
};


extern DamageTable D_80A07980;
extern DamageTable D_80A079A0;
extern DamageTable D_80A079C0;
extern DamageTable D_80A079E0;
extern DamageTable D_80A07A00;
extern ColliderJntSphElementInit D_80A07A40[11];
extern ColliderJntSphInit D_80A07BCC;
extern ColliderCylinderInit D_80A07BDC;
extern ColliderJntSphElementInit D_80A07C08[1];
extern ColliderJntSphInit D_80A07C2C;
extern ColliderQuadInit D_80A07C3C;
extern ColliderQuadInit D_80A07C8C;
extern ColliderJntSphElementInit D_80A07CDC[11];
extern ColliderJntSphInit D_80A07E68;
extern ColliderCylinderInit D_80A07E78;
extern ColliderCylinderInit D_80A07EA4;
extern ColliderCylinderInit D_80A07ED0;
#endif

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_07_0x809F4980/func_809F4980.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_07_0x809F4980/func_809F49A0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_07_0x809F4980/func_809F49C0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_07_0x809F4980/func_809F4AE8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_07_0x809F4980/func_809F4BB0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_07_0x809F4980/func_809F4C40.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_07_0x809F4980/func_809F4CBC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_07_0x809F4980/func_809F4D10.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_07_0x809F4980/func_809F4D54.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_07_0x809F4980/func_809F4FAC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_07_0x809F4980/func_809F4FF8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_07_0x809F4980/func_809F51E8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_07_0x809F4980/func_809F52CC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_07_0x809F4980/func_809F536C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_07_0x809F4980/func_809F5494.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_07_0x809F4980/Boss07_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_07_0x809F4980/Boss07_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_07_0x809F4980/func_809F5E14.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_07_0x809F4980/func_809F5E88.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_07_0x809F4980/func_809F64F4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_07_0x809F4980/func_809F65F4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_07_0x809F4980/func_809F7400.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_07_0x809F4980/func_809F748C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_07_0x809F4980/func_809F7688.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_07_0x809F4980/func_809F76D0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_07_0x809F4980/func_809F77A8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_07_0x809F4980/func_809F783C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_07_0x809F4980/func_809F7968.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_07_0x809F4980/func_809F7AB4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_07_0x809F4980/func_809F7BC4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_07_0x809F4980/func_809F7D2C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_07_0x809F4980/func_809F805C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_07_0x809F4980/func_809F8658.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_07_0x809F4980/func_809F86B8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_07_0x809F4980/func_809F87C8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_07_0x809F4980/func_809F8908.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_07_0x809F4980/func_809F8AB0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_07_0x809F4980/func_809F8B1C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_07_0x809F4980/func_809F8D04.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_07_0x809F4980/func_809F8DEC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_07_0x809F4980/func_809F8E68.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_07_0x809F4980/func_809F8EC8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_07_0x809F4980/func_809F91D4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_07_0x809F4980/func_809F9280.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_07_0x809F4980/func_809F93DC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_07_0x809F4980/func_809F94AC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_07_0x809F4980/func_809F99C4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_07_0x809F4980/func_809F9CEC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_07_0x809F4980/func_809F9E94.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_07_0x809F4980/Boss07_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_07_0x809F4980/func_809FAA44.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_07_0x809F4980/func_809FB114.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_07_0x809F4980/func_809FB504.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_07_0x809F4980/func_809FB55C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_07_0x809F4980/func_809FB728.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_07_0x809F4980/func_809FB7D4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_07_0x809F4980/func_809FBB9C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_07_0x809F4980/func_809FBF94.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_07_0x809F4980/Boss07_Draw.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_07_0x809F4980/func_809FC4C0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_07_0x809F4980/func_809FC8B0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_07_0x809F4980/func_809FC960.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_07_0x809F4980/func_809FCBC8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_07_0x809F4980/func_809FCC70.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_07_0x809F4980/func_809FCCCC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_07_0x809F4980/func_809FD5F8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_07_0x809F4980/func_809FD710.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_07_0x809F4980/func_809FD818.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_07_0x809F4980/func_809FD89C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_07_0x809F4980/func_809FD984.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_07_0x809F4980/func_809FDAB0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_07_0x809F4980/func_809FDB2C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_07_0x809F4980/func_809FDBA0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_07_0x809F4980/func_809FDEDC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_07_0x809F4980/func_809FDF54.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_07_0x809F4980/func_809FE068.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_07_0x809F4980/func_809FE0E4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_07_0x809F4980/func_809FE2D4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_07_0x809F4980/func_809FE348.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_07_0x809F4980/func_809FE4B0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_07_0x809F4980/func_809FE524.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_07_0x809F4980/func_809FE6B0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_07_0x809F4980/func_809FE734.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_07_0x809F4980/func_809FEE70.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_07_0x809F4980/func_809FF0E4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_07_0x809F4980/func_809FF12C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_07_0x809F4980/func_809FF5CC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_07_0x809F4980/func_809FF678.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_07_0x809F4980/func_809FF6B0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_07_0x809F4980/func_809FF810.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_07_0x809F4980/func_809FF900.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_07_0x809F4980/func_809FFA04.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_07_0x809F4980/func_809FFA80.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_07_0x809F4980/func_809FFE64.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_07_0x809F4980/func_809FFEAC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_07_0x809F4980/func_80A0021C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_07_0x809F4980/func_80A00274.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_07_0x809F4980/func_80A00484.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_07_0x809F4980/func_80A00554.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_07_0x809F4980/func_80A006D0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_07_0x809F4980/func_80A006F4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_07_0x809F4980/func_80A00720.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_07_0x809F4980/func_80A016E4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_07_0x809F4980/func_80A01750.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_07_0x809F4980/func_80A025AC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_07_0x809F4980/func_80A0264C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_07_0x809F4980/func_80A02B30.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_07_0x809F4980/func_80A02C54.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_07_0x809F4980/func_80A03238.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_07_0x809F4980/func_80A036C4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_07_0x809F4980/func_80A03868.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_07_0x809F4980/func_80A03F18.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_07_0x809F4980/func_80A03F5C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_07_0x809F4980/func_80A0434C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_07_0x809F4980/func_80A045A8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_07_0x809F4980/func_80A04768.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_07_0x809F4980/func_80A04878.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_07_0x809F4980/func_80A04890.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_07_0x809F4980/func_80A04DE0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_07_0x809F4980/func_80A04E5C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_07_0x809F4980/func_80A055E0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_07_0x809F4980/func_80A05608.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_07_0x809F4980/func_80A05694.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_07_0x809F4980/func_80A057A0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_07_0x809F4980/func_80A05AF8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_07_0x809F4980/func_80A05B50.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_07_0x809F4980/func_80A05C88.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_07_0x809F4980/func_80A05DDC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_07_0x809F4980/func_80A06500.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_07_0x809F4980/func_80A06990.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_07_0x809F4980/func_80A06C64.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_07_0x809F4980/func_80A06E24.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_07_0x809F4980/func_80A06F48.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_07_0x809F4980/func_80A07604.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_07_0x809F4980/func_80A07638.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_07_0x809F4980/func_80A07740.asm")
