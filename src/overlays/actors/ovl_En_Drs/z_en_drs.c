#include "z_en_drs.h"

#define FLAGS 0x00000000

#define THIS ((EnDrs*)thisx)

void EnDrs_Init(Actor* thisx, GlobalContext* globalCtx);
void EnDrs_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnDrs_Update(Actor* thisx, GlobalContext* globalCtx);
void EnDrs_Draw(Actor* thisx, GlobalContext* globalCtx);
void EnDrs_DoNothing(EnDrs* this, GlobalContext *globalCtx);
void EnDrs_CheckMoonMask(EnDrs* this, GlobalContext* globalCtx);
void EnDrs_UpdateCollider(EnDrs* this, GlobalContext* globalCtx);

const ActorInit En_Drs_InitVars = {
    ACTOR_EN_DRS,
    ACTORCAT_PROP,
    FLAGS,
    OBJECT_DRS,
    sizeof(EnDrs),
    (ActorFunc) EnDrs_Init,
    (ActorFunc) EnDrs_Destroy,
    (ActorFunc) EnDrs_Update,
    (ActorFunc) NULL,
};

//static ColliderCylinderInit D_80C1E5E0 = {
static ColliderCylinderInit sCylinderInit = {
    { COLTYPE_HIT1, AT_NONE, AC_NONE, OC1_ON | OC1_TYPE_ALL, OC2_TYPE_1, COLSHAPE_CYLINDER, },
    { ELEMTYPE_UNK1, { 0x00000000, 0x00, 0x00 }, { 0x00000000, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_NONE, OCELEM_ON, },
    { 16, 62, 0, { 0, 0, 0 } },
};

CollisionCheckInfoInit2 sCylinderCheckInfoInit = {
    0x00, 0x0000, 0x0000, 0x0000, 0xFF,
};

// start frame: 0x0000FFFF = 9.18340948595e-41f? OK
ActorAnimationEntry drsAnimations[] = {
    {object_drs_posing_anim, 1.0f, 9.18340948595e-41f, 0.0f, 0x0, 0x0,},
};

void EnDrs_UpdateCollider(EnDrs *this, GlobalContext *globalCtx) {
    Collider_UpdateCylinder(&this->actor, &this->collider);
    CollisionCheck_SetOC(globalCtx, &globalCtx->colCheckCtx, &this->collider);
}

void EnDrs_CheckMoonMask(EnDrs *this, GlobalContext *globalCtx) {
    s32 pad;
    SkelAnime* tempAnime = &this->skelAnime;

    // func_8013D8DC: wrapper for Object_IsLoaded
    if ((this->moonMaskObjId >= 0) && (func_8013D8DC(this->moonMaskObjId, globalCtx))) {
        ActorShape_Init(&this->actor.shape, 0.0f, NULL, 0.0f);
        SkelAnime_InitSV(globalCtx, tempAnime, object_drs_skeleton, NULL, this->limbDrawTable, this->transitionDrawTable, 4);
        func_8013BC6C(tempAnime, drsAnimations, 0); // animation set?
        Collider_InitAndSetCylinder(globalCtx, &this->collider, &this->actor, &sCylinderInit);
        CollisionCheck_SetInfo2(&this->actor.colChkInfo, DamageTable_Get(0x16), &sCylinderCheckInfoInit);
        Actor_SetScale(&this->actor, 0.01f);
        this->actor.draw = EnDrs_Draw;
        this->actionFunc = EnDrs_DoNothing;
    }
}

void EnDrs_DoNothing(EnDrs* this, GlobalContext *globalCtx) { }

void EnDrs_Init(Actor *thisx, GlobalContext *globalCtx) {
    EnDrs* this = THIS;
    // func_8013D924: wrapper for Scene_FindSceneObjectIndex
    this->moonMaskObjId = func_8013D924(OBJECT_MSMO, globalCtx); // moon mask
    this->actionFunc = EnDrs_CheckMoonMask;
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
        EnDrs_UpdateCollider(this, globalCtx);
    }
}

void EnDrs_PostLimbDraw(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3s* rot, Actor* actor) {
    EnDrs* this = (EnDrs*) actor;

    s8 maskObjId = this->moonMaskObjId;
    s8 tempObjBankIndex = actor->objBankIndex;

    // fake match? this temp is required but never used
    GraphicsContext* fakeGfxCtx = globalCtx->state.gfxCtx;

    // assumption: the moonmask is a limb, this is checking if the player reunited kafei+anju
    if (((gSaveContext.perm.weekEventReg[0x57] & 2) == 0) && (limbIndex == 2)) {
        OPEN_DISPS(globalCtx->state.gfxCtx);
        gSPSegment(POLY_OPA_DISP++, 0x06, globalCtx->objectCtx.status[maskObjId].segment);
        gSPDisplayList(POLY_OPA_DISP++, object_drs_dlist);
        gSPSegment(POLY_OPA_DISP++, 0x06, globalCtx->objectCtx.status[tempObjBankIndex].segment);
        CLOSE_DISPS(globalCtx->state.gfxCtx);
    }
}

void EnDrs_Draw(Actor* thisx, GlobalContext *globalCtx) {
    EnDrs* this = THIS;
    func_8012C5B0(globalCtx->state.gfxCtx);
    SkelAnime_DrawSV(globalCtx, this->skelAnime.skeleton, this->skelAnime.limbDrawTbl, this->skelAnime.dListCount, 
      NULL, EnDrs_PostLimbDraw, &this->actor);
}
