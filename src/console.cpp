#include "console.h"
#include "string.h"
VGAentry::VGAentry(uint8_t ch, VGAcolorinfo c)
{
  character = ch;
  color = (uint8_t)c;

}
Console::Console()
{
  data = (VGAentry*)0xB8000;
  clrscr();
}
void Console::clrscr()
{
  for (size_t y = 0; y < VGA_HEIGHT; y++) {
    for (size_t x = 0; x < VGA_WIDTH; x++) {
      const size_t index = y * VGA_WIDTH + x;
       data[index] = VGAentry(' ', curr_color);
      }
    }
}
void Console::endl()
{
  if(++pos_y == VGA_HEIGHT)pos_y=0;
  pos_x=0;
}
void Console::putchar(const char c)
{
  if(c == '\n'){endl();return;}
  data[pos_x + VGA_WIDTH*pos_y] = VGAentry(c,curr_color);
  if (++pos_x == VGA_WIDTH)
  {
		pos_x = 0;
		if (++pos_y == VGA_HEIGHT) pos_y = 0;
	}
}
void Console::write(const char* str)
{
  int i=0;
  while(str[i] != 0)
  {
    if(str[i] == '\n') endl();
    else
    {
      data[pos_x + VGA_WIDTH*pos_y] = VGAentry(str[i],curr_color);
      pos_x++;
    }
    i++;
  }
  while(pos_x > VGA_WIDTH)
  {
    pos_x -= VGA_WIDTH;
    pos_y++;
  }
}
Console& Console::operator<<(ioflags::fgcolor c)
{
  switch(c)
  {
    case ioflags::fgcolor::black:       curr_color.fg_color = VGA_COLOR_BLACK;break;
    case ioflags::fgcolor::blue:        curr_color.fg_color = VGA_COLOR_BLUE;break;
    case ioflags::fgcolor::green:       curr_color.fg_color = VGA_COLOR_GREEN;break;
    case ioflags::fgcolor::cyan:        curr_color.fg_color = VGA_COLOR_CYAN;break;
    case ioflags::fgcolor::red:         curr_color.fg_color = VGA_COLOR_RED;break;
    case ioflags::fgcolor::magenta:     curr_color.fg_color = VGA_COLOR_MAGENTA;break;
    case ioflags::fgcolor::brown:       curr_color.fg_color = VGA_COLOR_BROWN;break;
    case ioflags::fgcolor::lightgrey:   curr_color.fg_color = VGA_COLOR_LIGHT_GREY;break;
    case ioflags::fgcolor::darkgrey:    curr_color.fg_color = VGA_COLOR_DARK_GREY;break;
    case ioflags::fgcolor::lightblue:   curr_color.fg_color = VGA_COLOR_LIGHT_BLUE;break;
    case ioflags::fgcolor::lightgreen:  curr_color.fg_color = VGA_COLOR_LIGHT_GREEN;break;
    case ioflags::fgcolor::lightcyan:   curr_color.fg_color = VGA_COLOR_LIGHT_CYAN;break;
    case ioflags::fgcolor::lightred:    curr_color.fg_color = VGA_COLOR_LIGHT_RED;break;
    case ioflags::fgcolor::lightmagenta:curr_color.fg_color = VGA_COLOR_LIGHT_MAGENTA;break;
    case ioflags::fgcolor::lightbrown:  curr_color.fg_color = VGA_COLOR_LIGHT_BROWN;break;
    case ioflags::fgcolor::white:       curr_color.fg_color = VGA_COLOR_WHITE;break;
  }
  return *this;
}
Console& Console::operator<<(ioflags::bgcolor c)
{
  switch(c)
  {
    case ioflags::bgcolor::black:       curr_color.bg_color = VGA_COLOR_BLACK;break;
    case ioflags::bgcolor::blue:        curr_color.bg_color = VGA_COLOR_BLUE;break;
    case ioflags::bgcolor::green:       curr_color.bg_color = VGA_COLOR_GREEN;break;
    case ioflags::bgcolor::cyan:        curr_color.bg_color = VGA_COLOR_CYAN;break;
    case ioflags::bgcolor::red:         curr_color.bg_color = VGA_COLOR_RED;break;
    case ioflags::bgcolor::magenta:     curr_color.bg_color = VGA_COLOR_MAGENTA;break;
    case ioflags::bgcolor::brown:       curr_color.bg_color = VGA_COLOR_BROWN;break;
    case ioflags::bgcolor::lightgrey:   curr_color.bg_color = VGA_COLOR_LIGHT_GREY;break;
    case ioflags::bgcolor::darkgrey:    curr_color.bg_color = VGA_COLOR_DARK_GREY;break;
    case ioflags::bgcolor::lightblue:   curr_color.bg_color = VGA_COLOR_LIGHT_BLUE;break;
    case ioflags::bgcolor::lightgreen:  curr_color.bg_color = VGA_COLOR_LIGHT_GREEN;break;
    case ioflags::bgcolor::lightcyan:   curr_color.bg_color = VGA_COLOR_LIGHT_CYAN;break;
    case ioflags::bgcolor::lightred:    curr_color.bg_color = VGA_COLOR_LIGHT_RED;break;
    case ioflags::bgcolor::lightmagenta:curr_color.bg_color = VGA_COLOR_LIGHT_MAGENTA;break;
    case ioflags::bgcolor::lightbrown:  curr_color.bg_color = VGA_COLOR_LIGHT_BROWN;break;
    case ioflags::bgcolor::white:       curr_color.bg_color = VGA_COLOR_WHITE;break;
  }
  return *this;
}


Console& operator<<(Console& c,const char* str)
{
  c.write(str);
  return c;
}
Console& operator<<(Console& c,uint8_t val)
{
  char buf[32];
  itos_hex(val,buf);
  c.write(buf);
  return c;
}
Console& operator<<(Console& c,uint16_t val)
{
  char buf[32];
  itos_hex(val,buf);
  c.write(buf);
  return c;
}
Console& operator<<(Console& c,uint32_t val)
{
  char buf[32];
  itos_hex(val,buf);
  c.write(buf);
  return c;
}
Console& operator<<(Console& c,uint64_t val)
{
  char buf[32];
  itos_hex(val,buf);
  c.write(buf);
  return c;
}
Console& operator<<(Console& c,int val)
{
  return c << (uint32_t)val;
}
