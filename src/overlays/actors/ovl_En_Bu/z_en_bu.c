/*
 * File: z_en_bu.c
 * Overlay: ovl_En_Bu
 * Description: Unused dummied-out enemy
 */

#include "z_en_bu.h"
#include "objects/object_box/object_box.h"
#include "objects/gameplay_keep/gameplay_keep.h"


#define FLAGS (ACTOR_FLAG_10)

#define THIS ((EnBu*)thisx)

void EnBu_Init(Actor* thisx, GlobalContext* globalCtx);
void EnBu_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnBu_Update(Actor* thisx, GlobalContext* globalCtx);
void EnBu_Draw(Actor* thisx, GlobalContext* globalCtx);

void EnBu_WaitClosed(EnBu* this, GlobalContext* globalCtx);

const ActorInit En_Bu_InitVars = {
    ACTOR_EN_BU, // new and improved
    ACTORCAT_CHEST,
    FLAGS,
    OBJECT_BOX,
    sizeof(EnBu),
    (ActorFunc)EnBu_Init,
    (ActorFunc)EnBu_Destroy,
    (ActorFunc)EnBu_Update,
    (ActorFunc)EnBu_Draw,
};



void EnBu_Init(Actor* thisx, GlobalContext* globalCtx) {
    EnBu* this = THIS;
    CollisionHeader* colHeader;

    f32 animFrame;
    f32 animFrameEnd;

    animFrame = 0.0f;
    animFrameEnd = Animation_GetLastFrame(&gBoxChestOpenAnim);
    //animFrameEnd = 0.0f;


    DynaPolyActor_Init(&this->dyna, 0);
    CollisionHeader_GetVirtual(&gBoxChestCol, &colHeader);

    this->dyna.bgId = DynaPoly_SetBgActor(globalCtx, &globalCtx->colCtx.dyna, &this->dyna.actor, colHeader);
    this->dyna.actor.gravity = -5.5f;
    this->dyna.actor.terminalVelocity = -50.0f;
    this->dyna.actor.floorHeight = this->dyna.actor.world.pos.y;

    SkelAnime_Init(globalCtx, &this->skelAnime, &gBoxChestSkel, &gBoxChestOpenAnim, this->jointTable, this->morphTable,
                   OBJECT_BOX_CHEST_LIMB_MAX);
    Animation_Change(&this->skelAnime, &gBoxChestOpenAnim, 1.5f, animFrame, animFrameEnd, ANIMMODE_ONCE, 0.0f);

    this->status = false;
    this->actionFunc = EnBu_WaitClosed;
}

void EnBu_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    EnBu* this = THIS;

    DynaPoly_DeleteBgActor(globalCtx, &globalCtx->colCtx.dyna, this->dyna.bgId);
}

void EnBu_WaitClosed(EnBu* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);
    Vec3f offset;


    Actor_OffsetOfPointInActorCoords(&this->dyna.actor, &offset, &player->actor.world.pos);
    if (offset.z > -50.0f && offset.z < 0.0f && fabsf(offset.y) < 10.0f && fabsf(offset.x) < 20.0f &&
        Player_IsFacingActor(&this->dyna.actor, 0x3000, globalCtx)) {

        this->dyna.actor.id = ACTOR_EN_BOX;
        Actor_PickUpNearby(&this->dyna.actor, globalCtx, 0);
        //Actor_PickUpNearby(&this->dyna.actor, globalCtx, 1);
        //this->dyna.actor.id = ACTOR_EN_BU;
        this->status = true;
    } else {
        this->status = false;

    }

    //if (Flags_GetTreasure(globalCtx, ENBOX_GET_CHEST_FLAG(&this->dyna.actor))) {
            //EnBox_SetupAction(this, EnBox_Open);
    //}

}


// TODO take damage from light arrows or fire arrows
void EnBu_Update(Actor* thisx, GlobalContext* globalCtx) {
    EnBu* this = THIS;

    //Actor_MoveWithGravity(&this->actor);
    this->actionFunc(this, globalCtx);
}

