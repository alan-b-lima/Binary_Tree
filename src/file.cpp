#include "file.h"

// Local utilities, not meant to de used elsewhere

static inline void __load(RecordFile::File*);
static inline bool __getch(RecordFile::File*, char&);
template <typename type_t> static bool __read_int(RecordFile::File*, type_t&);
static inline bool __find_newl(RecordFile::File*);

inline bool RecordFile::open(const char* filename, File* rc_file) {
   rc_file->file = fopen(filename, "rw");
   if (!rc_file->file) return false;

   __load(rc_file);
   return rc_file->size != 0;
}

inline void RecordFile::close(File* rc_file) {
   if (rc_file->file) fclose(rc_file->file); 
}

bool RecordFile::read(File* rc_file, Record* record) {

   // If the buffer is empty, try to load more from the file
   if (!rc_file->size) __load(rc_file);

   char* cursor = record->name;
   uint64_t char_count = 0;

   record->data = 0;
   record->key = 0;

   if (!__read_int(rc_file, record->key)) return false;
   if (!__read_int(rc_file, record->data)) return false;

   do {
      char ch;

      // get the next character in the loaded file
      while (__getch(rc_file, ch)) {

         switch (ch) {

         // Terminates the name
         case '\n':
            record->name[char_count] = '\0';
            return true;

         // Put the next character literally in the name buffer
         case '\\':
            __getch(rc_file, record->name[char_count++]);
            break;

         // Put a normal character in the name buffer
         default:
            record->name[char_count++] = ch;
            break;
         }

         // The name on the file exceds the record's name buffer
         if (char_count >= NAME_SIZE) {
            record->name[char_count] = '\0';
            return __find_newl(rc_file);
         }
      }

      __load(rc_file);

      // If the buffer is empty after trying to load, returns false
   } while (rc_file->size);

   // Upon EOF reached, also terminates the name
   record->name[char_count] = '\0';
   return false;
}

static inline void __load(RecordFile::File* rc_file) {
   rc_file->size = fread(rc_file->buffer, sizeof(char), RecordFile::PAGE_SIZE, rc_file->file);
   rc_file->cursor = 0;
}

static inline bool __getch(RecordFile::File* rc_file, char& ch) {
   if (rc_file->cursor >= rc_file->size) return false;

   ch = rc_file->buffer[rc_file->cursor];
   rc_file->cursor++;

   return true;
}

template <typename type_t>
static bool __read_int(RecordFile::File* rc_file, type_t& field) {
   do {
      char ch;

      // get the next character in the loaded file
      while (__getch(rc_file, ch)) {

         // Stops reading if ';' or '\n' are founded
         if (ch == ';' || ch == '\n') {
            return true;
         }

         // Process numerical characters, base 10 assumed
         if ('0' <= ch && ch <= '9') {
            field = 10 * field + ch - '0';
         }

         // Ignores any other characters
      }

      __load(rc_file);

      // If the buffer is empty after trying to load, returns false
   } while (rc_file->size);

   return false;
}

static inline bool __find_newl(RecordFile::File* rc_file) {
   do {
      while (rc_file->cursor < rc_file->size) {

         if (rc_file->buffer[rc_file->cursor++] == '\n') {
            return true;
         }
      }

      __load(rc_file);
   } while (rc_file->size);

   return false;
}
