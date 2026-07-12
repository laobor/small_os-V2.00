#include "small_os_typedef.h"
#include "small_os_time.h"


#define SMALL_OS_LOG_CUR_LVL_  LOG_LVL_DEBUG
 volatile uint32 __attribute__ ((aligned(8)))  g_small_os_tick = 0; 
 
 
 const uint16_t days_per_month[2][12] = {
    {31,28,31,30,31,30,31,31,30,31,30,31}, // 平年
    {31,29,31,30,31,30,31,31,30,31,30,31}  // 闰年
};

uint8 is_leap_year(uint16_t year) 
{
    return ((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0);
}

uint8 validate_date(const Small_Os_Date_Time* dt)
{
	 uint8 leap;
	uint8_t max_day;
    if (dt->year < 2000 || dt->year > 2099) 
			return 0;
    if (dt->month < 1 || dt->month > 12) 
			return 0;
    
      leap = is_leap_year(dt->year);
      max_day = days_per_month[leap][dt->month - 1];
    if (dt->day < 1 || dt->day > max_day) return 0;
    
    if (dt->hour > 23 || dt->minute > 59 || dt->second > 59) return 0;
    return 1;
}
 uint32 small_os_load_sys_datetime(const Small_Os_Date_Time* dt)
{
	  uint32 total_days = 0;
    uint8 leap;
	  uint32 total_seconds;
	  uint16 y;
	  uint8_t m;
    if (!validate_date(dt))
			return 0;
    
 
    // 计算2000年到目标年份之间的总天数
    for ( y = 2000; y < dt->year; y++)
  	{
        total_days += is_leap_year(y) ? 366 : 365;
    }
    
    // 计算当年已过天数
     leap = is_leap_year(dt->year);
    for (  m = 1; m < dt->month; m++) 
		{
        total_days += days_per_month[leap][m - 1];
    }
    total_days += dt->day - 1;
    
    // 计算总秒数
    total_seconds = total_days * 86400UL;
    total_seconds += dt->hour * 3600UL;
    total_seconds += dt->minute * 60UL;
    total_seconds += dt->second;
 
		return total_seconds;

}
Small_Os_Date_Time small_os_get_sys_datetime(uint32 counter) 
{
 
    Small_Os_Date_Time dt = {2000, 1, 1, 0, 0, 0};
    uint32 days = counter / 86400;
    uint8 leap;
    uint32 secs;
    // 计算年
    while(days >= 365) 
			{
        uint8 leap = is_leap_year(dt.year);
        uint16_t year_days = leap ? 366 : 365;
        if(days >= year_days)
				{
            days -= year_days;
            dt.year++;
        } else 
				{
            break;
        }
     }
    
    // 计算月日
    leap = is_leap_year(dt.year);
    while(days >= days_per_month[leap][dt.month-1]) 
			{
        days -= days_per_month[leap][dt.month-1];
        dt.month++;
      }
    dt.day = days + 1;
    
    // 计算时分秒
    secs = counter % 86400;
    dt.hour = secs / 3600;
    dt.minute = (secs % 3600) / 60;
    dt.second = secs % 60;
    
    return dt;
}

void small_os_time_set(uint32 counter)
{
	g_small_os_tick =counter;
}
void small_os_time_refresh(void)
{
	 g_small_os_tick ++;
}

void small_os_set_cur_datetime(const Small_Os_Date_Time* dt)
{
	  g_small_os_tick =small_os_load_sys_datetime(dt);
}
Small_Os_Date_Time small_os_get_cur_datetime(void)
{
	return small_os_get_sys_datetime(g_small_os_tick);
}
