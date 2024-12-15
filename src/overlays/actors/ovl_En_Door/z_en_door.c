/*
 * File: z_en_door.c
 * Overlay: ovl_En_Door
 * Description: Wooden Door
 */

#include "z_en_door.h"
#include "objects/object_kinsta2_obj/object_kinsta2_obj.h"
#include "objects/object_dor01/object_dor01.h"
#include "objects/object_dor02/object_dor02.h"
#include "objects/object_dor03/object_dor03.h"
#include "objects/object_dor04/object_dor04.h"
#include "objects/object_wdor01/object_wdor01.h"
#include "objects/object_wdor02/object_wdor02.h"
#include "objects/object_wdor03/object_wdor03.h"
#include "objects/object_wdor04/object_wdor04.h"
#include "objects/object_wdor05/object_wdor05.h"
#include "objects/object_numa_obj/object_numa_obj.h"
#include "objects/object_kaizoku_obj/object_kaizoku_obj.h"
#include "objects/gameplay_field_keep/gameplay_field_keep.h"

#define FLAGS (ACTOR_FLAG_10)

#define THIS ((EnDoor*)thisx)

void EnDoor_Init(Actor* thisx, PlayState* play2);
void EnDoor_Destroy(Actor* thisx, PlayState* play);
void EnDoor_Update(Actor* thisx, PlayState* play);
void EnDoor_Draw(Actor* thisx, PlayState* play);

void func_80866B20(EnDoor* this, PlayState* play);
void func_8086704C(EnDoor* this, PlayState* play);
void func_80866F94(EnDoor* this, PlayState* play);
void func_80867080(EnDoor* this, PlayState* play);
void func_80867144(EnDoor* this, PlayState* play);
void func_808670F0(EnDoor* this, PlayState* play);
void func_80866A5C(EnDoor* this, PlayState* play);

#include "build/src/overlays/actors/ovl_En_Door/scheduleScripts.schl.inc"

ScheduleScript* D_8086778C[] = {
    D_808675D0, D_808675E4, D_80867634, D_80867640, D_8086764C, D_80867658, D_80867684, D_80867688,
    D_80867690, D_80867698, D_808676A0, D_808676B8, D_808676D0, D_808676D4, D_808676D8, D_808676E4,
    D_808676EC, D_808676F0, D_80867704, D_80867708, D_8086770C, D_80867710, D_80867714, D_8086771C,
    D_80867734, D_8086773C, D_80867744, D_8086775C, D_80867778, D_8086777C, D_80867780, D_80867784,
};

ActorInit En_Door_InitVars = {
    /**/ ACTOR_EN_DOOR,
    /**/ ACTORCAT_DOOR,
    /**/ FLAGS,
    /**/ GAMEPLAY_KEEP,
    /**/ sizeof(EnDoor),
    /**/ EnDoor_Init,
    /**/ EnDoor_Destroy,
    /**/ EnDoor_Update,
    /**/ EnDoor_Draw,
};

typedef struct {
    /* 0x0 */ s16 sceneId;
    /* 0x2 */ u8 dListIndex;
    /* 0x4 */ s16 objectId;
} EnDoorInfo; // size = 0x6

