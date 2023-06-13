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

// almost half of these are completely unused, only one odd value is used at all
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
    gRomaniMouthHappyTex, gRomaniMouthFrownTex, gRomaniMouthHangingOpenTex, gRomaniMouthSmileTex,
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
void EnMaYts2_SittingNew(EnMaYts* this, PlayState* play);
void EnMaYts2_SittingTalkNew(EnMaYts* this, PlayState* play);
void EnMaYts2_StandingTalk(EnMaYts* this, PlayState* play);

// seems its safest to make sure that when talking you can only take care of talking, do not merge this logic into another actionfunc withoutjank
// BUG: if we try to close this with regular dialogue we get stuck in a state that isnt zero, its fine so long as you dont pull out the ocarina
void EnMaYts2_Talking(EnMaYts* this, PlayState* play){
  s16 talkState = Message_GetState(&play->msgCtx);

  if(EN_MA_YTS2_DIALOGUE_WATCHDOG(this)++ == (30 * 20)){
    func_801477B4(play); // ends dialogue
    //Message_CloseTextbox(play); 
    //play->
    this->actionFunc = EnMaYts2_StandingTalk;
  }

  if (Message_ShouldAdvance(play)){
    func_801477B4(play); // ends dialogue
    //Message_CloseTextbox(play);
    this->actionFunc = EnMaYts2_StandingTalk;
  }

}


// TODO FIX THIS
void EnMaYts2_StandingTalk(EnMaYts* this, PlayState* play) {

    // TODO this is a hotfix, not sure how we get here but we can get in dialogue and be in this function which is bad
    if (Message_GetState(&play->msgCtx) != 0) func_801477B4(play); // ends dialogue

    //if(this->actor.xzDistToPlayer > 20.0f){
    if(this->actor.xzDistToPlayer > 100.0f){
        if (this->type == MA_YTS_TYPE_SINGING){
          // player has left, go back to singing
          // TODO figure out how to animate it smoother since she sorta starts doing it instantly
          EnMaYts2_SetupSing(this);
        }else { // just standing normally
          // why is this here? why is this not somewhere else??
          if (CURRENT_DAY == 1) {
            this->overrideEyeTexIndex = false;
          } else {
            // her half eye is kinda half-asleep sleepwalky
            this->overrideEyeTexIndex = true; // force half eye
          }
        }
    }//} else if (Message_GetState(&play->msgCtx) == 5 && Message_ShouldAdvance(play)) {
        //func_801477B4(play); // ends dialogue
        //if (this->actor.textId == 0x296D) {this->randomTextIndex = 1;}
    /*
    } else if (Actor_ProcessTalkRequest(&this->actor, &play->state)) {
        EN_MA_YTS2_DIALOGUE_WATCHDOG(this) =  0;
        this->actionFunc = EnMaYts2_Talking;
    } else {
        // waiting for dialogue prompt and close by
        EnMaYts2_ChooseNewText(this, play);
        func_800B8614(&this->actor, play, 120.0f); // enables talking prompt
        
    } // */
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
  //if (true){  // testing romani status
  if ( CURRENT_DAY > 1 && (this->type == MA_YTS_TYPE_SITTING && this->typeExt == MAYTS_BOX)
    //  if day > 1 and saved aliens and sitting on a crate, milk selling/giving dialogue
    && gSaveContext.save.weekEventReg[22] & 1)  // saved romani
    { 
      if (ROMANI_GET_NEWEVENT) { // previous customer
        this->actor.textId = 0x278E;
      } else { // new customer 
        if (gSaveContext.save.playerForm == PLAYER_FORM_HUMAN ){
          this->actor.textId = 0x3367; // thanks for last night
        } else {
          this->actor.textId = 0x3395; // explaining chatou
        }
      }
    
  } else if (gSaveContext.save.playerForm != PLAYER_FORM_HUMAN) {
    this->actor.textId = 0x3336; // cute foreigner
  } else if (Player_GetMask(play) != PLAYER_MASK_NONE){ 
    this->actor.textId = 0x233F; // oh you found a cute mask
  } else if (Object_GetIndex(&play->objectCtx, GAMEPLAY_DANGEON_KEEP) != -1) {
    this->actor.textId = 0x208;  // eeevil
  } else if (CURRENT_DAY == 1 && 
    (gSaveContext.save.weekEventReg[21] & 0x20 || CHECK_QUEST_ITEM(QUEST_SONG_EPONA))) {
    this->actor.textId = 0x3348; // don't be late tonight
  } else { //random text
    this->actor.textId = sRandomText[this->randomTextIndex];
  }
  //this->actor.textId = 0x13F6; // testing
  //this->actor.textId = sRandomText[this->randomTextIndex];

}

