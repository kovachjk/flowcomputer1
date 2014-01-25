/****************************************************************************
   CREATED BY: 	Stillbright Managment LLC
*					Copyright 2012
*                                                                           
*   FILE:           time_date.h                                               
*                                                                           
*   DESCRIPTION:    Time and date functions.  This module is a templet and define
                    generic function calls that are agnostic of the RTC module used.
                    When a RTC is choosen, it should be implemented with the function calls
                    that are defined here.
                    The format of time used in this module will be unix time which is
*                                                        
*   CREATED:		March 29 2012  
*   REVISION:   	v0.1 - Define operation and functions
					10/10/12 - Expanded functions
****************************************************************************/
#include "sysglobals.h"

#define DisplayTime24 	0x0001// else display time in AM and PM
#define Alarm1ON        0x0004
#define Alarm2ON        0x0008
#define Alarm1Cleared	0x0010

typedef struct dtVar
{
    uShort mSec;
    uChar min;
    uChar hr;
    uChar day;
    uChar mth;
    uChar yr;
}DateTimeVar;
extern int dateTimeFlags;

char * Time2String(int flags);
DateTimeVar* GetDateTime(DateTimeVar * DateTime);
//Set Date will use the format MMDDYY to set the date)123099
char * SetDate(long currentDate);
//Set Time will use the format HHMM to set 24 hour based time) e.g. 1730 = 5:30PM
char * SetTime(uInt currentTime);
