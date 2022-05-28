/*
 * File: z_en_al.c
 * Overlay: ovl_En_Al
 * Description: Madame Aroma
 */

#include "z_en_al.h"
#include "objects/object_al/object_al.h"

#define FLAGS (ACTOR_FLAG_1 | ACTOR_FLAG_8 | ACTOR_FLAG_10 | ACTOR_FLAG_20)

#define THIS ((EnAl*)thisx)

void EnAl_Init(Actor* thisx, GlobalContext* globalCtx);
void EnAl_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnAl_Update(Actor* thisx, GlobalContext* globalCtx);
void EnAl_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_80BDF5E8(EnAl* this, GlobalContext* globalCtx);
void func_80BDF6C4(EnAl* this, GlobalContext* globalCtx);

static u8 sSchedule[] = {
    /* 0x00 */ SCHEDULE_CMD_CHECK_NOT_IN_DAY_S(3, 0x11 - 0x04),
    /* 0x04 */ SCHEDULE_CMD_CHECK_TIME_RANGE_S(18, 0, 6, 0, 0x0B - 0x0A),
    /* 0x0A */ SCHEDULE_CMD_RET_NONE(),
    /* 0x0B */ SCHEDULE_CMD_RET_TIME(18, 0, 6, 0, 2),
    /* 0x11 */ SCHEDULE_CMD_CHECK_TIME_RANGE_S(8, 0, 10, 0, 0x46 - 0x17),
    /* 0x17 */ SCHEDULE_CMD_CHECK_TIME_RANGE_S(10, 0, 10, 55, 0x40 - 0x1D),
    /* 0x1D */ SCHEDULE_CMD_CHECK_TIME_RANGE_S(10, 55, 11, 45, 0x30 - 0x23),
    /* 0x23 */ SCHEDULE_CMD_CHECK_TIME_RANGE_S(11, 45, 20, 0, 0x2A - 0x29),
    /* 0x29 */ SCHEDULE_CMD_RET_NONE(),
    /* 0x2A */ SCHEDULE_CMD_RET_TIME(11, 45, 20, 0, 1),
    /* 0x30 */ SCHEDULE_CMD_CHECK_NOT_IN_DAY_S(2, 0x3A - 0x34),
    /* 0x34 */ SCHEDULE_CMD_RET_TIME(10, 55, 11, 45, 1),
    /* 0x3A */ SCHEDULE_CMD_RET_TIME(10, 55, 11, 45, 3),
    /* 0x40 */ SCHEDULE_CMD_RET_TIME(10, 0, 10, 55, 1),
    /* 0x46 */ SCHEDULE_CMD_RET_VAL_L(1),
};

s32 D_80BDFCBC[] = {
    0x09000017, 0x0E27A50C, 0x09000018, 0x0E27A60C, 0x09000017, 0x0E27A70C, 0x09000018, 0x0E27A80C,
    0x09000017, 0x0E27A90C, 0x09000018, 0x0E27AA0C, 0x09000017, 0x0E27AB0C, 0x09000018, 0x0E27AC0C,
    0x09000017, 0x0E27AD2D, 0x000B2D00, 0x080C1159, 0x08090000, 0x10000000,
};

s32 D_80BDFD14[] = {
    0x00562000, 0xA2090000, 0x170E2AA6, 0x0C090000, 0x180E2AA7, 0x0C090000, 0x170E2AA8, 0x0C090000,
    0x180E2AA9, 0x0C090000, 0x170E2AAA, 0x0C090000, 0x180E2AAB, 0x0C090000, 0x170E2AAC, 0x0C090000,
    0x170E2AAD, 0x0C0F2AAE, 0x0C090000, 0x180E2AAF, 0x0C090000, 0x170E2AB0, 0x0C090000, 0x170E2AB1,
    0x0C090000, 0x180E2AB2, 0x0C090000, 0x170E2AB3, 0x0C090000, 0x180E2AB4, 0x0C090000, 0x170E2AB5,
    0x0C090000, 0x180E2AB6, 0x0C090000, 0x170E2AB7, 0x0C090000, 0x180E2AB8, 0x2D00082D, 0x00092D00,
    0x0A0C1156, 0x20121009, 0x0000170E, 0x2AEA0C09, 0x0000180E, 0x2AEB0C09, 0x00001210,
};

s32 D_80BDFDD0[] = { 0x005C0800, 0x0B0E2AE5, 0x2D000811, 0x5C080C10, 0x0E2AE62D, 0x00080C10 };

