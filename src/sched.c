#include "sched.h"
#include "mm.h"
#include "irq.h"
#include "printf.h"


static struct task_struct init_task = INIT_TASK;
struct task_struct *current = &(init_task);
struct task_struct **tasks = 0;
int nr_tasks = 0;

int sched_init(void)
{
    struct task_struct **p;

    p = (struct task_struct**) get_free_page();
    if(!p) return 0;

    tasks = p;
    p[0] = &(init_task);
    nr_tasks = 1;

    return 1;
}

int add_task(struct task_struct *new){

    if(nr_tasks * sizeof(struct task_struct*) >= PAGE_SIZE){
        return 0;
    }

    int pid = nr_tasks++;
    tasks[pid] = new;

    printf("%i of %i tasks\r\n", nr_tasks, PAGE_SIZE / sizeof(struct task_struct*));

    return 1;
}

void preempt_disable(void)
{
    current->preempt_count++;
}

void preempt_enable(void)
{
    current->preempt_count--;
}

void _schedule(void)
{
    preempt_disable();
    int next,c;
    struct task_struct * p;

    printf("number of tasks: %i\r\n", nr_tasks);

    while (1) {
        c = -1;
        next = 0;
        for (int i = 0; i < nr_tasks; i++){
            p = tasks[i];
            if (p && p->state == TASK_RUNNING && p->counter > c) {
                c = p->counter;
                next = i;
            }
        }
        if (c) {
            break;
        }
        for (int i = 0; i < nr_tasks; i++) {
            p = tasks[i];
            if (p) {
                p->counter = (p->counter >> 1) + p->priority;
            }
        }
    }

    switch_to(tasks[next]);
    preempt_enable();
}

void schedule(void)
{
    current->counter = 0;
    _schedule();
}

void switch_to(struct task_struct * next) 
{
    if (current == next) return;
    struct task_struct * prev = current;
    current = next;
    
    // current->counter = current->priority;

    // printf("\r\npriority: %u\r\n", current->priority);

    cpu_switch_to(prev, next);
}

void schedule_tail(void) {
    preempt_enable();
}

void timer_tick()
{
    --current->counter;
    printf("\r\n[%i|%i]\r\n", current->counter, current->preempt_count);
    
    if (current->counter>0 || current->preempt_count >0) {
        return;
    }

    current->counter=0;
    enable_irq();
    _schedule();
    disable_irq();
}