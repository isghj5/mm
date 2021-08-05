#include "z_demo_kankyo.h"

#define FLAGS 0x00000030

#define THIS ((DemoKankyo*)thisx)

void DemoKankyo_Init(Actor* thisx, GlobalContext* globalCtx);
void DemoKankyo_Destroy(Actor* thisx, GlobalContext* globalCtx);
void DemoKankyo_Update(Actor* thisx, GlobalContext* globalCtx);
void DemoKankyo_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_808CF0CC(DemoKankyo* this, GlobalContext* globalCtx);

extern Gfx D_0407AB58[];
extern Gfx D_06001000[];
extern Gfx D_04023428[];

static u8 D_808D03C0 = 0;
static s16 D_808D03C4 = 0;

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

static s32 D_808D03E8 = 0x1000E;

void DemoKankyo_SetupAction(DemoKankyo* this, DemoKankyoActionFunc actionFunc) {
    this->actionFunc = actionFunc;
}

void func_808CE45C(DemoKankyo* this, GlobalContext* globalCtx) {
    s32 pad;
    s32 i;
    f32 var;
    f32 temp_f2;
    f32 spCC;
    f32 spC8;
    f32 spC4;
    f32 temp_f0;
    f32 spBC;
    f32 spB8;
    f32 spB4;
    f32 temp_f12;
    f32 temp_f14;
    f32 temp_f0_2;
    Player* player = PLAYER;

    if (globalCtx->roomCtx.unk7A[1] != 0) {
        if (globalCtx->envCtx.unk_F2[3] != 0) {
            globalCtx->envCtx.unk_F2[3]--;
        } else {
            Actor_MarkForDeath(&this->actor);
        }
    } else if (globalCtx->envCtx.unk_F2[3] < 0x40) {
        globalCtx->envCtx.unk_F2[3] += 16;
    }

    for (i = 0; i < globalCtx->envCtx.unk_F2[3]; i++) {
        var = 130.0f;
        temp_f2 = globalCtx->view.at.x - globalCtx->view.eye.x;
        temp_f12 = globalCtx->view.at.y - globalCtx->view.eye.y;
        temp_f14 = globalCtx->view.at.z - globalCtx->view.eye.z;
        temp_f0 = sqrtf(SQ(temp_f2) + SQ(temp_f12) + SQ(temp_f14));
        spCC = temp_f2 / temp_f0;
        spC8 = temp_f12 / temp_f0;
        spC4 = temp_f14 / temp_f0;

        switch (this->particles[i].unk_00) {
            case 0:
                this->particles[i].unk_1C.x = globalCtx->view.eye.x + (spCC * 80.0f);
                this->particles[i].unk_1C.y = globalCtx->view.eye.y + (spC8 * 80.0f);
                this->particles[i].unk_1C.z = globalCtx->view.eye.z + (spC4 * 80.0f);
                this->particles[i].unk_04.x = (Rand_ZeroOne() - 0.5f) * 160.0f;
                this->particles[i].unk_04.y = 30.0f;
                this->particles[i].unk_04.z = (Rand_ZeroOne() - 0.5f) * 160.0f;
                this->particles[i].unk_38 = (Rand_ZeroOne() * 1.6f) + 0.5f;
                this->particles[i].unk_40 = 0;
                this->particles[i].unk_3C = Rand_ZeroOne() * 65535;
                this->particles[i].unk_44 = 0.1f;
                this->particles[i].unk_28.x = Rand_ZeroOne() * 360.0f;
                this->particles[i].unk_28.y = Rand_ZeroOne() * 360.0f;
                this->particles[i].unk_28.z = Rand_ZeroOne() * 360.0f;
                this->particles[i].unk_50 = 0;
                this->particles[i].unk_00 += 1;
                break;

            case 1:
            case 2:
                this->particles[i].unk_3C += 1;
                spBC = globalCtx->view.eye.x + (spCC * 80.0f);
                spB8 = globalCtx->view.eye.y + (spC8 * 80.0f);
                spB4 = globalCtx->view.eye.z + (spC4 * 80.0f);
                this->particles[i].unk_10.x = this->particles[i].unk_04.x;
                this->particles[i].unk_10.y = this->particles[i].unk_04.y;
                this->particles[i].unk_10.z = this->particles[i].unk_04.z;
                if (this->particles[i].unk_00 == 1) {
                    if (i < 32) {
                        if (Rand_ZeroOne() < 0.5f) {
                            this->particles[i].unk_48 = (s16)(Rand_ZeroOne() * 200.0f) + 200;
                        } else {
                            this->particles[i].unk_48 = -200 - (s16)(Rand_ZeroOne() * 200.0f);
                        }
                        this->particles[i].unk_4A = (s16)(Rand_ZeroOne() * 50.0f) + 15;
                        this->particles[i].unk_4C = ((Rand_ZeroOne() * 10.0f) + 10.0f) * 0.01f;
                        temp_f0_2 = Rand_ZeroOne();
                        if (temp_f0_2 < 0.2f) {
                            D_808D03C4 = 1;
                        } else if (temp_f0_2 < 0.2f) {
                            D_808D03C4 = 3;
                        } else if (temp_f0_2 < 0.4f) {
                            D_808D03C4 = 7;
                        } else {
                            D_808D03C4 = 0xF;
                        }
                        if ((D_808D03C4 & i) == 0) {
                            this->particles[i].unk_04.y = 0.0f;
                        }
                        this->particles[i].unk_00 = 2;
                        this->particles[i].unk_38 = 0.0f;
                    }

                    Math_SmoothStepToF(&this->particles[i].unk_44, 0.1, 0.1f, 0.001f, 0.00001f);
                    Math_SmoothStepToF(&this->particles[i].unk_34, this->particles[i].unk_38, 0.5f, 0.2f, 0.02f);
                    this->particles[i].unk_04.x += __sinf(this->particles[i].unk_28.x) * this->particles[i].unk_34;
                    this->particles[i].unk_04.y += __sinf(this->particles[i].unk_28.y) * this->particles[i].unk_34;
                    this->particles[i].unk_04.z += __sinf(this->particles[i].unk_28.z) * this->particles[i].unk_34;

                    switch ((i >> 1) & 3) {
                        case 0:
                            this->particles[i].unk_28.x += 0.008f;
                            this->particles[i].unk_28.y += 0.05f * Rand_ZeroOne();
                            this->particles[i].unk_28.z += 0.015f;
                            break;

                        case 1:
                            this->particles[i].unk_28.x += 0.01f * Rand_ZeroOne();
                            this->particles[i].unk_28.y += 0.05f * Rand_ZeroOne();
                            this->particles[i].unk_28.z += (0.005f * Rand_ZeroOne());
                            break;

                        case 2:
                            this->particles[i].unk_28.x += 0.01f * Rand_ZeroOne();
                            this->particles[i].unk_28.y += 0.4f * Rand_ZeroOne();
                            this->particles[i].unk_28.z += (0.004f * Rand_ZeroOne());
                            break;

                        case 3:
                            this->particles[i].unk_28.x += 0.01f * Rand_ZeroOne();
                            this->particles[i].unk_28.y += 0.08f * Rand_ZeroOne();
                            this->particles[i].unk_28.z += (0.05f * Rand_ZeroOne());
                            break;
                    }
                } else if (this->particles[i].unk_00 == 2) {
                    if ((D_808D03C4 & i) == 0) {
                        Math_SmoothStepToF(&this->particles[i].unk_44, 0.25f, 0.1f, 0.001f, 0.00001f);
                        Math_SmoothStepToF(&this->particles[i].unk_1C.x, player->actor.world.pos.x, 0.5f, 1.0f, 0.2f);
                        Math_SmoothStepToF(&this->particles[i].unk_1C.y, player->actor.world.pos.y + 50.0f, 0.5f, 1.0f,
                                           0.2f);
                        Math_SmoothStepToF(&this->particles[i].unk_1C.z, player->actor.world.pos.z, 0.5f, 1.0f, 0.2f);
                        Math_SmoothStepToF(&this->particles[i].unk_04.x,
                                           Math_SinS(this->particles[i].unk_3E - 0x8000) * this->particles[i].unk_4A,
                                           0.5f, 2.0f, 0.2f);
                        Math_SmoothStepToF(&this->particles[i].unk_04.z,
                                           Math_CosS(this->particles[i].unk_3E - 0x8000) * this->particles[i].unk_4A,
                                           0.5f, 2.0f, 0.2f);
                        this->particles[i].unk_3E += this->particles[i].unk_48;
                        this->particles[i].unk_04.y += __sinf(this->particles[i].unk_28.y);
                        this->particles[i].unk_28.x += 0.2f * Rand_ZeroOne();
                        this->particles[i].unk_28.y += this->particles[i].unk_4C;
                        this->particles[i].unk_28.z += 0.1f * Rand_ZeroOne();
                        this->particles[i].unk_04.x =
                            Math_SinS(this->particles[i].unk_3E - 0x8000) * this->particles[i].unk_4A;
                        this->particles[i].unk_04.z =
                            Math_CosS(this->particles[i].unk_3E - 0x8000) * this->particles[i].unk_4A;
                    } else {
                        Math_SmoothStepToF(&this->particles[i].unk_44, 0.1, 0.1f, 0.001f, 0.00001f);
                        Math_SmoothStepToF(&this->particles[i].unk_34, 1.5f, 0.5f, 0.1f, 0.0002f);
                        this->particles[i].unk_04.x = this->particles[i - 1].unk_10.x +
                                                      (this->particles[i - 1].unk_1C.x - this->particles[i].unk_1C.x);
                        this->particles[i].unk_04.y = this->particles[i - 1].unk_10.y +
                                                      (this->particles[i - 1].unk_1C.y - this->particles[i].unk_1C.y);
                        this->particles[i].unk_04.z = this->particles[i - 1].unk_10.z +
                                                      (this->particles[i - 1].unk_1C.z - this->particles[i].unk_1C.z);
                    }
                }

                if ((this->particles[i].unk_00 != 2) &&
                    ((((this->particles[i].unk_1C.x + this->particles[i].unk_04.x) - spBC) > var) ||
                     (((this->particles[i].unk_1C.x + this->particles[i].unk_04.x) - spBC) < -var) ||
                     (((this->particles[i].unk_1C.y + this->particles[i].unk_04.y) - spB8) > var) ||
                     (((this->particles[i].unk_1C.y + this->particles[i].unk_04.y) - spB8) < -var) ||
                     (((this->particles[i].unk_1C.z + this->particles[i].unk_04.z) - spB4) > var) ||
                     (((this->particles[i].unk_1C.z + this->particles[i].unk_04.z) - spB4) < -var))) {
                    if (((this->particles[i].unk_04.x + this->particles[i].unk_1C.x) - spBC) > var) {
                        this->particles[i].unk_04.x = 0.0f;
                        this->particles[i].unk_1C.x = spBC - var;
                    }

                    if (((this->particles[i].unk_1C.x + this->particles[i].unk_04.x) - spBC) < -var) {
                        this->particles[i].unk_04.x = 0.0f;
                        this->particles[i].unk_1C.x = spBC + var;
                    }

                    if (((this->particles[i].unk_1C.y + this->particles[i].unk_04.y) - spB8) > 50.0f) {
                        this->particles[i].unk_04.y = 0.0f;
                        this->particles[i].unk_1C.y = spB8 - 50.0f;
                    }

                    if (((this->particles[i].unk_1C.y + this->particles[i].unk_04.y) - spB8) < -50.0f) {
                        this->particles[i].unk_04.y = 0.0f;
                        this->particles[i].unk_1C.y = spB8 + 50.0f;
                    }

                    if (((this->particles[i].unk_1C.z + this->particles[i].unk_04.z) - spB4) > var) {
                        this->particles[i].unk_04.z = 0.0f;
                        this->particles[i].unk_1C.z = spB4 - var;
                    }

                    if (((this->particles[i].unk_1C.z + this->particles[i].unk_04.z) - spB4) < -var) {
                        this->particles[i].unk_04.z = 0.0f;
                        this->particles[i].unk_1C.z = spB4 + var;
                    }
                }
                break;

            case 3:
                this->particles[i].unk_00 = 0;
                break;
        }
    }
}

