#include "z_en_po_sisters.h"

#define FLAGS 0x00005015

#define THIS ((EnPoSisters*)thisx)

void EnPoSisters_Init(Actor* thisx, GlobalContext* globalCtx);
//void EnPoSisters_Init(EnPoSisters* this, GlobalContext* globalCtx);
void EnPoSisters_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnPoSisters_Update(Actor* thisx, GlobalContext* globalCtx);
//void EnPoSisters_Update(EnPoSisters* this, GlobalContext* globalCtx);
void EnPoSisters_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_80B1AAE8(EnPoSisters* this, GlobalContext* globalCtx);
void func_80B1ABB8(EnPoSisters* this, GlobalContext* globalCtx);
void func_80B1ACB8(EnPoSisters* this, GlobalContext* globalCtx);
void func_80B1AE3C(EnPoSisters* this, GlobalContext* globalCtx);
void func_80B1B020(EnPoSisters* this, GlobalContext* globalCtx);
void func_80B1B168(EnPoSisters* this, GlobalContext* globalCtx);
void func_80B1B2F0(EnPoSisters* this, GlobalContext* globalCtx);
void func_80B1B444(EnPoSisters* this, GlobalContext* globalCtx);
void func_80B1B628(EnPoSisters* this, GlobalContext* globalCtx);
void func_80B1B7BC(EnPoSisters* this, GlobalContext* globalCtx);
void func_80B1B940(EnPoSisters* this, GlobalContext* globalCtx);
void func_80B1BA90(EnPoSisters* this, GlobalContext* globalCtx);
void func_80B1BCA0(EnPoSisters* this, GlobalContext* globalCtx);
void func_80B1BF2C(EnPoSisters* this, GlobalContext* globalCtx);
void func_80B1C0A4(EnPoSisters* this, GlobalContext* globalCtx);
void func_80B1C340(EnPoSisters* this, GlobalContext* globalCtx);

// new
void func_80B1A768(EnPoSisters* this, GlobalContext* globalCtx);
void func_80B1A894(EnPoSisters* this, GlobalContext* globalCtx);
void func_80B1A9B0(EnPoSisters* this, GlobalContext* globalCtx);
void func_80B1AA88(EnPoSisters* this);
void func_80B1AB5C(EnPoSisters* this);
void func_80B1AC40(EnPoSisters* this);
void func_80B1AE28(EnPoSisters* this);
void func_80B1AF8C(EnPoSisters* this);
void func_80B1B0E0(EnPoSisters* this);
void func_80B1B280(EnPoSisters* this);
void func_80B1B3A8(EnPoSisters* this);
void func_80B1B5B4(EnPoSisters* this);
void func_80B1B70C(EnPoSisters* this);
void func_80B1BA3C(EnPoSisters* this);
void func_80B1BC4C(EnPoSisters* this, GlobalContext* globalCtx);
void func_80B1BE4C(EnPoSisters* this, GlobalContext* globalCtx);
void func_80B1C030(EnPoSisters* this);
void func_80B1C2E8(EnPoSisters* this);
// might be s32 return
void func_80B1C974(EnPoSisters* this);
void func_80B1BCF0(EnPoSisters* this, GlobalContext* globalCtx);
void func_80B1B860(EnPoSisters *this, GlobalContext *globalCtx);



const ActorInit En_Po_Sisters_InitVars = {
    ACTOR_EN_PO_SISTERS,
    ACTORCAT_ENEMY,
    FLAGS,
    OBJECT_PO_SISTERS,
    sizeof(EnPoSisters),
    (ActorFunc)EnPoSisters_Init,
    (ActorFunc)EnPoSisters_Destroy,
    (ActorFunc)EnPoSisters_Update,
    (ActorFunc)EnPoSisters_Draw,
};

