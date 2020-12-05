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

/**
 * 该函数将停止一个定时器
 * 
 * @param timer 将要停止的定时器
 * 
 * @return 操作状态 , RT_EOK on OK, -RT_ERROR on error
 */
rt_err_t rt_timer_stop(rt_timer_t  timer)
{
    register rt_base_t level;
    if (!(timer->parent.flag & RT_TIMER_FLAG_ACTIVATED))
    {
        return -RT_ERROR;
    }

    /* 关中断 */
    level = rt_hw_interrupt_disable();

    /* 将定时器从定时列表删除 */
    _rt_timer_remove(timer);

    /* 开中断 */
    rt_hw_interrupt_enable(level);

    /* 改变定时器的状态为非active */
    timer->parent.flag &= ~RT_TIMER_FLAG_ACTIVATED;

    return RT_EOK;
}

/**
 * 该函数将获取或者设置定时器的一些选项
 * 
 * @param timer 将要被设置或者获取的定时器
 * @param cmd 控制命令
 * @param arg 形参
 * 
 * @return RT_EOK
 */
rt_err_t rt_timer_control(rt_timer_t timer, int cmd, void *arg)
{
    switch (cmd) 
    {
    case RT_TIMER_CTRL_GET_TIME:
        *(rt_tick_t *)arg = timer->init_tick;
        break;
    case RT_TIMER_CTRL_SET_TIME:
        timer->init_tick = *(rt_tick_t *)arg;
        break;
    case RT_TIMER_CTRL_SET_ONESHOT:
        timer->parent.flag &= ~RT_TIMER_FLAG_PERIODIC;
        break;
    case RT_TIMER_CTRL_SET_PERIODIC:
        timer->parent.flag |= RT_TIMER_FLAG_PERIODIC;
        break;
    }
}

/**
 * 启动定时器
 * 
 * @param timer 将要启动的定时器
 * 
 * @return 操作状态 ， RT_EOR on OK, -RT_ERROR on error
 */
rt_err_t rt_timer_start(rt_timer_t timer)
{
    unsigned int row_lvl = 0;
    rt_list_t *timer_list;
    register rt_base_t level;
    rt_list_t *row_head[RT_TIMER_SKIP_LIST_LEVEL];
    unsigned int tst_nr;
    static unsigned int random_nr;

    /* 关中断 */
    level = rt_hw_interrupt_disable();

    /* 将定时器从系统定时器列表删除 */
    rt_list_remove(timer);

    /* 改变定时器的状态为非 active */
    timer->parent.flag &= ~RT_TIMER_FLAG_ACTIVATED;

    /* 开中断 */
    rt_hw_interrupt_enable(level);

    /* 获取timeout tick,
       最大的timeout tick 不能大于 RT_TICK_MAX/2 */
    timer->timeout_tick = rt_tick_get() + timer->init_tick;    

    /* 关中断 */
    level = rt_hw_interrupt_disable();

    /* 将定时器插入到定时器列表 */
    /* 获取系统定时器列表根节点地址， rt_timer_list是一个全局变量 */
    timer_list = rt_timer_list;

    /* 获取系统定时器列表第一条链表根节点地址 */
    row_head[0] = &timer_list[0];
}
