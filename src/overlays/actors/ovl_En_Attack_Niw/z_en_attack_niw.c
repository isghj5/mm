/*
 * File: z_en_attack_niw.c
 * Overlay: ovl_En_Attack_Niw
 * Description: Attacking cucco
 */

#include "z_en_attack_niw.h"
#include "overlays/actors/ovl_En_Niw/z_en_niw.h"

#define FLAGS (ACTOR_FLAG_10)

#define THIS ((EnAttackNiw*)thisx)

void EnAttackNiw_Init(Actor* thisx, GlobalContext* globalCtx);
void EnAttackNiw_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnAttackNiw_Update(Actor* thisx, GlobalContext* globalCtx);
void EnAttackNiw_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_80958634(EnAttackNiw* this, GlobalContext* globalCtx);
void func_80958974(EnAttackNiw* this, GlobalContext* globalCtx);
void func_80958BE4(EnAttackNiw* this, GlobalContext* globalCtx);

const ActorInit En_Attack_Niw_InitVars = {
    ACTOR_EN_ATTACK_NIW,
    ACTORCAT_ENEMY,
    FLAGS,
    OBJECT_NIW,
    sizeof(EnAttackNiw),
    (ActorFunc)EnAttackNiw_Init,
    (ActorFunc)EnAttackNiw_Destroy,
    (ActorFunc)EnAttackNiw_Update,
    (ActorFunc)EnAttackNiw_Draw,
};

static InitChainEntry sInitChain[] = {
    ICHAIN_U8(targetMode, 1, ICHAIN_CONTINUE),
    ICHAIN_F32_DIV1000(gravity, -2000, ICHAIN_CONTINUE),
    ICHAIN_F32(targetArrowOffset, 0, ICHAIN_STOP),
};

void EnAttackNiw_Init(Actor* thisx, GlobalContext* globalCtx) {
    EnAttackNiw* this = THIS;

    Actor_ProcessInitChain(&this->actor, sInitChain);
    ActorShape_Init(&this->actor.shape, 0.0f, ActorShadow_DrawCircle, 25.0f);
    SkelAnime_InitFlex(globalCtx, &this->skelAnime, &gNiwSkeleton, &gNiwIdleAnim, this->jointTable,
                       this->morphTable, NIW_LIMB_MAX);

    // probably copy pasted from EnNiw, which has this same code, but AttackNiw has no params
    if (this->actor.params < 0) {
        this->actor.params = 0;
    }

    Actor_SetScale(&this->actor, 0.01f);
    this->actor.gravity = 0.0f;

    this->unk_290.x = randPlusMinusPoint5Scaled(100.0f);
    this->unk_290.y = randPlusMinusPoint5Scaled(10.0f);
    this->unk_290.z = randPlusMinusPoint5Scaled(100.0f);

    Actor_SetScale(&this->actor, 0.01f);
    this->actor.flags &= ~ACTOR_FLAG_1; // Unnecessary: this actor does not start with this flag
    this->actor.shape.rot.y = this->actor.world.rot.y = (Rand_ZeroOne() - 0.5f) * 60000.0f;
    this->actionFunc = func_80958634;
}

void EnAttackNiw_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    EnAttackNiw* this = THIS;
    EnNiw* parent = (EnNiw*)this->actor.parent;

    if ((thisx->parent != NULL) && (thisx->parent->update != NULL)) {
        if (parent->attackNiwCount > 0) {
            parent->attackNiwCount--;
        }
    }
}

