MBALIGN 	equ 1 << 0
MEMINFO 	equ 1 << 1
FLAGS		equ MBALIGN | MEMINFO
MAGIC		equ 0x1BADB002
CHECKSUM 	equ -(MAGIC + FLAGS)


section .multiboot
align 4
	dd MAGIC
	dd FLAGS
	dd CHECKSUM

section .bbs
align 16
stack_bottom:
resb 16384 ; 16KB
stack_top:


;quick copy-paste simple gdt for now (or forever)
section .data
gdt:
  gdt_null:
  dq 0

  gdt_code:
  dw 0FFFFh
  dw 0

  db 0
  db 10011010b
  db 11001111b
  db 0

  gdt_data:
  dw 0FFFFh
  dw 0

  db 0
  db 10010010b
  db 11001111b
  db 0

  gdt_end:

  gdt_desc:
   dw gdt_end - gdt - 1
   dd gdt

section .text
global _start:function (_start.end - _start)
_start:
	cli
	lgdt [gdt_desc]
	sti

	mov esp, stack_top

	extern _init
	call _init

	extern kernel_main
	call kernel_main

	sub esp, 4
	mov [esp], dword 0x0
	extern __cxa_finalize
	call __cxa_finalize
	add esp, 4

	extern _fini
	call _fini


	cli
 .hang: hlt
	jmp .hang
.end:
