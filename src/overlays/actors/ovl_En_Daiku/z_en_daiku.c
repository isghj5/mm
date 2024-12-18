/*
 * File: z_en_daiku.c
 * Overlay: ovl_En_Daiku
 * Description: Carpenter
 */

#include "z_en_daiku.h"

#define FLAGS (ACTOR_FLAG_TARGETABLE | ACTOR_FLAG_FRIENDLY)

#define THIS ((EnDaiku*)thisx)

void EnDaiku_Init(Actor* thisx, PlayState* play);
void EnDaiku_Destroy(Actor* thisx, PlayState* play);
void EnDaiku_Update(Actor* thisx, PlayState* play);
void EnDaiku_Draw(Actor* thisx, PlayState* play);
void Debug_PrintToScreen(Actor* thisx, PlayState* play);

void EnDaiku_InitPart2(EnDaiku* this);
void func_80943BC0(EnDaiku* this);
void func_80943BDC(EnDaiku* this, PlayState* play);
void func_809438F8(EnDaiku* this, PlayState* play);

ActorInit En_Daiku_InitVars = {
    /**/ ACTOR_EN_DAIKU,
    /**/ ACTORCAT_NPC,
    /**/ FLAGS,
    /**/ OBJECT_DAIKU,
    /**/ sizeof(EnDaiku),
    /**/ EnDaiku_Init,
    /**/ EnDaiku_Destroy,
    /**/ EnDaiku_Update,
    /**/ EnDaiku_Draw,
};

// ugh
static u16 sTextIds[] = {
 0x061C, 0x061A, 0x061B,
 0x061C, 0x061C, 0x061D,
 0x061E, 0x061F, 0x061C,
 0x0620, 0x0621, 0x0622,
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
        { 0xF7CFFFFF, 0x00, 0x00 },
        TOUCH_NONE | TOUCH_SFX_NORMAL,
        BUMP_NONE,
        OCELEM_ON,
    },
    { 20, 60, 0, { 0, 0, 0 } },
};

typedef enum {
    /* -1 */ ENDAIKU_ANIM_NONE = -1,
    /*  0 */ ENDAIKU_ANIM_0,
    /*  1 */ ENDAIKU_ANIM_1,
    /*  2 */ ENDAIKU_ANIM_2,
    /*  3 */ ENDAIKU_ANIM_3,
    /*  4 */ ENDAIKU_ANIM_4,
    /*  5 */ ENDAIKU_ANIM_5,
    /*  6 */ ENDAIKU_ANIM_6,
    /*  7 */ ENDAIKU_ANIM_7,
    /*  8 */ ENDAIKU_ANIM_8,
    /*  9 */ ENDAIKU_ANIM_MAX
} EnDaiAnimation;

static AnimationHeader* sAnimations[ENDAIKU_ANIM_MAX] = {
    &object_daiku_Anim_002FA0, // ENDAIKU_ANIM_0 // smug and making faces
    &object_daiku_Anim_00ACD0, // ENDAIKU_ANIM_1 // staring straight ahead
    &object_daiku_Anim_00C92C, // ENDAIKU_ANIM_2 // celebrating
    &object_daiku_Anim_000C44, // ENDAIKU_ANIM_3 // galavanting run
    &object_daiku_Anim_00C234, // ENDAIKU_ANIM_4 // fetal position from OOT gerudo fortress
    &object_daiku_Anim_000600, // ENDAIKU_ANIM_5 // sweat on head from OOT
    &object_daiku_Anim_001114, // ENDAIKU_ANIM_6 // walking with lumber over shoulder
    &object_daiku_Anim_00B690, // ENDAIKU_ANIM_7 // shouting up at seth
    &object_daiku_Anim_00BEAC, // ENDAIKU_ANIM_8 // waving up at seth
};
// exists in object missing from this list: pickaxe animations

static u8 sAnimationModes[ENDAIKU_ANIM_MAX] = {
    ANIMMODE_LOOP, // ENDAIKU_ANIM_0
    ANIMMODE_LOOP, // ENDAIKU_ANIM_1
    ANIMMODE_LOOP, // ENDAIKU_ANIM_2
    ANIMMODE_LOOP, // ENDAIKU_ANIM_3
    ANIMMODE_ONCE, // ENDAIKU_ANIM_4
    ANIMMODE_LOOP, // ENDAIKU_ANIM_5
    ANIMMODE_LOOP, // ENDAIKU_ANIM_6
    ANIMMODE_ONCE, // ENDAIKU_ANIM_7
    ANIMMODE_ONCE, // ENDAIKU_ANIM_8
};

void EnDaiku_Init(Actor* thisx, PlayState* play) {
    EnDaiku* this = THIS;

    this->actor.colChkInfo.mass = MASS_IMMOVABLE;
    ActorShape_Init(&this->actor.shape, 0.0f, ActorShadow_DrawCircle, 40.0f);
    this->actor.targetMode = TARGET_MODE_0;
    Collider_InitAndSetCylinder(play, &this->collider, &this->actor, &sCylinderInit);
    this->type = ENDAIKU_GET_TYPE(&this->actor);
    if (this->type == DAIKU_TYPE_WALKING) {
        this->pathIndex = ENDAIKU_GET_PATH_INDEX(&this->actor);
        this->path = SubS_GetPathByIndex(play, this->pathIndex, ENDAIKU_PATH_INDEX_NONE);
    } else if (this->type == DAIKU_TYPE_SHOUTING_WAVING) {
        this->unk_264 = -2000;
    }

    if (this->type == DAIKU_TYPE_MAYOR_MEETING) {
        this->collider.dim.radius = 30;
        this->collider.dim.height = 60;
        this->collider.dim.yShift = 0;
        this->actor.flags |= ACTOR_FLAG_CANT_LOCK_ON;
        if (CHECK_WEEKEVENTREG(WEEKEVENTREG_63_80) || ((gSaveContext.save.day == 3) && gSaveContext.save.isNight)) {
            Actor_Kill(&this->actor);
        }
    } else if ((gSaveContext.save.day == 3) && this->type <= 3 && gSaveContext.save.isNight) {
        Actor_Kill(&this->actor);
    }

    this->randomChoice = Rand_Next() % 4;

    Math_Vec3f_Copy(&this->pathNextPointPos, &this->actor.world.pos);
    this->unusedYaw280 = this->actor.world.rot.y;
    this->actor.gravity = -3.0f;

    Actor_SetFocus(&this->actor, 65.0f);
    switch (this->type) {
        case DAIKU_TYPE_MAYOR_MEETING:
            this->mayorOfficeSkeletonUpdateTimer = this->type * 4 + 4; // (0) + 4

        case DAIKU_TYPE_POSTER_READING:
            SkelAnime_InitFlex(play, &this->skelAnime, &object_daiku_Skel_00A850, &object_daiku_Anim_002FA0,
                               this->jointTable, this->morphTable, OBJECT_DAIKU_LIMB_MAX);
            break;

        case DAIKU_TYPE_SHOUTING_WAVING:
            SkelAnime_InitFlex(play, &this->skelAnime, &object_daiku_Skel_00A850, &object_daiku_Anim_00B690,
                               this->jointTable, this->morphTable, OBJECT_DAIKU_LIMB_MAX);
            break;

        case DAIKU_TYPE_WALKING:
            SkelAnime_InitFlex(play, &this->skelAnime, &object_daiku_Skel_00A850, &object_daiku_Anim_001114,
                               this->jointTable, this->morphTable, OBJECT_DAIKU_LIMB_MAX);
            break;
        //case 4: exists in actor draw but not here..? migt be bug
        case 5: // happy
            SkelAnime_InitFlex(play, &this->skelAnime, &object_daiku_Skel_00A850, &object_daiku_Anim_00C92C,
                               this->jointTable, this->morphTable, OBJECT_DAIKU_LIMB_MAX);
            EnDaiku2_SetIdle(this);
            return;
        case 6: // sad
            SkelAnime_InitFlex(play, &this->skelAnime, &object_daiku_Skel_00A850, &object_daiku_Anim_00C234,
                               this->jointTable, this->morphTable, OBJECT_DAIKU_LIMB_MAX);
            Actor_SetFocus(&this->actor, 25.0f);
            EnDaiku2_SetIdle(this);
            return;
    }

    // our new types should have random pants colors
    if (this->type >= 5){
        // this is bad because of all the float conversions
        //u32 protoColor = thisx->home.pos.x + thisx->home.pos.y + thisx->home.pos.z;// + thisx->home.rot.y;
        // smaller but still too much float
        //u32 protoColor = (u16)thisx->home.pos.x + ((u16)thisx->home.pos.y) + (u16)thisx->home.pos.z;// + thisx->home.rot.y;
        //this->RandomPantsColor.seededInt = Rand_Next_Variable(protoColor);

        // yes its a float but its just a random value we want thats different than the other actors
        // almost no actors should have the same X cords, even they did it's different in series
        // this saves SOOO MUCH code, like 0x200 bytes of instruction and no coprocessor use
        // then we save to union so we dont have to care about all the shifting nonsense
        this->RandomPantsColor.seededInt = Rand_Next_Variable(&thisx->home.pos.x);
    }

    // why set the animation above when we get reset in next function?
    EnDaiku_InitPart2(this);
}

