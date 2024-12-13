/*
 * File: z_en_bubble.c
 * Overlay: ovl_En_Bubble
 * Description: Shabom (unused)
 */

#include "z_en_bubble.h"

#define FLAGS (ACTOR_FLAG_ATTENTION_ENABLED)

#define THIS ((EnBubble*)thisx)

void EnBubble_Init(Actor* thisx, PlayState* play);
void EnBubble_Destroy(Actor* thisx, PlayState* play);
void EnBubble_Update(Actor* thisx, PlayState* play);
void EnBubble_Draw(Actor* thisx, PlayState* play);

void EnBubble_Wait(EnBubble* this, PlayState* play);
void EnBubble_Pop(EnBubble* this, PlayState* play);
void EnBubble_Regrow(EnBubble* this, PlayState* play);

ActorProfile En_Bubble_Profile = {
    /**/ ACTOR_EN_BUBBLE,
    /**/ ACTORCAT_ENEMY,
    /**/ FLAGS,
    /**/ OBJECT_BUBBLE,
    /**/ sizeof(EnBubble),
    /**/ EnBubble_Init,
    /**/ EnBubble_Destroy,
    /**/ EnBubble_Update,
    /**/ EnBubble_Draw,
};

// z64collision.h contains the flags
// search #define DMG_DEKU_NUT to find the code for which flag is which

static ColliderJntSphElementInit sJntSphElementsInit[2] = {
    {
        {   // damage take collider
            ELEM_MATERIAL_UNK0,
            { 0x00000000, 0x00, 0x04 },
            //{ 0xF7CFD757, 0x00, 0x00 }, // vanilla
            { 0xF7CFD777, 0x00, 0x00 },
            ATELEM_NONE | ATELEM_SFX_NORMAL,
            ACELEM_ON,
            OCELEM_ON,
        },
        { 0, { { 0, 0, 0 }, 16 }, 100 },
    },
    {
        {   // collider for detecting non-damage, this one is for wiggling on bad damage attack
            ELEM_MATERIAL_UNK0,
            { 0x00000000, 0x00, 0x00 },   // atDmgInfo
            //{ 0x00002820, 0x00, 0x00 }, // acDmgInfo (vanilla)
            // removal: 0x20 is arrow, 0x800 is fire arrow, 0x3000 is ice/light arrow
            // add: 0x100 is goron punch, 0x10000 is deku spit, 0x100000 is regular shield
            { 0x00110100, 0x00, 0x00 },   // acDmgInfo
            ATELEM_NONE | ATELEM_SFX_NORMAL,
            ACELEM_ON | ACELEM_NO_AT_INFO | ACELEM_NO_DAMAGE | ACELEM_NO_SWORD_SFX | ACELEM_NO_HITMARK,
            OCELEM_NONE,
        },
        { 0, { { 0, 0, 0 }, 16 }, 100 },
    },
};

static ColliderJntSphInit sJntSphInit = {
    {
        COL_MATERIAL_HIT6,
        AT_ON | AT_TYPE_ENEMY,
        AC_ON | AC_TYPE_PLAYER,
        OC1_ON | OC1_TYPE_ALL,
        OC2_TYPE_1,
        COLSHAPE_JNTSPH,
    },
    ARRAY_COUNT(sJntSphElementsInit),
    sJntSphElementsInit,
};

static CollisionCheckInfoInit2 sColChkInfoInit = { 1, 2, 25, 25, MASS_IMMOVABLE };

void EnBubble_SetDimensions(EnBubble* this, f32 dim) {
    f32 x;
    f32 y;
    f32 z;
    f32 norm;

    this->actor.flags |= ACTOR_FLAG_ATTENTION_ENABLED;
    Actor_SetScale(&this->actor, 1.0f);
    this->actor.shape.yOffset = 16.0f;
    this->modelRotSpeed = 16.0f;
    this->modelEllipticity = 0.08f;
    this->modelWidth = dim;
    this->modelHeight = dim;
    x = Rand_ZeroOne();
    y = Rand_ZeroOne();
    z = Rand_ZeroOne();
    this->unk_210 = 1.0f;
    this->unk_214 = 1.0f;
    norm = SQ(x) + SQ(y) + SQ(z);
    this->unk1F8.x = x / norm;
    this->unk1F8.y = y / norm;
    this->unk1F8.z = z / norm;
}

