/**********************************************************************
* © 2009 Stillbright
* Created 10/24/2009
*	
* FileName:        memory.c
* Purpose: Routines to read and write from non-volatile memory
* Dependencies:    Other (.h) files if applicable, see below
9/16/12 Marked this file for deletion
*
**********************************************************************/
#include "../sysglobals.h"
//#include "p33fxxxx.h"
#include "../spi.h"
#include "../nv_memory.h"

extern unsigned int mState;
extern spiStatus cSPI2;
unsigned int readAddress, writeAddress;.
unsigned int readIndex, writeIndex;
unsigned int xm, iData = 0;
unsigned char cData;

//InitNVM
void epInit(void)
{
	// init the SPI peripheral
    TRISEPROM = 0;          // make SSEE pin output
    EPDISABLE = 1;          // de-select the Serial EEPROM
    SPI2CON1 = SPI_MASTER;  // select SPI mode
    SPI2STAT = SPI_ENABLE;  // enable the peripheral

}

// Check the Serial EEPROM status register
char epReadSR( void)
{
    EPDISABLE = 0;			// select the Serial EEPROM
    cData = rwCharSPI2(EP_RSTATUS); // send a READ STATUS COMMAND
    cData = rwCharSPI2(0);
    EPDISABLE = 1;			// deselect to terminate command
    return cData;
} //ReadSR

// read a 16-bit value starting at an even address
int epReadInt( int address)
 {
	// wait until any work in progress is completed
	while ( epReadSR() & 0x3);	// check the two lsb WEN and WIP

	// perform a 16-bit read sequence (two byte sequential read)
	EPDISABLE = 0;				// select the Serial EEPROM
	rwCharSPI2( EP_READ);	// read command
	rwIntSPI2(address);	// address MSB first
	iData = rwIntSPI2(0x00);	// address MSB first
	//WriteSPI2( address & 0xfe);// address LSB (word aligned)
	//msb = WriteCharSPI2( 0);	// send dummy, read msb
	//lsb = WriteCharSPI2( 0);	// send dummy, read lsb
	EPDISABLE = 1;
	return (iData);
}


// send a Write Enable command
void epWriteEnable( void)
{

	EPDISABLE = 0;				// select the Serial EEPROM
	rwCharSPI2(EP_WREN);	// write enable command
	EPDISABLE = 1;				// deselect to complete the command
}


// write a 16-bit value starting at an even address
void epWriteInt( int address, int data)
{

	// wait until any work in progress is completed
	while (epReadSR() && 0x3);	// check the two lsb WEN and WIP

	// Set the Write Enable Latch
	epWriteEnable();

	// perform a 16-bit write sequence (2 byte page write)
					// select the Serial EEPROM
	rwCharSPI2(EP_WRITE);		// write command
	EPDISABLE = 0;
	rwIntSPI2(address);
	//WriteSPI2( address>>8);		// address MSB first
	//WriteSPI2( address & 0xfe);	// address LSB (word aligned)
	//WriteSPI2( data >>8);		// send msb
	rwIntSPI2(data);	// send lsb
	EPDISABLE = 1;
}//iWriteNVM


char epReadChar(int address)
{
	// read a 8-bit value

	// wait until any work in progress is completed
	while ( epReadSR() & 0x3);	// check the two lsb WEN and WIP

	// perform a 16-bit read sequence (two byte sequential read)
	EPDISABLE = 0;				// select the Serial EEPROM
	rwCharSPI2( EP_READ);	// read command
	rwIntSPI2( address);	// address MSB first
	//WriteSPI2( address & 0xff);// address LSB (word aligned)
	//msb = WriteSPI2( 0);	// send dummy, read msb
	cData = rwCharSPI2( 0);	// send dummy, read lsb
	EPDISABLE = 1;
	return (cData);
}

int epReadInts(int address,int* data,int numInts)
{


	// wait until any work in progress is completed
	while ( epReadSR() & 0x3);	// check the two lsb WEN and WIP

	// perform a 16-bit read sequence (two byte sequential read)
	EPDISABLE = 0;				// select the Serial EEPROM
	rwCharSPI2( EP_READ);	// read command
	rwIntSPI2( address);	// address MSB first
	//WriteSPI2( address & 0xfe);// address LSB (word aligned)
	for(xm=0; xm<numInts;xm++)
	{
		data[xm] = rwIntSPI2(0);//<<8;	// send dummy, read msb
		//data[x] += WriteSPI2( 0);	// send dummy, read lsb
	}
	EPDISABLE = 1;
	return (1);
}

/*
* WriteEPInts takes array and write it to DMA buffer
* returns error if address rule is broken ( not implemented yet)
*/
int epWriteIntsDMA(int Address,int* Data,int Num2Write)
{

	if(cSPI2.status == spiIdle)
	{
		cSPI2.status |= spiWriting;
		cSPI2.data = Data;
		cSPI2.address = Address;
		cSPI2.numInts = Num2Write;
		cSPI2.offset = 0;
		cSPI2.block = 0;
	}
	// wait until any work in progress is completed

	while ( epReadSR() & 0x3);	// check the two lsb WEN and WIP

	// Set the Write Enable Latch
	epWriteEnable();

	// perform a 16-bit write sequence (2 byte page write)
	//EPDISABLE = 0;					// select the Serial EEPROM
	WriteSPI2( EP_WRITE);		// write command
	WriteSPI2( Address>>8);		// address MSB first
	WriteSPI2( Address & 0xfe);	// address LSB (word aligned)
	initWritesSPI2();

	return (1);
}
