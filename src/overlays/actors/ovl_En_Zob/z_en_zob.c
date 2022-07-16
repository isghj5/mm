/*
 * File: z_en_zob.c
 * Overlay: ovl_En_Zob
 * Description: Zora Bassist Japas
 */

#include "z_en_zob.h"

#define FLAGS (ACTOR_FLAG_1 | ACTOR_FLAG_8)

#define THIS ((EnZob*)thisx)

void EnZob_Init(Actor* thisx, PlayState* play);
void EnZob_Destroy(Actor* thisx, PlayState* play);
void EnZob_Update(Actor* thisx, PlayState* play);
void EnZob_Draw(Actor* thisx, PlayState* play);

void EnZob_ChangeAnimation(EnZob* this, s16 arg1, u8 arg2);
void func_80B9FD24(EnZob* this, PlayState* play);
void func_80B9FDDC(EnZob* this, PlayState* play);
void func_80B9FE1C(EnZob* this, PlayState* play);
void func_80B9FE5C(EnZob* this, PlayState* play);
void func_80B9FF20(EnZob* this, PlayState* play);
void func_80B9FF80(EnZob* this, PlayState* play);
void func_80BA005C(EnZob* this, PlayState* play);
void func_80BA00BC(EnZob* this, PlayState* play);
void func_80BA0318(EnZob* this, PlayState* play);
void func_80BA0374(EnZob* this, PlayState* play);
void func_80BA0610(EnZob* this, PlayState* play);
void func_80BA06BC(EnZob* this, PlayState* play);
void func_80BA0728(EnZob* this, PlayState* play);
void func_80BA09E0(EnZob* this, PlayState* play);
void func_80BA0A04(EnZob* this, PlayState* play);
void func_80BA0AD8(EnZob* this, PlayState* play);
void func_80BA0BB4(EnZob* this, PlayState* play);
void func_80BA0C14(EnZob* this, PlayState* play);
void func_80BA0CF4(EnZob* this, PlayState* play);

const ActorInit En_Zob_InitVars = {
    ACTOR_EN_ZOB,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_ZOB,
    sizeof(EnZob),
    (ActorFunc)EnZob_Init,
    (ActorFunc)EnZob_Destroy,
    (ActorFunc)EnZob_Update,
    (ActorFunc)EnZob_Draw,
};

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

static AnimationHeader* sAnimations[] = {
    &gJapasBassStrumLoopingAnim, &object_zob_Anim_002B38, &object_zob_Anim_0037A0,
    &object_zob_Anim_0043C4, &gJapasHairAdjustAnim, &gJapasHairAdjustLoopAnim,
    &gJapasIdleBassPracticeAnim, &gJapaLookingUpAnim, &gJapasBassStrumIntoIdleAnim,
};

Vec3f D_80BA1120 = { 300.0f, 900.0f, 0.0f };

