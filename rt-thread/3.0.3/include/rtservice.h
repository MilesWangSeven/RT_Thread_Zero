#ifndef __RT_SERVICE_H__
#define __RT_SERVICE_H__

#include "rtconfig.h"
#include "rtdef.h"

extern rt_list_t rt_thread_priority_table[RT_THREAD_PRIORITY_MAX];

rt_inline void rt_list_init(rt_list_t *l)
{
    l->next  = l->prev = l;
}

rt_inline void rt_list_insert_after(rt_list_t *l, rt_list_t *n)
{
    l->next->prev = n;
    n->next = l->next;

    l->next = n;
    n->prev = l;
}

rt_inline void rt_list_insert_before(rt_list_t *l, rt_list_t *n)
{
    l->prev->next = n;
    n->prev = l->prev;

    l->prev = n;
    n->next = l;
}

rt_inline void rt_list_remove(rt_list_t *n)
{
    n->prev->next = n->next;
    n->next->prev = n->prev;

    n->next = n->prev = n;
}

rt_err_t rt_thread_init(struct rt_thread *thread,
                        void (*entry)(void *parameter),
                        void *parameter,
                        void *stack_start,
                        rt_uint32_t stack_size);

rt_uint8_t *rt_hw_stack_init(void *tentry,
                             void *parameter,
                             rt_uint8_t *stack_addr);

void rt_system_scheduler_init(void);
void rt_system_scheduler_start(void);
void rt_schedule(void);
void rt_hw_context_switch_to(rt_uint32_t to);
void rt_hw_context_switch(rt_uint32_t from, rt_uint32_t to);
#endif
