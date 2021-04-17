#include "z_en_mm.h"

#define FLAGS 0x00000010

#define THIS ((EnMm*)thisx)

void EnMm_Init(Actor* thisx, GlobalContext* globalCtx);
void EnMm_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnMm_Update(Actor* thisx, GlobalContext* globalCtx);
void EnMm_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_80965DB4(EnMm* this, GlobalContext* globalCtx);
void func_80965D3C(EnMm* this, GlobalContext* globalCtx);
void func_8096611C(EnMm* this, GlobalContext* globalCtx);


const ActorInit En_Mm_InitVars = {
    ACTOR_EN_MM,
    ACTORCAT_ITEMACTION,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(EnMm),
    (ActorFunc)EnMm_Init,
    (ActorFunc)EnMm_Destroy,
    (ActorFunc)EnMm_Update,
    (ActorFunc)EnMm_Draw
};

static ColliderCylinderInit sCylinderInit = {
    { COLTYPE_METAL, AT_NONE, AC_NONE, OC1_ON | OC1_TYPE_ALL, OC2_TYPE_2, COLSHAPE_CYLINDER, },
    { ELEMTYPE_UNK2, { 0x00100000, 0x00, 0x00 }, { 0x01000202, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_NONE, OCELEM_ON, },
    { 6, 30, 0, { 0, 0, 0 } },
};

static InitChainEntry sInitChain[] = {
    ICHAIN_F32_DIV1000(gravity, -1200, ICHAIN_CONTINUE),
    ICHAIN_VEC3F_DIV1000(scale, 270, ICHAIN_STOP),
};

// setup actionfunc
void func_80965BB0(EnMm* this, EnMmActionFunc* newActionFunc) {
    this->actionFunc = newActionFunc;
}

void func_80965BBC(EnMm* this) {
    func_80965BB0(this, &func_8096611C); //set actionfunc
    this->actor.room = -1;
    if (this->actor.parent->id == 0) {
        gSaveContext.owl.unk8 = 1;
    }
}

void EnMm_Init(Actor* thisx, GlobalContext* globalCtx) {
    EnMm* this = THIS;
    EnMmActionFunc *actionFunc;

    if ((this->actor.params >= 0) && ((gSaveContext.perm.weekEventReg[0x25] & 0x10) == 0
        || (gSaveContext.perm.weekEventReg[0x25] & 0x08) != 0 || gSaveContext.owl.unk8 != 0)) {
            Actor_MarkForDeath(&this->actor);
            return;
    }

    Actor_ProcessInitChain(&this->actor, &sInitChain);
    //Actor_SetDrawParams(&this->actor.shape, 50.0f, &func_800B3FC0, 1.2f);
    ActorShape_Init(&this->actor.shape, 50.0f, &func_800B3FC0, 1.2f);
    Collider_InitCylinder(globalCtx,  &this->collider);
    Collider_SetCylinder(globalCtx, &this->collider, &this->actor, &sCylinderInit);

    if (this->actor.parent != 0) {
        func_80965BBC(&this->actor);
    } else {
        actionFunc = (this->actor.cutscene >= 0) ? func_80965D3C : func_80965DB4;
        func_80965BB0(&this->actor, actionFunc);
    }
}

void EnMm_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    EnMm* this = THIS;
    Collider_DestroyCylinder(globalCtx, &this->collider);
}

// action func
void func_80965D3C(EnMm* this, GlobalContext* globalCtx) {
    s16 cutscene;

    cutscene = ActorCutscene_GetAdditionalCutscene( this->actor.cutscene);
    if (ActorCutscene_GetCanPlayNext(cutscene) != 0) {
        ActorCutscene_StartAndSetUnkLinkFields(cutscene, &this->actor);
        func_80965BB0(&this->actor, func_80965DB4);
    } else {
        ActorCutscene_SetIntentToPlay(cutscene);
    }
}

