#include "z_en_kakasi.h"

#define FLAGS 0x02000019

#define THIS ((EnKakasi*)thisx)

void EnKakasi_Init(Actor* thisx, GlobalContext* globalCtx);
void EnKakasi_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnKakasi_Update(Actor* thisx, GlobalContext* globalCtx);
void EnKakasi_Draw(Actor* thisx, GlobalContext* globalCtx);


void func_80970A10(EnKakasi* this, GlobalContext *globalCtx);
void func_8096FC8C(EnKakasi* this);
void func_8096FDE8(EnKakasi* this);

// lot of action functions
void func_8096F88C(Actor *thisx, GlobalContext* globalCtx);
void func_8096FCC4(Actor *thisx, GlobalContext* globalCtx);
void func_8096FE00(Actor *thisx, GlobalContext* globalCtx);
void func_80970658(Actor *thisx, GlobalContext* globalCtx);
void func_80970740(Actor *thisx, GlobalContext* globalCtx);
void func_80970978(Actor *thisx, GlobalContext* globalCtx);
void func_80970A9C(Actor *thisx, GlobalContext* globalCtx);
void func_809714BC(Actor *thisx, GlobalContext* globalCtx);
void func_80971AD4(Actor *thisx, GlobalContext* globalCtx);
void func_809717D0(Actor* thisx, GlobalContext* globalCtx);
void func_80971A64(Actor* thisx, GlobalContext* globalCtx);
void func_8097185C(Actor* thisx, GlobalContext* globalCtx);
void func_8097193C(Actor *thisx, GlobalContext *globalCtx);
void func_80971064(EnKakasi* this, GlobalContext *globalCtx);
void func_80971430(Actor* thisx, GlobalContext* globalCtx);
void func_80970F20(Actor *thisx, GlobalContext *globalCtx);
void func_8097006C(Actor* thisx, GlobalContext* globalCtx);

void func_80971794(EnKakasi *this);
void func_80970008(EnKakasi* this);
void func_809705E4(EnKakasi* this, GlobalContext *arg1);
void func_80971440(EnKakasi* this);
void func_80971A38(EnKakasi *this);
void func_80970FF8(EnKakasi *this);

void func_80971CE0(struct GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3s* rot, struct Actor* actor);

ColliderCylinderInit D_80971D80[] = { // col init
    0x0A000939, 0x20010000, 0x00000000, 0xF7CFFFFF,
    0x00000000, 0xF7CFFFFF, 0x00000000, 0x00050100,
    0x00140046, 0x00000000, 0x00000000,
};
// cant use this until we match init
//static ColliderCylinderInit sCylinderInit = {
    //{ COLTYPE_NONE, AT_NONE, AC_ON | AC_TYPE_PLAYER, OC1_ON | OC1_TYPE_ALL, OC2_TYPE_2, COLSHAPE_CYLINDER, },
    //{ ELEMTYPE_UNK0, { 0xF7CFFFFF, 0x00, 0x00 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON | BUMP_HOOKABLE, OCELEM_ON, },
    //{ 20, 70, 0, { 0, 0, 0 } },
//};

const ActorInit En_Kakasi_InitVars = {
    ACTOR_EN_KAKASI,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_KA,
    sizeof(EnKakasi),
    (ActorFunc)EnKakasi_Init,
    (ActorFunc)EnKakasi_Destroy,
    (ActorFunc)EnKakasi_Update,
    (ActorFunc)EnKakasi_Draw
};

// todo: find a way to painlessly turn these into 0.0f notation
Vec3f D_80971DCC[] = {
    {0x00000000, 0x42700000, 0x42700000},
    {0x42200000, 0x42200000, 0x42480000},
    {0xC2200000, 0x42200000, 0x42480000},
    {0x42200000, 0x41A00000, 0x42DC0000},
    {0xC2200000, 0x41A00000, 0x42DC0000},
    {0x00000000, 0x42A00000, 0x42700000},
    {0x42480000, 0x42200000, 0xC1F00000},
    {0xC2480000, 0x42200000, 0xC1F00000},
    {0x00000000, 0x42480000, 0x42700000},
};
Vec3f D_80971E38[] = {
    {0x00000000, 0x425C0000, 0x42700000,},
    {0x00000000, 0x425C0000, 0x42700000,},
    {0xC2A00000, 0x420C0000, 0x41700000,},
    {0x42A00000, 0x42340000, 0x41700000,},
    {0xC1200000, 0x420C0000, 0x42820000,},
    {0x00000000, 0x42DC0000, 0x43340000,},
    {0x00000000, 0x42700000, 0x428C0000,},
    {0x00000000, 0x42700000, 0x428C0000,},
    {0xC2A00000, 0x42480000, 0x42200000,},
    {0x00000000, 0xC1200000, 0x42480000,},
    {0x42A00000, 0x42480000, 0x42200000,},
    {0x00000000, 0x42F00000, 0x42200000,},
    {0x00000000, 0x41E00000, 0xC2480000,},
    {0x00000000, 0x42700000, 0x42480000,},
    {0x00000000, 0x42A00000, 0x43200000,},
};

Vec3f D_80971EEC[] = {
    {0x41400000, 0x3F800000, 0x40000000,},
    {0x41400000, 0x3F800000, 0x40000000,},
    {0x40000000, 0xC0C00000, 0x00000000,},
    {0x41400000, 0xC0C00000, 0xC1200000,},
    {0xC2B00000, 0x41600000, 0xC1200000,},
    {0x00000000, 0x00000000, 0x00000000,},
    {0x00000000, 0x00000000, 0x00000000,},
    {0x00000000, 0x00000000, 0x00000000,},
    {0x00000000, 0xC1200000, 0x00000000,},
    {0x00000000, 0xC1200000, 0x00000000,},
    {0x00000000, 0xC1200000, 0x00000000,},
    {0x00000000, 0xC1200000, 0x00000000,},
    {0x00000000, 0xC1200000, 0x00000000,},
    {0x00000000, 0x00000000, 0x00000000,},
    {0x00000000, 0x00000000, 0x00000000,},
};

Vec3f D_80971FA0[] = {
    {0xC2480000, 0x43200000, 0xC2200000,},
    {0xC2480000, 0x43200000, 0xC2200000,},
    {0xC1A00000, 0x42A00000, 0x42700000,},
    {0x42640000, 0x42700000, 0x42F00000,},
    {0x41D80000, 0x42A00000, 0x42700000,},
    {0xC0400000, 0x42480000, 0x428C0000,},
};

Vec3f D_80971FE8[] = {
    {0x00000000, 0x00000000, 0x00000000,},
    {0x00000000, 0x00000000, 0x00000000,},
    {0xC1200000, 0xC0A00000, 0x00000000,},
    {0x41200000, 0xC1200000, 0x40E00000,},
    {0x41A00000, 0x40A00000, 0x40000000,},
    {0x41200000, 0x40A00000, 0x40000000,},
};
Vec3f D_80972030 = {
    0xC0400000,
    0x42480000,
    0x42B40000,
};

Vec3f D_8097203C = {
    0x41200000,
    0xC1700000,
    0x40000000,
};

u32 D_80972048[] = { //generic animation header
    0x06007444, // are these segmented addresses?
    0x0600686C,
    0x060081A4,
    0x06007B90,
    0x060071EC,
    0x06007444,
    0x0600686C,
    0x060081A4,
    0x06000214,
};

u8  D_8097206C[] = {
    0x00, 0x00, 0x00, 0x02, 
    0x02, 0x02, 0x02, 0x02, 
    0x02, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
};

void EnKakasi_Destroy(Actor *thisx, GlobalContext *globalCtx) {
    EnKakasi* this = THIS;
    Collider_DestroyCylinder(globalCtx, &this->collider);
}

#if NON_EQUIVILENT
// not even close
void EnKakasi_Init(Actor *thisx, GlobalContext *globalCtx) {
    EnKakasi* this = THIS;
    //EnKakasi* thisTemp = this;
    s16 zRot;
    s16 xRot;
    //s16 getCutsceneReturn;
    //s16 cutsceneTemp2;

    s16 tempCutscene;
    //int tempCutscene; // permuter swears this is an int, but why
    s32 i;// = 0;

    Collider_InitAndSetCylinder(globalCtx, &this->collider, &this->actor, &D_80971D80);
    SkelAnime_InitSV(globalCtx, &this->skelanime, &D_060065B0, &D_06000214, 0, 0, 0);

    this->unk250 = ((this->actor.params >> 8) & 0xFF) * 20.0f;
    if (this->unk250 < 40.0f) {
        this->unk250 = 40.0f;
    }

    //zRot = this->actor.world.rot.z;
    //xRot = this->actor.world.rot.x;
    this->actor.world.rot.z = 0;
    this->actor.targetMode = 0;
    //this->unkHeight = (((f32) zRot * 20.0f) + 60.0f);
    this->unkHeight = ((this->actor.world.rot.z * 20.0f) + 60.0f);
    //if (((s32) xRot > 0) && ((s32) xRot < 8)) {
    if ((this->actor.world.rot.x > 0) && (this->actor.world.rot.x < 8)) {
        this->actor.targetMode = this->actor.world.rot.x--;
    }

    // combined with the temp below, aligns the Actorcutscene_getadd call and gSaveContext load
    if (!gSaveContext.perm.weekEventReg) { }  

    this->unk194 = (this->actor.params & 1);
    this->actor.world.rot.x = 0;
    this->actor.flags |= 0x400;
    this->actor.colChkInfo.mass = 0xFF;
    this->actor.shape.rot.y = this->actor.world.rot.y;
    Actor_SetScale(thisx, 0.01f);

    for(tempCutscene = this->actor.cutscene; tempCutscene != -1; ++i ){
          this->actorCutscenes[i] = tempCutscene;
          tempCutscene = ActorCutscene_GetAdditionalCutscene(tempCutscene);
    }
    //tempCutscene = this->actor.cutscene;
    ////cutsceneTemp2 = (s16) tempCutscene;
    //if (tempCutscene != -1) {
        //do {
          //thisTemp->actorCutscenes[0] = getCutsceneReturn;
          //getCutsceneReturn = ActorCutscene_GetAdditionalCutscene( getCutsceneReturn);
          ////cutsceneTemp2 = getCutsceneReturn;
          //thisTemp += 2; // wat? actor* + 2
        //} while (getCutsceneReturn != -1);
        
    //}
    //for(i = 0, tempCutscene = this->actor.cutscene; tempCutscene != -1; ++i ){
    xRot = gSaveContext.perm.weekEventReg[79];
    if (this->unk194 != 0) {
        this->unk194 = 2;
        this->unk250 = 80.0f;
        func_80971794(this);
        //if ((gSaveContext.perm.weekEventReg[79] & 8) == 0) {
        if ((xRot & 8) == 0) {
            Actor_SetHeight(thisx, 60.0f);
            this->actionFunc = func_8096F88C;
            if ((gSaveContext.perm.weekEventReg[83] & 1) == 0) {
                func_8096FDE8(this);
                return;
            }
            func_8096FC8C(this);
            return;
        }
        //func_80971794(this);
        return;
    }
    func_80971794(this);
}
#else
#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kakasi_0x8096F5E0/EnKakasi_Init.asm")
#endif

void func_8096F800(EnKakasi *this, s32 offset) {   
    this->unk1A0 = offset;
    this->animationFrameTarget = SkelAnime_GetFrameCount(D_80972048[this->unk1A0]);
    SkelAnime_ChangeAnim(&this->skelanime, D_80972048[this->unk1A0],
         1.0f, 0.0f, this->animationFrameTarget, 
         D_8097206C[this->unk1A0], -4.0f);
}

// action func
void func_8096F88C(Actor *this, GlobalContext *globalCtx) {
    func_8013A530( this, globalCtx, 0x7, 
      &globalCtx->state.input[1].press.errno, &globalCtx->view.gfxCtx, 280.0f, 1800.0f, -1);
}

void func_8096F8D8(EnKakasi *this) {
    if ((this->unk1A0 == 1) || (this->unk1A0 == 5)) {
        if ((func_801378B8(&this->skelanime, 1.0f) != 0) 
          || (func_801378B8(&this->skelanime, 8.0f) != 0)) {
            Audio_PlayActorSound2(&this->actor, 0x286A);
        }
    }
    if ((this->unk1A0 == 2) || (this->unk1A0 == 7)) {
        if ((func_801378B8(&this->skelanime, 4.0f) != 0) 
          || (func_801378B8(&this->skelanime, 8.0f) != 0)) {
            Audio_PlayActorSound2(&this->actor, 0x286A);
        }
        if ((func_801378B8(&this->skelanime, 1.0f) != 0) 
          || (func_801378B8(&this->skelanime, 9.0f) != 0) 
          || (func_801378B8(&this->skelanime, 16.0f) != 0)) {
            Audio_PlayActorSound2(&this->actor, 0x1847);
        }
        if (func_801378B8(&this->skelanime, 18.0f) != 0) {
            Audio_PlayActorSound2(&this->actor, 0x286B);
        }
    }
    if ((this->unk1A0 == 3) || (this->unk1A0 == 4)) {
        if (func_801378B8( &this->skelanime, 1.0f) != 0) {
            Audio_PlayActorSound2(&this->actor, 0x286E);
        }
    }
}

void func_8096FA18(EnKakasi *this, GlobalContext *globalCtx) {
    Actor* player = PLAYER;
    s16 sceneNum;

    sceneNum = globalCtx->sceneNum;
    if (sceneNum == 0x34) {
        player->world.pos.x = -50.0f;
        player->world.pos.z = 155.0f;
    } else if (sceneNum == 0x29) {
        player->world.pos.x = 60.0f;
        player->world.pos.z = -190.0f;
    }

    Math_SmoothScaleMaxMinS(&player->shape.rot.y, (this->actor.yawTowardsPlayer + 0x8000), 5, 0x3E8, 0);
}

#if NON-MATCHING
// the end functions lack prototypes, think the remaining non-matching is caused by that
void func_8096FAAC(EnKakasi *this, GlobalContext* globalCtx) {
    f32 magicNum = 0.40000000596;
    //Vec3f* ptrUnk214 = &this->unk214;
    //Vec3f* ptrUnk220;// = &this->unk214;
    f32 tempUnk214X;// = this->unk214.x;
    f32 tempUnk220X;// = 

    if (this->cutsceneCamera != 0) {
        tempUnk214X = this->unk214.x;
        Math_SmoothScaleMaxF(&tempUnk214X, this->unk238.x, magicNum, 4.0f);
        //Math_SmoothScaleMaxF(&this->unk214.x, this->unk238.x, magicNum, 4.0f);
        Math_SmoothScaleMaxF(&this->unk214.y, this->unk238.y, magicNum, 4.0f);
        Math_SmoothScaleMaxF(&this->unk214.z, this->unk238.z, magicNum, 4.0f);
        //dummy_permuter_label_func_8096FAAC: ;
        //Math_SmoothScaleMaxF(&ptrUnk214->x, this->unk238.x, magicNum, 4.0f);
        //Math_SmoothScaleMaxF(&ptrUnk214->y, this->unk238.y, magicNum, 4.0f);
        //Math_SmoothScaleMaxF(&ptrUnk214->z, this->unk238.z, magicNum, 4.0f);
        //ptrUnk220 = &this->unk220;
        tempUnk220X = this->unk220.x;
        Math_SmoothScaleMaxF(&tempUnk220X, this->unk244.x, magicNum, 4.0f);
        //Math_SmoothScaleMaxF(&this->unk220.x, this->unk244.x, magicNum, 4.0f);
        Math_SmoothScaleMaxF(&this->unk220.y, this->unk244.y, magicNum, 4.0f);
        Math_SmoothScaleMaxF(&this->unk220.z, this->unk244.z, magicNum, 4.0f);
        //Math_SmoothScaleMaxF(&ptrUnk220->x, this->unk244.x, magicNum, 4.0f);
        //Math_SmoothScaleMaxF(&ptrUnk220->y, this->unk244.y, magicNum, 4.0f);
        //Math_SmoothScaleMaxF(&ptrUnk220->z, this->unk244.z, magicNum, 4.0f);
        
        Math_SmoothScaleMaxF(&this->unk20C, this->unk210, 0.3f, 10.0f);
        //func_8016970C(globalCtx, this->cutsceneCamera, this->unk220.x, this->unk214.x);
        func_8016970C(globalCtx, this->cutsceneCamera, tempUnk220X, tempUnk214X);
        //func_8016970C(globalCtx, this->cutsceneCamera, ptrUnk220->x, ptrUnk214->x);
        func_80169940(globalCtx, this->cutsceneCamera, this->unk20C);
    }
}
#else
#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kakasi_0x8096F5E0/func_8096FAAC.asm")
#endif

void func_8096FBB8(EnKakasi* this, GlobalContext* globalCtx) {
    if ((globalCtx->msgCtx.unk12048 == 0) || (globalCtx->msgCtx.unk12048 == 1) || (globalCtx->msgCtx.unk12048 == 2) 
      || (globalCtx->msgCtx.unk12048 == 3) || (globalCtx->msgCtx.unk12048 == 4)) {
        this->unk190++;
    }
    if ((this->unk190 != 0) && (this->unk1A0 != 1)) {
        func_8096F800(this, 1);
    }
    if (this->unk190 >= 9) {
        this->unk190 = 8;
    }
    if (this->unk190 != 0) {
        Math_SmoothScaleMaxF(&this->skelanime.animPlaybackSpeed, 1.0f, 0.1f, 0.2f);
        this->actor.shape.rot.y = this->actor.shape.rot.y + 0x800;
    }
}

// init extension
void func_8096FC8C(EnKakasi *this) {
    func_8096F800(this, 7);
    this->actionFunc = func_8096FCC4;
}


// action func
void func_8096FCC4(Actor* thisx, GlobalContext* globalCtx) {
    ActorPlayer* player = PLAYER;
    EnKakasi* this = THIS;

    if ((gSaveContext.extra.unk10 != -4) && (gSaveContext.extra.unk10 != -8)) {
        if ((gSaveContext.perm.time != 0x4000) && (gSaveContext.perm.time != 0xC000) 
          && ((gSaveContext.owl.unk1 & 0x80) == 0)) {
            if (this->actor.textId == 0) {
                this->actor.textId = 0x1653;
                gSaveContext.perm.weekEventReg[0x53] &= 0xFE;
                this->unk1AC = 5;
                player->stateFlags1 |= 0x20;
                this->actor.flags |= 0x10000;
            }
            if (func_800B84D0(&this->actor, globalCtx) != 0) {
                player->stateFlags1 &= ~0x20;
                this->unk196 =  2;
                this->actor.flags &= 0xFFFEFFFF;
                this->actionFunc = func_8097006C;
                return;
            }
            func_800B8500(&this->actor, globalCtx, 9999.90039062f, 9999.90039062f, -1);
        }
    }
}

// init extension
void func_8096FDE8(EnKakasi* this) {
    this->unk196 = 0;
    this->actionFunc = func_8096FE00;
}

// action func
void func_8096FE00(Actor *thisx, GlobalContext *globalCtx) {
    //EnKakasi* this = THIS; // matches without, with stack is too big
    u32 saveContextDay;
    s16 passedValue1;
    s16 passedValue2;

    saveContextDay = gSaveContext.perm.day;
    thisx->textId = 0x1644;
    if (func_800B8718(thisx, globalCtx) != 0) {
        THIS->skelanime.animPlaybackSpeed = 1.0f;
        func_809705E4(thisx, globalCtx);
        return;
    }
    if (func_800B84D0(thisx, globalCtx) != 0) {
        THIS->skelanime.animPlaybackSpeed = 1.0f;
        func_80970008(THIS);
        return;
    }
    if ((globalCtx->actorCtx.unk5 & 4) != 0) {
        func_800B8898(globalCtx, thisx, &passedValue1, &passedValue2);
        if ((thisx->projectedPos.z > -20.0f) 
          && ((s32) passedValue1 > 0) && ((s32) passedValue1 < 0x140) 
          && ((s32) passedValue2 > 0) && ((s32) passedValue2 < 0xF0) && (THIS->unk1A0 != 1)) {
            func_8096F800(thisx, 1);
            THIS->skelanime.animPlaybackSpeed = 2.0f;
        }
    } else if (func_8012403C(globalCtx) == 0xE) {
        if (THIS->unk1A0 != 1) {
            func_8096F800(thisx, 1);
            THIS->skelanime.animPlaybackSpeed = 2.0f;
        }
    } else if ((saveContextDay == 3) && (gSaveContext.perm.isNight != 0)) {
        THIS->skelanime.animPlaybackSpeed = 1.0f;
        if (THIS->unk1A0 != 1) {
            func_8096F800(thisx, 1);
        }
    } else if (THIS->unk1A0 != 8) {
        func_8096F800(thisx, 8);
    }
    if (thisx->xzDistToPlayer < 120.0f) {
        func_800B8614(thisx, globalCtx, 100.0f);
        func_800B874C(thisx, globalCtx, 0x42C80000, 0x42A00000);
    }
}


