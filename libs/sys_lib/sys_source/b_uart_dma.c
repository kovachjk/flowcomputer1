/****************************************************************************
   CREATED BY: 	Stillbright Managment LLC
*					Copyright 2010
*                                                                           
*   FILE:           mb_uart.c                                                
*                                                                           
*   DESCRIPTION:    Source Code uart routines using PIC33 DMA capabilities and implements 
					the definitions in serial.h       
*                                                                           
*   REVISION:   	v1.005                                                      
*   Aug 20 2010 	Created
*	3/9/2012	-	Changed name to mb_uart.c. Intent is to seperate protocol based serial uart and a char based uart
****************************************************************************/
#include <string.h>                     // String and buffer processing definitions
#include <uart.h>
#include <stdio.h>
#include "sysglobals.h"
#include "mb_uart.h" //Function definitions and global flags 
#include "protocols.h"
#include "digital.h"
//********************* file scope variables ********************
char 	jktest = 0, uartTimeout = 0;
uChar	msgTimeoutFlag2 = 0;
uInt16 	msgTimeoutFlag=0;
//uChar 	uartMsgBuff[RX_MSG_SZ]__attribute__((space(dma)));

uChar	rxBuffA[RX_BUFF_SZ] __attribute__((space(dma)));  
uChar	rxBuffB[RX_BUFF_SZ] __attribute__((space(dma)));
uChar   txBuffA[TX_BUFF_SZ] __attribute__((space(dma))); 	
uChar	unitID = 100,	
		bufferSelect = 0,
		PageMarker = 0, 	// Tracks number of buffers to be sent 
		delimiter;			//Var to hold delimiting char between numbers.
//int		uartFailSafe = 0;  //Recheck occasionally to make sure that your in cmd mode
uInt16  delay = 0; 		
		
volatile uInt16	UARTstate;		
long 	gblBaud; 		// variable to hold baud rate
float 	time4Byte;  	//Holds time in mSec to transmit 1 Byta at baud rate 

//******************** flags and variables for transmit **********
uChar	*txCharData = NULL,  	//Pointer to  CHAR data to be transmitted.
		int2CharIndex,
		txTimeout;
		//timer for clearing tx Buffer
uInt16 	*txIntData = NULL,		//Pointer to  INT data to be transmitted.
		loopIndex,
		txDataIndex,	//Holds index to data for multi packet transmits
		txTotalLength,	//Overall number of registers to be transmitted
		txLengthRemaining; //number of bytes remaining.
float	*txFloatData;
//***************** flags and variables for receive **********
uChar	*rxCharData, //Pointer to hold application buffer of chars
		rxStatus,		
		lastByteCount = 0, //Var to varify that we are still receiving data
		rxTimeout = 10; //timer for clearing rx Buffer
uInt16	*rxIntData,		
		rxDataIndex,	//Holds index to data for multi packet transmits
		dma1staBaseAddress, //Represents zero index of bytes received
		bytesCaptured; 	//Have we got all of the message
uInt16 	bytes2Capture;		//Length of message to capture		
long	rxArray2Capture = 0,  //number of bytes in the array to capture
		rxArrayCaptured; //number of bytes remaining.
		
float 	*rxFloatData;
//************** MARKED FOR DELEATION **********************
uChar 	receiveBuff;		// takes data from U2RXREG
//uChar	msgBuff[RX_MSG_SZ];	//Need to Delete	
//uChar	charData[1024]; //Need to move to DSP
//uInt16  intData[512];	//Need to move to DSP
//uChar	lowByte;	//Flag indicating where next byte goes in uInt16

uInt16  *fileBuff, jkint;; //Pointer to int data to be stored

volatile uInt16
	msgIndex = 0,				//Index for MsgBuffer
    rxISRIndex = 0,           // Index for Rx buffer access by ISR
    rxAppIndex = 0,           // Index for Rx buffer access by application
    txAppIndex = 0,           //   "    "  Tx   "      "    "  application    
    txISRIndex = 0,           //   "    "  Tx   "      "    "  ISR
    BufferCount = 0; //buffA is even buffB is odd
	 		//What stage of a message reception is the porgram in.
	 		
uInt16 	*IntsBuffer;  // Pointer to hold Int array for transmission

