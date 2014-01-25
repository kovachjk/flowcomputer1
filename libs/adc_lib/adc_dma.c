/**********************************************************************
* © 2009 Stillbright Managment LLC
* Created 8/15/2009
* FileName:        adcDrv1.c
* Dependencies:    Header (.h) files if applicable, see below
*
*
**********************************************************************/

#include "p33fxxxx.h"
#include "dsp.h"
#include "..\h\adc.h"
#include "..\h\tglPin.h" 
#include "..\h\defines.h"             



unsigned int ADCBuffA[8][ADCSAMPLES] __attribute__((space(dma), aligned(512)));
unsigned int ADCBuffB[8][ADCSAMPLES] __attribute__((space(dma), aligned(512)));

//  Block of data for ADC Results
unsigned int wvFrmBuffer[35][288];// __attribute__ ((far));//((space(xmemory),far, aligned(512)));//was 512
unsigned int segIndex[8] = {0,4,8,12,16,20,24,28};//Innitial segment index used by each channel
unsigned int *pInput[8]; //pointer to the current location of an input channel
unsigned int chNumber = 0; //quarter wavform offsets for each 288 waveform segment
unsigned int buffOffset = 0; //actual index calculated by chNumber*NUMSAMPLES+buffOffset
unsigned int nvBuffOffset = 0; //holds buffer offset location between interrupts
unsigned int smplIndex = 0;
unsigned int wfLength = 0; //holds length to make sure first wvform is 1148 ints long
unsigned int numCollected = 0;//number of ADC collections before we run DSP
unsigned int smplsRequired = NUMSAMPLES;// number of samples needed befor we run DSP
unsigned int nvSegOffset = 0; // hold segment buffer offset between interrupts
unsigned int segmtOffset = 0;	//Offset within waveform segment
unsigned int numChannels = 0;	//number of channels
unsigned int DmaBuffer = 0; //Which DMA buffer are we using
unsigned int offsetMAX = 0; //used to hold maxADC samples in interrupt
unsigned int ADCIndex = 0; //for indexing thur ADC Samples
unsigned int segmentsNeeded = 4; // need four segments in buffer to run DSP
unsigned int bufferReady = 0;	//starting point for segments Needed
int flag = 0;

// FIR Output Buffer
fractional outputSignal[NUMSAMPLES]; __attribute__ ((space(xmemory),far,aligned(512)));

/*=============================================================================
initAdc1() is used to configure A/D to convert channel 5 on Timer event. 
It generates event to DMA on every sample/convert sequence. 
=============================================================================*/
void initAdc1()
{
	
	numChannels = NUMCHANNELS; // 4 segments per 1152 smplwavefr,+ 3 to allow for continuous
	AD1CON1bits.FORM   = 0;		// Data Output Format:0=INT; 3=Signed Fraction (Q15 format)
	AD1CON1bits.SSRC   = 7;		// Sample Clock Source: GP Timer starts conversion
	AD1CON1bits.ASAM   = 0;		// ADC Sample Control: Sampling begins immediately after conversion
	AD1CON1bits.AD12B  = 1;		// 12-bit ADC operation
	AD1CON1bits.ADDMABM = 0; 	// DMA buffers are built in scatter gather mode
	AD1CON1bits.SIMSAM = 0;
	
	AD1CON2bits.BUFM  = 0;
	AD1CON2bits.CHPS  = 0;		// Converts CH0
	AD1CON2bits.SMPI  = 7;		// Number of Buffers = SMPI + 1   
	AD1CON2bits.CSCNA = 1;		// Scan channels
	AD1CON3bits.ADRC  = 0;		// ADC Clock is derived from System Clock
	AD1CON3bits.ADCS  = 4;		// ADC Conversion Clock Tad=Tcy*(ADCS+1)= (1/40M)*5 = 129ns
								// ADC Conversion Time for 12-bit Tc=14*Tad = 1.8us	
	AD1CON3bits.SAMC = 3;		// Number of TAD cycles before conversions						
	
	AD1CON4bits.DMABL = 5;		// size of each buffer = 2^DMABL(2^5=32)

    //AD1CHS0: A/D Input Select Register
    AD1CHS0bits.CH0SA=5;		// MUXA +ve input selection (AN5) for CH0
	AD1CHS0bits.CH0NA=0;		// MUXA -ve input selection (Vref-) for CH0
	
	//AD1CSSH/AD1CSSL: A/D Input Scan Selection Register
	AD1CSSH = 0x0000;
	AD1CSSL = 0x00FF; // Scan AIN0, AIN1, AIN2, AIN3 inputs
	
   	//Configure Port Register
    AD1PCFGH=0xFFFF;   
	AD1PCFGL=0xFF00;			//AIN0 thru AIN7 configured as analog input
	

    //Interrupt Control bits
    IFS0bits.AD1IF = 0;			// Clear the A/D interrupt flag bit
    IEC0bits.AD1IE = 0;			// Do Not Enable A/D interrupt 
    
    AD1CON1bits.ADON = 1;		// Turn on the A/D converter	

    //tglPinInit();				// Toggle RA6 Init to enable blinky
    //pointers to place DMA data into working buffers
    // pCH1 thru pCH8 are all pointer into the super buffer wvFrmBuffer
    // all cCHx pointers will be offset number ADCSAMPLES every
    // DMA interrupt
    buffOffset = 0; //starting position of pointers all pointers offset from here
      


}

