#include "z_obj_rotlift.h"

#define FLAGS 0x00000000

#define THIS ((ObjRotlift*)thisx)

void ObjRotlift_Init(Actor* thisx, GlobalContext* globalCtx);
void ObjRotlift_Destroy(Actor* thisx, GlobalContext* globalCtx);
void ObjRotlift_Update(Actor* thisx, GlobalContext* globalCtx);
void ObjRotlift_Draw(Actor* thisx, GlobalContext* globalCtx);

#if 0
const ActorInit Obj_Rotlift_InitVars = {
    ACTOR_OBJ_ROTLIFT,
    ACTORCAT_BG,
    FLAGS,
    OBJECT_ROTLIFT,
    sizeof(ObjRotlift),
    (ActorFunc)ObjRotlift_Init,
    (ActorFunc)ObjRotlift_Destroy,
    (ActorFunc)ObjRotlift_Update,
    (ActorFunc)ObjRotlift_Draw,
};


// static InitChainEntry sInitChain[] = {
static InitChainEntry D_80B96178[] = {
    ICHAIN_VEC3F_DIV1000(scale, 100, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneForward, 4000, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneScale, 800, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneDownward, 800, ICHAIN_STOP),
};


extern InitChainEntry D_80B96178[];
#endif

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Rotlift_0x80B95E20/func_80B95E20.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Rotlift_0x80B95E20/ObjRotlift_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Rotlift_0x80B95E20/ObjRotlift_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Rotlift_0x80B95E20/ObjRotlift_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Rotlift_0x80B95E20/ObjRotlift_Draw.asm")
