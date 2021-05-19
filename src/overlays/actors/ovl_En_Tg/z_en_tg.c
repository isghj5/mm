#include "z_en_tg.h"

#define FLAGS 0x00000009

#define THIS ((EnTg*)thisx)

void EnTg_Init(Actor* thisx, GlobalContext* globalCtx);
void EnTg_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnTg_Update(Actor* thisx, GlobalContext* globalCtx);
//void EnTg_Update(EnTg* this, GlobalContext* globalCtx);
void EnTg_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_8098FD50(Actor* actor, EnTgParticle particles[], Vec3f* paramV, s32 length );
void func_8098FEA8(EnTg* this, EnTgParticle particles[], s32 length);
void func_8098F8A8(EnTg* this, GlobalContext* globalCtx);

void func_8098F800(SkelAnime *skelAnim, UNK_PTR animationPtr, s16 length);
void func_8098F8A8(EnTg *this, GlobalContext *globalCtx);
//void func_8098F928(EnTg *this, EnTgActionFunc actionFunc);
void func_8098F928(EnTg *this, GlobalContext* globalCtx);

// one and only actionfunc
void func_8098FA70(EnTg* this, GlobalContext* globalCtx);

const ActorInit En_Tg_InitVars = {
    ACTOR_EN_TG,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_MU,
    sizeof(EnTg),
    (ActorFunc)EnTg_Init,
    (ActorFunc)EnTg_Destroy,
    (ActorFunc)EnTg_Update,
    (ActorFunc)EnTg_Draw
};

//static ColliderCylinderInit sCylinderInit = { //glabel D_809901C0
static ColliderCylinderInit D_809901C0 = {
    { COLTYPE_HIT0, AT_NONE, AC_ON | AC_TYPE_PLAYER, OC1_ON | OC1_TYPE_ALL, OC2_TYPE_1, COLSHAPE_CYLINDER, },
    { ELEMTYPE_UNK1, { 0x00000000, 0x00, 0x00 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_ON, },
    { 18, 64, 0, { 0, 0, 0 } },
};

// info 2
UNK_TYPE D_809901EC[] = {
0x00000000, 0x00000000, 0xFF000000,
};

UNK_TYPE D_809901F8[] = {
0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
};

// that new animation type
UNK_TYPE D_80990218[] = { 0x060053E0, 0x3F800000, 0x0000FFFF, 0x00000000, };

Vec3f D_80990228 = { 0, 0, 0 };


Vec3f D_80990234 = { 0x00000000, 0x3FC00000, 0x00000000, };
Vec3f D_80990240 = { 0x00000000, 0x00000000, 0x00000000, };
Vec3f D_8099024C = { 0x00000000, 0x00000000, 0x00000000, };
//0x00000000, // prob padding
//0x00000000,

// takes our weird animation type
#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Tg_0x8098F800/func_8098F800.asm")

// update collider
void func_8098F8A8(EnTg *this, GlobalContext *globalCtx) {
    this->collider.dim.pos.x = (s16) this->actor.world.pos.x;
    this->collider.dim.pos.y = (s16) this->actor.world.pos.y;
    this->collider.dim.pos.z = (s16) this->actor.world.pos.z;
    CollisionCheck_SetAC(globalCtx, &globalCtx->colCheckCtx, &this->collider);
    CollisionCheck_SetOC(globalCtx, &globalCtx->colCheckCtx, &this->collider);
}

void func_8098F928(EnTg *this, GlobalContext *globalCtx) {
    SkelAnime_FrameUpdateMatrix(&this->anime);
}

void EnTg_Init(Actor *thisx, GlobalContext *globalCtx) {
    EnTg* this = THIS;

    ActorShape_Init(&thisx->shape, 0.0f, NULL, 0.0f);
    SkelAnime_InitSV(globalCtx, &this->anime, D_0600B2B0, NULL, &this->limbDrawTbl, &this->transitionDrawTbl, 0x15);

    func_8098F800(&this->anime, D_80990218, 0); // set animation
    Collider_InitCylinder(globalCtx, &this->collider);
    Collider_SetCylinder(globalCtx, &this->collider, &this->actor, &D_809901C0);
    CollisionCheck_SetInfo2(&thisx->colChkInfo, &D_809901F8, &D_809901EC);
    Actor_SetScale(&this->actor, 0.01f);
    this->actionFunc = func_8098FA70;
    this->actor.gravity = -4.0f;
}

void EnTg_Destroy(Actor *thisx, GlobalContext *globalCtx) {
    EnTg* this = THIS;

    Collider_DestroyCylinder(globalCtx, &this->collider);
}

//action func
void func_8098FA70(EnTg *this, GlobalContext *globalCtx) {
    Vec3f tempPos;
    s32 tmp2EC = this->unk2EC;

    this->actor.shape.rot.y += sREG(0) + 0x258;
    this->actor.world.rot = this->actor.shape.rot;
  
    if (DECR(this->unk2EC) == 0) {
        this->unk2EC = 0xC;
        tempPos = this->actor.world.pos;
        tempPos.y += 62.0f;
        func_8098FD50(this, this->particles, &tempPos, ENTG_PARTICLECOUNT);
    }
}

void EnTg_Update(Actor *thisx, GlobalContext *globalCtx) { 
    EnTg* this = THIS;

    this->actionFunc(&this->actor, globalCtx); 
    func_800B78B8(globalCtx, &this->actor, 0.0f, 0.0f, 0.0f, 4); 
    func_8098F928(this, globalCtx); 
    func_8098FEA8(globalCtx, this->particles, 0xA); 
    func_8098F8A8(this, globalCtx); 
}

// limb draw
s32 func_8098FBB4(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, Actor* actor) {
    return 0;
}

// post limbdraw
void func_8098FBD0(GlobalContext *globalCtx, s32 limbIndex, Gfx **dList, Vec3s *rot, Actor *actor) {
    s32 pad;
    Vec3f zeroTmp;

    zeroTmp = D_80990228; // 0,0,0
    if (limbIndex == 9) {
        SysMatrix_MultiplyVector3fByState(&zeroTmp, &actor->focus);
    }
}

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Tg_0x8098F800/EnTg_Draw.asm")

#if NON_MATCHING
// non-matching: stack oversize and regalloc, romshift by one
//  think the regalloc causes the stack since it all seems necessary
// attempts to shrink stack with a smaller i/length just add casting instructions
void func_8098FD50(Actor* actor, EnTgParticle particles[], Vec3f *paramV, s32 length) {
    Vec3f sp2C = D_80990234;
    Vec3f sp20 = D_80990240;
    s32 i = 0;
    EnTgParticle* ptr = &particles[0];

    for (i = 0; i < length && ptr->unk0 != 0; ++i, ptr++);
    if (i < length) {
        ptr->unk0 = 1;
        ptr->unk14 = *paramV;
        ptr->unk2C = sp2C;
        ptr->unk20 = sp20;
        ptr->unk4 = 0.01f; //D_80990260;
        ptr->unk14.x += (4.0f * Math_SinS(actor->shape.rot.y));
        ptr->unk14.z += (4.0f * Math_CosS(actor->shape.rot.y));
        ptr->unk1 = 0x10;
    }
}
#else
#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Tg_0x8098F800/func_8098FD50.asm")
#endif

// draw particles?
#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Tg_0x8098F800/func_8098FEA8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Tg_0x8098F800/func_8099000C.asm")
