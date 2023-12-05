/*
 * File: z_en_hs2.c
 * Overlay: ovl_En_Hs2
 * Description: Near-empty actor. Does nothing, but can be targeted.
 */

/*
 * File: z_en_twig.c
 * Overlay: ovl_En_Twig
 * Description: Beaver Race Ring
 *  THIS WAS MOVED TO EN_HS2 which was empty, attempted to change actor slot to see if I can get this working in MMR for now
 */

#include "../ovl_En_Twig/z_en_twig.h"
#include "objects/object_twig/object_twig.h"

#define FLAGS (ACTOR_FLAG_10)

#define THIS ((EnTwig*)thisx)

void EnTwig_Moved_Init2(Actor* thisx, PlayState* play2);
void EnTwig_Moved_Draw2(Actor* thisx, PlayState* play2);

void EnTwig_Moved_Init(Actor* thisx, PlayState* play2);
void EnTwig_Moved_Destroy(Actor* thisx, PlayState* play2);
void EnTwig_Moved_Update(Actor* thisx, PlayState* play2);
void EnTwig_Moved_Draw(Actor* thisx, PlayState* play);

void func_80AC0A54_moved(EnTwig* this, PlayState* play);
void func_80AC0A6C_moved(EnTwig* this, PlayState* play);

void func_80AC0A7C_moved(EnTwig* this, PlayState* play);
void func_80AC0AC8_moved(EnTwig* this, PlayState* play);

void func_80AC0CC4_moved(EnTwig* this, PlayState* play);
void func_80AC0D2C_moved(EnTwig* this, PlayState* play);

//ActorInit En_Twig_Moved_InitVars = {
ActorInit En_Hs2_InitVars= {
    ///**/ ACTOR_EN_TWIG,
    /**/ ACTOR_EN_HS2,
    /**/ ACTORCAT_MISC,
    /**/ FLAGS,
    /**/ OBJECT_TWIG,
    /**/ sizeof(EnTwig),
    /**/ EnTwig_Moved_Init2,
    /**/ EnTwig_Moved_Destroy,
    /**/ EnTwig_Moved_Update,
    /**/ EnTwig_Moved_Draw2,
};

//static s32 sCurrentRing = 0;
//static s16 sRingCount = 0;
//static s16 sRingNotCollected[25];

static CollisionHeader* sColHeaders[] = {
    //NULL,
    &object_twig_Colheader_0020A0,
    &object_twig_Colheader_0020A0,
    &object_twig_Colheader_0016C0,
};

static s16 sRingsHaveSpawned = false;

static InitChainEntry sInitChain[] = {
    ICHAIN_F32(uncullZoneScale, 40, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneDownward, 40, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneForward, 1000, ICHAIN_CONTINUE),
    ICHAIN_VEC3F_DIV1000(scale, 10, ICHAIN_STOP),
};

