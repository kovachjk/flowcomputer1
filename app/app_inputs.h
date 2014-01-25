
/****************************************************************************
*          STILLBRIGHT MANAGMENT                *
*                                                                           *
*   FILE:           app_sensors.h                                              *
*                                                                           *
*   DESCRIPTION:    This file contains the definitions required by and      *
*                   the function prototypes for all the sensor types use
 *                  by an application.   This file uses the sys_adc.h file                                  *
*                                                                           *
*   REVISIONS:  9/15/10 Created
 *              10/27/12 Menus started
 *              11/23/12 Rename file.  Broke code logic for inputs  into
 *              two files.  sys_adc.h will deal with converting voltage
 *              pulses and current into a percent of range.
 *              flow_sensors.h will convert from a range of electrical units
 *              to a range of product flow or temperature.
*       Original release.                                                   *
****************************************************************************/

#ifndef _APP_SENSORS_H              // Show that this file has been included
#define _APP_SENSORS_H
/***********************************************************************************************
                                **  Required Header Files  **
************************************************************************************************/
#include "../LIBS/SYS_LIB/sysglobals.h"
#include "app_includes.h"

/***********************************************************************************************
                                **  Defined Meter Types  **
************************************************************************************************/

#define turbineMeter    0
#define srMeter         1
#define linearMeter     2
#define expoMeter       3
/***********************************************************************************************
                                **  Required Header Files  **
************************************************************************************************/

typedef struct
{
	int	typeUnits; //gal, l, bbl
	int 	timeBase; 		//gal/Hr gal/min	
	float	PPU; //Pulse Per Unit
	long	pulsesTot; // Total since last reset
	long	pulsesPerTime; //Pulses stored then reset per time base 
	long	pulsesMax;
	long	pulsesMin;
}structFlowObject ;

/***********************************************************************************************
                                **  Required Header Files  **
************************************************************************************************/
char* ConfigSensors(char* cBuff, char keyPress);
char* FlowMeterConfig(char* cBuff, char keyPress);
void initFlowIn1(int Units, float UPP); //How many measurement units per pulse				
void ResetMinMax(char FlowNum); 
char* ChangeFlowMeterType(char* MenuBuff, char KeyPress );
char* ConfigMeter(char *MenuBuff, char KeyPress);
/***********************************************************************************************
                                **  Required Header Files  **
************************************************************************************************/
void AddFlow2(uInt NumPulses);
extern structFlowObject Flow1;	//Flow1 Var
extern structFlowObject Flow2;	//Flow2 Var

#endif
