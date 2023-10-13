OUTPUT_FORMAT(elf32-i386)
ENTRY(start)
SECTIONS
{
   . = 0x100000;
   .text : { *(.text) }
   
   .data : { 

      // The variable start_ctors is set equal to the current point in the section.
      start_ctors = .;

      // All content of the .init_array sections is kept (preserved), contains initialization routines to be executed at program startup.
      KEEP(*( .init_array ));

      // The content of the .init_array.* sections is kept and is required to be preserved according to initialization priority.
      KEEP(*(SORT_BY_INIT_PRIORITY( .init_array.* )));

      // The variable end_ctors is set equal to the current point in the section.
      end_ctors = .;

      *(.data) 
   }
   
   .bss  : { *(.bss)  }

   // Discard all sections with the names .fini_array and .comment from the final output.
   /DISCARD/ : { *(.fini_array*) *(.comment) }

}