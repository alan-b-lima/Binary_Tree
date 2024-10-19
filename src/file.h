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

   inline bool open(const char*, File*);
   inline void close(File*);
   
   bool read(File*, Record*);

   template <typename... Args>
   uint64_t iterator(const char* filename, void(*handler)(Record*, Args...), Args... args) {
      RecordFile::File rc_file;
      bool not_complete = RecordFile::open("./rc/test.rc", &rc_file);
      uint64_t record_count = 0;

      while (not_complete) {
         Record* record = new Record;
         if (!record) return -1;

         not_complete = RecordFile::read(&rc_file, record);
         record_count++;

         handler(record, args...);
      }

      RecordFile::close(&rc_file);
      return record_count;
   }
};

#include "file.cpp"