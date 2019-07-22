#include "string.h"

void itos_hex(uint8_t num,char* out)
{
    out[0] = '0';
    out[1] = 'x';
    char* dst = out + 2;
    for(int i=0;i<2;++i)dst[1-i] = "0123456789ABCDEF"[(num >> (4*i))& 0xF];
    dst[2] = '\0';
}
void itos_hex(uint16_t num,char* out)
{
    out[0] = '0';
    out[1] = 'x';
    char* dst = out + 2;
    for(int i=0;i<4;++i)dst[3-i] = "0123456789ABCDEF"[(num >> (4*i))& 0xF];
}
void itos_hex(uint32_t num,char* out)
{
    out[0] = '0';
    out[1] = 'x';
    char* dst = out + 2;
    for(int i=0;i<8;++i)dst[7-i] = "0123456789ABCDEF"[(num >> (4*i))& 0xF];
    dst[8] = '\0';
}
void itos_hex(uint64_t num,char* out)
{
    out[0] = '0';
    out[1] = 'x';
    char* dst = out + 2;
    for(int i=0;i<16;++i)dst[15-i] = "0123456789ABCDEF"[(num >> (4*i))& 0xF];
    dst[16] = '\0';
}
size_t strlen(const char* str)
{
	size_t len = 0;
	while (str[len])len++;
	return len;
}
