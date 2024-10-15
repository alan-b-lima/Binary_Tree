#pragma once

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

#include <iostream>
#include <fstream>
#include <random>

#include "../lib/bittools.h"
#include "../lib/stack.h"
#include "system.h"

typedef unsigned char      byte;
typedef unsigned short     word;
typedef unsigned long      dword;
typedef unsigned long long qword;

enum EXIT_CODE {
   FINE,
   BAD_ALLOCATION,
   FILE_NOT_FOUND,
};

char EXIT_CODE_MSG[][30] = {
   "",
   "Bad allocation",
   "File Not Found"
};

void finish(int exit_code) {
   std::cout << EXIT_CODE_MSG[exit_code];
   exit(1);
}


uint64_t string_copy(char* _Dest, uint64_t _DestSize, const char* _Src, uint64_t _SrcSize) {

   uint64_t size = (_DestSize - 1) < _SrcSize ? (_DestSize - 1) : _SrcSize;

   for (size_t i = 0; i < size; i++) {
      *_Dest++ = _Src[i];
      if (!_Src[i]) return i;
   }

   return size;
}