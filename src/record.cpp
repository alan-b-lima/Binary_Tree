#include "record.h"

void write_record(Record* record, int data, const char* name) {

   for (uint64_t i = 0; name[i]; i++) {

      if (i >= NAME_SIZE) {
         record->name[i] = '\0';
         break;
      }

      record->name[i] = name[i];
   }

   record->data = data;
}

void print_record(Record* record, const char* format) {

   while (*format) {

      if (*format == '$') {

         format++;
         switch (*format) {

         case '0': std::cout << record->key; break;
         case '1': std::cout << record->data; break;
         case '2': std::cout << record->name; break;
         default: std::cout.put(*format); break;
         
         }

      } else std::cout.put(*format);
      format++;
   }
}

void populate_record_randomly(Record* record) {
   record->data = rand();

   char* cursor = record->name;
   uint64_t remaining_space = NAME_SIZE;

   // It's a bit field
   //    [0-1] bits select the number of surnames
   //    [2] bit says whether the record's name will be composed
   byte params = rand() & 0b111;
   uint64_t random;

   /* name */

   while (true) {
      random = rand() % NAME_LIST_SIZE;

      strncpy_s(record->name, NAME_LIST[random], remaining_space);

      for (uint64_t i = 0; NAME_LIST[random][i]; i++) {
         *cursor++ = NAME_LIST[random][i];

         // if not enough space, quits
         if (!(--remaining_space)) goto exit;
      }

      // if not enough space, quits before termination with a space
      if (!(--remaining_space)) goto exit;
      *cursor++ = ' ';

      if (params & 0b100) break;
      params ^= 0b100;
   }

   /* surname */

   // Garantees at least one surname
   if (!params) params = 1;

   do {
      random = rand() % SURNAME_LIST_SIZE;
      params--;

      for (uint64_t i = 0; SURNAME_LIST[random][i]; i++) {
         *cursor++ = SURNAME_LIST[random][i];

         // if not enough space, quits
         if (!(--remaining_space)) goto exit;
      }

      // if not enough space, quits before putting a space
      if (!(--remaining_space)) goto exit;
      *cursor++ = ' ';

   } while (params);

   // Effectively removes the last space
   cursor--;

   // goto labels, hate or love them, I'll use them regardless, with some regard, still
exit:

   // Garanties null termination inside the intended buffer
   *cursor = '\0';
}

void destruct_record(Record* record) {
   delete record;
}
