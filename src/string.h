#ifndef STRING_HPP
#define STRING_HPP
#include <stdint.h>
#include <stddef.h>
void itos_hex(uint8_t num,char* out);
void itos_hex(uint16_t num,char* out);
void itos_hex(uint32_t num,char* out);
void itos_hex(uint64_t num,char* out);
size_t strlen(const char* str);
#endif
