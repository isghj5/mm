/*
 * File: z_en_horse_link_child.c
 * Overlay: ovl_En_Horse_Link_Child
 * Description: Child Epona from OOT, when player learns Epona's song (Unused in MM)
 */

#include "z_en_horse_link_child.h"
#include "z64horse.h"
#include "objects/object_horse_link_child/object_horse_link_child.h"

#define FLAGS (ACTOR_FLAG_10 | ACTOR_FLAG_2000000)

#define THIS ((EnHorseLinkChild*)thisx)

void EnHorseLinkChild_Init(Actor* thisx, PlayState* play);
void EnHorseLinkChild_Destroy(Actor* thisx, PlayState* play);
void EnHorseLinkChild_Update(Actor* thisx, PlayState* play);
void EnHorseLinkChild_Draw(Actor* thisx, PlayState* play);

void EnHorseLinkChild_ActionFunc0(EnHorseLinkChild* this, PlayState* play);
void EnHorseLinkChild_SetupWaitForPlayer(EnHorseLinkChild* this, s32 nextAnimIndex);
void EnHorseLinkChild_WaitForPlayer(EnHorseLinkChild* this, PlayState* play);
void EnHorseLinkChild_SetupGreetPlayer(EnHorseLinkChild* this);
void EnHorseLinkChild_GreetPlayer(EnHorseLinkChild* this, PlayState* play);
void EnHorseLinkChild_SetupLonLonIdle(EnHorseLinkChild* this);
void EnHorseLinkChild_LonLonIdle(EnHorseLinkChild* this, PlayState* play);
void EnHorseLinkChild_SetupActionFunc5(EnHorseLinkChild* this);
void EnHorseLinkChild_ActionFunc5(EnHorseLinkChild* this, PlayState* play);
void EnHorseLinkChild_SetupActionFunc4(EnHorseLinkChild* this);
void EnHorseLinkChild_ActionFunc4(EnHorseLinkChild* this, PlayState* play);

ActorInit En_Horse_Link_Child_InitVars = {
    ACTOR_EN_HORSE_LINK_CHILD,
    ACTORCAT_BG,
    FLAGS,
    OBJECT_HORSE_LINK_CHILD,
    sizeof(EnHorseLinkChild),
    (ActorFunc)EnHorseLinkChild_Init,
    (ActorFunc)EnHorseLinkChild_Destroy,
    (ActorFunc)EnHorseLinkChild_Update,
    (ActorFunc)EnHorseLinkChild_Draw,
};

typedef enum {
    OOT_EPONA_ANIMATION_IDLE,   // head down + pawing
    OOT_EPONA_ANIMATION_WHINNY, // head shake
    OOT_EPONA_ANIMATION_WALK,   // slow
    OOT_EPONA_ANIMATION_TROT,   // mid
    OOT_EPONA_ANIMATION_GALLOP, // fast
    OOT_EPONA_ANIMATION_MAX
} OOTEponaAnimations;

AnimationHeader* sAnimations[] = {
    &gEponaIdleAnim,   // OOT_EPONA_ANIMATION_IDLE
    &gEponaWhinnyAnim, // OOT_EPONA_ANIMATION_WHINNY
    &gEponaWalkAnim,   // OOT_EPONA_ANIMATION_WALK
    &gEponaTrotAnim,   // OOT_EPONA_ANIMATION_TROT
    &gEponaGallopAnim, // OOT_EPONA_ANIMATION_GALLOP
};

static ColliderJntSphElementInit sJntSphElementsInit[] = {
    {
        {
            ELEMTYPE_UNK0,
            { 0x00000000, 0x00, 0x00 },
            { 0x00000000, 0x00, 0x00 },
            TOUCH_NONE | TOUCH_SFX_NORMAL,
            BUMP_NONE,
            OCELEM_ON,
        },
        { 13, { { 0, 0, 0 }, 10 }, 100 },
    },
};

static ColliderJntSphInit sJntSphInit = {
    {
        COLTYPE_NONE,
        AT_NONE,
        AC_ON | AC_TYPE_PLAYER,
        OC1_ON | OC1_TYPE_ALL,
        OC2_TYPE_1 | OC2_UNK1,
        COLSHAPE_JNTSPH,
    },
    ARRAY_COUNT(sJntSphElementsInit),
    sJntSphElementsInit,
};

static CollisionCheckInfoInit sColChkInfoInit = { 10, 35, 100, MASS_HEAVY };

// the animation frames that should have sfx
static s32 sAnimSoundFrames[] = { 1, 19 };

static f32 sAnimPlaySpeeds[] = { 1.0f, 1.0f, 1.5f, 1.5f, 1.5f };

static InitChainEntry sInitChain[] = {
    ICHAIN_F32(uncullZoneScale, 1200, ICHAIN_STOP),
};

typedef enum {
    OOT_EPONA_ACTION_0,            // unfinished
    OOT_EPONA_ACTION_GREET_PLAYER, // approaching
    OOT_EPONA_ACTION_WAIT_FOR_PLAYER,
    OOT_EPONA_ACTION_LONLON_IDLE,
    OOT_EPONA_ACTION_4,
    OOT_EPONA_ACTION_5,
    OOT_EPONA_ACTION_MAX
} OOTEponaActions;

