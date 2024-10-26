#pragma once

/*
* Author
*    Alan Lima (https://github.com/AlanLima287/)
*
* Terminal
*    It's a not precompiled C++ library that aims for a unified pseudorandom
*    number generator, since different systems will usually have diferent 
*    generators.
*/

#include <stdint.h>

namespace Random {

   static uint64_t __seed;

   void srand(uint64_t seed) {
      __seed = seed;
   }

   uint32_t rand() {
      __seed = __seed * 0x10A860C1ull + 0x2DEF29ull;
      return (__seed & 0x0000'FFFF'FFFF'0000) >> 16;
   }
}