static EnDoorInfo sObjectInfo[] = {
    { SCENE_MITURIN, 0x01, OBJECT_NUMA_OBJ },
    { SCENE_TENMON_DAI, 0x02, OBJECT_DOR01 },
    { SCENE_00KEIKOKU, 0x02, OBJECT_DOR01 },
    { SCENE_30GYOSON, 0x02, OBJECT_DOR01 },
    { SCENE_LABO, 0x02, OBJECT_DOR01 },
    { SCENE_33ZORACITY, 0x03, OBJECT_DOR02 },
    { SCENE_UNSET_31, 0x03, OBJECT_DOR02 },
    { SCENE_BANDROOM, 0x03, OBJECT_DOR02 },
    { SCENE_20SICHITAI, 0x04, OBJECT_DOR03 },
    { SCENE_20SICHITAI2, 0x04, OBJECT_DOR03 },
    { SCENE_MAP_SHOP, 0x04, OBJECT_DOR03 },
    { SCENE_KAIZOKU, 0x0B, OBJECT_KAIZOKU_OBJ },
    { SCENE_PIRATE, 0x0B, OBJECT_KAIZOKU_OBJ },
    { SCENE_TORIDE, 0x0B, OBJECT_KAIZOKU_OBJ },
    { SCENE_KINDAN2, 0x0C, OBJECT_KINSTA2_OBJ },
    { -1, 0x00, GAMEPLAY_KEEP },
    { -1, 0x0D, GAMEPLAY_FIELD_KEEP },
    { -1, 0x08, OBJECT_WDOR03 },
    { -1, 0x07, OBJECT_WDOR02 },
    { -1, 0x06, OBJECT_WDOR01 },
    { -1, 0x07, OBJECT_WDOR02 },
    { -1, 0x06, OBJECT_WDOR01 },
    { -1, 0x00, GAMEPLAY_KEEP },
    { -1, 0x00, GAMEPLAY_KEEP },
    { -1, 0x00, GAMEPLAY_KEEP },
    { -1, 0x00, GAMEPLAY_KEEP },
    { -1, 0x00, GAMEPLAY_KEEP },
    { -1, 0x09, OBJECT_WDOR04 },
    { -1, 0x08, OBJECT_WDOR03 },
    { -1, 0x08, OBJECT_WDOR03 },
    { -1, 0x0D, GAMEPLAY_FIELD_KEEP },
    { -1, 0x0D, GAMEPLAY_FIELD_KEEP },
    { -1, 0x0D, GAMEPLAY_FIELD_KEEP },
    { -1, 0x0D, GAMEPLAY_FIELD_KEEP },
    { -1, 0x06, OBJECT_WDOR01 },
    { -1, 0x00, GAMEPLAY_KEEP },
    { -1, 0x00, GAMEPLAY_KEEP },
    { -1, 0x00, GAMEPLAY_KEEP },
    { -1, 0x00, GAMEPLAY_KEEP },
    { -1, 0x0D, GAMEPLAY_FIELD_KEEP },
    { -1, 0x0D, GAMEPLAY_FIELD_KEEP },
    { -1, 0x0D, GAMEPLAY_FIELD_KEEP },
    { -1, 0x0D, GAMEPLAY_FIELD_KEEP },
    { -1, 0x00, GAMEPLAY_KEEP },
    { -1, 0x0A, OBJECT_WDOR05 },
    { -1, 0x0D, GAMEPLAY_FIELD_KEEP },
    { -1, 0x05, OBJECT_DOR04 },
    { -1, 0x09, OBJECT_WDOR04 },
    { -1, 0x04, OBJECT_DOR03 },
};

static InitChainEntry sInitChain[] = {
    ICHAIN_U8(targetMode, TARGET_MODE_0, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneForward, 4000, ICHAIN_CONTINUE),
    ICHAIN_U16(shape.rot.x, 0, ICHAIN_CONTINUE),
    ICHAIN_U16(shape.rot.z, 0, ICHAIN_STOP),
};

static AnimationHeader* sAnimations[2 * PLAYER_FORM_MAX] = {
    // left
    &gameplay_keep_Anim_020658, // PLAYER_FORM_FIERCE_DEITY
    &gameplay_keep_Anim_022CA8, // PLAYER_FORM_GORON
    &gameplay_keep_Anim_020658, // PLAYER_FORM_ZORA
    &gameplay_keep_Anim_022E68, // PLAYER_FORM_DEKU
    &gameplay_keep_Anim_0204B4, // PLAYER_FORM_HUMAN
    // right
    &gameplay_keep_Anim_022BE8, // PLAYER_FORM_FIERCE_DEITY
    &gameplay_keep_Anim_022D90, // PLAYER_FORM_GORON
    &gameplay_keep_Anim_022BE8, // PLAYER_FORM_ZORA
    &gameplay_keep_Anim_022FF0, // PLAYER_FORM_DEKU
    &gameplay_keep_Anim_0205A0, // PLAYER_FORM_HUMAN
};
static u8 sAnimOpenFrames[2 * PLAYER_FORM_MAX] = {
    // left
    25, // PLAYER_FORM_FIERCE_DEITY
    25, // PLAYER_FORM_GORON
    25, // PLAYER_FORM_ZORA
    25, // PLAYER_FORM_DEKU
    25, // PLAYER_FORM_HUMAN
    // right
    25, // PLAYER_FORM_FIERCE_DEITY
    25, // PLAYER_FORM_GORON
    25, // PLAYER_FORM_ZORA
    25, // PLAYER_FORM_DEKU
    25, // PLAYER_FORM_HUMAN
};