// what is arg
void func_80958228(EnAttackNiw* this, GlobalContext* globalCtx, s16 arg2) {
    if (this->unk_24C == 0) {
        if (arg2 == 0) {
            this->targetBodyRotY = 0.0f;
        } else {
            this->targetBodyRotY = -10000.0f;
        }
        this->unk_286++;
        this->unk_24C = 3;
        if ((this->unk_286 % 2) == 0) {
            this->targetBodyRotY = 0.0f;
            if (arg2 == 0) {
                this->unk_24C = Rand_ZeroFloat(30.0f);
            }
        }
    }

    if (this->unk_250 == 0) {
        this->unk_28A++;
        this->unk_28A &= 1;

        switch (arg2) {
            case 0:
                this->targetLeftWingRotZ = 0.0f;
                this->targetRightWingRotZ = 0.0f;
                break;

            case 1:
                this->unk_250 = 3;
                this->targetLeftWingRotZ = 7000.0f;
                this->targetRightWingRotZ = 7000.0f;
                if (this->unk_28A == 0) {
                    this->targetLeftWingRotZ = 0.0f;
                    this->targetRightWingRotZ = 0.0f;
                }
                break;

            case 2:
                this->unk_250 = 2;
                this->targetLeftWingRotZ = -10000.0f;
                this->targetRightWingRotZ = -10000.0f;
                this->targetLeftWingRotY = 25000.0f;
                this->targetRightWingRotY = 25000.0f;
                this->targetLeftWingRotX = 6000.0f;
                this->targetRightWingRotX = 6000.0f;
                if (this->unk_28A == 0) {
                    this->targetRightWingRotY = 8000.0f;
                    this->targetLeftWingRotY = 8000.0f;
                }
                break;

            case 3:
                this->unk_250 = 2;
                this->targetRightWingRotY = 10000.0f;
                this->targetLeftWingRotY = 10000.0f;
                if (this->unk_28A == 0) {
                    this->targetRightWingRotY = 3000.0f;
                    this->targetLeftWingRotY = 3000.0f;
                }
                break;

            case 4:
                this->unk_24E = 5;
                this->unk_24C = this->unk_24E;
                break;

            case 5:
                this->unk_250 = 5;
                this->targetRightWingRotY = 14000.0f;
                this->targetLeftWingRotY = 14000.0f;
                if (this->unk_28A == 0) {
                    this->targetRightWingRotY = 10000.0f;
                    this->targetLeftWingRotY = 10000.0f;
                }
                break;
        }
    }

    if (this->targetHeadRotZ != this->headRotZ) {
        Math_ApproachF(&this->headRotZ, this->targetHeadRotZ, 0.5f, 4000.0f);
    }

    if (this->targetBodyRotY != this->upperBodyRotY) {
        Math_ApproachF(&this->upperBodyRotY, this->targetBodyRotY, 0.5f, 4000.0f);
    }

    if (this->targetLeftWingRotZ != this->leftWingRotZ) {
        Math_ApproachF(&this->leftWingRotZ, this->targetLeftWingRotZ, 0.8f, 7000.0f);
    }

    if (this->targetLeftWingRotY != this->leftWingRotY) {
        Math_ApproachF(&this->leftWingRotY, this->targetLeftWingRotY, 0.8f, 7000.0f);
    }

    if (this->targetLeftWingRotX != this->leftWingRotX) {
        Math_ApproachF(&this->leftWingRotX, this->targetLeftWingRotX, 0.8f, 7000.0f);
    }

    if (this->targetRightWingRotZ != this->rightWingRotZ) {
        Math_ApproachF(&this->rightWingRotZ, this->targetRightWingRotZ, 0.8f, 7000.0f);
    }

    if (this->targetRightWingRotY != this->rightWingRotY) {
        Math_ApproachF(&this->rightWingRotY, this->targetRightWingRotY, 0.8f, 7000.0f);
    }

    if (this->targetRightWingRotX != this->rightWingRotX) {
        Math_ApproachF(&this->rightWingRotX, this->targetRightWingRotX, 0.8f, 7000.0f);
    }
}

// EnAttackNiw_IsOnScreen
s32 func_809585B0(EnAttackNiw* this, GlobalContext* globalCtx) {
    s16 posX;
    s16 posY;

    Actor_SetFocus(&this->actor, this->unk_2DC);
    Actor_GetScreenPos(globalCtx, &this->actor, &posX, &posY);

    if ((this->actor.projectedPos.z < -20.0f) || (posX < 0) || (posX > SCREEN_WIDTH) || (posY < 0) ||
        (posY > SCREEN_HEIGHT)) {
        return false;
    }
    return true;
}

// first actionfunc for all
void func_80958634(EnAttackNiw* this, GlobalContext* globalCtx) {
    s16 sp4E;
    s16 sp4C;
    Vec3f temp;
    Vec3f sp34;
    s32 pad;

    this->actor.speedXZ = 10.0f;

    temp.x = (this->unk_290.x + globalCtx->view.at.x) - globalCtx->view.eye.x;
    temp.y = (this->unk_290.y + globalCtx->view.at.y) - globalCtx->view.eye.y;
    temp.z = (this->unk_290.z + globalCtx->view.at.z) - globalCtx->view.eye.z;

    sp34.x = globalCtx->view.at.x + temp.x;
    sp34.y = globalCtx->view.at.y + temp.y;
    sp34.z = globalCtx->view.at.z + temp.z;

    this->targetRotY = Math_Vec3f_Yaw(&this->actor.world.pos, &sp34);
    this->targetRotX = Math_Vec3f_Pitch(&this->actor.world.pos, &sp34) * -1.0f;

    Math_SmoothStepToS(&this->actor.world.rot.y, this->targetRotY, 5, this->rotStep, 0);
    Math_SmoothStepToS(&this->actor.world.rot.x, this->targetRotX, 5, this->rotStep, 0);
    Math_ApproachF(&this->rotStep, 5000.0f, 1.0f, 100.0f);

    Actor_SetFocus(&this->actor, this->unk_2DC);
    Actor_GetScreenPos(globalCtx, &this->actor, &sp4E, &sp4C);

    if (this->actor.bgCheckFlags & 8) { // touching a wall
        this->targetRotY = this->actor.yawTowardsPlayer;
        this->targetRotX = this->actor.world.rot.x - 3000.0f;
        this->unk_252 = 0;
        this->unk_254 = 100;
        this->rotStep = 0.0f;
        this->targetLeftWingRotX = 0.0f;
        this->targetRightWingRotX = 0.0f;
        this->unk_250 = this->unk_252;
        this->unk_24E = this->unk_252;
        this->unk_24C = this->unk_252;
        this->actor.gravity = -0.2f;
        this->targetHeadRotZ = 0.0f;
        this->actionFunc = func_80958974;
        this->targetXZSpeed = 5.0f;
    } else if (((this->actor.projectedPos.z > 0.0f) && (fabsf(sp34.x - this->actor.world.pos.x) < 50.0f) &&
                (fabsf(sp34.y - this->actor.world.pos.y) < 50.0f) &&
                (fabsf(sp34.z - this->actor.world.pos.z) < 50.0f)) ||
               (this->actor.bgCheckFlags & 1)) { // touching ground or ... is this on screen again?
        this->unk_252 = 0;
        this->unk_250 = this->unk_252;
        this->unk_24E = this->unk_252;
        this->unk_24C = this->unk_252;
        this->rotStep = 0.0f;
        this->targetRightWingRotX = 0.0f;
        this->targetLeftWingRotX = 0.0f;
        this->targetRotY = this->actor.yawTowardsPlayer;
        this->targetRotX = this->actor.world.rot.x - 2000.0f;
        this->actor.gravity = -0.2f;
        this->targetHeadRotZ = 0.0f;
        this->actionFunc = func_80958974;
        this->targetXZSpeed = 5.0f;
    } else {
        this->unk_24C = 10;
        this->targetBodyRotY = -10000.0f;
        this->targetHeadRotZ = -3000.0f;
        func_80958228(this, globalCtx, 2);
    }
}

void func_80958974(EnAttackNiw* this, GlobalContext* globalCtx) {
    if (!func_809585B0(this, globalCtx)) {
        Actor_MarkForDeath(&this->actor);
        return;
    }

    if (this->actor.bgCheckFlags & 1) { // touching floor 
        if (this->unk_252 == 0) {
            this->unk_252 = 3;
            this->actor.velocity.y = 3.5f;
        }

        if (this->actor.gravity != -2.0f) {
            this->targetRotY = this->actor.yawTowardsPlayer;
            this->unk_25A = 50;
            this->unk_254 = 100;
            this->targetRightWingRotY = 14000.0f;
            this->targetLeftWingRotY = 14000.0f;
            this->targetRightWingRotX = 0.0f;
            this->targetLeftWingRotX = 0.0f;
            this->targetRightWingRotZ = 0.0f;
            this->targetLeftWingRotZ = 0.0f;
            this->targetRotX = 0.0f;
            this->actor.gravity = -2.0f;
        }
    }

    if (this->unk_254 == 50) {
        this->targetRotY = randPlusMinusPoint5Scaled(200.0f) + this->actor.yawTowardsPlayer;
    }

    Math_SmoothStepToS(&this->actor.world.rot.y, this->targetRotY, 2, this->rotStep, 0);
    Math_SmoothStepToS(&this->actor.world.rot.x, this->targetRotX, 2, this->rotStep, 0);
    Math_ApproachF(&this->rotStep, 10000.0f, 1.0f, 1000.0f);
    Math_ApproachF(&this->actor.speedXZ, this->targetXZSpeed, 0.9f, 1.0f);

    if ((this->actor.gravity == -2.0f) && (this->unk_25A == 0) &&
        ((this->actor.bgCheckFlags & 8) || (this->unk_254 == 0))) {
        this->targetXZSpeed = 0.0f;
        this->actor.gravity = 0.0f;
        this->rotStep = 0.0f;
        this->targetRotX = this->actor.world.rot.x - 5000.0f;
        this->actionFunc = func_80958BE4;
    } else if (this->actor.bgCheckFlags & 1) {
        func_80958228(this, globalCtx, 5);
    } else {
        func_80958228(this, globalCtx, 2);
    }
}

