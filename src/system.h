#pragma once

// UTF-8, ASCII extended and pure ascii respectivily
// Assuming Linux terminals will support UTF-8

inline void system_specifics_setup();

#if defined(__linux__)

   const char BRANCH_ROOT[]      = "\u003A\u2500\u2500\u2500"; /* ":───" */
   const char BRANCH_DOWN[]      = "\u2502\u0020\u0020\u0020"; /* "│   " */
   const char NO_BRANCH[]        = "\u0020\u0020\u0020\u0020"; /* "    " */
   const char BRANCH_SIDE[]      = "\u251C\u2500\u2500\u2500"; /* "├───" */
   const char BRANCH_DOWN_SIDE[] = "\u2514\u2500\u2500\u2500"; /* "└───" */
   const char BRANCH_UP_SIDE[]   = "\u250C\u2500\u2500\u2500"; /* "┌───" */

   inline void system_specifics_setup() {}

#elif defined(_WIN32) || defined(_WIN64)

   #include <Windows.h>

   #if defined(_WINDOWS_) && defined(_APISETCONSOLEL2_)

      const char BRANCH_ROOT[]      = "\u003A\u2500\u2500\u2500"; /* ":───" */
      const char BRANCH_DOWN[]      = "\u2502\u0020\u0020\u0020"; /* "│   " */
      const char NO_BRANCH[]        = "\u0020\u0020\u0020\u0020"; /* "    " */
      const char BRANCH_SIDE[]      = "\u251C\u2500\u2500\u2500"; /* "├───" */
      const char BRANCH_DOWN_SIDE[] = "\u2514\u2500\u2500\u2500"; /* "└───" */
      const char BRANCH_UP_SIDE[]   = "\u250C\u2500\u2500\u2500"; /* "┌───" */

      // The default code page, i.e, under which encoding caracters are renderer,
      // is not garantied to be UTF-8, this fixes that
      inline void system_specifics_setup() {
         SetConsoleOutputCP(CP_UTF8);
      }

   #else // Extended ascii version, identical to the UTF-8 one

      const char BRANCH_ROOT[]      = "\x3A\xC4\xC4\xC4"; /* ":───" */
      const char BRANCH_DOWN[]      = "\xB3\x20\x20\x20"; /* "│   " */
      const char NO_BRANCH[]        = "\x20\x20\x20\x20"; /* "    " */
      const char BRANCH_SIDE[]      = "\xC3\xC4\xC4\xC4"; /* "├───" */
      const char BRANCH_DOWN_SIDE[] = "\xC0\xC4\xC4\xC4"; /* "└───" */
      const char BRANCH_UP_SIDE[]   = "\xDA\xC4\xC4\xC4"; /* "┌───" */

      inline void system_specifics_setup() {}

   #endif

#else

   const char BRANCH_ROOT[]      = ":---";
   const char BRANCH_DOWN[]      = "|   ";
   const char NO_BRANCH[]        = "    ";
   const char BRANCH_SIDE[]      = "|---";
   const char BRANCH_DOWN_SIDE[] = "+---";
   const char BRANCH_UP_SIDE[]   = "+---";

   inline void system_specifics_setup() {}

#endif