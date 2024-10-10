#include "bittools.h"

byte* BitTools::construct(uint32_t size, byte set) {
   size = (size + 7) >> 3;

   byte* arr = new (std::nothrow) byte[size];
   if (!arr) return nullptr;

   for (uint32_t i = 0; i < size; i++)
      arr[i] = set;

   return arr;
}

byte* BitTools::initialize(byte* arr, uint32_t size, byte set) {
   size = (size + 7) >> 3;
   
   for (uint32_t i = 0; i < size; i++)
      arr[i] = set;

   return arr;
}

inline void BitTools::destruct(byte* arr) {
   delete[] arr;
}

void BitTools::print_bits(byte* arr, uint32_t size) {
   do putchar(getbit(arr, size) ? '1' : '0');
   while (size--);
}

#if defined(__INTRIN_H_) && defined(_VCRT_COMPILER_PREPROCESSOR) && !defined(__midl)

inline bool BitTools::getbit(byte* base, uint32_t pos) { return _bittest(reinterpret_cast<const long*>(base), pos); }
inline bool BitTools::flipbit(byte* base, uint32_t pos) { return _bittestandcomplement(reinterpret_cast<long*>(base), pos); }
inline bool BitTools::setbit_0(byte* base, uint32_t pos) { return _bittestandreset(reinterpret_cast<long*>(base), pos); }
inline bool BitTools::setbit_1(byte* base, uint32_t pos) { return _bittestandset(reinterpret_cast<long*>(base), pos); }

#else

inline bool BitTools::getbit(byte* base, uint32_t pos) {
   return base[pos >> 3] & (1 << (pos & 0b111));
}

inline bool BitTools::flipbit(byte* base, uint32_t pos) {
   bool bit = getbit(base, pos);
   base[pos >> 3] ^= 1 << (pos & 0b111);
   return bit;
}

inline bool BitTools::setbit_0(byte* base, uint32_t pos) {
   bool bit = getbit(base, pos);
   base[pos >> 3] &= ~(1 << (pos & 0b111));
   return bit;
}

inline bool BitTools::setbit_1(byte* base, uint32_t pos) {
   bool bit = getbit(base, pos);
   base[pos >> 3] |= 1 << (pos & 0b111);
   return bit;
}

#endif /* defined(__INTRIN_H_) && defined(_VCRT_COMPILER_PREPROCESSOR) && !defined(__midl) */