void func_808CF06C(DemoKankyo* this, GlobalContext* globalCtx) {
    if (Object_IsLoaded(&globalCtx->objectCtx, this->unk_1648)) {
        this->unk_164C = 1;
        this->actor.objBankIndex = this->unk_1648;
        DemoKankyo_SetupAction(this, func_808CF0CC);
    }
}

void func_808CF0CC(DemoKankyo* this, GlobalContext* globalCtx) {
    s32 i;
    f32 temp_f2;
    f32 temp_f12;
    f32 temp_f14;
    f32 spDC;
    f32 spD8;
    f32 spD4;
    f32 temp_f0;
    f32 temp_f0_5;
    f32 temp_f2_3;
    f32 temp_f18;
    f32 temp_f20;
    f32 temp_f24;
    f32 temp_f26;
    f32 var;
    s32 pad;
    Vec3f spA4;

    if (globalCtx->envCtx.unk_F2[3] < 0x40) {
        globalCtx->envCtx.unk_F2[3] += 16;
    }

    temp_f2 = globalCtx->view.at.x - globalCtx->view.eye.x;
    temp_f12 = globalCtx->view.at.y - globalCtx->view.eye.y;
    temp_f14 = globalCtx->view.at.z - globalCtx->view.eye.z;
    temp_f0 = sqrtf(SQ(temp_f2) + SQ(temp_f12) + SQ(temp_f14));
    spDC = temp_f2 / temp_f0;
    spD8 = temp_f12 / temp_f0;
    spD4 = temp_f14 / temp_f0;
    var = 120.0f;

    for (i = 0; i < globalCtx->envCtx.unk_F2[3]; i++) {
        switch (this->particles[i].unk_00) {
            case 0:
                this->particles[i].unk_1C.x = globalCtx->view.eye.x + (spDC * var);
                this->particles[i].unk_1C.y = globalCtx->view.eye.y + (spD8 * var);
                this->particles[i].unk_1C.z = globalCtx->view.eye.z + (spD4 * var);
                this->particles[i].unk_04.x = (Rand_ZeroOne() - 0.5f) * (var + var);
                this->particles[i].unk_04.y = (Rand_ZeroOne() - 0.5f) * (var + var);
                this->particles[i].unk_04.z = (Rand_ZeroOne() - 0.5f) * (var + var);
                this->particles[i].unk_38 = (Rand_ZeroOne() * 1.6f) + 0.5f;
                this->particles[i].unk_40 = 0;
                this->particles[i].unk_3C = (Rand_ZeroOne() * 65535);
                this->particles[i].unk_44 = 0.2f;
                this->particles[i].unk_28.x = Rand_ZeroOne() * 360.0f;
                this->particles[i].unk_28.y = Rand_ZeroOne() * 360.0f;
                this->particles[i].unk_28.z = Rand_ZeroOne() * 360.0f;
                this->particles[i].unk_50 = 0;
                this->particles[i].unk_00 += 1;
                break;

            case 1:
            case 2:
                this->particles[i].unk_3C += 1;
                if (this->actor.params == 2) {
                    this->particles[i].unk_1C.y = globalCtx->view.eye.y + (spD8 * var) + 80.0f;
                }
                temp_f20 = globalCtx->view.eye.x + (spDC * var);
                temp_f24 = globalCtx->view.eye.y + (spD8 * var);
                temp_f26 = globalCtx->view.eye.z + (spD4 * var);
                Math_SmoothStepToF(&this->particles[i].unk_44, 0.2f, 0.1f, 0.001f, 0.00001f);
                Math_SmoothStepToF(&this->particles[i].unk_34, this->particles[i].unk_38, 0.5f, 0.2f, 0.02f);
                this->particles[i].unk_04.x += __sinf(this->particles[i].unk_28.x) * this->particles[i].unk_34;
                this->particles[i].unk_04.y += __sinf(this->particles[i].unk_28.y) * this->particles[i].unk_34;
                this->particles[i].unk_04.z += __sinf(this->particles[i].unk_28.z) * this->particles[i].unk_34;

                switch ((i >> 1) & 3) {
                    case 0:
                        this->particles[i].unk_28.x += 0.008f;
                        this->particles[i].unk_28.y += 0.05f * Rand_ZeroOne();
                        this->particles[i].unk_28.z += 0.015f;
                        break;

                    case 1:
                        this->particles[i].unk_28.x += 0.01f * Rand_ZeroOne();
                        this->particles[i].unk_28.y += 0.05f * Rand_ZeroOne();
                        this->particles[i].unk_28.z += 0.005f * Rand_ZeroOne();
                        break;

                    case 2:
                        this->particles[i].unk_28.x += 0.01f * Rand_ZeroOne();
                        this->particles[i].unk_28.y += 0.4f * Rand_ZeroOne();
                        this->particles[i].unk_28.z += 0.004f * Rand_ZeroOne();
                        break;

                    case 3:
                        this->particles[i].unk_28.x += 0.01f * Rand_ZeroOne();
                        this->particles[i].unk_28.y += 0.08f * Rand_ZeroOne();
                        this->particles[i].unk_28.z += 0.05f * Rand_ZeroOne();
                        break;
                }

                if (((this->particles[i].unk_1C.x + this->particles[i].unk_04.x) - temp_f20) > var) {
                    this->particles[i].unk_1C.x = temp_f20 - var;
                }

                if (((this->particles[i].unk_1C.x + this->particles[i].unk_04.x) - temp_f20) < -var) {
                    this->particles[i].unk_1C.x = temp_f20 + var;
                }

                spA4.x = this->particles[i].unk_1C.x + this->particles[i].unk_04.x;
                spA4.y = this->particles[i].unk_1C.y + this->particles[i].unk_04.y;
                spA4.z = this->particles[i].unk_1C.z + this->particles[i].unk_04.z;
                temp_f2_3 = Math_Vec3f_DistXZ(&spA4, &globalCtx->view.eye) / 200.0f;
                temp_f2_3 = CLAMP(temp_f2_3, 0.0f, 1.0f);
                temp_f0_5 = 100.0f + temp_f2_3 + 60.0f;

                if (temp_f0_5 < ((this->particles[i].unk_1C.y + this->particles[i].unk_04.y) - temp_f24)) {
                    this->particles[i].unk_1C.y = temp_f24 - temp_f0_5;
                }

                if (((this->particles[i].unk_1C.y + this->particles[i].unk_04.y) - temp_f24) < -temp_f0_5) {
                    this->particles[i].unk_1C.y = temp_f24 + temp_f0_5;
                }

                if (((this->particles[i].unk_1C.z + this->particles[i].unk_04.z) - temp_f26) > var) {
                    this->particles[i].unk_1C.z = temp_f26 - var;
                }

                if (((this->particles[i].unk_1C.z + this->particles[i].unk_04.z) - temp_f26) < -var) {
                    this->particles[i].unk_1C.z = temp_f26 + var;
                }
                break;

            case 3:
                this->particles[i].unk_00 = 0;
                break;
        }
    }
}

