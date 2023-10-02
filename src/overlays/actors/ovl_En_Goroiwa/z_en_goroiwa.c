/*
 * File: z_en_goroiwa.c
 * Overlay: ovl_En_Goroiwa
 * Description: Rolling boulders
 */

#include "z_en_goroiwa.h"
#include "z64quake.h"
#include "objects/object_goroiwa/object_goroiwa.h"
#include "objects/gameplay_keep/gameplay_keep.h"

#define FLAGS (ACTOR_FLAG_10 | ACTOR_FLAG_80000000)

#define THIS ((EnGoroiwa*)thisx)

void EnGoroiwa_Init(Actor* thisx, PlayState* play);
void EnGoroiwa_Destroy(Actor* thisx, PlayState* play);
void EnGoroiwa_Update(Actor* thisx, PlayState* play);
void EnGoroiwa_Draw(Actor* thisx, PlayState* play);

void EnGoroiwa_SetupRoll(EnGoroiwa* this);
void EnGoroiwa_Roll(EnGoroiwa* this, PlayState* play);
void func_809421E0(EnGoroiwa* this);
void func_8094220C(EnGoroiwa* this, PlayState* play);
void func_809425CC(EnGoroiwa* this);
void func_80942604(EnGoroiwa* this, PlayState* play);
void EnGoroiwa_SetupMoveToGround(EnGoroiwa* this);
void EnGoroiwa_MoveToGround(EnGoroiwa* this, PlayState* play);
void EnGoroiwa_SetupWait(EnGoroiwa* this);
void EnGoroiwa_Wait(EnGoroiwa* this, PlayState* play);
void EnGoroiwa_SetupMoveUp(EnGoroiwa* this);
void EnGoroiwa_MoveUp(EnGoroiwa* this, PlayState* play);
void EnGoroiwa_SetupMoveDown(EnGoroiwa* this);
void EnGoroiwa_MoveDown(EnGoroiwa* this, PlayState* play);

ActorInit En_Goroiwa_InitVars = {
    ACTOR_EN_GOROIWA,
    ACTORCAT_PROP,
    FLAGS,
    OBJECT_GOROIWA,
    sizeof(EnGoroiwa),
    (ActorFunc)EnGoroiwa_Init,
    (ActorFunc)EnGoroiwa_Destroy,
    (ActorFunc)EnGoroiwa_Update,
    (ActorFunc)EnGoroiwa_Draw,
};

static ColliderJntSphElementInit sJntSphElementsInit[1] = {
    {
        {
            ELEMTYPE_UNK0,
            { 0x20000000, 0x00, 0x04 },
            { 0x01C37BB6, 0x00, 0x00 },
            TOUCH_ON | TOUCH_SFX_NONE,
            BUMP_ON,
            OCELEM_ON,
        },
        { 0, { { 0, 0, 0 }, 58 }, 100 },
    },
};

static ColliderJntSphInit sJntSphInit = {
    {
        COLTYPE_METAL,
        AT_ON | AT_TYPE_ENEMY,
        AC_ON | AC_HARD | AC_TYPE_PLAYER,
        OC1_ON | OC1_TYPE_ALL,
        OC2_TYPE_2,
        COLSHAPE_JNTSPH,
    },
    ARRAY_COUNT(sJntSphElementsInit),
    sJntSphElementsInit,
};

static CollisionCheckInfoInit sColChkInfoInit = { 0, 12, 60, MASS_HEAVY };

// speeds, cut in half
static f32 D_80942DFC[] = {
    10.0f,
    12.0f,
    14.0f,
    10.0f,
};

static Gfx* sGoroiwaBrokenFragments[][3] = {
    { gGoroiwaSilverRockChunk1DL, gGoroiwaSilverRockChunk2DL, gGoroiwaSilverRockChunk3DL },
    { gGoroiwaRedRockChunk1DL, gGoroiwaRedRockChunk2DL, gGoroiwaRedRockChunk3DL },
    { gGoroiwaSnowBallChunk1DL, gGoroiwaSnowBallChunk2DL, gGoroiwaSnowBallChunk3DL },
};

static Color_RGBA8 sGoriwaUnkPrimColors[] = {
    { 190, 195, 200, 255 },
    { 170, 130, 90, 255 },
};

static Color_RGBA8 sGoriwaSoftSpritePrimColor = { 250, 250, 250, 255 };

static Color_RGBA8 sGoriwaUnkEnvColors[] = {
    { 130, 135, 140, 255 },
    { 100, 60, 20, 255 },
};

static Color_RGBA8 sGoriwaSoftSpriteEnvColor = { 180, 180, 180, 255 };

static Vec3f sGoriwaSoftSpriteVelocity = { 0.0f, 0.0f, 0.0f };
static Vec3f sGoriwaSoftSpriteAccel = { 0.0f, 0.3f, 0.0f };
static Vec3f D_80942E60 = { 0.0f, 1.0f, 0.0f };
static Vec3f D_80942E6C = { 0.0f, 0.0f, 1.0f };

static InitChainEntry sInitChain[] = {
    ICHAIN_F32_DIV1000(gravity, -900, ICHAIN_CONTINUE),   ICHAIN_F32_DIV1000(terminalVelocity, -26000, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneForward, 2000, ICHAIN_CONTINUE), ICHAIN_F32(uncullZoneScale, 160, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneDownward, 350, ICHAIN_STOP),
};

static UNK_TYPE D_80942E8C[] = {
    0x0000003B,
    0x1A1A2864,
};

void func_8093E8A0(EnGoroiwa* this) {
    s32 params = ENGOROIWA_GET_3000(&this->actor);
    f32 phi_f2;

    if (params == ENGOROIWA_3000_0) {
        phi_f2 = 0.1f;
    } else if (params == ENGOROIWA_3000_1) {
        phi_f2 = 0.05f;
    } else {
        phi_f2 = (Rand_ZeroOne() * (f32)0.04) + 0.04f;
    }

    Actor_SetScale(&this->actor, phi_f2);
}

void func_8093E91C(EnGoroiwa* this) {
    this->unk_1DC = this->actor.scale.x * 595.0f;
}

// UpdateCollider in OOT
// This actor has no skeleton, so the position of the sphere is not updated by a skeleton animation
void EnGoroiwa_UpdateColliderPos(EnGoroiwa* this) {
    Sphere16* worldSphere = &this->collider.elements->dim.worldSphere;

    worldSphere->center.x = this->actor.world.pos.x;
    worldSphere->center.y = this->actor.world.pos.y + this->unk_1DC;
    worldSphere->center.z = this->actor.world.pos.z;
    this->collider.elements->dim.worldSphere.radius = this->unk_1DC - 1.0f;
}

// EnGoroiwa_InitCollider();
void EnGoroiwa_InitCollider(EnGoroiwa* this, PlayState* play) {
    s32 pad[2];
    s32 params = ENGOROIWA_GET_COLOR(&this->actor);

    Collider_InitJntSph(play, &this->collider);
    Collider_SetJntSph(play, &this->collider, &this->actor, &sJntSphInit, this->colliderElements);
    EnGoroiwa_UpdateColliderPos(this);
    this->collider.elements[0].dim.worldSphere.radius = this->unk_1DC - 1.0f;

    if ((params == ENGOROIWA_COLOR_REDROCK) || (params == ENGOROIWA_COLOR_SNOWBALL)) {
        this->collider.elements[0].info.bumper.dmgFlags |= (0x4000 | 0x400 | 0x100);
        if (params == ENGOROIWA_COLOR_REDROCK) {
            this->collider.base.colType = COLTYPE_WOOD;
        } else {
            this->collider.elements[0].info.bumper.dmgFlags &= ~(0x400000 | 0x200 | 0x2);
            this->collider.elements[0].info.bumper.dmgFlags |= (0x80000000 | 0x800 | 0x8);
            this->collider.base.colType = COLTYPE_NONE;
        }
    }
}

void EnGoriwa_UpdateFlags(EnGoroiwa* this, u8 setFlags) {
    this->stateFlags &= ~(0x4 | 0x2 | 0x1);
    this->stateFlags |= setFlags;
}

// Name pulled from OOT
s32 EnGoriwa_Vec3fNormalize(Vec3f* retVec, Vec3f* a) {
    f32 magnitude = Math3D_Vec3fMagnitude(a);
    f32 scale;

    if (magnitude < 0.001f) {
        return false;
    }

    scale = 1.0f / magnitude;

    retVec->x = a->x * scale;
    retVec->y = a->y * scale;
    retVec->z = a->z * scale;
    return true;
}

void EnGoroiwa_GetRollingSFXUpper(EnGoroiwa* this, PlayState* play) {
    // home.rot.x >> 1 & 3
    this->rollingSFXUpperIndex = ENGOROIWA_GET_ROT_ROLLINGSFX_UPPER(this);
}

// gets path distance, total or dist to end?
f32 func_8093EB74(EnGoroiwa* this, PlayState* play) {
    s32 i;
    Path* path = &play->setupPathList[ENGOROIWA_GET_PATH(&this->actor)];
    s32 pointCount = path->count;
    f32 returnDist = 0.0f;
    Vec3f sp54;
    Vec3f sp48;

    Math_Vec3s_ToVec3f(&sp48, &this->curPathPoints[0]);

    for (i = 1; i < pointCount; i++) {
        Math_Vec3f_Copy(&sp54, &sp48);
        Math_Vec3s_ToVec3f(&sp48, &this->curPathPoints[i]);
        returnDist += Math3D_Distance(&sp54, &sp48);
    }

    return returnDist;
}

