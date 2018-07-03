#include "EL.h"
#include "mm.h"

.data
.balign 4
initialized:
    .byte 0

.section ".text.boot"

.globl _start
_start:

    adr     x0, el1_entry
    bl      switch_to_el1

el1_entry:
    mrs     x0, mpidr_el1   // Read from a special MPIDR_EL1 register which contains core ID
                            // mrs = Move PSR status/flags to register (PSR = Program Status Register)
    and     x0, x0, #0xFF   // Check processor id
    
    cbz     x0, master      // Hang for all non-primary CPU 
                            // cbz = Compare and Branch on Zero
                            // so, if 0 we jump to master
    b       core_setup

master:
    adr     x0, bss_begin   //ADR = generate a register-relative address
    adr     x1, bss_end     
    sub     x1, x1, x0
    bl      memzero         //Branch with link (effectively a function call)
                            //Copies the next instruction addr into the 
                            //LR (link register) used to hold the return
                            //address for a fucntion call
    bl      set_stack
    
    // everything is initialized
    // so we can tell the other cores to run
    mov     w0, #1
    ldr     x1, =initialized
    strb    w0, [x1]
    b       run_kernel


core_setup:
    // Wait for the bss to be initialized
    ldr     x1, =initialized
    ldrb    w0, [x1]
    cbz     w0, core_setup

    bl      set_stack
    b       run_kernel


// setup stack pointer
set_stack: 
    mov     x0, #LOW_MEMORY
    mrs     x1, mpidr_el1 //get processor num 0,1,2,3
    and     x1, x1, 0xFF
    add     x1, x1, #1 // add 1 for mult by 1,2,3,4
    mul     x0, x0, x1 // (4MB * 2, 3 or 4)
    mov     sp, x0 
    ret


run_kernel:
    mrs     x0, mpidr_el1
    and     x0, x0, #0xFF
    bl      kernel_main  

    mrs     x0, mpidr_el1
    and     x0, x0, #0xFF
    bl      kernel_exit
proc_hang:
    b       proc_hang       // infinite loop town



