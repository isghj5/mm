/*
 * File: z_dm_zl.c
 * Overlay: ovl_Dm_Zl
 * Description: Child Zelda (Re-learning Song of Time cutscene)
 */

#include "z_dm_zl.h"
#include "objects/object_zl4/object_zl4.h"

#define FLAGS (ACTOR_FLAG_10)

#define THIS ((DmZl*)thisx)

void DmZl_SetupRaiseFlute(DmZl* this, GlobalContext* globalCtx);
void DmZl_UpdateCutscene(DmZl* this, GlobalContext* globalCtx); 

void DmZl_Init(Actor* thisx, GlobalContext* globalCtx);
void DmZl_Destroy(Actor* thisx, GlobalContext* globalCtx);
void DmZl_Update(Actor* thisx, GlobalContext* globalCtx);
void DmZl_Draw(Actor* thisx, GlobalContext* globalCtx);


const ActorInit Dm_Zl_InitVars = {
    ACTOR_DM_ZL,
    ACTORCAT_NPC, // changed because shes real now
    FLAGS,
    OBJECT_ZL4,
    sizeof(DmZl),
    (ActorFunc)DmZl_Init,
    (ActorFunc)DmZl_Destroy,
    (ActorFunc)DmZl_Update,
    (ActorFunc)DmZl_Draw,
};

// ripped from Ani, which I know has a basic repel collider with avg size
static ColliderCylinderInit sCylinderInit = {
    {
        COLTYPE_NONE,
        AT_NONE,
        AC_ON | AC_TYPE_ENEMY,
        OC1_ON | OC1_TYPE_ALL,
        OC2_TYPE_1,
        COLSHAPE_CYLINDER,
    },
    {
        ELEMTYPE_UNK0,
        { 0x00000000, 0x00, 0x00 },
        { 0xF7CFFFFF, 0x00, 0x00 },
        TOUCH_NONE | TOUCH_SFX_NORMAL,
        BUMP_ON,
        OCELEM_ON,
    },
    { 30, 40, 0, { 0, 0, 0 } },
};

static AnimationInfo sAnimations[7] = {
    { &gDmZl4FacingAwayHandsOverEmblemLoop, 1.0f, 0.0f, -1.0f, ANIMMODE_LOOP, -10.0f },
    { &gDmZl4TurningAround2Anim, 1.0f, 0.0f, -1.0f, ANIMMODE_ONCE, -10.0f },
    { &gDmZl4HandsOverEmblemLoopAnim, 1.0f, 0.0f, -1.0f, ANIMMODE_LOOP, -10.0f },
    { &gDmZl4GivingItemStartAnim, 1.0f, 0.0f, -1.0f, ANIMMODE_ONCE, -10.0f },
    { &gDmZl4GivingItemLoopAnim, 1.0f, 0.0f, -1.0f, ANIMMODE_LOOP, -10.0f },
    { &gDmZl4RaisingOcarinaToPlayAnim, 1.0f, 0.0f, -1.0f, ANIMMODE_ONCE, -10.0f },
    { &gDmZl4PlayingOcarinaAnim, 1.0f, 0.0f, -1.0f, ANIMMODE_LOOP, -10.0f },
};

typedef enum {
    ZELDA_ANIM_FACING_AWAY,
    ZELDA_ANIM_TURNING_TOWARD_PLAYER,
    ZELDA_ANIM_FACING_PLAYER,
    ZELDA_ANIM_GIVING_OCARINA_START,
    ZELDA_ANIM_GIVING_OCARINA,
    ZELDA_ANIM_PLAYING_OCARINA_START,
    ZELDA_ANIM_PLAYING_OCARINA,
    ZELDA_ANIM_MAX,
} DmZlAnimations;

static TexturePtr sMouthTextures[4] = {
    gZl4MouthNeutralTex,
    gZl4MouthOpenSmilingTex,
    gZl4MouthFrowningTex,
    gZl4MouthOpenTex,
};

typedef enum {
    /* 0 */ ZELDA_MOUTH_NEUTRAL,
    /* 1 */ ZELDA_MOUTH_SMILING,
    /* 2 */ ZELDA_MOUTH_FROWNING,
    /* 3 */ ZELDA_MOUTH_OPEN,
} DmZlMouthTextures;

static TexturePtr sEyeTextures[] = {
    gDmZl4EyeOpenNormalTex, gDmZl4EyeBlinkingTex,        gDmZl4EyeClosedTex,           gDmZl4EyeWideTex,
    gDmZl4EyeHappyTex,      gDmZl4EyeOpenLookingLeftTex, gDmZl4EyeOpenLookingRightTex,
};

typedef enum {
    /* 0 */ ZELDA_EYE_OPEN_NORMAL,
    /* 1 */ ZELDA_EYE_BLINKING,
    /* 2 */ ZELDA_EYE_CLOSED,
    /* 3 */ ZELDA_EYE_WIDE,
    /* 4 */ ZELDA_EYE_HAPPY,
    /* 5 */ ZELDA_EYE_OPEN_LOOKING_LEFT,
    /* 6 */ ZELDA_EYE_OPEN_LOOKING_RIGHT,
} DmZlEyeTextures;

void DmZl_ChangeAnimation(SkelAnime* skelAnime, AnimationInfo animation[], u16 index) {
    f32 endFrame;

    animation += index;
    endFrame = (animation->frameCount < 0.0f) ? Animation_GetLastFrame(animation->animation) : animation->frameCount;

    Animation_Change(skelAnime, animation->animation, animation->playSpeed, animation->startFrame, endFrame,
                     animation->mode, animation->morphFrames);
}

// todo remove globalCtx
void DmZl_ChangeAnimationSimple(DmZl* this, GlobalContext* globalCtx, AnimationHeader* animation, u8 animationMode) {
    //{ &gDmZl4FacingAwayHandsOverEmblemLoop, 1.0f, 0.0f, -1.0f, ANIMMODE_LOOP, -10.0f },
    //{ &gDmZl4TurningAround2Anim, 1.0f, 0.0f, -1.0f, ANIMMODE_ONCE, -10.0f },
    //{ &gDmZl4HandsOverEmblemLoopAnim, 1.0f, 0.0f, -1.0f, ANIMMODE_LOOP, -10.0f },
  
   Animation_Change(&this->skelAnime, animation, 1.0f, 0, Animation_GetLastFrame(animation),
                    animationMode , -10.0f); // all seem to use -10f in this actor

}


//void DmZl_Talking(DmZl* this, GlobalContext* globalCtx) {
//}

void DmZl_WaitingForDialogue(DmZl* this, GlobalContext* globalCtx) {
    if (this->actor.xzDistToPlayer > 100.0f){
        // slight issue: she should go back to playing faster if her animation is still up
        DmZl_SetupRaiseFlute(this, globalCtx);
    }

    // todo only say this if you have the ocarina
    // todo limit this to in front of them or turn them to face the player
    // todo find better dialogue match
    this->actor.textId = 0x1700; // ocarina debug
    func_800B8614(&this->actor, globalCtx, 120.0f); // enables talking prompt
    if (Actor_ProcessTalkRequest(&this->actor, &globalCtx->state)) {
        DmZl_ChangeAnimationSimple(this, globalCtx, &gDmZl4IdleHandsInFrontAnim, ANIMMODE_ONCE);

        //this->actionFunc = DmZl_Talking;
        //return;
    }

}

void DmZl_LoweringFlute(DmZl* this, GlobalContext* globalCtx) {
    // wait for flute lower to finish
    if (Animation_OnFrame(&this->skelAnime, this->skelAnime.endFrame)) {
      this->actionFunc = DmZl_WaitingForDialogue;
    }
}

void DmZl_SetupLowerFlute(DmZl* this, GlobalContext* globalCtx) {
    this->blinkTimer = 1;
    // doesnt loop properly, let it sit on last frame
    DmZl_ChangeAnimationSimple(this, globalCtx, &gDmZl4LowerFluteAfterPlayAnim, ANIMMODE_ONCE);
    this->actionFunc = DmZl_LoweringFlute;
}

