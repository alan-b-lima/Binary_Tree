#pragma once

#include <stdint.h>
#include <stdlib.h>
#include <intrin.h>
#include <stdio.h>

namespace BitTools {

   typedef byte* bool_array;

   bool_array construct(uint32_t size, byte set = 0) {
      size = (size + 7) >> 3;

      bool_array arr = new (std::nothrow) byte[size];
      if (!arr) return nullptr;

      for (uint32_t i = 0; i < size; i++)
         arr[i] = set;

      return arr;
   }

   inline void fill(bool_array arr, byte set, uint32_t size) {
      size = (size + 7) >> 3;
      for (uint32_t i = 0; i < size; i++)
         arr[i] = set;
   }

   inline void destruct(bool_array arr) {
      delete[] arr;
   }

   // BT (Bit Test)
   inline bool getbit(bool_array, uint32_t);
   // BTC (Bit Test and Complement)
   inline bool flipbit(bool_array, uint32_t);
   // BTR (Bit Test and Reset)
   inline bool setbit_0(bool_array, uint32_t);
   // BTD (Bit Test and Set)
   inline bool setbit_1(bool_array, uint32_t);

#ifndef __INTRIN_H_

   inline bool getbit(bool_array base, uint32_t pos) {
      return base[pos >> 3] & (1 << (pos & 0b111));
   }

   inline bool flipbit(bool_array base, uint32_t pos) {
      bool bit = getbit(base, pos);
      base[pos >> 3] ^= 1 << (pos & 0b111);
      return bit;
   }

   inline bool setbit_0(bool_array base, uint32_t pos) {
      bool bit = getbit(base, pos);
      base[pos >> 3] &= ~(1 << (pos & 0b111));
      return bit;
   }

   inline bool setbit_1(bool_array base, uint32_t pos) {
      bool bit = getbit(base, pos);
      base[pos >> 3] |= 1 << (pos & 0b111);
      return bit;
}

#else

   inline bool getbit(bool_array base, uint32_t pos) { return _bittest((long*)base, pos); }
   inline bool flipbit(bool_array base, uint32_t pos) { return _bittestandcomplement((long*)base, pos); }
   inline bool setbit_0(bool_array base, uint32_t pos) { return _bittestandreset((long*)base, pos); }
   inline bool setbit_1(bool_array base, uint32_t pos) { return _bittestandset((long*)base, pos); }

#endif

   void print_bits(bool_array arr, uint32_t size) {
      do putchar(getbit(arr, size) ? '1' : '0');
      while (size--);
   }
};