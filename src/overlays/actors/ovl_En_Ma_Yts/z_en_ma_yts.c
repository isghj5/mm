/*
 * File: z_en_ma_yts.c
 * Overlay: ovl_En_Ma_Yts
 * Description: Romani. As opposed as EnMa4, this actor is used in conjunction with another actor, like EnMaYto.
 */

#include "z_en_ma_yts.h"

#define FLAGS (ACTOR_FLAG_1 | ACTOR_FLAG_8 | ACTOR_FLAG_100000 | ACTOR_FLAG_2000000)

#define THIS ((EnMaYts*)thisx)

void EnMaYts_Init(Actor* thisx, PlayState* play);
void EnMaYts_Destroy(Actor* thisx, PlayState* play);
void EnMaYts_Update(Actor* thisx, PlayState* play);
void EnMaYts_Draw(Actor* thisx, PlayState* play);

void EnMaYts_SetupDoNothing(EnMaYts* this);
void EnMaYts_DoNothing(EnMaYts* this, PlayState* play);
void EnMaYts_SetupStartDialogue(EnMaYts* this);
void EnMaYts_StartDialogue(EnMaYts* this, PlayState* play);
void EnMaYts_SetupDialogueHandler(EnMaYts* this);
void EnMaYts_DialogueHandler(EnMaYts* this, PlayState* play);
void EnMaYts_SetupEndCreditsHandler(EnMaYts* this);
void EnMaYts_EndCreditsHandler(EnMaYts* this, PlayState* play);
void EnMaYts_ChooseNextDialogue(EnMaYts* this, PlayState* play);

void EnMaYts_SetFaceExpression(EnMaYts* this, s16 overrideEyeTexIndex, s16 mouthTexIndex);

void EnMaYts_DrawSleeping(Actor* thisx, PlayState* play);

const ActorInit En_Ma_Yts_InitVars = {
    ACTOR_EN_MA_YTS,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_MA1,
    sizeof(EnMaYts),
    (ActorFunc)EnMaYts_Init,
    (ActorFunc)EnMaYts_Destroy,
    (ActorFunc)EnMaYts_Update,
    (ActorFunc)EnMaYts_Draw,
};

void EnMaYts_UpdateEyes(EnMaYts* this) {
    if (this->overrideEyeTexIndex != 0) {
        this->eyeTexIndex = this->overrideEyeTexIndex;
    } else if (DECR(this->blinkTimer) == 0) {
        this->eyeTexIndex++;
        if (this->eyeTexIndex >= 3) {
            this->blinkTimer = Rand_S16Offset(30, 30);
            this->eyeTexIndex = 0;
        }
    }
}

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
    { 18, 46, 0, { 0, 0, 0 } },
};

static CollisionCheckInfoInit2 sColChkInfoInit2 = {
    0, 0, 0, 0, MASS_IMMOVABLE,
};

static AnimationSpeedInfo sAnimationInfo[] = {
    { &gRomaniIdleAnim, 1.0f, ANIMMODE_LOOP, 0.0f },
    { &gRomaniIdleAnim, 1.0f, ANIMMODE_LOOP, -6.0f },
    { &gRomaniSingStartAnim, 1.0f, ANIMMODE_ONCE, 0.0f },
    { &gRomaniSingStartAnim, 1.0f, ANIMMODE_ONCE, -6.0f },
    { &gRomaniSingLoopAnim, 1.0f, ANIMMODE_LOOP, 0.0f },
    { &gRomaniSingLoopAnim, 1.0f, ANIMMODE_LOOP, -6.0f },
    { &gRomaniRunAnim, 1.0f, ANIMMODE_LOOP, 0.0f },
    { &gRomaniRunAnim, 1.0f, ANIMMODE_LOOP, -6.0f },
    { &gRomaniWalkAnim, 1.0f, ANIMMODE_LOOP, 0.0f },
    { &gRomaniWalkAnim, 1.0f, ANIMMODE_LOOP, -6.0f },
    { &gRomaniLookAroundAnim, 1.0f, ANIMMODE_LOOP, 0.0f },
    { &gRomaniLookAroundAnim, 1.0f, ANIMMODE_LOOP, -6.0f },
    { &gRomaniShootBowAnim, 1.0f, ANIMMODE_LOOP, 0.0f },
    { &gRomaniShootBowAnim, 1.0f, ANIMMODE_LOOP, -6.0f },
    { &gRomaniSittingAnim, 1.0f, ANIMMODE_LOOP, 0.0f },
    { &gRomaniSittingAnim, 1.0f, ANIMMODE_LOOP, -6.0f },
    { &gRomaniSittingHeadShakeAnim, 1.0f, ANIMMODE_LOOP, 0.0f },
    { &gRomaniSittingHeadShakeAnim, 1.0f, ANIMMODE_LOOP, -6.0f },
    { &gRomaniSittingLookDownAnim, 1.0f, ANIMMODE_LOOP, 0.0f },
    { &gRomaniSittingLookDownAnim, 1.0f, ANIMMODE_LOOP, -6.0f },
    { &gRomaniTurnAroundAndFlickHairAnim, 1.0f, ANIMMODE_ONCE, 0.0f },
    { &gRomaniTurnAroundAndFlickHairAnim, 1.0f, ANIMMODE_ONCE, -6.0f },
};

static TexturePtr sMouthTextures[] = {
    gRomaniMouthHappyTex,
    gRomaniMouthFrownTex,
    gRomaniMouthHangingOpenTex,
    gRomaniMouthSmileTex,
};

// happy is closed happy
static TexturePtr sEyeTextures[] = {
    gRomaniEyeOpenTex, gRomaniEyeHalfTex, gRomaniEyeClosedTex, gRomaniEyeHappyTex, gRomaniEyeSadTex,
};

void EnMaYts_ChangeAnim(EnMaYts* this, s32 index) {
    Animation_Change(&this->skelAnime, sAnimationInfo[index].animation, 1.0f, 0.0f,
                     Animation_GetLastFrame(sAnimationInfo[index].animation), sAnimationInfo[index].mode,
                     sAnimationInfo[index].morphFrames);
}

// is this dialogue things? the parent could be cremia during dialogue or could be part of the ending cutscene
void func_80B8D12C(EnMaYts* this, PlayState* play) {
    Player* player = GET_PLAYER(play);
    s16 flag = this->unk_32C == 2 ? true : false;

    if (this->unk_32C == 0 || this->actor.parent == NULL) {
        this->unk_1D8.unk_18 = player->actor.world.pos;
        this->unk_1D8.unk_18.y -= -10.0f;
    } else {
        Math_Vec3f_StepTo(&this->unk_1D8.unk_18, &this->actor.parent->world.pos, 8.0f);
        this->unk_1D8.unk_18.y -= -10.0f;
    }

    func_800BD888(&this->actor, &this->unk_1D8, 0, flag);
}

void EnMaYts_InitAnimation(EnMaYts* this, PlayState* play) {
    switch (this->type) {
        case MA_YTS_TYPE_BARN:
            this->actor.targetMode = 0;
            EnMaYts_ChangeAnim(this, 0);
            break;

        case MA_YTS_TYPE_SITTING:
            this->actor.targetMode = 6;
            // Day 1 or "Winning" the alien invasion
            if (CURRENT_DAY == 1 || (gSaveContext.save.weekEventReg[22] & 1)) {
                EnMaYts_ChangeAnim(this, 14);
            } else {
                EnMaYts_ChangeAnim(this, 18);
            }
            break;

        case MA_YTS_TYPE_SLEEPING:
            this->actor.targetMode = 0;
            this->actor.draw = EnMaYts_DrawSleeping;
            EnMaYts_ChangeAnim(this, 0);
            break;

        case MA_YTS_TYPE_ENDCREDITS:
            this->actor.targetMode = 0;
            EnMaYts_ChangeAnim(this, 0);
            break;

        case MA_YTS_TYPE_SINGING:
            this->actor.targetMode = 0;
            EnMaYts_ChangeAnim(this, 4);
            break;

        default:
            EnMaYts_ChangeAnim(this, 0); // standing doing nothing
            break;
    }
}

