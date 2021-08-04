#include "z_obj_usiyane.h"

#define FLAGS 0x00000020

#define THIS ((ObjUsiyane*)thisx)

void ObjUsiyane_Init(Actor* thisx, GlobalContext* globalCtx);
void ObjUsiyane_Destroy(Actor* thisx, GlobalContext* globalCtx);
void ObjUsiyane_Update(Actor* thisx, GlobalContext* globalCtx);
void ObjUsiyane_Draw(Actor* thisx, GlobalContext* globalCtx);

#if 0
const ActorInit Obj_Usiyane_InitVars = {
    ACTOR_OBJ_USIYANE,
    ACTORCAT_PROP,
    FLAGS,
    OBJECT_OBJECT_UNSET_USIYANE,
    sizeof(ObjUsiyane),
    (ActorFunc)ObjUsiyane_Init,
    (ActorFunc)ObjUsiyane_Destroy,
    (ActorFunc)ObjUsiyane_Update,
    (ActorFunc)ObjUsiyane_Draw,
};


// static InitChainEntry sInitChain[] = {
static InitChainEntry D_80C086B0[] = {
    ICHAIN_F32(uncullZoneScale, 1200, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneForward, 3000, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneDownward, 900, ICHAIN_STOP),
};


extern InitChainEntry D_80C086B0[];
#endif

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Usiyane_0x80C07C80/func_80C07C80.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Usiyane_0x80C07C80/func_80C07CD0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Usiyane_0x80C07C80/func_80C07DC4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Usiyane_0x80C07C80/func_80C07DFC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Usiyane_0x80C07C80/func_80C07F30.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Usiyane_0x80C07C80/func_80C081C8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Usiyane_0x80C07C80/func_80C082CC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Usiyane_0x80C07C80/func_80C082E0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Usiyane_0x80C07C80/ObjUsiyane_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Usiyane_0x80C07C80/ObjUsiyane_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Usiyane_0x80C07C80/ObjUsiyane_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Usiyane_0x80C07C80/ObjUsiyane_Draw.asm")
