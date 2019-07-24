#include "debug_funcs.h"
#include "interrupts.h"
extern "C" void irq0();
extern "C" void irq1();
extern "C" void irq2();
extern "C" void irq3();
extern "C" void irq4();
extern "C" void irq5();
extern "C" void irq6();
extern "C" void irq7();
extern "C" void irq8();
extern "C" void irq9();
extern "C" void irq10();
extern "C" void irq11();
extern "C" void irq12();
extern "C" void irq13();
extern "C" void irq14();
extern "C" void irq15();
IDT_entry IDT [256];

extern "C" void setupIDT()
{
  //BRZYDKIE!!!
  //ale assembler w gcc jest brzydszy
  //Może później to naprawie
  configure_PIC();
  const uint8_t IRQ32 = 32;
  setIntHandler(IRQ32,irq0);
  setIntHandler(IRQ32+1,irq1);
  setIntHandler(IRQ32+2,irq2);
  setIntHandler(IRQ32+3,irq3);
  setIntHandler(IRQ32+4,irq4);
  setIntHandler(IRQ32+5,irq5);
  setIntHandler(IRQ32+6,irq6);
  setIntHandler(IRQ32+7,irq7);
  setIntHandler(IRQ32+8,irq8);
  setIntHandler(IRQ32+9,irq9);
  setIntHandler(IRQ32+10,irq10);
  setIntHandler(IRQ32+11,irq11);
  setIntHandler(IRQ32+12,irq12);
  setIntHandler(IRQ32+13,irq13);
  setIntHandler(IRQ32+14,irq14);
  setIntHandler(IRQ32+15,irq15);
  uint32_t idtaddr = (uint32_t)IDT;
  uint32_t idtptr[2];
  idtptr[0] = (sizeof(IDT_entry)*256) + ((idtaddr & 0xffff) << 16);
  idtptr[1] = idtaddr >> 16;
  load_IDT(idtptr);

}
void setIntHandler(uint8_t num, IRQ_handler address)
{
  uint32_t addr = (uint32_t)address;
  IDT[num].lowOffset = addr & 0xFFFF;
  IDT[num].selector = 0x8;
  IDT[num].reserved = 0x0;
  IDT[num].flags = 0x8E;
  IDT[num].highOffset = (addr & 0xFFFF0000) >> 16;
}
extern "C" void default_handler()
{
  debug_write("INTERRUPT CALLED!!!");
}
