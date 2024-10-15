#pragma once

#include "base.h"
#include "record.h"

namespace RecordFile {

   const uint64_t PAGE_SIZE = 0x10;

   typedef struct File {
      FILE* file;
      char buffer[PAGE_SIZE];
      uint64_t cursor;
      uint64_t size;
   } File;

   inline bool open(const char*, File*);
   inline void close(File*);

   bool read(File*, Record*);
};

#include "file.cpp"