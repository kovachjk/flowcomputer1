/****************************************************************************
   CREATED BY: 	Stillbright Managment LLC
*					Copyright 2012
*                                                                           
*   FILE:           tMenus.h                                               
*                                                                           
*   DESCRIPTION:    Code for displaying to and interacting with users      
*					through a hypertermal or TTY type interface.                                                                           
*                                                        
*   CREATED:		Feb 24 2012  
* 	REVISION:   	v0.1 - Define operation and functions 
*  	3/8/2012		v0.xx- file abandoned for a function pointer system
****************************************************************************/

#ifndef __MENUMANAGER_H
#define __MENUMANAGER_H
#include "GenericTypeDefs.h"


/****************************************************************************
*   FUNCTION:       _U1TXInterrupt(void)                                    *
*                                                                           *
*   DESCRIPTION:    This function is the handler for the UART 1 Transmit    *
*                   interrupt, which is generated whenever the UART's       *
*                   Transmit Buffer is empty.  It checks to see whether     *
*                   more data is queued to send, and if so, loads the       *
*                   next available byte into the Transmit Buffer.  If       *
*                   no more data is left to send the routine turns off      *
*                   the Transmit interrupt.                                 *
*                                                                           *
*   PARAMETERS:     None                                                    *
*                                                                           *
*   RETURNS:        The function returns no value since it is an ISR.       *
*                                                                           *
*   REVISION:  0    v1.0                DATE:  1 October 2006               *
*       Original release.                                                   *
****************************************************************************/

/*
*  	HTI application will send prompts to the user.  These prompts will define 
* 	the type of response expected, byte, int, string, float, etc.  
*	
*	Menu selections and (Y,N,y,n) will be the only response not needing a RTN to run process.
*/

#define htESC 
#define htBS 
#define htCLS	\x1B[2J
#define htNULLS 0x00 //ending sequence to htcontrol
//#define htControl(x) htESC, x, htNULLS
//extern TERM_DATA TermData;
/*********************************************************************
 * Function:        void RunMenuManager(BYTE *)
 *
 * PreCondition:    There is a socket connection
 *
 * Input:           Pointer to an array of bytes
 *
 * Output:          None
 *
 * Side Effects:    Modification of the BYTE array
 *
 * Overview:        RunMenu:Is a series of switchs that run code based on user input
 *						
 *						Filters BYTE buffer for screen control keys
 *						Filters and saves ascii chars which represent numbers 
 *						Saves ascii chars which will represent a string
 *					Types of inputs:
 *						Single screen control key(arrow keys for next and previous
 *						backspace for strings and numbers)
 *						Single numeric key( 0-9 ) - Used for menu movement
 *						Int and float - CR will enter sequence
 *						String - CR will enter sequence
 *
 *					Once a connection
 *					is established,any key hit will start the process of displaying 
 *					the first screen, which normally will be a menu screen.
 *
 * Note:            RunMen uses Response2Input to build response to 
 ********************************************************************/
void RunMenuMenu(BYTE *buff);
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
extern void RunMenu(char *buff);
void Respond2Input(void);
void GetAccessPoints(void);
#endif