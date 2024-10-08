#pragma once

#include <stdlib.h>
#include <stdint.h>
#include <malloc.h>

namespace Stack {

   const uint64_t FRAME_SIZE = 0x200;

   typedef struct Stack {
      uint64_t allocated;
      uint8_t frame[FRAME_SIZE];
   } Stack;

   static Stack __stack = { 0 };

   void* allocate(uint64_t size, Stack& stack = __stack) {
      if (size == 0) return nullptr;
      if (FRAME_SIZE >= stack.allocated + size) {
         void* prt = (void*)(stack.frame + stack.allocated);
         stack.allocated += size;
         return prt;
      }

      return malloc(size);
   }

   void release(void* ptr, Stack& stack = __stack) {
      if (uint64_t(stack.frame) > uint64_t(ptr) || uint64_t(ptr) >= uint64_t(stack.frame + FRAME_SIZE))
         free(ptr);
      else
         stack.allocated = uint64_t(ptr) - uint64_t(stack.frame);
   }
}