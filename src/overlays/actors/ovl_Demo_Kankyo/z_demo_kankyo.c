#include "z_demo_kankyo.h"

#define FLAGS 0x00000030

#define THIS ((DemoKankyo*)thisx)

void DemoKankyo_Init(DemoKankyo* this, GlobalContext* globalCtx);
//void DemoKankyo_Init(Actor* thisx, GlobalContext* globalCtx);
void DemoKankyo_Destroy(Actor* thisx, GlobalContext* globalCtx);
void DemoKankyo_Update(Actor* thisx, GlobalContext* globalCtx);
//void DemoKankyo_Draw(DemoKankyo* this, GlobalContext* globalCtx);
void DemoKankyo_Draw(Actor* thisx, GlobalContext* globalCtx);

// huge
void func_808CE45C(DemoKankyo* this, GlobalContext* globalCtx);
void func_808CF0CC(DemoKankyo* this, GlobalContext* globalCtx);

// draw function extensions
void func_808CF970(DemoKankyo* this, GlobalContext* globalCtx);
void func_808CFE04(DemoKankyo* this, GlobalContext* globalCtx);


u8 D_808D03C0 = 0; // actually gets changed as a value
UNK_TYPE D_808D03C4 = 0;

const ActorInit Demo_Kankyo_InitVars = {
    ACTOR_DEMO_KANKYO,
    ACTORCAT_ITEMACTION,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(DemoKankyo),
    (ActorFunc)DemoKankyo_Init,
    (ActorFunc)DemoKankyo_Destroy,
    (ActorFunc)DemoKankyo_Update,
    (ActorFunc)DemoKankyo_Draw,
};

// passed to Scene_FindSceneObjectIndex as the ID
s16 D_808D03EA = 0xE;


void func_808CE450(DemoKankyo* this, DemoKankyoActionFunc func) {
    this->actionFunc = func;
}

