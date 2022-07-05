/*
 * File: z_en_bu.c
 * Overlay: ovl_En_Bu
 * Description: Mimick that looks like a -------
 */

#include "z_en_bu.h"
#include "objects/object_box/object_box.h"
#include "objects/gameplay_keep/gameplay_keep.h"

#define FLAGS (ACTOR_FLAG_10 | ACTOR_FLAG_20)

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

static ColliderCylinderInit sCylinderInit = {
    {
        COLTYPE_NONE,
        AT_NONE | AT_TYPE_ENEMY,
        AC_ON | AC_TYPE_PLAYER,
        OC1_ON | OC1_TYPE_ALL,
        OC2_TYPE_1,
        COLSHAPE_CYLINDER,
    },
    {
        ELEMTYPE_UNK0,
        { 0xF7CFFFFF, 0x00, 0x10 },
        { 0xF7CFFFFF, 0x00, 0x00 },
        TOUCH_ON | TOUCH_SFX_NORMAL,
        BUMP_ON,
        OCELEM_ON,
    },
    { 30, 40, 0, { 0, 0, 0 } }, // ani
    //{ 35, 100, 5, { 0, 0, 0 } }, // bigpo
};

static CollisionCheckInfoInit sColChkInfoInit = { 3, 30, 40, 150 };


typedef enum {
  /* 0 */ MIMIC_DAMAGE_NOTHING,
  /* 1 */ MIMIC_DAMAGE_EXPLOSION, // hit with non-damage attack, first attack cannot giggle 
  /* 2 */ MIMIC_DAMAGE_,
  /* 3 */ MIMIC_DAMAGE_FIRE_ARROWS,
  /* 4 */ MIMIC_DAMAGE_LIGHT_ARROWS,
} MimicDamageTypes;

static DamageTable sDamageTable = {
    /* Deku Nut       */ DMG_ENTRY(0, MIMIC_DAMAGE_NOTHING),
    /* Deku Stick     */ DMG_ENTRY(0, MIMIC_DAMAGE_NOTHING),
    /* Horse trample  */ DMG_ENTRY(0, MIMIC_DAMAGE_NOTHING),
    /* Explosives     */ DMG_ENTRY(1, MIMIC_DAMAGE_EXPLOSION),
    /* Zora boomerang */ DMG_ENTRY(0, MIMIC_DAMAGE_NOTHING),
    /* Normal arrow   */ DMG_ENTRY(0, MIMIC_DAMAGE_NOTHING),
    /* UNK_DMG_0x06   */ DMG_ENTRY(0, MIMIC_DAMAGE_NOTHING),
    ///* Hookshot       */ DMG_ENTRY(0, 0xF),
    /* Hookshot       */ DMG_ENTRY(0, MIMIC_DAMAGE_NOTHING), // we want to hookshot to the chest even if its a mimic
    /* Goron punch    */ DMG_ENTRY(1, MIMIC_DAMAGE_EXPLOSION),
    /* Sword          */ DMG_ENTRY(0, MIMIC_DAMAGE_NOTHING),
    /* Goron pound    */ DMG_ENTRY(1, MIMIC_DAMAGE_EXPLOSION),
    /* Fire arrow     */ DMG_ENTRY(1, MIMIC_DAMAGE_NOTHING),
    /* Ice arrow      */ DMG_ENTRY(0, MIMIC_DAMAGE_NOTHING),
    /* Light arrow    */ DMG_ENTRY(2, MIMIC_DAMAGE_LIGHT_ARROWS),
    /* Goron spikes   */ DMG_ENTRY(0, MIMIC_DAMAGE_EXPLOSION),
    /* Deku spin      */ DMG_ENTRY(0, MIMIC_DAMAGE_NOTHING),
    /* Deku bubble    */ DMG_ENTRY(0, MIMIC_DAMAGE_NOTHING),
    /* Deku launch    */ DMG_ENTRY(2, MIMIC_DAMAGE_NOTHING),
    /* UNK_DMG_0x12   */ DMG_ENTRY(0, MIMIC_DAMAGE_NOTHING),
    /* Zora barrier   */ DMG_ENTRY(1, 0x2),
    /* Normal shield  */ DMG_ENTRY(0, MIMIC_DAMAGE_NOTHING),
    /* Light ray      */ DMG_ENTRY(0, MIMIC_DAMAGE_NOTHING),
    /* Thrown object  */ DMG_ENTRY(0, MIMIC_DAMAGE_NOTHING),
    /* Zora punch     */ DMG_ENTRY(0, MIMIC_DAMAGE_NOTHING),
    /* Spin attack    */ DMG_ENTRY(0, MIMIC_DAMAGE_NOTHING),
    /* Sword beam     */ DMG_ENTRY(1, MIMIC_DAMAGE_NOTHING),
    /* Normal Roll    */ DMG_ENTRY(0, MIMIC_DAMAGE_NOTHING),
    /* UNK_DMG_0x1B   */ DMG_ENTRY(0, MIMIC_DAMAGE_NOTHING),
    /* UNK_DMG_0x1C   */ DMG_ENTRY(0, MIMIC_DAMAGE_NOTHING),
    /* Unblockable    */ DMG_ENTRY(1, MIMIC_DAMAGE_NOTHING),
    /* UNK_DMG_0x1E   */ DMG_ENTRY(0, MIMIC_DAMAGE_NOTHING),
    /* Powder Keg     */ DMG_ENTRY(1, MIMIC_DAMAGE_EXPLOSION),
};



