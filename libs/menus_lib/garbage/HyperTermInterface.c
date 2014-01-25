
/****************************************************************************
*   CREATED BY: 	Stillbright Managment LLC
*					Copyright 2012
*                                                                           
*   FILE:           HyperTermInterface.c                                               
*                                                                           
*   DESCRIPTION:    Code for displaying to and interacting with users      
*					through a hypertermal or TTY type interface.                                                                           
*                                                        
*   CREATED:		Feb 24 2012  
* 	REVISION:   	v0.1 - Define operation and functions 
******************************************************************************/


#include "../HyperTermInterface.h"
#include <stdio.h>
#include <stdlib.h>
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
BYTE mBuff[16];
uchar x, mIndex = 0, mMainLevel1 = 0, mSubLevel1 = 0, mSubLevel2 = 0;
typedef struct 
{
	BYTE scrnPrep[32];
	BYTE menuResponse[128];
}TERM_DATA;



int RunInterface(unsigned char *trmBuff)
{
	static enum
	{
		MENU_INPUT = 0,
		INT_INPUT,
		Y_N_INPUT,
		STRING_INPUT,
	}INPUT_TYPE = MENU_INPUT;
		
	mIndex= 0;
	if(INPUT_TYPE == MENU_INPUT)
	{
		if(trmBuff[0] >= 47 && trmBuff[0] <= 57)
		{
			//x = trmBuff[0];
			sprintf(trmBuff,"Item Selected = %i\r\nHello World, Now is the time for all good men to come the aid of their country!", atoi(trmBuff));	
			return 0;
		}
		trmBuff[0] = 0x00;
		return 0;
	}
	if(INPUT_TYPE == INT_INPUT)	
	{
		while(trmBuff[mIndex] != 0x00)
		{
		
		}
	}
	
	return;
	
}