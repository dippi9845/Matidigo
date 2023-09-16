bits 32			;nasm directive - 32 bit
section .text

    ;multiboot specification

    align 4
    dd 0x1BADB002            ; magic field
    dd 0x00                  ; flags field
    dd - (0x1BADB002 + 0x00) ; checksum field m+f+c should be zero

global start
extern cmain    ;cmain is defined in a c file
global load_idt


load_idt:
	mov edx, [esp + 4]
	lidt [edx]
	sti
	ret



start:
  cli 			                ;block interrupts
  mov esp, start_stack_space	;set stack pointer
  call cmain
  hlt		 	                ;halt the CPU

section .bss
resb 8192		;8KB for stack
start_stack_space: