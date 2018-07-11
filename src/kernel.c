#include "mini_uart.h"
#include "printf.h"
#include "irq.h"
#include "timer.h"
#include "utils.h"
#include "fork.h"
#include "sched.h"
#include "sys.h"

void user_process1(char* array)
{
    if(array[0] == '1'){
        printf("changing priority\r\n");
        call_sys_priority(5);
        printf("priority changed!!\r\n");
    }

    char buf[2] = {0};
    while(1){
        for(int i = 0; i < 5; i++){
            buf[0] = array[i];
            call_sys_write(buf);
            delay(100000);
        }
    }
}

void user_process(){
    char* buf = "User process started\r\n";
    call_sys_write(buf);

    unsigned long stack = call_sys_malloc();
    if(stack < 0){
        printf("Error while allocating stack for process 1\r\n");
        return;
    }

    int err = call_sys_clone((unsigned long)&user_process1, (unsigned long)"12345", stack);
    if(err < 0){
        printf("Error while cloning process 1\r\n");
        return;
    }

    stack = call_sys_malloc();
    if(stack < 0){
        printf("Error while allocating stack for process 2\r\n");
        return;
    }

    err = call_sys_clone((unsigned long)&user_process1, (unsigned long)"abcd", stack);
    if(err < 0){
        printf("Error while cloning process 2\r\n");
        return;
    }

    call_sys_exit();
}

void kernel_process(){
    printf("Kernel process started. EL %i\r\n", get_el());
    int err = move_to_user_mode((unsigned long)&user_process);
    if(err < 0){
        printf("Error while moving process to user mode \r\n");
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

    // for(int i = 1; i < 5000; i++)
    // {
    printf("creating process...\r\n");
    int copied;

    copied = copy_process(PF_KTHREAD, (unsigned long)&kernel_process, 0, 0);
    
    if (!copied) {
        printf("error while starting process");
        return;
    }

    delay(2500000);

    // // }

    while (1){
        schedule();
    }
}

void kernel_exit(unsigned long id)
{
    delay(10000000 * id);
    printf("kernel at core %u exited.\r\n", id);
}
