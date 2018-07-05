#ifndef _P_TIMER_H
#define _P_TIMER_H

#include "peripherals/base.h"

#define T_BASE (PBASE+0x00003000)

#define TIMER_CS    (T_BASE+0x00)
#define TIMER_CLO   (T_BASE+0x04)
#define TIMER_CHI   (T_BASE+0x08)
#define TIMER_C0    (T_BASE+0x0C)
#define TIMER_C1    (T_BASE+0x10)
#define TIMER_C2    (T_BASE+0x14)
#define TIMER_C3    (T_BASE+0x18)


#define TIMER_CS_M0 (1 << 0)
#define TIMER_CS_M1 (1 << 1)
#define TIMER_CS_M2 (1 << 2)
#define TIMER_CS_M3 (1 << 3)

#endif /* _P_TIMER_H */