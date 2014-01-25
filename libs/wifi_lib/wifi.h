/****************************************************************************
   CREATED BY: 	Stillbright Managment LLC
*					Copyright 2012
*
*   FILE:           sensors.h
*
*   DESCRIPTION:    Code for displaying to and interacting with users
*					through a hypertermal or TTY type interface.
*
*   CREATED:		Feb 24 2012
* 	REVISION:   	v0.1 - Define operation and functions
*	3/8/2012	v0.xx- tMenus_old0.h abandoned for a function pointer system
****************************************************************************/


#ifndef _WIFI_H
#define _WIFI_H

#include "../../LIBS/SYS_LIB/sysglobals.h"
typedef struct
{
    char apName[16];
    char apPassword[16];
    char Remove;//Flag AP for removal
}apStruct;
typedef struct
{
    uChar DHCP;//Static or DCHCP
    uChar IP[6];
    uChar Subnet[6];
}epConfig;
char* WiFiConfigMenu(char* cBuff, char keyPress);
char* WiFiAccessPoints(char* cBuff, char keyPress);
char* WiFiConfigDHCP(char* cBuff, char keyPress);
char AddAP();
char SubtractAP(char apIndex);
char GetAPs(void); //Retieves all stored APs returns number of APs
apStruct* FindAccessPoint(char* cBuff);//Looks through array of previously used APs


#endif