// action function: fairy particles
/*
void func_808CE45C(DemoKankyo *this, GlobalContext *globalCtx) {
    Vec3f spCC;
    Vec3f spBC;
    Actor *player;
    f32 *sp90;
    f32 *sp8C;
    f32 *sp88;
    f32 *sp84;
    f32 *sp7C;
    f32 *temp_s1;
    f32 sqrtResult;
    f32 randResult;
    f32 temp_f0_3;
    f32 temp_f0_4;
    f32 temp_f0_5;
    f32 temp_f0_6;
    f32 temp_f0_7;
    f32 temp_f0_8;
    f32 temp_f10;
    //f32 temp_f10_2;
    f32 eyeY;
    f32 -130.0f;
    f32 eyeZ;
    //f32 temp_f18;
    //f32 temp_f20;
    //f32 temp_f22;
    Vec3f temp_f18;
    f32 eyeX;
    f32 temp_f2_2;
    f32 temp_f6;
    f32 temp_f8;
    f32 temp_f8_2;
    s32 temp_s4;
    s32 temp_v0_4;
    u16 temp_t3;
    //u16 temp_t5;
    u16 temp_t8;
    u16 temp_t9_2;
    u8 temp_t9;
    u8 temp_v0_2;
    //u8 temp_v0_3;
    u8 temp_v1;
    void *temp_fp;
    s32 phi_v1;
    s32 i;
    f32 phi_f4;
    f32 phi_f8;
    f32 phi_f10;
    f32 phi_f6;
    f32 phi_f2;
    f32 phi_f0;
    f32 phi_f0_2;
    s32 phi_v1_2;
    void *phi_fp;

    //player = globalCtx->actorCtx.actorList[2].first;
    player = PLAYER; 
    temp_fp = globalCtx + 0x10000;
    if (globalCtx->roomContext.unk7A[1] != 0) {
        if (globalCtx->unk170F9 != 0) {
            globalCtx->unk170F9--;
        } else {
            Actor_MarkForDeath((Actor *) this);
        }
        phi_v1 = (s32) globalCtx->unk170F9;
        phi_fp = globalCtx + 0x10000;
    } else {
        temp_v1 = globalCtx->unk170F9;
        temp_t9 = temp_v1 + 0x10;
        phi_v1 = (s32) temp_v1;
        phi_fp = temp_fp;
        if ((s32) temp_v1 < 0x40) {
            globalCtx->unk170F9 = temp_t9;
            phi_v1 = temp_t9 & 0xFF;
            phi_fp = temp_fp;
        }
    }
    if (phi_v1 > 0) {
        //0.2f = 0.2f;
        //this = this;
      i = 0;
      phi_v1_2 = phi_v1;
      for (i = 0; i < DEMOKANKYO_PARTICLE_COUNT; ++i){// loop_9:
        eyeX = globalCtx->view.focalPoint.x - globalCtx->view.eye.x;
        eyeY = globalCtx->view.focalPoint.y - globalCtx->view.eye.y;
        eyeZ = globalCtx->view.focalPoint.z - globalCtx->view.eye.z;
        sqrtResult = sqrtf((eyeX * eyeX) + (eyeY * eyeY) + (eyeZ * eyeZ));
        temp_f18.x = eyeX / sqrtResult;
        temp_f18.y = eyeY / sqrtResult;
        temp_f18.z = eyeZ / sqrtResult;
        spCC.x = temp_f18.x;
        spCC.y = temp_f18.y;
        spCC.z = temp_f18.z;
        switch( this->unk144[i].unk0 ) { // particle type?
        //temp_v0_2 = this->unk144[i].unk0;
        //if (temp_v0_2 != 0) {
            //if ((temp_v0_2 != 1) && (temp_v0_2 != 2)) {
                //if (temp_v0_2 != 3) {
        case 0:
            this->unk144[i].unk1C.x = globalCtx->view.eye.x + (spCC.x * 80.0f);
            this->unk144[i].unk1C.y = globalCtx->view.eye.y + (spCC.y * 80.0f);
            this->unk144[i].unk1C.z = globalCtx->view.eye.z + (spCC.z * 80.0f);
            temp_f8_2 = (Rand_ZeroOne() - 0.5f) * 160.0f;
            this->unk144[i].unk4.y = 30.0f;
            this->unk144[i].unk4.x = temp_f8_2;
            this->unk144[i].unk4.z = (Rand_ZeroOne() - 0.5f) * 160.0f;
            temp_f0_7 = Rand_ZeroOne();
            this->unk184 = (u8)0;
            this->unk144[i].unk38 = (temp_f0_7 * 1.6f) + 0.5f;
            this->unk144[i].unk3C = (u16) (Rand_ZeroOne() * 65535.0f);
            this->unk144[i].unk44 = 0.1f;
            this->unk144[i].unk28.x = Rand_ZeroOne() * 360.0f;
            this->unk144[i].unk28.y = Rand_ZeroOne() * 360.0f;
            temp_f0_8 = Rand_ZeroOne();
            this->unk144[i].unk50 = 0;
            this->unk144[i].unk0 = this->unk144[i].unk0 + 1;
            this->unk144[i].unk28.z = temp_f0_8 * 360.0f;
            //goto block_74;
            phi_v1_2 = (s32) phi_fp->unk70F9;
            break;
        case 1:
        case 2:
            this->unk144[i].unk3C = this->unk144[i].unk3C + 1;
            spBC.x = globalCtx->view.eye.x + (temp_f18.x * 80.0f);
            spBC.y = globalCtx->view.eye.y + (temp_f18.y * 80.0f);
            spBC.z = globalCtx->view.eye.z + (temp_f18.z * 80.0f);
            //temp_v0_3 = this->unk144[i].unk0;
            this->unk144[i].unk10.x = this->unk144[i].unk4.x;
            this->unk158 = (f32) this->unk144[i].unk4.y;
            this->unk15C = (f32) this->unk144[i].unk4.z;
            if (this->unk144[i].unk0 == 1) {
                if (i < 0x20) {
                    if (Rand_ZeroOne() < 0.5f) {
                        this->unk144[i].unk48 = (s32) (Rand_ZeroOne() * 200.0f) + 0xC8;
                    } else {
                        this->unk144[i].unk48 = -0xC8 - (s32) (Rand_ZeroOne() * 200.0f);
                    }
                    this->unk18E = (u16) ((s32) (Rand_ZeroOne() * 50.0f) + 0xF);
                    this->unk190 = (f32) (((Rand_ZeroOne() * 10.0f) + 10.0f) * 0.01f);
                    // please god this better not be a switch
                    randResult = Rand_ZeroOne();
                    if (randResult < 0.2f) {
                        D_808D03C4 = 1;
                    } else if (randResult < 0.2f) {
                        D_808D03C4 = 3;
                    } else if (randResult < 0.4f) {
                        D_808D03C4 = 7;
                    } else {
                        D_808D03C4 = 0xF;
                    }
                    if ((D_808D03C4 & i) == 0) {
                        this->unk144[i].unk4.y = 0.0f;
                    }
                    this->unk144[i].unk0 = 2;
                    this->unk144[i].unk38 = 0.0f;
                }
                Math_SmoothStepToF(this + 0x188, 0.1f, 0.1f, 0.001f, 1e-05f); // D_808D0408
                Math_SmoothStepToF(this + 0x178, (f32) (s32) this->unk144[i].unk38, 0.5f, 0.2f, 0.02f);
                this->unk144[i].unk4.x = this->unk144[i].unk4.x + (__sinf(this->unk144[i].unk28.x) * this->unk144[i].pad34);
                this->unk144[i].unk4.y = this->unk144[i].unk4.y + (__sinf(this->unk144[i].unk28.y) * this->unk144[i].pad34);
                //temp_v0_4 = (i >> 1) & 3;
                this->unk144[i].unk4.z = this->unk144[i].unk4.z + (__sinf(this->unk144[i].unk28.z) * this->unk144[i].pad34);
                switch ((i >> 1) & 3){
                case 0:
                  this->unk144[i].unk28.x = this->unk144[i].unk28.x + D_808D0410;
                  this->unk144[i].unk28.y = this->unk144[i].unk28.y + (D_808D0414 * Rand_ZeroOne());
                  phi_f4 = this->unk144[i].unk28.z + D_808D0418;
                  this->unk144[i].unk28.z = phi_f4;

                  break;
                case 1:
                  this->unk144[i].unk28.x = this->unk144[i].unk28.x + (D_808D041C * Rand_ZeroOne());
                  this->unk144[i].unk28.y = this->unk144[i].unk28.y + (D_808D0420 * Rand_ZeroOne());
                  phi_f4 = this->unk144[i].unk28.z + (D_808D0424 * Rand_ZeroOne());
                  this->unk144[i].unk28.z = phi_f4;

                  break;
                case 2:
                  this->unk144[i].unk28.x = this->unk144[i].unk28.x + (D_808D0428 * Rand_ZeroOne());
                  this->unk144[i].unk28.y = this->unk144[i].unk28.y + (D_808D042C * Rand_ZeroOne());
                  phi_f4 = this->unk144[i].unk28.z + (D_808D0430 * Rand_ZeroOne());
                  this->unk144[i].unk28.z = phi_f4;
                  break;

                case 3:
                  this->unk144[i].unk28.x = this->unk144[i].unk28.x + (D_808D0434 * Rand_ZeroOne());
                  this->unk144[i].unk28.y = this->unk144[i].unk28.y + (D_808D0438 * Rand_ZeroOne());
                  phi_f4 = this->unk144[i].unk28.z + (D_808D043C * Rand_ZeroOne());
                  this->unk144[i].unk28.z = phi_f4;

                  break;
              
                } // end switch
            } else if (this->unk144[i].unk0 == 2) {
                temp_s1 = this + 0x188;
                if ((D_808D03C4 & i) == 0) {
                    sp7C = this + 0x150;
                    sp84 = this + 0x148;
                    sp88 = this + 0x168;
                    sp8C = this + 0x164;
                    sp90 = this + 0x160;
                    Math_SmoothStepToF(temp_s1, 0.25f, 0.1f, 0.001f, D_808D0440);
                    Math_SmoothStepToF(sp90, (f32) (s32) player->world.pos.x, 0.5f, 1.0f, 0.2f);
                    Math_SmoothStepToF(sp8C, player->world.pos.y + 50.0f, 0.5f, 1.0f, 0.2f);
                    Math_SmoothStepToF(sp88, (f32) (s32) player->world.pos.z, 0.5f, 1.0f, 0.2f);
                    temp_t8 = this->unk18E;
                    temp_f8 = (f32) temp_t8;
                    phi_f8 = temp_f8;
                    if ((s32) temp_t8 < 0) {
                        phi_f8 = temp_f8 + 4294967296.0f;
                    }
                    Math_SmoothStepToF(sp84, phi_f8 * Math_SinS((s16) (this->unk144[i].unk40 - 0x8000)), 0.5f, 2.0f, 0.2f);
                    temp_t9_2 = this->unk18E;
                    temp_f10 = (f32) temp_t9_2;
                    phi_f10 = temp_f10;
                    if ((s32) temp_t9_2 < 0) {
                        phi_f10 = temp_f10 + 4294967296.0f;
                    }
                    Math_SmoothStepToF(sp7C, phi_f10 * Math_CosS((s16) (this->unk144[i].unk40 - 0x8000)), 0.5f, 2.0f, 0.2f);
                    this->unk144[i].unk40 = this->unk144[i].unk40 + this->unk144[i].unk48;
                    this->unk144[i].unk4.y = this->unk144[i].unk4.y + __sinf(this->unk144[i].unk28.y);
                    this->unk144[i].unk28.x = this->unk144[i].unk28.x + (0.2f * Rand_ZeroOne());
                    this->unk144[i].unk28.y = this->unk144[i].unk28.y + this->unk190;
                    this->unk144[i].unk28.z = this->unk144[i].unk28.z + (D_808D0444 * Rand_ZeroOne());
                    temp_t3 = this->unk18E;
                    temp_f6 = (f32) temp_t3;
                    phi_f6 = temp_f6;
                    if ((s32) temp_t3 < 0) {
                        phi_f6 = temp_f6 + 4294967296.0f;
                    }
                    this->unk144[i].unk4.x = phi_f6 * Math_SinS((s16) (this->unk144[i].unk40 - 0x8000));
                    //temp_t5 = this->unk18E;
                    //temp_f10_2 = (f32) temp_t5;
                    if ((s32) this->unk18E < 0) {
                        // this might be a temp
                        this->unk18E += 4294967296.0f; // mystery
                    }
                    this->unk144[i].unk4.z = this->unk18E * Math_CosS((s16) (this->unk144[i].unk40 - 0x8000));
                } else {
                    Math_SmoothStepToF(temp_s1, 0.1f, 0.1f, 0.001f, D_808D0448);
                    Math_SmoothStepToF(this + 0x178, 1.5f, 0.5f, 0.1f, D_808D044C);
                    this->unk144[i].unk4.x = (this->actor.prevPos.y - this->unk144[i].unk1C.x) + this->actor.uncullZoneScale;
                    this->unk144[i].unk4.y = (this->actor.prevPos.z - this->unk144[i].unk1C.y) + this->actor.uncullZoneDownward;
                    this->unk144[i].unk4.z = (this->actor.isTargeted - this->unk144[i].unk1C.z) + this->actor.prevPos.x;
                }
            } // no else?
            if (this->unk144[i].unk0 != 2) {
                //-130.0f = -130.0f;
                temp_f2_2 = (this->unk144[i].unk4.x + this->unk144[i].unk1C.x) - spBC.x;
                if ((temp_f2_2 > 130.0f) || (temp_f2_2 < -130.0f) 
                  || (temp_f0_3 = (this->unk144[i].unk4.y + this->unk144[i].unk1C.y) - spBC.y, (temp_f0_3 > 130.0f)) 
                  || (temp_f0_3 < -130.0f) 
                  || (temp_f0_4 = (this->unk144[i].unk4.z + this->unk144[i].unk1C.z) - spBC.z, (temp_f0_4 > 130.0f)) 
                  || (temp_f0_4 < -130.0f)) {
                    phi_f2 = temp_f2_2;
                    if (temp_f2_2 > 130.0f) {
                        this->unk144[i].unk4.x = 0.0f;
                        this->unk144[i].unk1C.x = spBC.x - 130.0f;
                        phi_f2 = (this->unk144[i].unk4.x + this->unk144[i].unk1C.x) - spBC.x;
                    }
                    if (phi_f2 < -130.0f) {
                        this->unk144[i].unk4.x = 0.0f;
                        this->unk144[i].unk1C.x = spBC.x + 130.0f;
                    }
                    temp_f0_5 = (this->unk144[i].unk4.y + this->unk144[i].unk1C.y) - spBC.y;
                    phi_f0 = temp_f0_5;
                    if (temp_f0_5 > 50.0f) {
                        this->unk144[i].unk4.y = 0.0f;
                        this->unk144[i].unk1C.y = spBC.y - 50.0f;
                        phi_f0 = (this->unk144[i].unk4.y + this->unk144[i].unk1C.y) - spBC.y;
                    }
                    if (phi_f0 < -50.0f) {
                        this->unk144[i].unk4.y = 0.0f;
                        this->unk144[i].unk1C.y = spBC.y + 50.0f;
                    }
                    temp_f0_6 = (this->unk144[i].unk4.z + this->unk144[i].unk1C.z) - spBC.z;
                    phi_f0_2 = temp_f0_6;
                    if (temp_f0_6 > 130.0f) {
                        this->unk144[i].unk4.z = 0.0f;
                        this->unk144[i].unk1C.z = spBC.z - 130.0f;
                        phi_f0_2 = (this->unk144[i].unk4.z + this->unk144[i].unk1C.z) - spBC.z;
                    }
                    if (phi_f0_2 < -130.0f) {
                        this->unk144[i].unk4.z = 0.0f;
                        this->unk144[i].unk1C.z = spBC.z + 130.0f;
                    }
                }
            }
            phi_v1_2 = (s32) phi_fp->unk70F9;
            //goto block_74;
            break;
        case 3:
            this->unk144[i].unk0 = 0;
            //block_74:
            phi_v1_2 = (s32) phi_fp->unk70F9;
            break;
        default:
            break;

        }

                //} else {
                //}
            //} else {
            //}
        //} else {
        //}
        //this = this + 0x54;
        //i = temp_s4;
        //i++;
        //if (temp_s4 < phi_v1_2) {
            //goto loop_9;
        }
    }
} // */
//#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Demo_Kankyo_0x808CE450/func_808CE45C.asm")

