/*
 * File: z_en_okarina_tag.c
 * Overlay: ovl_En_Okarina_Tag
 * Description:
 */

#include "z_en_okarina_tag.h"

#define FLAGS (ACTOR_FLAG_10 | ACTOR_FLAG_2000000 | ACTOR_FLAG_CANT_LOCK_ON)

#define THIS ((EnOkarinaTag*)thisx)

void EnOkarinaTag_Init(Actor* thisx, PlayState* play);
void EnOkarinaTag_Destroy(Actor* thisx, PlayState* play);
void EnOkarinaTag_Update(Actor* thisx, PlayState* play);

void func_8093E518(EnOkarinaTag* this, PlayState* play);
void func_8093E68C(EnOkarinaTag* this, PlayState* play);

ActorInit En_Okarina_Tag_InitVars = {
    ACTOR_EN_OKARINA_TAG,
    ACTORCAT_SWITCH,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(EnOkarinaTag),
    (ActorFunc)EnOkarinaTag_Init,
    (ActorFunc)EnOkarinaTag_Destroy,
    (ActorFunc)EnOkarinaTag_Update,
    (ActorFunc)NULL,
};

void EnOkarinaTag_Destroy(Actor* thisx, PlayState* play) {
}

void EnOkarinaTag_Init(Actor* thisx, PlayState* play) {
    EnOkarinaTag* this = THIS;
    f32 zRot = 0.0f;
    s32 i = 0;

    this->actor.flags &= ~ACTOR_FLAG_1;
    this->unk148 = ENOKARINATAG_GET_F800(thisx);
    this->unk14A = ENOKARINATAG_GET_780(thisx);
    this->switchFlags = ENOKARINATAG_GET_SWITCHFLAGS(thisx);
    if (this->actor.world.rot.z > 0) {
        zRot = this->actor.world.rot.z;
        while (zRot > 10.0f) {
            zRot -= 10.0f;
            i++;
        }
    }
    this->unk154 = zRot * 50.0f;
    this->unk158 = i * 50.0f;
    if (this->switchFlags == 0x7F) {
        this->switchFlags = -1;
    }
    if (this->unk14A == 0xF) {
        this->unk14A = -1;
    }
    this->actor.targetMode = 1;
    this->actionFunc = func_8093E518;
}

void func_8093E518(EnOkarinaTag* this, PlayState* play) {
    f32 xzRange;
    f32 yRange;
    s16 yDiff;
    u16 var_v1;

    if (this->switchFlags >= 0) {
        if (this->unk148 == 0) {
            if (Flags_GetSwitch(play, this->switchFlags)) {
                return;
            }
        }
        if (this->unk148 == 1) {
            if (!Flags_GetSwitch(play, this->switchFlags)) {
                return;
            }
        }
    }
    var_v1 = this->unk14A;
    if (var_v1 == 6) {
        var_v1 = 0xA;
        if (gSaveContext.save.saveInfo.unk_F41 == 0) {
            return;
        }
    }
    if (this->unk14A == -1) {
        var_v1 = 0;
    }
    if (func_800B8718(&this->actor, &play->state)) {
        func_80152434(play, var_v1 + 0x29);
        this->actionFunc = func_8093E68C;
    } else {
        yDiff = ABS_ALT((s16)(this->actor.yawTowardsPlayer - this->actor.world.rot.y));
        if (yDiff >= 0x4300) {
            this->unk150 = 0;
            return;
        }
        xzRange = this->unk154;
        this->unk150 = 1;
        if (xzRange == 0.0f) {
            xzRange = 50000.0f;
        }
        yRange = this->unk158;
        if (yRange == 0.0f) {
            yRange = 50000.0f;
        }
        func_800B874C(&this->actor, play, xzRange, yRange);
    }
}

void func_8093E68C(EnOkarinaTag* this, PlayState* play) {
    if (play->msgCtx.ocarinaMode == 4) {
        this->actionFunc = func_8093E518;
    } else {
        if ((play->msgCtx.ocarinaMode == 3) ||
            ((this->unk14A == -1) &&
             ((play->msgCtx.ocarinaMode == 5) || (play->msgCtx.ocarinaMode == 6) || (play->msgCtx.ocarinaMode == 7) ||
              (play->msgCtx.ocarinaMode == 8) || (play->msgCtx.ocarinaMode == 0xA) || (play->msgCtx.ocarinaMode == 9) ||
              (play->msgCtx.ocarinaMode == 0xF)))) {
            if (this->switchFlags >= 0) {
                switch (this->unk148) {
                    case 0:
                        Flags_SetSwitch(play, this->switchFlags);
                        break;
                    case 1:
                        Flags_UnsetSwitch(play, this->switchFlags);
                        break;
                    case 2:
                        if (Flags_GetSwitch(play, this->switchFlags)) {
                            Flags_UnsetSwitch(play, this->switchFlags);
                        } else {
                            Flags_SetSwitch(play, this->switchFlags);
                        }
                        break;
                }
            }
            play->msgCtx.ocarinaMode = 4;
            Audio_PlaySfx(NA_SE_SY_CORRECT_CHIME);
            this->actionFunc = func_8093E518;
        }
    }
}

void EnOkarinaTag_Update(Actor* thisx, PlayState* play) {
    EnOkarinaTag* this = THIS;

    this->actionFunc(this, play);
}
