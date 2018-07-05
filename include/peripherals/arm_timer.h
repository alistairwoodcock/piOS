#ifndef _P_ARM_TIMER_H
#define _P_ARM_TIMER_H

#include "peripherals/base.h"

#define A_T_BASE (PBASE+0x0000B400)

#define A_TIMER_LOAD        (A_T_BASE+0x00)
#define A_TIMER_VAL         (A_T_BASE+0x04)
#define A_TIMER_CTRL        (A_T_BASE+0x08)
#define A_TIMER_IRQ_CLEAR   (A_T_BASE+0x0C)
#define A_TIMER_IRQ_RAW     (A_T_BASE+0x10)
#define A_TIMER_IRQ_MASKED  (A_T_BASE+0x14)
#define A_TIMER_RELOAD      (A_T_BASE+0x18)


#define A_TIMER_CLEAR_WRITE (1 << 0)


#define A_TIMER_CTRL_32BIT  (1 << 1)
#define A_TIMER_INTERRUPT_ENABLE (1 << 5)
#define A_TIMER_ENABLE      (1 << 7)

#define A_TIMER_CTRL_VAL    (A_TIMER_ENABLE | A_TIMER_INTERRUPT_ENABLE | A_TIMER_CTRL_32BIT)



#endif /* _P_ARM_TIMER_H */