s32 func_8089F59C(EnBubble* this) {
    ColliderElement* elem = &this->colliderSphere.elements[0].base;

    elem->atDmgInfo.dmgFlags = DMG_EXPLOSIVES;
    elem->atDmgInfo.effect = 0;
    elem->atDmgInfo.damage = 4;
    elem->atElemFlags = ATELEM_ON;
    this->actor.velocity.y = 0.0f;
    return 6;
}

s32 func_8089F5D0(EnBubble* this) {
    EnBubble_SetDimensions(this, -1.0f);
    return 12;
}

void EnBubble_DamagePlayer(EnBubble* this, PlayState* play) {
    play->damagePlayer(play, -this->colliderSphere.elements[0].base.atDmgInfo.damage);
    func_800B8E1C(play, &this->actor, 6.0f, this->actor.yawTowardsPlayer, 6.0f);
}

s32 EnBubble_Explosion(EnBubble* this, PlayState* play) {
    static Color_RGBA8 sEffectPrimColor = { 255, 255, 255, 255 };
    static Color_RGBA8 sEffectEnvColor = { 150, 150, 150, 0 };
    s32 i;
    Vec3f effectAccel = { 0.0f, -0.5f, 0.0f };
    Vec3f effectVelocity;
    Vec3f effectPos;

    Math_SmoothStepToF(&this->modelWidth, 4.0f, 0.1f, 1000.0f, 0.0f);
    Math_SmoothStepToF(&this->modelHeight, 4.0f, 0.1f, 1000.0f, 0.0f);
    Math_SmoothStepToF(&this->modelRotSpeed, 54.0f, 0.1f, 1000.0f, 0.0f);
    Math_SmoothStepToF(&this->modelEllipticity, 0.2f, 0.1f, 1000.0f, 0.0f);
    this->actor.shape.yOffset = (this->modelHeight + 1.0f) * 16.0f;

    if (DECR(this->explosionCountdown) != 0) {
        return -1;
    }
    effectPos.x = this->actor.world.pos.x;
    effectPos.y = this->actor.world.pos.y + this->actor.shape.yOffset;
    effectPos.z = this->actor.world.pos.z;
    for (i = 0; i < 20; i++) {
        effectVelocity.x = (Rand_ZeroOne() - 0.5f) * 7.0f;
        effectVelocity.y = Rand_ZeroOne() * 7.0f;
        effectVelocity.z = (Rand_ZeroOne() - 0.5f) * 7.0f;
        EffectSsDtBubble_SpawnCustomColor(play, &effectPos, &effectVelocity, &effectAccel, &sEffectPrimColor,
                                          &sEffectEnvColor, Rand_S16Offset(100, 50), 25, 0);
    }
    Item_DropCollectibleRandom(play, NULL, &this->actor.world.pos, 0x50);
    this->actor.flags &= ~ACTOR_FLAG_ATTENTION_ENABLED;
    return Rand_S16Offset(90, 60);
}

s32 func_8089F8BC(EnBubble* this) {
    if (DECR(this->explosionCountdown) != 0) {
        return -1;
    } else {
        return func_8089F5D0(this);
    }
}

s32 func_8089F908(EnBubble* this) {
    this->modelWidth += 1.0f / 12.0f;
    this->modelHeight += 1.0f / 12.0f;

    if (DECR(this->explosionCountdown) != 0) {
        return false;
    } else {
        return true;
    }
}

void EnBubble_Vec3fNormalizedReflect(Vec3f* vec1, Vec3f* vec2, Vec3f* dest) {
    f32 norm;

    Math3D_Vec3fReflect(vec1, vec2, dest);
    norm = sqrtf(SQ(dest->x) + SQ(dest->y) + SQ(dest->z));
    if (norm != 0.0f) {
        dest->x /= norm;
        dest->y /= norm;
        dest->z /= norm;
    } else {
        dest->x = dest->y = dest->z = 0.0f;
    }
}

void EnBubble_Vec3fNormalize(Vec3f* vec) {
    f32 norm = sqrtf(SQ(vec->x) + SQ(vec->y) + SQ(vec->z));

    if (norm != 0.0f) {
        vec->x /= norm;
        vec->y /= norm;
        vec->z /= norm;
    } else {
        vec->x = vec->y = vec->z = 0.0f;
    }
}

