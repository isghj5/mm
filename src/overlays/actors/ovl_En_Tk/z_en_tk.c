/*
 * File: z_en_tk.c
 * Overlay: ovl_En_Tk
 * Description: Dampé
 */

#include "z_en_tk.h"
#include "overlays/actors/ovl_Bg_Danpei_Movebg/z_bg_danpei_movebg.h"
#include "overlays/actors/ovl_En_Door/z_en_door.h"

#define FLAGS (ACTOR_FLAG_1 | ACTOR_FLAG_8)

#define THIS ((EnTk*)thisx)

void EnTk_Init(Actor* thisx, PlayState* play);
void EnTk_Destroy(Actor* thisx, PlayState* play);
void EnTk_UpdateDigGame(Actor* thisx, PlayState* play);
void EnTk_Draw(Actor* thisx, PlayState* play);

void EnTk_SetupHidingUnderBed(EnTk* this, PlayState* play);
void EnTk_HidingUnderBed(EnTk* this, PlayState* play);
void EnTk_SetupWalkingOutside(EnTk* this, PlayState* play);
void EnTk_WalkingOutside(EnTk* this, PlayState* play);
void func_80AECE0C(EnTk* this, PlayState* play);
s32 func_80AECE60(EnTk* this, PlayState* play);
s32 func_80AED354(EnTk* this, PlayState* play, ScheduleOutput* scheduleOutput);
s32 func_80AED38C(EnTk* this, PlayState* play, ScheduleOutput* scheduleOutput);
void EnTk_SetupStopToTalkOutside(EnTk* this, PlayState* play);
void EnTk_TalkOutSide(EnTk* this, PlayState* play);
void EnTk_SetupDigGameIdle(EnTk* this, PlayState* play);
void EnTk_DigGameIdle(EnTk* this, PlayState* play);
void EnTk_RunFromBigpo(EnTk* this, PlayState* play);
void EnTk_SetupRunFromBigpoKill(EnTk* this, PlayState* play);
void EnTk_RunFromBigpoKill(EnTk* this, PlayState* play);
void EnTk_ChooseNextDialogue(EnTk* this, PlayState* play);
void EnTk_TalkDigGame(EnTk* this, PlayState* play);
void EnTk_SetupWaitForDigCutscene(EnTk* this, PlayState* play);
void EnTk_WaitForDigCutscene(EnTk* this, PlayState* play);
void EnTk_CheckForDampeDigSpot(EnTk* this, PlayState* play);
void EnTk_TurnTowardDigSpot(EnTk* this, PlayState* play);
void EnTk_SetupDigging(EnTk* this, PlayState* play);
void EnTk_Digging(EnTk* this, PlayState* play);
void func_80AEE650(EnTk* this, PlayState* play);
void func_80AEE6B8(EnTk* this, PlayState* play);
void EnTk_SetupDigGameWalking(EnTk* this, PlayState* play);
void EnTk_DigGameWalking(EnTk* this, PlayState* play);
void EnTk_CheckDigGameMovingState(EnTk* this, PlayState* play);
void EnTk_SetFollowFuncLost(EnTk* this, PlayState* play);
void EnTk_FollowFuncLost(EnTk* this, PlayState* play);
void EnTk_SetFollowFuncFollowing(EnTk* this, PlayState* play);
void EnTk_FollowFuncFollowing(EnTk* this, PlayState* play);
void EnTk_SetFollowFuncRidingElevator(EnTk* this, PlayState* play);
void EnTk_FollowFuncRidingElevator(EnTk* this, PlayState* play);
void EnTk_SetFollowFuncUnused(EnTk* this, PlayState* play);
void EnTk_FollowFuncUnused(EnTk* this, PlayState* play);
void EnTk_SetFollowFuncStanding(EnTk* this, PlayState* play);
void EnTk_WalkingFuncStanding(EnTk* this, PlayState* play);
void EnTk_UpdateDoNothing(Actor* thisx, PlayState* play);
void EnTk_UpdateOutside(Actor* thisx, PlayState* play);
void EnTk_UpdateHidingUnderBed(Actor* thisx, PlayState* play);

static s32 sIsSpawned;

static u8 D_80AEF800[] = {
    /* 0x0 */ SCHEDULE_CMD_CHECK_TIME_RANGE_L(6, 0, 18, 0, 0x8 - 0x7),
    /* 0x7 */ SCHEDULE_CMD_RET_NONE(),
    /* 0x8 */ SCHEDULE_CMD_RET_TIME(6, 0, 18, 0, 1),
    /* 0xE */ SCHEDULE_CMD_RET_NONE(),
};

ActorInit En_Tk_InitVars = {
    ACTOR_EN_TK,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_TK,
    sizeof(EnTk),
    (ActorFunc)EnTk_Init,
    (ActorFunc)EnTk_Destroy,
    (ActorFunc)EnTk_UpdateDigGame,
    (ActorFunc)EnTk_Draw,
};

static ColliderCylinderInit sCylinderInit = {
    {
        COLTYPE_NONE,
        AT_NONE,
        AC_NONE,
        OC1_ON | OC1_TYPE_ALL,
        OC2_TYPE_2,
        COLSHAPE_CYLINDER,
    },
    {
        ELEMTYPE_UNK0,
        { 0x00000000, 0x00, 0x00 },
        { 0x00000000, 0x00, 0x00 },
        TOUCH_NONE | TOUCH_SFX_NORMAL,
        BUMP_NONE,
        OCELEM_ON,
    },
    { 30, 52, 0, { 0, 0, 0 } },
};

// part of the collider??
static u32 D_80AEF85C[] = {
    0x00000000,
    0x00000000,
    0xFF000000,
};

typedef enum {
    /*  0 */ DAMPE_ANIM_WALK,
    /*  1 */ DAMPE_ANIM_WALK2,
    /*  2 */ DAMPE_ANIM_REST,
    /*  3 */ DAMPE_ANIM_DIG,
    /*  4 */ DAMPE_ANIM_STARTLE,
    /*  5 */ DAMPE_ANIM_RUN,
    /*  6 */ DAMPE_ANIM_UNK, // unused it would seem
    /*  7 */ DAMPE_ANIM_STARTLE_LOOP,
    /* -1 */ DAMPE_ANIM_START = -1, // set by init
} DampeAnims;

static AnimationSpeedInfo sAnimations[] = {
    { &gDampeWalkAnim, 1.0f, ANIMMODE_LOOP, -10.0f },
    { &gDampeWalkAnim, 2.0f, ANIMMODE_LOOP, -10.0f },
    { &gDampeRestAnim, 1.0f, ANIMMODE_LOOP, -10.0f },
    { &gDampeDigAnim, 1.0f, ANIMMODE_ONCE, -10.0f },
    { &gDampeStartleAnim, 1.0f, ANIMMODE_ONCE, -10.0f },
    { &gDampeRunAnim, 1.0f, ANIMMODE_LOOP, -10.0f },
    { &gDampeUnk20C8Anim, 1.0f, ANIMMODE_LOOP, -10.0f },
    { &gDampeStartleLoopAnim, 1.0f, ANIMMODE_LOOP, -10.0f },
};

static s32 D_80AEF8E8[2] = { 0, 0 };

static f32 D_80AEF8F0[] = {
    0.637399971485f, 0.637399971485f, 0.637399971485f, 0.637399971485f, 0.637399971485f, 0.637399971485f,
    0.637399971485f, 0.637399971485f, 0.637399971485f, 0.637399971485f, 0.637399971485f, 0.637399971485f,
    1.88639998436f,  3.44770002365f,  5.29629993439f,  7.39470005035f,  9.60550022125f,  11.9537000656f,
    14.30189991f,    16.6000995636f,  18.8108997345f,  20.8342990875f,  22.6203994751f,  24.1441993713f,
    25.3057994843f,  25.3057994843f,  25.3057994843f,  25.3057994843f,  25.3057994843f,  25.3057994843f,
    25.3057994843f,  25.3057994843f,  25.3057994843f,  25.3057994843f,  25.3057994843f,  25.3057994843f,
    25.3057994843f,  26.5048999786f,  28.0412006378f,  29.9146995544f,  31.9881000519f,  34.2238998413f,
    36.572101593f,   38.932800293f,   41.28099823f,    43.5416984558f,  45.6276016235f,  47.4511985779f,
    49.0f,
};

typedef struct {
    /* 0x00 */ Actor* searchResult;
    /* 0x04 */ f32 distance;
} EnTkStruct; // size = 0x8?


void EnTk_Blink(EnTk* this) {
    if (DECR(this->blinkTimer) == 0) {
        this->eyeState++;
        if (this->eyeState >= 3) {
            this->unk_2C0--;
            if (this->unk_2C0 < 0) {
                this->blinkTimer = Rand_S16Offset(30, 30);
                this->unk_2C0 = 2;
                if (Rand_ZeroOne() > 0.5f) {
                    this->unk_2C0++;
                }
            }
            this->eyeState = 0;
        }
    }
}

// the hell is this
f32 func_80AEC524(f32 arg0) {
    f32 temp_f0;
    f32 ret;
    s32 temp_a0;
    s32 temp_a1;

    while ((arg0 >= ARRAY_COUNT(D_80AEF8F0)) || (arg0 < 0.0f)) {
        if (arg0 >= ARRAY_COUNT(D_80AEF8F0)) {
            arg0 -= ARRAY_COUNT(D_80AEF8F0);
        } else if (arg0 < 0.0f) {
            arg0 += ARRAY_COUNT(D_80AEF8F0);
        }
    }

    // temp_f0 always becomes 0
    temp_a1 = arg0;
    temp_a0 = temp_a1 + 1;
    temp_f0 = arg0 - temp_a1;

    if (arg0 != temp_a1) {
        if (temp_a0 >= ARRAY_COUNT(D_80AEF8F0)) {
            temp_a0 -= ARRAY_COUNT(D_80AEF8F0);
            ret = (((D_80AEF8F0[temp_a0] + D_80AEF8F0[ARRAY_COUNT(D_80AEF8F0) - 1]) - D_80AEF8F0[temp_a1]) * temp_f0) +
                  D_80AEF8F0[temp_a1];
        } else {
            ret = ((D_80AEF8F0[temp_a0] - D_80AEF8F0[temp_a1]) * temp_f0) + D_80AEF8F0[temp_a1];
        }
    } else {
        ret = D_80AEF8F0[temp_a1];
    }
    return ret;
}

void func_80AEC658(SkelAnime* skelAnime, f32 arg1, f32 arg2, f32* arg3, f32* arg4) {
    static f32 D_80AEF9B4[] = { 0.95f, 0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,
                                0.0f,  0.0f,  1.0f,  1.25f, 1.48f, 1.68f, 1.77f, 1.88f, 1.88f, 1.84f,
                                1.77f, 1.62f, 1.43f, 1.22f, 0.93f, 0.0f,  0.0f,  0.0f,  0.0f,  0.0f,
                                0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.96f, 1.23f, 1.5f,
                                1.66f, 1.79f, 1.88f, 1.89f, 1.88f, 1.81f, 1.67f, 1.46f, 1.24f };

    *arg3 = D_80AEF9B4[(s32)skelAnime->curFrame] * 0.5f * skelAnime->playSpeed * arg2;
    *arg4 = (func_80AEC524(skelAnime->curFrame) - func_80AEC524(arg1)) * arg2;

    while (*arg4 < 0.0f) {
        *arg4 += D_80AEF8F0[(s32)skelAnime->animLength - 1] * arg2;
    }
}

void EnTk_Init(Actor* thisx, PlayState* play) {
    s32 pad;
    EnTk* this = THIS;

    this->type = DAMPE_GET_TYPE(&this->actor);
    this->switchFlag = DAMPE_GET_SWITCH_FLAGS(&this->actor);
    Collider_InitCylinder(play, &this->collider);

    if (Flags_GetSwitch(play, this->switchFlag)) {
        if (this->type == DAMPE_TYPE_DIG_GAME_NPC) {
            Actor_Kill(&this->actor);
            return;
        }
    } else if (this->type == DAMPE_TYPE_HIDING) {
        Actor_Kill(&this->actor);
        return;
    }

    if ((this->type == DAMPE_TYPE_RUNNING) || (this->type == DAMPE_TYPE_DIG_GAME_SPOT)) {
        this->actor.flags &= ~(ACTOR_FLAG_1 | ACTOR_FLAG_8);
        this->actor.update = EnTk_UpdateDoNothing;
        this->actor.draw = NULL;
        return;
    }

    ActorShape_Init(&this->actor.shape, 0.0f, ActorShadow_DrawCircle, 24.0f);
    SkelAnime_InitFlex(play, &this->skelAnime, &gDampeSkel, NULL, this->jointTable, this->morphTable, DAMPE_LIMB_MAX);
    Animation_Change(&this->skelAnime, &gDampeRestAnim, 1.0f, 0.0f,
                     Animation_GetLastFrame(&gDampeRestAnim.common), ANIMMODE_LOOP, 0.0f);

    this->unk_318 = 0;
    this->animIndex = DAMPE_ANIM_START;
    Actor_SetScale(&this->actor, 0.01f);
    this->actor.targetMode = 1;
    this->actor.colChkInfo.mass = MASS_IMMOVABLE;

    if (this->type == DAMPE_TYPE_HIDING) {
        this->unk_316 = 0;
        this->actor.update = EnTk_UpdateHidingUnderBed;
        EnTk_SetupHidingUnderBed(this, play);
        return;
    }

    Collider_SetCylinder(play, &this->collider, &this->actor, &sCylinderInit);
    this->actor.world.rot.y = this->actor.yawTowardsPlayer;
    this->actor.gravity = -1.0f;
    this->actor.shape.rot.y = this->actor.world.rot.y;
    this->actor.flags |= ACTOR_FLAG_10;
    SubS_ChangeAnimationBySpeedInfo(&this->skelAnime, sAnimations, DAMPE_ANIM_WALK, &this->animIndex);
    SubS_FillCutscenesList(&this->actor, this->cutscenes, ARRAY_COUNT(this->cutscenes));

    switch (this->type) {
        case DAMPE_TYPE_OUTSIDE_NPC:
            // Ikana Graveyard has two rooms, need to check if the other room spawned one already.
            if (sIsSpawned) {
                Actor_Kill(&this->actor);
                return;
            }
            sIsSpawned = true;
            this->actor.room = -1; // Do not despawn on room change.
            this->actor.update = EnTk_UpdateOutside;
            this->unk_2D8 = 0.0f;
            EnTk_SetupWalkingOutside(this, play);
            EnTk_UpdateOutside(&this->actor, play);
            break;

        case DAMPE_TYPE_DIG_GAME_NPC:
            this->digGameMovingState = DAMPE_DIG_GAME_MOVING_STATE_PRE;
            this->digGameState = DAMPE_DIG_GAME_STATE_IDLE;
            this->bigpoFlameFoundCount = 0;
            EnTk_SetupDigGameIdle(this, play);
            break;

        default:
            Actor_Kill(&this->actor);
            return;
    }
}

void EnTk_Destroy(Actor* thisx, PlayState* play) {
    EnTk* this = THIS;

    Collider_DestroyCylinder(play, &this->collider);
}

void EnTk_SetupHidingUnderBed(EnTk* this, PlayState* play) {
    this->unk_316 = 0;
    SubS_ChangeAnimationBySpeedInfo(&this->skelAnime, sAnimations, DAMPE_ANIM_REST, &this->animIndex);
    this->actionFunc = EnTk_HidingUnderBed;
}

void EnTk_HidingUnderBed(EnTk* this, PlayState* play) {
    if (Actor_ProcessTalkRequest(&this->actor, &play->state)) {
        play->msgCtx.msgMode = 0;
        play->msgCtx.msgLength = 0;
        EnTk_ChooseNextDialogue(this, play);
    } else if (this->actor.xzDistToPlayer < 100.0f) {
        func_800B8614(&this->actor, play, 100.0f);
    }
}

void EnTk_SetupWalkingOutside(EnTk* this, PlayState* play) {
    this->actor.speedXZ = 0.0f;
    this->scheduleResult = -1;
    this->unk_2DC = 0.0f; // related to speed?
    SubS_ChangeAnimationBySpeedInfo(&this->skelAnime, sAnimations, DAMPE_ANIM_WALK, &this->animIndex);
    this->actionFunc = EnTk_WalkingOutside;
}

void EnTk_WalkingOutside(EnTk* this, PlayState* play) {
    f32 temp_f0;
    s32 temp2;
    s32 temp3;
    f32 sp48;
    f32 sp44;
    ScheduleOutput scheduleOutput;
    u8 schResult;

    this->actor.textId = 0;
    if (Actor_ProcessTalkRequest(&this->actor, &play->state)) {
        play->msgCtx.msgMode = 0;
        play->msgCtx.msgLength = 0;
        EnTk_SetupStopToTalkOutside(this, play);
        return;
    }

    if (R_TIME_SPEED != 0.0f) {
        this->skelAnime.playSpeed = (f32)func_800FE620(play) / R_TIME_SPEED;
    } else {
        this->skelAnime.playSpeed = 0.0f;
    }

    if (this->tkFlags2 & TKFLAGS2_UNK_10) {
        SubS_ChangeAnimationBySpeedInfo(&this->skelAnime, sAnimations, DAMPE_ANIM_RUN, &this->animIndex);
        sp48 = 1.0f;
        sp44 = 22.0f;
    } else {
        func_80AEC658(&this->skelAnime, this->curAnimFrame, 1.0f, &sp48, &sp44);
    }

    temp2 = R_TIME_SPEED * sp44;
    temp_f0 = temp2;

    this->unk_2DC += (R_TIME_SPEED * sp44) - temp2;
    temp3 = this->unk_2DC;
    this->timePathTimeSpeed = temp2 + temp3;
    this->unk_2DC -= temp3;
    this->unk_2E0 += R_TIME_SPEED;

    if (Schedule_RunScript(play, D_80AEF800, &scheduleOutput)) {
        if ((this->scheduleResult != scheduleOutput.result) && !func_80AED354(this, play, &scheduleOutput)) {
            return;
        }
        schResult = scheduleOutput.result;
    } else {
        scheduleOutput.result = 0;
        schResult = scheduleOutput.result;
    }

    if (!schResult && (this->scheduleResult != 0)) {
        this->actor.draw = NULL;
        this->actor.flags &= ~ACTOR_FLAG_1;
    } else if (schResult && (this->scheduleResult == 0)) {
        this->actor.flags |= ACTOR_FLAG_1;
        this->actor.draw = EnTk_Draw;
    }

    this->scheduleResult = scheduleOutput.result;
    func_80AECE0C(this, play);

    if (this->tkFlags & 8) {
        this->actor.flags &= ~ACTOR_FLAG_1;
        this->actor.draw = NULL;
    }
}

void func_80AECE0C(EnTk* this, PlayState* play) {
    if (this->scheduleResult != 0) {
        if (1) {}
        func_80AECE60(this, play);
    }
    Math_SmoothStepToS(&this->actor.shape.rot.y, this->actor.world.rot.y, 4, 0x1555, 0xB6);
}

s32 func_80AECE60(EnTk* this, PlayState* play) {
    EnDoor* door;
    f32 knots[265];
    Vec3f sp94;
    Vec3f sp88;
    Vec3f timePathTargetPos;
    s32 sp78;
    s32 sp74;
    s32 pad;

    SubS_TimePathing_FillKnots(knots, SUBS_TIME_PATHING_ORDER, this->timePath->count + SUBS_TIME_PATHING_ORDER);
    // if timepath, else regular path?
    if (!(this->tkFlags & 4)) {
        timePathTargetPos = gZeroVec3f;
        SubS_TimePathing_Update(this->timePath, &this->timePathProgress, &this->timePathElapsedTime,
                                this->timePathWaypointTime, this->timePathTotalTime, &this->timePathWaypoint, knots,
                                &timePathTargetPos, this->timePathTimeSpeed);
        SubS_TimePathing_ComputeInitialY(play, this->timePath, this->timePathWaypoint, &timePathTargetPos);
        this->actor.world.pos.y = timePathTargetPos.y;
    } else {
        timePathTargetPos = this->timePathTargetPos;
    }

    this->actor.world.pos.x = timePathTargetPos.x;
    this->actor.world.pos.z = timePathTargetPos.z;

    if (!(this->tkFlags & 4)) {
        Math_Vec3f_Copy(&this->actor.prevPos, &this->actor.world.pos);
        this->tkFlags |= 4;
    }

    if ((play->transitionMode != TRANS_MODE_OFF) || (this->timePathTimeSpeed == 0)) {
        sp78 = this->timePathElapsedTime;
        sp74 = this->timePathWaypoint;
        timePathTargetPos = this->actor.world.pos;
    }

    this->timePathTargetPos = gZeroVec3f;

    if (SubS_TimePathing_Update(this->timePath, &this->timePathProgress, &this->timePathElapsedTime,
                                this->timePathWaypointTime, this->timePathTotalTime, &this->timePathWaypoint, knots,
                                &this->timePathTargetPos, this->timePathTimeSpeed)) {
        this->tkFlags |= 8;
    } else {
        sp94 = this->actor.world.pos;
        sp88 = this->timePathTargetPos;
        this->actor.world.rot.y = Math_Vec3f_Yaw(&sp94, &sp88);
    }

    if ((play->transitionMode != TRANS_MODE_OFF) || (this->timePathTimeSpeed == 0)) {
        this->timePathElapsedTime = sp78;
        this->timePathWaypoint = sp74;
        this->timePathTargetPos = timePathTargetPos;
    }

    door = NULL;
    if (!(this->tkFlags2 & (TKFLAGS2_UNK_400 | TKFLAGS2_UNK_800))) {
        Actor* doorIter = NULL;

        do {
            doorIter = SubS_FindActor(play, doorIter, ACTORCAT_DOOR, ACTOR_EN_DOOR);
            if (doorIter != NULL) {
                if (Actor_XZDistanceBetweenActors(&this->actor, doorIter) <= 120.0f) {
                    if (ABS(BINANG_SUB(Actor_YawToPoint(&this->actor, &doorIter->world.pos),
                                       this->actor.shape.rot.y)) <= 0x2000) {
                        this->tkFlags2 |= TKFLAGS2_UNK_400;
                        door = (EnDoor*)doorIter;
                        break;
                    }
                }
                doorIter = doorIter->next;
            }
        } while (doorIter != NULL);
    } else {
        Actor* doorIter = NULL;

        do {
            doorIter = SubS_FindActor(play, doorIter, ACTORCAT_DOOR, ACTOR_EN_DOOR);
            if (doorIter != NULL) {
                if (Actor_XZDistanceBetweenActors(&this->actor, doorIter) <= 160.0f) {
                    door = (EnDoor*)doorIter;
                    break;
                }
                doorIter = doorIter->next;
            }
        } while (doorIter != NULL);
    }

    if ((door != NULL) && (this->tkFlags2 & TKFLAGS2_UNK_400)) {
        Vec3f sp5C;

        Actor_OffsetOfPointInActorCoords(&this->actor, &sp5C, &door->dyna.actor.world.pos);
        door->unk_1A7 = 2;
        if (sp5C.z < -20.0f) {
            this->tkFlags2 &= ~0x400;
            this->tkFlags2 |= 0x800;
        }
    }

    if (door != NULL) {
        if ((this->tkFlags2 & 0x800) && (door->unk_1A7 == 0)) {
            this->tkFlags2 &= ~0x800;
        }
    }

    if (!(this->tkFlags & 8) && !(this->tkFlags2 & 0x10) && (this->actor.xzDistToPlayer < 100.0f)) {
        func_8013E8F8(&this->actor, play, 100.0f, 100.0f, PLAYER_IA_NONE, 0x4000, 0x4000);
    }

    return false;
}

s32 func_80AED354(EnTk* this, PlayState* play, ScheduleOutput* scheduleOutput) {
    s32 result = false;

    if (scheduleOutput->result != 0) {
        result = func_80AED38C(this, play, scheduleOutput);
    }
    return result;
}

s32 func_80AED38C(EnTk* this, PlayState* play, ScheduleOutput* scheduleOutput) {
    u16 now = SCHEDULE_TIME_NOW;
    u8 pathIndex = DAMPE_GET_PATH_INDEX(&this->actor);
    u16 phi_a1;
    s32 index = scheduleOutput->result - 1;
    u16 tmp;

    this->timePath = SubS_GetAdditionalPath(play, pathIndex, D_80AEF8E8[index + 1]);
    if (this->timePath == NULL) {
        return false;
    }

    if ((this->scheduleResult <= 0) && (this->scheduleResult != 0) && (this->timePathTimeSpeed >= 0)) {
        phi_a1 = now;
    } else {
        phi_a1 = scheduleOutput->time0;
    }

    this->timePathTotalTime = scheduleOutput->time1 - phi_a1;
    this->timePathElapsedTime = now - phi_a1;
    tmp = phi_a1 = this->timePath->count - (SUBS_TIME_PATHING_ORDER - 1);
    this->timePathWaypointTime = this->timePathTotalTime / tmp;
    this->timePathWaypoint = (this->timePathElapsedTime / this->timePathWaypointTime) + (SUBS_TIME_PATHING_ORDER - 1);
    this->tkFlags &= ~4;
    this->tkFlags &= ~8;
    return true;
}

void EnTk_SetupStopToTalkOutside(EnTk* this, PlayState* play) {
    SubS_ChangeAnimationBySpeedInfo(&this->skelAnime, sAnimations, DAMPE_ANIM_REST, &this->animIndex);
    this->actionFunc = EnTk_TalkOutSide;
}

