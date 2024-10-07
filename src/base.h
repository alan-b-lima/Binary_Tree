#pragma once

#include <iostream>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <random>

enum EXIT_CODE {
   FINE,
   BAD_ALLOCATION,
   FILE_NOT_FOUND,
};

char EXIT_CODE_MSG[][30] = {
   "",
   "Bad allocation",
   ""
};

void finish(int exit_code) {
   std::cerr << EXIT_CODE_MSG[exit_code];
   exit(1);
}

typedef unsigned char      byte;
typedef unsigned short     word;
typedef unsigned long      dword;
typedef unsigned long long qword;