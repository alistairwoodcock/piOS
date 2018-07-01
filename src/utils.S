.globl getcpuid
getcpuid:
    mrs     x0, mpidr_el1   // Read from a special MPIDR_EL1 register which contains core ID
                            // mrs = Move PSR status/flags to register (PSR = Program Status Register)
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