void EnZob_Init(Actor* thisx, PlayState* play) {
    EnZob* this = THIS;
    s32 i;
    s16 cs;

    ActorShape_Init(&this->actor.shape, 0.0f, ActorShadow_DrawCircle, 20.0f);
    this->actor.colChkInfo.mass = MASS_IMMOVABLE;
    Actor_SetScale(&this->actor, 0.0115f);
    SkelAnime_InitFlex(play, &this->skelAnime, &gJapasSkeleton, &gJapasIdleBassPracticeAnim, this->jointTable,
                       this->morphTable, ZOB_LIMB_MAX);
    Animation_PlayLoop(&this->skelAnime, &gJapasIdleBassPracticeAnim);
    Collider_InitAndSetCylinder(play, &this->collider, &this->actor, &sCylinderInit);
    this->unk_2F4 = 0;
    this->unk_30E = -1;
    this->unk_310 = 0;
    this->curAnimationIndex = 9;
    this->unk_304 = 0;
    this->actor.terminalVelocity = -4.0f;
    this->actor.gravity = -4.0f;
    EnZob_ChangeAnimation(this, 6, ANIMMODE_ONCE);
    this->actionFunc = func_80BA0728;
    this->actor.textId = 0;

    cs = this->actor.cutscene;
    for (i = 0; i < ARRAY_COUNT(this->unk_306); i++) {
        this->unk_306[i] = cs;
        if (cs != -1) {
            this->actor.cutscene = cs;
            cs = ActorCutscene_GetAdditionalCutscene(this->actor.cutscene);
        }
    }

    this->actor.cutscene = this->unk_306[0];
    this->actor.flags |= ACTOR_FLAG_2000000;

    switch (ENZOB_GET_TYPE(&this->actor)) {
        case ZOB_TYPE_1: // standing outside
            if (gSaveContext.save.weekEventReg[78] & 1) {
                this->actionFunc = func_80BA0BB4;
            } else {
                this->actionFunc = func_80BA0AD8;
            }

            if (!(gSaveContext.save.weekEventReg[55] & 0x80)) {
                Actor_MarkForDeath(&this->actor);
                return;
            }
            break;

        case ZOB_TYPE_2: // mikaus memories during healing
            this->actionFunc = func_80BA0CF4;
            this->unk_2F4 |= 0x20;
            this->unk_312 = -1;
            EnZob_ChangeAnimation(this, 0, ANIMMODE_ONCE);
            this->unk_304 = 5;
            break;

        default: // in his room 
            if (gSaveContext.save.weekEventReg[55] & 0x80) {
                Actor_MarkForDeath(&this->actor);
            }
            this->actor.flags |= ACTOR_FLAG_10;
            break;
    }
}

void EnZob_Destroy(Actor* thisx, PlayState* play) {
    EnZob* this = THIS;

    Collider_DestroyCylinder(play, &this->collider);
}

void EnZob_ChangeAnimation(EnZob* this, s16 arg1, u8 arg2) {
    Animation_Change(&this->skelAnime, sAnimations[arg1], 1.0f, 0.0f, Animation_GetLastFrame(sAnimations[arg1]), arg2,
                     -5.0f);
    this->curAnimationIndex = arg1;
}

void func_80B9F86C(EnZob* this) {
    if (SkelAnime_Update(&this->skelAnime)) {
        switch (this->unk_304) {
            case 0:
                if (Rand_ZeroFloat(1.0f) > 0.7f) {
                    if (this->curAnimationIndex == 6) {
                        EnZob_ChangeAnimation(this, 7, ANIMMODE_ONCE);
                    } else {
                        EnZob_ChangeAnimation(this, 6, ANIMMODE_ONCE);
                    }
                } else {
                    EnZob_ChangeAnimation(this, this->curAnimationIndex, 2);
                }
                break;

            case 1:
                EnZob_ChangeAnimation(this, 3, ANIMMODE_LOOP);
                break;

            case 2:
                EnZob_ChangeAnimation(this, 4, ANIMMODE_LOOP);
                break;

            case 3:
                EnZob_ChangeAnimation(this, 5, ANIMMODE_LOOP);
                break;

            case 4:
                if (this->curAnimationIndex == 3) {
                    EnZob_ChangeAnimation(this, 0, ANIMMODE_LOOP);
                } else {
                    EnZob_ChangeAnimation(this, 3, ANIMMODE_ONCE);
                }
                break;

            case 5:
                if (Rand_ZeroFloat(1.0f) < 0.8f) {
                    EnZob_ChangeAnimation(this, this->curAnimationIndex, ANIMMODE_ONCE);
                } else if (this->curAnimationIndex == 0) {
                    EnZob_ChangeAnimation(this, 1, ANIMMODE_ONCE);
                } else {
                    EnZob_ChangeAnimation(this, 0, ANIMMODE_ONCE);
                }
                break;
        }

        SkelAnime_Update(&this->skelAnime);
    }
}

