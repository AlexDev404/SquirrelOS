/*
   32-bits Random number generator U[0,1): lfsr113
   Author: Pierre L'Ecuyer,
   Source: http://www.iro.umontreal.ca/~lecuyer/myftp/papers/tausme2.ps
   ---------------------------------------------------------
*/

#include "../types/types.h"


/**** VERY IMPORTANT **** :
  The initial seeds z1, z2, z3, z4  MUST be larger than
  1, 7, 15, and 127 respectively.
****/

#define SEED 987654321

static uint32_t z1 = SEED, z2 = SEED, z3 = SEED, z4 = SEED;


double lfsr113(void)
{
   uint32_t b;
   b  = ((z1 << 6) ^ z1) >> 13;
   z1 = ((z1 & 4294967294U) << 18) ^ b;
   b  = ((z2 << 2) ^ z2) >> 27;
   z2 = ((z2 & 4294967288U) << 2) ^ b;
   b  = ((z3 << 13) ^ z3) >> 21;
   z3 = ((z3 & 4294967280U) << 7) ^ b;
   b  = ((z4 << 3) ^ z4) >> 12;
   z4 = ((z4 & 4294967168U) << 13) ^ b;
   return (z1 ^ z2 ^ z3 ^ z4) * 2.3283064365386963e-10;
}
