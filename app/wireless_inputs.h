/****************************************************************************
   CREATED BY: 	Stillbright Managment LLC
*					Copyright 2012
*                                                                           
*   FILE:           sensors.h                                               
*                                                                           
*   DESCRIPTION:    Functions for managing generic sensors.  These functions were initially
					written for wireless sensors which use batteries.
*                                                        
*   Feb 24 2012  	Define operation and functions 
*	11/23/12		Trying to rewrite so that these same functions can be used for both
					wireless and embedded generic sensors
****************************************************************************/

#ifndef __WIRELESS_SENSORS_H
#define __WIRELESS_SENSORS_H
#include "../LIBS/SYS_LIB/sysglobals.h"

/**************** structSensor ****************************************
 *  Goal is to make stuct as generica as possible.  Different function will
 *  pre calculate change per count therefore needing only a mulitplication
 *  routine for each conversion.
*/
#define MAX_NUM_SENSORS 10

typedef struct
{
	uChar   ID;
	uChar   batPercent;
	uInt16  updateInterval; // In minutes
	uInt16  intervalAmount;// Minutes since last interval
        int     zeroOffset;
        float   changePerCount;
        float   lastValue;
        float   alarmLimitHH;
        float   alarmLimitHigh;
        float   alarmLimitLow;
        float   alarmLimitLL;
        char    name[20];
        char    units[8];
}wSensor;

//extern wSensor *s1;

//Sets pointer to one of the sensors in the sensor array
//Adds default values to sensor and selects it as current
extern char* AddSensor(void);
//Load the params in the Sensor array from NVmemory
void PopulateSensorArray(void);
char* ConfigSensorParams(char* cBuffchar, char Param2Config);
char* SelectSensor(char* cBuff, char SensorNumber);
char* SetMaxProcessValue(char* cBuff, int MaxValue);
char* SetMinProcessValue(char* cBuff, uInt16 MinValue);
char* SetUpdateInterval(char* cBuff, uInt16 Interval);
char* SetMultiplier(char* cBuff, float pMultiplier);
char* SetZeroOffset(char* cBuff, uInt16 zOffset);
char* SetHighHighLimit(char* cBuff, uInt16 hhAlarm);
char* SetHighLimit(char* cBuff, uInt16 hAlarm);
char* SetLowLimit(char* cBuff, uInt16 lAlarm);
char* SetLowLowLimit(char* cBuff, uInt16 llAlarm);
char* SetSensorName(char* cBuff, uInt16 NumChars);
char* ConfigureAlarms(char* cBuff, char Param2Config);
//Reads sensor information from NV memory and fills in info at wSensor array at index ID
wSensor* GetSensor(uChar ID);
//Takes wSensor info at wSensor array[ID] and writes it to NV memory
void PutSensor(uChar ID);
#endif