s32 D_80BDFDE8[] = { 0x0900000E, 0x2B192D00, 0x080C1509, 0x00001210 };

s32 D_80BDFDF8[] = {
    0x09000000, 0x39040071, 0x0E2B1A0C, 0x0F00FF1E, 0x00330018, 0x000D0000, 0x0E2B1B2D, 0x00080C15, 0x09000012,
    0x102C2B1C, 0x0C2F0000, 0x0C19FFDC, 0x2C2B1D0C, 0x2F00000C, 0x0F2B1E0C, 0x0F2B1F0C, 0x122A002E, 0x00390800,
    0x1306006F, 0x00001300, 0x6F2F0000, 0x2E2D0023, 0x0C07000C, 0x06000500, 0x00130005, 0x0C070000, 0x0E2B202D,
    0x00080C16, 0x11390411, 0x390819FF, 0xA60E2B3C, 0x2D00080C, 0x19FF9C00,
};

s32 D_80BDFE7C[] = { 0x0E2A9C2D, 0x00080C10 };

s32 D_80BDFE84[] = { 0x0E2A9D2D, 0x00080C10 };

s32 D_80BDFE8C[] = {
    0x00390200, 0x0F0E2A9E, 0x0C0F2A9F, 0x0C0F2AA0, 0x0C190004, 0x0E2AA00C, 0x05000000, 0x1A001A30, 0x0E2AA20C,
    0x1206008F, 0x00001300, 0x8F2F0000, 0x2E2D002C, 0x2D00080C, 0x10310E2A, 0xA12D0008, 0x0C113902, 0x10000000,
};

s32 D_80BDFED4[] = {
    0x0900002C, 0x2B1D0C2F, 0x00000C0F, 0x2B1E0C0F, 0x2B1F0C12, 0x2A002E00, 0x39080013,
    0x06006F00, 0x0013006F, 0x2F00002E, 0x2D00230C, 0x07000C06, 0x00050000, 0x1300050C,
    0x0700000E, 0x2B202D00, 0x080C1611, 0x39041139, 0x08150900, 0x00121000,
};

s32 D_80BDFF24[] = {
    0x0900002C, 0x2B1C0C0F, 0x00FF1E00, 0x33000DFF, 0xF000000E, 0x2B1B2D00, 0x080C1509, 0x00001210,
    0x2C2B1D0C, 0x2F00000C, 0x0F2B1E0C, 0x0F2B1F0C, 0x122A002E, 0x00390800, 0x1306006F, 0x00001300,
    0x6F2F0000, 0x2E2D0023, 0x0C07000C, 0x06000500, 0x00130005, 0x0C070000, 0x0E2B202D, 0x00080C16,
    0x11390411, 0x390819FF, 0xB10E2B3C, 0x2D00080C, 0x19FFA700,
};

const ActorInit En_Al_InitVars = {
    ACTOR_EN_AL,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_AL,
    sizeof(EnAl),
    (ActorFunc)EnAl_Init,
    (ActorFunc)EnAl_Destroy,
    (ActorFunc)EnAl_Update,
    (ActorFunc)EnAl_Draw,
};

static ColliderCylinderInit sCylinderInit = {
    {
        COLTYPE_HIT1,
        AT_NONE,
        AC_NONE,
        OC1_ON | OC1_TYPE_ALL,
        OC2_TYPE_1,
        COLSHAPE_CYLINDER,
    },
    {
        ELEMTYPE_UNK1,
        { 0x00000000, 0x00, 0x00 },
        { 0x00000000, 0x00, 0x00 },
        TOUCH_NONE | TOUCH_SFX_NORMAL,
        BUMP_NONE,
        OCELEM_ON,
    },
    { 14, 62, 0, { 0, 0, 0 } },
};

static CollisionCheckInfoInit2 sColChkInfoInit = { 0, 0, 0, 0, MASS_IMMOVABLE };

static AnimationInfoS sAnimations[] = {
    { &object_al_Anim_000C54, 1.0f, 0, -1, 0, -4 }, { &object_al_Anim_00DBE0, 1.0f, 0, -1, 0, 0 },
    { &object_al_Anim_00DBE0, 1.0f, 0, -1, 0, -4 }, { &object_al_Anim_00ACA0, 1.0f, 0, -1, 2, 0 },
    { &object_al_Anim_00ACA0, -1.0f, 0, -1, 2, 0 }, { &object_al_Anim_00CA28, 1.0f, 0, -1, 0, -4 },
    { &object_al_Anim_00BCA4, 1.0f, 0, -1, 2, 0 },  { &object_al_Anim_00A764, 1.0f, 0, -1, 0, -4 },
};

