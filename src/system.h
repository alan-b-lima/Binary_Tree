// UTF-8, ASCII extended and pure ascii respectivily
// Assuming Linux terminals will support UTF-8

inline void system_specifics_setup();

#if defined(__linux__)

char BRANCH_ROOT[]      = "\u003A\u2500\u2500\u2500"; /* ":───" */
char BRANCH_DOWN[]      = "\u2502\u0020\u0020\u0020"; /* "│   " */
char NO_BRANCH[]        = "\u0020\u0020\u0020\u0020"; /* "    " */
char BRANCH_SIDE[]      = "\u251C\u2500\u2500\u2500"; /* "├───" */
char BRANCH_DOWN_SIDE[] = "\u2514\u2500\u2500\u2500"; /* "└───" */
char BRANCH_UP_SIDE[]   = "\u250C\u2500\u2500\u2500"; /* "┌───" */

void system_specifics_setup() {}

#elif defined(_WIN32) || defined(_WIN64)

#include <Windows.h>

char BRANCH_ROOT[]      = "\u003A\u2500\u2500\u2500"; /* ":───" */
char BRANCH_DOWN[]      = "\u2502\u0020\u0020\u0020"; /* "│   " */
char NO_BRANCH[]        = "\u0020\u0020\u0020\u0020"; /* "    " */
char BRANCH_SIDE[]      = "\u251C\u2500\u2500\u2500"; /* "├───" */
char BRANCH_DOWN_SIDE[] = "\u2514\u2500\u2500\u2500"; /* "└───" */
char BRANCH_UP_SIDE[]   = "\u250C\u2500\u2500\u2500"; /* "┌───" */

void system_specifics_setup() {
   SetConsoleOutputCP(CP_UTF8);
}

#elif 1 // Extended ascii version, identical to the UTF-8 one

char BRANCH_ROOT[]      = "\x3A\xC4\xC4\xC4"; /* ":───" */
char BRANCH_DOWN[]      = "\xB3\x20\x20\x20"; /* "│   " */
char NO_BRANCH[]        = "\x20\x20\x20\x20"; /* "    " */
char BRANCH_SIDE[]      = "\xC3\xC4\xC4\xC4"; /* "├───" */
char BRANCH_DOWN_SIDE[] = "\xC0\xC4\xC4\xC4"; /* "└───" */
char BRANCH_UP_SIDE[]   = "\xDA\xC4\xC4\xC4"; /* "┌───" */

void system_specifics_setup() {}

#else

char BRANCH_ROOT[]      = ":---";
char BRANCH_DOWN[]      = "|   ";
char NO_BRANCH[]        = "    ";
char BRANCH_SIDE[]      = "|---";
char BRANCH_DOWN_SIDE[] = "+---";
char BRANCH_UP_SIDE[]   = "+---";

void system_specifics_setup() {}

#endif