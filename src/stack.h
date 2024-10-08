#pragma once
#include "base.h"

namespace Stack {

   typedef void* raw_ptr;

   const uint64_t TABLE_SIZE = 0x200;
   void* table[TABLE_SIZE];
   bool is_allocated = false;

   raw_ptr* alloc(uint64_t size) {

      if (size == 0) return nullptr;
      if (size <= TABLE_SIZE && !is_allocated) {
         is_allocated = true;
         return table;
      }

      raw_ptr* ptr = new (std::nothrow) raw_ptr[size];
      return ptr;
   }

   void free(raw_ptr* ptr) {
      if (table != ptr)
         delete[] ptr;

      is_allocated = false;
      return;
   }

   /*
   const uint64_t PAGE_SIZE = 0x1000;

   typedef struct Frame {
      Frame* prev_frame;
      void* page[PAGE_SIZE];
   } Frame;

   typedef struct Stack {
      uint64_t stack_pointer;
      Frame* frame;
   } Stack;

   bool push(Stack*& stack, void* pointer) {

      sizeof(Frame);

      stack->stack_pointer++;
      if (stack->stack_pointer >= PAGE_SIZE) {

         Frame* new_frame = new Frame;
         if (!new_frame) return false;

         new_frame->prev_frame = stack->frame;
         stack->frame = new_frame;

         stack->stack_pointer = 0;
      }

      stack->frame->page[stack->stack_pointer] = pointer;
      return true;
   }

   void* pop(Stack*& stack) {
      if (!stack->stack_pointer) {
         void* pointer = stack->frame->page[0];

         Frame* old_frame = stack->frame->prev_frame;
         delete stack->frame;

         return pointer;
      }

      return stack->frame->page[stack->stack_pointer];
   }
   */
}