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

   inline bool open(const char*, File*, mode_t mode);
   inline void close(File*);
   
   bool read(File*, Record*);
   void write(File*, Record*, bool = true);

   // template <typename... Args>
   // void read_iterator(const char* filename, void(*handler)(Record*, Args...), Args... args) {
   //    RecordFile::File rc_file;
   //    bool not_complete = RecordFile::open(filename, &rc_file, mode_t::READ);

   //    while (not_complete) {
   //       Record* record = new Record;
   //       if (!record) return;

   //       not_complete = RecordFile::read(&rc_file, record);
   //       handler(record, args...);
   //    }

   //    RecordFile::close(&rc_file);
   // }

   // template <typename... Args>
   // void write_iterator(const char* filename, Record*(*handler)(Args...), Args... args) {
   //    RecordFile::File rc_file;
   //    bool not_complete = RecordFile::open(filename, &rc_file, mode_t::WRITE);

   //    while (not_complete) {
   //       Record* record = handler(record, args...);
   //       if (!record) return;

   //       not_complete = RecordFile::read(&rc_file, record);
   //    }

   //    RecordFile::close(&rc_file);
   // }
};