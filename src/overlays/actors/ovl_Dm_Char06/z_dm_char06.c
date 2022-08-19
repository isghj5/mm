/*
 * File: z_dm_char06.c
 * Overlay: ovl_Dm_Char06
 * Description: Mountain Village Snowy landscape fadeout in post-Snowhead thawing cutscene
 */

#include "z_dm_char06.h"

#define FLAGS (ACTOR_FLAG_10 | ACTOR_FLAG_20)

#define THIS ((DmChar06*)thisx)

void DmChar06_Init(Actor* thisx, PlayState* play);
void DmChar06_Destroy(Actor* thisx, PlayState* play);
void DmChar06_Update(Actor* thisx, PlayState* play);
void DmChar06_Draw(Actor* thisx, PlayState* play);

void DmChar06_SetupAction(DmChar06* this, DmChar06ActionFunc actionFunc);
void func_80AAE6F0(DmChar06* this, PlayState* play);

const ActorInit Dm_Char06_InitVars = {
    ACTOR_DM_CHAR06,
    ACTORCAT_ITEMACTION,
    FLAGS,
    OBJECT_YUKIYAMA,
    sizeof(DmChar06),
    (ActorFunc)DmChar06_Init,
    (ActorFunc)DmChar06_Destroy,
    (ActorFunc)DmChar06_Update,
    (ActorFunc)DmChar06_Draw,
};

void DmChar06_SetupAction(DmChar06* this, DmChar06ActionFunc actionFunc) {
    this->actionFunc = actionFunc;
}

void DmChar06_Init(Actor* thisx, PlayState* play) {
    DmChar06* this = THIS;

    gSaveContext.save.weekEventReg[33] |= 0x80;
    Actor_SetScale(&this->actor, 1.0f);
    this->alpha = 255;
    DmChar06_SetupAction(this, func_80AAE6F0);
}

void DmChar06_Destroy(Actor* thisx, PlayState* play) {
}

void func_80AAE6F0(DmChar06* this, PlayState* play) {
    if (Cutscene_CheckActorAction(play, 0x1CF)) {
        s32 actionIndex = Cutscene_GetActorActionIndex(play, 0x1CF);

        if ((play->csCtx.frames >= play->csCtx.actorActions[actionIndex]->startFrame) &&
            (play->csCtx.actorActions[actionIndex]->endFrame >= play->csCtx.frames)) {
            if (play->csCtx.actorActions[actionIndex]->action == 1) {
                this->alpha = 255;
            } else if (play->csCtx.actorActions[actionIndex]->action == 2) {
                f32 lerp = 1.0f - Environment_LerpWeight(play->csCtx.actorActions[actionIndex]->endFrame,
                                                         play->csCtx.actorActions[actionIndex]->startFrame,
                                                         play->csCtx.frames);
                this->alpha = 255 * lerp;
            }
        }
    }
}

void DmChar06_Update(Actor* thisx, PlayState* play) {
    DmChar06* this = THIS;

    this->actionFunc(this, play);
}

void DmChar06_Draw(Actor* thisx, PlayState* play) {
    s32 pad;
    DmChar06* this = THIS;

    AnimatedMat_Draw(play, Lib_SegmentedToVirtual(object_yukiyama_Matanimheader_006868));

    OPEN_DISPS(play->state.gfxCtx);

    func_8012C2DC(play->state.gfxCtx);
    Scene_SetRenderModeXlu(play, 1, 2);
    gDPPipeSync(POLY_XLU_DISP++);
    gDPSetEnvColor(POLY_XLU_DISP++, 0, 0, 0, this->alpha);
    gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(POLY_XLU_DISP++, object_yukiyama_DL_0013A8);

    CLOSE_DISPS(play->state.gfxCtx);
}
