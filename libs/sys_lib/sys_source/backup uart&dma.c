/****************************************************************************
   CREATED BY: 	Stillbright Managment LLC
*					Copyright 2010
*                                                                           
*   FILE:           serial_dma33.c                                                
*                                                                           
*   DESCRIPTION:    Source Code uart routines using PIC33 DMA capabilities and implements 
					the definitions in serial.h       
*                                                                           
*   REVISION:   	v1.005                                                      
*   CREATED:		Aug 20 2010   
****************************************************************************/
#include <string.h>                     // String and buffer processing definitions
#include <uart.h>
#include <stdio.h>
#include "sysglobals.h"
#include "uart.h" //Function definitions and global flags 
#include "protocols.h"
//********************* file scope variables ********************
uChar	  msgTimeoutFlag2 = 0;
uInt16 msgTimeoutFlag=0;
//uChar 	uartMsgBuff[RX_MSG_SZ]__attribute__((space(dma)));

uChar	rxBuffA[RX_BUFF_SZ] __attribute__((space(dma)));  
uChar	rxBuffB[RX_BUFF_SZ] __attribute__((space(dma)));
uChar   txBuffA[TX_BUFF_SZ] __attribute__((space(dma))); 	
uChar   txBuffB[TX_BUFF_SZ] __attribute__((space(dma))); 
uChar	unitID = 100,	
		bufferSelect = 0,
		PageMarker = 0, 	// Tracks number of buffers to be sent 
		delimiter;			//Var to hold delimiting char between numbers.
//int		uartFailSafe = 0;  //Recheck occasionally to make sure that your in cmd mode
uInt16  delay = 0, 		
		loopIndex;
volatile uInt16	UARTstate;		
long 	gblBaud; 		// variable to hold baud rate
float 	time4Byte;  	//Holds time in mSec to transmit 1 Byta at baud rate 

//******************** flags and variables for transmit **********
uChar	*txCharData = NULL,  	//Pointer to  CHAR data to be transmitted.
		txTimeout;
		//timer for clearing tx Buffer
uInt16 	*txIntData,		//Pointer to  INT data to be transmitted.
		txDataIndex,	//Holds index to data for multi packet transmits
		txTotalLength,	//Overall number of registers to be transmitted
		txLengthRemaining; //number of bytes remaining.
float	*txFloatData;
//***************** flags and variables for receive **********

uChar	*rxCharData, //Pointer to hold application buffer of chars
		rxStatus,
		MsgTimeout = 0, //Timout used when receiving a message
		rxTimeout = 10; //timer for clearing rx Buffer
uInt16	*rxIntData,		
		rxDataIndex,	//Holds index to data for multi packet transmits
		dma1staBaseAddress, //Represents zero index of bytes received
		msgLength2Capture,		//Length of message to capture
		msgLengthCaptured; 	//Have we got all of the message
		
long	rxArray2Capture,  //number of bytes in the array to capture
		rxArrayCaptured; //number of bytes remaining.
		
float 	*rxFloatData;
//************** MARKED FOR DELEATION **********************
uChar 	receiveBuff;		// takes data from U2RXREG
//uChar	msgBuff[RX_MSG_SZ];	//Need to Delete	
uChar	charData[1024]; //Need to move to DSP
uInt16  intData[512];	//Need to move to DSP
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
void InitComm(uChar UnitID, float BaudRate)
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
	DMA1CNT = 101 -1; 	// interrupt after 100 bytes . 
	msgLength2Capture = 30; // resize this later to see if total msg received	
	IFS0bits.DMA1IF = 0; 	// Clear DMA interrupt
	IEC0bits.DMA1IE = 0; 	// Disable interrupt. Let checkUART() check.
	   
	
    //Configure DMA2 For to transmit 
    DMA2CONbits.MODE = 1;  // Continuous, Post-Increment, Ping Pong
    DMA2CONbits.DIR = 1; //Write from SRAM to periphrial
    DMA2CNT = TX_BUFF_SZ-1; // Number of chars befor DMA interrupt
	DMA2REQ = 0x001F; // Select UART2 Transmitter
	DMA2PAD = (volatile unsigned int) &U2TXREG;
	DMA2CONbits.SIZE = 1;  //1 = byte transfers
	DMA2STA = __builtin_dmaoffset(txBuffA);
	DMA2STB = __builtin_dmaoffset(txBuffB);
	DMA2CONbits.CHEN = 0; 	
	IFS1bits.DMA2IF = 0; // Clear DMA Interrupt Flag
	IEC1bits.DMA2IE = 0; // Enable DMA interrupt only when you have something to send
	rxBuffA[0] = 0; // UnitID byte should always be empty

