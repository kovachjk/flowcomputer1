
/****************************************************************************
   CREATED BY: 	Stillbright Managment LLC
*					Copyright 2012
*
*   FILE:           tMenus.h
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
 *      contains a switch that will do one of three things.
 *          1. Return a string discribing what options are available
 *          2. Have an option that will call another menu function
 *          3. Have an option that will set up a call to a configuration function o
	Menu type functions will only recognize a single keypress of zero to 9. Configuration
 *      functions are called from a menu function by using a SetXXXConfig function.  A
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
****************************************************************************/

#ifndef __TMENUS_H
#define __TMENUS_H
#include "../SYS_LIB/sysglobals.h"




/*******      HyperTerminal and Telnet Menu System
*  	HTI application will send prompts to the user.  These prompts will define 
* 	the type of response expected, byte, int, string, float, etc.  
*	
*	Menu selections and (Y,N,y,n) will be the only response not needing a RTN to run process.
*/

#define htESC       0x1B
#define htBS        0x08
#define htCLS       \x1B[2J //Telnet clear screen command
#define htNULLS     0x00 //ending sequence to htcontrol


extern char ScreenBuff[MENUBUFF_SZ];
// Menu Action controls what input screen is presented to the user.
static enum
{
    MENU_INACTIVE,
    SHOW_MAIN_MENU,
    NAVIGATE_MENU,
    INPUT_INT,
    INPUT_UINT,
    INPUT_FLOAT,
    INPUT_LONG,
    INPUT_Y_N,
    INPUT_STRING
}MENU_ACTION = MENU_INACTIVE;

//#define htControl(x) htESC, x, htNULLS
//extern TERM_DATA TermData;
/*********************************************************************
 * Function:       void ResetMenu(void);
 * Input:           none
 * Output:          None
 * Overview:        The only thing Reset Menu does is reset the exit menu
 *                  flag that might be left hanging if the menu times out
 *                  and the main system loop switches to run app mode
 ********************************************************************/
void ResetMenu(void);
/*********************************************************************
 * Function:        char* RunMenu(char *)
 *
 *
 * Input:           Char array, input is either single number from keyboard
 *
 * Output:          returns the same char array that was input
 *
 * Side Effects:    Modification of the chars array
 *
 * Overview:        RunMenu:Is a series of switchs that run code based on user input
 *						
                    Filters BYTE buffer for screen control keys
                    Filters and saves ascii chars which represent numbers
                    Saves ascii chars which will represent a string
                    Types of inputs:
                    Single screen control key(arrow keys for next and previous
                    backspace for strings and numbers)
                    Single numeric key( 0-9 ) - Used for menu movement
                    Int and float - CR will enter sequence
                    String - CR will enter sequence

                    Once a connection is established,two quick esc will start
 *                  the process of displaying
                    the first screen, which normally will be a menu screen.
 *
 * Note:            RunMen uses Response2Input to build response to 
 ********************************************************************/
extern char* RunMenu(char *buff);
/*********************************************************************
 * Function:        void Response2Input(void)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    Modification of the BYTE array
 *
 * Overview:        Used as a helper to RunMenu.  Organizes all the
 *					prompt screens
 *
 * Note:            None
 ********************************************************************/
//void DummySensorInput(int SensorNum, int MaxValue);// Would be in sensor file
//void Respond2Input(void);
//char* WelcomeMenu(char* cBuff, char keyPress);
//char* GetAccessPoints(char* cBuff, char Value);

//char* MainMenu(char* cBuff, char keyPress);
void InitMenuStartPage(char*(*MenuFuncPtr)(char*, char));
void SetMenuPage(char*(*MenuFuncPtr)(char*, char));
void SetIntConfig(char*(*intFuncPtr)(char*,int));
void SetStrConfig(char*(*StrFuncPtr)(char*, uInt));
void SetUintConfig(char*(*uIntFuncPtr)(char*, uInt));
void SetFloatConfig(char*(*FloatFuncPtr)(char*, float));
void SetLongConfig(char*(*LongFuncPtr)(char*, double));
#endif
