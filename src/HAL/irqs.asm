global irq0
global irq1
global irq2
global irq3
global irq4
global irq5
global irq6
global irq7
global irq8
global irq9
global irq10
global irq11
global irq12
global irq13
global irq14
global irq15

global configure_PIC
global load_IDT
global test_interrupt
extern default_handler

section .text
test_interrupt:
  int 33
  ret
configure_PIC:
  mov al, 0x11
  out 0x20, al
  out 0xA0, al

  mov al, 0x20
  out 0x21, al
  mov al, 0x28
  out 0xA1, al

  mov al, 0x4
  out 0x21, al
  mov al, 0x2
  out 0xA1, al

  mov al, 0x1
  out 0x21, al
  out 0xA1, al

  mov al, 0x0
  out 0x21, al
  out 0xA1, al
  ret
load_IDT:
  mov edx, [esp+4]
  lidt [edx]
  sti
  ret

  irq0:
    pusha
    call default_handler
    mov al, 0x20
    out 0x20, al
    popa
    iret

  irq1:
    pusha
    call default_handler
    mov al, 0x20
    out 0x20, al
    popa
    iret

  irq2:
    pusha
    call default_handler
    mov al, 0x20
    out 0x20, al
    popa
    iret

  irq3:
    pusha
    call default_handler
    mov al, 0x20
    out 0x20, al
    popa
    iret

  irq4:
    pusha
    call default_handler
    mov al, 0x20
    out 0x20, al
    popa
    iret

  irq5:
    pusha
    call default_handler
    mov al, 0x20
    out 0x20, al
    popa
    iret
  irq6:
    pusha
    call default_handler
    mov al, 0x20
    out 0x20, al
    popa
    iret

  irq7:
    pusha
    call default_handler
    mov al, 0x20
    out 0x20, al
    popa
    iret

  irq8:
    pusha
    call default_handler
    mov al, 0x20
    out 0xA0, al
    out 0x20, al
    popa
    iret

  irq9:
    pusha
    call default_handler
    mov al, 0x20
    out 0xA0, al
    out 0x20, al
    popa
    iret

  irq10:
    pusha
    call default_handler
    mov al, 0x20
    out 0xA0, al
    out 0x20, al
    popa
    iret

  irq11:
    pusha
    call default_handler
    mov al, 0x20
    out 0xA0, al
    out 0x20, al
    popa
    iret

  irq12:
    pusha
    call default_handler
    mov al, 0x20
    out 0xA0, al
    out 0x20, al
    popa
    iret

  irq13:
    pusha
    call default_handler
    mov al, 0x20
    out 0xA0, al
    out 0x20, al
    popa
    iret

  irq14:
    pusha
    call default_handler
    mov al, 0x20
    out 0xA0, al
    out 0x20, al
    popa
    iret

  irq15:
    pusha
    call default_handler
    mov al, 0x20
    out 0xA0, al
    out 0x20, al
    popa
    iret
