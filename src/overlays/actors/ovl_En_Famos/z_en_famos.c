#include "z_en_famos.h"

#define FLAGS 0x00000005

#define THIS ((EnFamos*)thisx)

//void EnFamos_Init(Actor* thisx, GlobalContext* globalCtx);
void EnFamos_Init(EnFamos* this, GlobalContext* globalCtx);

void EnFamos_Destroy(Actor* thisx, GlobalContext* globalCtx);
//void EnFamos_Update(Actor* thisx, GlobalContext* globalCtx);
void EnFamos_Draw(Actor* thisx, GlobalContext* globalCtx);
//void EnFamos_Destroy(EnFamos* this, GlobalContext* globalCtx);
void EnFamos_Update(EnFamos* this, GlobalContext* globalCtx);
//void EnFamos_Draw(EnFamos* this, GlobalContext* globalCtx);

void func_808ACB58(EnFamos *this);
void func_808ACD2C(EnFamos *this);
void func_808AD05C(EnFamos* this);
void func_808AD170(EnFamos* this);
void func_808AD1F0(EnFamos* this);
void func_808AD31C(EnFamos* this);
void func_808AD3E8(EnFamos* this);
void func_808AD54C(EnFamos* this);
void func_808AD66C(EnFamos* this);
void func_808AD7EC(EnFamos* this);
void func_808AD888(EnFamos* this);
void func_808ADA74(EnFamos* this);
void func_808ADB4C(EnFamos* this);
void func_808ADC40(EnFamos* this);
void func_808ADD20(EnFamos* this);
void func_808ADE00(EnFamos* this);
void func_808ADFA4(EnFamos* this);

// action funcs
void func_808ADFF0(EnFamos* this, GlobalContext* globalCtx);
void func_808AD18C(EnFamos* this, GlobalContext* globalCtx);
void func_808AD294(EnFamos* this, GlobalContext* globalCtx);
void func_808AD378(EnFamos* this, GlobalContext* globalCtx);
void func_808AD42C(EnFamos* this, GlobalContext* globalCtx);
void func_808AD5B0(EnFamos* this, GlobalContext* globalCtx);
void func_808AD68C(EnFamos* this, GlobalContext* globalCtx);
void func_808AD840(EnFamos* this, GlobalContext* globalCtx);
void func_808AD8B8(EnFamos* this, GlobalContext* globalCtx);
void func_808ADAE8(EnFamos* this, GlobalContext* globalCtx);
void func_808ADB70(EnFamos* this, GlobalContext* globalCtx);
void func_808ADC64(EnFamos* this, GlobalContext* globalCtx);
void func_808ADDA8(EnFamos* this, GlobalContext* globalCtx);
void func_808ADE74(EnFamos* this, GlobalContext* globalCtx);
void func_808ADFF0(EnFamos* this, GlobalContext* globalCtx);

void func_808AE304(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, Actor* actor);
void func_808AE3A8(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3s* rot, Actor* actor);
// draw func extension
void func_808AE3FC(EnFamos* this, GlobalContext* globalCtx);

const ActorInit En_Famos_InitVars = {
    ACTOR_EN_FAMOS,
    ACTORCAT_ENEMY,
    FLAGS,
    OBJECT_FAMOS,
    sizeof(EnFamos),
    (ActorFunc)EnFamos_Init,
    (ActorFunc)EnFamos_Destroy,
    (ActorFunc)EnFamos_Update,
    (ActorFunc)EnFamos_Draw
};

