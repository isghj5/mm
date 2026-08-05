/*
 * File: z_en_cne_01.c
 * Overlay: ovl_En_Cne_01
 * Description: Unused Market NPC (modded for placable use)
 */

#include "z_en_cne_01.h"
#include "assets/objects/object_cne/object_cne.h"

#define FLAGS (ACTOR_FLAG_ATTENTION_ENABLED | ACTOR_FLAG_FRIENDLY | ACTOR_FLAG_UPDATE_CULLING_DISABLED)

#define CNE_GET_TYPE(thisx) ((thisx)->params & 0xF)

void EnCne01_Init(Actor* thisx, PlayState* play);
void EnCne01_Destroy(Actor* thisx, PlayState* play);
void EnCne01_Update(Actor* thisx, PlayState* play);
void EnCne01_Draw(Actor* thisx, PlayState* play);

void EnCne01_Walk(EnCne01* this, PlayState* play);
void EnCne01_FaceForward(EnCne01* this, PlayState* play);
void EnCne01_Talk(EnCne01* this, PlayState* play);
s32 EnCne01_TestIsTalking(EnCne01* this, PlayState* play);

ActorProfile En_Cne_01_Profile = {
    /**/ ACTOR_EN_CNE_01,
    /**/ ACTORCAT_NPC,
    /**/ FLAGS,
    /**/ OBJECT_CNE,
    /**/ sizeof(EnCne01),
    /**/ EnCne01_Init,
    /**/ EnCne01_Destroy,
    /**/ EnCne01_Update,
    /**/ EnCne01_Draw,
};

static ColliderCylinderInit sCylinderInit = {
    {
        COL_MATERIAL_NONE,
        AT_NONE,
        AC_ON | AC_TYPE_PLAYER,
        OC1_ON | OC1_TYPE_ALL,
        OC2_TYPE_1,
        COLSHAPE_CYLINDER,
    },
    {
        ELEM_MATERIAL_UNK1,
        { 0x00000000, 0x00, 0x00 },
        { 0xF7CFFFFF, 0x00, 0x00 },
        ATELEM_NONE | ATELEM_SFX_NORMAL,
        ACELEM_ON,
        OCELEM_ON,
    },
    { 18, 64, 0, { 0, 0, 0 } },
};

static CollisionCheckInfoInit2 sColChkInfoInit = { 0, 0, 0, 0, MASS_IMMOVABLE };

static DamageTable sDamageTable = {
    /* Deku Nut       */ DMG_ENTRY(0, 0),
    /* Deku Stick     */ DMG_ENTRY(0, 0),
    /* Horse trample  */ DMG_ENTRY(0, 0),
    /* Explosives     */ DMG_ENTRY(0, 0),
    /* Zora boomerang */ DMG_ENTRY(0, 0),
    /* Normal arrow   */ DMG_ENTRY(0, 0),
    /* UNK_DMG_0x06   */ DMG_ENTRY(0, 0),
    /* Hookshot       */ DMG_ENTRY(0, 0),
    /* Goron punch    */ DMG_ENTRY(0, 0),
    /* Sword          */ DMG_ENTRY(0, 0),
    /* Goron pound    */ DMG_ENTRY(0, 0),
    /* Fire arrow     */ DMG_ENTRY(0, 0),
    /* Ice arrow      */ DMG_ENTRY(0, 0),
    /* Light arrow    */ DMG_ENTRY(0, 0),
    /* Goron spikes   */ DMG_ENTRY(0, 0),
    /* Deku spin      */ DMG_ENTRY(0, 0),
    /* Deku bubble    */ DMG_ENTRY(0, 0),
    /* Deku launch    */ DMG_ENTRY(0, 0),
    /* UNK_DMG_0x12   */ DMG_ENTRY(0, 0),
    /* Zora barrier   */ DMG_ENTRY(0, 0),
    /* Normal shield  */ DMG_ENTRY(0, 0),
    /* Light ray      */ DMG_ENTRY(0, 0),
    /* Thrown object  */ DMG_ENTRY(0, 0),
    /* Zora punch     */ DMG_ENTRY(0, 0),
    /* Spin attack    */ DMG_ENTRY(0, 0),
    /* Sword beam     */ DMG_ENTRY(0, 0),
    /* Normal Roll    */ DMG_ENTRY(0, 0),
    /* UNK_DMG_0x1B   */ DMG_ENTRY(0, 0),
    /* UNK_DMG_0x1C   */ DMG_ENTRY(0, 0),
    /* Unblockable    */ DMG_ENTRY(0, 0),
    /* UNK_DMG_0x1E   */ DMG_ENTRY(0, 0),
    /* Powder Keg     */ DMG_ENTRY(0, 0),
};

static TrackOptionsSet sTrackOptions = {
    { 0xFA0, 4, 1, 3 },
    { 0x1770, 4, 1, 6 },
    { 0xFA0, 4, 1, 3 },
    { 0x1770, 4, 1, 6 },
};

#include "new_animations.c"

s32 EnCne01_AttemptItemRecieve(EnCne01* this, PlayState* play) {
    s16 x;
    s16 y;

    Actor_GetScreenPos(play, &this->actor, &x, &y);
    if (((x >= 0) && (x < SCREEN_WIDTH)) && ((y >= 0) && (y < SCREEN_HEIGHT))) {
        Actor_OfferTalkExchangeEquiCylinder(&this->actor, play, 30.0f, PLAYER_IA_MOONS_TEAR);
    }
    return true;
}

void EnCne02_TestGiftItem(EnCne01* this, PlayState* play){
    Player* player = GET_PLAYER(play);
    s16 playerType = CNE_GET_TYPE(&this->actor);
    PlayerItemAction itemAction = func_80123810(play);

    if (itemAction > PLAYER_IA_NONE && playerType == CNE_TYPE_VENESA) {
        if (itemAction == PLAYER_IA_PICTOGRAPH_BOX) {
            player->exchangeItemAction = itemAction;
            this->textId = 0x221B;
        }
        else{
            this->textId = 0x2220;
        }
    } else  if (itemAction > PLAYER_IA_NONE && playerType == CNE_TYPE_ORANGE) {
        if (itemAction == PLAYER_IA_PICTOGRAPH_BOX) {
            player->exchangeItemAction = itemAction;
            this->textId = 0x221B;
        }
        else{
            this->textId = 0x2220;
        }
    }
    Message_StartTextbox(play, this->textId, NULL);
}

void EnCne02_SetAnimation(EnCne01* this, AnimationHeader* anim){
    this->curAnim = anim;
    Animation_Change(&this->skelAnime, anim, 1.0f, 0.0f, 0.0f, ANIMMODE_LOOP, 1.0f);
}

void EnCne01_UpdateModel(EnCne01* this, PlayState* play) {
    Vec3f point;
    int talkingDist = (CNE_GET_TYPE(&this->actor) == CNE_TYPE_VENESA) ? 90: 200;

    SkelAnime_Update(&this->skelAnime);

    this->stateFlags &= ~2;

    if (this->actor.xzDistToPlayer < talkingDist &&
      SubS_AngleDiffLessEqual(this->actor.shape.rot.y, 0x36B0, this->actor.yawTowardsPlayer)) {
        Player* player = GET_PLAYER(play);
        point.x = player->actor.world.pos.x;
        point.y = player->bodyPartsPos[PLAYER_BODYPART_HEAD].y + 3.0f;
        point.z = player->actor.world.pos.z;
        SubS_TrackPoint(&point, &this->actor.focus.pos, &this->actor.shape.rot, &this->trackTarget,
                        &this->headRot, &this->torsoRot, &sTrackOptions);

        if (CNE_GET_TYPE(&this->actor) == CNE_TYPE_VENESA
            && player->heldActor != NULL && player->heldActor->id == ACTOR_EN_NIW){
          this->stateFlags |= 2;
        }

    } else if (this->moonPtr != NULL) {
        point.x = this->moonPtr->world.pos.x;
        point.y = this->moonPtr->world.pos.y;
        point.z = this->moonPtr->world.pos.z;
        SubS_TrackPoint(&point, &this->actor.focus.pos, &this->actor.shape.rot, &this->trackTarget,
                        &this->headRot, &this->torsoRot, &sTrackOptions);
    } else {
        Math_SmoothStepToS(&this->trackTarget.x, 0, 4, 0x3E8, 1);
        Math_SmoothStepToS(&this->trackTarget.y, 0, 4, 0x3E8, 1);
        Math_SmoothStepToS(&this->headRot.x, 0, 4, 0x3E8, 1);
        Math_SmoothStepToS(&this->headRot.y, 0, 4, 0x3E8, 1);
        Math_SmoothStepToS(&this->torsoRot.x, 0, 4, 0x3E8, 1);
        Math_SmoothStepToS(&this->torsoRot.y, 0, 4, 0x3E8, 1);
    }

    if ((this->stateFlags & 2) && this->curAnim != &gCneAnjuMyChickenHaveEscapedAnim){
        EnCne02_SetAnimation(this,  &gCneAnjuMyChickenHaveEscapedAnim);
    } else if (!(this->stateFlags & 2) && this->curAnim == &gCneAnjuMyChickenHaveEscapedAnim){
        EnCne02_SetAnimation(this,  this->defaultAnim);
    }

    SubS_UpdateFidgetTables(play, this->limbRotTableY, this->limbRotTableZ, ARRAY_COUNT(this->limbRotTableY));

    this->collider.dim.pos.x = this->actor.world.pos.x;
    this->collider.dim.pos.y = this->actor.world.pos.y;
    this->collider.dim.pos.z = this->actor.world.pos.z;

    CollisionCheck_SetAC(play, &play->colChkCtx, &this->collider.base);
    CollisionCheck_SetOC(play, &play->colChkCtx, &this->collider.base);
}

void EnCne01_Walk(EnCne01* this, PlayState* play) {
}

void EnCne02_SetupFaceForward(EnCne01* this){
    if (this->moonPtr != NULL && (this->stateFlags & 0x1) && CNE_GET_TYPE(&this->actor) == CNE_TYPE_VENESA){
      this->stateFlags &= ~1;
    }
    this->actionFunc = EnCne01_FaceForward;
}

void EnCne01_FaceForward(EnCne01* this, PlayState* play) {
    EnCne01_TestIsTalking(this, play);
    this->actor.shape.rot = this->actor.world.rot;
}

void EnCne01_Talk(EnCne01* this, PlayState* play) {
    u8 talkState;

    Math_SmoothStepToS(&this->actor.shape.rot.y, this->actor.yawTowardsPlayer, 4, 0xFA0, 1);

    if (++this->dialogueTimer >= (20 * 45)){
      Message_CloseTextbox(play);
      EnCne02_SetupFaceForward(this);
    }

    talkState = Message_GetState(&play->msgCtx);
    this->inMsgState3 = (talkState == TEXT_STATE_FADING);

    switch (talkState) {
        case TEXT_STATE_EVENT:
            if (!Message_ShouldAdvance(play)) return;

            Message_CloseTextbox(play);
            EnCne02_SetupFaceForward(this);

            break;

        case TEXT_STATE_CLOSING:
            if (this->textId == 0x33D3){
              this->textId = 0;
              EnCne02_SetupFaceForward(this);
            }
            break;

        case TEXT_STATE_DONE:
            if (!Message_ShouldAdvance(play)) return;

            this->actor.textId = 0;

            EnCne02_SetupFaceForward(this);
            Message_CloseTextbox(play);
            break;
        default:
            break;
    }
}

s32 EnCne01_TestIsTalking(EnCne01* this, PlayState* play) {
    s32 isTalking = false;
    const u16 talkingAngle = 0x100;
    s16 yaw = ABS_ALT(this->actor.shape.rot.y - this->actor.yawTowardsPlayer);

    if (yaw < talkingAngle && Actor_TalkOfferAccepted(&this->actor, &play->state)) {
        isTalking = true;
        if (CNE_GET_TYPE(&this->actor) == CNE_TYPE_VENESA){
            if (SubS_GetObjectSlot(GAMEPLAY_DANGEON_KEEP, play) != OBJECT_SLOT_NONE){
               this->textId = 0x221B;

            }else if (this->moonPtr != NULL){
                if (this->stateFlags & 0x1){
                  this->textId = 0x05DE;

                } else {
                  this->stateFlags |= 0x1;
                  this->textId = 0x05DD;
                }
            } else {
                this->textId = 0x14B4;
            }
        } else {
            this->textId = 0x33D3;
        }

        Message_StartTextbox(play, this->textId, &this->actor);
        this->prevActionFunc = this->actionFunc;
        this->dialogueTimer = 0;
        this->actionFunc = EnCne01_Talk;

    } else if (yaw < talkingAngle) {
        Actor_OfferTalk(&this->actor, play, 90.0f);
    }

    return isTalking;
}

void EnCne01_Init(Actor* thisx, PlayState* play) {
    EnCne01* this = (EnCne01*)thisx;

    this->moonPtr = SubS_FindActor(play, 0, ACTORCAT_ITEMACTION, ACTOR_EN_FALL);

    if (this->moonPtr != NULL){
        this->actor.world.rot.y = Math_Vec3f_Yaw(&this->actor.world.pos, &this->moonPtr->world.pos);
        this->actor.shape.rot.y = this->actor.world.rot.y;
    }

    switch (CNE_GET_TYPE(thisx)){
        default:
        case CNE_TYPE_VENESA:
            if (this->moonPtr != NULL){
              this->curAnim = &gCneAnjuHandsTogetherAnim;
            } else {
              this->curAnim = &gCnePatientHandsTogetherAnim;
            }

            break;

        case CNE_TYPE_ORANGE:
            if (this->moonPtr != NULL){
              this->curAnim = &gCneArmsCrossedAnim;
            } else {
              this->curAnim = &gCnePatientHandsTogetherAnim;
            }
            break;
    }
    this->defaultAnim = this->curAnim;

    SkelAnime_InitFlex(play, &this->skelAnime,
        &gHylianYoungWomanSkel, this->curAnim,
        this->jointTable, this->morphTable, HYLIAN_YOUNG_WOMAN_LIMB_MAX);

    Collider_InitCylinder(play, &this->collider);
    Collider_SetCylinder(play, &this->collider, &this->actor, &sCylinderInit);
    CollisionCheck_SetInfo2(&this->actor.colChkInfo, &sDamageTable, &sColChkInfoInit);
    this->path = SubS_GetPathByIndex(play, ENCNE01_GET_PATH_INDEX(&this->actor), ENCNE01_PATH_INDEX_NONE);
    Actor_SetScale(&this->actor, 0.01f);

    this->actor.attentionRangeType = ATTENTION_RANGE_6;

    if (ENCNE01_GET_PATH_INDEX(&this->actor) == ENCNE01_PATH_INDEX_NONE) {
        this->actionFunc = EnCne01_FaceForward;
    } else {
        this->actionFunc = EnCne01_FaceForward;
    }
}

void EnCne01_Destroy(Actor* thisx, PlayState* play) {
    EnCne01* this = (EnCne01*)thisx;

    Collider_DestroyCylinder(play, &this->collider);
}

void EnCne01_Update(Actor* thisx, PlayState* play) {
    EnCne01* this = (EnCne01*)thisx;

    this->actionFunc(this, play);
    Actor_UpdateBgCheckInfo(play, &this->actor, 0.0f, 0.0f, 0.0f, UPDBGCHECKINFO_FLAG_4);
    EnCne01_UpdateModel(this, play);
}

