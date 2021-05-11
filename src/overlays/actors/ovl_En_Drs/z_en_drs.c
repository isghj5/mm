#include "z_en_drs.h"

#define FLAGS 0x00000000

#define THIS ((EnDrs*)thisx)

void EnDrs_Init(Actor* thisx, GlobalContext* globalCtx);
//void EnDrs_Init(Actor* thisx);
void EnDrs_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnDrs_Update(Actor* thisx, GlobalContext* globalCtx);
//void EnDrs_Update(EnDrs* this, GlobalContext* globalCtx);


void func_80C1E2D4(EnDrs* this, GlobalContext* globalCtx);
void func_80C1E290(EnDrs* this, GlobalContext* globalCtx);

/*
const ActorInit En_Drs_InitVars = {
    ACTOR_EN_DRS,
    ACTORCAT_PROP,
    FLAGS,
    OBJECT_DRS,
    sizeof(EnDrs),
    (ActorFunc)EnDrs_Init,
    (ActorFunc)EnDrs_Destroy,
    (ActorFunc)EnDrs_Update,
    (ActorFunc)NULL
};
*/

// update extension
void func_80C1E290(EnDrs* this, GlobalContext *globalCtx);

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Drs_0x80C1E290/func_80C1E290.asm")

extern UNK_TYPE D_80C1E618;

//action func
/*
void func_80C1E2D4(EnDrs *this, GlobalContext *globalCtx) {
    //SkelAnime *sp30;
    //SkelAnime *temp_a1;
    s8 temp_a2;

    //temp_a2 = this->unk208;
    //if (((s32) temp_a2 >= 0) && (func_8013D8DC(temp_a2, globalCtx, temp_a2) != 0)) {
    temp_a2 = this->unk208;
    if ((this->unk208 >= 0) && (func_8013D8DC(this->unk208, globalCtx, this->unk208) != 0)) {
        ActorShape_Init(&this->actor.shape, 0.0f, NULL, 0.0f);
        //temp_a1 = &this->skelAnime;
        //sp30 = temp_a1;
        SkelAnime_InitSV(globalCtx, &this->skelAnime, 0x6005A78, NULL, this->limbDrawTable, this->transitionDrawTable, 4);
        func_8013BC6C(sp30, &D_80C1E618, 0); // animation function?
        Collider_InitAndSetCylinder(globalCtx, &this->collider, &this->actor, &D_80C1E5E0);
        CollisionCheck_SetInfo2(&this->actor.colChkInfo, DamageTable_Get(0x16), &D_80C1E60C);
        Actor_SetScale(&this->actor, 0.01f);
        this->actor.draw = func_80C1E568;
        this->actionFunc = func_80C1E3DC;
    }
} // */
#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Drs_0x80C1E290/func_80C1E2D4.asm")

void func_80C1E3DC(EnDrs* this, GlobalContext *globalCtx) { }

void EnDrs_Init(Actor *thisx, GlobalContext *globalCtx) {
    EnDrs* this = THIS;
    this->unk208 = func_8013D924(0x16, globalCtx);
    this->actionFunc = func_80C1E2D4;

}

void EnDrs_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    EnDrs* this = THIS;
    Collider_DestroyCylinder(globalCtx, &this->collider);
}

void EnDrs_Update(Actor* thisx, GlobalContext* globalCtx) {
    EnDrs* this = THIS;
    this->actionFunc(this, globalCtx);
    if (this->actor.draw) {
        SkelAnime_FrameUpdateMatrix(&this->skelAnime);
        func_80C1E290(this, globalCtx);
    }
}

// override limb draw
void func_80C1E4B0(GlobalContext* globalCtx, Skeleton* skeleton, Vec3s* limbDrawTable, s32 dListCount, OverrideLimbDraw2 overrideLimbDraw, PostLimbDraw2 postLimbDraw, Actor* actor, Gfx* gfx);
#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Drs_0x80C1E290/func_80C1E4B0.asm")

// this is a draw function, gets assigned late
void func_80C1E568(EnDrs* this, GlobalContext* globalCtx);
#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Drs_0x80C1E290/func_80C1E568.asm")