static EnHorseLinkChildActionFunc sActionFuncs[] = {
    /* 0 */ EnHorseLinkChild_ActionFunc0,   // OOT_EPONA_ACTION_0
    /* 1 */ EnHorseLinkChild_GreetPlayer,   // OOT_EPONA_ACTION_GREET_PLAYER
    /* 2 */ EnHorseLinkChild_WaitForPlayer, // OOT_EPONA_ACTION_WAIT_FOR_PLAYER
    /* 3 */ EnHorseLinkChild_LonLonIdle,    // OOT_EPONA_ACTION_LONLON_IDLE
    /* 4 */ EnHorseLinkChild_ActionFunc4,   // OOT_EPONA_ACTION_4
    /* 5 */ EnHorseLinkChild_ActionFunc5,   // OOT_EPONA_ACTION_5
};

static TexturePtr sEyeTextures[] = { gEponaEyeOpenTex, gEponaEyeHalfTex, gEponaEyeClosedTex };

s8 sEyeTextureIndexOverride[] = { 0, 1, 2, 1 };

// This plays the walking/gallop sfx, which needs to be timed based on horse speed,
// this is only used for animation OOT_EPONA_ANIMATION_WALK
void EnHorseLinkChild_PlayWalkingSound(EnHorseLinkChild* this) {
    if ((sAnimSoundFrames[this->footstepCounter] < this->skin.skelAnime.curFrame) &&
        ((this->footstepCounter != 0) || !(sAnimSoundFrames[1] < this->skin.skelAnime.curFrame))) {
        Audio_PlaySfx_AtPos(&this->actor.projectedPos, NA_SE_EV_KID_HORSE_WALK);

        this->footstepCounter++;
        if (this->footstepCounter >= 2) {
            this->footstepCounter = 0;
        }
    }
}

void EnHorseLinkChild_PlaySound(EnHorseLinkChild* this) {
    if (this->animIndex == OOT_EPONA_ANIMATION_WALK) {
        EnHorseLinkChild_PlayWalkingSound(this);
    } else if (this->skin.skelAnime.curFrame == 0.0f) {
        if ((this->animIndex == OOT_EPONA_ANIMATION_TROT) || (this->animIndex == OOT_EPONA_ANIMATION_GALLOP)) {
            Audio_PlaySfx_AtPos(&this->actor.projectedPos, NA_SE_EV_KID_HORSE_RUN);
        } else if (this->animIndex == OOT_EPONA_ANIMATION_WHINNY) {
            if (Rand_ZeroOne() > 0.5f) {
                Audio_PlaySfx_AtPos(&this->actor.projectedPos, NA_SE_EV_KID_HORSE_GROAN);
            } else {
                Audio_PlaySfx_AtPos(&this->actor.projectedPos, NA_SE_EV_KID_HORSE_NEIGH);
            }
        }
    }
}

f32 EnHorseLinkChild_GetAnimSpeed(EnHorseLinkChild* this) {
    f32 animSpeed;

    if (this->animIndex == OOT_EPONA_ANIMATION_WALK) {
        animSpeed = sAnimPlaySpeeds[this->animIndex] * this->actor.speed * (1.0f / 2.0f);
    } else if (this->animIndex == OOT_EPONA_ANIMATION_TROT) {
        animSpeed = sAnimPlaySpeeds[this->animIndex] * this->actor.speed * (1.0f / 3.0f);
    } else if (this->animIndex == OOT_EPONA_ANIMATION_GALLOP) {
        animSpeed = sAnimPlaySpeeds[this->animIndex] * this->actor.speed * (1.0f / 5.0f);
    } else {
        animSpeed = sAnimPlaySpeeds[this->animIndex];
    }

    return animSpeed;
}


/// This is a copy of Skin_Init but we check if malloc returns null, because if it does that means our actor cannot spawn, and we must depart
bool Epona2_SkinInitFixed(GameState* gameState, Skin* skin, SkeletonHeader* skeletonHeader, AnimationHeader* animationHeader){

    s32 limbCount;
    s32 i;
    SkinLimb** skeleton;
    SkeletonHeader* virtSkelHeader = Lib_SegmentedToVirtual(skeletonHeader);

    skin->limbCount = virtSkelHeader->limbCount;
    skin->skeletonHeader = virtSkelHeader;
    limbCount = skin->skeletonHeader->limbCount;

    skeleton = Lib_SegmentedToVirtual(skin->skeletonHeader->segment);
    skin->vtxTable = ZeldaArena_Malloc(limbCount * sizeof(SkinLimbVtx));

    if (skin->vtxTable == NULL) return false;

    for (i = 0; i < limbCount; i++) {
        SkinLimbVtx* vtxEntry = &skin->vtxTable[i];

        if ((((SkinLimb*)Lib_SegmentedToVirtual(skeleton[i]))->segmentType != SKIN_LIMB_TYPE_ANIMATED) ||
            (((SkinLimb*)Lib_SegmentedToVirtual(skeleton[i]))->segment == NULL)) {
            vtxEntry->index = 0;

            vtxEntry->buf[0] = NULL;
            vtxEntry->buf[1] = NULL;
        } else {
            SkinAnimatedLimbData* animatedLimbData =
                Lib_SegmentedToVirtual((((SkinLimb*)Lib_SegmentedToVirtual(skeleton[i]))->segment));

            { s32 tmp; }

            vtxEntry->index = 0;
            vtxEntry->buf[0] = ZeldaArena_Malloc(animatedLimbData->totalVtxCount * sizeof(Vtx));
            if (skin->vtxTable == NULL) return false;
            vtxEntry->buf[1] = ZeldaArena_Malloc(animatedLimbData->totalVtxCount * sizeof(Vtx));
            if (skin->vtxTable == NULL) return false;

            Skin_InitAnimatedLimb(gameState, skin, i);
        }
    }

    SkelAnime_InitSkin(gameState, &skin->skelAnime, skeletonHeader, animationHeader);

    return true;
}


