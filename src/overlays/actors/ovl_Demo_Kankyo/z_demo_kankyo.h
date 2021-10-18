#ifndef Z_DEMO_KANKYO_H
#define Z_DEMO_KANKYO_H

#include "global.h"

struct DemoKankyo;

typedef void (*DemoKankyoActionFunc)(struct DemoKankyo*, GlobalContext*);

// todo make particle state enum

typedef struct {
  /* 0x000 */ u8 state;
  /* 0x004 */ Vec3f vel;
  /* 0x010 */ Vec3f velPrevious;
  /* 0x01C */ Vec3f pos;
  /* 0x028 */ Vec3f unk_28; // rotation position? 
  /* 0x034 */ f32 speed;
  /* 0x038 */ f32 unk_38;
  /* 0x03C */ u16 unk_3C; // random start,
  /* 0x03E */ u16 unk_3E;
  /* 0x040 */ u8 alpha;
  /* 0x044 */ f32 unk_44; // part of the visibility system?
  /* 0x048 */ u16 unk_48; // pos or neg 200-400 
  /* 0x04A */ u16 unk_4A; // random value between 15-65
  /* 0x04C */ f32 unk_4C;
  /* 0x050 */ u16 pad50; // unused, always assigned to 0, nothing else in this actor uses it
} DemoKankyoParticle; // size = 0x54

#define DEMOKANKYO_PARTICLE_COUNT 64

typedef struct DemoKankyo {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ DemoKankyoParticle particles[DEMOKANKYO_PARTICLE_COUNT];
    /* 0x1644 */ DemoKankyoActionFunc actionFunc;
    /* 0x1648 */ s32 objectId;
    /* 0x164C */ u8 isSafeToDrawGiants;
} DemoKankyo; // size = 0x1650

typedef enum {
    /* 0 */ DEMO_KANKYO_TYPE_LOSTWOODS,
    /* 1 */ DEMO_KANKYO_TYPE_GIANTS,
    /* 2 */ DEMO_KANKYO_TYPE_MOON,
} DemoKankyoType;

extern const ActorInit Demo_Kankyo_InitVars;

#endif // Z_DEMO_KANKYO_H
