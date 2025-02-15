/*
 * File: z_en_boj_04.c
 * Overlay: ovl_En_Boj_04
 * Description: in vanilla this was empty, now I want to turn it into our "grotto actor placer" actor
 */

#include "z_en_boj_04.h"
#include "build.h"

#define FLAGS 0x0

#define THIS ((EnBoj04*)thisx)

void EnBoj04_Init(Actor* thisx, PlayState* play);
void EnBoj04_Destroy(Actor* thisx, PlayState* play);
void EnBoj04_Update(Actor* thisx, PlayState* play);
void EnBoj04_Draw(Actor* thisx, PlayState* play);

void GS_SpawnReplacement(Actor* thisx, PlayState* play);
void GS_ChooseGeneric(Actor* thisx, PlayState* play);
void GS_AssignReplacementParameters(Actor* thisx, u32 roomIndex, u32 babaIndex);

ActorInit En_Boj_04_InitVars = {
    /**/ ACTOR_EN_BOJ_04,
    /**/ ACTORCAT_PROP,
    /**/ FLAGS,
    /**/ GAMEPLAY_KEEP,
    /**/ sizeof(EnBoj04),
    /**/ EnBoj04_Init,
    /**/ EnBoj04_Destroy,
    /**/ //EnBoj04_Update,
    ///**/ NULL,
    /**/ Actor_Noop, // Update: NULL, if we make it actually null it wont draw for debug and might do nothing else eitehr
    /**/ EnBoj04_Draw, // Draw: debugging
    /**/ //NULL, // we dont need to draw anything
    // NULL, // draw func n/a
};