void EnDaiku_Destroy(Actor* thisx, PlayState* play) {
    EnDaiku* this = THIS;

    Collider_DestroyCylinder(play, &this->collider);
}

void EnDaiku_ChangeAnim(EnDaiku* this, s32 animIndex) {
    this->animEndFrame = Animation_GetLastFrame(sAnimations[animIndex]);
    Animation_Change(&this->skelAnime, sAnimations[animIndex], 1.0f, 0.0f, this->animEndFrame,
                     sAnimationModes[animIndex], -4.0f);
}

// check if actor has reached end of path and kill? is there even a version where one walks out of SCT?
void func_809437C8(EnDaiku* this) {
    if ((this->pathIndex != PATH_INDEX_NONE) && (this->path != NULL)) {
        if (!SubS_CopyPointFromPath(this->path, this->pathPointIndex, &this->pathNextPointPos)) {
            Actor_Kill(&this->actor);
        }
    }
}

EnDaiku2_Idle(EnDaiku* this, PlayState* play){
  if (Player_GetMask(play) == PLAYER_MASK_KAFEIS_MASK) {
      this->actor.textId = 0x2365;
  }
  if (Actor_TalkOfferAccepted(&this->actor, &play->state)) {
      func_80943BC0(this);
      return;
  }
}

EnDaiku2_SetIdle(EnDaiku* this){
    this->unk_28C = Rand_Next() % ARRAY_COUNT(sTextIds);
    this->actor.textId = sTextIds[this->unk_28C];
    this->unusedYaw280 = this->actor.shape.rot.y;
    this->unusedBool28A = false;
    this->actionFunc = func_809438F8;
}

// set actionfunc
void EnDaiku_InitPart2(EnDaiku* this) {
    s32 day = gSaveContext.save.day - 1;

    switch (this->type) {
        case 0: // @ BUG: type zero has no skeleton
        case 1:
            EnDaiku_ChangeAnim(this, ENDAIKU_ANIM_0);
            break;

        case 2:
            EnDaiku_ChangeAnim(this, ENDAIKU_ANIM_7);
            break;

        case 3:
            EnDaiku_ChangeAnim(this, ENDAIKU_ANIM_6);
            break;

        default:
            break;
    }

    this->unk_28C = (day * 4) + this->type;
    this->actor.textId = sTextIds[this->unk_28C];
    this->unusedYaw280 = this->actor.shape.rot.y;
    this->unusedBool28A = false;
    if (this->type <= 4){
      this->actionFunc = func_809438F8;
    } else {
      this->actionFunc = EnDaiku2_Idle; 
    }
}