void EnBu_Init(Actor* thisx, GlobalContext* globalCtx) {
    EnBu* this = THIS;
    CollisionHeader* colHeader;

    f32 animFrame;
    f32 animFrameEnd;

    animFrame = 0.0f;
    animFrameEnd = Animation_GetLastFrame(&gBoxChestOpenAnim);

    DynaPolyActor_Init(&this->dyna, 0);
    CollisionHeader_GetVirtual(&gBoxChestCol, &colHeader);
    this->dyna.actor.colChkInfo.health = 10;
    this->alpha = 255;

    this->dyna.bgId = DynaPoly_SetBgActor(globalCtx, &globalCtx->colCtx.dyna, &this->dyna.actor, colHeader);
    this->dyna.actor.gravity = -5.5f;
    this->dyna.actor.terminalVelocity = -50.0f;
    this->dyna.actor.floorHeight = this->dyna.actor.world.pos.y;

    SkelAnime_Init(globalCtx, &this->skelAnime, &gBoxChestSkel, &gBoxChestOpenAnim, this->jointTable, this->morphTable,
                   OBJECT_BOX_CHEST_LIMB_MAX);
    Animation_Change(&this->skelAnime, &gBoxChestOpenAnim, 1.5f, animFrame, animFrameEnd, ANIMMODE_ONCE, 0.0f);

    this->actionFunc = EnBu_WaitClosed;

    Collider_InitAndSetCylinder(globalCtx, &this->collider, &this->dyna.actor, &sCylinderInit);
    CollisionCheck_SetInfo(&this->dyna.actor.colChkInfo, &sDamageTable, &sColChkInfoInit);


    MIMIC_FLAGS(this) = MIMIC_FLAG_CLEAR;
}

void EnBu_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    EnBu* this = THIS;

    DynaPoly_DeleteBgActor(globalCtx, &globalCtx->colCtx.dyna, this->dyna.bgId);
    Collider_DestroyCylinder(globalCtx, &this->collider);

}

// todo finish these
void EnBu_Dissappear(EnBu* this, GlobalContext* globalCtx) {
    Item_DropCollectibleRandom(globalCtx, &this->dyna.actor, &this->dyna.actor.world.pos, 0x10);

    Actor_MarkForDeath(&this->dyna.actor);
}

//void EnBu_SetupDissapear(EnBu* this) {
    //this->actionFunc = EnBu_Dissappear;
//}

#define BU_START_TIMER 20

void EnBu_BurnAway(EnBu* this, GlobalContext* globalCtx) {
    static Vec3f D_80BFB2E8 = { 0.0f, 0.5f, 0.0f };
    Vec3f effectPos;
    
    if (DECR(this->stateTimer) <= 0){
        this->actionFunc = EnBu_Dissappear;
        //Actor_MarkForDeath(&this->dyna.actor);
    }

    Math_StepToF(&this->dyna.actor.scale.x, 0.0f, 0.0005f);
    Math_StepToF(&this->dyna.actor.scale.y, 0.0f, 0.0005f);
    Math_StepToF(&this->dyna.actor.scale.z, 0.0f, 0.0005f);


    // spawn effect every frame
    effectPos.x = randPlusMinusPoint5Scaled(60.0f) + this->dyna.actor.world.pos.x;
    effectPos.z = randPlusMinusPoint5Scaled(60.0f) + this->dyna.actor.world.pos.z;
    effectPos.y = randPlusMinusPoint5Scaled(50.0f) + (this->dyna.actor.world.pos.y + 20.0f);
    func_800B3030(globalCtx, &effectPos, &D_80BFB2E8, &D_80BFB2E8, 100, 0, 2); // flames ghosts have on death

    func_800B9010(&this->dyna.actor, NA_SE_EN_COMMON_EXTINCT_LEV - SFX_FLAG); //Bigpo
}