void EnTwig_Moved_Init(Actor* thisx, PlayState* play2) {
    PlayState* play = play2;
    EnTwig* this = THIS;
    s32 i;

    Actor_ProcessInitChain(&this->dyna.actor, sInitChain);
    this->type = RACERING_GET_PARAM_F(&this->dyna.actor);
    DynaPolyActor_Init(&this->dyna, DYNA_TRANSFORM_POS);
    if (sColHeaders[this->type] != NULL) {
        DynaPolyActor_LoadMesh(play, &this->dyna, sColHeaders[this->type]);
    }

    this->dyna.actor.bgCheckFlags |= BGCHECKFLAG_PLAYER_400;
    switch (this->type) { // type
        case 0: // unused and does nothing weird
            Actor_Kill(&this->dyna.actor);
            //Actor_SetScale(&this->dyna.actor, 4.2f);
            //this->dyna.actor.uncullZoneScale = this->dyna.actor.uncullZoneDownward = this->dyna.actor.scale.x * 60.0f;
            //DynaPoly_DisableCollision(play, &play->colCtx.dyna, this->dyna.bgId);
            //func_80AC0A7C_moved(this, play);
            break;

        //case 1: // wooden bramble
            //if (!sRingsHaveSpawned) {
                //sRingCount = CHECK_WEEKEVENTREG(WEEKEVENTREG_24_04) ? 25 : 20;
                //for (i = 0; i < sRingCount; i++) {
                    //sRingNotCollected[i] = false;
                //}
                //sRingsHaveSpawned = true;
            //}
            //if (RACERING_GET_PARAM_1F0(&this->dyna.actor) != 0) {
                //if (!CHECK_WEEKEVENTREG(WEEKEVENTREG_24_04)) {
                    //Actor_Kill(&this->dyna.actor);
                    //return;
                //}
            //} else if (CHECK_WEEKEVENTREG(WEEKEVENTREG_24_04)) {
                //Actor_Kill(&this->dyna.actor);
                //return;
            //}
            //Actor_SetScale(&this->dyna.actor, 4.2f);
            //this->dyna.actor.uncullZoneScale = this->dyna.actor.uncullZoneDownward = this->dyna.actor.scale.x * 60.0f;
            //DynaPoly_DisableCollision(play, &play->colCtx.dyna, this->dyna.bgId);
            //func_80AC0A7C_moved(this, play);
            //break;

        case 2:
            Actor_SetScale(&this->dyna.actor, 1.0f);
            this->dyna.actor.uncullZoneScale = this->dyna.actor.uncullZoneDownward = this->dyna.actor.scale.x * 880.0f;
            func_80AC0A54_moved(this, play);
            break;

        default:
            break;
    }
}

void EnTwig_Moved_Destroy(Actor* thisx, PlayState* play2) {
    PlayState* play = play2;
    EnTwig* this = THIS;

    DynaPoly_DeleteBgActor(play, &play->colCtx.dyna, this->dyna.bgId);
}

// do nothing? really?
void func_80AC0A54_moved(EnTwig* this, PlayState* play) {
    this->actionFunc = func_80AC0A6C_moved;
}

void func_80AC0A6C_moved(EnTwig* this, PlayState* play) {
}

// setup to draw the rings
void func_80AC0A7C_moved(EnTwig* this, PlayState* play) {
    Player* player = GET_PLAYER(play);

    Math_Vec3f_Copy(&this->unk_180, &player->bodyPartsPos[PLAYER_BODYPART_WAIST]);
    this->unk_178 = 0;
    this->ringColorshiftTimer = 0;
    this->actionFunc = func_80AC0AC8_moved;
}

void func_80AC0AC8_moved(EnTwig* this, PlayState* play) {
    static Vec3f D_80AC10D0 = { 0.0f, 0.0f, 1.0f };
    Player* player = GET_PLAYER(play);
    Plane sp4C;
    Vec3f sp40;

    //if (sCurrentRing == RACERING_GET_PARAM_FE0(&this->dyna.actor)) {
        //if (this->ringColorshiftTimer == 3) {
            //this->ringColorshiftTimer = 0;
            //this->dyna.actor.shape.rot.z += 0x2000;
        //} else {
            //this->ringColorshiftTimer++;
        //}
    //}
    SubS_ConstructPlane(&this->dyna.actor.world.pos, &D_80AC10D0, &this->dyna.actor.shape.rot, &sp4C);
    if (/* (sCurrentRing == RACERING_GET_PARAM_FE0(&this->dyna.actor)) && */
        Math3D_LineSegVsPlane(sp4C.normal.x, sp4C.normal.y, sp4C.normal.z, sp4C.originDist, &this->unk_180,
                              &player->bodyPartsPos[PLAYER_BODYPART_WAIST], &sp40, 0)) {
        if (Math3D_Vec3fDistSq(&this->dyna.actor.world.pos, &sp40) <= SQ(this->dyna.actor.scale.x * 0.345f * 40.0f)) {
            func_80AC0CC4_moved(this, play);
            return;
        }
    } else {
        if (this->dyna.actor.xyzDistToPlayerSq <= SQ((this->dyna.actor.scale.x * 40.0f) + 40)) {
            DynaPoly_EnableCollision(play, &play->colCtx.dyna, this->dyna.bgId);
        } else {
            DynaPoly_DisableCollision(play, &play->colCtx.dyna, this->dyna.bgId);
        }
        if (this->dyna.actor.xyzDistToPlayerSq >= (this->dyna.actor.scale.x * 10.0f * 40.0f * 40.0f)) {
            this->dyna.actor.shape.rot.y = this->dyna.actor.yawTowardsPlayer;
            this->dyna.actor.world.rot.y = this->dyna.actor.yawTowardsPlayer;
        }
    }
    Math_Vec3f_Copy(&this->unk_180, &player->bodyPartsPos[PLAYER_BODYPART_WAIST]);
}