void EnBubble_Fly(EnBubble* this, PlayState* play) {
    CollisionPoly* poly;
    Actor* bumpActor;
    Vec3f sp84;
    Vec3f curPos;
    Vec3f nextBouncePos;
    Vec3f normal;
    Vec3f bounceDirection;
    f32 bounceSpeed;
    s32 bgId;
    u8 bounceCount;

    if (this->colliderSphere.elements[1].base.acElemFlags & ACELEM_HIT) {
        bumpActor = this->colliderSphere.base.ac;
        this->normalizedBumpVelocity = bumpActor->velocity;
        EnBubble_Vec3fNormalize(&this->normalizedBumpVelocity);
        this->velocityFromBump.x += this->normalizedBumpVelocity.x * 3.0f;
        this->velocityFromBump.y += this->normalizedBumpVelocity.y * 3.0f;
        this->velocityFromBump.z += this->normalizedBumpVelocity.z * 3.0f;
    }
    this->yVelocity -= 0.1f;
    if (this->yVelocity < this->actor.terminalVelocity) {
        this->yVelocity = this->actor.terminalVelocity;
    }
    bounceDirection.x = this->velocityFromBounce.x + this->velocityFromBump.x;
    bounceDirection.y = this->velocityFromBounce.y + this->velocityFromBump.y + this->yVelocity;
    bounceDirection.z = this->velocityFromBounce.z + this->velocityFromBump.z;
    EnBubble_Vec3fNormalize(&bounceDirection);

    curPos.x = this->actor.world.pos.x;
    curPos.y = this->actor.world.pos.y + this->actor.shape.yOffset;
    curPos.z = this->actor.world.pos.z;
    nextBouncePos = curPos;

    nextBouncePos.x += (bounceDirection.x * 24.0f);
    nextBouncePos.y += (bounceDirection.y * 24.0f);
    nextBouncePos.z += (bounceDirection.z * 24.0f);
    if (BgCheck_EntityLineTest1(&play->colCtx, &curPos, &nextBouncePos, &sp84, &poly, true, true, true, false, &bgId)) {
        normal.x = COLPOLY_GET_NORMAL(poly->normal.x);
        normal.y = COLPOLY_GET_NORMAL(poly->normal.y);
        normal.z = COLPOLY_GET_NORMAL(poly->normal.z);
        EnBubble_Vec3fNormalizedReflect(&bounceDirection, &normal, &bounceDirection);
        this->bounceDirection = bounceDirection;
        bounceCount = this->bounceCount;
        this->bounceCount = ++bounceCount;
        if (bounceCount > TRUNCF_BINANG(Rand_ZeroOne() * 10.0f)) {
            this->bounceCount = 0;
        }
        bounceSpeed = (this->bounceCount == 0) ? 3.6000001f : 3.0f;
        this->velocityFromBump.x = this->velocityFromBump.y = this->velocityFromBump.z = 0.0f;
        this->velocityFromBounce.x = this->bounceDirection.x * bounceSpeed;
        this->velocityFromBounce.y = this->bounceDirection.y * bounceSpeed;
        this->velocityFromBounce.z = this->bounceDirection.z * bounceSpeed;
        this->yVelocity = 0.0f;
        Actor_PlaySfx(&this->actor, NA_SE_EN_AWA_BOUND);
        this->modelRotSpeed = 128.0f;
        this->modelEllipticity = 0.48f;
    } else if ((this->actor.bgCheckFlags & BGCHECKFLAG_WATER) && (bounceDirection.y < 0.0f)) {
        normal.x = normal.z = 0.0f;
        normal.y = 1.0f;
        EnBubble_Vec3fNormalizedReflect(&bounceDirection, &normal, &bounceDirection);
        this->bounceDirection = bounceDirection;
        bounceCount = this->bounceCount;
        this->bounceCount = ++bounceCount;
        if (bounceCount > TRUNCF_BINANG(Rand_ZeroOne() * 10.0f)) {
            this->bounceCount = 0;
        }
        bounceSpeed = (this->bounceCount == 0) ? 3.6000001f : 3.0f;
        this->velocityFromBump.x = this->velocityFromBump.y = this->velocityFromBump.z = 0.0f;
        this->velocityFromBounce.x = (this->bounceDirection.x * bounceSpeed);
        this->velocityFromBounce.y = (this->bounceDirection.y * bounceSpeed);
        this->velocityFromBounce.z = (this->bounceDirection.z * bounceSpeed);
        this->yVelocity = 0.0f;
        Actor_PlaySfx(&this->actor, NA_SE_EN_AWA_BOUND);
        this->modelRotSpeed = 128.0f;
        this->modelEllipticity = 0.48f;
    }
    // this is different from above when we calculate position as the actor wants to gain momentum not just keep it
    this->actor.velocity.x = this->velocityFromBounce.x + this->velocityFromBump.x;
    this->actor.velocity.y = this->velocityFromBounce.y + this->velocityFromBump.y + this->yVelocity;
    this->actor.velocity.z = this->velocityFromBounce.z + this->velocityFromBump.z;
    Math_ApproachF(&this->velocityFromBump.x, 0.0f, 0.3f, 0.1f);
    Math_ApproachF(&this->velocityFromBump.y, 0.0f, 0.3f, 0.1f);
    Math_ApproachF(&this->velocityFromBump.z, 0.0f, 0.3f, 0.1f);
}

