bits 32			;nasm directive - 32 bit
section .text

global start
extern cmain    ;cmain is defined in a c file

start:
  cli 			;block interrupts
  mov esp, start_stack_space	
  call cmain
  hlt		 	;halt the CPU