void func_80B9FA3C(EnZob* this, PlayState* play) {
    u16 textId;

    this->unk_2F4 |= 1;

    if (gSaveContext.save.playerForm != PLAYER_FORM_ZORA) {
        if (gSaveContext.save.weekEventReg[30] & 2) {
            textId = 0x11F9;
        } else {
            textId = 0x11F8;
        }
        this->unk_304 = 3;
        EnZob_ChangeAnimation(this, 5, ANIMMODE_LOOP);
    } else if (this->unk_2F4 & 0x10) {
        textId = 0x1210;
        this->unk_304 = 3;
        EnZob_ChangeAnimation(this, 5, ANIMMODE_ONCE);
    } else if (gSaveContext.save.weekEventReg[31] & 8) {
        textId = 0x1205;
        this->unk_304 = 1;
        EnZob_ChangeAnimation(this, 3, ANIMMODE_LOOP);
    } else if (this->unk_2F4 & 8) {
        textId = 0x1215;
        this->unk_304 = 3;
        EnZob_ChangeAnimation(this, 5, ANIMMODE_ONCE);
    } else if (this->unk_2F4 & 2) {
        textId = 0x1203;
        this->unk_304 = 1;
        EnZob_ChangeAnimation(this, 2, ANIMMODE_ONCE);
    } else if (gSaveContext.save.weekEventReg[30] & 8) {
        textId = 0x11FA;
        this->unk_304 = 1;
        EnZob_ChangeAnimation(this, 2, ANIMMODE_ONCE);
    } else if (!(gSaveContext.save.weekEventReg[30] & 4)) {
        gSaveContext.save.weekEventReg[30] |= 4;
        textId = 0x11FB;
        this->unk_304 = 1;
        EnZob_ChangeAnimation(this, 2, ANIMMODE_ONCE);
    } else {
        textId = 0x1201;
        this->unk_304 = 3;
        EnZob_ChangeAnimation(this, 4, ANIMMODE_ONCE);
    }

    Message_StartTextbox(play, textId, &this->actor);
}

void func_80B9FC0C(EnZob* this) {
    if (this->unk_30E != -1) {
        if (ActorCutscene_GetCurrentIndex() == this->unk_306[this->unk_30E]) {
            ActorCutscene_Stop(this->unk_306[this->unk_30E]);
        }
        this->unk_30E = -1;
    }
}

void func_80B9FC70(EnZob* this, s16 arg1) {
    func_80B9FC0C(this);
    this->unk_30E = arg1;
}

void func_80B9FCA0(EnZob* this, PlayState* play) {
    func_801477B4(play);
    play->msgCtx.ocarinaMode = 4;
    func_80B9FC0C(this);
    this->unk_2F4 &= ~1;
    this->actionFunc = func_80BA0728;
    this->unk_304 = 0;
    EnZob_ChangeAnimation(this, 6, ANIMMODE_ONCE);
    func_800B8718(&this->actor, &play->state);
}

void func_80B9FD24(EnZob* this, PlayState* play) {
    s32 actionIndex;
    s16 action;

    func_80B9F86C(this);

    if (Cutscene_CheckActorAction(play, 500)) {
        this->unk_30E = -1;
        actionIndex = Cutscene_GetActorActionIndex(play, 500);
        action = play->csCtx.actorActions[actionIndex]->action;

        if (action != this->unk_310) {
            this->unk_310 = action;
            switch (action) {
                case 1:
                    EnZob_ChangeAnimation(this, 8, ANIMMODE_LOOP);
                    break;

                case 2:
                    EnZob_ChangeAnimation(this, 7, ANIMMODE_LOOP);
                    break;
            }
        }
    }
}

void func_80B9FDDC(EnZob* this, PlayState* play) {
    Message_StartTextbox(play, 0x120C, &this->actor);
    this->actionFunc = func_80BA00BC;
}

void func_80B9FE1C(EnZob* this, PlayState* play) {
    Message_StartTextbox(play, 0x1211, &this->actor);
    this->actionFunc = func_80BA00BC;
}

void func_80B9FE5C(EnZob* this, PlayState* play) {
    func_80B9F86C(this);
    if (play->msgCtx.ocarinaMode == 3) {
        play->msgCtx.unk11F10 = 0;
        this->actionFunc = func_80B9FDDC;
        func_80B9FC70(this, 0);
    } else if (Message_GetState(&play->msgCtx) == 11) {
        play->msgCtx.unk11F10 = 0;
        this->actionFunc = func_80B9FE1C;
        this->unk_304 = 3;
        EnZob_ChangeAnimation(this, 5, ANIMMODE_ONCE);
        func_80B9FC70(this, 0);
    }
}