s32 func_8089FF30(EnBubble* this) {
    if (((this->colliderSphere.base.acFlags & AC_HIT) != 0) == false) {
        return false;
    }
    this->colliderSphere.base.acFlags &= ~AC_HIT;
    if (this->colliderSphere.elements[1].base.acElemFlags & ACELEM_HIT) {
        this->unk1F4.x = this->colliderSphere.base.ac->velocity.x / 10.0f;
        this->unk1F4.y = this->colliderSphere.base.ac->velocity.y / 10.0f;
        this->unk1F4.z = this->colliderSphere.base.ac->velocity.z / 10.0f;
        this->modelRotSpeed = 128.0f;
        this->modelEllipticity = 0.48f;
        return false;
    }
    this->timer = 8;
    return true;
}

s32 EnBubble_IsPopped(EnBubble* this, PlayState* play) {
    if ((DECR(this->timer) != 0) || (this->actionFunc == EnBubble_Pop)) {
        return false;
    }
    if (this->colliderSphere.base.ocFlags2 & OC2_HIT_PLAYER) {
        this->colliderSphere.base.ocFlags2 &= ~OC2_HIT_PLAYER;
        EnBubble_DamagePlayer(this, play);
        this->timer = 8;
        return true;
    }
    return func_8089FF30(this);
}

void func_808A005C(EnBubble* this) {
    ColliderJntSphElementDim* dim = &this->colliderSphere.elements[0].dim;
    Vec3f src;
    Vec3f dest;

    src.x = dim->modelSphere.center.x;
    src.y = dim->modelSphere.center.y;
    src.z = dim->modelSphere.center.z;

    Matrix_MultVec3f(&src, &dest);
    dim->worldSphere.center.x = dest.x;
    dim->worldSphere.center.y = dest.y;
    dim->worldSphere.center.z = dest.z;
    dim->worldSphere.radius = dim->modelSphere.radius * (1.0f + this->modelWidth);
    this->colliderSphere.elements[1].dim = *dim;
}

/*
 * this looks very simple but stuck in inf loop, weird
u16 EnBubble2_FindNearbyEnemies(Actor* thisx, PlayState* play){
  unsigned short count;
  Actor *actor = play->actorCtx.actorLists[ACTORCAT_ENEMY].first;
  
  while (actor != NULL) {
      count++;
      actor = actor->next;
  }   

  return count;
} // */

// we want to increase difficulty by increasing volume a bit
void EnBubble2_CheckAndSpawnMore(Actor* thisx, PlayState* play){
    // if type is X
    unsigned int spawnCount = thisx->params;

    if (thisx->params == 0 // random possible selected
         || (play->sceneId == SCENE_HAKASHITA && thisx->room != 3) // one of the "boss rooms"
         || (play->sceneId == SCENE_KAKUSIANA && thisx->room == 13 || thisx->room == 7) // grotto peahat or dodongo
         || (play->sceneId == SCENE_MITURIN && thisx->room == 4 || thisx->room == 6)){ // miniboss rooms of woodfall temple
 
      spawnCount = Rand_S16Offset(0, 5); // randomly select a count from 0 to 5

      // search for nearby
      //unsigned int nearbyEnemyCount = EnBubble2_FindNearbyEnemies(thisx, play);
      //spawnCount -= nearbyEnemyCount;

    }

    while(spawnCount > 0){
      Actor_Spawn(&play->actorCtx, play, ACTOR_EN_BUBBLE,
         thisx->world.pos.x, thisx->world.pos.y, thisx->world.pos.z,
         thisx->world.rot.x, thisx->world.rot.y, thisx->world.rot.z,
         -1);
      spawnCount--;
    }
}