s32 EnMaYts_CheckValidSpawn(EnMaYts* this, PlayState* play) {
    if (this->typeExt != MAYTS_VANILLA) return true; // let me do things damn it

    switch (this->type) {
        case MA_YTS_TYPE_SITTING:
            switch (CURRENT_DAY) {
                case 1:
                    break;

                case 2:
                    // Failing the alien invasion
                    if (!(gSaveContext.save.weekEventReg[22] & 1)) {
                        return false;
                    }
                    break;

                case 3:
                    // "Winning" the alien invasion
                    if (gSaveContext.save.weekEventReg[22] & 1) {
                        return false;
                    }
                    break;
            }
            break;

        case MA_YTS_TYPE_BARN:
            // Failing the alien invasion
            if (!(gSaveContext.save.weekEventReg[22] & 1)) {
                return false;
            } else if (gSaveContext.save.time >= CLOCK_TIME(20, 0) && CURRENT_DAY == 3) {
                return false;
            }
            break;

        case MA_YTS_TYPE_SLEEPING:
            // "Winning" the alien invasion
            if (gSaveContext.save.weekEventReg[22] & 1) {
                return false;
            }
            break;

        case MA_YTS_TYPE_ENDCREDITS:
            break;
    }

    return true;
}

void EnMaYts2_SetupSing(EnMaYts* this);
void EnMaYts2_ChooseNewText(EnMaYts* this, PlayState* play);

void EnMaYts2_StandingTalk(EnMaYts* this, PlayState* play) {
    if(this->actor.xzDistToPlayer > 100.0f){
        if (this->type == MA_YTS_TYPE_SINGING){
          // player has left, go back to singing
          // TODO figure out how to animate it smoother since she sorta starts doing it instantly
          EnMaYts2_SetupSing(this);
        }else { // just standing normally
          if (CURRENT_DAY == 1) {
            this->overrideEyeTexIndex = 0;
          } else {
            // her half eye is kinda half-asleep sleepwalky
            this->overrideEyeTexIndex = 1; // force half eye
          }
        }
    } else if (Message_GetState(&play->msgCtx) == 5 && Message_ShouldAdvance(play)) {
        func_801477B4(play); // ends dialogue
        if (this->actor.textId == 0x296D) {this->randomTextIndex = 1;}
    } else {
        // waiting for dialogue prompt and close by
        EnMaYts2_ChooseNewText(this, play);
        func_800B8614(&this->actor, play, 120.0f); // enables talking prompt
    }
}

void EnMaYts2_SetupStandingTalk(EnMaYts* this) {
    EnMaYts_ChangeAnim(this, 0); // change anim to standing
    this->overrideEyeTexIndex = 0; // regular blinking eyes 

    this->actionFunc = EnMaYts2_StandingTalk;
}

u16 sRandomText[] = {
  0x335C, // who are you again?
  0x2A3A, // I am not a suspicious persona
  0x296D, // I am sparticus
  0x13F6  // huh?
  // 273C I dont want to die
};

void EnMaYts2_ChooseNewText(EnMaYts* this, PlayState* play) {
  if (gSaveContext.save.playerForm != PLAYER_FORM_HUMAN) {
    this->actor.textId = 0x3336; // cute foreigner
  } else if (Player_GetMask(play) != PLAYER_MASK_NONE){ 
    this->actor.textId = 0x233F; // oh you found a cute mask
  } else if (CURRENT_DAY == 1) {
    this->actor.textId = 0x3348; // don't be late tonight
  } else if (Object_IsLoaded(&play->objectCtx, GAMEPLAY_DANGEON_KEEP)) {
    this->actor.textId = 0x208;  // eeevil
  } else { //random text
    this->actor.textId = sRandomText[this->randomTextIndex];
  }
  //this->actor.textId = 0x13F6; // testing
  //this->actor.textId = sRandomText[this->randomTextIndex];

}

void EnMaYts2_Sing(EnMaYts* this, PlayState* play) {
    // ripped from GuruGuru, because his proxmity music isn't jank like EnYb
    // using carriage music because if she shows up in romani ranch its just weird to hear ranch music ontop of ranch music
    // wish I could include a basic singing music in here...
    func_801A1D44(&this->actor.projectedPos, NA_BGM_CREMIA_CARRIAGE, 540.0f); // 540 is this range or speed?

    if (ABS(this->actor.yawTowardsPlayer) <= 0x4000) {
        EnMaYts2_ChooseNewText(this, play);

        func_800B8614(&this->actor, play, 120.0f); // enables talking prompt
        if (Actor_ProcessTalkRequest(&this->actor, &play->state)) {
          EnMaYts2_SetupStandingTalk(this);
        }
    }
}