void DemoKankyo_Init(Actor* thisx, GlobalContext* globalCtx) {
    DemoKankyo* this = THIS;
    s32 pad;
    s32 i;
    s32 sp20;

    // This must be a single line to match, possibly a macro?
    // clang-format off
    for (i = 0; i < ARRAY_COUNT(this->particles); i++) { this->particles[i].unk_00 = 0; }
    // clang-format on

    if (0) {};

    switch (this->actor.params) {
        case 0:
            sp20 = 0;
            this->actor.room = -1;
            if (D_808D03C0 == 0) {
                DemoKankyo_SetupAction(this, func_808CE45C);
                D_808D03C0 = 1;
            } else {
                Actor_MarkForDeath(&this->actor);
            }
            break;

        case 1:
            this->unk_164C = 0;
            sp20 = Object_GetIndex(&globalCtx->objectCtx, D_808D03E8);
            DemoKankyo_SetupAction(this, func_808CF06C);
            break;

        case 2:
            sp20 = 0;
            this->unk_164C = 1;
            DemoKankyo_SetupAction(this, func_808CF0CC);
            break;

        default:
            sp20 = -1;
            break;
    }

    if (sp20 >= 0) {
        this->unk_1648 = sp20;
    }
}

void DemoKankyo_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    DemoKankyo* this = THIS;

    Actor_MarkForDeath(&this->actor);
}

