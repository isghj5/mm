/*
 * File: z_en_cne_01.c
 * Overlay: ovl_En_Cne_01
 * Description: Unused Market NPC
 */

#include "z_en_cne_01.h"
#include "objects/object_cne/object_cne.h"

#define FLAGS (ACTOR_FLAG_1 | ACTOR_FLAG_8 | ACTOR_FLAG_10)

#define THIS ((EnCne01*)thisx)

void EnCne01_Init(Actor* thisx, PlayState* play);
void EnCne01_Destroy(Actor* thisx, PlayState* play);
void EnCne01_Update(Actor* thisx, PlayState* play);
void EnCne01_Draw(Actor* thisx, PlayState* play);

void EnCne01_Walk(EnCne01* this, PlayState* play);
void EnCne01_FaceForward(EnCne01* this, PlayState* play);
void EnCne01_Talk(EnCne01* this, PlayState* play);

ActorInit En_Cne_01_InitVars = {
    ACTOR_EN_CNE_01,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_CNE,
    sizeof(EnCne01),
    (ActorFunc)EnCne01_Init,
    (ActorFunc)EnCne01_Destroy,
    (ActorFunc)EnCne01_Update,
    (ActorFunc)EnCne01_Draw,
};

// her collider was supposed to take hits from the player??? nah that looks weird
static ColliderCylinderInit sCylinderInit = {
    {
        COLTYPE_NONE, // changed
        AT_NONE,
        AC_ON | AC_TYPE_ENEMY, // changed
        OC1_ON | OC1_TYPE_ALL,
        OC2_TYPE_1,
        COLSHAPE_CYLINDER,
    },
    {
        ELEMTYPE_UNK0, // changed
        { 0x00000000, 0x00, 0x00 },
        { 0xF7CFFFFF, 0x00, 0x00 },
        TOUCH_NONE | TOUCH_SFX_NORMAL,
        BUMP_ON,
        OCELEM_ON,
    },
    { 18, 64, 0, { 0, 0, 0 } },
};

static CollisionCheckInfoInit2 sColChkInfoInit = { 0, 0, 0, 0, MASS_IMMOVABLE };

// why did the dev leave this instead of using the blank ones...
/*
static DamageTable sDamageTable = {
}; // */

static TrackOptionsSet sTrackOptions = {
    { 0xFA0, 4, 1, 3 },
    { 0x1770, 4, 1, 6 },
    { 0xFA0, 4, 1, 3 },
    { 0x1770, 4, 1, 6 },
};

// end vanilla data

#include "new_animations.c"

// is actor on screen, attempt to accept beans
s32 EnCne01_AttemptItemRecieve(EnCne01* this, PlayState* play) {
    s16 x;
    s16 y;

    Actor_GetScreenPos(play, &this->actor, &x, &y);
    //! @bug: Both x and y conditionals are always true, || should be an &&
    if (((x >= 0) && (x < SCREEN_WIDTH)) && ((y >= 0) && (y < SCREEN_HEIGHT))) {
        // what if you give vampire girl fish and she gives you a blood potion?
        // or you give her red potion and you get a poe?
        //func_800B85E0(&this->actor, play, 30.0f, PLAYER_IA_MAGIC_BEANS);
        func_800B85E0(&this->actor, play, 30.0f, PLAYER_IA_MOON_TEAR); // think -1 is all
    }
    return true;
}

void EnCne02_TestGiftItem(EnCne01* this, PlayState* play){
    Player* player = GET_PLAYER(play);
    s16 playerType = CNE_GET_TYPE(&this->actor);
    PlayerItemAction itemAction = func_80123810(play);

    // trying to make this code work from En_Akindonuts, the only actor used in the game that can just accept an item without the prompt
    if (itemAction > PLAYER_IA_NONE && playerType == CNE_TYPE_VENESA) {
        
        //if (itemAction == PLAYER_IA_BOTTLE_POTION_RED) {
        if (itemAction == PLAYER_IA_PICTO_BOX) {
            player->exchangeItemId = itemAction; // what does this doooooo
            this->textId = 0x221B;
        }
        else{ // wrong item
            this->textId = 0x2220;
        }
    } else  if (itemAction > PLAYER_IA_NONE && playerType == CNE_TYPE_ORANGE) {
        //if (itemAction == PLAYER_IA_PENDANT_OF_MEMORIES) {
        if (itemAction == PLAYER_IA_PICTO_BOX) {
            player->exchangeItemId = itemAction; // what does this doooooo
            this->textId = 0x221B;

        }
        else{ // wrong item
            this->textId = 0x2220;
        }

    }
    Message_StartTextbox(play, this->textId, NULL);

}