s32 EnCne01_OverrideLimbDraw(PlayState* play, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, Actor* thisx) {
    EnCne01* this = (EnCne01*)thisx;
    s8 bodyPart;
    Vec3f zeroVec = { 0.0f, 0.0f, 0.0f };

    bodyPart = gEnHyLimbToBodyParts[limbIndex];
    if (bodyPart >= 0) {
        Matrix_MultVec3f(&zeroVec, &this->bodyPartsPos[bodyPart]);
    }

    if (limbIndex == HYLIAN_YOUNG_WOMAN_LIMB_HEAD && CNE_GET_TYPE(&this->actor) == CNE_TYPE_ORANGE) {
        OPEN_DISPS(play->state.gfxCtx);
        *dList = gHylianYoungWomanHeadOrangeHairDL;
        CLOSE_DISPS(play->state.gfxCtx);
    }
    if (limbIndex == HYLIAN_YOUNG_WOMAN_LIMB_HEAD) {
        Matrix_Translate(1500.0f, 0.0f, 0.0f, MTXMODE_APPLY);
        Matrix_RotateXS(this->headRot.y, MTXMODE_APPLY);
        Matrix_RotateZS(-this->headRot.x, MTXMODE_APPLY);
        Matrix_Translate(-1500.0f, 0.0f, 0.0f, MTXMODE_APPLY);
    }

    if (limbIndex == HYLIAN_YOUNG_WOMAN_LIMB_TORSO) {
        Matrix_RotateXS(-this->torsoRot.y, MTXMODE_APPLY);
        Matrix_RotateZS(-this->torsoRot.x, MTXMODE_APPLY);
    }

    if ((limbIndex == HYLIAN_YOUNG_WOMAN_LIMB_HEAD) && this->inMsgState3 && ((play->state.frames % 2) == 0)) {
        Matrix_Translate(20.0f, 0.0f, 0.0f, MTXMODE_APPLY);
    }

    if ((limbIndex == HYLIAN_YOUNG_WOMAN_LIMB_TORSO) || (limbIndex == HYLIAN_YOUNG_WOMAN_LIMB_LEFT_UPPER_ARM) ||
        (limbIndex == HYLIAN_YOUNG_WOMAN_LIMB_RIGHT_UPPER_ARM)) {
        rot->y += TRUNCF_BINANG(Math_SinS(this->limbRotTableY[limbIndex]) * 200.0f);
        rot->z += TRUNCF_BINANG(Math_CosS(this->limbRotTableZ[limbIndex]) * 200.0f);
    }

    return false;
}

void EnCne01_PostLimbDraw(PlayState* play, s32 limbIndex, Gfx** dList, Vec3s* rot, Actor* thisx) {
    EnCne01* this = (EnCne01*)thisx;
    Vec3f zeroVec = { 0.0f, 0.0f, 0.0f };

    if (limbIndex == HYLIAN_YOUNG_WOMAN_LIMB_HEAD) {
        Matrix_MultVec3f(&zeroVec, &this->actor.focus.pos);
    }
}

void EnCne01_TransformLimbDraw(PlayState* play, s32 limbIndex, Actor* thisx) {
}

void EnCne01_Draw(Actor* thisx, PlayState* play) {
    EnCne01* this = (EnCne01*)thisx;
    Color_RGBA8 originalBlueColor = { 160, 180, 255, 0 };

    OPEN_DISPS(play->state.gfxCtx);

    Gfx_SetupDL25_Opa(play->state.gfxCtx);
    if (CNE_GET_TYPE(&this->actor) == CNE_TYPE_ORANGE) {
        gSPSegment(POLY_OPA_DISP++, 0x08, Gfx_EnvColor(play->state.gfxCtx,
          70, 160, 230, 0));
        gSPSegment(POLY_OPA_DISP++, 0x09, Gfx_EnvColor(play->state.gfxCtx,
          255, 255, 100, 0));
        gSPSegment(POLY_OPA_DISP++, 0x0A, Gfx_EnvColor(play->state.gfxCtx,
          255, 255, 255, 255));
    } else {
        gSPSegment(POLY_OPA_DISP++, 0x08, Gfx_EnvColor(play->state.gfxCtx,
          originalBlueColor.r, originalBlueColor.g,
          originalBlueColor.b, originalBlueColor.a));
        gSPSegment(POLY_OPA_DISP++, 0x09, Gfx_EnvColor(play->state.gfxCtx,
          originalBlueColor.r, originalBlueColor.g,
          originalBlueColor.b, originalBlueColor.a));
        gSPSegment(POLY_OPA_DISP++, 0x0A, Gfx_EnvColor(play->state.gfxCtx,
          originalBlueColor.r, originalBlueColor.g,
          originalBlueColor.b, originalBlueColor.a));
    }
    gDPPipeSync(POLY_OPA_DISP++);
    SkelAnime_DrawTransformFlexOpa(play, this->skelAnime.skeleton, this->skelAnime.jointTable,
                                   this->skelAnime.dListCount, EnCne01_OverrideLimbDraw, EnCne01_PostLimbDraw,
                                   EnCne01_TransformLimbDraw, &this->actor);
    Matrix_RotateXS(0, MTXMODE_NEW);

    CLOSE_DISPS(play->state.gfxCtx);
}