void DmZl_PlayFluteIdle(DmZl* this, GlobalContext* globalCtx) {
    if (this->actor.xzDistToPlayer < 50.0f && Player_GetMask(globalCtx) != PLAYER_MASK_STONE){
        // if player is in range, stop and stare
        DmZl_SetupLowerFlute(this, globalCtx);
    } else {
        // play zelda's theme as a local music, taken from GuruGuru
        func_801A1D44(&this->actor.projectedPos, NA_BGM_ZELDAS_LULLABY, 540.0f); // 540 is this range or speed?
    }
} 

void DmZl_SetupPlayFluteIdle(DmZl* this, GlobalContext* globalCtx) {
    DmZl_ChangeAnimationSimple(this, globalCtx, &gDmZl4PlayingFluteAnim, ANIMMODE_LOOP);
    this->actionFunc = DmZl_PlayFluteIdle;
}


void DmZl_RaisingFlute(DmZl* this, GlobalContext* globalCtx) {
    // wait for flute raising to stop
    if (Animation_OnFrame(&this->skelAnime, this->skelAnime.endFrame)) {
      DmZl_SetupPlayFluteIdle(this, globalCtx);
    }
}

void DmZl_SetupRaiseFlute(DmZl* this, GlobalContext* globalCtx) {
    // change animation
    DmZl_ChangeAnimationSimple(this, globalCtx, &gDmZl4RaiseFluteToPlayAnim, ANIMMODE_ONCE);
    this->actionFunc = DmZl_RaisingFlute;
    this->animationIndex = -1; // tells us we are not using the system
}


void DmZl_Init(Actor* thisx, GlobalContext* globalCtx) {
    //s32 pad;
    DmZl* this = THIS;

    // all of this has been shuffled to make a new non-cutscene version    

    //this->actor.targetArrowOffset = 1000.0f;
    this->actor.targetArrowOffset = 900.0f; // not sure if this is moving correctly
    ActorShape_Init(&this->actor.shape, 0.0f, ActorShadow_DrawCircle, 24.0f);
    Actor_SetScale(&this->actor, 0.01f);
    this->unused2BA = 0; // set here, used nowhere after

    if (thisx->params == DMZL_TYPE_PLAYING_FLUTE){
        // 8 is no cull
        thisx->flags |= 1 + 0x02000000 + 0x8;
        Collider_InitAndSetCylinder(globalCtx, &this->collider, &this->actor, &sCylinderInit);
        DmZl_SetupRaiseFlute(this, globalCtx);

    } else { // 0 vanilla
        this->animationIndex = 0;

        DmZl_ChangeAnimation(&this->skelAnime, &sAnimations[this->animationIndex], ZELDA_ANIM_FACING_AWAY);
        //this->actionFunc = DmZL_NoNothing;
        //this->actionFunc = Actor_Noop;
        this->actionFunc = DmZl_UpdateCutscene; // this could have been the actionFunc the whole time, but instead he made an empty one
    }

    SkelAnime_InitFlex(globalCtx, &this->skelAnime, &gZl4Skeleton, NULL, this->jointTable, this->morphTable, ZL4_LIMB_MAX);
}

// not sure why they didnt use noop for empty destruction pointers
void DmZl_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    DmZl* this = THIS;

    if (thisx->params == DMZL_TYPE_PLAYING_FLUTE) {
       Collider_DestroyCylinder(globalCtx, &this->collider);
    }
}


void DmZl_UpdateCutscene(DmZl* this, GlobalContext* globalCtx) {
    s32 actionIndex;

    if (Cutscene_CheckActorAction(globalCtx, 0x66)) { // currently in cutscene
        actionIndex = Cutscene_GetActorActionIndex(globalCtx, 0x66);
        if (globalCtx->csCtx.frames == globalCtx->csCtx.actorActions[actionIndex]->startFrame) {
            s16 nextAnimationIndex = ZELDA_ANIM_FACING_AWAY;

            switch (globalCtx->csCtx.actorActions[actionIndex]->action) {
                case 2:
                    nextAnimationIndex = ZELDA_ANIM_TURNING_TOWARD_PLAYER;
                    break;
                case 3:
                    nextAnimationIndex = ZELDA_ANIM_GIVING_OCARINA_START;
                    break;
                case 4:
                    nextAnimationIndex = ZELDA_ANIM_PLAYING_OCARINA_START;
                    break;
                case 1:
                default:
                    break;
            }

            if (nextAnimationIndex != this->animationIndex) {
                this->animationIndex = nextAnimationIndex;
                DmZl_ChangeAnimation(&this->skelAnime, &sAnimations[this->animationIndex], ZELDA_ANIM_FACING_AWAY);
            }
        }

        Cutscene_ActorTranslateAndYaw(&this->actor, globalCtx, actionIndex);
    }

    if (Animation_OnFrame(&this->skelAnime, this->skelAnime.endFrame) != 0) {
        actionIndex = this->animationIndex;
        if ((actionIndex == 1) || (actionIndex == 3) || (actionIndex == 5)) {
            this->animationIndex++;
            DmZl_ChangeAnimation(&this->skelAnime, &sAnimations[this->animationIndex], ZELDA_ANIM_FACING_AWAY);
        }
    }
}

/**
 * Updates the eye blinking and state, and mouth textures.
 *  (Assumption: these modifications are from outside of this actor by a cutscene).
 */
void DmZl_UpdateFace(DmZl* this) {
    DECR(this->blinkTimer);

    if (this->blinkTimer < 3) {
        this->eyeTextureIndexRight = this->blinkTimer;
        this->eyeTextureIndexLeft = this->blinkTimer;
    }

    switch (this->nextEyeState) {
        case 0:
            if (this->blinkTimer == 0) {
                this->blinkTimer = Rand_S16Offset(30, 30);
            }
            break;
        case 1:
            if (this->blinkTimer == 0) {
                this->eyeTextureIndexLeft = this->eyeTextureIndexRight = ZELDA_EYE_CLOSED;
            }
            break;
        case 2:
            if (this->blinkTimer == 0) {
                this->eyeTextureIndexLeft = ZELDA_EYE_OPEN_LOOKING_LEFT;
                this->eyeTextureIndexRight = ZELDA_EYE_OPEN_LOOKING_RIGHT;
            }
            break;
        case 3:
            if (this->blinkTimer == 0) {
                this->eyeTextureIndexLeft = ZELDA_EYE_OPEN_LOOKING_RIGHT;
                this->eyeTextureIndexRight = ZELDA_EYE_OPEN_LOOKING_LEFT;
            }
            break;
        case 4:
            if (this->blinkTimer == 0) {
                this->eyeTextureIndexLeft = this->eyeTextureIndexRight = ZELDA_EYE_WIDE;
            }
            break;
        case 5:
            if (this->blinkTimer == 0) {
                this->eyeTextureIndexLeft = this->eyeTextureIndexRight = ZELDA_EYE_HAPPY;
            }
            break;
        case 6:
            if (this->blinkTimer >= 3) {
                this->blinkTimer = 0;
            }
            break;
    }

    switch (this->nextMouthState) {
        default:
            this->mouthTextureIndex = ZELDA_MOUTH_NEUTRAL;
            break;
        case 1:
            this->mouthTextureIndex = ZELDA_MOUTH_SMILING;
            break;
        case 2:
            this->mouthTextureIndex = ZELDA_MOUTH_FROWNING;
            break;
        case 3:
            this->mouthTextureIndex = ZELDA_MOUTH_OPEN;
            break;
    }

    if (this->animationIndex == ZELDA_ANIM_PLAYING_OCARINA || this->actionFunc == DmZl_PlayFluteIdle) {
        // override blinking: eyes closed while playing ocarina
        this->eyeTextureIndexLeft = this->eyeTextureIndexRight = ZELDA_EYE_CLOSED;
    }
}