void func_80958BE4(EnAttackNiw* this, GlobalContext* globalCtx) {
    if (!func_809585B0(this, globalCtx)) {
        Actor_MarkForDeath(&this->actor);
        return;
    }

    Math_SmoothStepToS(&this->actor.world.rot.x, this->targetRotX, 5, this->rotStep, 0);
    Math_ApproachF(&this->rotStep, 5000.0f, 1.0f, 100.0f);
    Math_ApproachF(&this->actor.velocity.y, 5.0f, 0.3f, 1.0f);
    func_80958228(this, globalCtx, 2);
}

void EnAttackNiw_Update(Actor* thisx, GlobalContext* globalCtx) {
    EnAttackNiw* this = THIS;
    s32 pad;
    EnNiw* parent;
    Player* player = GET_PLAYER(globalCtx);
    s32 pad2;
    Vec3f sp30;

    this->unk_284++;

    DECR (this->unk_24C);
    DECR (this->unk_250);
    DECR (this->unk_252);
    DECR (this->cryTimer);
    DECR (this->flutterTimer);
    DECR (this->unk_254);
    DECR (this->unk_25A);

    this->actor.shape.rot = this->actor.world.rot;
    this->actor.shape.shadowScale = 15.0f;

    this->actionFunc(this, globalCtx);

    Actor_UpdateBgCheckInfo(globalCtx, &this->actor, 20.0f, 20.0f, 60.0f, 0x1D);

    if (this->actionFunc == func_80958634) {
        Actor_MoveWithoutGravity(&this->actor);
    } else {
        Actor_MoveWithGravity(&this->actor);
    }

    if (this->actor.floorHeight <= BGCHECK_Y_MIN) { // under the world
        Actor_MarkForDeath(&this->actor);
    } else if ((this->actor.bgCheckFlags & 0x20) && // on or below water
 (this->actionFunc != func_80958BE4)) {
        Math_Vec3f_Copy(&sp30, &this->actor.world.pos);
        sp30.y += this->actor.depthInWater;

        EffectSsGSplash_Spawn(globalCtx, &sp30, NULL, NULL, 0, 400);
        this->rotStep = 0.0f;
        this->actor.gravity = 0.0f;
        this->targetXZSpeed = 0.0f;
        this->targetRotX = this->actor.world.rot.x - 5000.0f;
        this->actionFunc = func_80958BE4;
    } else {
        f32 temp = 20.0f;

    label:

        if (this->actor.xyzDistToPlayerSq < SQ(temp)) {
            parent = (EnNiw*)this->actor.parent;
            if ((this->actor.parent->update != NULL) && (this->actor.parent != NULL) && (parent != NULL) &&
                (parent->unusedTimer25E == 0) && (player->invincibilityTimer == 0)) {
                func_800B8D50(globalCtx, &this->actor, 2.0f, this->actor.world.rot.y, 0.0f, 0x10);
                parent->unusedTimer25E = 70; // need to know what hti func does before we can name this temp
            }
        }

        if (this->cryTimer == 0) {
            this->cryTimer = 30;
            Actor_PlaySfxAtPos(&this->actor, NA_SE_EV_CHICKEN_CRY_A);
        }

        if (this->flutterTimer == 0) {
            this->flutterTimer = 7;
            Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_CHICKEN_FLUTTER);
        }
    }
}

s32 EnAttackNiw_OverrideLimbDraw(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot,
                                 Actor* thisx) {
    EnAttackNiw* this = THIS;

    if (limbIndex == NIW_LIMB_UPPER_BODY) {
        rot->y += (s16)this->upperBodyRotY;
    }

    if (limbIndex == NIW_LIMB_HEAD) {
        rot->z += (s16)this->headRotZ;
    }

    if (limbIndex == NIW_LIMB_RIGHT_WING_ROOT) {
        rot->x += (s16)this->rightWingRotX;
        rot->y += (s16)this->rightWingRotY;
        rot->z += (s16)this->rightWingRotZ;
    }

    if (limbIndex == NIW_LIMB_LEFT_WING_ROOT) {
        rot->x += (s16)this->leftWingRotX;
        rot->y += (s16)this->leftWingRotY;
        rot->z += (s16)this->leftWingRotZ;
    }
    return false;
}

void EnAttackNiw_Draw(Actor* thisx, GlobalContext* globalCtx) {
    EnAttackNiw* this = THIS;

    func_8012C28C(globalCtx->state.gfxCtx);
    SkelAnime_DrawFlexOpa(globalCtx, this->skelAnime.skeleton, this->skelAnime.jointTable, this->skelAnime.dListCount,
                          EnAttackNiw_OverrideLimbDraw, NULL, &this->actor);
}
