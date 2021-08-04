#include "z_bg_umajump.h"

#define FLAGS 0x00000000

#define THIS ((BgUmajump*)thisx)

void BgUmajump_Init(Actor* thisx, GlobalContext* globalCtx);
void BgUmajump_Destroy(Actor* thisx, GlobalContext* globalCtx);
void BgUmajump_Update(Actor* thisx, GlobalContext* globalCtx);

#if 0
const ActorInit Bg_Umajump_InitVars = {
    ACTOR_BG_UMAJUMP,
    ACTORCAT_PROP,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(BgUmajump),
    (ActorFunc)BgUmajump_Init,
    (ActorFunc)BgUmajump_Destroy,
    (ActorFunc)BgUmajump_Update,
    (ActorFunc)NULL,
};


// static InitChainEntry sInitChain[] = {
static InitChainEntry D_8091A810[] = {
    ICHAIN_F32(uncullZoneScale, 1200, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneDownward, 300, ICHAIN_CONTINUE),
    ICHAIN_VEC3F_DIV1000(scale, 100, ICHAIN_STOP),
};


extern InitChainEntry D_8091A810[];
#endif

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Umajump_0x80919F30/func_80919F30.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Umajump_0x80919F30/func_80919FC8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Umajump_0x80919F30/func_8091A044.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Umajump_0x80919F30/func_8091A0B8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Umajump_0x80919F30/BgUmajump_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Umajump_0x80919F30/BgUmajump_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Umajump_0x80919F30/BgUmajump_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Umajump_0x80919F30/func_8091A5A0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Umajump_0x80919F30/func_8091A7B0.asm")
