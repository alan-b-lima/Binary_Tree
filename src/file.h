#include <stdlib.h>
#include <stdio.h>

#include "base.h"

namespace FileHandling {

   typedef struct file_handler {
      FILE* file;
      void* page;
      uint64_t size;
   } file_handler;

   enum {
      READ = 0b001,
      WRITE = 0b010
   };

   bool open_file(const char* filename, byte mode) {

   }
};