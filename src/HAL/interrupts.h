
#ifndef INTERRUPTS_H
#define INTERRUPTS_H
#include <stdint.h>
typedef void (*IRQ_handler)();

struct IDT_entry
{
  uint16_t  lowOffset;
  uint16_t  selector;
  uint8_t   reserved;
  uint8_t   flags;
  uint16_t  highOffset;
}__attribute__((packed));
extern "C" void setupIDT();
void setIntHandler(uint8_t num, IRQ_handler address);
void runInterrupt(int num);
extern "C" void configure_PIC();
extern "C" void load_IDT(void*);
extern "C" void test_interrupt();
extern "C" void default_handler();


#endif
