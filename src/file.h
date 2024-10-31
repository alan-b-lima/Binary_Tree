#pragma once

#include "base.h"
#include "record.h"

namespace RecordFile {

   const uint64_t PAGE_SIZE = 0x1000;

   typedef struct File {
      FILE* file;
      char buffer[PAGE_SIZE];
      uint64_t cursor;
      uint64_t size;
   } File;

   enum mode_t : byte { READ, WRITE };
   enum exit_t : byte { GOOD, BAD, EMPTY };

   inline exit_t open(const char*, File*, mode_t mode);
   inline void close(File*);
   
   bool read(File*, Record*);
   void write(File*, Record*, bool = true);
};