void EnMaYts2_Singing(EnMaYts* this, PlayState* play) {
    // ripped from GuruGuru, because his proxmity music isn't jank like EnYb
    // using carriage music because if she shows up in romani ranch its just weird to hear ranch music ontop of ranch music
    // wish I could include a basic singing music in here...
    //func_801A1D44(&this->actor.projectedPos, NA_BGM_CREMIA_CARRIAGE, 540.0f); // 
    func_801A1D44(&this->actor.projectedPos, NA_BGM_CREMIA_CARRIAGE, 2000.0f); // value is range

    if (this->actor.xzDistToPlayer < 200 && ABS(this->actor.yawTowardsPlayer) <= 0x4000) {
        EnMaYts2_ChooseNewText(this, play);

        /*
        if (Actor_ProcessTalkRequest(&this->actor, &play->state)) {
          //EnMaYts2_SetupStandingTalk(this);
          EnMaYts_ChangeAnim(this, 0); // change anim to standing
          this->overrideEyeTexIndex = 0; // regular blinking eyes 
          this->actionFunc = EnMaYts2_Talking;

        } else {
          func_800B8614(&this->actor, play, 120.0f); // enables talking prompt for next frame

        } // */
    }
}

void EnMaYts2_SetupSing(EnMaYts* this) {
    EnMaYts_ChangeAnim(this, 4); // singing 
    this->overrideEyeTexIndex = 2; // sing with eyes closed
    this->actionFunc = EnMaYts2_Singing;
}


void EnMaYts2_SittingTalkNew(EnMaYts* this, PlayState* play) {
    u8 msgState = Message_GetState(&play->msgCtx); // dont know why vanilla does this first, might be a state reset thing
    u8 shouldAdvance = Message_ShouldAdvance(play);

    if(EN_MA_YTS2_DIALOGUE_WATCHDOG(this)++ == (30 * 20)){
      func_801477B4(play); // ends dialogue
      this->actionFunc = EnMaYts2_SittingNew;
    }
    // if player succeded in helping sisters, they should sell or give milk/chatou
    // 3395: explaining what chatou is
    // 278E will you try?
    // 0c82: will you give it a try?
    // 3356 is try again?
    // 12E4 you dont have an empty bottle to put it in
    if (shouldAdvance) {
      if (msgState == 5 || msgState == 6) {
        // bug: for some reason I cannot chain these two toegether so I made them separate for different races
        // it would just never leave middle chain onto the last dialogue... dont know why
        if (this->actor.textId == 0x3395 || this->actor.textId == 0x3367) { // explaining milk
          Message_StartTextbox(play, 0x0C82, &this->actor);
          this->actor.textId = 0x0C82; // would you like to try?
        //} else if (this->actor.textId == 0x3367) { // thanking link for helping
          //Message_StartTextbox(play, 0x3395, &this->actor);
          //this->actor.textId = 0x3395; // explaining milk

        } else { // regular dialogue is one shot, end after whatever it was previously
          func_801477B4(play); // ends dialogue
          this->actionFunc = EnMaYts2_SittingNew;
          // force mouth back to smile

          // be extra suspicious
          if (this->actor.textId == 0x296D) {this->randomTextIndex = 3;}
        }
      }else if ( msgState == TEXT_STATE_CHOICE ){
        // choosing to buy milk or not
        //switch (this->textId){ // except we should only have the on choice
        if (play->msgCtx.choiceIndex == 0) { // yes
          if (Inventory_HasEmptyBottle()){ // if player has bottle
            ROMANI_SET_NEWEVENT;
            func_801477B4(play); // ends dialogue
            this->overrideEyeTexIndex = 3;
            Actor_PickUp(&this->actor, play, GI_CHATEAU, 500.0f, 100.0f);
            this->actionFunc = EnMaYts2_SittingNew;

          } else { // no bottle to use
            this->actor.textId = 0x12E4;
            Message_StartTextbox(play, 0x12E4, &this->actor);
            this->overrideEyeTexIndex = 0;
            this->mouthTexIndex = 1;
          }
        } else { // no
          Message_StartTextbox(play, 0x12E7, &this->actor);
          this->actor.textId = 0x12E7; // take care
        }
      }
    }
}


