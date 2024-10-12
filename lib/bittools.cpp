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

void BitTools::print(mword* arr, uint64_t size) {
   size--;
   do putchar(getbit(arr, size) ? '1' : '0');
   while (size--);
}

#if defined(__INTRIN_H_) && __HAS__INTRINSICS____

inline bool BitTools::getbit(mword* base, uint64_t pos) { return _bittest64((const long long*)(base + (pos >> SHIFT)), pos & MASK); }
inline bool BitTools::flipbit(mword* base, uint64_t pos) { return _bittestandcomplement64((long long*)(base + (pos >> SHIFT)), pos & MASK); }
inline bool BitTools::setbit_0(mword* base, uint64_t pos) { return _bittestandreset64((long long*)(base + (pos >> SHIFT)), pos & MASK); }
inline bool BitTools::setbit_1(mword* base, uint64_t pos) { return _bittestandset64((long long*)(base + (pos >> SHIFT)), pos & MASK); }

#else

inline bool BitTools::getbit(mword* base, uint64_t pos) {
   return base[pos >> SHIFT] & (1 << (pos & MASK));
}

inline bool BitTools::flipbit(mword* base, uint64_t pos) {
   mword* word = base + (pos >> SHIFT);
   int64_t offset = 1 << (pos & MASK);

   bool bit = *word & offset;
   *word ^= offset;

   return bit;
}

inline bool BitTools::setbit_0(mword* base, uint64_t pos) {
   mword* word = base + (pos >> SHIFT);
   int64_t offset = 1 << (pos & MASK);

   bool bit = *word & offset;
   *word &= ~offset;

   return bit;
}

inline bool BitTools::setbit_1(mword* base, uint64_t pos) {
   mword* word = base + (pos >> SHIFT);
   int64_t offset = 1 << (pos & MASK);

   bool bit = *word & offset;
   *word |= offset;

   return bit;
}

#endif /* defined(__INTRIN_H_) && defined(_VCRT_COMPILER_PREPROCESSOR) && !defined(__midl) */