void DemoKankyo_Update(Actor* thisx, GlobalContext* globalCtx) {
    DemoKankyo* this = THIS;

    this->actionFunc(this, globalCtx);
}

void func_808CF970(Actor* thisx, GlobalContext* globalCtx2) {
    DemoKankyo* this = THIS;
    GlobalContext* globalCtx = globalCtx2;
    s16 i;
    f32 temp_f0;
    Vec3f spA4;
    Vec3f sp98;

    if (!(globalCtx->cameraPtrs[0]->flags2 & 0x100)) {
        OPEN_DISPS(globalCtx->state.gfxCtx);

        POLY_XLU_DISP = Gfx_CallSetupDL(POLY_XLU_DISP, 20);

        gSPSegment(POLY_XLU_DISP++, 0x08, Lib_SegmentedToVirtual(&D_04079B10));
        gSPDisplayList(POLY_XLU_DISP++, D_0407AB10);

        for (i = 0; i < globalCtx->envCtx.unk_F2[3]; i++) {
            spA4.x = this->particles[i].unk_1C.x + this->particles[i].unk_04.x;
            spA4.y = this->particles[i].unk_1C.y + this->particles[i].unk_04.y;
            spA4.z = this->particles[i].unk_1C.z + this->particles[i].unk_04.z;
            func_80169474(globalCtx, &spA4, &sp98);
            if ((sp98.x >= 0.0f) && (sp98.x < 320.0f) && (sp98.y >= 0.0f) && (sp98.y < 240.0f)) {
                SysMatrix_InsertTranslation(spA4.x, spA4.y, spA4.z, MTXMODE_NEW);
                temp_f0 = this->particles[i].unk_40 / 50.0f;
                if (temp_f0 > 1.0f) {
                    temp_f0 = 1.0f;
                }

                Matrix_Scale(this->particles[i].unk_44 * temp_f0, this->particles[i].unk_44 * temp_f0,
                             this->particles[i].unk_44 * temp_f0, MTXMODE_APPLY);
                if (i < 32) {
                    if (this->particles[i].unk_00 != 2) {
                        if (this->particles[i].unk_40 > 0) {
                            this->particles[i].unk_40--;
                        }
                    } else if (this->particles[i].unk_40 < 100) {
                        this->particles[i].unk_40++;
                    }
                } else if (this->particles[i].unk_00 != 2) {
                    if ((this->particles[i].unk_3C & 0x1F) < 16) {
                        if (this->particles[i].unk_40 < 0xEB) {
                            this->particles[i].unk_40 += 20;
                        }
                    } else if (this->particles[i].unk_40 > 20) {
                        this->particles[i].unk_40 -= 20;
                    }
                } else if ((this->particles[i].unk_3C & 0xF) < 8) {
                    if (this->particles[i].unk_40 < 0xFF) {
                        this->particles[i].unk_40 += 100;
                    }
                } else if (this->particles[i].unk_40 > 10) {
                    this->particles[i].unk_40 -= 10;
                }

                gDPPipeSync(POLY_XLU_DISP++);

                switch (i & 1) {
                    case 0:
                        gDPSetPrimColor(POLY_XLU_DISP++, 0, 0, 255, 255, 155, this->particles[i].unk_40);
                        gDPSetEnvColor(POLY_XLU_DISP++, 250, 180, 0, this->particles[i].unk_40);
                        break;

                    case 1:
                        gDPSetPrimColor(POLY_XLU_DISP++, 0, 0, 255, 255, 255, this->particles[i].unk_40);
                        gDPSetEnvColor(POLY_XLU_DISP++, 0, 100, 255, this->particles[i].unk_40);
                        break;
                }

                SysMatrix_InsertMatrix(&globalCtx->mf_187FC, MTXMODE_APPLY);
                SysMatrix_InsertZRotation_f(globalCtx->state.frames * 20.0f * 0.017453292f, MTXMODE_APPLY);

                gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx),
                          G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
                gSPDisplayList(POLY_XLU_DISP++, D_0407AB58);
            }
        }

        CLOSE_DISPS(globalCtx->state.gfxCtx);
    }
}

