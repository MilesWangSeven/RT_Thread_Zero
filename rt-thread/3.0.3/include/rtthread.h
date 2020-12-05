#ifndef __RT_THREAD_H__
#define __RT_THREAD_H__

#include "rtconfig.h"
#include "rtdef.h"
#include "rtservice.h"

char *rt_strncpy(char *dst, const char *src, rt_ubase_t n);
void rt_object_init(struct rt_object *object, enum rt_object_class_type type, const char *name);
void rt_tick_increase(void);

void rt_interrupt_enter(void);
void rt_interrupt_leave(void);

void rt_thread_idle_init(void);

void rt_thread_delay(rt_tick_t tick);
rt_err_t rt_thread_startup(rt_thread_t thread);
rt_err_t rt_thread_resume(rt_thread_t thread);
rt_thread_t rt_thread_self(void);

void rt_system_timer_init(void);
void rt_timer_init(rt_timer_t timer,
                   const char *name,
                   void (*timeout)(void *parameter),
                   void *parameter,
                   rt_tick_t time,
                   rt_uint8_t flag);
rt_inline void _rt_timer_remove(rt_timer_t timer)
{
    int i;

    for (i = 0; i < RT_TIMER_SKIP_LIST_LEVEL; i++)
    {
        rt_list_remove(&timer->row[i]);
    }
}

#endif
