#pragma once

/*
* Author
*    Alan Lima (https://github.com/AlanLima287/)
*
* Stack
*    It's a not precompiled C++ library that implements a
*    stack structure for dynamic allocation with less overhead.
*    It has a static array of size 4KiB, in which the allocations
*    are done. Does not support object, to use objects, constructors
*    and destructors must be called manually.
*/

#ifndef __STACK_AL_
#define __STACK_AL_

#include <stdlib.h>
#include <stdint.h>
#include <malloc.h>

namespace Stack {

   const uint64_t FRAME_SIZE = 0x1000; // 4KiB
   const uint64_t _ALIGNMENT = 16;

   typedef struct Stack {
      uint64_t allocated;
      alignas(_ALIGNMENT) uint8_t frame[FRAME_SIZE];
   } Stack;

   static Stack __stack = { 0 };

   template <typename type_t>
   type_t* allocate(uint64_t size, Stack& stack = __stack) {
      if (size == 0) return nullptr;
      
      size *= sizeof(type_t);

      uint64_t alignment = sizeof(type_t) < _ALIGNMENT ? sizeof(type_t) : _ALIGNMENT;
      type_t* pointer = (type_t*)((uint64_t(stack.frame) + stack.allocated + alignment - 1) & -alignment);
      
      if (uint64_t(uintptr_t(pointer) - uintptr_t(stack.frame)) > FRAME_SIZE) {
         return (type_t*)malloc(size);
      }

      stack.allocated = uint64_t(uintptr_t(pointer) - uintptr_t(stack.frame)) + size;
      return pointer;
   }

   template <typename type_t>
   void release(type_t* pointer, Stack& stack = __stack) {
      if (pointer == nullptr) return;

      if (uintptr_t(stack.frame) > uintptr_t(pointer) || uintptr_t(pointer) >= uintptr_t(stack.frame + FRAME_SIZE)) {
         delete[] pointer;
         return;
      }

      uint64_t to_release = uint64_t(uintptr_t(pointer) - uintptr_t(stack.frame));
      if (to_release < stack.allocated) stack.allocated = to_release;
   }
}

#endif /* __STACK_AL_ */