static DamageTable sDamageTable = {
    /* Deku Nut       */ DMG_ENTRY(1, 0xF),
    /* Deku Stick     */ DMG_ENTRY(1, 0x0),
    /* Horse trample  */ DMG_ENTRY(1, 0x0),
    /* Explosives     */ DMG_ENTRY(1, 0x0),
    /* Zora boomerang */ DMG_ENTRY(1, 0x0),
    /* Normal arrow   */ DMG_ENTRY(1, 0x0),
    /* UNK_DMG_0x06   */ DMG_ENTRY(0, 0x0),
    /* Hookshot       */ DMG_ENTRY(1, 0xE),
    /* Goron punch    */ DMG_ENTRY(0, 0x0),
    /* Sword          */ DMG_ENTRY(1, 0x0),
    /* Goron pound    */ DMG_ENTRY(0, 0x0),
    /* Fire arrow     */ DMG_ENTRY(1, 0x0),
    /* Ice arrow      */ DMG_ENTRY(1, 0x0),
    /* Light arrow    */ DMG_ENTRY(2, 0x4),
    /* Goron spikes   */ DMG_ENTRY(1, 0x0),
    /* Deku spin      */ DMG_ENTRY(1, 0x0),
    /* Deku bubble    */ DMG_ENTRY(1, 0x0),
    /* Deku launch    */ DMG_ENTRY(2, 0x0),
    /* UNK_DMG_0x12   */ DMG_ENTRY(0, 0x1),
    /* Zora barrier   */ DMG_ENTRY(1, 0x0),
    /* Normal shield  */ DMG_ENTRY(0, 0x0),
    /* Light ray      */ DMG_ENTRY(0, 0x0),
    /* Thrown object  */ DMG_ENTRY(1, 0x0),
    /* Zora punch     */ DMG_ENTRY(1, 0x0),
    /* Spin attack    */ DMG_ENTRY(1, 0x0),
    /* Sword beam     */ DMG_ENTRY(1, 0x0),
    /* Normal Roll    */ DMG_ENTRY(1, 0x0),
    /* UNK_DMG_0x1B   */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1C   */ DMG_ENTRY(0, 0x0),
    /* Unblockable    */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1E   */ DMG_ENTRY(0, 0x0),
    /* Powder Keg     */ DMG_ENTRY(1, 0x0),
};


void EnBubble_Init(Actor* thisx, PlayState* play) {
    //s32 pad;
    EnBubble* this = THIS;

    if (thisx->params >= 0) EnBubble2_CheckAndSpawnMore(thisx, play); 

    ActorShape_Init(&this->actor.shape, 16.0f, ActorShadow_DrawCircle, 0.2f);
    Collider_InitJntSph(play, &this->colliderSphere);
    Collider_SetJntSph(play, &this->colliderSphere, &this->actor, &sJntSphInit, this->colliderElements);

    //CollisionCheck_SetInfo2(&this->actor.colChkInfo, DamageTable_Get(9), &sColChkInfoInit);
    CollisionCheck_SetInfo2(&this->actor.colChkInfo, &sDamageTable, &sColChkInfoInit);
    //! @bug: hint Id not correctly migrated from OoT `NAVI_ENEMY_SHABOM`
    this->actor.hintId = TATL_HINT_ID_IGOS_DU_IKANA;
    this->bounceDirection.x = Rand_ZeroOne();
    this->bounceDirection.y = Rand_ZeroOne();
    this->bounceDirection.z = Rand_ZeroOne();
    EnBubble_Vec3fNormalize(&this->bounceDirection);
    this->velocityFromBounce.x = this->bounceDirection.x * 3.0f;
    this->velocityFromBounce.y = this->bounceDirection.y * 3.0f;
    this->velocityFromBounce.z = this->bounceDirection.z * 3.0f;
    EnBubble_SetDimensions(this, 0);
    this->actionFunc = EnBubble_Wait;
}

