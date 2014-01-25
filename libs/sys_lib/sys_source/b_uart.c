/****************************************************************************
   CREATED BY: 	Stillbright Managment LLC
*					Copyright 2008
*                                                                           
*   FILE:           b_uart.c  (No DMA)                                              
*                                                                           
*   DESCRIPTION:    Source Code for non DMA char based uart routines which implements 
					the definitions in b_uart.h       
*                                                                           
*   REVISION:   	v1.005                                                      
*   Aug 20 2008	-	Created
*	3/9/2012	-	Made two different uart h files.  One which is  char based and one  
*					which is binary based. There are two different ssource files for the 
*					b_uart.h file one that uses DMA and this one which does not.
****************************************************************************/
#include <string.h>                     // String and buffer processing definitions
#include <b_uart.h>
#include <stdio.h>
#include "globals.h"
#include "serial.h"                  // Communication interface definitions

uInt16 delay = 0, jkTest = 0, UARTResetDelay =11;   // Status code definitions
long 	gblBaud; 	// global variable to hold baud rate
uChar 	receiveBuff;		// Serial port data
uChar	*txBuff,	
		*rxBuff,	
		lowByte,	//Flag indicating where next byte goes in uInt16
		unitID = DEFAULT_ID;	//= 100	
uInt16  *fileBuff; //Pointer to int data to be stored
		
int 	TypeOfDeLimit;		//Var to hold delimiting char between numbers.
uInt16 	*IntsBuffer;  // Pointer to hold Int array for transmission
		
uChar  	
		uartMsgBuff[RX_MSG_SZ], // Buffer to hold command
		rxData[RX_BUFF_SZ],   
    	txreceiveBuff[TX_BUFF_SZ],   //   "     "  transmit  "     "
		txAppBuff[TX_BUFF_SZ];
volatile uInt16
	msgIndex = 0,		//Index for uartMsgBuffer
    rxISRIndex = 0,           // Index for Rx buffer access by ISR
    rxAppIndex = 0,           // Index for Rx buffer access by application
    txAppIndex = 0,           //   "    "  Tx   "      "    "  application    
    txISRIndex = 0;           //   "    "  Tx   "      "    "  ISR
    
	 		//What stage of a message reception is the porgram in.
char   rxIndex = 0;	//number of bytes received
uInt16
	// Change rxPageMaker when wanting to receive new msg while working on old 
	// msg
	rxPageMarker = 0, 	// Use this to allow two messages to exist 
	rxFileLength = 0,	// Length of File to receive;
	txType = 0, //Flag that allows transmisson or chars ints floats or common delimited
	rxMode = 0, //Flag to indicates if RX is in command or file mode.
	rxStatus = 0;
    
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
void InitUART2(uChar UnitID, long BaudRate, uInt16 Timeout)
{
   	int iBaud;
   	gblBaud = BaudRate;
   	// This is an EXAMPLE, so brutal typing goes into explaining all bit sets
	// The HPC16 board has a DB9 connector wired to UART2, so we will
	// be configuring this port only

	// configure U2MODE

	// Load a value into Baud Rate Generator.  Example is for 9600.
	// See section 19.3.1 of datasheet.
	//  U2BRG = (37M/(16*9600))-1
	iBaud = (gblFcy/(16*gblBaud))-1;
	
	//  U2BRG = 240
	U2BRG = 41;	// 36 Fcy, 57,600 Baud

	//Load all values in for U1STA SFR
	

	IPC7 = 0x4400;	// Mid Range Interrupt Priority level, no urgent reason

	IFS1bits.U2TXIF = 0;	// Clear the Transmit Interrupt Flag
	IEC1bits.U2TXIE = 1;	// Enable Transmit Interrupts
	IFS1bits.U2RXIF = 0;	// Clear the Recieve Interrupt Flag
	IEC1bits.U2RXIE = 1;	// Enable Recieve Interrupts
	U2STAbits.UTXISEL1 = 1;	//Bit15(13) Int FIRST HALF when last char into TXREG
	U2MODEbits.UARTEN = 1;	// And turn the peripheral on
	U2STAbits.UTXEN = 1;
	U2STAbits.URXISEL1 = 0;	
	txISRIndex = 0; 
	txAppIndex = 0;	
	txISRIndex = 0;
	txAppIndex = 0;
    txType = TX_NONE;
    rxMode = RX_CMDMODE;// Set system to receive commands
    
    if(Timeout < 10) // Make sure what ever comm delay user configures is larger than 10
	{
		UARTResetDelay = 10; // Used when sending or receive multi packet arrays.
	}
	else UARTResetDelay = Timeout;
 }

		
  /****************************************************************************
*   FUNCTION:       _U1TXInterrupt(void)                                    *
*                                                                           *
*   DESCRIPTION:    This function is the handler for the UART 1 Transmit    *
*                   interrupt, which is generated whenever the UART's       *
*                   Transmit Buffer is empty.  It checks to see whether     *
*                   more data is queued to send, and if so, loads the       *
*                   next available byte into the Transmit Buffer.  If       *
*                   no more data is left to send the routine turns off      *
*                   the Transmit interrupt.                                 *
*                                                                           *
*   PARAMETERS:     None                                                    *
*                                                                           *
*   RETURNS:        The function returns no value since it is an ISR.       *
*                                                                           *
*   REVISION:  0    v1.0                DATE:  1 October 2006               *
*       Original release.                                                   *
****************************************************************************/