void func_80B9FF20(EnZob* this, PlayState* play) {
    func_80B9F86C(this);
    if (Message_GetState(&play->msgCtx) == 7) {
        func_80152434(play, 0x42);
        this->actionFunc = func_80B9FE5C;
        func_80B9FC70(this, 2);
    }
}

void func_80B9FF80(EnZob* this, PlayState* play) {
    func_80B9F86C(this);
    if (play->msgCtx.ocarinaMode == 3) {
        this->actionFunc = func_80B9FF20;
        this->unk_304 = 6;
        EnZob_ChangeAnimation(this, 1, ANIMMODE_LOOP);
        func_80152434(play, 0x3E);
        func_80B9FC70(this, 1);
    } else if (Message_GetState(&play->msgCtx) == 11) {
        play->msgCtx.unk11F10 = 0;
        this->actionFunc = func_80B9FE1C;
        this->unk_304 = 3;
        EnZob_ChangeAnimation(this, 5, ANIMMODE_ONCE);
        func_80B9FC70(this, 0);
    }
}

void func_80BA005C(EnZob* this, PlayState* play) {
    func_80B9F86C(this);
    if (Message_GetState(&play->msgCtx) == 7) {
        func_80152434(play, 0x41);
        this->actionFunc = func_80B9FF80;
        func_80B9FC70(this, 2);
    }
}

void func_80BA00BC(EnZob* this, PlayState* play) {
    func_80B9F86C(this);

    switch (Message_GetState(&play->msgCtx)) {
        case 4:
            if (Message_ShouldAdvance(play) && (play->msgCtx.currentTextId == 0x1212)) {
                switch (play->msgCtx.choiceIndex) {
                    case 1:
                        func_8019F208();
                        func_80151938(play, 0x1209);
                        this->unk_304 = 1;
                        EnZob_ChangeAnimation(this, 2, ANIMMODE_ONCE);
                        break;

                    case 0:
                        func_8019F230();
                        func_80151938(play, 0x1213);
                        break;
                }
            }
            break;

        case 5:
            if (Message_ShouldAdvance(play)) {
                switch (play->msgCtx.currentTextId) {
                    case 0x1208:
                    case 0x120E:
                    case 0x1216:
                        func_80151938(play, play->msgCtx.currentTextId + 1);
                        break;

                    case 0x120C:
                        play->msgCtx.unk11F10 = 0;
                        this->actionFunc = func_80B9FD24;
                        EnZob_ChangeAnimation(this, 8, ANIMMODE_LOOP);
                        func_80B9FC70(this, 3);
                        break;

                    case 0x120D:
                    case 0x1211:
                    case 0x1213:
                    case 0x1217:
                        func_80151938(play, play->msgCtx.currentTextId + 1);
                        this->unk_304 = 3;
                        EnZob_ChangeAnimation(this, 4, ANIMMODE_ONCE);
                        break;

                    case 0x1218:
                        func_80B9FCA0(this, play);
                        break;

                    case 0x1214:
                        this->unk_2F4 |= 8;
                        func_80B9FCA0(this, play);
                        break;

                    case 0x120F:
                        gSaveContext.save.weekEventReg[31] |= 8;
                        this->unk_2F4 |= 0x10;
                        func_80B9FCA0(this, play);
                        break;

                    case 0x1209:
                        func_80152434(play, 0x3D);
                        this->unk_304 = 4;
                        EnZob_ChangeAnimation(this, 0, ANIMMODE_LOOP);
                        this->actionFunc = func_80BA005C;
                        func_80B9FC70(this, 1);
                        break;
                }
            }
            break;
    }
}

void func_80BA0318(EnZob* this, PlayState* play) {
    func_80152434(play, 0x3D);
    this->unk_304 = 4;
    EnZob_ChangeAnimation(this, 0, ANIMMODE_LOOP);
    this->actionFunc = func_80BA005C;
    func_80B9FC70(this, 1);
}