void func_809438F8(EnDaiku* this, PlayState* play) {
    f32 curFrame = this->skelAnime.curFrame;
    s32 pad;
    s32 day = gSaveContext.save.day - 1;
    s32 pad2;

    if (Player_GetMask(play) == PLAYER_MASK_KAFEIS_MASK) {
        if (this->type == DAIKU_TYPE_POSTER_READING) {
            this->actor.textId = 0x2365;
        } else {
            this->actor.textId = 0x2366;
        }
    } else {
        this->unk_28C = (day * 4) + this->type;
        this->actor.textId = sTextIds[this->unk_28C];
    }

    if (Actor_TalkOfferAccepted(&this->actor, &play->state)) {
        func_80943BC0(this);
        return;
    }


    if ((this->type == DAIKU_TYPE_SHOUTING_WAVING) && (curFrame >= this->animEndFrame)) {
        if (Rand_ZeroOne() < 0.5f) {
            EnDaiku_ChangeAnim(this, ENDAIKU_ANIM_7);
        } else {
            EnDaiku_ChangeAnim(this, ENDAIKU_ANIM_8);
        }
    }

    if (this->type == DAIKU_TYPE_WALKING) {
        f32 xzDist;
        f32 yawDiff;

        Math_ApproachF(&this->actor.world.pos.x, this->pathNextPointPos.x, 0.5f,
                       fabsf(2.0f * Math_SinS(this->actor.world.rot.y)));
        Math_ApproachF(&this->actor.world.pos.z, this->pathNextPointPos.z, 0.5f,
                       fabsf(2.0f * Math_CosS(this->actor.world.rot.y)));
        Math_SmoothStepToS(&this->actor.world.rot.y, this->yawToNextPathPoint, 1, 0x7D0, 0xA);

        xzDist = sqrtf(SQ(this->actor.world.pos.x - this->pathNextPointPos.x) + SQ(this->actor.world.pos.z - this->pathNextPointPos.z));
        yawDiff = fabsf(this->actor.world.rot.y - this->yawToNextPathPoint);
        if ((xzDist < 4.0f) && (this->path != NULL) && (yawDiff < 10.0f)) {
            this->pathPointIndex++;
            if (this->pathPointIndex >= this->path->count) {
                this->pathPointIndex = 0;
            }

            func_809437C8(this);
            this->yawToNextPathPoint = Math_Vec3f_Yaw(&this->actor.world.pos, &this->pathNextPointPos);
        }
    }

    if (this->type != DAIKU_TYPE_MAYOR_MEETING) {
        s16 angle = ABS_ALT(BINANG_SUB(this->actor.yawTowardsPlayer, this->actor.world.rot.y));

        this->unusedYaw280 = this->actor.yawTowardsPlayer;
        if ((this->type == DAIKU_TYPE_POSTER_READING) || (this->type == DAIKU_TYPE_SHOUTING_WAVING) || (angle <= 0x2890)) {
            Actor_OfferTalk(&this->actor, play, 100.0f);
        }
    }
}

// setup talk
void func_80943BC0(EnDaiku* this) {
    this->unusedBool28A = true;
    this->actionFunc = func_80943BDC;
}

// talk
void func_80943BDC(EnDaiku* this, PlayState* play) {
    f32 curFrame = this->skelAnime.curFrame;

    if ((this->type == DAIKU_TYPE_SHOUTING_WAVING) && (curFrame >= this->animEndFrame)) {
        if (Rand_ZeroOne() < 0.5f) {
            EnDaiku_ChangeAnim(this, ENDAIKU_ANIM_7);
        } else {
            EnDaiku_ChangeAnim(this, ENDAIKU_ANIM_8);
        }
    }

    if ((Message_GetState(&play->msgCtx) == TEXT_STATE_EVENT) && Message_ShouldAdvance(play)) {
        Message_CloseTextbox(play);
        EnDaiku_InitPart2(this);
    }
}

void EnDaiku_Update(Actor* thisx, PlayState* play) {
    EnDaiku* this = THIS;
    //s32 pad;

    if (this->skelAnime.update.normal == NULL){
        // for reasons I can't figure out, their skeleton can break, if this happens they should print error instead of crash
        //this->actionFunc = Actor_Noop;
        thisx->update = Actor_Noop;
        thisx->draw = Debug_PrintToScreen;
        return;   
    }  

    // this timer is only set with type==0, but that type has no skeleton
    if (this->mayorOfficeSkeletonUpdateTimer == 0) {
        SkelAnime_Update(&this->skelAnime);
    }

    if ((this->type == DAIKU_TYPE_MAYOR_MEETING) && (gSaveContext.save.day == 3) && (gSaveContext.save.isNight)) {
        Actor_Kill(&this->actor);
        return;
    }

    this->actionFunc(this, play);

    DECR(this->unusedTimer27C);
    DECR(this->mayorOfficeSkeletonUpdateTimer);

    Actor_SetScale(&this->actor, 0.01f);
    this->actor.shape.rot.y = this->actor.world.rot.y;
    //Actor_SetFocus(&this->actor, 65.0f);
    Actor_MoveWithGravity(&this->actor);
    Math_SmoothStepToS(&this->unk_260, this->unk_266, 1, 0xBB8, 0); // limb rotations for the pickaxe?
    Math_SmoothStepToS(&this->unk_25E, this->unk_264, 1, 0xBB8, 0);
    Actor_UpdateBgCheckInfo(play, &this->actor, 20.0f, 20.0f, 50.0f,
                            UPDBGCHECKINFO_FLAG_1 | UPDBGCHECKINFO_FLAG_4 | UPDBGCHECKINFO_FLAG_8 |
                                UPDBGCHECKINFO_FLAG_10);
    this->actor.uncullZoneForward = 650.0f;
    Collider_UpdateCylinder(&this->actor, &this->collider);
    CollisionCheck_SetOC(play, &play->colChkCtx, &this->collider.base);
}

