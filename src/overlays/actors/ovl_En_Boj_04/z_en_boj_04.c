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
    /**/ NULL,
};

struct ActorCombo{
  u16 actorId;
  u16 params;
};

// going to need a way to map this data to the entrance, torch does this too but only for 8 items and we have a least 10 grottos
// two in TF: pillar and grass
// mystery woods and outside of ssh
// behind fishermans hut and cape boulder
// 


// struct of ActorCombos structs per grotto

// struct of objects per grotto

void EnBoj04_Init(Actor* thisx, PlayState* play) {
  EnBoj04* this = THIS;
 
  // first we need to load the object, for now let's assume there is only one type of enemy per grotto so one object for all

  // load the object for the grotto
  this->objectId = 0x17; // dinofos, testing

  Object_SpawnPersistent(&play->objectCtx, &this->objectId);

}

void EnBoj04_Destroy(Actor* thisx, PlayState* play) {
}

void EnBoj04_Update(Actor* thisx, PlayState* play) {
  EnBoj04* this = THIS;

  // if object is loaded, spawn actor
  if (Object_IsLoaded(&play->objectCtx, &this->objectId)){

    Actor_Spawn(&play->actorCtx, play, ACTOR_EN_DINOFOS, 
                this->actor.world.pos.x, this->actor.world.pos.y, this->actor.world.pos.z,
                this->actor.shape.rot.x, this->actor.shape.rot.y, this->actor.shape.rot.z,
                0x0000);
                //ENBOX_PARAMS(ENBOX_TYPE_SMALL, sChestContents[(returnData >> 0x5) & 0x7], returnData));

    Actor_Kill(&this);
  }
}



//#include "z_en_torch.h"
//#include "overlays/actors/ovl_En_Box/z_en_box.h"


//ActorInit En_Torch_InitVars = {
    ///**/ ACTOR_EN_TORCH,
    ///**/ ACTORCAT_ITEMACTION,
    ///**/ FLAGS,
    ///**/ GAMEPLAY_KEEP,
    ///**/ sizeof(EnTorch),
    ///**/ EnTorch_Init,
    ///**/ NULL,
    ///**/ NULL,
    ///**/ NULL,
//};

//static u8 sChestContents[] = {
    //GI_RUPEE_BLUE, GI_RUPEE_RED, GI_RUPEE_PURPLE, GI_RUPEE_SILVER, GI_BOMBCHUS_1, GI_BOMBCHUS_5, GI_BOMBS_1, GI_BOMBS_1,
//};

//void EnTorch_Init(Actor* thisx, PlayState* play) {
    //EnTorch* this = THIS;
    //s8 returnData = gSaveContext.respawn[RESPAWN_MODE_UNK_3].data;

    //Actor_Spawn(&play->actorCtx, play, ACTOR_EN_BOX, this->actor.world.pos.x, this->actor.world.pos.y,
                //this->actor.world.pos.z, 0, this->actor.shape.rot.y, 0,
                //ENBOX_PARAMS(ENBOX_TYPE_SMALL, sChestContents[(returnData >> 0x5) & 0x7], returnData));
    //Actor_Kill(&this->actor);
//}
