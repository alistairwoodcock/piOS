#include "arm/sysregs.h"

//Swtich to EL1 
//param 1 (x0) is the  adr for where to retun after this call
.globl switch_to_el1
switch_to_el1:
    mov     x1, x0 //storing addr here for later use

    //disable MMU in System Control Register 
    //because we don't have any Virtual Memory yet
    ldr     x0, =SCTLR_EL1_VALUE_MMU_DISABLED
    msr     sctlr_el1, x0

    //Hypervisor Control Register is responsible for
    //the execution state at EL1 so we need to set it
    ldr     x0, =HCR_VALUE
    msr     hcr_el2, x0

    //Setting security controls. EL2 executes at AArch64
    //and all lower exception levels will be "non secure"
    ldr     x0, =SCR_VALUE
    msr     scr_el3, x0

    //Enable Floating Point and SIMD
    ldr     x0, =CPACR_EL1_VALUE
    msr     cpacr_el1, x0

    //Saved Program Status Register
    // All interrupts will be masked (disabled)
    // Using EL1 dedicated stack pointer
    ldr     x0, =SPSR_EL1_VALUE
    msr     spsr_el3, x0

    bl      get_el
    cmp     x0, #3
    beq     exception_from_el3
    cmp     x0, #2
    beq     exception_from_el2
    b       exit_switch_to_el1

    exception_from_el3:
        //we return after changing the Exception level
        //to x1 where we stored the return addr from the param
        mov     x0, x1 
        msr     elr_el3, x0
        eret

    exception_from_el2:
        //we return after changing the Exception level
        //to x1 where we stored the return addr from the param
        mov     x0, x1 
        msr     elr_el2, x0
        eret

    exit_switch_to_el1:
        ret



.globl switch_to_el2
switch_to_el2:
    mov     x1, x0

    //disable MMU in System Control Register 
    //because we don't have any Virtual Memory yet
    ldr     x0, =SCTLR_EL2_VALUE_MMU_DISABLED
    msr     sctlr_el2, x0

    //Hypervisor Control Register is responsible for
    //the execution state at EL1 so we need to set it
    ldr     x0, =HCR_VALUE
    msr     hcr_el2, x0

    //Setting security controls. EL2 executes at AArch64
    //and all lower exception levels will be "non secure"
    ldr     x0, =SCR_VALUE
    msr     scr_el3, x0

    //Saved Program Status Register
    // All interrupts will be masked (disabled)
    // Using EL1 dedicated stack pointer
    ldr     x0, =SPSR_EL2_VALUE
    msr     spsr_el3, x0

    //we return after changing the Exception level
    //to  el1_entry when eret is called
    mov     x0, x1 
    msr     elr_el3, x0

    eret