void EnHorseLinkChild_Init(Actor* thisx, PlayState* play) {
    EnHorseLinkChild* this = THIS;
    bool skinTest;

    Actor_ProcessInitChain(&this->actor, sInitChain);
    Actor_SetScale(&this->actor, 64.8f * 0.0001f);

    this->actor.gravity = -3.5f;

    ActorShape_Init(&this->actor.shape, 0.0f, ActorShadow_DrawHorse, 20.0f);

    //this->action = OOT_EPONA_ACTION_GREET_PLAYER;
    //this->animIndex = OOT_EPONA_ANIMATION_IDLE;
    this->actor.speed = 0.0f;
    this->actor.focus.pos = this->actor.world.pos;
    this->actor.focus.pos.y += 70.0f;

    // ERROR: if we fail to allocate skin its a crash, gotta replace this function
    //Skin_Init(&play->state, &this->skin, &gEponaSkel, &gEponaGallopAnim);
    skinTest = Epona2_SkinInitFixed(&play->state, &this->skin, &gEponaSkel, &gEponaGallopAnim);

    if (! skinTest){
      Actor_Kill(this);
      return;
    }

    Animation_PlayOnce(&this->skin.skelAnime, sAnimations[OOT_EPONA_ANIMATION_IDLE]);

    Collider_InitCylinder(play, &this->colldierCylinder);
    Collider_InitJntSph(play, &this->colliderJntSph);
    Collider_SetJntSph(play, &this->colliderJntSph, &this->actor, &sJntSphInit, this->colliderJntSphElements);
    CollisionCheck_SetInfo(&this->actor.colChkInfo, NULL, &sColChkInfoInit);

    this->footstepCounter = 0;
    this->eyeTexIndex = 0;

    //if (gSaveContext.sceneLayer >= 4) { // IS_CUTSCENE_LAYER in OOT
    //if (gHorseIsMounted) { // we only want fake-epona to be following player when epona is being ridden
        EnHorseLinkChild_SetupWaitForPlayer(this, OOT_EPONA_ANIMATION_IDLE);
    //} else {
        //EnHorseLinkChild_SetupActionFunc5(this);
    //}

    this->actor.home.rot.z = this->actor.world.rot.z = this->actor.shape.rot.z = 0;
}

void EnHorseLinkChild_Destroy(Actor* thisx, PlayState* play) {
    EnHorseLinkChild* this = THIS;

    Skin_Free(&play->state, &this->skin);
    Collider_DestroyCylinder(play, &this->colldierCylinder);
    Collider_DestroyJntSph(play, &this->colliderJntSph);
}

void EnHorseLinkChild_SetupActionFunc0(EnHorseLinkChild* this) {
    this->action = OOT_EPONA_ACTION_0;
    this->animIndex++;
    if (this->animIndex >= ARRAY_COUNT(sAnimPlaySpeeds)) {
        this->animIndex = OOT_EPONA_ANIMATION_IDLE;
    }
    Animation_PlayOnce(&this->skin.skelAnime, sAnimations[this->animIndex]);
    this->skin.skelAnime.playSpeed = EnHorseLinkChild_GetAnimSpeed(this);
}

/**
 * Mostly broken
 */
void EnHorseLinkChild_ActionFunc0(EnHorseLinkChild* this, PlayState* play) {
    this->actor.speed = 0.0f;
    if (SkelAnime_Update(&this->skin.skelAnime)) {
        EnHorseLinkChild_SetupActionFunc0(this);
    }
}

void EnHorseLinkChild_SetupWaitForPlayer(EnHorseLinkChild* this, s32 nextAnimIndex) {
    this->action = OOT_EPONA_ACTION_WAIT_FOR_PLAYER;
    this->actor.speed = 0.0f;

    if ((nextAnimIndex != OOT_EPONA_ANIMATION_IDLE) && (nextAnimIndex != OOT_EPONA_ANIMATION_WHINNY)) {
        nextAnimIndex = OOT_EPONA_ANIMATION_IDLE;
    }

    if (nextAnimIndex != this->animIndex) {
        this->animIndex = nextAnimIndex;
        Animation_Change(&this->skin.skelAnime, sAnimations[this->animIndex], EnHorseLinkChild_GetAnimSpeed(this), 0.0f,
                         Animation_GetLastFrame(sAnimations[this->animIndex]), ANIMMODE_ONCE, -5.0f);
    }
}

