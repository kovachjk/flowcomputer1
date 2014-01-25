/****************************************************************************
   CREATED BY: 	Stillbright Managment LLC
*					Copyright 2012
*                                                                           
*   FILE:           sys_time.h                                               
*                                                                           
*   DESCRIPTION:    Controls Timer1 or Core Timer (MCU dependant) functions.  This 
					module defines function calls that are agnostic of the RTC module used.
					When a RTC is choosen, it should be implemented with the function calls
					that are defined here.
					
					The format of time used in this module will be unix time which is 
*                                                        
*   CREATED:		March 29 2012  
* 	REVISION:   	v0.1 - Define operation and functions 
					10/10/12 - Expanded functions
					10/27/12 - Combined time_date.h with this sys_time
****************************************************************************/
#ifndef _sys_time_h_
#define _sys_time_h_
#include "../SYS_LIB/sysglobals.h"
#include "../WIFI_LIB/wifi.h"
//sysTime is used by the timer funtions in timer.h 						
// Let compile time pre-processor calculate the CORE_TICK_PERIOD
#define TOGGLES_PER_SEC     1000
//#define OffTime             (SYSCLK/60)
#define CORE_TICK_RATE  (SYSCLK/TOGGLES_PER_SEC)
#define displayTime24 	0x0001// else display time in AM and PM 
#define alarm1Enabled 	0x0002
#define alarm1ON	0x0004
#define alarm1Cleared	0x0008
// At startup, the RTC will seed this struct with current time.
//TODO: Consider just running unix number and using functions to return
//strings for different date time formats.
typedef struct sysClock
{
	uChar Hours;
	uChar Minutes;
	uChar Seconds;
	uInt mSeconds;
}SysClock;

extern SysClock Time;  // Used by other peripherals
void InitSysClock(void);
char* ConfigRTC(char* cBuff, char keyPress);
char* ConfigTimeDate(char* cBuff, char keyPress);
/********************************************************************************************
										MENU FUNCTIONS
**********************************************************************************************/

/********************************************************************************************
										CONFIGURATION FUNCTIONS
**********************************************************************************************/
extern int dateTimeFlags;
char * Time2String(int flags);
//Set Date will use the format MMDDYY to set the date)123099
char * SetDate(long currentDate);
//Set Time will use the format HHMM to set the date)123099
char * SetTime(uInt currentTime);

#endif
