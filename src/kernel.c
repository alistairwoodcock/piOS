#include <stddef.h>
#include <stdint.h>

#include "printf.h"
#include "utils.h"
#include "timer.h"
#include "irq.h"
#include "fork.h"
#include "sched.h"
#include "mini_uart.h"
#include "sys.h"
#include "user.h"

void kernel_process(){
    printf("Kernel process started. EL %i\r\n", get_el());

    unsigned long begin = (unsigned long)&user_begin;
    unsigned long end = (unsigned long)&user_end;
    unsigned long process = (unsigned long)&user_process;

    int err = move_to_user_mode(begin, end - begin, process - begin);

    if(err < 0){
        printf("Error while moving process to user mode \r\n");
    }
}

void kernel_main(unsigned long id)
{
    
    uart_init();
    printf_init(uart_send);
    
    if(id != 0){
        while(1){
            printf("kernel at core %u doin nothing.\r\n", id);
        }
    }

    for(int i = 5; i > 0; i--){
        printf("running in %i...\r\n", i);
        delay(2500000);
    }

    irq_vector_init();
    timer_init();
    enable_interrupt_controller();
    enable_irq();

    printf("creating process...\r\n");
    int copied;

    copied = copy_process(PF_KTHREAD, (unsigned long)&kernel_process, 0);
    
    if (!copied) {
        printf("error while starting process");
        return;
    }


    while (1){
        schedule();
        printf("Hello, World!\r\n");
        delay(2500000);
    }
}
