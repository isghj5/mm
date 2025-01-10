/*
 * File: z_en_kaizoku.c
 * Overlay: ovl_En_Kaizoku
 * Description: Fighter pirate
 */

#include "z_en_kaizoku.h"
#include "overlays/actors/ovl_En_Clear_Tag/z_en_clear_tag.h"
#include "overlays/actors/ovl_En_Arrow/z_en_arrow.h"

#define FLAGS (ACTOR_FLAG_TARGETABLE | ACTOR_FLAG_UNFRIENDLY | ACTOR_FLAG_10 | ACTOR_FLAG_100000)

#define THIS ((EnKaizoku*)thisx)

void EnKaizoku_Init(Actor* thisx, PlayState* play);
void EnKaizoku_Destroy(Actor* thisx, PlayState* play);
void EnKaizoku_Update(Actor* thisx, PlayState* play2);
void EnKaizoku_Draw(Actor* thisx, PlayState* play);

s32 EnKaizoku_ValidatePictograph(PlayState* play, Actor* actor);
void EnKaizoku_SetupWaitForApproach(EnKaizoku* this);
void EnKaizoku_WaitForApproach(EnKaizoku* this, PlayState* play);
void EnKaizoku_Loss(EnKaizoku* this, PlayState* play);
void EnKaizoku_SetupWin(EnKaizoku* this);
void EnKaizoku_Win(EnKaizoku* this, PlayState* play);
void func_80B872A4(EnKaizoku* this);
void func_80B872F4(EnKaizoku* this, PlayState* play);
void func_80B874D8(EnKaizoku* this, PlayState* play);
void func_80B8760C(EnKaizoku* this, PlayState* play);
void func_80B87900(EnKaizoku* this);
void func_80B8798C(EnKaizoku* this, PlayState* play);
void func_80B87C7C(EnKaizoku* this);
void EnKaizoku_SpawnFootDust(PlayState* play, Vec3f* pos);
void func_80B87D3C(EnKaizoku* this, PlayState* play);
void func_80B87E28(EnKaizoku* this);
void func_80B87E9C(EnKaizoku* this, PlayState* play);
void func_80B87F70(EnKaizoku* this);
void func_80B87FDC(EnKaizoku* this, PlayState* play2);
void func_80B88214(EnKaizoku* this);
void func_80B88278(EnKaizoku* this, PlayState* play);
void func_80B8833C(EnKaizoku* this);
void func_80B88378(EnKaizoku* this, PlayState* play);
void func_80B88770(EnKaizoku* this);
void func_80B887AC(EnKaizoku* this, PlayState* play);
void func_80B88910(EnKaizoku* this);
void func_80B88964(EnKaizoku* this, PlayState* play);
void func_80B88CD8(EnKaizoku* this);
void func_80B88D6C(EnKaizoku* this, PlayState* play);
void EnKaizoku_Stunned(EnKaizoku* this, PlayState* play);
void func_80B894C0(EnKaizoku* this, PlayState* play);
void func_80B8971C(EnKaizoku* this, PlayState* play);

typedef enum EnKaizokuAction {
    /*  0 */ KAIZOKU_ACTION_0,
    /*  1 */ KAIZOKU_ACTION_1,
    /*  2 */ KAIZOKU_ACTION_2,
    /*  3 */ KAIZOKU_ACTION_3,
    /*  4 */ KAIZOKU_ACTION_4,
    /*  5 */ KAIZOKU_ACTION_5,
    /*  6 */ KAIZOKU_ACTION_6,
    /*  7 */ KAIZOKU_ACTION_7,
    /*  8 */ KAIZOKU_ACTION_8,
    /*  9 */ KAIZOKU_ACTION_9,
    /* 10 */ KAIZOKU_ACTION_10,
    /* 11 */ KAIZOKU_ACTION_11,
    /* 12 */ KAIZOKU_ACTION_12,
    /* 13 */ KAIZOKU_ACTION_13,
    /* 14 */ KAIZOKU_ACTION_14,
    /* 15 */ KAIZOKU_ACTION_15,
    /* 16 */ KAIZOKU_ACTION_16
} EnKaizokuAction;

// text Ids
static u16 sKaizokuTextIds[] = {
  0x11A4, // (intro.1) halt
  0x11A5, // (intro.2) you must have courage, going to love doing this to you
  0x11A6, // (win) ouch, dont think this is the end
  0x11A7, // (loss) you're nothing to talk about  
  0x11A8, // (intro.1) go no further
  0x11A9, // (intro.2) you wont get past here
  0x11AA, // (win) not bad, but this isnt the end
  0x11AB, // (loss) hmph, we're not fools
  0x11AC, // (stone mask) we aren't fooled by that mask
  0x11AD, // (stone mask) did you think that mask would work?
};

static Vec3f sCutsceneCameraPositions[] = {
    { -70.0f, 9.0f, 30.0f },   { -70.0f, 9.0f, 30.0f },   { -70.0f, 9.0f, 30.0f },   { 41.0f, 55.0f, 11.0f },
    { 41.0f, 55.0f, 11.0f },   { 70.0f, 45.0f, 35.0f },   { 80.0f, 45.0f, 25.0f },   { 0.0f, 0.0f, 0.0f },
    { -70.0f, 9.0f, 30.0f },   { -70.0f, 9.0f, 30.0f },   { -70.0f, 9.0f, 30.0f },   { 41.0f, 55.0f, 11.0f },
    { 41.0f, 55.0f, 11.0f },   { 70.0f, 45.0f, 25.0f },   { 80.0f, 45.0f, 25.0f },   { 0.0f, 0.0f, 0.0f },
    { 90.0f, 9.0f, -30.0f },   { 90.0f, 9.0f, -30.0f },   { 90.0f, 9.0f, -30.0f },   { -41.0f, 55.0f, -11.0f },
    { -41.0f, 55.0f, -11.0f }, { -70.0f, 45.0f, -25.0f }, { -80.0f, 45.0f, -25.0f }, { 0.0f, 0.0f, 0.0f },
};

Vec3f sCutsceneCameraTargetPositions[] = {
    { 120.0f, 60.0f, -20.0f },   { 120.0f, 60.0f, -20.0f },   { 120.0f, 60.0f, -20.0f },   { -470.0f, 30.0f, -140.0f },
    { -470.0f, 30.0f, -140.0f }, { -410.0f, 80.0f, -130.0f }, { -410.0f, 80.0f, -130.0f }, { 0.0f, 0.0f, 0.0f },
    { 120.0f, 60.0f, -20.0f },   { 120.0f, 60.0f, -20.0f },   { 120.0f, 60.0f, -20.0f },   { -470.0f, 30.0f, -140.0f },
    { -470.0f, 30.0f, -140.0f }, { -410.0f, 80.0f, -130.0f }, { -410.0f, 80.0f, -130.0f }, { 0.0f, 0.0f, 0.0f },
    { -120.0f, 60.0f, 20.0f },   { -120.0f, 60.0f, 20.0f },   { -120.0f, 60.0f, 20.0f },   { 470.0f, 30.0f, 140.0f },
    { 470.0f, 30.0f, 140.0f },   { 410.0f, 80.0f, 130.0f },   { 410.0f, 80.0f, 130.0f },   { 0.0f, 0.0f, 0.0f },
};

Color_RGBA8 sKaizokuLipstickColors[] = {
    { 255, 255, 90, 255 }, // yellow
    { 55, 25, 80, 255 },   // dark purple
    { 5, 195, 110, 255 },  // seagreen (between aqua and green)
};

static Color_RGBA8 sKaizokuOutfitColors[] = {

    { 255, 130, 10, 255 },  // orange
    { 185, 130, 210, 255 }, // lavender
    { 135, 195, 80, 255 },  // pale green
};

typedef enum EnKaizokuDamageEffect {
    /* 0x0 */ KAIZOKU_DMGEFF_NONE,
    /* 0x1 */ KAIZOKU_DMGEFF_1,
    /* 0x2 */ KAIZOKU_DMGEFF_2,
    /* 0x3 */ KAIZOKU_DMGEFF_FREEZE,
    /* 0x4 */ KAIZOKU_DMGEFF_4,
    /* 0x5 */ KAIZOKU_DMGEFF_5,
    /* 0xD */ KAIZOKU_DMGEFF_D = 0xD,
    /* 0xE */ KAIZOKU_DMGEFF_E,
    /* 0xF */ KAIZOKU_DMGEFF_F
} EnKaizokuDamageEffect;

static DamageTable sDamageTable = {
    /* Deku Nut       */ DMG_ENTRY(0, KAIZOKU_DMGEFF_1),
    /* Deku Stick     */ DMG_ENTRY(1, KAIZOKU_DMGEFF_F),
    /* Horse trample  */ DMG_ENTRY(0, KAIZOKU_DMGEFF_NONE),
    /* Explosives     */ DMG_ENTRY(1, KAIZOKU_DMGEFF_F),
    /* Zora boomerang */ DMG_ENTRY(0, KAIZOKU_DMGEFF_1),
    /* Normal arrow   */ DMG_ENTRY(1, KAIZOKU_DMGEFF_F),
    /* UNK_DMG_0x06   */ DMG_ENTRY(0, KAIZOKU_DMGEFF_NONE),
    /* Hookshot       */ DMG_ENTRY(0, KAIZOKU_DMGEFF_1),
    /* Goron punch    */ DMG_ENTRY(1, KAIZOKU_DMGEFF_E),
    /* Sword          */ DMG_ENTRY(1, KAIZOKU_DMGEFF_E),
    /* Goron pound    */ DMG_ENTRY(0, KAIZOKU_DMGEFF_D),
    /* Fire arrow     */ DMG_ENTRY(2, KAIZOKU_DMGEFF_2),
    /* Ice arrow      */ DMG_ENTRY(2, KAIZOKU_DMGEFF_FREEZE),
    /* Light arrow    */ DMG_ENTRY(2, KAIZOKU_DMGEFF_4),
    /* Goron spikes   */ DMG_ENTRY(1, KAIZOKU_DMGEFF_E),
    /* Deku spin      */ DMG_ENTRY(0, KAIZOKU_DMGEFF_1),
    /* Deku bubble    */ DMG_ENTRY(1, KAIZOKU_DMGEFF_E),
    /* Deku launch    */ DMG_ENTRY(2, KAIZOKU_DMGEFF_E),
    /* UNK_DMG_0x12   */ DMG_ENTRY(0, KAIZOKU_DMGEFF_1),
    /* Zora barrier   */ DMG_ENTRY(0, KAIZOKU_DMGEFF_5),
    /* Normal shield  */ DMG_ENTRY(0, KAIZOKU_DMGEFF_NONE),
    /* Light ray      */ DMG_ENTRY(0, KAIZOKU_DMGEFF_NONE),
    /* Thrown object  */ DMG_ENTRY(1, KAIZOKU_DMGEFF_E),
    /* Zora punch     */ DMG_ENTRY(1, KAIZOKU_DMGEFF_E),
    /* Spin attack    */ DMG_ENTRY(1, KAIZOKU_DMGEFF_D),
    /* Sword beam     */ DMG_ENTRY(0, KAIZOKU_DMGEFF_NONE),
    /* Normal Roll    */ DMG_ENTRY(0, KAIZOKU_DMGEFF_NONE),
    /* UNK_DMG_0x1B   */ DMG_ENTRY(0, KAIZOKU_DMGEFF_NONE),
    /* UNK_DMG_0x1C   */ DMG_ENTRY(0, KAIZOKU_DMGEFF_NONE),
    /* Unblockable    */ DMG_ENTRY(0, KAIZOKU_DMGEFF_NONE),
    /* UNK_DMG_0x1E   */ DMG_ENTRY(0, KAIZOKU_DMGEFF_NONE),
    /* Powder Keg     */ DMG_ENTRY(1, KAIZOKU_DMGEFF_E),
};

ActorInit En_Kaizoku_InitVars = {
    /**/ ACTOR_EN_KAIZOKU,
    /**/ ACTORCAT_ENEMY,
    /**/ FLAGS,
    /**/ OBJECT_KZ,
    /**/ sizeof(EnKaizoku),
    /**/ EnKaizoku_Init,
    /**/ EnKaizoku_Destroy,
    /**/ EnKaizoku_Update,
    /**/ NULL,
};

static ColliderCylinderInit sCylinderInit = {
    {
        COLTYPE_NONE,
        AT_NONE,
        AC_ON | AC_TYPE_PLAYER,
        OC1_ON | OC1_TYPE_ALL,
        OC2_TYPE_1,
        COLSHAPE_CYLINDER,
    },
    {
        ELEMTYPE_UNK4,
        { 0x00000000, 0x00, 0x00 },
        { 0xF7CFFFFF, 0x00, 0x00 },
        TOUCH_NONE | TOUCH_SFX_NORMAL,
        BUMP_ON | BUMP_HOOKABLE,
        OCELEM_ON,
    },
    { 20, 50, 0, { 0, 0, 0 } },
};

static ColliderQuadInit sQuadInit = {
    {
        COLTYPE_NONE,
        AT_ON | AT_TYPE_PLAYER | AT_TYPE_ENEMY,
        AC_NONE,
        OC1_NONE,
        OC2_NONE,
        COLSHAPE_QUAD,
    },
    {
        ELEMTYPE_UNK4,
        { 0xF7CFFFFF, 0x00, 0x00 },
        { 0x00000000, 0x00, 0x00 },
        TOUCH_ON | TOUCH_SFX_NORMAL | TOUCH_UNK7,
        BUMP_NONE,
        OCELEM_NONE,
    },
    { { { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } } },
};