Vec3f D_80BE0070 = { 1000.0f, 0.0f, 0.0f };

// clothing display lists
Gfx* D_80BE007C[] = {
    object_al_DL_006598, object_al_DL_005920, object_al_DL_005878,
    object_al_DL_0057D0, object_al_DL_005728, object_al_DL_005680,
};

Actor* EnAl_FindActor(EnAl* this, GlobalContext* globalCtx, u8 actorCategory, s16 actorId) {
    Actor* foundActor = NULL;
    Actor* actorLookahead;

    while (true) {
        foundActor = SubS_FindActor(globalCtx, foundActor, actorCategory, actorId);

        if (foundActor == NULL) {
            break;
        }

        if ((this != (EnAl*)foundActor) && (foundActor->update != NULL)) {
            break;
        }

        actorLookahead = foundActor->next;
        if (actorLookahead == NULL) {
            foundActor = NULL;
            break;
        }
        foundActor = actorLookahead;
    }
    return foundActor;
}

void EnAl_UpdateSkeleton(EnAl* this) {
    this->skelAnime.playSpeed = this->animationSpeed;
    SkelAnime_Update(&this->skelAnime);
}

s32 EnAl_ChangeAnimation(EnAl* this, s32 animId) {
    s32 safeToChangeAnim = false;
    s32 ret = false;

    if ((animId == 1) || (animId == 2)) {
        if ((this->animationId != 1) && (this->animationId != 2)) {
            safeToChangeAnim = true;
        }
    } else if (animId != this->animationId) {
        safeToChangeAnim = true;
    }

    if (safeToChangeAnim) {
        this->animationId = animId;
        ret = SubS_ChangeAnimationByInfoS(&this->skelAnime, sAnimations, animId);
        this->animationSpeed = this->skelAnime.playSpeed;
    }

    return ret;
}

void func_80BDE318(EnAl* this, GlobalContext* globalCtx) {
    s32 pad;
    f32 height;

    Collider_UpdateCylinder(&this->actor, &this->unk_310);
    height = this->actor.focus.pos.y - this->actor.world.pos.y;
    this->unk_310.dim.height = height;
    CollisionCheck_SetOC(globalCtx, &globalCtx->colChkCtx, &this->unk_310.base);
}

Actor* func_80BDE384(EnAl* this, GlobalContext* globalCtx) {
    Actor* actor;

    switch (this->lastScheduleResult) {
        case 2:
            if (!(gSaveContext.save.weekEventReg[89] & 8) && (gSaveContext.save.weekEventReg[85] & 0x80)) {
                actor = EnAl_FindActor(this, globalCtx, ACTORCAT_NPC, ACTOR_EN_PM); // postman
            } else {
                actor = &GET_PLAYER(globalCtx)->actor;
            }
            break;

        case 3:
            actor = this->actorPtr;
            break;

        default:
            actor = &GET_PLAYER(globalCtx)->actor;
            break;
    }

    return actor;
}

// EnAl_TryCutscene
s32 func_80BDE408(EnAl* this, s16 cutscene) {
    s32 ret = false;

    if (ActorCutscene_GetCurrentIndex() == 0x7C) {
        ActorCutscene_Stop(0x7C);
        ActorCutscene_SetIntentToPlay(cutscene);
    } else if (ActorCutscene_GetCanPlayNext(cutscene)) {
        ActorCutscene_StartAndSetUnkLinkFields(cutscene, &this->actor);
        ret = true;
    } else {
        ActorCutscene_SetIntentToPlay(cutscene);
    }
    return ret;
}

// EnAl_GetExtraCutscene ?
s16 func_80BDE484(EnAl* this, s32 arg1) {
    s16 cs = this->actor.cutscene;
    s32 i;

    for (i = 0; i < arg1; i++) {
        cs = ActorCutscene_GetAdditionalCutscene(cs);
    }

    return cs;
}