void EnTk_ChooseNextOutsideDialogue(EnTk* this, PlayState* play) {
    if (!CHECK_WEEKEVENTREG(WEEKEVENTREG_31_10)) {
        // I am Dampe! My face is frightening but I am not a bad person.
        Message_StartTextbox(play, 0x13FE, &this->actor);
        SET_WEEKEVENTREG(WEEKEVENTREG_31_10);
    } else if (gSaveContext.save.time < CLOCK_TIME(9, 0)) {
        // All the graves belong to royals, ghosts come out.
        Message_StartTextbox(play, 0x13FF, &this->actor);
    } else if (gSaveContext.save.time < CLOCK_TIME(12, 0)) {
        // (remarking on the captain keeta skeleton lore)
        Message_StartTextbox(play, 0x1400, &this->actor);
    } else if (gSaveContext.save.time < CLOCK_TIME(15, 0)) {
        // Do you want to see dancing bones? Just wait here... I don't want to see it.
        Message_StartTextbox(play, 0x1401, &this->actor);
    } else {
        // Don't bother me! Soon ghosts will apear, go home!
        Message_StartTextbox(play, 0x1402, &this->actor);
    }
}

void EnTk_TalkOutSide(EnTk* this, PlayState* play) {
    if ((this->animIndex == DAMPE_ANIM_STARTLE) && Animation_OnFrame(&this->skelAnime, this->skelAnime.endFrame)) {
        SubS_ChangeAnimationBySpeedInfo(&this->skelAnime, sAnimations, DAMPE_ANIM_STARTLE_LOOP, &this->animIndex);
    }

    switch (Message_GetState(&play->msgCtx)) {
        case TEXT_STATE_NONE:
            if (Math_ScaledStepToS(&this->actor.shape.rot.y, this->actor.yawTowardsPlayer - 0x1555, 0x71C)) {
                if (Player_GetMask(play) == PLAYER_MASK_CAPTAIN) {
                    SubS_ChangeAnimationBySpeedInfo(&this->skelAnime, sAnimations, DAMPE_ANIM_STARTLE, &this->animIndex);
                    // (Screamin) They're out! Why are they out when its not night!
                    Message_StartTextbox(play, 0x13FD, &this->actor);
                } else if (CURRENT_DAY != 2) {
                    EnTk_ChooseNextOutsideDialogue(this, play);
                } else if (!Flags_GetSwitch(play, DAMPE_GET_SWITCH_FLAGS(&this->actor))) {
                    // There are a lot of bats, I don't like bats.
                    Message_StartTextbox(play, 0x1403, &this->actor);
                } else if (CHECK_WEEKEVENTREG(WEEKEVENTREG_DAMPE_REMOVED_BATS)) {
                    EnTk_ChooseNextOutsideDialogue(this, play);
                } else {
                    // Was it you who chased those bats away? Here have 30 rupees for your trouble.
                    Message_StartTextbox(play, 0x1413, &this->actor);
                }
                break;
            }

        case TEXT_STATE_1:
        case TEXT_STATE_CLOSING:
        case TEXT_STATE_3:
            break;

        case TEXT_STATE_CHOICE:
        case TEXT_STATE_5:
        case TEXT_STATE_DONE:
            if (Message_ShouldAdvance(play)) {
                switch (play->msgCtx.currentTextId) {
                    case 0x13FD: // (Screamin) They're out! Why are they out when its not night!
                        this->tkFlags2 |= 0x10;
                        SubS_ChangeAnimationBySpeedInfo(&this->skelAnime, sAnimations, DAMPE_ANIM_WALK, &this->animIndex);
                        this->skelAnime.playSpeed = 10.0f;
                        this->actionFunc = EnTk_WalkingOutside;
                        break;

                    case 0x13FE: // I am Dampe! My face is frightening but I am not a bad person.
                        func_80151938(play, 0x13FF); // All the graves here belong to royal family.
                        break;

                    case 0x1413: // Was it you who chased those bats away? Here have 30 rupees for your trouble.
                        Rupees_ChangeBy(30);
                        SET_WEEKEVENTREG(WEEKEVENTREG_DAMPE_REMOVED_BATS);
                        func_80151938(play, 0x13FF); // All the graves here belong to royal family.
                        break;

                    // TODO are all of these necessary?
                    case 0x13FF:
                    case 0x1400:
                    case 0x1401:
                    case 0x1402:
                    case 0x1403:
                    case 0x1404: // (Screaming) They're out! Go away!
                    case 0x1405: // Who are you? Not a ghost are you?
                    case 0x1406:
                    case 0x1407:
                    case 0x1408:
                    case 0x1409:
                    case 0x140A:
                    case 0x140B: // Where did you go? ... I need to follow your light.
                    case 0x140C:
                    case 0x140D: // Something here, want me to dig? y/n
                    case 0x140E:
                    case 0x140F: // Nothing here, show me another spot.
                    case 0x1410: // (dug up bigpo flame) Something strange is here.. Show me anothe spot
                    case 0x1411:
                    case 0x1412:
                    default:
                        SubS_ChangeAnimationBySpeedInfo(&this->skelAnime, sAnimations, DAMPE_ANIM_WALK, &this->animIndex);
                        this->actionFunc = EnTk_WalkingOutside;
                        break;
                }
            }
            break;
    }
}

// standing around waiting for player
void EnTk_SetupDigGameIdle(EnTk* this, PlayState* play) {
    this->unk_316 = 0;
    this->actor.speedXZ = 0.0f;
    if (this->tkFlags2 & 0x1000) {
        if ((this->animIndex == DAMPE_ANIM_STARTLE) && Animation_OnFrame(&this->skelAnime, this->skelAnime.endFrame)) {
            SubS_ChangeAnimationBySpeedInfo(&this->skelAnime, sAnimations, DAMPE_ANIM_STARTLE_LOOP, &this->animIndex);
        }
    } else {
        SubS_ChangeAnimationBySpeedInfo(&this->skelAnime, sAnimations, DAMPE_ANIM_REST, &this->animIndex);
    }
    this->actionFunc = EnTk_DigGameIdle;
}

// dig game idle
// before we talk to dampe, tkflags2 0x40 is set, tkflags is unset, state is zero
// state 1 is following player
// tkflags was 0xc0 for a second when it collided with soil
// state 2 is talking about digging
// tkflags2 62 is while digging
// tkflags2 is 4040 when lost state is still 1
// tkflags2 is 4040 when talking too, maybe 4000 is the lost dialogue has played
// tkflags2 is 4060 when the flame spawns, does not change if not flame
void EnTk_DigGameIdle(EnTk* this, PlayState* play) {
    Player* player = GET_PLAYER(play);
    Actor* dampeSearchIter;

    if ((this->animIndex != DAMPE_ANIM_STARTLE) && (this->animIndex != DAMPE_ANIM_STARTLE_LOOP)) {
        Vec3f focusTarget;
        s16 temp_v0 = (this->actor.shape.rot.y - this->actor.yawTowardsPlayer) + 0x1555;

        if (ABS(temp_v0) < 0x1800) {
            Math_SmoothStepToS(&this->skullRotY, temp_v0, 3, 0x71C, 0);
        } else {
            Math_SmoothStepToS(&this->skullRotY, 0, 3, 0x71C, 0);
        }

        Math_Vec3f_Copy(&focusTarget, &player->actor.world.pos);
        focusTarget.y = player->bodyPartsPos[PLAYER_BODYPART_HEAD].y + 3.0f;
        temp_v0 = Math_Vec3f_Pitch(&this->actor.focus.pos, &focusTarget);
        if (ABS(temp_v0) < 0x800) {
            Math_SmoothStepToS(&this->skullRotZ, temp_v0, 3, 0x16C, 0);
        } else {
            Math_SmoothStepToS(&this->skullRotZ, 0, 3, 0x16C, 0);
        }
    }

    if ((this->animIndex == DAMPE_ANIM_STARTLE) && Animation_OnFrame(&this->skelAnime, this->skelAnime.endFrame)) {
        SubS_ChangeAnimationBySpeedInfo(&this->skelAnime, sAnimations, DAMPE_ANIM_STARTLE_LOOP, &this->animIndex);
    }

    if (!(this->tkFlags2 & TKFLAGS2_UNK_40)) {
        dampeSearchIter = NULL;

        do {
            dampeSearchIter = SubS_FindActor(play, dampeSearchIter, ACTORCAT_NPC, ACTOR_EN_TK);
            if (dampeSearchIter != NULL) {
                if (DAMPE_GET_TYPE(dampeSearchIter) == DAMPE_TYPE_RUNNING) {
                    Math_Vec3f_Copy(&this->unk_2EC, &dampeSearchIter->world.pos);
                    Math_Vec3s_Copy(&this->unk_2F8, &dampeSearchIter->world.rot);
                    Actor_Kill(dampeSearchIter);
                    this->tkFlags2 |= TKFLAGS2_UNK_40;
                    break;
                }
                dampeSearchIter = dampeSearchIter->next;
            }
        } while (dampeSearchIter != NULL);
    }

    if (Actor_ProcessTalkRequest(&this->actor, &play->state)) {
        this->tkFlags2 &= ~TKFLAGS2_UNK_80;
        this->actor.flags &= ~ACTOR_FLAG_10000;
        play->msgCtx.msgMode = 0;
        play->msgCtx.msgLength = 0;
        EnTk_ChooseNextDialogue(this, play);
    } else if (!(this->tkFlags2 & TKFLAGS2_UNK_80)) {
        if (this->actor.xzDistToPlayer < 100.0f) {
            func_8013E8F8(&this->actor, play, 100.0f, 100.0f, PLAYER_IA_NONE, 0x4000, 0x4000);
        }
    } else {
        func_800B8500(&this->actor, play, this->actor.xzDistToPlayer, this->actor.playerHeightRel, PLAYER_IA_NONE);
    }
}

