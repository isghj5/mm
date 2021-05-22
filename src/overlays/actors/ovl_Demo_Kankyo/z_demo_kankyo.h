#ifndef Z_DEMO_KANKYO_H
#define Z_DEMO_KANKYO_H

#include <global.h>

typedef void (*DemoKankyoActionFunc)(struct DemoKankyo*, GlobalContext*);


// as this actor handles the funny particles in the air in lost woods, this is likely those particles
typedef struct {
  /* 0x000 */ u8 unk0; // enabled?
  /* 0x004 */ Vec3f unk4; // 148
  /* 0x010 */ Vec3f unk10;
  /* 0x01C */ Vec3f unk1C; //160
  /* 0x028 */ Vec3f unk28; // 16C
  /* 0x034 */ u8 pad34[0x4];
  /* 0x038 */ f32 unk38; // 17C
  /* 0x03C */ u16 unk3C; // 180
  /* 0x040 */ u8 unk40;
  /* 0x041 */ u8 unk41[0x3];
  /* 0x044 */ f32 unk44;
  /* 0x048 */ u8 unk48[0x8];
  /* 0x050 */ u16 unk50;
  /* 0x052 */ u16 pad52;

} DemoKankyoParticle; // size = 0x54

#define DEMOKANKYO_PARTICLE_COUNT 0x40

struct DemoKankyo;

typedef struct DemoKankyo {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ DemoKankyoParticle unk144[DEMOKANKYO_PARTICLE_COUNT];
    /* 0x1644 */ DemoKankyoActionFunc actionFunc;
    /* 0x1648 */ s32 objBankIndex;
    /* 0x164C */ char unk164C[0x4];
} DemoKankyo; // size = 0x1650

extern const ActorInit Demo_Kankyo_InitVars;

#endif // Z_DEMO_KANKYO_H
