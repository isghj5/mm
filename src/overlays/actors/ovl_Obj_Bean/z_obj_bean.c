/*
 * File: z_obj_bean.c
 * Overlay: ovl_Obj_Bean
 * Description: Floating Bean Plant / Soft Soil
 *   This actor does NOT accept bugs for skulltula/other rewards, that is another actor placed on top of this one
 */

#include "z_obj_bean.h"
#include "objects/object_mamenoki/object_mamenoki.h"
#include "objects/gameplay_keep/gameplay_keep.h"

#define FLAGS (ACTOR_FLAG_400000)

#define THIS ((ObjBean*)thisx)

void ObjBean_Init(Actor* thisx, PlayState* play);
void ObjBean_Destroy(Actor* thisx, PlayState* play);
void ObjBean_Update(Actor* thisx, PlayState* play);
void ObjBean_UpdateAlt(Actor* thisx, PlayState* play);
void ObjBean_Draw(Actor* thisx, PlayState* play);
void ObjBean_DrawWallCrack(Actor* thisx, PlayState* play);

void ObjBean_SetupUnkFuncDoNothing(ObjBean* this);
void ObjBean_UnkFuncDoNothing(ObjBean* this);
void func_80937CA0(ObjBean* this);
void func_80937CE4(ObjBean* this);
void func_80937D54(ObjBean* this);
void func_80937DD8(ObjBean* this);
void func_80937DEC(ObjBean* this, PlayState* play);
void func_80937FB0(ObjBean* this);
void func_80937FC8(ObjBean* this, PlayState* play);
void func_809381B0(ObjBean* this);
void func_809381C4(ObjBean* this, PlayState* play);
void func_80938284(ObjBean* this);
void func_80938298(ObjBean* this, PlayState* play);
void func_8093833C(ObjBean* this);
void func_80938358(ObjBean* this, PlayState* play);
void func_809383B4(ObjBean* this);
void func_809383D0(ObjBean* this, PlayState* play);
void func_80938408(ObjBean* this);
void func_80938444(ObjBean* this, PlayState* play);
void func_809384E8(ObjBean* this);
void func_80938504(ObjBean* this, PlayState* play);
void func_80938588(ObjBean* this);
void func_809385A8(ObjBean* this, PlayState* play);
void ObjBean_SetupGrowPlatform(ObjBean* this);
void ObjBean_GrowPlatform(ObjBean* this, PlayState* play);
void ObjBean_SetupWaitForWater(ObjBean* this);
void ObjBean_WaitForWater(ObjBean* this, PlayState* play);
void ObjBean_SetupGrowSeedlingCutscene(ObjBean* this);
void ObjBean_GrowSeedlingCutscene(ObjBean* this, PlayState* play);
void ObjBean_SetupPlatformWaitForPlayer(ObjBean* this);
void ObjBean_PlatformWaitForPlayer(ObjBean* this, PlayState* play);
void ObjBean_SetupPlatformFly(ObjBean* this);
void ObjBean_PlatformFly(ObjBean* this, PlayState* play);
void ObjBean_SetupWaitForStepOff(ObjBean* this);
void ObjBean_WaitForStepOff(ObjBean* this, PlayState* play);
void func_809389BC(ObjBean* this, PlayState* play);
void func_80938A14(ObjBean* this);
void func_80938A5C(ObjBean* this, PlayState* play);
void func_80938AA4(ObjBean* this);
void func_80938AD8(ObjBean* this, PlayState* play);

const ActorInit Obj_Bean_InitVars = {
    ACTOR_OBJ_BEAN,
    ACTORCAT_BG,
    FLAGS,
    OBJECT_MAMENOKI,
    sizeof(ObjBean),
    (ActorFunc)ObjBean_Init,
    (ActorFunc)ObjBean_Destroy,
    (ActorFunc)ObjBean_Update,
    (ActorFunc)NULL,
};

static ColliderCylinderInit sCylinderInit1 = {
    {
        COLTYPE_NONE,
        AT_NONE,
        AC_NONE,
        OC1_ON | OC1_TYPE_PLAYER,
        OC2_TYPE_2,
        COLSHAPE_CYLINDER,
    },
    {
        ELEMTYPE_UNK0,
        { 0x00000000, 0x00, 0x00 },
        { 0x00000000, 0x00, 0x00 },
        TOUCH_NONE | TOUCH_SFX_NORMAL,
        BUMP_NONE,
        OCELEM_ON,
    },
    { 64, 30, -31, { 0, 0, 0 } },
};

static ColliderCylinderInit sCylinderInit2 = {
    {
        COLTYPE_NONE,
        AT_NONE,
        AC_ON | AC_TYPE_OTHER,
        OC1_NONE,
        OC2_TYPE_2,
        COLSHAPE_CYLINDER,
    },
    {
        ELEMTYPE_UNK0,
        { 0x00000000, 0x00, 0x00 },
        { 0xF7CFFFFF, 0x00, 0x00 },
        TOUCH_NONE | TOUCH_SFX_NORMAL,
        BUMP_ON,
        OCELEM_NONE,
    },
    { 10, 10, 0, { 0, 0, 0 } },
};

// xz values 
static Vec2f sPlatformSpeeds[] = {
    { 3.0f, 0.3f },
    { 10.0f, 0.5f },
    { 30.0f, 0.5f },
    { 3.0f, 0.3f },
};