s32 func_80BDE4E0(EnAl* this, s16* arg1, s16 arg2) {
    s32 ret = false;
    s16 sp42;
    Vec3f sp34;
    Vec3f sp28;
    s32 temp;

    if ((this->actorPtr == NULL) || (this->actorPtr->update == NULL)) {
        return true;
    }

    if (arg2 == *arg1) {
        Actor_PlaySfxAtPos(&this->actor, NA_SE_EV_CHAIR_ROLL);
        EnAl_ChangeAnimation(this, 3);
        this->unk_4E8 = 0;
        (*arg1)++;
    }

    if ((arg2 + 1) == *arg1) {
        Math_Vec3f_Copy(&sp28, &this->actorPtr->world.pos);
        Math_Vec3f_Copy(&sp34, &this->actor.world.pos);
        sp42 = Math_Vec3f_Yaw(&sp34, &sp28);
        temp = sp42 / 364;
        this->unk_4E8++;
        if ((temp != (this->actor.world.rot.y / 364)) && (this->unk_4E8 < 20)) {
            Math_ApproachS(&this->actor.world.rot.y, sp42, 3, 0x2AA8);
        } else {
            EnAl_ChangeAnimation(this, 5);
            this->actor.world.rot.y = sp42;
            this->unk_4E8 = 0;
            (*arg1)++;
            ret = true;
        }
    }
    return ret;
}

s32 func_80BDE678(EnAl* this, s16* arg1, s16 arg2) {
    s32 ret = false;
    s16 sp22;
    s32 temp;

    if ((this->actorPtr == NULL) || (this->actorPtr->update == NULL)) {
        return true;
    }

    if (arg2 == *arg1) {
        Actor_PlaySfxAtPos(&this->actor, NA_SE_EV_CHAIR_ROLL);
        EnAl_ChangeAnimation(this, 4);
        this->unk_4E8 = 0;
        (*arg1)++;
    }

    if ((arg2 + 1) == *arg1) {
        sp22 = this->actor.home.rot.y;
        temp = sp22 / 364;
        this->unk_4E8++;
        if ((temp != (this->actor.world.rot.y / 364)) && (this->unk_4E8 < 20)) {
            Math_ApproachS(&this->actor.world.rot.y, sp22, 3, 0x2AA8);
        } else {
            EnAl_ChangeAnimation(this, 2);
            this->actor.world.rot.y = sp22;
            this->unk_4E8 = 0;
            (*arg1)++;
            ret = true;
        }
    }
    return ret;
}

s32 func_80BDE7FC(EnAl* this, GlobalContext* globalCtx) {
    s32 pad;
    s16 sp2A = func_80BDE484(this, 0);
    s32 pad2;
    s32 sp20 = false;

    switch (this->unk_4E6) {
        case 0:
            if (!func_80BDE408(this, sp2A)) {
                break;
            }

        case 2:
        case 4:
        case 6:
        case 8:
            if ((this->actor.child != NULL) && (this->actor.child->update != NULL)) {
                Camera_SetTargetActor(Play_GetCamera(globalCtx, ActorCutscene_GetCurrentCamera(sp2A)),
                                      this->actor.child);
            }
            this->unk_4E6++;
            sp20 = true;
            break;

        case 1:
        case 3:
        case 5:
        case 7:
            Camera_SetTargetActor(Play_GetCamera(globalCtx, ActorCutscene_GetCurrentCamera(sp2A)), &this->actor);
            this->unk_4E6++;
            sp20 = true;
            break;

        case 9:
            ActorCutscene_Stop(sp2A);
            this->unk_4E6++;
            sp20 = true;
            break;
    }
    return sp20;
}

s32 func_80BDE92C(EnAl* this, GlobalContext* globalCtx) {
    s32 pad[2];
    Actor* gorman = EnAl_FindActor(this, globalCtx, ACTORCAT_NPC, ACTOR_EN_GM);
    Actor* toto = EnAl_FindActor(this, globalCtx, ACTORCAT_NPC, ACTOR_EN_TOTO);

    if ((gorman == NULL) || (gorman->update == NULL) || (toto == NULL) || (toto->update == NULL)) {
        this->unk_4E6++;
        return true;
    }

    switch (this->unk_4E6) {
        case 0:
        case 1:
        case 3:
        case 5:
        case 8:
        case 10:
        case 11:
        case 13:
        case 15:
        case 17:
            this->actor.child = gorman;
            this->unk_4E6++;
            break;

        case 7:
        case 9:
        case 12:
            this->actor.child = toto;
            this->unk_4E6++;
            break;

        case 2:
        case 4:
        case 6:
        case 14:
        case 16:
            this->unk_4E6++;
            break;

        default:
            this->unk_4E6++;
            break;
    }
    return true;
}

s32 func_80BDEA14(EnAl* this, GlobalContext* globalCtx) {
    s32 pad;
    s32 sp18 = false;

    switch (this->unk_4E6) {
        case 0:
        case 1:
            if ((gSaveContext.save.weekEventReg[75] & 2)) {
                sp18 = true;
            } else if (func_80BDE4E0(this, &this->unk_4E6, 0)) {
                sp18 = true;
            }
            break;

        case 2:
        case 3:
            if (func_80BDE678(this, &this->unk_4E6, 2)) {
                sp18 = true;
            }
            break;
    }
    return sp18;
}