// TODO rip the dialogue stuff and separate as a separate function
void EnMaYts2_SittingNew(EnMaYts* this, PlayState* play) {
  if ( this->actor.xzDistToPlayer < 100.0f && ABS(this->actor.yawTowardsPlayer) <= 0x4000) {
    Player* player = GET_PLAYER(play);

    if (Actor_ProcessTalkRequest(&this->actor, &play->state)) {
        this->actionFunc = EnMaYts2_SittingTalkNew;

    }else if (!(player->stateFlags1 & 0x800000)){
        EnMaYts2_ChooseNewText(this, play);
        func_800B8614(&this->actor, play, 120.0f); // enables talking prompt
    }

  } else { // not close enough
    this->overrideEyeTexIndex = 0;
    this->mouthTexIndex = 0;

  }
}

// over A0 lines of asm for this float asm, separate because IDO wont reuse
void EnMaYts2_GenerateRandomText(EnMaYts* this, PlayState* play) {
     this->randomTextIndex = (u8)(Rand_ZeroOne() * sizeof(sRandomText));
}

void EnMaYts_Kill(Actor* thisx){
    Actor_MarkForDeath(thisx);
    thisx->update = NULL;
    thisx->draw = NULL;
}

void EnMaYts_Init(Actor* thisx, PlayState* play) {
    EnMaYts* this = THIS;
    bool aliensWon = false;
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
    // YOU EVEN MADE A FACE CHANGE FUNC oh mah god
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

    aliensWon = CURRENT_DAY > 1 && ! (gSaveContext.save.weekEventReg[22] & 1);

    if (this->type == MA_YTS_TYPE_ENDCREDITS) {
        this->overrideEyeTexIndex = 0;
        this->eyeTexIndex = 0;
        this->mouthTexIndex = 0;
        this->unk_32C = 2;
        EnMaYts_SetupEndCreditsHandler(this);
    } else if (this->type ==  MA_YTS_TYPE_SITTING && this->typeExt == MAYTS_BOX) { // new
        if ( aliensWon )
        {
          //Actor_MarkForDeath(&this);
          EnMaYts_Kill(thisx);
        }
        EnMaYts2_GenerateRandomText(this, play);
        this->actionFunc = EnMaYts2_SittingNew;
    } else if (this->type == MA_YTS_TYPE_SINGING) { // new
        if ( aliensWon )
        {
          //Actor_MarkForDeath(&this);
          EnMaYts_Kill(thisx);
        }
        EnMaYts2_GenerateRandomText(this, play);
        EnMaYts2_SetupSing(this);
    // why is this based on time and not based on type?
    } else if (CURRENT_DAY == 2 && gSaveContext.save.isNight == 1 && (gSaveContext.save.weekEventReg[22] & 1)) {
        EnMaYts_SetupStartDialogue(this);
    } else if (this->type == MA_YTS_TYPE_SLEEPING) {
        if ( aliensWon )
        {
          //Actor_MarkForDeath(&this);
          EnMaYts_Kill(thisx);
        }
        this->actionFunc = Actor_Noop;

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

// get out of here with this stupid shit, just Noop if you want to do nothing
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

    if (this->actionFunc != EnMaYts2_Singing){ // shes distracted by singing to notice you
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

///*
void Debug_PrintToScreen(Actor* thisx, PlayState* play) {
    EnMaYts* this = THIS;
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
        //GfxPrint_Printf(&printer, "func %X", &EnPoSisters_CheckCollision);
        GfxPrint_Printf(&printer, "actionfunc vram:        func_%X", convertedAddr);
        GfxPrint_SetPos(&printer, 1, 12);
        GfxPrint_Printf(&printer, "actionfunc actual ram:  %X", this->actionFunc);
    }

    GfxPrint_SetPos(&printer, 1, 14);
    
    //GfxPrint_Printf(&printer, "drawflags %X", this->drawFlags);
    //GfxPrint_Printf(&printer, "BREG86 %X", BREG(86));
    GfxPrint_Printf(&printer, "mesgState  %X", Message_GetState(&play->msgCtx));
    GfxPrint_SetPos(&printer, 1, 15);
    GfxPrint_Printf(&printer, "timer %hd", EN_MA_YTS2_DIALOGUE_WATCHDOG(this));

    // end of text printing
    gfx = GfxPrint_Close(&printer);
    GfxPrint_Destroy(&printer);

    gSPEndDisplayList(gfx++);
    // make the opa dlist jump over the part that will be executed as part of overlay
    gSPBranchList(POLY_OPA_DISP, gfx);
    POLY_OPA_DISP = gfx;

    CLOSE_DISPS(play->state.gfxCtx);
    //Debug_PrintToScreen(thisx, play);
} // */


void EnMaYts_Draw(Actor* thisx, PlayState* play) {
    EnMaYts* this = THIS;
    //Debug_PrintToScreen(thisx, play);

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
