/*
 * File: z_obj_toge.c
 * Overlay: ovl_Obj_Toge
 * Description: Blade Trap - A spike trap that either slides back and forth along a path
 *              or acts as a stationary hitbox zone around a rectangular area.
 *              Uses the object_trap object (OBJECT_TRAP).
 *              Renders: object_trap_DL_001400
 */

#include "z_obj_toge.h"
#include "assets/objects/object_trap/object_trap.h"

#define FLAGS (ACTOR_FLAG_UPDATE_CULLING_DISABLED)

void ObjToge_Init(Actor* thisx, PlayState* play);
void ObjToge_Destroy(Actor* thisx, PlayState* play2);
void ObjToge_Update(Actor* thisx, PlayState* play);
void ObjToge_Draw(Actor* thisx, PlayState* play);

void ObjToge_SetupSlide(ObjToge* this);
void ObjToge_Slide(ObjToge* this, PlayState* play);
void ObjToge_SetupHitbox(ObjToge* this);
void ObjToge_Hitbox(ObjToge* this, PlayState* play);
void ObjToge_SetupMove(ObjToge* this);
void ObjToge_Move(ObjToge* this, PlayState* play);

ActorProfile Obj_Toge_Profile = {
    /**/ ACTOR_OBJ_TOGE,
    /**/ ACTORCAT_PROP,
    /**/ FLAGS,
    /**/ OBJECT_TRAP,
    /**/ sizeof(ObjToge),
    /**/ ObjToge_Init,
    /**/ ObjToge_Destroy,
    /**/ ObjToge_Update,
    /**/ ObjToge_Draw,
};

static ColliderCylinderInit sCylinderInit = {
    {
        COL_MATERIAL_METAL,
        AT_NONE,
        AC_ON | AC_HARD | AC_TYPE_PLAYER,
        OC1_ON | OC1_TYPE_ALL,
        OC2_TYPE_2,
        COLSHAPE_CYLINDER,
    },
    {
        ELEM_MATERIAL_UNK0,
        { 0x00000000, 0x00, 0x00 },
        { 0x01C37BB6, 0x00, 0x00 },
        ATELEM_NONE | ATELEM_SFX_NORMAL,
        ACELEM_ON,
        OCELEM_ON,
    },
    { 30, 20, 0, { 0, 0, 0 } },
};

f32 gTogeSpeeds[] = { 2.0f, 4.0f, 6.0f, 8.0f, 10.0f, 12.0f, 14.0f, 16.0f };

// Delay/timer values in frames, indexed by params bits 11-13 (OBJTOGE_GET_DELAY)
// Used as initial countdown before the sliding trap begins moving
s16 gDelayTimes[] = { 0, 10, 20, 30, 40, 50, 60, 70 };

// Scale multipliers indexed by params bit 14 (OBJTOGE_GET_4000)
// Variant 0 (sliding): scale = 1.0f * 0.1f
// Variant 1 (hitbox): scale = 2.0f * 0.1f
f32 D_809A4D0C[] = { 1.0f, 2.0f };

static InitChainEntry sInitChain[] = {
    ICHAIN_F32_DIV1000(terminalVelocity, 0, ICHAIN_CONTINUE),
    ICHAIN_F32(cullingVolumeDistance, 4000, ICHAIN_CONTINUE),
    ICHAIN_F32(cullingVolumeScale, 150, ICHAIN_CONTINUE),
    ICHAIN_F32(cullingVolumeDownward, 150, ICHAIN_STOP),
};

/**
 * Spawns ice arrow hit effect particles around the trap.
 * Used by the sliding variant when hit by an ice arrow.
 * Spawns 3 particle clusters in a triangular pattern offset from the trap center.
 */
void func_809A41C0(ObjToge* this, PlayState* play) {
    Vec3f sp1C = this->actor.world.pos;

    // First particle cluster: offset +10 Z from trap center, +10 Y (height)
    sp1C.y += 10.0f;
    sp1C.z += 10.0f;
    func_800B2B44(play, &this->actor, &sp1C, 1.8f);

    // Second particle cluster: offset +10 X, -20 Z from first position
    sp1C.x += 10.0f;
    sp1C.z -= 20.0f;
    func_800B2B44(play, &this->actor, &sp1C, 1.8f);

    // Third particle cluster: offset -20 X from second position
    sp1C.x -= 20.0f;
    func_800B2B44(play, &this->actor, &sp1C, 1.8f);
}

/**
 * Spawns ice arrow hit effect particles in a circular pattern around the trap.
 * Used by the hitbox variant when hit by an ice arrow.
 * Spawns 5 particle clusters in a circle of radius 15 around the trap.
 */
void func_809A42A0(ObjToge* this, PlayState* play) {
    Vec3f sp54;
    s32 i;
    s16 phi_s0;

    sp54.y = this->actor.world.pos.y + 15.0f;

    for (i = 0, phi_s0 = 0; i < 5; i++, phi_s0 += 0x3333) {
        sp54.x = (Math_SinS(phi_s0) * 15.0f) + this->actor.world.pos.x;
        sp54.z = (Math_CosS(phi_s0) * 15.0f) + this->actor.world.pos.z;
        func_800B2B44(play, &this->actor, &sp54, (Rand_ZeroOne() * 0.6f) + 2.8f);
    }
}

/**
 * Spawns ice arrow hit particles based on the trap variant.
 * Linear pattern for sliding variant, circular pattern for hitbox variant.
 */
void func_809A43A8(ObjToge* this, PlayState* play) {
    if (!OBJTOGE_GET_4000(&this->actor)) {
        func_809A41C0(this, play);
    } else {
        func_809A42A0(this, play);
    }
}

/**
 * Checks if the player is currently within the rectangular damage zone.
 * Only used by the hitbox variant (OBJTOGE_GET_4000 == 1).
 *
 * Uses a point-in-rectangle test: transforms the player position into
 * a coordinate system aligned with the rectangle's axes, then checks
 * if the transformed coordinates fall within the rectangle bounds.
 *
 * The rectangle is centered at (unk_1B8, unk_1BC) and rotated by the
 * yaw angle between the two path endpoints. unk_1C0 is the half-width
 * in the rotated X axis (based on home.rot.z), unk_1C4 is the half-width
 * in the rotated Z axis (half the distance between path endpoints).
 *
 * @return true if player is inside the damage rectangle
 */
bool func_809A43EC(ObjToge* this, PlayState* play) {
    Player* player = GET_PLAYER(play);
    f32 temp_fv1 = player->actor.world.pos.x - this->unk_1B8;
    f32 temp_fa0 = player->actor.world.pos.z - this->unk_1BC;
    f32 temp = -(this->unk_1CC * temp_fa0) + (temp_fv1 * this->unk_1C8);
    f32 temp2 = (this->unk_1CC * temp_fv1) + (temp_fa0 * this->unk_1C8);

    return fabsf(temp) <= this->unk_1C0 && fabsf(temp2) <= this->unk_1C4;
}

/**
 * Initializes the blade trap actor.
 *
 * Processes the init chain, sets up the collider, reads the path from
 * play->setupPathList, and stores the two endpoint positions.
 *
 * The actor has two modes controlled by params bit 14 (OBJTOGE_GET_4000):
 *   0 - Sliding mode: moves back and forth between two path endpoints
 *   1 - Hitbox mode: stays at its spawn position and damages players
 *      within a rectangular zone defined by home.rot.z
 *
 * A path with exactly 2 points is required. If the path index is invalid
 * or the path doesn't have exactly 2 points, the actor kills itself.
 *
 * home.rot.z is used as the hitbox zone radius for the hitbox variant.
 * When positive (> 0), the trap creates a rectangular damage zone.
 */
void ObjToge_Init(Actor* thisx, PlayState* play) {
    s32 pad;
    ObjToge* this = (ObjToge*)thisx;
    Path* path;
    Vec3s* points;
    s16 hitboxRadius;
    s32 variant = OBJTOGE_GET_4000(thisx);

    Actor_ProcessInitChain(thisx, sInitChain);
    Actor_SetScale(thisx, D_809A4D0C[variant] * 0.1f);

    hitboxRadius = thisx->home.rot.z;
    thisx->home.rot.z = thisx->world.rot.z = thisx->shape.rot.z = 0;

    Collider_InitCylinder(play, &this->collider);

    if (OBJTOGE_GET_PATH_INDEX(thisx) == OBJTOGE_PATH_INDEX_NONE) {
        Actor_Kill(thisx);
        return;
    }

    path = &play->setupPathList[OBJTOGE_GET_PATH_INDEX(thisx)];
    if (path->count != 2) {
        Actor_Kill(thisx);
        return;
    }

    points = Lib_SegmentedToVirtual(path->points);
    Math_Vec3s_ToVec3f(&this->pathPoints[0], &points[0]);
    Math_Vec3s_ToVec3f(&this->pathPoints[1], &points[1]);
    Math_Vec3f_Copy(&thisx->world.pos, &this->pathPoints[0]);
    thisx->world.rot.y = Math_Vec3f_Yaw(&this->pathPoints[0], &this->pathPoints[1]);
    this->pathPointTarget = 0;
    thisx->speed = 0.0f;

    if (hitboxRadius > 0) {
        s16 sp36;

        this->unk_1B4 = true;
        this->unk_1B8 = (this->pathPoints[0].x + this->pathPoints[1].x) * 0.5f;
        this->unk_1BC = (this->pathPoints[0].z + this->pathPoints[1].z) * 0.5f;

        sp36 = Math_Vec3f_Yaw(&this->pathPoints[0], &this->pathPoints[1]);
        this->unk_1C8 = Math_CosS(sp36);
        this->unk_1CC = Math_SinS(sp36);
        this->unk_1C0 = hitboxRadius * 7.5f;
        this->unk_1C4 = Math3D_Vec3f_DistXYZ(&this->pathPoints[0], &this->pathPoints[1]) * 0.5f;
    } else {
        this->unk_1B4 = false;
    }

    Collider_SetCylinder(play, &this->collider, thisx, &sCylinderInit);
    Collider_UpdateCylinder(thisx, &this->collider);
    thisx->colChkInfo.mass = MASS_IMMOVABLE;

    if (variant == 1) {
        this->collider.dim.radius = 60;
        this->collider.dim.height = 40;
    }

    if (this->unk_1B4) {
        ObjToge_SetupHitbox(this);
    } else {
        ObjToge_SetupSlide(this);
    }
}