// static ColliderCylinderInit sCylinderInit = {
static ColliderCylinderInit D_80B1DA70 = {
    { COLTYPE_HIT3, AT_ON | AT_TYPE_ENEMY, AC_ON | AC_TYPE_PLAYER, OC1_ON | OC1_TYPE_ALL, OC2_TYPE_1, COLSHAPE_CYLINDER, },
    { ELEMTYPE_UNK0, { 0xF7CFFFFF, 0x00, 0x08 }, { 0xF7CBFFFE, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_NORMAL, BUMP_ON | BUMP_HOOKABLE, OCELEM_ON, },
    { 18, 60, 15, { 0, 0, 0 } },
};

// sColChkInfoInit
static CollisionCheckInfoInit D_80B1DA9C = { 6, 25, 60, 50 };

// static DamageTable sDamageTable = {
static DamageTable D_80B1DAA4 = {
    /* Deku Nut       */ DMG_ENTRY(0, 0xF),
    /* Deku Stick     */ DMG_ENTRY(1, 0x0),
    /* Horse trample  */ DMG_ENTRY(1, 0x0),
    /* Explosives     */ DMG_ENTRY(1, 0x0),
    /* Zora boomerang */ DMG_ENTRY(1, 0x0),
    /* Normal arrow   */ DMG_ENTRY(1, 0x0),
    /* UNK_DMG_0x06   */ DMG_ENTRY(0, 0x0),
    /* Hookshot       */ DMG_ENTRY(1, 0x0),
    /* Goron punch    */ DMG_ENTRY(1, 0x0),
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
    /* Zora barrier   */ DMG_ENTRY(0, 0x0),
    /* Normal shield  */ DMG_ENTRY(0, 0x0),
    /* Light ray      */ DMG_ENTRY(0, 0x0),
    /* Thrown object  */ DMG_ENTRY(1, 0x0),
    /* Zora punch     */ DMG_ENTRY(1, 0x0),
    /* Spin attack    */ DMG_ENTRY(1, 0xE),
    /* Sword beam     */ DMG_ENTRY(0, 0x0),
    /* Normal Roll    */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1B   */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1C   */ DMG_ENTRY(0, 0x0),
    /* Unblockable    */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1E   */ DMG_ENTRY(0, 0x0),
    /* Powder Keg     */ DMG_ENTRY(1, 0x0),
};

// static InitChainEntry sInitChain[] = {
static InitChainEntry D_80B1DAC4[] = {
    ICHAIN_VEC3F_DIV1000(scale, 7, ICHAIN_CONTINUE),
    ICHAIN_F32(targetArrowOffset, 6000, ICHAIN_STOP),
};

extern AnimationHeader D_06000114;
extern UNK_TYPE D_060008C0;
extern AnimationHeader D_06000A54;
extern AnimationHeader D_06000D40;
extern AnimationHeader D_0600119C;
extern AnimationHeader D_060014CC;
extern UNK_TYPE D_060027B0;
extern UNK_TYPE D_060046E0;

extern SkeletonHeader D_060065C8;

#ifdef NON_MATCHING
// tripple param load what
void EnPoSisters_Init(Actor* thisx, GlobalContext *globalCtx) {
    EnPoSisters *this = THIS;
    u8 sisType;

    Actor_ProcessInitChain((Actor *) this, D_80B1DAC4);
    ActorShape_Init(&this->actor.shape, 0.0f, (void (*)(struct Actor *actor, struct Lights *mapper, GlobalContext *globalCtx)) func_800B3FC0, 50.0f);
    SkelAnime_Init(globalCtx, &this->skelAnime, &D_060065C8, (AnimationHeader *) &D_060014CC, this->limbDrawTbl, this->transitionDrawTable, 0xC);
    this->unkColor226.r = 0xFF;
    this->unkColor226.g = 0xFF;
    this->unkColor226.b = 0xD2;
    this->unkColor226.a = 0xFF;
    //temp_a2 = &this->lightInfo;
    //sp34 = temp_a2;
    this->lightNode = LightContext_InsertLight(globalCtx, &globalCtx->lightCtx, &this->lightInfo);
    Lights_PointGlowSetInfo(&this->lightInfo, (s16) (s32) this->actor.home.pos.x, (s16) (s32) this->actor.home.pos.y, (s16) (s32) this->actor.home.pos.z, 0, 0, 0, 0);
    Collider_InitAndSetCylinder(globalCtx, &this->collider, (Actor *) this, &D_80B1DA70);
    CollisionCheck_SetInfo(&this->actor.colChkInfo, &D_80B1DAA4, &D_80B1DA9C);

    // issues here: vanilla wants to load params into three separate registers...
    // last time I ran into that issue the answer was using this and thisx together, but three?

    //sisType = ((s32) this->actor.params >> 8) & 3;
    //sisType = ((s32) thisx->params >> 8) & 3;

    this->sisterType = (this->actor.params >> 8) & 3;
    //this->sisterType = sisType;
    //this->actor.hintId = sisType + 0x50;
    //this->actor.hintId = this->sisterType + 0x50;
    this->actor.hintId = ((this->actor.params >> 8) & 3) + 0x50;
    if (1) {}
    //this->unk18D = (this->actor.params >> 0xA) & 3;
    this->unk18D = (thisx->params >> 0xA) & 3;
    this->unk18E = 0x20;
    this->unk18F = 0x14;
    this->unk190 = 1;
    this->unk191 = 0x20;
    this->actor.flags &= -0x2;
    this->unk2EC = 110.0f;
    if ((this->actor.params & 0x1000) != 0) {
    //if ((thisx->params & 0x1000) != 0) {
        func_80B1AA88(this);
    } else if (this->sisterType == 0) {
        if (this->unk18D == 0) {
            this->actor.colChkInfo.health = 8;
            this->collider.info.toucher.damage = 0x10;
            this->collider.base.ocFlags1 = 9;
            func_80B1BCF0(this, globalCtx);
            func_80B1C2E8(this);
        } else {
            this->collider.info.elemType = 4;
            this->actor.flags &= -0x4201;
            this->collider.info.bumper.dmgFlags |= 0x40001;
            this->collider.base.ocFlags1 = 0;
            func_80B1BE4C(this, globalCtx);
        }
    } else {
        func_80B1C2E8(this);
    }
    this->actor.params &= 0xFF;
}
#else
#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Po_Sisters/EnPoSisters_Init.s")
#endif

void EnPoSisters_Destroy(Actor *thisx, GlobalContext *globalCtx) {
    EnPoSisters* this = THIS;

    LightContext_RemoveLight(globalCtx, &globalCtx->lightCtx, this->lightNode);
    Collider_DestroyCylinder(globalCtx, &this->collider);
}

// loop over struct function, ugh
void func_80B1A648(EnPoSisters *this, s16 arg2, Vec3f *pos);
#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Po_Sisters/func_80B1A648.s")

// this control flow looks like !A || B but why does it load 2ec twice?
#ifdef NON_MATCHING
void func_80B1A768(EnPoSisters *this, GlobalContext *globalCtx) {
    f32 sp20;
    Player *player = PLAYER;
    //u8 yawDiff;

    if (this->unk18D == 0 || this->actionFunc != func_80B1B444) {
    //yawDiff = this->unk18D;
    // reverse
    ///* 
        if (!(player->swordState == 0 || player->swordAnimation  >= 0x1E) 
          || (player->actor.world.pos.y - player->actor.floorHeight < 1.0f)) {
            Math_StepToF(&this->unk2EC, 170.0f, 10.0f);
        } else {
            Math_StepToF(&this->unk2EC, 110.0f, 3.0f);
            sp20 = this->unk2EC;
        }

    //  */

        //if ((player->swordState == 0) || (player->swordAnimation  >= 0x1E)) {
            //if ((player->actor.world.pos.y - player->actor.floorHeight) < 1.0f) {
                //Math_StepToF(&this->unk2EC, 110.0f, 3.0f);
            //} else {
        //block_6:
                //Math_StepToF(&this->unk2EC, 170.0f, 10.0f);
            //}
        //} else {
            //goto block_6;
        //}
    } else if (this->unk18D != 0) {
        sp20 = this->actor.parent->xzDistToPlayer;
    }
    this->actor.world.pos.x = (Math_SinS((s16) (this->actor.shape.rot.y + 0x8000)) * sp20) + player->actor.world.pos.x;
    this->actor.world.pos.z = (Math_CosS((s16) (this->actor.shape.rot.y + 0x8000)) * sp20) + player->actor.world.pos.z;
}
#else
#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Po_Sisters/func_80B1A768.s")
#endif

// decr is being stupid
#ifdef NON_MATCHING
void func_80B1A894(EnPoSisters *this, GlobalContext *globalCtx) {
    f32 sp24;
    //u8 temp_t8;
    //u8 yawDiff;
    //u8 unk190decr;
    //u8 pad;
    Player* player = PLAYER;

    Math_ApproachF(&this->actor.world.pos.y, player->actor.world.pos.y + 5.0f, 0.5f, 3.0f);

    // this section looks like a timer countdown with DECR but wont match
    //yawDiff = this->unk18E;
    //unk190decr = yawDiff;
    if (this->unk18E == 0) {
        this->unk18E = 0x20;
        //unk190decr = (u8)0x20U & 0xFF;
    }
    //phi_v1 = unk190decr;
    if (this->unk18E != 0) {
        ////temp_t8 = unk190decr - 1;
        this->unk18E--;
        ////phi_v1 = temp_t8 & 0xFF;
    }
    sp24 = Math_SinS(((this->unk18E << 0x1B) >> 0x10));
    //sp24 = Math_SinS(((DECR(this->unk18E) << 0x1B) >> 0x10));

    // the branching here is a bit odd, postdecr without DECR's zero check is the cloesest
    //sp24 = Math_SinS(((this->unk18E-- << 0x1B) >> 0x10));
    this->actor.world.pos.y += (2.0f + (0.5f * Rand_ZeroOne())) * sp24;
    if (this->unkColor226.a == 0xFF) {
        if ((this->actionFunc != func_80B1B168 ) && (this->actionFunc != func_80B1B020 )) {
            if (this->actionFunc == func_80B1B628 ) {
                func_800B9010((Actor *) this, NA_SE_EN_PO_AWAY - SFX_FLAG);
                return;
            }
            func_800B9010((Actor *) this, NA_SE_EN_PO_FLY - SFX_FLAG);
        }
    }
}
#else
#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Po_Sisters/func_80B1A894.s")
#endif

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Po_Sisters/func_80B1A9B0.s")

void func_80B1AA88(EnPoSisters *this) {
    SkelAnime_ChangeAnimTransitionRepeat(&this->skelAnime, &D_060014CC, -3.0f);
    this->actor.speedXZ = 0.0f;
    this->unk192 = Rand_S16Offset(100, 50);
    this->actionFunc = func_80B1AAE8;
}

void func_80B1AAE8(EnPoSisters *this, GlobalContext *globalCtx) {
    SkelAnime_FrameUpdateMatrix(&this->skelAnime);
    if (DECR(this->unk192) == 0) {
        this->unk192 = Rand_S16Offset(100, 50);
        Audio_PlayActorSound2((Actor *) this, NA_SE_EN_PO_LAUGH2);
    }
}

void func_80B1AB5C(EnPoSisters *this) {
    SkelAnime_ChangeAnimTransitionRepeat(&this->skelAnime, &D_060014CC, -3.0f);
    this->unk192 = Rand_S16Offset(2, 3);
    this->actionFunc = func_80B1ABB8;
    this->actor.speedXZ = 0.0f;
}

void func_80B1ABB8(EnPoSisters *this, GlobalContext *globalCtx) {
    SkelAnime_FrameUpdateMatrix(&this->skelAnime);
    if (func_801378B8(&this->skelAnime, 0.0f) != 0) {
        DECR(this->unk192);
    }
    if (this->unk192 == 0 || (this->actor.xzDistToPlayer < 600.0f)) {
        func_80B1AC40(this);
    }
}

void func_80B1AC40(EnPoSisters *this) {
    if (this->actionFunc != func_80B1AE3C) {
        SkelAnime_ChangeAnimTransitionRepeat(&this->skelAnime, &D_06000D40, -3.0f);
    }
    this->unk192 = Rand_S16Offset(15, 3);
    this->unk191 |= 0x7;
    this->actionFunc = func_80B1ACB8;
}

void func_80B1ACB8(EnPoSisters *this, GlobalContext *globalCtx) {
    SkelAnime_FrameUpdateMatrix(&this->skelAnime);
    Math_StepToF(&this->actor.speedXZ, 1.0f, 0.2f);
    if (func_801378B8(&this->skelAnime, 0.0f) != 0) {
        DECR(this->unk192);
    }
    if (this->actor.xzDistToPlayer < 600.0f && fabsf(this->actor.yDistToPlayer + 5.0f) < 30.0f) {
        func_80B1AE28(this);
    } else if (this->unk192 == 0 && Math_StepToF(&this->actor.speedXZ, 0.0f, 0.2f) != 0) {
        func_80B1AB5C(this);
    }
    if ((this->actor.bgCheckFlags & 0x8) != 0) {
        // 1820?
        Math_ScaledStepToS(&this->actor.world.rot.y, 
            Actor_YawToPoint((Actor *) this, &this->actor.home.pos), 0x71C);
    } else {
        if (Actor_XZDistanceToPoint((Actor *) this, &this->actor.home.pos) > 600.0f) {
            Math_ScaledStepToS(&this->actor.world.rot.y, 
                Actor_YawToPoint((Actor *) this, &this->actor.home.pos), 0x71C);
        }
    }
}

void func_80B1AE28(EnPoSisters *this) {
    this->actionFunc = func_80B1AE3C;
}

void func_80B1AE3C(EnPoSisters *this, GlobalContext *globalCtx) {
    Player* player = PLAYER; 
    s16 yawDiff;

    SkelAnime_FrameUpdateMatrix(&this->skelAnime);
    yawDiff = this->actor.yawTowardsPlayer - player->actor.shape.rot.y;
    Math_StepToF(&this->actor.speedXZ, 2.0f, 0.2f);
    if (yawDiff >= 0x3001) {
        Math_ScaledStepToS(&this->actor.world.rot.y, (this->actor.yawTowardsPlayer + 0x3000), 0x71C);
    } else if ((s32) yawDiff < -0x3000) {
        Math_ScaledStepToS(&this->actor.world.rot.y, (this->actor.yawTowardsPlayer - 0x3000), 0x71C);
    } else {
        Math_ScaledStepToS(&this->actor.world.rot.y, this->actor.yawTowardsPlayer, 0x71C);
    }
    if ((this->actor.xzDistToPlayer < 320.0f) && (fabsf(this->actor.yDistToPlayer + 5.0f) < 30.0f)) {
        func_80B1AF8C(this);
    } else {
        if (this->actor.xzDistToPlayer > 720.0f) {
            func_80B1AC40(this);
        } 
    }
}

void func_80B1AF8C(EnPoSisters *this) {
    if (this->unkColor226.a != 0) {
        this->collider.base.colType = 9;
        this->collider.base.acFlags |= 0x4;
    }
    SkelAnime_ChangeAnimTransitionRepeat(&this->skelAnime, &D_06000114, -5.0f);
    this->actor.speedXZ = 0.0f;
    this->unk192 = (SkelAnime_GetFrameCount((AnimationHeaderCommon *) &D_06000114) * 3) + 3;
    this->unk191 &= ~0x2;
    this->actionFunc = func_80B1B020;
}

void func_80B1B020(EnPoSisters *this, GlobalContext *globalCtx) {

    SkelAnime_FrameUpdateMatrix(&this->skelAnime);
    DECR(this->unk192);
    this->actor.shape.rot.y += ((s32) ((this->skelAnime.animFrameCount + 1.0f) * 3.0f) - this->unk192) * 0x180;
    if (this->unk192 == 0x12 || this->unk192 == 7) {
        Audio_PlayActorSound2((Actor *) this, NA_SE_EN_PO_ROLL);
    } else {
        if (this->unk192 == 0) {
            func_80B1B0E0(this);
        }
    }
}

void func_80B1B0E0(EnPoSisters *this) {
    //EnPoSisters *temp_a3;

    this->actor.speedXZ = 5.0f;
    if (this->sisterType == 0) {
        this->collider.base.colType = 9;
        this->collider.base.acFlags |= 0x4;
        SkelAnime_ChangeAnimTransitionRepeat(&this->skelAnime, &D_06000114, -5.0f);
    }
    this->unk192 = 5;
    this->actor.world.rot.y = this->actor.yawTowardsPlayer;
    this->unk191 |= 0x8;
    this->actionFunc = func_80B1B168;
}

void func_80B1B168(EnPoSisters *this, GlobalContext *globalCtx) {
    s16 yawDiff;

    SkelAnime_FrameUpdateMatrix(&this->skelAnime);
    if (func_801378B8(&this->skelAnime, 0.0f) != 0) {
        DECR(this->unk192);
    }

    this->actor.shape.rot.y += (s32) (1152.0f * this->skelAnime.animFrameCount);
    if (this->unk192 == 0) {
        yawDiff = this->actor.shape.rot.y - this->actor.world.rot.y;
        if (ABS_ALT(yawDiff) < 0x1000) {
            if (this->sisterType != 0) {
                this->collider.base.colType = 3;
                this->collider.base.acFlags &= ~0x4;
                func_80B1AC40(this);
            } else {
                Audio_PlayActorSound2((Actor *) this, NA_SE_EN_PO_LAUGH2);
                func_80B1BE4C(this, globalCtx);
            }
        }
    }
    if (func_801378B8(&this->skelAnime, 1.0f) != 0) {
        Audio_PlayActorSound2((Actor *) this, NA_SE_EN_PO_ROLL);
    }
}

void func_80B1B280(EnPoSisters *this) {
    SkelAnime_ChangeAnimTransitionRepeat(&this->skelAnime, &D_06000D40, -3.0f);
    this->actor.world.rot.y = this->actor.yawTowardsPlayer + 0x8000;
    if (this->sisterType != 0) {
        this->collider.base.colType = 3;
        this->collider.base.acFlags &= ~0x4;
    }
    this->actionFunc = func_80B1B2F0;
}

void func_80B1B2F0(EnPoSisters *this, GlobalContext *globalCtx) {
    SkelAnime_FrameUpdateMatrix(&this->skelAnime);
    this->actor.shape.rot.y -= (s16)(this->actor.speedXZ * 10.0f * 128.0f);
    if (Math_StepToF(&this->actor.speedXZ, 0.0f, 0.1f) != 0) {
        this->actor.world.rot.y = this->actor.shape.rot.y;
        if (this->sisterType != 0) {
            func_80B1AC40(this);
        } else {
            Audio_PlayActorSound2((Actor *) this, NA_SE_EN_PO_LAUGH2);
            func_80B1BE4C(this, globalCtx);
        }
    }
}

void func_80B1B3A8(EnPoSisters *this) {
    SkelAnime_ChangeAnimTransitionStop(&this->skelAnime, (AnimationHeader *) &D_060008C0, -3.0f);
    if (this->collider.base.ac != NULL) {
        func_800BE504((Actor *) this, &this->collider);
    }
    if (this->sisterType != 0) {
        this->actor.speedXZ = 10.0f;
    }
    this->unk191 &= ~0xB;
    func_800BCB70((Actor *) this, (u16)0x4000, (u16)0xFF, (u16)0, 0x10);
    this->actionFunc = func_80B1B444;
}

void func_80B1B444(EnPoSisters *this, GlobalContext *globalCtx) {
    s32 fadePercent;

    if ((SkelAnime_FrameUpdateMatrix(&this->skelAnime) != 0) && ((this->actor.flags & 0x8000) == 0)) {
        if (this->actor.colChkInfo.health != 0) {
            if (this->sisterType != 0) {
                func_80B1B5B4(this);
            } else if (this->unk18D != 0) {
                func_80B1BE4C(this, NULL); // wat
            } else {
                func_80B1BE4C(this, globalCtx);
            }
        } else {
            func_80B1BA3C(this);
        }
    }
    if (this->unk18D != 0) {
        Math_ScaledStepToS(&this->actor.shape.rot.y, this->actor.parent->shape.rot.y, (this->unk18D == 2) ? (0x800): (0x400));
        fadePercent = (s32) (((this->skelAnime.animFrameCount - this->skelAnime.animCurrentFrame) * 255.0f) 
            / this->skelAnime.animFrameCount);
        this->unkColor226.a = CLAMP(fadePercent, 0, 0xFF);
        this->actor.world.pos.y = this->actor.parent->world.pos.y;
        func_80B1A768(this, globalCtx);
    } else {
        if (this->sisterType != 0) {
            Math_StepToF(&this->actor.speedXZ, 0.0f, 0.5f);
        }
    }
}

void func_80B1B5B4(EnPoSisters *this) {
    SkelAnime_ChangeAnimTransitionRepeat(&this->skelAnime, &D_06000A54, -3.0f);
    this->actor.world.rot.y = this->actor.shape.rot.y + 0x8000;
    this->unk192 = 5;
    this->unk191 |= 0xB;
    this->actionFunc = func_80B1B628;
    this->actor.speedXZ = 5.0f;
}

void func_80B1B628(EnPoSisters *this, GlobalContext *globalCtx) {
    SkelAnime_FrameUpdateMatrix(&this->skelAnime);
    Math_ScaledStepToS(&this->actor.world.rot.y, (this->actor.yawTowardsPlayer + 0x8000), 0x71C);
    if (func_801378B8(&this->skelAnime, 0.0f) != 0) {
        DECR(this->unk192);
    }
    if ((this->actor.bgCheckFlags & 0x8) != 0) {
        this->actor.world.rot.y = this->actor.shape.rot.y;
        this->unk191 |= 0x2;
        func_80B1B70C(this);
        return;
    }
    if ((this->unk192 == 0) && (this->actor.xzDistToPlayer > 480.0f)) {
        this->actor.world.rot.y = this->actor.shape.rot.y;
        func_80B1AC40(this);
    }
}

void func_80B1B70C(EnPoSisters *this) {
    SkelAnime_ChangeAnim(&this->skelAnime, &D_0600119C, 1.5f, 0.0f, 
          (f32) SkelAnime_GetFrameCount((AnimationHeaderCommon *) &D_0600119C), 2, -3.0f);
    this->unk194 = 100;
    this->actor.speedXZ = 0.0f;
    this->actor.world.rot.y = this->actor.shape.rot.y;
    this->unk191 &= ~0x5;
    Audio_PlayActorSound2((Actor *) this, NA_SE_EN_PO_DISAPPEAR);
    Audio_PlayActorSound2((Actor *) this, NA_SE_EN_PO_LAUGH2);
    this->actionFunc = func_80B1B7BC;
}

void func_80B1B7BC(EnPoSisters *this, GlobalContext *globalCtx) {
    s32 fadePercent;

    if (SkelAnime_FrameUpdateMatrix(&this->skelAnime) != 0) {
        this->unkColor226.a = 0;
        this->collider.info.bumper.dmgFlags = 0x40001;
        func_80B1AC40(this);
    } else {
        fadePercent = (s32) (((this->skelAnime.animFrameCount - this->skelAnime.animCurrentFrame) * 255.0f) 
            / this->skelAnime.animFrameCount);
        this->unkColor226.a = CLAMP(fadePercent, 0, 0xFF);
    }
}

void func_80B1B860(EnPoSisters *this, GlobalContext *globalCtx) {
    SkelAnime_ChangeAnim(&this->skelAnime, &D_0600119C, 1.5f, 0.0f, 
        SkelAnime_GetFrameCount((AnimationHeaderCommon *) &D_0600119C), 2, -3.0f);
    if (this->sisterType == 0) {
        this->unk2EC = 110.0f;
        func_80B1A768(this, globalCtx);
        this->unkColor226.a = 0;
        this->actor.draw = EnPoSisters_Draw;
    } else {
        this->actor.world.rot.y = this->actor.shape.rot.y;
    }
    this->unk192 = 0xF;
    this->actor.speedXZ = 0.0f;
    Audio_PlayActorSound2((Actor *) this, NA_SE_EN_STALKIDS_APPEAR);
    this->unk191 &= ~0x1;
    this->actionFunc = func_80B1B940;

}

void func_80B1B940(EnPoSisters *this, GlobalContext *globalCtx) {
    s32 fadePercent;

    if (SkelAnime_FrameUpdateMatrix(&this->skelAnime) != 0) {
        this->unkColor226.a = 0xFF;
        if (this->sisterType != 0) {
            this->unk191 |= 0x1;
            this->collider.info.bumper.dmgFlags = 0xF7CBFFFE;

            // I know it looks like DECR but wont match
            if (this->unk192 != 0) {
                this->unk192--;
            }
            if (this->unk192 == 0) {
                this->unk18F = 0x14;
                func_80B1AC40(this);
            }
        } else {
            func_80B1C030(this);
        }
    } else {
        fadePercent = (s32) ((this->skelAnime.animCurrentFrame * 255.0f) / this->skelAnime.animFrameCount);
        this->unkColor226.a = CLAMP(fadePercent, 0, 0xFF);
        if (this->sisterType == 0) {
            func_80B1A768(this, globalCtx);
        }
    }
}

void func_80B1BA3C(EnPoSisters *this) {
    this->actor.speedXZ = 0.0f;
    this->actor.world.pos.y += 42.0f;
    this->unk192 = 0;
    this->actor.shape.yOffset = -6000.0f;
    this->actor.flags &= -2;
    this->unk191 = 0;
    this->actionFunc = func_80B1BA90;
}

// ah fuck another struct array of weirdness
/*
void func_80B1BA90(EnPoSisters *this, GlobalContext *globalCtx) {
    //f32 temp_f0;
    //s16 temp_v0_4;
    //s32 temp_v0;
    s32 unk190decr;
    s32 temp_v0_3;
    void *temp_a0;
    void *temp_a1;
    void *temp_v1;
    void *t220;
    void *phi_v1;
    s32 unk190decr;

    this->unk190 = (++this->unk190 >= 9) : (8) : (this->unk190);
    //temp_v0 = this->unk190 + 1;
    //if (temp_v0 >= 9) {
        //this->unk190 = 8;
    //} else {
        //this->unk190 = (u8) temp_v0;
    //}
    this->unk192 += 1;
    unk190decr = this->unk190 - 1;
    if (unk190decr > 0) {
        temp_a1 = this + (unk190decr * 0xC);
        t220 = temp_a1 + 0x220;
        t22C = temp_a1 + 0x22C;
        //unk190decr = unk190decr;
        for()
loop_5:
        temp_v0_3 = unk190decr - 1;
        t220_2 = t22C - 0xC;
        t220_2->unkC = (?32) t220->unk0;
        beforet220 = t220 - 0xC;
        t220_2->unk10 = (?32) t220->unk4;
        t220_2->unk14 = (?32) beforet220->unk14;
        t220 = beforet220;
        t22C = t220_2;
        unk190decr = temp_v0_3;
        if (temp_v0_3 > 0) {
            goto loop_5;
        }
    }
    this->unk22C = (Math_SinS((s16) ((this->actor.shape.rot.y + (this->unk192 * 0x3000)) - 0x4000)) 
        * (3000.0f * this->actor.scale.x)) + this->actor.world.pos.x;
    //temp_v0_4 = this->unk192;
    this->unk234 = (Math_CosS((s16) ((this->actor.shape.rot.y + (this->unk192 * 0x3000)) - 0x4000)) 
        * (3000.0f * this->actor.scale.x)) + this->actor.world.pos.z;
    if (this->unk192 < 8) {
        this->unk230 = this->unk23C - 9.0f;
    } else {
        this->unk230 = this->unk23C + 2.0f;
        if (this->unk192 >= 0x10) {
            if (Math_StepToF(&this->actor.scale, 0.0f, 0.001f) != 0) {
                func_80B1BC4C(this);
            }
            //temp_f0 = this->actor.scale.x;
            this->actor.scale.z = this->actor.scale.x;
            this->actor.scale.y = this->actor.scale.x;
        }
    }
    if (this->unk192 == 0x10) {
        Audio_PlayActorSound2((Actor *) this, (u16)0x3877U);
    }
} // */
#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Po_Sisters/func_80B1BA90.s")

void func_80B1BC4C(EnPoSisters *this, GlobalContext *globalCtx) {
    this->unk192 = 0;
    this->actor.world.pos.y = this->unk230;
    Item_DropCollectibleRandom(globalCtx, (Actor *) this, &this->actor.world.pos, (u16)0x80);
    this->actionFunc = func_80B1BCA0;
}

void func_80B1BCA0(EnPoSisters *this, GlobalContext *globalCtx) {
    this->unk192++;
    if (this->unk192 == 0x20) {
        Actor_MarkForDeath((Actor *) this);
    }else {
        func_80B1A648(this, this->unk192, &this->actor.world.pos);
    }
}

// this spawns three meg clones, if any failed to spawn the rest die of embarasment
void func_80B1BCF0(EnPoSisters *this, GlobalContext *globalCtx) {
    Actor* clone1 = Actor_SpawnAsChild(&globalCtx->actorCtx, (Actor *) this, globalCtx, ACTOR_EN_PO_SISTERS, 
        this->actor.world.pos.x, this->actor.world.pos.y, this->actor.world.pos.z, 
        0, 0, 0, 0x400);
    Actor* clone2 = Actor_SpawnAsChild(&globalCtx->actorCtx, (Actor *) this, globalCtx, ACTOR_EN_PO_SISTERS, 
        this->actor.world.pos.x, this->actor.world.pos.y, this->actor.world.pos.z, 
        0, 0, 0, 0x800);
    Actor* clone3 = Actor_SpawnAsChild(&globalCtx->actorCtx, (Actor *) this, globalCtx, ACTOR_EN_PO_SISTERS, 
        this->actor.world.pos.x, this->actor.world.pos.y, this->actor.world.pos.z, 
        0, 0, 0, 0xC00);

    if ((clone1 == NULL) || (clone2 == NULL) || (clone3 == NULL)) {
        if (clone1 != 0) {
            Actor_MarkForDeath(clone1);
        }
        if (clone2 != 0) {
            Actor_MarkForDeath(clone2);
        }
        if (clone3 != 0) {
            Actor_MarkForDeath(clone3);
        }
        Actor_MarkForDeath((Actor *) this);
    }
}


void func_80B1BE4C(EnPoSisters *this, GlobalContext *globalCtx) {
    Vec3f newPos;

    this->actor.draw = NULL;
    this->actor.flags &= -2;
    this->unk194 = 100;
    this->unk191 = 32;
    this->collider.base.colType = 3;
    this->collider.base.acFlags &= ~0x4;
    if (globalCtx != NULL) {
        newPos.x = this->actor.world.pos.x;
        newPos.y = this->actor.world.pos.y + 45.0f;
        newPos.z = this->actor.world.pos.z;
        func_800B3030(globalCtx, &newPos, &D_801D15B0, &D_801D15B0, 150, 0, 3);
    }
    Lights_PointSetColorAndRadius(&this->lightInfo, 0, 0, 0, 0);
    this->actionFunc = func_80B1BF2C;
}

#ifdef NON_MATCHING
// first branch needs to be likely, ugh
void func_80B1BF2C(EnPoSisters *this, GlobalContext *globalCtx) {
    Actor *parent = this->actor.parent;
    Player *player = PLAYER;
    //GlobalContext* gCtx2 = globalCtx;

    // this branch is likely when it shouldn't be...?
    if (this->unk18D == 0) {
        DECR(this->unk194);
        if (this->unk194 == 0) {
            this->actor.shape.rot.y = ((s32) Rand_ZeroFloat(4.0f) << 0xE) + this->actor.yawTowardsPlayer;
            this->actor.world.pos.y = player->actor.world.pos.y + 5.0f;
            func_80B1B860(this, globalCtx);
        }
    } else {
        if (this->actionFunc == func_80B1B940) {
            this->actor.shape.rot.y = parent->shape.rot.y + (this->unk18D << 0xE);
            //this->actor.shape.rot.y =  (this->unk18D << 0xE) + parent->shape.rot.y;
            this->actor.world.pos.y = player->actor.world.pos.y + 5.0f;
            func_80B1B860(this, globalCtx);
            return;
        }
        if (!parent->shape.rot.y){ }
        if (this->actionFunc == func_80B1BA90) {
            Actor_MarkForDeath((Actor *) this);
        }
    }
}
#else
#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Po_Sisters/func_80B1BF2C.s")
#endif

void func_80B1C030(EnPoSisters *this) {
    SkelAnime_ChangeAnimTransitionRepeat(&this->skelAnime, &D_06000D40, -3.0f);
    this->unkColor226.a = 0xFF;
    this->unk192 = 0x12C;
    this->unk194 = 3;
    this->unk191 |= 9;
    this->actor.flags |= 1;
    this->actionFunc = func_80B1C0A4;
}


#ifdef NON_EQUIVLENT
// non-matching: its trying some weird cast the input to a sins function
void func_80B1C0A4(EnPoSisters *this, GlobalContext *globalCtx) {
    s16 tempunk192;
    s16 temp_a0_2;
    s16 old192;

    DECR(this->unk192);
    if (this->unk194 > 0) {
        if (this->unk192 >= 0x10) {
            SkelAnime_FrameUpdateMatrix(&this->skelAnime);
            if (this->unk18D == 0) {
                if (ABS_ALT(0x10 - this->unk18E) < 0xE) {
                    // some casting weirdness leading into Math_SinS, this matches but ugly
                    this->actor.shape.rot.y += (s32) ((f32) (0x580 - (this->unk194 * 0x180)) 
                      //* fabsf(Math_SinS( this->unk18E & 0x10)));
                      //* fabsf(Math_SinS( ((this->unk18E) << 0x1B ) >> 0x10 )));
                      //* fabsf(Math_SinS( this->unk18E & 0x1F )));
                      * fabsf(Math_SinS( (s16)this->unk18E & 0xFFFFFFFF)));
                }
                if ((this->unk192 >= 0x11C) || (this->unk192 < 0x1F)) {
                    this->unk191 |= 0x40;
                } else {
                    this->unk191 &= 0xFFBF;
                }
            } else {
                this->actor.shape.rot.y = this->actor.parent->shape.rot.y + (this->unk18D << 0xE);
            }
        }
    }
    if (this->unk18D == 0) {
        if (! (this->unk192 < 0x11C) || (this->unk192 < 0x1F) && (this->unk192 >= 0x10)) {
            this->unk191 |= 0x40;
        } else {
            this->unk191 &= 0xFFBF;
        }
    }
    if (this->unk192 == 0) {
        if (this->unk18D == 0) {
            func_80B1B0E0(this);
        } else {
            func_80B1BE4C(this, globalCtx);
        }
    } else if (this->unk18D != 0) {
        // thinking fake match
        if (((EnPoSisters*)this->actor.parent)->actionFunc == func_80B1B444 ) {
        //if (func_80B1B444 == ((EnPoSisters*)this->actor.parent)->actionFunc ) {
            func_80B1B3A8(this);
        }
    } else {
        tempunk192 = this->unk194;
        if (tempunk192 == 0) {
            this->unk194 = -0xF;
        } else {
            if ((s32) tempunk192 < 0) {
                this->unk194 = tempunk192 + 1;
                if (this->unk194 == 0) {
                    func_80B1B0E0(this);
                }
            }
        }
    }
    func_80B1A768(this, globalCtx);
}
#else
#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Po_Sisters/func_80B1C0A4.s")
#endif

void func_80B1C2E8(EnPoSisters *this) {
    SkelAnime_ChangeAnimDefaultStop(&this->skelAnime, &D_0600119C);
    Audio_PlayActorSound2((Actor *) this, NA_SE_EN_STALKIDS_APPEAR);
    this->unkColor226.a = 0;
    this->unk191 = 0x20;
    this->actionFunc = func_80B1C340;
}

// regalloc around temp_f16 calc
void func_80B1C340(EnPoSisters *this, GlobalContext *globalCtx) {
    //s32 temp_f16;

    if (SkelAnime_FrameUpdateMatrix(&this->skelAnime) != 0) {
        this->unkColor226.a = 0xFF;
        this->actor.flags |= 1;
        this->unk191 |= 0x18;
        if (this->sisterType == 0) {
            func_80B1BE4C(this, globalCtx);
        } else {
            func_80B1AC40(this);
        }
    }else {

        //temp_f16 = (s32) (255.0f * (this->skelAnime.animCurrentFrame / this->skelAnime.animFrameCount));
        f32 ratio = 255.0f * (this->skelAnime.animCurrentFrame / this->skelAnime.animFrameCount);
        //f32 ratio = (this->skelAnime.animCurrentFrame / this->skelAnime.animFrameCount) * 255.0f;
        s32 temp_f16 = (s32) ratio;
        //s32 temp_f16 = (s32) ((this->skelAnime.animCurrentFrame / this->skelAnime.animFrameCount) * 255.0f);
        //if (temp_f16 < 0) {
            //this->unkColor226.a = 0;
            //return;
        //}
        //phi_v1 = (u8) temp_f16;
        //if (temp_f16 >= 0x100) {
            //phi_v1 = (u8)0xFFU;
        //}
        //this->unkColor226.a = phi_v1;
        this->unkColor226.a = CLAMP(temp_f16, 0, 0xFF);
    }
}
//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Po_Sisters/func_80B1C340.s")

void func_80B1C408(EnPoSisters* this, GlobalContext *globalCtx);
#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Po_Sisters/func_80B1C408.s")

void EnPoSisters_Update(Actor* thisx, GlobalContext *globalCtx) {
    EnPoSisters* this = THIS;
    s32 pad;
    s32 temp190;
    Vec3f pos;
    s32 unuseds32Ptr; // passed to func_800C411C by address then never used

    if ((this->collider.base.atFlags & 2) != 0) {
        this->collider.base.atFlags &= ~0x2;
        func_80B1B280(this);
    }
    func_80B1C408(this, globalCtx);
    if ((this->unk191 & 0x4) != 0) {
        func_80B1A9B0(this, globalCtx);
    }

    this->actionFunc(this, globalCtx);

    if ((this->unk191 & 0x8) != 0) {
        func_80B1A894(this, globalCtx);
    }
    Actor_SetVelocityAndMoveYRotationAndGravity((Actor *) this);
    if ((this->unk191 & 0x10) != 0) {
        Actor_UpdateBgCheckInfo(globalCtx, (Actor *) this, 20.0f, 20.0f, 0.0f, 5);
    } else {
        pos.x = this->actor.world.pos.x;
        pos.y = this->actor.world.pos.y + 10.0f;
        pos.z = this->actor.world.pos.z;
        this->actor.floorHeight = func_800C411C(&globalCtx->colCtx, &this->actor.floorPoly, &unuseds32Ptr, (Actor *) this, &pos);
    }

    this->actor.shape.shadowAlpha = this->unkColor226.a;
    Actor_SetHeight((Actor *) this, 40.0f);
    if (this->unk2F0 > 0.0f) {
        Math_StepToF(&this->unk2F0, 0.0f, 0.05f);

        if (this->unkColor226.a != 0xFF) {
            f32 colorCheck = ((f32) this->unkColor226.a) * 0.003921569f;
            if (colorCheck < this->unkColor226.a ){
                this->unk2F0 = colorCheck;
            }
        }

        this->unk2F4 = (this->unk2F0 + 1.0f) * 0.25f;
        this->unk2F4 = CLAMP_MAX(this->unk2F4, 0.5f); 
    }

    if ((this->unk191 & 0x1F) != 0) {
        Collider_UpdateCylinder((Actor *) this, &this->collider);
        if (this->actionFunc == func_80B1B168  || this->actionFunc == func_80B1B020 ) {
            this->unk190++;
            this->unk190 = CLAMP_MAX(this->unk190, 8);
        } else if (this->actionFunc != func_80B1BA90 ) {
            temp190 = this->unk190 - 1;
            this->unk190 = CLAMP_MIN(temp190, 1);
        }
        if (this->actionFunc == func_80B1B168 ) {
            this->actor.flags |= 0x1000000;
            CollisionCheck_SetAT(globalCtx, &globalCtx->colChkCtx, &this->collider.base);
        }
        if ((this->unk191 & 0x1) != 0) {
            CollisionCheck_SetAC(globalCtx, &globalCtx->colChkCtx, &this->collider.base);
        }
        if (this->actionFunc != func_80B1BF2C ) {
            CollisionCheck_SetOC(globalCtx, &globalCtx->colChkCtx, &this->collider.base);
        }
        if (this->actionFunc == func_80B1B628 ) {
            this->actor.shape.rot.y = this->actor.world.rot.y + 0x8000;
        } else {
            if ((this->unk191 & 0x2) != 0) {
                this->actor.shape.rot.y = this->actor.world.rot.y;
            }
        }
    }
}

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Po_Sisters/func_80B1C974.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Po_Sisters/func_80B1CB44.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Po_Sisters/func_80B1CD34.s")

// cannot do draw function until we have our array of struct mapped
#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Po_Sisters/EnPoSisters_Draw.s")
