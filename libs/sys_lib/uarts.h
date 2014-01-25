/****************************************************************************
*   CREATED BY: 	Stillbright Managment LLC
*					Copyright 2010
*                                                                           
*   FILE:           serial.h                                                 
*                                                                           
*   DESCRIPTION:    Defines names and functions for the implemation
    *               of MODBUS and RioTech serial communication. RS232, RS485.
                    Timeouts and resets are automatically calculated, base on
                    command size of a message which is base on protocol type.

*                                                                           
*   REVISION:   	v1.000                                                      
*   DATE:           12/15/12 - Moved all TX Buffers to sysglobals.h where they
 *                  can be shared by all modules.  All RX buffers will remain
 *                  with uart.h.  There will be RX buffers for
 *                  - mbRX_Buff for re
****************************************************************************/
#include <string.h> 
#include <stdio.h>
#include "../SYS_LIB/sysglobals.h"
#include "../MODBUS_LIB/modbus.h"

#ifndef _UARTS_H
#define _UARTS_H

#define BAUD		57600 				// Serial baud rate
#define GLOBAL_ID 	255  //Used to get back lost ID's and to send global commands
#define RX_MSG_SZ 8  // The number of bytes before the system will see if there is a valid command
//#define PROTOCOL MODBUS
//#define PROTOCOL RIOTECH
/*
typedef enum
{
#if defined _UART1
    // UART1 Module ID.
    UART1 = 0,
#endif
#if defined _UART2
    // UART2 Module ID.
    UART2,
#endif
#ifdef _UART3
    // UART3 Module ID.
    UART3,
#endif
#ifdef _UART4
    // UART4 Module ID (not available if UART1 CTS/RTS used).
    UART4,
#endif
#ifdef _UART5
    // UART5 Module ID (not available if UART2 CTS/RTS used).
    UART5,
#endif
#ifdef _UART6
    // UART6 Module ID (not available if UART3 CTS/RTS used).
    UART6,
#endif
    // Number of available UART modules.
    UART_NUMBER_OF_MODULES

} UART_MODULE;*/
/********************* Description*****************************
State machine in main will check UART to make sure if always goes back to MSG mode.
When is MSG mode the RX interrupt is disabled so that CheckUART can watch for hangs.
If UART is in some other state than msg mode the switch in checkUART() will 
direct the program to the function for that state.
The DMA interrupts will watch to see if there will be any more date to be received
or transmitted, if so they will leave the UART state alone so that CheckUART() can
manage the continuation of operation.
***************************************************************/

//#define FILERX_BUFF_SZ    4096u //254 bytes for data and 2 for CRC
//#define CMD_BUFF_SZ      16u //254 bytes for cmd and 2 for CRC


/***************************************************************************
 The reception of data is divided into two parts
    1. What type of date are you receiving
    2. What is the status of the reception
   RX starts out in Modbus command mode, and its status idle.  The only two ways
 * to proceed farther into the operation is to either have the unitID number
 * or an escape character in the first position of the rxBuffer.  If there is
 * an excape character the code will drop down into menu mode, if the correct ID
 * is found and the CRC is correct then the status changes to RXSTATUS_STARTED.
 * The same happens  */
//*********************  rxMode Defines ***********************

#define RXMODE_CLRSTATUS		0XFFF0	// Mask to clear all mode setting
#define RXMODE_CMD 			0x0000	// Flag indicating RX set to receive message
#define RXMODE_PRE_MENU                 0x0001  // One ESC char was received
#define RXMODE_MENU                     0x0002  // Second ESC chas received now in menu mode
#define RXMODE_INTS 			0x0004 	// Flag indicating RX set to receive ints
#define RXMODE_CHARS 			0x0008 	// Flag indicating RX set to receive chars
#define RXMODE_FLTS			0x0010
#define RXMODE_INT_ARRAY                0x0020	// Used in no DMA serial.c
 
/*********************  rxState Defines ************************/
//#define RXSTATUS_CLEARSTATUS		0xFF0F  //Mask to clear all RX status flags
#define RX_IDLE         0x0000
#define	RXMB_WAITING    0x0010 //Process this msg before looking for another
#define RXMENU_STARTING 0x0040
#define RXMENU_ACTIVE   0x0080
#define RXMENU_ENDING   0x0100
#define RX_INBLACKOUT   0x0200 //Traffic on network delay 10mSec


//*********************  TxMode Defines ***********************

#define	TXSTATUS_BUSY		0x1000
#define TXSTATUS_DONE           0x2000
//************************ txStatus Defines  ***********/
//int 	TransmitType; is variable used for below flags
/*  Modes will only be set if the TX transmit register cannot hold everything
    that needs to be transmitted.  The state machine will see that txStatus
    is non zero and call the */
