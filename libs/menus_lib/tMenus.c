
/****************************************************************************
   CREATED BY: 	Stillbright Managment LLC
*					Copyright 2012
*
*   FILE:           tMenus.c
*
*   DESCRIPTION:    Menu System for displaying to and interacting with users
*	through a hypertermal or TTY type interface.
	OVERVIEW:	The System is based on a menu state machine that changes state based on the
	operation to be performed, some examples of different states are, menu navigation, SetIntConfig,
	SetUintConfig, SetStringConfig, SetBinaryConfig.  The different states control and verify
	the input requirements and restriction of each type of parameter that needs to be configured.
	All function fall into two main catagories, navigation and configuration.  While navagation
	funtions can have depth, allowing users to go up and down a menu tree. Configuration function
	are one deep.  This means that a user can go done several levels to select a parameter to
	change and  once the change is made the system will automatically return the user back to the
	previous menu that called the configuration function. Both groups of funtions have simular
	structure.  Both can return a char pointer and take a char pointer as the first argument.  The
	second argument is specific to the type of parameter to be changed; menu keypress, int,
	unsigned int, string, binary, ect.  Both types of functions also have a default string that
	is use to communcate options and actions to the user.

	The menu system starts with the main menu function found in tmenu.c.
					char* MainMenu(char* cBuff, char keyPress)
	This function holds the default string discribing the start of the menu tree and the options
	avaiable within.  The MainMenu function is a templet for all other functions.  It contains
 *      a switch that will do one of three things.
 *          1. If <0 Return a string discribing what options are available
 *          2. 0 to 9 - Call SetMenuPage and assign a funtion that will call another menu function
 *          3. 0 to 9 - call SetxxxConfig and assign a function that config an int, float, string, etc. function
	Menu type functions will only recognize a single keypress of zero to 9 or other
 *      control key char.
 *      Configuration functions are called from a menu function by using a SetXXXConfig function.  A
 *      SetXXXConfig function takes a function pointer as its single argument.  The structure
	of any particular function is defined in tmenu.h.

	The system is set up so that menu navigation and configuration settings can broken out and contained
	within the files associated with the periphereal.  The setting to

*
*   CREATED:		Feb 24 2012
*   REVISION:   v0.1 - Define operation and functions
*   3/8/2012    tMenus_old0.h abandoned for a function pointer system
*   4/2/2012    Moved uart function over to c_uart.h.  Exposed CONFIG_FUNCTION,
 *              and all function pointers to other files, so that thier menu confiuration
 *              function can control tmenu.
 * 4/14/2012    Undid work done on 4/2, created SetXXXConfig functions that
 *              will change the state of the CONFIG_FUNCTION to the apporiate
 *              type of parameter to be configured and also take the supplied 
 *              function pointer, and set it to the appropriate menu function pointer
 * 12/16/12     Changed code to exit menu system if esc is received while in main
 *              menu screen.
****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../SYS_LIB/sysglobals.h"
#include "../../../LIBS/SYS_LIB/c_uart.h"
#include "../../../Microhip/Include/Graphics/Graphics.h"
#include "../../../LIBS/SYS_LIB/lcd_interface.h"
#include "../tMenus.h"


uChar	uBuffIndex = 0,
        aBufferIndex = 0;

char	ScreenBuff[MENUBUFF_SZ],
        *mBuff,
        rtnCount = 0,
        notZeroFlag = 0, //this flag is set to show user sent something other then zero 
        negSymbolExists = 0, // This flag limits input to one negative symbol
        decimalExists = 0,  //User gets one decimal place.
        menuSelection = 0,
        menuExitFlag = 0,
        alphaBuff[8];// alpha number buffer for atoi function
uInt    tempuInt = 0;
int     tempInt = 0;
long    tempLong = 0;
int     param1Int = 0;//Hold a parameter used when doing configuration
float	tempFloat = 0;	//Holds atof conversion 
//uChar rxIndex = 0; //For building string arrays of ints, floats and strings
char* (*MenuHomePage)(char*, char);
char* (*CurrentMenuPtr)(char*, char);
char* (*IntFunctionPtr)(char*, int);
char* (*uIntFunctionPtr)(char*, uInt);
char* (*LongFunctionPtr)(char*, double);
char* (*StrFunctionPtr)(char*, uInt);
char* (*FloatFunctionPtr)(char*, float);
char* (*MenuHistory[5])(char*, char); 
char    keyBuff[5],//Holds the history of keys pressed in menu history
        menuIndex = 0,
        mainMenuFlag = 0;//menu history index
//TODO set null pointers to SetXXXConfig to see how they are handled
//TODO make sure all SetXXXConfigs handle '-' and '.' properly
void ResetMenu(void)
{
    menuExitFlag = 0;
    MENU_ACTION = MENU_INACTIVE;
    menuIndex = 0;
}
char* RunMenu(char *cBuff)
{
    
    uBuffIndex = 0x00;
    //Limit the number of of key inputs to one
    char keyPress  = cBuff[0];
    
    //INT_INPUT stores chars from user until CR then converts to int
    //then takes int and uses it to set pre selected variable of
    //pre-selected object.
    if(MENU_ACTION == INPUT_INT)
    {
        if(IntFunctionPtr == NULL )//Be sure your pointing at something
        {
            sprintf(cBuff,"Null Pointer Error \r\n ");
            CurrentMenuPtr(&cBuff[23],-1);//Re Run last menu;
            MENU_ACTION = NAVIGATE_MENU; //Go back to last menu
            return cBuff;
        }
        if(cBuff[0] == 0x00) return IntFunctionPtr(cBuff, 0); // RunMenu
        while(cBuff[uBuffIndex] != 0x00)
        {
            // bound input to numbers and negative symbol. Exclude '.' and '/'
            if((cBuff[uBuffIndex] == 45)&&(negSymbolExists != 0)) //capture negative symbol
            {
                negSymbolExists = 1; // user only gets one negative symbol
                alphaBuff[aBufferIndex++] = cBuff[uBuffIndex++];
            }
            if((cBuff[uBuffIndex] > 47) && (cBuff[uBuffIndex] <= 57))
            {
                while(cBuff[uBuffIndex] > 47 && cBuff[uBuffIndex] <= 57)//Get everything in buffer
                {
                    notZeroFlag = 1;
                    alphaBuff[aBufferIndex + 1] = 0x00;
                    alphaBuff[aBufferIndex++]=cBuff[uBuffIndex++];
                }
                if(cBuff[uBuffIndex] == 0x00)return cBuff;
            }
            if(cBuff[uBuffIndex] == 0x0D)//Input complete, process string
            {
                aBufferIndex = 0; //Reset index
                //if(tempInt != NULL) (*tempInt)(int);
                cBuff[0] = 1; //Being non zero supresses menu
                tempInt = atoi(alphaBuff);//Check bounds
                if((tempInt == 0)&& notZeroFlag)
                {
                  cBuff[0] = -1;
                  sprintf(cBuff,"\x1B[1D\x1B[K Number to large or too small");
                  return IntFunctionPtr(cBuff, -1); //Display menu which shows bounds
                }
                IntFunctionPtr(cBuff, tempInt);//atoi(alphaBuff));
                MENU_ACTION = NAVIGATE_MENU; //Go back to last menu
                return CurrentMenuPtr(cBuff, -1);

            }
            if(cBuff[uBuffIndex] == 0x08)//if there is a back space erase last number
            {
                alphaBuff[--aBufferIndex] = 0x00; // erase last number
                sprintf(cBuff,"\x1B[1D\x1B[K");
                return cBuff;
            }
            uBuffIndex++;
        }
        uBuffIndex = 0;
        cBuff[0] = 0x00;
        return cBuff;
    }
    if(MENU_ACTION == INPUT_UINT)
    {
        if(uIntFunctionPtr == NULL )//Be sure your pointing at something
        {
            sprintf(cBuff,"Null Pointer Error \r\n ");
            CurrentMenuPtr(&cBuff[23],-1);//Re Run last menu;
            MENU_ACTION = NAVIGATE_MENU; //Go back to last menu
            return cBuff;
        }
        if(cBuff[0] == 0x00) return uIntFunctionPtr(cBuff, 0); // RunMenu
        while(cBuff[uBuffIndex] != 0x00)
        {
            // bound input to numbers.
            if((cBuff[uBuffIndex] > 47) && (cBuff[uBuffIndex] <= 57))// if input is a number
            {
                while(cBuff[uBuffIndex] > 47 && cBuff[uBuffIndex] <= 57)//Get everything in buffer
                {
                    notZeroFlag = 1;
                    alphaBuff[aBufferIndex + 1] = 0x00;
                    alphaBuff[aBufferIndex++]=cBuff[uBuffIndex++];
                }
                if(cBuff[uBuffIndex] == 0x00)return cBuff;
            }
            if(cBuff[uBuffIndex] == 0x0D)//Input complete, process string
            {
                aBufferIndex = 0; //Reset index
                //if(tempInt != NULL) (*tempInt)(int);
                cBuff[0] = 1; //Being non zero supresses menu
                tempInt = atol(alphaBuff);//Check bounds
                if((tempInt == 0) && notZeroFlag)
                {
                  cBuff[0] = -1;
                  sprintf(cBuff,"\x1B[1D\x1B[K Number to large or too small");
                  return uIntFunctionPtr(cBuff, -1); //Display menu which shows bounds
                }
                uIntFunctionPtr(cBuff,tempInt);//atoi(alphaBuff));
                MENU_ACTION = NAVIGATE_MENU; //Go back to last menu
                return CurrentMenuPtr(cBuff, -1);
            }
            if(cBuff[uBuffIndex] == 0x08)//if there is a back space erase last number
            {
                alphaBuff[--aBufferIndex] = 0x00; // erase last number
                sprintf(cBuff,"\x1B[1D\x1B[K");
                return cBuff;
            }
            uBuffIndex++;
        }
        uBuffIndex = 0;
        cBuff[0] = 0x00;
        return cBuff;
    }
//TODO : finish double input
    if(MENU_ACTION == INPUT_LONG)
    {
         if(LongFunctionPtr == NULL )//Be sure your pointing at something
        {
            sprintf(cBuff,"Null Pointer Error \r\n ");
            CurrentMenuPtr(&cBuff[23],-1);//Re Run last menu;
            MENU_ACTION = NAVIGATE_MENU; //Go back to last menu
            return cBuff;
        }
        if(cBuff[0] == 0x00) return LongFunctionPtr(cBuff, 0); // RunMenu
        while(cBuff[uBuffIndex] != 0x00)
        {
            // bound input to numbers and negative symbol. Exclude '/'
            if((cBuff[uBuffIndex] == 45)&&(negSymbolExists != 0)) //capture negative symbol
            {
                if(decimalExists == 0) // Cannot but neg symbor behind decimal
                {
                    negSymbolExists = 1; // user only gets one negative symbol
                    alphaBuff[aBufferIndex++] = cBuff[uBuffIndex++];
                }
            }
            if((cBuff[uBuffIndex] == 46)&&(decimalExists == 0))  //capture decimal
            {
                decimalExists = 1; // no more decimal places
                alphaBuff[aBufferIndex++] = cBuff[uBuffIndex++];
            }
            if((cBuff[uBuffIndex] > 47) && (cBuff[uBuffIndex] <= 57))// if input is a number
            {   //Just in case there's more than one number
                while(cBuff[uBuffIndex] > 47 && cBuff[uBuffIndex] <= 57)
                {
                    notZeroFlag = 1;
                    alphaBuff[aBufferIndex + 1] = 0x00;//Make sure alphaBuff is NULL terminated
                    alphaBuff[aBufferIndex++]=cBuff[uBuffIndex++]; // capture and number
                }
                if(cBuff[uBuffIndex] == 0x00)return cBuff; //Go back and wait for more
            }
            if(cBuff[uBuffIndex] == 0x0D)//Input complete, process string
            {
                aBufferIndex = 0; //Reset index
                //if(tempInt != NULL) (*tempInt)(int);
                cBuff[0] = 1; //Being non zero supresses menu
                tempLong = atol(alphaBuff);//Check bounds
                if((tempInt == 0)&& notZeroFlag)
                {
                  cBuff[0] = -1;
                  sprintf(cBuff,"\x1B[1D\x1B[K Number to large or too small");
                  return uIntFunctionPtr(cBuff, -1); //Display menu which shows bounds
                }
                LongFunctionPtr(cBuff,tempLong);//atoi(alphaBuff));
                MENU_ACTION = NAVIGATE_MENU; //Go back to last menu
                return CurrentMenuPtr(cBuff, -1);
            }
            if(cBuff[uBuffIndex] == 0x08)//if there is a back space erase last number
            {
                alphaBuff[--aBufferIndex] = 0x00; // erase last number
                sprintf(cBuff,"\x1B[1D\x1B[K");
                return cBuff;
            }
            uBuffIndex++;
        }
        uBuffIndex = 0;
        cBuff[0] = 0x00;
        return cBuff;
    }
    if(MENU_ACTION == INPUT_FLOAT)
    {
        if(FloatFunctionPtr == NULL )//Be sure your pointing at something
        {
            sprintf(cBuff,"Null Pointer Error \r\n ");
            CurrentMenuPtr(&cBuff[23],-1);//Re Run last menu;
            MENU_ACTION = NAVIGATE_MENU; //Go back to last menu
            return cBuff;
        }
        if(cBuff[0] == 0x00) return FloatFunctionPtr(cBuff, 0); // RunMenu
        while(cBuff[uBuffIndex] != 0x00)
        {
//TODO 's: Handle atoxx's returning 0 on error
            if((cBuff[uBuffIndex] >= 45) && (cBuff[uBuffIndex] <= 57))// if input is a  real number
            {
                if((cBuff[uBuffIndex] == 45)&&(negSymbolExists != 0)) //capture negative symbol
                {
                    if(decimalExists == 0) // Cannot but neg symbor behind decimal
                    {
                        negSymbolExists = 1; // user only gets one negative symbol
                        alphaBuff[aBufferIndex++] = cBuff[uBuffIndex++];
                    }
                }
                if((cBuff[uBuffIndex] == 46)&&(decimalExists == 0))  //capture decimal
                {
                    decimalExists = 1; // no more decimal places
                    alphaBuff[aBufferIndex++] = cBuff[uBuffIndex++];
                }

                //Just in case there's more than one number
                while(cBuff[uBuffIndex] > 47 && cBuff[uBuffIndex] <= 57)
                {
                    notZeroFlag = 1;
                    alphaBuff[aBufferIndex + 1] = 0x00;//Make sure alphaBuff is NULL terminated
                    alphaBuff[aBufferIndex++]=cBuff[uBuffIndex++]; // capture and number
                }
                if(cBuff[uBuffIndex] == 0x00)return cBuff; //Go back and wait for more
            }
            if(cBuff[uBuffIndex] == 0x0D)//Input complete, process string
            {
                aBufferIndex = 0; //Reset index
                //if(tempInt != NULL) (*tempInt)(int);
                cBuff[0] = 1; //Being non zero supresses menu
                tempFloat = atof(alphaBuff);//Check bounds
                if((tempInt == 0)&& notZeroFlag)
                {
                  cBuff[0] = -1;
                  sprintf(cBuff,"\x1B[1D\x1B[1K Number to large or too small");
                  return uIntFunctionPtr(cBuff, -1); //Display menu which shows bounds
                }
                FloatFunctionPtr(cBuff,tempFloat);//atoi(alphaBuff));
                MENU_ACTION = NAVIGATE_MENU; //Go back to last menu
                return CurrentMenuPtr(cBuff, -1);
            }
            if(cBuff[uBuffIndex] == 0x08)//if there is a back space erase last number
            {
                alphaBuff[--aBufferIndex] = 0x00; // erase last number
                sprintf(cBuff,"\x1B[1D\x1B[K");
                return cBuff;
            }
            uBuffIndex++;
        }
        uBuffIndex = 0;
        cBuff[0] = 0x00;
        return cBuff;
    }
    if(MENU_ACTION == INPUT_STRING)
    {
        if(cBuff[0] == 0x00) return StrFunctionPtr(cBuff, 0); // RunMenu
        while(cBuff[uBuffIndex] != 0x00)
        {
            while((cBuff[uBuffIndex] >= 20) && (cBuff[uBuffIndex] <= 126))//Get everything in buffer
            {
                alphaBuff[aBufferIndex + 1] = 0x00;
                alphaBuff[aBufferIndex++]=cBuff[uBuffIndex++];
            }
            if(cBuff[uBuffIndex] == 0x00)return cBuff;

            if(cBuff[uBuffIndex] == 0x0D)//Input complete, process string
            {
                aBufferIndex = 0; //Reset index
                cBuff[uBuffIndex] = 0x00;
                //if(tempInt != NULL) (*tempInt)(int);
                if(StrFunctionPtr != NULL )//Be sure your pointing at something
                {
                    cBuff[0] = 1; //Being non zero supresses menu
                    StrFunctionPtr(alphaBuff, 1);// Second argument is optional
                    MENU_ACTION = NAVIGATE_MENU; //Go back to last menu
                    return CurrentMenuPtr(cBuff, -1);
                }
                else
                {
                    sprintf(cBuff,"Null Pointer Error \r\n ");
                    CurrentMenuPtr(&cBuff[23],-1);//Re Run last menu;
                    MENU_ACTION = NAVIGATE_MENU; //Go back to last menu
                    return cBuff;
                }
            }
            if(cBuff[uBuffIndex] == 0x08)//if there is a back space erase last number
            {
                alphaBuff[--aBufferIndex] = 0x00; // erase last number
                sprintf(cBuff,"\x1B[1D\x1B[K");
                return cBuff;
            }
            uBuffIndex++;
        }
        uBuffIndex = 0;
        cBuff[0] = 0x00;
        return cBuff;
    }
        //if the esc or backspace key is pressed go up the menu tree

    if((keyPress == htESC)|(keyPress == htBS))//If user presses ecs move menu back one
    {      
        if(menuIndex > 0) //
        {
            menuIndex--;
            //If we are going to show the main menu, then get ready to exit next esc char
            if(menuIndex == 0)menuExitFlag = 1;
            if(MenuHistory[menuIndex] != 0x00)
            {
                MenuHistory[menuIndex](cBuff, -1);
                CurrentMenuPtr = MenuHistory[menuIndex];
            }
            MenuHistory[menuIndex] = 0x00; // Erase last menu history
            LCDClear();
            LCDPutString(cBuff);
            BuildTouchPad(NavigationPad,BRIGHTGREEN);
            return cBuff;
        }
        else if(menuIndex == 0)//Show Main Menu
        {
            if(menuExitFlag == 1)
            {
                MENU_ACTION = MENU_INACTIVE;
                //cBuff[0] = NULL;
                menuIndex = 0;
                menuExitFlag = 0;
                ExitMenus();
                cBuff[0] = 0x20;
                cBuff[2] = NULL;
                return cBuff;

            }
            //menuIndex--;
            menuExitFlag = 1;
            MENU_ACTION = NAVIGATE_MENU;//SHOW_MAIN_MENU;
            CurrentMenuPtr = MenuHomePage;
            MenuHistory[menuIndex] = CurrentMenuPtr;
            CurrentMenuPtr(cBuff, -1);
            LCDClear();
            LCDPutString(cBuff);
            BuildTouchPad(NavigationPad,BRIGHTGREEN);
            return cBuff;
        }  
    }
    if(MENU_ACTION == NAVIGATE_MENU) //Limits inputs to number 1 to 9;
    {
        keyPress = keyPress - 48; //Normalize keypress to numbers
        if(keyPress >= (char)0 && keyPress <= (char)9)
        {
            //First navigate using the menu displayed previously
            //When keypress >=0 the CurrentMenuPtr is set to the new menu page
            //by SetMenuPage()
            CurrentMenuPtr(cBuff, keyPress);//keyPress[menuIndex]);
            //if(CONFIG_FUNCTION != NAVIGATE_MENU)

            //cBuff[0] = 0x00;// The 0x00 will display cofig discriptor
            if(MenuHistory[menuIndex] != CurrentMenuPtr)
            {
                menuIndex++;
                menuExitFlag = 0;
                MenuHistory[menuIndex] = CurrentMenuPtr;
                //return CurrentMenuPtr(cBuff, -1);  // When < 0 function's menu screen is run;
                CurrentMenuPtr(cBuff, -1);  // When second param is < 0 function's menu screen is run;
                mainMenuFlag = 0;
                LCDClear();
                LCDPutString(cBuff);
                BuildTouchPad(NavigationPad,BRIGHTGREEN);
                return cBuff;
            }
        }
        else
        {
            cBuff[0] = 0x00;
            return cBuff;
        }
    }
    
    if(MENU_ACTION == SHOW_MAIN_MENU) //Limits inputs to number 1 to 9;
    {
        //menuIndex = 0;
        MENU_ACTION  = NAVIGATE_MENU;
        //CurrentMenuPtr = MenuHomePage;
        //MenuHistory[menuIndex] = CurrentMenuPtr;
        //MenuHistory[menuIndex](cBuff, -1);
        //return cBuff;
    }
    /*
    if(cBuff[0] != NULL)
    {

    }*/
    return cBuff;
    //uBuffIndex++;

}

