#include "z_bg_f40_swlift.h"

#define FLAGS 0x00000010

#define THIS ((BgF40Swlift*)thisx)

void BgF40Swlift_Init(Actor* thisx, GlobalContext* globalCtx);
void BgF40Swlift_Destroy(Actor* thisx, GlobalContext* globalCtx);
void BgF40Swlift_Update(Actor* thisx, GlobalContext* globalCtx);
void BgF40Swlift_Draw(Actor* thisx, GlobalContext* globalCtx);

#if 0
const ActorInit Bg_F40_Swlift_InitVars = {
    ACTOR_BG_F40_SWLIFT,
    ACTORCAT_BG,
    FLAGS,
    OBJECT_F40_OBJ,
    sizeof(BgF40Swlift),
    (ActorFunc)BgF40Swlift_Init,
    (ActorFunc)BgF40Swlift_Destroy,
    (ActorFunc)BgF40Swlift_Update,
    (ActorFunc)BgF40Swlift_Draw,
};


// static InitChainEntry sInitChain[] = {
static InitChainEntry D_8096F540[] = {
    ICHAIN_F32(uncullZoneScale, 550, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneForward, 5000, ICHAIN_CONTINUE),
    ICHAIN_VEC3F_DIV1000(scale, 100, ICHAIN_STOP),
};


extern InitChainEntry D_8096F540[];
#endif

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_F40_Swlift_0x8096F160/BgF40Swlift_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_F40_Swlift_0x8096F160/BgF40Swlift_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_F40_Swlift_0x8096F160/BgF40Swlift_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_F40_Swlift_0x8096F160/BgF40Swlift_Draw.asm")
