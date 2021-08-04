#include "z_obj_lift.h"

#define FLAGS 0x00000010

#define THIS ((ObjLift*)thisx)

void ObjLift_Init(Actor* thisx, GlobalContext* globalCtx);
void ObjLift_Destroy(Actor* thisx, GlobalContext* globalCtx);
void ObjLift_Update(Actor* thisx, GlobalContext* globalCtx);
void ObjLift_Draw(Actor* thisx, GlobalContext* globalCtx);

#if 0
const ActorInit Obj_Lift_InitVars = {
    ACTOR_OBJ_LIFT,
    ACTORCAT_BG,
    FLAGS,
    OBJECT_D_LIFT,
    sizeof(ObjLift),
    (ActorFunc)ObjLift_Init,
    (ActorFunc)ObjLift_Destroy,
    (ActorFunc)ObjLift_Update,
    (ActorFunc)ObjLift_Draw,
};


// static InitChainEntry sInitChain[] = {
static InitChainEntry D_8093DD84[] = {
    ICHAIN_F32_DIV1000(gravity, -600, ICHAIN_CONTINUE),
    ICHAIN_F32_DIV1000(minVelocityY, -15000, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneForward, 4000, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneScale, 350, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneDownward, 350, ICHAIN_STOP),
};


extern InitChainEntry D_8093DD84[];
#endif

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Lift_0x8093D3C0/func_8093D3C0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Lift_0x8093D3C0/ObjLift_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Lift_0x8093D3C0/ObjLift_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Lift_0x8093D3C0/func_8093D760.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Lift_0x8093D3C0/func_8093D7A0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Lift_0x8093D3C0/func_8093D88C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Lift_0x8093D3C0/func_8093D8B4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Lift_0x8093D3C0/func_8093D9C0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Lift_0x8093D3C0/func_8093DA48.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Lift_0x8093D3C0/func_8093DB70.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Lift_0x8093D3C0/func_8093DB90.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Lift_0x8093D3C0/ObjLift_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Lift_0x8093D3C0/ObjLift_Draw.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Lift_0x8093D3C0/func_8093DC90.asm")
