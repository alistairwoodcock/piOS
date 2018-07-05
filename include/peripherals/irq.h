#ifndef _P_IRQ_H
#define _P_IRQ_H

#include "peripherals/base.h"

#define IRQ_BASE                (PBASE+0x0000B200)

#define IRQ_BASIC_PENDING       (IRQ_BASE+0x00)
#define IRQ_PENDING_1           (IRQ_BASE+0x04)
#define IRQ_PENDING_2           (IRQ_BASE+0x08)
#define FIQ_CONTROL             (IRQ_BASE+0x0C)
#define ENABLE_IRQS_1           (IRQ_BASE+0x10)
#define ENABLE_IRQS_2           (IRQ_BASE+0x14)
#define ENABLE_BASIC_IRQS       (IRQ_BASE+0x18)
#define DISABLE_IRQS_1          (IRQ_BASE+0x1C)
#define DISABLE_IRQS_2          (IRQ_BASE+0x20)
#define DISABLE_BASIC_IRQS      (IRQ_BASE+0x24)


#define ARM_TIMER_IRQ           (1 << 0)

#define AUX_IRQ                 (1 << 29)

#define SYSTEM_TIMER_IRQ_0      (1 << 0)
#define SYSTEM_TIMER_IRQ_1      (1 << 1)
#define SYSTEM_TIMER_IRQ_2      (1 << 2)
#define SYSTEM_TIMER_IRQ_3      (1 << 3)


#endif /* _P_IRQ_H */