#ifndef _UART_H
#define _UART_H

void pl_uart_init(void);
char pl_uart_recv(void);
void pl_uart_send(char c);
void pl_uart_send_string(char* str);

#endif /*_UART_H */