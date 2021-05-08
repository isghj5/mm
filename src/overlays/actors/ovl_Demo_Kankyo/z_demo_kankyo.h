#ifndef Z_DEMO_KANKYO_H
#define Z_DEMO_KANKYO_H

#include <global.h>

typedef void (*DemoKankyoActionFunc)(struct DemoKankyo*, GlobalContext*);

// as this actor handles the funny particles in the air in lost woods, this is likely those particles
typedef struct {
  /* 0x000 */ UNK_TYPE unk0;
  /* 0x004 */ Vec3f unk4; // 148
  /* 0x01C */ Vec3f unk1C; //160
  /* 0x020 */ f32 unk20;
  /* 0x028 */ Vec3f unk28; // 16C
  /* 0x038 */ f32 unk38; // 17C
  /* 0x03C */ u16 unk3C; // 180
  /* 0x040 */ u8 unk40;
  /* 0x044 */ f32 unk44;
  /* 0x050 */ u16 unk50;
  /* 0x054 */ u8 unk54;
  /* 0x0A8 */ u8 unkA8;
  /* 0x0FC */ u8 unkFC;

} DemoKankyoParticle; // size = 0x150
// clearly not that big, need to figure out real size

struct DemoKankyo;

typedef struct DemoKankyo {
    /* 0x0000 */ Actor actor;
    ///* 0x0144 */ char unk_0144[0x150C];
    /* 0x0144 */ char unk144[0x1500];
    /* 0x1644 */ DemoKankyoActionFunc actionFunc;
    /* 0x1648 */ s32 unk1648; // object index?
    /* 0x164C */ char unk164C[0x4];
} DemoKankyo; // size = 0x1650

extern const ActorInit Demo_Kankyo_InitVars;

#endif // Z_DEMO_KANKYO_H