#ifdef _TMENU_CONNECTION_UART


#endif
void InitMenuStartPage(char*(*MenuFuncPtr)(char*, char))
{
    MenuHomePage = MenuFuncPtr;
    MENU_ACTION = NAVIGATE_MENU;
}

char* GetAccessPoints(char* cBuff, char Value)
{
	sprintf(cBuff, "!** Select Access Point **!\r\n");
	strcat(cBuff,"\t 1 - Stillbright\r\n");
	strcat(cBuff,"\t 2 - Riotech\r\n");
	return cBuff;
}
void SetMenuPage(char*(*MenuFuncPtr)(char*, char))
{
    CurrentMenuPtr = MenuFuncPtr;
    MENU_ACTION = NAVIGATE_MENU;
}
void SetIntConfig(char*(*IntFuncPtr)(char*, int))
{
    notZeroFlag = 0; //so far users input is zero 
    negSymbolExists = 0; //user has not entered neg symbol
    decimalExists = 0;
    IntFunctionPtr = IntFuncPtr;
    MENU_ACTION = INPUT_INT;
}
void SetUintConfig(char*(*uIntFuncPtr)(char*, uInt))
{
    notZeroFlag = 0; //so far users input is zero 
    negSymbolExists = 0; //user has not entered neg symbol
    decimalExists = 0;
    uIntFunctionPtr = uIntFuncPtr;
    MENU_ACTION = INPUT_UINT;
}
void SetLongConfig(char*(*LongFuncPtr)(char*, double))
{
    notZeroFlag = 0; //so far users input is zero 
    negSymbolExists = 0; //user has not entered neg symbol
    decimalExists = 0;
    LongFunctionPtr = LongFuncPtr;
    MENU_ACTION = INPUT_LONG;
}
void SetFloatConfig(char*(*FloatFuncPtr)(char*, float))
{
    notZeroFlag = 0; //so far users input is zero 
    negSymbolExists = 0; //user has not entered neg symbol
    decimalExists = 0;
    FloatFunctionPtr = FloatFuncPtr;
    MENU_ACTION = INPUT_FLOAT;
}
void SetStrConfig(char*(*StrFuncPtr)(char*, uInt))
{
    notZeroFlag = 0; //so far users input is zero 
    StrFunctionPtr = StrFuncPtr;
    MENU_ACTION = INPUT_STRING;
}
