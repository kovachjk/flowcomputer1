//#include "compairs.h" //holds function descriptions
#include "sysglobals.h"
#include "tacho.h"

int volatile IC1Hertz;
	
//*****************************************************************
// 		Input Compair will work down to 450 RPM with 
//		default settings
//		IntFreq can be 0,1,2 or 3 for an interrupt every 
//		pulse or every second, third or forth pulse
//****************************************************************
void InitTacho(void)
{
	T3CON = 0;// Turn off timer 3
	T3CONbits.TCKPS = 3;// timer prescale 1:256 give min 1.46 htz
	PR3 = 65400;
	IC1CON = 0;// Clear IC configure register
	IC1CONbits.ICSIDL = 0;// do not opperate in idle mode
	
	
	_TRISD8 = 1;// Change pin RD8 to input
	IC1CONbits.ICTMR = 0;  //Use timer 3
	//if(IntFreq > 3) IntFreq = 1;
	IC1CONbits.ICI = 1; //IntFreq; // generate interrupt every  2 IC events
	IC1CONbits.ICM = 0;// generate IC event every rising pulse;
	IC1Hertz = 0;
	_IC1IF = 0;
	_IC1IE=1;
	
}
void TachoStop(void)
{
	IC1CONbits.ICM = 0;
	IC1Hertz = 0;
}
void TachoStart(void)
{
	IC1CONbits.ICM = 3;
	IC1Hertz = 0;
}		

void __attribute__((interrupt, auto_psv)) _IC1Interrupt(void)
{
	int x = 0;
	IC1Hertz = 0;
	// consider putting in check for ICNE overflow
	while(IC1CONbits.ICBNE)
	{
		IC1Hertz += IC1BUF;
		x++;
	}
	if(x) IC1Hertz = IC1Hertz/x;

	_IC1IF = 0;

}	

	