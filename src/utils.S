.globl getcpuid
getcpuid:
    mrs     x0, mpidr_el1   // Read from a special MPIDR_EL1 register which contains core ID
                            // mrs = Move PSR status/flags to register (PSR = Program Status Register)
    ret                    

.globl get_el
get_el:
    mrs     x0, CurrentEL
    lsr     x0, x0, #2
    ret

.globl getsp
getsp:
    mov     x0, sp
    ret

.globl put32
put32:
    str w1,[x0]     //str = Unpriveleged Store, byte, halfword, or word
                    // w1 = first word (32bits) of x1 register [  x1  |  w1  ]
                    //[x0] => get the real value from the memory addressed in x0
    ret

.globl get32
get32:
    ldr w0,[x0]     //ldr = load with immediate offset
    ret

.globl delay
delay:
    subs x0, x0, #1
    bne delay
    ret

.globl set_pgd
set_pgd:
    msr     ttbr0_el1, x0
    tlbi vmalle1is
    DSB ISH //ensure completion of TLB invalidation
    isb
    ret

.globl get_pgd
get_pgd:
    mov x1, 0
    ldr x0, [x1]
    mov x0, 0x1000
    msr ttbr0_el1, x0
    ldr x0, [x1]
    ret
