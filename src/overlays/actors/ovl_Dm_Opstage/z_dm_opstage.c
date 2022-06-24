/*
 * File: z_dm_opstage.c
 * Overlay: ovl_Dm_Opstage
 * Description: Lost Woods cutscene objects
 */

#include "z_dm_opstage.h"
#include "objects/object_keikoku_demo/object_keikoku_demo.h"

#define FLAGS (ACTOR_FLAG_10 | ACTOR_FLAG_20)

#define THIS ((DmOpstage*)thisx)

void DmOpstage_Init(Actor* thisx, GlobalContext* globalCtx);
void DmOpstage_Destroy(Actor* thisx, GlobalContext* globalCtx);
void DmOpstage_Update(Actor* thisx, GlobalContext* globalCtx);
void DmOpstage_Draw(Actor* thisx, GlobalContext* globalCtx);

void DmOpstage_FollowCutsceneScript(DmOpstage* this, GlobalContext* globalCtx);
void DmOpstage_CheckBonk(DmOpstage* this, GlobalContext* globalCtx);

const ActorInit Dm_Opstage_InitVars = {
    ACTOR_DM_OPSTAGE,
    ACTORCAT_ITEMACTION,
    FLAGS,
    OBJECT_KEIKOKU_DEMO,
    sizeof(DmOpstage),
    (ActorFunc)DmOpstage_Init,
    (ActorFunc)DmOpstage_Destroy,
    (ActorFunc)DmOpstage_Update,
    (ActorFunc)DmOpstage_Draw,
};

static InitChainEntry sInitChain[] = {
    ICHAIN_F32(uncullZoneScale, 300, ICHAIN_STOP),
};

// ripped from wood02
static ColliderCylinderInit sCylinderInit = {
    {
        COLTYPE_TREE,
        AT_NONE,
        AC_ON | AC_HARD | AC_TYPE_PLAYER,
        OC1_ON | OC1_TYPE_ALL,
        OC2_TYPE_1,
        COLSHAPE_CYLINDER,
    },
    {
        ELEMTYPE_UNK5, // wood 
        { 0x00000000, 0x00, 0x00 },
        //{ 0xF7CFFFFF, 0x00, 0x00 }, // ani
        { 0x0100020A, 0x00, 0x00 }, // wood2
        //{ 0x0FC0074A, 0x00, 0x00 }, // wood2 oot 
        TOUCH_NONE | TOUCH_SFX_NORMAL,
        BUMP_ON,
        OCELEM_ON,
    },
    { 30, 60, 0, { 0, 0, 0 } },
};

//void DmOpstage_SetupAction(DmOpstage* this, DmOpstageActionFunc actionFunc) {
    //this->actionFunc = actionFunc;
//}


void DmOpstage_Init(Actor* thisx, GlobalContext* globalCtx) {
    DmOpstage* this = THIS;

    Actor_ProcessInitChain(&this->dyna.actor, sInitChain);
    //DmOpstage_SetupAction(this, DmOpstage_FollowCutsceneScript);
    this->actionFunc = DmOpstage_FollowCutsceneScript;
    this->type = DMOPSTAGE_GET_TYPE(&this->dyna.actor);
    
    Actor_SetScale(&this->dyna.actor, 0.1f);
    if (this->type == DMOPSTAGE_TYPE_FLOOR) {
        DynaPolyActor_Init(&this->dyna, 0);
        DynaPolyActor_LoadMesh(globalCtx, &this->dyna, &gKeikokuDemoFloorColliderHeader);
    }

    //if (DMOPSTAGE_GET_TYPE(&this->dyna.actor) > DMOPSTAGE_TYPE_FLOOR) {
        //this->pos.x = this->dyna.actor.world.pos.x; // this offset lets us draw at center, but official pos is zero
        //this->pos.y = this->dyna.actor.world.pos.y;
        //this->pos.z = this->dyna.actor.world.pos.z;
        //this->dyna.actor.world.pos.x = 0.0f;
        //this->dyna.actor.world.pos.y = 0.0f;
        //this->dyna.actor.world.pos.z = 0.0f;
    //}
    this->dropType = DMOPSTAGE_GET_SUPERTYPE(thisx);
    if (this->dropType > DMOPSTAGE_SUPERTYPE_NONE) { // collider and tree bonk, maybe collectable drops
        Collider_InitAndSetCylinder(globalCtx, &this->collider, &this->dyna.actor, &sCylinderInit);
        Collider_UpdateCylinder(&this->dyna.actor, &this->collider);
        if (this->type == DMOPSTAGE_TYPE_ROOT_TREE){
            this->collider.dim.radius = 50;
        }

        // lol, because of course bonk detection is hardcoded in player code to only the trees
        // even if the code has to exist in player, they could have checked for collidertype, not actor ID
        thisx->id = ACTOR_EN_WOOD02;
        this->dyna.actor.home.rot.y = 0; // bonk detection
        this->actionFunc = DmOpstage_CheckBonk;
    }
  
}

