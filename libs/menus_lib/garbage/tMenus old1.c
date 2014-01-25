
/****************************************************************************
*   CREATED BY: 	Stillbright Managment LLC
*					Copyright 2012
*                                                                           
*   FILE:           tMenus.c
*                                                                           
*   DESCRIPTION:    Code for displaying to and interacting with users      
*                   through a hypertermal or TTY type interface.
*                                                        
*   CREATED:		Feb 24 2012  
* 	REVISION:   	v0.1 - Define operation and functions 
*	3/8/2012	v0.xx - abandoned for a function pointer system
******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../SYS_LIB/sysglobals.h"
#include "../tMenus.h"
#include "../../SENSORS/sensors.h"
#include DefinedCPU

uChar	uBufferIndex = 0,//index for numeric string
        mBufferIndex = 0;

char	*mBuff, 
        rtnCount = 0,
        menuSelection,
        stringBuff[MENU_BUFF_SZ];//Holds users input before conversion of atoi() or atof()
int	tempInt,//Holds atoi conversion
        param1Int;//Hold a parameter used when doing configuration
float	tempFloat;	//Holds atof conversion 
uChar rxIndex = 0; //For building string arrays of ints, floats and strings
void (*CurrentMenuPtr)(char);
void (*IntFunctionPtr)(int);
void (*MenuHistory[5])(char); 
char keyPress[5];//Holds the key pressed in menu history
int  mIndex;//menu history index   
static enum
{
	SHOW_MENU = 0,
	MENU_INPUT,
	INT_INPUT,
	FLOAT_INPUT,
	Y_N_INPUT,
	STRING_INPUT
}INPUT_TYPE = MENU_INPUT;
void WelcomeMenu(char keyPress)
{
    if(keyPress > 0)
    sprintf(mBuff,"\x1B[2J\x1B[H !** Welcome - Main Menu **!\r\n \
\t1 - Config Sensors \r\n \
\t2 - Config WiFi\r\n "); 
    CurrentMenuPtr = MainMenu;
}
void MainMenu(char keyPress)
{
    if(keyPress == 1)
    {
        CurrentMenuPtr = SelectSensor;   
        sprintf(mBuff,"\x1B[2J\x1B[H !** Choose Sensor to Configure, 0-9 **!\r\n");
    }
    if(keyPress == 2)
    {
        sprintf(mBuff,"\x1B[2J\x1B[H  !** Config WiFi Menu **!\r\n \
\t1 - List Access Points\r\n \
\t2 - Configure DHCP 1-9\r\n");
        CurrentMenuPtr = WiFiConfigMenu;
    }
}
void SelectSensor(char SensorNumber)
{
    ListParams(mBuff);
    /*
    sprintf(mBuff,"\x1B[2J\x1B[H!** Sensor Number %i Configuration**!\r\n \
\t1 - Set Max Process Value\r\n \
\t2 - Set Min Process Value\r\n \
\t3 - Set Max Input\r\n  \
\t3 - Set Min Input\r\n", SensorNumber );    */
    param1Int = SensorNumber; //Holds the Sensor we want to configure
    CurrentMenuPtr = ConfigSensorParams;
    
}
void ConfigSensorParams(char ParamType)
{
    if(ParamType == 1)
    {
        sprintf(mBuff,"\x1B[2J\x1B[H Enter Value -32,768 to 32,767");
        IntFunctionPtr = SensorMaxProcessValue;   
    }
    if(ParamType == 2)
    {
        sprintf(mBuff,"\x1B[2J\x1B[H Enter Value -32,768 to 32,767");
        IntFunctionPtr = SensorMinProcessValue;  
    }
}
void WiFiConfigMenu(char keyPress)
{
    if(keyPress == 1)
        sprintf(mBuff,"\x1B[2J\x1B[H List of Access Points");
    if(keyPress ==2)
        sprintf(mBuff,"\x1B[2J\x1B[H Enable/Disable DHCP" );
}
void SensorMaxProcessValue(int MaxValue)
{
    DummySensorInput(param1Int, MaxValue);
}
void SensorMinProcessValue(int MinValue)
{
    DummySensorInput(param1Int, MinValue);
}
void DummySensorInput(int SensorNum, int MaxValue)// Would be in sensor file
{
    SensorNum = MaxValue;
}

/*

void fOption1(char keyPress)
{
    sprintf(mBuff,"Option 2 Says Hello");
    if(keyPress > 0 )
    {
        //CurrentMenuPtr = &fOption1;
    }
}*/
void ShowPreviousMenu()
{
    
    return;
}