// returns pointer to some of our data... gets passed to unk func
s32* func_80BDEABC(EnAl* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);

    if (this->lastScheduleResult == 3) {
        this->unk_4EC = func_80BDE92C;
        return D_80BDFD14;
    }

    switch (this->lastScheduleResult) {
        case 1:
            if (player->transformation == PLAYER_FORM_DEKU) {
                return D_80BDFDD0;
            }

            if (INV_CONTENT(ITEM_MASK_KAFEIS_MASK) != ITEM_MASK_KAFEIS_MASK) {
                return D_80BDFE8C;
            }

            if (Player_GetMask(globalCtx) == PLAYER_MASK_KAFEIS_MASK) {
                return D_80BDFE7C;
            }
            return D_80BDFE84;

        case 2:
            if (!(gSaveContext.save.weekEventReg[89] & 8) && (gSaveContext.save.weekEventReg[85] & 0x80)) {
                this->unk_4EC = func_80BDE7FC;
                return D_80BDFCBC;
            }

            this->unk_4EC = func_80BDEA14;
            if (Player_GetMask(globalCtx) != PLAYER_MASK_KAFEIS_MASK) {
                return D_80BDFDE8;
            }

            if (this->flags & 0x800) {
                return D_80BDFED4;
            }

            if (this->flags & 0x1000) {
                return D_80BDFF24;
            }
            return D_80BDFDF8;
    }
    return NULL;
}

s32 func_80BDEC2C(EnAl* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);
    s32 ret = false;

    if ((this->flags & 7) && Actor_ProcessTalkRequest(&this->actor, &globalCtx->state)) {
        this->flags &= ~0x1800;
        if (player->exchangeItemId == 0x33) {
            this->flags |= 0x800;
            this->unk_4F4 = player->exchangeItemId;
        } else if (player->exchangeItemId != 0) {
            this->flags |= 0x1000;
            this->unk_4F4 = player->exchangeItemId;
        }
        SubS_UpdateFlags(&this->flags, 0, 7);
        this->unk_4E6 = 0;
        this->unk_4EC = 0;
        this->actor.child = this->actorPtr;
        this->dataArrayPtr = func_80BDEABC(this, globalCtx);
        this->flags |= 0x20;
        this->actionFunc = func_80BDF6C4;
        ret = true;
    }

    return ret;
}

void func_80BDED20(EnAl* this) {
    s32 pad;
    Vec3f sp40;
    Vec3f sp34;
    s32 pad2;

    Math_Vec3f_Copy(&sp40, &this->actorPtr->world.pos);
    Math_Vec3f_Copy(&sp34, &this->actor.world.pos);

    Math_ApproachS(&this->unk_4DE, Math_Vec3f_Yaw(&sp34, &sp40) - this->actor.shape.rot.y, 4, 0x2AA8);
    this->unk_4DE = CLAMP(this->unk_4DE, -0x1FFE, 0x1FFE);

    Math_Vec3f_Copy(&sp34, &this->actor.focus.pos);

    if (this->actorPtr->id == ACTOR_PLAYER) {
        sp40.y = ((Player*)this->actorPtr)->bodyPartsPos[7].y + 3.0f; // holding letter to show?
    } else {
        Math_Vec3f_Copy(&sp40, &this->actorPtr->focus.pos);
    }

    Math_ApproachS(&this->unk_4DC, Math_Vec3f_Pitch(&sp34, &sp40), 4, 0x2AA8);
    this->unk_4DC = CLAMP(this->unk_4DC, -0x1554, 0x1554);
}

void func_80BDEE5C(EnAl* this) {
    if (this->flags & 0x20) {
        if ((this->actorPtr != NULL) && (this->actorPtr->update != NULL)) {
            if (DECR(this->stateTimer) == 0) {
                func_80BDED20(this);
                this->flags &= ~0x200;
                this->flags |= 0x80;
                return;
            }
        }
    }

    if (this->flags & 0x80) {
        this->flags &= ~0x80;
        this->unk_4DC = 0;
        this->unk_4DE = 0;
        this->stateTimer = 0x14;
    } else if (DECR(this->stateTimer) == 0) {
        this->flags |= 0x200;
    }
}

