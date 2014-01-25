/**********************************************************************
* © 2009 Stillbright
* Created 10/24/2009
*
* FileName:        spi2.c
* Dependencies:    Other (.h) files if applicable, see below
*
**********************************************************************/
#include "p33fxxxx.h"	
#include "spi.h"

#include "globals.h"
extern unsigned int mState;
static spiStatus cSPI2;
int index;
unsigned char SPI2TxBuff[spiBuffSize] __attribute__((space(dma)));
unsigned char SPI2RxBuff[spiBuffSize] __attribute__((space(dma)));
void initSPI2(void)
{
	SPI2CON1bits.PPRE = 1;
}
int WriteCharSPI2( int i)
{
    SPI2BUF = i;					// write to buffer for TX to start
    while( !SPI2STATbits.SPIRBF);	// wait for transfer to complete
    return SPI2BUF;    				// read the received value
}//WriteSPI2


void initWritesSPI2(void)
{
	int index;
	//Configure DMA Channel 5 to write bytes to SPI2
	DMA5CON = 0; //Reset register
	DMA5CONbits.MODE = 1; 	// 01 = One shot mode, Ping Pong disabled
	DMA5CONbits.AMODE = 0;	// 00 = Register indirect with post increment
	DMA5CONbits.DIR = 1; 	//  1 = Write to peripheral
	DMA5CONbits.SIZE = 0;	//  1 = byte, 0 = word
	

	DMA5STA = __builtin_dmaoffset(SPI2TxBuff);
	//DMA5STB = __builtin_dmaoffset(SPI2TxBufferB);
	DMA5PAD = (volatile unsigned int) &SPI2BUF;
	DMA5CNT = spiBuffSize - 1;
	DMA5REQ = 0x000A;
	for(index = 0; index < spiBuffSize; index++)
	{
		SPI2TxBuff[index] = cSPI2.data[index + cSPI2.offset++];	
	}
	DMA5CONbits.CHEN=1;
	IFS3bits.DMA5IF = 0;
	IEC3bits.DMA5IE = 1;
	DMA5REQbits.FORCE=1; //Start Transfer
}
//Configure DMA to mamage NV memory writes
void initReadsSPI2(void)
{		
	//Set up DMA Channel 6 to Receive in Continuous Ping-Pong mode:
	DMA6CON = 0; //Reset register	
	DMA6CONbits.MODE = 1; // 01 = One shot mode, Ping Pong disabled//
	DMA6CONbits.SIZE = 0;	//  1 = byte, 0 = word
	DMA6CONbits.DIR = 0;  //  0 = Read from peripheral
	DMA6STA = __builtin_dmaoffset(SPI2RxBuff);
	//DMA6STB = __builtin_dmaoffset(SPI2RxBufferB);
	DMA6PAD = (volatile unsigned int) &SPI2BUF;
	DMA6CNT = spiBuffSize - 1;
	DMA6REQ = 0x0021;	//0100001 = SPI2 Transfer complete interrupt selected
	DMA6CONbits.CHEN=1;
	//IFS4bits.DMA6IF = 0;
	//IEC4bits.DMA6IE = 1;	
	DMACS0 = 0;	// Clear collision bit flags in DMA
	DMA5REQbits.FORCE=1; //Start Transfer
	while (DMA5REQbits.FORCE==1);
}


//SPI and DMA Interrupt Handler
void __attribute__((__interrupt__)) _SPI2Interrupt(void)
{
	IFS2bits.SPI2IF =0;
}
/*
*	DMA5Interupt is for writing arrays to NV memory
*	It will be called by either EPWriteInts or EPWriteChars
*/
void __attribute__((__interrupt__)) _DMA5Interrupt(void)
{
	//static unsigned int BufferCount = 0; // Keep record of which buffer
	// contains TX Data
	if(cSPI2.offset >= cSPI2.numInts)
	{
		cSPI2.status &= !spiWriting;
		mState &= !SPI2Idle;
	}
	if(cSPI2.offset + spiBuffSize < cSPI2.numInts)
	{
		for(index = 0; index < spiBuffSize; index++)
		{
			SPI2TxBuff[index] = data[cSPI2.offset++]	
		}
	}
	else
	{	index = 0;
		while(cSPI2.offset < cSPI2.numInts)
		{
			
			cSPI2TxBuff[index++] = cSPI2.data[cSPI2.offset++]
		}
		DMA5CNT = index - 1;			
	}	
	//BufferCount ^= 1;	
	IFS0bits.DMA0IF = 0; // Clear the DMA0 Interrupt Flag
	DMA5REQbits.FORCE=1; //Start Transfer

}
	
void __attribute__((__interrupt__)) _DMA6Interrupt(void)
{
	//static unsigned int BufferCount = 0; // Keep record of which buffer
	// contains RX Data
/*	if(BufferCount == 0)
	{
		SPI2RxBuff[5] = 8; // Process received SPI data in
		// DMA RAM Primary buffer
	}

	BufferCount ^= 1;*/
	IFS0bits.DMA1IF = 0; // Clear the DMA1 Interrupt Flag
}


unsigned char rwSPI2chars(unsigned char *Data, int NumOfChars, int Channel)
{
	return 8;
	
}