void EnTk_SetupRunFromBigpo(EnTk* this, PlayState* play) {
    this->actor.params = -1;
    this->bigpoRunCutsceneTimer = 0;
    this->actor.speedXZ = 0.0f;
    SubS_ChangeAnimationBySpeedInfo(&this->skelAnime, sAnimations, DAMPE_ANIM_REST, &this->animIndex);
    this->actionFunc = EnTk_RunFromBigpo;
}

void EnTk_RunFromBigpo(EnTk* this, PlayState* play) {
    if ((this->actor.params >= 0) && SubS_StartActorCutscene(&this->actor, this->cutscenes[1], this->actor.params,
                                                             SUBS_CUTSCENE_SET_UNK_LINK_FIELDS)) {
        this->bigpoRunCutsceneTimer = ActorCutscene_GetLength(this->cutscenes[1]);
        func_80151938(play, 0x1411); // (Scream) It's the leader of the ghosts!
        EnTk_SetupRunFromBigpoKill(this, play);
    }
}

void EnTk_SetupRunFromBigpoKill(EnTk* this, PlayState* play) {
    this->actor.speedXZ = 10.0f;
    SubS_ChangeAnimationBySpeedInfo(&this->skelAnime, sAnimations, DAMPE_ANIM_RUN, &this->animIndex);
    Math_Vec3f_Copy(&this->actor.world.pos, &this->unk_2EC);
    Math_Vec3f_Copy(&this->actor.prevPos, &this->unk_2EC);
    Math_Vec3s_Copy(&this->actor.world.rot, &this->unk_2F8);
    Math_Vec3s_Copy(&this->actor.shape.rot, &this->unk_2F8);
    this->actionFunc = EnTk_RunFromBigpoKill;
}

void EnTk_RunFromBigpoKill(EnTk* this, PlayState* play) {
    this->bigpoRunCutsceneTimer--;
    if (this->bigpoRunCutsceneTimer <= 0) {
        ActorCutscene_Stop(this->cutscenes[1]);
        func_801477B4(play);
        Actor_Kill(&this->actor);
    }
}

// second DigGameIdle Setup function called when you find a flame
void EnTk_SetupDigGameIdleFoundSpot(EnTk* this, PlayState* play) {
    this->actor.speedXZ = 0.0f;
    SubS_ChangeAnimationBySpeedInfo(&this->skelAnime, sAnimations, DAMPE_ANIM_REST, &this->animIndex);
    this->actor.flags |= ACTOR_FLAG_10000;
    this->tkFlags2 |= TKFLAGS2_UNK_80;
    this->actionFunc = EnTk_DigGameIdle;
}

// might not be the only one
void EnTk_ChooseNextDialogue(EnTk* this, PlayState* play) {
    switch (this->type) {
        case DAMPE_TYPE_DIG_GAME_NPC:
            if (Player_GetMask(play) == PLAYER_MASK_CAPTAIN) {
                this->textId = 0x1404; // (Screaming) They're out! Go away!
                break;
            }

            switch (this->digGameState) {
                case DAMPE_DIG_GAME_STATE_IDLE:
                    this->tkFlags2 &= ~TKFLAGS2_UNK_1000;
                    if (!CHECK_WEEKEVENTREG(WEEKEVENTREG_52_80)) {
                        this->textId = 0x1405; // Who are you? Not a ghost are you?
                    } else {
                        this->textId = 0x140B; // Where did you go? ... I need to follow your light.
                    }
                    break;

                case DAMPE_DIG_GAME_STATE_FOUND_DIG_SPOT:
                    this->textId = 0x140D; // Something here, want me to dig? y/n
                    break;

                case DAMPE_DIG_GAME_STATE_FOUND_NOTHING: 
                    // Nothing here, show me another spot.
                    Message_StartTextbox(play, 0x140F, &this->actor);
                    SubS_ChangeAnimationBySpeedInfo(&this->skelAnime, sAnimations, DAMPE_ANIM_REST, &this->animIndex);
                    break;

                case DAMPE_DIG_GAME_STATE_FOUND_FLAME:
                    // (dug up bigpo flame) Something strange is here.. Show me anothe spot
                    Message_StartTextbox(play, 0x1410, &this->actor);
                    SubS_ChangeAnimationBySpeedInfo(&this->skelAnime, sAnimations, DAMPE_ANIM_REST, &this->animIndex);
                    break;
            }
            break;

        case DAMPE_TYPE_HIDING:
            this->textId = 0x1414; // (Hiding under bed) I didn't see anything!
            break;
    }

    this->actionFunc = EnTk_TalkDigGame;
}

void EnTk_TalkDigGame(EnTk* this, PlayState* play) {
    if ((this->animIndex == DAMPE_ANIM_STARTLE) && Animation_OnFrame(&this->skelAnime, this->skelAnime.endFrame)) {
        SubS_ChangeAnimationBySpeedInfo(&this->skelAnime, sAnimations, DAMPE_ANIM_STARTLE_LOOP, &this->animIndex);
    }

    switch (Message_GetState(&play->msgCtx)) {
        case TEXT_STATE_NONE:
            switch (this->textId) {
                case 0x1404: // (Screaming) They're out! Go away!
                case 0x1405: // Who are you? Not a ghost are you?
                case 0x140B: // Where did you go? ... I need to follow your light.
                case 0x140D: // Something here, want me to dig? y/n
                    Math_SmoothStepToS(&this->actor.shape.rot.y, this->actor.yawTowardsPlayer - 0x1555, 1, 0x71C, 0);
                    this->actor.world.rot.y = this->actor.shape.rot.y;
                    if (!Math_SmoothStepToS(&this->skullRotZ, 0, 3, 0x16C, 10) &&
                        !Math_SmoothStepToS(&this->skullRotY, 0, 3, 0x71C, 10) &&
                        (this->actor.shape.rot.y == (s16)(this->actor.yawTowardsPlayer - 0x1555))) {
                        if (this->textId == 0x1404) {
                            // (Screaming) They're out! Go away!
                            SubS_ChangeAnimationBySpeedInfo(&this->skelAnime, sAnimations, DAMPE_ANIM_STARTLE, &this->animIndex);
                        } else {
                            SubS_ChangeAnimationBySpeedInfo(&this->skelAnime, sAnimations, DAMPE_ANIM_REST, &this->animIndex);
                        }
                        Message_StartTextbox(play, this->textId, &this->actor);
                    }
                    break;

                case 0x1414: // (Hiding under bed) I didn't see anything!
                    Message_StartTextbox(play, this->textId, &this->actor);
                    break;
            }
            break;

        case TEXT_STATE_1:
        case TEXT_STATE_CLOSING:
        case TEXT_STATE_3:
            break;

        case TEXT_STATE_CHOICE:
        case TEXT_STATE_5:
        case TEXT_STATE_DONE:
            if (Message_ShouldAdvance(play)) {
                switch (play->msgCtx.currentTextId) {
                    case 0x1404: // (Screaming) They're out! Go away!
                        this->tkFlags2 |= TKFLAGS2_UNK_1000;
                        EnTk_SetupDigGameIdle(this, play);
                        break;

                    case 0x1405: // Who are you? Not a ghost are you?
                        func_80151938(play, 0x1406);
                        break;

                    case 0x1406: // A fairy? Could you lead me?
                        func_80151938(play, 0x1407);
                        break;

                    case 0x1407: // Please? y/n
                        if (play->msgCtx.choiceIndex == 0) {
                            func_8019F208();
                            func_80151938(play, 0x1409);
                        } else {
                            func_8019F230();
                            func_80151938(play, 0x1408);
                        }
                        break;

                    case 0x1408: // I wont give up, thats how I won my wife
                        func_80151938(play, 0x1407);
                        break;

                    case 0x1409: // You will? (walk in front of me with light)
                        func_80151938(play, 0x140A);
                        break;

                    case 0x140A: // I'll even split the treasure with you, y/n
                        SET_WEEKEVENTREG(WEEKEVENTREG_52_80);

                    case 0x140B: // Where did you go? ... I need to follow your light.
                        EnTk_SetupDigGameWalking(this, play);
                        break;

                    case 0x140D: // Something here, want me to dig? y/n
                        this->tkFlags2 |= TKFLAGS2_UNK_02;
                        if (play->msgCtx.choiceIndex == 0) { // yes
                            func_8019F208();
                            play->msgCtx.msgMode = 0x44;
                            EnTk_SetupWaitForDigCutscene(this, play);
                        } else {
                            func_8019F230();
                            // In that case, take me to another spot
                            func_80151938(play, 0x140E);
                        }
                        break;

                    case 0x140E: // In any case, take me to another spot
                    case 0x140F: // Nothing here, show me another spot.
                    case 0x1410: // (dug up bigpo flame) Something strange is here.. Show me anothe spot
                        EnTk_SetupDigGameWalking(this, play);
                        break;

                    case 0x1414: // (Hiding under bed) I didn't see anything!
                        EnTk_SetupHidingUnderBed(this, play);
                        break;
                }
            }
            break;
    }
}

void EnTk_SetupWaitForDigCutscene(EnTk* this, PlayState* play) {
    this->actionFunc = EnTk_WaitForDigCutscene;
}

void EnTk_WaitForDigCutscene(EnTk* this, PlayState* play) {
    if (SubS_StartActorCutscene(&this->actor, this->cutscenes[0], 0x7C, SUBS_CUTSCENE_SET_UNK_LINK_FIELDS)) {
        EnTk_CheckForDampeDigSpot(this, play);
    }
}

// called from SubS_FindActorCustom
// where "thisActor" is the actor that calls the subs func
// where "nullActor" is the second optional actor from subs, since we call it on ourselves we know its always null
s32 EnTk_SubsVerifyActor(PlayState* play, Actor* thisActor, Actor* nullActor, void* _verifyData) {
    EnTkStruct* verifyData = (EnTkStruct*)_verifyData;

    if ((nullActor != thisActor) && (DAMPE_GET_TYPE(nullActor) == DAMPE_TYPE_DIG_GAME_SPOT)) {
        f32 distance = Actor_DistanceBetweenActors(thisActor, nullActor);
        if (distance < verifyData->distance) {
            verifyData->searchResult = nullActor;
            verifyData->distance = distance;
        }
    }

    return false;
}

void EnTk_CheckForDampeDigSpot(EnTk* this, PlayState* play) {
    EnTkStruct tkStruct;

    tkStruct.searchResult = NULL;
    tkStruct.distance = FLT_MAX;

    SubS_FindActorCustom(play, &this->actor, NULL, ACTORCAT_NPC, ACTOR_EN_TK, &tkStruct, EnTk_SubsVerifyActor);
    if (tkStruct.searchResult == NULL) {
        Actor_Kill(&this->actor);
    } else {
      this->unk_2CC = Actor_YawToPoint(&this->actor, &tkStruct.searchResult->world.pos);
      this->actionFunc = EnTk_TurnTowardDigSpot;
    }
}

void EnTk_TurnTowardDigSpot(EnTk* this, PlayState* play) {
    Math_SmoothStepToS(&this->actor.shape.rot.y, this->unk_2CC, 2, 0xE38, 0x5B);
    this->actor.world.rot.y = this->actor.shape.rot.y;
    if (this->actor.shape.rot.y == this->unk_2CC) {
        EnTk_SetupDigging(this, play);
    }
}

void EnTk_SetupDigging(EnTk* this, PlayState* play) {
    this->digGameState = DAMPE_DIG_GAME_STATE_FOUND_DIG_SPOT;
    SubS_ChangeAnimationBySpeedInfo(&this->skelAnime, sAnimations, DAMPE_ANIM_DIG, &this->animIndex);
    this->actionFunc = EnTk_Digging;
}

void EnTk_Digging(EnTk* this, PlayState* play) {
    Actor* bigPoe;

    if ((this->skelAnime.curFrame > 33.0f) && (this->skelAnime.curFrame < 41.0f)) {
        func_800BBFB0(play, &this->unk_2B4, 10.0f, 2, 50, 30, 1);
    }

    if (Animation_OnFrame(&this->skelAnime, 33.0f)) {
        Actor_PlaySfxAtPos(&this->actor, NA_SE_EV_DIG_UP);
    }

    if (!(this->tkFlags2 & TKFLAGS2_UNK_20)) {
        if (Animation_OnFrame(&this->skelAnime, 37.0f)) {
            bigPoe = NULL;
            do {
                bigPoe = SubS_FindActor(play, bigPoe, ACTORCAT_PROP, ACTOR_EN_BIGPO);

                if (bigPoe != NULL) {
                    if ((bigPoe->params == ENBIGPO_CHOSENFIRE) && (Actor_DistanceBetweenActors(&this->actor, bigPoe) < 80.0f)) {
                        bigPoe->params = ENBIGPO_REVEALEDFIRE;
                        this->tkFlags2 |= TKFLAGS2_UNK_20;
                        this->bigpoFlameFoundCount++;
                    }
                    bigPoe = bigPoe->next;
                }
            } while (bigPoe != NULL);
        }
    }

    if (Animation_OnFrame(&this->skelAnime, this->skelAnime.endFrame)) {
        func_80AEE650(this, play);
    }
}

void func_80AEE650(EnTk* this, PlayState* play) {
    if (this->unk_36C < ARRAY_COUNT(this->unk_324)) {
        Math_Vec3f_Copy(&this->unk_324[this->unk_36C], &this->actor.world.pos);
        this->unk_36C++;
    }
    this->actionFunc = func_80AEE6B8;
}

void func_80AEE6B8(EnTk* this, PlayState* play) {
    if (this->tkFlags2 & TKFLAGS2_UNK_20) {
        if (this->bigpoFlameFoundCount >= 3) {
            ActorCutscene_Stop(this->cutscenes[0]);
            func_801477B4(play);
            EnTk_SetupRunFromBigpo(this, play);
        } else if (SubS_StartActorCutscene(&this->actor, 0x7C, this->cutscenes[0], SUBS_CUTSCENE_SET_UNK_LINK_FIELDS)) {
            this->digGameState = DAMPE_DIG_GAME_STATE_FOUND_FLAME;
            EnTk_ChooseNextDialogue(this, play);
            this->tkFlags2 &= ~TKFLAGS2_UNK_20;
        }
    } else if (SubS_StartActorCutscene(&this->actor, 0x7C, this->cutscenes[0], SUBS_CUTSCENE_SET_UNK_LINK_FIELDS)) {
        this->digGameState = DAMPE_DIG_GAME_STATE_FOUND_NOTHING;
        EnTk_ChooseNextDialogue(this, play);
    }
}

// this is a meta function, it includes following player, wandering, lost, etc
void EnTk_SetupDigGameWalking(EnTk* this, PlayState* play) {
    this->digGameMovingState = DAMPE_DIG_GAME_MOVING_STATE_PRE;
    this->digGameState = DAMPE_DIG_GAME_STATE_WALKING;
    Math_Vec3s_Copy(&this->actor.world.rot, &this->actor.shape.rot);
    EnTk_CheckDigGameMovingState(this, play);
    this->actionFunc = EnTk_DigGameWalking;
}

s32 func_80AEE7E0(Vec3f* arg0, f32 arg1, Vec3f* arg2, s32 arg3) {
    s32 i;
    s32 ret = true;

    for (i = 0; i < arg3; i++) {
        if (Math_Vec3f_DistXZ(arg0, &arg2[i]) < arg1) {
            ret = false;
            break;
        }
    }
    return ret;
}

s32 EnTk_CheckFoundDigSpot(EnTk* this, PlayState* play) {
    static Vec3f D_80AEFA78 = { 0.0f, 20.0f, 32.0f };
    s32 pad;
    s32 ret = false;
    s32 pad2;
    CollisionPoly* sp38;
    s32 sp34;
    Vec3f sp28;

    Lib_Vec3f_TranslateAndRotateY(&this->actor.world.pos, this->actor.shape.rot.y, &D_80AEFA78, &sp28);
    if ((BgCheck_EntityRaycastFloor3(&play->colCtx, &sp38, &sp34, &sp28) != BGCHECK_Y_MIN) &&
        (func_800C9BB8(&play->colCtx, sp38, sp34) == 1) && (this->digGameMovingState == (u32)DAMPE_DIG_GAME_MOVING_STATE_FOLLOWING) &&
        (this->actor.xyzDistToPlayerSq <= SQ(115.0f)) &&
        func_80AEE7E0(&this->actor.world.pos, 100.0f, this->unk_324, this->unk_36C) &&
        (((this->tkFlags2 & TKFLAGS2_RIDING_ELEVATOR) && (Math_Vec3f_DistXZ(&this->unk_300, &sp28) >= 100.0f)) || !(this->tkFlags2 & TKFLAGS2_RIDING_ELEVATOR)) &&
        !Play_InCsMode(play)) {
        Math_Vec3f_Copy(&this->unk_300, &sp28);
        ret = true;
    }
    return ret;
}