// unk func 1
void func_80BDEF3C(EnAl* this, GlobalContext* globalCtx) {
    if (this->unk_4E4 == 0) {
        EnAl_ChangeAnimation(this, 7);
        this->flags &= ~0x20;
        this->flags |= 0x200;
        this->unk_4E4++;
    } else if ((this->unk_4E4 == 1) && Animation_OnFrame(&this->skelAnime, this->skelAnime.endFrame)) {
        EnAl_ChangeAnimation(this, 0);
        this->flags &= ~0x200;
        this->flags |= 0x20;
        this->unk_4E4++;
    }
}

// unk func 2
void func_80BDEFE4(EnAl* this, GlobalContext* globalCtx) {
    if (this->unk_4E4 == 0) {
        EnAl_ChangeAnimation(this, 6);
        this->unk_4E4 += 1;
    } else if ((this->unk_4E4 == 1) && Animation_OnFrame(&this->skelAnime, this->skelAnime.endFrame)) {
        EnAl_ChangeAnimation(this, 5);
        this->unk_4E4 += 1;
    }
}

s32 func_80BDF064(EnAl* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);
    u16 currentTextId = globalCtx->msgCtx.currentTextId;
    Actor* gorman = EnAl_FindActor(this, globalCtx, ACTORCAT_NPC, ACTOR_EN_GM);
    Actor* toto = EnAl_FindActor(this, globalCtx, ACTORCAT_NPC, ACTOR_EN_TOTO);

    if (player->stateFlags1 & 0x40) {
        this->flags |= 0x400;
        if (this->lastTextId != currentTextId) {
            switch (currentTextId) {
                case 0x2AA6:
                case 0x2AAF:
                case 0x2AB4:
                    if ((gorman != NULL) && (gorman->update != NULL)) {
                        this->actorPtr = gorman;
                    }
                    break;

                case 0x2AAD:
                case 0x2AB0:
                    if ((toto != NULL) && (toto->update != NULL)) {
                        this->actorPtr = toto;
                    }
                    break;
            }

            switch (currentTextId) {
                case 0x2AA1:
                case 0x2AA2:
                case 0x2AA7:
                case 0x2AE6:
                case 0x2AE8:
                case 0x2AE9:
                case 0x2AB4:
                    this->unkFuncPtr = func_80BDEF3C;
                    this->unk_4E4 = 0;
                    break;

                case 0x27A6:
                case 0x27A8:
                case 0x27AA:
                case 0x2B1E:
                    this->unkFuncPtr = func_80BDEFE4;
                    this->unk_4E4 = 0;
                    break;

                case 0x2B19:
                case 0x2B20:
                case 0x2B3C:
                    EnAl_ChangeAnimation(this, 5);
                    break;
            }
        }
        this->lastTextId = currentTextId;
    } else if (this->flags & 0x400) {
        this->lastTextId = 0;
        this->flags &= ~0x400;
    }

    if (this->unkFuncPtr != NULL) {
        this->unkFuncPtr(this, globalCtx);
    }

    return false;
}

s32 EnAl_CheckForGormanAndToto(EnAl* this, GlobalContext* globalCtx, ScheduleResult* unused) {
    s32 ret = false;
    Actor* gorman = EnAl_FindActor(this, globalCtx, ACTORCAT_NPC, ACTOR_EN_GM);
    Actor* toto = EnAl_FindActor(this, globalCtx, ACTORCAT_NPC, ACTOR_EN_TOTO);

    if ((gorman != NULL) && (gorman->update != NULL) && (toto != NULL) && (toto->update != NULL)) {
        EnAl_ChangeAnimation(this, 0);
        SubS_UpdateFlags(&this->flags, 3, 7);
        this->actorPtr = gorman;
        this->flags |= 0x20;
        ret = true;
    }
    return ret;
}

// EnAl_Update... what exactly?
s32 func_80BDF308(EnAl* this, GlobalContext* globalCtx, ScheduleResult* scheduleResult) {
    SubS_UpdateFlags(&this->flags, 3, 7);

    switch (scheduleResult->result) {
        case 1:
            EnAl_ChangeAnimation(this, 0);
            break;

        case 2:
            this->unk_4F0 = EXCH_ITEM_NONE;
            this->unk_4EA = 0;
            EnAl_ChangeAnimation(this, 2);
            break;
    }
    return true;
}