char   
	//MsgTimeout = 0, //Timout used when receiving a message
	rxIndex = 0;	//number of bytes received
	
	uInt16
	// Change rxPageMaker when wanting to receive new msg while working on old 
	// msg
	
	rxFileLength = 0,	// Length of File to receive;
	txType = 0, //Flag that allows transmisson or chars ints floats or common delimited
	rxMode = 0; //Flag to indicates if RX is in command or file mode.

    
//************** MARKED FOR DELEATION **********************

     


/****************************************************************************
*   FUNCTION:       CommInit(Uint8 ui8Port, Uint16 ui16BaudRate,            *
*                            Uint16 ui16Parity, Uint16 ui16StopBits)        *
*                                                                           *
*   DESCRIPTION:    This function configures the system's communication     *
*                   channel(s).  It must be customized for the specific     *
*                   communication modules and channel parameters used       *
*                   for the particular application.                         *
*                                                                           *
*                   The function uses the global system communication       *
*                   configuration parameters; if any of these parameters    *
*                   are invalid, it uses the default channel parameters     *
*                   to ensure that the communication channel is at least    *
*                   operational.                                            *
*                                                                           *
*          			Msg is processed after 4 bytes worth of time            *
*                                                                           *
*   PARAMETERS:     ui8Port      - index of UART port to configure          *
*                                  (MUST be either UART_1 or UART_2)        *
*                   ui16BaudRate - communication baud rate in bits/sec      *
*                   ui16Parity   - type of parity to use (MUST be one       *
*                                  of PARITY_*)                             *
*                   ui16StopBits - number of stop bits (MUST be either      *
*                                  STOP_BITS_1 or STOP_BITS_2)              *
*                                                                           *
*   RETURNS:        The function returns one of the following status        *
*                   code values:                                            *
*                   ST_OK        - operation successful                     *
*                   ST_INV_PARM  - invalid communication parameter          *
*                                  detected, default channel parameters     *
*                                  used                                     *
*                   ST_COMM_INIT - failed to initialize the requested       *
*                                  communication channel(s)                 *
*                                                                           *
*   REVISION:  0    v1.0                DATE:  1 October 2008               *
*       Original release.                                                   *
****************************************************************************/
void InitUART(uChar UnitID, float BaudRate)
{
	SetBaudRate(BaudRate);
	IPC7 = 0x4400;	// Mid Range Interrupt Priority level

	IFS1bits.U2RXIF = 0;	// Clear the Recieve Interrupt Flag
	U2STAbits.UTXISEL1 = 0;	// Interrupt when char is loaded into
	U2STAbits.UTXISEL1 = 0; // U2TXREG transmit register
	U2MODEbits.UARTEN = 1;	// And turn the peripheral on
	U2STAbits.UTXEN = 1;	// Enable UART transmitter.
	U2STAbits.URXISEL1 = 0;	
    UARTstate = RXMODE_CMD;// Set system to receive commands
    //Configure DMA1 to Receive	Commands
    DMA1CON = 0x0001; // Continuous, no Ping-Pong, Post-Inc., Periph-RAM
	DMA1REQ = 0x001E; 		// Select UART2 Receiver
	DMA1CONbits.SIZE = 1;  	//1 = byte size transfers
	DMA1PAD = (volatile unsigned int) &U2RXREG;
	DMA1STA = __builtin_dmaoffset(rxBuffA);
	DMA1STB = __builtin_dmaoffset(rxBuffB);	
	DMA1CONbits.CHEN = 1; 	// Enable DMA Channel 
	DMA1CNT = 101 -1; 	//interrupt after 100 bytes . 
	dma1staBaseAddress = DMA1STA; //Allows us to count number of bytes received
	IFS0bits.DMA1IF = 0; 	// Clear DMA interrupt
	IEC0bits.DMA1IE = 0; 	// Disable interrupt. Let checkUART() check.
	bytes2Capture = MIN_MB_MSG_SZ;  //All messages start with this size 
	
    //Configure DMA2 For to transmit 
    DMA2CONbits.MODE = 1;  // Continuous, Post-Increment, Ping Pong
    DMA2CONbits.DIR = 1; //Write from SRAM to periphrial
    DMA2CNT = TX_BUFF_SZ-1; // Number of chars befor DMA interrupt
	DMA2REQ = 0x001F; // Select UART2 Transmitter
	DMA2PAD = (volatile unsigned int) &U2TXREG;
	DMA2CONbits.SIZE = 1;  //1 = byte transfers
	DMA2STA = __builtin_dmaoffset(txBuffA);
	DMA2CONbits.CHEN = 0; 	
	IPC6bits.DMA2IP = 7;  //Set DMA2 interrupt prioity to highest setting
	IFS1bits.DMA2IF = 0; // Clear DMA Interrupt Flag
	IEC1bits.DMA2IE = 0; // Enable DMA interrupt only when you have something to send
	rxBuffA[0] = 0; // UnitID byte should always be empty

//	Set Msg timeout to be 3 times the time to receive a Msg
	//BaudRate = 1/(float)(gblBaud/1000);	
	//BaudRate = (BaudRate * 10 * RX_MSG_SZ * 3);
//	MsgTimeout = BaudRate;
	for(loopIndex = 0; loopIndex<=20;loopIndex++)rxBuffA[loopIndex]=0;
	unitID = UnitID;
}

