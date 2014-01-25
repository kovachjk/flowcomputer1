/* 
 * File:   runapp.h
 * Author: JKovach - Copyright Stillbright LLC 2012
 * Description: Module for holding the appMain function which is the starting point for any
 * application.
 * September 9, 2012, 2:40 PM: Created
 *
 */
//#include "../LIBS/SYS_LIB/time_date.h"
//#include "../LIBS/SYS_LIB/sys_clock.h"
#include "../LIBS/MENUS_LIB/tMenus.h"
#include "../LIBS/SYS_LIB/sysglobals.h"
//#include "../LIBS/SYS_LIB/c_uart.h"
#include "fluids.h"
#include "../LIBS/WIFI_LIB/wifi.h"
#include "../LIBS/SYS_LIB/systime_date.h"
#include "../LIBS/SYS_LIB/sys_inputs.h"
//#include "../report_mgr.h"

#ifndef RUNAPP_H
#define	RUNAPP_H



/*********************************************************************************************
	             **        Aplication Status Defines       **
 ************************************************************************************************/
#define app_CLEAR_ERRORS    0X00000000
#define app_PAUSED          0x00000002
#define app_STOP_OUTPUT     0x00000004
#define app_420_ERR         0x00000008
#define app_VIN_ERR         0x00000010
#define app_FLUID_ERR       0x00000020
#define app_DIVBYZERO_ERR   0x00000040
#define app_CHECK_ALL_ERRORS 0xFFFFFFFF
/*********************************************************************************************
	             **        Aplication Error Defines       **
 ************************************************************************************************/


extern uInt appStatus;


void RunAppMain(void);
char* AppMainMenu(char* cBuff, char keyPress);
char* ConfigSystem(char* cBuff, char keyPress);
char* ConfigApps(char* cBuff, char keyPress);
char* ConfigSensors(char* cBuff, char keyPress);
char* ReportMenu(char* cBuff, char keyPress);
char* RunErrorMenu(char* cBuff, char keyPress);
void DisplayAppResults(char *ScreenData);
void SetAppStatus(uInt State);
void ClearAppStatus(uInt State);
uShort CheckAppStatus(uInt State);
#endif	/* RUNAPP_H */