static u8 sAnimCloseFrames[2 * PLAYER_FORM_MAX] = {
    // left
    60, // PLAYER_FORM_FIERCE_DEITY
    60, // PLAYER_FORM_GORON
    60, // PLAYER_FORM_ZORA
    70, // PLAYER_FORM_DEKU
    70, // PLAYER_FORM_HUMAN
    // right
    60, // PLAYER_FORM_FIERCE_DEITY
    60, // PLAYER_FORM_GORON
    60, // PLAYER_FORM_ZORA
    60, // PLAYER_FORM_DEKU
    70, // PLAYER_FORM_HUMAN
};

static Gfx* D_808679A4[14][2] = {
    { gDoorLeftDL, gDoorRightDL },
    { gWoodfallDoorDL, gWoodfallDoorDL },
    { gObservatoryLabDoorDL, gObservatoryLabDoorDL },
    { gZoraHallDoorDL, gZoraHallDoorDL },
    { gSwampDoorDL, gSwampDoorDL },
    { gMagicHagPotionShopDoorDL, gMagicHagPotionShopDoorDL },
    { gLotteryCuriosityShopMayorHouseDoorDL, gLotteryCuriosityShopMayorHouseDoorDL },
    { gPostOfficeTradingPostDoorDL, gPostOfficeTradingPostDoorDL },
    { gInnSchoolDoorDL, gInnSchoolDoorDL },
    { gMilkBarDoorDL, gMilkBarDoorDL },
    { gMusicBoxHouseDoorDL, gMusicBoxHouseDoorDL },
    { gPiratesFortressDoorDL, gPiratesFortressDoorDL },
    { gOceansideSpiderHouseDoorDL, gOceansideSpiderHouseDoorDL },
    { gFieldWoodDoorLeftDL, gFieldWoodDoorRightDL },
};

void EnDoor_Init(Actor* thisx, PlayState* play2) {
    PlayState* play = play2;
    s32 objectSlot;
    EnDoorInfo* objectInfo = &sObjectInfo[0];
    EnDoor* this = THIS;
    s32 i;

    Actor_ProcessInitChain(&this->knobDoor.dyna.actor, sInitChain);

    this->doorType = ENDOOR_GET_TYPE(thisx);

    this->switchFlag = ENDOOR_GET_SWITCH_FLAG(thisx);
    if ((this->doorType == ENDOOR_TYPE_7) && (this->switchFlag == 0)) {
        DynaPolyActor_Init(&this->knobDoor.dyna, 0);
        DynaPolyActor_LoadMesh(play, &this->knobDoor.dyna, &gDoorCol);
    }
    SkelAnime_Init(play, &this->knobDoor.skelAnime, &gDoorSkel, &gameplay_keep_Anim_020658, this->limbTable,
                   this->limbTable, DOOR_LIMB_MAX);
    if (this->doorType == ENDOOR_TYPE_5) {
        objectInfo = &sObjectInfo[17 + this->switchFlag];
    } else {
        for (i = 0; i < ARRAY_COUNT(sObjectInfo) - 34; i++, objectInfo++) {
            if (play->sceneId == objectInfo->sceneId) {
                break;
            }
        }
        if ((i >= ARRAY_COUNT(sObjectInfo) - 34) &&
            (Object_GetSlot(&play->objectCtx, GAMEPLAY_FIELD_KEEP) > OBJECT_SLOT_NONE)) {
            objectInfo++;
        }
    }

    this->knobDoor.dlIndex = objectInfo->dListIndex;
    objectSlot = Object_GetSlot(&play->objectCtx, objectInfo->objectId);
    if (objectSlot <= OBJECT_SLOT_NONE) {
        objectInfo = &sObjectInfo[15];
        objectSlot = Object_GetSlot(&play->objectCtx, objectInfo->objectId);
        if (objectSlot != 0) {
            Actor_Kill(&this->knobDoor.dyna.actor);
            return;
        }
    }
    this->knobDoor.objectSlot = objectSlot;
    this->knobDoor.dlIndex = objectInfo->dListIndex; // Set twice?
    if (this->knobDoor.dyna.actor.objectSlot == this->knobDoor.objectSlot) {
        func_80866A5C(this, play);
    } else {
        this->actionFunc = func_80866A5C;
    }
    Actor_SetFocus(&this->knobDoor.dyna.actor, 35.0f);
}