static AnimationHeader* sAnimations[EN_KAIZOKU_ANIM_MAX] = {
    &gKaizokuFightingIdleAnim, // KAIZOKU_ANIM_FIGHTING_IDLE
    &gKaizokuOOTConversationAnim, // EN_KAIZOKU_ANIM_1
    &gKaizokuOOTJumpAnim, // EN_KAIZOKU_ANIM_2
    &gKaizokuSidestepAnim, // KAIZOKU_ANIM_SIDESTEP
    &gKaizokuWalkAnim, // KAIZOKU_ANIM_WALK
    &gKaizokuDamageAnim, // KAIZOKU_ANIM_DAMAGE
    &gKaizokuDefeatOldAnim, // EN_KAIZOKU_ANIM_6
    &gKaizokuBlockAnim, // KAIZOKU_ANIM_BLOCK
    &gKaizokuFlipAnim, // KAIZOKU_ANIM_FLIP
    &gKaizokuSlashAnim, // KAIZOKU_ANIM_SLASH_ATTCK
    &gKaizokuSpinAttackAnim, // KAIZOKU_ANIM_SPIN_ATTACK
    &gKaizokuLandAnim, // KAIZOKU_ANIM_LAND
    &gKaizokuChallengeTalkAnim, // KAIZOKU_ANIM_CHALLENGE
    &gKaizokuUnsheatheAnim, // KAIZOKU_ANIM_UNSHEATHE
    &gKaizokuLowerWeaponsAnim, // KAIZOKU_ANIM_LOWER_WEAPONS
    &gKaizokuDemonstrativeSwordSwingAnim, // KAIZOKU_ANIM_DEMONSTRATIVE_SWORD_SWING
    &gKaizokuDefeatAnim, // KAIZOKU_ANIM_DEFEAT
    &gKaizokuDefeatIdleAnim, // KAIZOKU_ANIM_DEFEAT_IDLE
    &gKaizokuThrowFlashAnim, // KAIZOKU_ANIM_THROW_FLASH
};

static u8 sAnimationModes[EN_KAIZOKU_ANIM_MAX] = {
    ANIMMODE_LOOP, // KAIZOKU_ANIM_FIGHTING_IDLE
    ANIMMODE_LOOP, // EN_KAIZOKU_ANIM_1
    ANIMMODE_ONCE, // EN_KAIZOKU_ANIM_2
    ANIMMODE_LOOP, // KAIZOKU_ANIM_SIDESTEP
    ANIMMODE_LOOP, // KAIZOKU_ANIM_WALK
    ANIMMODE_ONCE, // KAIZOKU_ANIM_DAMAGE
    ANIMMODE_ONCE, // EN_KAIZOKU_ANIM_6
    ANIMMODE_ONCE, // KAIZOKU_ANIM_BLOCK
    ANIMMODE_ONCE, // KAIZOKU_ANIM_FLIP
    ANIMMODE_ONCE, // KAIZOKU_ANIM_SLASH_ATTCK
    ANIMMODE_ONCE, // KAIZOKU_ANIM_SPIN_ATTACK
    ANIMMODE_ONCE, // KAIZOKU_ANIM_LAND
    ANIMMODE_LOOP, // KAIZOKU_ANIM_CHALLENGE
    ANIMMODE_ONCE, // KAIZOKU_ANIM_UNSHEATHE
    ANIMMODE_ONCE, // KAIZOKU_ANIM_LOWER_WEAPONS
    ANIMMODE_ONCE, // KAIZOKU_ANIM_DEMONSTRATIVE_SWORD_SWING
    ANIMMODE_ONCE, // KAIZOKU_ANIM_DEFEAT
    ANIMMODE_LOOP, // KAIZOKU_ANIM_DEFEAT_IDLE
    ANIMMODE_ONCE, // KAIZOKU_ANIM_THROW_FLASH
};

void EnKaizoku_Init(Actor* thisx, PlayState* play) {
    s32 pad;
    EnKaizoku* this = THIS;
    Player* player = GET_PLAYER(play);
    EffectBlureInit1 blureInit;

    this->picto.actor.hintId = TATL_HINT_ID_PIRATE;
    this->picto.actor.targetMode = TARGET_MODE_3;
    this->picto.actor.colChkInfo.mass = 80;
    ActorShape_Init(&this->picto.actor.shape, 0.0f, ActorShadow_DrawFeet, 0.0f);
    this->textType = KAIZOKU_GET_TYPE(this);
    this->picto.actor.colChkInfo.health = 8;
    this->exitIndex = KAIZOKU_GET_EXIT_INDEX(&this->picto.actor);
    this->switchFlag = KAIZOKU_GET_SWITCH_FLAG(&this->picto.actor);

    if (this->textType >= 2) {
        this->textType = 0;
    } else if (this->textType == 2) { // @Bug: '2' also matches '>= 2'
        this->textType = 0;
    }

    this->colorType = KAIZOKU_GET_TYPE(this);
    KAIZOKU_GET_TYPE(this) = 0;
    this->picto.actor.colChkInfo.damageTable = &sDamageTable;
    SkelAnime_InitFlex(play, &this->skelAnime, &gKaizokuSkel, &gKaizokuWalkAnim, this->jointTable,
                       this->morphTable, KAIZOKU_LIMB_MAX);
    Collider_InitAndSetCylinder(play, &this->bodyCollider, &this->picto.actor, &sCylinderInit);
    Collider_InitAndSetQuad(play, &this->swordCollider, &this->picto.actor, &sQuadInit);
    blureInit.p1StartColor[0] = blureInit.p1StartColor[1] = blureInit.p1StartColor[2] = blureInit.p1StartColor[3] =
        blureInit.p2StartColor[0] = blureInit.p2StartColor[1] = blureInit.p2StartColor[2] = blureInit.p1EndColor[0] =
            blureInit.p1EndColor[1] = blureInit.p1EndColor[2] = blureInit.p2EndColor[0] = blureInit.p2EndColor[1] =
                blureInit.p2EndColor[2] = 255;
    blureInit.p2StartColor[3] = 64;
    blureInit.p1EndColor[3] = blureInit.p2EndColor[3] = 0;
    blureInit.elemDuration = 8;
    blureInit.unkFlag = 0;
    blureInit.calcMode = 2;
    Effect_Add(play, &this->blureIndex, EFFECT_BLURE1, 0, 0, &blureInit);
    Actor_SetScale(&this->picto.actor, 0.0125f);
    this->picto.actor.flags |= ACTOR_FLAG_CANT_LOCK_ON;
    this->picto.actor.flags &= ~ACTOR_FLAG_TARGETABLE;
    if (this->switchFlag == KAIZOKU_SWITCH_FLAG_NONE) {
        this->switchFlag = SWITCH_FLAG_NONE;
    }

    if ((this->switchFlag > SWITCH_FLAG_NONE) && Flags_GetSwitch(play, this->switchFlag)) {
        Actor_Kill(&this->picto.actor);
        return;
    }

    this->bodyCollider.dim.radius = 20;
    this->bodyCollider.dim.height = 65;
    this->bodyCollider.dim.yShift = 0;
    this->csId = this->picto.actor.csId;
    this->picto.actor.world.pos.y = player->actor.world.pos.y + 160.0f;
    this->picto.validationFunc = EnKaizoku_ValidatePictograph;
    this->picto.actor.flags |= ACTOR_FLAG_400;
    EnKaizoku_SetupWaitForApproach(this);
}

void EnKaizoku_Destroy(Actor* thisx, PlayState* play) {
    EnKaizoku* this = THIS;

    Effect_Destroy(play, this->blureIndex);
    Collider_DestroyCylinder(play, &this->bodyCollider);
    Collider_DestroyQuad(play, &this->swordCollider);
    Audio_RestorePrevBgm();
}

s32 func_80B85858(EnKaizoku* this, PlayState* play) {
    Actor* itemAction;
    Player* player = GET_PLAYER(play);
    s16 prevAction = this->action;

    for (itemAction = play->actorCtx.actorLists[ACTORCAT_ITEMACTION].first; itemAction != NULL;
         itemAction = itemAction->next) {
        if (((itemAction->id != ACTOR_ARMS_HOOK) && (itemAction->id != ACTOR_EN_ARROW)) || (player->unk_D57 == 0)) {
            continue;
        }

        if (((itemAction->id != ACTOR_ARMS_HOOK) || (this->action != KAIZOKU_ACTION_13)) &&
            (this->action != KAIZOKU_ACTION_6)) {
            func_80B87C7C(this);
        }
        break;
    }

    if (prevAction != this->action) {
        return true;
    } else {
        return false;
    }
}

void func_80B85900(EnKaizoku* this) {
    if (this->action == KAIZOKU_ACTION_1) {
        this->headRot.y = Math_SinS(this->lookTimer * 0x1068) * 0x22D8;
    } else if (this->action != KAIZOKU_ACTION_13) {
        if ((this->action == KAIZOKU_ACTION_9) || (this->action == KAIZOKU_ACTION_11)) {
            Math_SmoothStepToS(&this->headRot.y, this->picto.actor.yawTowardsPlayer - this->picto.actor.shape.rot.y, 1,
                               500, 0);
            this->headRot.y = CLAMP(this->headRot.y, -0x256F, 0x256F);
        } else {
            this->headRot.y = 0;
        }
    }
}

s32 func_80B85A00(EnKaizoku* this, PlayState* play, s16 arg2) {
    Player* player = GET_PLAYER(play);
    s16 sp32 = ABS_ALT(this->picto.actor.wallYaw - this->picto.actor.shape.rot.y);
    s16 sp30 = ABS_ALT(this->picto.actor.yawTowardsPlayer - this->picto.actor.shape.rot.y);
    Actor* explosiveActor;

    if (func_800BE184(play, &this->picto.actor, 100.0f, 0x2710, 0x4000, this->picto.actor.shape.rot.y)) {
        if (player->meleeWeaponAnimation == PLAYER_MWA_JUMPSLASH_START) {
            if (this->action != KAIZOKU_ACTION_2) {
                func_80B874D8(this, play);
            }
            return true;
        } else {
            func_80B87900(this);
            return true;
        }
    } else if (func_800BE184(play, &this->picto.actor, 100.0f, 0x5DC0, 0x2AA8, this->picto.actor.shape.rot.y)) {
        this->picto.actor.shape.rot.y = this->picto.actor.world.rot.y = this->picto.actor.yawTowardsPlayer;
        if ((this->picto.actor.bgCheckFlags & BGCHECKFLAG_WALL) && (ABS_ALT(sp32) < 0x2EE0) &&
            (this->picto.actor.xzDistToPlayer < 90.0f)) {
            if (this->action != KAIZOKU_ACTION_6) {
                func_80B87C7C(this);
            }
            return true;
        } else if (player->meleeWeaponAnimation == PLAYER_MWA_JUMPSLASH_START) {
            if (this->action != KAIZOKU_ACTION_2) {
                func_80B874D8(this, play);
            }
        } else if (this->picto.actor.xzDistToPlayer < BREG(11) + 180.0f) {
            func_80B87900(this);
        } else if (this->action != KAIZOKU_ACTION_7) {
            func_80B87E28(this);
        }
        return true;
    }

    explosiveActor = Actor_FindNearby(play, &this->picto.actor, -1, ACTORCAT_EXPLOSIVES, 80.0f);
    if (explosiveActor != NULL) {
        this->picto.actor.shape.rot.y = this->picto.actor.world.rot.y = this->picto.actor.yawTowardsPlayer;

        if (((this->picto.actor.bgCheckFlags & BGCHECKFLAG_WALL) && (sp32 < 0x2EE0)) ||
            (explosiveActor->id == ACTOR_EN_BOM_CHU)) {
            if ((explosiveActor->id == ACTOR_EN_BOM_CHU) &&
                (Actor_WorldDistXYZToActor(&this->picto.actor, explosiveActor) < 80.0f) &&
                (BINANG_ADD(this->picto.actor.shape.rot.y - explosiveActor->world.rot.y, 0x8000) < 0x4000)) {
                if (this->action != KAIZOKU_ACTION_6) {
                    func_80B87C7C(this);
                }
            } else {
                func_80B87900(this);
            }

            return true;
        }

        if (this->action != KAIZOKU_ACTION_7) {
            func_80B87E28(this);
        }
        return true;
    }

    if (arg2) {
        s16 sp2A;

        //! FAKE:
    label:;
        if (sp30 >= 10000) {
            func_80B87900(this);
        } else {
            sp2A = player->actor.shape.rot.y - this->picto.actor.shape.rot.y;
            if ((this->picto.actor.xzDistToPlayer <= 65.0f) && !Actor_OtherIsTargeted(play, &this->picto.actor) &&
                (ABS_ALT(sp2A) < 0x5000)) {
                if (this->action != KAIZOKU_ACTION_9) {
                    func_80B87F70(this);
                    return 1;
                }
            } else if (this->action != KAIZOKU_ACTION_3) {
                func_80B88CD8(this);
            }
        }
        return true;
    }

    return false;
}

void EnKaizoku_ChangeAnim(EnKaizoku* this, EnKaizokuAnimation animIndex) {
    this->animIndex = animIndex;
    this->animEndFrame = Animation_GetLastFrame(sAnimations[this->animIndex]);
    Animation_Change(&this->skelAnime, sAnimations[this->animIndex], 1.0f, 0.0f, this->animEndFrame,
                     sAnimationModes[this->animIndex], 0.0f);
}

s32 EnKaizoku_ValidatePictograph(PlayState* play, Actor* actor) {
    s32 ret = Snap_ValidatePictograph(play, actor, PICTO_VALID_PIRATE_GOOD, &actor->focus.pos, &actor->shape.rot, 10.0f,
                                      400.0f, -1);

    ret |= Snap_ValidatePictograph(play, actor, PICTO_VALID_PIRATE_TOO_FAR, &actor->focus.pos, &actor->shape.rot, 10.0f,
                                   1200.0f, -1);
    return ret;
}

void EnKaizoku_SetupWaitForApproach(EnKaizoku* this) {
    Math_Vec3f_Copy(&this->unk_2F8, &gZeroVec3f);
    Math_Vec3f_Copy(&this->unk_304, &gZeroVec3f);
    this->bool2D8 = true;
    this->action = KAIZOKU_ACTION_0;
    this->actionFunc = EnKaizoku_WaitForApproach;
}

