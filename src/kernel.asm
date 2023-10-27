bits 32			;nasm directive - 32 bit
section .text

    ;multiboot specification

    align 4
    dd 0x1BADB002            ; magic field
    dd 0x03                  ; flags field
    dd - (0x1BADB002 + 0x03) ; checksum field m+f+c should be zero

global start

extern CMain    ; is defined in a cpp file
extern CallConstructors 

start:
	cli 			                ;block interrupts
	mov esp, start_stack_space	;set stack pointer
	call CallConstructors
	push eax
	push ebx
	call CMain
			 	                

stop:
	cli
	hlt ;halt the CPU
	jmp stop

section .bss
resb 8192		;8KB for stack
start_stack_space: