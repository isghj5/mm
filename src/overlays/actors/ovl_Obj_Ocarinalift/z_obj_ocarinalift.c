#include "z_obj_ocarinalift.h"

#define FLAGS 0x00000010

#define THIS ((ObjOcarinalift*)thisx)

void ObjOcarinalift_Init(Actor* thisx, GlobalContext* globalCtx);
void ObjOcarinalift_Destroy(Actor* thisx, GlobalContext* globalCtx);
void ObjOcarinalift_Update(Actor* thisx, GlobalContext* globalCtx);
void ObjOcarinalift_Draw(Actor* thisx, GlobalContext* globalCtx);

#if 0
const ActorInit Obj_Ocarinalift_InitVars = {
    ACTOR_OBJ_OCARINALIFT,
    ACTORCAT_BG,
    FLAGS,
    OBJECT_RAILLIFT,
    sizeof(ObjOcarinalift),
    (ActorFunc)ObjOcarinalift_Init,
    (ActorFunc)ObjOcarinalift_Destroy,
    (ActorFunc)ObjOcarinalift_Update,
    (ActorFunc)ObjOcarinalift_Draw,
};


// static InitChainEntry sInitChain[] = {
static InitChainEntry D_80AC9D70[] = {
    ICHAIN_U8(targetMode, 2, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneForward, 4000, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneScale, 200, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneDownward, 300, ICHAIN_CONTINUE),
    ICHAIN_VEC3F_DIV1000(scale, 100, ICHAIN_STOP),
};


extern InitChainEntry D_80AC9D70[];
#endif

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Ocarinalift_0x80AC94C0/func_80AC94C0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Ocarinalift_0x80AC94C0/ObjOcarinalift_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Ocarinalift_0x80AC94C0/ObjOcarinalift_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Ocarinalift_0x80AC94C0/func_80AC9680.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Ocarinalift_0x80AC94C0/func_80AC96A4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Ocarinalift_0x80AC94C0/func_80AC96B4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Ocarinalift_0x80AC94C0/func_80AC96D0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Ocarinalift_0x80AC94C0/func_80AC99C0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Ocarinalift_0x80AC94C0/func_80AC99D4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Ocarinalift_0x80AC94C0/func_80AC9A68.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Ocarinalift_0x80AC94C0/func_80AC9A7C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Ocarinalift_0x80AC94C0/func_80AC9AB8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Ocarinalift_0x80AC94C0/func_80AC9AE0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Ocarinalift_0x80AC94C0/func_80AC9B48.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Ocarinalift_0x80AC94C0/func_80AC9B5C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Ocarinalift_0x80AC94C0/func_80AC9C20.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Ocarinalift_0x80AC94C0/func_80AC9C48.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Ocarinalift_0x80AC94C0/ObjOcarinalift_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Ocarinalift_0x80AC94C0/ObjOcarinalift_Draw.asm")
