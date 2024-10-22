#include "terminal.h"

/* @param mode
*    PRE_CURSOR: Clear from the cursor to the end of the screen;
*    POS_CURSOR: Clear from the cursor to the beginning of the screen;
*    ENTIRE: Clear the entire screen.
*    CLEANSE: Clear the entire screen and delete all lines saved in the scrollback.
*/
void esc::clear(csi mode) {
   printf_s("\e[%hhuJ", mode);
}

/* @param mode
 *    PRE_CURSOR: Clear from the cursor to the end of the line;
 *    POS_CURSOR: Clear from the cursor to the beginning of the line;
 *    ENTIRE: Clear the entire line.
*/
void esc::clear_line(csi mode) {
   printf_s("\e[%hhuK", mode);
}

/* @param direction
 *    UP: Move the cursor amount of cells upwards;
 *    DOWN: Move the cursor amount of cells downwards;
 *    FORWARD: Move the cursor amount of cells forward;
 *    BACK: Move the cursor amount of cells backwards.
 *
 * @param amount
 *    defines the amount (default 1) of cells the cursor will move in the given
 *    direction.
*/
void esc::move(csi direction, word amount) {
   printf_s("\e[%hu%c", amount, direction + 'A');
}

/* @param direction
 *    UP: Move the cursor amount of lines upwards;
 *    DOWN: Move the cursor amount of lines downwards;
 *
 * @param amount
 *    defines the amount (default 1) of lines the cursor will move in the given
 *    direction.
*/
void esc::move_line(csi direction, word amount) {
   printf_s("\e[%hu%c", amount, direction + 'E');
}

/* @param direction
 *    UP: Scroll page up by amount lines;
 *    DOWN: Scroll page down by amount lines;
 *
 * @param amount
 *    defines the amount (default 1) of lines the cursor will scroll in the given
 *    direction.
*/
void esc::scroll(csi direction, word amount) {
   printf_s("\e[%hhu;%huf", direction + 'S', amount);
}

/* @param xpos, ypos
 *    moves the cursor to the specified position by xpos and ypos.
*/
void esc::move_to(word xpos, word ypos) {
   // The coordinate system starts at one
   printf_s("\e[%hu;%huH", xpos + 1, ypos + 1);
}

/* Clear all styles apllied
*/
void esc::reset() {
   printf_s("\e[0m");
}

/* Set the foreground according to predefinided colors.
 *
 * @param color
 *    BLACK, RED, GREEN, YELLOW, BLUE, MAGENTA, CYAN, WHITE or RESET.
 *    BRIGHT_<color> to get a brighter version of the color.
 * @param ground
 *    selects amongst BACKGROUND AND FOREGROUND
*/
void esc::color(clr color, grnd ground) {
   // Backgroung literal are 10 plus foreground ones
   printf_s("\e[%hhum", ground == BACKGROUNG ? color + 10 : color);
}

/* Reset colors to default color (specified by the system).
*/
void esc::color() {
   printf_s("\e[39;49m");
}

/* Set the specified ground to and 24-bit RGB color
 *
 * @param ground
 *    selects amongst BACKGROUND AND FOREGROUND
 * @param red
 *    especifies the red channel value [0, 255].
 * @param green
 *    especifies the green channel value [0, 255].
 * @param blue
 *    especifies the blue channel value [0, 255].
*/
void esc::color(grnd ground, byte red, byte green, byte blue) {
   printf_s("\e[%hhu;2;%hhu;%hhu;%hhum", ground, red, green, blue);
}

/* Set the specified ground to and 24-bit RGB color
 *
 * @param ground
 *    selects amongst BACKGROUND AND FOREGROUND
 * @param color
 *    especifies an RGB color 0xRRGGBB.
*/
void esc::color(grnd ground, rgb color) {
   printf_s("\e[%hhu;2;%lu;%lu;%lum", ground,
      (color & 0xFF0000) >> 16, (color & 0x00FF00) >> 8, (color & 0x0000FF));
}

/* Set or unset bold to the font.
 *
 * @param on true for set and false for unset.
*/
void esc::bold(bool on) {
   printf_s("\e[%hhum", byte(on ? 1 : 22));
}

/* Set or unset light (faint) to the font.
 *
 * @param on true for set and false for unset.
*/
void esc::light(bool on) {
   printf_s("\e[%hhum", byte(on ? 2 : 22));
}

/* Set or unset italic to the font.
 *
 * @param on true for set and false for unset.
*/
void esc::italic(bool on) {
   printf_s("\e[%hhum", byte(on ? 3 : 23));
}

/* Set or unset underline to the font.
 *
 * @param on true for set and false for unset.
*/
void esc::underline(bool on) {
   printf_s("\e[%hhum", byte(on ? 4 : 24));
}

/* Swap and unswap foreground and background colors
 *
 * @param on true for swap and false for unswap.
*/
void esc::invert(bool on) {
   printf_s("\e[%hhum", byte(on ? 7 : 27));
}

/* Set or unset strike to the font.
 *
 * @param on true for set and false for unset.
*/
void esc::strike(bool on) {
   printf_s("\e[%hhum", byte(on ? 9 : 29));
}

/* Set the style of printing
 *
 * @param foreground, background
 *    BLACK, RED, GREEN, YELLOW, BLUE, MAGENTA, CYAN, WHITE or RESET.
 *    BRIGHT_<color> to get a brighter version of the color.
 * @param style
 * 
*/
void esc::style(byte style, clr foreground, clr background) {

   printf_s("\e[%hhu;%hhu", foreground, 10 + background);

   if (style & BOLD)      printf_s(";1");
   if (style & LIGHT)     printf_s(";2");
   if (style & ITALIC)    printf_s(";3");
   if (style & UNDERLINE) printf_s(";4");
   if (style & STRIKE)    printf_s(";9");
   if (style & INVERT)    printf_s(";7");

   printf_s("m");
}

void esc::style(byte style, rgb foreground, rgb background) {

   printf_s("\e[0");
   
   if (foreground != DEFAULT) printf_s(";38;2;%lu;%lu;%lu",
      (foreground & 0xFF0000) >> 16, (foreground & 0x00FF00) >> 8, (foreground & 0x0000FF));

   if (background != DEFAULT) printf_s(";48;2;%lu;%lu;%lu",
      (background & 0xFF0000) >> 16, (background & 0x00FF00) >> 8, (background & 0x0000FF));

   if (style & BOLD)      printf_s(";1");
   if (style & LIGHT)     printf_s(";2");
   if (style & ITALIC)    printf_s(";3");
   if (style & UNDERLINE) printf_s(";4");
   if (style & STRIKE)    printf_s(";9");
   if (style & INVERT)    printf_s(";7");

   printf_s("m");
}