// EnGoroiwa_FaceNextWaypoint in OOT
void EnGoroiwa_AdjustYaw(EnGoroiwa* this) {
    Vec3s* nextPathPoint = &this->curPathPoints[this->nextWaypoint];
    Vec3f targetPoint;

    targetPoint.x = nextPathPoint->x;
    targetPoint.y = nextPathPoint->y;
    targetPoint.z = nextPathPoint->z;
    this->actor.world.rot.y = Math_Vec3f_Yaw(&this->actor.world.pos, &targetPoint);
}

// exact copy of OoT version
void EnGoroiwa_CheckEndOfPath(EnGoroiwa* this) {
    s32 loopMode = ENGOROIWA_GET_LOOPMODE(&this->actor);

    if (this->nextWaypoint < 0) {
        if ((loopMode == ENGOROIWA_LOOPMODE_ONEWAY) || (loopMode == ENGOROIWA_LOOPMODE_ONEWAY_BREAK)) {
            this->currentWaypoint = this->endWaypoint;
            this->nextWaypoint = this->endWaypoint - 1;
            this->pathDirection = -1;
        } else if (loopMode == ENGOROIWA_LOOPMODE_ROUNDTRIP) {
            this->currentWaypoint = 0;
            this->nextWaypoint = 1;
            this->pathDirection = 1;
        }
    } else if (this->endWaypoint < this->nextWaypoint) {
        if ((loopMode == ENGOROIWA_LOOPMODE_ONEWAY) || (loopMode == ENGOROIWA_LOOPMODE_ONEWAY_BREAK)) {
            this->currentWaypoint = 0;
            this->nextWaypoint = 1;
            this->pathDirection = 1;
        } else if (loopMode == ENGOROIWA_LOOPMODE_ROUNDTRIP) {
            this->currentWaypoint = this->endWaypoint;
            this->nextWaypoint = this->endWaypoint - 1;
            this->pathDirection = -1;
        }
    }
}

void EnGoroiwa_SetNextWaypoint(EnGoroiwa* this) {
    this->currentWaypoint = this->nextWaypoint;
    this->nextWaypoint += this->pathDirection;
    EnGoroiwa_CheckEndOfPath(this);
}

// TODO
void func_8093EDB0(EnGoroiwa* this) {
    this->pathDirection = -this->pathDirection;
    this->currentWaypoint = this->nextWaypoint;
    this->nextWaypoint += this->pathDirection;
}

void func_8093EDD8(EnGoroiwa* this, PlayState* play) {
    this->endWaypoint = play->setupPathList[ENGOROIWA_GET_PATH(&this->actor)].count - 1;
    this->currentWaypoint = 0;
    this->nextWaypoint = 1;
    this->pathDirection = 1;
}

void EnGoroiwa_InitPath(EnGoroiwa* this, PlayState* play) {
    this->endWaypoint = play->setupPathList[ENGOROIWA_GET_PATH(&this->actor)].count - 1;
    this->currentWaypoint = ENGOROIWA_GET_ROT_Y(&this->actor);
    this->nextWaypoint = this->currentWaypoint + 1;
    this->pathDirection = 1;
}

void EnGoroiwa_TeleportToWaypoint(EnGoroiwa* this, s32 waypoint) {
    Vec3s* pointPos = &this->curPathPoints[waypoint];

    this->actor.world.pos.x = pointPos->x;
    this->actor.world.pos.y = pointPos->y;
    this->actor.world.pos.z = pointPos->z;
}

// InitRotation in OOT
void EnGoroiwa_InitRotation(EnGoroiwa* this) {
    this->prevUnitRollAxis.x = 1.0f;
    this->rollRotSpeed = 1.0f;
    this->unk_1A8.x = 1.0f;
}

s32 EnGoroiwa_GetAscendDirection(EnGoroiwa* this) {
    Vec3s* nextPointPos = &this->curPathPoints[this->nextWaypoint];
    Vec3s* currentPointPos = &this->curPathPoints[this->currentWaypoint];

    if ((nextPointPos->x == currentPointPos->x) && (nextPointPos->z == currentPointPos->z)) {
        if (currentPointPos->y < nextPointPos->y) {
            return 1;
        }
        return -1;
    }
    return 0;
}

void EnGoroiwa_SpawnDust(PlayState* play, Vec3f* pos, Color_RGBA8* primColor, Color_RGBA8* envColor, f32 arg4) {
    Vec3f randDustPos;
    f32 temp_f0;
    f32 randZeroOne;
    f32 temp_f24;
    f32 temp_f26;
    s32 temp_f16;
    s16 phi_s0;
    s16 temp;
    f32 temp_f28;
    f32 temp_f30;
    s32 i;

    temp_f0 = (arg4 + 0.1f) * 0.5f;
    temp_f16 = temp_f0 * 165.0f;
    temp_f24 = 470.0f * arg4;
    temp_f30 = 400.0f * arg4;
    temp_f26 = 800.0f * temp_f0;
    temp_f28 = 600.0f * temp_f0;
    temp = 0x10000 / temp_f16;

    for (i = 0, phi_s0 = 0; i < temp_f16; i++, phi_s0 += temp) {
        // clang-format off
        randZeroOne = Rand_ZeroOne(); randDustPos.x = (Math_SinS(phi_s0) * (temp_f24 * ((randZeroOne * 0.5f) + 0.5f))) + pos->x;
        randDustPos.y = ((Rand_ZeroOne() - 0.5f) * temp_f30) + pos->y;
        randZeroOne = Rand_ZeroOne(); randDustPos.z = (Math_CosS(phi_s0) * (temp_f24 * ((randZeroOne * 0.5f) + 0.5f))) + pos->z;
        // clang-format on

        // spawn SsDust
        func_800B0E48(play, &randDustPos, &sGoriwaSoftSpriteVelocity, &sGoriwaSoftSpriteAccel, primColor, envColor,
                      (Rand_ZeroOne() * temp_f28) + temp_f26, temp_f26);
    }
}

// OOT this was a touch different
void EnGoroiwa_SpawnWaterEffects(PlayState* play, Vec3f* contactPos, f32 scale) {
    Vec3f splashPos;
    f32 temp_f20;
    s32 splashCount;
    s16 temp_lo;
    s16 phi_s0;
    s32 i;

    splashCount = (scale + 0.1f) * 58.0f;
    splashPos.y = contactPos->y;
    temp_f20 = 550.0f * scale;
    temp_lo = 0x10000 / splashCount;

    for (i = 0, phi_s0 = 0; i < splashCount; i++, phi_s0 += temp_lo) {
        splashPos.x = (Math_SinS((s32)(Rand_ZeroOne() * temp_lo) + phi_s0) * temp_f20) + contactPos->x;
        splashPos.z = (Math_CosS((s32)(Rand_ZeroOne() * temp_lo) + phi_s0) * temp_f20) + contactPos->z;
        EffectSsGSplash_Spawn(play, &splashPos, NULL, NULL, 0, 0x15E);
    }

    EffectSsGRipple_Spawn(play, contactPos, 0x1F4, 0x384, 4);
}

s32 EnGoroiwa_MoveAndFall(EnGoroiwa* this) {
    s32 pad[3];
    Vec3s* nextPoint;
    f32 tempX;
    f32 tempZ;
    f32 x;
    f32 z;

    Math_StepToF(&this->actor.speed, D_80942DFC[this->rollingSFXUpperIndex], 0.3f);
    Actor_UpdateVelocityWithGravity(&this->actor);
    nextPoint = &this->curPathPoints[this->nextWaypoint];
    this->actor.velocity.y *= 0.97f;
    x = nextPoint->x;
    z = nextPoint->z;

    tempX = x - this->actor.world.pos.x;
    tempZ = z - this->actor.world.pos.z;

    if (SQ(this->actor.speed + 1.0f) < (SQ(tempX) + SQ(tempZ))) {
        this->actor.world.pos.x += this->actor.velocity.x;
        this->actor.world.pos.y += this->actor.velocity.y;
        this->actor.world.pos.z += this->actor.velocity.z;
        this->stateFlags &= ~0x40;
        return false;
    }

    this->actor.world.pos.x = x;
    this->actor.world.pos.y += this->actor.velocity.y;
    this->actor.world.pos.z = z;
    this->stateFlags |= 0x40;
    return true;
}

// Move?
s32 func_8093F498(EnGoroiwa* this) {
    s32 pad;
    f32 velocityMagnitude;
    Vec3f targetPos;
    Vec3s* nextPoint = &this->curPathPoints[this->nextWaypoint];

    targetPos.x = nextPoint->x;
    targetPos.y = nextPoint->y;
    targetPos.z = nextPoint->z;

    Math_StepToF(&this->actor.speed, D_80942DFC[this->rollingSFXUpperIndex], 0.3f);
    Math_Vec3f_Diff(&targetPos, &this->actor.world.pos, &this->actor.velocity);

    velocityMagnitude = Math3D_Vec3fMagnitude(&this->actor.velocity);
    if ((this->actor.speed + 1.0f) < velocityMagnitude) {
        // scale off mag? is this snowball?
        Math_Vec3f_Scale(&this->actor.velocity, this->actor.speed / velocityMagnitude);
        this->actor.world.pos.x += this->actor.velocity.x;
        this->actor.world.pos.y += this->actor.velocity.y;
        this->actor.world.pos.z += this->actor.velocity.z;
        this->stateFlags &= ~0x40;
        return false;
    }

    this->actor.world.pos.x = targetPos.x;
    this->actor.world.pos.y = targetPos.y;
    this->actor.world.pos.z = targetPos.z;
    this->stateFlags |= 0x40;
    return true;
}

// ?? slowing down??
s32 func_8093F5EC(EnGoroiwa* this) {
    s32 pad;
    Vec3s* nextPoint = &this->curPathPoints[this->nextWaypoint];

    if (this->actor.velocity.y < 0.0f) {
        this->actor.velocity.y = 0.0f;
    }

    Math_StepToF(&this->actor.velocity.y, D_80942DFC[this->rollingSFXUpperIndex] * 0.5f, 0.18f);
    this->actor.world.pos.x = nextPoint->x;
    this->actor.world.pos.z = nextPoint->z;

    if (Math_StepToF(&this->actor.world.pos.y, nextPoint->y, fabsf(this->actor.velocity.y))) {
        this->stateFlags |= 0x40;
        return true;
    } else {
        this->stateFlags &= ~0x40;
        return false;
    }
}

// almost copy of OOT version
s32 EnGoroiwa_MoveDownToNextWaypoint(EnGoroiwa* this, PlayState* play) {
    f32 floorY;
    Vec3s* nextPointPos = &this->curPathPoints[this->nextWaypoint];
    f32 nextPointY = nextPointPos->y;
    f32 thisY;
    f32 yDistToFloor;

    Math_StepToF(&this->actor.velocity.y, -18.367346f, 1.0f); // gravity is a universal constant
    this->actor.velocity.y *= 0.98f;

    this->actor.world.pos.x = nextPointPos->x;
    this->actor.world.pos.z = nextPointPos->z;
    thisY = this->actor.world.pos.y;
    this->actor.world.pos.y += this->actor.velocity.y;

    if ((this->actor.velocity.y < 0.0f) && (this->actor.world.pos.y <= nextPointY)) {
        if (this->bounceCount == 0) {
            if (this->actor.xzDistToPlayer < 400.0f) {
                s16 quakeIndex = Quake_Request(GET_ACTIVE_CAM(play), QUAKE_TYPE_3);

                Quake_SetSpeed(quakeIndex, 17232);
                Quake_SetPerturbations(quakeIndex, 3, 0, 0, 0);
                Quake_SetDuration(quakeIndex, 7);
            }

            this->rollRotSpeed = 0.0f;

            if (!(this->stateFlags & ENGOROIWA_STATE_INWATER)) {
                CollisionPoly* poly;
                Vec3f checkPos;
                s32 pad[2];
                s32 bgId;
                Vec3f dustPos;

                checkPos.x = this->actor.world.pos.x;
                checkPos.y = this->actor.world.pos.y + 50.0f;
                checkPos.z = this->actor.world.pos.z;

                floorY = BgCheck_EntityRaycastFloor5_2(play, &play->colCtx, &poly, &bgId, &this->actor, &checkPos);
                yDistToFloor = floorY - this->actor.world.pos.y;

                if (fabsf(yDistToFloor) < (fabsf(this->actor.velocity.y) + 0.01f)) {
                    if (this->actor.flags & ACTOR_FLAG_40) {
                        dustPos.x = this->actor.world.pos.x;
                        dustPos.y = floorY + 10.0f;
                        dustPos.z = this->actor.world.pos.z;

                        EnGoroiwa_SpawnDust(play, &dustPos, &sGoriwaUnkPrimColors[ENGOROIWA_GET_COLOR(&this->actor)],
                                            &sGoriwaUnkEnvColors[ENGOROIWA_GET_COLOR(&this->actor)],
                                            this->actor.scale.x);
                    }
                    Actor_PlaySfx(&this->actor, NA_SE_EV_BIGBALL_BOUND);
                }
            }
        }

        if (this->bounceCount >= 1) {
            this->stateFlags |= 0x40; // wasnt here in OOT
            return true;
        }

        this->bounceCount++;
        this->actor.velocity.y *= -0.3f;
        this->actor.world.pos.y = nextPointY - ((this->actor.world.pos.y - nextPointY) * 0.3f);
    }

    if (this->bounceCount == 0) {
        WaterBox* waterbox;
        f32 waterSurfaceY;

        if (WaterBox_GetSurface1_2(play, &play->colCtx, this->actor.world.pos.x, this->actor.world.pos.z,
                                   &waterSurfaceY, &waterbox)) {
            if ((this->actor.world.pos.y + this->unk_1DC) <= waterSurfaceY) {
                this->stateFlags |= ENGOROIWA_STATE_INWATER;
                if (waterSurfaceY < (this->unk_1DC + thisY)) {
                    if (this->actor.flags & ACTOR_FLAG_40) {
                        Vec3f waterHitPos;

                        waterHitPos.x = this->actor.world.pos.x;
                        waterHitPos.y = waterSurfaceY;
                        waterHitPos.z = this->actor.world.pos.z;
                        EnGoroiwa_SpawnWaterEffects(play, &waterHitPos, this->actor.scale.x);
                    }
                    this->actor.velocity.y *= 0.2f;
                }

                if (this->actor.velocity.y < -8.0f) {
                    this->actor.velocity.y = -8.0f;
                }
            }
        }
    }

    this->stateFlags &= ~0x40;
    return false;
}

void EnGoroiwa_UpdateRotation(EnGoroiwa* this, PlayState* play) {
    f32 tmp;
    f32 tmp2;
    f32 rolAngleDiff;
    Vec3f rollAxisPtr;
    Vec3f unitRollAxis;
    MtxF mtx;

    if (this->stateFlags & ENGOROIWA_STATE_RETAIN_ROT_SPEED) {
        rolAngleDiff = this->prevRollAngleDiff;
    } else {
        // in OOT this divisor was static 59.2f
        tmp = Math3D_Distance(&this->actor.world.pos, &this->actor.prevPos);
        tmp2 = tmp / this->unk_1DC;
        this->prevRollAngleDiff = tmp2;
        rolAngleDiff = this->prevRollAngleDiff;
    }

    rolAngleDiff *= this->rollRotSpeed;
    if (!(this->stateFlags & ENGOROIWA_STATE_RETAIN_ROT_SPEED)) {
        if (Math3D_LengthSquared(&this->actor.velocity) > 0.1f) {
            Math_Vec3f_Copy(&this->unk_1A8, &this->actor.velocity);
        }
    }

    Math3D_CrossProduct(&D_80942E60, &this->unk_1A8, &rollAxisPtr);

    if (EnGoriwa_Vec3fNormalize(&unitRollAxis, &rollAxisPtr)) {
        this->prevUnitRollAxis = unitRollAxis;
    } else {
        unitRollAxis = this->prevUnitRollAxis;
    }

    Matrix_RotateAxisF(rolAngleDiff, &unitRollAxis, MTXMODE_NEW);
    Matrix_RotateYS(this->actor.shape.rot.y, MTXMODE_APPLY);
    Matrix_RotateXS(this->actor.shape.rot.x, MTXMODE_APPLY);
    Matrix_RotateZS(this->actor.shape.rot.z, MTXMODE_APPLY);
    Matrix_Get(&mtx);
    Matrix_MtxFToYXZRot(&mtx, &this->actor.shape.rot, false);
}

void EnGoroiwa_NextWaypoint(EnGoroiwa* this) {
    s32 loopMode = ENGOROIWA_GET_LOOPMODE(&this->actor);

    EnGoroiwa_SetNextWaypoint(this);

    if (((loopMode == ENGOROIWA_LOOPMODE_ONEWAY) || (loopMode == ENGOROIWA_LOOPMODE_ONEWAY_BREAK)) &&
        ((this->currentWaypoint == 0) || (this->currentWaypoint == this->endWaypoint))) {
        EnGoroiwa_TeleportToWaypoint(this, this->currentWaypoint);
    }
}

void EnGoroiwa_SpawnIceAndSmoke(EnGoroiwa* this, PlayState* play) {
    s32 i;
    Vec3f pos;
    Vec3f vel;
    Vec3f accel;
    s16 temp_s3;
    s16 rot;
    s16 temp;
    s32 pad;
    s32 smokeCount;
    f32 temp_f20;
    f32 temp_f22;
    f32 halfScale;
    f32 biggerScale;

    halfScale = (this->actor.scale.x + 0.1f) * 0.5f;
    smokeCount = halfScale * 150.0f;
    biggerScale = this->actor.scale.x * 600.0f;
    temp = 0x10000 / smokeCount;

    for (i = 0, rot = 0; i < smokeCount; i++, rot += temp) {
        temp_s3 = Rand_Next() >> 0x10;
        temp_f20 = Math_SinS(temp_s3);
        temp_f22 = Math_CosS(temp_s3);

        pos.x = Math_SinS(rot);
        pos.z = Math_CosS(rot);

        vel.x = 2.0f * pos.x;
        vel.y = (2.0f * Rand_ZeroOne()) + 1.0f;
        vel.z = 2.0f * pos.z;

        pos.x *= temp_f22 * biggerScale;
        pos.y = temp_f20 * biggerScale;
        pos.z *= (temp_f22 * biggerScale);

        pos.x += this->actor.world.pos.x;
        pos.y += this->actor.world.pos.y;
        pos.z += this->actor.world.pos.z;

        accel.x = vel.x * -0.02f;
        accel.y = vel.y * -0.05f;
        accel.z = vel.z * -0.02f;

        EffectSsIceSmoke_Spawn(play, &pos, &vel, &accel, ((s32)(Rand_ZeroOne() * 170.0f) + 150) * halfScale * 10.0f);
    }

    for (i = 0, rot = 0; i < smokeCount; i++, rot += temp) {
        temp_f20 = (Rand_ZeroOne() * (450.0f * this->actor.scale.x)) + 50.0f;

        pos.x = Math_SinS(rot);
        pos.z = Math_CosS(rot);

        vel.x = pos.x * 30.0f * halfScale;
        vel.y = 0.0f;
        vel.z = pos.z * 30.0f * halfScale;

        accel.x = vel.x * -0.02f;
        accel.y = 0.03f;
        accel.z = vel.z * -0.02f;

        pos.x = (pos.x * temp_f20) + this->actor.world.pos.x;
        pos.y = (Rand_ZeroOne() * 20.0f) + this->actor.world.pos.y;
        pos.z = (pos.z * temp_f20) + this->actor.world.pos.z;

        EffectSsIceSmoke_Spawn(play, &pos, &vel, &accel, (s32)(Rand_ZeroOne() * 1400.0f * halfScale) + 100);
    }
}


// spawn fragments for snowball because it spawns ice smoke? except it works with any color
void func_80940090(EnGoroiwa* this, PlayState* play) {
    s32 pad;
    s32 pad2;
    s32 i;
    s32 color = ENGOROIWA_GET_COLOR(&this->actor);
    s32 kakeraArg5;
    s32 kakeraArg10;
    Vec3f posPlus;
    Vec3f pos;
    Vec3f vel;
    s32 phi_s6;
    f32 halfScale;
    Gfx* chunkDL;
    s16 rot;
    f32 velScale;
    s32 gravity;
    s32 spD8;
    s16 spA8;
    f32 randMagnitude;
    s32 pad3;

    if (this->actor.flags & ACTOR_FLAG_40) {
        halfScale = (this->actor.scale.x + 0.1f) * 0.5f;
        posPlus.x = this->actor.world.pos.x;
        posPlus.y = this->actor.world.pos.y + this->unk_1DC;
        posPlus.z = this->actor.world.pos.z;

        //! FAKE:
        if (1) {}

        spD8 = halfScale * 150.0f;
        spA8 = 0x10000 / spD8;

        for (i = 0, rot = 0; i < spD8; i++, rot += spA8) {
            if ((i & 3) == 0) {
                velScale = 1.0f;
                chunkDL = sGoroiwaBrokenFragments[color][2];
                gravity = -0x118;
                kakeraArg10 = 0;
                kakeraArg5 = 0x40;
            } else {
                gravity = -0x190;
                if ((i & 3) == 1) {
                    chunkDL = sGoroiwaBrokenFragments[color][1];
                    gravity = -0x154;
                    kakeraArg10 = 0;
                    velScale = 0.9f;
                    if (Rand_ZeroOne() < 0.4f) {
                        kakeraArg5 = 0x20;
                    } else {
                        kakeraArg5 = 0x40;
                    }
                } else {
                    chunkDL = sGoroiwaBrokenFragments[color][0];
                    kakeraArg10 = 1;
                    velScale = 0.8f;
                    if ((s32)Rand_Next() > 0) {
                        kakeraArg5 = 0x21;
                    } else {
                        kakeraArg5 = 0x41;
                    }
                }
            }

            randMagnitude = (Rand_ZeroOne() * this->actor.scale.x * 400.0f) + 20.0f;

            pos.x = Math_SinS((s32)(Rand_ZeroOne() * spA8) + rot) * randMagnitude;
            pos.y = (Rand_ZeroOne() - 0.4f) * randMagnitude * 1.6666666f;
            pos.z = Math_CosS((s32)(Rand_ZeroOne() * spA8) + rot) * randMagnitude;

            vel.x = pos.x * 0.16f * velScale;
            vel.y = (Rand_ZeroOne() * 16.0f) + 3.0f;
            vel.z = pos.z * 0.16f * velScale;

            // ??
            Math_Vec3f_Sum(&pos, &posPlus, &pos);

            EffectSsKakera_Spawn(play, &pos, &vel, &pos, gravity, kakeraArg5, 30, 0, 0,
                                 ((Rand_ZeroOne() * 150.0f) + 300.0f) * this->actor.scale.x, // scale
                                 kakeraArg10, 
                                 0, 0x32, -1,
                                 OBJECT_GOROIWA, chunkDL);

            if (this->unk_1E6 == 0) {
                pos.x += ((Rand_ZeroOne() * 1200.0f) - 600.0f) * this->actor.scale.x;
                pos.y += ((Rand_ZeroOne() * 1400.0f) - 600.0f) * this->actor.scale.y;
                pos.z += ((Rand_ZeroOne() * 1200.0f) - 600.0f) * this->actor.scale.z;

                // spawn SsDust
                func_800B0E48(play, &pos, &sGoriwaSoftSpriteVelocity, &sGoriwaSoftSpriteAccel,
                              &sGoriwaUnkPrimColors[color], &sGoriwaUnkEnvColors[color],
                              (Rand_ZeroOne() * 50.0f) + (400.0f * halfScale), (Rand_ZeroOne() * 60.0f) + (500.0f * halfScale));
            }
        }

        if (this->unk_1E6 != 0) {
            EnGoroiwa_SpawnIceAndSmoke(this, play);
        }
    }
}

// chunkDLs is subarray of possible chunk dls based on color
void func_80940588(PlayState* play, Vec3f* arg1, Gfx* chunkDLs[], Color_RGBA8* primColor, Color_RGBA8* envColor,
                   f32 arg5) {
    Gfx* chunkDL;
    Vec3f kakeraPos;
    Vec3f vel;
    Vec3f pos;
    f32 temp_f20;
    f32 spB0;
    s32 j;
    s32 i;
    s32 kakeraArg5;
    s32 spD0;
    s16 spCE;
    s16 spA8;
    s16 gravity;
    s16 kakeraArg10;
    f32 spAC;

    spD0 = (s32)(arg5 * 35.0f) + 6;
    temp_f20 = (arg5 + 0.1f) * 0.5f;
    spB0 = 550.0f * temp_f20;
    spAC = 500.0f * temp_f20;
    spA8 = 0x10000 / spD0;

    for (i = 0, spCE = 0; i < spD0; i++, spCE += spA8) {
        temp_f20 = (Rand_ZeroOne() * arg5 * 500.0f) + 20.0f;

        kakeraPos.x = Math_SinS((s32)(Rand_ZeroOne() * spA8) + spCE) * temp_f20;
        kakeraPos.y = (Rand_ZeroOne() - 0.4f) * temp_f20 * 1.6666666f;
        kakeraPos.z = Math_CosS((s32)(Rand_ZeroOne() * spA8) + spCE) * temp_f20;

        vel.x = kakeraPos.x * 0.19f;
        vel.y = (Rand_ZeroOne() * 16.0f) + 3.0f;
        vel.z = kakeraPos.z * 0.19f;

        Math_Vec3f_Sum(&kakeraPos, arg1, &kakeraPos);

        if ((i & 3) == 0) {
            chunkDL = chunkDLs[0];
            gravity = -0x190;
            kakeraArg10 = 1;
            if ((s32)Rand_Next() > 0) {
                kakeraArg5 = 0x21;
            } else {
                kakeraArg5 = 0x41;
            }
        } else {
            kakeraArg10 = 0;
            if ((i & 3) == 1) {
                gravity = -0x154;
                chunkDL = chunkDLs[1];
                if (Rand_ZeroOne() < 0.4f) {
                    kakeraArg5 = 0x20;
                } else {
                    kakeraArg5 = 0x40;
                }
            } else {
                gravity = -0x118;
                kakeraArg5 = 0x40;
                chunkDL = chunkDLs[2];
            }
        }

        EffectSsKakera_Spawn(play, &kakeraPos, &vel, &kakeraPos, gravity, kakeraArg5, 30, 0, 0,
                             ((Rand_ZeroOne() * 100.0f) + 170.0f) * arg5, // scale
                             kakeraArg10, 0,
                             0x36, // life
                             -1, OBJECT_GOROIWA, chunkDL);

        for (j = 0; j < 2; j++) {
            pos.x = (((Rand_ZeroOne() * 1000.0f) - 500.0f) * arg5) + kakeraPos.x;
            pos.y = (((Rand_ZeroOne() * 1300.0f) - 500.0f) * arg5) + kakeraPos.y;
            pos.z = (((Rand_ZeroOne() * 1000.0f) - 500.0f) * arg5) + kakeraPos.z;

            
            // spawn SsDust
            func_800B0E48(play, &pos, &sGoriwaSoftSpriteVelocity, &sGoriwaSoftSpriteAccel, primColor, envColor,
                          (Rand_ZeroOne() * 80.0f) + spB0, (Rand_ZeroOne() * 70.0f) + spAC);
        }
    }
}