void EnDoor_Destroy(Actor* thisx, PlayState* play) {
    EnDoor* this = (EnDoor*)thisx;

    if (this->doorType != ENDOOR_TYPE_7) {
        TransitionActorEntry* transitionEntry =
            &play->doorCtx.transitionActorList[DOOR_GET_TRANSITION_ID(&this->knobDoor.dyna.actor)];
        if (transitionEntry->id < 0) {
            transitionEntry->id = -transitionEntry->id;
        }
    } else if (this->switchFlag == 0) {
        DynaPoly_DeleteBgActor(play, &play->colCtx.dyna, this->knobDoor.dyna.bgId);
    }
}

void func_80866A5C(EnDoor* this, PlayState* play) {
    if (Object_IsLoaded(&play->objectCtx, this->knobDoor.objectSlot)) {
        this->knobDoor.dyna.actor.objectSlot = this->knobDoor.objectSlot;
        this->actionFunc = func_80866B20;
        this->knobDoor.dyna.actor.world.rot.y = 0;
        if (this->doorType == ENDOOR_TYPE_1) {
            if (!Flags_GetSwitch(play, this->switchFlag)) {
                this->unk_1A6 = 10;
            }
        } else if ((this->doorType == ENDOOR_TYPE_4) &&
                   (Actor_WorldDistXZToActor(&this->knobDoor.dyna.actor, &GET_PLAYER(play)->actor) > 120.0f)) {
            this->actionFunc = func_8086704C;
            this->knobDoor.dyna.actor.world.rot.y = -0x1800;
        }
    }
}