void EnCne02_SetAnimation(EnCne01* this, AnimationHeader* anim){
    this->curAnim = anim;

    Animation_Change(&this->skelAnime, anim, 1.0f, 0.0f, 0.0f, ANIMMODE_LOOP, 1.0f);
}

void EnCne01_UpdateModel(EnCne01* this, PlayState* play) {
    Vec3f point;
    int talkingDist = (CNE_GET_TYPE(&this->actor) == CNE_TYPE_VENESA) ? 90: 200;
    
    //EnHy_UpdateSkelAnime(&this->enHy, play);
    SkelAnime_Update(&this->skelAnime);

    this->stateFlags &= ~2;
    
    if (this->actor.xzDistToPlayer < talkingDist && 
      SubS_AngleDiffLessEqual(this->actor.shape.rot.y, 0x36B0, this->actor.yawTowardsPlayer)) {
        Player* player = GET_PLAYER(play);
        point.x = player->actor.world.pos.x;
        point.y = player->bodyPartsPos[PLAYER_BODYPART_HEAD].y + 3.0f;
        point.z = player->actor.world.pos.z;
        SubS_TrackPoint(&point, &this->actor.focus.pos, &this->actor.shape.rot, &this->trackTarget,
                        &this->headRot, &this->torsoRot, &sTrackOptions);

        // does player have cucco?
        if (CNE_GET_TYPE(&this->actor) == CNE_TYPE_VENESA 
            && player->heldActor != NULL && player->heldActor->id == ACTOR_EN_NIW){
          this->stateFlags |= 2;
        }

    } else if (this->moonPtr != NULL) { // look at the moon
        point.x = this->moonPtr->world.pos.x;
        point.y = this->moonPtr->world.pos.y;
        point.z = this->moonPtr->world.pos.z;
        SubS_TrackPoint(&point, &this->actor.focus.pos, &this->actor.shape.rot, &this->trackTarget,
                        &this->headRot, &this->torsoRot, &sTrackOptions);
    } else {
        Math_SmoothStepToS(&this->trackTarget.x, 0, 4, 0x3E8, 1);
        Math_SmoothStepToS(&this->trackTarget.y, 0, 4, 0x3E8, 1);
        Math_SmoothStepToS(&this->headRot.x, 0, 4, 0x3E8, 1);
        Math_SmoothStepToS(&this->headRot.y, 0, 4, 0x3E8, 1);
        Math_SmoothStepToS(&this->torsoRot.x, 0, 4, 0x3E8, 1);
        Math_SmoothStepToS(&this->torsoRot.y, 0, 4, 0x3E8, 1);
    }

    if ((this->stateFlags & 2) && this->curAnim != &gCneAnjuMyChickenHaveEscapedAnim){
        EnCne02_SetAnimation(this,  &gCneAnjuMyChickenHaveEscapedAnim);
    } else if (!(this->stateFlags & 2) && this->curAnim == &gCneAnjuMyChickenHaveEscapedAnim){
        EnCne02_SetAnimation(this,  &this->defaultAnim);
    }

    SubS_FillLimbRotTables(play, this->limbRotTableY, this->limbRotTableZ, ARRAY_COUNT(this->limbRotTableY));

    //EnHy_UpdateCollider(&this->enHy, play);
    this->collider.dim.pos.x = this->actor.world.pos.x;
    this->collider.dim.pos.y = this->actor.world.pos.y;
    this->collider.dim.pos.z = this->actor.world.pos.z;
    
    CollisionCheck_SetAC(play, &play->colChkCtx, &this->collider.base);
    CollisionCheck_SetOC(play, &play->colChkCtx, &this->collider.base);

}

// no longer double object, don't need this shit
/*
void EnCne01_FinishInit(EnHy* this, PlayState* play) {
} // */

// disabled for now because we need to completely rebuild the path system and also have pathing variants as an mmra option
void EnCne01_Walk(EnCne01* this, PlayState* play) {
    //if (EnHy_MoveForwards(this, 1.0f)) {
        //this->curPoint = 0;
    //}
}

