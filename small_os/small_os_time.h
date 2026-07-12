#ifndef _SMALL_OS_TIME_H_
#define _SMALL_OS_TIME_H_
 


typedef struct {
    uint16_t year;   // 2000-2099
    uint8_t month;   // 1-12
    uint8_t day;     // 1-31
    uint8_t hour;    // 0-23
    uint8_t minute;  // 0-59
    uint8_t second;  // 0-59
}Small_Os_Date_Time;

 

uint32 small_os_load_sys_datetime(const Small_Os_Date_Time* dt);
Small_Os_Date_Time small_os_get_sys_datetime(uint32 counter);

void small_os_set_cur_datetime(const Small_Os_Date_Time* dt);
Small_Os_Date_Time small_os_get_cur_datetime(void);
void small_os_time_set(uint32 counter);//如果定时刷新时间可以用这个
void small_os_time_refresh(void);//刷新时间，这里放到计数器里
#endif //_SMALL_OS_TIME_H_