void func_80866B20(EnDoor* this, PlayState* play) {
    static s32 D_80867BC0;
    Player* player = GET_PLAYER(play);

    if (Actor_TalkOfferAccepted(&this->knobDoor.dyna.actor, &play->state) &&
        (this->knobDoor.dyna.actor.textId == 0x1821)) {
        D_80867BC0 = true;
    }
    if (this->knobDoor.playOpenAnim) {
        this->actionFunc = func_80867144;
        Animation_PlayOnceSetSpeed(&this->knobDoor.skelAnime, sAnimations[this->knobDoor.animIndex],
                                   (player->stateFlags1 & PLAYER_STATE1_8000000) ? 0.75f : 1.5f);
        if (this->unk_1A6 != 0) {
            DUNGEON_KEY_COUNT(gSaveContext.mapIndex) = DUNGEON_KEY_COUNT(gSaveContext.mapIndex) - 1;
            Flags_SetSwitch(play, this->switchFlag);
            Actor_PlaySfx(&this->knobDoor.dyna.actor, NA_SE_EV_CHAIN_KEY_UNLOCK);
        }
    } else if (this->openTimer != 0) {
        this->actionFunc = func_80866F94;
        Actor_PlaySfx(&this->knobDoor.dyna.actor, NA_SE_EV_DOOR_OPEN);
    } else if (!Player_InCsMode(play)) {
        Vec3f playerPosRelToDoor;

        Actor_OffsetOfPointInActorCoords(&this->knobDoor.dyna.actor, &playerPosRelToDoor, &player->actor.world.pos);
        if (D_80867BC0 || ((fabsf(playerPosRelToDoor.y) < 20.0f) && (fabsf(playerPosRelToDoor.x) < 20.0f) &&
                           (fabsf(playerPosRelToDoor.z) < 50.0f))) {
            s16 yawDiff = player->actor.shape.rot.y - this->knobDoor.dyna.actor.shape.rot.y;

            if (playerPosRelToDoor.z > 0.0f) {
                yawDiff = (0x8000 - yawDiff);
            }
            if (ABS_ALT(yawDiff) < 0x3000) {
                player->doorType = PLAYER_DOORTYPE_HANDLE;
                player->doorDirection = playerPosRelToDoor.z >= 0.0f ? 1.0f : -1.0f;
                player->doorActor = &this->knobDoor.dyna.actor;
                if (this->unk_1A6 != 0) {
                    if (DUNGEON_KEY_COUNT(gSaveContext.mapIndex) <= 0) {
                        player->doorType = PLAYER_DOORTYPE_TALKING;
                        this->knobDoor.dyna.actor.textId = 0x1802;
                    } else {
                        player->doorTimer = 10;
                    }
                } else if (this->doorType == ENDOOR_TYPE_4) {
                    player->doorType = PLAYER_DOORTYPE_TALKING;
                    this->knobDoor.dyna.actor.textId = 0x1800;
                } else if ((this->doorType == ENDOOR_TYPE_0) || (this->doorType == ENDOOR_TYPE_2) ||
                           (this->doorType == ENDOOR_TYPE_3)) {
                    s32 halfDaysDayBit = (play->actorCtx.halfDaysBit & HALFDAYBIT_DAWNS) >> 1;
                    s32 halfDaysNightBit = play->actorCtx.halfDaysBit & HALFDAYBIT_NIGHTS;
                    s16 temp_a2 = D_801AED48[this->switchFlag & 7];
                    s32 textIdOffset = (this->switchFlag >> 3) & 0xF;

                    if (((this->doorType == ENDOOR_TYPE_0) && !((halfDaysDayBit | halfDaysNightBit) & temp_a2)) ||
                        ((this->doorType == ENDOOR_TYPE_2) && !(halfDaysNightBit & temp_a2)) ||
                        ((this->doorType == ENDOOR_TYPE_3) && !(halfDaysDayBit & temp_a2))) {
                        s16 baseTextId = 0x182D;

                        if (this->doorType == ENDOOR_TYPE_3) {
                            baseTextId = 0x180D;
                        } else if (this->doorType == ENDOOR_TYPE_2) {
                            baseTextId = 0x181D;
                        }
                        player->doorType = PLAYER_DOORTYPE_TALKING;
                        this->knobDoor.dyna.actor.textId = baseTextId + textIdOffset;
                    }
                } else if ((this->doorType == ENDOOR_TYPE_5) && (playerPosRelToDoor.z > 0.0f)) {
                    ScheduleOutput scheduleOutput;

                    if (Schedule_RunScript(play, D_8086778C[this->switchFlag], &scheduleOutput)) {
                        this->knobDoor.dyna.actor.textId = scheduleOutput.result + 0x1800;

                        player->doorType = ((this->knobDoor.dyna.actor.textId == 0x1821) && D_80867BC0)
                                               ? PLAYER_DOORTYPE_PROXIMITY
                                               : PLAYER_DOORTYPE_TALKING;
                    }
                }
                func_80122F28(player);
            }
        } else if ((this->doorType == ENDOOR_TYPE_4) && (this->knobDoor.dyna.actor.xzDistToPlayer > 240.0f)) {
            Actor_PlaySfx(&this->knobDoor.dyna.actor, NA_SE_EV_DOOR_OPEN);
            this->actionFunc = func_80867080;
        }
    }
}

void func_80866F94(EnDoor* this, PlayState* play) {
    s32 direction;

    if (this->openTimer != 0) {
        if (this->openTimer >= 0) {
            direction = 1;
        } else {
            direction = -1;
        }
        if (Math_ScaledStepToS(&this->knobDoor.dyna.actor.world.rot.y, direction * 0x3E80, 0x7D0)) {
            Math_StepToC(&this->openTimer, 0, 1);
        }
    } else {
        if (Math_ScaledStepToS(&this->knobDoor.dyna.actor.world.rot.y, 0, 0x7D0)) {
            this->actionFunc = func_80866B20;
            Actor_PlaySfx(&this->knobDoor.dyna.actor, NA_SE_EV_AUTO_DOOR_CLOSE);
        }
    }
}

void func_8086704C(EnDoor* this, PlayState* play) {
    if (this->knobDoor.dyna.actor.xzDistToPlayer < 120.0f) {
        this->actionFunc = func_808670F0;
    }
}

void func_80867080(EnDoor* this, PlayState* play) {
    if (this->knobDoor.dyna.actor.xzDistToPlayer < 120.0f) {
        this->actionFunc = func_808670F0;
    } else if (Math_ScaledStepToS(&this->knobDoor.dyna.actor.world.rot.y, -0x1800, 0x100)) {
        this->actionFunc = func_8086704C;
    }
}

void func_808670F0(EnDoor* this, PlayState* play) {
    if (Math_ScaledStepToS(&this->knobDoor.dyna.actor.world.rot.y, 0, 0x700)) {
        Actor_PlaySfx(&this->knobDoor.dyna.actor, NA_SE_EV_DOOR_CLOSE);
        this->actionFunc = func_80866B20;
    }
}