// for actorizer, we want to randomize the grass too
// except, I dont want highly specific data for every single grass/beetle spawn in every grotto, too much data
// instead, lets just make a shorter array that we randomly access, filled with common stuff
// so far, we have butterflies, grottos, water, rocks, bushes(trees), bushes()
static ActorCombo grottoGrassSpawnData[] = {
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

// what parameters for grottos are acceptable
// we want some variety, but we dont want to increase chances of spawning in the list
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

static s16 ourLocation = -1;
static u32 ourSeed = -1;
void GS_GetOurLocation(u16 grottoData); // get location from grotto data
void GS_GetOurSeed(u16 grottoData); // get location from grotto data

// each grotto gets data for the chest, we need to map them to each area so we can index everything
// we dont need this anymore, its here for reference or in case I was wrong
/* static u8 GrottoIdIndexMap [] = { // the number on the right is chronological order
 0x13, // 7  road to snowhead 
 0x14, // 13 secret shrine (B4)
 0x15, // 10 zora cape rock (95)
 0x16, // 11 road to ikana (96)
 0x17, // 9  fishermans hut (37)
 0x18, // 12 graveyard 
 0x19, // 6  goron racetrack grotto
 0x1A, // 2  tf pillar (9A)
 0x1B, // 8  tunnel to goron grave (3B)
 0x1C, // 4  woods of mystery (5C)
 0x1D, // 5  swamp spiderhouse (3D)
 0x1E, // 3  road to south tree (3E)
 0x1F, // 1  tf grass (3F)
}; // */

// going to need a way to map this data to the entrance, torch does this too but only for 8 items and we have a least 10 grottos
// 13 generic grottos: the order matches the item param of the grotto hole
// default clay pot params 101 for testing
static GrottoCombo grottoDekuBabaPlacementData[13] = {
//static ActorCombo grottoDekuBabaPlacementData[][] = {
 {{ {0x82, 0x101}, {0x82, 0x101}, {0x82, 0x101} }}, // 0 road to snowhead
 {{ {0x82, 0x101}, {0x82, 0x101}, {0x82, 0x101} }}, // 1 secret shrine
 {{ {0x82, 0x101}, {0x82, 0x101}, {0x82, 0x101} }}, // 2 zora cape rock (95)
 {{ {0x82, 0x101}, {0x82, 0x101}, {0x82, 0x101} }}, // 3 road to ikana
 {{ {0x82, 0x101}, {0x82, 0x101}, {0x82, 0x101} }}, // 4 fishermans hut (37)
 {{ {0x82, 0x101}, {0x82, 0x101}, {0x82, 0x101} }}, // 5 Ikana graveyard
 {{ {0x82, 0x101}, {0x82, 0x101}, {0x82, 0x101} }}, // 6 Goron racetrack grotto
 {{ {0x82, 0x101}, {0x82, 0x101}, {0x82, 0x101} }}, // 7 tf pillar (9A)
 {{ {0x82, 0x101}, {0x82, 0x101}, {0x82, 0x101} }}, // 8 goron grave (spring) tunnel
 {{ {0x82, 0x101}, {0x82, 0x101}, {0x82, 0x101} }}, // 9 woods of mystery ()
 {{ {0x82, 0x101}, {0x82, 0x101}, {0x82, 0x101} }}, // A swamp spiderhouse
 {{ {0x82, 0x101}, {0x82, 0x101}, {0x82, 0x101} }}, // B road to south tree (3E)
 {{ {0x82, 0x101}, {0x82, 0x101}, {0x82, 0x101} }}  // C tf grass (3F)
}; // where 0x82 should be clay pot

void EnBoj04_Init(Actor* thisx, PlayState* play) {
  EnBoj04* this = THIS;
  GrottoCombo* thisCombo = NULL;


  // first, we need to figure out where we are, which grotto is this?
  // this is what enTorch has to work with to spawn the correct chest for a given grotto, 
  //  rando leaves 0x1F data vanilla so we can keep using that

  // if the static value is already loaded, use that
  if (ourLocation == -1){
      // the value we get from the save context is range 13-1F, sequential, we can just reduce
      s16 temp = (gSaveContext.respawn[RESPAWN_MODE_UNK_3].data & 0x1F) - 0x13;
      if (temp < 0)
         temp = 0;
      ourLocation = temp;
  } // else: we are the first actor, look up the value from the array

  if (ourSeed == -1){
      GS_GetOurSeed(GROTTO_SPAWNER_GROTTO_DATA(thisx));
  } // else: previous actor in this room already loaded it, reuse

  // we dont really need this anymore, we can get ourLocation
  // DEBUGGING
  //GROTTO_SPAWNER_GROTTO_DATA(thisx) = gSaveContext.respawn[RESPAWN_MODE_UNK_3].data & 0x1F;

  // if the param is 0x0001/2/3, then its a dekubaba, look up params from the table and use those
  if (thisx->params & 0x8000) // grass
  {
      GS_ChooseGeneric(thisx, play); 
  }
  else // dekubaba
  {
      GS_AssignReplacementParameters(thisx, ourLocation, (thisx->params & 0xF));

  }

  GS_SpawnReplacement(thisx, play); 

}

void GS_AssignReplacementParameters(Actor* thisx, u32 roomIndex, u32 babaIndex){

      GrottoCombo* thisCombo = &grottoDekuBabaPlacementData[roomIndex];
      GROTTO_SPAWNER_ACTORID(thisx) = thisCombo->actors[babaIndex].actorId;
      GROTTO_SPAWNER_PARAMS(thisx) = thisCombo->actors[babaIndex].params;
}

void GS_ChooseGeneric(Actor* thisx, PlayState* play) {
      u32 spawnMarker = thisx->params & 0xFFF;
      u32 seedStarter = (ourSeed & 0xFFFFFF);

      u32 randomRoll = ourSeed & 0xDEADBEEF % 100;

      if (randomRoll < 25){         // 10% and 25 merged
          // chance to roll a random actor from a different grotto group
          u32 chosenRoom = (randomRoll < 10) ? (ourLocation + ((ourSeed >> 4) & 0xFFFFFF) % 13) : (ourLocation);
        
          // chance to roll an actor from this grotto group
          u32 chosenSpawn = spawnMarker + seedStarter % 3;
          GS_AssignReplacementParameters(thisx, chosenRoom, chosenSpawn);

      } else {                      // 75%
          // spawn generic actor from generic list 
          u32 chosenSpawn = spawnMarker + seedStarter % sizeof(grottoGrassSpawnData);
          ActorCombo* thisCombo = &grottoGrassSpawnData[chosenSpawn];

          GROTTO_SPAWNER_ACTORID(thisx) = thisCombo->actorId;
          GROTTO_SPAWNER_PARAMS(thisx) = thisCombo->params;

          // if butterfly, raise height
          if (GROTTO_SPAWNER_ACTORID(thisx) == ACTOR_EN_BUTTE){
              thisx->world.pos.y += 100;     
          }
      }

      // if grotto, we need to re-roll for what the door parameters will be
      if (GROTTO_SPAWNER_ACTORID(thisx) == ACTOR_DOOR_ANA){
        u32 chosenGrottoParams = spawnMarker + seedStarter % sizeof(grottoParameters);
        GROTTO_SPAWNER_PARAMS(thisx) = grottoParameters[chosenGrottoParams];
          
      }


}

void GS_SpawnReplacement(Actor* thisx, PlayState* play) {

  Actor_Spawn(&play->actorCtx, play,
                //ACTOR_EN_DINOFOS,
                GROTTO_SPAWNER_ACTORID(thisx),
                thisx->world.pos.x, thisx->world.pos.y, thisx->world.pos.z,
                thisx->shape.rot.x, thisx->shape.rot.y, thisx->shape.rot.z,
                GROTTO_SPAWNER_PARAMS(thisx)); // debugging with dinofos
                //ENBOX_PARAMS(ENBOX_TYPE_SMALL, sChestContents[(returnData >> 0x5) & 0x7],
                    // returnData));

  //Actor_Kill(&this); // disabled to debug test keep the actor drawing 
  thisx->update = Actor_Noop;
}


void EnBoj04_Destroy(Actor* thisx, PlayState* play) { }

// grotto passes this actor an itemId, we can use that to identify what items we have,
// left here, but we just reordered the grotto order by flags which are sequential
/*
void GS_GetOurLocation(u16 grottoData){
  u16 i;

  for(i = 0; i < sizeof(GrottoIdIndexMap); i++) {
    if (grottoData == GrottoIdIndexMap[i]){
      ourLocation = i;
    }
  }
  if (ourLocation == -1) 
    ourLocation = 1; 
} // */

u32 GS_GetBuildDateChkSum(){
    u32 buildCksum = 0;
    u8 i = 0;
    //for (i = 0; i < sizeof(gBuildDate); i++){ // not known at build time, C cannot know this size yet
    for (i = 0; i < 17; i++){
        buildCksum += gBuildDate[i];
    }
    return buildCksum;
}

// maybe needlessly expensive seed converter
void GS_GetOurSeed(u16 grottoData){

    // generate the seed value from seed data
    // for now, just use the vanilla games randomized save values
    u32 seed = 0;
    
    {
      // the code is an array of 5 bytes, lets just read as is for the first four bytes
      seed +=  *(u32 *)gSaveContext.save.saveInfo.bomberCode; 
      seed *=  gSaveContext.save.saveInfo.bomberCode[4]; // last digit is multiplier
      // value max should be below 0x140F,0A05 from this
    }
    
    seed += (gSaveContext.save.saveInfo.checksum & 0xFFFFFFF);
 
    {
      u32 spiderhouseTemp = gSaveContext.save.saveInfo.spiderHouseMaskOrder[0] * gSaveContext.save.saveInfo.spiderHouseMaskOrder[1] + gSaveContext.save.saveInfo.spiderHouseMaskOrder[2];
      spiderhouseTemp += gSaveContext.save.saveInfo.spiderHouseMaskOrder[3] * gSaveContext.save.saveInfo.spiderHouseMaskOrder[4] + gSaveContext.save.saveInfo.spiderHouseMaskOrder[5]; 
      seed += spiderhouseTemp << 4;
    }
    
    {
      u32 lotteryTemp = gSaveContext.save.saveInfo.lotteryCodes[0][1] + gSaveContext.save.saveInfo.lotteryCodes[0][2] * gSaveContext.save.saveInfo.lotteryCodes[0][3]; 
      lotteryTemp += gSaveContext.save.saveInfo.lotteryCodes[1][1] * gSaveContext.save.saveInfo.lotteryCodes[1][2] * gSaveContext.save.saveInfo.lotteryCodes[1][3]; 
      lotteryTemp += gSaveContext.save.saveInfo.lotteryCodes[2][1] * gSaveContext.save.saveInfo.lotteryCodes[2][2] + gSaveContext.save.saveInfo.lotteryCodes[2][3]; 
      seed += lotteryTemp << 2;
    }

    // however, not only do I want this seed based, 
    //  I want this build-based too so its not always the same on my debug seed
    seed += GS_GetBuildDateChkSum();

    ourSeed = seed;

}

// we dont need this as an actor spawner
/*
void EnBoj04_Update(Actor* thisx, PlayState* play) {
  EnBoj04* this = THIS;
}
// */

// debug print while I try to figure out if this is working
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
        GfxPrint_Printf(&printer, "grotto SEED:      %X", ourSeed);
        GfxPrint_SetPos(&printer, 1, 13);
        GfxPrint_Printf(&printer, "grotto location:      %X", ourLocation);
        //GfxPrint_SetPos(&printer, 1, 12);
        //GfxPrint_Printf(&printer, "grotto actorid:      %X", GROTTO_SPAWNER_ACTORID(thisx));
        //GfxPrint_SetPos(&printer, 1, 13);
        //GfxPrint_Printf(&printer, "grotto actor params:      %X", GROTTO_SPAWNER_PARAMS(thisx));
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

