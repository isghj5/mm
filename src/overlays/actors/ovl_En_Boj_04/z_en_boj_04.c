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
    /**/ ACTORCAT_ITEMACTION,
    /**/ FLAGS,
    /**/ GAMEPLAY_KEEP,
    /**/ sizeof(EnBoj04),
    /**/ EnBoj04_Init,
    /**/ EnBoj04_Destroy,
    /**/ EnBoj04_Update,
    /**/ NULL, // draw func n/a
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
 { {10, 0}, {0, 0}, {0,0}   }, // tf grass
 { {10, 0}, {0, 0}, {0,0}   }, // tf pillar
 { {10, 0}, {0, 0}, {0,0}   }, // 
 { {10, 0}, {0, 0}, {0,0}   } ,
 { {10, 0}, {0, 0}, {0,0}   } ,
 { {10, 0}, {0, 0}, {0,0}   } ,
 { {10, 0}, {0, 0}, {0,0}   } ,
 { {10, 0}, {0, 0}, {0,0}   } ,
 { {10, 0}, {0, 0}, {0,0}   } ,
 { {10, 0}, {0, 0}, {0,0}   } ,
 { {10, 0}, {0, 0}, {0,0}   }
};

// struct of ActorCombos structs per grotto

// struct of objects per grotto
static GrottoComboObjects[] = {
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
  111  //  11
};

void EnBoj04_Init(Actor* thisx, PlayState* play) {
  EnBoj04* this = THIS;
 
  // first we need to load the object, for now let's assume there is only one type of enemy per grotto so one object for all

  // load the object for the grotto
  GROTTO_SPAWNER_OBJ_ID(thisx) = 0x17; // dinofos, testing

  // this does not work, we need to use randos function stead
  //Object_SpawnPersistent(&play->objectCtx, &this->objectId);

  

  //this->actionFunc // we dont need an actionfunc we can just do our work in update
}

void EnBoj04_Destroy(Actor* thisx, PlayState* play) {
}

void EnBoj04_Update(Actor* thisx, PlayState* play) {
  EnBoj04* this = THIS;

  // if object is loaded, spawn actor
  if (Object_IsLoaded(&play->objectCtx, &GROTTO_SPAWNER_OBJ_ID(thisx))){

    Actor_Spawn(&play->actorCtx, play, ACTOR_EN_DINOFOS, 
                this->actor.world.pos.x, this->actor.world.pos.y, this->actor.world.pos.z,
                this->actor.shape.rot.x, this->actor.shape.rot.y, this->actor.shape.rot.z,
                0x0000);
                //ENBOX_PARAMS(ENBOX_TYPE_SMALL, sChestContents[(returnData >> 0x5) & 0x7], returnData));

    Actor_Kill(&this);
  }
}

