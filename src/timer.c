#include "utils.h"
#include "printf.h"
#include "sched.h"
#include "peripherals/timer.h"
#include "peripherals/arm_timer.h"

const unsigned int interval = 400000;
unsigned int curVal = 0;

void timer_init(void)
{
    curVal = get32(TIMER_CLO);
    curVal += interval;
    put32(TIMER_C1, curVal);
}

void handle_timer_irq(void)
{
    curVal += interval;
    put32(TIMER_C1, curVal);
    put32(TIMER_CS, TIMER_CS_M1);
    timer_tick();
}

void timer_arm_init(void)
{
    put32(A_TIMER_LOAD, interval);
    put32(A_TIMER_CTRL, A_TIMER_CTRL_VAL);
}

void handle_arm_timer_irq(void)
{
    put32(A_TIMER_IRQ_CLEAR, A_TIMER_CLEAR_WRITE);
    printf("Arm Timer interrupt received\n");
}