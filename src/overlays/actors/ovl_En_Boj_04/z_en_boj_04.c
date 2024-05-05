/*
 * File: z_en_boj_04.c
 * Overlay: ovl_En_Boj_04
 * Description: in vanilla this was empty, now I want to turn it into our "grotto actor placer" actor
 */

#include "z_en_boj_04.h"

#define FLAGS 0x0

#define THIS ((EnBoj04*)thisx)

void EnBoj04_Init(Actor* thisx, PlayState* play);
void EnBoj04_Destroy(Actor* thisx, PlayState* play);
void EnBoj04_Update(Actor* thisx, PlayState* play);
void EnBoj04_Draw(Actor* thisx, PlayState* play);

ActorInit En_Boj_04_InitVars = {
    /**/ ACTOR_EN_BOJ_04,
    /**/ ACTORCAT_PROP,
    /**/ FLAGS,
    /**/ GAMEPLAY_KEEP,
    /**/ sizeof(EnBoj04),
    /**/ EnBoj04_Init,
    /**/ EnBoj04_Destroy,
    /**/ EnBoj04_Update,
    /**/ EnBoj04_Draw, // draw func n/a
    // NULL, // draw func n/a
};

typedef struct ActorCombo{
  u16 actorId;
  u16 params;
} ActorCombo;

typedef struct GrottoCombo {
  ActorCombo left;
  ActorCombo center;
  ActorCombo right;
} GrottoCombo;

// going to need a way to map this data to the entrance, torch does this too but only for 8 items and we have a least 10 grottos
// two in TF: pillar and grass
// mystery woods and outside of ssh
// behind fishermans hut and cape boulder

static GrottoCombo grottoActorPlacemenetData[] = {
 { {10, 0}, {0, 0}, {0, 0}   }, // 1  tf grass (3F)
 { {10, 0}, {0, 0}, {0, 0}   }, // 2  tf pillar (9A)
 { {10, 0}, {0, 0}, {0, 0}   }, // 3  road to south tree (3E)
 { {10, 0}, {0, 0}, {0, 0}   }, // 4  woods of mystery ()
 { {10, 0}, {0, 0}, {0, 0}   }, // 5  swamp spiderhouse
 { {10, 0}, {0, 0}, {0, 0}   }, // 6  racetrack grotto
 { {10, 0}, {0, 0}, {0, 0}   }, // 7  road to snowhead
 { {10, 0}, {0, 0}, {0, 0}   }, // 8  tunnel to goron grave
 { {10, 0}, {0, 0}, {0, 0}   }, // 9  fishermans hut (37)
 { {10, 0}, {0, 0}, {0, 0}   }, // 10 zora cape rock (95)
 { {10, 0}, {0, 0}, {0, 0}   }, // 11 road to ikana
 { {10, 0}, {0, 0}, {0, 0}   }, // 12 graveyard
 { {10, 0}, {0, 0}, {0, 0}   }  // 13 secret shrine

};

// struct of ActorCombos structs per grotto

// struct of objects per grotto
static int GrottoComboObjects[] = {
  101, //  01
  102, //  02
  103, //  03
  104, //  04
  105, //  05
  106, //  06
  107, //  07
  108, //  08
  109, //  09
  110, //  10
  111, //  11
  112, //  12
  113  //  13
};

// grotto passes this actor an itemId, we can use that to identify what items we have,
// do we need an itemId map to grottoId map?

void EnBoj04_Init(Actor* thisx, PlayState* play) {
  EnBoj04* this = THIS;
 
  // first, we need to figure out where we are, which grotto is this?
  // this is what enTorch has to work with to spawn the correct chest for a given grotto, rando leaves 0x1F data vanilla so we can keep using that
  GROTTO_SPAWNER_GROTTO_DATA(thisx) = gSaveContext.respawn[RESPAWN_MODE_UNK_3].data & 0x1F;

  // first we need to load the object, for now let's assume there is only one type of enemy per grotto so one object for al

  // load the object for the grotto
  GROTTO_SPAWNER_OBJ_ID(thisx) = 0x17; // dinofos, testing

  // this does not work, we CANNOT start an object from within our actor with this function, need to use rando's object heap
  //Object_SpawnPersistent(&play->objectCtx, GROTTO_SPAWNER_OBJ_ID(thisx));
  // I thought I could just replace this function, but the rando function takes a pointer to the heap not to the object context
  //Object_SpawnPersistent(&play->objectCtx, GROTTO_SPAWNER_OBJ_ID(thisx));
  // instead I need a different function that takes only the int, I added one on rando side just need to use one on decomp side
  Actor_GetArrowDmgFlags(GROTTO_SPAWNER_OBJ_ID(thisx));

  //this->actionFunc // we dont need an actionfunc we can just do our work in update
}

void EnBoj04_Destroy(Actor* thisx, PlayState* play) {
}

void EnBoj04_Update(Actor* thisx, PlayState* play) {
  EnBoj04* this = THIS;

  // if object is loaded, spawn actor
  //if (Object_IsLoaded(&play->objectCtx, &GROTTO_SPAWNER_OBJ_ID(thisx))){
  if (Object_IsLoaded(&play->objectCtx, GROTTO_SPAWNER_OBJ_ID(thisx))){

    Actor_Spawn(&play->actorCtx, play,
                ACTOR_EN_DINOFOS,
                this->actor.world.pos.x, this->actor.world.pos.y, this->actor.world.pos.z,
                this->actor.shape.rot.x, this->actor.shape.rot.y, this->actor.shape.rot.z,
                0x0000); // params
                //ENBOX_PARAMS(ENBOX_TYPE_SMALL, sChestContents[(returnData >> 0x5) & 0x7], returnData));

    //Actor_Kill(&this);
    thisx->update = Actor_Noop; // debugging, leave it drawing but not doing anything after we get there so we can see some debug data
  }
}
void Debug_PrintToScreen(Actor* thisx, PlayState* play) {
    //ObjBean* this = THIS; // replace with THIS actor
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
        //void* actionFuncAddr = this->actionFunc;
        //u32 convertedAddr = (u32) Fault_ConvertAddress(actionFuncAddr);
        GfxPrint_SetPos(&printer, 1, 11);
        //GfxPrint_Printf(&printer, "actionfunc vram:        func_%X", convertedAddr);
        GfxPrint_Printf(&printer, "grotto data:      %X", GROTTO_SPAWNER_GROTTO_DATA(thisx));

        //GfxPrint_SetPos(&printer, 1, 12);
        //GfxPrint_Printf(&printer, "grotto data:      %X", GROTTO_SPAWNER_GROTTO_DATA(thisx));
    }

    //GfxPrint_SetPos(&printer, 1, 13);
    //GfxPrint_Printf(&printer, "drawflags %X", this->drawFlags);
    //GfxPrint_Printf(&printer, "BREG86 %X", BREG(86));
    //GfxPrint_Printf(&printer, "mesgState %X", Message_GetState(&play->msgCtx));

    // end of text printing
    gfx = GfxPrint_Close(&printer);
    GfxPrint_Destroy(&printer);

    gSPEndDisplayList(gfx++);
    // make the opa dlist jump over the part that will be executed as part of overlay
    gSPBranchList(POLY_OPA_DISP, gfx);
    POLY_OPA_DISP = gfx;

    CLOSE_DISPS(play->state.gfxCtx);
    //if (BREG(86)) 
    //  Debug_PrintToScreen(thisx, play); // put this in your actors draw func
} // */

void EnBoj04_Draw(Actor* thisx, PlayState* play){
    EnBoj04* this = THIS;

    Debug_PrintToScreen(thisx, play); // put this in your actors draw func
}

