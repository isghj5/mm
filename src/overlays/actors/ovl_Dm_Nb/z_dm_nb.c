/*
// this used to be a credits actor, now its our puppet
 */

#include "z_dm_nb.h"
#include "objects/object_nb/object_nb.h"

#define FLAGS (ACTOR_FLAG_TARGETABLE | ACTOR_FLAG_FRIENDLY | ACTOR_FLAG_10 | ACTOR_FLAG_20)

#define THIS ((DmNb*)thisx)

void DmNb_Init(Actor* thisx, PlayState* play);
void DmNb_Destroy(Actor* thisx, PlayState* play);
void DmNb_Update(Actor* thisx, PlayState* play);
void DmNb_Draw(Actor* thisx, PlayState* play);

void unkfunc_80BC0EAC(DmNb* this, PlayState* play);

#define EN_NB_FLAG_NONE (0)
#define EN_NB_FLAG_8 (1 << 3)
#define EN_NB_FLAG_10 (1 << 4)
#define EN_NB_FLAG_20 (1 << 5)
#define EN_NB_FLAG_40 (1 << 6)
#define EN_NB_FLAG_80 (1 << 7)
#define EN_NB_FLAG_100 (1 << 8)
#define EN_NB_FLAG_200 (1 << 9)
#define EN_NB_FLAG_400 (1 << 10)

typedef enum DmNbScheduleResult {
    /* 0 */ EN_NB_SCH_NONE,
    /* 1 */ EN_NB_SCH_1,
    /* 2 */ EN_NB_SCH_2,
    /* 3 */ EN_NB_SCH_3,
    /* 4 */ EN_NB_SCH_4
} DmNbScheduleResult;

#include "build/src/overlays/actors/ovl_En_Nb/scheduleScripts.schl.inc"

static u8 D_80BC1464[] = {
    0x1B, 0x04, 0x08, 0x00, 0x6A, 0x0A, 0x00, 0x10, 0x00, 0x08, 0x00, 0x10, 0x00, 0x08, 0x00, 0x00, 0x00, 0x08, 0x0E,
    0x29, 0x12, 0x2D, 0x00, 0x0E, 0x0C, 0x10, 0x0E, 0x29, 0x01, 0x2D, 0x00, 0x0E, 0x0C, 0x10, 0x0E, 0x29, 0x02, 0x0C,
    0x0F, 0x29, 0x03, 0x0C, 0x05, 0x00, 0x00, 0x00, 0x06, 0x00, 0x22, 0x31, 0x2D, 0x00, 0x0E, 0x12, 0x10, 0x30, 0x1C,
    0x04, 0x04, 0x0E, 0x29, 0x04, 0x0C, 0x20, 0x00, 0x03, 0x00, 0x04, 0x15, 0x09, 0x00, 0xC4, 0x09, 0x00, 0x00, 0x0F,
    0x29, 0x05, 0x0C, 0x15, 0x09, 0x00, 0xB9, 0x30, 0x1D, 0x04, 0x04, 0x0E, 0x29, 0x0B, 0x0C, 0x20, 0x00, 0x03, 0x00,
    0x04, 0x15, 0x09, 0x00, 0xA8, 0x09, 0x00, 0x00, 0x0F, 0x29, 0x0C, 0x0C, 0x15, 0x09, 0x00, 0x9D, 0x20, 0x00, 0x03,
    0x00, 0x17, 0x1B, 0x04, 0x04, 0x00, 0x09, 0x0E, 0x29, 0x11, 0x2D, 0x00, 0x0E, 0x0C, 0x16, 0x10, 0x0E, 0x29, 0x0A,
    0x2D, 0x00, 0x0E, 0x0C, 0x16, 0x10, 0x1B, 0x04, 0x04, 0x00, 0x3B, 0x0E, 0x29, 0x0D, 0x0C, 0x05, 0x00, 0x00, 0x00,
    0x0A, 0x00, 0x00, 0x0E, 0x29, 0x10, 0x2D, 0x00, 0x0E, 0x0C, 0x12, 0x16, 0x10, 0x0E, 0x29, 0x0E, 0x00, 0x32, 0x04,
    0x00, 0x59, 0x0C, 0x0F, 0x29, 0x0F, 0x0C, 0x12, 0x06, 0x00, 0x0C, 0x00, 0x00, 0x13, 0x00, 0x0C, 0x2F, 0x00, 0x00,
    0x2E, 0x2D, 0x00, 0x2A, 0x2D, 0x00, 0x0E, 0x11, 0x32, 0x04, 0x0C, 0x16, 0x10, 0x0E, 0x29, 0x06, 0x0C, 0x05, 0x00,
    0x0A, 0x00, 0x00, 0x00, 0x00, 0x0E, 0x29, 0x07, 0x2D, 0x00, 0x0E, 0x0C, 0x12, 0x16, 0x10, 0x0E, 0x29, 0x08, 0x00,
    0x32, 0x02, 0x00, 0x1E, 0x0C, 0x0F, 0x29, 0x09, 0x0C, 0x12, 0x06, 0x00, 0x0C, 0x00, 0x00, 0x13, 0x00, 0x0C, 0x2F,
    0x00, 0x00, 0x2E, 0x2D, 0x00, 0x29, 0x2D, 0x00, 0x0E, 0x11, 0x32, 0x02, 0x0C, 0x16, 0x10, 0x2D, 0x00, 0x0E, 0x0C,
    0x12, 0x16, 0x10, 0x00, 0x00, 0x00,
};

static u8 D_80BC1574[] = {
    0x09, 0x00, 0x00, 0x0E, 0x28, 0xC7, 0x0C, 0x09, 0x00, 0x00, 0x17, 0x0E, 0x28, 0xC8, 0x0C, 0x09, 0x00,
    0x00, 0x18, 0x0E, 0x28, 0xC9, 0x0C, 0x09, 0x00, 0x00, 0x17, 0x0E, 0x28, 0xCA, 0x0C, 0x09, 0x00, 0x00,
    0x18, 0x0E, 0x28, 0xCB, 0x0C, 0x09, 0x00, 0x00, 0x17, 0x0E, 0x28, 0xCC, 0x0C, 0x09, 0x00, 0x00, 0x18,
    0x0E, 0x28, 0xCD, 0x0C, 0x09, 0x00, 0x00, 0x17, 0x0E, 0x28, 0xCE, 0x0C, 0x09, 0x00, 0x00, 0x18, 0x0E,
    0x28, 0xCF, 0x2D, 0x00, 0x01, 0x2D, 0x00, 0x0E, 0x0C, 0x09, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00,
};

static u8 D_80BC15C8[] = {
    0x0E, 0x23, 0x62, 0x2D, 0x00, 0x0E, 0x0C, 0x10,
};

ActorInit Dm_Nb_InitVars = {
    /**/ ACTOR_DM_NB,
    /**/ ACTORCAT_NPC,
    /**/ FLAGS,
    /**/ OBJECT_NB,
    /**/ sizeof(DmNb),
    /**/ DmNb_Init,
    /**/ DmNb_Destroy,
    /**/ DmNb_Update,
    /**/ DmNb_Draw,
};

static ColliderCylinderInit sCylinderInit = {
    {
        COLTYPE_HIT1,
        AT_NONE,
        AC_NONE,
        OC1_ON | OC1_TYPE_ALL,
        OC2_TYPE_1,
        COLSHAPE_CYLINDER,
    },
    {
        ELEMTYPE_UNK1,
        { 0x00000000, 0x00, 0x00 },
        { 0x00000000, 0x00, 0x00 },
        TOUCH_NONE | TOUCH_SFX_NORMAL,
        BUMP_NONE,
        OCELEM_ON,
    },
    { 10, 68, 0, { 0, 0, 0 } },
};

static CollisionCheckInfoInit2 sColChkInfoInit = { 0, 0, 0, 0, MASS_IMMOVABLE };

Actor* DmNb_FindActor(DmNb* this, PlayState* play, u8 actorCategory, s16 actorId) {
    Actor* actorIter = NULL;

    while (true) {
        actorIter = SubS_FindActor(play, actorIter, actorCategory, actorId);

        if (actorIter == NULL) {
            break;
        }

        if ((this != (DmNb*)actorIter) && (actorIter->update != NULL)) {
            break;
        }

        if (actorIter->next == NULL) {
            actorIter = NULL;
            break;
        }

        actorIter = actorIter->next;
    }

    return actorIter;
}

void DmNb_UpdateSkelAnime(DmNb* this) {
    this->skelAnime.playSpeed = this->animPlaySpeed;
    SkelAnime_Update(&this->skelAnime);
}

static AnimationInfoS sAnimationInfo[EN_NB_ANIM_MAX] = {
    { &gNbIdleAnim, 1.0f, 0, -1, ANIMMODE_LOOP, 0 },      // EN_NB_ANIM_0
    { &gNbIdleAnim, 1.0f, 0, -1, ANIMMODE_LOOP, -4 },     // EN_NB_ANIM_1
    { &gNbTalkAnim, 1.0f, 0, -1, ANIMMODE_ONCE, 0 },      // EN_NB_ANIM_TALK_ONCE
    { &gNbTalkAnim, 1.0f, 0, -1, ANIMMODE_LOOP, -4 },     // EN_NB_ANIM_TALK_LOOP
    { &gNbAngryAnim, 1.0f, 0, -1, ANIMMODE_LOOP, -4 },    // EN_NB_ANIM_ANGRY
    { &gNbRelievedAnim, 1.0f, 0, -1, ANIMMODE_ONCE, -4 }, // EN_NB_ANIM_RELIEVED
};

s32 DmNb_ChangeAnim(DmNb* this, DmNbAnimation animIndex) {
    s32 changeAnim = false;
    s32 didAnimChange = false;

    if ((animIndex == EN_NB_ANIM_0) || (animIndex == EN_NB_ANIM_1)) {
        if ((this->animIndex != EN_NB_ANIM_0) && (this->animIndex != EN_NB_ANIM_1)) {
            changeAnim = true;
        }
    } else if (animIndex != this->animIndex) {
        changeAnim = true;
    }

    if (changeAnim) {
        this->animIndex = animIndex;
        didAnimChange = SubS_ChangeAnimationByInfoS(&this->skelAnime, sAnimationInfo, animIndex);
        this->animPlaySpeed = this->skelAnime.playSpeed;
    }

    return didAnimChange;
}

void unkfunc_80BBFF24(DmNb* this, PlayState* play) {
    f32 yDiff;
    s32 pad;

    Collider_UpdateCylinder(&this->actor, &this->collider);

    yDiff = this->actor.focus.pos.y - this->actor.world.pos.y;
    this->collider.dim.height = yDiff;
    CollisionCheck_SetOC(play, &play->colChkCtx, &this->collider.base);
}

Actor* unkfunc_80BBFF90(DmNb* this, PlayState* play) {
    Actor* actor;

    if (this->scheduleResult == EN_NB_SCH_2) {
        actor = DmNb_FindActor(this, play, ACTORCAT_NPC, ACTOR_EN_AN);
    } else {
        actor = &GET_PLAYER(play)->actor;
    }
    return actor;
}

s32 unkfunc_80BBFFD4(DmNb* this, s16 csId) {
    s32 ret = false;

    if (CutsceneManager_GetCurrentCsId() == CS_ID_GLOBAL_TALK) {
        CutsceneManager_Stop(CS_ID_GLOBAL_TALK);
        CutsceneManager_Queue(csId);
    } else if (CutsceneManager_IsNext(csId)) {
        CutsceneManager_StartWithPlayerCs(csId, &this->actor);
        ret = true;
    } else {
        CutsceneManager_Queue(csId);
    }

    return ret;
}

s16 unkfunc_80BC0050(DmNb* this, s32 numCutscenes) {
    s16 csId = this->actor.csId;
    s32 i;

    for (i = 0; i < numCutscenes; i++) {
        csId = CutsceneManager_GetAdditionalCsId(csId);
    }

    return csId;
}

typedef enum DmNbBehaviour {
    /* 0 */ ENNB_BEHAVIOUR_0,
    /* 1 */ ENNB_BEHAVIOUR_1,
    /* 2 */ ENNB_BEHAVIOUR_2,
    /* 3 */ ENNB_BEHAVIOUR_3,
    /* 4 */ ENNB_BEHAVIOUR_4,
    /* 5 */ ENNB_BEHAVIOUR_5,
    /* 6 */ ENNB_BEHAVIOUR_6,
    /* 7 */ ENNB_BEHAVIOUR_7,
    /* 8 */ ENNB_BEHAVIOUR_8,
    /* 9 */ ENNB_BEHAVIOUR_9
} DmNbBehaviour;

s32 unkfunc_80BC00AC(Actor* thisx, PlayState* play) {
    DmNb* this = THIS;
    s16 csId = unkfunc_80BC0050(this, 0);
    s32 ret = false;

    switch (this->behaviour) {
        case ENNB_BEHAVIOUR_0:
            if (!unkfunc_80BBFFD4(this, csId)) {
                break;
            }
        // fallthrough
        case ENNB_BEHAVIOUR_2:
        case ENNB_BEHAVIOUR_4:
        case ENNB_BEHAVIOUR_6:
        case ENNB_BEHAVIOUR_8:
            Camera_SetTargetActor(Play_GetCamera(play, CutsceneManager_GetCurrentSubCamId(csId)), &this->actor);
            this->behaviour++;
            ret = true;
            break;

        case ENNB_BEHAVIOUR_1:
        case ENNB_BEHAVIOUR_3:
        case ENNB_BEHAVIOUR_5:
        case ENNB_BEHAVIOUR_7:
            if ((this->actor.child != NULL) && (this->actor.child->update != NULL)) {
                Camera_SetTargetActor(Play_GetCamera(play, CutsceneManager_GetCurrentSubCamId(csId)),
                                      this->actor.child);
            }
            this->behaviour++;
            ret = true;
            break;

        case ENNB_BEHAVIOUR_9:
            CutsceneManager_Stop(csId);
            this->behaviour++;
            ret = true;
            break;

        default:
            break;
    }

    return ret;
}

s32 unkfunc_80BC01DC(Actor* thisx, PlayState* play) {
    DmNb* this = THIS;
    s32 pad;
    s32 ret = false;

    switch (this->behaviour) {
        case ENNB_BEHAVIOUR_0:
            if (Player_GetMask(play) == PLAYER_MASK_ALL_NIGHT) {
                this->behaviour = ENNB_BEHAVIOUR_1;
            } else {
                this->behaviour = ENNB_BEHAVIOUR_5;
            }
            break;

        case ENNB_BEHAVIOUR_1:
            // Setup a black fill-screen, although initialize to 0 alpha
            Play_FillScreen(&play->state, true, 0, 0, 0, 0);
            this->storyTimer = 40;
            this->behaviour = (u16)(this->behaviour + 1);
            break;

        case ENNB_BEHAVIOUR_2:
            // Slowly increase alpha to fill the screen with a black rectangle
            R_PLAY_FILL_SCREEN_ALPHA = TRUNCF_BINANG(255.0f - (((f32)ABS_ALT(20 - this->storyTimer) / 20.0f) * 255.0f));

            if (this->storyTimer == 20) {
                if (CHECK_EVENTINF(EVENTINF_42)) {
                    play->interfaceCtx.storyType = STORY_TYPE_MASK_FESTIVAL;
                } else {
                    play->interfaceCtx.storyType = STORY_TYPE_GIANTS_LEAVING;
                }
                play->interfaceCtx.storyState = STORY_STATE_FADE_IN;
                R_STORY_FILL_SCREEN_ALPHA = 255;
            }

            if (DECR(this->storyTimer) == 0) {
                this->behaviour++;
            }
            break;

        case ENNB_BEHAVIOUR_3:
            play->interfaceCtx.storyState = STORY_STATE_SETUP_IDLE;
            this->behaviour++;
            ret = true;
            break;

        case ENNB_BEHAVIOUR_4:
            play->interfaceCtx.storyState = STORY_STATE_FADE_OUT;
            this->behaviour++;
            // fallthrough
        case ENNB_BEHAVIOUR_5:
            if (!CHECK_EVENTINF(EVENTINF_42)) {
                gSaveContext.save.time = CLOCK_TIME(8, 0);
                Sram_IncrementDay();
            } else {
                Environment_SetTimeJump(120.0f);
            }

            this->behaviour++;
            play->nextEntrance = ENTRANCE(STOCK_POT_INN, 2);
            gSaveContext.nextCutsceneIndex = 0;
            play->transitionTrigger = TRANS_TRIGGER_START;
            play->transitionType = TRANS_TYPE_FADE_BLACK;
            gSaveContext.nextTransitionType = TRANS_TYPE_FADE_BLACK_SLOW;
            SET_EVENTINF(EVENTINF_43);
            break;

        default:
            break;
    }

    return ret;
}

u8* unkfunc_80BC045C(DmNb* this, PlayState* play) {
    if (CHECK_EVENTINF(EVENTINF_43)) {
        this->msgEventCallback = unkfunc_80BC01DC;
        return D_80BC1464;
    } else if (this->scheduleResult == EN_NB_SCH_2) {
        this->msgEventCallback = unkfunc_80BC00AC;
        return D_80BC1574;
    } else if (Player_GetMask(play) == PLAYER_MASK_KAFEIS_MASK) {
        return D_80BC15C8;
    } else {
        this->msgEventCallback = unkfunc_80BC01DC;
        return D_80BC1464;
    }
}

s32 unkfunc_80BC04FC(DmNb* this, PlayState* play) {
    s32 ret = false;

    if (((this->stateFlags & SUBS_OFFER_MODE_MASK) != SUBS_OFFER_MODE_NONE) &&
        Actor_TalkOfferAccepted(&this->actor, &play->state)) {
        this->stateFlags |= EN_NB_FLAG_20;
        SubS_SetOfferMode(&this->stateFlags, SUBS_OFFER_MODE_NONE, SUBS_OFFER_MODE_MASK);
        this->behaviour = ENNB_BEHAVIOUR_0;
        this->msgEventCallback = NULL;
        this->actor.child = this->unk_1E8;
        this->msgEventScript = unkfunc_80BC045C(this, play);
        this->stateFlags |= EN_NB_FLAG_20;
        this->actionFunc = unkfunc_80BC0EAC;
        ret = true;
    }
    return ret;
}

void unkfunc_80BC05A8(DmNb* this, PlayState* play) {
    Player* player = GET_PLAYER(play);
    TextState talkState = Message_GetState(&play->msgCtx);
    u16 textId = play->msgCtx.currentTextId;

    if ((&this->actor == player->talkActor) && ((textId < 0xFF) || (textId > 0x200)) &&
        (talkState == TEXT_STATE_FADING) && (this->prevTalkState == TEXT_STATE_FADING)) {
        if ((play->state.frames % 3) == 0) {
            if (this->unk_26C == 120.0f) {
                this->unk_26C = 0.0f;
            } else {
                this->unk_26C = 120.0f;
            }
        }
    } else {
        this->unk_26C = 0.0f;
    }

    Math_SmoothStepToF(&this->unk_270, this->unk_26C, 0.8f, 40.0f, 10.0f);
    Matrix_Translate(this->unk_270, 0.0f, 0.0f, MTXMODE_APPLY);
    this->prevTalkState = talkState;
}

void unkfunc_80BC06C4(DmNb* this) {
    s32 pad;
    Vec3f sp40;
    Vec3f sp34;
    Player* player;

    Math_Vec3f_Copy(&sp40, &this->unk_1E8->world.pos);
    Math_Vec3f_Copy(&sp34, &this->actor.world.pos);
    Math_ApproachS(&this->headRotY, Math_Vec3f_Yaw(&sp34, &sp40) - this->actor.shape.rot.y, 4, 0x2AA8);

    this->headRotY = CLAMP(this->headRotY, -0x1FFE, 0x1FFE);

    Math_Vec3f_Copy(&sp34, &this->actor.focus.pos);

    if (this->unk_1E8->id == ACTOR_PLAYER) {
        player = (Player*)this->unk_1E8;

        sp40.y = player->bodyPartsPos[PLAYER_BODYPART_HEAD].y + 3.0f;
    } else {
        Math_Vec3f_Copy(&sp40, &this->unk_1E8->focus.pos);
    }

    Math_ApproachS(&this->headRotZ, Math_Vec3f_Pitch(&sp34, &sp40), 4, 0x2AA8);

    this->headRotZ = CLAMP(this->headRotZ, -0x1554, 0x1554);
}

void unkfunc_80BC0800(DmNb* this) {
    if (this->stateFlags & EN_NB_FLAG_20) {
        if ((this->unk_1E8 != NULL) && (this->unk_1E8->update != NULL)) {
            if (DECR(this->unk_282) == 0) {
                unkfunc_80BC06C4(this);
                this->stateFlags &= ~EN_NB_FLAG_400;
                this->stateFlags |= EN_NB_FLAG_100;
                return;
            }
        }
    }

    if (this->stateFlags & EN_NB_FLAG_100) {
        this->stateFlags &= ~EN_NB_FLAG_100;
        this->headRotZ = 0;
        this->headRotY = 0;
        this->unk_282 = 20;
    } else if (DECR(this->unk_282) == 0) {
        this->stateFlags |= EN_NB_FLAG_400;
    }
}

// Related to both stories?
void unkfunc_80BC08E0(DmNb* this, PlayState* play) {
    if (this->unk_284 == 0) {
        DmNb_ChangeAnim(this, EN_NB_ANIM_TALK_ONCE);
        this->stateFlags |= EN_NB_FLAG_400;
        this->unk_284++;
    } else if ((this->unk_284 == 1) && Animation_OnFrame(&this->skelAnime, this->skelAnime.endFrame)) {
        DmNb_ChangeAnim(this, EN_NB_ANIM_1);
        this->stateFlags &= ~EN_NB_FLAG_400;
        this->unk_284++;
    }
}

void unkfunc_80BC0978(DmNb* this, PlayState* play) {
    if (this->unk_284 == 0) {
        DmNb_ChangeAnim(this, EN_NB_ANIM_RELIEVED);
        this->stateFlags &= ~EN_NB_FLAG_20;
        this->stateFlags |= EN_NB_FLAG_400;
        this->unk_284++;
    } else if ((this->unk_284 == 1) && Animation_OnFrame(&this->skelAnime, this->skelAnime.endFrame)) {
        DmNb_ChangeAnim(this, EN_NB_ANIM_TALK_LOOP);
        this->stateFlags &= ~EN_NB_FLAG_400;
        this->unk_284++;
    }
}

s32 unkfunc_80BC0A18(DmNb* this, PlayState* play) {
    Player* player = GET_PLAYER(play);
    u16 currentTextId = play->msgCtx.currentTextId;

    if (player->stateFlags1 & PLAYER_STATE1_40) {
        this->stateFlags |= EN_NB_FLAG_80;

        if (this->textId != currentTextId) {
            switch (currentTextId) {
                case 0x28CF:
                    this->stateFlags |= EN_NB_FLAG_20;
                    DmNb_ChangeAnim(this, EN_NB_ANIM_TALK_LOOP);
                    break;

                case 0x2904:
                case 0x290B:
                    this->unk_18C = unkfunc_80BC08E0;
                    this->unk_284 = 0;
                    break;

                case 0x28CD:
                    this->unk_18C = unkfunc_80BC0978;
                    this->unk_284 = 0;
                    break;

                case 0x28CB:
                    DmNb_ChangeAnim(this, EN_NB_ANIM_ANGRY);
                    break;

                case 0x28C7:
                case 0x2901:
                case 0x2902:
                case 0x2906:
                case 0x290D:
                case 0x2912:
                    DmNb_ChangeAnim(this, EN_NB_ANIM_TALK_LOOP);
                    break;

                default:
                    break;
            }
        }

        this->textId = currentTextId;
    } else if (this->stateFlags & EN_NB_FLAG_80) {
        this->unk_18C = NULL;
        this->textId = 0;
        this->stateFlags &= ~EN_NB_FLAG_80;
        DmNb_ChangeAnim(this, EN_NB_ANIM_1);
    }

    if (this->unk_18C != NULL) {
        this->unk_18C(this, play);
    }

    return 0;
}

s32 unkfunc_80BC0B98(DmNb* this, PlayState* play, ScheduleOutput* scheduleOutput) {
    s32 success = false;

    if (DmNb_FindActor(this, play, ACTORCAT_NPC, ACTOR_EN_AN) != NULL) {
        SubS_SetOfferMode(&this->stateFlags, SUBS_OFFER_MODE_ONSCREEN, SUBS_OFFER_MODE_MASK);
        this->stateFlags |= EN_NB_FLAG_20;
        DmNb_ChangeAnim(this, EN_NB_ANIM_0);
        success = true;
    }

    return success;
}

s32 unkfunc_80BC0C0C(DmNb* this, PlayState* play, ScheduleOutput* scheduleOutput) {
    if (!CHECK_EVENTINF(EVENTINF_43)) {
        SubS_SetOfferMode(&this->stateFlags, SUBS_OFFER_MODE_ONSCREEN, SUBS_OFFER_MODE_MASK);
    } else {
        SubS_SetOfferMode(&this->stateFlags, SUBS_OFFER_MODE_AUTO, SUBS_OFFER_MODE_MASK);
    }
    DmNb_ChangeAnim(this, EN_NB_ANIM_0);

    return true;
}

s32 DmNb_ProcessScheduleOutput(DmNb* this, PlayState* play, ScheduleOutput* scheduleOutput) {
    s32 success;

    this->actor.flags |= ACTOR_FLAG_TARGETABLE;
    this->actor.targetMode = TARGET_MODE_0;
    this->stateFlags = EN_NB_FLAG_NONE;
    this->unk_274 = 40.0f;

    switch (scheduleOutput->result) {
        case EN_NB_SCH_1:
        case EN_NB_SCH_3:
        case EN_NB_SCH_4:
            success = unkfunc_80BC0C0C(this, play, scheduleOutput);
            break;

        case EN_NB_SCH_2:
            success = unkfunc_80BC0B98(this, play, scheduleOutput);
            break;

        default:
            success = false;
            break;
    }
    return success;
}

// what? default function for schedule things?
s32 unkfunc_80BC0D08(DmNb* this, PlayState* play) {
    return 0;
}

void DmNb_HandleSchedule(DmNb* this, PlayState* play) {
    if ((this->scheduleResult == EN_NB_SCH_1) || (this->scheduleResult == EN_NB_SCH_2) ||
        (this->scheduleResult == EN_NB_SCH_3) || (this->scheduleResult == EN_NB_SCH_4)) {
        unkfunc_80BC0D08(this, play);
    }

    Math_ApproachS(&this->actor.shape.rot.y, this->actor.world.rot.y, 3, 0x2AA8);
}

// first action func
void DmNb_FollowSchedule(DmNb* this, PlayState* play) {
    ScheduleOutput scheduleOutput;

    this->timePathTimeSpeed = R_TIME_SPEED + ((void)0, gSaveContext.save.timeSpeedOffset);

    if (CHECK_EVENTINF(EVENTINF_43)) {
        scheduleOutput.result = EN_NB_SCH_1;
        DmNb_ProcessScheduleOutput(this, play, &scheduleOutput);
        this->actor.shape.shadowDraw = ActorShadow_DrawCircle;
        this->actor.flags |= ACTOR_FLAG_TARGETABLE;
    } else if (!Schedule_RunScript(play, sScheduleScript, &scheduleOutput) ||
               ((this->scheduleResult != scheduleOutput.result) &&
                !DmNb_ProcessScheduleOutput(this, play, &scheduleOutput))) {
        this->actor.shape.shadowDraw = NULL;
        this->actor.flags &= ~ACTOR_FLAG_TARGETABLE;
        scheduleOutput.result = EN_NB_SCH_NONE;
    } else {
        // these still need to happen, we just ignore output?
        //Schedule_RunScript(play, sScheduleScript, &scheduleOutput);
        //DmNb_ProcessScheduleOutput(this, play, &scheduleOutput);

        // that said, ignore this?
        //scheduleOutput.result = EN_NB_SCH_2;

        this->actor.shape.shadowDraw = ActorShadow_DrawCircle;
        this->actor.flags |= ACTOR_FLAG_TARGETABLE;
    }

    this->scheduleResult = scheduleOutput.result;
    this->unk_1E8 = unkfunc_80BBFF90(this, play);
    DmNb_HandleSchedule(this, play);
}

void unkfunc_80BC0EAC(DmNb* this, PlayState* play) {
    if (func_8010BF58(&this->actor, play, this->msgEventScript, this->msgEventCallback, &this->msgEventArg4)) {
        if (CHECK_EVENTINF(EVENTINF_43)) {
            CLEAR_EVENTINF(EVENTINF_42);
            CLEAR_EVENTINF(EVENTINF_43);
        }

        SubS_SetOfferMode(&this->stateFlags, SUBS_OFFER_MODE_ONSCREEN, SUBS_OFFER_MODE_MASK);
        if (this->scheduleResult != EN_NB_SCH_2) {
            this->stateFlags &= ~EN_NB_FLAG_20;
        }

        this->actor.child = NULL;
        this->stateFlags |= EN_NB_FLAG_400;
        this->unk_282 = 20;
        this->msgEventArg4 = 0;
        this->actionFunc = DmNb_FollowSchedule;
    }
}

void DmNb_Init(Actor* thisx, PlayState* play) {
    DmNb* this = THIS;

    ActorShape_Init(&this->actor.shape, 0.0f, NULL, 0.0f);
    SkelAnime_InitFlex(play, &this->skelAnime, &gNbSkel, NULL, this->jointTable, this->morphTable, NB_LIMB_MAX);

    this->animIndex = EN_NB_ANIM_INVALID;
    DmNb_ChangeAnim(this, EN_NB_ANIM_0);

    Collider_InitAndSetCylinder(play, &this->collider, &this->actor, &sCylinderInit);
    CollisionCheck_SetInfo2(&this->actor.colChkInfo, DamageTable_Get(0x16), &sColChkInfoInit);
    Actor_SetScale(&this->actor, 0.01f);
    this->stateFlags = EN_NB_FLAG_NONE;

    if (CHECK_EVENTINF(EVENTINF_43)) {
        SubS_SetOfferMode(&this->stateFlags, SUBS_OFFER_MODE_AUTO, SUBS_OFFER_MODE_MASK);
    } else {
        CLEAR_EVENTINF(EVENTINF_42);
        CLEAR_EVENTINF(EVENTINF_43);
    }

    this->actionFunc = DmNb_FollowSchedule;
    this->actionFunc(this, play);
}