void SetBaudRate(long BaudRate)
{
	
   	if((BaudRate >115000)||BaudRate<9600)BaudRate = 19200;
   	gblBaud = BaudRate;
   	time4Byte = BaudRate;
   	time4Byte = (1/time4Byte)*12;  //Time to transmit 1 byte plus margin
   	// This is an EXAMPLE, so brutal typing goes into explaining all bit sets
	// The HPC16 board has a DB9 connector wired to UART2, so we will
	// be configuring this port only
	
	// configure U2MODE

	// Load a value into Baud Rate Generator.  Example is for 9600.
	// See section 19.3.1 of datasheet.
	//  U2BRG = (37M/(16*9600))-1
	U2BRG = (gblFcy/(16*gblBaud))-1;
	
		
	
}
uInt16 GetBaudRate(void)
{
	return 2;//need to write code here
}
void SetPacketSize(uInt16 Size)
{
	
}
/********************************************************
	Function: CheckUART
	Operation:  UARTstate manages the different states of the
	uart without blocking other MCU opperation.  
	Pseudo Code
	Every 1mSec CheckUART()
	If rxBuff[0] empty return;
	If rxBuff[0] = unit ID then check and see if a msg has already been started
	If number of bytes >= default message size then process message to see if we
	have more bytes to capture
	Process Message will either check CRC and generate the command or return 
	the number of extra bytes we need to capture
	Once we have all the bytes, Process Message and check CRC;
	Reset UART
	
*/
uChar CheckUART(void)
{
	static uChar rxByteCount; 

	rxByteCount = DMA1STA - dma1staBaseAddress;
	if((rxByteCount) != 0) // Is there anything in the DMA buffer
	{
		#if PROTOCOL == RIOTECH
		if ((rxBuffA[0] == unitID) && IFS0bits.DMA1IF)// This is for me
		{
			ProcessSerialMsg(rxByteCount);
			ResetRX();	
			//MachineState |= s_MSGRDY; //Tell state machine msg is ready	
			return;	
		}
		else 
		#endif
		#if PROTOCOL == MODBUS
		LED0 = 1;
		if (rxBuffA[0] == unitID) 
		{	
			if((UARTstate & RXSTATUS_MSGSTARTED) == RXSTATUS_MSGSTARTED)
			{		
				LED2 = 1;
				if (rxByteCount >= bytes2Capture)//Enough bytes for minimum sized msg
				{	
					//do I need more bytes?. If not, implement command and return zero.
					bytes2Capture = ProcessSerialMsg(rxByteCount);
					if(bytes2Capture == 0) //Done with this message
					{
						PORTA = 0;//jk test flag
						ResetRX();
						return 0;
					}
					return 0;//Get the rest of the message
				}
				if((rxByteCount)==lastByteCount)//Am I still receiving?
				{	
					if(uartTimeout >= 1)//Give it one more go around
					{
						//Guess not, reset
						LED3 = 1;	//reset jk test flags
						uartTimeout = 0;								
						ResetRX();

					}						
					uartTimeout++;	
				}						
				lastByteCount =	rxByteCount; //Remember how many bytes so far
				return 0;	//Give more time to get more bytes and come back
			}
			else
			{
				if (rxByteCount >= bytes2Capture)//Enough bytes for minimum sized msg
				{	
					//do I need more bytes?. If not, implement command and return zero.
					bytes2Capture = ProcessSerialMsg(rxByteCount);
					if(bytes2Capture == 0) //Done with this message
					{
						PORTA = 0;//reset jk test flags
						ResetRX();
						return 0;
					}
				}
				LED1 = 1;
				UARTstate |= RXSTATUS_MSGSTARTED;
				return 0;
				//bytes2Capture = RX_MSG_SZ;//Start with smallest msg possible
			}		
		}
		#endif		
		else //If ID isn't for me, reset ID byte
		{
			//I could look at command and delay looking at RX for a time period
			ResetRX();
		}	
	}

	if((UARTstate & RXMODE_CMD) != RXMODE_CMD)	
	{
		if((UARTstate & RXMODE_CHARS) == RXMODE_CHARS)
					ReadChars(rxCharData, rxArrayCaptured);
	
		if((UARTstate & RXSTATUS_RXARRAY) == RXSTATUS_RXARRAY)//for receiving long files
		{
		//	resetDelay --;	
		}		
	}
	if((UARTstate & TXMODE_CHARS) == TXMODE_CHARS)
	{
		WriteChars(txCharData, txLengthRemaining);	
	}
	if((UARTstate & TXMODE_INTS) == TXMODE_INTS)	
	{
		if(IFS1bits.DMA2IF == 1)
		{
			if(SRbits.IPL > 6) return 1;//Transmitting long buffer, let DMA2 interrupt handle this.
			UARTstate &= ~TXMODE_INTS;
			IFS1bits.DMA2IF = 0; 	
		} 	
	}			
	if((UARTstate & TXMODE_INTS_CD) == TXMODE_INTS_CD)//COMMA DELIMITED INTS
	{	
	//	resetDelay --;
	} 
	
	return 0;	
}

