/*
 * File: z_dm_gm.c
 * Overlay: ovl_Dm_Gm
 * Description: Complete duplicate of Dm_An
 *   Because this is supposed to be a complete dup, we're going to overwrite it
 */

#include "z_dm_gm.h"


#include "attributes.h"
#include "overlays/actors/ovl_En_Door/z_en_door.h"

#include "assets/objects/object_an2/object_an2.h"
#include "assets/objects/object_an3/object_an3.h"
#include "assets/objects/object_an4/object_an4.h"
#include "assets/objects/object_mask_kerfay/object_mask_kerfay.h"
#include "assets/objects/object_msmo/object_msmo.h"

#define THIS ((DmGm*)thisx)

#define FLAGS                                                                                  \
    (ACTOR_FLAG_ATTENTION_ENABLED | ACTOR_FLAG_FRIENDLY | ACTOR_FLAG_UPDATE_CULLING_DISABLED | \
     ACTOR_FLAG_DRAW_CULLING_DISABLED)

void DmGm2_Init(Actor* thisx, PlayState* play);
void DmGm2_Destroy(Actor* thisx, PlayState* play);
void DmGm2_Update(Actor* thisx, PlayState* play);
void DmGm2_Draw(Actor* thisx, PlayState* play);

// Action funcs
void DmGm2_FinishInit(DmGm* this, PlayState* play);
void DmGm2_FollowSchedule(DmGm* this, PlayState* play);
void DmGm2_Talk(DmGm* this, PlayState* play);

ActorProfile Dm_Gm_Profile = {
    /**/ ACTOR_DM_GM,
    /**/ ACTORCAT_NPC,
    /**/ FLAGS,
    /**/ OBJECT_AN1,
    /**/ sizeof(DmGm),
    /**/ DmGm2_Init,
    /**/ DmGm2_Destroy,
    /**/ DmGm2_Update,
    /**/ NULL,
};

typedef enum AnjuScheduleResult {
    /*  0 */ ANJU_SCH_NONE,
    // Waiting for Kafei on the night of Day 3
    /*  1 */ ANJU_SCH_WAITING_FOR_KAFEI,
    // unused
    /*  2 */ ANJU_SCH_2,
    // Day 2, 13:45 ~ 15:25, No midnight meeting. Sit on the Laundry Pool under the rain
    /*  3 */ ANJU_SCH_LAUNDRY_POOL_SIT,
    // unused
    /*  4 */ ANJU_SCH_4,
    // unused
    /*  5 */ ANJU_SCH_5,
    // unused
    /*  6 */ ANJU_SCH_6,
    // unused
    /*  7 */ ANJU_SCH_7,
    // unused
    /*  8 */ ANJU_SCH_8,
    // unused
    /*  9 */ ANJU_SCH_9,
    // unused
    /* 10 */ ANJU_SCH_10,
    // unused
    /* 11 */ ANJU_SCH_11,
    // Day 3, Night, if not delivered the Pendant of Memories
    /* 12 */ ANJU_SCH_RANCH,
    // unused
    /* 13 */ ANJU_SCH_13,
    // Cooking lunch for Granny at 11:10 ~ 11:30 on Day 1 and Day 2 (if did had the Midnight meeting)
    /* 14 */ ANJU_SCH_COOKING,
    // unused
    /* 15 */ ANJU_SCH_15,
    // Day 1, 14:08 ~ 14:18. Receive Kafei's letter from Postman
    /* 16 */ ANJU_SCH_RECEIVE_LETTER_FROM_POSTMAN,
    // Day 1, 16:10 ~ 16:30. Attends the goron named after the player
    /* 17 */ ANJU_SCH_ATTEND_GORON,
    // Just standing on the front desk of the Inn
    /* 18 */ ANJU_SCH_RECEPTIONIST_IDLE,
    // Standing next to the Inn's front door at closing time
    /* 19 */ ANJU_SCH_WAITING_CLOSING_TIME,
    // unused
    /* 20 */ ANJU_SCH_20,
    // 12:00 ~ 12:15, Day 1 and Day 2 (if did had the Midnight meeting). Give lunch to Granny
    /* 21 */ ANJU_SCH_GIVE_LUNCH_TO_GRANNY,
    // Day 3, 06:00 ~ 11:00. Sweeping the Large Suite.
    /* 22 */ ANJU_SCH_SWEEPING,
    // Day 1, 00:00 ~ 06:00. Waiting for player at the kitchen to have the Midnight meeting.
    /* 23 */ ANJU_SCH_MIDNIGHT_MEETING,
    // Day 2, 21:30 ~ 23:00. On the staff room talking with her mom. This can be seen from the Knife Chamber
    /* 24 */ ANJU_SCH_TALKING_WITH_MOM,
    // Reunited with Kafei on the Staff room. Set manually in code instead of via script
    /* 25 */ ANJU_SCH_WITH_KAFEI,
    // Passing through to Granny's door (entering)
    /* 26 */ ANJU_SCH_DOOR_26,
    // Passing through to Granny's door (leaving)
    /* 27 */ ANJU_SCH_DOOR_27,
    // Passing through the door of the staff room (entering), after giving Granny's lunch
    /* 28 */ ANJU_SCH_DOOR_28,
    // Passing through the door of the staff room (leaving), after giving Granny's lunch
    /* 29 */ ANJU_SCH_DOOR_29,
    // Passing through the door of the staff room (entering), after closing the Inn
    /* 30 */ ANJU_SCH_DOOR_30,
    // Passing through the door of the staff room (leaving), to have the midnight meeting
    /* 31 */ ANJU_SCH_DOOR_31,
    // Passing through the door of the staff room (leaving), going to the Laundry Pool
    /* 32 */ ANJU_SCH_DOOR_32,
    // Passing through the Inn's front door (leaving) (inside the Inn), going to the Laundry Pool
    /* 33 */ ANJU_SCH_DOOR_33,
    // Passing through the Inn's front door (entering) (inside the Inn), going from the Laundry Pool
    /* 34 */ ANJU_SCH_DOOR_34,
    // Passing through the door of the staff room (entering), after going to the Laundry Pool
    /* 35 */ ANJU_SCH_DOOR_35,
    // Passing through the door of the Large Suite (leaving), after sweeping the floor
    /* 36 */ ANJU_SCH_DOOR_36,
    // Passing through the Inn's front door (leaving) (East Clock Town), going to the Laundry Pool
    /* 37 */ ANJU_SCH_DOOR_37,
    // Passing through the Inn's front door (entering) (East Clock Town), going from the Laundry Pool
    /* 38 */ ANJU_SCH_DOOR_38,
    // Passing through the door of the staff room (entering), after sweeping the floor
    /* 39 */ ANJU_SCH_DOOR_39,
    // Going from the front desk to the kitchen
    /* 40 */ ANJU_SCH_WALKING_40,
    // unused
    /* 41 */ ANJU_SCH_41,
    // Walking from the kitchen to Granny's room
    /* 42 */ ANJU_SCH_WALKING_42,
    // Inside Granny's room, walking to give her her food
    /* 43 */ ANJU_SCH_WALKING_43,
    // Inside Granny's room, walking out
    /* 44 */ ANJU_SCH_WALKING_44,
    // Left Granny's room, walking towards staff room
    /* 45 */ ANJU_SCH_WALKING_45,
    // Left staff room, walking to front desk
    /* 46 */ ANJU_SCH_WALKING_46,
    // Walking from the front desk to right next to the Inn's front door
    /* 47 */ ANJU_SCH_WALKING_47,
    // Walking from the Inn's front door after closing, to the staff room
    /* 48 */ ANJU_SCH_WALKING_48,
    // Walking from the staff room to the kitchen, to have the midnight meeting
    /* 49 */ ANJU_SCH_WALKING_49,
    // Walking from the staff room to Inn's front door, to go to the Laundry Pool
    /* 50 */ ANJU_SCH_WALKING_50,
    // Walking from the Inn's front door to the staff room, after going to the Laundry Pool
    /* 51 */ ANJU_SCH_WALKING_51,
    // Day 3, 11:00 ~ 11:25, Stopped sweeping, walking out of the room
    /* 52 */ ANJU_SCH_WALKING_52,
    // Day 3, 11:00 ~ 11:25, Walking through the hallway after sweeping
    /* 53 */ ANJU_SCH_WALKING_53,
    // Walking through East Clock Town, going to the Laundry Pool
    /* 54 */ ANJU_SCH_WALKING_54,
    // Walking through South Clock Town, East Clock Town perspective, going to the Laundry Pool
    /* 55 */ ANJU_SCH_WALKING_55,
    // Walking through Laundry Pool, entering
    /* 56 */ ANJU_SCH_WALKING_56,
    // Walking through Laundry Pool, leaving
    /* 57 */ ANJU_SCH_WALKING_57,
    // Walking through South Clock Town, East Clock Town perspective, going to the Inn from the Laundry Pool
    /* 58 */ ANJU_SCH_WALKING_58,
    // Walking through East Clock Town, going to the Inn from the Laundry Pool
    /* 59 */ ANJU_SCH_WALKING_59,
    // Walking through East Clock Town, South Clock Town perspective, going to the Laundry Pool
    /* 60 */ ANJU_SCH_WALKING_60,
    // Walking through South Clock Town, going to the Laundry Pool
    /* 61 */ ANJU_SCH_WALKING_61,
    // Walking through South Clock Town, going to the Inn from the Laundry Pool
    /* 62 */ ANJU_SCH_WALKING_62,
    // Walking through East Clock Town, South Clock Town perspective, going to the Inn from the Laundry Pool
    /* 63 */ ANJU_SCH_WALKING_63,
    /* 64 */ ANJU_SCH_MAX
} AnjuScheduleResult;

#include "src/overlays/actors/ovl_En_An/scheduleScripts.schl.inc"

static s32 sSearchTimePathLimit[ANJU_SCH_MAX] = {
    -1, // ANJU_SCH_NONE
    10, // ANJU_SCH_WAITING_FOR_KAFEI
    -1, // ANJU_SCH_2
    0,  // ANJU_SCH_LAUNDRY_POOL_SIT
    -1, // ANJU_SCH_4
    -1, // ANJU_SCH_5
    -1, // ANJU_SCH_6
    -1, // ANJU_SCH_7
    -1, // ANJU_SCH_8
    -1, // ANJU_SCH_9
    -1, // ANJU_SCH_10
    -1, // ANJU_SCH_11
    -1, // ANJU_SCH_RANCH
    -1, // ANJU_SCH_13
    0,  // ANJU_SCH_COOKING
    -1, // ANJU_SCH_15
    10, // ANJU_SCH_RECEIVE_LETTER_FROM_POSTMAN
    10, // ANJU_SCH_ATTEND_GORON
    10, // ANJU_SCH_RECEPTIONIST_IDLE
    11, // ANJU_SCH_WAITING_CLOSING_TIME
    -1, // ANJU_SCH_20
    4,  // ANJU_SCH_GIVE_LUNCH_TO_GRANNY
    22, // ANJU_SCH_SWEEPING
    15, // ANJU_SCH_MIDNIGHT_MEETING
    -1, // ANJU_SCH_TALKING_WITH_MOM
    -1, // ANJU_SCH_WITH_KAFEI
    3,  // ANJU_SCH_DOOR_26
    6,  // ANJU_SCH_DOOR_27
    8,  // ANJU_SCH_DOOR_28
    9,  // ANJU_SCH_DOOR_29
    13, // ANJU_SCH_DOOR_30
    14, // ANJU_SCH_DOOR_31
    16, // ANJU_SCH_DOOR_32
    18, // ANJU_SCH_DOOR_33
    19, // ANJU_SCH_DOOR_34
    21, // ANJU_SCH_DOOR_35
    23, // ANJU_SCH_DOOR_36
    0,  // ANJU_SCH_DOOR_37
    5,  // ANJU_SCH_DOOR_38
    25, // ANJU_SCH_DOOR_39
    0,  // ANJU_SCH_WALKING_40
    1,  // ANJU_SCH_41
    2,  // ANJU_SCH_WALKING_42
    4,  // ANJU_SCH_WALKING_43
    5,  // ANJU_SCH_WALKING_44
    7,  // ANJU_SCH_WALKING_45
    10, // ANJU_SCH_WALKING_46
    11, // ANJU_SCH_WALKING_47
    12, // ANJU_SCH_WALKING_48
    15, // ANJU_SCH_WALKING_49
    17, // ANJU_SCH_WALKING_50
    20, // ANJU_SCH_WALKING_51
    22, // ANJU_SCH_WALKING_52
    24, // ANJU_SCH_WALKING_53
    1,  // ANJU_SCH_WALKING_54
    2,  // ANJU_SCH_WALKING_55
    0,  // ANJU_SCH_WALKING_56
    1,  // ANJU_SCH_WALKING_57
    3,  // ANJU_SCH_WALKING_58
    4,  // ANJU_SCH_WALKING_59
    0,  // ANJU_SCH_WALKING_60
    1,  // ANJU_SCH_WALKING_61
    2,  // ANJU_SCH_WALKING_62
    3,  // ANJU_SCH_WALKING_63
};

static ColliderCylinderInit sCylinderInit = {
    {
        COL_MATERIAL_HIT1,
        AT_NONE,
        AC_NONE,
        OC1_ON | OC1_TYPE_ALL,
        OC2_TYPE_1,
        COLSHAPE_CYLINDER,
    },
    {
        ELEM_MATERIAL_UNK1,
        { 0x00000000, 0x00, 0x00 },
        { 0x00000000, 0x00, 0x00 },
        ATELEM_NONE | ATELEM_SFX_NORMAL,
        ACELEM_NONE,
        OCELEM_ON,
    },
    { 14, 62, 0, { 0, 0, 0 } },
};

static CollisionCheckInfoInit2 sColChkInfoInit = { 0, 0, 0, 0, MASS_IMMOVABLE };


Actor* DmGm2_FindActor(DmGm* this, PlayState* play, u8 actorCategory, s16 actorId) {
    Actor* actorIter = NULL;

    while (true) {
        actorIter = SubS_FindActor(play, actorIter, actorCategory, actorId);

        if (actorIter == NULL) {
            break;
        }

        if ((this != (DmGm*)actorIter) && (actorIter->update != NULL)) {
            break;
        }

        if (actorIter->next == NULL) {
            actorIter = NULL;
            break;
        }

        actorIter = actorIter->next;
    }

    return actorIter;
}

// Name after DMGM2_8000
Actor* DmGm_Func_80B53A7C(DmGm* this, PlayState* play, u8 actorCategory, s16 actorId) {
    Actor* actorIter = NULL;

    while (true) {
        actorIter = SubS_FindActor(play, actorIter, actorCategory, actorId);

        if (actorIter == NULL) {
            break;
        }

        if ((this != (DmGm*)actorIter) && (actorIter->update != NULL)) {
            if (!DMGM2_GET_8000(actorIter)) {
                break;
            }
        }

        if (actorIter->next == NULL) {
            actorIter = NULL;
            break;
        }

        actorIter = actorIter->next;
    }

    return actorIter;
}

// EnDoor* DmGm2_FindScheduleDoor(PlayState* play, AnjuScheduleResult scheduleOutputResult);

/**
 * Anju stores her animations across 4 objects and all of them are put together right next to each other in the
 * sAnimationInfo array. Due to this, animation functions check which object to load by comparing index ranges. To make
 * this a bit easier to read, this enum includes `DMGM2_ANIMOBJ_*` values that mark when a range of animations of a
 * certain object start
 */
typedef enum DmGm2Animation {
    /* -1 */ DMGM2_ANIM_NONE = -1,
    /*  0 */ DMGM2_ANIM_HOLD_HANDS,
    /*  1 */ DMGM2_ANIM_IDLE,
    /*  2 */ DMGM2_ANIM_IDLE_MORPH,
    /*  3 */ DMGM2_ANIM_BOW,
    /*  4 */ DMGM2_ANIM_BOW_MORPH,
    /*  5 */ DMGM2_ANIM_SURPRISED,
    /*  6 */ DMGM2_ANIM_LOOK_UP_RELIEVED,
    /*  7 */ DMGM2_ANIM_WALK,
    /*  8 */ DMGM2_ANIM_WALK2, // Duplicate of DMGM2_ANIM_WALK
    /*  9 */ DMGM2_ANIM_SIT,
    /* 10 */ DMGM2_ANIM_SIT_MORPH,
    /* 11 */ DMGM2_ANIM_SITTING_IN_DISBELIEF,
    /* 12 */ DMGM2_ANIM_COOK,
    /* 13 */ DMGM2_ANIM_TASTE,
    /* 14 */ DMGM2_ANIM_TASTE_END,
    /* 15 */ DMGM2_ANIM_WAIT_WITH_TRAY,
    /* 16 */ DMGM2_ANIM_WALK_WITH_TRAY,

    /* 17 */ DMGM2_ANIMOBJ_AN2,
    /* 17 */ DMGM2_ANIM_UMBRELLA_IDLE = DMGM2_ANIMOBJ_AN2,
    /* 18 */ DMGM2_ANIM_UMBRELLA_WALK,
    /* 19 */ DMGM2_ANIM_UMBRELLA_SIT,
    /* 20 */ DMGM2_ANIM_UMBRELLA_CRY,

    /* 21 */ DMGM2_ANIMOBJ_AN3,
    /* 21 */ DMGM2_ANIM_BROOM_IDLE = DMGM2_ANIMOBJ_AN3,
    /* 22 */ DMGM2_ANIM_BROOM_WALK,
    /* 23 */ DMGM2_ANIM_BROOM_SWEEP,
    /* 24 */ DMGM2_ANIM_24, //! @bug See note at `sAnimationInfo`

    /* 25 */ DMGM2_ANIMOBJ_AN4,
    /* 25 */ DMGM2_ANIM_MASK_STAND_LOOP = DMGM2_ANIMOBJ_AN4,
    /* 26 */ DMGM2_ANIM_MASK_KNEEL,
    /* 27 */ DMGM2_ANIM_MASK_KNEEL_LOOP,
    /* 28 */ DMGM2_ANIM_HUG,
    /* 29 */ DMGM2_ANIM_HUG_LOOP,
    /* 30 */ DMGM2_ANIM_HUG_RELEASE,
    /* 31 */ DMGM2_ANIM_HUG_RELEASE_LOOP,
    /* 32 */ DMGM2_ANIM_COMBINE_MASKS_1,
    /* 33 */ DMGM2_ANIM_COMBINE_MASKS_2,
    /* 34 */ DMGM2_ANIM_LOOK_UP,
    /* 35 */ DMGM2_ANIM_LOOK_UP_LOOP,
    /* 36 */ DMGM2_ANIM_MAX
} DmGm2Animation;

static AnimationInfoS sAnimationInfo[DMGM2_ANIM_MAX] = {
    { &gAnju1HoldHandsAnim, 1.0f, 0, -1, ANIMMODE_LOOP, 0 },          // DMGM2_ANIM_HOLD_HANDS
    { &gAnju1IdleAnim, 1.0f, 0, -1, ANIMMODE_LOOP, 0 },               // DMGM2_ANIM_IDLE
    { &gAnju1IdleAnim, 1.0f, 0, -1, ANIMMODE_LOOP, -6 },              // DMGM2_ANIM_IDLE_MORPH
    { &gAnju1BowAnim, 1.0f, 0, -1, ANIMMODE_ONCE, 0 },                // DMGM2_ANIM_BOW
    { &gAnju1BowAnim, 1.0f, 0, -1, ANIMMODE_ONCE, -6 },               // DMGM2_ANIM_BOW_MORPH
    { &gAnju1SurprisedAnim, 1.0f, 0, -1, ANIMMODE_ONCE, 0 },          // DMGM2_ANIM_SURPRISED
    { &gAnju1LookUpRelievedAnim, 1.0f, 0, -1, ANIMMODE_ONCE, 0 },     // DMGM2_ANIM_LOOK_UP_RELIEVED
    { &gAnju1WalkAnim, 1.0f, 0, -1, ANIMMODE_LOOP, 0 },               // DMGM2_ANIM_WALK
    { &gAnju1WalkAnim, 1.0f, 0, -1, ANIMMODE_LOOP, 0 },               // DMGM2_ANIM_WALK2
    { &gAnju1SitAnim, 1.0f, 0, -1, ANIMMODE_LOOP, 0 },                // DMGM2_ANIM_SIT
    { &gAnju1SitAnim, 1.0f, 0, -1, ANIMMODE_LOOP, -6 },               // DMGM2_ANIM_SIT_MORPH
    { &gAnju1SittingInDisbeliefAnim, 1.0f, 0, -1, ANIMMODE_LOOP, 0 }, // DMGM2_ANIM_SITTING_IN_DISBELIEF
    { &gAnju1CookAnim, 1.0f, 0, -1, ANIMMODE_LOOP, 0 },               // DMGM2_ANIM_COOK
    { &gAnju1TasteAnim, 1.0f, 0, -1, ANIMMODE_ONCE, 0 },              // DMGM2_ANIM_TASTE
    { &gAnju1TasteEndAnim, 1.0f, 0, -1, ANIMMODE_ONCE, 0 },           // DMGM2_ANIM_TASTE_END
    { &gAnju1WaitWithTrayAnim, 1.0f, 0, -1, ANIMMODE_LOOP, 0 },       // DMGM2_ANIM_WAIT_WITH_TRAY
    { &gAnju1WalkWithTrayAnim, 1.0f, 0, -1, ANIMMODE_LOOP, 0 },       // DMGM2_ANIM_WALK_WITH_TRAY

    // DMGM2_ANIMOBJ_AN2
    { &gAnju2UmbrellaIdleAnim, 1.0f, 0, -1, ANIMMODE_LOOP, 0 }, // DMGM2_ANIM_UMBRELLA_IDLE
    { &gAnju2UmbrellaWalkAnim, 1.0f, 0, -1, ANIMMODE_LOOP, 0 }, // DMGM2_ANIM_UMBRELLA_WALK
    { &gAnju2UmbrellaSitAnim, 1.0f, 0, -1, ANIMMODE_ONCE, 0 },  // DMGM2_ANIM_UMBRELLA_SIT
    { &gAnju2UmbrellaCryAnim, 1.0f, 0, -1, ANIMMODE_LOOP, 0 },  // DMGM2_ANIM_UMBRELLA_CRY

    // DMGM2_ANIMOBJ_AN3
    { &gAnju3BroomIdleAnim, 1.0f, 0, -1, ANIMMODE_LOOP, 0 },  // DMGM2_ANIM_BROOM_IDLE
    { &gAnju3BroomWalkAnim, 1.0f, 0, -1, ANIMMODE_LOOP, 0 },  // DMGM2_ANIM_BROOM_WALK
    { &gAnju3BroomSweepAnim, 1.0f, 0, -1, ANIMMODE_LOOP, 0 }, // DMGM2_ANIM_BROOM_SWEEP
    //! @bug Uses symbol from OBJECT_AN2 instead of OBJECT_AN3. Because of this entry being in the OBJECT_AN3 block,
    //! then the actor will try to load this address from OBJECT_AN3, but this address is way outside said object,
    //! producing an OoB read and reading garbage, possible from other object. This will likely produce a crash.
    { &gAnju2UmbrellaSitAnim, -1.0f, 0, -1, ANIMMODE_ONCE, 0 }, // DMGM2_ANIM_24

    // DMGM2_ANIMOBJ_AN4
    { &gAnju4MaskStandLoopAnim, 1.0f, 0, -1, ANIMMODE_LOOP, 0 },  // DMGM2_ANIM_MASK_STAND_LOOP
    { &gAnju4MaskKneelAnim, 1.0f, 0, -1, ANIMMODE_ONCE, 0 },      // DMGM2_ANIM_MASK_KNEEL
    { &gAnju4MaskKneelLoopAnim, 1.0f, 0, -1, ANIMMODE_LOOP, 0 },  // DMGM2_ANIM_MASK_KNEEL_LOOP
    { &gAnju4HugAnim, 1.0f, 0, -1, ANIMMODE_ONCE, 0 },            // DMGM2_ANIM_HUG
    { &gAnju4HugLoopAnim, 1.0f, 0, -1, ANIMMODE_LOOP, 0 },        // DMGM2_ANIM_HUG_LOOP
    { &gAnju4HugReleaseAnim, 1.0f, 0, -1, ANIMMODE_ONCE, 0 },     // DMGM2_ANIM_HUG_RELEASE
    { &gAnju4HugReleaseLoopAnim, 1.0f, 0, -1, ANIMMODE_LOOP, 0 }, // DMGM2_ANIM_HUG_RELEASE_LOOP
    { &gAnju4CombineMasks1Anim, 1.0f, 0, -1, ANIMMODE_ONCE, 0 },  // DMGM2_ANIM_COMBINE_MASKS_1
    { &gAnju4CombineMasks2Anim, 1.0f, 0, -1, ANIMMODE_ONCE, 0 },  // DMGM2_ANIM_COMBINE_MASKS_2
    { &gAnju4LookUpAnim, 1.0f, 0, -1, ANIMMODE_ONCE, 0 },         // DMGM2_ANIM_LOOK_UP
    { &gAnju4LookUpLoopAnim, 1.0f, 0, -1, ANIMMODE_LOOP, 0 },     // DMGM2_ANIM_LOOK_UP_LOOP
};

s32 DmGm2_UpdateSkelAnime(DmGm* this, PlayState* play) {
    s8 originalObjectSlot = this->actor.objectSlot;
    s8 otherObjectSlot = OBJECT_SLOT_NONE;
    s32 ret = false;

    if ((this->animIndex >= DMGM2_ANIMOBJ_AN4) && (this->an4ObjectSlot > OBJECT_SLOT_NONE)) {
        otherObjectSlot = this->an4ObjectSlot;
    } else if ((this->animIndex >= DMGM2_ANIMOBJ_AN3) && (this->an3ObjectSlot > OBJECT_SLOT_NONE)) {
        otherObjectSlot = this->an3ObjectSlot;
    } else if ((this->animIndex >= DMGM2_ANIMOBJ_AN2) && (this->an2ObjectSlot > OBJECT_SLOT_NONE)) {
        otherObjectSlot = this->an2ObjectSlot;
    } else if (this->animIndex < DMGM2_ANIMOBJ_AN2) {
        otherObjectSlot = originalObjectSlot;
    }

    if (otherObjectSlot <= OBJECT_SLOT_NONE) {
        return 0;
    }

    if (otherObjectSlot > OBJECT_SLOT_NONE) {
        gSegments[0x06] = OS_K0_TO_PHYSICAL(play->objectCtx.slots[otherObjectSlot].segment);
        this->skelAnime.playSpeed = this->animPlaySpeed;
        ret = SkelAnime_Update(&this->skelAnime);
        gSegments[0x06] = OS_K0_TO_PHYSICAL(play->objectCtx.slots[originalObjectSlot].segment);
    }

    return ret;
}

s32 DmGm2_ChangeAnim(DmGm* this, PlayState* play, DmGm2Animation animIndex) {
    s8 originalObjectSlot = this->actor.objectSlot;
    s8 otherObjectSlot = OBJECT_SLOT_NONE;
    s32 changeAnim = false;
    s32 didAnimChange = false;

    if ((animIndex >= DMGM2_ANIMOBJ_AN4) && (this->an4ObjectSlot > OBJECT_SLOT_NONE)) {
        otherObjectSlot = this->an4ObjectSlot;
    } else if ((animIndex >= DMGM2_ANIMOBJ_AN3) && (this->an3ObjectSlot > OBJECT_SLOT_NONE)) {
        otherObjectSlot = this->an3ObjectSlot;
    } else if ((animIndex >= DMGM2_ANIMOBJ_AN2) && (this->an2ObjectSlot > OBJECT_SLOT_NONE)) {
        otherObjectSlot = this->an2ObjectSlot;
    } else if (animIndex < DMGM2_ANIMOBJ_AN2) {
        otherObjectSlot = originalObjectSlot;
    }

    if (otherObjectSlot <= OBJECT_SLOT_NONE) {
        return false;
    }

    switch (animIndex) {
        case DMGM2_ANIM_IDLE:
        case DMGM2_ANIM_IDLE_MORPH:
            if ((this->animIndex != DMGM2_ANIM_IDLE) && (this->animIndex != DMGM2_ANIM_IDLE_MORPH)) {
                changeAnim = true;
            }
            break;

        case DMGM2_ANIM_WALK:
        case DMGM2_ANIM_WALK2:
            if ((this->animIndex != DMGM2_ANIM_WALK) && (this->animIndex != DMGM2_ANIM_WALK2)) {
                changeAnim = true;
            }
            break;

        case DMGM2_ANIM_SIT:
        case DMGM2_ANIM_SIT_MORPH:
            if ((this->animIndex != DMGM2_ANIM_SIT) && (this->animIndex != DMGM2_ANIM_SIT_MORPH)) {
                changeAnim = true;
            }
            break;

        default:
            if (this->animIndex != animIndex) {
                changeAnim = true;
            }
            break;
    }

    if (changeAnim && (otherObjectSlot > OBJECT_SLOT_NONE)) {
        gSegments[0x06] = OS_K0_TO_PHYSICAL(play->objectCtx.slots[otherObjectSlot].segment);
        this->animIndex = animIndex;
        didAnimChange = SubS_ChangeAnimationByInfoS(&this->skelAnime, sAnimationInfo, animIndex);
        this->animPlaySpeed = this->skelAnime.playSpeed;
        gSegments[0x06] = OS_K0_TO_PHYSICAL(play->objectCtx.slots[originalObjectSlot].segment);
    }

    return didAnimChange;
}

void DmGm2_UpdateCollider(DmGm* this, PlayState* play) {
    f32 height;
    Vec3f sp24;

    if (this->scheduleResult == ANJU_SCH_WITH_KAFEI) {
        static Vec3f D_80B58E34 = { 0.0f, 0.0f, 8.0f };

        Lib_Vec3f_TranslateAndRotateY(&this->actor.world.pos, this->actor.shape.rot.y, &D_80B58E34, &sp24);
        this->collider.dim.radius = 20;
        Math_Vec3f_ToVec3s(&this->collider.dim.pos, &sp24);
    } else {
        Collider_UpdateCylinder(&this->actor, &this->collider);
    }

    height = this->actor.focus.pos.y - this->actor.world.pos.y;
    this->collider.dim.height = TRUNCF_BINANG(height);
    CollisionCheck_SetOC(play, &play->colChkCtx, &this->collider.base);
}

typedef enum DmGm2Eyes {
    /* 0 */ DMGM2_EYES_OPEN,
    /* 1 */ DMGM2_EYES_HALF1,
    /* 2 */ DMGM2_EYES_CLOSED,
    /* 3 */ DMGM2_EYES_HALF2,
    /* 4 */ DMGM2_EYES_COMFORT,
    /* 5 */ DMGM2_EYES_SAD,
    /* 6 */ DMGM2_EYES_RELIEVED_CLOSED,
    /* 7 */ DMGM2_EYES_MAX
} DmGm2Eyes;

typedef enum DmGm2Mouth {
    /* 0 */ DMGM2_MOUTH_CLOSED,
    /* 1 */ DMGM2_MOUTH_HAPPY,
    /* 2 */ DMGM2_MOUTH_OPEN,
    /* 3 */ DMGM2_MOUTH_MAX
} DmGm2Mouth;

typedef enum DmGm2Face {
    /*  0 */ DMGM2_FACE_0,
    /*  1 */ DMGM2_FACE_1,
    /*  2 */ DMGM2_FACE_2,
    /*  3 */ DMGM2_FACE_3,
    /*  4 */ DMGM2_FACE_4,
    /*  5 */ DMGM2_FACE_5,
    /*  6 */ DMGM2_FACE_6,
    /*  7 */ DMGM2_FACE_7, // RELIEVED?
    /*  8 */ DMGM2_FACE_8, // COMFORTING
    /*  9 */ DMGM2_FACE_9, // HAPPY_BLINK?
    /* 10 */ DMGM2_FACE_MAX
} DmGm2Face;

void DmGm2_UpdateFace(DmGm* this) {
    static s16 sMouthIndices[DMGM2_FACE_MAX] = {
        DMGM2_MOUTH_CLOSED, // DMGM2_FACE_0
        DMGM2_MOUTH_OPEN,   // DMGM2_FACE_1
        DMGM2_MOUTH_CLOSED, // DMGM2_FACE_2
        DMGM2_MOUTH_HAPPY,  // DMGM2_FACE_3
        DMGM2_MOUTH_OPEN,   // DMGM2_FACE_4
        DMGM2_MOUTH_CLOSED, // DMGM2_FACE_5
        DMGM2_MOUTH_HAPPY,  // DMGM2_FACE_6
        DMGM2_MOUTH_OPEN,   // DMGM2_FACE_7
        DMGM2_MOUTH_HAPPY,  // DMGM2_FACE_8
        DMGM2_MOUTH_HAPPY,  // DMGM2_FACE_9
    };
    s32 skipBlink = false;

    if (this->stateFlags & DMGM2_STATE_UPDATE_EYES) {
        if (DECR(this->eyeTimer) == 0) {
            switch (this->faceIndex) {
                case DMGM2_FACE_2:
                case DMGM2_FACE_4:
                case DMGM2_FACE_6:
                    if ((this->eyeTexIndex == DMGM2_EYES_SAD) || (this->eyeTexIndex == DMGM2_EYES_CLOSED)) {
                        skipBlink = true;
                        this->eyeTexIndex = DMGM2_EYES_SAD;
                    }
                    break;

                case DMGM2_FACE_5:
                case DMGM2_FACE_7:
                    if ((this->eyeTexIndex == DMGM2_EYES_RELIEVED_CLOSED) || (this->eyeTexIndex == DMGM2_EYES_HALF1)) {
                        skipBlink = true;
                        this->eyeTexIndex = DMGM2_EYES_RELIEVED_CLOSED;
                    }
                    break;

                case DMGM2_FACE_8:
                    if ((this->eyeTexIndex == DMGM2_EYES_COMFORT) || (this->eyeTexIndex == DMGM2_EYES_CLOSED)) {
                        skipBlink = true;
                        this->eyeTexIndex = DMGM2_EYES_COMFORT;
                    }
                    break;
            }

            if (!skipBlink) {
                if ((this->eyeTexIndex == DMGM2_EYES_COMFORT) || (this->eyeTexIndex == DMGM2_EYES_SAD)) {
                    this->eyeTexIndex = DMGM2_EYES_OPEN;
                } else if (this->eyeTexIndex == DMGM2_EYES_RELIEVED_CLOSED) {
                    this->eyeTexIndex = DMGM2_EYES_HALF1;
                }
            }

            if (!skipBlink) {
                this->eyeTexIndex++;

                if (this->eyeTexIndex > DMGM2_EYES_HALF2) {
                    if ((this->faceIndex == DMGM2_FACE_0) || (this->faceIndex == DMGM2_FACE_1) ||
                        (this->faceIndex == DMGM2_FACE_3)) {
                        this->eyeTimer = Rand_S16Offset(30, 30);
                    } else {
                        this->eyeTimer = 8;
                    }
                    this->eyeTexIndex = DMGM2_EYES_OPEN;
                }
            }
        }
    }

    this->mouthTexIndex = sMouthIndices[this->faceIndex];
}

typedef enum DmGm2Accessory {
    /* 0 */ DMGM2_ACCESSORY_FOOD_TRAY,
    /* 1 */ DMGM2_ACCESSORY_KAFEI_MASK,
    /* 2 */ DMGM2_ACCESSORY_UMBRELLA,
    /* 3 */ DMGM2_ACCESSORY_BROOM,
    /* 4 */ DMGM2_ACCESSORY_CHOPSTICKS,
    /* 5 */ DMGM2_ACCESSORY_MOON_MASK
} DmGm2Accessory;

void DmGm2_DrawAccessory(DmGm* this, PlayState* play, DmGm2Accessory accessoryId) {
    s8 originalObjectSlot = this->actor.objectSlot;
    s8 otherObjectSlot;

    OPEN_DISPS(play->state.gfxCtx);

    Matrix_Push();

    switch (accessoryId) {
        case DMGM2_ACCESSORY_FOOD_TRAY:
            if ((this->stateFlags & DMGM2_STATE_DRAW_TRAY) && !this->forceDraw) {
                this->trayTexScrollTimer1++;
                this->trayTexScrollTimer2 -= 2;
                Gfx_SetupDL25_Xlu(play->state.gfxCtx);

                MATRIX_FINALIZE_AND_LOAD(POLY_XLU_DISP++, play->state.gfxCtx);
                gSPSegment(POLY_XLU_DISP++, 0x08,
                           Gfx_TwoTexScroll(play->state.gfxCtx, 0, this->trayTexScrollTimer1, 0, 16, 16, 1, 0,
                                            this->trayTexScrollTimer2, 16, 16));
                gSPDisplayList(POLY_XLU_DISP++, gAnju1FoodTrayDL);

                Gfx_SetupDL25_Opa(play->state.gfxCtx);
            }
            break;

        case DMGM2_ACCESSORY_KAFEI_MASK:
            otherObjectSlot = this->maskKerfayObjectSlot;
            if ((this->stateFlags & DMGM2_STATE_DRAW_KAFEIS_MASK) && !this->forceDraw &&
                (otherObjectSlot > OBJECT_SLOT_NONE)) {
                static Vec3f D_80B58E54 = { 190.0f, -130.0f, 0.0f };
                static Vec3s D_80B58E60 = { 0, 0, 0x4168 };

                gSPSegment(POLY_OPA_DISP++, 0x0A, play->objectCtx.slots[otherObjectSlot].segment);

                Matrix_TranslateRotateZYX(&D_80B58E54, &D_80B58E60);

                MATRIX_FINALIZE_AND_LOAD(POLY_OPA_DISP++, play->state.gfxCtx);
                gSPDisplayList(POLY_OPA_DISP++, gKafeisMaskDL);
                gSPSegment(POLY_OPA_DISP++, 0x06, play->objectCtx.slots[originalObjectSlot].segment);
            }
            break;

        case DMGM2_ACCESSORY_UMBRELLA:
            otherObjectSlot = this->an2ObjectSlot;
            if ((this->stateFlags & DMGM2_STATE_DRAW_UMBRELLA) && !this->forceDraw &&
                (otherObjectSlot > OBJECT_SLOT_NONE)) {
                gSPSegment(POLY_OPA_DISP++, 0x06, play->objectCtx.slots[otherObjectSlot].segment);
                gSPDisplayList(POLY_OPA_DISP++, gAnju2UmbrellaDL);
                gSPSegment(POLY_OPA_DISP++, 0x06, play->objectCtx.slots[originalObjectSlot].segment);
            }
            break;

        case DMGM2_ACCESSORY_BROOM:
            otherObjectSlot = this->an3ObjectSlot;
            if ((this->stateFlags & DMGM2_STATE_DRAW_BROOM) && !this->forceDraw &&
                (otherObjectSlot > OBJECT_SLOT_NONE)) {
                gSPSegment(POLY_OPA_DISP++, 0x06, play->objectCtx.slots[otherObjectSlot].segment);
                gSPDisplayList(POLY_OPA_DISP++, gAnju3BroomDL);
                gSPSegment(POLY_OPA_DISP++, 0x06, play->objectCtx.slots[originalObjectSlot].segment);
            }
            break;

        case DMGM2_ACCESSORY_CHOPSTICKS:
            if ((this->stateFlags & DMGM2_STATE_DRAW_CHOPSTICKS) && !this->forceDraw) {
                gSPDisplayList(POLY_OPA_DISP++, gAnju1ChopsticksDL);
            }
            break;

        //case DMGM2_ACCESSORY_MOON_MASK:

        default:
            break;
    }

    Matrix_Pop();

    CLOSE_DISPS(play->state.gfxCtx);
}

