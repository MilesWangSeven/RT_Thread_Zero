#ifndef __RT_DEF_H__
#define __RT_DEF_H__
 
/*
* Data type
*/

/* RT-Thread data type */
typedef signed char rt_int8_t;
typedef signed short rt_int16_t;
typedef signed long rt_int32_t;
typedef unsigned char rt_uint8_t;
typedef unsigned short rt_uint16_t;
typedef unsigned long rt_uint32_t;
typedef int rt_bool_t;

/* 32bit CPU */
typedef long rt_base_t;
typedef unsigned long rt_ubase_t;

typedef rt_base_t rt_err_t;
typedef rt_uint32_t rt_time_t;
typedef rt_uint32_t rt_tick_t;
typedef rt_base_t rt_flag_t;
typedef rt_ubase_t rt_size_t;
typedef rt_ubase_t rt_dev_t;
typedef rt_base_t rt_off_t;

/* boolean data type */
#define RT_TRUE 1
#define RT_FALSE 0
 
#ifdef __CC_ARM
#define rt_inline static __inline
#define ALIGN(n) __attribute__((aligned(n)))
 
#elif defined(__IAR_SYSTEMS_ICC__)
#define rt_inline static inline
#define ALIGN(n) PRAGMA(data_alignment=n)

#elif defined (_GNUC__)
#define rt_inline static __inline
#define ALIGN(n) __attribute__((aligned(n)))

#else
#error not supported tool chain
#endif

#define RT_ALIGN(size, align) (((size) + (align) - 1) & ~((align) - 1))
#define RT_ALIGN_DOWN(size, align) ((size) & ~((align) - 1))

#define RT_NULL (0)

struct rt_list_node
{
    struct rt_list_node *next;
    struct rt_list_node *prev;
};
typedef struct rt_list_node rt_list_t;

enum rt_object_class_type
{
    RT_Object_Class_Thread = 0,     /* 对象是线程 */
    RT_Object_Class_Semaphore,      /* 对象是信号量 */
    RT_Object_Class_Mutex,          /* 对象是互斥量 */
    RT_Object_Class_Event,          /* 对象是事件 */
    RT_Object_Class_MailBox,        /* 对象是邮箱 */
    RT_Object_Class_MessageQueue,   /* 对象是消息队列 */
    RT_Object_Class_MemHeap,        /* 对象是内存堆 */
    RT_Object_Class_MemPool,        /* 对象是内存池 */
    RT_Object_Class_Device,         /* 对象是设备 */
    RT_Object_Class_Timer,          /* 对象是定时器 */
    RT_Object_Class_Module,         /* 对象是模块 */
    RT_Object_Class_Unknown,        /* 对象是未知 */
    RT_Object_Class_Static = 0x80   /* 对象是静态对象 */
};

struct rt_object
{
    char        name[RT_NAME_MAX];  /* 内核对象的名字 */
    rt_uint8_t  type;               /* 内核对象的类型 */
    rt_uint8_t  flag;               /* 内核对象的状态 */
    rt_list_t   list;               /* 内核对象的列表节点 */
};
typedef struct rt_object *rt_object_t;  /* 内核对象数据类型重定义 */

struct rt_object_information {
    enum rt_object_class_type type;
    rt_list_t object_list;
    rt_size_t object_size;
};

enum rt_object_info_type
{
    RT_Object_Info_Thread = 0,
#ifdef RT_USING_SEMAPHORE
    RT_Object_Info_Semaphore,
#endif
#ifdef RT_USING_MUTEX
    RT_Object_Info_Mutex,
#endif
#ifdef RT_USING_EVENT
    RT_Object_Info_Event,
#endif
#ifdef RT_USING_MAILBOX
    RT_Object_Info_MailBox,
#endif
#ifdef RT_USING_MESSAGEQUEUE
    RT_Object_Info_MessageQueue,
#endif
#ifdef RT_USING_MEMHEAP
    RT_Object_Info_MemHeap,
#endif
#ifdef RT_USING_MEMPOOL
    RT_Object_Info_MemPool,
#endif
#ifdef RT_USING_DEVICE
    RT_Object_Info_Device,
#endif
    RT_Object_Info_Timer,
#ifdef RT_USING_MODULE
    RT_Object_Info_Module,
#endif
    RT_Object_Info_Unknown
};

struct rt_thread
{
    /* rt 对象 */
    char        name[RT_NAME_MAX];  /* 内核对象的名字 */
    rt_uint8_t  type;               /* 内核对象的类型 */
    rt_uint8_t  flag;               /* 内核对象的状态 */
    rt_list_t   list;               /* 内核对象的列表节点 */

    rt_list_t tlist;
    void *sp;
    void *entry;
    void *parameter;
    void *stack_addr;
    rt_uint32_t stack_size;
    rt_ubase_t remaining_tick;
};
typedef struct rt_thread *rt_thread_t;

struct rt_timer
{
    /* rt 对象 */
    char        name[RT_NAME_MAX];  /* 内核对象的名字 */
    rt_uint8_t  type;               /* 内核对象的类型 */
    rt_uint8_t  flag;               /* 内核对象的状态 */
    rt_list_t   list;               /* 内核对象的列表节点 */
    //TODO
};
typedef struct rt_timer *rt_timer_t;

/* Error Code */
#define RT_EOK          0   /* There is no error */
#define RT_ERROR        1   /* A generic error happens */
#define RT_ETIMEOUT     2   /* Time out */
#define RT_EFULL        3   /* The resource is full */
#define RT_EEMPTY       4   /* The resource is empty */
#define RT_ENOMEM       5   /* No memory */
#define RT_ENOSYS       6   /* No system */
#define RT_EBUSY        7   /* Busy */
#define RT_EIO          8   /* IO error */
#define RT_EINTR        9   /* Interrupted system call */
#define RT_EINVAL       10  /* Invalid argument */

#define rt_container_of(ptr, type, member) \
    ((type*)((char *)ptr - (rt_uint32_t)&((type *)0)->member))

#define rt_list_entry(node, type, member) \
    rt_container_of(node, type, member)

#endif /* __RT_DEF_H__ */
