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
	; 导出rt_hw_context_switch_to, 让其具有全局属性，可以在C文件调用
    EXPORT rt_hw_context_switch_to

    ; 设置rt_interrupt_to_thread的值
    ; 将rt_interrupt_to_thread的地址加载到r1
    LDR r1, =rt_interrupt_to_thread
    ; 将r0的值存储到rt_interrupt_to_thread
    STR r0, [r1]

    ; 设置rt_interrupt_from_thread的值为0，表示第一次线程切换
    LDR r1, =rt_interrupt_from_thread
    MOV r0, #0x0
    STR r0, [r1]

    ; 设置中断标志位rt_thread_switch_interrupt_flag的值为1
    LDR r1, =rt_thread_switch_interrupt_flag
    MOV r0, #0x01
    STR r0, [r1]

    ; 设置PendSV异常的优先级
    LDR r0, =NVIC_SYSPRI2
	LDR r1, =NVIC_PENDSV_PRI
    LDR.W r2, [r0, #0x00]   ;读
    ORR r1, r1, r2          ;改
    STR r1, [r0]            ;写
	
    ; 设置PendSV异常(产生上下文切换)
    LDR r0, =NVIC_INT_CTRL
    LDR r1, =NVIC_PENDSVSET
    STR r1, [r0]

    CPSIE F
    CPSIE I

    ;永远不会到这里
	ENDP
        ALIGN 4
	END