void EnBu_SetupBurnAway(EnBu* this) {
    this->stateTimer = BU_START_TIMER;
    this->actionFunc = EnBu_BurnAway;
}

// every frame, check if we can take damage
// comes after bonk
void EnBu_CheckDamage(EnBu* this, GlobalContext* globalCtx){
    if ((this->collider.base.acFlags & AC_HIT)) {
        this->collider.base.acFlags &= ~AC_HIT;

        if (this->dyna.actor.colChkInfo.damageEffect > 0){
            Actor_ApplyDamage(&this->dyna.actor);
            if ( this->dyna.actor.colChkInfo.health == 0) {
            
                Actor_PlaySfxAtPos(&this->dyna.actor, NA_SE_EN_PO_DEAD);
                //Actor_PlaySfxAtPos(&this->dyna.actor, NA_SE_EN_EXTINCT);
                //Enemy_StartFinishingBlow(globalCtx, &this->dyna.actor);
                EnBu_SetupBurnAway(this);
            }else if (this->dyna.actor.colChkInfo.damage > 0){ 
                //Audio_PlaySfxAtPos(&this->dyna.actor.projectedPos, NA_SE_EN_PO_DAMAGE);
                Audio_PlaySfxAtPos(&this->dyna.actor.projectedPos, NA_SE_EN_EYEGOLE_ATTACK);
            }

            if (this->dyna.actor.colChkInfo.damageEffect == MIMIC_DAMAGE_LIGHT_ARROWS) { // light arrows
                Actor_Spawn(&globalCtx->actorCtx, globalCtx, ACTOR_EN_CLEAR_TAG, this->collider.info.bumper.hitPos.x,
                            this->collider.info.bumper.hitPos.y, this->collider.info.bumper.hitPos.z, 0, 0, 0,
                            CLEAR_TAG_LARGE_LIGHT_RAYS);
            }
        //} else {
            // no effect, wrong attack type
            MIMIC_FLAGS(this) |= MIMIC_FLAG_PREVIOUSLY_NOTICED;

        }

    } else if (this->dyna.actor.xzDistToPlayer < 1000 ){ // free laugh
        Player* player = GET_PLAYER(globalCtx); 
        if (player->invincibilityTimer > 0){
  
            if (!(MIMIC_FLAGS(this) & MIMIC_FLAG_PREVIOUSLY_LAUGHED) && (MIMIC_FLAGS(this) & MIMIC_FLAG_PREVIOUSLY_NOTICED)) {
                Audio_PlaySfxAtPos(&this->dyna.actor.projectedPos, NA_SE_EN_PO_LAUGH);
                MIMIC_FLAGS(this) |= MIMIC_FLAG_PREVIOUSLY_LAUGHED;
            } else {
                MIMIC_FLAGS(this) |= MIMIC_FLAG_PREVIOUSLY_NOTICED;
            }
        }
    }

    Collider_UpdateCylinder(&this->dyna.actor, &this->collider);
    // do we really need this every time?
    CollisionCheck_SetAC(globalCtx, &globalCtx->colChkCtx, &this->collider.base);
}

void EnBu_CheckBonk(EnBu* this, GlobalContext* globalCtx){

    // detect bonk
    if ( this->dyna.actor.xzDistToPlayer < 200 && (globalCtx->actorCtx.unk1F5 != 0) && (globalCtx->actorCtx.unk1F4 == 0 || globalCtx->actorCtx.unk1F4 == 2)){ 
        Player* player = GET_PLAYER(globalCtx); // unfortunately bonk detection also detects damage to player
        if (player->invincibilityTimer > 0){
            return;
        }

        if ((MIMIC_FLAGS(this) & MIMIC_FLAG_PREVIOUSLY_NOTICED) && !(MIMIC_FLAGS(this) & MIMIC_FLAG_PREVIOUSLY_LAUGHED)) {
            s32 randomChance = ((s32)Rand_ZeroFloat(5)) % 5;

            if (randomChance == 4) {
                Audio_PlaySfxAtPos(&this->dyna.actor.projectedPos, NA_SE_EN_PO_LAUGH);
                MIMIC_FLAGS(this) |= MIMIC_FLAG_PREVIOUSLY_LAUGHED;
            }
            //random chance of sinister laugh
        } else {
            MIMIC_FLAGS(this) |= MIMIC_FLAG_PREVIOUSLY_NOTICED;
        }
    }
}


