/****************************************************************************
   CREATED BY: 	Stillbright Managment LLC
*					Copyright 2012
*                                                                           
*   FILE:           sensors.c                                               
*                                                                           
*   DESCRIPTION:    variables and functions that manage sensors                                                                           
*                                                        
*   CREATED:		March 9 2012  
* 	REVISION:   	v0.1 - Define operation and functions 
****************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../LIBS/SYS_LIB/sysglobals.h"
#include "../../LIBS/MENUS_LIB/tMenus.h"
#include "../../LIBS/SYS_LIB/c_uart.h"
//#include "../../LIBS/SYS_LIB/spi.h"
//#include "../../LIBS/SYS_LIB/nv_memory.h" //For storing sensors
//#include "../app_memory.h"
#include "../app_inputs.h"
#include DefinedCPU

//wSensor *selectedSensor;
wSensor Sensor[10];  //System will store up to 10 sensors
int     selectedSensor = 0;
/****************** List Params *********************
 * Function used in tMenus for listing all the sensor parameters
 * that are configurable by the user
 */
char* ListParams(char * cBuff)
{
    sprintf(cBuff, "\x1B[2J\x1B[H *** Change Sensor %d Params ***\r\n \
1 - Sensor Name = %s \r\n \
2 - Minutes Between Updates = %d \r\n \
3 - Change Per Count %f\r\n \
4 - Configure Alarms",Sensor[selectedSensor].ID,
                        Sensor[selectedSensor].name,
                        Sensor[selectedSensor].updateInterval,
                        Sensor[selectedSensor].changePerCount );
    return cBuff;
}
char* ConfigSensorParams(char* cBuff, char Param2Config)
{
    if(Param2Config < 0)
    {
        return ListParams(cBuff);
    }
    if(Param2Config == 1)
    {
        SetStrConfig(SetSensorName);
        return;
    }
    if(Param2Config == 2)
    {
        SetUintConfig(SetUpdateInterval);
        return;
    }
    if(Param2Config == 3)
    {
        SetFloatConfig(SetMultiplier);
        return;
    }
    if(Param2Config == 4)
    {
        SetMenuPage(ConfigureAlarms);
        return;
    }
    //cBuff[0] = 0x00;
}
/********************* Select Sensor ****************************
 * Function used in tMenues for allow user to select the sensor 
 * that is to be configured.
 */
char* ConfigureAlarms(char* cBuff, char Param2Config)
{
    if(Param2Config < 0)
    {
        sprintf(cBuff, "\x1B[2J\x1B[H *** Sensor %d Alarm Settings ***\r\n \
1 - HH Alarm = %f \r\n \
2 - High Alarm = %f \r\n \
3 - Low Alarm  = %f\r\n \
4 - LL Alarm  = %f",Sensor[selectedSensor].ID,
                Sensor[selectedSensor].alarmLimitHH,
                Sensor[selectedSensor].alarmLimitHigh,
                Sensor[selectedSensor].alarmLimitLow,
                Sensor[selectedSensor].alarmLimitLL);
        return cBuff;
    }
    if(Param2Config == 1)
    {
        SetStrConfig(SetSensorName);
        return;
    }
    if(Param2Config == 2)
    {
        SetUintConfig(SetUpdateInterval);
        return;
    }
    if(Param2Config == 3)
    {
        SetFloatConfig(SetMultiplier);
        return;
    }
    if(Param2Config == 4)
    {
        SetMenuPage(ConfigureAlarms);
        return;
    }
}
char* SelectSensor(char* cBuff, char SensorNumber)
{
    if(SensorNumber < 0)
    {
         sprintf(cBuff,"\x1B[2J\x1B[H !** Choose Sensor to Configure, 0-9 **!\r\n");
         return cBuff;
    }
    selectedSensor = SensorNumber; //selectedSensor will point to item in array of sensors
    SetMenuPage(ConfigSensorParams);
}

void PutSensor(uChar index)
{
    nvMemBuff[0] = Sensor[index].ID;
    nvMemBuff[1] = Sensor[index].batPercent;
    nvMemBuff[4] = Sensor[index].zeroOffset>>8;
    nvMemBuff[3] = Sensor[index].zeroOffset;
     nvMemBuff[4] = Sensor[index].updateInterval<<8;
    nvMemBuff[5] = Sensor[index].updateInterval;
    nvMemBuff[6] = ((long)Sensor[index].changePerCount>>24) & 0x000F;
    nvMemBuff[7] = ((long)Sensor[index].changePerCount>>16) & 0x000F;
    nvMemBuff[8] = ((long)Sensor[index].changePerCount>>8) & 0x000F;
    nvMemBuff[9] = (long)Sensor[index].changePerCount & 0x000F;
    nvMemBuff[10] = ((long)Sensor[index].alarmLimitHH>>24) & 0x000F;
    nvMemBuff[11] = ((long)Sensor[index].alarmLimitHH>>16) & 0x000F;
    nvMemBuff[12] = ((long)Sensor[index].alarmLimitHH>>8) & 0x000F;
    nvMemBuff[13] = (long)Sensor[index].alarmLimitHH & 0x000F;
    nvMemBuff[14] = ((long)Sensor[index].alarmLimitHigh>>24) & 0x000F;
    nvMemBuff[15] = ((long)Sensor[index].alarmLimitHigh>>16) & 0x000F;
    nvMemBuff[16] = ((long)Sensor[index].alarmLimitHigh>>8) & 0x000F;
    nvMemBuff[17] = (long)Sensor[index].alarmLimitHigh & 0x000F;
    nvMemBuff[18] = ((long)Sensor[index].alarmLimitLow>>24) & 0x000F;
    nvMemBuff[19] = ((long)Sensor[index].alarmLimitLow>>16) & 0x000F;
    nvMemBuff[20] = ((long)Sensor[index].alarmLimitLow>>8) & 0x000F;
    nvMemBuff[21] = (long)Sensor[index].alarmLimitLL & 0x000F;
    nvMemBuff[22] = ((long)Sensor[index].alarmLimitLL>>24) & 0x000F;
    nvMemBuff[23] = ((long)Sensor[index].alarmLimitLL>>16) & 0x000F;
    nvMemBuff[24] = ((long)Sensor[index].alarmLimitLL>>8) & 0x000F;
    nvMemBuff[25] = (long)Sensor[index].alarmLimitLL & 0x000F;
    strcpy(&nvMemBuff[26], Sensor[index].name);
    strcpy(&nvMemBuff[47], Sensor[index].units);
    WriteRTChars(1000,65,nvMemBuff);
}

