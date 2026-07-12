/*
小型模拟系统
by laoqiuyi 2020 05 04 //劳秋意

*/
#include "small_os.h"

#define  MAX_LEVEL  (64) 
#define  MAX_ERROR_COUNTS (100)  
//#define _STACK_SIZES_ 14
#define  _OS_RDY_TBL_SIZE_   ((MAX_LEVEL) / 8 + 1)
#define  TASK_IDL_F  (MAX_LEVEL-1)

#define _OS_PRESS_COUNTS 8

 volatile uint8 __attribute__ ((aligned(8))) g_find_pow_level[256];
 volatile SMALL_OS_TASK __attribute__ ((aligned(8)))  g_small_task[SMALL_OS_TASK_NUMBERS];
 volatile uint8 __attribute__ ((aligned(8)))  g_os_rdy_tabl[_OS_RDY_TBL_SIZE_];//={0}; 
 volatile uint8 __attribute__ ((aligned(8)))  g_os_rdy_grp;// =0; 
 volatile uint8 __attribute__ ((aligned(8)))  g_os_set_tbl_true[8];//   = {0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80}; 
 volatile uint8 __attribute__ ((aligned(8)))  g_os_set_tbl_false[8];//   = {0xFE, 0xFD, 0xFB, 0xF7, 0xEF, 0xDF, 0xBF, 0x7F}; 
 volatile uint8 __attribute__ ((aligned(8))) g_os_press_table[_OS_PRESS_COUNTS];//={0,0,0,0,0,0};

//uint32 *samll_os_task_stacks[MAX_LEVEL];
uint32 __attribute__ ((aligned(8))) * g_small_os_tasks[SMALL_OS_TASK_NUMBERS];
 
volatile uint8 g_small_os_next_task_id = 0;
volatile uint8 g_small_os_current_task_id = 0;
//uint32 __attribute__((aligned(8)))   g_task_main_buf[256];
uint32 __attribute__((aligned(8)))   g_task_idl_buf[SMALL_OS_STACK_SIZES];
uint32 __attribute__((aligned(8)))   g_task_idl_end_buf[SMALL_OS_STACK_SIZES];
 
uint32 *    g_small_os_pCurTCB = NULL;
uint32 *    g_small_os_pNextTCB = NULL;
//uint8 g_small_os_check_f =0;
 
 
 
///////////////////////////////////////////////////////////////////////


void small_os_idle(uint8 *buf);
/////////////////////////////////////////////////////////////////////
void small_os_suspend(uint8 level)//挂起
{
	uint8 x=0,y=0;
	//uint8 task_id =0;
	//g_os_rdy_grp            &= g_os_set_tbl_false[level >> 3]; 
	g_os_rdy_tabl[level >> 3] &= g_os_set_tbl_false[level & 0x07];
 
		y    = g_find_pow_level[g_os_rdy_grp]; 
		x    = g_find_pow_level[g_os_rdy_tabl[y]]; 
      //  task_id = (y << 3) + x;
      if(x ==0) 
	   {
		   g_os_rdy_grp  &= g_os_set_tbl_false[level >> 3]; 
	   }
}
void small_os_ready(uint8 level)//就绪
{
	g_os_rdy_grp            |= g_os_set_tbl_true[level >> 3]; 
	g_os_rdy_tabl[level >> 3] |= g_os_set_tbl_true[level & 0x07];
}
 
