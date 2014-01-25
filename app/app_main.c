/*
 * File:   app_main.c
 * Author: JKovach - Copyright Stillbright LLC 2012
 * Description: Module for holding the appMain function which is the starting point for any
 * application.
 * Revisions:   9/9/12 - Created
 *              10/24/12 -  Added switch variable to control what sensor inputs are being used
 *              used by the application.
 *
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../app_main.h"
#include "../../Microhip/Include/Graphics/Graphics.h"

//************************************* Sensor Input Defines ********************************
// There are four groups of switches, allowing configuration of up to four inputs.
//Switches for 

uInt    inputSwitches, 
        appStatus; //Holds error flags indicating app condition
void RunAppMain(void)
{
    if(appStatus == 0)
    {
        mPORTAToggleBits(BIT_0);
        //Switch run apps
    
    }
    else SetMenuPage(RunErrorMenu);
    

}
void DisplayAppResults(char *CharBuff)
{
      SetColor(YELLOW);
        LCDCenterString( -4, "Main Application Running");
       // SetColor(BLACK);
        //LCDLineHome();
        LCDClearLine(9);//JK This function Takes a lot of time
        SetColor(YELLOW);
        sprintf(CharBuff,"Time is %d :%d : %d", Time.Hours, Time.Minutes, Time.Seconds);
        LCDCenterString( 4, CharBuff);
        //WriteTerminalU1(CharBuff);
}
char* RunErrorMenu(char* cBuff, char keyPress)
{
    if(keyPress < 0)
    {
        sprintf(cBuff," !** Error Menu **!\r\n \
** Press to Fix ** \
1-Sensor Errors\r\n \
2-Fluid Errors\r\n \
3-App Errors\r\n");
        return cBuff;
    }
    if(keyPress == 1)
    {
        SetMenuPage(ReportMenu);
    }
    if(keyPress == 2)
    {
        SetMenuPage(ConfigApps);
    }
    if(keyPress == 3)
    {
        SetMenuPage(ConfigSystem);
    }   
    cBuff[0] = 0x00;
    return cBuff;
}
char* AppMainMenu(char* cBuff, char keyPress)
{
    if(keyPress < 0)
    {
        sprintf(cBuff," !** Main Menu **!\r\n \
1-Reports\r\n \
2-Config Apps\r\n \
3-Config System\r\n \
4-Run App");
        return cBuff;
    }
    if(keyPress == 1)
    {
        SetMenuPage(ReportMenu);
    }
    if(keyPress == 2)
    {
        SetMenuPage(ConfigApps);
    }
    if(keyPress == 3)
    {
        SetMenuPage(ConfigSystem);
    } 
    if(keyPress == 4)
    {
        SetMenuPage(ConfigSystem);
    }     
    cBuff[0] = 0x00;
    return cBuff;
}
/*
 * 1 - report_mgr
 * 2 - app_inputs
 * 3 - app_main */

char* ConfigApps(char* cBuff, char keyPress)
{
    if(keyPress < 0)
    {
        sprintf(cBuff," *Application Menu*\r\n \
1-Config Fluid\r\n \
2-Config Sensors\r\n \
3-Config App\r\n \
");
        return cBuff;
    }
    if(keyPress == 1)
    {
        //SetMenuPage(ConfigSensors);
    }
    if(keyPress ==2)
    {
        SetMenuPage(WiFiConfigDHCP);
    }
    cBuff[0] = 0x00;
    return cBuff;
}

char* ConfigSystem(char* cBuff, char keyPress)
{
    if(keyPress < 0)
    {
        sprintf(cBuff," *Config System*\r\n \
1 - Config ADC\r\n \
2 - Config Time/Date \r\n \
3 - Pressure User\r\n");
        return cBuff;
    }
    if(keyPress == 1)
    {
        SetMenuPage(ConfigSystemInputs);
    }
    if(keyPress ==2)
    {
        SetMenuPage(ConfigTimeDate);
    }
    cBuff[0] = 0x00;
    return cBuff;
}
char* ReportMenu(char* cBuff, char keyPress)
{
    if(keyPress < 0)
    {
        sprintf(cBuff," *Report Menu* \r\n \
1 - Config ADC\r\n \
2 - Config Time/Date \r\n \
3 - Pressure User\r\n");
        return cBuff;
    }
    if(keyPress == 1)
    {
        SetMenuPage(ConfigSystemInputs);
    }
    if(keyPress ==2)
    {
        SetMenuPage(ConfigTimeDate);
    }
    cBuff[0] = 0x00;
    return cBuff;
}
void SetAppStatus(uInt State)
{
    appStatus |= State;
}
void ClearAppStatus(uInt State)
{
    appStatus &= ~State;
}
uShort CheckAppStatus(uInt State)
{
    if(appStatus & State == State)
        return (uShort)1;
    else
        return (uShort)0;
}