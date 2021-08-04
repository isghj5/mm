#include "z_obj_hsblock.h"

#define FLAGS 0x00000000

#define THIS ((ObjHsblock*)thisx)

void ObjHsblock_Init(Actor* thisx, GlobalContext* globalCtx);
void ObjHsblock_Destroy(Actor* thisx, GlobalContext* globalCtx);
void ObjHsblock_Update(Actor* thisx, GlobalContext* globalCtx);
void ObjHsblock_Draw(Actor* thisx, GlobalContext* globalCtx);

#if 0
const ActorInit Obj_Hsblock_InitVars = {
    ACTOR_OBJ_HSBLOCK,
    ACTORCAT_BG,
    FLAGS,
    OBJECT_D_HSBLOCK,
    sizeof(ObjHsblock),
    (ActorFunc)ObjHsblock_Init,
    (ActorFunc)ObjHsblock_Destroy,
    (ActorFunc)ObjHsblock_Update,
    (ActorFunc)ObjHsblock_Draw,
};


// static InitChainEntry sInitChain[] = {
static InitChainEntry D_8093E33C[] = {
    ICHAIN_VEC3F_DIV1000(scale, 100, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneForward, 4000, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneScale, 100, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneDownward, 200, ICHAIN_STOP),
};


extern InitChainEntry D_8093E33C[];
#endif

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Hsblock_0x8093DEA0/func_8093DEA0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Hsblock_0x8093DEA0/func_8093DEAC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Hsblock_0x8093DEA0/ObjHsblock_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Hsblock_0x8093DEA0/ObjHsblock_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Hsblock_0x8093DEA0/func_8093E03C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Hsblock_0x8093DEA0/func_8093E05C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Hsblock_0x8093DEA0/func_8093E0A0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Hsblock_0x8093DEA0/func_8093E0E8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Hsblock_0x8093DEA0/func_8093E10C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Hsblock_0x8093DEA0/ObjHsblock_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Hsblock_0x8093DEA0/ObjHsblock_Draw.asm")