void __attribute__((interrupt, auto_psv)) _U2TXInterrupt(void)
{
    //  Local Variables
    //if(txBuff == 0) return;
    char receiveBuff;   // receiveBuff to transmit to UART     
    uInt16 Index;  // Index of current slot in the global
                                        //   Transmit receiveBuff Buffer to process
    
    //  Load the next character into the UART
    
   	Index = txISRIndex;   // Work with a temporary copy of the
                                        //  buffer access index to avoid coherency                                   //   problems
	if(txType == TX_CHARS)
	{                                       
		while ((Index != txAppIndex) && !U2STAbits.UTXBF)
		{
	        receiveBuff = txreceiveBuff[Index++];                     
	        U2TXREG = receiveBuff;         
	        //Index &= (TX_BUFF_SZ - 1); // Perform a rapid modulo-COMM_TX_BUFF_SZ
	                                     //   calculation (assume power of 2)                        
		}
	}
	if(txType == TX_INTS)
	{    
	
		U2TXREG = IntsBuffer[Index]>>8;
		lowByte = 1;
		U2TXREG = IntsBuffer[Index++] & 0xFF;  
		lowByte = 0;
		__builtin_btg( (unsigned int *)&LATA, 7 ); //Blink light for test
	}		 
    
    txISRIndex = Index;   // Log the updated buffer access index
   	if(Index == txAppIndex) //All data sent
   	{
	   	DisableIntU2TX;
	   	txISRIndex = 0;
	   	txAppIndex =0;
	   	txType = TX_NONE;
	}
   	//  Clear the associated interrupt
    //  flag to complete the ISR    
   	IFS1bits.U2TXIF = 0;    
}

void WriteChar(uChar receiveBuff)
{
	U2TXREG = receiveBuff;
	//IFS1bits.U2TXIF = 0;  
	return;
}

void WriteChars(uChar *Buffer, uInt16 Length)
{	
	if((Length+txAppIndex) > (TX_BUFF_SZ - 30))
	{
		//ErrorFlags = ERR_TXOVRFLOW;
		return ;
	}
	if(txType != TX_NONE) return;// Busy transmitting other buffers
	uChar bIndex;
	DisableIntU1TX;		// Disable TX interrupt
	uInt16 dIndex = txAppIndex;
	uChar *chreceiveBuff = txreceiveBuff;		
	for(bIndex = 0;bIndex < Length;bIndex++)
	{
		if(dIndex + 1 != (TX_BUFF_SZ - 1)) //make sure message in not overwriting self
		{
			*chreceiveBuff++ = *Buffer++;
			dIndex++;
			//dIndex &= (TX_BUFF_SZ - 1);	//modulus wrap;
		}
	}
	txAppIndex = dIndex;
	!U2STAbits.UTXBF;	// Clear the buffer full flag in status register
	txType  = TX_CHARS;	
	IFS1bits.U2TXIF = 1;// Set the interrupt flag	
	EnableIntU2TX;		// Enable interrupt for flag to work	
	return;
}
	
void WriteInts(uInt16 *Buffer, int Length)
{
	if(txAppIndex > 0) return;// ErrorFlags = ERR_TXOVRFLOW;
	txISRIndex = 0;
	IntsBuffer = Buffer;
	txAppIndex = Length;
	!U2STAbits.UTXBF;	// Clear the buffer full flag in status register
	txType  = TX_INTS;	
	IFS1bits.U2TXIF = 1;// Set the interrupt flag	
	EnableIntU2TX;		// Enable interrupt for flag to work
	lowByte = 0;
	return;
	__builtin_btg( (unsigned int *)&LATA, 6 );
	
}

void ReadInts(uInt16 *Buffer, uInt16 Length)
{
	CheckUART(10); // Delay RX reset for 40mSec
	rxFileLength = Length;
	fileBuff = Buffer;
	rxMode = RX_INTS;
	rxISRIndex = 0;
	lowByte = 0;
	return;	
}


