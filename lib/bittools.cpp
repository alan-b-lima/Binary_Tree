#include "bittools.h"

BitTools::mword* BitTools::construct(uint64_t size, mword set) {
   size = (size + 7) >> 3;

   mword* arr = new (std::nothrow) mword[size];
   if (!arr) return nullptr;

   for (uint64_t i = 0; i < size; i++)
      arr[i] = set;

   return arr;
}

BitTools::mword* BitTools::initialize(mword* arr, uint64_t size, mword set) {
   size = (size + 7) >> 3;
   
   for (uint64_t i = 0; i < size; i++)
      arr[i] = set;

   return arr;
}

inline void BitTools::destruct(mword* arr) {
   delete[] arr;
}

void BitTools::print_bits(mword* arr, uint64_t size) {
   do putchar(getbit(arr, size) ? '1' : '0');
   while (size--);
}

#if defined(__INTRIN_H_) && defined(_VCRT_COMPILER_PREPROCESSOR) && !defined(__midl)

inline bool BitTools::getbit(mword* base, uint64_t pos) { return _bittest((const long*)base, pos); }
inline bool BitTools::flipbit(mword* base, uint64_t pos) { return _bittestandcomplement((long*)base, pos); }
inline bool BitTools::setbit_0(mword* base, uint64_t pos) { return _bittestandreset((long*)base, pos); }
inline bool BitTools::setbit_1(mword* base, uint64_t pos) { return _bittestandset((long*)base, pos); }

#else

inline bool BitTools::getbit(mword* base, uint64_t pos) {
   return base[pos >> SHIFT] & (1 << (pos & MASK));
}

inline bool BitTools::flipbit(mword* base, uint64_t pos) {
   bool bit = getbit(base, pos);
   base[pos >> SHIFT] ^= 1 << (pos & MASK);
   return bit;
}

inline bool BitTools::setbit_0(mword* base, uint64_t pos) {
   bool bit = getbit(base, pos);
   base[pos >> SHIFT] &= ~(1 << (pos & MASK));
   return bit;
}

inline bool BitTools::setbit_1(mword* base, uint64_t pos) {
   bool bit = getbit(base, pos);
   base[pos >> SHIFT] |= 1 << (pos & MASK);
   return bit;
}

#endif /* defined(__INTRIN_H_) && defined(_VCRT_COMPILER_PREPROCESSOR) && !defined(__midl) */