#ifndef __RT_THREAD_H__
#define __RT_THREAD_H__

#include "rtconfig.h"
#include "rtdef.h"
#include "rtservice.h"

char *rt_strncpy(char *dst, const char *src, rt_ubase_t n);
void rt_object_init(struct rt_object *object, enum rt_object_class_type type, const char *name);

#endif
