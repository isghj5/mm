/*
 * File: z_en_tag_obj.c
 * Overlay: ovl_En_Tag_Obj
 * Description: ~~Unused Seahorse Spawner~~
 *   WE CUBE NOW
 */

// with us now
#include "z_en_tag_obj.h"

#include "objects/gameplay_keep/gameplay_keep.h"

#define FLAGS (ACTOR_FLAG_10)

#define THIS ((CUBE*)thisx)

void CUBE_Init(Actor* thisx, PlayState* play);
void CUBE_Destroy(Actor* thisx, PlayState* play);
void CUBE_Update(Actor* thisx, PlayState* play);
void CUBE_Draw(Actor* thisx, PlayState* play);

void CUBE_Idle(CUBE* this, PlayState* play);
void CUBE_Elevate(CUBE* this, PlayState* play);

//ActorInit Bg_F40_Flift_InitVars = {
ActorInit En_Tag_Obj_InitVars = {
    ACTOR_BG_F40_FLIFT, // its and old code but it checks out
    ACTORCAT_BG,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(CUBE),
    (ActorFunc)CUBE_Init,
    (ActorFunc)CUBE_Destroy,
    (ActorFunc)CUBE_Update,
    (ActorFunc)CUBE_Draw,
};

static InitChainEntry sInitChain[] = {
    ICHAIN_F32(uncullZoneScale, 400, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneForward, 5000, ICHAIN_CONTINUE),
    ICHAIN_VEC3F_DIV1000(scale, 100, ICHAIN_STOP), // scale
};


void CUBE_Init(Actor* thisx, PlayState* play) {
    CUBE* this = THIS;

    Actor_ProcessInitChain(&this->dyna.actor, sInitChain);
    DynaPolyActor_Init(&this->dyna, 1);
    DynaPolyActor_LoadMesh(play, &this->dyna, &gameplay_keep_Colheader_05A270);
    this->dyna.actor.params = 1;
    this->actionFunc = CUBE_Idle;
    this->dyna.actor.home.pos.y += 5;
}

void CUBE_Destroy(Actor* thisx, PlayState* play) {
    CUBE* this = THIS;

    DynaPoly_DeleteBgActor(play, &play->colCtx.dyna, this->dyna.bgId);
}

void CUBE_Idle(CUBE* this, PlayState* play) {
    if (((this->dyna.actor.params == 1) && (DynaPolyActor_IsInRidingMovingState(&this->dyna))) ||
        ((this->dyna.actor.params == -1) && (!DynaPolyActor_IsInRidingMovingState(&this->dyna)))) {
        //this->timer = 96;
        this->timer = 96;
        this->actionFunc = CUBE_Elevate;
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

void CUBE_Elevate(CUBE* this, PlayState* play) {
    if (this->timer != 0) {
        this->timer--;
        this->dyna.actor.world.pos.y =
            //(((cos_rad(this->timer * (M_PI / 96.0f)) * this->dyna.actor.params) + 1.0f) * 463.4f) +
            (((cos_rad(this->timer * (M_PI / 96.0f)) * this->dyna.actor.params) + 1.0f) * 163.4f) +
            this->dyna.actor.home.pos.y;
    } else {
        // decend
        this->dyna.actor.params = -this->dyna.actor.params;
        this->actionFunc = CUBE_Idle;
    }
}

void CUBE_Update(Actor* thisx, PlayState* play) {
    CUBE* this = THIS;

    this->actionFunc(this, play);
}

void CUBE_Draw(Actor* thisx, PlayState* play) {
    Gfx_DrawDListOpa(play, gameplay_keep_DL_05A0B0);
}
