#ifndef _P_UART_H
#define _P_UART_H

#include "peripherals/base.h"

#define UART_BASE   (PBASE + 0x201000)

#define UART_DR     (UART_BASE + 0x0)
#define UART_RSRECR (UART_BASE + 0x4)
#define UART_FR     (UART_BASE + 0x18)
#define UART_ILPR   (UART_BASE + 0x20)
#define UART_IBRD   (UART_BASE + 0x24)
#define UART_FBRD   (UART_BASE + 0x28)
#define UART_LCRH   (UART_BASE + 0x2c)
#define UART_CR     (UART_BASE + 0x30)
#define UART_IFLS   (UART_BASE + 0x34)
#define UART_IMSC   (UART_BASE + 0x38)
#define UART_RIS    (UART_BASE + 0x3c)
#define UART_MIS    (UART_BASE + 0x40)
#define UART_ICR    (UART_BASE + 0x44)
#define UART_DMACR  (UART_BASE + 0x48)

#endif /* _P_UART_H */