//	Set Msg timeout to be 3 times the time to receive a Msg
	BaudRate = 1/(float)(gblBaud/1000);	
	BaudRate = (BaudRate * 10 * RX_MSG_SZ * 3);
	MsgTimeout = BaudRate;
	for(loopIndex = 0; loopIndex<=20;loopIndex++)rxBuffA[loopIndex]=0;
	unitID = UnitID;
}
void SetMsgTimeout(uChar mSecTimeout)
{
	long BaudRate;
	BaudRate = 1/(gblBaud/1000);	
	BaudRate = (BaudRate * 10 * RX_MSG_SZ * 3);
	if(mSecTimeout < (uChar)BaudRate) // Make sure what ever comm delay user configures is larger than min
	{
		return;
	}
	else if(mSecTimeout > 40)
	{
		 return;
	}
	else MsgTimeout = mSecTimeout;
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
	uart without blocking other MCU opperation.  All cases
	
*/
void CheckUART(void)
{
	static int resetDelay;
	static uChar msgByteCount; 
	
	
	if((UARTstate & RXMODE_CMD) == RXMODE_CMD)
	{
		if(rxBuffA[0] != 0) // Check for messages
		{
			#if PROTOCOL == RIOTECH
			if ((rxBuffA[0] == unitID) && IFS0bits.DMA1IF)// This is for me
			{
				ProcessSerialMsg();
				ResetRX();	
				//MachineState |= s_MSGRDY; //Tell state machine msg is ready	
				return;	
			}
			else 
			#endif
			if (rxBuffA[0] == unitID) // give time to finish command
			{	
				if((UARTstate & RXSTATUS_MSGSTARTED) != RXSTATUS_MSGSTARTED)
				{
					resetDelay = MsgTimeout;
					msgLength2Capture = BytesPerMsgType(rxBuffA[1]);//Lookup Length of msg type
					if(msgLength2Capture >= 999)
					{
						ResetRX();//If 999 then msgType is corrupted
						return;
					}
					if((DMA1STA - dma1staBaseAddress) >= msgLength2Capture)//If we have complete msg
					{
						ProcessSerialMsg();
						ResetRX();
						return;
					}
					else
					UARTstate |= RXSTATUS_MSGSTARTED;		
					msgTimeoutFlag = 1;
					return;
				}				
			}		
			else //If ID isn't for me, reset ID byte
			{
				DMA1CONbits.CHEN = 0;  //Toggle DMA1 to reset	
				rxBuffA[0] = 0;	
				DMA1CONbits.CHEN = 1;
			}	
		}
	}	
			
	if((UARTstate & RXSTATUS_MSGSTARTED) == RXSTATUS_MSGSTARTED)
	{
		/* old RIOTECH protocol
		if ((rxBuffA[0] == unitID) && (IFS0bits.DMA1IF))// This is for me
		{
			msgTimeoutFlag2++;			
			ProcessSerialMsg();
			ResetRX();
			//MachineState |= s_MSGRDY; //Tell state machine msg is ready
		}*/
		if((DMA1STA - dma1staBaseAddress)>=msgLength2Capture)//If we have complete msg
		{
			ProcessSerialMsg();
			ResetRX();
			return;
		}		
		else
		{
			__builtin_btg( (unsigned int *)&LATA, 2 );	//blink lite
			if(msgTimeoutFlag++ > MsgTimeout)
			{					
				ResetRX();				
				msgTimeoutFlag = 1; //log error
			}
		}
	}	
	if((UARTstate & TXMODE_CHARS) == TXMODE_CHARS)
	{
		WriteChars(txCharData, txLengthRemaining);
	}
	if((UARTstate & RXMODE_CHARS) == RXMODE_CHARS)
	{
		ReadChars(rxCharData, rxArrayCaptured);
	}	
	if((UARTstate & RXSTATUS_RXARRAY) == RXSTATUS_RXARRAY)//for receiving long files
	{
		resetDelay --;	
	}				
	if((UARTstate & TXMODE_INTS_CD) == TXMODE_INTS_CD)
	{	
		resetDelay --;
	} 		
	resetDelay --;			
	if(resetDelay <= 0)
	{
		//resetDelay will be set to 10 when message is started
		//so that retrys and other commands can occure is rx is quite
		//Occasionally Reset RX;
		resetDelay = 500;		
		ResetRX();
	}		
}

	
void ResetRX(void) // Puts RX back into command mode
{	

	DMA1CONbits.CHEN = 0;  //Toggle DMA1 to reset	
	//DMA1STA = __builtin_dmaoffset(rxBuffA);	
	//IE0bits.DMA1IE = 0; // disable DMA interrupt let app check	
	UARTstate &= RXCLR_STATUSFLAGS; //Clear all status flags
	UARTstate &= RXCLR_MODEFLAGS; // Clear all RX mode flags
	UARTstate |= RXMODE_CMD; // Put RX back in mode to receive commands
	DMA1CONbits.CHEN = 1; 	// Enable DMA1 Channel for messages	
	IFS0bits.DMA1IF = 0; // Clear DMA Interrupt Flag.
	DMA1CNT = RX_MSG_SZ -1; 	// interrupt after RX_MSG_SZ bytes .
	rxBuffA[0] = 0;
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
	
	if(Buffer == NULL) return; //check for null pointers
	txCharData = Buffer; // Tells UART state machine from where to get data		
	if(Length >= TX_BUFF_SZ) 
	{
		if(txLengthRemaining == 0)
		{
			txLengthRemaining = Length; //Tell app about total length	
			bufferSelect = 0; // Tell UART state machine which buffer to start with
		}			
		UARTstate = TXMODE_CHARS;//Tell UART state machine there will be more to transmit
		Length = TX_BUFF_SZ;			
		if(bufferSelect == 0)
		{
			for(loopIndex = 0; loopIndex < Length; loopIndex++)
			{
				rxBuffA[loopIndex] = Buffer[loopIndex];
			}
			DMA2STA = __builtin_dmaoffset(rxBuffA);			
			txCharData = &Buffer[txDataIndex + loopIndex];	
			bufferSelect ^= 1; // Tell application to switch buffers
		}
		else
		{				
			for(loopIndex = 0; loopIndex < Length; loopIndex++)
			{
				txBuffA[loopIndex] = Buffer[loopIndex];
			}
			txCharData = &Buffer[txDataIndex + loopIndex];
			DMA2STA = __builtin_dmaoffset(txBuffA);	
			bufferSelect ^= 1; // Tell UART state machine to load txBuffA next			
		}
		txLengthRemaining -= Length;				
	}
	else 
	{	
		for(loopIndex = 0; loopIndex < Length; loopIndex++)
		{
			rxBuffA[loopIndex] = Buffer[loopIndex];
		}
		if(txLengthRemaining != 0) //If UART was put in TXMODE_CHARS mode then
		{
			UARTstate &= ~TXMODE_CHARS; //Remove TXMODE_CHARS flag
			txLengthRemaining = 0;
		}
	}
	DMA2CNT = Length - 1;
	txTimeout += Length * time4Byte; // Delay reset 
	IEC1bits.DMA2IE = 1; // Enable DMA interrupt
	DMA2CONbits.CHEN = 1;// Enable DMA2 Channel	
	DMA2REQbits.FORCE = 1;// Manual mode: Kick-start the 1st transfer	
}

void WriteInts(uInt16 *Buffer, int Length)
{
 	
	
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
			//IFS2bits.DMA3IF = 0; // Clear DMA Interrupt Flag
		}
		else 
		{
			DMA1CNT = RX_BUFF_SZ - 1;
			rxArrayCaptured = RX_BUFF_SZ;//after interrupt
		}	
		IFS0bits.DMA1IF = 0; // Clear DMA Interrupt Flag					
		IEC0bits.DMA1IE = 1; 	// Enable DMA3 interrupts
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
			
			//IFS2bits.DMA3IF = 0; // Clear DMA Interrupt Flag
			//IEC2bits.DMA3IE = 0; // disable DMA interrupt	
			//DMA3CONbits.CHEN = 0; 	// Disable RX DMA
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


///DMA interrupt for MSG is disabled
void __attribute__((__interrupt__)) _DMA1Interrupt(void)
{
		IFS0bits.DMA1IF = 0;
				UARTstate &= RXCLR_STATUSFLAGS; //Clear all status flags
				UARTstate &= RXCLR_MODEFLAGS; // Clear all RX mode flags
				UARTstate |= RXMODE_CMD; // Put RX back in mode to receive commands	
				rxBuffA[0] = 0;		
	//Let State machine capture interrupt flag when in msg mode
	//UARTstate = RX_CHARS; //Tell state machine you have received something	
	/*
	if( rxArrayCaptured >= RX_BUFF_SZ) // no need to switch buffer
	{
		if(bufferSelect == 0)
		{
			DMA1STA = __builtin_dmaoffset(rxBuffA); // Change buffer to load data into
		}
		else DMA1STA = __builtin_dmaoffset(rxBuffB);
		
	}

	DMA1CNT = rxArray2Capture - rxArrayCaptured; //DMA3CNT;
	IFS0bits.DMA1IF = 0; // Clear DMA Interrupt Flag
	*/	
}

//DMA interrupt for TX
void __attribute__((__interrupt__)) _DMA2Interrupt(void)
{	
	if(txLengthRemaining < 1) 
	{
		IFS1bits.DMA2IF = 0;// Clear the DMA1 Interrupt Flag
		bufferSelect = 0;
		//DMA2CONbits.CHEN = 0; 	// Reset DMA2 
		//DMA2CONbits.CHEN = 1; 
		IEC1bits.DMA2IE = 0; // Enable DMA interrupt
	}
	txType = 66;
}
//DMA interrupt for RX
void __attribute__((__interrupt__)) _DMA3Interrupt(void)
{
	UARTstate = RXMODE_CHARS; //Tell state machine you have received something	
	if( rxArrayCaptured >= RX_BUFF_SZ) // no need to switch buffer
	{
		if(bufferSelect == 0)
		{
			DMA3STA = __builtin_dmaoffset(txBuffA); // Change buffer to load data into
		}
		else DMA3STA = __builtin_dmaoffset(rxBuffA);
		
	}

	DMA3CNT = rxArray2Capture - rxArrayCaptured; //DMA3CNT;
	IFS2bits.DMA3IF = 0; // Clear DMA Interrupt Flag
		
}