void ObjToge_Destroy(Actor* thisx, PlayState* play2) {
    PlayState* play = play2;
    ObjToge* this = (ObjToge*)thisx;

    Collider_DestroyCylinder(play, &this->collider);
}

/**
 * Sets up the sliding mode action function.
 * Starts a delay timer (delayTimer) before the trap begins moving.
 * The delay value is selected from gDelayTimes[] based on params bits 11-13.
 */
void ObjToge_SetupSlide(ObjToge* this) {
    this->actionFunc = ObjToge_Slide;
    this->spinRot = 0;
    this->delayTimer = gDelayTimes[OBJTOGE_GET_DELAY(&this->actor)];
}

/**
 * Handles the sliding mode for the blade trap.
 *
 * First waits for the delay timer (delayTimer) to expire. Then increments
 * the rotation angle (spinRot) each frame until it reaches 0x1770
 * (approximately 59.7 degrees), at which point it transitions to
 * the movement phase. The actor's visual rotation increases by
 * spinRot each frame to create a spinning blade effect.
 */
void ObjToge_Slide(ObjToge* this, PlayState* play) {
    if (this->delayTimer > 0) {
        this->delayTimer--;
    }

    if (this->spinRot >= 0x1770) {
        this->spinRot = 0x1770;
        ObjToge_SetupMove(this);
    } else if ((this->spinRot > 0) || (this->delayTimer <= 0)) {
        this->spinRot += 200;
    }

    if (!this->unk_1B4) {
        this->actor.shape.rot.y += this->spinRot;
    }
}

/**
 * Sets up the hitbox mode action function.
 * The hitbox variant has no delay timer.
 */
void ObjToge_SetupHitbox(ObjToge* this) {
    this->actionFunc = ObjToge_Hitbox;
    this->spinRot = 0;
}

/**
 * Handles the hitbox mode for the blade trap.
 *
 * Increments the rotation angle (spinRot) each frame until it reaches
 * 0x1770, at which point it transitions to the movement phase.
 * The rotation starts incrementing either when spinRot is already
 * positive or when the player enters the damage rectangle (checked
 * via func_809A43EC).
 *
 * The actor's visual rotation increases by spinRot each frame.
 */
void ObjToge_Hitbox(ObjToge* this, PlayState* play) {
    if (this->spinRot >= 0x1770) {
        this->spinRot = 0x1770;
        ObjToge_SetupMove(this);
    } else if ((this->spinRot > 0) || func_809A43EC(this, play)) {
        this->spinRot += 200;
    }
    this->actor.shape.rot.y += this->spinRot;
}

/**
 * Transitions to the movement phase.
 * Sets speed to 1.0f and switches the action function to ObjToge_Move.
 */
void ObjToge_SetupMove(ObjToge* this) {
    this->actor.speed = 1.0f;
    this->actionFunc = ObjToge_Move;
}

