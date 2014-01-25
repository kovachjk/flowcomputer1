#include "compairs.h" //holds function descriptions
#include "globals.h"
//*****************************************************************
// 		Output Compair 
//****************************************************************
int volatile IC1Hertz;

void OC5Init(double Hertz)
{
	float temp;
	//Configure Timer 2 for Compair
	T2CON = 0; 				// Stop timer 2
	T2CONbits.TCKPS = 0; 	// prescales Fcy by 8
	temp = gblFcy/1; 		// 1 when TCKPS is 0, 8 when TCKPS is 1
	OC5CONbits.OCM = 5;		// OC1pin starts low with  continous pulse
	OC5CONbits.OCTSEL = 0;	// Timer select is timer 2
	PR2 = temp/Hertz;
	OC5CONbits.OCSIDL = 1; 	// Timer stop when CPU is idle
	OC5R = PR2/2;			// Set OC1 pin High when OC5RS == PR2/2
	OC5RS = 0;				// Set OC1 pin low when OC5RS == 0
	T2CONbits.TON = 1;		// Turn timer 2 on
	
}
void OC5Start(void)
{
	T2CON = 0XF000;
}
void OC5Stop(void)
{
	T2CON = 0;
}		
//*****************************************************************
// 		Input Compair will work down to 450 RPM with 
//		default settings
//		IntFreq can be 0,1,2 or 3 for an interrupt every 
//		pulse or every second, third or forth pulse
//****************************************************************
void IC1Init(void)
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
void IC1Stop(void)
{
	IC1CONbits.ICM = 0;
	IC1Hertz = 0;
}
void IC1Start(void)
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

	