void EnMaYts2_SetupSing(EnMaYts* this) {
    EnMaYts_ChangeAnim(this, 4); // singing 
    this->overrideEyeTexIndex = 2; // sing with eyes closed
    this->actionFunc = EnMaYts2_Sing;
}

// TODO rip the dialogue stuff and separate as a separate function
void EnMaYts2_SittingNew(EnMaYts* this, PlayState* play) {
    if (ABS(this->actor.yawTowardsPlayer) <= 0x4000) {
        EnMaYts2_ChooseNewText(this, play);

        if (Message_GetState(&play->msgCtx) == 5 && Message_ShouldAdvance(play)) {
            func_801477B4(play); // ends dialogue
            if (this->actor.textId == 0x296D) {this->actor.textId = 0x2A3A;}
        } else {
            func_800B8614(&this->actor, play, 120.0f); // enables talking prompt
        }
    }
}

// > 20 lines of asm for this stupid float bullshit, separate
void EnMaYts2_GenerateRandomText(EnMaYts* this, PlayState* play) {
     this->randomTextIndex = (u8)(Rand_ZeroOne() * sizeof(sRandomText));
}


void EnMaYts_Init(Actor* thisx, PlayState* play) {
    EnMaYts* this = THIS;
    //s32 pad;

    this->type = EN_MA_YTS_PARSE_TYPE(thisx);
    if (!EnMaYts_CheckValidSpawn(this, play)) {
        Actor_MarkForDeath(&this->actor);
    }

    this->typeExt = thisx->params & 0xF; // new

    ActorShape_Init(&this->actor.shape, 0.0f, ActorShadow_DrawCircle, 18.0f);
    SkelAnime_InitFlex(play, &this->skelAnime, &gRomaniSkel, NULL, this->jointTable, this->morphTable, ROMANI_LIMB_MAX);
    EnMaYts_InitAnimation(this, play);

    Collider_InitCylinder(play, &this->collider);
    Collider_SetCylinder(play, &this->collider, &this->actor, &sCylinderInit);
    CollisionCheck_SetInfo2(&this->actor.colChkInfo, DamageTable_Get(0x16), &sColChkInfoInit2);

    if (this->type == MA_YTS_TYPE_SLEEPING) {
        this->collider.dim.radius = 40;
    }

    Actor_UpdateBgCheckInfo(play, &this->actor, 0.0f, 0.0f, 0.0f, 0x4);
    Actor_SetScale(&this->actor, 0.01f);

    this->unk_1D8.unk_00 = 0;
    //this->unk_200 = 0;
    this->blinkTimer = 0;

    if (this->type == MA_YTS_TYPE_ENDCREDITS) {
        this->hasBow = true;
    } else {
        this->hasBow = false;
    }

    // ugh, this shit should be in setup funcs
    if (CURRENT_DAY == 1 || (gSaveContext.save.weekEventReg[22] & 1)) {
        this->overrideEyeTexIndex = 0;
        this->eyeTexIndex = 0;
        this->mouthTexIndex = 0;
        this->unk_32C = 0;
    } else {
        this->overrideEyeTexIndex = 1;
        this->eyeTexIndex = 1;
        this->mouthTexIndex = 2;
        this->unk_32C = 2;
    }

    if (this->type == MA_YTS_TYPE_ENDCREDITS) {
        this->overrideEyeTexIndex = 0;
        this->eyeTexIndex = 0;
        this->mouthTexIndex = 0;
        this->unk_32C = 2;
        EnMaYts_SetupEndCreditsHandler(this);
    } else if (this->type ==  MA_YTS_TYPE_SITTING && this->typeExt == MAYTS_BOX) { // new
        EnMaYts2_GenerateRandomText(this, play);
        this->actionFunc = EnMaYts2_SittingNew;
    } else if (this->type == MA_YTS_TYPE_SINGING) { // new
        EnMaYts2_GenerateRandomText(this, play);
        EnMaYts2_SetupSing(this);
    // why is this based on time and not based on type?
    } else if (CURRENT_DAY == 2 && gSaveContext.save.isNight == 1 && (gSaveContext.save.weekEventReg[22] & 1)) {
        EnMaYts_SetupStartDialogue(this);
    } else { // standing doing nothing should now have dialogue
        //EnMaYts_SetupDoNothing(this);
        //this->actionFunc = Actor_Noop;
        EnMaYts2_ChooseNewText(this, play);
        EnMaYts2_SetupStandingTalk(this);
    }
}