s32 DmGm2_ChangeCutscene(DmGm* this, s16 csId) {
    s32 ret = false;

    if (CutsceneManager_GetCurrentCsId() == CS_ID_GLOBAL_TALK) {
        CutsceneManager_Stop(CS_ID_GLOBAL_TALK);
        CutsceneManager_Queue(csId);
    } else if (CutsceneManager_IsNext(csId)) {
        CutsceneManager_StartWithPlayerCs(csId, &this->actor);
        ret = true;
    } else {
        CutsceneManager_Queue(csId);
    }

    return ret;
}

s16 DmGm2_GetCsId(DmGm* this, s32 numCutscenes) {
    s16 csId = this->actor.csId;
    s32 i;

    for (i = 0; i < numCutscenes; i++) {
        csId = CutsceneManager_GetAdditionalCsId(csId);
    }

    return csId;
}

s16 DmGm2_GetChildCsId(DmGm* this, s32 numCutscenes) {
    Actor* child = this->actor.child;
    s16 csId = CS_ID_NONE;
    s32 i;

    if ((child != NULL) && (child->update != NULL)) {
        csId = child->csId;

        for (i = 0; i < numCutscenes; i++) {
            csId = CutsceneManager_GetAdditionalCsId(csId);
        }
    }

    return csId;
}

// s32 DmGm2_MsgEvent_ReceiveLetterFromPostman(Actor* thisx, PlayState* play) {

// s32 DmGm2_MsgEvent_AttendGoron(Actor* thisx, PlayState* play) {

// s32 DmGm2_MsgEvent_GiveLunchToGranny(Actor* thisx, PlayState* play) {

// Only used if Player is using Kafei's Mask or if Human and Promised midnight meeting
// s32 DmGm2_MsgEvent_MidnightMeeting(Actor* thisx, PlayState* play) {

// s32 DmGm2_MsgEvent_Cooking(Actor* thisx, PlayState* play) {

s32 DmGm2_MsgEvent_LaundryPool(Actor* thisx, PlayState* play) {
    DmGm* this = (DmGm*)thisx;
    s32 ret = false;

    switch (this->msgEventState) {
        case 0x0:
            if ((Player_GetMask(play) == PLAYER_MASK_KAFEIS_MASK) ||
                CHECK_WEEKEVENTREG(WEEKEVENTREG_TALKED_ANJU_IN_LAUNDRY_POOL)) {
                this->msgEventState++;
            } else {
                ret = true;
                this->stateFlags |= DMGM2_STATE_DRAW_KAFEIS_MASK;
                this->msgEventState++;
                break;
            }
            FALLTHROUGH;
        case 0x1:
            this->stateFlags &= ~(DMGM2_STATE_ENGAGED | DMGM2_STATE_DRAW_KAFEIS_MASK);
            this->stateFlags |= DMGM2_STATE_LOST_ATTENTION;
            DmGm2_ChangeAnim(this, play, DMGM2_ANIM_UMBRELLA_CRY);
            ret = true;
            this->msgEventState++;
            break;

        default:
            break;
    }

    return ret;
}

/*
MsgScript* DmGm2_GetMsgScript(DmGm* this, PlayState* play) {
    Player* player = GET_PLAYER(play);

    switch (this->scheduleResult) {
        case ANJU_SCH_GIVE_LUNCH_TO_GRANNY:
            this->msgScriptCallback = DmGm2_MsgEvent_GiveLunchToGranny;
            return sAnjuMsgScript_SchGiveLunchToGranny;

        case ANJU_SCH_RECEIVE_LETTER_FROM_POSTMAN:
            this->msgScriptCallback = DmGm2_MsgEvent_ReceiveLetterFromPostman;
            return sAnjuMsgScript_SchReceiveLetterFromPostman;

        case ANJU_SCH_ATTEND_GORON:
            this->msgScriptCallback = DmGm2_MsgEvent_AttendGoron;
            return sAnjuMsgScript_SchAttendGoron;

        case ANJU_SCH_COOKING:
            this->msgScriptCallback = DmGm2_MsgEvent_Cooking;
            return sAnjuMsgScript_SchCooking;

        case ANJU_SCH_RANCH:
            return sAnjuMsgScript_SchRanch;

        case ANJU_SCH_WITH_KAFEI:
            return sAnjuMsgScript_SchWithKafei;

        default:
            break;
    }

    if (player->transformation == PLAYER_FORM_DEKU) {
        switch (this->scheduleResult) {
            case ANJU_SCH_WAITING_FOR_KAFEI:
                return sAnjuMsgScript_SchWaitingForKafei;

            case ANJU_SCH_WALKING_40:
            case ANJU_SCH_WALKING_42:
            case ANJU_SCH_WALKING_43:
            case ANJU_SCH_WALKING_44:
            case ANJU_SCH_WALKING_45:
            case ANJU_SCH_WALKING_47:
                return sAnjuMsgScript_80B58B7C;

            case ANJU_SCH_LAUNDRY_POOL_SIT:
                return sAnjuMsgScript_SchLaundryPoolDeku;

            case ANJU_SCH_WALKING_49:
                return sAnjuMsgScript_80B589FC;

            default:
                return sAnjuMsgScript_DekuDefault;
        }
    }

    if (Player_GetMask(play) == PLAYER_MASK_KAFEIS_MASK) {
        if (this->scheduleResult == ANJU_SCH_WALKING_49) {
            return sAnjuMsgScript_80B58B88;
        }

        if (this->scheduleResult == ANJU_SCH_MIDNIGHT_MEETING) {
            this->msgScriptCallback = DmGm2_MsgEvent_MidnightMeeting;
            return sAnjuMsgScript_SchMidnightMeeting;
        }

        if (this->scheduleResult == ANJU_SCH_LAUNDRY_POOL_SIT) {
            this->msgScriptCallback = DmGm2_MsgEvent_LaundryPool;
            return sAnjuMsgScript_SchLaundryPoolKafeiMask;
        }

        if (gSaveContext.save.day >= 2) {
            return sAnjuMsgScript_80B58A44;
        }

        if (SCRIPT_TIME_NOW < SCRIPT_TIME(14, 18)) {
            return sAnjuMsgScript_80B58ABC;
        }

        return sAnjuMsgScript_80B58AC4;
    }

    if ((player->transformation == PLAYER_FORM_HUMAN) && CHECK_WEEKEVENTREG(WEEKEVENTREG_PROMISED_MIDNIGHT_MEETING)) {
        if (this->scheduleResult == ANJU_SCH_MIDNIGHT_MEETING) {
            this->msgScriptCallback = DmGm2_MsgEvent_MidnightMeeting;
            return sAnjuMsgScript_SchMidnightMeeting;
        }

        if (this->scheduleResult == ANJU_SCH_LAUNDRY_POOL_SIT) {
            this->msgScriptCallback = DmGm2_MsgEvent_LaundryPool;
            return sAnjuMsgScript_SchLaundryPoolDefault;
        }

        if (gSaveContext.save.day >= 2) {
            return sAnjuMsgScript_80B58A44;
        }
    }

    switch (this->scheduleResult) {
        case ANJU_SCH_WAITING_FOR_KAFEI:
            return sAnjuMsgScript_SchWaitingForKafei;

        case ANJU_SCH_WALKING_40:
            return sAnjuMsgScript_80B5894C;

        case ANJU_SCH_WALKING_42:
        case ANJU_SCH_WALKING_43:
        case ANJU_SCH_WALKING_44:
        case ANJU_SCH_WALKING_45:
            return sAnjuMsgScript_80B58980;

        case ANJU_SCH_LAUNDRY_POOL_SIT:
            this->msgScriptCallback = DmGm2_MsgEvent_LaundryPool;
            return sAnjuMsgScript_SchLaundryPoolDefault;

        case ANJU_SCH_RECEPTIONIST_IDLE:
            if (gSaveContext.save.day >= 2) {
                return sAnjuMsgScript_Receptionist;
            }
            return sAnjuMsgScript_ReceptionistDay1;

        case ANJU_SCH_WAITING_CLOSING_TIME:
        case ANJU_SCH_WALKING_47:
            return sAnjuMsgScript_InnCloseTime;

        case ANJU_SCH_SWEEPING:
            return sAnjuMsgScript_SchSweeping;

        case ANJU_SCH_MIDNIGHT_MEETING:
            return sAnjuMsgScript_80B589FC;

        case ANJU_SCH_WALKING_48:
            return sAnjuMsgScript_80B58944;

        case ANJU_SCH_WALKING_49:
            if (player->transformation == PLAYER_FORM_HUMAN) {
                return sAnjuMsgScript_80B58B88;
            }
            return sAnjuMsgScript_80B589FC;

        case ANJU_SCH_WALKING_52:
        case ANJU_SCH_WALKING_53:
            return sAnjuMsgScript_80B58994;

        default:
            break;
    }

    return NULL;
} // */

// TODO: consider renaming this (and similar functions of other schedule actors) to `TryTalking`
s32 DmGm2_CheckTalk(DmGm* this, PlayState* play) {
    s32 ret = false;

    if (((this->stateFlags & SUBS_OFFER_MODE_MASK) != SUBS_OFFER_MODE_NONE) &&
        Actor_TalkOfferAccepted(&this->actor, &play->state)) {
        SubS_SetOfferMode(&this->stateFlags, SUBS_OFFER_MODE_NONE, SUBS_OFFER_MODE_MASK);
        this->unk_3C4 = 0;
        this->msgEventState = 0;
        this->msgScriptCallback = NULL;
        this->actor.child = this->lookAtActor;
        //this->msgScript = DmGm2_GetMsgScript(this, play);

        //if ((this->scheduleResult == ANJU_SCH_WAITING_FOR_KAFEI) ||
            //(this->scheduleResult == ANJU_SCH_LAUNDRY_POOL_SIT) ||
            //(this->scheduleResult == ANJU_SCH_RECEPTIONIST_IDLE) ||
            //(this->scheduleResult == ANJU_SCH_WAITING_CLOSING_TIME) ||
            //(this->scheduleResult == ANJU_SCH_MIDNIGHT_MEETING) || (this->scheduleResult == ANJU_SCH_SWEEPING) ||
            //(this->scheduleResult == ANJU_SCH_WALKING_40) || (this->scheduleResult == ANJU_SCH_WALKING_42) ||
            //(this->scheduleResult == ANJU_SCH_WALKING_43) || (this->scheduleResult == ANJU_SCH_WALKING_44) ||
            //(this->scheduleResult == ANJU_SCH_WALKING_45) || (this->scheduleResult == ANJU_SCH_WALKING_47) ||
            //(this->scheduleResult == ANJU_SCH_WALKING_48) || (this->scheduleResult == ANJU_SCH_WALKING_49) ||
            //(this->scheduleResult == ANJU_SCH_WALKING_52) || (this->scheduleResult == ANJU_SCH_WALKING_53)) {
            //this->stateFlags |= DMGM2_STATE_ENGAGED;
        //}

        // TODO re-enable for laundry anju
        //if ((this->scheduleResult == ANJU_SCH_LAUNDRY_POOL_SIT) &&
            //CHECK_WEEKEVENTREG(WEEKEVENTREG_TALKED_ANJU_IN_LAUNDRY_POOL)) {
            //this->stateFlags &= ~DMGM2_STATE_ENGAGED;
        //}

        this->actionFunc = DmGm2_Talk;
        ret = true;
    }

    return ret;
}

// s32 DmGm2_IsCouplesMaskCsPlaying(DmGm* this, PlayState* play) {

void DmGm2_UpdateHeadRot(DmGm* this) {
    Actor* lookAtActor;
    Vec3f lookAtPos;
    Vec3f pos;
    Player* player;

    Math_Vec3f_Copy(&lookAtPos, &this->lookAtActor->world.pos);
    Math_Vec3f_Copy(&pos, &this->actor.world.pos);
    Math_ApproachS(&this->headRotY, Math_Vec3f_Yaw(&pos, &lookAtPos) - this->actor.shape.rot.y, 4, 0x2AA8);

    this->headRotY = CLAMP(this->headRotY, -0x1FFE, 0x1FFE);

    Math_Vec3f_Copy(&pos, &this->actor.focus.pos);

    lookAtActor = this->lookAtActor;
    if (lookAtActor->id == ACTOR_PLAYER) {
        player = (Player*)lookAtActor;

        lookAtPos.y = player->bodyPartsPos[PLAYER_BODYPART_HEAD].y + 3.0f;
    } else {
        Math_Vec3f_Copy(&lookAtPos, &lookAtActor->focus.pos);
    }

    Math_ApproachS(&this->headRotZ, Math_Vec3f_Pitch(&pos, &lookAtPos), 4, 0x2AA8);

    this->headRotZ = CLAMP(this->headRotZ, -0x1554, 0x1554);
}

void DmGm2_UpdateAttention(DmGm* this) {
    if (this->stateFlags & DMGM2_STATE_ENGAGED) {
        if ((this->lookAtActor != NULL) && (this->lookAtActor->update != NULL)) {
            if (DECR(this->loseAttentionTimer) == 0) {
                DmGm2_UpdateHeadRot(this);
                this->stateFlags &= ~DMGM2_STATE_LOST_ATTENTION;
                this->stateFlags |= DMGM2_STATE_FACE_TARGET;
                return;
            }
        }
    }

    if (this->stateFlags & DMGM2_STATE_FACE_TARGET) {
        this->stateFlags &= ~DMGM2_STATE_FACE_TARGET;
        this->headRotZ = 0;
        this->headRotY = 0;
        this->loseAttentionTimer = 20;
        return;
    }

    if (DECR(this->loseAttentionTimer) == 0) {
        this->stateFlags |= DMGM2_STATE_LOST_ATTENTION;
    }
}

s32 DmGm2_ChooseAnimAfterTalking(DmGm* this, PlayState* play) {
    // TODO fix this for new types
    //switch (this->scheduleResult) {
        //case ANJU_SCH_RECEIVE_LETTER_FROM_POSTMAN:
        //case ANJU_SCH_ATTEND_GORON:
        //case ANJU_SCH_RECEPTIONIST_IDLE:
        //case ANJU_SCH_WAITING_CLOSING_TIME:
        //case ANJU_SCH_MIDNIGHT_MEETING:
            //DmGm2_ChangeAnim(this, play, DMGM2_ANIM_IDLE);
            //break;

        //case ANJU_SCH_SWEEPING:
            //DmGm2_ChangeAnim(this, play, DMGM2_ANIM_BROOM_SWEEP);
            //this->stateFlags |= DMGM2_STATE_DRAW_BROOM;
            //break;

        //case ANJU_SCH_COOKING:
            //DmGm2_ChangeAnim(this, play, DMGM2_ANIM_COOK);
            //break;

        //case ANJU_SCH_GIVE_LUNCH_TO_GRANNY:
            //DmGm2_ChangeAnim(this, play, DMGM2_ANIM_WAIT_WITH_TRAY);
            //break;

        //case ANJU_SCH_WALKING_47:
        //case ANJU_SCH_WALKING_49:
            //DmGm2_ChangeAnim(this, play, DMGM2_ANIM_WALK);
            //break;

        //case ANJU_SCH_WALKING_52:
        //case ANJU_SCH_WALKING_53:
            //DmGm2_ChangeAnim(this, play, DMGM2_ANIM_BROOM_WALK);
            //this->stateFlags |= DMGM2_STATE_DRAW_BROOM;
            //break;

        //default:
            //if (this->animIndex == DMGM2_ANIM_WAIT_WITH_TRAY) {
                //DmGm2_ChangeAnim(this, play, DMGM2_ANIM_WALK_WITH_TRAY);
            //}
            //if (this->animIndex == DMGM2_ANIM_UMBRELLA_IDLE) {
                //DmGm2_ChangeAnim(this, play, DMGM2_ANIM_UMBRELLA_WALK);
            //}
            //if ((this->animIndex == DMGM2_ANIM_IDLE) || (this->animIndex == DMGM2_ANIM_IDLE_MORPH)) {
                //DmGm2_ChangeAnim(this, play, DMGM2_ANIM_WALK2);
            //}
            //break;
    //}

    return 0;
}

void DmGm2_DialogueFunc_80B556F8(DmGm* this, PlayState* play) {
    if (this->dialogueFuncState == 0) {
        DmGm2_ChangeAnim(this, play, DMGM2_ANIM_LOOK_UP_RELIEVED);
        this->stateFlags &= ~DMGM2_STATE_ENGAGED;
        this->stateFlags |= DMGM2_STATE_LOST_ATTENTION;
        this->dialogueFuncState++;
    } else if ((this->dialogueFuncState == 1) && Animation_OnFrame(&this->skelAnime, this->skelAnime.endFrame)) {
        DmGm2_ChangeAnim(this, play, DMGM2_ANIM_IDLE_MORPH);
        this->stateFlags &= ~DMGM2_STATE_LOST_ATTENTION;
        this->stateFlags |= DMGM2_STATE_ENGAGED;
        this->dialogueFuncState++;
    }
}

void DmGm2_DialogueFunc_80B557AC(DmGm* this, PlayState* play) {
    if (this->dialogueFuncState == 0) {
        DmGm2_ChangeAnim(this, play, DMGM2_ANIM_BOW);
        this->stateFlags &= ~DMGM2_STATE_ENGAGED;
        this->stateFlags |= DMGM2_STATE_LOST_ATTENTION;
        this->dialogueFuncState++;
    } else if ((this->dialogueFuncState == 1) && Animation_OnFrame(&this->skelAnime, this->skelAnime.endFrame)) {
        DmGm2_ChangeAnim(this, play, DMGM2_ANIM_IDLE_MORPH);
        this->stateFlags &= ~DMGM2_STATE_LOST_ATTENTION;
        this->stateFlags |= DMGM2_STATE_ENGAGED;
        this->dialogueFuncState++;
    }
}

void DmGm2_DialogueFunc_80B55860(DmGm* this, PlayState* play) {
    if (this->dialogueFuncState == 0) {
        DmGm2_ChangeAnim(this, play, DMGM2_ANIM_BOW_MORPH);
        this->stateFlags |= DMGM2_STATE_LOST_ATTENTION;
        this->stateFlags &= ~DMGM2_STATE_ENGAGED;
        this->dialogueFuncState++;
    } else if ((this->dialogueFuncState == 1) && Animation_OnFrame(&this->skelAnime, this->skelAnime.endFrame)) {
        DmGm2_ChangeAnim(this, play, DMGM2_ANIM_IDLE_MORPH);
        this->stateFlags &= ~DMGM2_STATE_LOST_ATTENTION;
        this->stateFlags |= DMGM2_STATE_ENGAGED;
        this->dialogueFuncState++;
    }
}

s32 DmGm2_HandleDialogue(DmGm* this, PlayState* play) {
    Player* player = GET_PLAYER(play);
    u16 textId = play->msgCtx.currentTextId;

    if (player->stateFlags1 & PLAYER_STATE1_TALKING) {
        this->stateFlags |= DMGM2_STATE_TALKING;

        if (this->prevTextId != textId) {
            switch (textId) {
                case 0x28E5: // Ah!
                    DmGm2_ChangeAnim(this, play, DMGM2_ANIM_SURPRISED);
                    this->stateFlags &= ~DMGM2_STATE_DRAW_BROOM;
                    break;

                case 0x28BA: // What's this?
                case 0x28D1: // You are looking for Kafei?
                    DmGm2_ChangeAnim(this, play, DMGM2_ANIM_SURPRISED);
                    break;

                case 0x28AF: // Good night
                case 0x28C1: // I need to hurry and cook for grandmother
                    DmGm2_ChangeAnim(this, play, DMGM2_ANIM_IDLE);
                    break;

                case 0x28BC: // Where did you got that letter?
                    DmGm2_ChangeAnim(this, play, DMGM2_ANIM_IDLE_MORPH);
                    break;

                case 0x28C6: // Don't talk to me or I'll drop this plate
                    DmGm2_ChangeAnim(this, play, DMGM2_ANIM_WAIT_WITH_TRAY);
                    break;

                case 0x28F5: // The town will be crushed by the moon. Forget about the letter
                    DmGm2_ChangeAnim(this, play, DMGM2_ANIM_SIT_MORPH);
                    break;

                case 0x28F7: // Everyone will be taking refuge by tomorrow
                case 0x28F8: // We'll go to Romani Ranch to take refuge
                    DmGm2_ChangeAnim(this, play, DMGM2_ANIM_BROOM_IDLE);
                    break;

                case 0x28EB: // I'm afraid to meet him...
                    if (this->animIndex != DMGM2_ANIM_UMBRELLA_CRY) {
                        this->stateFlags &= ~(DMGM2_STATE_ENGAGED | DMGM2_STATE_DRAW_KAFEIS_MASK);
                        this->stateFlags |= DMGM2_STATE_LOST_ATTENTION;
                        DmGm2_ChangeAnim(this, play, DMGM2_ANIM_UMBRELLA_CRY);
                    }
                    break;

                case 0x28A4: // That's good. We're totally booked right before the carnival
                case 0x28A9: // You do have a reservation?
                case 0x28BE: // From what postbox did you got that letter?!
                case 0x28C0: // Not what I mean!
                case 0x295E: // I need to know!
                    this->dialogueFunc = DmGm2_DialogueFunc_80B556F8;
                    this->dialogueFuncState = 0;
                    break;

                case 0x28E6: // It's from Kafei
                    this->stateFlags &= ~DMGM2_STATE_DRAW_BROOM;
                    this->dialogueFunc = DmGm2_DialogueFunc_80B55860;
                    this->dialogueFuncState = 0;
                    break;

                case 0x1885: // It's 8:30 pm and the Inn is locking the door
                case 0x28A0: // Welcome to the Inn.
                case 0x28A3: // I'm sorry, there are no vacancies. We are always booked at the carnival
                case 0x28A5: // Visit us again in the future
                case 0x28B1: // I'm sorry, there are no vacancies
                case 0x28D2: // I have a clue that will help find Kafei
                case 0x28D9: // Please
                case 0x28DC: // Thank you
                case 0x28DE: // Mail it in the morning
                    this->dialogueFunc = DmGm2_DialogueFunc_80B557AC;
                    this->dialogueFuncState = 0;
                    break;

                case 0x28A1: // Are you staying the night?
                case 0x28A2: // You are staying the night!?
                case 0x28A6: // Are you staying the night? Did I ask you the same earlier?
                case 0x28A7: // Enjoy the carnival
                case 0x28A8: // Did you have a reservation?
                case 0x28AA: // One moment please
                case 0x28AB: // I expected your arrival for afternoon. Your room is on the second floor
                case 0x28AC: // Have you been to the plaza yet? They are putting up the carnival stuff
                case 0x28AD: // Relax...
                case 0x28AE: // doesn't exist
                case 0x28B0: // It's hard to find one's way on the city, goro
                case 0x28B2: // I should have a reservation-goro
                case 0x28B3: // I do have your reservation. Your room is on the second floor
                case 0x28B4: // The place is falling apart-goro
                case 0x28B5: // I made a reservation. I'm [Player]-goro
                case 0x28B6: // [Player]-goro? There's a reservation under a similar name, but it's taken
                case 0x28B7: // Really-goro? I'll just sleep outside then-goro
                case 0x28B8: // I'm sorry
                case 0x28B9: // It's a hard world-goro
                case 0x28BB: // I delivered this to you!
                case 0x28BD: // From the postbox
                case 0x28BF: // From somewhere
                case 0x28C2: // I need to hurry! The afternoon guest will arrive soon
                case 0x28C3: // Used to be a cafeteria
                case 0x28C4:
                case 0x28C5: // Mmm?
                case 0x28C7: // Tortus, I've already had lunch
                case 0x28C8: // I'm Anju! Tortus was my dad...
                case 0x28C9: // I've already had lunch
                case 0x28CA: // Please eat...
                case 0x28CB: // I already ate lunch
                case 0x28CC: // Don't eat my food then
                case 0x28CD: // Phew
                case 0x28CE: // Phew?
                case 0x28CF: // Want me to read a story?
                case 0x28D0: // That mask... You are looking for Kafei
                case 0x28D3: // Come to our kitchen at 11:30
                case 0x28D4: // I'll find him myself
                case 0x28D5: // I wonder where Kafei could have gone
                case 0x28D6: // Nevermind!
                case 0x28D7: // I'm sorry to bother you late at night
                case 0x28D8: // I received a letter from Kafei
                case 0x28DA: // Put my letter in a postbox
                case 0x28DB: // Can I ask this to you?
                case 0x28DD: // oesn't exis
                case 0x28DF: // You won't take refuge?
                case 0x28E0: // Today's weather
                case 0x28E1: // I'll wait for him
                case 0x28E2: // Did you see him? It's too late
                case 0x28E3: // Did you see him? It's too early
                case 0x28E4: // Did you meet him?
                case 0x28E7: // What's that?
                case 0x28E8: // Have you seen a man around here?
                case 0x28E9: // He looks like this
                case 0x28EA: // He disappeared a month ago
                case 0x28EC: // Should I wait?
                case 0x28ED: // You are looking for him too
                case 0x28EE: // I came here to look for him myself
                case 0x28EF: // What a ramshackle inn
                case 0x28F0: // Everything is falling apart
                case 0x28F1: // We are leaving in the evening for the ranch
                case 0x28F2: // I wonder if Kafei is really at Cremia's
                case 0x28F3:
                case 0x28F4: // But he said in the letter he'll come back
                case 0x28F6: // Mother thank you
                default:
                    if (this->animIndex == DMGM2_ANIM_WALK_WITH_TRAY) {
                        DmGm2_ChangeAnim(this, play, DMGM2_ANIM_WAIT_WITH_TRAY);
                    }
                    if (this->animIndex == DMGM2_ANIM_UMBRELLA_WALK) {
                        DmGm2_ChangeAnim(this, play, DMGM2_ANIM_UMBRELLA_IDLE);
                    }
                    if ((this->animIndex == DMGM2_ANIM_BROOM_WALK) || (this->animIndex == DMGM2_ANIM_BROOM_SWEEP)) {
                        DmGm2_ChangeAnim(this, play, DMGM2_ANIM_BROOM_IDLE);
                    }
                    if ((this->animIndex == DMGM2_ANIM_WALK) || (this->animIndex == DMGM2_ANIM_WALK2)) {
                        DmGm2_ChangeAnim(this, play, DMGM2_ANIM_IDLE_MORPH);
                    }
                    break;
            }

            switch (textId) {
                case 0x28F5: // The town will be crushed by the moon. Forget about the letter
                    this->savedFaceIndex = DMGM2_FACE_0;
                    FALLTHROUGH;
                case 0x28A5: // Visit us again in the future
                case 0x28AA: // One moment please
                case 0x28F8: // We'll go to Romani Ranch to take refuge
                    this->faceIndex = DMGM2_FACE_0;
                    this->eyeTimer = 8;
                    break;

                case 0x1885: // It's 8:30 pm and the Inn is locking the door
                case 0x28A0: // Welcome to the Inn.
                case 0x28A6: // Are you staying the night? Did I ask you the same earlier?
                case 0x28AF: // Good night
                case 0x28C1: // I need to hurry and cook for grandmother
                    this->faceIndex = DMGM2_FACE_3;
                    this->eyeTimer = 8;
                    break;

                case 0x28A2: // You are staying the night!?
                case 0x28B3: // I do have your reservation. Your room is on the second floor
                case 0x28B6: // [Player]-goro? There's a reservation under a similar name, but it's taken
                case 0x28BA: // What's this?
                case 0x28BE: // From what postbox did you got that letter?!
                case 0x28CE: // Phew?
                case 0x28D0: // That mask... You are looking for Kafei
                case 0x28D6: // Nevermind!
                case 0x28E5: // Ah!
                case 0x28E7: // What's that?
                case 0x28ED: // You are looking for him too
                    this->faceIndex = DMGM2_FACE_1;
                    this->eyeTimer = 8;
                    break;

                case 0x28AD: // Relax...
                    this->faceIndex = DMGM2_FACE_8;
                    this->eyeTimer = 8;
                    break;

                case 0x28C0: // Not what I mean!
                case 0x28D7: // I'm sorry to bother you late at night
                case 0x28DE: // Mail it in the morning
                    this->faceIndex = DMGM2_FACE_2;
                    this->eyeTimer = 8;
                    break;

                case 0x28E6: // It's from Kafei
                case 0x28F7: // Everyone will be taking refuge by tomorrow
                    this->faceIndex = DMGM2_FACE_6;
                    this->eyeTimer = 8;
                    break;

                case 0x28A3: // I'm sorry, there are no vacancies. We are always booked at the carnival
                case 0x28B1: // I'm sorry, there are no vacancies
                case 0x28B8: // I'm sorry
                case 0x28C6: // Don't talk to me or I'll drop this plate
                case 0x28CA: // Please eat...
                case 0x28CC: // Don't eat my food then
                case 0x28D5: // I wonder where Kafei could have gone
                case 0x28E2: // Did you see him? It's too late
                case 0x28E3: // Did you see him? It's too early
                case 0x28E4: // Did you meet him?
                    this->faceIndex = DMGM2_FACE_4;
                    this->eyeTimer = 8;
                    break;

                case 0x28EC: // Should I wait?
                    this->savedFaceIndex = DMGM2_FACE_5;
                    FALLTHROUGH;
                case 0x28DC: // Thank you
                case 0x28EB: // I'm afraid to meet him...
                case 0x28F2: // I wonder if Kafei is really at Cremia's
                case 0x28F9: // Perhaps I was wrong...
                    this->faceIndex = DMGM2_FACE_5;
                    this->eyeTimer = 8;
                    break;

                case 0x28F6: // Mother thank you
                    this->faceIndex = DMGM2_FACE_9;
                    this->eyeTimer = 8;
                    break;

                case 0x28A4: // That's good. We're totally booked right before the carnival
                case 0x28A9: // You do have a reservation?
                    this->faceIndex = DMGM2_FACE_7;
                    this->eyeTimer = 8;
                    break;

                default:
                    break;
            }
        }

        this->prevTextId = textId;
    } else if (this->stateFlags & DMGM2_STATE_TALKING) {
        // Player stopped talking with Anju

        this->dialogueFunc = NULL;
        this->prevTextId = 0;
        this->stateFlags &= ~DMGM2_STATE_TALKING;
        this->faceIndex = this->savedFaceIndex;
        this->eyeTimer = 4;
        DmGm2_ChooseAnimAfterTalking(this, play);
    }

    if (this->dialogueFunc != NULL) {
        this->dialogueFunc(this, play);
    }

    return 0;
}

