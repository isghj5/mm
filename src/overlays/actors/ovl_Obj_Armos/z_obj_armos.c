#include "z_obj_armos.h"

#define FLAGS 0x04000010

#define THIS ((ObjArmos*)thisx)

void ObjArmos_Init(Actor* thisx, GlobalContext* globalCtx);
void ObjArmos_Destroy(Actor* thisx, GlobalContext* globalCtx);
void ObjArmos_Update(Actor* thisx, GlobalContext* globalCtx);
void ObjArmos_Draw(Actor* thisx, GlobalContext* globalCtx);

#if 0
const ActorInit Obj_Armos_InitVars = {
    ACTOR_OBJ_ARMOS,
    ACTORCAT_PROP,
    FLAGS,
    OBJECT_AM,
    sizeof(ObjArmos),
    (ActorFunc)ObjArmos_Init,
    (ActorFunc)ObjArmos_Destroy,
    (ActorFunc)ObjArmos_Update,
    (ActorFunc)ObjArmos_Draw,
};


// static InitChainEntry sInitChain[] = {
static InitChainEntry D_809A5BC0[] = {
    ICHAIN_F32(uncullZoneForward, 4000, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneScale, 120, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneDownward, 250, ICHAIN_CONTINUE),
    ICHAIN_F32_DIV1000(gravity, -4000, ICHAIN_CONTINUE),
    ICHAIN_VEC3F_DIV1000(scale, 10, ICHAIN_STOP),
};


extern InitChainEntry D_809A5BC0[];
#endif

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Armos_0x809A4E00/func_809A4E00.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Armos_0x809A4E00/func_809A4E68.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Armos_0x809A4E00/func_809A4F00.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Armos_0x809A4E00/func_809A500C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Armos_0x809A4E00/func_809A518C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Armos_0x809A4E00/ObjArmos_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Armos_0x809A4E00/ObjArmos_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Armos_0x809A4E00/func_809A54B4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Armos_0x809A4E00/func_809A54E0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Armos_0x809A4E00/func_809A5610.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Armos_0x809A4E00/func_809A562C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Armos_0x809A4E00/func_809A57D8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Armos_0x809A4E00/func_809A57F4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Armos_0x809A4E00/ObjArmos_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Armos_0x809A4E00/func_809A5960.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Armos_0x809A4E00/func_809A5A3C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Armos_0x809A4E00/ObjArmos_Draw.asm")
