#include <stdint.h>
void debug_write(const char* str)
{
  uint16_t* data = (uint16_t*)0xB8000;
  int x = 0;
  while(*str != 0)
  {
    data[x] = (0x15*256)+(*str);
    str++;
    x++;

  }
}
