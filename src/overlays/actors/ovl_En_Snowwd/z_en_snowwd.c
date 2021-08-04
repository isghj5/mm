#include "z_en_snowwd.h"

#define FLAGS 0x00000000

#define THIS ((EnSnowwd*)thisx)

void EnSnowwd_Init(Actor* thisx, GlobalContext* globalCtx);
void EnSnowwd_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnSnowwd_Update(Actor* thisx, GlobalContext* globalCtx);
void EnSnowwd_Draw(Actor* thisx, GlobalContext* globalCtx);

#if 0
const ActorInit En_Snowwd_InitVars = {
    ACTOR_EN_SNOWWD,
    ACTORCAT_PROP,
    FLAGS,
    OBJECT_SNOWWD,
    sizeof(EnSnowwd),
    (ActorFunc)EnSnowwd_Init,
    (ActorFunc)EnSnowwd_Destroy,
    (ActorFunc)EnSnowwd_Update,
    (ActorFunc)EnSnowwd_Draw,
};


// static ColliderCylinderInit sCylinderInit = {
static ColliderCylinderInit D_80AF7A90 = {
    { COLTYPE_TREE, AT_NONE, AC_ON | AC_HARD | AC_TYPE_PLAYER, OC1_ON | OC1_TYPE_ALL, OC2_TYPE_1, COLSHAPE_CYLINDER, },
    { ELEMTYPE_UNK5, { 0x00000000, 0x00, 0x00 }, { 0x0100020A, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_ON, },
    { 18, 60, 0, { 0, 0, 0 } },
};


extern ColliderCylinderInit D_80AF7A90;
#endif

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Snowwd_0x80AF7640/EnSnowwd_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Snowwd_0x80AF7640/EnSnowwd_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Snowwd_0x80AF7640/func_80AF76F0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Snowwd_0x80AF7640/EnSnowwd_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Snowwd_0x80AF7640/EnSnowwd_Draw.asm")