// spawns a fragment upon destruction
// chunkDLs is sGoroiwaBrokenFragments sub section, based on color
void func_80940A1C(PlayState* play, Vec3f* arg1, Gfx** chunkDLs, Color_RGBA8* primColor, Color_RGBA8* envColor,
                   f32 scale) {
    s32 i;
    Vec3f pos;
    Vec3f vel;
    s32 gravity;
    s32 kakeraArg5;
    s32 kakeraArg10;
    Gfx* chunkDL;
    s32 spC8;
    f32 temp_f20;
    f32 spAC;
    s16 spA8;
    s16 phi_s6;

    spC8 = (s32)(scale * 35.0f) + 5;
    temp_f20 = (scale + 0.1f) * 0.5f;
    spAC = 600.0f * temp_f20;
    spA8 = 0x10000 / spC8;

    for (i = 0, phi_s6 = 0; i < spC8; i++, phi_s6 += spA8) {
        temp_f20 = (Rand_ZeroOne() * scale * 400.0f) + 20.0f;

        pos.x = Math_SinS((s32)(Rand_ZeroOne() * spA8) + phi_s6) * temp_f20;
        pos.y = (Rand_ZeroOne() - 0.2f) * temp_f20 * 0.8f;
        pos.z = Math_CosS((s32)(Rand_ZeroOne() * spA8) + phi_s6) * temp_f20;

        vel.x = pos.x * 0.17f;
        vel.y = (Rand_ZeroOne() * 14.0f) + 3.0f;
        vel.z = pos.z * 0.17f;

        Math_Vec3f_Sum(&pos, arg1, &pos);

        if ((i & 3) == 0) {
            chunkDL = chunkDLs[2];
            gravity = -0x118;
            kakeraArg10 = 0;
            kakeraArg5 = 0x40;
        } else {
            kakeraArg10 = 1;
            if ((i & 3) == 1) {
                chunkDL = chunkDLs[1];
                gravity = -0x154;
                if ((s32)Rand_Next() > 0) {
                    kakeraArg5 = 0x21;
                } else {
                    kakeraArg5 = 0x41;
                }
            } else {
                chunkDL = chunkDLs[0];
                gravity = -0x190;
                if ((s32)Rand_Next() > 0) {
                    kakeraArg5 = 0x21;
                } else {
                    kakeraArg5 = 0x41;
                }
            }
        }

        EffectSsKakera_Spawn(play, &pos, &vel, &pos, gravity, kakeraArg5, 30, 0, 0,
                             ((Rand_ZeroOne() * 150.0f) + 250.0f) * scale, // scale
                             kakeraArg10, 0,
                             0x36, // life
                             -1,   // colourIdx
                             OBJECT_GOROIWA, chunkDL);

        pos.x += ((Rand_ZeroOne() * 800.0f) - 400.0f) * scale;
        pos.y += ((Rand_ZeroOne() * 800.0f) - 250.0f) * scale;
        pos.z += ((Rand_ZeroOne() * 800.0f) - 400.0f) * scale;

        // spawn SsDust
        func_800B0E48(play, &pos, &sGoriwaSoftSpriteVelocity, &sGoriwaSoftSpriteAccel, primColor, envColor,
                      (Rand_ZeroOne() * 60.0f) + spAC, (Rand_ZeroOne() * 30.0f) + spAC);
    }
}

void func_80940E38(EnGoroiwa* this, PlayState* play) {
    f32 sp5C;
    s32 pad;
    f32 sp54;
    Vec3f pos;
    s16 sp46;
    s16 temp_a0;

    if (this->actor.flags & ACTOR_FLAG_40) {
        if (this->actor.xzDistToPlayer < 1000.0f) {
            sp5C = (1000.0f - this->actor.xzDistToPlayer) * 0.0012f * (this->actor.speed * 0.1f);
            if (Rand_ZeroOne() < sp5C) {
                this->unk_1CE += 20000;
                sp46 = (s32)Rand_ZeroFloat(20000.0f) + this->unk_1CE;
                temp_a0 = sp46 - this->actor.world.rot.y;
                if (ABS(temp_a0) < 0x4000) {
                    sp54 = Math_CosS(temp_a0) * 1.6f * this->unk_1DC;
                } else {
                    sp54 = this->unk_1DC;
                }

                pos.x = (Math_SinS(sp46) * sp54) + this->actor.world.pos.x;
                pos.y = this->actor.world.pos.y + 20.0f;
                pos.z = (Math_CosS(sp46) * sp54) + this->actor.world.pos.z;

                // spawn SsDust
                func_800B0E48(play, &pos, &sGoriwaSoftSpriteVelocity, &sGoriwaSoftSpriteAccel,
                              &sGoriwaSoftSpritePrimColor, &sGoriwaSoftSpriteEnvColor,
                              (Rand_ZeroOne() * 600.0f) + (600.0f * (this->actor.scale.x + 0.1f) * 0.5f),
                              (s32)(Rand_ZeroOne() * 50.0f) + 30);
            }
        }
    }
}

void func_80941060(EnGoroiwa* this, PlayState* play) {
    Vec3f accel;
    Vec3f vel;
    Vec3f pos;
    Vec3s* vec = &this->collider.elements[0].info.bumper.hitPos;
    s32 i;

    for (i = 0; i < 4; i++) {
        pos.x = ((Rand_ZeroOne() * 14.0f) - 7.0f) + vec->x;
        pos.y = ((Rand_ZeroOne() * 14.0f) - 7.0f) + vec->y;
        pos.z = ((Rand_ZeroOne() * 14.0f) - 7.0f) + vec->z;

        vel.x = (Rand_ZeroOne() - 0.5f) * 1.6f;
        vel.y = -0.8f;
        vel.z = (Rand_ZeroOne() - 0.5f) * 1.6f;

        accel.x = vel.x * -0.06f;
        accel.y = vel.y * -0.06f;
        accel.z = vel.z * -0.06f;

        // spawn SsDust
        func_800B0E48(play, &pos, &vel, &accel, &sGoriwaSoftSpritePrimColor, &sGoriwaSoftSpriteEnvColor,
                      (s32)(Rand_ZeroOne() * 30.0f) + 15, (s32)(Rand_ZeroOne() * 40.0f) + 30);
    }
}

void EnGoroiwa_PlaySnowballBrokenSound(EnGoroiwa* this, PlayState* play) {
    SoundSource_PlaySfxAtFixedWorldPos(play, &this->actor.world.pos, 30, NA_SE_EV_SNOWBALL_BROKEN);
}

void EnGoroiwa_Init(Actor* thisx, PlayState* play) {
    EnGoroiwa* this = THIS;
    f32 dist;
    s32 pathID = ENGOROIWA_GET_PATH(&this->actor);
    s32 pad;
    Path* path = &play->setupPathList[pathID];

    Actor_ProcessInitChain(&this->actor, sInitChain);

    this->actor.world.rot.x = 0;
    this->actor.world.rot.z = 0;
    this->actor.world.rot.y = Rand_Next() & 0xFFFF;
    this->actor.shape.rot.y = this->actor.world.rot.y;
    this->actor.shape.rot.x = 0;
    this->actor.shape.rot.z = 0;

    func_8093E8A0(this);
    func_8093E91C(this);
    EnGoroiwa_InitCollider(this, play);

    if (pathID == 0xFF) {
        // "Error: Invalid arg_data" in OoT
        Actor_Kill(&this->actor);
        return;
    }

    if (path->count < 2) {
        // "Error: Invalid Path Data" im OoT
        Actor_Kill(&this->actor);
        return;
    }

    if ((ENGOROIWA_GET_ROT_Y(thisx) >= (path->count - 1)) && (ENGOROIWA_GET_ROT_Y(thisx) < 0)) {
        this->actor.home.rot.y = 0;
    }

    CollisionCheck_SetInfo(&this->actor.colChkInfo, NULL, &sColChkInfoInit);
    ActorShape_Init(&this->actor.shape, 595.0f, ActorShadow_DrawCircle, 9.4f);
    this->actor.shape.shadowAlpha = 200;

    EnGoroiwa_GetRollingSFXUpper(this, play);

    this->curPathPoints = Lib_SegmentedToVirtual(path->points);

    EnGoroiwa_InitPath(this, play);
    EnGoroiwa_TeleportToWaypoint(this, ENGOROIWA_GET_ROT_Y(thisx));
    EnGoroiwa_InitRotation(this);
    EnGoroiwa_AdjustYaw(this);

    if (ENGOROIWA_GET_3000(&this->actor) == ENGOROIWA_3000_2) {
        dist = func_8093EB74(this, play);

        if (dist < 0.1f) {
            this->unk_1E0 = 0.0f;
        } else {
            this->unk_1E0 = (D_80942DFC[this->rollingSFXUpperIndex] * ((s32)play->state.framerateDivisor * 0.5f)) / dist;
            this->unk_1E0 *= 0.020000001f; // 3CA3D70B
            if (this->unk_1E0 > 0.00037f) {
                this->unk_1E0 = 0.00037f;
            } else if (this->unk_1E0 < 0.00015f) {
                this->unk_1E0 = 0.00015f;
            }
        }
    }

    Effect_Add(play, &this->effectIndex, 4, 0, 0, &D_80942E8C);
    EnGoroiwa_SetupRoll(this);
}

void EnGoroiwa_Destroy(Actor* thisx, PlayState* play) {
    EnGoroiwa* this = THIS;

    Collider_DestroyJntSph(play, &this->collider);
    Effect_Destroy(play, this->effectIndex);
}

// returns bool isBroken
s32 func_8094156C(EnGoroiwa* this, PlayState* play) {
    Actor* actor = &this->actor;
    s32 params = ENGOROIWA_GET_COLOR(&this->actor);
    EnGoroiwaStruct* ptr;
    s32 i;
    s32 isBroken = false;
    Vec3f sp80;

    // why is silver singled out? does it not stop?
    if ((this->collider.base.acFlags & AC_HIT) &&
        ((params == ENGOROIWA_COLOR_REDROCK) || (params == ENGOROIWA_COLOR_SNOWBALL))) {
        if (this->collider.elements->info.acHitInfo->toucher.dmgFlags & 0x4000) {
            s16 sp7E = BINANG_SUB(actor->yawTowardsPlayer, this->actor.world.rot.y);
            f32 temp;
            f32 temp2;
            f32 temp3;

            this->collisionDisabledTimer = 50;
            this->unk_1E8[0].unk_1C.y = BINANG_SUB(this->actor.yawTowardsPlayer, 0x4000);
            this->unk_1E8[0].unk_24 = Rand_ZeroOne() * -600.0f;
            this->unk_1E8[1].unk_1C.y = BINANG_ADD(this->actor.yawTowardsPlayer, 0x4000);
            this->unk_1E8[1].unk_24 = Rand_ZeroOne() * 600.0f;

            for (i = 0; i < ARRAY_COUNT(this->unk_1E8); i++) {
                ptr = &this->unk_1E8[i];

                ptr->unk_00.x = this->actor.world.pos.x;
                ptr->unk_00.y = this->actor.world.pos.y + this->unk_1DC;
                ptr->unk_00.z = this->actor.world.pos.z;

                temp = Rand_ZeroOne();
                temp2 = Math_SinS(ptr->unk_1C.y);
                temp3 = Math_SinS(this->actor.world.rot.y);

                ptr->unk_0C = ((1.0f / D_80942DFC[this->rollingSFXUpperIndex]) * (temp3 * 14.0f * this->actor.speed)) +
                              (temp2 * (temp + 5.0f));

                ptr->unk_10 = (Rand_ZeroOne() * 11.0f) + 20.0f;

                temp = Rand_ZeroOne();
                temp2 = Math_CosS(ptr->unk_1C.y);
                temp3 = Math_CosS(this->actor.world.rot.y);
                ptr->unk_14 =
                    ((1.0f / D_80942DFC[this->rollingSFXUpperIndex]) * ((temp3 * 14.0f) * this->actor.speed)) +
                    (temp2 * (temp + 5.0f));

                ptr->unk_1C.x = 0;
                ptr->unk_1C.z = 0;
                ptr->unk_22 = (s32)(Rand_ZeroOne() * 400.0f) + 1100;

                temp3 = Rand_ZeroOne();
                temp2 = Math_CosS(sp7E);
                ptr->unk_26 = (s32)(temp2 * 3000.0f) + (s32)(600.0f * (temp3 - 0.5f));
                ptr->unk_2D = 0;
                ptr->unk_2C = 0;
            }

            func_809421E0(this);
            sp80.x = this->actor.world.pos.x;
            sp80.y = this->actor.world.pos.y + this->unk_1DC;
            sp80.z = this->actor.world.pos.z;
            func_80940588(play, &sp80, sGoroiwaBrokenFragments[params], &sGoriwaUnkPrimColors[params],
                          &sGoriwaUnkEnvColors[params], this->actor.scale.x);
            EnGoroiwa_PlaySnowballBrokenSound(this, play);
            isBroken = true;
        } else if (((params == ENGOROIWA_COLOR_REDROCK) &&
                    (this->collider.elements->info.acHitInfo->toucher.dmgFlags & (0x400 | 0x100))) ||
                   ((params == ENGOROIWA_COLOR_SNOWBALL) && (this->collider.elements->info.acHitInfo->toucher.dmgFlags &
                                                             (0x80000000 | 0x800 | 0x400 | 0x100 | 0x8)))) {
            this->collisionDisabledTimer = 50;
            if ((params == ENGOROIWA_COLOR_SNOWBALL) &&
                (this->collider.elements->info.acHitInfo->toucher.dmgFlags & 0x800)) {
                this->unk_1E6 = 1;
            }

            func_80940090(this, play);
            EnGoroiwa_PlaySnowballBrokenSound(this, play);
            func_809425CC(this);
            isBroken = true;
        } else if ((params == ENGOROIWA_COLOR_SNOWBALL) && (this->unk_1E7 <= 0)) {
            func_80941060(this, play);
            this->unk_1E7 = 10;
        }
    }

    if (params == ENGOROIWA_COLOR_SNOWBALL) {
        if (this->unk_1E7 > 0) {
            this->unk_1E7--;
        }

        if (isBroken) {
            Item_DropCollectibleRandom(play, NULL, &this->actor.world.pos, 0x20);
        }
    }
    return isBroken;
}

void EnGoroiwa_SetupRoll(EnGoroiwa* this) {
    this->actionFunc = EnGoroiwa_Roll;
    EnGoriwa_UpdateFlags(this, (0x4 | 0x2 | 0x1));
    this->rollRotSpeed = 1.0f;
}

// quite a bit different from OOT
void EnGoroiwa_Roll(EnGoroiwa* this, PlayState* play) {
    static EnGoroiwaUnkFunc D_80942E94[] = { // MoveFunc?
        func_8093F498,
        EnGoroiwa_MoveAndFall,
    };
    static u16 sGoroiwaRollingSfx[][2] = {
        { NA_SE_EV_BIGBALL_ROLL - SFX_FLAG, NA_SE_EV_BIGBALL_ROLL_SR - SFX_FLAG },
        { NA_SE_EV_BIGBALL_ROLL_2 - SFX_FLAG, NA_SE_EV_BIGBALL_ROLL_SR_2 - SFX_FLAG },
        { NA_SE_EV_BIGBALL_ROLL_3 - SFX_FLAG, NA_SE_EV_BIGBALL_ROLL_SR_3 - SFX_FLAG },
        { NA_SE_EV_BIGBALL_ROLL - SFX_FLAG, NA_SE_EV_BIGBALL_ROLL_SR - SFX_FLAG },
    };
    s32 pad;
    Player* player = GET_PLAYER(play);
    // in OOT this was a y offset for height in child vs adult, in this game its different
    s32 param400 = ENGOROIWA_GET_400(&this->actor); // used as array index AND bool
    s32 param3000 = ENGOROIWA_GET_3000(&this->actor);
    s16 yawDiff;
    s32 pad2;

    if (!func_8094156C(this, play)) { // new to MM
        if ((this->collider.base.atFlags & AT_HIT) && !(player->stateFlags3 & PLAYER_STATE3_80000)) {
            s32 zRot = ENGOROIWA_GET_ROT_Z_3(this);

            if (zRot == 2) {
                func_80940090(this, play);
                if (param3000 == ENGOROIWA_3000_2) {
                    func_8093E8A0(this);
                    func_8093E91C(this);
                }
                EnGoroiwa_PlaySnowballBrokenSound(this, play);
                func_8093EDD8(this, play);
                EnGoroiwa_TeleportToWaypoint(this, 0);
                EnGoroiwa_InitRotation(this);
            } else {
                this->stateFlags &= ~8;
                yawDiff = this->actor.yawTowardsPlayer - this->actor.world.rot.y;
                if ((yawDiff > -0x4000) && (yawDiff < 0x4000)) {
                    this->stateFlags |= 8;
                    if (param400 || (zRot != 1)) {
                        func_8093EDB0(this);
                    }
                }
            }

            func_800B8D50(play, &this->actor, 2.0f, this->actor.yawTowardsPlayer, 0.0f, 0);

            if (zRot == 2) {
                EnGoroiwa_SetupWait(this);
            } else if (!param400) {
                EnGoroiwa_SetupWait(this);
            } else {
                EnGoroiwa_SetupMoveToGround(this);
            }

            Player_PlaySfx(player, NA_SE_PL_BODY_HIT);

            if ((zRot == 1) || (zRot == 2)) {
                this->collisionDisabledTimer = 50;
            }
        } else {
            if (D_80942E94[param400](this)) {
                // in OOT these were different, the mm dev re-used the local for two separate things
                union {
                    s32 loopMode;
                    s32 ascendDirection;
                } local_s32;

                local_s32.loopMode = ENGOROIWA_GET_LOOPMODE(&this->actor);

                if ((local_s32.loopMode == ENGOROIWA_LOOPMODE_ONEWAY_BREAK) &&
                    ((this->nextWaypoint == 0) || (this->nextWaypoint == this->endWaypoint))) {
                    func_80940090(this, play);
                    EnGoroiwa_PlaySnowballBrokenSound(this, play);
                }

                if (((local_s32.loopMode == ENGOROIWA_LOOPMODE_ONEWAY_BREAK) ||
                     (local_s32.loopMode == ENGOROIWA_LOOPMODE_ONEWAY)) &&
                    (param3000 == ENGOROIWA_3000_2) &&
                    ((this->nextWaypoint == 0) || (this->nextWaypoint == this->endWaypoint))) {
                    func_8093E8A0(this);
                    func_8093E91C(this);
                }

                EnGoroiwa_NextWaypoint(this);

                if ((local_s32.loopMode == ENGOROIWA_LOOPMODE_ROUNDTRIP) &&
                    ((this->currentWaypoint == 0) || (this->currentWaypoint == this->endWaypoint))) {
                    EnGoroiwa_SetupWait(this);
                } else if (!param400 && (this->currentWaypoint != 0) && (this->currentWaypoint != this->endWaypoint)) {
                    local_s32.ascendDirection = EnGoroiwa_GetAscendDirection(this);
                    if (local_s32.ascendDirection > 0) {
                        EnGoroiwa_SetupMoveUp(this);
                    } else if (local_s32.ascendDirection < 0) {
                        EnGoroiwa_SetupMoveDown(this);
                    } else {
                        EnGoroiwa_SetupRoll(this);
                    }
                } else {
                    EnGoroiwa_SetupRoll(this);
                }
            }
        }

        if (this->actor.bgCheckFlags & BGCHECKFLAG_GROUND) {
            Actor_PlaySfx(&this->actor,
                          sGoroiwaRollingSfx[this->rollingSFXUpperIndex][ENGOROIWA_GET_ROT_ROLLINGSFX_LOWER(this)]);
        }
    }
}

