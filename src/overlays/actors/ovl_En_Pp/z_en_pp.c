#include "z_en_pp.h"

#define FLAGS 0x00000005

#define THIS ((EnPp*)thisx)

void EnPp_Init(Actor* thisx, GlobalContext* globalCtx);
void EnPp_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnPp_Update(Actor* thisx, GlobalContext* globalCtx);
void EnPp_Draw(Actor* thisx, GlobalContext* globalCtx);

#if 0
// static DamageTable sDamageTable = {
static DamageTable D_80B21624 = {
    /* Deku Nut       */ DMG_ENTRY(0, 0x1),
    /* Deku Stick     */ DMG_ENTRY(1, 0xF),
    /* Horse trample  */ DMG_ENTRY(0, 0x0),
    /* Explosives     */ DMG_ENTRY(1, 0xC),
    /* Zora boomerang */ DMG_ENTRY(1, 0xF),
    /* Normal arrow   */ DMG_ENTRY(1, 0xF),
    /* UNK_DMG_0x06   */ DMG_ENTRY(0, 0x0),
    /* Hookshot       */ DMG_ENTRY(1, 0xD),
    /* Goron punch    */ DMG_ENTRY(1, 0xC),
    /* Sword          */ DMG_ENTRY(1, 0xF),
    /* Goron pound    */ DMG_ENTRY(0, 0xE),
    /* Fire arrow     */ DMG_ENTRY(1, 0x2),
    /* Ice arrow      */ DMG_ENTRY(1, 0x3),
    /* Light arrow    */ DMG_ENTRY(2, 0x4),
    /* Goron spikes   */ DMG_ENTRY(1, 0xF),
    /* Deku spin      */ DMG_ENTRY(0, 0x1),
    /* Deku bubble    */ DMG_ENTRY(1, 0xF),
    /* Deku launch    */ DMG_ENTRY(2, 0xC),
    /* UNK_DMG_0x12   */ DMG_ENTRY(0, 0x1),
    /* Zora barrier   */ DMG_ENTRY(0, 0x5),
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
    /* Powder Keg     */ DMG_ENTRY(1, 0xC),
};


const ActorInit En_Pp_InitVars = {
    ACTOR_EN_PP,
    ACTORCAT_ENEMY,
    FLAGS,
    OBJECT_PP,
    sizeof(EnPp),
    (ActorFunc)EnPp_Init,
    (ActorFunc)EnPp_Destroy,
    (ActorFunc)EnPp_Update,
    (ActorFunc)EnPp_Draw,
};


// static ColliderJntSphElementInit sJntSphElementsInit[1] = {
static ColliderJntSphElementInit D_80B21664[1] = {
    {
        { ELEMTYPE_UNK2, { 0xF7CFFFFF, 0x04, 0x10 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_NORMAL, BUMP_ON | BUMP_HOOKABLE, OCELEM_ON, },
        { 1, { { 0, 0, 0 }, 0 }, 1 },
    },
};

// static ColliderJntSphInit sJntSphInit = {
static ColliderJntSphInit D_80B21688 = {
    { COLTYPE_HARD, AT_ON | AT_TYPE_ENEMY, AC_ON | AC_TYPE_PLAYER, OC1_ON | OC1_TYPE_ALL, OC2_TYPE_1, COLSHAPE_JNTSPH, },
    1, D_80B21664, // sJntSphElementsInit,
};


// static ColliderJntSphElementInit sJntSphElementsInit[1] = {
static ColliderJntSphElementInit D_80B21698[1] = {
    {
        { ELEMTYPE_UNK0, { 0xF7CFFFFF, 0x04, 0x04 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_NORMAL, BUMP_ON | BUMP_HOOKABLE, OCELEM_ON, },
        { 1, { { 0, 0, 0 }, 0 }, 1 },
    },
};

// static ColliderJntSphInit sJntSphInit = {
static ColliderJntSphInit D_80B216BC = {
    { COLTYPE_HARD, AT_ON | AT_TYPE_ENEMY, AC_ON | AC_TYPE_PLAYER, OC1_ON | OC1_TYPE_ALL, OC2_TYPE_1, COLSHAPE_JNTSPH, },
    1, D_80B21698, // sJntSphElementsInit,
};


// static ColliderQuadInit sQuadInit = {
static ColliderQuadInit D_80B216CC = {
    { COLTYPE_NONE, AT_ON | AT_TYPE_ENEMY, AC_NONE, OC1_NONE, OC2_NONE, COLSHAPE_QUAD, },
    { ELEMTYPE_UNK0, { 0xF7CFFFFF, 0x04, 0x08 }, { 0x00000000, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_NORMAL | TOUCH_UNK7, BUMP_NONE, OCELEM_NONE, },
    { { { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } } },
};


extern DamageTable D_80B21624;
extern ColliderJntSphElementInit D_80B21664[1];
extern ColliderJntSphInit D_80B21688;
extern ColliderJntSphElementInit D_80B21698[1];
extern ColliderJntSphInit D_80B216BC;
extern ColliderQuadInit D_80B216CC;
#endif

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Pp_0x80B1DEB0/EnPp_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Pp_0x80B1DEB0/EnPp_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Pp_0x80B1DEB0/func_80B1E29C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Pp_0x80B1DEB0/func_80B1E3D4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Pp_0x80B1DEB0/func_80B1E5A8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Pp_0x80B1DEB0/func_80B1E680.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Pp_0x80B1DEB0/func_80B1E778.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Pp_0x80B1DEB0/func_80B1E958.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Pp_0x80B1DEB0/func_80B1E970.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Pp_0x80B1DEB0/func_80B1EBD8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Pp_0x80B1DEB0/func_80B1EC24.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Pp_0x80B1DEB0/func_80B1EFFC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Pp_0x80B1DEB0/func_80B1F048.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Pp_0x80B1DEB0/func_80B1F0A4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Pp_0x80B1DEB0/func_80B1F188.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Pp_0x80B1DEB0/func_80B1F244.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Pp_0x80B1DEB0/func_80B1F29C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Pp_0x80B1DEB0/func_80B1F4A0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Pp_0x80B1DEB0/func_80B1F560.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Pp_0x80B1DEB0/func_80B1F664.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Pp_0x80B1DEB0/func_80B1F6B4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Pp_0x80B1DEB0/func_80B1F770.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Pp_0x80B1DEB0/func_80B1F940.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Pp_0x80B1DEB0/func_80B1FAD0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Pp_0x80B1DEB0/func_80B1FC7C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Pp_0x80B1DEB0/func_80B1FF20.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Pp_0x80B1DEB0/func_80B20030.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Pp_0x80B1DEB0/func_80B202B8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Pp_0x80B1DEB0/func_80B203BC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Pp_0x80B1DEB0/func_80B20668.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Pp_0x80B1DEB0/EnPp_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Pp_0x80B1DEB0/func_80B20E6C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Pp_0x80B1DEB0/func_80B20F70.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Pp_0x80B1DEB0/EnPp_Draw.asm")