void EnBubble_Destroy(Actor* thisx, PlayState* play) {
    EnBubble* this = (EnBubble*)thisx;

    Collider_DestroyJntSph(play, &this->colliderSphere);
}

void EnBubble_Wait(EnBubble* this, PlayState* play) {
    if (EnBubble_IsPopped(this, play)) {
        this->explosionCountdown = func_8089F59C(this);
        this->actionFunc = EnBubble_Pop;
    } else {
        EnBubble_Fly(this, play);
        this->actor.shape.yOffset = (this->modelHeight + 1.0f) * 16.0f;
        CollisionCheck_SetAC(play, &play->colChkCtx, &this->colliderSphere.base);
        CollisionCheck_SetOC(play, &play->colChkCtx, &this->colliderSphere.base);
    }
}

void EnBubble_Pop(EnBubble* this, PlayState* play) {
    if (EnBubble_Explosion(this, play) > -1) {
        SoundSource_PlaySfxAtFixedWorldPos(play, &this->actor.world.pos, 60, NA_SE_EN_AWA_BREAK);
        Actor_Kill(&this->actor);
    }
}

void EnBubble_Disappear(EnBubble* this, PlayState* play) {
    s32 temp_v0 = func_8089F8BC(this);

    if (temp_v0 >= 0) {
        this->actor.shape.shadowDraw = ActorShadow_DrawCircle;
        this->explosionCountdown = temp_v0;
        this->actionFunc = EnBubble_Regrow;
    }
}

void EnBubble_Regrow(EnBubble* this, PlayState* play) {
    if (func_8089F908(this)) {
        this->actionFunc = EnBubble_Wait;
    }
    CollisionCheck_SetAC(play, &play->colChkCtx, &this->colliderSphere.base);
    CollisionCheck_SetOC(play, &play->colChkCtx, &this->colliderSphere.base);
}

void EnBubble_Update(Actor* thisx, PlayState* play) {
    EnBubble* this = (EnBubble*)thisx;

    Actor_UpdatePos(&this->actor);
    Actor_UpdateBgCheckInfo(play, &this->actor, 16.0f, 16.0f, 0.0f,
                            UPDBGCHECKINFO_FLAG_1 | UPDBGCHECKINFO_FLAG_2 | UPDBGCHECKINFO_FLAG_4);
    this->actionFunc(this, play);
    Actor_SetFocus(&this->actor, this->actor.shape.yOffset);
}

void EnBubble_Draw(Actor* thisx, PlayState* play) {
    //s32 pad;
    EnBubble* this = (EnBubble*)thisx;

    OPEN_DISPS(play->state.gfxCtx);

    if (this->actionFunc != EnBubble_Disappear) {
        Gfx_SetupDL25_Xlu(play->state.gfxCtx);

        Math_SmoothStepToF(&this->modelRotSpeed, 16.0f, 0.2f, 1000.0f, 0.0f);

        Math_SmoothStepToF(&this->modelEllipticity, 0.08f, 0.2f, 1000.0f, 0.0f);

        Matrix_ReplaceRotation(&play->billboardMtxF);

        Matrix_Scale(this->modelWidth + 1.0f, this->modelHeight + 1.0f, 1.0f, MTXMODE_APPLY);

        Matrix_RotateZF(DEG_TO_RAD((f32)play->state.frames) * this->modelRotSpeed, MTXMODE_APPLY);

        Matrix_Scale(this->modelEllipticity + 1.0f, 1.0f, 1.0f, MTXMODE_APPLY);

        Matrix_RotateZF(DEG_TO_RAD(-(f32)play->state.frames) * this->modelRotSpeed, MTXMODE_APPLY);

        MATRIX_FINALIZE_AND_LOAD(POLY_XLU_DISP++, play->state.gfxCtx);

        gSPDisplayList(POLY_XLU_DISP++, gBubbleDL);
    }

    CLOSE_DISPS(play->state.gfxCtx);

    if (this->actionFunc != EnBubble_Disappear) {
        this->actor.shape.shadowScale = (this->modelWidth + 1.0f) * 0.2f;
        func_808A005C(this);
    }
}
