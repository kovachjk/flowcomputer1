
#include "ADC.h"
#include "globals.h"
#include "serial.h"
#include <stdio.h>
#include <string.h>
volatile int samplesAcquired = 0;
volatile int samplesRequested = 0;
uInt16 adTest;
double adTemp;
//OSamples can be 0, 2 or 4.  This gives 12, 13 or 14 bits of resoluton


void ADCInit()
{
	
	TRISBbits.TRISB6 = 1;	// Configure Pin 21 (AN6) as an input - POT1
	TRISBbits.TRISB5 = 1;	// Configure Pin 16 (AN4) as an input - POT2
	AD1PCFGL = 0XFFFF;
	AD1PCFGH = 0XFFFF;
 	AD1PCFGLbits.PCFG4 = 0;         // ensure AN4/RB4 is analog (Temp Sensor)
 	AD1PCFGLbits.PCFG5 = 0;
 	
	AD1CON1bits.ADON = 0;	//Turn ADC  off	

	//FORM = bb;
	//11 = Signed fractional (DOUT = sddd dddd dddd 0000)
	//10 = Fractional (DOUT = dddd dddd dddd 0000)
	//01 = Signed integer (DOUT = ssss sddd dddd dddd)
	//00 = Integer (DOUT = 0000 dddd dddd dddd)	
	AD1CON1bits.FORM = 00;
	//AD12B
	//1 = 12-bit, 1-channel ADC operation
	//0 = 10-bit, 4-channel ADC operation
	//SSRC<2:0>: Conversion Trigger Source Select bits
	AD1CON1bits.AD12B = 1;
	//111 = Internal counter ends sampling and starts conversion (auto convert)
	//110 = Reserved
	//101 = Reserved
	//100 = Reserved
	//011 = Motor Control PWM interval ends sampling and starts conversion
	//010 = General purpose Timer3 compare ends sampling and starts conversion
	//001 = Active transition on INT0 pin ends sampling and starts conversion
	//000 = Manual - Clearing SAMP bit ends sampling and starts conversion
	AD1CON1bits.SSRC = 0;
	//ASAM: A/D Sample Auto-Start bit
	//1 = Sampling begins immediately after last conversion completes. SAMP bit is auto set.
	//0 = Sampling begins when SAMP bit set
	AD1CON1bits.ASAM = 0;
	//SAMP: A/D Sample Enable bit
	//1 = At least one A/D sample/hold amplifier is sampling
	//0 = A/D sample/hold amplifiers are holding
	//When ASAM = 0, writing `1' to this bit will start sampling.
	//When SSRC = 000, writing `0' to this bit will end sampling and start conversion.
	//ADCON1bits.SAMP = 0;

	////////////////////////////////////////////////////////////////////////////
	//						ADCON2
	/////////////////////////////////////////////////////////////////////////
	AD1CON2bits.VCFG = 0; 	// AVdd and AVss are the reference
	AD1CON2bits.CSCNA = 0; 	// Do not scan inputs
	AD1CON2bits.SMPI = 0;	// Generate interupt every 1 conversions
	AD1CON2bits.BUFM = 0;;	// Buffer configured as one 16 bit word;
	AD1CON2bits.ALTS = 0; 	// Always use MUXA for input
	T3Stop();  				// Make sure T3 is off
	////////////////////////////////////////////////////////////////////////////
	//						ADCON3
	/////////////////////////////////////////////////////////////////////////
	AD1CON3bits.ADCS = 25;	// Set Conversion speed to over 333 nSec	
	AD1CON1bits.ADON = 1;	//Turn on ADC
	

	/* enable DMA mode (ADC module sends all results 
	   to ADBUF0 and interrupts on each result */
	//	ADCON1bits.ADDMAEN = 1;
	

	
	IFS0bits.AD1IF = 0;    // reset ADC interrupt flag */   
	    
	/* enable ADC interrupts, disable this interrupt if the DMA is enabled */	  
	IEC0bits.AD1IE = 1;       

	AD1CON1bits.ADON = 1;  
}
	
void ReadAIN5(int SampleRate, int NumSamples) // AN5 is Pot
{	
	if(NumSamples < 1) NumSamples = 1;
	if(SampleRate > 500) SampleRate = 500;
	//adTest = 0;
	//adTemp = 0;
	AD1CHS0 = 0x0005; // Select AN5 as CH0 input .
	AD1CON1bits.SAMP = 1; // start sampling ...
	_AD1IE = 1;// turn interrupts on;
	_AD1IF = 0;

	samplesRequested = NumSamples;
	samplesAcquired = 0; //reset AD buffer counter		
	T3Init(SampleRate);
	
	
}
void ReadAIN4(int SampleRate, int NumSamples) // AN4 is Temperature
{
	if(NumSamples < 1) NumSamples = 1;
	if(SampleRate > 500) SampleRate = 500;
	AD1CHS0 = 0x0004; // Select AN4 as CH0 input .
	AD1CON1bits.SAMP = 1; // start sampling ...
	_AD1IE = 1;// turn interrupts on;
	_AD1IF = 0;	
	samplesAcquired = 0; //reset AD buffer counter
	samplesRequested = NumSamples;		
	T3Init(SampleRate);	
}	

void __attribute__((__interrupt__)) _ADC1Interrupt(void)
{
	WvFmIn1[samplesAcquired++] = ADCBUF0;
	adTemp += ADCBUF0; // test variable
	_AD1IF = 0; // Clear ADC interrupt flag
	if(samplesAcquired >= samplesRequested)
	{
		adTemp = adTemp/samplesRequested;
		adTest = adTemp;
		MachineState |= s_WVFMRDY;	// Waveform is ready
		T3Stop();
		adTemp = 0;
		return;
	}
	AD1CON1bits.SAMP = 1; // Sample again
}	

void ReadChannelVoltage(int Channel)
{
	Channel++;
	ReadAIN5(500, 10);
	MachineState |= 0X1000;
	
	
}

void TransmitVoltage(void)
{
	//sprintf(txAppBuff,"Wavefrom Result is %d\n\r",adTest);		
	//WriteChars(txAppBuff, strlen(txAppBuff));
	adTest = 0;
}
		