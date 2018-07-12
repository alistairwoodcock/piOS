#include "mm.h"
#include "sched.h"
#include "entry.h"
#include "printf.h"
#include "fork.h"
#include "utils.h"

int copy_process(unsigned long clone_flags, unsigned long fn, unsigned long arg)
{
    preempt_disable();
    struct task_struct *p;

    unsigned long page = allocate_kernel_page();
    p = (struct task_struct *) page;

    if(!p){
        printf("get free page failed\r\n");
        printf("p: %x\r\n", p);
        return -1;
    }

    struct pt_regs *childregs = task_pt_regs(p);
    
    if(clone_flags & PF_KTHREAD){
        p->cpu_context.x19 = fn;
        p->cpu_context.x20 = arg;
    } else {
        struct pt_regs *cur_regs = task_pt_regs(current);
        *cur_regs = *childregs;
        childregs->regs[0] = 0;
        copy_virt_memory(p);
    }

    p->flags = clone_flags;
    p->priority = current->priority;
    p->state = TASK_RUNNING;
    p->counter = p->priority;
    p->preempt_count = 1; //disable preemtion until schedule_tail
    
    p->cpu_context.pc = (unsigned long)ret_from_fork;
    p->cpu_context.sp = (unsigned long)childregs;
      
    int pid = nr_tasks++;
    task[pid] = p;

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
    return pid;
}

int move_to_user_mode(unsigned long start, unsigned long size, unsigned long pc)
{
    struct pt_regs *regs = task_pt_regs(current);
    regs->pstate = PSR_MODE_EL0t;
    regs->pc = pc;
    regs->sp = 2 * PAGE_SIZE;
    unsigned long code_page = allocate_user_page(current, 0);
    if(code_page == 0){
        return -1;
    }
    memcpy(start, code_page, size);
    set_pgd(current->mm.pgd);
    return 0;
}

struct pt_regs * task_pt_regs(struct task_struct *tsk){
    unsigned long p = (unsigned long)tsk + THREAD_SIZE - sizeof(struct pt_regs);
    return (struct pt_regs *)p;
}

