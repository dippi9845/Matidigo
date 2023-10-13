bits 32			;nasm directive - 32 bit
section .text

    ;multiboot specification

    align 4
    dd 0x1BADB002            ; magic field
    dd 0x03                  ; flags field
    dd - (0x1BADB002 + 0x03) ; checksum field m+f+c should be zero

global start
global load_idt
global keyboard_handler
global read_port
global write_port

extern CMain    ; is defined in a cpp file
extern keyboard_handler_main
extern CallConstructors 

read_port:
	mov edx, [esp + 4]
			;al is the lower 8 bits of eax
	in al, dx	;dx is the lower 16 bits of edx
	ret

write_port:
	mov   edx, [esp + 4]    
	mov   al, [esp + 4 + 4]  
	out   dx, al  
	ret

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
  call CallConstructors
  call CMain
  hlt		 	                ;halt the CPU

section .bss
resb 8192		;8KB for stack
start_stack_space: