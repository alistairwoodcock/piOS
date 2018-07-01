#include "mm.h"

.section ".text.boot"

.globl _start
_start:
    mrs     x0, mpidr_el1   // Read from a special MPIDR_EL1 register which contains core ID
                            // mrs = Move PSR status/flags to register (PSR = Program Status Register)
    and     x0, x0, #0xFF   // Check processor id
    
    cbz     x0, master      // Hang for all non-primary CPU 
                            // cbz = Compare and Branch on Zero
                            // so, if 0 we jump to master
    b       core_setup
   

proc_hang:
    b       proc_hang       // infinite loop town

master:                     
    adr     x0, bss_begin   //ADR = generate a register-relative address
    adr     x1, bss_end     
    sub     x1, x1, x0
    bl      memzero         //Branch with link (effectively a function call)
                            //Copies the next instruction addr into the 
                            //LR (link register) used to hold the return
                            //address for a fucntion call
 
    mov     sp, #LOW_MEMORY
    
    mrs     x0, mpidr_el1
    and     x0, x0, #0xFF
    bl      kernel_main      
    
    b       proc_hang       // should never come here


core_setup:
    mov     sp, #LOW_MEMORY
    
    mrs     x0, mpidr_el1
    and     x0, x0, 0xFF
    lsl     x0, x0, #15
    bl      delay

    mrs     x0, mpidr_el1
    and     x0, x0, 0xFF    
    bl kernel_main
    
    b proc_hang
