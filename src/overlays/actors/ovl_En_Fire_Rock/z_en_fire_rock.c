#include "z_en_fire_rock.h"

#define FLAGS 0x00000030

#define THIS ((EnFireRock*)thisx)

void EnFireRock_Init(Actor* thisx, GlobalContext* globalCtx);
void EnFireRock_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnFireRock_Update(Actor* thisx, GlobalContext* globalCtx);
void EnFireRock_Draw(Actor* thisx, GlobalContext* globalCtx);

const ActorInit En_Fire_Rock_InitVars = {
    ACTOR_EN_FIRE_ROCK,
    ACTORCAT_ENEMY,
    FLAGS,
    OBJECT_EFC_STAR_FIELD,
    sizeof(EnFireRock),
    (ActorFunc)EnFireRock_Init,
    (ActorFunc)EnFireRock_Destroy,
    (ActorFunc)EnFireRock_Update,
    (ActorFunc)EnFireRock_Draw,
};

void EnFireRock_Init(Actor* thisx, GlobalContext* globalCtx) {
}
void EnFireRock_Destroy(Actor* thisx, GlobalContext* globalCtx) {
}
void EnFireRock_Update(Actor* thisx, GlobalContext* globalCtx) {
}
void EnFireRock_Draw(Actor* thisx, GlobalContext* globalCtx) {
}
