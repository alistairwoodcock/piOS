#include "mini_uart.h"
#include "printf.h"
#include "irq.h"
#include "timer.h"
#include "utils.h"

static unsigned long share = 1;

void read_data(){
    printf("Ready to recevie...\r\n");


    char n1 = uart_recv();
    char n2 = uart_recv();
    char n3 = uart_recv();
    char n4 = uart_recv();

    unsigned long data_len = n4 << 0 | n3 << 8 | n2 << 16 | n1 << 24;

    printf("data_len: %u\r\n", data_len);

    printf("Done receiving\r\n");
}

void next_core(){
    share++;
    if(share > 3) share = 0;
}

void kernel_main(unsigned long id)
{
    delay(1000000);

    if(id == 0) {
        printf_init(uart_send);
        
        uart_init();
        irq_vector_init();
        timer_init();
        enable_interrupt_controller();
        enable_irq();

        char *s = "hello, world!";

        printf("Init finished.\r\n%s\r\n", s);
    }

    while (1){
        delay(1000000);
        continue;

        if(share == id){
            printf("Hello, from processor %u.\r\n", id);

            printf("Options:\r\n");
            printf("(1) Read in data\r\n");
            printf("(2) Next Core\r\n");
            printf("(3) Exception Level\r\n");

            char c = uart_recv();

            switch(c)
            {
                case '1': read_data(); break;
                case '2': next_core(); break;
                case '3': {
                    int el = get_el();
                    printf("Exception level: %i \r\n", el);
                } break;

                default: printf("err: not a valid option\r\n"); break;
            }
        }
    }
}

void kernel_exit(unsigned long id)
{
    printf("kernel %u exited.\r\n", id);
}