void EnKaizoku_WaitForApproach(EnKaizoku* this, PlayState* play) {
    Player* player = GET_PLAYER(play);
    f32 curFrame = this->skelAnime.curFrame;
    s32 nextTextId;

    switch (this->cutsceneState) {
        case 0: // waiting
            if (!(this->picto.actor.xzDistToPlayer < 200.0f)) {
                break;
            }

            if (!CutsceneManager_IsNext(this->csId)) {
                CutsceneManager_Queue(this->csId);
                return;
            }

            CutsceneManager_StartWithPlayerCs(this->csId, &this->picto.actor);
            Player_SetCsActionWithHaltedActors(play, &this->picto.actor, PLAYER_CSACTION_21);
            this->subCamId = CutsceneManager_GetCurrentSubCamId(this->picto.actor.csId);
            this->picto.actor.shape.rot.y = this->picto.actor.world.rot.y = this->picto.actor.yawTowardsPlayer;

            nextTextId = (this->textType * 4) + this->textidOffset;
            if (this->colorType != 2) {
                player->actor.world.pos.x = this->picto.actor.home.pos.x + 90.0f;
                player->actor.world.pos.z = this->picto.actor.home.pos.z + 30.0f;
            } else {
                player->actor.world.pos.x = this->picto.actor.home.pos.x - 90.0f;
                player->actor.world.pos.z = this->picto.actor.home.pos.z - 30.0f;
            }

            player->actor.speed = 0.0f;
            this->picto.actor.world.pos.x = this->picto.actor.home.pos.x;
            this->picto.actor.world.pos.z = this->picto.actor.home.pos.z;
            Message_StartTextbox(play, sKaizokuTextIds[nextTextId], &this->picto.actor);
            this->textidOffset++; // KAIZOKU_COVERSATION_INTRO_2
            this->picto.actor.flags &= ~ACTOR_FLAG_TARGETABLE;
            player->actor.shape.rot.y = player->actor.world.rot.y =
                Math_Vec3f_Yaw(&player->actor.world.pos, &this->picto.actor.world.pos);
            Math_Vec3f_Copy(&this->subCamEye, &this->unk_5C8);
            Math_Vec3f_Copy(&this->subCamAt, &this->unk_5D4);
            this->subCamUp.x = -0.11f;
            this->picto.actor.draw = EnKaizoku_Draw;
            this->cutsceneTimer = 0;
            Audio_SetMainBgmVolume(0, 0xA);
            this->cutsceneState++;
            // fallthrough
        case 1:
            player->actor.shape.rot.y = player->actor.world.rot.y =
                Math_Vec3f_Yaw(&player->actor.world.pos, &this->picto.actor.world.pos);
            this->picto.actor.shape.rot.y = this->picto.actor.world.rot.y = this->picto.actor.yawTowardsPlayer;

            if (this->colorType != 2) {
                player->actor.world.pos.x = this->picto.actor.home.pos.x + 90.0f;
                player->actor.world.pos.z = this->picto.actor.home.pos.z + 30.0f;
            } else {
                player->actor.world.pos.x = this->picto.actor.home.pos.x - 90.0f;
                player->actor.world.pos.z = this->picto.actor.home.pos.z - 30.0f;
            }

            if ((Message_GetState(&play->msgCtx) == TEXT_STATE_EVENT) && Message_ShouldAdvance(play)) {
                Message_CloseTextbox(play);
                EnKaizoku_ChangeAnim(this, KAIZOKU_ANIM_LAND);
                this->cutsceneTimer = 0;
                this->cutsceneState++;
                this->picto.actor.gravity = -2.0f;
            }
            break;

        case 2:
            if (this->picto.actor.bgCheckFlags & BGCHECKFLAG_GROUND) {
                if (this->bool2D8 != false) {
                    this->bool2D8 = false;
                    this->picto.actor.world.pos.y = this->picto.actor.floorHeight;
                    this->picto.actor.velocity.y = 0.0f;
                    Player_SetCsActionWithHaltedActors(play, &this->picto.actor, PLAYER_CSACTION_4);
                    Actor_SpawnFloorDustRing(play, &this->picto.actor, &this->leftFootPos, 3.0f, 2, 2.0f, 0, 0, false);
                    Actor_SpawnFloorDustRing(play, &this->picto.actor, &this->rightFootPos, 3.0f, 2, 2.0f, 0, 0, false);
                    Actor_PlaySfx(&this->picto.actor, NA_SE_EN_PIRATE_ONGND);
                }

                if (curFrame >= 11.0f) {
                    this->cutsceneState++;
                    this->cutsceneTimer = 0;
                    this->subCamUp.x = 0.0f;
                }
            }
            break;

        case 3:
            if (curFrame >= this->animEndFrame) {
                nextTextId = this->textType * 4 + this->textidOffset;
                if (Player_GetMask(play) == PLAYER_MASK_STONE) {
                    // adjust textIds to mention the mask
                    if (sKaizokuTextIds[nextTextId] == 0x11A5) {
                        nextTextId = 8;
                    } else if (sKaizokuTextIds[nextTextId] == 0x11A9) {
                        nextTextId = 9;
                    }
                }

                Message_StartTextbox(play, sKaizokuTextIds[nextTextId], &this->picto.actor);
                EnKaizoku_ChangeAnim(this, KAIZOKU_ANIM_CHALLENGE);
                this->textidOffset++; // KAIZOKU_COVERSATION_INTRO_WIN, although that gets set directly later
                this->cutsceneTimer = 0;
                this->cutsceneState++;
            }
            break;

        case 4:
            if ((Message_GetState(&play->msgCtx) == TEXT_STATE_EVENT) && Message_ShouldAdvance(play)) {
                Message_CloseTextbox(play);
                this->cutsceneTimer = 0;
                this->cutsceneState++;
                Audio_SetMainBgmVolume(0x7F, 0);
                Audio_PlayBgm_StorePrevBgm(NA_BGM_MINI_BOSS);
                EnKaizoku_ChangeAnim(this, KAIZOKU_ANIM_UNSHEATHE);
            }
            break;

        case 5:
            Math_ApproachF(&this->unk_5E0, 2.0f, 0.2f, 1.0f);
            if (Animation_OnFrame(&this->skelAnime, 20.0f)) {
                Actor_PlaySfx(&this->picto.actor, NA_SE_EN_BOSU_SWORD);
            }
            if (curFrame >= 30.0f) {
                this->cutsceneTimer = 0;
                this->cutsceneState++;
            }
            break;

        case 6:
            Math_ApproachF(&this->unk_5E0, 5.0f, 0.3f, 1.0f);
            if (curFrame >= this->animEndFrame) {
                this->cutsceneTimer = 7;
                this->unk_2F8.x = 1.0f;
                this->cutsceneState++;
                this->unk_2F8.y = 1.0f;
                this->unk_2F8.z = 1.0f;
                this->unk_304.x = 1.0f;
                this->unk_304.y = 1.0f;
                this->unk_304.z = 1.0f;
            }
            break;

        case 7:
            if (this->cutsceneTimer == 0) {
                Player_SetCsActionWithHaltedActors(play, &this->picto.actor, PLAYER_CSACTION_END);
                CutsceneManager_Stop(this->csId);
                this->cutsceneState = 0;
                this->subCamId = SUB_CAM_ID_DONE;
                this->picto.actor.flags &= ~ACTOR_FLAG_100000;
                this->picto.actor.flags &= ~ACTOR_FLAG_CANT_LOCK_ON;
                this->picto.actor.flags |= ACTOR_FLAG_TARGETABLE;
                func_80B872A4(this);
            }
            break;
    }

    if (this->cutsceneState < 7) {
        s32 typeCameraOffset = this->colorType * 8;

        typeCameraOffset += this->cutsceneState;
        this->unk_5C8.x = sCutsceneCameraPositions[typeCameraOffset].x + this->picto.actor.home.pos.x;
        this->unk_5C8.y = sCutsceneCameraPositions[typeCameraOffset].y + player->actor.world.pos.y;
        this->unk_5C8.z = sCutsceneCameraPositions[typeCameraOffset].z + this->picto.actor.home.pos.z;

        this->unk_5D4.x = sCutsceneCameraTargetPositions[typeCameraOffset].x + this->picto.actor.home.pos.x;
        this->unk_5D4.y = sCutsceneCameraTargetPositions[typeCameraOffset].y + player->actor.world.pos.y;
        this->unk_5D4.z = sCutsceneCameraTargetPositions[typeCameraOffset].z + this->picto.actor.home.pos.z;
    }

    if (this->cutsceneState >= 5) {
        if (curFrame >= 6.0f) {
            Math_ApproachF(&this->unk_2F8.x, 1.0f, 0.3f, 0.3f);
            this->unk_2F8.z = this->unk_2F8.y = this->unk_2F8.x;
        }

        if (curFrame >= 22.0f) {
            Math_ApproachF(&this->unk_304.x, 1.0f, 0.3f, 0.3f);
            this->unk_304.z = this->unk_304.y = this->unk_304.x;
        }
    }

    if (this->cutsceneState >= 5) {
        Math_ApproachF(&this->subCamEye.x, this->unk_5C8.x, 0.5f, this->unk_5E0);
        Math_ApproachF(&this->subCamEye.y, this->unk_5C8.y, 0.5f, this->unk_5E0);
        Math_ApproachF(&this->subCamEye.z, this->unk_5C8.z, 0.5f, this->unk_5E0);
        Math_ApproachF(&this->subCamAt.x, this->unk_5D4.x, 0.5f, this->unk_5E0);
        Math_ApproachF(&this->subCamAt.y, this->unk_5D4.y, 0.5f, this->unk_5E0);
        Math_ApproachF(&this->subCamAt.z, this->unk_5D4.z, 0.5f, this->unk_5E0);
    } else {
        Math_Vec3f_Copy(&this->subCamEye, &this->unk_5C8);
        Math_Vec3f_Copy(&this->subCamAt, &this->unk_5D4);
    }

    if (this->subCamId != SUB_CAM_ID_DONE) {
        this->subCamUp.y = 1.0f;
        this->subCamUp.z = 0.0f;
        Play_SetCameraAtEyeUp(play, this->subCamId, &this->subCamAt, &this->subCamEye, &this->subCamUp);
    }
}


void EnKaizoku_SetupLoss(EnKaizoku* this, PlayState* play) {
    if (this->subCamId == SUB_CAM_ID_DONE) {
        if (!CutsceneManager_IsNext(this->csId)) {
            CutsceneManager_Queue(this->csId);
            return;
        }
        CutsceneManager_StartWithPlayerCs(this->csId, &this->picto.actor);
    }

    Player_SetCsActionWithHaltedActors(play, &this->picto.actor, PLAYER_CSACTION_96);
    this->subCamId = CutsceneManager_GetCurrentSubCamId(this->picto.actor.csId);
    this->timer2B2 = 30;
    this->picto.actor.flags &= ~ACTOR_FLAG_TARGETABLE;
    this->cutsceneTimer = 0;
    this->cutsceneState = 0;
    this->bool2D8 = false;
    this->action = KAIZOKU_ACTION_0;
    this->actionFunc = EnKaizoku_Loss;
    this->picto.actor.speed = 0.0f;
}

void EnKaizoku_Loss(EnKaizoku* this, PlayState* play) {
    f32 curFrame = this->skelAnime.curFrame;

    Math_SmoothStepToS(&this->picto.actor.shape.rot.y, this->picto.actor.yawTowardsPlayer, 1, 0xFA0, 1);
    this->subCamEye.x = Math_SinS(this->picto.actor.yawTowardsPlayer) * 155.0f + this->picto.actor.world.pos.x;
    this->subCamEye.y = this->picto.actor.world.pos.y + 10.0f;
    this->subCamEye.z = Math_CosS(this->picto.actor.yawTowardsPlayer) * 115.0f + this->picto.actor.world.pos.z;

    this->subCamAt.x = Math_SinS(this->picto.actor.yawTowardsPlayer) + this->picto.actor.world.pos.x;
    this->subCamAt.y = this->picto.actor.world.pos.y + 30.0f;
    this->subCamAt.z = Math_CosS(this->picto.actor.yawTowardsPlayer) * 11.0f + this->picto.actor.world.pos.z;

    switch (this->cutsceneState) {
        case 0:
            if (curFrame >= this->animEndFrame) {
                EnKaizoku_ChangeAnim(this, KAIZOKU_ANIM_LOWER_WEAPONS);
                this->textidOffset = KAIZOKU_COVERSATION_LOSS;
                this->cutsceneTimer = 0;
                this->cutsceneState++;
            }
            break;

        case 1:
            if (curFrame >= this->animEndFrame) {
                s32 textId;

                EnKaizoku_ChangeAnim(this, KAIZOKU_ANIM_DEMONSTRATIVE_SWORD_SWING);
                textId = this->textType * 4 + this->textidOffset;
                Message_StartTextbox(play, sKaizokuTextIds[textId], &this->picto.actor);
                Actor_PlaySfx(&this->picto.actor, NA_SE_EN_LAST2_SHOUT);
                this->cutsceneTimer = 0;
                this->cutsceneState++;
            }
            break;

        case 2:
            if ((Message_GetState(&play->msgCtx) == TEXT_STATE_EVENT) && Message_ShouldAdvance(play)) {
                Message_CloseTextbox(play);
                Player_SetCsActionWithHaltedActors(play, &this->picto.actor, PLAYER_CSACTION_END);
                CutsceneManager_Stop(this->csId);
                this->subCamId = SUB_CAM_ID_DONE;
                play->nextEntrance = play->setupExitList[this->exitIndex];
                gSaveContext.nextCutsceneIndex = 0;
                Scene_SetExitFade(play);
                play->transitionTrigger = TRANS_TRIGGER_START;
                this->cutsceneState++;
                this->action = KAIZOKU_ACTION_16;
            }
            break;

        default:
            break;
    }

    if (this->subCamId != SUB_CAM_ID_DONE) {
        this->subCamUp.x = 0.0f;
        this->subCamUp.y = 1.0f;
        this->subCamUp.z = 0.0f;
        Play_SetCameraAtEyeUp(play, this->subCamId, &this->subCamAt, &this->subCamEye, &this->subCamUp);
    }
}

void EnKaizoku_SetupWin(EnKaizoku* this) {
    this->bool2D8 = 0;
    this->action = KAIZOKU_ACTION_0;
    this->actionFunc = EnKaizoku_Win;
}