static ColliderCylinderInit D_808AE600 = {
    { COLTYPE_METAL, AT_NONE | AT_TYPE_ENEMY, AC_ON | AC_HARD | AC_TYPE_PLAYER, OC1_ON | OC1_TYPE_ALL, OC2_TYPE_1, COLSHAPE_CYLINDER, },
    { ELEMTYPE_UNK2, { 0x20000000, 0x04, 0x10 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_ON, },
    { 20, 80, 0, { 0, 0, 0 } },
};

static ColliderCylinderInit D_808AE62C = {
    { COLTYPE_NONE, AT_NONE | AT_TYPE_ENEMY, AC_NONE, OC1_NONE, OC2_TYPE_1, COLSHAPE_CYLINDER, },
    { ELEMTYPE_UNK0, { 0xF7CFFFFF, 0x04, 0x08 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_NORMAL, BUMP_NONE, OCELEM_NONE, },
    { 70, 10, 0, { 0, 0, 0 } },
};

//UNK_TYPE D_808AE658
static ColliderJntSphElementInit sJntSphElementsInit[2] = {
    {
        { ELEMTYPE_UNK0, { 0x00000000, 0x00, 0x00 }, { 0x00002000, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_NONE, },
        { 2, { { 2500, 0, 0 }, 20 }, 100 },
    },
    {
        { ELEMTYPE_UNK0, { 0x00000000, 0x00, 0x00 }, { 0x00002000, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_NONE, },
        { 2, { { -1500, 0, 0 }, 20 }, 100 },
    },
};

//UNK_TYPE D_808AE6A0
static ColliderJntSphInit D_808AE6A0 = { // sJntSphInit 
    { COLTYPE_NONE, AT_NONE, AC_ON | AC_TYPE_PLAYER, OC1_NONE, OC2_TYPE_1, COLSHAPE_JNTSPH, },
    2, sJntSphElementsInit,
};

extern AnimatedMaterial D_06003E30;
extern AnimatedMaterial D_06003E38;

AnimatedMaterial* D_808AE6B0[] = { &D_06003E30, &D_06003E38, };

//UNK_TYPE D_808AE6B8[] = 0x891F000F, 0x30540DAC, };
static InitChainEntry sInitChain[] = {
    ICHAIN_S8(hintId, 15, ICHAIN_CONTINUE),
    ICHAIN_F32(targetArrowOffset, 3500, ICHAIN_STOP),
};

//unk state
UNK_TYPE D_808AE6C0 = 0x00000000;
//0x00000000,
//0x00000000,
//0x00000000,

extern FlexSkeletonHeader D_06003D38;
extern LinkAnimationHeader D_06003DC8;

/*
void EnFamos_Init(Actor *thisx, GlobalContext *globalCtx) {
    EnFamos* this = (EnFamos*) thisx;
    u8 pCount;
    Path* path;
    void *temp_s0_2;
    f32 phi_f6;

    Actor_ProcessInitChain((Actor *) this, &sInitChain);
    if (this->actor.params != 0xFF) {
        path = &globalCtx->setupPathList[this->actor.params];
        this->pathPoints = Lib_SegmentedToVirtual(path->points);
        //pCount = path->count;
        //this->unk1D6 = pCount;
        this->unk1D6 = path->count;
        if ((this->unk1D6 & 0xFF) == 1) {
            this->pathPoints = NULL;
            this->unk1D6 = 0;
        }
    }
    ActorShape_Init(&this->actor.shape, 0.0f, func_800B4024, 30.0f);
    //SkelAnime_Init(globalCtx, &this->skelAnime, (void *) 0x6003D38, (void *) 0x6003DC8,
    SkelAnime_Init(globalCtx, &this->skelAnime, &D_06003D38, &D_06003DC8,
         this->limbDrawTbl, this->transitionDrawTbl, 6);
    Collider_InitAndSetCylinder(globalCtx, &this->collider1, &this->actor, &D_808AE600);
    Collider_InitAndSetCylinder(globalCtx, &this->collider2, &this->actor, &D_808AE62C);
    Collider_InitAndSetJntSph(globalCtx, &this->collider3, &this->actor, &D_808AE6A0, &this->collider3Elements);
    // this section is broken:
    if (D_808AE6C0 == 0) {
        //phi_s0 = &D_808AE6B0;
        //for ( temp_s0_2 = &D_808AE6B0; temp_s0_2 != &sInitChain; temp_s0_2 += 4) {//loop_5:
          //temp_s0_2 = phi_s0 + 4;
          //temp_s0_2->points = Lib_SegmentedToVirtual(*phi_s0);
          //phi_s0->points = Lib_SegmentedToVirtual(*phi_s0);
          //phi_s0 = temp_s0_2;
          //if (temp_s0_2 != &D_808AE6B8) {
              //goto loop_5;
          //}
        //}
        D_808AE6C0 += 1;
    }
    this->actor.colChkInfo.mass = 0xFA;
    this->unk1EC = this->actor.world.pos.y;
    if ((s32) this->actor.shape.rot.x <= 0) {
        phi_f6 = 200.0f;
    } else {
        phi_f6 = (f32) this->actor.shape.rot.x * 40.0f * 0.1f;
    }
    this->unk1F0 = phi_f6;
    this->actor.shape.rot.x = 0;
    this->actor.world.rot.x = 0;
    this->unk1D5 = (u8)1;
    this->unk1D8 = 1;
    if (this->pathPoints != NULL) {
        func_808AD1F0(this);
    } else {
        func_808AD170(this);
    }
}// */
#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Famos_0x808AC920/EnFamos_Init.asm")

void EnFamos_Destroy(Actor *thisx, GlobalContext *globalCtx) {
    EnFamos* this = (EnFamos*) thisx;
    Collider_DestroyCylinder(globalCtx, &this->collider1);
    Collider_DestroyCylinder(globalCtx, &this->collider2);
    Collider_DestroyJntSph(globalCtx, &this->collider3);
}

#if NON_MATCHING
// non-matching: instructions out of order and regalloc, but pretty sure it equivelent
void func_808ACB58(EnFamos *this) {
    f32 cosSResult;
    f32 randFloat;
    s16 randOffset;
    s16 randNextResult;
    EnFamosParticle *phi_s0;
    s32 i;

    this->unk1DE = 0x28;
    phi_s0 = this->particles;

    for (i = 0; i < 0x14; ++i) { //loop_1:
        randNextResult = (Rand_Next() >> 0x10);
        randOffset = Rand_S16Offset(0x1800, 0x2800);
        randFloat = Rand_ZeroFloat(5.0f) + 5.0f;
        cosSResult = Math_CosS(randOffset);
        phi_s0->unkC.x = (f32) (Math_SinS(randNextResult) * (randFloat * cosSResult));
        if (1) { }  if (1) { }  if (1) { }  if (1) { }  if (1) { } 
        phi_s0->unkC.y = (f32) ((Math_SinS(randOffset) * randFloat) + 3.0f);
        //temp_f20_2 = Math_CosS(randOffset);
        //phi_s0->unkC.z = (f32) (Math_CosS(randNextResult) * (randFloat * temp_f20_2));
        phi_s0->unkC.z = (f32) (Math_CosS(randNextResult) * (randFloat * Math_CosS(randOffset)));
        phi_s0->unk18.x = (s16) (Rand_Next() >> 0x10);
        phi_s0->unk18.y = (s16) (Rand_Next() >> 0x10);
        phi_s0->unk18.z = (s16) (Rand_Next() >> 0x10);
        phi_s0->unk0.x = (f32) ((Math_SinS(randNextResult) * 20.0f) + this->actor.world.pos.x);
        phi_s0->unk0.y = (f32) this->actor.floorHeight;
        phi_s0->unk0.z = (f32) ((Math_CosS(randNextResult) * 20.0f) + this->actor.world.pos.z);
        phi_s0->unk20 = (f32) (Rand_ZeroFloat(0.0015f) + 0.002f);
        phi_s0++;
    }

}
#else
#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Famos_0x808AC920/func_808ACB58.asm")
#endif

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Famos_0x808AC920/func_808ACD2C.asm")

// check agro conditions? true false return
s32 func_808ACF1C(EnFamos *this, GlobalContext *globalCtx) {
    if ((func_8012403C(globalCtx) != 0x10) 
        && (Actor_XZDistanceToPoint(&PLAYER->base, &this->unk200) < this->unk1F0) 
        && (Actor_IsActorFacingLink(&this->actor, 0x5000) != 0)) {
        return 1;
    }
    return 0;
}

void func_808ACF98(EnFamos *this) {
    s32 tempUnk1E6;

    if (this->unk1DA == 0) {
        this->unk1DA = 30;
    }
    this->unk1DA--;
    this->actor.world.pos.y = (Math_SinS((this->unk1DA * 2184)) * 10.0f) + this->unk1EC;

    tempUnk1E6 = this->unk1E6 < 0 ? -this->unk1E6 : this->unk1E6;
    if (tempUnk1E6 >= 0x4001) {
        func_800B9010(&this->actor, 0x3294); // NA_SE_EN_FAMOS_FLOAT_REVERSE
    } else { 
        func_800B9010(&this->actor, 0x3293); // NA_SE_EN_FAMOS_FLOAT
    }
}

// check collision 
void func_808AD05C(EnFamos* this) {
    u8 scalled1E6;

    if ((this->collider3.base.acFlags & AC_HIT)) {
        this->collider3.base.acFlags &= ~AC_HIT;
        if (this->unk1D5 == 1) {
            if (this->unk1D4 != 0) {
                this->unk1D4 = 0;
                Audio_PlayActorSound2(this, 0x3A92);
            } else {
                this->unk1D4 = 1;
                this->unk1E0 = 100;
                Audio_PlayActorSound2(this, 0x3A91);
                Audio_PlayActorSound2(this, 0x3847);
            }
            this->unk1D5 = 0;
        }
    } else { // not hit
        if (this->unk1E0 > 0) {
            this->unk1E0--;
            if (this->unk1E0 == 0) {
                if (this->unk1D4 != 0) {
                    Audio_PlayActorSound2(this, 0x3A92);
                }
                this->unk1D4 = 0;
                this->unk1D5 = 0;
            }
        }
    }
    if (this->unk1D5 == 0) {
        if (this->unk1D4 != 0) {
            scalled1E6 = (u8) Math_ScaledStepToS(&this->unk1E6, -0x8000, 0x1000);
        } else {
            scalled1E6 = (u8) Math_ScaledStepToS(&this->unk1E6, 0, 0x1000);
        }
        this->unk1D5 = scalled1E6;
    }
}

void func_808AD170(EnFamos *this) {
    this->actionFunc = func_808AD18C;
    this->actor.speedXZ = 0.0f;
}

void func_808AD18C(EnFamos *this, GlobalContext *globalCtx) {
    func_808ACF98(this);
    if (this->unk1D8 != 0) {
        Math_Vec3f_Copy(&this->unk200, &this->actor.world.pos);
    }
    if (func_808ACF1C(this, globalCtx)) {
        func_808AD54C(this);
    }
}

void func_808AD1F0(EnFamos *this) {
    if (this->unk1D8 != 0) {
        if ( ++this->unk1D7 == this->unk1D6) {
            this->unk1D7 = 0;
        }
    } else {
        this->unk1D8 = 1;
    }
    Math_Vec3s_ToVec3f(&this->unk1F4, &this->pathPoints[this->unk1D7]);
    this->unk1E4 = Actor_YawToPoint(&this->actor, &this->unk1F4);
    this->actionFunc = func_808AD294;
    this->actor.speedXZ = 0.0f;
}

void func_808AD294(EnFamos *this, GlobalContext *globalCtx) {
    func_808ACF98(this);
    if (this->unk1D8 != 0) {
        Math_Vec3f_Copy(&this->unk200, &this->actor.world.pos);
    }
    if (func_808ACF1C(this, globalCtx)) {
        func_808AD54C(this);
        return;
    }
    if (Math_ScaledStepToS(&this->actor.shape.rot.y, this->unk1E4, 0x200) != 0) {
        func_808AD3E8(this);
    }
}

void func_808AD31C(EnFamos *this) {
    this->unk1E4 = Actor_YawToPoint(&this->actor, &this->unk200);
    Math_Vec3f_Copy(&this->unk1F4, &this->unk200);
    this->actionFunc = func_808AD378;
    this->actor.speedXZ = 0.0f;
}

void func_808AD378(EnFamos *this, GlobalContext *globalCtx) {
    func_808ACF98(this);
    if (func_808ACF1C(this, globalCtx)) {
        func_808AD54C(this);
    } else if (Math_ScaledStepToS(&this->actor.shape.rot.y, this->unk1E4, 0x200) != 0) {
        func_808AD3E8(this);
    }
}

void func_808AD3E8(EnFamos *this) {
    this->actor.world.rot.y = this->actor.shape.rot.y;
    this->actor.world.rot.x = -Actor_PitchToPoint(&this->actor, &this->unk1F4);
    this->actionFunc = func_808AD42C;
}

void func_808AD42C(EnFamos *this, GlobalContext *globalCtx) {
    f32 sp24 = Actor_XZDistanceToPoint((Actor *) this, &this->unk1F4);

    this->actor.shape.rot.y = Actor_YawToPoint((Actor *) this, &this->unk1F4);
    this->actor.world.rot.y = this->actor.shape.rot.y;
    func_808ACF98(this);
    if (this->unk1D8 != 0) {
        Math_Vec3f_Copy(&this->unk200, &this->actor.world.pos);
    }
    if (func_808ACF1C(this, globalCtx)) {
        func_808AD54C(this);
    } else if (sp24 < 20.0f) {
        if (this->pathPoints != 0) {
            func_808AD1F0(this);
        } else {
            func_808AD170(this);
        }
    } else if (sp24 < 40.0f) {
        Math_StepToF(&this->actor.speedXZ, 0.5f, 0.3f);
    } else {
        Math_StepToF(&this->actor.speedXZ, 3.0f, 0.3f);
    }
}

void func_808AD54C(EnFamos *this) {
    this->actor.world.rot.y = this->actor.shape.rot.y;
    this->unk1DC = 8;
    this->actor.speedXZ = 0.0f;
    if (this->unk1D8 == 1) {
        this->unk1D8 = 0;
        Math_Vec3f_Copy(&this->unk200, &this->actor.world.pos);
    }
    this->actionFunc = func_808AD5B0;
}

void func_808AD5B0(EnFamos *this, GlobalContext *globalCtx) {
    s32 v0;
    s32 temp1DC;

    v0 = this->unk1E6 < 0 ? -this->unk1E6 : this->unk1E6;
    if (v0 >= 0x4001) {
        func_800B9010((Actor *) this, 0x3294);
    } else {
        func_800B9010((Actor *) this, 0x3293);
    }

    this->unk1DC--;
    if (this->unk1DC == 0) {
        this->actor.world.pos.y = this->unk1EC;
        func_808AD66C(this);
    } else {
        this->actor.world.pos.y = (Math_SinS( (this->unk1DC) * 0x1000) * 30.0f) + this->unk1EC;
    }
}

void func_808AD66C(EnFamos *this) {
    this->unk1DA = 0;
    this->actor.world.rot.y = this->actor.shape.rot.y;
    this->actionFunc = func_808AD68C;
}

void func_808AD68C(EnFamos *this, GlobalContext *globalCtx) {
    ActorPlayer *player;
    Vec3f abovePlayerPos;
    u32 floorValue; // name is a guess

    player = PLAYER;
    func_808ACF98(this);
    Math_ScaledStepToS(&this->actor.shape.rot.y, this->actor.yawTowardsPlayer, (u16)0x800);
    this->actor.world.rot.y = this->actor.shape.rot.y;
    abovePlayerPos.x = player->base.world.pos.x;
    abovePlayerPos.y = player->base.world.pos.y + 100.0f;
    abovePlayerPos.z = player->base.world.pos.z;
    this->actor.world.rot.x = (s16) -Actor_PitchToPoint((Actor *) this, &abovePlayerPos);
    Math_StepToF(&this->actor.speedXZ, 6.0f, 0.5f);

    floorValue = func_800C9B18(&globalCtx->colCtx, this->actor.floorPoly, this->actor.floorBgId);
    if ((this->actor.xzDistToPlayer < 30.0f) && (this->actor.floorHeight > -32000.0f) 
      && (floorValue != 0xC) && (floorValue != 0xD)) {
        func_808AD7EC(this);

    } else if ((func_8012403C(globalCtx) == 0x10) 
      || (this->unk1F0 < Actor_XZDistanceToPoint(&PLAYER->base, &this->unk200))
      || (Actor_IsActorFacingLink((Actor *) this, (u16)0x6000) == 0)) {
        func_808ADC40(this);
    }
}

void func_808AD7EC(EnFamos *this) {
    SkelAnime_ChangeAnimDefaultStop(&this->skelAnime, D_060000F8);
    this->actor.speedXZ = 0.0f;
    Audio_PlayActorSound2(this, 0x3848); // NA_SE_EN_AMOS_VOICE
    this->actionFunc = func_808AD840;
}

void func_808AD840(EnFamos *this, GlobalContext *globalCtx) {
    func_800B9010((Actor *) this, 0x31D7); // NA_SE_EN_LAST1_FALL_OLD
    if (SkelAnime_FrameUpdateMatrix(&this->skelAnime)) {
        func_808AD888(this);
    }
}

void func_808AD888(EnFamos *this) {
    this->actor.world.rot.x = -0x4000;
    this->collider1.base.atFlags |= 1; // can hit?
    this->unk1DC = 4;
    this->actionFunc = func_808AD8B8;
}

void func_808AD8B8(EnFamos *this, GlobalContext *globalCtx) {
    s32 bgflags; // temp name, should be more psecific
    u32 floorValue; // name is a guess

    Math_StepToF(&this->actor.speedXZ, 20.0f, 2.0f);
    this->unk1DC--;
    if (this->unk1DC == 0) {
        this->collider3.base.acFlags = this->collider3.base.acFlags & 0xFFFE;
    }
    floorValue = func_800C9B18(&globalCtx->colCtx, (CollisionPoly *) this->actor.floorPoly, (s32) this->actor.floorBgId);
    bgflags = this->actor.bgCheckFlags & 1;
    if (( bgflags != 0) 
      || (this->actor.floorHeight == -32000.0f)
      || (floorValue == 0xC)
      || (floorValue == 0xD)) {
        this->collider1.base.atFlags = this->collider1.base.atFlags & 0xFFFE;
        this->collider2.base.atFlags |= 1;
        if ( bgflags != 0) {
            func_800DFD04(globalCtx->cameraPtrs[globalCtx->activeCamera], 2, 0xF, 0xA);
            func_8013ECE0(this->actor.xyzDistToPlayerSq, 0xB4, 0x14, 0x64);
            func_808ACB58(this);
            Actor_SpawnWithParent(&globalCtx->actorCtx, (Actor *) this, globalCtx, 
                (u16)1, this->actor.world.pos.x, this->actor.floorHeight, this->actor.world.pos.z, 0, 0, 0, 0);

            if (this->actor.child != NULL) {
                Actor_SetScale(this->actor.child, 0.015f);
            }

            if (this->unk1D4 != 0) {
                this->unk1E2 = 0x46;
                func_808ADD20(this);
                return;
            } else {
                this->unk1E2 = 0x14;
                func_808ADA74(this);
                return;
            }
        }
        else {
            this->collider3.base.acFlags = this->collider3.base.acFlags | 1;
            func_808ADB4C(this);
            return;

        }
    }

    func_800B9010((Actor *) this, 0x31D7); // NA_SE_EN_LAST1_FALL_OLD
}

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Famos_0x808AC920/func_808ADA74.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Famos_0x808AC920/func_808ADAE8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Famos_0x808AC920/func_808ADB4C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Famos_0x808AC920/func_808ADB70.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Famos_0x808AC920/func_808ADC40.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Famos_0x808AC920/func_808ADC64.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Famos_0x808AC920/func_808ADD20.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Famos_0x808AC920/func_808ADDA8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Famos_0x808AC920/func_808ADE00.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Famos_0x808AC920/func_808ADE74.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Famos_0x808AC920/func_808ADFA4.asm")

//actionfunc
#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Famos_0x808AC920/func_808ADFF0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Famos_0x808AC920/func_808AE030.asm")

/*
void EnFamos_Update(EnFamos *this, GlobalContext *globalCtx) {
    f32 sp34;
    s32 sp30;
    CollisionCheckContext *sp2C;
    ColliderCylinder *sp28;
    ColliderCylinder *temp_a1;
    ColliderCylinder *temp_a2;
    CollisionCheckContext *temp_a1_2;
    s16 temp_v0_2;

    if ((this->unk1DE <= 0) || (this->unk1DE = this->unk1DE - 1, func_808AE030(this), (&func_808ADFF0 != this->actionFunc))) {
        sp30 = (s32) this->unk1DA;
        func_808AD05C(this);
        temp_v0_2 = this->unk1E2;
        if ((s32) temp_v0_2 > 0) {
            this->unk1E2 = temp_v0_2 - 1;
            if (this->unk1E2 == 0) {
                this->actor.child->parent = NULL;
            }
        }
        this->actionFunc(this, globalCtx);
        sp34 = this->actor.world.pos.y;
        Actor_SetVelocityAndMoveXYRotation((Actor *) this);
        if (sp30 != this->unk1DA) {
            this->unk1EC = this->unk1EC + (this->actor.world.pos.y - sp34);
        }
        if ((s32) this->unk1E0 >= 0) {
            func_800B78B8(globalCtx, (Actor *) this, 35.0f, 30.0f, 80.0f, 0x1F);
            if ((&func_808AD8B8 == this->actionFunc) && ((u8) this->unk1D4 != 0) && ((this->actor.bgCheckFlags & 1) != 0)) {
                this->actor.world.pos.y = this->actor.world.pos.y - 60.0f;
            }
        }
        temp_a1 = &this->collider1;
        this->actor.focus.rot.y = this->actor.shape.rot.y;
        sp28 = temp_a1;
        Collider_UpdateCylinder((Actor *) this, temp_a1);
        if ((this->collider1.base.atFlags & 1) != 0) {
            CollisionCheck_SetAT(globalCtx, &globalCtx->colCheckCtx, (Collider *) sp28);
        }
        temp_a1_2 = &globalCtx->colCheckCtx;
        sp2C = temp_a1_2;
        CollisionCheck_SetAC(globalCtx, temp_a1_2, (Collider *) sp28);
        CollisionCheck_SetOC(globalCtx, temp_a1_2, (Collider *) sp28);
        if ((this->collider3.base.acFlags & 1) != 0) {
            CollisionCheck_SetAC(globalCtx, temp_a1_2, (Collider *) &this->collider3);
        }
        temp_a2 = &this->collider2;
        if ((this->collider2.base.atFlags & 1) != 0) {
            sp28 = temp_a2;
            Collider_UpdateCylinder((Actor *) this, temp_a2);
            this->collider2.dim.pos.y = (s16) (s32) this->actor.floorHeight;
            CollisionCheck_SetAT(globalCtx, sp2C, (Collider *) temp_a2);
        }
    }
}// */
#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Famos_0x808AC920/EnFamos_Update.asm")

// limbdraw
#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Famos_0x808AC920/func_808AE304.asm")

// override limbdraw
#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Famos_0x808AC920/func_808AE3A8.asm")

// draw something else
#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Famos_0x808AC920/func_808AE3FC.asm")

void EnFamos_Draw(Actor *actorx, GlobalContext *globalCtx) {
    EnFamos* this = (EnFamos*) actorx;

    func_8012C28C(globalCtx->state.gfxCtx);
    if (this->actionFunc != func_808ADFF0) {
        AnimatedMat_Draw(globalCtx, D_808AE6B0[this->unk1D4]);
        SkelAnime_Draw(globalCtx, this->skelAnime.skeleton, this->skelAnime.limbDrawTbl, 
            func_808AE304, func_808AE3A8, &this->actor);
        if (this->actor.colorFilterTimer != 0) {
            func_800AE5A0(globalCtx); // effect function?
        }
    }
    func_808AE3FC(this, globalCtx);
}