/**
 * Waiting for the player to get close, to notice and begin to approach the player.
 */
void EnHorseLinkChild_WaitForPlayer(EnHorseLinkChild* this, PlayState* play) {
    f32 distToPlayer = Actor_WorldDistXZToActor(&this->actor, &GET_PLAYER(play)->actor);
    s32 nextAnimIndex;

    if (SkelAnime_Update(&this->skin.skelAnime)) {
        if ((distToPlayer < 1000.0f) && (distToPlayer > 70.0f)) {
            if (gHorseIsMounted)
              EnHorseLinkChild_SetupGreetPlayer(this);
            else
              EnHorseLinkChild_SetupActionFunc4(this);
            return;
        }

        if (this->animIndex == OOT_EPONA_ANIMATION_WHINNY) {
            nextAnimIndex = OOT_EPONA_ANIMATION_IDLE;
        } else {
            nextAnimIndex = OOT_EPONA_ANIMATION_WHINNY;
        }

        if (nextAnimIndex != this->animIndex) {
            this->animIndex = nextAnimIndex;
            Animation_Change(&this->skin.skelAnime, sAnimations[this->animIndex], EnHorseLinkChild_GetAnimSpeed(this),
                             0.0f, Animation_GetLastFrame(sAnimations[this->animIndex]), ANIMMODE_ONCE, -5.0f);
        } else {
            Animation_Change(&this->skin.skelAnime, sAnimations[this->animIndex], EnHorseLinkChild_GetAnimSpeed(this),
                             0.0f, Animation_GetLastFrame(sAnimations[this->animIndex]), ANIMMODE_ONCE, 0.0f);
        }
    }
}

void EnHorseLinkChild_SetupGreetPlayer(EnHorseLinkChild* this) {
    this->action = OOT_EPONA_ACTION_GREET_PLAYER;
    this->animIndex = OOT_EPONA_ANIMATION_IDLE;
    this->actor.speed = 0.0f;
    Animation_Change(&this->skin.skelAnime, sAnimations[this->animIndex], EnHorseLinkChild_GetAnimSpeed(this), 0.0f,
                     Animation_GetLastFrame(sAnimations[this->animIndex]), ANIMMODE_ONCE, -5.0f);
}

/**
 * Chasing the player down.
 */
void EnHorseLinkChild_GreetPlayer(EnHorseLinkChild* this, PlayState* play) {
    f32 distToPlayer;
    s16 yawTowardPlayerDiff;
    s32 nextAnimIndex;

    if ((this->animIndex == OOT_EPONA_ANIMATION_GALLOP) || (this->animIndex == OOT_EPONA_ANIMATION_TROT) ||
        (this->animIndex == OOT_EPONA_ANIMATION_WALK)) {
        yawTowardPlayerDiff =
            Actor_WorldYawTowardActor(&this->actor, &GET_PLAYER(play)->actor) - this->actor.world.rot.y;
        if (yawTowardPlayerDiff > 0x12C) {
            this->actor.world.rot.y += 0x12C;
        } else if (yawTowardPlayerDiff < -0x12C) {
            this->actor.world.rot.y -= 0x12C;
        } else {
            this->actor.world.rot.y += yawTowardPlayerDiff;
        }
        this->actor.shape.rot.y = this->actor.world.rot.y;
    }

    if (SkelAnime_Update(&this->skin.skelAnime)) {
        distToPlayer = Actor_WorldDistXZToActor(&this->actor, &GET_PLAYER(play)->actor);
        if (distToPlayer > 1000.0f) {
            EnHorseLinkChild_SetupWaitForPlayer(this, 0);
            return;
        }

        if ((distToPlayer < 1000.0f) && (distToPlayer >= 300.0f)) {
            nextAnimIndex = OOT_EPONA_ANIMATION_GALLOP;
            this->actor.speed = 6.0f;
        } else if ((distToPlayer < 300.0f) && (distToPlayer >= 150.0f)) {
            nextAnimIndex = OOT_EPONA_ANIMATION_TROT;
            this->actor.speed = 4.0f;
        } else if ((distToPlayer < 150.0f) && (distToPlayer >= 70.0f)) {
            nextAnimIndex = OOT_EPONA_ANIMATION_WALK;
            this->footstepCounter = 0;
            this->actor.speed = 2.0f;
        } else {
            EnHorseLinkChild_SetupWaitForPlayer(this, 1);
            return;
        }

        if (nextAnimIndex != this->animIndex) {
            this->animIndex = nextAnimIndex;
            Animation_Change(&this->skin.skelAnime, sAnimations[this->animIndex], EnHorseLinkChild_GetAnimSpeed(this),
                             0.0f, Animation_GetLastFrame(sAnimations[this->animIndex]), ANIMMODE_ONCE, -5.0f);
        } else {
            Animation_Change(&this->skin.skelAnime, sAnimations[this->animIndex], EnHorseLinkChild_GetAnimSpeed(this),
                             0.0f, Animation_GetLastFrame(sAnimations[this->animIndex]), ANIMMODE_ONCE, 0.0f);
        }
    }
}