Actor* DmGm2_FindLookAtActor(DmGm* this, PlayState* play) {
    Actor* actor;

    switch (this->scheduleResult) {
        case ANJU_SCH_GIVE_LUNCH_TO_GRANNY:
            actor = DmGm2_FindActor(this, play, ACTORCAT_NPC, ACTOR_EN_NB);
            break;

        case ANJU_SCH_RECEIVE_LETTER_FROM_POSTMAN:
            actor = DmGm2_FindActor(this, play, ACTORCAT_NPC, ACTOR_EN_PM);
            break;

        case ANJU_SCH_ATTEND_GORON:
            actor = DmGm2_FindActor(this, play, ACTORCAT_NPC, ACTOR_EN_IG);
            break;

        default:
            actor = &GET_PLAYER(play)->actor;
            break;
    }

    return actor;
}

// Known uses: looks for En_Ig, En_Nb, En_Pm
// this was for talking between EnAn and another actor, skip thats too difficult I think
// s32 func_80B55D98(DmGm* this, PlayState* play, ScheduleOutput* scheduleOutput, u8 actorCategory, s16 actorId) {

s32 DmGm2_IsFacingAndNearPlayer(DmGm* this) {
    s32 ret = false;

    // TODO: why is the range variable?
    if (Actor_IsFacingAndNearPlayer(&this->actor, this->unk_3BC ? 150.0f : 100.0f, 0x2800)) {
        ret = true;
    }

    if (DECR(this->unk_386) == 0) {
        this->unk_3BC ^= 1;
        this->unk_386 = Rand_S16Offset(60, 60); // 3~6 seconds
    }

    return ret;
}

s32 DmGm_Func_80B55F8C(PlayState* play) {
    Player* player = GET_PLAYER(play);
    s32 ret = false;

    if ((Player_GetMask(play) == PLAYER_MASK_KAFEIS_MASK) &&
        CHECK_WEEKEVENTREG(WEEKEVENTREG_PROMISED_MIDNIGHT_MEETING)) {
        ret = true;
    } else if ((player->transformation == PLAYER_FORM_HUMAN) &&
               CHECK_WEEKEVENTREG(WEEKEVENTREG_PROMISED_MIDNIGHT_MEETING)) {
        ret = true;
    }

    return ret;
}

// s32 DmGm2_ProcessSchedule_ReceiveLetterFromPostman(DmGm* this, PlayState* play, ScheduleOutput* scheduleOutput) {

// s32 DmGm2_ProcessSchedule_AttendGoron(DmGm* this, PlayState* play, ScheduleOutput* scheduleOutput) {

// s32 DmGm2_ProcessSchedule_GiveLunchToGranny(DmGm* this, PlayState* play, ScheduleOutput* scheduleOutput) {

// s32 DmGm2_ProcessSchedule_Door(DmGm* this, PlayState* play, ScheduleOutput* scheduleOutput) {

/*
s32 DmGm2_ProcessSchedule_Walking(DmGm* this, PlayState* play, ScheduleOutput* scheduleOutput) {
    u16 now = SCRIPT_TIME_NOW;
    u16 startTime;
    u8 pathIndex = DMGM2_GET_PATH_INDEX(&this->actor);
    s32 ret = false;
    s32 limit;

    this->timePath = NULL;

    limit = sSearchTimePathLimit[scheduleOutput->result];
    if (limit >= 0) {
        this->timePath = SubS_GetAdditionalPath(play, pathIndex, limit);
    }

    if ((this->timePath != NULL) && (this->timePath->count < 3)) {
        this->timePath = NULL;
    }

    if (this->timePath != NULL) {
        if ((this->scheduleResult < ANJU_SCH_WALKING_40) && (this->scheduleResult != ANJU_SCH_NONE) &&
            (this->timePathTimeSpeed >= 0)) {
            startTime = now;
        } else {
            startTime = scheduleOutput->time0;
        }

        if (scheduleOutput->time1 < startTime) {
            this->timePathTotalTime = (startTime - scheduleOutput->time1) + 0xFFFF;
        } else {
            this->timePathTotalTime = scheduleOutput->time1 - startTime;
        }

        this->timePathElapsedTime = now - startTime;
        startTime = (this->timePath->count - 2);
        this->timePathWaypointTime = this->timePathTotalTime / startTime;

        this->timePathWaypoint = (this->timePathElapsedTime / this->timePathWaypointTime) + 2;
        this->stateFlags &= ~DMGM2_STATE_8;
        this->stateFlags &= ~DMGM2_STATE_REACHED_PATH_END;

        switch (scheduleOutput->result) {
            case ANJU_SCH_WALKING_44:
            case ANJU_SCH_WALKING_45:
            case ANJU_SCH_WALKING_50:
            case ANJU_SCH_WALKING_51:
            case ANJU_SCH_WALKING_54:
            case ANJU_SCH_WALKING_55:
            case ANJU_SCH_WALKING_56:
            case ANJU_SCH_WALKING_57:
            case ANJU_SCH_WALKING_58:
            case ANJU_SCH_WALKING_59:
            case ANJU_SCH_WALKING_60:
            case ANJU_SCH_WALKING_61:
            case ANJU_SCH_WALKING_62:
            case ANJU_SCH_WALKING_63:
                this->savedFaceIndex = DMGM2_FACE_2;
                this->faceIndex = DMGM2_FACE_2;
                this->eyeTimer = 8;
                break;

            default:
                break;
        }

        switch (scheduleOutput->result) {
            case ANJU_SCH_WALKING_42:
            case ANJU_SCH_WALKING_43:
                SubS_SetOfferMode(&this->stateFlags, SUBS_OFFER_MODE_ONSCREEN, SUBS_OFFER_MODE_MASK);
                FALLTHROUGH;
            case ANJU_SCH_WALKING_44:
            case ANJU_SCH_WALKING_45:
                DmGm2_ChangeAnim(this, play, DMGM2_ANIM_WALK_WITH_TRAY);
                this->stateFlags |= DMGM2_STATE_UPDATE_EYES | DMGM2_STATE_LOST_ATTENTION;
                this->stateFlags |= DMGM2_STATE_DRAW_TRAY;
                break;

            case ANJU_SCH_WALKING_52:
            case ANJU_SCH_WALKING_53:
                DmGm2_ChangeAnim(this, play, DMGM2_ANIM_BROOM_WALK);
                SubS_SetOfferMode(&this->stateFlags, SUBS_OFFER_MODE_ONSCREEN, SUBS_OFFER_MODE_MASK);
                this->stateFlags |= DMGM2_STATE_UPDATE_EYES | DMGM2_STATE_LOST_ATTENTION;
                this->stateFlags |= DMGM2_STATE_DRAW_BROOM;
                break;

            case ANJU_SCH_WALKING_50:
            case ANJU_SCH_WALKING_51:
                DmGm2_ChangeAnim(this, play, DMGM2_ANIM_WALK);
                this->stateFlags |= DMGM2_STATE_UPDATE_EYES | DMGM2_STATE_LOST_ATTENTION;
                break;

            case ANJU_SCH_WALKING_54:
            case ANJU_SCH_WALKING_55:
            case ANJU_SCH_WALKING_56:
            case ANJU_SCH_WALKING_57:
            case ANJU_SCH_WALKING_58:
            case ANJU_SCH_WALKING_59:
            case ANJU_SCH_WALKING_60:
            case ANJU_SCH_WALKING_61:
            case ANJU_SCH_WALKING_62:
            case ANJU_SCH_WALKING_63:
                DmGm2_ChangeAnim(this, play, DMGM2_ANIM_UMBRELLA_WALK);
                this->stateFlags |= DMGM2_STATE_UPDATE_EYES | DMGM2_STATE_LOST_ATTENTION;
                this->stateFlags |= DMGM2_STATE_DRAW_UMBRELLA;
                break;

            case ANJU_SCH_WALKING_40:
            case ANJU_SCH_WALKING_47:
            case ANJU_SCH_WALKING_48:
            case ANJU_SCH_WALKING_49:
                SubS_SetOfferMode(&this->stateFlags, SUBS_OFFER_MODE_ONSCREEN, SUBS_OFFER_MODE_MASK);
                this->stateFlags |= DMGM2_STATE_UPDATE_EYES | DMGM2_STATE_LOST_ATTENTION;
                FALLTHROUGH;
            default:
                DmGm2_ChangeAnim(this, play, DMGM2_ANIM_WALK);
                break;
        }

        ret = true;
        this->actor.gravity = -1.0f;
    }

    return ret;
} // */

s32 DmGm2_ProcessSchedule_Sweeping(DmGm* this, PlayState* play, ScheduleOutput* scheduleOutput) {
    u8 pathIndex = DMGM2_GET_PATH_INDEX(&this->actor);
    Vec3f firstPos;
    Vec3f secondPos;
    Vec3s* points;
    s32 limit;
    s32 ret = false;

    //this->timePath = NULL;

    //limit = sSearchTimePathLimit[scheduleOutput->result];
    //if (limit >= 0) {
        //this->timePath = SubS_GetAdditionalPath(play, pathIndex, limit);
    //}

    //if ((this->timePath != NULL) && (this->timePath->count >= 2)) {
        //points = Lib_SegmentedToVirtual(this->timePath->points);
        //Math_Vec3s_ToVec3f(&firstPos, &points[0]);
        //Math_Vec3s_ToVec3f(&secondPos, &points[1]);

        this->actor.world.rot.y = Math_Vec3f_Yaw(&firstPos, &secondPos);
        Math_Vec3s_Copy(&this->actor.shape.rot, &this->actor.world.rot);
        Math_Vec3f_Copy(&this->actor.world.pos, &firstPos);
        Math_Vec3f_Copy(&this->actor.prevPos, &firstPos);

        if (scheduleOutput->result == ANJU_SCH_SWEEPING) {
            DmGm2_ChangeAnim(this, play, DMGM2_ANIM_BROOM_SWEEP);
            SubS_SetOfferMode(&this->stateFlags, SUBS_OFFER_MODE_ONSCREEN, SUBS_OFFER_MODE_MASK);

            this->stateFlags |= DMGM2_STATE_UPDATE_EYES | DMGM2_STATE_LOST_ATTENTION;
            this->stateFlags |= DMGM2_STATE_DRAW_BROOM;
        }

        ret = true;
    //}

    return ret;
}

// midnight meeting I think
// s32 DmGm2_ProcessSchedule_80B56880(DmGm* this, PlayState* play, ScheduleOutput* scheduleOutput) {

// do we want the depressive thing?
s32 DmGm2_ProcessSchedule_Ranch(DmGm* this, PlayState* play, ScheduleOutput* scheduleOutput) {
    static Vec3f D_80B58E7C = { 905.0f, 260.0f, -64.0f };
    static Vec3s D_80B58E88 = { 0, 0, 0 };

    Math_Vec3f_Copy(&this->actor.world.pos, &D_80B58E7C);
    Math_Vec3s_Copy(&this->actor.shape.rot, &D_80B58E88);
    Math_Vec3s_Copy(&this->actor.world.rot, &this->actor.shape.rot);

    if (scheduleOutput->result == ANJU_SCH_RANCH) {
        DmGm2_ChangeAnim(this, play, DMGM2_ANIM_SITTING_IN_DISBELIEF);
        SubS_SetOfferMode(&this->stateFlags, SUBS_OFFER_MODE_ONSCREEN, SUBS_OFFER_MODE_MASK);

        this->stateFlags |= DMGM2_STATE_UPDATE_EYES | DMGM2_STATE_LOST_ATTENTION;
        this->stateFlags |= DMGM2_STATE_IGNORE_GRAVITY;

        this->savedFaceIndex = DMGM2_FACE_5;
        this->faceIndex = DMGM2_FACE_5;
        this->eyeTimer = 8;
    }

    return true;
}

//s32 DmGm2_ProcessSchedule_StaffRoom(DmGm* this, PlayState* play, ScheduleOutput* scheduleOutput) {

//s32 DmGm2_ProcessSchedule_WithKafei(DmGm* this, PlayState* play, ScheduleOutput* scheduleOutput) {

/*
s32 DmGm2_ProcessScheduleOutput(DmGm* this, PlayState* play, ScheduleOutput* scheduleOutput) {
    s32 ret;

    this->actor.flags |= ACTOR_FLAG_ATTENTION_ENABLED;
    this->actor.attentionRangeType = ATTENTION_RANGE_6;
    this->stateFlags = 0;
    this->savedFaceIndex = DMGM2_FACE_0;
    this->faceIndex = DMGM2_FACE_0;
    this->eyeTimer = 8;
    this->offerRange = 40.0f;

    switch (scheduleOutput->result) {
        case ANJU_SCH_RECEIVE_LETTER_FROM_POSTMAN:
            ret = DmGm2_ProcessSchedule_ReceiveLetterFromPostman(this, play, scheduleOutput);
            break;

        case ANJU_SCH_ATTEND_GORON:
            ret = DmGm2_ProcessSchedule_AttendGoron(this, play, scheduleOutput);
            break;

        case ANJU_SCH_GIVE_LUNCH_TO_GRANNY:
            ret = DmGm2_ProcessSchedule_GiveLunchToGranny(this, play, scheduleOutput);
            break;

        case ANJU_SCH_RANCH:
            ret = DmGm2_ProcessSchedule_Ranch(this, play, scheduleOutput);
            break;

        case ANJU_SCH_WAITING_FOR_KAFEI:
        case ANJU_SCH_TALKING_WITH_MOM:
            ret = DmGm2_ProcessSchedule_StaffRoom(this, play, scheduleOutput);
            break;

        case ANJU_SCH_LAUNDRY_POOL_SIT:
        case ANJU_SCH_COOKING:
        case ANJU_SCH_RECEPTIONIST_IDLE:
        case ANJU_SCH_WAITING_CLOSING_TIME:
        case ANJU_SCH_MIDNIGHT_MEETING:
            ret = DmGm2_ProcessSchedule_80B56880(this, play, scheduleOutput);
            break;

        case ANJU_SCH_SWEEPING:
            ret = DmGm2_ProcessSchedule_Sweeping(this, play, scheduleOutput);
            break;

        case ANJU_SCH_WITH_KAFEI:
            ret = DmGm2_ProcessSchedule_WithKafei(this, play, scheduleOutput);
            break;

        //case ANJU_SCH_DOOR_26:
        //case ANJU_SCH_DOOR_27:
        //case ANJU_SCH_DOOR_28:
        //case ANJU_SCH_DOOR_29:
        //case ANJU_SCH_DOOR_30:
        //case ANJU_SCH_DOOR_31:
        //case ANJU_SCH_DOOR_32:
        //case ANJU_SCH_DOOR_33:
        //case ANJU_SCH_DOOR_34:
        //case ANJU_SCH_DOOR_35:
        //case ANJU_SCH_DOOR_36:
        //case ANJU_SCH_DOOR_37:
        //case ANJU_SCH_DOOR_38:
        //case ANJU_SCH_DOOR_39:
            //ret = DmGm2_ProcessSchedule_Door(this, play, scheduleOutput);
            //break;

        case ANJU_SCH_WALKING_40:
        case ANJU_SCH_WALKING_42:
        case ANJU_SCH_WALKING_43:
        case ANJU_SCH_WALKING_44:
        case ANJU_SCH_WALKING_45:
        case ANJU_SCH_WALKING_46:
        case ANJU_SCH_WALKING_47:
        case ANJU_SCH_WALKING_48:
        case ANJU_SCH_WALKING_49:
        case ANJU_SCH_WALKING_50:
        case ANJU_SCH_WALKING_51:
        case ANJU_SCH_WALKING_52:
        case ANJU_SCH_WALKING_53:
        case ANJU_SCH_WALKING_54:
        case ANJU_SCH_WALKING_55:
        case ANJU_SCH_WALKING_56:
        case ANJU_SCH_WALKING_57:
        case ANJU_SCH_WALKING_58:
        case ANJU_SCH_WALKING_59:
        case ANJU_SCH_WALKING_60:
        case ANJU_SCH_WALKING_61:
        case ANJU_SCH_WALKING_62:
        case ANJU_SCH_WALKING_63:
            ret = DmGm2_ProcessSchedule_Walking(this, play, scheduleOutput);
            break;

        default:
            ret = false;
            break;
    }

    return ret;
} // */

/* Start of HandleShedule functions */

// RotateTowardsLookAtActor?
/*
s32 DmGm2_HandleSch_InteractActor(DmGm* this, PlayState* play) {
    Vec3f lookAtActorPos;
    Vec3f pos;

    if ((this->lookAtActor != NULL) && (this->lookAtActor->update != NULL)) {
        Math_Vec3f_Copy(&lookAtActorPos, &this->lookAtActor->world.pos);
        Math_Vec3f_Copy(&pos, &this->actor.world.pos);
        this->actor.world.rot.y = Math_Vec3f_Yaw(&pos, &lookAtActorPos);
    }

    return true;
} // */

//s32 DmGm2_HandleSch_Door(DmGm* this, PlayState* play) {

//s32 DmGm2_HandleSch_FollowTimePath(DmGm* this, PlayState* play) {

/*
s32 DmGm2_HandleSch_80B572D4(DmGm* this, PlayState* play) {
    switch (this->scheduleResult) {
        case ANJU_SCH_MIDNIGHT_MEETING:
            if (DmGm_Func_80B55F8C(play) && DmGm2_IsFacingAndNearPlayer(this)) {
                this->stateFlags |= DMGM2_STATE_ENGAGED;
            } else {
                this->stateFlags &= ~DMGM2_STATE_ENGAGED;
            }
            break;

        case ANJU_SCH_WAITING_FOR_KAFEI:
            if (DmGm2_IsFacingAndNearPlayer(this)) {
                this->stateFlags |= DMGM2_STATE_ENGAGED;
            } else {
                this->stateFlags &= ~DMGM2_STATE_ENGAGED;
            }
            break;

        case ANJU_SCH_RECEPTIONIST_IDLE:
        case ANJU_SCH_WAITING_CLOSING_TIME:
            if (DmGm2_IsFacingAndNearPlayer(this)) {
                this->stateFlags |= DMGM2_STATE_ENGAGED;
            } else {
                this->stateFlags &= ~DMGM2_STATE_ENGAGED;
            }
            break;

        case ANJU_SCH_SWEEPING:
            if (Animation_OnFrame(&this->skelAnime, 6.0f) && (this->animIndex == DMGM2_ANIM_BROOM_SWEEP)) {
                Actor_PlaySfx(&this->actor, NA_SE_EV_SWEEP);
            }
            break;

        default:
            break;
    }

    return 0;
} // */

/*
s32 DmGm2_HandleSch_LaundryPool(DmGm* this, PlayState* play) {
    s16 worldRot;
    s16 shapeRot;

    switch (this->schState.laundryPoolState) {
        case 0x0:
            this->actor.world.rot.y += 0x7FF8;
            this->schState.laundryPoolState++;
            break;

        case 0x1:
            worldRot = (this->actor.world.rot.y / 0xB6) * 0xB6;
            shapeRot = (this->actor.shape.rot.y / 0xB6) * 0xB6;
            if (worldRot == shapeRot) {
                Math_Vec3s_Copy(&this->actor.shape.rot, &this->actor.world.rot);
                DmGm2_ChangeAnim(this, play, DMGM2_ANIM_UMBRELLA_SIT);
                this->stateFlags |= DMGM2_STATE_IGNORE_GRAVITY;
                this->schState.laundryPoolState++;
            }
            break;

        case 0x2:
            if (Animation_OnFrame(&this->skelAnime, this->skelAnime.endFrame)) {
                this->schState.laundryPoolState++;
            }
            break;

        case 0x3:
            if (ABS_ALT(BINANG_SUB(this->actor.yawTowardsPlayer, this->actor.shape.rot.y)) < 0x3000) {
                SubS_SetOfferMode(&this->stateFlags, SUBS_OFFER_MODE_ONSCREEN, SUBS_OFFER_MODE_MASK);
            } else {
                SubS_SetOfferMode(&this->stateFlags, SUBS_OFFER_MODE_NONE, SUBS_OFFER_MODE_MASK);
            }
            break;

        case 0x4:
            SubS_SetOfferMode(&this->stateFlags, SUBS_OFFER_MODE_ONSCREEN, SUBS_OFFER_MODE_MASK);
            this->schState.laundryPoolState++;
            break;

        default:
            break;
    }

    return 0;
} // */

//s32 DmGm2_HandleSch_WaitingForKafei(DmGm* this, PlayState* play) {

//s32 DmGm2_HandleSch_WithKafei(DmGm* this, PlayState* play) {

/* End of HandleShedule functions */

/*
void DmGm2_HandleSchedule(DmGm* this, PlayState* play) {
    switch (this->scheduleResult) {
        case ANJU_SCH_RECEIVE_LETTER_FROM_POSTMAN:
        case ANJU_SCH_ATTEND_GORON:
        case ANJU_SCH_GIVE_LUNCH_TO_GRANNY:
            DmGm2_HandleSch_InteractActor(this, play);
            break;

        case ANJU_SCH_LAUNDRY_POOL_SIT:
            DmGm2_HandleSch_LaundryPool(this, play);
            break;

        //case ANJU_SCH_WAITING_FOR_KAFEI:
            //DmGm2_HandleSch_WaitingForKafei(this, play);
            //break;

        case ANJU_SCH_WITH_KAFEI:
            DmGm2_HandleSch_WithKafei(this, play);
            break;

        case ANJU_SCH_RANCH:
        case ANJU_SCH_COOKING:
        case ANJU_SCH_RECEPTIONIST_IDLE:
        case ANJU_SCH_WAITING_CLOSING_TIME:
        case ANJU_SCH_SWEEPING:
        case ANJU_SCH_TALKING_WITH_MOM:
            DmGm2_HandleSch_80B572D4(this, play);
            break;

        case ANJU_SCH_MIDNIGHT_MEETING:
            DmGm2_HandleSch_80B572D4(this, play);
            break;

        case ANJU_SCH_DOOR_26:
        case ANJU_SCH_DOOR_27:
        case ANJU_SCH_DOOR_28:
        case ANJU_SCH_DOOR_29:
        case ANJU_SCH_DOOR_30:
        case ANJU_SCH_DOOR_31:
        case ANJU_SCH_DOOR_32:
        case ANJU_SCH_DOOR_33:
        case ANJU_SCH_DOOR_34:
        case ANJU_SCH_DOOR_35:
        case ANJU_SCH_DOOR_36:
        case ANJU_SCH_DOOR_37:
        case ANJU_SCH_DOOR_38:
        case ANJU_SCH_DOOR_39:
            DmGm2_HandleSch_Door(this, play);
            break;

        case ANJU_SCH_WALKING_40:
        case ANJU_SCH_WALKING_42:
        case ANJU_SCH_WALKING_43:
        case ANJU_SCH_WALKING_44:
        case ANJU_SCH_WALKING_45:
        case ANJU_SCH_WALKING_46:
        case ANJU_SCH_WALKING_47:
        case ANJU_SCH_WALKING_48:
        case ANJU_SCH_WALKING_49:
        case ANJU_SCH_WALKING_50:
        case ANJU_SCH_WALKING_51:
        case ANJU_SCH_WALKING_52:
        case ANJU_SCH_WALKING_53:
        case ANJU_SCH_WALKING_54:
        case ANJU_SCH_WALKING_55:
        case ANJU_SCH_WALKING_56:
        case ANJU_SCH_WALKING_57:
        case ANJU_SCH_WALKING_58:
        case ANJU_SCH_WALKING_59:
        case ANJU_SCH_WALKING_60:
        case ANJU_SCH_WALKING_61:
        case ANJU_SCH_WALKING_62:
        case ANJU_SCH_WALKING_63:
            DmGm2_HandleSch_FollowTimePath(this, play);
            break;

        default:
            break;
    }

    Math_ApproachS(&this->actor.shape.rot.y, this->actor.world.rot.y, 3, 0x2AA8);
} // */


