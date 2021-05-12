#include "z_en_drs.h"

#define FLAGS 0x00000000

#define THIS ((EnDrs*)thisx)

void EnDrs_Init(Actor* thisx, GlobalContext* globalCtx);
void EnDrs_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnDrs_Update(Actor* thisx, GlobalContext* globalCtx);

void func_80C1E568(Actor* thisx, GlobalContext* globalCtx);
void func_80C1E3DC(EnDrs* this, GlobalContext *globalCtx);

void func_80C1E2D4(EnDrs* this, GlobalContext* globalCtx);
void func_80C1E290(EnDrs* this, GlobalContext* globalCtx);

const ActorInit En_Drs_InitVars = {
    ACTOR_EN_DRS,
    ACTORCAT_PROP,
    FLAGS,
    OBJECT_DRS,
    sizeof(EnDrs),
    (ActorFunc) EnDrs_Init,
    (ActorFunc) EnDrs_Destroy,
    (ActorFunc) EnDrs_Update,
    (ActorFunc) NULL
};

static ColliderCylinderInit D_80C1E5E0 = {
//static ColliderCylinderInit sCylinderInit = {
    { COLTYPE_HIT1, AT_NONE, AC_NONE, OC1_ON | OC1_TYPE_ALL, OC2_TYPE_1, COLSHAPE_CYLINDER, },
    { ELEMTYPE_UNK1, { 0x00000000, 0x00, 0x00 }, { 0x00000000, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_NONE, OCELEM_ON, },
    { 16, 62, 0, { 0, 0, 0 } },
};

UNK_TYPE D_80C1E60C[] = {
    0x00000000,
    0x00000000,
    0xFF000000,
};

// start frame: 0x0000FFFF = 9.18340948595e-41f? OK
ActorAnimationEntry D_80C1E618[] = {
    {D_0600001C, 1.0f, 9.18340948595e-41f, 0.0f, 0x0, 0x0,},
};

// update extension: update collider
void func_80C1E290(EnDrs *this, GlobalContext *globalCtx) {
    Collider_UpdateCylinder(&this->actor, &this->collider);
    CollisionCheck_SetOC(globalCtx, &globalCtx->colCheckCtx, &this->collider);
}

// actionfunc
void func_80C1E2D4(EnDrs *this, GlobalContext *globalCtx) {
    s32 pad;
    SkelAnime* tempAnime = &this->skelAnime;

    if ((this->unk208 >= 0) && (func_8013D8DC(this->unk208, globalCtx) != 0)) {
        ActorShape_Init(&this->actor.shape, 0.0f, NULL, 0.0f);
        SkelAnime_InitSV(globalCtx, tempAnime, D_06005A78, NULL, this->limbDrawTable, this->transitionDrawTable, 4);
        func_8013BC6C(tempAnime, D_80C1E618, 0); // animation set?
        Collider_InitAndSetCylinder(globalCtx, &this->collider, &this->actor, &D_80C1E5E0);
        CollisionCheck_SetInfo2(&this->actor.colChkInfo, DamageTable_Get(0x16), &D_80C1E60C);
        Actor_SetScale(&this->actor, 0.01f);
        this->actor.draw = func_80C1E568;
        this->actionFunc = func_80C1E3DC;
    }
}

//action func do nothing
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

// post limb draw
void func_80C1E4B0(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3s* rot, Actor* actor) {
    EnDrs* this = (EnDrs*) actor;

    s8 temp208 = this->unk208;
    s8 tempObjBankIndex = actor->objBankIndex;

    // fake match? this temp is required but never used
    GraphicsContext* fakeGfxCtx = globalCtx->state.gfxCtx;

    // assumption: the sunmask is a limb, this is checking if the player reunited kafei+anju
    if (((gSaveContext.perm.weekEventReg[0x57] & 2) == 0) && (limbIndex == 2)) {
        OPEN_DISPS(globalCtx->state.gfxCtx);
        gSPSegment(POLY_OPA_DISP++, 0x06, globalCtx->objectCtx.status[temp208].segment);
        gSPDisplayList(POLY_OPA_DISP++, D_06000E70);
        gSPSegment(POLY_OPA_DISP++, 0x06, globalCtx->objectCtx.status[tempObjBankIndex].segment);
        CLOSE_DISPS(globalCtx->state.gfxCtx);
    }
}

// this is a draw function, gets assigned late
void func_80C1E568(Actor* thisx, GlobalContext *globalCtx) {
    EnDrs* this = THIS;
    func_8012C5B0(globalCtx->state.gfxCtx);
    SkelAnime_DrawSV(globalCtx, this->skelAnime.skeleton, this->skelAnime.limbDrawTbl, this->skelAnime.dListCount, 
      NULL, func_80C1E4B0, &this->actor);
}
