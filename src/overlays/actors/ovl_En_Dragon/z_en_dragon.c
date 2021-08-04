#include "z_en_dragon.h"

#define FLAGS 0x00000035

#define THIS ((EnDragon*)thisx)

void EnDragon_Init(Actor* thisx, GlobalContext* globalCtx);
void EnDragon_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnDragon_Update(Actor* thisx, GlobalContext* globalCtx);
void EnDragon_Draw(Actor* thisx, GlobalContext* globalCtx);

#if 0
const ActorInit En_Dragon_InitVars = {
    ACTOR_EN_DRAGON,
    ACTORCAT_ENEMY,
    FLAGS,
    OBJECT_UTUBO,
    sizeof(EnDragon),
    (ActorFunc)EnDragon_Init,
    (ActorFunc)EnDragon_Destroy,
    (ActorFunc)EnDragon_Update,
    (ActorFunc)EnDragon_Draw,
};


// static DamageTable sDamageTable = {
static DamageTable D_80B605F4 = {
    /* Deku Nut       */ DMG_ENTRY(0, 0x0),
    /* Deku Stick     */ DMG_ENTRY(0, 0x0),
    /* Horse trample  */ DMG_ENTRY(0, 0x0),
    /* Explosives     */ DMG_ENTRY(1, 0xF),
    /* Zora boomerang */ DMG_ENTRY(1, 0xF),
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
    /* Zora barrier   */ DMG_ENTRY(1, 0xF),
    /* Normal shield  */ DMG_ENTRY(0, 0x0),
    /* Light ray      */ DMG_ENTRY(0, 0x0),
    /* Thrown object  */ DMG_ENTRY(0, 0x0),
    /* Zora punch     */ DMG_ENTRY(1, 0xF),
    /* Spin attack    */ DMG_ENTRY(0, 0x0),
    /* Sword beam     */ DMG_ENTRY(0, 0x0),
    /* Normal Roll    */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1B   */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1C   */ DMG_ENTRY(0, 0x0),
    /* Unblockable    */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1E   */ DMG_ENTRY(0, 0x0),
    /* Powder Keg     */ DMG_ENTRY(1, 0xF),
};


// static ColliderJntSphElementInit sJntSphElementsInit[8] = {
static ColliderJntSphElementInit D_80B60614[8] = {
    {
        { ELEMTYPE_UNK1, { 0xF7CFFFFF, 0x00, 0x00 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_ON, },
        { 13, { { 0, 0, 0 }, 0 }, 1 },
    },
    {
        { ELEMTYPE_UNK1, { 0xF7CFFFFF, 0x00, 0x00 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_ON, },
        { 12, { { 0, 0, 0 }, 0 }, 1 },
    },
    {
        { ELEMTYPE_UNK1, { 0xF7CFFFFF, 0x00, 0x00 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_ON, },
        { 12, { { 0, 0, 0 }, 0 }, 1 },
    },
    {
        { ELEMTYPE_UNK1, { 0xF7CFFFFF, 0x00, 0x00 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_ON, },
        { 10, { { 0, 0, 0 }, 0 }, 1 },
    },
    {
        { ELEMTYPE_UNK1, { 0xF7CFFFFF, 0x00, 0x00 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_ON, },
        { 10, { { 0, 0, 0 }, 0 }, 1 },
    },
    {
        { ELEMTYPE_UNK1, { 0xF7CFFFFF, 0x00, 0x00 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_ON, },
        { 9, { { 0, 0, 0 }, 0 }, 1 },
    },
    {
        { ELEMTYPE_UNK1, { 0xF7CFFFFF, 0x00, 0x00 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_ON, },
        { 9, { { 0, 0, 0 }, 0 }, 1 },
    },
    {
        { ELEMTYPE_UNK1, { 0xF7CFFFFF, 0x00, 0x00 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_ON, },
        { 9, { { 0, 0, 0 }, 0 }, 1 },
    },
};

// static ColliderJntSphInit sJntSphInit = {
static ColliderJntSphInit D_80B60734 = {
    { COLTYPE_HIT6, AT_NONE, AC_ON | AC_TYPE_PLAYER, OC1_ON | OC1_TYPE_PLAYER, OC2_TYPE_1, COLSHAPE_JNTSPH, },
    8, D_80B60614, // sJntSphElementsInit,
};


extern DamageTable D_80B605F4;
extern ColliderJntSphElementInit D_80B60614[8];
extern ColliderJntSphInit D_80B60734;
#endif

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dragon_0x80B5E890/EnDragon_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dragon_0x80B5E890/EnDragon_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dragon_0x80B5E890/func_80B5EAA0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dragon_0x80B5E890/func_80B5EB40.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dragon_0x80B5E890/func_80B5ED90.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dragon_0x80B5E890/func_80B5EDF0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dragon_0x80B5E890/func_80B5EE3C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dragon_0x80B5E890/func_80B5EF88.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dragon_0x80B5E890/func_80B5EFD0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dragon_0x80B5E890/func_80B5F3A4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dragon_0x80B5E890/func_80B5F418.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dragon_0x80B5E890/func_80B5F508.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dragon_0x80B5E890/func_80B5F888.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dragon_0x80B5E890/func_80B5F8D8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dragon_0x80B5E890/func_80B5FCC0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dragon_0x80B5E890/func_80B5FD68.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dragon_0x80B5E890/func_80B60138.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dragon_0x80B5E890/EnDragon_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dragon_0x80B5E890/func_80B6043C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dragon_0x80B5E890/func_80B60494.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dragon_0x80B5E890/EnDragon_Draw.asm")