/*
void DmGm2_FollowSchedule(DmGm* this, PlayState* play) {
    ScheduleOutput scheduleOutput;

    this->timePathTimeSpeed = R_TIME_SPEED + ((void)0, gSaveContext.save.timeSpeedOffset);

    if (!DMGM2_GET_8000(&this->actor) && !this->unk_3C0 &&
        CHECK_WEEKEVENTREG(WEEKEVENTREG_COUPLES_MASK_CUTSCENE_FINISHED)) {
        Actor_Kill(&this->actor);
        return;
    }

    if (this->unk_3C0) {
        scheduleOutput.result = ANJU_SCH_WITH_KAFEI;
        if (this->scheduleResult != ANJU_SCH_WITH_KAFEI) {
            DmGm2_ProcessScheduleOutput(this, play, &scheduleOutput);
        }
    } else if (!Schedule_RunScript(play, sScheduleScript, &scheduleOutput) ||
               ((this->scheduleResult != scheduleOutput.result) &&
                !DmGm2_ProcessScheduleOutput(this, play, &scheduleOutput))) {
        this->actor.shape.shadowDraw = NULL;
        this->actor.flags &= ~ACTOR_FLAG_ATTENTION_ENABLED;
        scheduleOutput.result = ANJU_SCH_NONE;
    } else {
        this->actor.shape.shadowDraw = ActorShadow_DrawCircle;
        this->actor.flags |= ACTOR_FLAG_ATTENTION_ENABLED;
    }

    this->scheduleResult = scheduleOutput.result;
    this->lookAtActor = DmGm2_FindLookAtActor(this, play);
    DmGm2_HandleSchedule(this, play);
} // */

void DmGm2_Talk(DmGm* this, PlayState* play) {
    if (MsgEvent_RunScript(&this->actor, play, this->msgScript, this->msgScriptCallback, &this->msgScriptPos)) {
        // Message event script is done

        SubS_SetOfferMode(&this->stateFlags, SUBS_OFFER_MODE_ONSCREEN, SUBS_OFFER_MODE_MASK);

        this->stateFlags &= ~DMGM2_STATE_ENGAGED;
        this->stateFlags |= DMGM2_STATE_LOST_ATTENTION;
        this->loseAttentionTimer = 20;
        this->msgScriptPos = 0;
        //this->actionFunc = DmGm2_FollowSchedule;

        return;
    }

    if ((this->scheduleResult == ANJU_SCH_WAITING_FOR_KAFEI) || (this->scheduleResult == ANJU_SCH_LAUNDRY_POOL_SIT) ||
        (this->scheduleResult == ANJU_SCH_RANCH) || (this->scheduleResult == ANJU_SCH_COOKING) ||
        (this->scheduleResult == ANJU_SCH_WITH_KAFEI)) {
        return;
    }

    if ((this->lookAtActor != NULL) && (this->lookAtActor->update != NULL)) {
        // Rotate towards actor
        s16 yaw;
        Vec3f lookAtPos;
        Vec3f pos;

        Math_Vec3f_Copy(&lookAtPos, &this->lookAtActor->world.pos);
        Math_Vec3f_Copy(&pos, &this->actor.world.pos);
        yaw = Math_Vec3f_Yaw(&pos, &lookAtPos);

        Math_ApproachS(&this->actor.shape.rot.y, yaw, 4, 0x2AA8);
    }
}

//void DmGm2_HandleCouplesMaskCutscene(DmGm* this, PlayState* play) {

void DmGm2_Init(Actor* thisx, PlayState* play) {
    DmGm* this = (DmGm*)thisx;
    //s32 temp_v1;
    //s32 watchedCouplesMaskCs;

    
    //if (play->sceneId != SCENE_YADOYA) {
        //this->actor.params &= (s16)~DMGM2_8000;
    //}

    //temp_v1 = DMGM2_GET_8000(&this->actor) >> 0xF;
    //watchedCouplesMaskCs = CHECK_WEEKEVENTREG(WEEKEVENTREG_COUPLES_MASK_CUTSCENE_FINISHED);

    //if ((!watchedCouplesMaskCs && (temp_v1 == 1)) || (watchedCouplesMaskCs && (temp_v1 == 0))) {
        //Actor_Kill(&this->actor);
        //return;
    //}

    // Check if there's an Anju actor with the DMGM2_8000 flag, if there's one then give priority to that Anju and Kill
    // all the others
    //if (temp_v1 == 0) {
        //if (DmGm_Func_80B53A7C(this, play, ACTORCAT_NPC, ACTOR_EN_AN) != NULL) {
            //Actor_Kill(&this->actor);
            //return;
        //}
    //}

    //this->roomNum = -0x80;
    //this->slotsInitialized = false;
    //if (temp_v1 == 0) {
        //this->actor.room = -1;
    //}

    this->actionFunc = DmGm2_FinishInit;
}


void DmGm2_FinishInit(DmGm* this, PlayState* play) {
    ActorShape_Init(&this->actor.shape, 0.0f, NULL, 14.0f);
    SkelAnime_InitFlex(play, &this->skelAnime, &gAnju1Skel, NULL, this->jointTable, this->morphTable, ANJU1_LIMB_MAX);

    this->animIndex = DMGM2_ANIM_NONE;
    DmGm2_ChangeAnim(this, play, DMGM2_ANIM_IDLE);
    Collider_InitAndSetCylinder(play, &this->collider, &this->actor, &sCylinderInit);
    CollisionCheck_SetInfo2(&this->actor.colChkInfo, DamageTable_Get(0x16), &sColChkInfoInit);

    if (DMGM2_GET_8000(&this->actor)) {
        this->unk_3C0 = true;
    }

    this->actor.draw = DmGm2_Draw;
    Actor_SetScale(&this->actor, 0.01f);
    this->stateFlags = 0;
    this->scheduleResult = ANJU_SCH_NONE;

    //this->actionFunc = DmGm2_FollowSchedule;
    this->actionFunc(this, play);
}

void DmGm2_Destroy(Actor* thisx, PlayState* play) {
    DmGm* this = (DmGm*)thisx;

    Collider_DestroyCylinder(play, &this->collider);
}

void DmGm2_Update(Actor* thisx, PlayState* play) {
    DmGm* this = (DmGm*)thisx;

    //if (DmGm2_InitObjectSlots(this, play)) {
        //return;
    //}

    if ((this->actionFunc != DmGm2_FinishInit) && !DmGm2_CheckTalk(this, play) ){
        //DmGm2_IsCouplesMaskCsPlaying(this, play)) {
        //DmGm2_HandleCouplesMaskCutscene(this, play);
        DmGm2_UpdateSkelAnime(this, play);
        DmGm2_UpdateFace(this);
        return;
    } // */

    this->actionFunc(this, play);
    //if (this->scheduleResult != ANJU_SCH_NONE) {
        DmGm2_HandleDialogue(this, play);
        DmGm2_UpdateSkelAnime(this, play);
        DmGm2_UpdateFace(this);
        DmGm2_UpdateAttention(this);
        SubS_Offer(&this->actor, play, this->offerRange, 30.0f, 0, this->stateFlags & SUBS_OFFER_MODE_MASK);

        if (!(this->stateFlags & DMGM2_STATE_IGNORE_GRAVITY)) {
            Actor_MoveWithGravity(&this->actor);
            Actor_UpdateBgCheckInfo(play, &this->actor, 30.0f, 12.0f, 0.0f, UPDBGCHECKINFO_FLAG_4);
        }

        DmGm2_UpdateCollider(this, play);
    //}
}

void DmGm2_PostLimbDraw(PlayState* play, s32 limbIndex, Gfx** dList, Vec3s* rot, Actor* thisx) {
    DmGm* this = (DmGm*)thisx;

    if (limbIndex == ANJU1_LIMB_HEAD) {
        static Vec3f D_80B58ED4 = { 1000.0f, 0.0f, 0.0f };

        Matrix_MultVec3f(&D_80B58ED4, &this->actor.focus.pos);
        Math_Vec3s_Copy(&this->actor.focus.rot, &this->actor.world.rot);
        DmGm2_DrawAccessory(this, play, DMGM2_ACCESSORY_KAFEI_MASK);
    } else if (limbIndex == ANJU1_LIMB_RIGHT_HAND) {
        DmGm2_DrawAccessory(this, play, DMGM2_ACCESSORY_FOOD_TRAY);
        DmGm2_DrawAccessory(this, play, DMGM2_ACCESSORY_CHOPSTICKS);
        DmGm2_DrawAccessory(this, play, DMGM2_ACCESSORY_UMBRELLA);
        DmGm2_DrawAccessory(this, play, DMGM2_ACCESSORY_BROOM);
    } else if (limbIndex == ANJU1_LIMB_LEFT_HAND) {
        DmGm2_DrawAccessory(this, play, DMGM2_ACCESSORY_MOON_MASK);
    }
}

void DmGm2_TransformLimbDraw(PlayState* play, s32 limbIndex, Actor* thisx) {
    DmGm* this = (DmGm*)thisx;
    s32 stepRot;
    s32 overrideRot;

    if (!(this->stateFlags & DMGM2_STATE_LOST_ATTENTION)) {
        if (this->stateFlags & DMGM2_STATE_FACE_TARGET) {
            overrideRot = true;
        } else {
            overrideRot = false;
        }
        stepRot = true;
    } else {
        overrideRot = false;
        stepRot = false;
    }

    if (limbIndex == ANJU1_LIMB_HEAD) {
        SubS_UpdateLimb(this->headRotZ + 0x4000, this->headRotY + this->actor.shape.rot.y + 0x4000,
                        &this->headComputedPos, &this->headComputedRot, stepRot, overrideRot);
        Matrix_Pop();
        Matrix_Translate(this->headComputedPos.x, this->headComputedPos.y, this->headComputedPos.z, MTXMODE_NEW);
        Matrix_Scale(this->actor.scale.x, this->actor.scale.y, this->actor.scale.z, MTXMODE_APPLY);
        Matrix_RotateYS(this->headComputedRot.y, MTXMODE_APPLY);
        Matrix_RotateXS(this->headComputedRot.x, MTXMODE_APPLY);
        Matrix_RotateZS(this->headComputedRot.z, MTXMODE_APPLY);
        Matrix_Push();
    }
}

void DmGm2_Draw(Actor* thisx, PlayState* play) {
    DmGm* this = (DmGm*)thisx;

    if ((this->scheduleResult != ANJU_SCH_NONE) || this->forceDraw) {
        static TexturePtr sMouthTextures[DMGM2_MOUTH_MAX] = {
            gAnju1MouthClosedTex, // DMGM2_MOUTH_CLOSED
            gAnju1MouthHappyTex,  // DMGM2_MOUTH_HAPPY
            gAnju1MouthOpenTex,   // DMGM2_MOUTH_OPEN
        };
        static TexturePtr sEyeTextures[DMGM2_EYES_MAX] = {
            gAnju1EyeOpenTex,           // DMGM2_EYES_OPEN
            gAnju1EyeHalfTex,           // DMGM2_EYES_HALF1
            gAnju1EyeClosedTex,         // DMGM2_EYES_CLOSED
            gAnju1EyeHalfTex,           // DMGM2_EYES_HALF2
            gAnju1EyeComfortTex,        // DMGM2_EYES_COMFORT
            gAnju1EyeSadTex,            // DMGM2_EYES_SAD
            gAnju1EyeRelievedClosedTex, // DMGM2_EYES_RELIEVED_CLOSED
        };

        OPEN_DISPS(play->state.gfxCtx);

        Gfx_SetupDL25_Opa(play->state.gfxCtx);

        gSPSegment(POLY_OPA_DISP++, 0x08, Lib_SegmentedToVirtual(sEyeTextures[this->eyeTexIndex]));
        gSPSegment(POLY_OPA_DISP++, 0x09, Lib_SegmentedToVirtual(sMouthTextures[this->mouthTexIndex]));

        SkelAnime_DrawTransformFlexOpa(play, this->skelAnime.skeleton, this->skelAnime.jointTable,
                                       this->skelAnime.dListCount, NULL, DmGm2_PostLimbDraw, DmGm2_TransformLimbDraw,
                                       &this->actor);

        CLOSE_DISPS(play->state.gfxCtx);
    }
}
