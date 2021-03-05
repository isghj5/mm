#include "z_en_niw.h"

#define FLAGS 0x00800010

#define THIS ((EnNiw*)thisx)

void EnNiw_Init(Actor* thisx, GlobalContext* globalCtx);
void EnNiw_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnNiw_Update(Actor* thisx, GlobalContext* globalCtx);
void EnNiw_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_80891D78(EnNiw* this, GlobalContext* globalCtx);

u32 D_80893460 = 0x0; // padding?

/*
const ActorInit En_Niw_InitVars = {
    ACTOR_EN_NIW,
    ACTORCAT_PROP,
    FLAGS,
    OBJECT_NIW,
    sizeof(EnNiw),
    (ActorFunc)EnNiw_Init,
    (ActorFunc)EnNiw_Destroy,
    (ActorFunc)EnNiw_Update,
    (ActorFunc)EnNiw_Draw
};
*/

u32 D_80893484[] = {
 0x459C4000,
 0xC59C4000,
};

u32 D_8089348C = 0x459C4000; 

u32 D_80893490[] = {
 0x453B8000,
 0x457A0000,
};

u32 D_80893498[] = { // collider
 0x0500093D,
 0x20010000,
 0x00000000,
 0x00000000,
 0x00000000,
 0xF7CFFFFF,
 0x00000000,
 0x00010100,
 0x000F0019,
 0x00040000,
 0x00000000,
};

Vec3f D_808934C4 = {
 90000.0f,
 90000.0f,
 90000.0f,
};

u32 D_808934D0[] = {
 0x801F0006,
 0xB874F830,
 0x30540000,
};

u32 D_808934DC[] = {
 0x47AFC800,
 0x47AFC800,
 0x47AFC800,
};

u32 D_808934E8[] = {
 0x47AFC800,
 0x47AFC800,
 0x47AFC800,
 0x00000000,
 0x00000000,
 0x00000000,
};

void EnNiw_Init(Actor *thisx, GlobalContext *globalCtx) {
    // NON matching: one stack offset issue and struct is wrong

    EnNiw* this = THIS;
    PosRot *worldPosRotTemp;
    Vec3f D_Temp = D_808934C4;

    if ( this->actor.params < 0) { //no bit 16 I guess
        this->actor.params = 0;
    }


    Math_Vec3f_Copy( &this->unk2BC, &D_Temp);


    this->paramsCopy = this->actor.params;
    Actor_ProcessInitChain(thisx, &D_808934D0);
    thisx->flags |= 1;
    Actor_SetDrawParams(&thisx->shape, 0.0f, func_800B3FC0, 25.0f);

    SkelAnime_InitSV(globalCtx, &this->skelanime,  
        &D_6002530, &D_60000E8,
         &this->limbDrawTbl, &this->transitionDrawtable, 0x10);
    worldPosRotTemp = &this->actor.world;
    Math_Vec3f_Copy(&this->unk2A4, &worldPosRotTemp->pos);
    //Math_Vec3f_Copy(&this->unk2B0, worldPosRotTemp.rot);
    Math_Vec3f_Copy(&this->unk2B0, &worldPosRotTemp->pos);

    this->unk308 = 10.0f;
    Actor_SetScale(&this->actor, 0.01f);

    if (this->paramsCopy == 1) {
        Actor_SetScale(&this->actor, ((f32) gStaticContext->data[2486] / D_80893500) + D_80893504);
    }
    thisx->colChkInfo.health = (u8) (u32) (randZeroOneScaled(D_80893508) + 10.0f);
    thisx->colChkInfo.mass = 0xFF;
    if (this->paramsCopy == 0) {
        Collision_InitCylinder(globalCtx, &this->collider, &this->actor, &D_80893498);
    }
    if (this->paramsCopy == 2) {
        func_800B8EC8(thisx, 0x2813U);
        this->unk256 = (u16)0x1E;
        this->unk250 = (u16)0x1E;
        thisx->flags &= ~1;
        this->unk28E = (u16)4;
        this->actionFunc = func_80891D78;
        thisx->speedXZ = 0.0f;
        this->unk2BC.z = 0.0f;
        thisx->velocity.y = 0.0f;
        thisx->gravity = 0.0f;
        return;
    }
    func_80891974(thisx);
}

//#pragma GLOBAL_ASM("asm/non_matchings/ovl_En_Niw_0x80891060/EnNiw_Init.asm")

#pragma GLOBAL_ASM("asm/non_matchings/ovl_En_Niw_0x80891060/EnNiw_Destroy.asm")

#pragma GLOBAL_ASM("asm/non_matchings/ovl_En_Niw_0x80891060/func_80891320.asm")

#pragma GLOBAL_ASM("asm/non_matchings/ovl_En_Niw_0x80891060/func_808916B0.asm")

#pragma GLOBAL_ASM("asm/non_matchings/ovl_En_Niw_0x80891060/func_808917F8.asm")

#pragma GLOBAL_ASM("asm/non_matchings/ovl_En_Niw_0x80891060/func_80891974.asm")

#pragma GLOBAL_ASM("asm/non_matchings/ovl_En_Niw_0x80891060/func_808919E8.asm")

#pragma GLOBAL_ASM("asm/non_matchings/ovl_En_Niw_0x80891060/func_80891D78.asm")

#pragma GLOBAL_ASM("asm/non_matchings/ovl_En_Niw_0x80891060/func_80891F60.asm")

#pragma GLOBAL_ASM("asm/non_matchings/ovl_En_Niw_0x80891060/func_808920A0.asm")

#pragma GLOBAL_ASM("asm/non_matchings/ovl_En_Niw_0x80891060/func_80892248.asm")

#pragma GLOBAL_ASM("asm/non_matchings/ovl_En_Niw_0x80891060/func_80892274.asm")

#pragma GLOBAL_ASM("asm/non_matchings/ovl_En_Niw_0x80891060/func_808922D0.asm")

#pragma GLOBAL_ASM("asm/non_matchings/ovl_En_Niw_0x80891060/func_80892390.asm")

#pragma GLOBAL_ASM("asm/non_matchings/ovl_En_Niw_0x80891060/func_80892414.asm")

#pragma GLOBAL_ASM("asm/non_matchings/ovl_En_Niw_0x80891060/func_808924B0.asm")

#pragma GLOBAL_ASM("asm/non_matchings/ovl_En_Niw_0x80891060/func_808925F8.asm")

#pragma GLOBAL_ASM("asm/non_matchings/ovl_En_Niw_0x80891060/func_8089262C.asm")

#pragma GLOBAL_ASM("asm/non_matchings/ovl_En_Niw_0x80891060/EnNiw_Update.asm")

#pragma GLOBAL_ASM("asm/non_matchings/ovl_En_Niw_0x80891060/func_80892E70.asm")

#pragma GLOBAL_ASM("asm/non_matchings/ovl_En_Niw_0x80891060/EnNiw_Draw.asm")

#pragma GLOBAL_ASM("asm/non_matchings/ovl_En_Niw_0x80891060/func_80893008.asm")

#pragma GLOBAL_ASM("asm/non_matchings/ovl_En_Niw_0x80891060/func_808930FC.asm")

#pragma GLOBAL_ASM("asm/non_matchings/ovl_En_Niw_0x80891060/func_808932B0.asm")
