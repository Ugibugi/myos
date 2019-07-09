section .init
global _init:function
_init:
	push ebp
	mov ebp, esp
	;gcc code goes here


section .fini
global _fini:function
_fini:
	push ebp
	mov ebp, esp
	;gcc code goes here