void EnKaizoku_Win(EnKaizoku* this, PlayState* play) {
    Player* player = GET_PLAYER(play);
    s32 textId;
    f32 curFrame = this->skelAnime.curFrame;

    if (this->cutsceneState < 2) {
        Math_SmoothStepToS(&this->picto.actor.shape.rot.y, this->picto.actor.yawTowardsPlayer, 1, 0xFA0, 1);
        player->actor.world.pos.x = this->picto.actor.home.pos.x + 90.0f;
        player->actor.world.pos.z = this->picto.actor.home.pos.z + 30.0f;
        this->picto.actor.world.pos.x = this->picto.actor.home.pos.x;
        this->picto.actor.world.pos.z = this->picto.actor.home.pos.z;
        this->unk_5C8.x = player->actor.world.pos.x + 39.0f;
        this->unk_5C8.y = player->actor.world.pos.y + 4.0f;
        this->unk_5C8.z = player->actor.world.pos.z - 41.0f;
        this->unk_5D4.x = player->actor.world.pos.x - 150.0f;
        this->unk_5D4.y = player->actor.world.pos.y + 60.0f;
        this->unk_5D4.z = player->actor.world.pos.z + 50.0f;
    }

    player->actor.shape.rot.y = player->actor.world.rot.y =
        Math_Vec3f_Yaw(&player->actor.world.pos, &this->picto.actor.world.pos);
    switch (this->cutsceneState) {
        case 0:
            EnKaizoku_ChangeAnim(this, KAIZOKU_ANIM_DEFEAT_IDLE);
            this->textidOffset = KAIZOKU_COVERSATION_WIN;
            textId = this->textType * 4 + this->textidOffset;
            Message_StartTextbox(play, sKaizokuTextIds[textId], &this->picto.actor);
            this->defeatBreathingStarted = 0;
            this->cutsceneTimer = 0;
            this->cutsceneState++;
            break;

        case 1:
            if (curFrame >= this->animEndFrame) {
                if (this->defeatBreathingStarted == 0) {
                    Actor_PlaySfx(&this->picto.actor, NA_SE_EN_PIRATE_DAMM_BREATH);
                    this->defeatBreathingStarted = 1;
                } else {
                    Actor_PlaySfx(&this->picto.actor, NA_SE_EN_PIRATE_BREATH);
                }
            }

            if ((Message_GetState(&play->msgCtx) == TEXT_STATE_EVENT) && Message_ShouldAdvance(play)) {
                Message_CloseTextbox(play);
                EnKaizoku_ChangeAnim(this, KAIZOKU_ANIM_THROW_FLASH);
                Player_SetCsActionWithHaltedActors(play, &this->picto.actor, PLAYER_CSACTION_133);
                this->flashTimer = 0;
                this->cutsceneTimer = 0;
                this->cutsceneState++;
            }
            break;

        case 2:
            this->unk_5C8.x = player->actor.world.pos.x + 77.0f;
            this->unk_5C8.y = player->actor.world.pos.y + 84.0f;
            this->unk_5C8.z = player->actor.world.pos.z - 71.0f;

            this->unk_5D4.x = player->actor.world.pos.x - 110.0f;
            this->unk_5D4.y = player->actor.world.pos.y;
            this->unk_5D4.z = player->actor.world.pos.z + 30.0f;
            this->flashTimer++;
            if (curFrame >= 1.0f) {
                Math_ApproachZeroF(&this->unk_2F8.x, 0.3f, 0.3f);
                Math_ApproachZeroF(&this->unk_304.x, 0.3f, 0.3f);
                this->unk_2F8.z = this->unk_2F8.y = this->unk_2F8.x;
                this->unk_304.z = this->unk_304.y = this->unk_304.x;
            }
            if (this->flashTimer == 0x12) {
                Actor* dekuNut;

                Actor_PlaySfx(&this->picto.actor, NA_SE_EN_PIRATE_SHOUT);
                // oddly, instead of just playing the sfx and spawning an effect
                //  they spawn a real nut
                dekuNut = Actor_Spawn(&play->actorCtx, play, ACTOR_EN_ARROW,  
                      this->picto.actor.world.pos.x, this->picto.actor.world.pos.y + 10.0f, this->picto.actor.world.pos.z,
                      this->picto.actor.shape.rot.x, this->picto.actor.shape.rot.y, this->picto.actor.shape.rot.z, 
                     -ARROW_TYPE_DEKU_NUT);
  
                if (dekuNut != NULL) {
                    dekuNut->gravity = -10.0f;
                    play->envCtx.fillScreen = true;
                }
            }

            if (this->flashTimer >= 0x12) {
                Math_ApproachF(&this->flashScreenAlphaTarget, 60.0f, 1.0f, 20.0f);
                this->flashScreenAlpha = this->flashScreenAlphaTarget / 60.0f;
                play->envCtx.screenFillColor[3] = this->flashScreenAlpha * 255.0f;
                play->envCtx.screenFillColor[0] = play->envCtx.screenFillColor[1] = play->envCtx.screenFillColor[2] =
                    255;
            }

            if ((curFrame >= this->animEndFrame) && (this->flashTimer >= 0x28)) {
                this->picto.actor.draw = NULL;
                this->cutsceneTimer = 10;
                Math_Vec3f_Copy(&this->unk_2F8, &gZeroVec3f);
                Math_Vec3f_Copy(&this->unk_304, &gZeroVec3f);
                this->cutsceneState++;
            }
            break;

        case 3:
            if (this->cutsceneTimer == 0) {
                Math_ApproachZeroF(&this->flashScreenAlphaTarget, 0.5f, 10.0f);
                this->flashScreenAlpha = this->flashScreenAlphaTarget / 60.0f;
                play->envCtx.screenFillColor[3] = this->flashScreenAlpha * 255.0f;
                if (play->envCtx.screenFillColor[3] < 10) {
                    play->envCtx.screenFillColor[0] = 0;
                    play->envCtx.screenFillColor[1] = 0;
                    play->envCtx.screenFillColor[2] = 0;
                    play->envCtx.screenFillColor[3] = 0;
                    play->envCtx.fillScreen = false;
                    this->cutsceneState = 0;
                    this->subCamId = SUB_CAM_ID_DONE;
                    Player_SetCsActionWithHaltedActors(play, &this->picto.actor, PLAYER_CSACTION_END);
                    CutsceneManager_Stop(this->csId);
                    if (this->switchFlag > SWITCH_FLAG_NONE) {
                        Flags_SetSwitch(play, this->switchFlag);
                    }
                    Actor_Kill(&this->picto.actor);
                }
            }
            break;

        default:
            break;
    }
    Math_ApproachF(&this->subCamEye.x, this->unk_5C8.x, 0.5f, this->unk_5E0);
    Math_ApproachF(&this->subCamEye.y, this->unk_5C8.y, 0.5f, this->unk_5E0);
    Math_ApproachF(&this->subCamEye.z, this->unk_5C8.z, 0.5f, this->unk_5E0);
    Math_ApproachF(&this->subCamAt.x, this->unk_5D4.x, 0.5f, this->unk_5E0);
    Math_ApproachF(&this->subCamAt.y, this->unk_5D4.y, 0.5f, this->unk_5E0);
    Math_ApproachF(&this->subCamAt.z, this->unk_5D4.z, 0.5f, this->unk_5E0);
    Math_ApproachF(&this->unk_5E0, 10.0f, 0.5f, 100.0f);

    if (this->subCamId != SUB_CAM_ID_DONE) {
        this->subCamUp.x = 0.0f;
        this->subCamUp.z = 0.0f;
        this->subCamUp.y = 1.0f;
        Play_SetCameraAtEyeUp(play, this->subCamId, &this->subCamAt, &this->subCamEye, &this->subCamUp);
    }
}


// this is the start-combat actionfunction after cutscene, but do we want to start immediately with an attack? is there a standing version we could start with?
void func_80B872A4(EnKaizoku* this) {
    this->picto.actor.speed = 0.0f;
    EnKaizoku_ChangeAnim(this, KAIZOKU_ANIM_FIGHTING_IDLE);
    this->action = KAIZOKU_ACTION_1;
    this->actionFunc = func_80B872F4;
    this->picto.actor.shape.shadowScale = 90.0f;
}

void func_80B872F4(EnKaizoku* this, PlayState* play) {
    Player* player = GET_PLAYER(play);

    if ((this->lookTimer == 0) && !func_80B85858(this, play) && !func_80B85A00(this, play, false)) {
        s16 yawDiff = this->picto.actor.yawTowardsPlayer - this->picto.actor.shape.rot.y;

        if ((this->picto.actor.xzDistToPlayer < 100.0f) && (player->meleeWeaponState != PLAYER_MELEE_WEAPON_STATE_0) &&
            (yawDiff >= 0x1F40)) {
            this->picto.actor.shape.rot.y = this->picto.actor.world.rot.y = this->picto.actor.yawTowardsPlayer;
            func_80B88CD8(this);
        } else if (Actor_IsFacingPlayer(&this->picto.actor, 0xBB8)) {
            if ((this->picto.actor.xzDistToPlayer < 400.0f && this->picto.actor.xzDistToPlayer > 150.0f) &&
                (Rand_ZeroOne() < 0.7f)) {
                if ((Rand_ZeroOne() > 0.5f) || (ABS_ALT(yawDiff) < 0x3000)) {
                    func_80B88214(this);
                } else {
                    func_80B88910(this);
                }
            } else if (Rand_ZeroOne() > 0.1f) {
                func_80B8833C(this);
            } else {
                func_80B88CD8(this);
            }
        } else {
            func_80B88770(this);
        }
    }
}

void func_80B874D8(EnKaizoku* this, PlayState* play) {
    Player* player = GET_PLAYER(play);

    EnKaizoku_ChangeAnim(this, KAIZOKU_ANIM_SIDESTEP);
    if (Math_SinS(player->actor.shape.rot.y - this->picto.actor.shape.rot.y) > 0.0f) {
        this->picto.actor.speed = -10.0f;
    } else if (Math_SinS(player->actor.shape.rot.y - this->picto.actor.shape.rot.y) < 0.0f) {
        this->picto.actor.speed = 10.0f;
    } else if (Rand_ZeroOne() > 0.5f) {
        this->picto.actor.speed = 10.0f;
    } else {
        this->picto.actor.speed = -10.0f;
    }

    this->skelAnime.playSpeed = 1.0f;
    this->picto.actor.world.rot.y = this->picto.actor.shape.rot.y;
    this->timer2B2 = 6;
    this->action = KAIZOKU_ACTION_2;
    this->unk_2E0 = 0.0f;
    this->actionFunc = func_80B8760C;
}

void func_80B8760C(EnKaizoku* this, PlayState* play) {
    s16 var_v0;
    s32 temp_ft0;
    s32 temp_ft1;

    this->picto.actor.world.rot.y = this->picto.actor.yawTowardsPlayer + 0x3A98;
    if ((this->picto.actor.bgCheckFlags & BGCHECKFLAG_WALL) ||
        !Actor_TestFloorInDirection(&this->picto.actor, play, this->picto.actor.speed,
                                    this->picto.actor.shape.rot.y + 0x4000)) {
        if (this->picto.actor.bgCheckFlags & BGCHECKFLAG_WALL) {
            if (this->picto.actor.speed >= 0.0f) {
                var_v0 = this->picto.actor.shape.rot.y + 0x4000;
            } else {
                var_v0 = this->picto.actor.shape.rot.y - 0x4000;
            }
            var_v0 = this->picto.actor.wallYaw - var_v0;
        } else {
            this->picto.actor.speed *= -0.8f;
            var_v0 = 0;
        }

        if (ABS_ALT(var_v0) > 0x4000) {
            func_80B87C7C(this);
            return;
        }
    }

    if (this->picto.actor.xzDistToPlayer <= 65.0f) {
        Math_ApproachF(&this->unk_2E0, -4.0f, 1.0f, 1.5f);
    } else if (this->picto.actor.xzDistToPlayer > 40.0f) {
        Math_ApproachF(&this->unk_2E0, 4.0f, 1.0f, 1.5f);
    } else {
        Math_ApproachZeroF(&this->unk_2E0, 1.0f, 6.65f);
    }

    if (this->unk_2E0 != 0.0f) {
        this->picto.actor.world.pos.x += Math_SinS(this->picto.actor.yawTowardsPlayer) * this->unk_2E0;
        this->picto.actor.world.pos.z += Math_CosS(this->picto.actor.yawTowardsPlayer) * this->unk_2E0;
    }

    this->skelAnime.playSpeed = 1.0f;
    temp_ft0 = this->skelAnime.curFrame - this->skelAnime.playSpeed;
    temp_ft1 = this->skelAnime.curFrame + this->skelAnime.playSpeed;
    if ((this->skelAnime.curFrame != 0.0f) &&
        (((temp_ft0 < 0) && (temp_ft1 > 0)) || ((temp_ft0 < 5) && (temp_ft1 >= 6)))) {
        Actor_PlaySfx(&this->picto.actor, NA_SE_EN_GERUDOFT_WALK);
    }

    if (!(play->gameplayFrames & 0x5F)) {
        Actor_PlaySfx(&this->picto.actor, NA_SE_EN_PIRATE_BREATH);
    }

    if (this->timer2B2 == 0) {
        this->picto.actor.shape.rot.y = this->picto.actor.yawTowardsPlayer;
        if (!func_80B85858(this, play)) {
            if (this->picto.actor.xzDistToPlayer <= 70.0f) {
                func_80B87F70(this);
            } else {
                func_80B87E28(this);
            }
        }
    } else if (this->picto.actor.speed >= 0.0f) {
        this->picto.actor.shape.rot.y += 0x4000;
    } else {
        this->picto.actor.shape.rot.y -= 0x4000;
    }
}

void func_80B87900(EnKaizoku* this) {
    EnKaizoku_ChangeAnim(this, KAIZOKU_ANIM_BLOCK);

    if (this->swordState != 0) {
        this->swordState = -1;
    }
    this->bool2D8 = false;
    this->picto.actor.speed = 0.0f;
    this->timer2B2 = Rand_S16Offset(10, 10);
    this->bodyCollider.base.acFlags |= AC_HARD;
    this->lookTimer = 12;
    this->action = KAIZOKU_ACTION_12;
    this->actionFunc = func_80B8798C;
}

