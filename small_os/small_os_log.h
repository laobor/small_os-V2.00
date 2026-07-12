#ifndef _SMALL_OS_LOG_
#define _SMALL_OS_LOG_
 typedef enum 
 {
    LOG_LVL_TRACE ,
    LOG_LVL_DEBUG ,
    LOG_LVL_INFO ,
    LOG_LVL_WARN  ,
    LOG_LVL_ERROR 
}Small_Os_Log_Level;
typedef  void(*extrn_printf_fun)(uint8*buf,uint16 lengs); 
// typedef struct 
// {
// 	extrn_printf_fun fun;
// 	uint16 lengs;
// 	uint8 *buf;
// } Small_Os_Printf_Fun;

void small_os_init_printf(extrn_printf_fun fun);
void small_os_printf(int level,char *buf);
void small_os_printf_log(Small_Os_Log_Level level,char *buf);
void small_os_printf_hex(uint8*buf,uint16 lengs);
#endif //_SMALL_OS_LOG_
