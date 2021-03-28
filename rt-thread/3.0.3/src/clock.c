#include "rtthread.h"
#include "rthw.h"

static rt_tick_t rt_tick = 0; /* 系统时基计数器 */
extern rt_list_t rt_thread_priority_table[RT_THREAD_PRIORITY_MAX];
extern rt_uint32_t rt_thread_ready_priority_group;

void rt_tick_increase(void)
{
#if 0
    rt_ubase_t i;
    struct rt_thread *thread;
    rt_tick ++;

    /* 扫描就绪列表中所有线程的remaining_tick, 如果不为0， 则减1 */
    for (i = 0; i<RT_THREAD_PRIORITY_MAX; i++)
    {
        thread = rt_list_entry(rt_thread_priority_table[i].next,
                               struct rt_thread,
                               tlist);
        if (thread->remaining_tick != 0)
        {
            thread->remaining_tick --;
        }
    }
    rt_schedule();
#else
    rt_ubase_t i;
    struct rt_thread *thread;
    rt_tick ++;

    /* 扫描就绪列表中所有线程的remaining_tick, 如果不为0， 则减1 */
    for (i = 0; i<RT_THREAD_PRIORITY_MAX; i++)
    {
        if(rt_list_isempty(&rt_thread_priority_table[i]) == 0)
        {
            thread = rt_list_entry(rt_thread_priority_table[i].next,
                                struct rt_thread,
                                tlist);
            if (thread->remaining_tick != 0)
            {
                thread->remaining_tick --;
                if (thread ->remaining_tick == 0)
                {
                    //rt_schedule_insert_thread(thread);
                    rt_thread_ready_priority_group |= thread->number_mask;
                }
            }
        }
    }
    rt_schedule();
#endif
}

rt_tick_t rt_tick_get(void)
{
    return rt_tick;
}