void func_80B8798C(EnKaizoku* this, PlayState* play) {
    Player* player = GET_PLAYER(play);
    s16 temp_v0;

    this->bool2D8 = true;
    if (this->timer2B2 == 0) {
        this->skelAnime.playSpeed = 1.0f;
    }
    if (this->lookTimer == 0) {
        this->bool2D8 = false;
        temp_v0 = this->picto.actor.yawTowardsPlayer - this->picto.actor.shape.rot.y;
        if ((ABS_ALT(temp_v0) <= 0x4000) && (this->picto.actor.xzDistToPlayer < 40.0f) &&
            (fabsf(this->picto.actor.playerHeightRel) < 50.0f)) {
            if (func_800BE184(play, &this->picto.actor, 100.0f, 10000, 0x4000, this->picto.actor.shape.rot.y)) {
                if (player->meleeWeaponAnimation == PLAYER_MWA_JUMPSLASH_START) {
                    this->bodyCollider.base.acFlags &= ~AC_HARD;
                    func_80B874D8(this, play);
                } else if (!(play->gameplayFrames & 1)) {
                    func_80B87900(this);
                } else {
                    this->bodyCollider.base.acFlags &= ~AC_HARD;
                    func_80B87E28(this);
                }
            } else {
                temp_v0 = player->actor.shape.rot.y - this->picto.actor.shape.rot.y;
                if (ABS_ALT(temp_v0) < 0x4000) {
                    this->bodyCollider.base.acFlags &= ~AC_HARD;
                    func_80B87F70(this);
                } else {
                    this->bodyCollider.base.acFlags &= ~AC_HARD;
                    func_80B88CD8(this);
                }
            }
        } else {
            this->bodyCollider.base.acFlags &= ~AC_HARD;
            func_80B88CD8(this);
        }
    } else if ((this->timer2B2 == 0) &&
               func_800BE184(play, &this->picto.actor, 100.0f, 10000, 0x4000, this->picto.actor.shape.rot.y)) {
        if (player->meleeWeaponAnimation == PLAYER_MWA_JUMPSLASH_START) {
            this->bodyCollider.base.acFlags &= ~AC_HARD;
            func_80B874D8(this, play);
        } else if (!func_80B85858(this, play)) {
            if (!(play->gameplayFrames & 1)) {
                if (this->picto.actor.xzDistToPlayer < 100.0f && Rand_ZeroOne() > 0.7f) {
                    this->bodyCollider.base.acFlags &= ~AC_HARD;
                    func_80B87C7C(this);
                } else {
                    this->bodyCollider.base.acFlags &= ~AC_HARD;
                    func_80B87E28(this);
                }
            } else {
                func_80B87900(this);
            }
        }
    }
}

void func_80B87C7C(EnKaizoku* this) {
    EnKaizoku_ChangeAnim(this, KAIZOKU_ANIM_FLIP);
    this->picto.actor.speed = 6.5f;
    this->picto.actor.velocity.y = 15.0f;
    Actor_PlaySfx(&this->picto.actor, NA_SE_EN_TEKU_JUMP);
    this->picto.actor.world.rot.y = this->picto.actor.shape.rot.y;
    this->bodyCollider.info.elemType = ELEMTYPE_UNK4;
    this->bodyCollider.base.colType = COLTYPE_NONE;
    this->swordCollider.info.elemType = ELEMTYPE_UNK4;
    this->action = KAIZOKU_ACTION_6;
    this->actionFunc = func_80B87D3C;
}

Color_RGBA8 D_80B8AC58 = { 200, 160, 120, 255 }; // light brown
Color_RGBA8 D_80B8AC5C = { 130, 90, 50, 255 };   // darker brown

Vec3f D_80B8AC60 = { 0.0f, -1.5f, 0.0f };
Vec3f D_80B8AC6C = { 0.0f, -0.2f, 0.0f };

void EnKaizoku_SpawnFootDust(PlayState* play, Vec3f* pos) {
    // reusing sparkles instead of the actual dust effect? is this left over from OOT?
    EffectSsKirakira_SpawnSmall(play, pos, &D_80B8AC60, &D_80B8AC6C, &D_80B8AC58, &D_80B8AC5C);
}

void func_80B87D3C(EnKaizoku* this, PlayState* play) {
    f32 curFrame = this->skelAnime.curFrame;

    Math_SmoothStepToS(&this->picto.actor.shape.rot.y, this->picto.actor.yawTowardsPlayer, 1, 0xFA0, 1);
    if (this->picto.actor.velocity.y >= 5.0f) {
        EnKaizoku_SpawnFootDust(play, &this->leftFootPos);
        EnKaizoku_SpawnFootDust(play, &this->rightFootPos);
    }

    this->bool2D8 = false;
    if ((curFrame >= this->animEndFrame) &&
        (this->picto.actor.bgCheckFlags & (BGCHECKFLAG_GROUND | BGCHECKFLAG_GROUND_TOUCH))) {
        this->bodyCollider.info.elemType = ELEMTYPE_UNK1;
        this->bodyCollider.base.colType = COLTYPE_HIT3;
        this->swordCollider.info.elemType = ELEMTYPE_UNK2;
        this->picto.actor.shape.rot.x = 0;
        this->picto.actor.world.rot.y = this->picto.actor.shape.rot.y = this->picto.actor.yawTowardsPlayer;
        this->picto.actor.speed = 0.0f;
        this->picto.actor.velocity.y = 0.0f;
        this->picto.actor.world.pos.y = this->picto.actor.floorHeight;
        func_80B87F70(this);
    }
}

void func_80B87E28(EnKaizoku* this) {
    EnKaizoku_ChangeAnim(this, KAIZOKU_ANIM_FLIP);
    this->picto.actor.speed = -8.0f;
    Actor_PlaySfx(&this->picto.actor, NA_SE_EN_TEKU_JUMP);
    this->bodyCollider.info.elemType = ELEMTYPE_UNK4;
    this->bodyCollider.base.colType = COLTYPE_NONE;
    this->swordCollider.info.elemType = ELEMTYPE_UNK4;
    this->action = KAIZOKU_ACTION_7;
    this->actionFunc = func_80B87E9C;
    this->picto.actor.shape.rot.y = this->picto.actor.world.rot.y = this->picto.actor.yawTowardsPlayer;
}

void func_80B87E9C(EnKaizoku* this, PlayState* play) {
    f32 curFrame = this->skelAnime.curFrame;

    this->bool2D8 = false;
    if (curFrame >= this->animEndFrame) {
        if ((this->picto.actor.xzDistToPlayer < 170.0f) && (this->picto.actor.xzDistToPlayer > 140.0f) &&
            (Rand_ZeroOne() < 0.2f)) {
            func_80B88910(this);
        } else {
            func_80B87900(this);
        }
    }
    if (!(play->state.frames & 0x5F)) {
        Actor_PlaySfx(&this->picto.actor, NA_SE_EN_PIRATE_BREATH);
    }
}

void func_80B87F70(EnKaizoku* this) {
    EnKaizoku_ChangeAnim(this, KAIZOKU_ANIM_SLASH_ATTCK);
    this->unk_2D0 = 0;
    this->swordCollider.base.atFlags &= ~AT_BOUNCED;
    this->picto.actor.speed = 0.0f;
    AudioSfx_StopByPosAndId(&this->picto.actor.projectedPos, NA_SE_EN_PIRATE_BREATH);
    this->action = KAIZOKU_ACTION_9;
    this->actionFunc = func_80B87FDC;
}

void func_80B87FDC(EnKaizoku* this, PlayState* play2) {
    PlayState* play = play2;
    f32 curFrame;
    s16 sp2E;
    s16 sp2C;
    Player* player = GET_PLAYER(play2);

    curFrame = this->skelAnime.curFrame;
    sp2E = ABS_ALT(player->actor.shape.rot.y - this->picto.actor.shape.rot.y);
    sp2C = ABS_ALT(this->picto.actor.yawTowardsPlayer - this->picto.actor.shape.rot.y);
    this->picto.actor.speed = 0.0f;

    if (Animation_OnFrame(&this->skelAnime, 1.0f)) {
        Actor_PlaySfx(&this->picto.actor, NA_SE_EN_PIRATE_ATTACK);
        this->swordState = 1;
    } else if (Animation_OnFrame(&this->skelAnime, 6.0f)) {
        this->swordState = -1;
    }

    if (this->swordCollider.base.atFlags & AT_BOUNCED) {
        this->swordState = -1;
        this->swordCollider.base.atFlags &= ~(AT_BOUNCED | AT_HIT);
        func_80B87E28(this);
        return;
    }

    this->bool2D8 = 0;
    if (curFrame >= this->animEndFrame) {
        if (!Actor_IsFacingPlayer(&this->picto.actor, 0x1554)) {
            func_80B872A4(this);

            if (sp2C > 0x4000) {
                this->lookTimer = 20;
            }
        } else {
            if (Rand_ZeroOne() > 0.7f || this->picto.actor.xzDistToPlayer >= 120.0f) {
                func_80B872A4(this);
                return;
            }

            this->picto.actor.world.rot.y = this->picto.actor.yawTowardsPlayer;

            if (BREG(12) * 0.1f + 0.01f * 40.0f < Rand_ZeroOne()) {
                func_80B87900(this);
            } else if (sp2E <= 0x2710) {
                if (sp2C > 0x4000) {
                    this->picto.actor.world.rot.y = this->picto.actor.yawTowardsPlayer;
                    func_80B88CD8(this);
                } else {
                    func_80B85A00(this, play, true);
                }
            } else {
                func_80B88CD8(this);
            }
        }
    }
}

void func_80B88214(EnKaizoku* this) {
    EnKaizoku_ChangeAnim(this, KAIZOKU_ANIM_FLIP);
    this->timer2B2 = 0;
    this->picto.actor.speed = 10.0f;
    this->picto.actor.world.rot.y = this->picto.actor.shape.rot.y = this->picto.actor.yawTowardsPlayer;
    Actor_PlaySfx(&this->picto.actor, NA_SE_EN_TEKU_JUMP);
    this->action = KAIZOKU_ACTION_5;
    this->actionFunc = func_80B88278;
}

void func_80B88278(EnKaizoku* this, PlayState* play) {
    f32 curFrame = this->skelAnime.curFrame;

    this->bool2D8 = 0;
    if (curFrame >= this->animEndFrame) {
        this->picto.actor.speed = 0.0f;
        if (!Actor_IsFacingPlayer(&this->picto.actor, 0x1554)) {
            func_80B872A4(this);
            this->timer2B2 = Rand_ZeroOne() * 5.0f + 5.0f;
        } else {
            func_80B87F70(this);
        }
    }
    if (!(play->gameplayFrames & 0x5F)) {
        Actor_PlaySfx(&this->picto.actor, NA_SE_EN_PIRATE_BREATH);
    }
}

void func_80B8833C(EnKaizoku* this) {
    EnKaizoku_ChangeAnim(this, KAIZOKU_ANIM_WALK);
    this->action = KAIZOKU_ACTION_4;
    this->actionFunc = func_80B88378;
}

void func_80B88378(EnKaizoku* this, PlayState* play) {
    Player* player = GET_PLAYER(play);
    s32 sp30;
    s32 sp2C;
    s16 sp2A;

    if (!func_80B85858(this, play)) {
        Math_SmoothStepToS(&this->picto.actor.shape.rot.y, this->picto.actor.yawTowardsPlayer, 1, 0x2EE, 0);
        this->picto.actor.world.rot.y = this->picto.actor.shape.rot.y;
        if (this->picto.actor.xzDistToPlayer <= 40.0f) {
            Math_ApproachF(&this->picto.actor.speed, -8.0f, 1.0f, 1.5f);
        } else if (this->picto.actor.xzDistToPlayer > 55.0f) {
            Math_ApproachF(&this->picto.actor.speed, 8.0f, 1.0f, 1.5f);
        } else {
            Math_ApproachZeroF(&this->picto.actor.speed, 2.0f, 6.65f);
        }

        this->skelAnime.playSpeed = 1.0f;
        sp2A = ABS_ALT(player->actor.shape.rot.y - this->picto.actor.shape.rot.y);
        if ((this->picto.actor.xzDistToPlayer < 150.0f) && (player->meleeWeaponState != PLAYER_MELEE_WEAPON_STATE_0) &&
            (sp2A >= 0x2000)) {
            this->picto.actor.shape.rot.y = this->picto.actor.world.rot.y = this->picto.actor.yawTowardsPlayer;
            if (Rand_ZeroOne() > 0.7f) {
                func_80B88CD8(this);
                return;
            }
        }

        sp30 = this->skelAnime.curFrame - this->skelAnime.playSpeed;
        sp2C = this->skelAnime.curFrame + this->skelAnime.playSpeed;
        if (!Actor_IsFacingPlayer(&this->picto.actor, 0x11C7)) {
            if (Rand_ZeroOne() > 0.5f) {
                func_80B88CD8(this);
            } else {
                func_80B872A4(this);
            }
        } else if (this->picto.actor.xzDistToPlayer < 90.0f) {
            if ((Rand_ZeroOne() > 0.03f) || ((this->picto.actor.xzDistToPlayer <= 65.0f) && (sp2A < 0x4000))) {
                func_80B87F70(this);
            } else if (Actor_OtherIsTargeted(play, &this->picto.actor) && (Rand_ZeroOne() > 0.5f)) {
                func_80B87E28(this);
            } else {
                func_80B88CD8(this);
            }
        }

        if (!func_80B85A00(this, play, false)) {
            if ((this->picto.actor.xzDistToPlayer < 210.0f) && (this->picto.actor.xzDistToPlayer > 150.0f) &&
                Actor_IsFacingPlayer(&this->picto.actor, 0x1388)) {
                if (Actor_IsTargeted(play, &this->picto.actor)) {
                    if (Rand_ZeroOne() > 0.5f) {
                        func_80B88214(this);
                    } else {
                        func_80B88910(this);
                    }
                } else {
                    func_80B88CD8(this);
                    return;
                }
            }

            if (!(play->gameplayFrames & 0x5F)) {
                Actor_PlaySfx(&this->picto.actor, NA_SE_EN_PIRATE_BREATH);
            }

            if ((this->skelAnime.curFrame != 0.0f) && (((sp30 < 0) && (sp2C > 0)) || ((sp30 < 4) && (sp2C >= 5)))) {
                Actor_PlaySfx(&this->picto.actor, NA_SE_EN_GERUDOFT_WALK);
            }
        }
    }
}

