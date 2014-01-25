/*  ***************************************************************************
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
#include "../../SYS_LIB/sysglobals.h"
#include "../../MENUS_LIB/tMenus.h"
#include "../../SYS_LIB/c_uart.h"
#include "../wifi.h"



char* WiFiConfigMenu(char* cBuff, char keyPress)
{
    if(keyPress < 0)
    {
        sprintf(cBuff,"\x1B[2J\x1B[H  !** Config WiFi Menu **!\r\n \
\t1 - List Access Points\r\n \
\t2 - Configure DHCP 1-9\r\n");
        return cBuff;
    }
    if(keyPress == 1)
    {
        SetMenuPage(WiFiAccessPoints);
    }
    if(keyPress ==2)
    {
        SetMenuPage(WiFiConfigDHCP);
    }
    cBuff[0] = 0x00;
    return cBuff;
}
char* WiFiAccessPoints(char* cBuff, char keyPress)
{
    if(keyPress < 0)
    {
        sprintf(cBuff, "\x1B[2J\x1B[H Available Access Points \r\n \
\t1 - Stillbright ");  
        return cBuff;
    }
}

char* WiFiConfigDHCP(char* cBuff, char keyPress)
{
    if(keyPress < 0)
    {
        sprintf(cBuff,"\x1B[2J\x1B[H  !** Config DHCP **!\r\n \
\t1 - Set Local IP\r\n \
\t2 - Set Network Mask \r\n \
\t3 - Set Static IP");
        return cBuff;
    }
}