// player has touched the thing
void func_80AC0CC4_moved(EnTwig* this, PlayState* play) {
    this->unk_170 = 3458.0f;
    this->unk_174 = 0.2f;
    this->unk_16C |= 1;
    DynaPoly_DisableCollision(play, &play->colCtx.dyna, this->dyna.bgId);
    this->actionFunc = func_80AC0D2C_moved;
}

void func_80AC0D2C_moved(EnTwig* this, PlayState* play) {
    static Vec3f sKiraVel = { 0.0f, -0.05f, 0.0f };
    static Vec3f sKiraAccel = { 0.0f, -0.025f, 0.0f };
    static Color_RGBA8 sColorWhite = { 255, 255, 255, 130 };
    static Color_RGBA8 sColorYellow = { 255, 255, 0, 0 };
    Player* player = GET_PLAYER(play);

    Math_SmoothStepToF(&this->dyna.actor.world.pos.x, player->bodyPartsPos[PLAYER_BODYPART_WAIST].x, 0.5f, 100.0f,
                       0.01f);
    Math_SmoothStepToF(&this->dyna.actor.world.pos.y, player->bodyPartsPos[PLAYER_BODYPART_WAIST].y, 0.5f, 100.0f,
                       0.01f);
    Math_SmoothStepToF(&this->dyna.actor.world.pos.z, player->bodyPartsPos[PLAYER_BODYPART_WAIST].z, 0.5f, 100.0f,
                       0.01f);
    this->dyna.actor.shape.rot.z += (s16)this->unk_170;
    this->dyna.actor.scale.x -= this->unk_174;
    if (this->dyna.actor.scale.x < 0.0f) {
        Actor_SetScale(&this->dyna.actor, 0.0f);
    } else {
        Actor_SetScale(&this->dyna.actor, this->dyna.actor.scale.x);
    }
    if (this->dyna.actor.scale.x <= 0.0f) {
        s32 j;
        Vec3f sp6C;

        for (j = 0; j < 7; j++) {
            sp6C.x = (Rand_Centered() * 10.0f) + this->dyna.actor.world.pos.x;
            sp6C.y = (Rand_Centered() * 10.0f) + this->dyna.actor.world.pos.y;
            sp6C.z = (Rand_Centered() * 10.0f) + this->dyna.actor.world.pos.z;
            EffectSsKirakira_SpawnDispersed(play, &sp6C, &sKiraVel, &sKiraAccel, &sColorWhite, &sColorYellow, 1000,
                                            (s32)(Rand_ZeroOne() * 10.0f) + 20);
        }
        Audio_PlaySfx(NA_SE_SY_GET_ITEM);
        play->interfaceCtx.minigamePoints--;
        //sRingNotCollected[RACERING_GET_PARAM_FE0(&this->dyna.actor)] = true;
        //if (sCurrentRing == RACERING_GET_PARAM_FE0(&this->dyna.actor)) {
            //s32 i;

            //for (i = 0; i < sRingCount; i++) {
                //if (!sRingNotCollected[i]) {
                    //sCurrentRing = i;
                    //break;
                //}
            //}
            //if (i == sRingCount) {
                //sCurrentRing = -1;
            //}
        //}
        Actor_Kill(&this->dyna.actor);
        return;
    }
    this->unk_170 += 180.0f / 0x10000;
    this->unk_174 += 0.15f;
}

