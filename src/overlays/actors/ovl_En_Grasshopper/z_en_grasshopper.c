#include "z_en_grasshopper.h"

#define FLAGS 0x00000015

#define THIS ((EnGrasshopper*)thisx)

void EnGrasshopper_Init(Actor* thisx, GlobalContext* globalCtx);
void EnGrasshopper_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnGrasshopper_Update(Actor* thisx, GlobalContext* globalCtx);
void EnGrasshopper_Draw(Actor* thisx, GlobalContext* globalCtx);

#if 0
// static DamageTable sDamageTable = {
static DamageTable D_809A8CDC = {
    /* Deku Nut       */ DMG_ENTRY(1, 0xF),
    /* Deku Stick     */ DMG_ENTRY(1, 0xF),
    /* Horse trample  */ DMG_ENTRY(0, 0x0),
    /* Explosives     */ DMG_ENTRY(1, 0xF),
    /* Zora boomerang */ DMG_ENTRY(1, 0xF),
    /* Normal arrow   */ DMG_ENTRY(1, 0xF),
    /* UNK_DMG_0x06   */ DMG_ENTRY(0, 0x0),
    /* Hookshot       */ DMG_ENTRY(0, 0xE),
    /* Goron punch    */ DMG_ENTRY(1, 0xF),
    /* Sword          */ DMG_ENTRY(1, 0xF),
    /* Goron pound    */ DMG_ENTRY(0, 0xF),
    /* Fire arrow     */ DMG_ENTRY(2, 0x2),
    /* Ice arrow      */ DMG_ENTRY(2, 0x3),
    /* Light arrow    */ DMG_ENTRY(2, 0x4),
    /* Goron spikes   */ DMG_ENTRY(1, 0xF),
    /* Deku spin      */ DMG_ENTRY(1, 0xF),
    /* Deku bubble    */ DMG_ENTRY(1, 0xF),
    /* Deku launch    */ DMG_ENTRY(2, 0xF),
    /* UNK_DMG_0x12   */ DMG_ENTRY(1, 0xF),
    /* Zora barrier   */ DMG_ENTRY(1, 0xF),
    /* Normal shield  */ DMG_ENTRY(0, 0x0),
    /* Light ray      */ DMG_ENTRY(0, 0x0),
    /* Thrown object  */ DMG_ENTRY(1, 0xF),
    /* Zora punch     */ DMG_ENTRY(1, 0xF),
    /* Spin attack    */ DMG_ENTRY(1, 0xF),
    /* Sword beam     */ DMG_ENTRY(0, 0x0),
    /* Normal Roll    */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1B   */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1C   */ DMG_ENTRY(0, 0x0),
    /* Unblockable    */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1E   */ DMG_ENTRY(0, 0x0),
    /* Powder Keg     */ DMG_ENTRY(1, 0xE),
};


const ActorInit En_Grasshopper_InitVars = {
    ACTOR_EN_GRASSHOPPER,
    ACTORCAT_ENEMY,
    FLAGS,
    OBJECT_GRASSHOPPER,
    sizeof(EnGrasshopper),
    (ActorFunc)EnGrasshopper_Init,
    (ActorFunc)EnGrasshopper_Destroy,
    (ActorFunc)EnGrasshopper_Update,
    (ActorFunc)EnGrasshopper_Draw,
};


// static ColliderJntSphElementInit sJntSphElementsInit[2] = {
static ColliderJntSphElementInit D_809A8D1C[2] = {
    {
        { ELEMTYPE_UNK3, { 0xF7CFFFFF, 0x00, 0x00 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_NORMAL, BUMP_ON | BUMP_HOOKABLE, OCELEM_ON, },
        { 7, { { 0, 0, 0 }, 0 }, 0 },
    },
    {
        { ELEMTYPE_UNK2, { 0xF7CFFFFF, 0x07, 0x04 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_NONE, },
        { 6, { { 0, 0, 0 }, 0 }, 0 },
    },
};

// static ColliderJntSphInit sJntSphInit = {
static ColliderJntSphInit D_809A8D64 = {
    { COLTYPE_HIT2, AT_ON | AT_TYPE_ENEMY, AC_ON | AC_TYPE_PLAYER, OC1_ON | OC1_TYPE_1, OC2_TYPE_1, COLSHAPE_JNTSPH, },
    2, D_809A8D1C, // sJntSphElementsInit,
};


extern DamageTable D_809A8CDC;
extern ColliderJntSphElementInit D_809A8D1C[2];
extern ColliderJntSphInit D_809A8D64;
#endif

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Grasshopper_0x809A6280/EnGrasshopper_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Grasshopper_0x809A6280/EnGrasshopper_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Grasshopper_0x809A6280/func_809A6524.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Grasshopper_0x809A6280/func_809A65D8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Grasshopper_0x809A6280/func_809A6628.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Grasshopper_0x809A6280/func_809A6668.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Grasshopper_0x809A6280/func_809A6754.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Grasshopper_0x809A6280/func_809A67A4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Grasshopper_0x809A6280/func_809A6B6C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Grasshopper_0x809A6280/func_809A6E18.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Grasshopper_0x809A6280/func_809A6E74.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Grasshopper_0x809A6280/func_809A6F8C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Grasshopper_0x809A6280/func_809A700C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Grasshopper_0x809A6280/func_809A7134.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Grasshopper_0x809A6280/func_809A71CC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Grasshopper_0x809A6280/func_809A7494.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Grasshopper_0x809A6280/func_809A753C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Grasshopper_0x809A6280/func_809A7844.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Grasshopper_0x809A6280/func_809A78EC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Grasshopper_0x809A6280/func_809A797C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Grasshopper_0x809A6280/func_809A7A8C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Grasshopper_0x809A6280/func_809A7AE4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Grasshopper_0x809A6280/func_809A7BBC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Grasshopper_0x809A6280/func_809A7C98.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Grasshopper_0x809A6280/func_809A7CE0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Grasshopper_0x809A6280/func_809A8044.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Grasshopper_0x809A6280/EnGrasshopper_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Grasshopper_0x809A6280/func_809A847C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Grasshopper_0x809A6280/EnGrasshopper_Draw.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Grasshopper_0x809A6280/func_809A8870.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Grasshopper_0x809A6280/func_809A8924.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Grasshopper_0x809A6280/func_809A8A64.asm")