/**
 * Handles the movement phase for the blade trap.
 *
 * The trap moves between two path endpoints stored in pathPoints[0] and
 * pathPoints[1]. The flag pathPointTarget tracks which endpoint is the current
 * target (0 or 1), and flips when the trap hits a wall or deviates
 * too far from its path.
 *
 * For the hitbox variant (unk_1B4 == true):
 *   - Only speeds up to 2.0f when pathPointTarget == 1 (moving in one direction)
 *   - Does not spin visually (rotation stays at 0x1770)
 *
 * For the sliding variant (unk_1B4 == false):
 *   - Speeds up using the speed table (params bits 8-10) via gTogeSpeeds[]
 *   - Spins continuously by adding 0x1770 to rotation each bounce
 *
 * Direction changes are triggered by:
 *   1. Hitting a wall (BGCHECKFLAG_WALL)
 *   2. The angle to the target endpoint deviating beyond 0x4000
 *      (approximately 180 degrees, i.e., the trap has passed the endpoint)
 *      or the angle being exactly -0x8000 (180 degrees)
 */
void ObjToge_Move(ObjToge* this, PlayState* play) {
    s32 pad;
    s32 nextEndpoint = this->pathPointTarget ^ 1;

    if (this->unk_1B4 && (this->pathPointTarget == 1)) {
        Math_StepToF(&this->actor.speed, 2.0f, 0.4f);
    } else {
        Math_StepToF(&this->actor.speed, gTogeSpeeds[OBJTOGE_GET_SPEED(&this->actor)], 1.5f);
        this->actor.shape.rot.y += 0x1770;
    }

    Actor_MoveWithGravity(&this->actor);
    Actor_UpdateBgCheckInfo(play, &this->actor, 10.0f, D_809A4D0C[OBJTOGE_GET_4000(&this->actor)] * 30.0f, 0.0f,
                            UPDBGCHECKINFO_FLAG_1 | UPDBGCHECKINFO_FLAG_80);

    if (this->actor.bgCheckFlags & BGCHECKFLAG_WALL) {
        this->actor.world.rot.y = Math_Vec3f_Yaw(&this->actor.world.pos, &this->pathPoints[this->pathPointTarget]);
        this->pathPointTarget = nextEndpoint;
        if (this->unk_1B4 && (this->pathPointTarget == 0)) {
            ObjToge_SetupHitbox(this);
        } else {
            ObjToge_SetupSlide(this);
        }
        Actor_PlaySfx(&this->actor, NA_SE_EV_SPINE_TRAP_MOVE);
    } else {
        s16 yaw = Math_Vec3f_Yaw(&this->actor.world.pos, &this->pathPoints[nextEndpoint]) - this->actor.world.rot.y;

        yaw = ABS_ALT(yaw);
        if ((yaw > 0x4000) || (yaw == -0x8000)) {
            this->actor.world.rot.y = Math_Vec3f_Yaw(&this->actor.world.pos, &this->pathPoints[this->pathPointTarget]);
            this->pathPointTarget = nextEndpoint;
            if (this->unk_1B4 && (this->pathPointTarget == 0)) {
                ObjToge_SetupHitbox(this);
            } else {
                ObjToge_SetupSlide(this);
            }
            Actor_PlaySfx(&this->actor, NA_SE_EV_SPINE_TRAP_MOVE);
        }
    }
}

void ObjToge_Update(Actor* thisx, PlayState* play) {
    ObjToge* this = (ObjToge*)thisx;
    ColliderCylinder* collider = &this->collider;

    if (this->collider.base.acFlags & AC_HIT) {
        if (this->collider.elem.acHitElem->atDmgInfo.dmgFlags & 0x1000) {
            func_809A43A8(this, play);
            Actor_SetColorFilter(&this->actor, COLORFILTER_COLORFLAG_BLUE, 250, COLORFILTER_BUFFLAG_OPA, 250);
        }
        collider->base.acFlags &= ~AC_HIT;
    }

    if (this->actor.colorFilterTimer == 0) {
        if (this->collider.base.ocFlags2 & OC2_HIT_PLAYER) {
            func_800B8DD4(play, &this->actor, 6.0f, this->actor.yawTowardsPlayer, 6.0f, 4);
        }

        this->actionFunc(this, play);

        Collider_UpdateCylinder(&this->actor, &this->collider);
        if (this->actor.xzDistToPlayer < 1000.0f) {
            CollisionCheck_SetAC(play, &play->colChkCtx, &this->collider.base);
        }
    }

    if ((this->actor.flags & ACTOR_FLAG_INSIDE_CULLING_VOLUME) || (this->actor.xzDistToPlayer < 300.0f)) {
        CollisionCheck_SetOC(play, &play->colChkCtx, &collider->base);
    } else {
        this->collider.base.ocFlags1 &= ~OC1_HIT;
        this->collider.base.ocFlags2 &= ~OC2_HIT_PLAYER;
    }
}

void ObjToge_Draw(Actor* thisx, PlayState* play) {
    ObjToge* this = (ObjToge*)thisx;

    func_800B8050(&this->actor, play, 1);
    Gfx_DrawDListOpa(play, object_trap_DL_001400);
}