void EnTwig_Moved_Update(Actor* thisx, PlayState* play2) {
    PlayState* play = play2;
    EnTwig* this = THIS;

    this->actionFunc(this, play);
}

void EnTwig_Moved_Draw(Actor* thisx, PlayState* play) {
    EnTwig* this = THIS;

    switch (this->type) {
        // type zero ignored
        case 1:
            Gfx_DrawDListOpa(play, object_twig_DL_001C38);
            break;
        case 2:
            Gfx_DrawDListOpa(play, object_twig_DL_0014C8);
            break;
    }
}

void EnTwig_Moved_Draw2(Actor* thisx, PlayState* play) {
     Gfx_DrawDListOpa(play, object_twig_DL_001C38);

}

// this is ONLY for our variant
void EnTwig_Moved_Update2(Actor* thisx, PlayState* play){
  EnTwig* this = THIS;

  // ripped from the function we want, but we will instead get to use it for our type
  //if (sCurrentRing == RACERING_GET_PARAM_FE0(&this->dyna.actor)) {
  if (this->dyna.actor.xzDistToPlayer < 200) {
      if (this->ringColorshiftTimer == 3) {
          this->ringColorshiftTimer = 0;
          this->dyna.actor.shape.rot.z += 0x2000;
      } else {
          this->ringColorshiftTimer++;
      }
  }

  // if the actionfunc changes from under us, we want to give the player some magic
  if (this->type == 0
    && this->oldActionFunc != this->actionFunc && this->actionFunc == func_80AC0D2C_moved ){
    // do something new 
    Magic_Add(play, MAGIC_NORMAL_METER / 2);

    thisx->update = EnTwig_Moved_Update;
    return;
  }

  this->oldActionFunc = this->actionFunc;
  EnTwig_Moved_Update(thisx, play);

}

void EnTwig_Moved_Init2(Actor* thisx, PlayState* play) {
  EnTwig* this = THIS;

  //this->type = RACERING_GET_PARAM_F(&this->dyna.actor);
  if (thisx->params == 0)
  {
    thisx->update = EnTwig_Moved_Update2;

    Actor_ProcessInitChain(&this->dyna.actor, sInitChain);
    //this->type = RACERING_GET_PARAM_F(&this->dyna.actor);
    DynaPolyActor_Init(&this->dyna, DYNA_TRANSFORM_POS);
    //if (sColHeaders[this->type] != NULL) {
        DynaPolyActor_LoadMesh(play, &this->dyna, sColHeaders[this->type]);
    //}

    this->dyna.actor.bgCheckFlags |= BGCHECKFLAG_PLAYER_400;


    //if (!sRingsHaveSpawned) {
        //sRingCount = CHECK_WEEKEVENTREG(WEEKEVENTREG_24_04) ? 25 : 20;
        //for (i = 0; i < sRingCount; i++) {
            //sRingNotCollected[i] = false;
        //}
        //sRingsHaveSpawned = true;
    //}
    //if (RACERING_GET_PARAM_1F0(&this->dyna.actor) != 0) {
        //if (!CHECK_WEEKEVENTREG(WEEKEVENTREG_24_04)) {
            //Actor_Kill(&this->dyna.actor);
            //return;
        //}
    //} else if (CHECK_WEEKEVENTREG(WEEKEVENTREG_24_04)) {
        //Actor_Kill(&this->dyna.actor);
        //return;
    //}
    Actor_SetScale(&this->dyna.actor, 4.2f);
    this->dyna.actor.uncullZoneScale = this->dyna.actor.uncullZoneDownward = this->dyna.actor.scale.x * 60.0f;
    //DynaPoly_DisableCollision(play, &play->colCtx.dyna, this->dyna.bgId);
    //func_80AC0A7C_moved(this, play);
    func_80AC0A7C_moved(this, play);
    //break;

  } else {

    EnTwig_Moved_Init(thisx, play);
    thisx->draw = EnTwig_Moved_Draw;
  }

}
