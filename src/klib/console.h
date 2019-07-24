#ifndef CONSOLE_H
#define CONSOLE_H
#include <stddef.h>
#include <stdint.h>
struct ioflags
{
  enum class fgcolor
  {
    black,
    blue,
    green,
    cyan,
    red,
    magenta,
    brown,
    lightgrey,
    darkgrey,
    lightblue,
    lightgreen,
    lightcyan,
    lightred,
    lightmagenta,
    lightbrown,
    white
  };
  enum class bgcolor
  {
    black,
    blue,
    green,
    cyan,
    red,
    magenta,
    brown,
    lightgrey,
    darkgrey,
    lightblue,
    lightgreen,
    lightcyan,
    lightred,
    lightmagenta,
    lightbrown,
    white
  };
};
enum VGAcolor {
	VGA_COLOR_BLACK = 0,
	VGA_COLOR_BLUE = 1,
	VGA_COLOR_GREEN = 2,
	VGA_COLOR_CYAN = 3,
	VGA_COLOR_RED = 4,
	VGA_COLOR_MAGENTA = 5,
	VGA_COLOR_BROWN = 6,
	VGA_COLOR_LIGHT_GREY = 7,
	VGA_COLOR_DARK_GREY = 8,
	VGA_COLOR_LIGHT_BLUE = 9,
	VGA_COLOR_LIGHT_GREEN = 10,
	VGA_COLOR_LIGHT_CYAN = 11,
	VGA_COLOR_LIGHT_RED = 12,
	VGA_COLOR_LIGHT_MAGENTA = 13,
	VGA_COLOR_LIGHT_BROWN = 14,
	VGA_COLOR_WHITE = 15,
};
struct VGAcolorinfo
{
  VGAcolor fg_color : 4;
  VGAcolor bg_color : 4;
  operator uint8_t()
  {
    return fg_color | bg_color << 4;
  }
};
struct VGAentry
{
  VGAentry(uint8_t ch,VGAcolorinfo c);
  uint8_t character;
  uint8_t color;
};
const size_t VGA_WIDTH = 80;
const size_t VGA_HEIGHT = 25;
class Console
{
	public:
	Console();
	void write(const char* str);
	void putchar(const char c);
  void clrscr();
  void endl();
  Console& operator<<(ioflags::fgcolor c);
  Console& operator<<(ioflags::bgcolor c);
  private:
  bool hexint=true;
  VGAcolorinfo curr_color={VGA_COLOR_WHITE,VGA_COLOR_BLACK};
  size_t pos_x=0;
  size_t pos_y=0;
  VGAentry* data;
};
Console& operator<<(Console& c, const char* str);
Console& operator<<(Console& c,uint8_t num);
Console& operator<<(Console& c,uint16_t num);
Console& operator<<(Console& c,uint32_t num);
Console& operator<<(Console& c,uint64_t num);
Console& operator<<(Console& c,int num);
#endif