void EnTk_DigGameWalking(EnTk* this, PlayState* play) {
    this->followActionFunc(this, play);

    EnTk_CheckDigGameMovingState(this, play);
    if (Math_Vec3f_DistXZ(&this->actor.world.pos, &this->unk_300) >= 100.0f) {
        this->tkFlags2 &= ~TKFLAGS2_RIDING_ELEVATOR;
    }

    if (EnTk_CheckFoundDigSpot(this, play)) {
        this->digGameState = DAMPE_DIG_GAME_STATE_FOUND_DIG_SPOT;
        EnTk_SetupDigGameIdleFoundSpot(this, play);
    }
}


s32 EnTk_GetNewDigGameMovingState(EnTk* this, PlayState* play) {
    s32 newState;

    if (this->tkFlags2 & TKFLAGS2_RIDING_ELEVATOR) {
        newState = DAMPE_DIG_GAME_MOVING_STATE_RIDING_ELEVATOR;
    } else if (this->actor.xyzDistToPlayerSq < SQ(60.0f)) {
        newState = DAMPE_DIG_GAME_MOVING_STATE_STANDING;
    } else if (this->actor.isTargeted || (play->actorCtx.targetContext.unk_94 == &this->actor) ||
               (this->actor.xyzDistToPlayerSq < SQ(80.0f))) {
        newState = DAMPE_DIG_GAME_MOVING_STATE_FOLLOWING;
    } else {
        newState = DAMPE_DIG_GAME_MOVING_STATE_LOST;
    }
    return newState;
}

// if not "check" what word best describes the action of checking if the status needs updating without "update"
void EnTk_CheckDigGameMovingState(EnTk* this, PlayState* play) {
    s32 newState = EnTk_GetNewDigGameMovingState(this, play);

    if (newState != this->digGameMovingState) {
        switch (newState) {
            case DAMPE_DIG_GAME_MOVING_STATE_STANDING:
                EnTk_SetFollowFuncStanding(this, play);
                break;

            case DAMPE_DIG_GAME_MOVING_STATE_FOLLOWING:
                EnTk_SetFollowFuncFollowing(this, play);
                break;

            case DAMPE_DIG_GAME_MOVING_STATE_LOST:
                EnTk_SetFollowFuncLost(this, play);
                break;

            case DAMPE_DIG_GAME_MOVING_STATE_RIDING_ELEVATOR:
                EnTk_SetFollowFuncRidingElevator(this, play);
                break;

            // ! @Bug: The above function cannot return 4, this case is never used
            case 4:
                EnTk_SetFollowFuncUnused(this, play);
                break;
        }
        this->digGameMovingState = newState;
    }
}

void EnTk_SetFollowFuncLost(EnTk* this, PlayState* play) {
    s32 sp74;
    Vec3f sp68;
    s32 i;
    f32 temp;

    for (i = 0; i < 8; i++) {
        sp68.x = Math_SinS(this->actor.world.rot.y + (i * 0x2000)) * 80.0f;
        sp68.z = Math_CosS(this->actor.world.rot.y + (i * 0x2000)) * 80.0f;

        sp68.x += this->actor.world.pos.x;
        sp68.y = this->actor.world.pos.y + 50.0f;
        sp68.z += this->actor.world.pos.z;

        temp =
            BgCheck_EntityRaycastFloor3(&play->colCtx, &this->actor.floorPoly, &sp74, &sp68) - this->actor.world.pos.y;
        if (temp <= -80.0f) {
            break;
        }
    }

    if (i == 8) {
        this->unk_2CC = BINANG_ROT180((Rand_Centered() * 0x8000) + this->actor.yawTowardsPlayer);
    } else {
        this->unk_2CC = this->actor.world.rot.y + (i * 0x2000);
    }

    this->unk_2C6 = 100;
    SubS_ChangeAnimationBySpeedInfo(&this->skelAnime, sAnimations, DAMPE_ANIM_WALK2, &this->animIndex);
    this->followActionFunc = EnTk_FollowFuncLost;
}

void EnTk_FollowFuncLost(EnTk* this, PlayState* play) {
    f32 sp64;
    Vec3f sp58;
    s16 sp56 = this->actor.shape.rot.y;
    Vec3f sp48;
    Vec3f sp3C;

    Math_Vec3f_Copy(&sp58, &this->actor.world.pos);
    sp58.x += (Math_SinS(sp56) * 20.0f);
    sp58.y += 30.0f;
    sp58.z += Math_CosS(sp56) * 20.0f;

    if (BgCheck_SphVsFirstWall(&play->colCtx, &sp58, 20.0f)) {
        Math_Vec3f_Copy(&sp48, &this->actor.world.pos);
        sp56 = BINANG_ADD(this->actor.shape.rot.y, 0x4000);
        sp48.x += (Math_SinS(sp56) * 20.0f);
        sp48.y += 30.0f;
        sp48.z += Math_CosS(sp56) * 20.0f;

        Math_Vec3f_Copy(&sp3C, &this->actor.world.pos);
        sp56 = BINANG_SUB(this->actor.shape.rot.y, 0x4000);
        sp3C.x += (Math_SinS(sp56) * 20.0f);
        sp3C.y += 30.0f;
        sp3C.z += Math_CosS(sp56) * 20.0f;

        if (BgCheck_SphVsFirstWall(&play->colCtx, &sp48, 20.0f)) {
            if (BgCheck_SphVsFirstWall(&play->colCtx, &sp3C, 20.0f)) {
                this->unk_2CC = this->actor.shape.rot.y - 0x4000;
            } else {
                this->unk_2CC = this->actor.shape.rot.y - 0x4000;
            }
        } else {
            this->unk_2CC = this->actor.shape.rot.y + 0x4000;
        }
    }

    if (this->tkFlags2 & TKFLAGS2_STOPPED) {
        SubS_ChangeAnimationBySpeedInfo(&this->skelAnime, sAnimations, DAMPE_ANIM_REST, &this->animIndex);
    } else {
        SubS_ChangeAnimationBySpeedInfo(&this->skelAnime, sAnimations, DAMPE_ANIM_WALK2, &this->animIndex);
        func_80AEC658(&this->skelAnime, this->curAnimFrame, 1.0f, &this->actor.speedXZ, &sp64);
    }

    if (this->actor.speedXZ > 0.5f) {
        Math_SmoothStepToS(&this->actor.world.rot.y, this->unk_2CC, 2, 0xAAA, 1);
        this->actor.shape.rot.y = this->actor.world.rot.y;
    }

    if ((Message_GetState(&play->msgCtx) == TEXT_STATE_NONE) && !Play_InCsMode(play) && (this->unk_2C6-- <= 0)) {
        // Where did you go? Please walk slower
        Message_StartTextbox(play, 0x140C, NULL);
        this->tkFlags2 |= TKFLAGS2_UNK_4000;
        this->unk_2C6 = 200;
    }
}

void EnTk_SetFollowFuncFollowing(EnTk* this, PlayState* play) {
    SubS_ChangeAnimationBySpeedInfo(&this->skelAnime, sAnimations, DAMPE_ANIM_WALK2, &this->animIndex);
    this->followActionFunc = EnTk_FollowFuncFollowing;
}

// TODO needs better name
// This is when he is actually following the player during dig minigame
void EnTk_FollowFuncFollowing(EnTk* this, PlayState* play) {
    f32 sp2C;

    if (this->tkFlags2 & TKFLAGS2_STOPPED) {
        SubS_ChangeAnimationBySpeedInfo(&this->skelAnime, sAnimations, DAMPE_ANIM_REST, &this->animIndex);
    } else {
        SubS_ChangeAnimationBySpeedInfo(&this->skelAnime, sAnimations, DAMPE_ANIM_WALK2, &this->animIndex);
        func_80AEC658(&this->skelAnime, this->curAnimFrame, 1.0f, &this->actor.speedXZ, &sp2C);
    }

    if (this->actor.speedXZ >= 0.5f) {
        Math_SmoothStepToS(&this->actor.world.rot.y, this->actor.yawTowardsPlayer, 2, 0x38E, 1);
        this->actor.shape.rot.y = this->actor.world.rot.y;
    }
}

void EnTk_SetFollowFuncRidingElevator(EnTk* this, PlayState* play) {
    this->actor.speedXZ = 0.0f;
    SubS_ChangeAnimationBySpeedInfo(&this->skelAnime, sAnimations, DAMPE_ANIM_REST, &this->animIndex);
    this->followActionFunc = EnTk_FollowFuncRidingElevator;
}

void EnTk_FollowFuncRidingElevator(EnTk* this, PlayState* play) {
}