// TODO better name?
void ObjBean_UpdateFloorHeight(ObjBean* this, PlayState* play) {
    Vec3f sp24;
    s32 sp20;

    sp24.x = this->dyna.actor.world.pos.x;
    sp24.y = this->dyna.actor.world.pos.y + 29.999998f;
    sp24.z = this->dyna.actor.world.pos.z;
    this->dyna.actor.floorHeight =
        BgCheck_EntityRaycastFloor5(&play->colCtx, &this->dyna.actor.floorPoly, &sp20, &this->dyna.actor, &sp24);
}

s32 ObjBean_CheckAgainstBGSurface(ObjBean* this, PlayState* play) {
    static Vec3f D_80939018 = { 0.0f, 30.0f, 0.0f };
    s32 pad;
    s32 bgId;
    Vec3f spAC;
    Vec3f posA;
    Vec3f posB;
    Vec3f posResult;
    MtxF sp48;

    Matrix_RotateYS(this->dyna.actor.shape.rot.y, MTXMODE_NEW);
    Matrix_RotateXS(this->dyna.actor.shape.rot.x, MTXMODE_APPLY);
    Matrix_RotateZS(this->dyna.actor.shape.rot.z, MTXMODE_APPLY);
    Matrix_MultVec3f(&D_80939018, &spAC);
    Math_Vec3f_Sum(&this->dyna.actor.world.pos, &spAC, &posA);
    Math_Vec3f_Diff(&this->dyna.actor.world.pos, &spAC, &posB);

    // four trues: checkWall, checkFloor, checkCeil, checkOneFace
    if (BgCheck_EntityLineTest2(&play->colCtx, &posA, &posB, &posResult, &this->dyna.actor.floorPoly, true, true, true, true,
                                &bgId, &this->dyna.actor)) {
        this->dyna.actor.world.pos.x = (COLPOLY_GET_NORMAL(this->dyna.actor.floorPoly->normal.x) * 1.9f) + posResult.x;
        this->dyna.actor.world.pos.y = (COLPOLY_GET_NORMAL(this->dyna.actor.floorPoly->normal.y) * 1.9f) + posResult.y;
        this->dyna.actor.world.pos.z = (COLPOLY_GET_NORMAL(this->dyna.actor.floorPoly->normal.z) * 1.9f) + posResult.z;
        func_800C0094(this->dyna.actor.floorPoly, this->dyna.actor.world.pos.x, this->dyna.actor.world.pos.y,
                      this->dyna.actor.world.pos.z, &sp48);
        Matrix_Put(&sp48);
        Matrix_RotateYS(this->dyna.actor.shape.rot.y, MTXMODE_APPLY);
        Matrix_Get(&sp48);
        Matrix_MtxFToYXZRot(&sp48, &this->dyna.actor.shape.rot, false);
        return true;
    } else {
        return false;
    }
}

void ObjBean_TimerReset(ObjBean* this) {
    this->timer1AC = this->unk_1AE = this->unk_1B0 = 0;
    this->unk_1C8 = 0.0f;
}

// Platform shrinks and grows in waves
void ObjBean_PlatformUndulate(ObjBean* this) {
    this->timer1AC += 0xB6;
    this->unk_1AE += 0xFB;
    this->unk_1B0 += 100;
    Math_StepToF(&this->unk_1C8, 2.0f, 0.1f);
    this->posOffsetX = (Math_SinS(this->timer1AC * 3) + Math_SinS(this->unk_1AE * 3)) * this->unk_1C8;
    this->posOffsetZ = (Math_CosS(this->timer1AC * 4) + Math_CosS(this->unk_1AE * 4)) * this->unk_1C8;
    this->dyna.actor.scale.z =
        ((Math_SinS(this->unk_1B0 * 5) * 0.06f) + (Math_SinS(this->unk_1AE * 8) * 0.01f) + 1.07f) * 0.1f;
    this->dyna.actor.scale.x = this->dyna.actor.scale.z;
    this->dyna.actor.scale.y = ((Math_CosS(this->unk_1B0 * 10) * 0.2f) + 1.0f) * 0.1f;
    this->dyna.actor.shape.rot.y = (this->dyna.actor.home.rot.y + (s32)(Math_SinS(this->timer1AC * 3) * 1000.0f)) +
                                   (s32)(Math_SinS(this->unk_1B0 * 2) * 2100.0f);
}

void func_80937130(ObjBean* this) {
    this->timer1AC = this->unk_1AE = this->unk_1B0 = 0;
    Actor_SetScale(&this->dyna.actor, 0.0f);
}

void func_80937160(ObjBean* this) {
    this->timer1AC += 0x384;
    if (this->timer1AC > 0x5FFF) {
        this->timer1AC = 0x5FFF;
    }

    this->unk_1AE += 0x258;
    if (this->unk_1AE > 0x4000) {
        this->unk_1AE = 0x4000;
    }

    this->dyna.actor.scale.y = Math_SinS(this->timer1AC) * 0.16970563f;
    this->dyna.actor.scale.x = this->dyna.actor.scale.z = Math_SinS(this->unk_1AE) * 0.10700001f;
    Math_StepToF(&this->posOffsetX, 0.0f, 0.1f);
    Math_StepToF(&this->posOffsetZ, 0.0f, 0.1f);
    Math_ScaledStepToS(&this->dyna.actor.shape.rot.y, this->dyna.actor.home.rot.y, 100);
}

void ObjBean_Move(ObjBean* this) {
    this->dyna.actor.world.pos.x = this->pathPoint.x + this->posOffsetX;
    this->dyna.actor.world.pos.y = this->pathPoint.y;
    this->dyna.actor.world.pos.z = this->pathPoint.z + this->posOffsetZ;
}

void ObjBean_SetupPathCount(ObjBean* this, PlayState* play) {
    this->pathNodeCount = play->setupPathList[OBJBEAN_GET_PATH(&this->dyna.actor)].count - 1;
    this->currentPointIndex = 0;
    this->nextPointIndex = 1;
}

