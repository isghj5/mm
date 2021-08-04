#include "z_obj_lupygamelift.h"

#define FLAGS 0x00000030

#define THIS ((ObjLupygamelift*)thisx)

void ObjLupygamelift_Init(Actor* thisx, GlobalContext* globalCtx);
void ObjLupygamelift_Destroy(Actor* thisx, GlobalContext* globalCtx);
void ObjLupygamelift_Update(Actor* thisx, GlobalContext* globalCtx);
void ObjLupygamelift_Draw(Actor* thisx, GlobalContext* globalCtx);

#if 0
const ActorInit Obj_Lupygamelift_InitVars = {
    ACTOR_OBJ_LUPYGAMELIFT,
    ACTORCAT_BG,
    FLAGS,
    OBJECT_RAILLIFT,
    sizeof(ObjLupygamelift),
    (ActorFunc)ObjLupygamelift_Init,
    (ActorFunc)ObjLupygamelift_Destroy,
    (ActorFunc)ObjLupygamelift_Update,
    (ActorFunc)ObjLupygamelift_Draw,
};


// static InitChainEntry sInitChain[] = {
static InitChainEntry D_80AF0740[] = {
    ICHAIN_F32(uncullZoneForward, 4000, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneScale, 200, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneDownward, 400, ICHAIN_CONTINUE),
    ICHAIN_VEC3F_DIV1000(scale, 100, ICHAIN_STOP),
};


extern InitChainEntry D_80AF0740[];
#endif

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Lupygamelift_0x80AF0170/ObjLupygamelift_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Lupygamelift_0x80AF0170/ObjLupygamelift_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Lupygamelift_0x80AF0170/func_80AF0394.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Lupygamelift_0x80AF0170/func_80AF04BC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Lupygamelift_0x80AF0170/func_80AF04D8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Lupygamelift_0x80AF0170/func_80AF0514.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Lupygamelift_0x80AF0170/func_80AF0530.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Lupygamelift_0x80AF0170/ObjLupygamelift_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Lupygamelift_0x80AF0170/ObjLupygamelift_Draw.asm")
