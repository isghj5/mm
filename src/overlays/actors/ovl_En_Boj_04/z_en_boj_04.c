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
    /**/ //EnBoj04_Update,
    /**/ NULL,
    /**/ EnBoj04_Draw, // debugging
    /**/ //NULL, // we dont need to draw anything
    // NULL, // draw func n/a
};

typedef struct ActorCombo{
  u16 actorId;
  u16 params;
} ActorCombo;

typedef struct GrottoCombo {
    ActorCombo actors[3]; // the three dekubaba
} GrottoCombo;

// each grotto gets data for the chest, we need to map them to each area so we can index everything
static GrottoIdIndexMap [] = {
 1, // 1  tf grass (3F)
 2, // 2  tf pillar (9A)
 3, // 3  road to south tree (3E)
 4, // 4  woods of mystery ()
 5, // 5  swamp spiderhouse
 6, // 6  racetrack grotto
 7, // 7  road to snowhead
 8, // 8  tunnel to goron grave
 9, // 9  fishermans hut (37)
 10, // 10 zora cape rock (95)
 11, // 11 road to ikana
 12, // 12 graveyard
 13, // 13 secret shrine
};


// going to need a way to map this data to the entrance, torch does this too but only for 8 items and we have a least 10 grottos
// 13 generic grottos:

static GrottoCombo grottoDekuBabaPlacementData[13] = {
//static ActorCombo grottoDekuBabaPlacementData[][] = {
 {{ {10, 0}, {0, 0}, {0, 0}   }}, // 1  tf grass (3F)
 {{ {10, 0}, {0, 0}, {0, 0}   }}, // 2  tf pillar (9A)
 {{ {10, 0}, {0, 0}, {0, 0}   }}, // 3  road to south tree (3E)
 {{ {10, 0}, {0, 0}, {0, 0}   }}, // 4  woods of mystery ()
 {{ {10, 0}, {0, 0}, {0, 0}   }}, // 5  swamp spiderhouse
 {{ {10, 0}, {0, 0}, {0, 0}   }}, // 6  racetrack grotto
 {{ {10, 0}, {0, 0}, {0, 0}   }}, // 7  road to snowhead
 {{ {10, 0}, {0, 0}, {0, 0}   }}, // 8  tunnel to goron grave
 {{ {10, 0}, {0, 0}, {0, 0}   }}, // 9  fishermans hut (37)
 {{ {10, 0}, {0, 0}, {0, 0}   }}, // 10 zora cape rock (95)
 {{ {10, 0}, {0, 0}, {0, 0}   }}, // 11 road to ikana
 {{ {10, 0}, {0, 0}, {0, 0}   }}, // 12 graveyard
 {{ {10, 0}, {0, 0}, {0, 0}   }}  // 13 secret shrine
};

// for actorizer, we want to randomize the grass too
// except, I dont want highly specific data for every single grass/beetle spawn in every grotto, too much data
// instead, lets just make a shorter array that we randomly access, filled with common stuff
// so far, we have butterflies, grottos, water, rocks, bushes(trees), bushes()
static GrottoCombo grottoGrassSpawnData[] = {
     //{ACTOR_EN_KUSA2, 0x0400} // keaton grass without the object could be funny? maybe not if people expect fox
    {ACTOR_EN_BUTTE, 0},
    {ACTOR_EN_BUTTE, 1},
    {ACTOR_EN_BUTTE, 2},

    {ACTOR_EN_KUSA, 0x0D00}, // all magic
    {ACTOR_EN_KUSA, 0x0E00}, // flexible
    {ACTOR_EN_KUSA, 0x0601}, // flexible
    {ACTOR_EN_KUSA, 0x0601}, // flexible
    {ACTOR_EN_KUSA, 0x0000}, // flexible tf
    {ACTOR_EN_KUSA, 0x0110}, // flexible swamp
    {ACTOR_EN_KUSA, 0x0210}, // mountain village
    {ACTOR_EN_KUSA, 0x0310}, // unused
    {ACTOR_EN_KUSA, 0x0B10}, // bombs?
    {ACTOR_EN_KUSA, 0x0B10}, // bombs?
    {ACTOR_EN_KUSA, 0x0F10}, // full mixeds

    // reminder FE is required for no collector flag
    {ACTOR_EN_ISHI, 0xFE91}, // coast silver boulder but drops money, lets call it a geo
    {ACTOR_EN_ISHI, 0xFEF0}, // small rock with lots of stuff in it
    {ACTOR_EN_ISHI, 0xFE20}, // small rock with spring mountains
    {ACTOR_EN_ISHI, 0xFEB0}, // bombs?
     
    {ACTOR_DOOR_ANA, 0x6233}, // grotto, dynamically load the replacement params if its a grotto, since we need to update Zrot too
    {ACTOR_DOOR_ANA, 0x0}, 
};