void func_80BA0374(EnZob* this, PlayState* play) {
    Player* player = GET_PLAYER(play);

    func_80B9F86C(this);

    switch (Message_GetState(&play->msgCtx)) {
        case 4:
            if (Message_ShouldAdvance(play) && (play->msgCtx.currentTextId == 0x1205)) {
                switch (play->msgCtx.choiceIndex) {
                    case 0:
                        func_8019F208();
                        func_80151938(play, 0x1207);
                        EnZob_ChangeAnimation(this, 2, ANIMMODE_ONCE);
                        break;

                    case 1:
                        func_8019F230();
                        func_80151938(play, 0x1206);
                        break;
                }
            }
            break;

        case 5:
            if (Message_ShouldAdvance(play)) {
                switch (play->msgCtx.currentTextId) {
                    case 0x11F8:
                        gSaveContext.save.weekEventReg[30] |= 2;
                        func_80151938(play, 0x11F9);
                        break;

                    case 0x11F9:
                        func_801477B4(play);
                        this->actionFunc = func_80BA0728;
                        this->unk_304 = 0;
                        EnZob_ChangeAnimation(this, 6, ANIMMODE_ONCE);
                        this->unk_2F4 &= ~1;
                        break;

                    case 0x11FB:
                    case 0x11FC:
                    case 0x11FF:
                    case 0x1201:
                    case 0x1203:
                        func_80151938(play, play->msgCtx.currentTextId + 1);
                        break;

                    case 0x11FD:
                        this->unk_304 = 3;
                        EnZob_ChangeAnimation(this, 4, ANIMMODE_ONCE);
                        func_80151938(play, play->msgCtx.currentTextId + 1);
                        break;

                    case 0x11FE:
                        this->unk_304 = 1;
                        EnZob_ChangeAnimation(this, 3, ANIMMODE_LOOP);
                        func_80151938(play, play->msgCtx.currentTextId + 1);
                        break;

                    case 0x11FA:
                    case 0x1200:
                    case 0x1202:
                    case 0x1204:
                    case 0x1206:
                    case 0x120F:
                    case 0x1210:
                    case 0x1215:
                        func_801477B4(play);
                        this->actionFunc = func_80BA0728;
                        this->unk_304 = 0;
                        EnZob_ChangeAnimation(this, 6, ANIMMODE_ONCE);
                        this->unk_2F4 &= ~1;
                        this->unk_2F4 |= 2;
                        break;

                    case 0x1207:
                        func_801477B4(play);
                        this->actionFunc = func_80BA0318;
                        player->unk_A90 = &this->actor;
                        player->stateFlags3 |= 0x20;
                        break;
                }
            }
            break;
    }
}

void func_80BA0610(EnZob* this, PlayState* play) {
    func_80B9F86C(this);
    if (Actor_ProcessTalkRequest(&this->actor, &play->state)) {
        this->actor.flags &= ~ACTOR_FLAG_10000;
        Message_StartTextbox(play, 0x120D, &this->actor);
        this->unk_304 = 3;
        EnZob_ChangeAnimation(this, 5, ANIMMODE_ONCE);
        func_80B9FC70(this, 0);
        this->actionFunc = func_80BA00BC;
    } else {
        func_800B8614(&this->actor, play, 500.0f);
    }
}

void func_80BA06BC(EnZob* this, PlayState* play) {
    func_80B9FD24(this, play);
    if (!Cutscene_CheckActorAction(play, 500)) {
        this->actionFunc = func_80BA0610;
        this->actor.flags |= ACTOR_FLAG_10000;
        func_80BA0610(this, play);
    }
}

