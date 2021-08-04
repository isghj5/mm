#include "z_obj_aqua.h"

#define FLAGS 0x00000010

#define THIS ((ObjAqua*)thisx)

void ObjAqua_Init(Actor* thisx, GlobalContext* globalCtx);
void ObjAqua_Destroy(Actor* thisx, GlobalContext* globalCtx);
void ObjAqua_Update(Actor* thisx, GlobalContext* globalCtx);
void ObjAqua_Draw(Actor* thisx, GlobalContext* globalCtx);

#if 0
const ActorInit Obj_Aqua_InitVars = {
    ACTOR_OBJ_AQUA,
    ACTORCAT_ITEMACTION,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(ObjAqua),
    (ActorFunc)ObjAqua_Init,
    (ActorFunc)ObjAqua_Destroy,
    (ActorFunc)ObjAqua_Update,
    (ActorFunc)ObjAqua_Draw,
};


// static ColliderCylinderInit sCylinderInit = {
static ColliderCylinderInit D_80ACC2C0 = {
    { COLTYPE_NONE, AT_ON | AT_TYPE_OTHER, AC_NONE, OC1_NONE, OC2_NONE, COLSHAPE_CYLINDER, },
    { ELEMTYPE_UNK0, { 0xF7CFFFFF, 0x00, 0x00 }, { 0x00000000, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_NONE, BUMP_NONE, OCELEM_NONE, },
    { 6, 10, 0, { 0, 0, 0 } },
};


// static InitChainEntry sInitChain[] = {
static InitChainEntry D_80ACC2EC[] = {
    ICHAIN_VEC3S(shape.rot, 0, ICHAIN_CONTINUE),
    ICHAIN_VEC3S(world.rot, 0, ICHAIN_CONTINUE),
    ICHAIN_F32_DIV1000(gravity, -900, ICHAIN_CONTINUE),
    ICHAIN_F32_DIV1000(minVelocityY, -4000, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneForward, 4000, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneScale, 300, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneDownward, 300, ICHAIN_STOP),
};


extern ColliderCylinderInit D_80ACC2C0;
extern InitChainEntry D_80ACC2EC[];
#endif

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Aqua_0x80ACB6A0/func_80ACB6A0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Aqua_0x80ACB6A0/func_80ACB7F4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Aqua_0x80ACB6A0/func_80ACB940.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Aqua_0x80ACB6A0/func_80ACBA10.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Aqua_0x80ACB6A0/func_80ACBA60.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Aqua_0x80ACB6A0/ObjAqua_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Aqua_0x80ACB6A0/ObjAqua_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Aqua_0x80ACB6A0/func_80ACBC70.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Aqua_0x80ACB6A0/func_80ACBC8C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Aqua_0x80ACB6A0/func_80ACBD34.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Aqua_0x80ACB6A0/func_80ACBD48.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Aqua_0x80ACB6A0/func_80ACBDCC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Aqua_0x80ACB6A0/func_80ACBDFC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Aqua_0x80ACB6A0/ObjAqua_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Aqua_0x80ACB6A0/ObjAqua_Draw.asm")
