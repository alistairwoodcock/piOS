#include "mini_uart.h"
#include "printf.h"
#include "irq.h"
#include "timer.h"
#include "utils.h"
#include "fork.h"
#include "sched.h"

void process(int id)
{
    unsigned int sp = getsp();
    printf("%x:entered process\r\n", sp);

    while(1){
        delay(400000);
        printf("process %i running\r\n", id);
    }
}

void kernel_main(unsigned long id)
{
    if(id != 0) return;
    
    uart_init();
    printf_init(uart_send);

    int init;

    init = sched_init();

    if(!init){
        printf("could not init sched.\r\n");
        return;
    }

    for(int i = 5; i > 0; i--){
        printf("running in %i...\r\n", i);
        delay(2500000);
    }


    irq_vector_init();
    timer_init();
    enable_interrupt_controller();
    enable_irq();

    for(int i = 1; i < 5000; i++)
    {
        printf("creating process %i...\n", i);
        int copied;

        copied = copy_process((unsigned long)&process, (unsigned long)i);
        
        if (!copied) {
            printf("error while starting process %i", i);
            return;
        }

        printf("process %i created...\n", i);

        delay(2500000);
    }

    while (1){
        schedule();
    }
}

void kernel_exit(unsigned long id)
{
    delay(10000000 * id);
    printf("kernel at core %u exited.\r\n", id);
}