void func_808CF06C(DemoKankyo *this, GlobalContext *globalCtx) {
    if (Object_IsLoaded(&globalCtx->objectCtx, this->objBankIndex) != 0) {
        this->unk164C[0] = 1;
        this->actor.objBankIndex = (s8) this->objBankIndex;
        func_808CE450(this, func_808CF0CC);
    }
}

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Demo_Kankyo_0x808CE450/func_808CF0CC.asm")

//#if NON_EQUIVELENT
// 
void DemoKankyo_Init(DemoKankyo *this, GlobalContext *globalCtx) {
    s32 pad;
    s32 objID;
    s32 oId2; // trying to convince oid into sp20
    s32 i;
    s32 pad2[9];

    // vanilla code wants to increment i first...? two instructions out of order
    //for (i = 0; i < DEMOKANKYO_PARTICLE_COUNT; i++){
    i = 0;
    while (i < DEMOKANKYO_PARTICLE_COUNT) {
      DemoKankyoParticle* particlePtr = &this->unk144[i]; 
      particlePtr->unk0 = 0;
      i++;
    }

    // control flow is wrong here, at leasst two branches to wrong locations
    switch (this->actor.params) {
        case 0:
            objID = 0;
            this->actor.room = -1;
            // check if another of this actor already exist, if so kill
            if (D_808D03C0 == 0) {
                func_808CE450(this, func_808CE45C);
                D_808D03C0 = 1;
                //break;
            } else {
                Actor_MarkForDeath(&this->actor);
                //break;
            }
            break;

        case 1:
            this->unk164C[0] = 0;
            objID = Object_GetIndex(&globalCtx->objectCtx, D_808D03EA);
            func_808CE450(this, func_808CF06C);
            break;

        case 2:
            objID = 1;
            //objID = 0;
            this->unk164C[0] = 1;
            func_808CE450(this, func_808CF0CC);
            break;

        default:
            objID = -1;
            //do { } while (0);
            break;
    }

    if (objID >= 0) {
        this->objBankIndex = objID;
    }
}
//#else
//#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Demo_Kankyo_0x808CE450/DemoKankyo_Init.asm")
//#endif

void DemoKankyo_Destroy(Actor *thisx, GlobalContext *globalCtx) {
    DemoKankyo* this = THIS;
    Actor_MarkForDeath(&this->actor);
}

void DemoKankyo_Update(Actor *thisx, GlobalContext *globalCtx) {
    DemoKankyo* this = THIS;
    this->actionFunc(this, globalCtx);
}

// draw func
#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Demo_Kankyo_0x808CE450/func_808CF970.asm")

// draw func
#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Demo_Kankyo_0x808CE450/func_808CFE04.asm")

void DemoKankyo_Draw(Actor *thisx, GlobalContext *globalCtx) {
    DemoKankyo* this = THIS;

    switch(this->actor.params){
      case 0:
          func_808CF970(this, globalCtx);
          break;
      case 1:
      case 2:
          func_808CFE04(this, globalCtx);
          break;
    }
}