void func_80970008(EnKakasi *this) {
    if (this->unk1A0 != 1) {
        func_8096F800(this, 1);
    }

    this->unk1AC = 5;
    this->unk196 = 1;
    func_8096F800(this, 3);
    this->actionFunc = func_8097006C;
}

// action func
// goes off if you cancel a song but kinda big?
#if NON_EQUIVALENT
// there is some out of order instructions around saveContextDay
// also the control flow gets confused near 70% down
void func_8097006C(Actor* this, GlobalContext *globalCtx) {
    // prob save context var
    //SaveContext* sCtx;// = &gSaveContext;
    u32 saveContextDay = gSaveContext.perm.day; 
    u32 saveContextDay2;
    f32 currentAnimeFrame = this->skelanime.animCurrentFrame;

    Math_SmoothScaleMaxMinS(&this->actor.shape.rot.y, this->actor.yawTowardsPlayer, 5, 0x7D0, 0);
    if ((this->actor.textId != 0x1644) && (this->animationFrameTarget <= currentAnimeFrame) && (this->unk1A0 == 7)) {
        func_8096F800(this, 3);
    if ((this->actor.textId == 0x1651) || (this->actor.textId == 0x1659)) {
        if ((this->animationFrameTarget <= currentAnimeFrame) && (this->unk1A0 != 3)) {
            if (++this->unk1A4 >= 2) {
                this->unk1A4 = 0;
                func_8096F800(this, 3);
            }
        }
    }

    if ((this->unk1A8 == 2) && (this->unk196 == 2)) {
        func_800B7298(globalCtx, &this->actor, 0x49);
        this->unk1A8 = 0;
    }

    if ((this->unk1AC == func_80152498(&globalCtx->msgCtx)) && (func_80147624(globalCtx) != 0)) {
        func_801477B4(globalCtx);
        if (this->unk1AC == 5) {
            if ((this->unk196 == 2) && (this->actor.textId == 0x1647)) {
                func_800B7298(globalCtx, &this->actor, 6);
            }

            if (this->actor.textId == 0x1653) {
                // this is the only way i've found to get savecontext to load twice and use the right v
                saveContextDay2 = gSaveContext.perm.day; // I hope this is a fake match

                // 1A0 loads AFTER globalcontext from above in vanilla
                if (this->unk1A0 != 1) {
                    func_8096F800(this, 1);
                }
        
                //if ((gSaveContext.perm.day == 3) && (gSaveContext.perm.isNight != 0)) {
                if ((saveContextDay2 == 3) && (gSaveContext.perm.isNight != 0)) {
                    this->actor.textId = 0x164F;
                } else if (gSaveContext.perm.isNight != 0) {
                    this->actor.textId = 0x164E;
                } else {
                    this->actor.textId = 0x1645;
                }

                func_80151938(globalCtx, this->actor.textId);
                return;

            } else if ((this->actor.textId == 0x165D) || (this->actor.textId == 0x165F)
              || (this->actor.textId == 0x1660) || (this->actor.textId == 0x1652)) {
                goto dummy_label_845001; dummy_label_845001: ;
                func_800B7298(globalCtx, (Actor *) this, (u8)4U);
                if (ActorCutscene_GetCurrentIndex() == 0x7C) {
                    ActorCutscene_Stop(0x7C);
                    ActorCutscene_SetIntentToPlay(this->actorCutscenes[0]);
                    this->actionFunc = func_80970F20;
                    return;
                } else { 
                    if (ActorCutscene_GetCanPlayNext(this->actorCutscenes[0]) == 0) {
                        ActorCutscene_SetIntentToPlay(this->actorCutscenes[0]);
                        this->actionFunc = func_80970F20;
                        return;
                    } else {
                        ActorCutscene_StartAndSetUnkLinkFields(this->actorCutscenes[0], &this->actor);
                        this->cutsceneCamera = ActorCutscene_GetCurrentCamera(this->actor.cutscene);
                        this->actionFunc = func_80970F20;
                        return;
                    }
                }
            } else if ((this->actor.textId == 0x1645) || (this->actor.textId == 0x164E)) {
                this->actor.textId = 0x1650;
                if (this->unk1A0 != 1) {
                    func_8096F800(this, 1);
                }
                this->unk1AC = 4;
            } else if (this->actor.textId == 0x1644) {
                if (this->unk1A0 != 1) {
                    func_8096F800(this, 1);
                }
                if (gSaveContext.perm.isNight != 0) {
                    this->actor.textId = 0x164E;
                } else {
                    this->actor.textId = 0x1645;
                }
            } else if (this->actor.textId == 0x164F) {
                if (this->unk1A0 != 1) {
                    func_8096F800(this, 1);
                }
                this->actor.textId = 0x165A;
            } else if (this->actor.textId == 0x1651) {
                if (this->unk1A0 != 1) {
                    func_8096F800(this, 1);
                }
                this->actor.textId = 0x1654;
            } else if (this->actor.textId == 0x1654) {
                this->actor.textId = 0x1655;
            } else if (this->actor.textId == 0x1655) {
                this->actor.textId = 0x1656;
                this->unk1AC = 4;
            } else if (this->actor.textId == 0x1658) {
                this->actor.textId = 0x1659;
            } else if (this->actor.textId == 0x165A) {
                this->actor.textId = 0x165B;
            } else if (this->actor.textId == 0x165B) {
                this->actor.textId = 0x165C;
                this->unk1AC = 4;

            // around here the controll flow gets confused
            } else if (this->actor.textId == 0x165E) {
                this->actor.textId = 0x165F;
                //return;
            }else{
                func_8096FDE8(this);
                //return;
            }
                //if (this->actor.textId == 0x165E) {
                    //this->actor.textId = 0x165F;
                    //return;
                //}else{
                    //func_8096FDE8(this);
                    //return;
                //}
                    //return;
        } else {
            this->unk1AC = 5;

            if (globalCtx->msgCtx.unk12022 == 1) {
                func_8019F208(); // play selected sfx and call another function
                //temp_v1_2 = this->actor.textId;
                if (this->actor.textId == 0x1656) {
                    this->actor.textId = 0x1658;
                } else if (this->actor.textId == 0x165C) {
                    this->actor.textId = 0x165E;
                } else if ((saveContextDay == 3) && (gSaveContext.perm.isNight != 0)) {
                    this->actor.textId = 0x164F;
                } else {
                    this->actor.textId = 0x1652;
                }
                func_8096F800(this, 2);
            } else {
                func_8019F230();
                //temp_v1_3 = this->actor.textId;
                if (this->actor.textId == 0x1656) {
                    this->actor.textId = 0x1657;
                } else if (this->actor.textId == 0x165C) {
                    this->actor.textId = 0x165D;
                } else {
                    this->actor.textId = 0x1651;
                }
                this->unk1A4 = 0;
                if (this->unk1A0 != 0) {
                    func_8096F800(this, 0);
                }
            }
        }
        func_80151938(globalCtx, this->actor.textId);
    }
}
#else
#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kakasi_0x8096F5E0/func_8097006C.asm")
#endif

void func_809705E4(EnKakasi* this, GlobalContext* globalCtx) {
    this->actor.textId = 0x1646;
    func_801518B0(globalCtx, this->actor.textId, &this->actor);
    this->cutsceneCamera = 0;
    this->unk20C = 0.0f;
    this->unk210 = 60.0f;
    func_8096F800(this, 4);
    this->unk196 = 2;
    this->actionFunc = func_80970658;
}

//action func
void func_80970658(Actor* thisx, GlobalContext* globalCtx) {
    EnKakasi* this = THIS;

    if ((func_80152498(&globalCtx->msgCtx) == 5) && (func_80147624(globalCtx) != 0)) {
        func_80152434(globalCtx, 0x35);
        this->unk1A8 = 0;
        if (ActorCutscene_GetCurrentIndex() == 0x7C) {
            ActorCutscene_Stop((u16)0x7C);
            ActorCutscene_SetIntentToPlay((s16) this->actorCutscenes[0]);
            this->actionFunc = func_80970740;
            return;
        }
        if (ActorCutscene_GetCanPlayNext((s16) this->actorCutscenes[0]) == 0) {
            ActorCutscene_SetIntentToPlay((s16) this->actorCutscenes[0]);
            this->actionFunc = func_80970740;
            return;
        }
        this->unk1A8 = 1;
        ActorCutscene_StartAndSetUnkLinkFields((s16) this->actorCutscenes[0], &this->actor);
        this->cutsceneCamera = ActorCutscene_GetCurrentCamera(this->actor.cutscene);
        Math_Vec3f_Copy(&this->unk22C, &this->actor.home.pos);
        this->actionFunc = func_80970740;
    }
}

// action func: each frame of songteaching?
void func_80970740(Actor* thisx, GlobalContext* globalCtx) {
    EnKakasi* this = THIS;
    Vec3f tempVec;

    func_8096FA18(this, globalCtx);
    Math_SmoothScaleMaxMinS(&this->actor.shape.rot.y, this->actor.home.rot.y, 1, 0xBB8, 0);
    if (this->unk1A8 == 0) {
        if (ActorCutscene_GetCurrentIndex() == 0x7C) {
            ActorCutscene_Stop(0x7C);
            ActorCutscene_SetIntentToPlay(this->actorCutscenes[0]);
            return;
        }
        if (ActorCutscene_GetCanPlayNext(this->actorCutscenes[0]) == 0) {
            ActorCutscene_SetIntentToPlay(this->actorCutscenes[0]);
            return;
        }
        ActorCutscene_StartAndSetUnkLinkFields(this->actorCutscenes[0], &this->actor);
        this->cutsceneCamera = ActorCutscene_GetCurrentCamera(this->actor.cutscene);
        Math_Vec3f_Copy(&this->unk22C, &this->actor.home.pos);
        this->unk1A8 = 1;
        this->unk1A8 = 1;
    }
  
    if (this->unk1A8 == 1) {
        this->unk22C.y = this->actor.home.pos.y + 50.0f;
        this->unk238.x = D_80971DCC[(s16)this->unk190].x;
        this->unk238.y = D_80971DCC[(s16)this->unk190].y;
        this->unk238.z = D_80971DCC[(s16)this->unk190].z;

        Math_Vec3f_Copy(&tempVec,  &this->unk238);
        func_8010CAA0(&this->actor.home.pos, &tempVec, &this->unk238, 1);
        Math_Vec3f_Copy(&this->unk244, &this->unk22C);
        Math_Vec3f_Copy(&this->unk214, &this->unk238);
        Math_Vec3f_Copy(&this->unk220, &this->unk244);
        func_8096FAAC(this, globalCtx);
        func_8096FBB8(this, globalCtx);

        if (globalCtx->msgCtx.unk1202A == 4) {
            this->unk190 = 0;
            this->unk1A4 = 0;
            ActorCutscene_Stop(this->actorCutscenes[0]);
            Audio_PlayActorSound2(&this->actor, 0x3A3F);
            if (!this){}
            this->unk196 = 2;
            this->cutsceneCamera = 0;
            this->actor.textId = 0x1647;
            this->unk1A8 = 2;
            this->unk1AC = 5;
            func_8096F800(this, 0);
            this->actionFunc = func_8097006C;

        } else if (globalCtx->msgCtx.unk1202A == 3) {
            this->unk192 = 0x1E;
            this->skelanime.animPlaybackSpeed = 2.0f;
            func_8096F800(this, 2);
            this->actionFunc = func_80970978;
        }
    }
}

// action func
void func_80970978(Actor* thisx, GlobalContext *globalCtx) {
    EnKakasi* this= THIS;
    f32 tempAnimeFrame;
    s16 temp192;

    temp192 = this->unk192;
    tempAnimeFrame = this->skelanime.animCurrentFrame;
    if ((temp192 == 0) && (this->unk1A0 != 4)) {
        func_8096F800(this, 4);
        this->skelanime.animPlaybackSpeed = 2.0f;
        temp192 = this->unk192;
    }
    if ((temp192 == 0) && (this->unk1A0 == 4) && (this->animationFrameTarget <= tempAnimeFrame)) {
        func_80970A10(this, globalCtx);
    }
}

void func_80970A10(EnKakasi *this, GlobalContext *globalCtx) {

    ActorCutscene_Stop(this->actorCutscenes[0]);
    globalCtx->msgCtx.unk1202A = 4;
    this->unk190 = 0;
    this->unk1A4 = 0;
    func_8096F800(this, 2);
    this->cutsceneCamera = 0;
    this->unk1AC = 5;
    this->unk1A8 = 1;
    this->actionFunc = func_80970A9C;
    this->unk20C = 0.0f;
    this->unk210 = 60.0f;
}

// action func
//  think this is the post-song teaching action func
// NON-MATCHING: stack too big, bit of regalloc
#if NON-MATCHING
void func_80970A9C(Actor* thisx, GlobalContext *globalCtx) {
    EnKakasi* this = THIS;
    ActorPlayer* player = PLAYER;
    f32 tempAnimFrame;
    Vec3f vec3fCopy;
    u16 pad;
    u16 pad1;
    u16 tempTextId;
    //u32 tempStaticId;

    tempAnimFrame = this->skelanime.animCurrentFrame;
    Math_SmoothScaleMaxMinS(&this->actor.shape.rot.y, this->actor.home.rot.y, 1, 0xBB8, 0);
    Math_SmoothScaleMaxMinS(&player->actor.shape.rot.y, (this->actor.yawTowardsPlayer + 0x8000), 5, 0x3E8, 0);
    // this is setup, only goes off first frame
    if ((s16) this->unk190 == 0) {
        func_801477B4(globalCtx);
        func_800B7298(globalCtx, &this->actor, 0x56U);
        this->actor.textId = 0x1648u;
        func_801518B0(globalCtx, (this->actor.textId), &this->actor);
        this->unk1A8 = 0;
        this->unk190 = 1;
    }
    if ((this->actor.textId == 0x1648) && (this->unk1A0 == 2) && (this->animationFrameTarget <= tempAnimFrame)) {
    //if ((this->actor.textId == 0x1648) && (this->unk1A0 == 2) && (this->animationFrameTarget <= this->skelanime.animCurrentFrame)) {
        this->unk1A4++;
        if (this->unk1A4>= 2) {
            func_8096F800(this, 0); // reach this point when he finishes dancing idle
        }
    }
    if ((this->actor.textId == 0x164B) && (this->unk1A0 == 0) && (this->animationFrameTarget <= tempAnimFrame)) {
    //if ((this->actor.textId == 0x164B) && (this->unk1A0 == 0) && (this->animationFrameTarget <= this->skelanime.animCurrentFrame)) {
        this->unk1A4++;
        if (this->unk1A4 >= 2) {
            func_8096F800(this, 3);
        }
    }
    if (this->unk1A8 == 0) {
        if (ActorCutscene_GetCurrentIndex() == 0x7C) {
            ActorCutscene_Stop((u16)0x7C);
            ActorCutscene_SetIntentToPlay(this->actorCutscenes[0]);
            return;
        }
        if (ActorCutscene_GetCanPlayNext(this->actorCutscenes[0]) == 0) {
            ActorCutscene_SetIntentToPlay(this->actorCutscenes[0]);
            return;
        }
        Math_Vec3f_Copy(&this->unk22C, (Vec3f *) &this->actor.home.pos);
        ActorCutscene_StartAndSetUnkLinkFields(this->actorCutscenes[0], &this->actor);
        this->cutsceneCamera = ActorCutscene_GetCurrentCamera(this->actor.cutscene);
        func_800B7298(globalCtx, &this->actor, 0x56);
        this->unk1A8 = 1;
    }
    if (this->cutsceneCamera != 0) {
        this->unk22C.y = this->actor.home.pos.y + 50.0f;
        func_8096FA18(this, globalCtx);
        this->unk238.x = D_80971FA0[this->unk190].x;
        this->unk238.y = D_80971FA0[this->unk190].y;
        this->unk238.z = D_80971FA0[this->unk190].z;
        //this->unk238 = D_80971FA0[this->unk190];
        Math_Vec3f_Copy(&vec3fCopy, &this->unk238);
        func_8010CAA0(&this->actor.home.pos, &vec3fCopy, &this->unk238, 1);
        this->unk244.x = D_80971FE8[(s16) this->unk190].x + this->unk22C.x;
        this->unk244.y = D_80971FE8[(s16) this->unk190].y + this->unk22C.y;
        this->unk244.z = D_80971FE8[(s16) this->unk190].z + this->unk22C.z;
        Math_Vec3f_Copy(&this->unk214, &this->unk238);
        Math_Vec3f_Copy(&this->unk220, &this->unk244);
    }
    func_8096FAAC(this, globalCtx);
      //&& ((s16) this->unk1AC == func_80152498(&globalCtx->msgCtx)) 
    if ((this->unk1A8 != 0) 
      && ((func_80152498(&globalCtx->msgCtx) == (this->unk1AC)) ) 
      && (func_80147624(globalCtx) != 0)) {
        func_801477B4(globalCtx);
        if (this->unk1AC == 5) {
            this->unk190++;
            if ((s32) (s16) this->unk190 >= 6) {
                this->unk190 = 5;
            }
            tempTextId = this->actor.textId;
            if (tempTextId == 0x1648) {
                func_800B7298(globalCtx, &this->actor, 7);
                this->actor.textId = 0x1649;
                if (this->unk1A0 != 0) {
                    func_8096F800(&this->actor, 0);
                }
                tempTextId = this->actor.textId;
            } else if (tempTextId == 0x1649) {
                this->actor.textId = 0x1660;
                this->unk1AC = 4;
                tempTextId = this->actor.textId;
            } else if (tempTextId == 0x164A) {
                this->actor.textId = 0x164B;
                tempTextId = this->actor.textId;
            } else if (tempTextId == 0x164B) {
                this->actor.textId = 0x164C;
                func_8096F800(this, 4);
                tempTextId = this->actor.textId;
            } else {
                if ((tempTextId == 0x164C) 
                    || (tempTextId == 0x1661)){
                    func_80971440(this);
                    return;
                }
            }
        } else {
            this->unk1AC = 5;
            // 16929 / 4908 / (12021)
            if (globalCtx->msgCtx.unk12022 == 1) {
                func_8019F208(); // play selected sfx and call another function
                this->actor.textId = 0x164A;
                tempTextId = this->actor.textId;
            } else {
                func_8019F230();
                this->actor.textId = 0x1661;
                tempTextId = this->actor.textId;
            }
        }
        func_80151938(globalCtx, tempTextId);
    }
} // */
#else
#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kakasi_0x8096F5E0/func_80970A9C.asm")
#endif


// action func
void func_80970F20(Actor* thisx, GlobalContext *globalCtx) {
    EnKakasi* this = THIS;
    u32 currentDay = gSaveContext.perm.day;

    this->unk196 = 3;
    if (ActorCutscene_GetCurrentIndex() == 0x7C) {
        ActorCutscene_Stop(0x7C);
        ActorCutscene_SetIntentToPlay(this->actorCutscenes[0]);
        return;
    }
    if (ActorCutscene_GetCanPlayNext(this->actorCutscenes[0]) == 0) {
        ActorCutscene_SetIntentToPlay(this->actorCutscenes[0]);
        return;
    }
    ActorCutscene_StartAndSetUnkLinkFields(this->actorCutscenes[0], &this->actor);
    this->cutsceneCamera = ActorCutscene_GetCurrentCamera(this->actor.cutscene);
    if ((currentDay == 3) && (gSaveContext.perm.isNight != 0)) {
        func_80971440(this);
        return;
    }
    func_801A2BB8(0x3E);
    func_80970FF8(this);
}

void func_80970FF8(EnKakasi *this) {
    this->unk190 = 0;
    this->unk1A4 = 0;
    this->unk20C = 0.0f;
    this->unk210 = 60.0f;
    func_8096F800(this, 4);
    Math_Vec3f_Copy(&this->unk22C, &this->actor.home.pos);
    func_8016566C(0xB4);
    this->actionFunc = func_80971064;
}

//action func
// guessing since this ends with a worthless action func it leads to the actor leaving
// todo convert this to Actor* thisx
void func_80971064(EnKakasi* this, GlobalContext* globalCtx) {
    //EnKakasi* this= THIS; // matches without, leaving as EnKakasi* this for now
    f32 currentFrame;
    Vec3f localVec3f;
    ActorPlayer* player;

    currentFrame = this->skelanime.animCurrentFrame;
    func_8096FA18(this, globalCtx);
    Math_SmoothScaleMaxMinS(&this->actor.shape.rot.y, this->actor.home.rot.y, 1, 0xBB8, 0);
    this->unk22C.y = this->actor.home.pos.y + 50.0f;

    this->unk238.x = D_80971E38[this->unk190].x;
    this->unk238.y = D_80971E38[this->unk190].y;
    this->unk238.z = D_80971E38[this->unk190].z;
    Math_Vec3f_Copy(&localVec3f, &this->unk238);
    func_8010CAA0(&this->actor.home, &localVec3f, &this->unk238, 1);

    // we assign unk244 here but then under the next condition we set unk220->unk244?
    // bug? think this condition was supposed to important, and was optimized out
    if (1) {
        this->unk244.x = D_80971EEC[this->unk190].x + this->unk22C.x;
        this->unk244.y = D_80971EEC[this->unk190].y + this->unk22C.y;
        this->unk244.z = D_80971EEC[this->unk190].z + this->unk22C.z;
    }
    if ((this->unk190 != 6) && (this->unk190 != 7)) {
        Math_Vec3f_Copy(&this->unk214, &this->unk238);
        Math_Vec3f_Copy(&this->unk220, &this->unk244);
    }
    if ((this->unk190 >= 7) && (this->unk190 != 0xE)) {
        this->actor.shape.rot.y = this->actor.shape.rot.y + 0x800;
    }

    func_8096FAAC(this, globalCtx);
    switch (this->unk190) {
        case 0:
            this->unk204 = 0x28;
            this->unk190++;
            return;
        case 1:
            if ((this->unk204 == 0) && (this->animationFrameTarget <= currentFrame)) {
                this->unk204 = 0x14;
                this->unk190++;
                func_8096F800(this, 1);
            }
            return;
        case 2:
            if (this->unk204 == 0) {
                this->unk204 = 0x14;
                this->unk190++;
            }
            return;
        case 3:
            if (this->unk204 == 0) {
                this->unk204 = 0x14;
                this->unk190++;
            }
            return;
        case 4:
            if (this->unk204 == 0) {
                this->unk204 = 0x14;
                this->unk190++;
            }
            return;
        case 5:
            if (this->unk204 == 0) {
                this->unk204 = 0xF;
                this->unk190++;
            }
            return;
        case 6:
            if (this->unk204 == 0) {
                this->unk204 = 0xF;
                this->unk190++;
            }
            return;
        case 7:
            if (this->unk204 == 0) {
                this->unk204 = 0xA;
                this->unk190++;
            }  
            return;
        case 8:
            if (this->unk204 == 0) {
                this->unk190++;
                this->unk204 = 0xA;
                if (this->unk190 == 0xE) {
                    func_800B7298(globalCtx, &this->actor, 0x49);
                    func_80165690();
                    this->unk204 = 0x14;
                }
            }
            return;
        case 14:
            Math_SmoothScaleMaxMinS(&this->actor.shape.rot.y, this->actor.yawTowardsPlayer, 5, 0x3E8, 0);
            if (this->unk204 == 0) {
                player = PLAYER;
                func_80169DCC(globalCtx, 0, func_80130784(0) & 0xFFFF, 
                    player->unk3CE, 0xBFF, &player->unk3C0, player->unk3CC);
                func_80169EFC(globalCtx);

                if(0){}
                if ((gSaveContext.perm.time >= 0xC001) || (gSaveContext.perm.time < 0x4000)) {
                    gSaveContext.perm.time = 0x4000;
                    gSaveContext.extra.unk10 = -4;
                    gSaveContext.owl.unk2 = gSaveContext.owl.unk2 | 0x80;
                } else {
                    gSaveContext.perm.time = 0xC000;
                    gSaveContext.extra.unk10 = -8;
                }
                gSaveContext.perm.weekEventReg[0x53] |= 1;
                this->unk190 = 0;
                this->actionFunc = func_80971430;
            }
            return;
    }
    return;
}

// ? do nothing action func?
void func_80971430(Actor* this, GlobalContext* globalCtx) { }

void func_80971440(EnKakasi *this){
    if (this->unk1A0 != 1) {
        func_8096F800(&this->actor, 1);
    }
    this->unk190 = 0;
    this->unk1A4 = 0;
    this->unk210 = 60.0f;
    this->unk20C = 60.0f;
    Math_Vec3f_Copy(&this->unk22C,  &this->actor.home.pos);
    this->unk196 = 4;
    this->actionFunc = func_809714BC;
}

#if NON-matching
// action func
// NON-MATCHING: stack and regalloc
// if you use a temp pointer for D_8097203C, the regalloc is gone but can't align stack
void func_809714BC(Actor* this, GlobalContext *globalCtx) {
    s8 pad1[2];
    Vec3f localVec3f;
    Vec3f* D_8097203CPtr;
    s8 pad[1];
    //s8 pad[2];

    if (this->cutsceneCamera != 0) {
        this->unk22C.y = this->actor.home.pos.y + 50.0f;
        this->unk238.x = D_80972030.x;
        this->unk238.y = D_80972030.y;
        this->unk238.z = D_80972030.z;
        Math_Vec3f_Copy( &localVec3f, &this->unk238);
        func_8010CAA0(&this->actor.home.pos,  &localVec3f, &this->unk238, 1);
        // using ptr fixes regalloc up here
        D_8097203CPtr = &D_8097203C;
        this->unk244.x = (*D_8097203CPtr).x + this->unk22C.x;
        this->unk244.y = (*D_8097203CPtr).y + this->unk22C.y;
        this->unk244.z = (*D_8097203CPtr).z + this->unk22C.z;
        //this->unk244.x = D_8097203C.x + this->unk22C.x;
        //this->unk244.y = D_8097203C.y + this->unk22C.y;
        //this->unk244.z = D_8097203C.z + this->unk22C.z;
        Math_Vec3f_Copy(&this->unk214, &this->unk238);
        Math_Vec3f_Copy(&this->unk220, &this->unk244);
        func_8096FAAC(this, globalCtx);
    }

    if (this->unk1A4 < 0xF) {
        this->unk1A4++;
        return;
    }

    this->actor.shape.rot.y = this->actor.shape.rot.y + 0x3000;
    Math_SmoothScaleMaxMinS(&this->unk190, 0x1F4, 5, 0x32, 0);
    if ((globalCtx->unk18840 & 3) == 0) {
        Math_Vec3f_Copy( &localVec3f,  &this->actor.world.pos);
        localVec3f.y = this->actor.floorHeight;
        localVec3f.x += randPlusMinusPoint5Scaled(2.0f);
        localVec3f.z += randPlusMinusPoint5Scaled(2.0f);

        if (globalCtx->sceneNum == 0x34) {
            EffectSS_SpawnGSplash(globalCtx, &localVec3f, 0, 0, 0, (s32) (randPlusMinusPoint5Scaled(100.0f) + 200.0f));
            func_800F0568(globalCtx, &localVec3f, 0x32, 0x2817); //sfx function

        } else {
            func_800BBDAC(globalCtx, &this->actor, &this->actor.world.pos,
                 this->actor.shape.shadowScale - 20.0f, 5,
                 4.0f, 0xC8, 0xA, 1);
            Audio_PlayActorSound2(&this->actor, 0x3987);
        }
    }

    Math_SmoothScaleMaxF(&this->actor.shape.yOffset, -6000.0f, 0.5f, 200.0f);
    if (fabsf(this->actor.shape.yOffset + 6000.0f) < 10.0f) {
        gSaveContext.perm.weekEventReg[79] |= 8;
        func_800B7298(globalCtx, &this->actor, 6);
        ActorCutscene_Stop(this->actorCutscenes[0]);
        this->unk194 = 2;
        this->unk250 = 80.0f;
        func_80971794(this);
    }
}
#else
#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kakasi_0x8096F5E0/func_809714BC.asm")
#endif

void func_80971794(EnKakasi *this) {
    this->actor.shape.yOffset = -7000.0;
    this->actor.draw = NULL;
    this->actor.flags |= 0x8000000;
    this->unk196 = 5;
    this->actionFunc = func_809717D0;
}

// action func
void func_809717D0(Actor* thisx, GlobalContext* globalCtx) {
    EnKakasi* this = THIS;
    //if (((*(&gSaveContext + 0xF47) & 8) != 0) && (this->actor.xzDistToPlayer < this->unk250)) {
    if (((gSaveContext.perm.weekEventReg[79]  & 8) != 0) 
        && (this->actor.xzDistToPlayer < this->unk250)
        && ((gGameInfo->data[2401] != 0) || (globalCtx->msgCtx.unk1202A == 0xD)) ) {
            this->actor.flags &= 0xF7FFFFFF;
            globalCtx->msgCtx.unk1202A = 4;
            this->actionFunc = func_8097185C;
    }
}

//action func
void func_8097185C(Actor* thisx, GlobalContext *globalCtx) {
    //EnKakasi* this = THIS; //matches without, with stack is too big
    s32 cutsceneIndex;

    cutsceneIndex = 0;
    if (THIS->unk194 == 2) {
        cutsceneIndex = 1;
    }
    
    if (ActorCutscene_GetCurrentIndex() == 0x7C) {
        ActorCutscene_Stop(0x7C);
        ActorCutscene_SetIntentToPlay(THIS->actorCutscenes[cutsceneIndex]);
        return;
    }
    if (ActorCutscene_GetCanPlayNext(THIS->actorCutscenes[cutsceneIndex]) == 0) {
        ActorCutscene_SetIntentToPlay(THIS->actorCutscenes[cutsceneIndex]);
        return;
    }
    ActorCutscene_StartAndSetUnkLinkFields(THIS->actorCutscenes[cutsceneIndex], thisx);
    cutsceneIndex = 0; // wat? no longer used by needed to build
    Audio_PlayActorSound2(&THIS->actor, 0x3987U);
    thisx->draw = EnKakasi_Draw;
    THIS->unk196 = 6;
    THIS->actionFunc = func_8097193C;
}


//action func
void func_8097193C(Actor* thisx, GlobalContext *globalCtx) {
    EnKakasi* this = THIS;
    this->actor.shape.rot.y += 0x3000;

    if (this->unk1A0 != 1) {
        func_8096F800(&this->actor, 1);
    }
    if (this->actor.shape.yOffset < -10.0f) {
        if ((globalCtx->unk18840 & 7) == 0) {
            func_800BBDAC(globalCtx, &this->actor, 
                &this->actor.world, this->actor.shape.shadowScale - 20.0f,
                0xA, 8.0f, 500, 0xA, 1);
            Audio_PlayActorSound2(&this->actor, 0x3987U);
        }
        Math_SmoothScaleMaxF(&this->actor.shape.yOffset, 0.0f, 0.5f, 200.0f);
        return;
    }
    func_80971A38(&this->actor);
}

void func_80971A38(EnKakasi *this) {
    this->actor.textId = 0x164D;
    this->unk196 = 7;
    this->actionFunc = func_80971A64;
    this->actor.shape.yOffset = 0.0f;
}

// action func
void func_80971A64(Actor* thisx, GlobalContext* globalCtx) {
    EnKakasi* this = THIS;
    Math_SmoothScaleMaxMinS(&this->actor.shape.rot.y, this->actor.yawTowardsPlayer, 5, 0x3E8, 0);
    if (func_800B84D0(this, globalCtx) != 0) {
        this->actionFunc = func_80971AD4;
        return;
    }
    func_800B8614(this, globalCtx, 70.0f);
}

// action func
void func_80971AD4(Actor* thisx, GlobalContext *globalCtx) {
    EnKakasi* this = THIS;
    Math_SmoothScaleMaxMinS(&this->actor.shape.rot.y, this->actor.yawTowardsPlayer, 5, 0x3E8, 0);
    
    if ((func_80152498(&globalCtx->msgCtx) == 5) && (func_80147624(globalCtx) != 0)) {
        func_801477B4(globalCtx);
        func_80971A38(this);
    }
}

void EnKakasi_Update(Actor* thisx, GlobalContext* globalCtx) {
    EnKakasi* this = THIS;
    s32 pad;

    SkelAnime_FrameUpdateMatrix(&this->skelanime);
    if (this->actor.draw != 0) {
        func_8096F8D8(this);
    }

    this->actor.world.rot.y = this->actor.shape.rot.y;
    if (this->unk192 != 0) {
        this->unk192 -= 1;
    }
    if (this->unk204 != 0) {
        this->unk204 -= 1;
    }

    if ((s16) this->unk196 != 5) {
        if (( this->unk1BC.x != 0.0f) || (this->unk1BC.z != 0.0f)) {
            Math_Vec3f_Copy( &this->actor.focus,  &this->unk1BC);
            this->actor.focus.pos.y += 10.0f;
            if (this->cutsceneCamera == 0) {
                Math_Vec3s_Copy(&this->actor.focus.rot, &this->actor.world.rot);
            } else {
                Math_Vec3s_Copy(&this->actor.focus.rot, &this->actor.home.rot);
            }
        }
    } else {
        Actor_SetHeight(&this->actor,  this->unkHeight);
    }

    this->actionFunc(this, globalCtx);
    Actor_SetVelocityAndMoveYRotationAndGravity(&this->actor);
    func_800B78B8(globalCtx, &this->actor, 50.0f, 50.0f, 100.0f, 0x1C);
    if (this->actor.draw != 0) {
        Collider_UpdateCylinder( &this->actor, &this->collider);
        CollisionCheck_SetAC(globalCtx, &globalCtx->colCheckCtx, &this->collider);
        CollisionCheck_SetOC(globalCtx, &globalCtx->colCheckCtx, &this->collider);
    }
}

// post limb draw func
void func_80971CE0(struct GlobalContext *globalCtx, s32 limbIndex, Gfx **dList, Vec3s *rot, struct Actor *actor) {
    EnKakasi* this = (EnKakasi*) actor;
    if (limbIndex == 4) {
        // what is D_801D15B0 ? we didn't have to define it, we store the output though
        SysMatrix_MultiplyVector3fByState(&D_801D15B0, &this->unk1BC); //first is src, second is dest
    }
}

void EnKakasi_Draw(Actor* thisx, GlobalContext *globalCtx) { 
    EnKakasi* this = THIS;
    func_8012C28C(globalCtx->state.gfxCtx);
    SkelAnime_DrawSV(globalCtx, this->skelanime.skeleton,
       this->skelanime.limbDrawTbl, (s32) this->skelanime.dListCount, NULL, func_80971CE0, this);

}