// Never used because this state doesn't exist, see: EnTk_CheckDigGameMovingState
void EnTk_SetFollowFuncUnused(EnTk* this, PlayState* play) {
    SubS_ChangeAnimationBySpeedInfo(&this->skelAnime, sAnimations, DAMPE_ANIM_REST, &this->animIndex);
    this->followActionFunc = EnTk_FollowFuncUnused;
}

void EnTk_FollowFuncUnused(EnTk* this, PlayState* play) {
}

void EnTk_SetFollowFuncStanding(EnTk* this, PlayState* play) {
    this->actor.speedXZ = 0.0f;
    SubS_ChangeAnimationBySpeedInfo(&this->skelAnime, sAnimations, DAMPE_ANIM_REST, &this->animIndex);
    this->followActionFunc = EnTk_WalkingFuncStanding;
}

void EnTk_WalkingFuncStanding(EnTk* this, PlayState* play) {
    Math_SmoothStepToS(&this->actor.shape.rot.y, this->actor.yawTowardsPlayer - 0x1555, 3, 0x1C7, 0);
    this->actor.world.rot.y = this->actor.shape.rot.y;
}

/**
 *  Assigned for both types: 
 *    DAMPE_TYPE_RUNNING (running away from scary mask
 *    DAMPE_TYPE_DIG_GAME_SPOT (the proximity spots dampe knows he can dig at)
 */
void EnTk_UpdateDoNothing(Actor* thisx, PlayState* play) {
}

void EnTk_UpdateOutside(Actor* thisx, PlayState* play) {
    s32 pad;
    EnTk* this = THIS;

    if (this->actor.draw != NULL) {
        Collider_UpdateCylinder(&this->actor, &this->collider);
        CollisionCheck_SetOC(play, &play->colChkCtx, &this->collider.base);
    }

    this->curAnimFrame = this->skelAnime.curFrame;
    SkelAnime_Update(&this->skelAnime);

    if ((this->actor.draw != NULL) && ((this->animIndex == DAMPE_ANIM_WALK) || (this->animIndex == DAMPE_ANIM_WALK2)) &&
        (Animation_OnFrame(&this->skelAnime, 0.0f) || Animation_OnFrame(&this->skelAnime, 24.0f))) {
        Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_GOLON_WALK);
    }

    this->actionFunc(this, play);

    Actor_MoveWithGravity(&this->actor);
    Actor_UpdateBgCheckInfo(play, &this->actor, 10.0f, 10.0f, 0.0f, 4);
    EnTk_Blink(this);
}

void EnTk_UpdateDigGame(Actor* thisx, PlayState* play) {
    s32 pad;
    EnTk* this = THIS;

    Collider_UpdateCylinder(&this->actor, &this->collider);
    CollisionCheck_SetOC(play, &play->colChkCtx, &this->collider.base);
    this->curAnimFrame = this->skelAnime.curFrame;
    SkelAnime_Update(&this->skelAnime);
    EnTk_Blink(this);

    if (((this->animIndex == DAMPE_ANIM_WALK) || (this->animIndex == DAMPE_ANIM_WALK2)) &&
        (Animation_OnFrame(&this->skelAnime, 0.0f) || Animation_OnFrame(&this->skelAnime, 24.0f))) {
        Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_GOLON_WALK);
    }

    this->tkFlags2 &= ~TKFLAGS2_RIDING_ELEVATOR;

    if (this->actor.floorBgId != BGCHECK_SCENE) {
        BgDanpeiMovebg* platform = (BgDanpeiMovebg*)DynaPoly_GetActor(&play->colCtx, this->actor.floorBgId);

        if (platform != NULL) {
            if (platform->dyna.actor.id == ACTOR_BG_DANPEI_MOVEBG) {
                platform->unk_1CC |= 1;
                if (platform->unk_1CC & 2) {
                    this->tkFlags2 |= TKFLAGS2_RIDING_ELEVATOR;
                }
            }
        } else {
            Math_Vec3f_Copy(&this->actor.world.pos, &this->actor.home.pos);
            Math_Vec3f_Copy(&this->actor.prevPos, &this->actor.home.pos);
        }
    }

    this->actionFunc(this, play);

    Actor_MoveWithGravity(&this->actor);
    Actor_UpdateBgCheckInfo(play, &this->actor, 10.0f, 10.0f, 0.0f, 5);

    if ((this->type == DAMPE_TYPE_DIG_GAME_NPC) && (func_800C9B40(&play->colCtx, this->actor.floorPoly, this->actor.floorBgId) == 12)) {
        Math_Vec3f_Copy(&this->actor.world.pos, &this->actor.prevPos);
        this->tkFlags2 |= TKFLAGS2_STOPPED;
        this->actor.velocity.y = 0.0f;
    } else {
        this->tkFlags2 &= ~TKFLAGS2_STOPPED;
    }

    if (!(this->tkFlags2 & TKFLAGS2_STOPPED)) {
        if (!(this->actor.bgCheckFlags & 1)) {
            func_800B9010(&this->actor, NA_SE_EV_HONEYCOMB_FALL - SFX_FLAG);
        } else if (this->actor.bgCheckFlags & 2) {
            Actor_PlaySfxAtPos(&this->actor, NA_SE_EV_HUMAN_BOUND);
        }
    }
}

void EnTk_UpdateHidingUnderBed(Actor* thisx, PlayState* play) {
    EnTk* this = THIS;

    this->unk_316 += 0x46C8;
    this->unk_318 = Math_SinS(this->unk_316) * 900.0f;
    this->actionFunc(this, play);
}

s32 EnTk_OverrideLimbDraw(PlayState* play, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, Actor* thisx) {
    EnTk* this = THIS;

    if (limbIndex == DAMPE_LIMB_SKULL) {
        rot->z += this->skullRotZ;
        rot->y += this->skullRotY;
    }
    return false;
}

void EnTk_PostLimbDraw(PlayState* play, s32 limbIndex, Gfx** dList, Vec3s* rot, Actor* thisx) {
    static Vec3f D_80AEFA84 = { 0.0f, 0.0f, 4600.0f };
    EnTk* this = THIS;

    if (this->type != DAMPE_TYPE_HIDING) {
        switch (limbIndex) {
            case DAMPE_LIMB_SKULL:
                Matrix_MultZero(&this->actor.focus.pos);
                break;

            case DAMPE_LIMB_RIGHT_HAND:
                Matrix_MultVec3f(&D_80AEFA84, &this->unk_2B4);

                OPEN_DISPS(play->state.gfxCtx);

                gSPDisplayList(POLY_OPA_DISP++, gDampeShovelDL);

                CLOSE_DISPS(play->state.gfxCtx);
                break;
        }
    }
}

/*
void Debug_PrintToScreen(Actor* thisx, PlayState* play) {
    EnTk* this = THIS; // replace with THIS actor
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
        u32 convertedAddr = (u32)Fault_ConvertAddress((void*)this->actionFunc);
        GfxPrint_SetPos(&printer, 1, 11);
        GfxPrint_Printf(&printer, "actionfunc vram:        func_%X", convertedAddr);
        GfxPrint_SetPos(&printer, 1, 12);
        GfxPrint_Printf(&printer, "actionfunc actual ram:  %X", this->actionFunc);
    }

    GfxPrint_SetPos(&printer, 1, 13);
    
    //GfxPrint_Printf(&printer, "drawflags %X", this->drawFlags);
    //GfxPrint_Printf(&printer, "BREG86 %X", BREG(86));
    GfxPrint_Printf(&printer, "2D0 %X", this->digGameMovingState);
    GfxPrint_SetPos(&printer, 1, 14);
    GfxPrint_Printf(&printer, "tkFlags2 %X", this->tkFlags2);
    GfxPrint_SetPos(&printer, 1, 15);
    GfxPrint_Printf(&printer, "otheractionfunc %X", this->followActionFunc);

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


void EnTk_Draw(Actor* thisx, PlayState* play) {
    static TexturePtr sDampeEyeTextures[] = { gDampeEyeOpenTex, gDampeEyeHalfTex, gDampeEyeClosedTex, };
    s32 pad;
    EnTk* this = THIS;

    OPEN_DISPS(play->state.gfxCtx);

    POLY_OPA_DISP = Gfx_CallSetupDL(POLY_OPA_DISP, 25);

    gSPSegment(POLY_OPA_DISP++, 0x08, Lib_SegmentedToVirtual(sDampeEyeTextures[this->eyeState]));

    Matrix_RotateYS(this->unk_318, MTXMODE_APPLY);
    SkelAnime_DrawFlexOpa(play, this->skelAnime.skeleton, this->skelAnime.jointTable, this->skelAnime.dListCount,
                          EnTk_OverrideLimbDraw, EnTk_PostLimbDraw, &this->actor);

    //if (this->type == DAMPE_TYPE_DIG_GAME_NPC){
      //Debug_PrintToScreen(thisx, play); // put this in your actors draw func
    //}
    
    CLOSE_DISPS(play->state.gfxCtx);
}
