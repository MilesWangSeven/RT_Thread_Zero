#include <rtthread.h>
#include "ARMCM3.h"
#include "rthw.h"

rt_uint8_t flag1;
rt_uint8_t flag2;
rt_uint8_t flag3;

extern rt_list_t rt_thread_priority_table[RT_THREAD_PRIORITY_MAX];

struct rt_thread rt_flag1_thread;
struct rt_thread rt_flag2_thread;
struct rt_thread rt_flag3_thread;

ALIGN(RT_ALIGN_SIZE)
rt_uint8_t rt_flag1_thread_stack[RT_THREAD_STACK_SIZE];
rt_uint8_t rt_flag2_thread_stack[RT_THREAD_STACK_SIZE];
rt_uint8_t rt_flag3_thread_stack[RT_THREAD_STACK_SIZE];

void flag1_thread_entry(void *p_arg);
void flag2_thread_entry(void *p_arg);
void flag3_thread_entry(void *p_arg);

void delay(rt_uint32_t count);

/*
* main function
*/
int main(void)
{
	/* 关中断 */
	rt_hw_interrupt_disable();

	/* SysTick 中断频率设置 */
	SysTick_Config( SystemCoreClock / RT_TICK_PER_SECOND );

	rt_system_timer_init();

	rt_system_scheduler_init();

	/* 初始化空闲线程 */
	rt_thread_idle_init();

	/* init thread */
	rt_thread_init( &rt_flag1_thread,
					"flag1",
					flag1_thread_entry,
					RT_NULL,
					&rt_flag1_thread_stack[0],
					sizeof(rt_flag1_thread_stack),
					2);
	// rt_list_insert_before( &(rt_thread_priority_table[0]), &(rt_flag1_thread.tlist) );
	rt_thread_startup(&rt_flag1_thread);

	/* init thread */
	rt_thread_init( &rt_flag2_thread,
					"flag2",
					flag2_thread_entry,
					RT_NULL,
					&rt_flag2_thread_stack[0],
					sizeof(rt_flag2_thread_stack),
					3);
	// rt_list_insert_before( &(rt_thread_priority_table[1]), &(rt_flag2_thread.tlist) );
	rt_thread_startup(&rt_flag2_thread);

	/* init thread */
	rt_thread_init(&rt_flag3_thread,
				   "flag3",
				   flag3_thread_entry,
				   RT_NULL,
				   &rt_flag3_thread_stack[0],
				   sizeof(rt_flag3_thread_stack),
				   4);
	rt_thread_startup(&rt_flag3_thread);

	rt_system_scheduler_start();
}

/* software delay */
void delay(rt_uint32_t count)
{
	for (; count!=0; count--);
}

/* thread 1 */
void flag1_thread_entry(void *p_arg)
{
	for ( ;; )
	{
		flag1 = 1;
		rt_thread_delay(4);
		flag1 = 0;
		rt_thread_delay(4);
	}
}

/* thread 2 */
void flag2_thread_entry(void *p_arg)
{
	for ( ;; )
	{
		flag2 = 1;
		rt_thread_delay(2);
		flag2 = 0;
		rt_thread_delay(2);
	}
}

/* thread 3 */
void flag3_thread_entry(void *p_arg)
{
	for (;;)
	{
		flag3 = 1;
		rt_thread_delay(3);
		flag3 = 0;
		rt_thread_delay(3);
	}
}

void SysTick_Handler(void)
{
	/* 进入中断 */
	rt_interrupt_enter();

	/* 时基更新 */
	rt_tick_increase();

	/* 离开中断 */
	rt_interrupt_leave();
}