void ResetRX(void) // Puts RX back into command mode
{	

	DMA1CONbits.CHEN = 0;  //Toggle DMA1 to reset	
	//DMA1STA = __builtin_dmaoffset(rxBuffA);	
	//IE0bits.DMA1IE = 0; // disable DMA interrupt let app check	
	//RTstate &= RXCLR_STATUSFLAGS; //Clear all status flags
	//RTstate &= RXCLR_MODEFLAGS; // Clear all RX mode flags
	UARTstate = RXMODE_CMD; // Put RX back in mode to receive commands
	DMA1CONbits.CHEN = 1; 	// Enable DMA1 Channel for messages	
	bytes2Capture = MIN_MB_MSG_SZ;
	IFS0bits.DMA1IF = 0; // Clear DMA Interrupt Flag.	
	DMA1CNT = 100;// RX_MSG_SZ -1; //Set interrupt flag after RX_MSG_SZ bytes .
	rxBuffA[0] = 0;
	lastByteCount = 0;
	//if(DMA1CONbits.CHEN == 0)PORTAbits.RA0=1;
	
}
		
void ResetTX(void)
{
	
}
void SetUARTStatus(uInt16 Status)
{
	UARTstate |= Status;
}
void ClearUARTStatus(uInt16 Status)
{
	UARTstate &= ~Status;
}
void WriteChar(uChar Data)
{
	DMA2CONbits.CHEN = 0;
	U2TXREG = Data;
	while(U2STAbits.TRMT == 0);
	IFS1bits.U2TXIF = 0;
	DMA2CONbits.CHEN = 0;
}