/*=============================================================================  
Timer 3 is setup to time-out every 4 microseconds (250Khz Rate). As a result, the module 
will stop sampling and trigger a conversion on every Timer3 time-out, i.e., Ts=4us. 
At that time, the conversion process starts and completes Tc=12*Tad periods later.

When the conversion completes, the module starts sampling again. However, since Timer3 
is already on and counting, about (Ts-Tc)us later, Timer3 will expire again and trigger 
next conversion. 
=============================================================================*/
void initTmr3() 
{
        TMR3 = 0x0000;
        PR3 = SAMPPERIOD;
        IFS0bits.T3IF = 0;
        IEC0bits.T3IE = 1;
		//T3CONbits.TCKPS = 1;
        //Start Timer 3
        T3CONbits.TON = 1;

}
void __attribute__((interrupt, no_auto_psv, __shadow__)) _T3Interrupt(void)
{
	AD1CON1bits.SAMP = 1;
	IFS0bits.T3IF = 0;	
}

// DMA0 configuration
// Direction: Read from peripheral address 0-x300 (ADC1BUF0) and write to DMA RAM 
// AMODE: Register indirect with post increment
// MODE: Continuous, Ping-Pong Mode
// IRQ: ADC Interrupt
// ADC stores results stored alternatively between BufferA[] and BufferB[]

void initDma0(void)
{
	DMA0CONbits.AMODE = 2;			// Configure DMA for Peripheral indirect mode
	DMA0CONbits.MODE  = 2;			// Configure DMA for Continuous Ping-Pong mode

	DMA0PAD=(volatile unsigned int)&ADC1BUF0;
	DMA0CNT=(ADCSAMPLES*8-1);				
	
	DMA0REQ=13;	
	
	DMA0STA = __builtin_dmaoffset(&ADCBuffA);		
	DMA0STB = __builtin_dmaoffset(&ADCBuffB);

	IFS0bits.DMA0IF = 0;			//Clear the DMA interrupt flag bit
    IEC0bits.DMA0IE = 1;			//Set the DMA interrupt enable bit
	
	DMA0CONbits.CHEN=1;

	//TRISBbits.TRISB1 = 0; This kept channel 2 from working
}


/*=============================================================================
_DMA0Interrupt(): ISR name is chosen from the device linker script.
=============================================================================*/


void __attribute__((interrupt, no_auto_psv)) _DMA0Interrupt(void)
{
	flag = 1;
	
	if(DmaBuffer == 0)
	{
		offsetMAX = nvSegOffset + ADCSAMPLES;
		for(chNumber = 0;chNumber < numChannels;chNumber++)
		{	ADCIndex = 0;
			for(smplIndex = nvSegOffset;smplIndex < offsetMAX;smplIndex++)
			{
				wvFrmBuffer[segIndex[chNumber]][smplIndex] = ADCBuffA[chNumber][ADCIndex++];	
			}		
		}	
		nvSegOffset += ADCSAMPLES;
		numCollected++;
		
		if(numCollected >= DMAs2COLLECT) 
		{
			bufferReady++;
			if(bufferReady == segmentsNeeded)
			{
				flag = 1;//run dsp.
				segmentsNeeded = 1;
				bufferReady = 0;
				for(chNumber =0; chNumber < numChannels; chNumber++)
					pInput[chNumber] = &wvFrmBuffer[segIndex[chNumber]][0];
			}			
			for(chNumber = 0; chNumber < numChannels; chNumber++)
			{
				segIndex[chNumber] = (segIndex[chNumber] ++)%32;	
			}

			numCollected = 0;
			nvSegOffset = 0;
		}
		DmaBuffer ^= 1;	
	}
	else
	{
		offsetMAX = nvSegOffset + ADCSAMPLES;
		for(chNumber = 0;chNumber < numChannels;chNumber++)
		{			
			ADCIndex = 0;
			for(smplIndex = nvSegOffset;smplIndex < offsetMAX;smplIndex++)
			{
				wvFrmBuffer[segIndex[chNumber]][smplIndex] = ADCBuffB[chNumber][ADCIndex++];				
			}	
		}
		nvSegOffset += ADCSAMPLES;				
		numCollected++;	
		if(numCollected >= DMAs2COLLECT) 
		{
			bufferReady++;
			if(bufferReady == segmentsNeeded)
			{	
				flag = 1;//run dsp.
				segmentsNeeded = 1;
				bufferReady = 0;
				for(chNumber =0; chNumber < numChannels; chNumber++)
					pInput[chNumber] = &wvFrmBuffer[segIndex[chNumber]][0];
			}
			for(chNumber = 0; chNumber < numChannels; chNumber++)
			{
				segIndex[chNumber] = (++segIndex[chNumber])%32;	
			}			
			numCollected = 0;
			nvSegOffset = 0;
		}
		DmaBuffer ^= 1;	
	}
	
 	IFS0bits.DMA0IF = 0;		//Clear the DMA0 Interrupt Flag

}




