/*
 * File: z_en_sth2.c
 * Overlay: ovl_En_Sth2
 * Description: Guy waving at the telescope in Termina Field
 */

#include "z_en_sth2.h"

#define FLAGS (ACTOR_FLAG_1 | ACTOR_FLAG_8)

#define THIS ((EnSth2*)thisx)

void EnSth2_Init(Actor* thisx, PlayState* play);
void EnSth2_Destroy(Actor* thisx, PlayState* play);
void EnSth2_Update(Actor* thisx, PlayState* play);
void EnSth2_Draw(Actor* thisx, PlayState* play2);

void EnSth2_IdleWaving(EnSth2* this, PlayState* play);
void EnSth2_IdleStanding(EnSth2* this, PlayState* play);
//void EnSth2_UpdateActionFunc(Actor* thisx, PlayState* play);

ActorInit En_Sth2_InitVars = {
    ACTOR_EN_STH2,
    ACTORCAT_NPC,
    FLAGS,
    //GAMEPLAY_KEEP,
    OBJECT_STH,
    sizeof(EnSth2),
    (ActorFunc)EnSth2_Init,
    (ActorFunc)EnSth2_Destroy,
    (ActorFunc)EnSth2_Update,
    (ActorFunc)EnSth2_Draw,
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

// head data 
#include "overlays/ovl_En_Sth2/ovl_En_Sth2.c"

void EnSth2_Init(Actor* thisx, PlayState* play) {
    EnSth2* this = THIS;
    AnimationHeader* anim;
    u8 type;

    //this->objIndex = Object_GetIndex(&play->objectCtx, OBJECT_STH);
    Actor_SetScale(&this->actor, 0.01f);
    ActorShape_Init(&this->actor.shape, 0.0f, ActorShadow_DrawCircle, 36.0f);
    //this->unused = 0;

    Collider_InitAndSetCylinder(play, &this->collider, &this->actor, &sCylinderInit);

    if (play->actorCtx.flags & ACTORCTX_FLAG_1) {
        this->actor.flags |= (ACTOR_FLAG_10 | ACTOR_FLAG_20);
    //} else {
        //Actor_Kill(&this->actor);
        //return;
    }

    type = STH2_GET_TYPE(thisx);
    if (CURRENT_DAY == 3 && type > 0){
      type = 2;
    }

    switch (type){
      case 0:
        anim = &gEnSth2WavingHandAnim;
        this->actionFunc = EnSth2_IdleWaving;
      break;
      case 1:
        anim = &gEnSth2WaitAnim;
        this->actionFunc = EnSth2_IdleStanding;

      break;
      case 2:
        anim = &gEnSth2PanicAnim;
        this->actionFunc = EnSth2_IdleWaving;

      break;
      default:

        anim = &gEnSth2WavingHandAnim;
        this->actionFunc = EnSth2_IdleWaving;
      break;
    }
    //EnSth2_Update(thisx, play);
    //SkelAnime_InitFlex(play, &this->skelAnime, &gSthSkel, &gEnSth2WavingHandAnim, this->jointTable,
                       //this->morphTable, STH_LIMB_MAX);
    SkelAnime_InitFlex(play, &this->skelAnime, &gSthSkel, anim, this->jointTable,
                       this->morphTable, STH_LIMB_MAX);
    Animation_PlayLoop(&this->skelAnime, anim);
    //Animation_Change(&this->skelAnime, anim, 0.0, 0, 4,
                    //1, 0);

}

void EnSth2_Destroy(Actor* thisx, PlayState* play) {
}

void EnSth2_IdleWaving(EnSth2* this, PlayState* play) {
    SkelAnime_Update(&this->skelAnime);
}

void EnSth2_IdleStanding(EnSth2* this, PlayState* play) {
    SkelAnime_Update(&this->skelAnime);
    {
      Actor_TrackPlayer(play, &this->actor, &this->headRot, &this->torsoRot, this->actor.focus.pos);
    }
}

//void EnSth2_Update(Actor* thisx, PlayState* play) {
    //s32 pad;
    //EnSth2* this = THIS;

    //if (Object_IsLoaded(&play->objectCtx, this->objIndex)) {
        //this->actor.objBankIndex = this->objIndex;
        //Actor_SetObjectDependency(play, &this->actor);
        //SkelAnime_InitFlex(play, &this->skelAnime, &gSthSkel, &gEnSth2WavingHandAnim, this->jointTable,
                           //this->morphTable, STH_LIMB_MAX);
        //Animation_PlayLoop(&this->skelAnime, &gEnSth2WavingHandAnim);
        //this->actor.update = EnSth2_UpdateActionFunc;
        //this->actor.draw = EnSth2_Draw;
    //}
//}

void EnSth2_Update(Actor* thisx, PlayState* play) {
    EnSth2* this = THIS;

    Collider_UpdateCylinder(&this->actor, &this->collider);
    CollisionCheck_SetOC(play, &play->colChkCtx, &this->collider.base);


    this->actionFunc(this, play);
}

s32 EnSth2_OverrideLimbDraw(PlayState* play, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, Actor* thisx) {
    //s32 pad;
    EnSth2* this = THIS;

    if (limbIndex == STH_LIMB_HEAD) {
        *dList = gEnSth2HeadDL;
        rot->x += this->headRot.y;
        rot->z += this->headRot.x;

    }
    if (limbIndex == STH_LIMB_CHEST){
        rot->x += this->torsoRot.y;
        rot->z += this->torsoRot.x;
    }

    // minor breathing animation changes
    // /*
    if ( STH2_GET_TYPE(thisx) == 1 ||
        (limbIndex == STH_LIMB_CHEST) || (limbIndex == STH_LIMB_LEFT_FOREARM) ||
        (limbIndex == STH_LIMB_RIGHT_FOREARM)) {
        rot->y += (s16)(Math_SinS((play->state.frames * ((limbIndex * 50) + 0x814))) * 200.0f);
        rot->z += (s16)(Math_CosS((play->state.frames * ((limbIndex * 50) + 0x940))) * 200.0f);
        //rot->y += (s16)(Math_SinS((play->state.frames * ((limbIndex * 50) + 0x814))) * DEG_TO_BINANG(20));
        //rot->z += (s16)(Math_CosS((play->state.frames * ((limbIndex * 50) + 0x940))) * DEG_TO_BINANG(20));
        //rot->y += 0x1000;
        //rot->z +=  0x1000;
    }
    // */
    return false;
}

void EnSth2_PostLimbDraw(PlayState* play, s32 limbIndex, Gfx** dList, Vec3s* rot, Actor* thisx) {
    static Vec3f focusOffset = { 700.0f, 400.0f, 0.0f };

    if (limbIndex == STH_LIMB_HEAD) {
        Matrix_MultVec3f(&focusOffset, &thisx->focus.pos);

        OPEN_DISPS(play->state.gfxCtx);

        if (STH2_GET_BALD(thisx) == false){
          gSPDisplayList(POLY_OPA_DISP++, gEnSth2HairDL);
        }

        CLOSE_DISPS(play->state.gfxCtx);
    }
}

void EnSth2_Draw(Actor* thisx, PlayState* play) {
    // orange, green, bright green, bright orange, 0-5
    // dull white, yellow
    static Color_RGB8 shirtColors[] = {
        { 190, 110, 0 }, { 0, 180, 110 }, { 0, 255, 80 }, { 255, 160, 60 },
        { 190, 230, 250 }, { 240, 230, 120 },
    };
    //PlayState* play = play2;
    EnSth2* this = THIS;
    u8 color = STH2_GET_COLOR(thisx);

    OPEN_DISPS(play->state.gfxCtx);

    Gfx_SetupDL25_Opa(play->state.gfxCtx);
    gSPSegment(POLY_OPA_DISP++, 0x08,
               //Gfx_EnvColor(play->state.gfxCtx, shirtColors[1].r, shirtColors[1].g, shirtColors[1].b, 255));
               Gfx_EnvColor(play->state.gfxCtx, shirtColors[color].r, shirtColors[color].g, shirtColors[color].b, 255));
    gSPSegment(POLY_OPA_DISP++, 0x09, Gfx_EnvColor(play->state.gfxCtx, 90, 110, 130, 255));
    SkelAnime_DrawFlexOpa(play, this->skelAnime.skeleton, this->skelAnime.jointTable, this->skelAnime.dListCount,
                          EnSth2_OverrideLimbDraw, EnSth2_PostLimbDraw, &this->actor);

    CLOSE_DISPS(play->state.gfxCtx);
}