void init_task(void)
{
// 	 uint8 task_id;
//     uint8 y,x;
//     y=task_id>>3;
// 		x=task_id&0x07;  
// 		g_os_rdy_grp  |= (1 << y);   
//     g_osrdy_tbl[y] |= (1 << x);   
 

 
}
void samll_os_run(void)
{
	
  uint8 y,x;
  uint8 task_id;
  
 	y    = g_find_pow_level[g_os_rdy_grp]; 
	x    = g_find_pow_level[g_os_rdy_tabl[y]]; 
	task_id = (y << 3) + x;
 
	
	
	do 
	{
	  g_small_task[task_id].fun(g_small_task[task_id].buf);
	  g_small_task[task_id].remaining_runs--;
	}
	while(g_small_task[task_id].remaining_runs >0);
  	if(task_id !=0x3f)
		small_os_suspend(task_id);


}
void samll_os_run_ex()
{
	uint8 task_id;
	uint8 i=0;
	for(i=0;i<_OS_PRESS_COUNTS;i++)
	{
		task_id =g_os_press_table[i];
		if(task_id>0&& task_id<(MAX_LEVEL-1))
		{
				g_small_task[task_id].fun(g_small_task[task_id].buf);
		    g_os_press_table[i] =0;
		}
		
	}
 
}
uint8 press_task_ex(uint8 task_id)
{
	uint8 i=0;
	for(i=0;i<_OS_PRESS_COUNTS;i++)
	{
	   if(g_os_press_table[i]==0)
		 {
			 g_os_press_table[i] =task_id;
			 
			 return 1;
		 }
 
		
	}
	return 0;
	
}
void small_os_init(void) 
{
	int i=0;
	int j=0;
 
 
//	uint32 psp_val;
	g_os_rdy_grp = 0;
g_os_set_tbl_true[0]=0x01;
g_os_set_tbl_true[1]=0x02;
g_os_set_tbl_true[2]=0x04;
g_os_set_tbl_true[3]=0x08;
g_os_set_tbl_true[4]=0x10;
g_os_set_tbl_true[5]=0x20;
g_os_set_tbl_true[6]=0x40;
g_os_set_tbl_true[7]=0x80;
g_os_rdy_grp =0;
 

g_os_set_tbl_false[0]=0xFE;
g_os_set_tbl_false[1]=0xFD;
g_os_set_tbl_false[2]=0xFB;
g_os_set_tbl_false[3]=0xF7;
g_os_set_tbl_false[4]=0xEF;
g_os_set_tbl_false[5]=0xDF;
g_os_set_tbl_false[6]=0xBF;
g_os_set_tbl_false[7]=0x7F;


 
g_os_press_table[0]=0;
g_os_press_table[1]=0;
g_os_press_table[2]=0;
g_os_press_table[3]=0;
g_os_press_table[4]=0;
g_os_press_table[5]=0;
g_os_press_table[6]=0;
g_os_press_table[7]=0;
for(i=0;i<_OS_RDY_TBL_SIZE_;i++)
{
 g_os_rdy_tabl[i] =0;
}
for(i=0;i<_OS_PRESS_COUNTS;i++)
{
	g_os_press_table[i]=0;
}
////////////////////???????/////////////////////////////////
	for (i=0;i<256;i++)
	{
		g_find_pow_level[i]=0;
		for (j=0;j<8;j++)
		{
			if (g_os_set_tbl_true[j]&i)
			{
				g_find_pow_level[i]=j;
				break;;
			}
		}
	}
/////////////////////////////////////////////////////////

 
	
 
   for(  i = 0; i < SMALL_OS_TASK_NUMBERS; i++) 
	{
        g_small_task[i].active = 0;
		   g_small_os_tasks[i] =0;
		   
    } 
		//memset((uint8*)(&g_small_os_tasks[i]),0,sizeof(SMALL_TASK_TCB));
  //	small_os_set(1,OS_SINGLE,TASK_IDL_F,small_idle,NULL);
 		small_os_init_task((MAX_LEVEL-1),small_idle,g_task_idl_end_buf,SMALL_OS_STACK_SIZES);			
		small_os_init_task(0,small_os_idle,g_task_idl_buf,SMALL_OS_STACK_SIZES);
	
// 		g_small_os_current_task_id = 0;
// g_small_os_next_task_id = 0;
// g_small_os_pCurTCB = NULL;
// g_small_os_pNextTCB = &g_small_os_tasks[0];
// psp_val = (uint32_t)g_small_os_tasks[0].stack_ptr;
// __set_PSP(psp_val);
// __set_CONTROL(0x02);   /* 线程模式使用 PSP */
// __ISB();
}
uint32 small_os_get_val()
{
 
	uint32 psp_val;
	g_small_os_current_task_id = 0;
	g_small_os_next_task_id = 0;
	g_small_os_pCurTCB = g_small_os_tasks[0];
	g_small_os_pNextTCB = g_small_os_pCurTCB;
	psp_val = (uint32) &g_task_idl_buf[(SMALL_OS_STACK_SIZES-33)];
 
	return psp_val;
}
 
int small_os_set(uint32_t counts, uint8 type, uint8_t priority, callback_fun fun, uint8* buf)
{
	int i=0;
	if(fun == NULL  || priority > 63)  return -1;
  for(i=0;i<SMALL_OS_TASK_NUMBERS;i++)
	{
        if(!g_small_task[priority].active) 
				{
           // g_small_task[i].remaining_runs = counts;
            g_small_task[priority].type = type;
            g_small_task[priority].fun = fun;
            g_small_task[priority].init_counts = counts;  
            g_small_task[priority].buf = buf;
            g_small_task[priority].active = 1;
            g_small_task[priority].priority = priority;
 
						switch(type)
						{
							case OS_SINGLE:
								g_small_task[priority].remaining_runs = 1;
							break;
							case OS_PERIODIC:
								g_small_task[priority].remaining_runs = counts;
							break;			
							case OS_PERMANENT:
								g_small_task[priority].remaining_runs = SMALL_OS_MAX_COUNTS;
							break;			
							default:
								g_small_task[priority].remaining_runs = 1;
							break;	
					   }
						 
						 small_os_ready(priority);
						  return 0;
					}
	}   
 return 0;
  
}

 
void small_os_stop(uint8_t uid) 
{
	uint8 priority;
    if(uid >0 && uid < SMALL_OS_TASK_NUMBERS)
			{
        g_small_task[uid].active = 0;
				priority =g_small_task[uid].priority;
				small_os_suspend(priority);
      }
}

