#include "rtconfig.h"
#include "rtdef.h"
#include "rtservice.h"

/* ready thread list */
rt_list_t rt_thread_priority_table[RT_THREAD_PRIORITY_MAX];
struct rt_thread *rt_current_thread;

#define rt_container_of(ptr, type, member) \
    ((type*)((char *)ptr - (rt_uint32_t)&((type *)0)->member))

#define rt_list_entry(node, type, member) \
    rt_container_of(node, type, member)

/* system scheduler initial */
void rt_system_scheduler_init(void)
{
    register rt_base_t offset;
    for (offset=0; offset < RT_THREAD_PRIORITY_MAX; offset++)
    {
        rt_list_init(&rt_thread_priority_table[offset]);
    }

    rt_current_thread = RT_NULL;
}

/* start system scheduler */
void rt_system_scheduler_start(void)
{
    register struct rt_thread *to_thread;

    to_thread = rt_list_entry(rt_thread_priority_table[0].next,
                              struct rt_thread,
                              tlist);

    rt_current_thread = to_thread;

    rt_hw_context_switch_to((rt_uint32_t)&to_thread->sp);
}
