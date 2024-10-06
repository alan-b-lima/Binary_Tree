#include "base.h"

namespace BitTools {

   template <typename type>
   void print_bits(type value, uint64_t bits) {
      for (bits = 1ull << bits - 1; bits; bits >>= 1)
         std::cout.put('0' + !!(value & bits));
   }

   inline bool getbit(byte* base, uint64_t pos) {
      return base[pos >> 3] & (1 << (pos & 0b111));
   }

   inline void flipbit(byte* base, uint64_t pos) {
      base[pos >> 3] ^= 1 << (pos & 0b111);
   }

   inline void setbit_0(byte* base, uint64_t pos) {
      base[pos >> 3] &= ~(1 << (pos & 0b111));
   }

   inline void setbit_1(byte* base, uint64_t pos) {
      base[pos >> 3] |= 1 << (pos & 0b111);
   }
};