/****************************************************************************
   CREATED BY: 	Stillbright Managment LLC
*					Copyright 2012
*                                                                           
*   FILE:           HyperTermInterface.h                                               
*                                                                           
*   DESCRIPTION:    Code for displaying to and interacting with users      
*					through a hypertermal or TTY type interface.                                                                           
*                                                        
*   CREATED:		Feb 24 2012  
* 	REVISION:   	v0.1 - Define operation and functions 
****************************************************************************/

#ifndef __HYPERTEMINTERFACE_H
#define __HYPERTERINTERFACE_H



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
*	Menu selections will be the only response not needing a RTN to start process.
*/

#define htESC 
#define htBS 
#define htCLS	\x1B[2J
#define htNULLS 0x00 //ending sequence to htcontrol
#define htControl(x) htESC, x, htNULLS
//extern TERM_DATA TermData;
int RunInterface(unsigned char *trmBuff);
#endif