#define TXMODE_STRING           0x0000
#define TXMODE_CHARS		0x0001
#define TXMODE_INTS 		0x0002
#define TXMODE_FLTS  		0x0004
#define TXMODE_INTS_CD 		0x0008 // Int16 with comma delimit
#define TXMODE_FLTS_CD 		0x0010 // float with comma delimit must come first in case statement

/***********************************************************************************
          **Defines for the State of reception of a Modbus command       **
**********************************************************************************/

#define	mbrx_CHCKRX         0x0001 // Check to make sure command isn't hung+
#define	mbrx_CMDRDY         0x0002	
#define mbrx_MSGRDY         0x0004 //Enough bytes are in to make a command
#define	mbrx_RXCOMPLETE     0x0010	

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
#define U1_BUFFSZ 128
#define TXMODBUS(Ptr2Chars,NumOfChars) WriteCharsU1(Ptr2Chars,NumOfChars);
extern char U1Buffer[U1_BUFFSZ];
//extern uChar rxBuffA[RX_BUFF_SZ]; //for vibration Waveforms
//extern uChar rxBuffB[RX_BUFF_SZ]; //for vibration Waveforms
//extern uChar uartMsgBuff[RX_MSG_SZ];
/**************************************************************************
 *                      UART1 prototypes
 **************************************************************************/


//extern uInt jkflag;
//extern uInt16 rxAppIndex;
//Resets and timeouts are automatically calculated based on msg length of protocol type
/**************************************************************************
 *                      UART1 prototypes
 **************************************************************************/
char CheckU1(void);
uInt InitU1(uInt BaudRate);//Initiallizes only U1 periphereal
uInt InitU2(uInt BaudRate);//Initiallizes only U1 periphereal
uInt InitU1AsMaster(uInt BaudRate, char UnitID);
uInt InitU1AsMBSlave(uInt BaudRate, char UnitID);
uInt InitMBMasterU1(uInt BaudRate);
uShort ReadU1AsMaster();//Initiates Modbus commands passes through menu command.
uShort ReadU1AsSlave(char * CmdBuffer, uShort SysStatus);//Listens for and responds to both Modbus and menu commands
char ReadMenuU1();
void ReadCharsU1(uChar *cData, uInt Length);
void ReadIntsU1(uInt *Buffer, uInt Length);
char* ReadStringU1(char *buffPtr);//Puts U1 recieve registers in buffer and adds null
void ResetU1(void);
void ResetMBU1(char *CmdBuffer);
void SetBaudRateU1(long BaudRate);
void WriteTerminalU1(char *buffPtr);
void WriteCharU1(uChar Data);
char WriteCharsU1(char *Buffer, uInt Length);
void WriteIntsU1(uInt *Buffer, int Length);
uChar WriteStringU1(uChar *cBuff);


/**************************************************************************
 *                      UART2 prototypes
 **************************************************************************/

void Init2(float BaudRate);
void CheckU2(int Delay);
uInt InitU2AsMaster(uInt BaudRate);
char* ReadU2(char *buffPtr);//Puts U2 recieve registers in buffer and adds null
char ReadMBMasterU2();//Initiates Modbus commands passes through menu command.
char ReadU2AsSlave();//Listens for and responds to both Modbus and menu commands
void WriteCharsU2(uChar *Buffer, uInt Length);
/*
	WriteInts allows up to 64 unsigned ints to be transfered without CPU intervention.  
	If more than 64 ints are transfered then there could be a delay in servicing
	the DMA interrupt as other processes might have higher priority.
	Remember to manage interrupt levels when receiving
*/

void WriteIntsU2(uInt *Buffer, int Length);

void ReadIntsU2(uInt *Buffer, uInt Length);
void ReadCharsU2(uChar *cData, uInt Length);
void WriteCharU2(uChar Data);
void WriteCharsU2(uChar *Buffer, uInt Length);
void ResetU2(void);
//void SetBaudRateU1(long BaudRate);
//Allowable limits for SetMsgTimeout is ~3 to 40.  Outside these limits it reset to default
//void InitUART1(uChar UnitID, float BaudRate);



/*
	WriteInts allows up to 64 unsigned ints to be transfered without CPU intervention.  
	If more than 64 ints are transfered then there could be a delay in servicing
	the DMA interrupt as other processes might have higher priority.
	Remember to manage interrupt levels when receiving
*/

//Allowable limits for SetMsgTimeout is ~3 to 40.  Outside these limits it reset to default


#endif
