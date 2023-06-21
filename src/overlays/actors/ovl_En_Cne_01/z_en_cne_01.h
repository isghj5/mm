#ifndef Z_EN_CNE_01_H
#define Z_EN_CNE_01_H

#include "z_en_hy_code.h"
#include "objects/object_cne/object_cne.h"


struct EnCne01;

typedef void (*EnCne01ActionFunc)(struct EnCne01*, PlayState*);

typedef struct EnCne01 {
    ///* 0x000 */ EnHy enHy;
    /* 0x000 */ Actor actor;
                EnCne01ActionFunc actionFunc;
                EnCne01ActionFunc prevActionFunc;
                ColliderCylinder collider;
                SkelAnime skelAnime;
                s16 limbRotTableY[CNE_LIMB_MAX];
                s16 limbRotTableZ[CNE_LIMB_MAX];
                Vec3s jointTable[CNE_LIMB_MAX];
                Vec3s morphTable[CNE_LIMB_MAX];
                Vec3f bodyPartsPos[CNE_LIMB_MAX]; // size unk
                Vec3s trackTarget;
                Vec3s headRot;
                //Vec3s prevHeadRot;
                Vec3s torsoRot;
                //Vec3s prevTorsoRot;
                Path* path;
                s16 inMsgState3; // head bob
                s16 headObjIndex;
                s16 textId;
                s16 stateFlags;
                s16 dialogueTimer;
                Actor* moonPtr;
                AnimationHeader* defaultAnim;
                AnimationHeader* curAnim;
    
    ///* 0x3EC */ UNK_TYPE1 unk_3EC[0x230];
} EnCne01; // size = 0x61C

#define CNE_GET_PATH(thisx) (((thisx)->params & 0x7E00) >> 9)
#define CNE_GET_TYPE(thisx) ((thisx)->params & 0xF)

typedef enum{
  CNE_TYPE_VENESA = 0,
  CNE_TYPE_ORANGE = 1

} EncCneTypes;


#endif // Z_EN_CNE_01_H
