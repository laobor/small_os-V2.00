#include "small_os_typedef.h"
#include "small_os_log.h"
#include "small_os_time.h"
#include "hlxd_uart.h"
#include <string.h>
#include <stdio.h>
#define SMALL_OS_LOG_CUR_LVL_  LOG_LVL_DEBUG
 
 Small_Os_Log_Level g_small_os_log_level_cur =SMALL_OS_LOG_CUR_LVL_;
 extrn_printf_fun send_msg=NULL;
 
 
 
 void small_os_init_printf(extrn_printf_fun fun)
 {
	 send_msg = fun;
 }
void small_os_printf_log(Small_Os_Log_Level level,char *buf)
{
	 char str[280];
	int lengs  =strlen(buf);
  if(lengs>256||send_msg==NULL||buf==NULL) return;
 
	switch(level)
	{
		case LOG_LVL_TRACE:
			strcpy(str,"TRACE:");
			lengs+=6;
			break;
		case LOG_LVL_DEBUG:
			strcpy(str,"DEBUG:");
			lengs+=6;
			break;
		case LOG_LVL_INFO:
			strcpy(str,"INFO:");
			lengs+=5;
			break;
		case LOG_LVL_WARN:
			strcpy(str,"WARN:");
			lengs+=5;
			break;
		case LOG_LVL_ERROR:
			strcpy(str,"ERROR:");
			lengs+=6;
			break;
		default:
			str[0]=0;
			break;
		
	}
		strcat(str,buf);
		send_msg((uint8*)str,lengs);
}
void small_os_printf(int level,char *buf)
{
	int lengs  =strlen(buf);
  if(lengs>256||send_msg==NULL||buf==NULL) return;
	if(g_small_os_log_level_cur<=level)
	{
		 send_msg((uint8*)buf,lengs);
	}
	 
	else  
	{
		//	small_os_log_debug(buf);
	}	
	
	
}
void small_os_printf_hex(uint8*buf,uint16 lengs)
{
	  if(lengs>256||send_msg==NULL||buf==NULL) return;
	send_msg((uint8*)buf,lengs);
}
