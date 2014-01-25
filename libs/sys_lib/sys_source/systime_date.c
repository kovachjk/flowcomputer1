/****************************************************************************
*          	               *
*                                                                           *
*   FILE:           systime_date.c                                                 *
*                                                                           *
*   DESCRIPTION:    T1 timer with interrupt configured for 2 mSec         *
*                                                                           *
*   REVISION:  0    v1.0                DATE:  1 October 2009              *
*       Original release.                                                   *
****************************************************************************/

                                /*******************
                                **  Header Files  **
                                *******************/


#include <plib.h>
#include "../systime_date.h"       // Timer interface definitions
#include "../sysglobals.h"
//#include "../digital.h"

//#include "protocols.h"

                            /***********************
                            **  Global Variables  **
                            ***********************/
//#define LED_STATE_OFF 0   // Image of Hardware LED state

//volatile uChar HWErrLEDImage = LED_STATE_OFF; 
SysClock Time;
 //TODO: Remove onTime  and the need for it.
//sInt onTime = 1;
uInt	time2ChckPrgm,			// Number of mSec between T1 interrupts
	AccumulatedTime = 0,  	// Blade count accumulation time
    	BlinkCount       = 0, 	// LED blink period counter
    	Timer100mSec     = 0; 	// 100 msec system timer counter
/*********************************************************************************************
 *                                          MENU ROUTINES
 *********************************************************************************************/
char* ConfigRTC(char* cBuff, char keyPress)
{
    if(keyPress < 0)
    {
        sprintf(cBuff,"\x1B[2J\x1B[H !* Set Date/Time *!\r\n \
\t1 - Set Date\r\n \
\t2 - Set Time\r\n");
        return cBuff;
    }
    if(keyPress == 1)
    {
        SetMenuPage(WiFiConfigMenu);
    }
    if(keyPress ==2)
    {
        SetMenuPage(WiFiConfigDHCP);
    }
    cBuff[0] = 0x00;
    return cBuff;
}
char* ConfigTimeDate(char* cBuff, char keyPress)
{
    if(keyPress < 0)
    {
        sprintf(cBuff,"\x1B[2J\x1B[H !* Set Date/Time *!\r\n \
\t1 - Set Date\r\n \
\t2 - Set Time\r\n");
        return cBuff;
    }
    if(keyPress == 1)
    {
        SetMenuPage(WiFiConfigMenu);
    }
    if(keyPress ==2)
    {
        SetMenuPage(WiFiConfigDHCP);
    }
    cBuff[0] = 0x00;
    return cBuff;
}
/****************** CLOCK TIMER 1 SETUP ********************
*	This configures timer 1 as a 1 mSec resolution timer
*	which interrupts on time out
*	This timer can also be configured to be a RTC
*   Checked for accuracy on 1/16/2011
*********************************************************/

void InitSysTime(void)
{
#ifndef __PIC32MX__ 
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
#endif
#ifdef __PIC32MX__
    
    OpenCoreTimer(CORE_TICK_RATE);
    // set up the core timer interrupt with a prioirty of 2 and zero sub-priority
    mConfigIntCoreTimer((CT_INT_ON | CT_INT_PRIOR_2 | CT_INT_SUB_PRIOR_0));
    // configure pins for LEDs
    PORTSetPinsDigitalOut(IOPORT_A, BIT_0 | BIT_1); //JK Added  for LEDs10/11/12
    PORTSetBits(IOPORT_A, BIT_1);
    // enable device multi-vector interrupts
    INTEnableSystemMultiVectoredInt();
    Time.Hours = 0;
    Time.Minutes = 0;
    Time.Seconds = 0;
    Time.mSeconds = 0;
 #endif   
	
	//******************* END TIMER 1 SETUP ***************************
}  

#ifndef __PIC32MX__ 
//1/16/2011: T1 interrupt was check on a PIC33 to make sure time base was accurate.
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


#ifdef __PIC32MX__ 
void __ISR(_CORE_TIMER_VECTOR, ipl2) CoreTimerHandler(void)
{
    // clear the interrupt flag
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
        }
        if(Time.Minutes > 59)
        {
            Time.Minutes = 0;
            Time.Hours++;
            if(Time.Hours >= 23) Time.Hours = 0;        
        }
    }
    UpdateCoreTimer(CORE_TICK_RATE);
    mCTClearIntFlag();
}
#endif

