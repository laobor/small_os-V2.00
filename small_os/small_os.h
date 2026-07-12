/*
小型模拟系统
by laoqiuyi 2020 05 04
*/
#ifndef _SMALL_OS_H_
#define _SMALL_OS_H_
#include "small_os_typedef.h"
#define SMALL_OS_TASK_NUMBERS   64              
#define SMALL_OS_MAX_COUNTS  24
#define SMALL_OS_STACK_SIZES 256
//#define SMALL_OS_TASK_MODE   1


typedef enum {
    OS_SINGLE,
    OS_PERIODIC,
    OS_PERMANENT
}_SMALL_OS_TYPE_;

typedef enum 
{
    TASK_RUN,//运行
    TASK_READY,//就绪
    TASK_WAIT//等待
}SMALL_OS_TASK_STATE;
typedef  void(*callback_fun)(uint8*buf);

#define HW_FRAME_SIZE       8
#define MANUAL_FRAME_SIZE   8

//#pragma pack(1)
typedef struct 
{
    uint32 init_counts;//初始化目标执行数量 	
    uint8 remaining_runs;//当前执行剩余数量   	                     
    uint8 active;
		uint8 type;
	  uint8 priority;
	 callback_fun fun;
		uint8 * buf;           
} SMALL_OS_TASK;

 
typedef struct 
{
    uint32 r4;      // 偏移 0x00
    uint32 r5;      // 偏移 0x04
    uint32 r6;      // 偏移 0x08
    uint32 r7;      // 偏移 0x0C
    uint32 r8;      // 偏移 0x10
    uint32 r9;      // 偏移 0x14
    uint32 r10;     // 偏移 0x18
    uint32 r11;     // 偏移 0x1C

    uint32 r0;      // 偏移 0x20  ← PSP 指向这里（硬件帧底部）
    uint32 r1;      // 偏移 0x24
    uint32 r2;      // 偏移 0x28
    uint32 r3;      // 偏移 0x2C
    uint32 r12;     // 偏移 0x30
    uint32 lr;      // 偏移 0x34  任务返回地址（如 small_idle）
    uint32 pc;      // 偏移 0x38  任务入口函数地址（最低位为 1）
    uint32 xpsr;    // 偏移 0x3C  Thumb 位 = 0x01000000
} SMALL_TaskStackFrame;
//#pragma pack(0)
void small_os_init(void);
int small_os_set(uint32_t counts, uint8 type, uint8_t priority, callback_fun fun, uint8* buf);
void small_task_sop(uint8_t timer_id);
void samll_os_run(void);
void small_os_suspend(uint8 level);//挂起
void small_os_ready(uint8 level);//就绪
void small_idle(uint8 *buf);
void samll_os_run_ex(void);//扩展运行
uint8 press_task_ex(uint8 task_id);//增加扩展
void samall_os_change_task_counts(uint8 priority,uint32 counts);//改变单次调度运行次数
static void small_task_exit(void);//退出任务
//void small_os_init_task(uint8 task_id, callback_fun fun,uint8 *stack_buf,uint32 sizes);//初始化任务
void small_os_init_task(uint8 task_id, callback_fun fun, uint32 *stack_buf,uint32 stack_sizes );
void small_os_scheduler(void);//任务切换
//extern void small_os_context_switch(void);
void samll_time_irq(void);
uint32 small_os_get_val();
#endif /* #ifndef _SMALL_OS_H_*/
