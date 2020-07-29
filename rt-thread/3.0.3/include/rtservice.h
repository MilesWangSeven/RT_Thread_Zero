#ifndef __RT_SERVICE_H__
#define __RT_SERVICE_H__

#include "rtconfig.h"
#include "rtdef.h"

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

rt_uint8_t *rt_hw_stack_init(void *tentry,
                             void *parameter,
                             rt_uint8_t *stack_addr);

#endif
