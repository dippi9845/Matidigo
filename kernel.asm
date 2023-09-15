bits 32			;nasm directive - 32 bit
section .text

global start
extern cmain    ;cmain is defined in a c file

start:
  cli 			                ;block interrupts
  mov esp, start_stack_space	;set stack pointer
  call cmain
  hlt		 	                ;halt the CPU

section .bss
resb 8192		;8KB for stack
start_stack_space: