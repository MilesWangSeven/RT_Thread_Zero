#include "rtdef.h"
#include "rtconfig.h"

ALIGN(RT_ALIGN_SIZE)
rt_uint8_t rt_flag1_thread_stack[RT_THREAD_STACK_SIZE];
rt_uint8_t rt_flag2_thread_stack[RT_THREAD_STACK_SIZE];
struct rt_thread rt_flag1_thread;
struct rt_thread rt_flag2_thread;

rt_uint32_t flag1, flag2;

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
	}
}

/* 
* main function
*/
int main(void)
{
	for (;;)
	{
		/* do nothing */
	}
}