void EnCne02_SetupFaceForward(EnCne01* this){
    if (this->moonPtr != NULL && (this->stateFlags & 0x1) && CNE_GET_TYPE(&this->actor) == CNE_TYPE_VENESA){
      this->stateFlags &= ~1;
      // this is crashing, skelanime is trying to look up a wrong address????
      //EnCne02_SetAnimation(this, &gCneAnjuMyChickenHaveEscapedAnim);
    }
    this->actionFunc = EnCne01_FaceForward;
}

void EnCne01_FaceForward(EnCne01* this, PlayState* play) {
    EnCne01_TestIsTalking(this, play);
    this->actor.shape.rot = this->actor.world.rot;
}


// 2AEE ....
// ideas: you bring her a cucco for a bottle, need to know there is cucco nearby tho
// you give her a bean for bean soup
//
void EnCne01_Talk(EnCne01* this, PlayState* play) {
    s16 yaw;
    u8 talkState;

    Math_SmoothStepToS(&this->actor.shape.rot.y, this->actor.yawTowardsPlayer, 4, 0xFA0, 1);

    talkState = Message_GetState(&play->msgCtx);
    //this->inMsgState3 = (talkState == TEXT_STATE_3) ? true : false;
    this->inMsgState3 = (talkState == TEXT_STATE_3); 

    switch (talkState) {
        //case TEXT_STATE_NONE:
            //Message_StartTextbox(play, this->textId, NULL);
            
            //break;

        case TEXT_STATE_5: // blue arrow mid-multiple text
            // supposed to be used for continue, but we use continue dialogue as one off
            // "have you guys talked about the moon in town" used for orangi
            if (!Message_ShouldAdvance(play)) return;

            func_801477B4(play);
            EnCne02_SetupFaceForward(this);

            break;

        case TEXT_STATE_CLOSING: // 2
            if (this->textId == 0x33D3){
              this->textId = 0;
              EnCne02_SetupFaceForward(this);
            }
            break;

        case TEXT_STATE_DONE: //  6
            if (!Message_ShouldAdvance(play)) return;

            this->actor.textId = 0;
            
            
            EnCne02_SetupFaceForward(this);
            func_801477B4(play);
            break;
        //case 0xA:
            //if (Message_ShouldAdvance(play)){
                //k
            //}
            //break;
        //case TEXT_STATE_16: //being given an item
            //EnCne02_TestGiftItem(this, play);
            //break;
        default:
            break;
    }
}

// bug: first time approaching her does not enable text, have to walk far away and walk back???

// 1479 ;; oh thanks here is something ffor thing
s32 EnCne01_TestIsTalking(EnCne01* this, PlayState* play) {
    s32 isTalking = false; // this is not test if talking, this is test if started talking, this frame
    const u16 talkingAngle = 0x64;
    s16 yaw = ABS_ALT(this->actor.shape.rot.y - this->actor.yawTowardsPlayer);
    //if (DECR(this->dialogueTimer) != 0) return;

    //if (yaw < 0x64 && (this->actor.xzDistToPlayer < 100) && Actor_ProcessTalkRequest(&this->actor, &play->state)) {
    if (yaw < talkingAngle && Actor_ProcessTalkRequest(&this->actor, &play->state)) {
        isTalking = true;
        //this->textId = 0x10B9; // Invalid textId, produces empty textbox
        if (CNE_GET_TYPE(&this->actor) == CNE_TYPE_VENESA){
            if (Object_GetIndex(&play->objectCtx, GAMEPLAY_DANGEON_KEEP) != -1){
               this->textId = 0x221B; // you fouuuuund meee

            }else if (this->moonPtr != NULL){
                if (this->stateFlags & 0x1){
                  this->textId = 0x05DE; // the moon is magicccc

                } else {
                  this->stateFlags |= 0x1;
                  this->textId = 0x05DD; // I love hte moooooon
                }
            } else {
                this->textId = 0x14B4; // Are you the one who freed my soul?
            }
            //this->textId = 0x28A5; // Please visit the inn
        } else { // orangi
            // this one is bugged: cannot figure out the code to keep the dialogue working smoothly
            this->textId = 0x33D3; // Are the village people saying the moon is going to fall?
            //this->textId = 0x33D3; // 
        }
        //this->prevTrackTarget = this->trackTarget;
        //this->prevHeadRot = this->headRot;
        //this->prevTorsoRot = this->torsoRot; // snaps her back too fast
        
        // maybe we dont need this?? not used in enms
        //this->actor.textId = this->textId;
        //Message_StartTextbox(play, this->textId, NULL);
        Message_StartTextbox(play, this->textId, &this->actor);
        this->prevActionFunc = this->actionFunc;
        this->actionFunc = EnCne01_Talk;

    } else if (yaw < talkingAngle) {
        // migth be angle, have an issue where you can walk behind her and keep talking
        func_800B8614(&this->actor, play, 90.0f); // is 90 the units of distance?
        //func_800B8614(&this->actor, play, 200.0f); // is 90 the units of distance?

    }

    return isTalking;
}