void func_80BA0728(EnZob* this, PlayState* play) {
    s32 pad;
    Vec3f sp28;

    func_80B9F86C(this);

    if (func_800B8718(&this->actor, &play->state)) {
        if (gSaveContext.save.playerForm == PLAYER_FORM_ZORA) {
            Message_StartTextbox(play, 0x1208, NULL);
            gSaveContext.save.weekEventReg[30] |= 8;
        } else {
            Message_StartTextbox(play, 0x1216, NULL);
        }
        this->actionFunc = func_80BA00BC;
        this->unk_304 = 1;
        EnZob_ChangeAnimation(this, 2, ANIMMODE_ONCE);
        this->unk_30E = 0;
        this->unk_2F4 |= 1;
    } else if (Actor_ProcessTalkRequest(&this->actor, &play->state)) {
        this->actionFunc = func_80BA0374;
        func_80B9FA3C(this, play);
    } else if (Cutscene_CheckActorAction(play, 500)) {
        this->actionFunc = func_80BA06BC;
    } else if ((this->actor.xzDistToPlayer < 180.0f) && (this->actor.xzDistToPlayer > 60.0f) &&
               Player_IsFacingActor(&this->actor, 0x3000, play) && Actor_IsFacingPlayer(&this->actor, 0x3000)) {
        func_800B8614(&this->actor, play, 150.0f);
        func_800B874C(&this->actor, play, 200.0f, 150.0f);
    }

    sp28.x = this->actor.projectedPos.x;
    sp28.y = this->actor.projectedPos.y;
    sp28.z = this->actor.projectedPos.z;
    func_801A1FB4(3, &sp28, 0x6C, 1000.0f);
}

void func_80BA08E8(EnZob* this, PlayState* play) {
    s32 textId;

    if (gSaveContext.save.playerForm == PLAYER_FORM_ZORA) {
        if (gSaveContext.save.weekEventReg[79] & 1) {
            textId = 0x1257;
            this->unk_304 = 3;
            EnZob_ChangeAnimation(this, 4, ANIMMODE_ONCE);
        } else if (gSaveContext.save.weekEventReg[78] & 0x40) {
            textId = 0x1256;
            this->unk_304 = 1;
            EnZob_ChangeAnimation(this, 2, ANIMMODE_ONCE);
        } else {
            textId = 0x1255;
            gSaveContext.save.weekEventReg[78] |= 0x40;
            this->unk_304 = 1;
            EnZob_ChangeAnimation(this, 2, ANIMMODE_ONCE);
        }
    } else {
        textId = 0x1254;
        this->unk_304 = 3;
        EnZob_ChangeAnimation(this, 5, ANIMMODE_ONCE);
    }

    Message_StartTextbox(play, textId, &this->actor);
}

void func_80BA09E0(EnZob* this, PlayState* play) {
    func_80B9F86C(this);
}

void func_80BA0A04(EnZob* this, PlayState* play) {
    u8 temp_v0;

    func_80B9F86C(this);
    Math_SmoothStepToS(&this->actor.shape.rot.y, this->actor.yawTowardsPlayer, 2, 0x1000, 0x200);
    this->actor.world.rot.y = this->actor.shape.rot.y;

    temp_v0 = Message_GetState(&play->msgCtx);
    if (temp_v0 != 2) {
        if ((temp_v0 == 5) && Message_ShouldAdvance(play)) {
            func_801477B4(play);
            this->actionFunc = func_80BA0AD8;
            this->unk_304 = 0;
            EnZob_ChangeAnimation(this, 6, ANIMMODE_ONCE);
        }
    } else {
        this->actionFunc = func_80BA0AD8;
        this->unk_304 = 0;
        EnZob_ChangeAnimation(this, 6, ANIMMODE_ONCE);
    }
}

void func_80BA0AD8(EnZob* this, PlayState* play) {
    func_80B9F86C(this);

    if (this->actor.home.rot.y != this->actor.shape.rot.y) {
        Math_SmoothStepToS(&this->actor.shape.rot.y, this->actor.home.rot.y, 2, 0x1000, 0x200);
        this->actor.world.rot.y = this->actor.shape.rot.y;
    }

    if (Actor_ProcessTalkRequest(&this->actor, &play->state)) {
        this->actionFunc = func_80BA0A04;
        func_80BA08E8(this, play);
    } else if ((this->actor.xzDistToPlayer < 120.0f) && Player_IsFacingActor(&this->actor, 0x3000, play) &&
               Actor_IsFacingPlayer(&this->actor, 0x3000)) {
        func_800B8614(&this->actor, play, 120.0f);
    }
}

void func_80BA0BB4(EnZob* this, PlayState* play) {
    func_80B9F86C(this);
    if (gSaveContext.save.weekEventReg[79] & 1) {
        this->actionFunc = func_80BA09E0;
        EnZob_ChangeAnimation(this, 0, ANIMMODE_ONCE);
        this->unk_304 = 5;
    }
}

