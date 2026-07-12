/*
œµÕ≥ ±÷”
by laoqiuyi 2020 05 04
*/
#ifndef _SMALL_OS_TIMER_H_
#define _SMALL_OS_TIMER_H_
#include "small_os_typedef.h"

typedef enum TIMER_ENUM
{
#undef define_timer
#define define_timer(ID) ID,
#include "small_os_timer_def.h"
	SMALL_OS_TIMER_MAX
}Small_Os_Timer;
void set_timeout(uint8 timerID, uint32 timeout);
char timeout(uint8 timerID);
uint32 last_time(uint8 timerID);
uint32 get_current_time(void);

#endif /* #ifndef _SMALL_OS_TIMER_H_*/
