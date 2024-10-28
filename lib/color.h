#pragma once

#include <stdint.h>
#include <math.h>

namespace Color {
  
   enum colors : uint32_t {
      BLACK  = 0x000000,
      SILVER = 0xcccccc,
      GRAY   = 0x808080,
      WHITE  = 0xffffff,

      BROWN = 0x803000,

      RED   = 0xff0000,
      GREEN = 0x00ff00,
      BLUE  = 0x0000ff,

      YELLOW  = 0xffff00,
      MAGENTA = 0xff00ff,
      CYAN    = 0x00ffff,

      MAROON = 0x800000,
      FOREST = 0x008000,
      NAVY   = 0x000080,

      PURPLE = 0x800080,
      OLIVE  = 0x808000,
      TEAL   = 0x008080,

      ROSE   = 0xff0080,
      ORANGE = 0xff8000,
      LIME   = 0x80ff00,
      AQUA   = 0x00ff80,
      VIOLET = 0x8000ff,
      SKY    = 0x0080ff,

      PINK = 0xffc0c0,
      MINT = 0xc0ffc0,
      ICE  = 0xc0c0ff,
   };

   template <typename type_t>
   static type_t __mod_f(type_t num, type_t mod) {
      type_t result = num - floor(num / mod) * mod;
      if (result < 0) result += mod;
      return result;
   }

   uint32_t rgb(float red, float green, float blue) {
      return (uint32_t(red * 255.f) << 16) | (uint32_t(green * 255.f) << 8) | uint32_t(blue * 255.f);
   }

   uint32_t rgb(double red, double green, double blue) {
      return (uint32_t(red * 255.) << 16) | (uint32_t(green * 255.) << 8) | uint32_t(blue * 255.);
   }

   template <typename type_t>
   uint32_t rgb(type_t red, type_t green, type_t blue) {
      return (uint32_t)red << 16 | (uint32_t)green << 8 | (uint32_t)blue;
   }

   uint32_t hsl(float hue, float sat, float lum) {

      hue /= 60.f;
      float C = (1 - abs(2 * lum - 1)) * sat;
      float X = C * (1 - abs(__mod_f(hue, 2.f) - 1));

      float m = lum - C / 2.f;

      C += m;
      X += m;

      switch ((long)hue % 6) {

      case 0: return uint32_t(C * 255.f) << 16 | uint32_t(X * 255.f) << 8 | uint32_t(m * 255.f);
      case 1: return uint32_t(X * 255.f) << 16 | uint32_t(C * 255.f) << 8 | uint32_t(m * 255.f);
      case 2: return uint32_t(m * 255.f) << 16 | uint32_t(C * 255.f) << 8 | uint32_t(X * 255.f);
      case 3: return uint32_t(m * 255.f) << 16 | uint32_t(X * 255.f) << 8 | uint32_t(C * 255.f);
      case 4: return uint32_t(X * 255.f) << 16 | uint32_t(m * 255.f) << 8 | uint32_t(C * 255.f);
      case 5: return uint32_t(C * 255.f) << 16 | uint32_t(m * 255.f) << 8 | uint32_t(X * 255.f);
      
      }

      return 0;
   }

   uint32_t lerp(uint32_t color0, uint32_t color1, float t) {
      return
         (uint32_t(float(color1 & 0xff0000) * t + float(color0 & 0xff0000) * (1 - t)) & 0xff0000) |
         (uint32_t(float(color1 & 0x00ff00) * t + float(color0 & 0x00ff00) * (1 - t)) & 0x00ff00) |
         (uint32_t(float(color1 & 0x0000ff) * t + float(color0 & 0x0000ff) * (1 - t)) & 0x0000ff);
   }
};