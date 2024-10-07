#pragma once

#include "base.h"
#include "record.h"
#include "../rc/names.cpp"

namespace Generator {

   // const uint64_t PAGE_SIZE = 0x1000;

   void populate_record_randomly(Record& record) {
      record.data = rand();

      char* cursor = record.name;
      uint64_t remaining_space = NAME_SIZE - 1;

      byte params = rand() & 0b111;
      uint64_t random;

   name:
      random = rand() % NAME_LIST_SIZE;

      for (uint64_t i = 0; NAME_LIST[random][i]; i++) {
         if (!remaining_space) goto exit;
         *cursor++ = NAME_LIST[random][i];
         remaining_space--;
      }

      *cursor++ = ' ';

      if (params & 0b100) { params ^= 0b100; goto name; }

   surname:
      random = rand() % SURNAME_LIST_SIZE;

      for (uint64_t i = 0; SURNAME_LIST[random][i]; i++) {
         if (!remaining_space) goto exit;
         *cursor++ = SURNAME_LIST[random][i];
         remaining_space--;
      }

      *cursor++ = ' ';

      if (params) { params--; goto surname; }

   exit:
      *cursor = '\0';
   }
}