// todo better name, as its converting from one type to another
void ObjBean_CopyPathPoints(ObjBean* this) {
    Math_Vec3s_ToVec3f(&this->pathPoint, this->pathPoints);
}

void ObjBean_FollowPath(ObjBean* this) {
    Actor* actor = &this->dyna.actor;
    Vec3f sp38;
    f32 mag;
    f32 unkx;
    f32 unkz;

    Math_Vec3s_ToVec3f(&sp38, &this->pathPoints[this->nextPointIndex]);
    Math_Vec3f_Diff(&sp38, &this->pathPoint, &actor->velocity);

    mag = Math3D_Vec3fMagnitude(&actor->velocity);
    unkx = sPlatformSpeeds[this->platformSpeedIndex].x;
    unkz = sPlatformSpeeds[this->platformSpeedIndex].z;
    if (mag < (actor->speedXZ * 8.0f)) {
        unkx = ((unkx - 2.0f) * 0.1f) + 2.0f;
        unkz *= 0.4f;
    }

    Math_StepToF(&actor->speedXZ, unkx, unkz);

    if ((actor->speedXZ + 0.05f) < mag) {
        Math_Vec3f_Scale(&actor->velocity, actor->speedXZ / mag);
        this->pathPoint.x += actor->velocity.x;
        this->pathPoint.y += actor->velocity.y;
        this->pathPoint.z += actor->velocity.z;
    } else {
        Math_Vec3f_Copy(&this->pathPoint, &sp38);
        this->currentPointIndex = this->nextPointIndex;
        if (this->currentPointIndex >= this->pathNodeCount) {
            this->nextPointIndex = 0;
        } else {
            this->nextPointIndex++;
        }
        actor->speedXZ *= 0.5f;
    }
}

// Epona and other horses break the platform
s32 ObjBean_CheckForHorseTrample(ObjBean* this, PlayState* play) {
    Actor* bgActor = play->actorCtx.actorLists[ACTORCAT_BG].first;

    while (bgActor != NULL) {
        if ((bgActor->id == ACTOR_EN_HORSE) &&
            (Math3D_Vec3fDistSq(&bgActor->world.pos, &this->dyna.actor.world.pos) < SQ(100.0f))) {
            return true;
        }
        bgActor = bgActor->next;
    }

    return false;
}

ObjBean* ObjBean_SearchForBean(ObjBean* this, PlayState* play) {
    Actor* bgActor = play->actorCtx.actorLists[ACTORCAT_BG].first;
    s32 params = OBJBEAN_GET_3F80(&this->dyna.actor, 0);

    while (bgActor != NULL) {
        if (bgActor->id == ACTOR_OBJ_BEAN) {
            s32 type = OBJBEAN_GET_TYPE(bgActor);

            if ((type == ENOBJBEAN_GET_C000_0) && (bgActor->room == this->dyna.actor.room) && !OBJBEAN_GET_80(bgActor) &&
                (params == OBJBEAN_GET_SWITCHFLAG(bgActor, 0)) &&
                (Math3D_Vec3fDistSq(&bgActor->world.pos, &this->dyna.actor.world.pos) < SQ(10.0f))) {
                break;
            }
        }
        bgActor = bgActor->next;
    }

    return (ObjBean*)bgActor;
}

void func_809375C8(ObjBean* this, PlayState* play) {
    ObjBean* bean = ObjBean_SearchForBean(this, play);

    if (bean != NULL) {
        bean->crossBeanFlag = 1;
    }
}

// spawning leaves when killed by horse?
void func_809375F4(ObjBean* this, PlayState* play) {
    static Gfx* D_80939024[] = {
        gKakeraLeafMiddle,
        gKakeraLeafTip,
    };
    Vec3f spC4;
    Vec3f spB8;
    f32 temp_f20;
    s32 temp_s2;
    s16 temp_s1 = 0;
    s32 phi_s3;
    s32 phi_v0;
    s32 i;

    for (i = 0; i < 36; i++) {
        temp_s1 += 0x4E20;
        temp_f20 = Rand_ZeroOne() * 60.0f;

        spC4.x = (Math_SinS(temp_s1) * temp_f20) + this->dyna.actor.world.pos.x;
        spC4.y = this->dyna.actor.world.pos.y;
        spC4.z = (Math_CosS(temp_s1) * temp_f20) + this->dyna.actor.world.pos.z;

        spB8.x = Math_SinS(temp_s1) * 3.5f;
        spB8.y = Rand_ZeroOne() * 13.0f;
        spB8.z = Math_CosS(temp_s1) * 3.5f;

        spB8.x += this->dyna.actor.world.pos.x - this->dyna.actor.prevPos.x;
        spB8.y += this->dyna.actor.world.pos.y - this->dyna.actor.prevPos.y;
        spB8.z += this->dyna.actor.world.pos.z - this->dyna.actor.prevPos.z;

        temp_s2 = (s32)(Rand_ZeroOne() * 180.0f) + 30;

        phi_v0 = 0x40;
        if (temp_s2 < 0x5A) {
            phi_s3 = -0x50;
            if (Rand_ZeroOne() < 0.1f) {
                phi_v0 = 0x60;
            } else {
                phi_v0 = 0x40;
            }
        } else {
            phi_s3 = -100;
            phi_v0 = 0x40;
        }
        EffectSsKakera_Spawn(play, &spC4, &spB8, &spC4, phi_s3, phi_v0, 40, 3, 0, temp_s2, 0, 0, (temp_s2 >> 3) + 40,
                             -1, GAMEPLAY_KEEP, D_80939024[i & 1]);
    }
}

