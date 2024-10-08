#pragma once

/**************************************************************
* Author                                                      *
*    Alan Lima @AlanLima287 (https://github.com/AlanLima287/) *
*                                                             *
* BitTools                                                    *
*    It's a not precompiled C++ library with wrapper function *
*    for especific assembly instructions (BT, BTC, BTR, BTS)  *
*    and a implementation of a boolean array structure        *
**************************************************************/

#ifndef __BIT_TOOLS_
#define __BIT_TOOLS_


#include <stdint.h>
#include <stdlib.h>
#include <intrin.h>
#include <stdio.h>
#include <new>

namespace BitTools {

   typedef unsigned char byte;
   typedef byte* bool_array;

   bool_array construct(uint32_t, byte = 0);
   inline void destruct(bool_array);

   // BT (Bit Test)
   inline bool getbit(bool_array, uint32_t);
   
   // BTC (Bit Test and Complement)
   inline bool flipbit(bool_array, uint32_t);
   
   // BTR (Bit Test and Reset)
   inline bool setbit_0(bool_array, uint32_t);
   
   // BTD (Bit Test and Set)
   inline bool setbit_1(bool_array, uint32_t);

   // Fills the boolean array with a bytewise pattern
   inline void fill(bool_array, byte, uint32_t);

   // Print the bits
   void print_bits(bool_array, uint32_t);
};

#endif /* #ifndef __BIT_TOOLS_ */