void func_80B88770(EnKaizoku* this) {
    EnKaizoku_ChangeAnim(this, KAIZOKU_ANIM_SIDESTEP);
    this->action = KAIZOKU_ACTION_10;
    this->actionFunc = func_80B887AC;
}

void func_80B887AC(EnKaizoku* this, PlayState* play) {
    s16 yawDiff;
    s16 yawAdjustment;

    if (!func_80B85858(this, play) && !func_80B85A00(this, play, false)) {
        yawDiff = this->picto.actor.yawTowardsPlayer - this->picto.actor.shape.rot.y;
        if (yawDiff > 0) {
            yawAdjustment = TRUNCF_BINANG(yawDiff * 0.25f) + 0x7D0;
        } else {
            yawAdjustment = TRUNCF_BINANG(yawDiff * 0.25f) - 0x7D0;
        }
        this->picto.actor.shape.rot.y += yawAdjustment;
        this->picto.actor.world.rot.y = this->picto.actor.shape.rot.y;
        this->skelAnime.playSpeed = 1.0f;

        if (Actor_IsFacingPlayer(&this->picto.actor, 0x1388)) {
            if (Rand_ZeroOne() > 0.8f) {
                func_80B88CD8(this);
            } else {
                func_80B8833C(this);
            }
        }
        if (!(play->gameplayFrames & 0x5F)) {
            Actor_PlaySfx(&this->picto.actor, NA_SE_EN_PIRATE_BREATH);
        }
    }
}

// long roundhouse jump attack
void func_80B88910(EnKaizoku* this) {
    EnKaizoku_ChangeAnim(this, KAIZOKU_ANIM_SPIN_ATTACK);
    this->swordCollider.base.atFlags &= ~(AT_BOUNCED | AT_HIT);
    this->unk_2D0 = 0;
    this->action = KAIZOKU_ACTION_11;
    this->actionFunc = func_80B88964;
    this->picto.actor.speed = 0.0f;
}

void func_80B88964(EnKaizoku* this, PlayState* play) {
    Player* player = GET_PLAYER(play);
    f32 curFrame = this->skelAnime.curFrame;
    s16 v1;
    s16 a0;
    s32 pad;

    if (this->unk_2D0 < 2) {
        if (this->swordCollider.base.atFlags & AT_BOUNCED) {
            this->swordCollider.base.atFlags &= ~(AT_BOUNCED | AT_HIT);
            this->unk_2D0 = 1;
            this->skelAnime.playSpeed = 1.0f;
        }
    }

    if (this->skelAnime.curFrame <= 8.0f) {
        this->picto.actor.shape.rot.y = this->picto.actor.world.rot.y = this->picto.actor.yawTowardsPlayer;
    } else if (Animation_OnFrame(&this->skelAnime, 13.0f)) {
        Actor_SpawnFloorDustRing(play, &this->picto.actor, &this->leftFootPos, 3.0f, 2, 2.0f, 0, 0, false);
        Actor_SpawnFloorDustRing(play, &this->picto.actor, &this->rightFootPos, 3.0f, 2, 2.0f, 0, 0, false);
        this->swordState = 1;
        this->picto.actor.speed = 10.0f;
        Actor_PlaySfx(&this->picto.actor, NA_SE_EN_PIRATE_ATTACK);
    } else if (Animation_OnFrame(&this->skelAnime, 21.0f)) {
        this->picto.actor.speed = 0.0f;
    } else if (Animation_OnFrame(&this->skelAnime, 24.0f)) {
        this->swordState = -1;
    }

    this->bool2D8 = 0;
    if ((curFrame >= this->animEndFrame) && (this->unk_2D0 < 2)) {
        if (!Actor_IsFacingPlayer(&this->picto.actor, 0x1554)) {
            func_80B872A4(this);
            this->timer2B2 = Rand_ZeroOne() * 5.0f + 5.0f;
            this->lookTimer = 46;
            return;
        }

        if (this->unk_2D0 != 0) {
            func_80B87E28(this);
            return;
        }

        if ((Rand_ZeroOne() > 0.7f) || (this->picto.actor.xzDistToPlayer >= 120.0f)) {
            func_80B872A4(this);
            this->timer2B2 = Rand_ZeroOne() * 5.0f + 5.0f;
            return;
        }

        this->picto.actor.world.rot.y = this->picto.actor.yawTowardsPlayer;
        if (BREG(12) * 0.1f + 0.01f * 40.0f < Rand_ZeroOne()) {
            func_80B87900(this);
            return;
        }

        v1 = ABS_ALT(player->actor.shape.rot.y - this->picto.actor.shape.rot.y);
        if (v1 <= 0x2710) {

            a0 = ABS_ALT(this->picto.actor.yawTowardsPlayer - this->picto.actor.shape.rot.y);
            if (a0 > 0x4000) {
                this->picto.actor.world.rot.y = this->picto.actor.yawTowardsPlayer;
                func_80B88CD8(this);
            } else {
                func_80B85A00(this, play, true);
            }
        } else {
            func_80B88CD8(this);
        }
    }
}

void func_80B88CD8(EnKaizoku* this) {
    EnKaizoku_ChangeAnim(this, KAIZOKU_ANIM_SIDESTEP);
    this->picto.actor.speed = Rand_CenteredFloat(12.0f);
    this->skelAnime.playSpeed = 1.0f;
    this->picto.actor.world.rot.y = this->picto.actor.shape.rot.y;
    this->timer2B2 = Rand_ZeroOne() * 30.0f + 30.0f;
    this->action = KAIZOKU_ACTION_3;
    this->actionFunc = func_80B88D6C;
    this->unk_2E0 = 0.0f;
}

void func_80B88D6C(EnKaizoku* this, PlayState* play) {
    Player* player = GET_PLAYER(play);
    s16 sp2A;
    s32 temp_ft4;
    s32 temp_ft5;
    s16 yaw;

    Math_SmoothStepToS(&this->picto.actor.shape.rot.y, this->picto.actor.yawTowardsPlayer, 1, 0xFA0, 1);
    if (!func_80B85858(this, play) && !func_80B85A00(this, play, false)) {
        this->picto.actor.world.rot.y = this->picto.actor.shape.rot.y + 0x4000;
        sp2A = player->actor.shape.rot.y + 0x8000;
        if (Math_SinS(sp2A - this->picto.actor.shape.rot.y) >= 0.0f) {
            this->picto.actor.speed -= 0.25f;
            if (this->picto.actor.speed < -8.0f) {
                this->picto.actor.speed = -8.0f;
            }
        } else if (Math_SinS(sp2A - this->picto.actor.shape.rot.y) < 0.0f) {
            this->picto.actor.speed += 0.25f;
            if (this->picto.actor.speed > 8.0f) {
                this->picto.actor.speed = 8.0f;
            }
        }

        if ((this->picto.actor.bgCheckFlags & BGCHECKFLAG_WALL) ||
            !Actor_TestFloorInDirection(&this->picto.actor, play, this->picto.actor.speed,
                                        this->picto.actor.shape.rot.y + 0x4000)) {

            if (this->picto.actor.bgCheckFlags & BGCHECKFLAG_WALL) {
                if (this->picto.actor.speed >= 0.0f) {
                    yaw = this->picto.actor.shape.rot.y + 0x4000;
                } else {
                    yaw = this->picto.actor.shape.rot.y - 0x4000;
                }
                yaw = this->picto.actor.wallYaw - yaw;
            } else {
                this->picto.actor.speed *= -0.8f;
                yaw = 0;
            }

            if (ABS_ALT(yaw) > 0x4000) {
                this->picto.actor.speed *= -0.8f;
                if (this->picto.actor.speed < 0.0f) {
                    this->picto.actor.speed -= 0.5f;
                } else {
                    this->picto.actor.speed += 0.5f;
                }
            }
        }

        if (this->picto.actor.xzDistToPlayer <= 65.0f) {
            Math_ApproachF(&this->unk_2E0, -4.0f, 1.0f, 1.5f);
        } else if (this->picto.actor.xzDistToPlayer > 40.0f) {
            Math_ApproachF(&this->unk_2E0, 4.0f, 1.0f, 1.5f);
        } else {
            Math_ApproachZeroF(&this->unk_2E0, 1.0f, 6.65f);
        }

        if (this->unk_2E0 != 0.0f) {
            this->picto.actor.world.pos.x += Math_SinS(this->picto.actor.shape.rot.y) * this->unk_2E0;
            this->picto.actor.world.pos.z += Math_CosS(this->picto.actor.shape.rot.y) * this->unk_2E0;
        }

        temp_ft4 = this->skelAnime.curFrame - this->skelAnime.playSpeed;
        temp_ft5 = this->skelAnime.curFrame + this->skelAnime.playSpeed;
        if (this->skelAnime.curFrame != 0.0f) {
            if ((((temp_ft4 < 0) && (temp_ft5 > 0)) || ((temp_ft4 < 5) && (temp_ft5 > 5)))) {
                Actor_PlaySfx(&this->picto.actor, NA_SE_EN_GERUDOFT_WALK);
            }
        }

        if (!(play->gameplayFrames & 0x5F)) {
            Actor_PlaySfx(&this->picto.actor, NA_SE_EN_PIRATE_BREATH);
        }

        if (this->picto.actor.xzDistToPlayer <= 65.0f) {
            func_80B87F70(this);
        } else if (this->timer2B2 == 0) {
            if (Actor_OtherIsTargeted(play, &this->picto.actor) && (Rand_ZeroOne() > 0.5f)) {
                func_80B87E28(this);
            } else {
                func_80B872A4(this);
            }
        }
    }
}

// not convinced these are the right function name
void EnKaizoku_SetupStunned(EnKaizoku* this) {
    if (this->picto.actor.bgCheckFlags & BGCHECKFLAG_GROUND) {
        this->picto.actor.speed = 0.0f;
    }

    if (this->action == KAIZOKU_ACTION_11) {
        EnKaizoku_ChangeAnim(this, KAIZOKU_ANIM_DAMAGE);
    }

    if (((this->drawDmgEffType == ACTOR_DRAW_DMGEFF_FROZEN_SFX) ||
         (this->drawDmgEffType == ACTOR_DRAW_DMGEFF_FROZEN_NO_SFX)) &&
        (this->colorFilterTimer == 0)) {
        this->colorFilterTimer = 0;
        this->drawDmgEffType = ACTOR_DRAW_DMGEFF_FIRE;
    }

    Actor_PlaySfx(&this->picto.actor, NA_SE_EN_COMMON_FREEZE);
    this->bool2D8 = 1;

    if ((this->drawDmgEffType != ACTOR_DRAW_DMGEFF_FROZEN_SFX) &&
        (this->drawDmgEffType != ACTOR_DRAW_DMGEFF_FROZEN_NO_SFX)) {
        this->unk_2B6 = 40;
    }

    this->action = KAIZOKU_ACTION_13;
    this->actionFunc = EnKaizoku_Stunned;
}

void EnKaizoku_Stunned(EnKaizoku* this, PlayState* play) {
    if (this->drawDmgEffType == ACTOR_DRAW_DMGEFF_FROZEN_SFX) {
        if ((this->colorFilterTimer != 0) && (this->colorFilterTimer < 60)) {
            this->drawDmgEffType = ACTOR_DRAW_DMGEFF_FROZEN_NO_SFX;
        }
    }

    if (this->picto.actor.bgCheckFlags & BGCHECKFLAG_GROUND_TOUCH) {
        this->picto.actor.speed = 0.0f;
    }

    if (this->picto.actor.bgCheckFlags & BGCHECKFLAG_GROUND) {
        if (this->picto.actor.speed < 0.0f) {
            this->picto.actor.speed += 0.05f;
        }
    }

    if ((this->unk_2B6 == 0) && (this->colorFilterTimer == 0) && !CHECK_FLAG_ALL(this->picto.actor.flags, ACTOR_FLAG_2000) &&
        (this->picto.actor.bgCheckFlags & BGCHECKFLAG_GROUND)) {
        this->bool2D8 = 0;
        func_80B85A00(this, play, true);

        if ((this->drawDmgEffType == ACTOR_DRAW_DMGEFF_FROZEN_SFX) ||
            (this->drawDmgEffType == ACTOR_DRAW_DMGEFF_FROZEN_NO_SFX)) {
            Actor_SpawnIceEffects(play, &this->picto.actor, this->bodyPartsPos, KAIZOKU_BODYPART_MAX, 2, 0.7f, 0.4f);
            this->colorFilterTimer = 0;
            this->drawDmgEffType = ACTOR_DRAW_DMGEFF_FIRE;
            this->picto.actor.flags |= ACTOR_FLAG_400;
        }
    }
}

void func_80B893CC(EnKaizoku* this, PlayState* play) {
    Vec3f sp34;

    Matrix_RotateYS(this->picto.actor.yawTowardsPlayer, MTXMODE_NEW);
    Matrix_MultVecZ(-10.0f, &sp34);
    Math_Vec3f_Copy(&this->unk_3C4, &sp34);
    this->lookTimer = 0;
    this->bool2D8 = 0;
    this->picto.actor.speed = 0.0f;
    EnKaizoku_ChangeAnim(this, KAIZOKU_ANIM_DAMAGE);

    if (((this->drawDmgEffType == ACTOR_DRAW_DMGEFF_FROZEN_SFX) ||
         (this->drawDmgEffType == ACTOR_DRAW_DMGEFF_FROZEN_NO_SFX)) &&
        (this->colorFilterTimer != 0)) {
        Actor_SpawnIceEffects(play, &this->picto.actor, this->bodyPartsPos, KAIZOKU_BODYPART_MAX, 2, 0.7f, 0.4f);
        this->colorFilterTimer = 0;
        this->drawDmgEffType = ACTOR_DRAW_DMGEFF_FIRE;
        this->picto.actor.flags |= ACTOR_FLAG_400;
    }

    Actor_PlaySfx(&this->picto.actor, NA_SE_EN_PIRATE_DAMAGE);
    this->action = KAIZOKU_ACTION_14;
    this->actionFunc = func_80B894C0;
}

