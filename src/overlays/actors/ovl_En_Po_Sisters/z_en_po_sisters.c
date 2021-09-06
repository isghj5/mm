#include "z_en_po_sisters.h"

#define FLAGS 0x00005015

#define THIS ((EnPoSisters*)thisx)

void EnPoSisters_Init(Actor* thisx, GlobalContext* globalCtx);
//void EnPoSisters_Init(EnPoSisters* this, GlobalContext* globalCtx);
void EnPoSisters_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnPoSisters_Update(Actor* thisx, GlobalContext* globalCtx);
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
void func_80B1BC4C(EnPoSisters* this);
void func_80B1BE4C(EnPoSisters* this);
void func_80B1C030(EnPoSisters* this);
void func_80B1C2E8(EnPoSisters* this);
// might be s32 return
void func_80B1C974(EnPoSisters* this);



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

extern UNK_TYPE D_06000114;
extern UNK_TYPE D_060008C0;
extern UNK_TYPE D_06000A54;
extern UNK_TYPE D_06000D40;
extern UNK_TYPE D_0600119C;
extern UNK_TYPE D_060014CC;
extern UNK_TYPE D_060027B0;
extern UNK_TYPE D_060046E0;

extern SkeletonHeader D_060065C8;

#ifdef NON_MATCHING
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
            func_80B1BE4C(this);
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

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Po_Sisters/func_80B1A648.s")

// this control flow looks like !A || B but why does it load 2ec twice?
#ifdef NON_MATCHING
void func_80B1A768(EnPoSisters *this, GlobalContext *globalCtx) {
    f32 sp20;
    Player *player = PLAYER;
    //u8 temp_v0;

    if (this->unk18D == 0 || this->actionFunc != func_80B1B444) {
    //temp_v0 = this->unk18D;
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
    //u8 temp_v0;
    //u8 phi_v0;
    //u8 pad;
    Player* player = PLAYER;

    Math_ApproachF(&this->actor.world.pos.y, player->actor.world.pos.y + 5.0f, 0.5f, 3.0f);

    // this section looks like a timer countdown with DECR but wont match
    //temp_v0 = this->unk18E;
    //phi_v0 = temp_v0;
    if (this->unk18E == 0) {
        this->unk18E = 0x20;
        //phi_v0 = (u8)0x20U & 0xFF;
    }
    //phi_v1 = phi_v0;
    if (this->unk18E != 0) {
        ////temp_t8 = phi_v0 - 1;
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

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Po_Sisters/func_80B1AB5C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Po_Sisters/func_80B1ABB8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Po_Sisters/func_80B1AC40.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Po_Sisters/func_80B1ACB8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Po_Sisters/func_80B1AE28.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Po_Sisters/func_80B1AE3C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Po_Sisters/func_80B1AF8C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Po_Sisters/func_80B1B020.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Po_Sisters/func_80B1B0E0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Po_Sisters/func_80B1B168.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Po_Sisters/func_80B1B280.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Po_Sisters/func_80B1B2F0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Po_Sisters/func_80B1B3A8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Po_Sisters/func_80B1B444.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Po_Sisters/func_80B1B5B4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Po_Sisters/func_80B1B628.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Po_Sisters/func_80B1B70C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Po_Sisters/func_80B1B7BC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Po_Sisters/func_80B1B860.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Po_Sisters/func_80B1B940.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Po_Sisters/func_80B1BA3C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Po_Sisters/func_80B1BA90.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Po_Sisters/func_80B1BC4C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Po_Sisters/func_80B1BCA0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Po_Sisters/func_80B1BCF0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Po_Sisters/func_80B1BE4C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Po_Sisters/func_80B1BF2C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Po_Sisters/func_80B1C030.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Po_Sisters/func_80B1C0A4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Po_Sisters/func_80B1C2E8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Po_Sisters/func_80B1C340.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Po_Sisters/func_80B1C408.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Po_Sisters/EnPoSisters_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Po_Sisters/func_80B1C974.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Po_Sisters/func_80B1CB44.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Po_Sisters/func_80B1CD34.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Po_Sisters/EnPoSisters_Draw.s")
