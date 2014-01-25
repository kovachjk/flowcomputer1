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
                    // String and buffer processing definitions
#include "../uarts.h"


//#include "serial.h"                  // Communication interface definitions


uInt delay = 0, uartTrash = 0, UARTResetDelay =11;   // Status code definitions
long 	gblBaud; 	// global variable to hold baud rate
char U1Buffer[U1_BUFFSZ];
uChar	*ptrU1TXBuff,
	*ptrU1RXBuff,
	lowByte;	//Flag indicating where next byte goes in uInt
        
uInt    *fileBuff; //Pointer to int data to be stored
		
int 	TypeOfDeLimit;		//Var to hold delimiting char between numbers.
uInt 	*IntsBuffer;  // Pointer to hold Int array for transmission
		
   // rxCmdBuff[CMD_BUFF_SZ],//Used to capture commands from MB Master mbTXBuff is in modbus.c
uChar numMBBytesLeftToReceive = 0; //if more then 8 byts neaded for command.
    
    //screenBuff[SCREEN_BUFF_SZ];   //   "     "  transmit  "     "

volatile uInt
    rxISRIndex = 0,           // Index for Rx buffer access by ISR
    u1RXIndex = 0,           // Index for Rx buffer access by application
    u2RXIndex = 0,           // Index for Rx buffer access by application
    txAppIndex = 0,           //   "    "  Tx   "      "    "  application    
    txISRIndex = 0;           //   "    "  Tx   "      "    "  ISR
    

uShort
	// Change rxPageMaker when wanting to receive new msg while working on old 
	// msg
	rxPageMarker = 0, 	// Use this to allow two messages to exist 
	rxFileLength = 0,	// Length of File to receive;
        u1TXFileLength = 0,

	u1TXStatus = 0,     //Flag that allows transmisson or chars ints floats or common delimited
        u1TXMode = 0,
        u2TXStatus = 0,
        u2TXMode = 0,
	u1RXStatus = 0,
        u1RXMode = 0,
        u2RXStatus,
        u2RXMode;



uInt ReadMBMasterU1()
{
    
}
/****************************************************************************
*   FUNCTION:       ReadU1(char*)                                    *
*                                                                           *
*   DESCRIPTION:    Moves data from RX recieve registers and
 *                  null terminates the array
*                                                                           *
*   PARAMETERS:     Pointer to char buffer                                            *
*                                                                           *
*   RETURNS:        pointer to the same char buffer parameter.       *
*                                                                           *
*   REVISION:  0    v1.0                DATE:  1 October 2012            *
*       Original release.                                                   *
****************************************************************************/
char* ReadStringU1(char *buffPtr)
{
    uShort msgIndex = 0;
    while (U1STAbits.URXDA) // While data is available in the buffer
    {
        buffPtr[msgIndex++]=U1RXREG;
    }
    buffPtr[msgIndex]=0x00;//*/
    //uart.if = 0; //Clear flag
    return buffPtr;
    
}
uInt InitMBSlaveU1(uInt BaudRate, char MasterID)
{
    
}
/****************************************************************************
*   FUNCTION:       CommInit(Uint8 ui8Port, uInt ui16BaudRate,            *
*                            uInt ui16Parity, uInt ui16StopBits)        *
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
uInt InitUART1(uInt BaudRate)
{
    U1BRG =  (PBCLK/(16*BaudRate))-1;
    U1ASTAbits.UTXEN = 1;
    U1ASTAbits.URXEN = 1;
    U1MODEbits.ON = 1;
    return PBCLK/(16*(U1BRG + 1));
}

void ResetMBU1(char *CmdBuffer)
{
    u1RXIndex = 0;
    CmdBuffer[0] = NULL;
    CmdBuffer[1] = NULL;
    u1RXStatus == RX_IDLE;
}
/****************************************************************************
*   FUNCTION:       ReadMBMasterU1(void)                                   *
*                                                                           *
*   DESCRIPTION:    Reads U1 looking for the possiblility of a Modbus
 *                  command.
*                                                                           *
*   PARAMETERS:     cmdBuffer - The uChar array holding the command
 *                                                             *
*                                                                           *
*   RETURNS:        zero if nither an ESC char or MasterID is found.  The tells
 *              the system that no action is required. The system
 *              will reset the uart if 
 *  
 *                  1 if MasterID found but in row are found then returns 1 *
*                                                                           *
*   REVISION:  0    v1.0                DATE:  12/9/2012            *
                                                   *
****************************************************************************/
uShort ReadU1AsSlave(char * CmdBuffer, uShort SysStatus)
{
    if(SysStatus == RX_IDLE)//This is because sys main may have timed out leaving the UART is an old state
    {
        u1RXStatus = RX_IDLE;
        u1RXIndex = 0;
    }
    //The ID and cmd was correct but the cmd needs more bytes
    if(u1RXStatus == RXMB_WAITING)//0x0010
    {
        while (U1STAbits.URXDA) // While data is available in the buffer
        {
           CmdBuffer[u1RXIndex++] = U1RXREG;
        }
        
        if(numMBBytesLeftToReceive == 0)
        {
            //We would only have a non zero numMBBytesLeftToReceive if a cmd
            // had run and was requesting more bytes, therefore
            //UART has not accumlated enough bytes to run any cmd.
            if(u1RXIndex >= MIN_MB_MSG_SZ) 
            {
                numMBBytesLeftToReceive = ProcessMBCommand(CmdBuffer,0,MasterID);
                if(numMBBytesLeftToReceive > 0)//Still need more bytes
                {
                    u1RXStatus = RXMB_WAITING;
                    return RXMB_WAITING;   
                }
                u1RXStatus = RX_IDLE;
                return RX_IDLE;//Stay in command mode

            }
            //MB cmd was processed and system is now ready for another.
            //Errors are handled in the MB module.
            else 
            {
                u1RXStatus = RXMB_WAITING;
                return RXMB_WAITING;//Stay in command mode
            }
        }
        //MB cmd has been run and is requesting more bytes, ck and see if we have them
        if(u1RXIndex < numMBBytesLeftToReceive)
        {
           return RXMB_WAITING; 
        }
        else
        {
            ProcessMBCommand(CmdBuffer,u1RXIndex,MasterID);
            numMBBytesLeftToReceive = 0;
            return RX_IDLE;//RXMB_WAITING
        }
    }
    //We weren't waiting on a cmd so check if we have either an ESC char or the MasterID
    else if(u1RXStatus == RX_IDLE)
    {
        u1RXIndex = 0;
        // Does first byte matches unit ID
        CmdBuffer[u1RXIndex] = U1RXREG;
        if(CmdBuffer[u1RXIndex] == MasterID)
        {   
            u1RXIndex = 1;
            //We know we have one byte do we have more
            while (U1STAbits.URXDA) // While data is available in the buffer
            {
               CmdBuffer[u1RXIndex++] = U1RXREG;
            }
            if(u1RXIndex >= MIN_MB_MSG_SZ)
            {
                numMBBytesLeftToReceive = ProcessMBCommand(CmdBuffer,0,MasterID);
                if(numMBBytesLeftToReceive > 0)
                {
                    u1RXStatus = RXMB_WAITING;
                    return RXMB_WAITING;   
                }
                u1RXStatus = RX_IDLE;
                return RX_IDLE;//Stay in command mode
            }
            u1RXStatus = RXMB_WAITING;
            return RXMB_WAITING;//Stay in command mode
        }
        if(CmdBuffer[0] == htESC)
        {
            u1RXIndex = 1;
            
            //We know we have one byte do we have more
            while (U1STAbits.URXDA) // While data is available in the buffer
            {
                CmdBuffer[u1RXIndex++] = U1RXREG;
            } 
            if(u1RXIndex > 1)//if we did already get another byte, check for ESC
            {
                if(CmdBuffer[1] == htESC)
                {
                  u1RXStatus = RXMENU_ACTIVE; 
                  return RXMENU_ACTIVE;
                }
                else u1RXStatus = RX_IDLE;
            }
            else //if we got one ESC, go back and see if next char is ESC
            {
                u1RXStatus = RXMENU_STARTING;// We may be in menu mode
            }
        }
    }
    if(u1RXStatus == RXMENU_ACTIVE)//0x0080
    {
        while (U1STAbits.URXDA) // While data is available in the buffer
        {
            CmdBuffer[u1RXIndex++] = U1RXREG;
        }
        u1RXIndex = 0;
        //Run menu
        if(1)
        {
            return RXMENU_ACTIVE;//0x0080
        }
        if(0)//if menu returns an exit command
        {
            return RX_IDLE;
        }
    }    
    if(u1RXStatus == RXMENU_STARTING)
    {
        while (U1STAbits.URXDA) // While data is available in the buffer
        {
            CmdBuffer[u1RXIndex++] = U1RXREG;
        }
        if(u1RXIndex <= 1) return RXMENU_STARTING;
        if(CmdBuffer[1] == htESC)//The only way menu can start is if first two bytes are esc
        {
            u1RXIndex = 0;
            u1RXStatus = RXMENU_ACTIVE;
            return RXMENU_ACTIVE;
        }
        return RX_IDLE;
    }
    return 0;//1 if we need to change to menu mode
  
}
uChar WriteStringU1(uChar *cBuff)
{
    int index = 0;
      while(cBuff[index] != 0x00)
    {
        while(U1STAbits.UTXBF);
        U1TXREG = cBuff[index++];
    }
    //uart.if = 0; //Clear flag
    return cBuff[index];
}
/****************************************************************************
*   FUNCTION:       ReadU1(char*)                                    *
*                                                                           *
*   DESCRIPTION:    Moves data from RX recieve registers and 
 *                  null terminates the array 
*                                                                           *
*   PARAMETERS:     Pointer to char buffer                                            *
*                                                                           *
*   RETURNS:        pointer to the same char buffer parameter.       *
*                                                                           *
*   REVISION:  0    v1.0                DATE:  1 October 2012            *
*       Original release.                                                   *
****************************************************************************/
char* ReadStringU2(char *buffPtr)
{
    int serialIndex = 0;
    while (U1STAbits.URXDA) // While data is available in the buffer
    {
        buffPtr[serialIndex++]=U2RXREG;
    }
    buffPtr[serialIndex]=0x00;//*/
    //uart.if = 0; //Clear flag
    return buffPtr;
    
}
  /****************************************************************************
*   FUNCTION:       TerminalOutU1(char)                                    *
*                                                                           *
*   DESCRIPTION:    This function takes a string ment for display
   *                on a embedded LCD screen and adds terminal code
   *                to the front of the string which clears the screen 
   *                the previous message *
*                                                                           *
*   PARAMETERS:     None                                                    *
*                                                                           *
*   RETURNS:        The function returns no value since it is an ISR.       *
*                                                                           *
*   REVISION:  0    v1.0                DATE:  1 October 2012            *
*       Original release.                                                   *
****************************************************************************/
void WriteTerminalU1(char *buffPtr)
{
    int index = 0;
    static const char scr1StrLn1[] ="\x1B[2J\x1B[H";
    while(scr1StrLn1[index] != 0x00)
    {
        while(U1STAbits.UTXBF);
        U1TXREG = scr1StrLn1[index++];
    }
     while(*buffPtr != 0x00)
    {
        switch(buffPtr[index])
        {
            case 0x08:
                break;
            default:
                break;
        }
        while(U1STAbits.UTXBF);
        U1TXREG = *buffPtr++;
    }     
}
void WriteCharU1(uChar receiveBuff)
{
	U1TXREG = receiveBuff;
	//IFS1bits.U2TXIF = 0;

}
char WriteCharsU1(char *Buffer, uInt Length)
{
    uChar bIndex = 0;
    while(bIndex < Length)
    {
        while(U1STAbits.UTXBF);
        U1TXREG = (char)Buffer[bIndex++];

    }
    bIndex = 0;
    return 1;
    /*
    if(u1TXStatus == TXSTATUS_BUSY) return;// Busy transmitting other buffers
    
    IEC1bits.U2TXIE = 0;	// Disable TX interrupt
    uInt dIndex = txAppIndex;
    //uChar *chreceiveBuff = txreceiveBuff;
    for(bIndex = 0;bIndex < Length;bIndex++)
    {
            if(dIndex + 1 != (FILE_BUFF_SZ - 1)) //make sure message in not overwriting self
            {
                    //*chreceiveBuff++ = *Buffer++;
                    dIndex++;
                    //dIndex &= (TX_BUFF_SZ - 1);	//modulus wrap;
            }
    }
    txAppIndex = dIndex;
    +
    u1TXMode  = TXMODE_CHARS;
    IFS1bits.U2TXIF = 1;// Set the interrupt flag
    IEC1bits.U2TXIE = 1;// Enable interrupt for flag to work
    return;
*/
}
  /****************************************************************************
*   FUNCTION:       _U1TXInterrupt(void)                                    *
*                                                                           *
*   DESCRIPTION:    This function is the handler for the UART 2 Transmit    *
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
    /*
    //  Local Variables
    //if(txBuff == 0) return;
    char receiveBuff;   // receiveBuff to transmit to UART     
    uInt Index;  // Index of current slot in the global
                                        //   Transmit receiveBuff Buffer to process
    
    //  Load the next character into the UART
    
   	Index = txISRIndex;   // Work with a temporary copy of the
                                        //  buffer access index to avoid coherency                                   //   problems
	if(txType == TXTYPE_CHARS)
	{                                       
            while ((Index != txAppIndex) && !U2STAbits.UTXBF)
            {
                receiveBuff = txreceiveBuff[Index++];
                U2TXREG = receiveBuff;
                //Index &= (TX_BUFF_SZ - 1); // Perform a rapid modulo-COMM_TX_BUFF_SZ
                                             //   calculation (assume power of 2)
            }
	}
	if(txType == TXTYPE_INTS)
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
            IEC1bits.U2EIE = 1;
            txISRIndex = 0;
            txAppIndex =0;
            txType = TXTYPE_NONE;
	}
   	//  Clear the associated interrupt
    //  flag to complete the ISR    
   	IFS1bits.U2TXIF = 0;
  */
}


void WriteCharU2(uChar receiveBuff)
{
	U2TXREG = receiveBuff;
	//IFS1bits.U2TXIF = 0;  
	
}

void WriteCharsU2(uChar *Buffer, uInt Length)
{	/*
	if((Length+txAppIndex) > (TX_BUFF_SZ - 30))
	{
		//ErrorFlags = ERR_TXOVRFLOW;
		return ;
	}
	if(txType != TXTYPE_NONE) return;// Busy transmitting other buffers
	uChar bIndex;
	IEC1bits.U2TXIE = 0;	// Disable TX interrupt
	uInt dIndex = txAppIndex;
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
	txType  = TXTYPE_CHARS;
	IFS1bits.U2TXIF = 1;// Set the interrupt flag	
	IEC1bits.U2TXIE = 1;// Enable interrupt for flag to work
	return;
          * */
}
	
void WriteIntsU2(uInt *Buffer, int Length)
{
	if(txAppIndex > 0) return;// ErrorFlags = ERR_TXOVRFLOW;
	txISRIndex = 0;
	IntsBuffer = Buffer;
	txAppIndex = Length;
	!U2STAbits.UTXBF;	// Clear the buffer full flag in status register
	//txType  = TXTYPE_INTS;
	IFS1bits.U2TXIF = 1;// Set the interrupt flag	
	IEC1bits.U2EIE = 1;		// Enable interrupt for flag to work
	lowByte = 0;
	return;
	__builtin_btg( (unsigned int *)&LATA, 6 );
	
}

