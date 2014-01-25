/****************************************************************************
*   Stillbright Managment LLC
*	Copyright 2010
*                                                                           
*   FILE:           Timer.c                                                 
*                                                                           
*   DESCRIPTION:    This file contains the application-specific timer       
*                   interface routines that must be customized by           
*                   the user for the particular hardware platform.          
*                                                                           
*   REVISION:   v1.000                                                      
*   DATE: 		Sept 3 2010                                                 
****************************************************************************/

                                /*******************
                                **  Header Files  **
                                *******************/


//#include "compairs.h"       // Timer interface definitions
#include "states.h"
                            /***********************
                            **  Global Variables  **
                            ***********************/
#define LED_STATE_OFF 0   // Image of Hardware LED state

volatile uChar HWErrLEDImage = LED_STATE_OFF; 
sClock Time;
    
uInt16	t1UpdateRate,			// Number of mSec between T1 interrupts
		AccumulatedTime = 0,  	// Blade count accumulation time
    	BlinkCount       = 0, 	// LED blink period counter
    	Timer100mSec     = 0, 	// 100 msec system timer counter
		T5CharMultiplier = 0;	//Multiplier used in setting char delay

/******************TIMER 1 SETUP ********************
*	This configures timer 1 as a 1 mSec resolution timer
*	which interrupts on time out
*	This timer can also be configured to be a RTC
*
*********************************************************/	
void InitT1(uInt16 mSecDelay)
{
	t1UpdateRate = mSecDelay;
	
	_T1IP = 2; //SET TIMER 1 INTERRUPT PRIORITY
	T1CONbits.TON=0;//	TURN ON T1
	TMR1 = 0; // CLEAR TIMER	
	T1CON = 0X0020; //SET PRESCALE TO 256  
	PR1 = mSecDelay * 156*2; //SET PERIOD REGISTER FOR TIMER 1	
	T1CONbits.TON=1;//	TURN ON T1
	_T1IF = 0; // CLEAR TMR1 INTERRUPT FLAG
	_T1IE = 1; // ENABLE TMR1 INTERRUPT	
	Time.Hours = 0;
	Time.Minutes = 0;
	Time.Seconds = 0;
	Time.mSeconds = 0;
	
	//******************* END TIMER 1 SETUP ***************************
}  
void __attribute__((interrupt, auto_psv)) _T1Interrupt(void)
{
	TMR1 = 0;
	/* Interrupt Service Routine code goes here         */
	__builtin_btg( (unsigned int *)&LATA, 2 );
	Time.mSeconds+=t1UpdateRate;
	MachineState |= s_CHCKPRGRM; // Do Housekeeping
	if(Time.mSeconds>=1000)
	{
		Time.mSeconds = 0;
		Time.Seconds++;
		
		if(Time.Seconds >= 59)
		{

			Time.Seconds = 0;
			Time.Minutes++;
			if(Time.Hours >= 23) Time.Hours = 0;
		}
	}
	_T1IF = 0; // CLEAR TMR1 INTERRUPT FLAG		
				
}; 


    
/****************************************************************************
*   FUNCTION:       Timer5Init(void)                                        *
*                                                                           *
*   DESCRIPTION:    This function initializes the Timer 5 module as a       *
*					Watchdog timer form incomming messages. This was        *
*					implemented early in the project and no longer used     *
*                                                                           *
*   PARAMETERS:     None                                                    *
*                                                                           *
*   RETURNS:        The function returns no value.                          *
*                                                                           *
*   REVISION:  0    v1.0                DATE:  1 October 2006               *
*       Original release.                                                   *
***************************************************************************


void T5Init(void)
{
	T5CON = 0;//Stop and clear timer 5
	TMR5 = 0;
	_T5IP = 2;
	T5CONbits.TCKPS = 2;// divide Fcy by 64
	T5CONbits.TON = 0;
	T5CharMultiplier =  (gblFcy/64)/gblBaud * 11 + 1; // 11 = num bits/char
}
void T5CharDelay(char nChars)//max 255 char delay
{

	T5CONbits.TON = 1;
	PR5 = T5CharMultiplier * nChars; // 117 is based on 		
	_T5IE = 1;
	_T5IF = 0;        
    return; 
}
void T5Reset()
{

	TMR5 = 0x0000;
	//_T5IE = 1;
	//_T5IF = 0; 
	return;
}
void T5Stop(void)
{
	T5CONbits.TON = 0;
	_T5IE = 0;
	return;
}
*/
//Timer5 will be used for signaling the timeout and processing of a message

 

