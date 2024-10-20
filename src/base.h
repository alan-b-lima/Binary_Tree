#pragma once

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include <iostream>
#include "../lib/random.h"

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