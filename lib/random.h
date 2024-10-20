#pragma once

#include <stdint.h>

namespace Random {

   static uint64_t __seed;

   void srand(uint64_t seed) {
      __seed = seed;
   }

   template <typename type_t>
   type_t rand() {
      __seed = __seed * 279470273ull + 3010349ull;
      return (type_t)(__seed & (~0ull >> (64 - (sizeof(type_t) << 3))));
   }
}