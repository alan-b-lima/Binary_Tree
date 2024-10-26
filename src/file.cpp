#include "file.h"
#include "../lib/bittools.h"

// Local utilities, not meant to de used elsewhere
/* Local utilities START */

// Reading

   static inline bool __getch(RecordFile::File*, char&);

   enum __state : byte { FIELD_TERMINATOR, RECORD_TERMINATOR, HALT };

   template <typename type_t> static inline __state __read_int(RecordFile::File*, type_t&);
   static inline __state __read_str(RecordFile::File*, char*);
   static inline __state __find_newl(RecordFile::File*);

// Writing

   static inline void __putch(RecordFile::File*, char);
   static inline void __flush(RecordFile::File*);

   template <typename type_t> static inline void __write_int(RecordFile::File*, type_t);
   static inline void __write_str(RecordFile::File*, const char*);

/* Local utilities END */

inline bool RecordFile::open(const char* filename, File* rc_file, mode_t mode) {
   char option[3] = " +";
   if (mode == READ)  option[0] = 'r';
   if (mode == WRITE) option[0] = 'w';

   rc_file->file = fopen(filename, option);
   if (!rc_file->file) return false;

   // Where doing our own management here, not buffering is needed
   setvbuf(rc_file->file, NULL, _IONBF, 0);

   // Does not reflect reality, it's for triggering it to load from
   // a file without terminating
   rc_file->size = PAGE_SIZE;
   rc_file->cursor = PAGE_SIZE;

   return true;
}

inline void RecordFile::close(File* rc_file) {
   if (rc_file->file) fclose(rc_file->file);
}

bool RecordFile::read(File* rc_file, Record* record) {

   record->key = 0;
   record->data = 0;
   record->name[0] = '\0';

   __state state;

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

void RecordFile::write(File* rc_file, Record* record, bool start) {
   if (start) __putch(rc_file, '\n');
   __write_int(rc_file, record->key); __putch(rc_file, ';');
   __write_int(rc_file, record->data); __putch(rc_file, ';');
   __write_str(rc_file, record->name);
   if (rc_file->cursor) __flush(rc_file);
}

static inline bool __getch(RecordFile::File* rc_file, char& ch) {

   // If the cursor has surpassed the amount of loaded bytes, more content will
   // possibly be loaded
   if (rc_file->cursor >= rc_file->size) {

      // If the buffer has not been entirely filled last time, an EOF has already
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
static inline __state __read_int(RecordFile::File* rc_file, type_t& field) {

   char ch;
   bool sign = false;

   if (__getch(rc_file, ch)) {
      if (ch == '-') {
         if (!__getch(rc_file, ch)) goto exit;
         sign = true;
      }
   } else goto exit;

   do {
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

   // get the next character in the loaded file
   } while (__getch(rc_file, ch));

   if (sign) field = -field;

exit:
   return __state::HALT;
}

static inline __state __read_str(RecordFile::File* rc_file, char* field) {

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

static inline __state __find_newl(RecordFile::File* rc_file) {

   char ch;
   while (__getch(rc_file, ch)) {

      if (ch == '\n')
         return __state::RECORD_TERMINATOR;
   }

   return __state::HALT;
}

static inline void __putch(RecordFile::File* rc_file, char ch) {

   // If the cursor has surpassed the amount of loaded bytes, the buffered content
   // will be written to the file
   if (rc_file->cursor >= RecordFile::PAGE_SIZE) {
      fwrite(rc_file->buffer, sizeof(char), RecordFile::PAGE_SIZE, rc_file->file);
      rc_file->cursor = 0;
   }

   rc_file->buffer[rc_file->cursor++] = ch;
}

static inline void __flush(RecordFile::File* rc_file) {
   fwrite(rc_file->buffer, sizeof(char), rc_file->cursor, rc_file->file);
   rc_file->cursor = 0;
}

template <typename type_t>
static inline void __write_int(RecordFile::File* rc_file, type_t field) {

   // An unsigned char, short, long and long long can have up to 3, 5, 10 and 20 decimal caracters
   // in their expresion, this calculates the number of qwords needed to store that
   const int64_t n_bytes = ((sizeof(type_t) == 1 ? 3 : (sizeof(type_t) >> 1) * 5) + 7) >> 3;

   // If negative, puts a sign and negate the number, turning it positive
   if (field < type_t(0)) {
      __putch(rc_file, '-');
      field = -field;
   }

   uint64_t number[n_bytes];
   uint64_t index, shift;

   // Uses number as BCD (Binary-Coded Decimal) array
   for (index = 0; index < n_bytes; index++) {
      number[index] = 0;
      shift = 60;

      while (true) {
         number[index] |= uint64_t(field % 10) << shift;
         field /= 10;

         if (!field) goto put;
         if (!shift) break;
         shift -= 4;
      }
   }

   // If you pay attention, here we count in the reverse order as before
put:

   // Put the interest part at the start of the BCD array
   number[index] >>= shift;

   // Decreasing for with unsigned stuff gets quite clumsy
   while (true) {

      for (; shift < 64; shift += 4) {
         __putch(rc_file, '0' + (number[index] & 0xF));
         number[index] >>= 4;
      }

      if (!index) break;

      shift = 0;
      index--;
   } 
}

static inline void __write_str(RecordFile::File* rc_file, const char* string) {
   while (*string) __putch(rc_file, *string++);
}