void EnMaYts_Destroy(Actor* thisx, PlayState* play) {
    EnMaYts* this = THIS;

    Collider_DestroyCylinder(play, &this->collider);
}

// get out of here with this stupid shit, just Noop
//void EnMaYts_SetupDoNothing(EnMaYts* this) { //this->actionFunc = EnMaYts_DoNothing; //}
//void EnMaYts_DoNothing(EnMaYts* this, PlayState* play) { //}

void EnMaYts_SetupStartDialogue(EnMaYts* this) {
    EnMaYts_SetFaceExpression(this, 0, 0);
    this->actionFunc = EnMaYts_StartDialogue;
}

void EnMaYts_StartDialogue(EnMaYts* this, PlayState* play) {
    s16 sp26 = this->actor.shape.rot.y - this->actor.yawTowardsPlayer;

    if (Actor_ProcessTalkRequest(&this->actor, &play->state)) {
        if (!(gSaveContext.save.playerForm == PLAYER_FORM_HUMAN)) {
            if (!(gSaveContext.save.weekEventReg[65] & 0x80)) {
                // Saying to non-human Link: "Cremia went to town."
                gSaveContext.save.weekEventReg[65] |= 0x80;
                EnMaYts_SetFaceExpression(this, 0, 0);
                Message_StartTextbox(play, 0x335F, &this->actor);
                this->textId = 0x335F;
            } else {
                // Saying to non-human Link: "Pretend you did not hear that."
                EnMaYts_SetFaceExpression(this, 4, 3);
                Message_StartTextbox(play, 0x3362, &this->actor);
                this->textId = 0x3362;
                func_80151BB4(play, 5);
            }
        } else if (Player_GetMask(play) != PLAYER_MASK_NONE) {
            if (!(gSaveContext.save.weekEventReg[65] & 0x40)) {
                gSaveContext.save.weekEventReg[65] |= 0x40;
                EnMaYts_SetFaceExpression(this, 0, 0);
                Message_StartTextbox(play, 0x3363, &this->actor);
                this->textId = 0x3363;
            } else {
                EnMaYts_SetFaceExpression(this, 4, 2);
                Message_StartTextbox(play, 0x3366, &this->actor);
                this->textId = 0x3366;
                func_80151BB4(play, 5);
            }
        } else if (!(gSaveContext.save.weekEventReg[21] & 0x20)) {
            EnMaYts_SetFaceExpression(this, 0, 0);
            Message_StartTextbox(play, 0x3367, &this->actor);
            this->textId = 0x3367;
        } else {
            if (!(gSaveContext.save.weekEventReg[65] & 0x20)) {
                // Saying to Grasshopper: "Cremia went to town."
                gSaveContext.save.weekEventReg[65] |= 0x20;
                EnMaYts_SetFaceExpression(this, 4, 2);
                Message_StartTextbox(play, 0x3369, &this->actor);
                this->textId = 0x3369;
            } else {
                // Saying to Grasshopper: "You're our bodyguard."
                EnMaYts_SetFaceExpression(this, 0, 0);
                Message_StartTextbox(play, 0x336C, &this->actor);
                this->textId = 0x336C;
                func_80151BB4(play, 5);
            }
        }
        EnMaYts_SetupDialogueHandler(this);
    } else if (ABS_ALT(sp26) < 0x4000) {
        func_800B8614(&this->actor, play, 120.0f);
    }
}

void EnMaYts_SetupDialogueHandler(EnMaYts* this) {
    this->actionFunc = EnMaYts_DialogueHandler;
}

void EnMaYts_DialogueHandler(EnMaYts* this, PlayState* play) {
    switch (Message_GetState(&play->msgCtx)) {
        case TEXT_STATE_5: // End message block
            EnMaYts_ChooseNextDialogue(this, play);
            break;

        case TEXT_STATE_DONE: // End conversation
            if (Message_ShouldAdvance(play)) {
                EnMaYts_SetupStartDialogue(this);
            }
            break;

        case TEXT_STATE_NONE:
        case TEXT_STATE_1:
        case TEXT_STATE_CLOSING:
        case TEXT_STATE_3:
        case TEXT_STATE_CHOICE:
            break;
    }
}

// new functions for sitting dialogue
// actually... nvm all the dialgoue options suck or are depressing
/*

void EnMaYts2_StartDialogue(EnMaYts* this, PlayState* play);
void EnMaYts2_DialogueHandler(EnMaYts* this, PlayState* play);
void EnMaYts2_SetupDialogueHandler(EnMaYts* this);

void EnMaYts2_SetupStartDialogue(EnMaYts* this) {
    //EnMaYts_SetFaceExpression(this, 0, 0);
    this->actionFunc = EnMaYts2_StartDialogue;
}

void EnMaYts2_StartDialogue(EnMaYts* this, PlayState* play) {
    s16 sp26 = this->actor.shape.rot.y - this->actor.yawTowardsPlayer;

    if (Actor_ProcessTalkRequest(&this->actor, &play->state)) {
        if (!(gSaveContext.save.playerForm == PLAYER_FORM_HUMAN)) {
            if (!(gSaveContext.save.weekEventReg[65] & 0x80)) {
                // Saying to non-human Link: "Cremia went to town."
                gSaveContext.save.weekEventReg[65] |= 0x80;
                EnMaYts_SetFaceExpression(this, 0, 0);
                Message_StartTextbox(play, 0x335F, &this->actor);
                this->textId = 0x335F;
            } else {
                // Saying to non-human Link: "Pretend you did not hear that."
                EnMaYts_SetFaceExpression(this, 4, 3);
                Message_StartTextbox(play, 0x3362, &this->actor);
                this->textId = 0x3362;
                func_80151BB4(play, 5);
            }
        } else if (Player_GetMask(play) != PLAYER_MASK_NONE) {
            if (!(gSaveContext.save.weekEventReg[65] & 0x40)) {
                gSaveContext.save.weekEventReg[65] |= 0x40;
                EnMaYts_SetFaceExpression(this, 0, 0);
                Message_StartTextbox(play, 0x3363, &this->actor);
                this->textId = 0x3363;
            } else {
                EnMaYts_SetFaceExpression(this, 4, 2);
                Message_StartTextbox(play, 0x3366, &this->actor);
                this->textId = 0x3366;
                func_80151BB4(play, 5);
            }
        } else if (!(gSaveContext.save.weekEventReg[21] & 0x20)) {
            EnMaYts_SetFaceExpression(this, 0, 0);
            Message_StartTextbox(play, 0x3367, &this->actor);
            this->textId = 0x3367;
        } else {
            if (!(gSaveContext.save.weekEventReg[65] & 0x20)) {
                // Saying to Grasshopper: "Cremia went to town."
                gSaveContext.save.weekEventReg[65] |= 0x20;
                EnMaYts_SetFaceExpression(this, 4, 2);
                Message_StartTextbox(play, 0x3369, &this->actor);
                this->textId = 0x3369;
            } else {
                // Saying to Grasshopper: "You're our bodyguard."
                EnMaYts_SetFaceExpression(this, 0, 0);
                Message_StartTextbox(play, 0x336C, &this->actor);
                this->textId = 0x336C;
                func_80151BB4(play, 5);
            }
        }
        EnMaYts2_SetupDialogueHandler(this);
    } else if (ABS_ALT(sp26) < 0x4000) {
        func_800B8614(&this->actor, play, 120.0f);
    }
}

// Select the following dialogue based on the current one, and an appropiate face expression
void EnMaYts2_ChooseNextDialogue(EnMaYts* this, PlayState* play) {
    if (Message_ShouldAdvance(play)) {
        switch (this->textId) {
            // 0x3358: // ... who are you again?
            // 0x333E: // They are coming...
            // 0x336F: They.. they come at night every year when the carnival approaches...
            // 0x3358: // 
            //case 0x335F:
                //EnMaYts_SetFaceExpression(this, 0, 2);
                //Message_StartTextbox(play, 0x3360, &this->actor);
                //this->textId = 0x3360;
                //break;

            //case 0x3360:
                //EnMaYts_SetFaceExpression(this, 4, 3);
                //Message_StartTextbox(play, 0x3361, &this->actor);
                //this->textId = 0x3361;
                //func_80151BB4(play, 5);
                //break;

            //case 0x3363:
                //EnMaYts_SetFaceExpression(this, 1, 1);
                //Message_StartTextbox(play, 0x3364, &this->actor);
                //this->textId = 0x3364;
                //break;

            //case 0x3364:
                //EnMaYts_SetFaceExpression(this, 4, 2);
                //Message_StartTextbox(play, 0x3365, &this->actor);
                //this->textId = 0x3365;
                //func_80151BB4(play, 5);
                //break;

            //case 0x3367:
                //EnMaYts_SetFaceExpression(this, 4, 3);
                //Message_StartTextbox(play, 0x3368, &this->actor);
                //this->textId = 0x3368;
                //func_80151BB4(play, 5);
                //break;

            //case 0x3369:
                //EnMaYts_SetFaceExpression(this, 0, 0);
                //Message_StartTextbox(play, 0x336A, &this->actor);
                //this->textId = 0x336A;
                //break;

            //case 0x336A:
                //EnMaYts_SetFaceExpression(this, 3, 3);
                //Message_StartTextbox(play, 0x336B, &this->actor);
                //this->textId = 0x336B;
                //func_80151BB4(play, 5);
                //break;

            default:
                break;
        }
    }
}

*/