void EnCne01_Init(Actor* thisx, PlayState* play) {
    //s32 pad;
    EnCne01* this = THIS;

    //this->enHy.animObjIndex = SubS_GetObjectIndex(OBJECT_OS_ANIME, play);
    //this->enHy.headObjIndex = SubS_GetObjectIndex(OBJECT_CNE, play);
    //this->enHy.skelUpperObjIndex = SubS_GetObjectIndex(OBJECT_CNE, play);
    //this->enHy.skelLowerObjIndex = SubS_GetObjectIndex(OBJECT_CNE, play);
    //if ((this->enHy.animObjIndex < 0) || (this->enHy.headObjIndex < 0) || (this->enHy.skelUpperObjIndex < 0) ||
        //(this->enHy.skelLowerObjIndex < 0)) {
        //Actor_Kill(&this->enHy.actor);
    //}
  
    this->moonPtr = SubS_FindActor(play, 0, ACTORCAT_ITEMACTION, ACTOR_EN_FALL);

    if (this->moonPtr != NULL){ // face the moon if it exists
        this->actor.world.rot.y = Actor_YawBetweenActors(&this->actor, this->moonPtr);
        this->actor.shape.rot.y = this->actor.world.rot.y;
    }
  
    switch (CNE_GET_TYPE(thisx)){
        default:
        case CNE_TYPE_VENESA:
            if (this->moonPtr != NULL){
              //this->curAnim = &gCneSmugAnim;
              this->curAnim = &gCneAnjuHandsTogetherAnim;
            } else {
              this->curAnim = &gCnePatientHandsTogetherAnim;
            }
          
            break;

        case CNE_TYPE_ORANGE:
            if (this->moonPtr != NULL){
              this->curAnim = &gCneArmsCrossedAnim;
            } else {
              this->curAnim = &gCnePatientHandsTogetherAnim;
            }
            break;
    }
    this->defaultAnim = this->curAnim;

    SkelAnime_InitFlex(play, &this->skelAnime, 
        &gCneSkel, this->curAnim, 
        this->jointTable, this->morphTable, CNE_LIMB_MAX);

    Collider_InitCylinder(play, &this->collider);
    Collider_SetCylinder(play, &this->collider, &this->actor, &sCylinderInit);
    CollisionCheck_SetInfo2(&this->actor.colChkInfo, DamageTable_Get(0x16), &sColChkInfoInit);
    this->path = SubS_GetPathByIndex(play, CNE_GET_PATH(&this->actor), 0x3F);
    Actor_SetScale(&this->actor, 0.01f);
    //this->actor.flags &= ~ACTOR_FLAG_1;
    //this->.waitingOnInit = true;

    this->actor.targetMode = 6; // increase talk range

    // she should have a fairy
    //Actor_SpawnAsChild(&play->actorCtx, &this->actor, play, ACTOR_EN_ELF, this->actor.world.pos.x,
            //this->actor.world.pos.y, this->actor.world.pos.z, 0, 0, 0,
            //0x0003);


    //this->actionFunc = EnCne01_FinishInit;
    //if (EnHy_Init(this, play, &gCneSkel, ENHY_ANIM_OS_ANIME_11)) {
        //this->actor.flags |= ACTOR_FLAG_1;
        //this->actor.draw = EnCne01_Draw;
        //this->actor.draw = NULL;
        //this->waitingOnInit = false;
    if (CNE_GET_PATH(&this->actor) == 0x3F) {
        this->actionFunc = EnCne01_FaceForward;
    } else {
        //this->actionFunc = EnCne01_Walk;
        this->actionFunc = EnCne01_FaceForward;
    }


    //}
}

