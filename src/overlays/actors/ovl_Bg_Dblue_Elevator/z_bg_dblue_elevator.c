#include "z_bg_dblue_elevator.h"

#define FLAGS 0x00000010

#define THIS ((BgDblueElevator*)thisx)

void BgDblueElevator_Init(Actor* thisx, GlobalContext* globalCtx);
void BgDblueElevator_Destroy(Actor* thisx, GlobalContext* globalCtx);
void BgDblueElevator_Update(Actor* thisx, GlobalContext* globalCtx);
void BgDblueElevator_Draw(Actor* thisx, GlobalContext* globalCtx);

#if 0
const ActorInit Bg_Dblue_Elevator_InitVars = {
    ACTOR_BG_DBLUE_ELEVATOR,
    ACTORCAT_BG,
    FLAGS,
    OBJECT_DBLUE_OBJECT,
    sizeof(BgDblueElevator),
    (ActorFunc)BgDblueElevator_Init,
    (ActorFunc)BgDblueElevator_Destroy,
    (ActorFunc)BgDblueElevator_Update,
    (ActorFunc)BgDblueElevator_Draw,
};


// static InitChainEntry sInitChain[] = {
static InitChainEntry D_80B929EC[] = {
    ICHAIN_F32(uncullZoneForward, 4000, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneScale, 250, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneDownward, 250, ICHAIN_CONTINUE),
    ICHAIN_VEC3F_DIV1000(scale, 100, ICHAIN_STOP),
};


extern InitChainEntry D_80B929EC[];
#endif

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Dblue_Elevator_0x80B91F20/func_80B91F20.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Dblue_Elevator_0x80B91F20/func_80B91F74.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Dblue_Elevator_0x80B91F20/func_80B922C0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Dblue_Elevator_0x80B91F20/func_80B922FC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Dblue_Elevator_0x80B91F20/BgDblueElevator_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Dblue_Elevator_0x80B91F20/BgDblueElevator_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Dblue_Elevator_0x80B91F20/func_80B924DC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Dblue_Elevator_0x80B91F20/func_80B924F8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Dblue_Elevator_0x80B91F20/func_80B9257C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Dblue_Elevator_0x80B91F20/func_80B925B8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Dblue_Elevator_0x80B91F20/func_80B92644.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Dblue_Elevator_0x80B91F20/func_80B92660.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Dblue_Elevator_0x80B91F20/BgDblueElevator_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Dblue_Elevator_0x80B91F20/BgDblueElevator_Draw.asm")
