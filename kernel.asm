bits 32			;nasm directive - 32 bit
section .text

    ;multiboot specification

    align 4
    dd 0x1BADB002            ; magic field
    dd 0x00                  ; flags field
    dd - (0x1BADB002 + 0x00) ; checksum field m+f+c should be zero

global start
global load_idt
global keyboard_handler

extern cmain    ;cmain is defined in a c file
extern keyboard_handler_main

load_idt:
	mov edx, [esp + 4]
	lidt [edx]
	sti
	ret


keyboard_handler:                 
	call    keyboard_handler_main
	iretd


start:
  cli 			                ;block interrupts
  mov esp, start_stack_space	;set stack pointer
  call cmain
  hlt		 	                ;halt the CPU

section .bss
resb 8192		;8KB for stack
start_stack_space: