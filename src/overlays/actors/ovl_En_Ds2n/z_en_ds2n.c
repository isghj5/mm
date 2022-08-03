/*
 * File: z_en_ds2n.c
 * Overlay: ovl_En_Ds2n
 * Description: Potion Shop Owner from OoT (unused)
 *
 *   This actor was placed in the Staff Office of Stockpot inn
 *   but does not spawn because their object is missing.
 */

#include "z_en_ds2n.h"

#define FLAGS (ACTOR_FLAG_1 | ACTOR_FLAG_8 | ACTOR_FLAG_10 | ACTOR_FLAG_2000000)

#define THIS ((EnDs2n*)thisx)

void EnDs2n_Init(Actor* thisx, PlayState* play);
void EnDs2n_Destroy(Actor* thisx, PlayState* play);
void EnDs2n_Update(Actor* thisx, PlayState* play);
void EnDs2n_Draw(Actor* thisx, PlayState* play);

void EnDs2n_Idle(EnDs2n* this, PlayState* play);

const ActorInit En_Ds2n_InitVars = {
    ACTOR_EN_DS2N,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_DS2N,
    sizeof(EnDs2n),
    (ActorFunc)EnDs2n_Init,
    (ActorFunc)EnDs2n_Destroy,
    (ActorFunc)EnDs2n_Update,
    (ActorFunc)EnDs2n_Draw,
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

static AnimationInfo sAnimations[] = {
    { &gDs2nIdleAnim, 1.0f, 0.0f, 0.0f, ANIMMODE_LOOP, 0.0f },
};

static Vec3f sZeroVec = { 0, 0, 0 };

static TexturePtr sEyeTextures[] = { gDs2nEyeOpenTex, gDs2nEyeHalfTex, gDs2nEyeClosedTex };

void EnDs2n_SetupIdle(EnDs2n* this) {
    this->blinkTimer = 20;
    this->blinkState = 0;
    Actor_ChangeAnimationByInfo(&this->skelAnime, sAnimations, 0);
    this->actionFunc = EnDs2n_Idle;
}


void EnDs2n2_ChooseText(EnDs2n* this, PlayState* play) {
    // wish I had more situational dialgoue
  if (gSaveContext.save.playerForm == PLAYER_FORM_ZORA ){
    this->actor.textId = 0x12D4; // AH mikau! wecome!
  } else if (gSaveContext.save.playerForm == PLAYER_FORM_DEKU){ 
    this->actor.textId = 0x06C6; // hey you are just some deku thing
  } else if (gSaveContext.save.playerForm == PLAYER_FORM_GORON){ 
    this->actor.textId = 0x0D6B; // yo darmani man
  } else if (gSaveContext.save.playerForm == PLAYER_FORM_FIERCE_DEITY){ 
    this->actor.textId = 0x06C2; // wow coolio man
  //} else if (Player_GetMask(play) != PLAYER_MASK_NONE){ 
    //this->actor.textId = 0x233F; // oh you found a cute mask
  //} else if (Object_GetIndex(&play->objectCtx, GAMEPLAY_DANGEON_KEEP) != -1) {
    //this->actor.textId = 0x208;  // eeevil
  //} else if (CURRENT_DAY == 1 && 
    //(gSaveContext.save.weekEventReg[21] & 0x20 || CHECK_QUEST_ITEM(QUEST_SONG_EPONA))) {
    //this->actor.textId = 0x3348; // don't be late tonight
  } else { //random text
    this->actor.textId = 0x06C7; // ...
  }
  //this->actor.textId = 0x13F6; // testing
  //this->actor.textId = sRandomText[this->randomTextIndex];
}

void EnDs2n2_Dialogue(EnDs2n* this, PlayState* play) {
    u8 msgState = Message_GetState(&play->msgCtx);
    u8 shouldAdvance = Message_ShouldAdvance(play);

    if (shouldAdvance) {
      if (msgState == 5 || msgState == 6) {
        if (this->actor.textId == 0x12D4 || this->actor.textId == 0x06C6 
          || this->actor.textId == 0x0D6B|| this->actor.textId == 0x06C2 ) { // good to sell
          Message_StartTextbox(play, 0x2B5D, &this->actor);
          this->actor.textId = 0x2B5D; // would you like to try?

        } else { // regular dialogue is one shot, end after whatever it was previously
          func_801477B4(play); // ends dialogue
          this->actionFunc = EnDs2n_Idle;
        }
      }else if ( msgState == TEXT_STATE_CHOICE ){
        // choosing to buy milk or not
        if (play->msgCtx.choiceIndex == 0) { // yes
          if (!Inventory_HasEmptyBottle()){ // if player has no empty bottle
            this->actor.textId = 0x6DB;
            Message_StartTextbox(play, 0x6DB, &this->actor);

          } else if (gSaveContext.save.playerData.rupees < 150) { // not enough rup
            this->actor.textId = 0x6DA;
            Message_StartTextbox(play, 0x6DA, &this->actor);
          } else { // sale
            Rupees_ChangeBy(-150);
            func_801477B4(play); // ends dialogue
            Actor_PickUp(&this->actor, play, GI_POTION_BLUE, 500.0f, 100.0f);
            this->actionFunc = EnDs2n_Idle;
          }
        } else { // no
          Message_StartTextbox(play, 0x12E7, &this->actor);
          this->actor.textId = 0x12E7; // take care
        }
      }
    }

}

void EnDs2n_Idle(EnDs2n* this, PlayState* play) {
  SubS_FillLimbRotTables(play, this->limbRotTableY, this->limbRotTableZ, DS2N_LIMB_MAX);

  // new
  // we want him to sell us his potions
  // 12D0 welcome little guy
  // 12D2 welcome.
  // 2b5d: well? Ill buy it, no
  // 1632: one for 150! 1634 for 100
  // 12d4 ah mikau! welcome
  // 6C7 ....
  // 2A3A: I am not sus

  if ( this->actor.xzDistToPlayer < 100.0f && ABS(this->actor.yawTowardsPlayer) <= 0x4000) {
    Player* player = GET_PLAYER(play);

    // attempt dialogue with player
    if (Actor_ProcessTalkRequest(&this->actor, &play->state)) {
        this->actionFunc = EnDs2n2_Dialogue;

    }else if (!(player->stateFlags1 & 0x800000)){
        EnDs2n2_ChooseText(this, play);
        func_800B8614(&this->actor, play, 120.0f); // enables talking prompt
    }

  } else { // not close enough
    //this->overrideEyeTexIndex = 0;
    //this->mouthTexIndex = 0;
  }

}

void EnDs2n_UpdateEyes(EnDs2n* this) {
    s16 nextBlinkTime = this->blinkTimer - 1;

    if (nextBlinkTime >= 3) {
        this->blinkState = 0;
        this->blinkTimer = nextBlinkTime;
    } else if (nextBlinkTime == 0) {
        this->blinkState = 2;
        this->blinkTimer = (s32)(Rand_ZeroOne() * 60.0f) + 20;
    } else {
        this->blinkState = 1;
        this->blinkTimer = nextBlinkTime;
    }
}

void EnDs2n_Init(Actor* thisx, PlayState* play) {
    EnDs2n* this = THIS;

    ActorShape_Init(&this->actor.shape, 0.0f, ActorShadow_DrawCircle, 20.0f);
    SkelAnime_InitFlex(play, &this->skelAnime, &gDs2nSkeleton, &gDs2nIdleAnim, NULL, NULL, 0);

    Collider_InitAndSetCylinder(play, &this->collider, &this->actor, &sCylinderInit);
    this->actor.colChkInfo.mass = MASS_IMMOVABLE;


    EnDs2n_SetupIdle(this);
}

void EnDs2n_Destroy(Actor* thisx, PlayState* play) {
    EnDs2n* this = THIS;

    SkelAnime_Free(&this->skelAnime, play);

    Collider_DestroyCylinder(play, &this->collider);

}

void EnDs2n_Update(Actor* thisx, PlayState* play) {
    EnDs2n* this = THIS;

    this->actionFunc(this, play);
    Actor_MoveWithGravity(&this->actor);
    SkelAnime_Update(&this->skelAnime);

    Collider_UpdateCylinder(&this->actor, &this->collider);
    CollisionCheck_SetOC(play, &play->colChkCtx, &this->collider.base);

    // better chest and head smoothing taken from ani
    if ( this->actor.xzDistToPlayer < 200.0f) {
        Actor_TrackPlayer(play, &this->actor, &this->headRot, &this->chestRot, this->actor.focus.pos);
    } else if (this->actor.xzDistToPlayer < 500.0f)  {
        Math_SmoothStepToS(&this->headRot.x, 0, 0x6, 0x1838, 0x64);
        Math_SmoothStepToS(&this->headRot.y, 0, 0x6, 0x1838, 0x64);
        Math_SmoothStepToS(&this->chestRot.x, 0, 0x6, 0x1838, 0x64);
        Math_SmoothStepToS(&this->chestRot.y, 0, 0x6, 0x1838, 0x64);
    }

    EnDs2n_UpdateEyes(this);
}

s32 EnDs2n_OverrideLimbDraw(PlayState* play, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, Actor* thisx) {
    EnDs2n* this = THIS;

    if (limbIndex == DS2N_LIMB_HEAD) {
        //Matrix_RotateXS(this->headRot.y, MTXMODE_APPLY);
        rot->x += this->headRot.y; // replacement taken from ani, works fine
        rot->z += this->headRot.x;

    }
    if (limbIndex == DS2N_LIMB_TORSO){
        rot->x += this->chestRot.y;
        rot->z += this->chestRot.x;
    }

    return false;
}

void EnDs2n_PostLimbDraw(PlayState* play, s32 limbIndex, Gfx** dList, Vec3s* rot, Actor* thisx) {
    EnDs2n* this = THIS;
    Vec3f focusOffset = sZeroVec;

    if ((limbIndex == DS2N_LIMB_HIPS) || (limbIndex == DS2N_LIMB_LEFT_UPPER_ARM) ||
        (limbIndex == DS2N_LIMB_RIGHT_UPPER_ARM)) {
        rot->y += (s16)Math_SinS(this->limbRotTableY[limbIndex]) * 0xC8;
        rot->z += (s16)Math_CosS(this->limbRotTableZ[limbIndex]) * 0xC8;
    }

    if (limbIndex == DS2N_LIMB_HEAD) {
        Matrix_MultVec3f(&focusOffset, &thisx->focus.pos);
    }
}

void EnDs2n_Draw(Actor* thisx, PlayState* play) {
    EnDs2n* this = THIS;

    OPEN_DISPS(play->state.gfxCtx);

    func_8012C5B0(play->state.gfxCtx);
    gSPSegment(POLY_OPA_DISP++, 0x08, Lib_SegmentedToVirtual(sEyeTextures[this->blinkState]));

    gSPSegment(POLY_OPA_DISP++, 0x09, Lib_SegmentedToVirtual(sEyeTextures[this->blinkState]));

    SkelAnime_DrawFlexOpa(play, this->skelAnime.skeleton, this->skelAnime.jointTable, this->skelAnime.dListCount,
                          EnDs2n_OverrideLimbDraw, EnDs2n_PostLimbDraw, &this->actor);

    CLOSE_DISPS(play->state.gfxCtx);
}