// never mind that we dont actually open
// TODO we want to make some minor sound if hit with a sword but only sometime
// TODO we want to turn to face the player if they are dancing as kamaro
// we want to take damage from bombs/light arrow/fire arrow
void EnBu_WaitClosed(EnBu* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);
    Vec3f offset;

    Actor_OffsetOfPointInActorCoords(&this->dyna.actor, &offset, &player->actor.world.pos);
    if (offset.z > -50.0f && offset.z < 0.0f && fabsf(offset.y) < 10.0f && fabsf(offset.x) < 20.0f &&
        Player_IsFacingActor(&this->dyna.actor, 0x3000, globalCtx)) {

        //this->dyna.actor.id = ACTOR_EN_BOX;
        Actor_PickUpNearby(&this->dyna.actor, globalCtx, 0); // real fake doors

        if (this->dyna.actor.parent != NULL){ // successful pickup
            Audio_PlaySfxAtPos(&this->dyna.actor.projectedPos, NA_SE_EN_PO_LAUGH);
        }
    }

    EnBu_CheckBonk(this, globalCtx);

}

void EnBu_Update(Actor* thisx, GlobalContext* globalCtx) {
    EnBu* this = THIS;

    //Actor_MoveWithGravity(&this->actor);

    this->actionFunc(this, globalCtx);
    EnBu_CheckDamage(this, globalCtx);
}

/*
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
    //GfxPrint_Printf(&printer, "flags: %X", this->alpha);
    GfxPrint_Printf(&printer, "flags: %X", MIMIC_FLAGS(THIS));
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
} // */

void EnBu_PostLimbDraw(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3s* rot, Actor* thisx, Gfx** gfx) {
    s32 pad;
    EnBu* this = THIS;

    OPEN_DISPS(globalCtx->state.gfxCtx);


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

    CLOSE_DISPS(globalCtx->state.gfxCtx);

} // */

// why did chest need to be so weird..
Gfx* EnBu_SetRenderMode1(GraphicsContext* gfxCtx) {
    Gfx* dl = GRAPH_ALLOC(gfxCtx, sizeof(Gfx) * 2);

    gSPEndDisplayList(dl);
    return dl;
}

void EnBu_Draw(Actor* thisx, GlobalContext* globalCtx) {
    EnBu* this = THIS;


    // works but opa only
    OPEN_DISPS(globalCtx->state.gfxCtx);
    gDPPipeSync(POLY_OPA_DISP++);
    gDPSetEnvColor(POLY_OPA_DISP++, 0, 0, 0, 255);
    gSPSegment(POLY_OPA_DISP++, 0x08, EnBu_SetRenderMode1(globalCtx->state.gfxCtx));
    func_8012C28C(globalCtx->state.gfxCtx);
    POLY_OPA_DISP = SkelAnime_Draw(globalCtx, this->skelAnime.skeleton, this->skelAnime.jointTable, NULL,
                                       EnBu_PostLimbDraw, &this->dyna.actor, POLY_OPA_DISP);

    // draws correctly except no xlu transparency working
    //Gfx* dispHead;
    //OPEN_DISPS(globalCtx->state.gfxCtx);
    //dispHead = POLY_XLU_DISP;
    //gSPDisplayList(dispHead, &sSetupDL[6 * 0x19]); // required to draw the textures
    //gSPSegment(&dispHead[1], 0x0C, &D_801AEF88); // transparency display list
    //gSPSegment(&dispHead[2], 0x08,
               //Gfx_EnvColor(globalCtx->state.gfxCtx, 255, 255, 255,
                            //this->alpha));
    //POLY_XLU_DISP = SkelAnime_Draw(globalCtx, this->skelAnime.skeleton, this->skelAnime.jointTable,
                                   //NULL, EnBu_PostLimbDraw, &this->dyna.actor, &dispHead[3]);
                                   ////NULL, NULL, &this->dyna.actor, &dispHead[3]);
 
    // TODO finish this
    //Actor_DrawDamageEffects(globalCtx, &this->actor, this->limbPos, ARRAY_COUNT(this->limbPos), this->drawDmgEffScale,
                            //this->drawDmgEffFrozenSteamScale, this->drawDmgEffAlpha, this->drawDmgEffType);


    CLOSE_DISPS(globalCtx->state.gfxCtx);
    //Debug_PrintToScreen(thisx, globalCtx);
}