static u16 grottoParameters[] = {
    0x6033, // 60XX are item grottos
    0x603B,
    0x6018,
    0x605C, 

    0x0, 0x2000, 0x3000, 0x4000, // gossip grottos

    0x8000, // secret japaneese grottos
    0xA000, 

    0x7000, // other regular grottos, dont remember which is which
    0xC000, 
    0xE000, 
    0xF000,
    0xD000
};


// grotto passes this actor an itemId, we can use that to identify what items we have,
// do we need an itemId map to grottoId map?

void EnBoj04_Init(Actor* thisx, PlayState* play) {
  EnBoj04* this = THIS;
  //u16 actorId;
  //u16 actorParams;
 
  GrottoCombo* thisCombo = NULL;

  // TODO we need to find a way to turn the grotto spawn data into a linear array index
  thisCombo = &grottoDekuBabaPlacementData[GROTTO_SPAWNER_GROTTO_DATA(thisx)];

  // first, we need to figure out where we are, which grotto is this?
  // this is what enTorch has to work with to spawn the correct chest for a given grotto, 
  //  rando leaves 0x1F data vanilla so we can keep using that
  //GROTTO_SPAWNER_GROTTO_DATA(thisx) = gSaveContext.respawn[RESPAWN_MODE_UNK_3].data & 0x1F;

  // if the param is 0x0001/2/3, then its a dekubaba, look up params from the table and use those
  if (thisx->params & 0x8000) // grass
  {
      
      // chance of spawning a regular list actor, not a generic actor

      // figure out which one of the actor/param combos we want

      // if its a grotto, re-get more seeded randomized values for the grotto params instead of using the actual data

      // if butterfly, raise height
  }
  else // dekubaba
  {
     u8 babaId = thisx->params & 0xF;
     GROTTO_SPAWNER_ACTORID(thisx) = thisCombo->actors[babaId].actorId;
     GROTTO_SPAWNER_PARAMS(thisx) = thisCombo->actors[babaId].params;
  }

  Actor_Spawn(&play->actorCtx, play,
                //ACTOR_EN_DINOFOS,
                GROTTO_SPAWNER_ACTORID(thisx),
                this->actor.world.pos.x, this->actor.world.pos.y, this->actor.world.pos.z,
                this->actor.shape.rot.x, this->actor.shape.rot.y, this->actor.shape.rot.z,
                GROTTO_SPAWNER_PARAMS(thisx)); // debugging with dinofos
                //ENBOX_PARAMS(ENBOX_TYPE_SMALL, sChestContents[(returnData >> 0x5) & 0x7], returnData));

  //Actor_Kill(&this); // disabled to debug test keep the actor drawing 
}

void EnBoj04_Destroy(Actor* thisx, PlayState* play) {
}

/*
void EnBoj04_Update(Actor* thisx, PlayState* play) {
  EnBoj04* this = THIS;

  // if object is loaded, spawn actor
  //if (Object_IsLoaded(&play->objectCtx, &GROTTO_SPAWNER_OBJ_ID(thisx))){
  if (Object_IsLoaded(&play->objectCtx, GROTTO_SPAWNER_OBJ_ID(thisx))){

  }
}
// */
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
        GfxPrint_SetPos(&printer, 1, 12);
        GfxPrint_Printf(&printer, "grotto actorid:      %X", GROTTO_SPAWNER_ACTORID(thisx));
        GfxPrint_SetPos(&printer, 1, 13);
        GfxPrint_Printf(&printer, "grotto actor params:      %X", GROTTO_SPAWNER_PARAMS(thisx));
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