void ReadChars(uChar *Buffer, uInt16 Length)
{
	CheckUART(6); // Delay RX reset for 50mSec
	rxFileLength = Length;
	rxBuff = Buffer;
	rxMode = RX_CHARS;
	rxISRIndex = 0;
	return;	
}  


	
 /**********************************************************
*   FUNCTION:   CheckRX(int Delay)                                    
*	
*	Resets the receive system after Delay * 10mSec Time
*************************************************************/
void ResetMsgBuff(void)
{
    msgIndex = 0; //reset message Index
  	uartMsgBuff[msgIndex] = 0; //clear command
  	
}
void CheckUART(int Delay)
{
	delay += Delay;
	if(rxStatus > UART_IDLE)
	{
		LATA |= 0x20;
		if(delay <= 0)
		{
			msgIndex = 0;
			rxAppIndex = 0;
		    rxISRIndex = 0; 
		    //rxreceiveBuff[0] = 0;
		    U2MODEbits.UARTEN = 1;
		    rxStatus =  UART_IDLE;
		    rxMode = RX_CMDMODE;
		    EnableIntU2RX;
		    IFS1bits.U2RXIF = 0;
			U2STAbits.OERR = 0;
			delay = 0;
			LATA &= ~0x60;
		}
		if(delay > 0) delay--;	
	}		
}
/****************************************************************************
*   FUNCTION:       _U1RXInterrupt(void)                                    *
*                                                                           *
*   DESCRIPTION:    This function is the handler for the Receive receiveBuff       *
*                   Ready interrupt for UART 1.  It reads the received      *
*                   data from the UART and stores it in the global          *
*                   Receive receiveBuff Buffer if there is room.                   *
*                                                                           *
*
*                                                        *
****************************************************************************/

void __attribute__((interrupt, auto_psv))_U2RXInterrupt(void)
{
	if(rxMode == RX_CMDMODE)//Ready to receive a command
    {
	   
	    while (U2STAbits.URXDA) // While data is available in the buffer
	    {    
		    receiveBuff = U2RXREG;
		   	//Continiue receiving data after ID has been checked
			if(rxStatus	== MSG_STARTED)
			{
		        if (msgIndex < RX_MSG_SZ)
		        {
		            //  Have room in the buffer so add the
		            //  new data to it and update the
		            //  associated buffer access index
		        
		            uartMsgBuff[msgIndex++] = receiveBuff;
		            uartMsgBuff[msgIndex + 1] = '\0'; //clear the next byte   
		            ErrorFlags |= ErrorFlags * 2;      
		        }
		        if(msgIndex >= RX_MSG_SZ) 
		        {		
			        //U2MODEbits.UARTEN = 0;
			        MachineState |= s_MSGRDY;
			        rxStatus = RX_MSGHOLDING; // Do not add more to buffer
		        	//U2MODEbits.UARTEN = 1;
		        	ErrorFlags |= ErrorFlags * 2;  
			    }
		 		
		 	}
			else if(rxStatus == UART_IDLE) // If RX is idle check ID to see if it's 4 us
			{
				if(receiveBuff == unitID)
				{
					
					rxStatus = MSG_STARTED;
					CheckUART(2); // Delay RX reset for 10mSec
					msgIndex = 0; 	//reset index used in rxInterrupt
					ErrorFlags = 1;						
					return;

					
				} 
				IFS0bits.U1RXIF = 0; //Reset RX interrupt Flag
				rxISRIndex = 0;
				return;
			}		 			       	
	       	else if(rxStatus == RX_MSGHOLDING) //Don't start another msg before processing this one
	       	{
		    	receiveBuff = U2RXREG; // keep UART RX reg clear
		    	receiveBuff = 0; // Clear receiveBuff
		       	IFS1bits.U2RXIF = 0;
		       	return;
		       	 //already hava a message
		    }        
	    }
	}    
    else if(rxMode == RX_INT_ARRAY_MODE)//for receiving word arrays
    {	
	    while (U2STAbits.URXDA) // While chars are in the buffer
		{     
			receiveBuff = U2RXREG;	
		    ///T5CharDelay(150);
			if(rxStatus != RX_BUSY) 
			{
				rxStatus = RX_BUSY;
				rxISRIndex = 0;
			}
				    
		    if(rxISRIndex < rxFileLength)
		    {
			    
			    if(lowByte == 1)
			    {
			    	fileBuff[rxISRIndex++] += receiveBuff;
			    	lowByte = 0;

			    }
			    else
			    {
			    	fileBuff[rxISRIndex] = receiveBuff<<8;
			    	lowByte = 1;	    
			    }
  			    
			}
			else if(rxISRIndex >= rxFileLength)
			{
				
				IFS1bits.U2RXIF = 0;
				MachineState = s_FILERDY;
			}	
		}
	}
	if(rxMode == RX_CHARS)//for receiving word arrays
   	{
	    while (U2STAbits.URXDA) // While chars are in the buffer
		{     
			receiveBuff = U2RXREG;	
		    ///T5CharDelay(150);
			if(rxStatus != RX_BUSY) 
			{
				rxStatus = RX_BUSY;
				LATA |= 0x40;
				rxISRIndex = 0;
			}			    
		    if(rxISRIndex < rxFileLength)
		    {
				rxBuff[rxISRIndex++] = receiveBuff;
			}
			if(rxISRIndex >= rxFileLength)
			{
				rxFileLength = 0;
				//LATA &= ~0x40;
				IFS1bits.U2RXIF = 0;
				MachineState = s_STRINGRDY; //Do not change state for chars
				__builtin_btg( (unsigned int *)&LATA, 7 );
			}	    	
	    	
	    }
	}			
	    //  Clear the Rx receiveBuff Interrupt Flag to
	    //  finish processing the interrupt	   	  
	IFS1bits.U2RXIF = 0; 
	
 
    
};