void EnMaYts_SetupEndCreditsHandler(EnMaYts* this) {
    this->actor.flags |= ACTOR_FLAG_10;
    EnMaYts_SetFaceExpression(this, 0, 0);
    this->actionFunc = EnMaYts_EndCreditsHandler;
}

static u16 D_80B8E32C = 99;
void EnMaYts_EndCreditsHandler(EnMaYts* this, PlayState* play) {
    if (Cutscene_CheckActorAction(play, 120)) {
        s32 actionIndex = Cutscene_GetActorActionIndex(play, 120);

        if (play->csCtx.frames == play->csCtx.actorActions[actionIndex]->startFrame) {
            if (play->csCtx.actorActions[actionIndex]->action != D_80B8E32C) {
                D_80B8E32C = play->csCtx.actorActions[actionIndex]->action;
                this->endCreditsFlag = 0;
                switch (play->csCtx.actorActions[actionIndex]->action) {
                    case 1:
                        this->hasBow = true;
                        EnMaYts_ChangeAnim(this, 0);
                        break;

                    case 2:
                        this->hasBow = false;
                        EnMaYts_ChangeAnim(this, 2);
                        break;

                    case 3:
                        this->hasBow = true;
                        EnMaYts_ChangeAnim(this, 12);
                        break;

                    case 4:
                        this->hasBow = true;
                        EnMaYts_ChangeAnim(this, 20);
                        break;
                }
            }
        }

        Cutscene_ActorTranslateAndYaw(&this->actor, play, actionIndex);
        if ((D_80B8E32C == 2) && (this->endCreditsFlag == 0) &&
            Animation_OnFrame(&this->skelAnime, this->skelAnime.endFrame)) {
            this->endCreditsFlag++;
            EnMaYts_ChangeAnim(this, 5);
        }
    } else {
        D_80B8E32C = 99;
        this->hasBow = true;
    }
}

// Select the following dialogue based on the current one, and an appropiate face expression
void EnMaYts_ChooseNextDialogue(EnMaYts* this, PlayState* play) {
    if (Message_ShouldAdvance(play)) {
        switch (this->textId) {
            case 0x335F:
                EnMaYts_SetFaceExpression(this, 0, 2);
                Message_StartTextbox(play, 0x3360, &this->actor);
                this->textId = 0x3360;
                break;

            case 0x3360:
                EnMaYts_SetFaceExpression(this, 4, 3);
                Message_StartTextbox(play, 0x3361, &this->actor);
                this->textId = 0x3361;
                func_80151BB4(play, 5);
                break;

            case 0x3363:
                EnMaYts_SetFaceExpression(this, 1, 1);
                Message_StartTextbox(play, 0x3364, &this->actor);
                this->textId = 0x3364;
                break;

            case 0x3364:
                EnMaYts_SetFaceExpression(this, 4, 2);
                Message_StartTextbox(play, 0x3365, &this->actor);
                this->textId = 0x3365;
                func_80151BB4(play, 5);
                break;

            case 0x3367:
                EnMaYts_SetFaceExpression(this, 4, 3);
                Message_StartTextbox(play, 0x3368, &this->actor);
                this->textId = 0x3368;
                func_80151BB4(play, 5);
                break;

            case 0x3369:
                EnMaYts_SetFaceExpression(this, 0, 0);
                Message_StartTextbox(play, 0x336A, &this->actor);
                this->textId = 0x336A;
                break;

            case 0x336A:
                EnMaYts_SetFaceExpression(this, 3, 3);
                Message_StartTextbox(play, 0x336B, &this->actor);
                this->textId = 0x336B;
                func_80151BB4(play, 5);
                break;

            default:
                break;
        }
    }
}

