    AREA    |.text|, CODE, READONLY
    THUMB
    PRESERVE8

    IMPORT  g_small_os_tasks
    IMPORT  g_small_os_current_task_id
    IMPORT  g_small_os_next_task_id


    EXPORT  PendSV_Handler

PendSV_Handler
    MRS     R0, PSP                     ; R0 = 当前 PSP
    STMDB   R0!, {R4-R11}               ; 压入 R4~R11，R0 更新为新的栈顶
    LDR     R1, =g_small_os_current_task_id
    LDRB    R2, [R1]                    ; R2 = current_id
    LDR     R3, =g_small_os_tasks
    LSL     R2, R2, #2                  ; 索引 *4
    STR     R0, [R3, R2]                ; 存储新 PSP

 
    LDR     R1, =g_small_os_next_task_id
    LDRB    R2, [R1]                    ; R2 = next_id
    LDR     R3, =g_small_os_tasks
    LSL     R2, R2, #2
    LDR     R0, [R3, R2]                ; R0 = 下一个任务的 PSP（保存时的栈顶）
    LDMIA   R0!, {R4-R11}               ; 弹出 R4~R11，R0 指向硬件帧底部
    LDR     R1, =g_small_os_next_task_id
    LDRB    R2, [R1]                    ; 重新加载 next_id
    LDR     R1, =g_small_os_current_task_id
    STRB    R2, [R1]                    ; 写入 current_id
    MSR     PSP, R0
    BX      LR

    END
