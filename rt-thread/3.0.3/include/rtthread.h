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

#endif
