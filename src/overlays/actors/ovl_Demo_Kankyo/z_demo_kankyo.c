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

/*
const ActorInit Demo_Kankyo_InitVars = {
    ACTOR_DEMO_KANKYO,
    ACTORCAT_ITEMACTION,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(DemoKankyo),
    (ActorFunc)DemoKankyo_Init,
    (ActorFunc)DemoKankyo_Destroy,
    (ActorFunc)DemoKankyo_Update,
    (ActorFunc)DemoKankyo_Draw
};
*/

void func_808CE450(DemoKankyo* this, DemoKankyoActionFunc func) {
    this->actionFunc = func;
}

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Demo_Kankyo_0x808CE450/func_808CE45C.asm")

void func_808CF06C(DemoKankyo *this, GlobalContext *globalCtx) {
    if (Scene_IsObjectLoaded(&globalCtx->sceneContext, this->unk1648) != 0) {
        this->unk164C[0] = 1;
        this->actor.objBankIndex = (s8) this->unk1648;
        func_808CE450(this, func_808CF0CC);
    }
}

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Demo_Kankyo_0x808CE450/func_808CF0CC.asm")


#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Demo_Kankyo_0x808CE450/DemoKankyo_Init.asm")

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