void EnCne01_Destroy(Actor* thisx, PlayState* play) {
    EnCne01* this = THIS;

    Collider_DestroyCylinder(play, &this->collider);
}

void EnCne01_Update(Actor* thisx, PlayState* play) {
    EnCne01* this = THIS;

    this->actionFunc(this, play);
    Actor_UpdateBgCheckInfo(play, &this->actor, 0.0f, 0.0f, 0.0f, 4);

    EnCne01_UpdateModel(this, play);
    // WARNING: this can interfere with text system or even replaec it
    //EnCne01_AttemptItemRecieve(this, play);
}

s32 EnCne01_OverrideLimbDraw(PlayState* play, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, Actor* thisx) {
    EnCne01* this = THIS;
    s8 bodyPart;
    Vec3f zeroVec = { 0.0f, 0.0f, 0.0f };

    bodyPart = gEnHyBodyParts[limbIndex];
    if (bodyPart >= 0) {
        Matrix_MultVec3f(&zeroVec, &this->bodyPartsPos[bodyPart]);
    }

    // peronsally I think the head is too orange
    ///*
    if (limbIndex == CNE_LIMB_HEAD && CNE_GET_TYPE(&this->actor) == CNE_TYPE_ORANGE) {
        OPEN_DISPS(play->state.gfxCtx);
        //gSPSegment(POLY_OPA_DISP++, 0x06, play->objectCtx.status[this->headObjIndex].segment);
        //gSegments[6] = VIRTUAL_TO_PHYSICAL(play->objectCtx.status[this->headObjIndex].segment);
        //*dList = gCneHeadBrownHairDL; // used by EnHy to specify head from object
        *dList = gCneHeadOrangeHairDL; // alt head
        //gSegments[6] = VIRTUAL_TO_PHYSICAL(play->objectCtx.status[this->enHy.skelLowerObjIndex].segment);
        CLOSE_DISPS(play->state.gfxCtx);
    } // */
    if (limbIndex == CNE_LIMB_HEAD) {
        Matrix_Translate(1500.0f, 0.0f, 0.0f, MTXMODE_APPLY);
        Matrix_RotateXS(this->headRot.y, MTXMODE_APPLY);
        Matrix_RotateZS(-this->headRot.x, MTXMODE_APPLY);
        Matrix_Translate(-1500.0f, 0.0f, 0.0f, MTXMODE_APPLY);
    }

    if (limbIndex == CNE_LIMB_TORSO) {
        Matrix_RotateXS(-this->torsoRot.y, MTXMODE_APPLY);
        Matrix_RotateZS(-this->torsoRot.x, MTXMODE_APPLY);
    }

    if ((limbIndex == CNE_LIMB_HEAD) && this->inMsgState3 && ((play->state.frames % 2) == 0)) {
        //Matrix_Translate(40.0f, 0.0f, 0.0f, MTXMODE_APPLY);
        Matrix_Translate(20.0f, 0.0f, 0.0f, MTXMODE_APPLY);
    }

    if ((limbIndex == CNE_LIMB_TORSO) || (limbIndex == CNE_LIMB_LEFT_UPPER_ARM) ||
        (limbIndex == CNE_LIMB_RIGHT_UPPER_ARM)) {
        rot->y += (s16)(Math_SinS(this->limbRotTableY[limbIndex]) * 200.0f);
        rot->z += (s16)(Math_CosS(this->limbRotTableZ[limbIndex]) * 200.0f);
    }

    return false;
}

void EnCne01_PostLimbDraw(PlayState* play, s32 limbIndex, Gfx** dList, Vec3s* rot, Actor* thisx) {
    EnCne01* this = THIS;
    GraphicsContext* gfxCtx = play->state.gfxCtx;
    Vec3f zeroVec = { 0.0f, 0.0f, 0.0f };

    /* // think this was how her segment for her body draw was assigned? craxy
    if (limbIndex == CNE_LIMB_RIGHT_FOOT) {
        OPEN_DISPS(play->state.gfxCtx);
        //gSPSegment(POLY_OPA_DISP++, 0x06, play->objectCtx.status[this->enHy.skelUpperObjIndex].segment);
        //gSegments[0x06] = VIRTUAL_TO_PHYSICAL(play->objectCtx.status[this->enHy.skelUpperObjIndex].segment);
        CLOSE_DISPS(play->state.gfxCtx);
    } // */


    if (limbIndex == CNE_LIMB_HEAD) {
        Matrix_MultVec3f(&zeroVec, &this->actor.focus.pos);
    }
}