static InitChainEntry sInitChain[] = {
    ICHAIN_VEC3F_DIV1000(scale, 100, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneForward, 2500, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneScale, 200, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneDownward, 200, ICHAIN_STOP),
};

void ObjBean_Init(Actor* thisx, PlayState* play) {
    s32 pad;
    ObjBean* this = THIS;
    s32 type = OBJBEAN_GET_TYPE(&this->dyna.actor);

    Actor_ProcessInitChain(&this->dyna.actor, sInitChain);
    this->drawFlags = OBJBEAN_DRAWFLAG_NONE;
    this->unk_1B8 = 0.1f;
    DynaPolyActor_Init(&this->dyna, 3);
    Collider_InitCylinder(play, &this->collider);

    // pathless? there is a tatl prompt...
    if ((type == ENOBJBEAN_GET_PATHLESS_SOIL) || (type == ENOBJBEAN_GET_WALLCRACK)) {
        this->dyna.actor.update = ObjBean_UpdateAlt;
        this->dyna.actor.textId = 0xFD; //  Tatl: this is soft soil
        if (type == ENOBJBEAN_GET_PATHLESS_SOIL) {
            Collider_SetCylinder(play, &this->collider, &this->dyna.actor, &sCylinderInit2);
            Collider_UpdateCylinder(&this->dyna.actor, &this->collider);
        }
        this->dyna.actor.flags |= ACTOR_FLAG_10;
        ObjBean_SetupUnkFuncDoNothing(this);
        if (!ObjBean_CheckAgainstBGSurface(this, play)) { // if we are floating off-surface, cull
            Actor_MarkForDeath(&this->dyna.actor);
        } else {
            func_800BC154(play, &play->actorCtx, &this->dyna.actor, 7);
            func_80937DD8(this);
        }
    } else { // platform? it draws platform but draw is turned OFF to start then waits for water?
        s32 pathIndex = OBJBEAN_GET_PATH(&this->dyna.actor);
        Path* path = &play->setupPathList[pathIndex];

        this->platformSpeedIndex = OBJBEAN_GETZ_PLATFORM_SPEED_INDEX(&this->dyna.actor);
        this->dyna.actor.world.rot.z = 0;
        this->dyna.actor.home.rot.z = 0;
        this->dyna.actor.shape.rot.z = 0;
        this->drawFlags |= OBJBEAN_DRAWFLAG_PLATFORM;

        DynaPolyActor_LoadMesh(play, &this->dyna, &gMagicBeanPlatformCol);
        Collider_SetCylinder(play, &this->collider, &this->dyna.actor, &sCylinderInit1);
        Collider_UpdateCylinder(&this->dyna.actor, &this->collider);

        this->pathPoints = Lib_SegmentedToVirtual(path->points);

        ObjBean_SetupPathCount(this, play);
        ObjBean_CopyPathPoints(this);
        ObjBean_Move(this);
        ActorShape_Init(&this->dyna.actor.shape, 0.0f, ActorShadow_DrawCircle, 8.8f);
        ObjBean_UpdateFloorHeight(this, play);

        if (!OBJBEAN_GET_80(&this->dyna.actor) && Flags_GetSwitch(play, OBJBEAN_GET_SWITCHFLAG(&this->dyna.actor, 0)) &&
            !Flags_GetSwitch(play, OBJBEAN_GET_SWITCHFLAG(&this->dyna.actor, 1)) && func_800FE9B4(play)) {
            Flags_SetSwitch(play, OBJBEAN_GET_SWITCHFLAG(&this->dyna.actor, 1));
        }

        if (OBJBEAN_GET_80(&this->dyna.actor) || Flags_GetSwitch(play, OBJBEAN_GET_SWITCHFLAG(&this->dyna.actor, 1))) {
            ObjBean_SetupPlatformWaitForPlayer(this);
        } else {
            func_800C62BC(play, &play->colCtx.dyna, this->dyna.bgId);
            ObjBean_SetupWaitForWater(this);
        }
    }
}

void ObjBean_Destroy(Actor* thisx, PlayState* play) {
    ObjBean* this = THIS;

    DynaPoly_DeleteBgActor(play, &play->colCtx.dyna, this->dyna.bgId);
    Collider_DestroyCylinder(play, &this->collider);
}

void func_80937B54(ObjBean* this) {
    Math_StepToS(&this->unk_1EE, this->unk_1F0, this->unk_1F2);
    Math_StepToS(&this->unk_1F4, this->unk_1F6, this->unk_1F8);
    this->unk_1FA += this->unk_1F4;
    this->unk_1FC = 6372.0f - (Math_SinS(this->unk_1FA) * this->unk_1EE);
    this->dyna.actor.scale.y = Math_SinS(this->unk_1FC) * 0.17434467f;
    this->dyna.actor.scale.x = this->dyna.actor.scale.z = Math_CosS(this->unk_1FC) * 0.12207746f;
}

// sets a do nothing function
void ObjBean_SetupUnkFuncDoNothing(ObjBean* this) {
    this->unkFunc1E8 = ObjBean_UnkFuncDoNothing;
}

void ObjBean_UnkFuncDoNothing(ObjBean* this) {
}

void func_80937C30(ObjBean* this) {
    this->unkFunc1E8 = func_80937CA0;
    this->stateTimer2 = Rand_S16Offset(12, 40);
    this->unk_1F0 = Rand_S16Offset(200, 400);
    this->unk_1F2 = 20;
    this->unk_1F6 = Rand_S16Offset(100, 800);
    this->unk_1F8 = 20;
}