void ReadIntsU2(uInt *Buffer, uInt Length)
{
	CheckU2(10); // Delay RX reset for 40mSec
	rxFileLength = Length;
	fileBuff = Buffer;
	//u1RXState = u1RXState_INTS;
	rxISRIndex = 0;
	lowByte = 0;
	return;	
}


void ReadCharsU2(uChar *Buffer, uInt Length)
{
	//CheckUART2(6); // Delay RX reset for 50mSec
	rxFileLength = Length;
	u1RXMode = RXMODE_CHARS;
	rxISRIndex = 0;
	return;	
}  


	
 /**********************************************************
*   FUNCTION:   CheckRX(int Delay)                                    
*	
*	Resets the receive system after Delay * 10mSec Time
*************************************************************/
void ResetMsgBuffU2(void)
{
    //msgIndex = 0; //reset message Index
    //u2RXBuff[0] = 0; //clear command
  	
}


void CheckU2(int Delay)
{
	delay += Delay;
	if(u2RXStatus > RX_IDLE)
	{
		//LATA |= 0x20;
		if(delay <= 0)
		{
                    u1RXIndex = 0;
                    //rxAppIndex = 0;
		    rxISRIndex = 0; 
		    //rxreceiveBuff[0] = 0;
		    U2MODEbits.UARTEN = 1;
		    u2RXStatus =  RX_IDLE;
		    u2RXMode = RXMODE_CMD;
		    IEC1bits.U2RXIE = 1; ;
		    IFS1bits.U2RXIF = 0;
                    U2STAbits.OERR = 0;
                    delay = 0;
                    //LATA &= ~0x60;
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
  
};

