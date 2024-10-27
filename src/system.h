#pragma once

#ifndef __SYSTEM___SPECIFICS___
#define __SYSTEM___SPECIFICS___

#include "../rc/strings.cpp"

// UTF-8, ASCII extended and pure ascii respectivily
// Assuming Linux terminals will support UTF-8

void get_terminal_dimensions(word&, word&);
inline void system_specifics_setup();

#if defined(__linux__) || defined(__APPLE__)

   #include <sys/ioctl.h>

   void get_terminal_dimensions(word&, word&) {
      struct winsize win;
      ioctl(fileno(stdout), TIOCGWINSZ, &w);
      width = word(win.ws_col);
      height = word(win.ws_row);
   }

   inline void system_specifics_setup() {}

#elif defined(_WIN32) || defined(_WIN64)

   #include <Windows.h>

   void get_terminal_dimensions(word& width, word& height) {
      CONSOLE_SCREEN_BUFFER_INFO csbi;
      GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
      
      height = word(csbi.srWindow.Bottom - csbi.srWindow.Top + 1);
      width = word(csbi.srWindow.Right - csbi.srWindow.Left + 1);
   }

   // The default code page, i.e, the encoding under which caracters are renderer,
   // is not garantied to be UTF-8, this fixes that
   inline void system_specifics_setup() {
      SetConsoleOutputCP(CP_UTF8);
   }

#endif

#endif /* __SYSTEM___SPECIFICS___ */