void func_80937CA0(ObjBean* this) {
    this->stateTimer2--;
    func_80937B54(this);
    if (this->stateTimer2 < 0) {
        func_80937CE4(this);
    }
}

void func_80937CE4(ObjBean* this) {
    this->unkFunc1E8 = func_80937D54;
    this->stateTimer2 = Rand_S16Offset(30, 4);
    this->unk_1F0 = Rand_S16Offset(2000, 1000);
    this->unk_1F2 = 200;
    this->unk_1F6 = Rand_S16Offset(14000, 6000);
    this->unk_1F8 = 4000;
}

void func_80937D54(ObjBean* this) {
    this->stateTimer2--;
    if (this->stateTimer2 == 14) {
        this->unk_1F0 = Rand_S16Offset(200, 400);
        this->unk_1F6 = Rand_S16Offset(100, 500);
        this->unk_1F8 = 2000;
    }

    func_80937B54(this);

    if (this->stateTimer2 < 0) {
        func_80937C30(this);
    }
}

// used for wall types
void func_80937DD8(ObjBean* this) {
    this->actionFunc = func_80937DEC;
}

// precheck actionfunc? why wait for the frame?
void func_80937DEC(ObjBean* this, PlayState* play) {
    s32 pad;
    s32 type = OBJBEAN_GET_TYPE(&this->dyna.actor);

    if (type == ENOBJBEAN_GET_PATHLESS_SOIL) {
        s32 pad2;

        if (ObjBean_SearchForBean(this, play) == NULL) {
            this->bool1FF = false;
        } else {
            this->bool1FF = true;
        }
    } else {
        this->bool1FF = false;
    }

    if (this->bool1FF && !Flags_GetSwitch(play, OBJBEAN_GET_3F80(&this->dyna.actor, 1)) &&
        Flags_GetSwitch(play, OBJBEAN_GET_3F80(&this->dyna.actor, 0)) && func_800FE9B4(play)) {
        Flags_SetSwitch(play, OBJBEAN_GET_3F80(&this->dyna.actor, 1));
    }

    if (this->bool1FF && Flags_GetSwitch(play, OBJBEAN_GET_3F80(&this->dyna.actor, 1))) {
        Actor_MarkForDeath(&this->dyna.actor);
        return;
    }

    if (type == ENOBJBEAN_GET_WALLCRACK) {
        this->dyna.actor.draw = ObjBean_DrawWallCrack;
    } else {
        this->dyna.actor.draw = ObjBean_Draw;
    }

    if (this->bool1FF && Flags_GetSwitch(play, OBJBEAN_GET_3F80(&this->dyna.actor, 0))) {
        this->drawFlags |= (OBJBEAN_DRAWFLAG_SOIL | OBJBEAN_DRAWFLAG_SEEDLING);
        func_80937C30(this);
    } else {
        this->drawFlags |= OBJBEAN_DRAWFLAG_SOIL;
        ObjBean_SetupUnkFuncDoNothing(this);
    }

    if (Flags_GetSwitch(play, OBJBEAN_GET_SWITCHFLAG(&this->dyna.actor, 0))) {
        this->unk_1E4 = 5;
    } else {
        this->unk_1E4 = 0;
    }

    func_80937FB0(this);
}



void func_80937FB0(ObjBean* this) {
    this->unk_1E0 = 0;
    this->actionFunc = func_80937FC8;
}

// regular bean idle
void func_80937FC8(ObjBean* this, PlayState* play) {
    this->unkFunc1E8(this);

    if (Actor_ProcessTalkRequest(&this->dyna.actor, &play->state)) {
        if (Player_GetExchangeItemId(play) == PLAYER_AP_MAGIC_BEANS) {
            func_809383B4(this);
            Flags_SetSwitch(play, OBJBEAN_GET_3F80(&this->dyna.actor, 0));
        }

        if (Flags_GetSwitch(play, OBJBEAN_GET_SWITCHFLAG(&this->dyna.actor, 0))) {
            this->unk_1E4 = 5;
        } else {
            s32 pad;

            this->unk_1E4 = 0;
        }
    } else if (this->unk_1E4 == 1) {
        this->unk_1DF = 16;
        func_809381B0(this);
    } else if (((this->collider.base.acFlags & AC_HIT) && (this->collider.base.ac != NULL) &&
                (this->collider.base.ac->id == ACTOR_OBJ_AQUA)) ||
               ((this->bool1FF) && (this->drawFlags & OBJBEAN_DRAWFLAG_SEEDLING) && (this->dyna.actor.xzDistToPlayer < 300.0f) &&
                func_800FE9B4(play))) {
        // sprouting a bean? getting hit with water
        func_809375C8(this, play);
        Flags_SetSwitch(play, OBJBEAN_GET_3F80(&this->dyna.actor, 1));
        this->unk_1E4 = 6;
        ObjBean_SetupGrowPlatform(this);
    } else if (this->bool1FF) {
        if (this->drawFlags & OBJBEAN_DRAWFLAG_SEEDLING) {
            this->collider.base.acFlags &= ~AC_HIT;
            if (this->dyna.actor.xzDistToPlayer < 150.0f) {
                CollisionCheck_SetAC(play, &play->colChkCtx, &this->collider.base);
            }
        } else {
            func_800B85E0(&this->dyna.actor, play, 28.0f, 0x2E);
        }
    }
}

void func_809381B0(ObjBean* this) {
    this->actionFunc = func_809381C4;
}

void func_809381C4(ObjBean* this, PlayState* play) {
    this->unkFunc1E8(this);

    if (ActorCutscene_GetCanPlayNext(this->dyna.actor.cutscene)) {
        ActorCutscene_StartAndSetUnkLinkFields(this->dyna.actor.cutscene, &this->dyna.actor);
        if (this->dyna.actor.cutscene >= 0) {
            func_800B7298(play, &this->dyna.actor, 1);
        }
        this->unk_1E4 = 2;
        func_80938284(this);
    } else if (this->unk_1E4 == 4) {
        ActorCutscene_Stop(this->dyna.actor.cutscene);
        play_sound(NA_SE_SY_ERROR);
        this->unk_1E4 = 0;
        func_80937FB0(this);
    } else {
        ActorCutscene_SetIntentToPlay(this->dyna.actor.cutscene);
    }
}

void func_80938284(ObjBean* this) {
    this->actionFunc = func_80938298;
}

void func_80938298(ObjBean* this, PlayState* play) {
    this->unkFunc1E8(this);

    if (this->unk_1E0 >= 3) {
        this->unk_1E4 = 3;
        Flags_SetSwitch(play, OBJBEAN_GET_SWITCHFLAG(&this->dyna.actor, 0));
        this->unk_1E4 = 5;
        func_8093833C(this);
    } else if (this->unk_1E4 == 4) {
        ActorCutscene_Stop(this->dyna.actor.cutscene);
        play_sound(NA_SE_SY_ERROR);
        this->unk_1E4 = 0;
        func_80937FB0(this);
    }
}

void func_8093833C(ObjBean* this) {
    this->actionFunc = func_80938358;
    this->stateTimer = 4;
}

void func_80938358(ObjBean* this, PlayState* play) {
    this->unkFunc1E8(this);

    if (this->stateTimer <= 0) {
        ActorCutscene_Stop(this->dyna.actor.cutscene);
        func_80937FB0(this);
    }
}

void func_809383B4(ObjBean* this) {
    this->stateTimer = 60;
    this->actionFunc = func_809383D0;
}

// cutscene watching bean grow before sprouting
void func_809383D0(ObjBean* this, PlayState* play) {
    if (this->stateTimer <= 0) {
        this->drawFlags |= OBJBEAN_DRAWFLAG_SEEDLING;
        func_80938408(this);
    }
}

void func_80938408(ObjBean* this) {
    Actor_SetScale(&this->dyna.actor, 0.01f);
    this->actionFunc = func_80938444;
}

// cutscene watching bean sprout growing
void func_80938444(ObjBean* this, PlayState* play) {
    s32 pad;
    s32 sp20 = Math_StepToF(&this->dyna.actor.scale.y, 0.16672663f, 0.01f) & 1;

    sp20 &= Math_StepToF(&this->dyna.actor.scale.x, 0.03569199f, 0.00113f);

    this->dyna.actor.scale.z = this->dyna.actor.scale.x;
    if (sp20) {
        if (this->stateTimer <= 0) {
            func_809384E8(this);
        }
    } else {
        this->stateTimer = 1;
    }
    func_800B9010(&this->dyna.actor, NA_SE_PL_PLANT_GROW_UP - SFX_FLAG);
}

void func_809384E8(ObjBean* this) {
    this->timer1AC = 0x33E9;
    this->actionFunc = func_80938504;
}

// short duration after sprout has finished growing,
void func_80938504(ObjBean* this, PlayState* play) {
    this->timer1AC -= 2400;
    this->dyna.actor.scale.y = Math_SinS(this->timer1AC) * 0.17434467f;
    this->dyna.actor.scale.x = this->dyna.actor.scale.z = Math_CosS(this->timer1AC) * 0.12207746f;
    if (this->timer1AC < 6372) {
        func_80938588(this);
    }
}

void func_80938588(ObjBean* this) {
    this->timer1AC = 0;
    this->unk_1AE = 3000;
    this->actionFunc = func_809385A8;
}

void func_809385A8(ObjBean* this, PlayState* play) {
    s32 pad;
    s16 sp22;

    this->timer1AC += 16000;
    this->unk_1AE -= 200;
    sp22 = 6372.0f - (Math_SinS(this->timer1AC) * this->unk_1AE);
    this->dyna.actor.scale.y = Math_SinS(sp22) * 0.17434467f;
    this->dyna.actor.scale.x = this->dyna.actor.scale.z = Math_CosS(sp22) * 0.12207746f;
    if (this->unk_1AE < 0) {
        func_80937C30(this);
        func_80937FB0(this);
    }
}

void ObjBean_SetupGrowPlatform(ObjBean* this) {
    this->actionFunc = ObjBean_GrowPlatform;
    this->stateTimer = 73;
}

// water has been poured on us
void ObjBean_GrowPlatform(ObjBean* this, PlayState* play) {
    if (this->stateTimer <= 0) {
        Actor_MarkForDeath(&this->dyna.actor);
    } else if (this->stateTimer <= 20) {
        this->dyna.actor.scale.x *= 0.89f;
        this->dyna.actor.scale.y *= 0.89f;
        this->dyna.actor.scale.z *= 0.89f;
        this->unk_1B8 *= 0.89f;
    }
}

// idle
void ObjBean_SetupWaitForWater(ObjBean* this) {
    this->dyna.actor.flags |= ACTOR_FLAG_10;
    this->dyna.actor.draw = NULL;
    this->actionFunc = ObjBean_WaitForWater;
}

void ObjBean_WaitForWater(ObjBean* this, PlayState* play) {
    if (this->crossBeanFlag) {
        ActorCutscene_SetIntentToPlay(this->dyna.actor.cutscene);
        ObjBean_SetupGrowSeedlingCutscene(this);
    }
}

void ObjBean_SetupGrowSeedlingCutscene(ObjBean* this) {
    this->actionFunc = ObjBean_GrowSeedlingCutscene;
}

void ObjBean_GrowSeedlingCutscene(ObjBean* this, PlayState* play) {
    if (ActorCutscene_GetCanPlayNext(this->dyna.actor.cutscene)) {
        ActorCutscene_StartAndSetUnkLinkFields(this->dyna.actor.cutscene, &this->dyna.actor);
        if (this->dyna.actor.cutscene >= 0) {
            func_800B7298(play, &this->dyna.actor, 1);
        }
        this->cutsceneTimer = 36;
        func_80937130(this);
        func_80938AA4(this);
    } else {
        ActorCutscene_SetIntentToPlay(this->dyna.actor.cutscene);
    }
}

// Platform has finished growing, waits for contact
void ObjBean_SetupPlatformWaitForPlayer(ObjBean* this) {
    this->dyna.actor.flags &= ~ACTOR_FLAG_10;
    this->dyna.actor.draw = ObjBean_Draw; // not sure why this is
    this->actionFunc = ObjBean_PlatformWaitForPlayer;
}

void ObjBean_PlatformWaitForPlayer(ObjBean* this, PlayState* play) {
    if (DynaPolyActor_IsInRidingMovingState(&this->dyna)) {
        ObjBean_SetupPlatformFly(this);
    }
    ObjBean_PlatformUndulate(this);
}

void ObjBean_SetupPlatformFly(ObjBean* this) {
    this->actionFunc = ObjBean_PlatformFly;
    this->dyna.actor.draw = ObjBean_Draw;
    this->dyna.actor.flags |= ACTOR_FLAG_10;
    this->dyna.actor.speedXZ = 0.0f;
}

void ObjBean_PlatformFly(ObjBean* this, PlayState* play) {
    ObjBean_FollowPath(this);
    if (this->currentPointIndex == this->pathNodeCount) {
        // if the bean has already done its whole path and player is still on it
        ObjBean_SetupPathCount(this, play);
        ObjBean_CopyPathPoints(this);
        ObjBean_SetupWaitForStepOff(this);
    } else if (DynaPolyActor_IsInRidingMovingState(&this->dyna)) {
        func_800B9010(&this->dyna.actor, NA_SE_PL_PLANT_MOVE - SFX_FLAG);
    }
    ObjBean_PlatformUndulate(this);
}

void ObjBean_SetupWaitForStepOff(ObjBean* this) {
    this->dyna.actor.flags |= ACTOR_FLAG_10;
    this->dyna.actor.draw = ObjBean_Draw; // bit overkill, we were already standing on it
    this->actionFunc = ObjBean_WaitForStepOff;
}

void ObjBean_WaitForStepOff(ObjBean* this, PlayState* play) {
    if (!DynaPolyActor_IsInRidingRotatingState(&this->dyna)) {
        ObjBean_SetupPlatformWaitForPlayer(this);
    }
    ObjBean_PlatformUndulate(this);
}

void func_80938998(ObjBean* this) {
    this->dyna.actor.flags |= ACTOR_FLAG_10;
    this->dyna.actor.draw = NULL;
    this->actionFunc = func_809389BC;
}

void func_809389BC(ObjBean* this, PlayState* play) {
    if (!DynaPolyActor_IsInRidingMovingState(&this->dyna)) {
        ObjBean_SetupPathCount(this, play);
        ObjBean_CopyPathPoints(this);
        ObjBean_Move(this);
        func_80938A14(this);
    }
}

void func_80938A14(ObjBean* this) {
    this->dyna.actor.draw = NULL;
    this->dyna.actor.flags |= ACTOR_FLAG_10;
    this->stateTimer = 100;
    func_80937130(this);
    this->actionFunc = func_80938A5C;
}

void func_80938A5C(ObjBean* this, PlayState* play) {
    if (ObjBean_CheckForHorseTrample(this, play)) {
        this->stateTimer = 100;
    } else if (this->stateTimer <= 0) {
        func_80938AA4(this);
    }
}

void func_80938AA4(ObjBean* this) {
    this->dyna.actor.flags |= ACTOR_FLAG_10;
    this->dyna.actor.draw = ObjBean_Draw;
    this->stateTimer = 30;
    this->actionFunc = func_80938AD8;
}

void func_80938AD8(ObjBean* this, PlayState* play) {
    s32 pad;
    s32 sp30 = ObjBean_CheckForHorseTrample(this, play);

    func_80937160(this);
    if (this->stateTimer == 25) {
        Actor_PlaySfxAtPos(&this->dyna.actor, NA_SE_PL_PLANT_GROW_BIG);
    }

    if (sp30 != 0) {
        func_800C6314(play, &play->colCtx.dyna, this->dyna.bgId);
    } else {
        func_800C6314(play, &play->colCtx.dyna, this->dyna.bgId);
    }

    if (this->dyna.actor.xzDistToPlayer < 74.0f) {
        Player* player = GET_PLAYER(play);
        f32 sp28 = 74.0f - this->dyna.actor.xzDistToPlayer;
        f32 sin;
        f32 cos;

        if (sp28 > 8.0f) {
            sp28 = 8.0f;
        }

        sin = Math_SinS(this->dyna.actor.yawTowardsPlayer) * sp28;
        cos = Math_CosS(this->dyna.actor.yawTowardsPlayer) * sp28;

        player->actor.world.pos.x += sin;
        player->actor.world.pos.z += cos;
    }

    if ((this->stateTimer <= 0) && (sp30 == 0)) {
        ObjBean_TimerReset(this);
        ObjBean_SetupPlatformWaitForPlayer(this);
    }
}