void EnHorseLinkChild_SetupLonLonIdle(EnHorseLinkChild* this) {
    this->action = OOT_EPONA_ACTION_LONLON_IDLE;
    this->animIndex = OOT_EPONA_ANIMATION_IDLE;
    this->actor.speed = 0.0f;
    Animation_Change(&this->skin.skelAnime, sAnimations[this->animIndex], EnHorseLinkChild_GetAnimSpeed(this), 0.0f,
                     Animation_GetLastFrame(sAnimations[this->animIndex]), ANIMMODE_ONCE, -5.0f);
}

void func_808DF088(EnHorseLinkChild* this, PlayState* play) {
    if ((this->animIndex == OOT_EPONA_ANIMATION_GALLOP) || (this->animIndex == OOT_EPONA_ANIMATION_TROT) ||
        (this->animIndex == OOT_EPONA_ANIMATION_WALK)) {
        Player* player = GET_PLAYER(play);
        s16 newYawDiff;
        s32 newYawDir;
        s32 pad;

        if (Math3D_Distance(&player->actor.world.pos, &this->actor.home.pos) < 250.0f) {
            newYawDiff = player->actor.shape.rot.y;
            if (Actor_WorldYawTowardActor(&this->actor, &player->actor) > 0) {
                newYawDir = 1;
            } else {
                newYawDir = -1;
            }
            newYawDiff += (newYawDir * 0x4000);
        } else {
            newYawDiff = Math_Vec3f_Yaw(&this->actor.world.pos, &this->actor.home.pos) - this->actor.world.rot.y;
        }

        if (newYawDiff > 0x12C) {
            this->actor.world.rot.y += 0x12C;
        } else if (newYawDiff < -0x12C) {
            this->actor.world.rot.y += -0x12C;
        } else {
            this->actor.world.rot.y += newYawDiff;
        }

        this->actor.shape.rot.y = this->actor.world.rot.y;
    }
}

/**
 * Idle in one spot, waiting for player to finish getting Epona song.
 * However, the flag was not migrated from OOT corectly, so it checks for the wrong flag.
 */
void EnHorseLinkChild_LonLonIdle(EnHorseLinkChild* this, PlayState* play) {
    Player* player;
    f32 distToPlayer;
    s32 animIsFinished;
    s32 nextAnimIndex;

    func_808DF088(this, play);

    player = GET_PLAYER(play);
    distToPlayer = Actor_WorldDistXZToActor(&this->actor, &player->actor);
    nextAnimIndex = this->animIndex;
    animIsFinished = SkelAnime_Update(&this->skin.skelAnime);

    if ((animIsFinished) || (this->animIndex == OOT_EPONA_ANIMATION_WHINNY) ||
        (this->animIndex == OOT_EPONA_ANIMATION_IDLE)) {
        //! @bug: The carry-over of this flag from OoT was not done correctly
        if (CHECK_WEEKEVENTREG(WEEKEVENTREG_ENTERED_ZORA_HALL)) {
            f32 distToHome = Math3D_Distance(&this->actor.world.pos, &this->actor.home.pos);
            s32 pad;

            if (Math3D_Distance(&player->actor.world.pos, &this->actor.home.pos) > 250.0f) {
                if (distToHome >= 300.0f) {
                    nextAnimIndex = OOT_EPONA_ANIMATION_GALLOP;
                    this->actor.speed = 6.0f;
                } else if ((distToHome < 300.0f) && (distToHome >= 150.0f)) {
                    nextAnimIndex = OOT_EPONA_ANIMATION_TROT;
                    this->actor.speed = 4.0f;
                } else if ((distToHome < 150.0f) && (distToHome >= 70.0f)) {
                    nextAnimIndex = OOT_EPONA_ANIMATION_WALK;
                    this->footstepCounter = 0;
                    this->actor.speed = 2.0f;
                } else {
                    this->actor.speed = 0.0f;
                    if (this->animIndex == OOT_EPONA_ANIMATION_IDLE) {
                        nextAnimIndex =
                            (animIsFinished == true) ? OOT_EPONA_ANIMATION_WHINNY : OOT_EPONA_ANIMATION_IDLE;
                    } else {
                        nextAnimIndex =
                            (animIsFinished == true) ? OOT_EPONA_ANIMATION_IDLE : OOT_EPONA_ANIMATION_WHINNY;
                    }
                }
            } else if (distToPlayer < 200.0f) {
                nextAnimIndex = OOT_EPONA_ANIMATION_GALLOP;
                this->actor.speed = 6.0f;
            } else if (distToPlayer < 300.0f) {
                nextAnimIndex = OOT_EPONA_ANIMATION_TROT;
                this->actor.speed = 4.0f;
            } else if (distToPlayer < 400.0f) {
                nextAnimIndex = OOT_EPONA_ANIMATION_WALK;
                this->footstepCounter = 0;
                this->actor.speed = 2.0f;
            } else {
                this->actor.speed = 0.0f;
                if (this->animIndex == OOT_EPONA_ANIMATION_IDLE) {
                    nextAnimIndex = (animIsFinished == true) ? OOT_EPONA_ANIMATION_WHINNY : OOT_EPONA_ANIMATION_IDLE;
                } else {
                    nextAnimIndex = (animIsFinished == true) ? OOT_EPONA_ANIMATION_IDLE : OOT_EPONA_ANIMATION_WHINNY;
                }
            }
        } else {
            this->actor.speed = 0.0f;
            if (this->animIndex == OOT_EPONA_ANIMATION_IDLE) {
                nextAnimIndex = (animIsFinished == true) ? OOT_EPONA_ANIMATION_WHINNY : OOT_EPONA_ANIMATION_IDLE;
            } else {
                nextAnimIndex = (animIsFinished == true) ? OOT_EPONA_ANIMATION_IDLE : OOT_EPONA_ANIMATION_WHINNY;
            }
        }
    }

    if ((nextAnimIndex != this->animIndex) || (animIsFinished == true)) {
        this->animIndex = nextAnimIndex;
        Animation_Change(&this->skin.skelAnime, sAnimations[this->animIndex], EnHorseLinkChild_GetAnimSpeed(this), 0.0f,
                         Animation_GetLastFrame(sAnimations[this->animIndex]), ANIMMODE_ONCE, -5.0f);
    } else {
        Animation_Change(&this->skin.skelAnime, sAnimations[this->animIndex], EnHorseLinkChild_GetAnimSpeed(this),
                         this->skin.skelAnime.curFrame, Animation_GetLastFrame(sAnimations[this->animIndex]),
                         ANIMMODE_ONCE, 0.0f);
    }
}

void EnHorseLinkChild_SetupActionFunc5(EnHorseLinkChild* this) {
    this->action = OOT_EPONA_ACTION_5;

    if (Rand_ZeroOne() > 0.5f) {
        this->animIndex = OOT_EPONA_ANIMATION_IDLE;
    } else {
        this->animIndex = OOT_EPONA_ANIMATION_WHINNY;
    }

    gHorsePlayedEponasSong = false;
    Animation_Change(&this->skin.skelAnime, sAnimations[this->animIndex], EnHorseLinkChild_GetAnimSpeed(this), 0.0f,
                     Animation_GetLastFrame(sAnimations[this->animIndex]), ANIMMODE_ONCE, 0.0f);
}

void EnHorseLinkChild_ActionFunc5(EnHorseLinkChild* this, PlayState* play) {
    s16 yawTowardsPlayer;

    if (gHorsePlayedEponasSong) {
        gHorsePlayedEponasSong = false;
        Audio_PlaySfx_AtPos(&this->actor.projectedPos, NA_SE_EV_KID_HORSE_NEIGH);
        EnHorseLinkChild_SetupActionFunc4(this);
        return;
    }

    this->actor.speed = 0.0f;
    yawTowardsPlayer = Actor_WorldYawTowardActor(&this->actor, &GET_PLAYER(play)->actor) - this->actor.world.rot.y;

    if ((Math_CosS(yawTowardsPlayer) < 0.7071f) && (this->animIndex == OOT_EPONA_ANIMATION_WALK)) {
        Horse_RotateToPoint(&this->actor, &GET_PLAYER(play)->actor.world.pos, 0x12C);
    }

    if (SkelAnime_Update(&this->skin.skelAnime)) {
        if (Math_CosS(yawTowardsPlayer) < 0.0f) {
            this->animIndex = OOT_EPONA_ANIMATION_WALK;
            Animation_Change(&this->skin.skelAnime, sAnimations[this->animIndex], sAnimPlaySpeeds[this->animIndex],
                             0.0f, Animation_GetLastFrame(sAnimations[OOT_EPONA_ANIMATION_WALK]), ANIMMODE_ONCE, -5.0f);
        } else {
            EnHorseLinkChild_SetupActionFunc5(this);
        }
    }
}

void EnHorseLinkChild_SetupActionFunc4(EnHorseLinkChild* this) {
    this->timer = 0;
    this->action = OOT_EPONA_ACTION_4;
    this->animIndex = OOT_EPONA_ANIMATION_WALK;
    this->isReturningHome = false;
    this->actor.speed = 2.0f;
    Animation_Change(&this->skin.skelAnime, sAnimations[this->animIndex], EnHorseLinkChild_GetAnimSpeed(this), 0.0f,
                     Animation_GetLastFrame(sAnimations[this->animIndex]), ANIMMODE_ONCE, -5.0f);
}

void EnHorseLinkChild_ActionFunc4(EnHorseLinkChild* this, PlayState* play) {
    Player* player = GET_PLAYER(play);
    f32 distToTargetLoc;
    s32 nextAnimIndex;

    this->timer++;
    if (this->timer > 300) {
        this->isReturningHome = true;
    }

    if ((this->animIndex == OOT_EPONA_ANIMATION_GALLOP) || (this->animIndex == OOT_EPONA_ANIMATION_TROT) ||
        (this->animIndex == OOT_EPONA_ANIMATION_WALK)) {
        if (this->isReturningHome == false) {
            Horse_RotateToPoint(&this->actor, &player->actor.world.pos, 0x12C);
        } else {
            Horse_RotateToPoint(&this->actor, &this->actor.home.pos, 0x12C);
        }
    }

    if (SkelAnime_Update(&this->skin.skelAnime)) {
        if (this->isReturningHome == false) {
            distToTargetLoc = Actor_WorldDistXZToActor(&this->actor, &GET_PLAYER(play)->actor);
        } else {
            distToTargetLoc = Math3D_Distance(&this->actor.world.pos, &this->actor.home.pos);
        }

        if (this->isReturningHome == false) {
            if (distToTargetLoc >= 300.0f) {
                nextAnimIndex = OOT_EPONA_ANIMATION_GALLOP;
                this->actor.speed = 6.0f;
            } else if (distToTargetLoc >= 150.0f) {
                nextAnimIndex = OOT_EPONA_ANIMATION_TROT;
                this->actor.speed = 4.0f;
            } else {
                nextAnimIndex = OOT_EPONA_ANIMATION_WALK;
                this->footstepCounter = 0;
                this->actor.speed = 2.0f;
            }
        } else if (distToTargetLoc >= 300.0f) {
            nextAnimIndex = OOT_EPONA_ANIMATION_GALLOP;
            this->actor.speed = 6.0f;
        } else if (distToTargetLoc >= 150.0f) {
            nextAnimIndex = OOT_EPONA_ANIMATION_TROT;
            this->actor.speed = 4.0f;
        } else if (distToTargetLoc >= 70.0f) {
            nextAnimIndex = OOT_EPONA_ANIMATION_WALK;
            this->footstepCounter = 0;
            this->actor.speed = 2.0f;
        } else {
            EnHorseLinkChild_SetupActionFunc5(this);
            return;
        }

        if (nextAnimIndex != this->animIndex) {
            this->animIndex = nextAnimIndex;
            Animation_Change(&this->skin.skelAnime, sAnimations[this->animIndex], EnHorseLinkChild_GetAnimSpeed(this),
                             0.0f, Animation_GetLastFrame(sAnimations[this->animIndex]), ANIMMODE_ONCE, -5.0f);
        } else {
            Animation_Change(&this->skin.skelAnime, sAnimations[this->animIndex], EnHorseLinkChild_GetAnimSpeed(this),
                             0.0f, Animation_GetLastFrame(sAnimations[this->animIndex]), ANIMMODE_ONCE, 0.0f);
        }
    }
}

void EnHorseLinkChild_Update(Actor* thisx, PlayState* play) {
    s32 pad;
    EnHorseLinkChild* this = THIS;

    sActionFuncs[this->action](this, play);

    Actor_MoveWithGravity(&this->actor);
    Actor_UpdateBgCheckInfo(play, &this->actor, 20.0f, 55.0f, 100.0f,
                            UPDBGCHECKINFO_FLAG_1 | UPDBGCHECKINFO_FLAG_4 | UPDBGCHECKINFO_FLAG_8 |
                                UPDBGCHECKINFO_FLAG_10);

    this->actor.focus.pos = this->actor.world.pos;
    this->actor.focus.pos.y += 70.0f;

    if ((Rand_ZeroOne() < 0.025f) && (this->eyeTexIndex == 0)) {
        this->eyeTexIndex++;
    } else if (this->eyeTexIndex > 0) {
        this->eyeTexIndex++;
        if (this->eyeTexIndex >= 4) {
            this->eyeTexIndex = 0;
        }
    }

    Collider_UpdateCylinder(&this->actor, &this->colldierCylinder);
    CollisionCheck_SetOC(play, &play->colChkCtx, &this->colldierCylinder.base);

    EnHorseLinkChild_PlaySound(this);
}

void EnHorseLinkChild_PostSkinDraw(Actor* thisx, PlayState* play, Skin* skin) {
    Vec3f sp4C;
    Vec3f sp40;
    EnHorseLinkChild* this = THIS;
    s32 i;

    for (i = 0; i < this->colliderJntSph.count; i++) {
        sp4C.x = this->colliderJntSph.elements[i].dim.modelSphere.center.x;
        sp4C.y = this->colliderJntSph.elements[i].dim.modelSphere.center.y;
        sp4C.z = this->colliderJntSph.elements[i].dim.modelSphere.center.z;

        Skin_GetLimbPos(skin, this->colliderJntSph.elements[i].dim.limb, &sp4C, &sp40);

        this->colliderJntSph.elements[i].dim.worldSphere.center.x = sp40.x;
        this->colliderJntSph.elements[i].dim.worldSphere.center.y = sp40.y;
        this->colliderJntSph.elements[i].dim.worldSphere.center.z = sp40.z;
        this->colliderJntSph.elements[i].dim.worldSphere.radius =
            this->colliderJntSph.elements[i].dim.modelSphere.radius * this->colliderJntSph.elements[i].dim.scale;
    }

    CollisionCheck_SetOC(play, &play->colChkCtx, &this->colliderJntSph.base);
}

