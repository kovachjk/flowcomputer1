/****************************************************************************
*   CREATED BY: 	Stillbright Managment LLC
*					Copyright 2010
*                                                                           
*   FILE:           serial.h                                                 
*                                                                           
*   DESCRIPTION:    Defines names and functions for the implemation
*					of MODBUS and RioTech serial communication. RS232, RS485.
					Timeouts and resets are automatically calculated, base on
					command size of a message which is base on protocol type.

*                                                                           
*   REVISION:   	v1.000                                                      
*   DATE: 			Sept 3 2010                                                 
****************************************************************************/
#include "sysglobals.h"
//#include "protocols.h"
#ifndef _comm_h
#define _comm_h

#define BAUD		57600 				// Serial baud rate
#define GLOBAL_ID 	255  //Used to get back lost ID's and to send global commands

//#define PROTOCOL MODBUS
//#define PROTOCOL RIOTECH

/********************* Description*****************************
State machine in main will check UART to make sure if always goes back to MSG mode.
When is MSG mode the RX interrupt is disabled so that CheckUART can watch for hangs.
If UART is in some other state than msg mode the switch in checkUART() will 
direct the program to the function for that state.
The DMA interrupts will watch to see if there will be any more date to be received
or transmitted, if so they will leave the UART state alone so that CheckUART() can
manage the continuation of operation.
***************************************************************/
#define TX_BUFF_SZ 256u //254 bytes for data and 2 for CRC
#define RX_BUFF_SZ 128u  //125 bytes
#define UARTMsgTimeout  10u  //reset occurs after x runs through CheckRX()
//*********************  rxMode Defines ***********************
#define UART_DISABLED			0x0000
#define RXCLR_MODEFLAGS			0XFFF0	// Mask to clear all mode setting
#define RXMODE_CMD 				0x0001	// Flag indicating RX set to receive message
#define RXMODE_INTS 			0x0002 	// Flag indicating RX set to receive ints
#define RXMODE_CHARS 			0x0004 	// Flag indicating RX set to receive chars
#define RXMODE_FLTS				0x0006
#define RXMODE_INT_ARRAY_MODE	0x0008	// Used in no DMA serial.c
 
//*********************  rxStatus Defines ***********************
#define RXCLR_STATUSFLAGS		0xFF0F  //Mask to clear all RX status flags
#define	RXSTATUS_MSGSTARTED		0x0010
#define RXSTATUS_MSGWORKING 	0x0020 //Process this msg before looking for another
#define RXSTATUS_INBLACKOUT		0x0040 //Traffic on network delay 10mSec
#define RXSTATUS_RXARRAY 		0x0080 //Tells system to receive array of chars, ints or flts
//*********************  TxMode Defines ***********************
#define TXCLR_STATUSFLAGS		0x0FFF  //Mask to clear all RX status flags
#define	TRXSTATUS_TXSTARTED		0x1000

//************************ txStatus Defines  ***********/
//int 	TransmitType; is variable used for below flags
#define TXCLR_MODEFLAGS		0xF0FF // Mask to clear all TX staturs flags
#define TXMODE_NONE 		0x0000
#define TXMODE_CHARS		0x0100
#define TXMODE_INTS 		0x0200
#define TXMODE_FLTS  		0x0400
#define TXMODE_INTS_CD 		0x0800 // Int16 with comma delimit 
#define TXMODE_FLTS_CD 		0x0900 // float with comma delimit must come first in case statement
/*
union
{
	struct
	{
		unsigned char lowByte;
		unsigned char highByte;
	}byte;
	struct
	{
		unsigned b0:1;
		unsigned b1:1;
		unsigned b2:1;
		unsigned b3:1;
		unsigned b4:1;
		unsigned b5:1;
		unsigned b6:1;
		unsigned b7:1;
		unsigned b8:1;
		unsigned b9:1;
		unsigned b10:1;
		unsigned b11:1;
		unsigned b12:1;
		unsigned b13:1;
		unsigned b14:1;
		unsigned b15:1;
	};	
	uInt16 reg;
}MBReg;//Modbus Register

*/

extern uChar rxBuffA[RX_BUFF_SZ]; //For Waveforms
extern uChar rxBuffB[RX_BUFF_SZ]; //for Waveforms
//extern uChar uartMsgBuff[RX_MSG_SZ];
extern uChar charData[1024];
extern uInt intData[512];
extern uChar txBuffA[TX_BUFF_SZ];
extern uInt jkflag;
//extern uInt16 rxAppIndex;
//Resets and timeouts are automatically calculated based on msg length of protocol type
void InitUART(uChar UnitID, float BaudRate);
uChar CheckUART(void); 
void WriteChars(uChar *Buffer, uInt Length);
/*
	WriteInts allows up to 64 unsigned ints to be transfered without CPU intervention.  
	If more than 64 ints are transfered then there could be a delay in servicing
	the DMA interrupt as other processes might have higher priority.
	Remember to manage interrupt levels when receiving
*/
void WriteInts(uInt *Buffer, int Length);
void ReadInts(uInt *Buffer, uInt Length); 
void ReadChars(uChar *cData, uInt Length);
void WriteChar(uChar Data);


void ResetRX(void);
void SetBaudRate(long BaudRate);
//Allowable limits for SetMsgTimeout is ~3 to 40.  Outside these limits it reset to default



#endif
