#include "rtconfig.h"
#include "rtthread.h"

/* 硬件定时器列表 */
static rt_list_t rt_timer_list[RT_TIMER_SKIP_LIST_LEVEL];

void rt_system_timer_init(void)
{
    int i;
    
    for (i = 0; i < sizeof(rt_timer_list) / sizeof(rt_timer_list[0]); i++)
    {
        rt_list_init(rt_timer_list + i);
    }
}

void _rt_timer_init(rt_timer_t timer,
                   void (*timeout)(void *parameter),
                   void *parameter,
                    rt_tick_t time,
                   rt_uint8_t flag)
{
    int i;

    /* 设置标志 */
    timer->parent.flag = flag;

    /* 先设置为非激活 */
    timer->parent.flag &= ~RT_TIMER_FLAG_ACTIVATED;

    timer->timeout_func = timeout;
    timer->parameter = parameter;

    /* 初始化定时器实际超时时的系统节拍数 */
    timer->timeout_tick = 0;
    /* 初始化定时器需要超时的节拍数 */
    timer->init_tick = time;

    /* 初始化定时器的内置节点 */
    for (i = 0; i < RT_TIMER_SKIP_LIST_LEVEL; i++)
    {
        rt_list_init(&(timer->row[i]));
    }
}

/**
 * 该函数用于初始化一个定时器，通常该函数用于初始化一个静态的定时器
 * 
 * @param timer 静态定时器对象
 * @param name 定时器的名字
 * @param timeout 超时函数
 * @param parameter 超时函数形参
 * @param time 定时器的超时时间
 * @param flag 定时器的标志
 */
void rt_timer_init(rt_timer_t timer,
                   const char *name,
                   void (*timeout)(void *parameter),
                   void *parameter,
                   rt_tick_t time,
                   rt_uint8_t flag)
{
    rt_object_init((rt_object_t)&timer, RT_Object_Class_Timer, name);

    _rt_timer_init(timer, timeout, parameter, time, flag);
}