void DmNb_Destroy(Actor* thisx, PlayState* play) {
    DmNb* this = THIS;

    Collider_DestroyCylinder(play, &this->collider);
    play->interfaceCtx.storyState = STORY_STATE_DESTROY;
}

void DmNb_Update(Actor* thisx, PlayState* play) {
    DmNb* this = THIS;

    unkfunc_80BC04FC(this, play);
    this->actionFunc(this, play);
    unkfunc_80BC0A18(this, play); // handle player dialogue

    if (this->scheduleResult != EN_NB_SCH_NONE) {
        DmNb_UpdateSkelAnime(this);
        unkfunc_80BC0800(this);
        if (Actor_IsFacingPlayer(&this->actor, 0x38E0)) {
            SubS_Offer(&this->actor, play, this->unk_274, 30.0f, PLAYER_IA_NONE,
                       this->stateFlags & SUBS_OFFER_MODE_MASK);
        }
        unkfunc_80BBFF24(this, play);
    }
}

s32 DmNb_OverrideLimbDraw(PlayState* play, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, Actor* thisx) {
    DmNb* this = THIS;

    if (limbIndex == NB_LIMB_HEAD) {
        unkfunc_80BC05A8(this, play);
    }

    return false;
}

void DmNb_PostLimbDraw(PlayState* play, s32 limbIndex, Gfx** dList, Vec3s* rot, Actor* thisx) {
    DmNb* this = THIS;
    Vec3f focusTarget;

    if ((CutsceneManager_GetCurrentCsId() == CS_ID_NONE) && (limbIndex == NB_LIMB_HEAD)) {
        Matrix_MultVec3f(&gZeroVec3f, &focusTarget);
        Math_ApproachF(&thisx->focus.pos.x, focusTarget.x, 0.6f, 10000.0f);
        Math_ApproachF(&thisx->focus.pos.y, focusTarget.y, 0.6f, 10000.0f);
        Math_ApproachF(&thisx->focus.pos.z, focusTarget.z, 0.6f, 10000.0f);
        Math_Vec3s_Copy(&thisx->focus.rot, &thisx->world.rot);
    }
}

void DmNb_TransformLimbDraw(PlayState* play, s32 limbIndex, Actor* thisx) {
    DmNb* this = THIS;
    s32 stepRot;
    s32 overrideRot;

    if (!(this->stateFlags & EN_NB_FLAG_400)) {
        overrideRot = false;
        if (this->stateFlags & EN_NB_FLAG_100) {
            overrideRot = true;
            stepRot = true;
        } else {
            stepRot = true;
        }
    } else {
        overrideRot = false;
        stepRot = false;
    }

    if (limbIndex == NB_LIMB_HEAD) {
        SubS_UpdateLimb(this->headRotZ + 0x4000, this->headRotY + this->actor.shape.rot.y + 0x4000,
                        &this->headComputedPos, &this->headComputedRot, stepRot, overrideRot);
        Matrix_Pop();
        Matrix_Translate(this->headComputedPos.x, this->headComputedPos.y, this->headComputedPos.z, MTXMODE_NEW);
        Matrix_Scale(this->actor.scale.x, this->actor.scale.y, this->actor.scale.z, MTXMODE_APPLY);
        Matrix_RotateYS(this->headComputedRot.y, MTXMODE_APPLY);
        Matrix_RotateXS(this->headComputedRot.x, MTXMODE_APPLY);
        Matrix_RotateZS(this->headComputedRot.z, MTXMODE_APPLY);
        Matrix_Push();
    }
}

void DmNb_Draw(Actor* thisx, PlayState* play) {
    DmNb* this = THIS;

    if (this->scheduleResult != EN_NB_SCH_NONE) {
        Gfx_SetupDL37_Opa(play->state.gfxCtx);
        SkelAnime_DrawTransformFlexOpa(play, this->skelAnime.skeleton, this->skelAnime.jointTable,
                                       this->skelAnime.dListCount, DmNb_OverrideLimbDraw, DmNb_PostLimbDraw,
                                       DmNb_TransformLimbDraw, &this->actor);
    }
}