wSensor* GetSensor(uChar index)
{
    ReadRTChars(1000, 65, nvMemBuff);
    char x = 0;
    for(x; x<44; x++) nvMemBuff[x]=0;
    ReadRTChars(1000,44,nvMemBuff);
    Sensor[index].ID = nvMemBuff[0];
    Sensor[index].batPercent = nvMemBuff[1];
    Sensor[index].zeroOffset = nvMemBuff[2]<<8;
    Sensor[index].zeroOffset = nvMemBuff[3];
    Sensor[index].updateInterval =nvMemBuff[4]<<8;
    Sensor[index].updateInterval = nvMemBuff[5];
    Sensor[index].changePerCount  = (long)nvMemBuff[6]<<24;
    Sensor[index].changePerCount += (long)nvMemBuff[7]<<16;
    Sensor[index].changePerCount += (uInt16)nvMemBuff[8]<<8;
    Sensor[index].changePerCount += nvMemBuff[9];
    Sensor[index].alarmLimitHH  = (long)nvMemBuff[10]<<24;
    Sensor[index].alarmLimitHH += (long)nvMemBuff[11]<<16;
    Sensor[index].alarmLimitHH += (uInt16)nvMemBuff[12]<<8;
    Sensor[index].alarmLimitHH += nvMemBuff[13];
    Sensor[index].alarmLimitHigh  = (long)nvMemBuff[14]<<24;
    Sensor[index].alarmLimitHigh += (long)nvMemBuff[15]<<16;
    Sensor[index].alarmLimitHigh += (uInt16)nvMemBuff[16]<<8;
    Sensor[index].alarmLimitHigh += nvMemBuff[17];
    Sensor[index].alarmLimitLow  = (long)nvMemBuff[18]<<24;
    Sensor[index].alarmLimitLow += (long)nvMemBuff[19]<<16;
    Sensor[index].alarmLimitLow += (uInt16)nvMemBuff[20]<<8;
    Sensor[index].alarmLimitLow += nvMemBuff[21];
    Sensor[index].alarmLimitLL  = (long)nvMemBuff[22]<<24;
    Sensor[index].alarmLimitLL += (long)nvMemBuff[23]<<16;
    Sensor[index].alarmLimitLL += (uInt16)nvMemBuff[24]<<8;
    Sensor[index].alarmLimitLL += nvMemBuff[25];
    strcpy(Sensor[index].name, &nvMemBuff[26]);
    strcpy(Sensor[index].units, &nvMemBuff[47]);

}
/********************** Populate Sensor Array *****************
 * Used in main to allocate memory in RAM for sensors.  Populates
 * sensors with defaut values. Which will then be overwritten with
 * values retrived from NV memory
 */
void PopulateSensorArray(void)
{
   int index = 0; 
   for(index = 0; index < MAX_NUM_SENSORS; index++)
   {
       Sensor[index].ID = index;
       Sensor[index].batPercent = 0;
       Sensor[index].changePerCount = .005; //Based on 0-5 Volts divided by 10 bits.
       Sensor[index].zeroOffset = 0;
       sprintf(Sensor[index].units, "volts");
       sprintf(Sensor[index].name,"Sensor %d",index);
       Sensor[index].alarmLimitHH = 500.555;
       Sensor[index].alarmLimitHigh = 400.445;
       Sensor[index].alarmLimitLow = -400.432;
       Sensor[index].alarmLimitLL = -500.543;
       Sensor[index].updateInterval = 4;//
   }
}


char* SetUpdateInterval(char* cBuff, uInt16 Interval)
{
    if(cBuff[0] <= 0x00)
    {
        sprintf(cBuff,"\x1B[2J\x1B[H Enter Value 1 to 65,535 \r\n \
\tUpdateInterval = ");
        return cBuff;
    }
    //selectedSensor->updateInterval = Interval;
   Sensor[selectedSensor].updateInterval = Interval;
}
char* SetMinProcessValue(char* cBuff,  uInt16 MinValue)
{
    //DummySensorInput(param1Int, MinValue);
    return cBuff;
}
char* SetMaxProcessValue(char* cBuff, int MaxValue)
{

}
char* SetMultiplier(char* cBuff, float pMultiplier)
{

}
char* SetZeroOffset(char* cBuff, uInt16 zOffset)
{

}
char* SetSensorName(char* cBuff, uInt16 NumChars)
{
    if(cBuff[0] <= 0x00)
    {
        sprintf(cBuff,"\x1B[2J\x1B[H New Sensor Name = ");
        return cBuff;
    }
    sprintf(Sensor[selectedSensor].name,cBuff,selectedSensor);
}
void SetID(wSensor *s, BYTE id)
{
	s->ID = id;
	return;
}

