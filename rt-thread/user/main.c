#include <rtthread.h>
#include "ARMCM3.h"

rt_uint8_t flag1;
rt_uint8_t flag2;

extern rt_list_t rt_thread_priority_table[RT_THREAD_PRIORITY_MAX];

struct rt_thread rt_flag1_thread;
struct rt_thread rt_flag2_thread;

ALIGN(RT_ALIGN_SIZE)
rt_uint8_t rt_flag1_thread_stack[RT_THREAD_STACK_SIZE];
rt_uint8_t rt_flag2_thread_stack[RT_THREAD_STACK_SIZE];

void flag1_thread_entry(void *p_arg);
void flag2_thread_entry(void *p_arg);

void delay(rt_uint32_t count);

/* 
* main function
*/
int main(void)
{
	rt_system_scheduler_init();
	/* init thread */
	rt_thread_init( &rt_flag1_thread,
					"flag1",
					flag1_thread_entry,
					RT_NULL,
					&rt_flag1_thread_stack[0],
					sizeof(rt_flag1_thread_stack) );
	rt_list_insert_before( &(rt_thread_priority_table[0]), &(rt_flag1_thread.tlist) );

	/* init thread */
	rt_thread_init( &rt_flag2_thread,
					"flag2",
					flag2_thread_entry,
					RT_NULL,
					&rt_flag2_thread_stack[0],
					sizeof(rt_flag2_thread_stack) );
	rt_list_insert_before( &(rt_thread_priority_table[1]), &(rt_flag2_thread.tlist) );
	
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
		delay(100);
		flag1 = 0;
		delay(100);
		
		/* switch thread manually */
		rt_schedule();
	}
}

/* thread 2 */
void flag2_thread_entry(void *p_arg)
{
	for ( ;; )
	{
		flag2 = 1;
		delay(100);
		flag2 = 0;
		delay(100);
		
		/* switch thread manually */
		rt_schedule();
	}
}