void WriteChars(uChar *Buffer, uInt16 Length)
{
	jktest = 0;
	if(Buffer == NULL) return; //check for null pointers
			
	if(Length >= TX_BUFF_SZ) 
	{	
		if((UARTstate &= TXMODE_CHARS) == 0)//New request
		{
			UARTstate != TXMODE_CHARS;//Tell UART state machine there will be more to transmit
			bufferSelect = 0;
			txLengthRemaining = Length; //Tell app about total length	
		}
		Length = TX_BUFF_SZ;
			
		if(bufferSelect == 0)
		{
			for(loopIndex = 0; loopIndex < Length; loopIndex++)
			{
				txBuffA[loopIndex] = txCharData[loopIndex];
			}		
		}
		else
		{				
			for(loopIndex = 0; loopIndex < Length; loopIndex++)
			{
				txBuffA[loopIndex] = Buffer[loopIndex];
			}			
		}
		txCharData = &Buffer[txDataIndex + Length];
		txLengthRemaining -= Length;
		bufferSelect ^= 1; // Tell UART state machine to load txBuffA next					
	}
	else 
	{	
		for(loopIndex = 0; loopIndex < Length; loopIndex++)
		{
			txBuffA[loopIndex] = Buffer[loopIndex];
		}
		
		if((UARTstate &= TXMODE_CHARS) == 1) //If UART in TXMODE_CHARS mode then
		{
			UARTstate &= ~TXMODE_CHARS; //Remove TXMODE_CHARS flag
			txLengthRemaining = 0;
		}
	}
	DMA2CNT = Length - 1;
	//txTimeout += Length * time4Byte; // Delay reset 
	//IEC1bits.DMA2IE = 1; // Enable DMA interrupt
	DMA2CONbits.CHEN = 1;// Enable DMA2 Channel	
	DMA2REQbits.FORCE = 1;// Manual mode: Kick-start the 1st transfer
	jktest = 8;	
}

void WriteInts(uInt16 *Buffer, int Length)
{

	if(Buffer == NULL) return; //check for null pointers
	if((UARTstate & TXMODE_INTS) == TXMODE_INTS) return;//I'm already busy
	txLengthRemaining = Length;
	if(txLengthRemaining * 2 >= TX_BUFF_SZ)// Extra long transmit need to use interrupt
	{
		Length = TX_BUFF_SZ>>1; 
		IEC1bits.DMA2IE = 1;
		SRbits.IPL = 7; 
	}		 		 
	for(loopIndex = 0; loopIndex < Length; loopIndex++)
	{
		rxBuffA[loopIndex] = Buffer[loopIndex]<<8;
		rxBuffA[loopIndex+1] = Buffer[loopIndex]&0x00FF;
	}	
	txLengthRemaining -= Length;
	DMA2CNT = Length - 1;
	IFS1bits.DMA2IF = 0;//Clear DMA2 interrupt flag 
	DMA2CONbits.CHEN = 1;// Enable DMA2 Channel	
	DMA2REQbits.FORCE = 1;// Manual mode: Kick-start the 1st transfer
}

void ReadInts(uInt16 *Buffer, uInt16 Length)
{
	//CheckRX(); // Delay RX reset for 40mSec
	rxFileLength = Length;
	fileBuff = Buffer;
	UARTstate |= RXMODE_INTS;
//	rxISRIndex = 0;
//	lowByte = 0;
	
}

void ReadChars(uChar *Buffer, uInt16 Length)
{
	if(Buffer == NULL) return; //check for null pointers
	if(rxArray2Capture == 0) // This is the start of a read
	{
		rxCharData = Buffer;
		rxArray2Capture = Length;
		DMA1CONbits.CHEN = 0; 	// Turn off MSG DMA 
		DMA1CONbits.CHEN = 1; 	//Turn on RX DMA
		if(Length <  RX_BUFF_SZ)
		{
			DMA1CNT = Length - 1;
			rxArrayCaptured = Length;//after interrupt
		}
		else 
		{
			DMA1CNT = RX_BUFF_SZ - 1;
			rxArrayCaptured = RX_BUFF_SZ;//after interrupt
		}	
		IFS0bits.DMA1IF = 0; // Clear DMA Interrupt Flag					
		IEC0bits.DMA1IE = 1; 	// Enable DMA1 interrupts
		DMA1STA = __builtin_dmaoffset(rxBuffA); // Start DMA looking at BuffA
		bufferSelect =0;  //Tell this function thats what your doing
		rxTimeout += 20; //Give DMA Time to receive rest of data
		UARTstate = RXSTATUS_RXARRAY;				
	}
	else //Read data thats already been captured
	{			
		if(bufferSelect == 0)
		{
			for(loopIndex = 0; loopIndex < Length; loopIndex++)
			{
				rxCharData[loopIndex] = rxBuffA[loopIndex];
			}
		}
		else
		{	
			for(loopIndex = 0; loopIndex < Length; loopIndex++)
			{
				rxCharData[loopIndex] = txBuffA[loopIndex];
			}		
		}
		bufferSelect ^= 1; // tell app we switched buffer	
		rxArray2Capture -= Length;	//Amount left to tranfer after this			

		if(rxArray2Capture <= 0)// Switch back to MSG mode
		{
			UARTstate &= RXCLR_STATUSFLAGS; //Clear all status flags
			UARTstate &= RXCLR_MODEFLAGS; // Clear all RX mode flags
			UARTstate |= RXMODE_CMD; // Put RX back in mode to receive commands	
			return;
		}			
		if(rxArray2Capture >=  RX_BUFF_SZ)
		{
			rxArrayCaptured = RX_BUFF_SZ;//after interrupt	
			DMA1CNT = RX_BUFF_SZ - 1;	
		}
		else 
		{
			rxArrayCaptured = rxArray2Capture;
			DMA1CNT = rxArray2Capture;
		}
	}	
	rxTimeout += rxArrayCaptured * time4Byte; // Delay reset 	
	
}  


	
 /**********************************************************
*   FUNCTION:   CheckRX(int Delay)                                    
*	
*	Resets the receive system after Delay * 10mSec Time
*************************************************************/
void ResetMsgBuff(void)
{
//    msgIndex = 0; //reset message Index
  //	msgBuff[msgIndex] = 0; //clear command
  	
}
void ClearTXFlags()
{
	UARTstate = UARTstate & TXCLR_MODEFLAGS; //Clear all txFlags	
}

