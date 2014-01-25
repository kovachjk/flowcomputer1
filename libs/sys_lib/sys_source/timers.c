/****************************************************************************
*           INTELLIGENT SENSOR DESIGN USING THE MICROCHIP dsPIC             *
*                TURBINE FLOW SENSOR PROCESSING FRAMEWORK                   *
*                                                                           *
*   FILE:           Timer.c                                                 *
*                                                                           *
*   DESCRIPTION:    This file contains the application-specific timer       *
*                   interface routines that must be customized by           *
*                   the user for the particular hardware platform.          *
*                                                                           *
*   REVISION:  0    v1.0                DATE:  1 October 2006               *
*       Original release.                                                   *
****************************************************************************/

                                /*******************
                                **  Header Files  **
                                *******************/


#include "compairs.h"       // Timer interface definitions
#include "globals.h"
                            /***********************
                            **  Global Variables  **
                            ***********************/
//#define LED_STATE_OFF 0   // Image of Hardware LED state


/*10/23/12  Remmed this out because these variables were moved to sys_clock.c 
don't know if these might be needed by the other functions if so then this file needs 
to look at sys_clock.h
volatile uChar HWErrLEDImage = LED_STATE_OFF; 
sClock Time;
    
uInt16	t1UpdateRate,			// Number of mSec between T1 interrupts
		AccumulatedTime = 0,  	// Blade count accumulation time
    	BlinkCount       = 0, 	// LED blink period counter
    	Timer100mSec     = 0, 	// 100 msec system timer counter
		T5CharMultiplier = 0;	//Multiplier used in setting char delay
*/
#ifdef __PIC32MX__  
//10/23/12 - This funtion is available only if using PIC32 otherwise T1 is being used by
// InitSysClock in sys_clock.h
void InitT1(uInt mSecDelay)
{

	time2ChckPrgm = 1; // Sets the default time to check for lockups to 1 mSec	
	_T1IP = 2; //SET TIMER 1 INTERRUPT PRIORITY
	T1CONbits.TON=0;//	TURN OFF T1
	TMR1 = 0; // CLEAR TIMER	
	T1CONbits.TCKPS = 3; //SET PRESCALE TO 256  
	PR1 =  156; //SET PERIOD TIMEOUT TO 1mSEC	
	T1CONbits.TON=1;//	TURN ON T1
	_T1IF = 0; // CLEAR TMR1 INTERRUPT FLAG
	_T1IE = 1; // ENABLE TMR1 INTERRUPT	
	Time.Hours = 0;
	Time.Minutes = 0;
	Time.Seconds = 0;
	Time.mSeconds = 0;


}  
#endif	
	//******************* END TIMER 1 SETUP ***************************

//1/16/2011: T1 interrupt was check on a PIC33 to make sure time base was accurate.
#ifdef __PIC32MX__
//10/23/12 - This funtion is available only if using PIC32 otherwise T1 is being used by
// InitSysClock in sys_clock.h
void __attribute__((interrupt, auto_psv)) _T1Interrupt(void)
{

	TMR1 = 0;
	Time.mSeconds ++;
	MachineState |= sys_CHCKSYSTEM; // Do Housekeeping
	if(Time.mSeconds > 999)
	{	
		
		Time.mSeconds = 0;
		Time.Seconds++;
		
		if(Time.Seconds > 59)
		{
			Time.Seconds = 0;
			Time.Minutes++;
			if(Time.Hours >= 23) Time.Hours = 0;
		}		
	}
	_T1IF = 0; // CLEAR TMR1 INTERRUPT FLAG		


}; 
#endif
/****************************************************************************
*   FUNCTION:       Timer3Init(uInt16 ui16Frequency)                        *
*                                                                           *
*   DESCRIPTION:    initializes the dsPIC's Timer 3 to        *
*                   generate an interrupt of the specified frequency        *
*                   that will control the ADC sampling rate.                    *
*                                                                           *
*   PARAMETERS:     ui16Frequency - desired interrupt frequency in Hz       *
*                                                                           *
*   RETURNS:        The function returns no value.                          *
*                                                                           *
*   REVISION:  0    v1.0                DATE:  1 October 2006               *
*       Original release.                                                   *
****************************************************************************/

void T3Init(uInt16 Frequency)
{
    //  Local Variables
    
    uInt16 	Period;             // Timer period 
        
    //  First, turn off Timer 3 and its associated
    //  interrupt so we can complete the initialization
    //  without being interrupted
    
    T3CONbits.TON = 0;
    
    //  Compute the timer period in counts based
    //  on the instruction clock frequency
    
    Period = (uInt16)((gblFcy / Frequency) + 1); // calculate timer period
    ConfigIntTimer3(T3_INT_PRIOR_4 & T3_INT_ON); // Set the interrupt priority
    T3CON = 0;	//Stop and clear timer 5
	TMR3 = 0;
	T3CONbits.TCKPS = 0;	// Prescale 1
	PR5 = Period;
	_T3IE = 1;
	_T3IF = 0;
	T3CONbits.TON = 1;   	//   and enable the interrupt
    
    return;
}

void T3Stop()
{
	T3CONbits.TON = 0;
	TMR3 = 0;
	_T3IE = 0;
	_T3IF = 0; 
	return;
}
void T3Start()
{
	TMR3 = 0;
	_T3IE = 1;
	_T3IF = 0; 
	T3CONbits.TON = 1;	
	return;	
}	
    
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

 


 
/****************************************************************************
*   FUNCTION:       _T3Interrupt(void)                                      *
*                                                                           *
*   DESCIPTION:     This function is the interrupt service routine for      *
*                   the Timer 3 interrupt, which is used to schedule        *
*                   ADC sampling.                                           *
*                                                                           *
*   PARAMETERS:     None                                                    *
*                                                                           *
*   RETURNS:        The function returns no value since it is an ISR.       *
*                                                                           *
*   REVISION:  0    v1.0                DATE:  1 October 2006               *
*       Original release.                                                   *
****************************************************************************/

void __attribute__((interrupt, auto_psv)) _T3Interrupt(void)
{

    asm("  btg PORTD, #3");
    asm("nop");
    asm("nop");

//	ADCON1bits.SAMP = 0; // STOP SAMPLING START CONVERTING
	
	asm("nop");
    asm("nop");	
    
       asm("  bclr PORTD, #0");        // Lower alarm is active, so turn LED1 on
        

       asm("  bset PORTD, #0");        // Lower alarm is inactive, so turn LED1 off

	
	AD1CON1bits.SAMP = 0;
    _T3IF = 0;
    
}