void EnMaYts_SetFaceExpression(EnMaYts* this, s16 overrideEyeTexIndex, s16 mouthTexIndex) {
    this->overrideEyeTexIndex = overrideEyeTexIndex;
    this->mouthTexIndex = mouthTexIndex;
    if (this->overrideEyeTexIndex == 0) {
        this->eyeTexIndex = 0;
    }
}

void EnMaYts_Update(Actor* thisx, PlayState* play) {
    EnMaYts* this = THIS;
    ColliderCylinder* collider;

    this->actionFunc(this, play);
    collider = &this->collider;
    Collider_UpdateCylinder(&this->actor, collider);
    CollisionCheck_SetOC(play, &play->colChkCtx, &collider->base);
    SkelAnime_Update(&this->skelAnime);
    EnMaYts_UpdateEyes(this);
    func_80B8D12C(this, play);
}

s32 EnMaYts_OverrideLimbDraw(PlayState* play, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, Actor* thisx) {
    EnMaYts* this = THIS;
    Vec3s sp4;

    if (this->actionFunc != EnMaYts2_Sing){
      if (limbIndex == ROMANI_LIMB_HEAD) {
          sp4 = this->unk_1D8.unk_08;
          rot->x += sp4.y;
          if ((this->skelAnime.animation == &gRomaniIdleAnim) || (this->skelAnime.animation == &gRomaniSittingAnim)) {
              rot->z += sp4.x;
          }
      } else if (limbIndex == ROMANI_LIMB_TORSO) {
          sp4 = this->unk_1D8.unk_0E;
          rot->x += sp4.y;
          rot->z += sp4.x;
      }
    }

    return false;
}

void EnMaYts_PostLimbDraw(PlayState* play, s32 limbIndex, Gfx** dList, Vec3s* rot, Actor* thisx) {
    EnMaYts* this = THIS;

    if (limbIndex == ROMANI_LIMB_HEAD) {
        Matrix_MultZero(&this->actor.focus.pos);
    } else if (limbIndex == ROMANI_LIMB_LEFT_HAND) {
        if (this->hasBow == true) {
            OPEN_DISPS(play->state.gfxCtx);
            gSPDisplayList(POLY_OPA_DISP++, gRomaniBowDL);
            CLOSE_DISPS(play->state.gfxCtx);
        }
    }
}

void EnMaYts_Draw(Actor* thisx, PlayState* play) {
    EnMaYts* this = THIS;

    OPEN_DISPS(play->state.gfxCtx);
    // ripped from EnMa4, returnt to box
    if (this->type == MA_YTS_TYPE_SITTING && this->typeExt == MAYTS_BOX) {
        gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gSPDisplayList(POLY_OPA_DISP++, gRomaniWoodenBoxDL);
    }

    func_8012C28C(play->state.gfxCtx);

    gSPSegment(POLY_OPA_DISP++, 0x09, SEGMENTED_TO_VIRTUAL(sMouthTextures[this->mouthTexIndex]));
    gSPSegment(POLY_OPA_DISP++, 0x08, SEGMENTED_TO_VIRTUAL(sEyeTextures[this->eyeTexIndex]));

    SkelAnime_DrawFlexOpa(play, this->skelAnime.skeleton, this->skelAnime.jointTable, this->skelAnime.dListCount,
                          EnMaYts_OverrideLimbDraw, EnMaYts_PostLimbDraw, &this->actor);

    CLOSE_DISPS(play->state.gfxCtx);
}

// Alternative draw function for sleeping
void EnMaYts_DrawSleeping(Actor* thisx, PlayState* play) {
    OPEN_DISPS(play->state.gfxCtx);
    func_8012C28C(play->state.gfxCtx);

    gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(POLY_OPA_DISP++, gRomaniSleepingDL);

    CLOSE_DISPS(play->state.gfxCtx);
}
