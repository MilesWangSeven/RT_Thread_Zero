#include "rtconfig.h"
#include "rtdef.h"

/* stack */
#define RT_STACK_WATERMARK  0xdeadbeef 
struct exception_stack_frame
{
    /* registers saved by hardware, when exception happend*/
    rt_uint32_t r0;
    rt_uint32_t r1;
    rt_uint32_t r2;
    rt_uint32_t r3;
    rt_uint32_t r12;
    rt_uint32_t lr;
    rt_uint32_t pc;
    rt_uint32_t psr;
};

struct stack_frame
{
    /* registers saved by software */
    rt_uint32_t r4;
    rt_uint32_t r5;
    rt_uint32_t r6;
    rt_uint32_t r7;
    rt_uint32_t r8;
    rt_uint32_t r9;
    rt_uint32_t r10;
    rt_uint32_t r11;

    struct exception_stack_frame exception_stack_frame;
};

rt_uint8_t *rt_hw_stack_init(void *tentry,
                             void *parameter,
                             rt_uint8_t *stack_addr)
{
    struct stack_frame *stack_frame;
    rt_uint8_t *stk;
    unsigned long i;

    stk = stack_addr + sizeof(rt_uint32_t);

    /* two words align */
    stk = (rt_uint8_t *)RT_ALIGN_DOWN((rt_uint32_t)stk, 8);

    stk -= sizeof(struct stack_frame);    

    stack_frame = (struct stack_frame *)stk;

    for (i = 0; i < sizeof(struct stack_frame) / sizeof(rt_uint32_t); i++)
    {
        ((rt_uint32_t *)stack_frame)[i] = RT_STACK_WATERMARK;
    }

    stack_frame->exception_stack_frame.r0 = (rt_uint32_t)parameter;
    stack_frame->exception_stack_frame.r1 = 0;
    stack_frame->exception_stack_frame.r2 = 0;
    stack_frame->exception_stack_frame.r3 = 0;
    stack_frame->exception_stack_frame.r12 = 0;
    stack_frame->exception_stack_frame.lr = 0;  /*TODO left zero */
    stack_frame->exception_stack_frame.pc = (rt_uint32_t)tentry;
    stack_frame->exception_stack_frame.psr = 0x01000000L;

    return stk;
}