void EnGoroiwa_SetupMoveToGround(EnGoroiwa* this) {
    this->actionFunc = EnGoroiwa_MoveToGround;
    EnGoriwa_UpdateFlags(this, (0x4 | 0x2));
    this->actor.gravity = -0.86f;
    this->actor.terminalVelocity = -15.0f;
    this->actor.speed *= 0.15f;
    this->actor.velocity.y = 5.0f;
    this->rollRotSpeed = 1.0f;
}

void EnGoroiwa_MoveToGround(EnGoroiwa* this, PlayState* play) {
    EnGoroiwa_MoveAndFall(this);
    if ((this->actor.bgCheckFlags & BGCHECKFLAG_GROUND) && (this->actor.velocity.y < 0.0f)) {
        if ((this->stateFlags & 8) && (ENGOROIWA_GET_ROT_Z_3(this) == 1)) {
            func_8093EDB0(this);
        }
        EnGoroiwa_SetupWait(this);
    }
}

void EnGoroiwa_SetupWait(EnGoroiwa* this) {
    static s16 waitDuration[] = { 20, 6, 20 };

    this->actionFunc = EnGoroiwa_Wait;
    this->actor.speed = 0.0f;
    EnGoriwa_UpdateFlags(this, (0x4 | 0x2));
    this->timer = waitDuration[ENGOROIWA_GET_ROT_Z_3(this)];
    this->rollRotSpeed = 0.0f;
}

void EnGoroiwa_Wait(EnGoroiwa* this, PlayState* play) {
    if (!func_8094156C(this, play)) {
        if (this->timer > 0) {
            this->timer--;
        } else {
            EnGoroiwa_SetupRoll(this);
        }
    }
}

void EnGoroiwa_SetupMoveUp(EnGoroiwa* this) {
    this->actionFunc = EnGoroiwa_MoveUp;
    EnGoriwa_UpdateFlags(this, (0x4 | 0x2| 0x1));
    this->rollRotSpeed = 0.0f;
    this->actor.velocity.y = fabsf(this->actor.speed) * 0.1f;
}

void EnGoroiwa_MoveUp(EnGoroiwa* this, PlayState* play) {
    Player* player = GET_PLAYER(play);

    if (func_8094156C(this, play) == false) {
        if ((this->collider.base.atFlags & AT_HIT) && !(player->stateFlags3 & PLAYER_STATE3_80000)) {
            func_800B8D50(play, &this->actor, 2.0f, this->actor.yawTowardsPlayer, 0.0f, 0);
            Player_PlaySfx(player, NA_SE_PL_BODY_HIT);
            if ((ENGOROIWA_GET_ROT_Z_3(this) == 1) || (ENGOROIWA_GET_ROT_Z_3(this) == 2)) {
                this->collisionDisabledTimer = 50;
            }
        } else if (func_8093F5EC(this)) {
            EnGoroiwa_NextWaypoint(this);
            EnGoroiwa_SetupRoll(this);
            this->actor.speed = 0.0f;
        }
    }
}

void EnGoroiwa_SetupMoveDown(EnGoroiwa* this) {
    this->actionFunc = EnGoroiwa_MoveDown;
    EnGoriwa_UpdateFlags(this, (0x4 | 0x2| 0x1));
    this->rollRotSpeed = 0.3f;
    this->bounceCount = 0;
    this->actor.velocity.y = fabsf(this->actor.speed) * -0.3f;
    this->stateFlags |= ENGOROIWA_STATE_RETAIN_ROT_SPEED;
    this->stateFlags &= ~ENGOROIWA_STATE_INWATER;
}

void EnGoroiwa_MoveDown(EnGoroiwa* this, PlayState* play) {
    Player* player = GET_PLAYER(play);

    if (func_8094156C(this, play) == false) {
        if ((this->collider.base.atFlags & AT_HIT) && !(player->stateFlags3 & PLAYER_STATE3_80000)) {
            func_800B8D50(play, &this->actor, 2.0f, this->actor.yawTowardsPlayer, 0.0f, 0);
            Player_PlaySfx(player, NA_SE_PL_BODY_HIT);
            if ((ENGOROIWA_GET_ROT_Z_3(this) == 1) || (ENGOROIWA_GET_ROT_Z_3(this) == 2)) {
                this->collisionDisabledTimer = 50;
            }
        } else if (EnGoroiwa_MoveDownToNextWaypoint(this, play)) {
            EnGoroiwa_NextWaypoint(this);
            EnGoroiwa_SetupRoll(this);
            this->stateFlags &= ~ENGOROIWA_STATE_RETAIN_ROT_SPEED;
            this->actor.speed = 0.0f;
        }
    }
}

// setup... what
void func_809421E0(EnGoroiwa* this) {
    this->actionFunc = func_8094220C;
    EnGoriwa_UpdateFlags(this, 0);
}

void func_8094220C(EnGoroiwa* this, PlayState* play) {
    s32 pad;
    EnGoroiwaStruct* ptr;
    s32 i;
    s32 spD0;
    Vec3f spC4;
    Vec3f spB8;
    f32 phi_f12;
    f32 temp_f20;
    f32 spAC;
    s32 color;
    Vec3f sp9C;
    s16 sp9A;

    for (i = 0; i < ARRAY_COUNT(this->unk_1E8); i++) {
        ptr = &this->unk_1E8[i];

        if (!(ptr->unk_2D & 1)) {
            ptr->unk_10 -= 6.0f;
            if (ptr->unk_10 < -20.0f) {
                ptr->unk_10 = -20.0f;
            }
            ptr->unk_00.x += ptr->unk_0C;
            ptr->unk_00.y += ptr->unk_10;
            ptr->unk_00.z += ptr->unk_14;

            ptr->unk_1C.x += ptr->unk_22;
            ptr->unk_1C.y += ptr->unk_24;
            ptr->unk_1C.z += ptr->unk_26;

            spC4.x = ptr->unk_00.x;
            spC4.y = ptr->unk_00.y + 25.0f;
            spC4.z = ptr->unk_00.z;

            ptr->floorHeight = BgCheck_EntityRaycastFloor5(&play->colCtx, &ptr->unk_28, &spD0, &this->actor, &spC4);

            if (ptr->unk_10 <= 0.0f) {
                Matrix_RotateZYX(ptr->unk_1C.x, ptr->unk_1C.y, ptr->unk_1C.z, MTXMODE_NEW);
                Matrix_MultVec3f(&D_80942E6C, &spB8);
                temp_f20 = this->unk_1DC * 0.9f;

                if (spB8.y > 0.0f) {
                    if (Math3D_AngleBetweenVectors(&D_80942E60, &spB8, &spAC)) {
                        phi_f12 = 1.0f;
                    } else {
                        phi_f12 = 1.0f - SQ(spAC);
                    }

                    if (phi_f12 <= 0.0f) {
                        temp_f20 = 0.0f;
                    } else {
                        temp_f20 *= sqrtf(phi_f12);
                    }
                }

                if (((ptr->unk_00.y + (this->unk_1DC - temp_f20)) < ptr->floorHeight) ||
                    (ptr->floorHeight < (BGCHECK_Y_MIN + 10))) {
                    color = ENGOROIWA_GET_COLOR(&this->actor);
                    ptr->unk_2D |= 1;
                    sp9C.x = ptr->unk_00.x;
                    sp9C.y = (ptr->unk_00.y - ptr->unk_10) + 10.0f;
                    sp9C.z = ptr->unk_00.z;

                    func_80940A1C(play, &sp9C, sGoroiwaBrokenFragments[color], &sGoriwaUnkPrimColors[color],
                                  &sGoriwaUnkEnvColors[color], this->actor.scale.x);
                }
            }
        }
    }

    if ((this->unk_1E8[0].unk_2D & 1) && (this->unk_1E8[1].unk_2D & 1)) {
        func_809425CC(this);
        return;
    }

    sp9A = this->actor.shape.shadowAlpha;
    Math_StepToS(&sp9A, 0, 40);
    this->actor.shape.shadowAlpha = sp9A;

    for (i = 0; i < ARRAY_COUNT(this->unk_1E8); i++) {
        ptr = &this->unk_1E8[i];

        if (ptr->unk_2D & 1) {
            ptr->unk_2C = 0;
        } else {
            sp9A = ptr->unk_2C;
            Math_StepToS(&sp9A, 160, 24);
            ptr->unk_2C = sp9A;
        }
    }
}