void DmOpstage_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    DmOpstage* this = THIS;

    //if (DMOPSTAGE_GET_TYPE(&this->dyna.actor) == DMOPSTAGE_TYPE_FLOOR) {
    if (this->type == DMOPSTAGE_TYPE_FLOOR) {
        DynaPoly_DeleteBgActor(globalCtx, &globalCtx->colCtx.dyna, this->dyna.bgId);
    } else {
        Collider_DestroyCylinder(globalCtx, &this->collider);
    }
}

/*
void Debug_PrintToScreen(Actor* thisx, GlobalContext *globalCtx) {
    DmOpstage* this = THIS;
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
    GfxPrint_Printf(&printer, "actor struct: %X", &this);
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
} // */

// action func for collider type
void DmOpstage_CheckBonk(DmOpstage* this, GlobalContext* globalCtx) {
    if (this->dyna.actor.xzDistToPlayer < 400.0f){

        if (this->collider.base.acFlags & AC_HIT) {
            this->collider.base.acFlags &= ~AC_HIT;
            Actor_PlaySfxAtPos(&this->dyna.actor, NA_SE_IT_REFLECTION_WOOD);

        }

        if (this->dyna.actor.home.rot.y == 1){// && this->dropType > DMOPSTAGE_SUPERTYPE_NODROP) { // player changes our home rot if bonk was activated
            Vec3f dropSpawnPos = this->dyna.actor.world.pos;
            dropSpawnPos.y += 200.0f;

            if (this->dropType == DMOPSTAGE_SUPERTYPE_FAIRY) {
                Actor_PlaySfxAtPos(&this->dyna.actor, NA_SE_EV_BUTTERFRY_TO_FAIRY);
                Actor_Spawn(&globalCtx->actorCtx, globalCtx, ACTOR_EN_ELF, dropSpawnPos.x, dropSpawnPos.y, dropSpawnPos.z,
                     0, 0, 0, 0x9); // yellow fairy because its hte only one I found that doesnt snap to player height without modding , flag 0x800

            } else if (this->dropType == DMOPSTAGE_SUPERTYPE_DROPTABLE) {
                //Actor_PlaySfxAtPos(&this->dyna.actor, NA_SE_EV_BUTTERFRY_TO_FAIRY);
                Item_DropCollectibleRandom(globalCtx, &this->dyna.actor, &dropSpawnPos, (0xE << 4)); // drop table E
            }


            this->dropType = DMOPSTAGE_SUPERTYPE_NODROP; // no more
            this->dyna.actor.home.rot.y = 0;
        }


        Collider_UpdateCylinder(&this->dyna.actor, &this->collider);
        CollisionCheck_SetOC(globalCtx, &globalCtx->colChkCtx, &this->collider.base);
        CollisionCheck_SetAC(globalCtx, &globalCtx->colChkCtx, &this->collider.base);
    }
}

// actiontype for cutscene floor
void DmOpstage_FollowCutsceneScript(DmOpstage* this, GlobalContext* globalCtx) {
    s32 actionIndex;
    //u16 actorAction = DMOPSTAGE_GET_ACTORACTION(&this->dyna.actor) + 0x74;

    if (DMOPSTAGE_GET_TYPE(&this->dyna.actor) == DMOPSTAGE_TYPE_FLOOR) {
        if (Cutscene_CheckActorAction(globalCtx, 0x73)) {
            actionIndex = Cutscene_GetActorActionIndex(globalCtx, 0x73);
            if (globalCtx->csCtx.actorActions[actionIndex]->action == 2) {
                this->dyna.actor.scale.x = 0.075f;
                this->dyna.actor.scale.z = 0.3f;
            } else {
                this->dyna.actor.scale.x = 0.1f;
                this->dyna.actor.scale.z = 0.1f;
            }
            Cutscene_ActorTranslateAndYaw(&this->dyna.actor, globalCtx, actionIndex);
        }
    } else if (Cutscene_CheckActorAction(globalCtx, DMOPSTAGE_GET_ACTORACTION(&this->dyna.actor) + 0x74)) {
    //} else if (Cutscene_CheckActorAction(globalCtx, actorAction)) {
        Cutscene_ActorTranslateAndYaw(
            &this->dyna.actor, globalCtx,
            Cutscene_GetActorActionIndex(globalCtx, DMOPSTAGE_GET_ACTORACTION(&this->dyna.actor) + 0x74));
            //Cutscene_GetActorActionIndex(globalCtx, actorAction));
    }
}

void DmOpstage_Update(Actor* thisx, GlobalContext* globalCtx) {
    DmOpstage* this = THIS;

    this->actionFunc(this, globalCtx);
    if ((globalCtx->sceneNum == SCENE_SPOT00) && (gSaveContext.sceneSetupIndex == 0) &&
        (globalCtx->csCtx.frames == 480)) {
        func_8019F128(NA_SE_EV_NAVY_FLY_REBIRTH);
    }
}

void DmOpstage_Draw(Actor* thisx, GlobalContext* globalCtx) {
    DmOpstage* this = THIS;
    u8 type = DMOPSTAGE_GET_TYPE(&this->dyna.actor);

    if (this->type > DMOPSTAGE_TYPE_FLOOR) {
        // draw trees offcenter
        //Matrix_Translate(this->dyna.actor.world.pos.x + this->pos.x, this->dyna.actor.world.pos.y + this->pos.y,
                         //this->dyna.actor.world.pos.z + this->pos.z, MTXMODE_NEW);
        Matrix_Translate(this->dyna.actor.world.pos.x, this->dyna.actor.world.pos.y, this->dyna.actor.world.pos.z, MTXMODE_NEW);
        Matrix_RotateYS(this->dyna.actor.world.rot.y, MTXMODE_APPLY);
        Matrix_Scale(0.1f, 0.1f, 0.1f, MTXMODE_APPLY);
    }

    switch (this->type) {
        case DMOPSTAGE_TYPE_FLOOR:
            Gfx_DrawDListOpa(globalCtx, gKeikokuDemoFloorDL);
            //Gfx_DrawDListXlu(globalCtx, gKeikokuDemoFloorEmptyDL);
            break;

        case DMOPSTAGE_TYPE_ROOT_TREE:
            Gfx_DrawDListOpa(globalCtx, gKeikokuDemoTallTreeWithRootBaseDL);
            //Gfx_DrawDListXlu(globalCtx, gKeikokuDemoTallTreeWithRootBaseEmptyDL);
            break;

        case DMOPSTAGE_TYPE_CUT_TREE:
            Gfx_DrawDListOpa(globalCtx, gKeikokuDemoTallTreeCutDL);
            //Gfx_DrawDListXlu(globalCtx, gKeikokuDemoTallTreeCutEmptyDL);
            break;

        case DMOPSTAGE_TYPE_STRAIGHT_TREE:
            Gfx_DrawDListOpa(globalCtx, gKeikokuDemoTallTreeStraightDL);
            //Gfx_DrawDListXlu(globalCtx, gKeikokuDemoTallTreeStraightEmptyDL);
            break;
    }
    //Debug_PrintToScreen(thisx, globalCtx);
}
