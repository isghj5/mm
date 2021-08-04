#ifndef _ULTRATYPES_H_
#define _ULTRATYPES_H_

typedef signed char            s8;
typedef unsigned char          u8;
typedef signed short int       s16;
typedef unsigned short int     u16;
typedef signed int             s32;
typedef unsigned int           u32;
typedef signed long long int   s64;
typedef unsigned long long int u64;

typedef volatile u8  vu8;
typedef volatile u16 vu16;
typedef volatile u32 vu32;
typedef volatile u64 vu64;
typedef volatile s8  vs8;
typedef volatile s16 vs16;
typedef volatile s32 vs32;
typedef volatile s64 vs64;

typedef float  f32;
typedef double f64;

typedef void* TexturePtr;

typedef long int Mtx_t[4][4];
typedef union {
    Mtx_t m;
    long long int forc_structure_alignment;
} Mtx; // size = 0x40

typedef float MtxF_t[4][4];
typedef union {
    MtxF_t mf;
    struct {
        float xx, xy, xz, xw,
              yx, yy, yz, yw,
              zx, zy, zz, zw,
              wx, wy, wz, ww;
    };
} MtxF; // size = 0x40

#endif
