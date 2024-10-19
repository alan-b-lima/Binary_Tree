#include "file.h"

// Local utilities, not meant to de used elsewhere
/* Local utilities START */

static inline bool __getch(RecordFile::File*, char&);

template <typename type_t> static byte __read_int(RecordFile::File*, type_t&);
static byte __read_str(RecordFile::File*, char*);
static inline byte __find_newl(RecordFile::File*);

enum __state : byte {
   FIELD_TERMINATOR,
   RECORD_TERMINATOR,
   HALT,
};

/* Local utilities END */

inline bool RecordFile::open(const char* filename, File* rc_file) {
   rc_file->file = fopen(filename, "rw");
   if (!rc_file->file) return false;

   // Where doing our own management here, not buffering is needed
   setvbuf(rc_file->file, NULL, _IONBF, 0);

   rc_file->size = PAGE_SIZE; // Does not reflect reality
   rc_file->cursor = 0;
   return true;
}

inline void RecordFile::close(File* rc_file) {
   if (rc_file->file) fclose(rc_file->file);
}

bool RecordFile::read(File* rc_file, Record* record) {

   record->key = 0;
   record->data = 0;
   record->name[0] = '\0';

   byte state;
   
   state = __read_int(rc_file, record->key);
   if (state == __state::HALT) return false;
   if (state == __state::RECORD_TERMINATOR) return true;

   state = __read_int(rc_file, record->data);
   if (state == __state::HALT) return false;
   if (state == __state::RECORD_TERMINATOR) return true;

   state = __read_str(rc_file, record->name);
   if (state == __state::HALT) return false;

   return true;

}

static inline bool __getch(RecordFile::File* rc_file, char& ch) {

   // If the cursor has surpassed the amount of loaded bytes,
   // more content will possibly be loaded
   if (rc_file->cursor >= rc_file->size) {

      // If the buffer has not been entirely filled, an EOF has already
      // been reached
      if (rc_file->size < RecordFile::PAGE_SIZE) return false;

      // Tries to load more stuff, if nothing is read, EOF has been reached
      rc_file->size = fread(rc_file->buffer, sizeof(char), RecordFile::PAGE_SIZE, rc_file->file);
      if (!rc_file->size) return false;

      rc_file->cursor = 0;
   }

   ch = rc_file->buffer[rc_file->cursor++];
   return true;
}

template <typename type_t>
static byte __read_int(RecordFile::File* rc_file, type_t& field) {

   char ch;
   // get the next character in the loaded file
   while (__getch(rc_file, ch)) {

      // Will read the next field if ';' is read
      if (ch == ';') {
         return __state::FIELD_TERMINATOR;
      }

      // Stops reading if '\n' is found
      if (ch == '\n') {
         return __state::RECORD_TERMINATOR;
      }

      // Process numerical characters, base 10 assumed
      if ('0' <= ch && ch <= '9') {
         field = 10 * field + ch - '0';
      }

      // Ignores any other character
   }

   return __state::HALT;
}

static byte __read_str(RecordFile::File* rc_file, char* field) {

   uint64_t cursor = 0;
   char ch;
   // get the next character in the loaded file
   while (__getch(rc_file, ch)) {

      switch (ch) {

      // Terminates the name
      case '\n':
         field[cursor] = '\0';
         return __state::RECORD_TERMINATOR;

      // Put the next character literally in the name buffer
      case '\\':
         if (!__getch(rc_file, ch)) goto exit;

      // Put a normal character in the name buffer
      default:
         field[cursor++] = ch;
         break;
      }

      // if the name on the file exceeds the record's name buffer also terminates
      // the name, searches for the next new line, if such exists
      if (cursor >= NAME_SIZE) {
         field[cursor] = '\0';
         return __find_newl(rc_file);
      }
   }

exit:
   field[cursor] = '\0';
   return __state::HALT;
}

static inline byte __find_newl(RecordFile::File* rc_file) {

   char ch;
   while (__getch(rc_file, ch)) {

      if (ch == '\n')
         return __state::RECORD_TERMINATOR;
   }

   return __state::HALT;
}