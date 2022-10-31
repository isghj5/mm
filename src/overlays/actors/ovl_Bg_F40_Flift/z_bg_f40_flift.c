/*
 * File: z_bg_f40_flift.c
 * Overlay: ovl_Bg_F40_Flift
 * Description: Stone Tower Temple - Grey Square Stone Elevator
 */

#include "z_bg_f40_flift.h"
#include "objects/gameplay_keep/gameplay_keep.h"

#define FLAGS (ACTOR_FLAG_10)

#define THIS ((BgF40Flift*)thisx)

void BgF40Flift_Init(Actor* thisx, PlayState* play);
void BgF40Flift_Destroy(Actor* thisx, PlayState* play);
void BgF40Flift_Update(Actor* thisx, PlayState* play);
void BgF40Flift_Draw(Actor* thisx, PlayState* play);

void BgF40Flift_Idle(BgF40Flift* this, PlayState* play);
void BgF40Flift_Elevate(BgF40Flift* this, PlayState* play);

ActorInit Bg_F40_Flift_InitVars = {
    ACTOR_BG_F40_FLIFT,
    ACTORCAT_BG,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(BgF40Flift),
    (ActorFunc)BgF40Flift_Init,
    (ActorFunc)BgF40Flift_Destroy,
    (ActorFunc)BgF40Flift_Update,
    (ActorFunc)BgF40Flift_Draw,
};

static InitChainEntry sInitChain[] = {
    ICHAIN_F32(uncullZoneScale, 400, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneForward, 5000, ICHAIN_CONTINUE),
    ICHAIN_VEC3F_DIV1000(scale, 100, ICHAIN_STOP), // scale
};


void BgF40Flift_Init(Actor* thisx, PlayState* play) {
    BgF40Flift* this = THIS;

    Actor_ProcessInitChain(&this->dyna.actor, sInitChain);
    DynaPolyActor_Init(&this->dyna, 1);
    //DynaPolyActor_LoadMesh(play, &this->dyna, &object_f40_obj_Colheader_004240); // vanilla
    DynaPolyActor_LoadMesh(play, &this->dyna, &gameplay_keep_Colheader_05A270); // not sure if this is what we want
    this->dyna.actor.params = 1;
    this->actionFunc = BgF40Flift_Idle;
    this->dyna.actor.home.pos.y += 5;
}

void BgF40Flift_Destroy(Actor* thisx, PlayState* play) {
    BgF40Flift* this = THIS;

    DynaPoly_DeleteBgActor(play, &play->colCtx.dyna, this->dyna.bgId);
}

void BgF40Flift_Idle(BgF40Flift* this, PlayState* play) {
    if (((this->dyna.actor.params == 1) && (DynaPolyActor_IsInRidingMovingState(&this->dyna))) ||
        ((this->dyna.actor.params == -1) && (!DynaPolyActor_IsInRidingMovingState(&this->dyna)))) {
        //this->timer = 96;
        this->timer = 96;
        this->actionFunc = BgF40Flift_Elevate;
    } else {
        if (this->timer == 0) {
            this->timer = 48;
        }
        this->timer--;
        if (this->dyna.actor.params == 1) {
            this->dyna.actor.world.pos.y = (sin_rad(this->timer * (M_PI / 24.0f)) * 5.0f) + this->dyna.actor.home.pos.y;
            this->dyna.actor.shape.rot.y = this->dyna.actor.world.rot.y += 50;
        } else {
            this->dyna.actor.world.pos.y =
                (sin_rad(this->timer * (M_PI / 24.0f)) * 5.0f) + (926.8f + this->dyna.actor.home.pos.y);
        }
    }
}

void BgF40Flift_Elevate(BgF40Flift* this, PlayState* play) {
    if (this->timer != 0) {
        this->timer--;
        this->dyna.actor.world.pos.y =
            //(((cos_rad(this->timer * (M_PI / 96.0f)) * this->dyna.actor.params) + 1.0f) * 463.4f) +
            (((cos_rad(this->timer * (M_PI / 96.0f)) * this->dyna.actor.params) + 1.0f) * 163.4f) +
            this->dyna.actor.home.pos.y;
    } else {
        // decend
        this->dyna.actor.params = -this->dyna.actor.params;
        this->actionFunc = BgF40Flift_Idle;
    }
}

void BgF40Flift_Update(Actor* thisx, PlayState* play) {
    BgF40Flift* this = THIS;

    this->actionFunc(this, play);
}

void BgF40Flift_Draw(Actor* thisx, PlayState* play) {
    //Gfx_DrawDListOpa(play, object_f40_obj_DL_004038);
    Gfx_DrawDListOpa(play, gameplay_keep_DL_05A0B0);
}
