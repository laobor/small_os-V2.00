/*
系统时钟
by laoqiuyi 2020 05 04
*/
#include "small_os_typedef.h"
#include "small_os_timer.h"


 volatile uint32 __attribute__ ((aligned(8)))  g_current_time = 0; 


typedef struct Timer
{
	SMALL_OS_bool timeout;
	uint32 remaining_time; //剩余时间
	uint32 last_time;  //上一次更新时间
}SMALL_OS_TIMER;


static SMALL_OS_TIMER g_timers[SMALL_OS_TIMER_MAX] = 
{
#undef define_timer
#define define_timer(ID) {TRUE, 0, 0},
#include "small_os_timer_def.h"
};
void set_timeout(uint8 timerID, uint32 timeout)
{
	g_timers[timerID].timeout = (timeout > 0) ? FALSE : TRUE;
	g_timers[timerID].remaining_time = timeout;
	//ET0 = 0; /* ????? */
	g_timers[timerID].last_time = get_current_time();
	//ET0 = 1; /* ????? */
}


uint32 get_current_time(void)
{
	uint32  cur_time1;
	uint32  cur_time2;

	cur_time1 = g_current_time;
	cur_time2 = g_current_time;
	if(cur_time1 == cur_time2)
	{
		return cur_time1; /* Firmware ??'??????????????????????? tick ??. */
	}
	else
	{
		return g_current_time;
	}
}


char timeout(uint8 timerID)
{
	if (! g_timers[timerID].timeout)
	{
		uint32 span, temp_now;

		//ET0 = 0;
		temp_now =  get_current_time();
		//ET0 = 1;
		if (g_timers[timerID].remaining_time > 0)
		{	
			span = temp_now - g_timers[timerID].last_time;
			g_timers[timerID].last_time = temp_now;
			if (span >= g_timers[timerID].remaining_time)
			{
				g_timers[timerID].remaining_time = 0;
				g_timers[timerID].timeout = TRUE;
			}
			else
				g_timers[timerID].remaining_time -= span;	
		}
		else 
		{
			g_timers[timerID].timeout = TRUE;
		}
	}
	return g_timers[timerID].timeout;
}

uint32 last_time(uint8 timerID)
{
	timeout(timerID);
	return g_timers[timerID].remaining_time;
}

