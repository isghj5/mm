#include "z_en_look_nuts.h"

#define FLAGS 0x80000000

#define THIS ((EnLookNuts*)thisx)

void EnLookNuts_Init(Actor* thisx, GlobalContext* globalCtx);
void EnLookNuts_Destroy(Actor* thisx, GlobalContext* globalCtx);
//void EnLookNuts_Update(Actor* thisx, GlobalContext* globalCtx);
//void EnLookNuts_Draw(Actor* thisx, GlobalContext* globalCtx);
//void EnLookNuts_Init(EnLookNuts* this, GlobalContext* globalCtx);
void EnLookNuts_Update(EnLookNuts* this, GlobalContext* globalCtx);
void EnLookNuts_Draw(EnLookNuts* this, GlobalContext* globalCtx);

void func_80A67A34(EnLookNuts* this);
void func_80A67C48(EnLookNuts* this);
void func_80A67F30(EnLookNuts* this);
void func_80A68080(EnLookNuts* this);

void func_80A67AA8(EnLookNuts* this, GlobalContext* globalCtx);
void func_80A67D0C(EnLookNuts* this, GlobalContext* globalCtx);
void func_80A67FC4(EnLookNuts* this, GlobalContext* globalCtx);
void func_80A680FC(EnLookNuts* this, GlobalContext* globalCtx);

/*
const ActorInit En_Look_Nuts_InitVars = {
    ACTOR_EN_LOOK_NUTS,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_DNK,
    sizeof(EnLookNuts),
    (ActorFunc)EnLookNuts_Init,
    (ActorFunc)EnLookNuts_Destroy,
    (ActorFunc)EnLookNuts_Update,
    (ActorFunc)EnLookNuts_Draw,
};
*/

extern DamageTable D_80A68630;
extern u32 D_80A68600[];
extern u32 D_06002848[];
extern u32 D_06000430[];

void EnLookNuts_Init(Actor* thisx, GlobalContext *globalCtx) {
    EnLookNuts* this = (EnLookNuts*)thisx;

    ActorShape_Init(&this->actor.shape, 0.0f, func_800B3FC0, 20.0f);
    SkelAnime_Init(globalCtx, &this->skelAnime, &D_06002848, &D_06000430, this->limbDrawTbl, this->transitionDrawTable, LOOKNUTS_LIMB_COUNT);
    Actor_SetScale(&this->actor, 0.01f); // default is huge?
    this->actor.colChkInfo.damageTable = &D_80A68630; // why damage table ????
    this->actor.colChkInfo.mass = 0xFF; //immovable? why? so you cant push them? they have no collider
    this->actor.targetMode = 1;

    Collider_InitAndSetCylinder(globalCtx, &this->collider, (Actor *) this, &D_80A68600);
    this->actor.flags |= 0x8000000;
    this->paramsCopy2 = (this->actor.params >> 7) & 0x1F;
    this->switchFlag = this->actor.params & 0x7F;
    this->unk226 = (this->actor.params >> 0xC) & 0xF;
  
    // all vanilla use 0x7F, so unused beta content?
    if (this->switchFlag == 0x7F) {
        this->switchFlag = -1;
    }
    if (this->switchFlag >= 0 && Flags_GetSwitch(globalCtx, this->switchFlag)) {
        Actor_MarkForDeath((Actor *) this);
    } else if (this->paramsCopy2 == 0x1F) {
        Actor_MarkForDeath((Actor *) this);
    } else {
        this->unk21C = 0;
        func_80A67A34(this);
    }
}

void EnLookNuts_Destroy(Actor *thisx, GlobalContext *globalCtx) {
    EnLookNuts* this = (EnLookNuts*)thisx;
    Collider_DestroyCylinder(globalCtx, &this->collider);
}

extern u32 D_06002B6C[];

void func_80A67A34(EnLookNuts *this) {
    SkelAnime_ChangeAnim(&this->skelAnime, D_06002B6C, 1.0f, 0.0f, SkelAnime_GetFrameCount(D_06002B6C), 0, -10.0f);
    this->unk21C = 0;
    this->actionFunc = func_80A67AA8;
}

extern u32 D_80A6862C;

void func_80A67AA8(EnLookNuts *this, GlobalContext *globalCtx) {
    s32 sp34;
    f32 sp30;
    //Vec3f sp30;
    //SkelAnime *sp2C;
    //SkelAnime *temp_a0;
    s8 *temp_v0;
    s8 *temp_v0_2;

    //temp_a0 = &this->skelAnime;
    //sp2C = temp_a0;
    //sp30.y = 0.0f;
    sp34 = 0.0f;
    SkelAnime_FrameUpdateMatrix(&this->skelAnime);
    if (func_801690CC(globalCtx) != 0) {
        this->actor.speedXZ = 0.0f;
        return;
    }
    this->actor.speedXZ = 2.0f;
    if ((func_801378B8(&this->skelAnime, 1.0f) != 0) || (func_801378B8(&this->skelAnime, 5.0f) != 0)) {
        Audio_PlayActorSound2((Actor *) this, (u16)0x387FU);
    }
    if (D_80A6862C != 0) {
        Math_ApproachZeroF(&this->actor.speedXZ, 0.3f, 1.0f);
        return;
    }
    temp_v0 = func_8013D648(globalCtx, this->paramsCopy2, 0x1F);
    this->unk210 = temp_v0;
    if (temp_v0 != 0) {
        //sp30.y = (f32) func_8013D83C(temp_v0, this->unk214, &this->actor.world, &sp30);
        sp34 = (f32) func_8013D83C(temp_v0, this->unk214, &this->actor.world, sp30);
    }
    if (sp30 < 10.0f) {
        temp_v0_2 = this->unk210;
        if (temp_v0_2 != 0) {
            this->unk214 = (s16) (this->unk214 + 1);
            if ((s32) this->unk214 >= (s32) (u8) *temp_v0_2) {
                this->unk214 = (u16)0;
            }
            if (Rand_ZeroOne() < 0.6f) {
                func_80A67C48(this);
                return;
            }
        }
    }
    Math_SmoothStepToS(&this->actor.shape.rot.y, (s16) (s32) sp34, 1, 0x1388, 0);
    this->actor.world.rot.y = this->actor.shape.rot.y;
}
//#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Look_Nuts_0x80A678B0/func_80A67AA8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Look_Nuts_0x80A678B0/func_80A67C48.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Look_Nuts_0x80A678B0/func_80A67D0C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Look_Nuts_0x80A678B0/func_80A67F30.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Look_Nuts_0x80A678B0/func_80A67FC4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Look_Nuts_0x80A678B0/func_80A68080.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Look_Nuts_0x80A678B0/func_80A680FC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Look_Nuts_0x80A678B0/EnLookNuts_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Look_Nuts_0x80A678B0/EnLookNuts_Draw.asm")