void func_809425CC(EnGoroiwa* this) {
    this->actionFunc = func_80942604;
    EnGoriwa_UpdateFlags(this, 0);
    this->timer = 100;
}

void func_80942604(EnGoroiwa* this, PlayState* play) {
    s32 pad;
    s16 alpha = this->actor.shape.shadowAlpha;

    Math_StepToS(&alpha, 0, 40);
    this->actor.shape.shadowAlpha = alpha;
    if (this->timer > 0) {
        this->timer--;
    } else {
        Actor_Kill(&this->actor);
    }
}

void EnGoroiwa_Update(Actor* thisx, PlayState* play) {
    s32 pad;
    EnGoroiwa* this = THIS;
    Player* player = GET_PLAYER(play);
    s32 bgId;
    s32 sp5C = false;
    Vec3f sp50;
    f32 sp4C;
    s32 sp48 = true;
    FloorType floorType;
    CollisionPoly* floorBgId;

    if (!(player->stateFlags1 & (PLAYER_STATE1_40 | PLAYER_STATE1_80 | PLAYER_STATE1_10000000 | PLAYER_STATE1_20000000))) {
        if (this->collisionDisabledTimer > 0) {
            this->collisionDisabledTimer--;
        }

        if ((ENGOROIWA_GET_3000(&this->actor) == ENGOROIWA_3000_2) && (this->actor.bgCheckFlags & BGCHECKFLAG_GROUND) &&
            (this->actionFunc == EnGoroiwa_Roll) && (this->actor.speed > 2.0f)) {
            Math_StepToF(&this->actor.scale.x, 0.16f,
                         (this->actor.xzDistToPlayer < 400.0f) ? this->unk_1E0 * 1.4f : this->unk_1E0);

            this->actor.scale.y = this->actor.scale.x;
            this->actor.scale.z = this->actor.scale.x;
            func_8093E91C(this);
            sp5C = true;

            if (this->actor.flags & ACTOR_FLAG_40) {
                floorBgId = this->actor.floorPoly;
                if (floorBgId != NULL) {
                    floorType = SurfaceType_GetFloorType(&play->colCtx, floorBgId, this->actor.floorBgId);

                    if ((floorType == FLOOR_TYPE_14) || (floorType == FLOOR_TYPE_15)) {
                        if (!(this->stateFlags & 0x40)) {
                            sp50.x = this->actor.world.pos.x;
                            sp50.y = this->actor.floorHeight;
                            sp50.z = this->actor.world.pos.z;
                            sp4C = (((Rand_ZeroOne() * 36.0f) + 250.0f) * this->actor.scale.x) + 10.0f;
                            func_800AE930(&play->colCtx, Effect_GetByIndex(this->effectIndex), &sp50, sp4C,
                                          this->actor.world.rot.y, this->actor.floorPoly, this->actor.floorBgId);
                        }
                        sp48 = false;
                    }
                }
            }
        }

        if (sp48) {
            func_800AEF44(Effect_GetByIndex(this->effectIndex));
        }

        this->actionFunc(this, play);

        if (this->actor.update != NULL) { // huh? we're in here already, no other actor/process should null our update by this point, right?
            EnGoroiwa_AdjustYaw(this);

            if (sp5C) {
                func_80940E38(this, play);
            }

            switch (ENGOROIWA_GET_400(&this->actor)) {
                case ENGOROIWA_400_1:
                    Actor_UpdateBgCheckInfo(play, &this->actor, 0.0f, 0.0f, 0.0f,
                                            UPDBGCHECKINFO_FLAG_4 | UPDBGCHECKINFO_FLAG_8 | UPDBGCHECKINFO_FLAG_10);
                    break;

                case ENGOROIWA_400_0:
                    sp50.x = this->actor.world.pos.x;
                    sp50.y = this->actor.world.pos.y + 50.0f;
                    sp50.z = this->actor.world.pos.z;
                    this->actor.floorHeight =
                        BgCheck_EntityRaycastFloor5(&play->colCtx, &this->actor.floorPoly, &bgId, &this->actor, &sp50);
                    if (this->actor.floorHeight > BGCHECK_Y_MIN) {
                        this->actor.floorBgId = bgId;
                        if (this->actor.world.pos.y <= (this->actor.floorHeight + 2.0f)) {
                            this->actor.bgCheckFlags |= BGCHECKFLAG_GROUND;
                        } else {
                            this->actor.bgCheckFlags &= ~BGCHECKFLAG_GROUND;
                        }
                    } else {
                        this->actor.bgCheckFlags &= ~BGCHECKFLAG_GROUND;
                        this->actor.floorBgId = 50;
                    }
                    break;

                default:
                    break;
            }

            EnGoroiwa_UpdateRotation(this, play);

            if (this->actor.flags & ACTOR_FLAG_40) {
                s32 color = ENGOROIWA_GET_COLOR(&this->actor);

                EnGoroiwa_UpdateColliderPos(this);

                if ((this->stateFlags & 1) && (this->collisionDisabledTimer <= 0) &&
                    (!(player->stateFlags3 & PLAYER_STATE3_2000000) || (player->transformation != PLAYER_FORM_GORON) ||
                     ((color != ENGOROIWA_COLOR_REDROCK) && (color != ENGOROIWA_COLOR_SNOWBALL)))) {
                    CollisionCheck_SetAT(play, &play->colChkCtx, &this->collider.base);
                } else {
                    this->collider.base.atFlags &= ~AT_HIT;
                }

                if (this->stateFlags & 2) {
                    CollisionCheck_SetAC(play, &play->colChkCtx, &this->collider.base);
                } else {
                    this->collider.base.acFlags &= ~AC_HIT;
                }

                if ((this->stateFlags & 4) && (this->collisionDisabledTimer <= 0)) {
                    CollisionCheck_SetOC(play, &play->colChkCtx, &this->collider.base);
                } else {
                    this->collider.base.ocFlags1 &= ~OC1_HIT;
                }
            } else {
                this->collider.base.atFlags &= ~AT_HIT;
                this->collider.base.ocFlags1 &= ~OC1_HIT;
                this->collider.base.acFlags &= ~AC_HIT;
            }
        }
    }
}

void func_80942B1C(EnGoroiwa* this, PlayState* play) {
    s32 pad;
    s32 pad2;
    s32 i;
    EnGoroiwaStruct* ptr;
    s32 color = ENGOROIWA_GET_COLOR(&this->actor);
    Gfx* halfDL;
    MtxF sp88;
    Vec3s sp80;

    if (color == ENGOROIWA_COLOR_REDROCK) {
        halfDL = gGoroiwaRedRockHalfDL;
    } else {
        halfDL = gGoroiwaSnowBallHalfDL;
    }
    // NOTE: missing silver half, not found in the object either

    for (i = 0; i < ARRAY_COUNT(this->unk_1E8); i++) {
        ptr = &this->unk_1E8[i];

        if (!(ptr->unk_2D & 1)) {
            sp80.x = ptr->unk_1C.x;
            sp80.y = ptr->unk_1C.y;
            sp80.z = ptr->unk_1C.z;

            Matrix_SetTranslateRotateYXZ(ptr->unk_00.x, ptr->unk_00.y, ptr->unk_00.z, &sp80);
            Matrix_Scale(this->actor.scale.x, this->actor.scale.y, this->actor.scale.z, MTXMODE_APPLY);
            Gfx_DrawDListOpa(play, halfDL);

            if ((ptr->unk_28 != 0) && (ptr->unk_2C > 0)) {
                OPEN_DISPS(play->state.gfxCtx);

                Gfx_SetupDL44_Xlu(play->state.gfxCtx);

                gDPSetCombineLERP(POLY_XLU_DISP++, 0, 0, 0, PRIMITIVE, TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0, COMBINED, 0, 0,
                                  0, COMBINED);
                gDPSetPrimColor(POLY_XLU_DISP++, 0, 0, 0, 0, 0, ptr->unk_2C);

                func_800C0094(ptr->unk_28, ptr->unk_00.x, ptr->floorHeight, ptr->unk_00.z, &sp88);
                Matrix_Put(&sp88);
                Matrix_Scale(this->actor.scale.x * 7.5f, 1.0f, this->actor.scale.z * 7.5f, MTXMODE_APPLY);

                gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(play->state.gfxCtx),
                          G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
                gSPDisplayList(POLY_XLU_DISP++, gCircleShadowDL);

                CLOSE_DISPS(play->state.gfxCtx);
            }
        }
    }
}

void EnGoroiwa_Draw(Actor* thisx, PlayState* play) {
    static Gfx* sGoroiwaTextures[] = {
        gGoroiwaSilverRockDL,
        gGoroiwaRedRockDL,
        gGoroiwaSnowBallDL,
    };
    EnGoroiwa* this = THIS;
    s32 color = ENGOROIWA_GET_COLOR(&this->actor);

    if (this->actionFunc == func_8094220C) {
        // draw half only, as unit has broken
        func_80942B1C(this, play);
    } else if (this->actionFunc != func_80942604) {
        // draw regular
        Gfx_DrawDListOpa(play, sGoroiwaTextures[color]);
    }
    //! BUG: Uncaught case (this->actionFunc == func_80942604), assumed they did not want to draw there
}