void DmZl_Update(Actor* thisx, GlobalContext* globalCtx) {
    DmZl* this = THIS;

    DmZl_UpdateFace(this);
    SkelAnime_Update(&this->skelAnime);

    // instead I turned it into an actionfunc, since new NPC doesnt use it
    //if (thisx->params == DMZL_TYPE_SOT_CUTCSENE){ //DmZl_UpdateCutscene(this, globalCtx); //}

    // new
    if (thisx->params == DMZL_TYPE_PLAYING_FLUTE){
        Collider_UpdateCylinder(&this->actor, &this->collider);
        CollisionCheck_SetOC(globalCtx, &globalCtx->colChkCtx, &this->collider.base);

        // change head/chest rotation to look at player, but not when playing or about to play flute
        if (this->actor.xzDistToPlayer < 100.0f && 
          (this->actionFunc != DmZl_PlayFluteIdle && this->actionFunc != DmZl_RaisingFlute)) {
            func_800E9250(globalCtx, &this->actor, &this->headRot, &this->chestRot, this->actor.focus.pos);
        } else {
            // does the same thing that is hand written in En_Ani, but it was already a separate function
            func_800E8F08(&this->headRot, &this->chestRot); // Smooth to zero
        }
    }
    this->actionFunc(this, globalCtx);
}

s32 DmZl_OverrideLimbDraw(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, Actor* thisx) {
    DmZl* this = THIS;
    if (limbIndex == ZL4_LIMB_HEAD) {
        rot->x += this->headRot.y;
        rot->z += this->headRot.x;
    }
    if (limbIndex == ZL4_LIMB_TORSO) {
        rot->x += this->chestRot.y;
        rot->z += this->chestRot.x;
    }

    return false;
}

void DmZl_PostLimbDraw(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3s* rot, Actor* thisx) {
    //static Vec3f focusReticuleLocation = { 800.0f, 500.0f, 0.0f }; // Ani too tall
    static Vec3f focusReticuleLocation = { 000.0f, 500.0f, 0.0f };

    DmZl* this = THIS;

    if (limbIndex == ZL4_LIMB_RIGHT_HAND) {
        if ((this->animationIndex >= ZELDA_ANIM_GIVING_OCARINA_START) && (this->animationIndex < ZELDA_ANIM_MAX)) {
            OPEN_DISPS(globalCtx->state.gfxCtx);

            gSPDisplayList(POLY_OPA_DISP++, gDmZl4OcarinaDL);

            CLOSE_DISPS(globalCtx->state.gfxCtx);
        }
    }

    if (limbIndex == ZL4_LIMB_LEFT_HAND) {
        if (this->animationIndex == -1) { // flute playing
            OPEN_DISPS(globalCtx->state.gfxCtx);

            gSPDisplayList(POLY_OPA_DISP++, gDmZl4FluteDL);

            CLOSE_DISPS(globalCtx->state.gfxCtx);
        }
    }

    if (limbIndex == ZL4_LIMB_HEAD) {
       Matrix_MultiplyVector3fByState(&focusReticuleLocation, &thisx->focus.pos);
    }
}

void DmZl_Draw(Actor* thisx, GlobalContext* globalCtx) {
    DmZl* this = THIS;

    OPEN_DISPS(globalCtx->state.gfxCtx);

    gSPSegment(POLY_OPA_DISP++, 0x08, Lib_SegmentedToVirtual(sEyeTextures[this->eyeTextureIndexRight]));

    gSPSegment(POLY_OPA_DISP++, 0x09, Lib_SegmentedToVirtual(sEyeTextures[this->eyeTextureIndexLeft]));

    gSPSegment(POLY_OPA_DISP++, 0x0A, Lib_SegmentedToVirtual(sMouthTextures[this->mouthTextureIndex]));

    func_8012C28C(globalCtx->state.gfxCtx);
    SkelAnime_DrawFlexOpa(globalCtx, this->skelAnime.skeleton, this->skelAnime.jointTable, this->skelAnime.dListCount,
                          DmZl_OverrideLimbDraw, DmZl_PostLimbDraw, &this->actor);

    CLOSE_DISPS(globalCtx->state.gfxCtx);
}
