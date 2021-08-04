#include "z_en_scopecrow.h"

#define FLAGS 0x00000030

#define THIS ((EnScopecrow*)thisx)

void EnScopecrow_Init(Actor* thisx, GlobalContext* globalCtx);
void EnScopecrow_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnScopecrow_Update(Actor* thisx, GlobalContext* globalCtx);
void EnScopecrow_Draw(Actor* thisx, GlobalContext* globalCtx);

#if 0
const ActorInit En_Scopecrow_InitVars = {
    ACTOR_EN_SCOPECROW,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_CROW,
    sizeof(EnScopecrow),
    (ActorFunc)EnScopecrow_Init,
    (ActorFunc)EnScopecrow_Destroy,
    (ActorFunc)EnScopecrow_Update,
    (ActorFunc)EnScopecrow_Draw,
};


// static ColliderJntSphElementInit sJntSphElementsInit[1] = {
static ColliderJntSphElementInit D_80BCDB70[1] = {
    {
        { ELEMTYPE_UNK0, { 0x00000000, 0x00, 0x00 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_ON, },
        { 1, { { 0, 60, 0 }, 50 }, 100 },
    },
};

// static ColliderJntSphInit sJntSphInit = {
static ColliderJntSphInit D_80BCDB94 = {
    { COLTYPE_HIT3, AT_NONE, AC_ON | AC_TYPE_PLAYER, OC1_ON | OC1_TYPE_ALL, OC2_TYPE_1, COLSHAPE_JNTSPH, },
    1, D_80BCDB70, // sJntSphElementsInit,
};


extern ColliderJntSphElementInit D_80BCDB70[1];
extern ColliderJntSphInit D_80BCDB94;
#endif

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Scopecrow_0x80BCD000/func_80BCD000.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Scopecrow_0x80BCD000/func_80BCD09C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Scopecrow_0x80BCD000/func_80BCD1AC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Scopecrow_0x80BCD000/func_80BCD2BC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Scopecrow_0x80BCD000/func_80BCD334.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Scopecrow_0x80BCD000/func_80BCD4D0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Scopecrow_0x80BCD000/func_80BCD590.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Scopecrow_0x80BCD000/func_80BCD640.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Scopecrow_0x80BCD000/EnScopecrow_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Scopecrow_0x80BCD000/EnScopecrow_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Scopecrow_0x80BCD000/EnScopecrow_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Scopecrow_0x80BCD000/EnScopecrow_Draw.asm")