///DMA interrupt for MSG is disabled
void __attribute__((__interrupt__,no_auto_psv)) _DMA1Interrupt(void)
{
		IFS0bits.DMA1IF = 0;
				UARTstate &= RXCLR_STATUSFLAGS; //Clear all status flags
				UARTstate &= RXCLR_MODEFLAGS; // Clear all RX mode flags
				UARTstate |= RXMODE_CMD; // Put RX back in mode to receive commands	
				rxBuffA[0] = 0;		
}

//DMA interrupt for extra long TX
void __attribute__((__interrupt__,no_auto_psv)) _DMA2Interrupt(void)
{	
	uInt16 Length;
	if((UARTstate & TXMODE_INTS) == TXMODE_INTS)
	{
		if(txLengthRemaining * 2 >= TX_BUFF_SZ)// Extra long transmit need to use interrupt
		{
			Length = TX_BUFF_SZ>>1; 
			IEC1bits.DMA2IE = 1;
			SRbits.IPL = 7; //Mask out all other interrupts
		}
		else //remaining transmission will fit in this buffer
		{
			Length = txLengthRemaining; 
			IEC1bits.DMA2IE = 0; // Don't need to interrupt any more
			SRbits.IPL = 0; //Allow all interrupts	
			UARTstate &= ~TXMODE_INTS;		
		}		 		 
		for(loopIndex = 0; loopIndex < Length; loopIndex++)
		{
			txBuffA[loopIndex] = txIntData[loopIndex]<<8;
			txBuffA[loopIndex+1] = txIntData[loopIndex]&0x00FF;
		}	
		txLengthRemaining -= Length;
		DMA2CNT = Length - 1;
		IFS1bits.DMA2IF = 0;//Clear DMA2 interrupt flag 
		DMA2CONbits.CHEN = 1;// Enable DMA2 Channel	
		DMA2REQbits.FORCE = 1;// Manual mode: Kick-start the 1st transfer
	}
	if((UARTstate & TXMODE_CHARS) == TXMODE_CHARS)
	{
		if(txLengthRemaining < TX_BUFF_SZ)
		{
			Length = txLengthRemaining; 
			IEC1bits.DMA2IE = 0;
			SRbits.IPL = 0; 			 
		}
		else
		{
			Length = TX_BUFF_SZ;	
		}		 		 
		for(loopIndex = 0; loopIndex < Length; loopIndex++)
		{
			txBuffA[loopIndex] = txCharData[loopIndex];
		}	
		txLengthRemaining -= Length;
		DMA2CNT = Length - 1;
		IFS1bits.DMA2IF = 0;//Clear DMA2 interrupt flag 
		DMA2CONbits.CHEN = 1;// Enable DMA2 Channel	
		DMA2REQbits.FORCE = 1;// Manual mode: Kick-start the 1st transfer	
	}
}



