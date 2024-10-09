#include "bittools.h"

BitTools::bool_array BitTools::construct(uint32_t size, byte set) {
   size = (size + 7) >> 3;

   bool_array arr = new (std::nothrow) byte[size];
   if (!arr) return nullptr;

   for (uint32_t i = 0; i < size; i++)
      arr[i] = set;

   return arr;
}

inline void BitTools::destruct(bool_array arr) {
   delete[] arr;
}

inline void BitTools::fill(bool_array arr, byte set, uint32_t size) {
   size = (size + 7) >> 3;
   for (uint32_t i = 0; i < size; i++)
      arr[i] = set;
}

void BitTools::print_bits(bool_array arr, uint32_t size) {
   do putchar(getbit(arr, size) ? '1' : '0');
   while (size--);
}

#if defined(__INTRIN_H_) && defined(_VCRT_COMPILER_PREPROCESSOR) && !defined(__midl)

inline bool BitTools::getbit(bool_array base, uint32_t pos) { return _bittest((long*)base, pos); }
inline bool BitTools::flipbit(bool_array base, uint32_t pos) { return _bittestandcomplement((long*)base, pos); }
inline bool BitTools::setbit_0(bool_array base, uint32_t pos) { return _bittestandreset((long*)base, pos); }
inline bool BitTools::setbit_1(bool_array base, uint32_t pos) { return _bittestandset((long*)base, pos); }

#else

inline bool BitTools::getbit(bool_array base, uint32_t pos) {
   return base[pos >> 3] & (1 << (pos & 0b111));
}

inline bool BitTools::flipbit(bool_array base, uint32_t pos) {
   bool bit = getbit(base, pos);
   base[pos >> 3] ^= 1 << (pos & 0b111);
   return bit;
}

inline bool BitTools::setbit_0(bool_array base, uint32_t pos) {
   bool bit = getbit(base, pos);
   base[pos >> 3] &= ~(1 << (pos & 0b111));
   return bit;
}

inline bool BitTools::setbit_1(bool_array base, uint32_t pos) {
   bool bit = getbit(base, pos);
   base[pos >> 3] |= 1 << (pos & 0b111);
   return bit;
}

#endif /* #if defined(__INTRIN_H_) && defined(_VCRT_COMPILER_PREPROCESSOR) && !defined(__midl) */