void func_80B894C0(EnKaizoku* this, PlayState* play) {
    s16 temp_v0;

    Math_SmoothStepToS(&this->picto.actor.shape.rot.y, this->picto.actor.yawTowardsPlayer, 1, 0x1194, 0);
    if (!func_80B85858(this, play) && !func_80B85A00(this, play, false) && (this->unk_3C4.x < 1.0f) &&
        (this->unk_3C4.z < 1.0f)) {
        temp_v0 = this->picto.actor.wallYaw - this->picto.actor.shape.rot.y;
        if (this->picto.actor.bgCheckFlags & BGCHECKFLAG_WALL) {
            if (ABS_ALT(temp_v0) < 0x3000 && (this->picto.actor.xzDistToPlayer < 90.0f)) {
                func_80B87C7C(this);
                return;
            }
        }

        if ((this->picto.actor.xzDistToPlayer <= 65.0f) && ((play->gameplayFrames % 8) != 0)) {
            this->swordCollider.info.elemType = ELEMTYPE_UNK2;
            func_80B87F70(this);
        } else {
            func_80B87E28(this);
        }
    }
}

void func_80B8960C(EnKaizoku* this, PlayState* play) {
    Vec3f sp24;

    this->picto.actor.flags |= ACTOR_FLAG_100000;
    Matrix_RotateYS(this->picto.actor.yawTowardsPlayer, MTXMODE_NEW);
    Matrix_MultVecZ(-10.0f, &sp24);
    Math_Vec3f_Copy(&this->unk_3C4, &sp24);
    EnKaizoku_ChangeAnim(this, KAIZOKU_ANIM_DEFEAT);

    if (((this->drawDmgEffType == ACTOR_DRAW_DMGEFF_FROZEN_SFX) ||
         (this->drawDmgEffType == ACTOR_DRAW_DMGEFF_FROZEN_NO_SFX)) &&
        (this->colorFilterTimer == 0)) {
        this->drawDmgEffType = ACTOR_DRAW_DMGEFF_FIRE;
    }
    this->picto.actor.speed = 0.0f;
    this->bool2D8 = 1;
    Player_SetCsActionWithHaltedActors(play, &this->picto.actor, PLAYER_CSACTION_123);
    Enemy_StartFinishingBlow(play, &this->picto.actor);
    Actor_PlaySfx(&this->picto.actor, NA_SE_EN_PIRATE_DEAD);
    this->picto.actor.flags |= ACTOR_FLAG_CANT_LOCK_ON;
    this->picto.actor.flags &= ~ACTOR_FLAG_TARGETABLE;
    this->picto.actor.flags &= ~ACTOR_FLAG_400;
    this->cutsceneTimer = 0;
    this->cutsceneState = 0;
    this->action = KAIZOKU_ACTION_15;
    this->actionFunc = func_80B8971C;
}

void func_80B8971C(EnKaizoku* this, PlayState* play) {
    f32 curFrame = this->skelAnime.curFrame;
    Player* player;

    if (this->picto.actor.bgCheckFlags & BGCHECKFLAG_GROUND_TOUCH) {
        this->picto.actor.speed = 0.0f;
    }

    if (this->picto.actor.bgCheckFlags & BGCHECKFLAG_GROUND) {
        Math_SmoothStepToF(&this->picto.actor.speed, 0.0f, 1.0f, 0.5f, 0.0f);
    }

    if ((this->drawDmgEffType == ACTOR_DRAW_DMGEFF_FROZEN_SFX) ||
        (this->drawDmgEffType == ACTOR_DRAW_DMGEFF_FROZEN_NO_SFX)) {
        if (this->colorFilterTimer == 0) {
            return;
        }
        Actor_SpawnIceEffects(play, &this->picto.actor, this->bodyPartsPos, KAIZOKU_BODYPART_MAX, 2, 0.7f, 0.4f);
        this->colorFilterTimer = 0;
        this->drawDmgEffType = ACTOR_DRAW_DMGEFF_FIRE;
    }

    if (curFrame >= 25.0f) {
        player = GET_PLAYER(play);
        if (this->subCamId == SUB_CAM_ID_DONE) {
            if (!CutsceneManager_IsNext(this->csId)) {
                CutsceneManager_Queue(this->csId);
                return;
            }
            CutsceneManager_StartWithPlayerCs(this->csId, &this->picto.actor);
            this->subCamId = CutsceneManager_GetCurrentSubCamId(this->picto.actor.csId);
        }

        Math_Vec3f_Copy(&this->unk_3C4, &gZeroVec3f);
        player->actor.world.pos.x = this->picto.actor.home.pos.x + 90.0f;
        player->actor.world.pos.z = this->picto.actor.home.pos.z + 30.0f;
        this->picto.actor.world.pos.x = this->picto.actor.home.pos.x;
        this->picto.actor.world.pos.z = this->picto.actor.home.pos.z;

        this->subCamEye.x = this->unk_5C8.x = player->actor.world.pos.x + 39.0f;
        this->subCamEye.y = this->unk_5C8.y = player->actor.world.pos.y + 4.0f;
        this->subCamEye.z = this->unk_5C8.z = player->actor.world.pos.z - 41.0f;

        this->subCamAt.x = this->unk_5D4.x = player->actor.world.pos.x - 150.0f;
        this->subCamAt.y = this->unk_5D4.y = player->actor.world.pos.y + 60.0f;
        this->subCamAt.z = this->unk_5D4.z = player->actor.world.pos.z + 50.0f;

        player->actor.shape.rot.y = player->actor.world.rot.y =
            Math_Vec3f_Yaw(&player->actor.world.pos, &this->picto.actor.world.pos);

        if (this->subCamId != SUB_CAM_ID_DONE) {
            this->subCamUp.x = 0.0f;
            this->subCamUp.y = 1.0f;
            this->subCamUp.z = 0.0f;
            Play_SetCameraAtEyeUp(play, this->subCamId, &this->subCamAt, &this->subCamEye, &this->subCamUp);
        }
    }

    Math_SmoothStepToS(&this->picto.actor.shape.rot.y, this->picto.actor.yawTowardsPlayer, 1, 0xFA0, 1);
    SkelAnime_Update(&this->skelAnime);
    if (curFrame >= this->animEndFrame) {
        this->bool2D8 = 0;
        EnKaizoku_SetupWin(this);
    } else if (Animation_OnFrame(&this->skelAnime, 10.0f)) {
        Actor_PlaySfx(&this->picto.actor, NA_SE_EN_GERUDOFT_DOWN);
    }
}


// handle damage to player and from player
void func_80B89A08(EnKaizoku* this, PlayState* play) {
    s32 sp64 = 0;
    Vec3f sp58;
    s32 i;

    if (gSaveContext.save.saveInfo.playerData.health <= 0x10) {
        this->swordCollider.info.toucher.damage = 0;
    } else {
        this->swordCollider.info.toucher.damage = 4;
    }

    if (!(this->swordCollider.base.atFlags & AT_BOUNCED) && (this->swordCollider.base.atFlags & AT_HIT)) {
        if ((gSaveContext.save.saveInfo.playerData.health <= 0x10) && (this->action != KAIZOKU_ACTION_16)) {
            this->unk_2D0 = 2;
            this->subCamId = SUB_CAM_ID_DONE;
            this->picto.actor.flags |= ACTOR_FLAG_100000;

            if (!CutsceneManager_IsNext(this->csId)) {
                CutsceneManager_Queue(this->csId);
                this->actionFunc = EnKaizoku_SetupLoss;
            } else {
                CutsceneManager_StartWithPlayerCs(this->csId, &this->picto.actor);
                this->subCamId = CutsceneManager_GetCurrentSubCamId(this->picto.actor.csId);
                this->actionFunc = EnKaizoku_SetupLoss;
            }
            return;
        } else if ((this->action == KAIZOKU_ACTION_11) && (this->swordCollider.base.at == &GET_PLAYER(play)->actor)) {
            func_800B8D98(play, &this->picto.actor, 3.0f, this->picto.actor.yawTowardsPlayer, 1.0f);
            Health_ChangeBy(play, -0xC);
            if ((gSaveContext.save.saveInfo.playerData.health <= 0x10) && (this->action != KAIZOKU_ACTION_16)) {
                Health_ChangeBy(play, 0x10);
                this->unk_2D0 = 2;
                this->subCamId = SUB_CAM_ID_DONE;
                this->picto.actor.flags |= ACTOR_FLAG_100000;

                if (!CutsceneManager_IsNext(this->csId)) {
                    CutsceneManager_Queue(this->csId);
                    this->actionFunc = EnKaizoku_SetupLoss;
                } else {
                    CutsceneManager_StartWithPlayerCs(this->csId, &this->picto.actor);
                    this->subCamId = CutsceneManager_GetCurrentSubCamId(this->picto.actor.csId);
                    this->actionFunc = EnKaizoku_SetupLoss;
                }
                return;
            }
        }

        // HUH? they are never in a room with a barrel? did they plan a special fight mechanic?
        if (this->swordCollider.base.at->id == ACTOR_OBJ_TARU) {
            this->swordCollider.base.at->home.rot.z = 1;
        }
    }

    if ((this->picto.actor.bgCheckFlags & BGCHECKFLAG_WALL) && (this->picto.actor.wallBgId != BG_ACTOR_MAX) &&
        ((this->action == KAIZOKU_ACTION_2) || (this->action == KAIZOKU_ACTION_3) ||
         (this->action == KAIZOKU_ACTION_4) || (this->action == KAIZOKU_ACTION_1))) {
        func_80B87F70(this);
    }

    if ((this->bodyCollider.base.acFlags & AC_HIT) && (this->action > KAIZOKU_ACTION_0) && (this->unk_2D0 < 2) &&
        (this->action != KAIZOKU_ACTION_6) && (this->action != KAIZOKU_ACTION_12) &&
        (this->action != KAIZOKU_ACTION_14) && (this->action != KAIZOKU_ACTION_15)) {
        Actor_SetDropFlag(&this->picto.actor, &this->bodyCollider.info);
        AudioSfx_StopByPosAndId(&this->picto.actor.projectedPos, NA_SE_EN_PIRATE_BREATH);

        switch (this->picto.actor.colChkInfo.damageEffect) {
            case KAIZOKU_DMGEFF_5:
                if (((this->drawDmgEffType != ACTOR_DRAW_DMGEFF_FROZEN_SFX) &&
                     (this->drawDmgEffType != ACTOR_DRAW_DMGEFF_FROZEN_NO_SFX)) ||
                    (this->colorFilterTimer == 0)) {
                    this->colorFilterTimer = 40;
                    this->drawDmgEffType = ACTOR_DRAW_DMGEFF_ELECTRIC_SPARKS_MEDIUM;
                }
                // fallthrough
            case KAIZOKU_DMGEFF_1:
                if (((this->drawDmgEffType != ACTOR_DRAW_DMGEFF_FROZEN_SFX) &&
                     (this->drawDmgEffType != ACTOR_DRAW_DMGEFF_FROZEN_NO_SFX)) ||
                    this->colorFilterTimer == 0) {
                    Actor_SetColorFilter(&this->picto.actor, COLORFILTER_COLORFLAG_BLUE, 120, COLORFILTER_BUFFLAG_OPA,
                                         40);
                    this->bodyCollider.info.elemType = ELEMTYPE_UNK1;
                    this->bodyCollider.base.colType = COLTYPE_HIT3;
                    this->swordCollider.info.elemType = ELEMTYPE_UNK2;
                    EnKaizoku_SetupStunned(this);
                }
                break;

            case KAIZOKU_DMGEFF_F:
                if ((this->action != KAIZOKU_ACTION_5) && (this->action != KAIZOKU_ACTION_7) &&
                    (this->action < KAIZOKU_ACTION_14)) {
                    sp64 = 1;
                }
                break;

            case KAIZOKU_DMGEFF_E:
                sp64 = 1;
                break;

            case KAIZOKU_DMGEFF_D:
                if (this->action == KAIZOKU_ACTION_13) {
                    sp64 = 1;
                } else if (this->action != KAIZOKU_ACTION_6) {
                    func_80B87C7C(this);
                }
                break;

            case KAIZOKU_DMGEFF_2:
                if ((this->action != KAIZOKU_ACTION_5) && (this->action != KAIZOKU_ACTION_7) &&
                    (this->action < KAIZOKU_ACTION_14)) {
                    this->colorFilterTimer = 40;
                    this->drawDmgEffType = ACTOR_DRAW_DMGEFF_FIRE;
                    sp64 = 1;
                }
                break;

            case KAIZOKU_DMGEFF_FREEZE:
                if (((this->drawDmgEffType != ACTOR_DRAW_DMGEFF_FROZEN_SFX) &&
                     (this->drawDmgEffType != ACTOR_DRAW_DMGEFF_FROZEN_NO_SFX)) ||
                    (this->colorFilterTimer == 0)) {
                    Actor_ApplyDamage(&this->picto.actor);
                    this->bodyCollider.info.elemType = ELEMTYPE_UNK1;
                    this->bodyCollider.base.colType = COLTYPE_HIT3;
                    this->swordCollider.info.elemType = ELEMTYPE_UNK4;
                    this->colorFilterTimer = 80;
                    this->drawDmgEffType = ACTOR_DRAW_DMGEFF_FROZEN_SFX;
                    this->drawDmgEffScale = 0.0f;
                    this->drawDmgEffFrozenSteamScale = 1.5f;
                    this->picto.actor.flags &= ~ACTOR_FLAG_400;
                    if (this->picto.actor.colChkInfo.health <= 0) {
                        func_80B8960C(this, play);
                    } else {
                        EnKaizoku_SetupStunned(this);
                    }
                }
                break;

            case KAIZOKU_DMGEFF_4:
                if (((this->drawDmgEffType != ACTOR_DRAW_DMGEFF_FROZEN_SFX) &&
                     (this->drawDmgEffType != ACTOR_DRAW_DMGEFF_FROZEN_NO_SFX)) ||
                    (this->colorFilterTimer == 0)) {
                    this->colorFilterTimer = 20;
                    this->drawDmgEffType = ACTOR_DRAW_DMGEFF_LIGHT_ORBS;
                    Actor_Spawn(&play->actorCtx, play, ACTOR_EN_CLEAR_TAG, this->picto.actor.focus.pos.x,
                                this->picto.actor.focus.pos.y, this->picto.actor.focus.pos.z, 0, 0, 0,
                                CLEAR_TAG_PARAMS(CLEAR_TAG_LARGE_LIGHT_RAYS));
                    sp64 = 1;
                }
                break;

            default:
                break;
        }

        if (sp64) {
            Actor_SetColorFilter(&this->picto.actor, COLORFILTER_COLORFLAG_RED, 255, COLORFILTER_BUFFLAG_OPA, 8);
            Actor_ApplyDamage(&this->picto.actor);
            if (this->picto.actor.colChkInfo.health <= 0) {
                func_80B8960C(this, play);
                return;
            }

            this->bodyCollider.info.elemType = ELEMTYPE_UNK1;
            this->bodyCollider.base.colType = COLTYPE_HIT3;
            this->swordCollider.info.elemType = ELEMTYPE_UNK4;
            Math_Vec3f_Copy(&sp58, &this->picto.actor.focus.pos);
            for (i = 0; i < 3; i++) {
                sp58.y += Rand_ZeroFloat(20.0f);
                CollisionCheck_BlueBlood(play, NULL, &sp58);
            }

            func_80B893CC(this, play);
        }
    } else if (this->bodyCollider.base.acFlags & AC_HIT) {
        if ((this->action != KAIZOKU_ACTION_6) && (this->action != KAIZOKU_ACTION_14) &&
            (this->action != KAIZOKU_ACTION_15)) {
            Vec3f pos;
            Player* player = GET_PLAYER(play);

            pos.x = this->bodyCollider.info.bumper.hitPos.x;
            pos.y = this->bodyCollider.info.bumper.hitPos.y;
            pos.z = this->bodyCollider.info.bumper.hitPos.z;

            if (player->transformation != PLAYER_FORM_HUMAN) {
                player->pushedYaw = this->picto.actor.yawTowardsPlayer;
                player->pushedSpeed = 15.0f;
            }

            this->bodyCollider.base.acFlags &= ~AC_HIT;
            Actor_PlaySfx(&this->picto.actor, NA_SE_IT_SHIELD_BOUND);
            EffectSsHitmark_SpawnFixedScale(play, 3, &pos);
            CollisionCheck_SpawnShieldParticlesMetal(play, &pos);
        }
    }
}

