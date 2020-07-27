#ifndef __RT_SERVICE_H__
#define __RT_SERVICE_H__

#include "rtconfig.h"
#include "rtdef.h"

rt_inline void rt_list_init(rt_list_t *l)
{
    l->next  = l->prev = l;
}

#endif
