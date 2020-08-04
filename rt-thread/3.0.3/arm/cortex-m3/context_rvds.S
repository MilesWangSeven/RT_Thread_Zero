;******************************************************
; Global Variable
;******************************************************
    IMPORT rt_thread_switch_interrupt_flag
    IMPORT rt_interrupt_from_thread
    IMPORT rt_interrupt_to_thread

;******************************************************
; Variable
;******************************************************
SCB_VTOR            EQU 0xE000ED08  ; 向量表偏移寄存器
NVIC_INT_CTRL       EQU 0xE000ED04  ; 中断控制状态寄存器
NVIC_SYSPRI2        EQU 0xE000ED20  ; 系统优先级寄存器(2)
NVIC_PENDSV_PRI     EQU 0x00FF0000  ; PendSV 优先级值(lowest)
NVIC_PENDSVSET      EQU 0x10000000  ; 触发PendSV exception 的值

;******************************************************
; 代码产生指令
;******************************************************
    AREA |.text|, CODE, READONLY, ALIGN=2
    THUMB
    REQUIRE8
    PRESERVE8

;******************************************************
; 函数原型: void rt_hw_context_switch_to(rt_uint32_t to);
; r0 --> to
; 该函数用于开启第一次线程切换
;******************************************************

rt_hw_context_switch_to PROC
    EXPORT rt_hw_context_switch_to

    LDR r1, =rt_interrupt_to_thread
    STR r0, [r1]

	;;;
	
	ENDP

    END
