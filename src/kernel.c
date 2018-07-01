#include "mini_uart.h"
#include "utils.h"

// static unsigned long share = 0;

void kernel_main(unsigned long id)
{
    if(id == 0) uart_init();

    delay(1000000);

    if(id == 0) uart_send_string("uart init\r\n\n");

    uart_send_string("Hello, from processor ");
    uart_send('0' + (unsigned char)id);
    uart_send_string(".\r\n\n");

    // share++;
    
    while (1){
        // if(id == 0){
        //     uart_send_string("id is zero\n");
        //     delay(32000*8);
        //     uart_send_string("S:");
        //     uart_send(48 + share);
        //     uart_send('\n');
        // } else if(id == 1){
        //     uart_send_string("id is one\n");
        //     delay(32000*12);
        // } else if(id == 2){
        //     uart_send_string("id is two\n");
        //     delay(32000*16);
        // } else if(id == 3){
        //     uart_send_string("id is three\n");
        //     delay(32000*20);
        // } else {
        //     uart_send_string("id is something else?\n");
        // }
        
        // uart_send_string("\n");
    }
}
