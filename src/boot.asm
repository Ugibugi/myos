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
resb 16384 ; 16KiB
stack_top:



section .text
global _start:function (_start.end - _start)
_start:

	mov esp, stack_top
	;experimental
  ;extern terminal_initialize
	;call terimnal_initialize

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