s32 EnDaiku_OverrideLimbDraw(PlayState* play, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, Actor* thisx) {
    EnDaiku* this = THIS;

    if (limbIndex == OBJECT_DAIKU_LIMB_0F) {
        rot->x += this->unk_260;
        rot->z += this->unk_25E;
    }

    return false;
}

void EnDaiku_PostLimbDraw(PlayState* play, s32 limbIndex, Gfx** dList, Vec3s* rot, Actor* thisx) {
    // different hair styles
    static Gfx* sDaikuHairGfx[] = {
        object_daiku_DL_0070C0,
        object_daiku_DL_006FB0,
        object_daiku_DL_006E80,
        object_daiku_DL_006D70,
    };
    EnDaiku* this = THIS;

    OPEN_DISPS(play->state.gfxCtx);

    if (limbIndex == OBJECT_DAIKU_LIMB_0F) { // hair
        if (this->type <= 3){
          gSPDisplayList(POLY_OPA_DISP++, sDaikuHairGfx[this->type]);
        } else{
          gSPDisplayList(POLY_OPA_DISP++, sDaikuHairGfx[this->randomChoice]);

        }
    }

    // wooden log
    if ((this->type == DAIKU_TYPE_WALKING) && (limbIndex == OBJECT_DAIKU_LIMB_08)) {
        gSPDisplayList(POLY_OPA_DISP++, object_daiku_DL_008EC8);
    }

    CLOSE_DISPS(play->state.gfxCtx);
}

void EnDaiku_Draw(Actor* thisx, PlayState* play) {
    EnDaiku* this = THIS;

    OPEN_DISPS(play->state.gfxCtx);

    Gfx_SetupDL25_Opa(play->state.gfxCtx);

    // envcolor is his pants color
    switch (this->type) {
        case 0:
            gDPSetEnvColor(POLY_OPA_DISP++, 170, 10, 70, 255);
            break;

        case 1:
            gDPSetEnvColor(POLY_OPA_DISP++, 170, 200, 255, 255);
            break;

        case 2:
            gDPSetEnvColor(POLY_OPA_DISP++, 0, 230, 70, 255);
            break;

        case 3:
            gDPSetEnvColor(POLY_OPA_DISP++, 200, 0, 150, 255);
            break;

        case 4: // this type doesn't exist in vanilla
            gDPSetEnvColor(POLY_OPA_DISP++, 200, 0, 0, 255);
            break;

        default: // our new types
            gDPSetEnvColor(POLY_OPA_DISP++, 
                    this->RandomPantsColor.color.r,
                    this->RandomPantsColor.color.g,
                    this->RandomPantsColor.color.b , 255);
            break;
    }

    SkelAnime_DrawFlexOpa(play, this->skelAnime.skeleton, this->skelAnime.jointTable, this->skelAnime.dListCount,
                          EnDaiku_OverrideLimbDraw, EnDaiku_PostLimbDraw, &this->actor);

    CLOSE_DISPS(play->state.gfxCtx);
}

void Debug_PrintToScreen(Actor* thisx, PlayState* play) {
    EnDaiku* this = THIS; // replace with THIS actor
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
    GfxPrint_Printf(&printer, "Daiku skeleton broken, report to isghj");
    GfxPrint_SetPos(&printer, 1, 13);
    GfxPrint_Printf(&printer, "actor struct loc: %X", &thisx);

    // end of text printing
    gfx = GfxPrint_Close(&printer);
    GfxPrint_Destroy(&printer);

    gSPEndDisplayList(gfx++);
    // make the opa dlist jump over the part that will be executed as part of overlay
    gSPBranchList(POLY_OPA_DISP, gfx);
    POLY_OPA_DISP = gfx;

    CLOSE_DISPS(play->state.gfxCtx);
    //if (BREG(86)) 
    //  Debug_PrintToScreen(thisx, play); // put this in your actors draw func
} // */