void func_80BA0C14(EnZob* this, PlayState* play) {
    func_80B9F86C(this);

    if (this->unk_312 < 799) {
        this->unk_312 += 200;
    } else {
        this->unk_312 += 30;
    }

    if (this->unk_312 > 999) {
        this->unk_312 = 999;
    }

    if (Cutscene_CheckActorAction(play, 515)) {
        if (play->csCtx.actorActions[Cutscene_GetActorActionIndex(play, 515)]->action == 1) {
            this->actionFunc = func_80BA0CF4;
            this->unk_312 = -1;
        }
    } else {
        this->actionFunc = func_80BA0CF4;
        this->unk_312 = -1;
    }
}

void func_80BA0CF4(EnZob* this, PlayState* play) {
    func_80B9F86C(this);
    if (Cutscene_CheckActorAction(play, 515) &&
        (play->csCtx.actorActions[Cutscene_GetActorActionIndex(play, 515)]->action == 2)) {
        this->actionFunc = func_80BA0C14;
    }
}

void EnZob_Update(Actor* thisx, PlayState* play) {
    s32 pad;
    EnZob* this = THIS;

    Actor_MoveWithGravity(&this->actor);

    Collider_UpdateCylinder(&this->actor, &this->collider);
    CollisionCheck_SetOC(play, &play->colChkCtx, &this->collider.base);
    Actor_UpdateBgCheckInfo(play, &this->actor, 10.0f, 10.0f, 10.0f, 4);

    this->actionFunc(this, play);

    if ((this->unk_30E != -1) && (ActorCutscene_GetCurrentIndex() != this->unk_306[this->unk_30E])) {
        if (ActorCutscene_GetCurrentIndex() == 0x7C) {
            ActorCutscene_Stop(0x7C);
            ActorCutscene_SetIntentToPlay(this->unk_306[this->unk_30E]);
        } else if (ActorCutscene_GetCanPlayNext(this->unk_306[this->unk_30E])) {
            ActorCutscene_Start(this->unk_306[this->unk_30E], &this->actor);
        } else {
            ActorCutscene_SetIntentToPlay(this->unk_306[this->unk_30E]);
        }
    }

    if (this->unk_2F4 & 1) {
        Actor_TrackPlayer(play, &this->actor, &this->unk_2F6, &this->unk_2FC, this->actor.focus.pos);
    } else {
        Math_SmoothStepToS(&this->unk_2F6.x, 0, 6, 6200, 100);
        Math_SmoothStepToS(&this->unk_2F6.y, 0, 6, 6200, 100);
        Math_SmoothStepToS(&this->unk_2FC.x, 0, 6, 6200, 100);
        Math_SmoothStepToS(&this->unk_2FC.y, 0, 6, 6200, 100);
    }
}

s32 func_80BA0F64(PlayState* play, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, Actor* thisx) {
    EnZob* this = THIS;

    if (limbIndex == 9) {
        rot->x += this->unk_2F6.y;
        rot->y += this->unk_2F6.x;
    }
    return false;
}

void func_80BA0FAC(PlayState* play, s32 limbIndex, Gfx** dList, Vec3s* rot, Actor* thisx) {
    EnZob* this = THIS;

    if (limbIndex == 9) {
        Matrix_MultVec3f(&D_80BA1120, &this->actor.focus.pos);
    }
}

void EnZob_Draw(Actor* thisx, PlayState* play) {
    EnZob* this = THIS;

    OPEN_DISPS(play->state.gfxCtx);

    func_8012C28C(play->state.gfxCtx);

    if (this->unk_2F4 & 0x20) {
        POLY_OPA_DISP = Gfx_SetFog(POLY_OPA_DISP, 0, 0, 0, 0, this->unk_312, 1000);
    }

    SkelAnime_DrawFlexOpa(play, this->skelAnime.skeleton, this->skelAnime.jointTable, this->skelAnime.dListCount,
                          func_80BA0F64, func_80BA0FAC, &this->actor);

    if (this->unk_2F4 & 0x20) {
        POLY_OPA_DISP = func_801660B8(play, POLY_OPA_DISP);
    }

    CLOSE_DISPS(play->state.gfxCtx);
}