void func_808CFE04(Actor* thisx, GlobalContext* globalCtx2) {
    DemoKankyo* this = THIS;
    GlobalContext* globalCtx = globalCtx2;
    s16 i;
    f32 temp_f0;

    if (this->unk_164C != 0) {
        Vec3f spB4;
        Vec3f spA8;
        s32 pad;
        GraphicsContext* gfxCtx = globalCtx->state.gfxCtx;

        OPEN_DISPS(gfxCtx);
        func_8012C2DC(gfxCtx);

        for (i = 0; i < globalCtx->envCtx.unk_F2[3]; i++) {
            spB4.x = this->particles[i].unk_1C.x + this->particles[i].unk_04.x;
            spB4.y = this->particles[i].unk_1C.y + this->particles[i].unk_04.y;
            spB4.z = this->particles[i].unk_1C.z + this->particles[i].unk_04.z;
            func_80169474(globalCtx, &spB4, &spA8);
            if ((spA8.x >= 0.0f) && (spA8.x < 320.0f) && (spA8.y >= 0.0f) && (spA8.y < 240.0f)) {
                SysMatrix_InsertTranslation(spB4.x, spB4.y, spB4.z, MTXMODE_NEW);
                temp_f0 = this->particles[i].unk_40 / 50.0f;
                if (temp_f0 > 1.0f) {
                    temp_f0 = 1.0f;
                }
                Matrix_Scale(this->particles[i].unk_44 * temp_f0, this->particles[i].unk_44 * temp_f0,
                             this->particles[i].unk_44 * temp_f0, MTXMODE_APPLY);
                temp_f0 = Math_Vec3f_DistXYZ(&spB4, &globalCtx->view.eye) / 300.0f;
                temp_f0 = (temp_f0 > 1.0f) ? 0.0f : (1.0f - temp_f0) > 1.0f ? 1.0f : 1.0f - temp_f0;

                if (this->actor.params == 1) {
                    this->particles[i].unk_40 = 255.0f * temp_f0;
                } else {
                    this->particles[i].unk_40 = 160.0f * temp_f0;
                }

                gDPPipeSync(POLY_XLU_DISP++);

                switch (i & 1) {
                    case 0:
                        gDPSetPrimColor(POLY_XLU_DISP++, 0, 0, 230, 230, 220, this->particles[i].unk_40);
                        gDPSetEnvColor(POLY_XLU_DISP++, 230, 230, 30, this->particles[i].unk_40);
                        break;

                    case 1:
                        gDPSetPrimColor(POLY_XLU_DISP++, 0, 0, 200, 200, 190, this->particles[i].unk_40);
                        gDPSetEnvColor(POLY_XLU_DISP++, 200, 200, 30, this->particles[i].unk_40);
                        break;
                }

                gSPDisplayList(POLY_XLU_DISP++, &D_04023348);

                SysMatrix_InsertMatrix(&globalCtx->mf_187FC, MTXMODE_APPLY);
                SysMatrix_InsertZRotation_f(globalCtx->state.frames * 20.0f * 0.017453292f, MTXMODE_APPLY);

                gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx),
                          G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

                if (this->actor.params == 1) {
                    gSPDisplayList(POLY_XLU_DISP++, D_06001000);
                } else {
                    gSPDisplayList(POLY_XLU_DISP++, D_04023428);
                }
            }
        }

        CLOSE_DISPS(gfxCtx);
    }
}

void DemoKankyo_Draw(Actor* thisx, GlobalContext* globalCtx) {
    DemoKankyo* this = THIS;

    switch (this->actor.params) {
        case 0:
            func_808CF970(this, globalCtx);
            break;

        case 1:
        case 2:
            func_808CFE04(this, globalCtx);
            break;
    }
}