static Vec3f sFootOffset = { 300.0f, 0.0f, 0.0f };

static Vec3f sSwordTipOffset = { 0.0f, -3000.0f, 0.0f };
static Vec3f sSwordHiltOffset = { 400.0f, 0.0f, 0.0f };

static Vec3f sSwordQuadOffset1 = { 1600.0f, -4000.0f, 0.0f };
static Vec3f sSwordQuadOffset0 = { -3000.0f, -2000.0f, 1300.0f };
static Vec3f sSwordQuadOffset3 = { -3000.0f, -2000.0f, -1300.0f };
static Vec3f sSwordQuadOffset2 = { 1000.0f, 1000.0f, 0.0f };

static TexturePtr sEyeTextures[] = {
    gKaizokuEyeOpenTex,
    gKaizokuEyeHalfTex,
    gKaizokuEyeClosedTex,
    gKaizokuEyeHalfTex,
};

void EnKaizoku_Update(Actor* thisx, PlayState* play2) {
    EnKaizoku* this = THIS;
    PlayState* play = play2;

    if (! this->bool2D8) {
        SkelAnime_Update(&this->skelAnime);
    }

    if (this->action != KAIZOKU_ACTION_0) {
        func_80B85900(this);
    }

    DECR (this->blinkTimer);
    DECR (this->timer2B2);
    DECR (this->lookTimer);
    DECR (this->unk_2B6);
    DECR (this->cutsceneTimer);
    DECR (this->colorFilterTimer);

    this->actionFunc(this, play);
    Actor_MoveWithGravity(&this->picto.actor);
    if (this->action != KAIZOKU_ACTION_0) {
        func_80B89A08(this, play);
    }
    if (this->action != KAIZOKU_ACTION_0) {
        Actor_SetFocus(&this->picto.actor, 60.0f);
    }

    Actor_SetScale(&this->picto.actor, 0.0125f);
    if (this->blinkTimer == 0) {
        this->eyeIndex++;
        if (this->eyeIndex >= ARRAY_COUNT(sEyeTextures)) {
            this->eyeIndex = 0;
            this->blinkTimer = Rand_S16Offset(20, 60);
        }
    }

    if (this->picto.actor.bgCheckFlags & BGCHECKFLAG_GROUND) {
        Vec3f sp34;
        s32 pad;

        Matrix_RotateYS(this->picto.actor.shape.rot.y + this->unk_2F4, MTXMODE_NEW);
        Matrix_MultVecZ(this->unk_2F0, &sp34);
        this->picto.actor.world.pos.x += this->unk_3C4.x + sp34.x;
        this->picto.actor.world.pos.z += this->unk_3C4.z + sp34.z;
        Math_ApproachZeroF(&this->unk_3C4.x, 1.0f, 2.0f);
        Math_ApproachZeroF(&this->unk_3C4.z, 1.0f, 2.0f);
        Math_ApproachZeroF(&this->unk_2F0, 1.0f, 5.0f);
    }

    Actor_UpdateBgCheckInfo(play, &this->picto.actor, 35.0f, 40.0f, 35.0f,
                            UPDBGCHECKINFO_FLAG_1 | UPDBGCHECKINFO_FLAG_2 | UPDBGCHECKINFO_FLAG_4 |
                                UPDBGCHECKINFO_FLAG_8 | UPDBGCHECKINFO_FLAG_10);
    Collider_UpdateCylinder(&this->picto.actor, &this->bodyCollider);
    CollisionCheck_SetOC(play, &play->colChkCtx, &this->bodyCollider.base);
    if ((this->unk_2D0 < 2) && (this->action != KAIZOKU_ACTION_0)) {
        CollisionCheck_SetAC(play, &play->colChkCtx, &this->bodyCollider.base);
    }
    if (this->swordState > 0) {
        CollisionCheck_SetAT(play, &play->colChkCtx, &this->swordCollider.base);
    }
}

s32 EnKaizoku_OverrideLimbDraw(PlayState* play, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, Actor* thisx) {
    EnKaizoku* this = THIS;

    OPEN_DISPS(play->state.gfxCtx);

    // disabled because left over from OOT, and dev wanted us to see lipstick
    if (limbIndex == KAIZOKU_LIMB_VEIL) {
        *dList = NULL;
    }

    if (limbIndex == KAIZOKU_LIMB_NECK) {
        rot->z += this->headRot.x;
        rot->x += this->headRot.y;
        rot->y += this->headRot.z;
    } else if (limbIndex == KAIZOKU_LIMB_HEAD) {
        gDPPipeSync(POLY_OPA_DISP++);
        gDPSetEnvColor(POLY_OPA_DISP++, sKaizokuLipstickColors[this->colorType].r, sKaizokuLipstickColors[this->colorType].g,
                       sKaizokuLipstickColors[this->colorType].b, 255);
    } else {
        gDPPipeSync(POLY_OPA_DISP++);
        gDPSetEnvColor(POLY_OPA_DISP++, sKaizokuOutfitColors[this->colorType].r, sKaizokuOutfitColors[this->colorType].g,
                       sKaizokuOutfitColors[this->colorType].b, 255);
    }

    CLOSE_DISPS(play->state.gfxCtx);

    return false;
}

void EnKaizoku_PostLimbDraw(PlayState* play, s32 limbIndex, Gfx** dList, Vec3s* rot, Actor* thisx) {
    Vec3f swordTip;
    Vec3f swordHilt;
    EnKaizoku* this = THIS;

    if (limbIndex == KAIZOKU_LIMB_R_SWORD) {
        Matrix_MultVec3f(&sSwordQuadOffset1, &this->swordCollider.dim.quad[1]);
        Matrix_MultVec3f(&sSwordQuadOffset0, &this->swordCollider.dim.quad[0]);
        Matrix_MultVec3f(&sSwordQuadOffset3, &this->swordCollider.dim.quad[3]);
        Matrix_MultVec3f(&sSwordQuadOffset2, &this->swordCollider.dim.quad[2]);
        Collider_SetQuadVertices(&this->swordCollider, &this->swordCollider.dim.quad[0],
                                 &this->swordCollider.dim.quad[1], &this->swordCollider.dim.quad[2],
                                 &this->swordCollider.dim.quad[3]);
        Matrix_MultVec3f(&sSwordTipOffset, &swordTip);
        Matrix_MultVec3f(&sSwordHiltOffset, &swordHilt);

        if ((this->swordState == 1) && ((this->action == KAIZOKU_ACTION_9) || (this->action == KAIZOKU_ACTION_11))) {
            EffectBlure_AddVertex(Effect_GetByIndex(this->blureIndex), &swordTip, &swordHilt);
        } else if (this->swordState != 0) {
            EffectBlure_AddSpace(Effect_GetByIndex(this->blureIndex));
            this->swordState = 0;
        }
    } else {
        Actor_SetFeetPos(&this->picto.actor, limbIndex, KAIZOKU_LIMB_L_FOOT, &sFootOffset, KAIZOKU_LIMB_R_FOOT,
                         &sFootOffset);
    }

    if (limbIndex == KAIZOKU_LIMB_L_FOOT) {
        Matrix_MultVec3f(&sFootOffset, &this->leftFootPos);
    } else if (limbIndex == KAIZOKU_LIMB_R_FOOT) {
        Matrix_MultVec3f(&sFootOffset, &this->rightFootPos);
    }

   /*
   if ((limbIndex == KAIZOKU_LIMB_02) || (limbIndex == KAIZOKU_LIMB_06) || (limbIndex == KAIZOKU_LIMB_07) ||
        (limbIndex == KAIZOKU_LIMB_08) || (limbIndex == KAIZOKU_LIMB_0A) || (limbIndex == KAIZOKU_LIMB_0C) ||
        (limbIndex == KAIZOKU_LIMB_0D) || (limbIndex == KAIZOKU_LIMB_0F) || (limbIndex == KAIZOKU_LIMB_11) ||
        (limbIndex == KAIZOKU_LIMB_12) || (limbIndex == KAIZOKU_LIMB_L_FOOT) || (limbIndex == KAIZOKU_LIMB_14) ||
        (limbIndex == KAIZOKU_LIMB_15) || (limbIndex == KAIZOKU_LIMB_R_FOOT) || (limbIndex == KAIZOKU_LIMB_17)) {
   // */

    if ((limbIndex == KAIZOKU_LIMB_TORSO) || (limbIndex == KAIZOKU_LIMB_HEAD) || (limbIndex == KAIZOKU_LIMB_R_UPPER_ARM) ||
        (limbIndex == KAIZOKU_LIMB_R_FOREARM) || (limbIndex == KAIZOKU_LIMB_R_HAND) || (limbIndex == KAIZOKU_LIMB_L_UPPER_ARM) ||
        (limbIndex == KAIZOKU_LIMB_L_FOREARM) || (limbIndex == KAIZOKU_LIMB_L_HAND) || (limbIndex == KAIZOKU_LIMB_L_THIGH) ||
        (limbIndex == KAIZOKU_LIMB_L_SHIN) || (limbIndex == KAIZOKU_LIMB_L_FOOT) || (limbIndex == KAIZOKU_LIMB_R_THIGH) ||
        (limbIndex == KAIZOKU_LIMB_R_SHIN) || (limbIndex == KAIZOKU_LIMB_R_FOOT) || (limbIndex == KAIZOKU_LIMB_WAIST)) {

        Matrix_MultZero(&this->bodyPartsPos[this->bodyPartIndex]);
        this->bodyPartIndex++;
        if (this->bodyPartIndex >= KAIZOKU_BODYPART_MAX) {
            this->bodyPartIndex = 0;
        }
    }
}

void EnKaizoku_TransformLimbDraw(PlayState* play, s32 limbIndex, Actor* thisx) {
    EnKaizoku* this = THIS;

    if (limbIndex == KAIZOKU_LIMB_R_SWORD) {
        Matrix_Scale(this->unk_2F8.x, this->unk_2F8.y, this->unk_2F8.z, MTXMODE_APPLY);
    }
    if (limbIndex == KAIZOKU_LIMB_L_SWORD) {
        Matrix_Scale(this->unk_304.x, this->unk_304.y, this->unk_304.z, MTXMODE_APPLY);
    }
}

void EnKaizoku_Draw(Actor* thisx, PlayState* play) {
    f32 pad[4];
    f32 drawDmgEffAlpha;
    EnKaizoku* this = THIS;

    Gfx_SetupDL25_Xlu(play->state.gfxCtx);
    Gfx_SetupDL25_Opa(play->state.gfxCtx);

    OPEN_DISPS(play->state.gfxCtx);

    gSPSegment(POLY_OPA_DISP++, 0x08, SEGMENTED_TO_K0(sEyeTextures[this->eyeIndex]));
    SkelAnime_DrawTransformFlexOpa(play, this->skelAnime.skeleton, this->skelAnime.jointTable,
                                   this->skelAnime.dListCount, EnKaizoku_OverrideLimbDraw, EnKaizoku_PostLimbDraw,
                                   EnKaizoku_TransformLimbDraw, &this->picto.actor);

    if (this->colorFilterTimer != 0) {
        drawDmgEffAlpha = this->colorFilterTimer * 0.05f;

        if ((this->drawDmgEffType == ACTOR_DRAW_DMGEFF_FROZEN_SFX) ||
            (this->drawDmgEffType == ACTOR_DRAW_DMGEFF_FROZEN_NO_SFX)) {
            this->drawDmgEffScale += 0.3f;
            if (this->drawDmgEffScale > 0.5f) {
                this->drawDmgEffScale = 0.5f;
            }
            Math_ApproachF(&this->drawDmgEffFrozenSteamScale, this->drawDmgEffScale, 0.1f, 0.04f);
        } else {
            this->drawDmgEffScale = 0.8f;
            this->drawDmgEffFrozenSteamScale = 0.8f;
        }

        Actor_DrawDamageEffects(play, &this->picto.actor, this->bodyPartsPos, KAIZOKU_BODYPART_MAX,
                                this->drawDmgEffScale, this->drawDmgEffFrozenSteamScale, drawDmgEffAlpha,
                                this->drawDmgEffType);
    }

    CLOSE_DISPS(play->state.gfxCtx);
}
