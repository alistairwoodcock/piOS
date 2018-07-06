#include "mm.h"
#include "sched.h"
#include "entry.h"
#include "printf.h"

int copy_process(unsigned long fn, unsigned long arg)
{
    preempt_disable();
    struct task_struct *p;

    p = (struct task_struct *) get_free_page();
    if(!p){
        printf("get free page railed\r\n");
        printf("p: %x\r\n", p);
        return 0;
    }

    p->priority = current->priority;
    p->state = TASK_RUNNING;
    p->counter = p->priority;
    p->preempt_count = 1; //disable preemtion until schedule_tail
    
    p->cpu_context.x19 = fn;
    p->cpu_context.x20 = arg;
    p->cpu_context.pc = (unsigned long)ret_from_fork;
    p->cpu_context.sp = (unsigned long)p + THREAD_SIZE;
      
    int res;
    res = add_task(p);

    if(!res){
        printf("add task failed\r\n");
        printf("res: %i\r\n", res);
        return 0;
    }

    printf("task_struct: \r\n");
    printf("sizeof(task_struct*): %i\r\n", sizeof(struct task_struct*));
    printf("p: %x\r\n", p);
    printf("fn: %x\r\n", fn);
    printf("arg: %x\r\n", arg);
    printf("x19: %x\r\n", p->cpu_context.x19);
    printf("x20: %x\r\n", p->cpu_context.x20);
    printf("pc: %x\r\n", p->cpu_context.pc);
    printf("sp: %x\r\n", p->cpu_context.sp);
    
    preempt_enable();
    return 1;
}