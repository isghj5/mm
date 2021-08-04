#include "z_obj_boat.h"

#define FLAGS 0x00000010

#define THIS ((ObjBoat*)thisx)

void ObjBoat_Init(Actor* thisx, GlobalContext* globalCtx);
void ObjBoat_Destroy(Actor* thisx, GlobalContext* globalCtx);
void ObjBoat_Update(Actor* thisx, GlobalContext* globalCtx);
void ObjBoat_Draw(Actor* thisx, GlobalContext* globalCtx);

#if 0
const ActorInit Obj_Boat_InitVars = {
    ACTOR_OBJ_BOAT,
    ACTORCAT_BG,
    FLAGS,
    OBJECT_KAIZOKU_OBJ,
    sizeof(ObjBoat),
    (ActorFunc)ObjBoat_Init,
    (ActorFunc)ObjBoat_Destroy,
    (ActorFunc)ObjBoat_Update,
    (ActorFunc)ObjBoat_Draw,
};


// static InitChainEntry sInitChain[] = {
static InitChainEntry D_80B9B680[] = {
    ICHAIN_VEC3F_DIV1000(scale, 100, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneForward, 4000, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneScale, 1000, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneDownward, 1000, ICHAIN_STOP),
};


extern InitChainEntry D_80B9B680[];
#endif

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Boat_0x80B9AF50/func_80B9AF50.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Boat_0x80B9AF50/ObjBoat_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Boat_0x80B9AF50/ObjBoat_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Boat_0x80B9AF50/func_80B9B124.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Boat_0x80B9AF50/ObjBoat_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Boat_0x80B9AF50/func_80B9B428.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Boat_0x80B9AF50/ObjBoat_Draw.asm")