void EnBu_PostLimbDraw(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3s* rot, Actor* thisx, Gfx** gfx) {
    s32 pad;
    EnBu* this = THIS;

    if (limbIndex == OBJECT_BOX_CHEST_LIMB_01) {
        gSPMatrix((*gfx)++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        //if (this->type == ENBOX_TYPE_BIG_ORNATE) {
            //gSPDisplayList((*gfx)++, &gBoxChestBaseOrnateDL);
        //} else if (Actor_IsSmallChest(this)) {
            //if (this->getItem == GI_KEY_SMALL) {
                //gSPDisplayList((*gfx)++, &gBoxChestBaseGildedDL);
            //} else {
                gSPDisplayList((*gfx)++, &gBoxChestBaseDL);
            //}
        //} else {
            //gSPDisplayList((*gfx)++, &gBoxChestBaseGildedDL);
        //}
    } else if (limbIndex == OBJECT_BOX_CHEST_LIMB_03) {
        gSPMatrix((*gfx)++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        //if (this->type == ENBOX_TYPE_BIG_ORNATE) {
            //gSPDisplayList((*gfx)++, &gBoxChestLidOrnateDL);
        //} else if (Actor_IsSmallChest(this)) {
            //if (this->getItem == GI_KEY_SMALL) {
                //gSPDisplayList((*gfx)++, &gBoxChestLidGildedDL);
            //} else {
                gSPDisplayList((*gfx)++, &gBoxChestLidDL);
            //}
        //} else {
            //gSPDisplayList((*gfx)++, &gBoxChestLidGildedDL);
        //}
    }
}


void Debug_PrintToScreen(Actor* thisx, GlobalContext *globalCtx) {
    EnBu* this = THIS;
    // with explanation comments
    GfxPrint printer;
    Gfx* gfx;

    OPEN_DISPS(globalCtx->state.gfxCtx);

    // the dlist will be written in the opa buffer because that buffer is larger,
    // but executed from the overlay buffer (overlay draws last, for example the hud is drawn to overlay)
    gfx = POLY_OPA_DISP + 1;
    gSPDisplayList(OVERLAY_DISP++, gfx);

    // initialize GfxPrint struct
    GfxPrint_Init(&printer);
    GfxPrint_Open(&printer, gfx);

    // set color to opaque pink
    GfxPrint_SetColor(&printer, 255, 0, 255, 255);
    // set position to somewhere near screen center
    GfxPrint_SetPos(&printer, 1, 10);
    //GfxPrint_Printf(&printer, "rot.y: %X", this->actor.home.rot.y);
    GfxPrint_Printf(&printer, "status: %X", this->status);
    GfxPrint_SetPos(&printer, 1, 12);

    // write Hello at previously set position with previously set color
    //GfxPrint_Printf(&printer, "limbpos (%X, %X, %X)", this->limbPos.x, this->limbPos.y, this->limbPos.z);
    //GfxPrint_SetPos(&printer, 1, 12);
    //GfxPrint_Printf(&printer, "BREG86 %X", BREG(86));

    // end of text printing
    gfx = GfxPrint_Close(&printer);
    GfxPrint_Destroy(&printer);

    gSPEndDisplayList(gfx++);
    // make the opa dlist jump over the part that will be executed as part of overlay
    gSPBranchList(POLY_OPA_DISP, gfx);
    POLY_OPA_DISP = gfx;

    CLOSE_DISPS(globalCtx->state.gfxCtx);
}

// why did chest need to be so weird..
Gfx* EnBu_SetRenderMode1(GraphicsContext* gfxCtx) {
    Gfx* dl = GRAPH_ALLOC(gfxCtx, sizeof(Gfx) * 2);

    gSPEndDisplayList(dl);
    return dl;
}

void EnBu_Draw(Actor* thisx, GlobalContext* globalCtx) {
    EnBu* this = THIS;


    OPEN_DISPS(globalCtx->state.gfxCtx);
    gDPPipeSync(POLY_OPA_DISP++);
    gDPSetEnvColor(POLY_OPA_DISP++, 0, 0, 0, 255);
    gSPSegment(POLY_OPA_DISP++, 0x08, EnBu_SetRenderMode1(globalCtx->state.gfxCtx));
    func_8012C28C(globalCtx->state.gfxCtx);
    POLY_OPA_DISP = SkelAnime_Draw(globalCtx, this->skelAnime.skeleton, this->skelAnime.jointTable, NULL,
                                       EnBu_PostLimbDraw, &this->dyna.actor, POLY_OPA_DISP);

    CLOSE_DISPS(globalCtx->state.gfxCtx);
    //Debug_PrintToScreen(thisx, globalCtx);
}