// alternative update
void ObjBean_UpdateAlt(Actor* thisx, PlayState* play) {
    ObjBean* this = THIS;

    if (this->stateTimer > 0) {
        this->stateTimer--;
    }

    if (this->unk_1DF > 0) {
        this->unk_1DF--;
        if (this->unk_1DF == 0) {
            play_sound(NA_SE_SY_TRE_BOX_APPEAR);
        }
    }

    this->actionFunc(this, play);
}

void ObjBean_Update(Actor* thisx, PlayState* play) {
    s32 pad;
    ObjBean* this = THIS;

    if (this->stateTimer > 0) {
        this->stateTimer--;
    }

    this->actionFunc(this, play);

    if (this->cutsceneTimer > 0) {
        this->cutsceneTimer--;
        if (this->cutsceneTimer == 0) {
            ActorCutscene_Stop(this->dyna.actor.cutscene);
        }
    }

    if (this->dyna.actor.draw != NULL) {
        ObjBean_Move(this);
        if (this->dyna.actor.xzDistToPlayer < 150.0f) {
            this->collider.dim.radius = (this->dyna.actor.scale.x * 640.0f) + 0.5f;
            Collider_UpdateCylinder(&this->dyna.actor, &this->collider);
            CollisionCheck_SetOC(play, &play->colChkCtx, &this->collider.base);
        }
        ObjBean_UpdateFloorHeight(this, play);
        this->dyna.actor.shape.shadowDraw = ActorShadow_DrawCircle;
        this->dyna.actor.shape.shadowScale = this->dyna.actor.scale.x * 88.0f;
        if (ObjBean_CheckForHorseTrample(this, play)) {
            func_809375F4(this, play);
            func_800C62BC(play, &play->colCtx.dyna, this->dyna.bgId);
            func_80938998(this);
        }
    } else {
        this->dyna.actor.shape.shadowDraw = NULL;
    }
    Actor_SetFocus(&this->dyna.actor, 6.0f);
}

/*
void Debug_PrintToScreen(Actor* thisx, PlayState* play) {
    ObjBean* this = THIS;
    // with explanation comments
    GfxPrint printer;
    Gfx* gfx;

    OPEN_DISPS(play->state.gfxCtx);

    // the dlist will be written in the opa buffer because that buffer is larger,
    // but executed from the overlay buffer (overlay draws last, for example the hud is drawn to overlay)
    gfx = POLY_OPA_DISP + 1;
    gSPDisplayList(OVERLAY_DISP++, gfx);

    // initialize GfxPrint struct
    GfxPrint_Init(&printer);
    GfxPrint_Open(&printer, gfx);

    GfxPrint_SetColor(&printer, 255, 255, 255, 255);
    GfxPrint_SetPos(&printer, 1, 10);
    GfxPrint_Printf(&printer, "actor struct loc: %X", &thisx);

    { // address locations
        u32 convertedAddr = (u32)Fault_ConvertAddress((void*)this->actionFunc);
        GfxPrint_SetPos(&printer, 1, 11);
        //GfxPrint_Printf(&printer, "func %X", &EnPoSisters_CheckCollision);
        GfxPrint_Printf(&printer, "actionfunc vram:        func_%X", convertedAddr);
        GfxPrint_SetPos(&printer, 1, 12);
        GfxPrint_Printf(&printer, "actionfunc actual ram:  %X", this->actionFunc);
    }

    GfxPrint_SetPos(&printer, 1, 13);
    GfxPrint_Printf(&printer, "drawflags %X", this->drawFlags);
    //GfxPrint_Printf(&printer, "BREG86 %X", BREG(86));

    // end of text printing
    gfx = GfxPrint_Close(&printer);
    GfxPrint_Destroy(&printer);

    gSPEndDisplayList(gfx++);
    // make the opa dlist jump over the part that will be executed as part of overlay
    gSPBranchList(POLY_OPA_DISP, gfx);
    POLY_OPA_DISP = gfx;

    CLOSE_DISPS(play->state.gfxCtx);
    //Debug_PrintToScreen(thisx, play);
} // */

// main draw for everything but the unused wallcrack variant
void ObjBean_Draw(Actor* thisx, PlayState* play) {
    ObjBean* this = THIS;

    OPEN_DISPS(play->state.gfxCtx);

    func_8012C28C(play->state.gfxCtx);

    gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

    if (this->drawFlags & OBJBEAN_DRAWFLAG_SEEDLING) {
        gSPDisplayList(POLY_OPA_DISP++, gMagicBeanSeedlingDL);
    }

    if (this->drawFlags & OBJBEAN_DRAWFLAG_PLATFORM) {
        gSPDisplayList(POLY_OPA_DISP++, gMagicBeanPlatformDL);
    }

    if (this->drawFlags & OBJBEAN_DRAWFLAG_SOIL) {
        Matrix_SetTranslateRotateYXZ(this->dyna.actor.world.pos.x, this->dyna.actor.world.pos.y,
                                     this->dyna.actor.world.pos.z, &this->dyna.actor.shape.rot);
        Matrix_Scale(this->unk_1B8, this->unk_1B8, this->unk_1B8, MTXMODE_APPLY);

        gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gSPDisplayList(POLY_OPA_DISP++, gSoftSoilPatchDL);
    }
    //Debug_PrintToScreen(thisx, play);

    CLOSE_DISPS(play->state.gfxCtx);
}

void ObjBean_DrawWallCrack(Actor* thisx, PlayState* play) {
    ObjBean* this = THIS;

    Gfx_DrawDListXlu(play, gSoftSoilWallCrackDL);
}