void func_80867144(EnDoor* this, PlayState* play) {
    s32 numEffects;
    s32 i;

    if (DECR(this->unk_1A6) == 0) {
        if (SkelAnime_Update(&this->knobDoor.skelAnime)) {
            this->actionFunc = func_80866B20;
            this->knobDoor.playOpenAnim = false;
        } else if (Animation_OnFrame(&this->knobDoor.skelAnime, sAnimOpenFrames[this->knobDoor.animIndex])) {
            Actor_PlaySfx(&this->knobDoor.dyna.actor, NA_SE_OC_DOOR_OPEN);
            if (this->knobDoor.skelAnime.playSpeed < 1.5f) {
                numEffects = (s32)(Rand_ZeroOne() * 30.0f) + 50;
                for (i = 0; i < numEffects; i++) {
                    EffectSsBubble_Spawn(play, &this->knobDoor.dyna.actor.world.pos, 60.0, 100.0f, 50.0f, 0.15f);
                }
            }
        } else if (Animation_OnFrame(&this->knobDoor.skelAnime, sAnimCloseFrames[this->knobDoor.animIndex])) {
            Actor_PlaySfx(&this->knobDoor.dyna.actor, NA_SE_EV_DOOR_CLOSE);
        }
    }
}

void EnDoor_Update(Actor* thisx, PlayState* play) {
    EnDoor* this = THIS;

    this->actionFunc(this, play);
}

s32 EnDoor_OverrideLimbDraw(PlayState* play, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, Actor* thisx) {
    TransitionActorEntry* transitionEntry;
    EnDoor* this = THIS;

    if (limbIndex == DOOR_LIMB_4) {
        Gfx** sideDLists = D_808679A4[this->knobDoor.dlIndex];

        transitionEntry = NULL;

        if (this->doorType != ENDOOR_TYPE_7) {
            transitionEntry = &play->doorCtx.transitionActorList[DOOR_GET_TRANSITION_ID(&this->knobDoor.dyna.actor)];
        }
        rot->z += this->knobDoor.dyna.actor.world.rot.y;
        if ((this->doorType == ENDOOR_TYPE_7) || (play->roomCtx.prevRoom.num >= 0) ||
            (transitionEntry->sides[0].room == transitionEntry->sides[1].room)) {
            s16 temp =
                (this->knobDoor.dyna.actor.shape.rot.y + this->knobDoor.skelAnime.jointTable[DOOR_LIMB_3].z + rot->z) -
                Math_Vec3f_Yaw(&play->view.eye, &this->knobDoor.dyna.actor.world.pos);

            *dList = (ABS_ALT(temp) < 0x4000) ? sideDLists[0] : sideDLists[1];

        } else {
            s32 index = 0;

            if (transitionEntry->sides[0].room != this->knobDoor.dyna.actor.room) {
                index = 1;
            }
            *dList = sideDLists[index];
        }
    }
    return false;
}

void EnDoor_Draw(Actor* thisx, PlayState* play) {
    EnDoor* this = THIS;

    if (this->knobDoor.dyna.actor.objectSlot == this->knobDoor.objectSlot) {
        OPEN_DISPS(play->state.gfxCtx);

        if ((this->doorType == ENDOOR_TYPE_7) && (this->switchFlag == 0)) {
            Gfx_DrawDListOpa(play, gameplay_keep_DL_0221B8);
        } else {
            Gfx_SetupDL25_Opa(play->state.gfxCtx);
        }
        SkelAnime_DrawOpa(play, this->knobDoor.skelAnime.skeleton, this->knobDoor.skelAnime.jointTable,
                          EnDoor_OverrideLimbDraw, NULL, &this->knobDoor.dyna.actor);
        if (this->knobDoor.dyna.actor.world.rot.y != 0) {
            if (this->knobDoor.dyna.actor.world.rot.y > 0) {
                gSPDisplayList(POLY_OPA_DISP++, gDoorRightDL);
            } else {
                gSPDisplayList(POLY_OPA_DISP++, gDoorLeftDL);
            }
        }
        if (this->unk_1A6) {
            Actor_DrawDoorLock(play, this->unk_1A6, 0);
        }

        CLOSE_DISPS(play->state.gfxCtx);
    }
}