s32 func_80BDF390(EnAl* this, GlobalContext* globalCtx, ScheduleResult* scheduleResult) {
    s32 ret;

    this->actor.flags |= ACTOR_FLAG_1;
    this->actor.targetMode = 0;
    this->unk_4F0 = EXCH_ITEM_NONE;
    this->flags = 0;
    this->unk_4D4 = 40.0f;

    switch (scheduleResult->result) {
        case 3:
            ret = EnAl_CheckForGormanAndToto(this, globalCtx, scheduleResult);
            break;

        case 1:
        case 2:
            ret = func_80BDF308(this, globalCtx, scheduleResult);
            break;

        default:
            ret = false;
            break;
    }
    return ret;
}

void func_80BDF414(EnAl* this, GlobalContext* globalCtx) {
    s16 temp_v0;

    switch (this->unk_4EA) {
        case 0:
        case 1:
            if (!(gSaveContext.save.weekEventReg[89] & 8)) {
                if (gSaveContext.save.weekEventReg[85] & 0x80) {
                    func_80BDE4E0(this, &this->unk_4EA, 0);
                }
            }
            break;

        case 2:
            if (gSaveContext.save.weekEventReg[89] & 8) {
                this->unk_4EA++;
            }
            break;

        case 3:
        case 4:
            func_80BDE678(this, &this->unk_4EA, 3);
            break;
    }

    temp_v0 = this->actor.world.rot.y - this->actor.yawTowardsPlayer;
    if (((this->unk_4EA == 0) && (ABS_ALT(temp_v0) >= 0x5800)) ||
        ((this->unk_4EA == 5) && (ABS_ALT(temp_v0) >= 0x5800)) || (this->unk_4EA == 2)) {
        SubS_UpdateFlags(&this->flags, 3, 7);
    } else {
        SubS_UpdateFlags(&this->flags, 0, 7);
    }
}

// weirdly, this is not an actionfunc but a regular func
void EnAl_DoNothing(EnAl* this, GlobalContext* globalCtx) {
}

void func_80BDF578(EnAl* this, GlobalContext* globalCtx) {
    switch (this->lastScheduleResult) {
        case 1:
        case 3:
            EnAl_DoNothing(this, globalCtx);
            break;

        case 2:
            func_80BDF414(this, globalCtx);
            break;
    }

    Math_ApproachS(&this->actor.shape.rot.y, this->actor.world.rot.y, 3, 0x2AA8);
}

void func_80BDF5E8(EnAl* this, GlobalContext* globalCtx) {
    ScheduleResult scheduleResult;

    this->unk_4E0 = REG(15) + ((void)0, gSaveContext.save.daySpeed);
    if (!Schedule_RunScript(globalCtx, sSchedule, &scheduleResult) ||
        ((this->lastScheduleResult != scheduleResult.result) && !func_80BDF390(this, globalCtx, &scheduleResult))) {
        this->actor.shape.shadowDraw = NULL;
        this->actor.flags &= ~ACTOR_FLAG_1;
        scheduleResult.result = 0;
    } else {
        this->actor.shape.shadowDraw = ActorShadow_DrawCircle;
        this->actor.flags |= ACTOR_FLAG_1;
    }
    this->lastScheduleResult = scheduleResult.result;
    this->actorPtr = func_80BDE384(this, globalCtx);
    func_80BDF578(this, globalCtx);
}

void func_80BDF6C4(EnAl* this, GlobalContext* globalCtx) {
    // most of our data is here
    if (func_8010BF58(&this->actor, globalCtx, this->dataArrayPtr, this->unk_4EC, &this->unk_364)) {
        SubS_UpdateFlags(&this->flags, 3, 7);
        this->flags &= ~0x20;
        this->flags |= 0x200;
        this->actor.child = NULL;
        this->stateTimer = 20;
        this->unk_364 = 0;
        this->actionFunc = func_80BDF5E8;
    } else {
        Math_ApproachS(&this->actor.shape.rot.y, this->actor.world.rot.y, 3, 0x2AA8);
    }
}

void EnAl_Init(Actor* thisx, GlobalContext* globalCtx) {
    EnAl* this = THIS;

    ActorShape_Init(&this->actor.shape, 0.0f, NULL, 0.0f);
    SkelAnime_InitFlex(globalCtx, &this->skelAnime, &object_al_Skel_00A0D8, NULL, this->jointTable, this->morphTable,
                       27);
    this->animationId = -1;
    EnAl_ChangeAnimation(this, 1);
    Collider_InitAndSetCylinder(globalCtx, &this->unk_310, &this->actor, &sCylinderInit);
    CollisionCheck_SetInfo2(&this->actor.colChkInfo, DamageTable_Get(0x16), &sColChkInfoInit);
    Actor_SetScale(&this->actor, 0.01f);
    this->lastScheduleResult = 0;
    this->actionFunc = func_80BDF5E8;

    this->actionFunc(this, globalCtx);
}

