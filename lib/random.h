#pragma once

/*
* Author
*    Alan Lima (https://github.com/AlanLima287/)
*
* Terminal
*    It's a not precompiled C++ library that aims for a unified pseudorandom
*    number generator, since different systems will usually have different
*    generators.
*/

#include <stdint.h>

namespace Random {

   uint64_t __seed;

   // Set the seed
   inline void srand(uint64_t seed) {
      __seed = seed;
   }

   // Generate pseudorandom 32 unsigned bit integers 
   inline uint32_t rand() {
      __seed = __seed * 6364136223846793005 + 1442695040888963407;
      return (__seed & 0x0000'FFFF'FFFF'0000) >> 16;
   }

   // Generate pseudorandom integers in the range [minv, maxv)
   inline uint32_t rand(uint32_t minv, uint32_t _maxv) {
      return minv + (rand() % (_maxv - minv));
   }
}