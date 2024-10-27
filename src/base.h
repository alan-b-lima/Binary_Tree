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

#define minimum(a, b) (((a) < (b)) ? (a) : (b))
#define maximum(a, b) (((a) > (b)) ? (a) : (b))

// Checks whether a some pointer is valid, if so, accesses some field in a 
// structure/object pointed by it, if not, then returns some default value
#define safe_access(ptr, field, def_ret) ((ptr) ? (ptr)->field : (def_ret))