char* RunMenu(char *buff)
{
        mBuff = buff;
	if(buff[0] == 0x0D)//If we receive 3 CRs together, reset menu. Used by program
	{
            if(rtnCount > 1)
            {
                mIndex = 0;
                INPUT_TYPE  = MENU_INPUT;
                MenuHistory[mIndex] = WelcomeMenu;
                keyPress[mIndex] = 9;
                MenuHistory[mIndex](keyPress[mIndex]);
                return mBuff;
            }
            rtnCount++;
	}
        else rtnCount = 0;
                 
	//if the esc or backspace key is pressed go up the menu tree
	if((mBuff[0] == 0x08) || (mBuff[0] == 0x1B))//If user presses backspace or ecs move menu back one
	{
            if(mIndex > 0) //
            {       
                mIndex--;
                MenuHistory[mIndex](keyPress[mIndex]);
                return mBuff ;
            }
	}			
	if(INPUT_TYPE == MENU_INPUT) //Limits inputs to number 1 to 9;
	{
		if(mBuff[0] >= 47 && mBuff[0] <= 57)
		{
                    mIndex++;
                    MenuHistory[mIndex] = CurrentMenuPtr;
                    keyPress[mIndex] = atoi(&mBuff[0]);
                    CurrentMenuPtr(keyPress[mIndex]);
                    //MenuHistory[mIndex + 1] = CurrentMenuPtr;
                    return mBuff;
		}      
                mBuff[0] = 0x00;
                return mBuff;
	}
	//INT_INPUT stores chars from user until CR then converts to int
	//then takes int and uses it to set pre selected variable of 
	//pre-selected object.
	if(INPUT_TYPE == INT_INPUT)	
	{
		if(mBuff[0] >= 47 && mBuff[0] <= 57)
		{
                    stringBuff[mBufferIndex++]=mBuff[uBufferIndex++];
                    stringBuff[mBufferIndex + 1] = 0x00;
                    return mBuff;
		}
		if(mBuff[uBufferIndex] == 0x0D)//Input complete, process string
		{
                    mBuff[--uBufferIndex] = 0x00;//Delete 0x0D replace with NULL
                    uBufferIndex = 0; //Reset index
                    mBufferIndex = 0; //Reset index
                    //if(tempInt != NULL) (*tempInt)(int);
                    if(IntFunctionPtr != NULL )//Be sure your pointing at something
                    {
                        IntFunctionPtr(atoi(stringBuff));
                        return mBuff;
                    }
                    else 
                    {
                        sprintf(mBuff,"Null Pointer Error");
                        INPUT_TYPE = MENU_INPUT; //Go back to last menu
                        return mBuff;
                    }
                    
		}
                mBuff[0] = 0x00;
                return mBuff;
              
	}
 	if(INPUT_TYPE == STRING_INPUT)	
	{     
            
        }  
	if(INPUT_TYPE == SHOW_MENU)	
	{
            sprintf(mBuff,"!**   Welcome-Main Menu   **!\r\n\t1 - Config Sensors \r\n \t2 - Do Whatever\r\n");
            //Do not write to uart here. Might want TCP
            INPUT_TYPE  = MENU_INPUT;
	}
	return mBuff;
	
}

void Respond2Input(void)
{
	switch(menuL0)
   	{
            case 1:
                switch(menuL1)//Sensor Configuration Menu
                {
                    case 1:
                        sprintf(mBuff,"!** Config Sensor Number 1 **!\r\n \t1 - Set Max Process Value\r\n \
                        \t2 - Set Min Process Value\r\n\t3 - Set Max Input\r\n  \
                        \t3 - Set Min Input\r\n ");
                        INPUT_TYPE = MENU_INPUT;
                        break;
                    case 2:
                        sprintf(mBuff,"!** Config Sensor Number 2 **!\r\n \t1 - Set Max Process Value\r\n \
                        \t2 - Set Min Process Value\r\n\t3 - Set Max Input\r\n  \
                        \t3 - Set Min Input\r\n ");
                        INPUT_TYPE = MENU_INPUT;
                        break;
                    case 0:
                        sprintf(mBuff,"!** Config Sensor Menu **!\r\n \t Enter Sensor Number 1-9\r\n\t ESC = GoBack\r\n");
                        INPUT_TYPE = MENU_INPUT;
                        menuL0 = 1;
                        menuL1 = 0;
                        return;
                }
                break;
		case 2:
                    switch(menuL1)// WiFi Setup Menu
                    {
                            case 1:
                                sprintf(mBuff,"!** List of WiFi Access Points  **!\r\n \t1 -Enter Sensor Number\r\n \t2 - Sensor 1-9\r\n\t3 - GoBack\r\n");
                                INPUT_TYPE = MENU_INPUT;
                                GetAccessPoints();
                                return;
                            case 2:
                                if(menuL2 > 0)
                                {
                                    sprintf(mBuff,"!** DHCP Setting  **!\r\n \t1 - Enable DHCP \r\n \t2 - Enter Password 1-9\r\n\t3 - GoBack\r\n");
                                    INPUT_TYPE = MENU_INPUT;
                                    menuL1 = 2;
                                }
                                break;
                            case 0:
                                
                                INPUT_TYPE = MENU_INPUT;
                                menuL0 = 2;
                                menuL1 = 0;
                                break;
                    }
                    break;
		default:
    		sprintf(mBuff,"!** Welcome to my main menu **!\r\n \t1 - Config Sensors \r\n \t2 - Config WiFi\r\n\t3 - GoBack\r\n");
			INPUT_TYPE = MENU_INPUT;
			menuL0 = 0;	
			menuL1 = 0;		
		return;	
	}	
}
#ifdef _TMENU_CONNECTION_UART

char* ReadRX2(void)
{
    //U2TXREG = U2RXREG;
    //*
    rxIndex = 0;


    while (U2STAbits.URXDA) // While data is available in the buffer
    {
        stringBuff[rxIndex++]=U2RXREG;
    }
    stringBuff[rxIndex]=0x00;//*/
    return stringBuff;

}
void WriteChar(char Data)
{
    U2TXREG = Data;
}

//Writes a null terminated series of chars

void WriteString(char *cData)
{
    //U2TXREG = cData[0];
    //txIndex++;
    while(*cData != 0x00)
    {
        while(U2STAbits.UTXBF);
        U2TXREG = *cData++;
    }
}
#endif
void GetAccessPoints(void)
{
	sprintf(mBuff, "!** Select Access Point **!\r\n");
	strcat(mBuff,"\t 1 - Stillbright\r\n");
	strcat(mBuff,"\t 2 - Riotech\r\n");
	return;	
}