s32 EnHorseLinkChild_OverrideSkinDraw(Actor* thisx, PlayState* play, s32 limbIndex, Skin* skin) {
    EnHorseLinkChild* this = THIS;

    OPEN_DISPS(play->state.gfxCtx);

    if (limbIndex == OBJECT_HORSE_LINK_CHILD_LIMB_0D) {
        u8 index = sEyeTextureIndexOverride[this->eyeTexIndex];

        gSPSegment(POLY_OPA_DISP++, 0x08, Lib_SegmentedToVirtual(sEyeTextures[index]));
    }

    CLOSE_DISPS(play->state.gfxCtx);

    return true;
}

void Debug_PrintToScreen(Actor* thisx, PlayState* play) {
    EnHorseLinkChild* this = THIS; // replace with THIS actor
    // with explanation comments
    GfxPrint printer;
    Gfx* gfx;

    OPEN_DISPS(play->state.gfxCtx);

    // the dlist will be written in the opa buffer because that buffer is larger,
    // but executed from the overlay buffer (overlay draws last, for example the hud is drawn to overlay)
    gfx = POLY_OPA_DISP + 1;
    gSPDisplayList(OVERLAY_DISP++, gfx);

    // initialize GfxPrint struct
    GfxPrint_Init(&printer);
    GfxPrint_Open(&printer, gfx);

    GfxPrint_SetColor(&printer, 255, 255, 255, 255);
    GfxPrint_SetPos(&printer, 1, 10);
    GfxPrint_Printf(&printer, "actor struct loc: %X", &thisx);

    { // address locations
        //void* actionFuncAddr = this->actionFunc;
        void* actionFuncAddr = sActionFuncs[this->action];
        u32 convertedAddr = (u32) Fault_ConvertAddress(actionFuncAddr);
        GfxPrint_SetPos(&printer, 1, 11);
        GfxPrint_Printf(&printer, "actionfunc vram:        func_%X", convertedAddr);
        GfxPrint_SetPos(&printer, 1, 12);
        GfxPrint_Printf(&printer, "actionfunc actual ram:  %X", actionFuncAddr);

    }

    GfxPrint_SetPos(&printer, 1, 13);
    
    //GfxPrint_Printf(&printer, "drawflags %X", this->drawFlags);
    //GfxPrint_Printf(&printer, "BREG86 %X", BREG(86));
    GfxPrint_Printf(&printer, "skin vtx size %X", sizeof(this->skin));

    // end of text printing
    gfx = GfxPrint_Close(&printer);
    GfxPrint_Destroy(&printer);

    gSPEndDisplayList(gfx++);
    // make the opa dlist jump over the part that will be executed as part of overlay
    gSPBranchList(POLY_OPA_DISP, gfx);
    POLY_OPA_DISP = gfx;

    CLOSE_DISPS(play->state.gfxCtx);
    //Debug_PrintToScreen(thisx, play); // put this in your actors draw func
} // */

void EnHorseLinkChildNew_Tint(Actor* thisx, PlayState* play, s16 intensity){
    EnHorseLinkChild* this = THIS;

    OPEN_DISPS(play->state.gfxCtx);

    Gfx* displayListHead;
    f32 cos;
    //Color_RGBA8 color = { 0, 0, 0, 255 }; // just black works, but I want to neutralize her red some
    // too blue
    //Color_RGBA8 color = { 0x20, 0xBE, 0xFF, 255 }; // 20BEFF: oposite of her color
    Color_RGBA8 color = { 0x2, 0xB, 0xF, 255 }; // 20BEFF: oposite of her color

    //cos = Math_CosS((0x4000 / intensity) * ); //arg2
    cos = Math_CosS(this->timer); //arg2

    displayListHead = POLY_OPA_DISP;

    gDPPipeSync(displayListHead++);

    gDPSetFogColor(displayListHead++, color.r, color.g, color.b, color.a);
    gSPFogPosition(displayListHead++, 0, (s16)(2800.0f * fabsf(cos)) + 1700);

    POLY_OPA_DISP = displayListHead;

    CLOSE_DISPS(play->state.gfxCtx);


    // run func_800AE5A0 after drawing her
}


void EnHorseLinkChild_Draw(Actor* thisx, PlayState* play) {
    EnHorseLinkChild* this = THIS;

    EnHorseLinkChildNew_Tint(thisx, play, 1); 
    
    Gfx_SetupDL25_Opa(play->state.gfxCtx);
    func_80138258(&this->actor, play, &this->skin, EnHorseLinkChild_PostSkinDraw, EnHorseLinkChild_OverrideSkinDraw,
                  true);
  
    func_800AE5A0(play);

    if (BREG(86))
    {
      Debug_PrintToScreen(thisx, play); // put this in your actors draw func
    }
}