#if NON_EQUIVELENT
// action func
// think this is calculating speed/direction of sirloin when breaking pot
// the math at the 0x8000 is wrong, other issues
void func_80965DB4(EnMm* this, GlobalContext* globalCtx) {
    //const static f32 D_80966380[] = { -0.3, 0.0, 0.0, 0.0, };
    
    Vec3f sp50;
    s16 sp4E;
    f32 sinsSpeed;
    f32 cossSpeed;
    f32 sqrtResult;
    s16 dRot;
    s32 dRot32;
    s16 newYRot;
    s32 overflowtemp;

    if (Actor_HasParent(&this->actor, globalCtx) != 0) {
       func_80965BBC(this);
       Audio_PlayActorSound2(&this->actor, 0x086A);
    } else {
        if ((this->actor.velocity.y > 0.0f) && ((this->actor.bgCheckFlags & 0x10) != 0)) {
            this->actor.velocity.y = 0.0f;
        }

        if ((this->actor.speedXZ != 0.0f) && ((this->actor.bgCheckFlags & 8) != 0)) {
            //overflowtemp = 0x8000;
            dRot = this->actor.wallYaw + 0x8000;
            //this->actor.world.rot.y += (s16)(0x8000 - (this->actor.world.rot.y - (this->actor.wallYaw + 0x8000)) * 2);
            this->actor.world.rot.y += (0x8000 - (this->actor.world.rot.y - dRot) * 2);
            //this->actor.world.rot.y += (overflowtemp - (s16)(this->actor.world.rot.y - (this->actor.wallYaw + overflowtemp)) * 2);
            this->actor.speedXZ *= 0.5f;
            CollisionCheck_SpawnShieldParticles(globalCtx,  &this->actor.world);
            Audio_PlayActorSound2(&this->actor, 0x2896);
        }

        if ((this->actor.bgCheckFlags & 1) == 0) {
            Lib_StepTowardsCheck_f(&this->actor.speedXZ, 0.0f, 0.08f);
        } else {
            sinsSpeed = Math_Sins(this->actor.world.rot.y) * this->actor.speedXZ;
            cossSpeed = Math_Coss(this->actor.world.rot.y) * this->actor.speedXZ;
            //sp4E = (s16) sp50.x;
            // sp4E is what we started with, but its a s16? can't be part of the vec3f?
            func_800B75A0(this->actor.floorPoly, &sp50, &sp4E);
            sinsSpeed = sinsSpeed + (3.0f * sp50.x);
            cossSpeed = cossSpeed + (3.0f * sp50.z);
            sqrtResult = sqrtf((sinsSpeed * sinsSpeed) + (cossSpeed* cossSpeed));

            if ((sqrtResult < this->actor.speedXZ) || 
              ((func_800C9C74(&globalCtx->colCtx, (BgPolygon *) this->actor.floorPoly,
              (s32) this->actor.floorBgId) == 1))) {
                if (sqrtResult > 16.0f) {
                    this->actor.speedXZ = 16.0f;
                } else {
                    this->actor.speedXZ = sqrtResult;
                }

                // lots of temps loaded/added here that shouldn't be
                //this->actor.world.rot.y = atans_flip(sinsSpeed, cossSpeed);
                this->actor.world.rot.y = Math_FAtan2F(sinsSpeed, cossSpeed);
            }

            if (Lib_StepTowardsCheck_f(&this->actor.speedXZ, 0.0f, 1.0f) == 0) {
                dRot = this->actor.world.rot.y - this->actor.shape.rot.y;
                if ((s32) dRot < 0) {
                    dRot32 = -(s32) dRot;
                } else {
                    dRot32 = (s32) dRot;
                }

                newYRot = this->actor.world.rot.y;
                dummy_permuter_label_func_80965DB4: ; 
                if (dRot32 >= 0x4001) {
                    newYRot = (newYRot + 0x8000);
                }

                Lib_StepTowardsCheckFramerateScaled_s(&this->actor.shape.rot.y,
                      newYRot, 
                      (s16) (this->actor.speedXZ * 100.0f));
                this->xRot += (s32) (this->actor.speedXZ * 800.0f);
            }

            if ((this->actor.bgCheckFlags & 2) != 0) {
                if (this->actor.velocity.y < -6.0f) {

                    //this->actor.velocity.y *= D_80966380[0];
                    this->actor.velocity.y *= -0.3f;
                    this->actor.bgCheckFlags &= ~0x1;
                }

                Audio_PlayActorSound2(&this->actor, 0x2896);
            } else {
                func_800B8A1C(&this->actor, globalCtx, 0, 50.0f, 30.0f);
            }
        }
        Actor_SetVelocityAndMoveYRotationAndGravity(&this->actor);
    }
    Collider_UpdateCylinder(&this->actor, &this->collider);
    CollisionCheck_SetOC(globalCtx, &globalCtx->colCheckCtx,  &this->collider);
}
#else
#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Mm_0x80965BB0/func_80965DB4.asm")
#endif

// actor func
void func_8096611C(EnMm* this, GlobalContext* globalCtx) {
    if (func_800B8BFC(&this->actor, globalCtx) != 0) {
        func_80965BB0(&this->actor, func_80965DB4); //set actionfunc
        this->actor.room = globalCtx->roomContext.currRoom.num;
        this->actor.bgCheckFlags &= ~0x1;
        Math_Vec3s_ToVec3f(&this->actor.prevPos, &this->actor.home.rot);
        gSaveContext.owl.unk8 = 0;
    } else {
        Math_Vec3f_ToVec3s(&this->actor.home.rot, &this->actor.parent->world);
    }
    Lib_StepTowardsCheckFramerateScaled_s(&this->xRot, 0, 0x7D0);
}

void EnMm_Update(Actor* thisx, GlobalContext* globalCtx) {
    EnMm* this = THIS;

    Collider_ResetCylinderAC(globalCtx, &this->collider );
    this->actionFunc(this, globalCtx);
    func_800B78B8(globalCtx, &this->actor, 20.0f, 10.0f, 20.0f, 0x1F);
    Actor_SetHeight(&this->actor, 20.0f);
}

#if NON-MATCHING
// stack offset
void EnMm_Draw(Actor* thisx, GlobalContext* globalCtx) {
    EnMm* this = THIS;
    s8 pad[4];
    //s8 pad2[1];
    s16 dY; // needs to be at 0x2a(sp)
    //s8 pad3[2];
    
    OPEN_DISPS(globalCtx->state.gfxCtx);

    func_8012C28C(globalCtx->state.gfxCtx);
    if (this->xRot != 0) {
        dY = this->actor.world.rot.y - this->actor.shape.rot.y;
        //SysMatrix_InsertYRotation_s(dY, 1);
        //SysMatrix_InsertXRotation_s(this->xRot, 1);
        //SysMatrix_InsertYRotation_s((s16) -(s32) dY, 1);
        Matrix_RotateY(dY, 1);
        SysMatrix_InsertXRotation_s(this->xRot, 1);
        Matrix_RotateY((s16) -(s32) dY, 1);
    }
    gSPMatrix(POLY_OPA_DISP++,
      Matrix_NewMtx(globalCtx->state.gfxCtx),
      G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

    gSPDisplayList(POLY_OPA_DISP++, &D_04055628);
    CLOSE_DISPS(globalCtx->state.gfxCtx);
}
#else
#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Mm_0x80965BB0/EnMm_Draw.asm")
#endif
