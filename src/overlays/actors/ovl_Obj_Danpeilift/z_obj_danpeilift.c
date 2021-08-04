#include "z_obj_danpeilift.h"

#define FLAGS 0x00000010

#define THIS ((ObjDanpeilift*)thisx)

void ObjDanpeilift_Init(Actor* thisx, GlobalContext* globalCtx);
void ObjDanpeilift_Destroy(Actor* thisx, GlobalContext* globalCtx);
void ObjDanpeilift_Update(Actor* thisx, GlobalContext* globalCtx);
void ObjDanpeilift_Draw(Actor* thisx, GlobalContext* globalCtx);

#if 0
const ActorInit Obj_Danpeilift_InitVars = {
    ACTOR_OBJ_DANPEILIFT,
    ACTORCAT_BG,
    FLAGS,
    OBJECT_OBJECT_UNSET_DANPEILIFT,
    sizeof(ObjDanpeilift),
    (ActorFunc)ObjDanpeilift_Init,
    (ActorFunc)ObjDanpeilift_Destroy,
    (ActorFunc)ObjDanpeilift_Update,
    (ActorFunc)ObjDanpeilift_Draw,
};


// static InitChainEntry sInitChain[] = {
static InitChainEntry D_80C1B540[] = {
    ICHAIN_F32(uncullZoneForward, 4000, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneScale, 200, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneDownward, 400, ICHAIN_CONTINUE),
    ICHAIN_VEC3F_DIV1000(scale, 100, ICHAIN_STOP),
};


extern InitChainEntry D_80C1B540[];
#endif

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Danpeilift_0x80C1ADC0/func_80C1ADC0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Danpeilift_0x80C1ADC0/ObjDanpeilift_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Danpeilift_0x80C1ADC0/ObjDanpeilift_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Danpeilift_0x80C1ADC0/func_80C1AF84.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Danpeilift_0x80C1ADC0/func_80C1AF94.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Danpeilift_0x80C1ADC0/func_80C1B210.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Danpeilift_0x80C1ADC0/func_80C1B26C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Danpeilift_0x80C1ADC0/ObjDanpeilift_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Danpeilift_0x80C1ADC0/ObjDanpeilift_Draw.asm")