void EnCne01_TransformLimbDraw(PlayState* play, s32 limbIndex, Actor* thisx) {
}

/*
void Debug_PrintToScreen(Actor* thisx, PlayState* play) {
    EnCne01* this = THIS;
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

    GfxPrint_SetPos(&printer, 1, 13);
    
    //GfxPrint_Printf(&printer, "drawflags %X", this->drawFlags);
    //GfxPrint_Printf(&printer, "BREG86 %X", BREG(86));
    GfxPrint_Printf(&printer, "mesgState %X", Message_GetState(&play->msgCtx));

    GfxPrint_SetPos(&printer, 1, 14);
    GfxPrint_Printf(&printer, "prev state %X", this->stateFlags );

    GfxPrint_SetPos(&printer, 1, 15);
    GfxPrint_Printf(&printer, "TestFunc %X", &EnCne01_Talk);

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


void EnCne01_Draw(Actor* thisx, PlayState* play) {
    EnCne01* this = THIS;
    s32 i;
    //u8* shadowTex = GRAPH_ALLOC(play->state.gfxCtx, SUBS_SHADOW_TEX_SIZE);
    //u8* shadowTexIter;
    Color_RGBA8 originalBlueColor = { 160, 180, 255, 0 };

    OPEN_DISPS(play->state.gfxCtx);

    func_8012C28C(play->state.gfxCtx);
    if (CNE_GET_TYPE(&this->actor) == CNE_TYPE_ORANGE) {
        gSPSegment(POLY_OPA_DISP++, 0x08, Gfx_EnvColor(play->state.gfxCtx, 
          70, 160, 230, 0)); // the side to side girl has different colors
        gSPSegment(POLY_OPA_DISP++, 0x09, Gfx_EnvColor(play->state.gfxCtx, 
          255, 255, 100, 0));
        gSPSegment(POLY_OPA_DISP++, 0x0A, Gfx_EnvColor(play->state.gfxCtx, 
          255, 255, 255, 255));
    } else { // venessa
        gSPSegment(POLY_OPA_DISP++, 0x08, Gfx_EnvColor(play->state.gfxCtx, 
          originalBlueColor.r, originalBlueColor.g, 
          originalBlueColor.b, originalBlueColor.a)); // blue for all, regular
        gSPSegment(POLY_OPA_DISP++, 0x09, Gfx_EnvColor(play->state.gfxCtx, 
          originalBlueColor.r, originalBlueColor.g,
          originalBlueColor.b, originalBlueColor.a)); // blue for all, regular
        gSPSegment(POLY_OPA_DISP++, 0x0A, Gfx_EnvColor(play->state.gfxCtx, 
          originalBlueColor.r, originalBlueColor.g,
          originalBlueColor.b, originalBlueColor.a)); // blue for all, regular
        //gSPSegment(POLY_OPA_DISP++, 0x09, Gfx_EnvColor(play->state.gfxCtx, 160, 180, 255, 0));
        //gSPSegment(POLY_OPA_DISP++, 0x0A, Gfx_EnvColor(play->state.gfxCtx, 160, 180, 255, 0));
    }
    gDPPipeSync(POLY_OPA_DISP++);
    SkelAnime_DrawTransformFlexOpa(play, this->skelAnime.skeleton, this->skelAnime.jointTable,
                                   this->skelAnime.dListCount, EnCne01_OverrideLimbDraw, EnCne01_PostLimbDraw,
                                   EnCne01_TransformLimbDraw, &this->actor);
    Matrix_RotateXS(0, MTXMODE_NEW);

    //for (i = 0, shadowTexIter = shadowTex; i < SUBS_SHADOW_TEX_SIZE; i++) {
        //*shadowTexIter++ = 0;
    //}
    //for (i = 0; i < 5; i++) {
        //SubS_GenShadowTex(this->bodyPartsPos, &this->actor.world.pos, shadowTex, i / 5.0f,
                          //ARRAY_COUNT(this->bodyPartsPos), gEnHyShadowSizes, gEnHyParentBodyParts);
    //}
    //SubS_DrawShadowTex(&this->actor, &play->state, shadowTex);
    
    //Debug_PrintToScreen(thisx, play);

    CLOSE_DISPS(play->state.gfxCtx);
}