void samall_os_change_task_counts(uint8 priority,uint32 counts)
{
	
	       if(g_small_task[priority].active) 
				{
 
            g_small_task[priority].init_counts = counts;  
				}
	
}
 

void small_os_idle(uint8 *buf)
{
   uint32 counts=0;
 	for(;;)
	{
		counts++;
	}
}
 
void small_idle(uint8 *buf)
{
  int id=0;
  
	for(id=0;id<SMALL_OS_TASK_NUMBERS;id++)
	{
		if(g_small_task[id].active)
		{
			switch(g_small_task[id].type)
			{
				case OS_SINGLE:
					 g_small_task[id].remaining_runs = 1;
				break;
				case OS_PERIODIC:
					  g_small_task[id].remaining_runs = g_small_task[id].init_counts;
				break;
				case OS_PERMANENT:
					g_small_task[id].remaining_runs =SMALL_OS_MAX_COUNTS; 
				break;			
				default:
					 g_small_task[id].remaining_runs = 1;
				break;	
			}

			 small_os_ready(id);
		}
		
			
	}
 
//	printf("small_idle");
 
}
 
void samll_time_irq(void)
{
   uint8 y,x;
   uint8 task_id;
	
 
			 if (g_small_os_pCurTCB == NULL) 
				{
					g_small_os_current_task_id =0;
					g_small_os_pCurTCB =g_small_os_tasks[0];;
					g_small_os_next_task_id = 0;
					g_small_os_pNextTCB = g_small_os_tasks[0];
			} 
			else 
			{
 
 
				small_os_suspend(g_small_os_current_task_id);
				y    = g_find_pow_level[g_os_rdy_grp]; 
				x    = g_find_pow_level[g_os_rdy_tabl[y]]; 
				task_id =(y << 3) + x;
				if(TASK_IDL_F== task_id )
				{
						small_idle(NULL);
						y    = g_find_pow_level[g_os_rdy_grp]; 
						x    = g_find_pow_level[g_os_rdy_tabl[y]]; 
				}
				
				g_small_os_next_task_id  = (y << 3) + x;
				//	g_small_os_pCurTCB  =	g_small_os_tasks[g_small_os_current_task_id];
					g_small_os_pNextTCB = g_small_os_tasks[g_small_os_next_task_id];
				
			}
 
	 
 
}
 
 
void small_os_no()
{
 for(;;)
 {
 }
}
void small_os_init_task(uint8 task_id, callback_fun fun ,uint32 *stack_buf,uint32 stack_sizes )
//void small_os_init_task(uint8 task_id, callback_fun fun, void *arg, uint8 *stack_buf, uint32 stack_size_bytes)
{
	 SMALL_TaskStackFrame *pFrame;
   uint32 *sp = stack_buf + stack_sizes ;   // 指向最高地址+1
   sp =(uint32 *)(((uint32)sp) & ~((uint32)0x0007));
   sp -= 16;    
    pFrame = (SMALL_TaskStackFrame*)sp;
    // 填充软件帧
    pFrame->r4  = 0;
    pFrame->r5  = 0;
    pFrame->r6  = 0;
    pFrame->r7  = 0;
    pFrame->r8  = 0;
    pFrame->r9  = 0;
    pFrame->r10 = 0;
    pFrame->r11 = 0;

    // 填充硬件帧 
    pFrame->r0   = (uint32)0;          // 任务参数（如无则 0）
    pFrame->r1   = 0;
    pFrame->r2   = 0;
    pFrame->r3   = 0;
    pFrame->r12  = 0;
    pFrame->lr   = (uint32)small_os_no;   // 返回后进入空闲
    pFrame->pc   = (uint32)fun | 1UL;       // 强制 Thumb 位
    pFrame->xpsr = 0x01000000UL;            // Thumb 位 = 1
    pFrame->r3   =  pFrame->pc;
 
    g_small_os_tasks[task_id] = sp;// &(pFrame->r0);
 

   small_os_set(1,OS_SINGLE,task_id,fun,NULL);
}
///////////////////////调度//////////////////////////
void small_os_scheduler(void) 
{
	 uint8 y,x;
   uint8 task_id;
	small_os_suspend(g_small_os_current_task_id);
 	y    = g_find_pow_level[g_os_rdy_grp]; 
	x    = g_find_pow_level[g_os_rdy_tabl[y]]; 
	
//   if(TASK_IDL_F== ((y << 3) + x) )
// 	{
// 		  small_idle(NULL);
// 		 	y    = g_find_pow_level[g_os_rdy_grp]; 
// 	    x    = g_find_pow_level[g_os_rdy_tabl[y]]; 
// 	}
//  	
//  	g_small_os_next_task_id  = (y << 3) + x;
   
 
 
}