void EnAl_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    EnAl* this = THIS;

    Collider_DestroyCylinder(globalCtx, &this->unk_310);
}

void EnAl_Update(Actor* thisx, GlobalContext* globalCtx) {
    EnAl* this = THIS;

    func_80BDEC2C(this, globalCtx);

    this->actionFunc(this, globalCtx);

    func_80BDF064(this, globalCtx);

    if (this->lastScheduleResult != 0) {
        EnAl_UpdateSkeleton(this);
        func_80BDEE5C(this);
        func_8013C964(&this->actor, globalCtx, this->unk_4D4, 30.0f, this->unk_4F0, this->flags & (0x1 + 0x2 + 0x4));
        func_80BDE318(this, globalCtx);
    }
}

s32 EnAl_OverrideLimbDraw(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, Actor* thisx) {
    switch (limbIndex) {
        case 3:
        case 11:
        case 12:
        case 13:
        case 14:
        case 15: // wat? we're just nulling that many limbs?
            *dList = NULL;
            break;

        case 16:
            break;
    }
    return false;
}

void EnAl_PostLimbDraw(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3s* rot, Actor* thisx) {
    EnAl* this = THIS;

    switch (limbIndex) {
        case 3:
            Matrix_Get(&this->limbMatrixes[0]);
            break;

        case 11:
            Matrix_Get(&this->limbMatrixes[1]);
            break;

        case 12:
            Matrix_Get(&this->limbMatrixes[2]);
            break;

        case 13:
            Matrix_Get(&this->limbMatrixes[3]);
            break;

        case 14:
            Matrix_Get(&this->limbMatrixes[4]);
            break;

        case 15:
            Matrix_Get(&this->limbMatrixes[5]);
            break;

        case 16:
            Matrix_MultVec3f(&D_80BE0070, &this->actor.focus.pos);
            Math_Vec3s_Copy(&this->actor.focus.rot, &this->actor.world.rot);
            break;
    }
}

void EnAl_TransformLimbDraw(GlobalContext* globalCtx, s32 limbIndex, Actor* thisx) {
    EnAl* this = THIS;
    s32 stepRot;
    s32 overrideRot;

    if (!(this->flags & 0x200)) {
        if (this->flags & 0x80) {
            overrideRot = true;
        } else {
            overrideRot = false;
        }
        stepRot = true;
    } else {
        overrideRot = false;
        stepRot = false;
    }

    if (limbIndex == 16) {
        SubS_UpdateLimb(this->unk_4DC + 0x4000, this->unk_4DE + this->actor.shape.rot.y + 0x4000, &this->unk_36C,
                        &this->limb16Rot, stepRot, overrideRot);
        Matrix_Pop();
        Matrix_Translate(this->unk_36C.x, this->unk_36C.y, this->unk_36C.z, MTXMODE_NEW);
        Matrix_Scale(this->actor.scale.x, this->actor.scale.y, this->actor.scale.z, MTXMODE_APPLY);
        Matrix_RotateYS(this->limb16Rot.y, MTXMODE_APPLY);
        Matrix_RotateXS(this->limb16Rot.x, MTXMODE_APPLY);
        Matrix_RotateZS(this->limb16Rot.z, MTXMODE_APPLY);
        Matrix_Push();
    }
}

void EnAl_Draw(Actor* thisx, GlobalContext* globalCtx) {
    EnAl* this = THIS;
    s32 i;

    if (this->lastScheduleResult != 0) {
        OPEN_DISPS(globalCtx->state.gfxCtx);

        func_8012C28C(globalCtx->state.gfxCtx);
        Matrix_Translate(0.0f, 0.0f, 850.0f, MTXMODE_APPLY);
        SkelAnime_DrawTransformFlexOpa(globalCtx, this->skelAnime.skeleton, this->skelAnime.jointTable,
                                       this->skelAnime.dListCount, EnAl_OverrideLimbDraw, EnAl_PostLimbDraw,
                                       EnAl_TransformLimbDraw, &this->actor);

        for (i = 0; i < ARRAY_COUNT(this->limbMatrixes); i++) {
            Matrix_Put(&this->limbMatrixes[i]);

            gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx),
                      G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
            gSPDisplayList(POLY_OPA_DISP++, D_80BE007C[i]);
        }

        CLOSE_DISPS(globalCtx->state.gfxCtx);
    }
}
