#pragma once

/*
* Author
*    Alan Lima (https://github.com/AlanLima287/)
*
* BitTools
*    It's a not precompiled C++ library with wrapper function
*    for especific assembly instructions (BT, BTC, BTR, BTS)
*    or its behavior
*/

#ifndef __BIT_TOOLS_
#define __BIT_TOOLS_

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <new>

#if defined(_MSC_VER) && __has_include("intrin.h")
#include <intrin.h>
#endif

typedef unsigned char byte;

namespace BitTools {

   byte* construct(uint32_t, byte = 0);
   inline void destruct(byte*);

   // BT (Bit Test)
   inline bool getbit(byte*, uint32_t);

   // BTC (Bit Test and Complement)
   inline bool flipbit(byte*, uint32_t);

   // BTR (Bit Test and Reset)
   inline bool setbit_0(byte*, uint32_t);

   // BTD (Bit Test and Set)
   inline bool setbit_1(byte*, uint32_t);

   // Fills the boolean array with a bytewise pattern
   byte* initialize(byte*, uint32_t, byte = 0);

   // Print the bits
   void print_bits(byte*, uint32_t);
};

#include "bittools.cpp"

#endif /* __BIT_TOOLS_ */