#include "fork.h"
#include "printf.h"
#include "utils.h"
#include "sched.h"
#include "mm.h"

void sys_write(char *buf){
    printf(buf);
}

int sys_fork(){
    return copy_process(0, 0, 0);
}

// int sys_clone(unsigned long stack){
//     return copy_process(0,0,0,stack);
// }

// unsigned long sys_malloc(){
//     unsigned long addr = get_free_page();
//     if(!addr){
//         return -1;
//     }

//     return addr;
// }

void sys_exit(){
    exit_process();
}

// void sys_priority(long new_priority){
//     change_priority(new_priority);
// }

void* const sys_call_table[] = {sys_write, sys_fork, sys_exit};