/****************************************************************************
   CREATED BY: 	Stillbright Managment LLC
*					Copyright 2008
*                                                                           
*   FILE:           c_uart.c  (No DMA)
*                                                                           
*   DESCRIPTION:    Source Code for non DMA char based uart routines which implements 
					the definitions in b_uart.h       
*                                                                                                                               
*   Aug 20 2008	-	Created
*	3/9/2012-	Made two different uart h files.  One which is  char based and one  
*			which is binary based. There are two different ssource files for the 
*			b_uart.h file one that uses DMA and this one which does not.
 *      4/2/2012 -      Moved stringBuff from tMenu.  May move it again to sysGlobals so that
 *                      TCP implemention can use it also.
****************************************************************************/
#include <string.h>                     // String and buffer processing definitions
#include "../c_uart.h"
#include <stdio.h>
#include "../../SYS_LIB/sysglobals.h"
#include cpuSFRegisters
              // Communication interface definitions

uShort delay = 0, jkTest = 0, UARTResetDelay =11;   // Status code definitions
long 	gblBaud; 	// global variable to hold baud rate
uChar 	serialIndex = 0,
        inputIndex = 0,
	*ptrTxBuff,
	*ptrRxBuff;
char    *ptrU1Buff;// Serial i/o data
//uChar   ioBuff_U1[SERIAL_STRING_SZ];// Serial i/o data
//uChar   inputBuff_U2_U2_U2[INPUT_BUFF_SZ];
uShort  *fileBuff; //Pointer to int data to be stored

int 	TypeOfDeLimit;		//Var to hold delimiting char between numbers.
uShort 	*IntsBuffer;  // Pointer to hold Int array for transmission
		


/****************************************************************************
*   FUNCTION:       CommInit(Uint8 ui8Port, uShort ui16BaudRate,            *
*                            uShort ui16Parity, uShort ui16StopBits)        *
*                                                                           *
*   DESCRIPTION:    This function configures the system's communication     *
*                   channel(s).  It must be customized for the specific     *
*                   communication modules and channel parameters used       *
*                   for the particular application.                         *
*                                                                           *
*          
*                                                                           *
*   REVISION:   Created:  1 October 2008 - UART2
 *              10/21/12 - Added init for  UART1 and WriteCharU1        *
 *                         Change InitUART2() to look at PBCLK which will change
 *                         depending on MCU used
                10/23/12 - UART1 is working with menu system            *
 *                         TODO: Rewrite to minimize lockups and 
 *                         for use with state machine
 *
****************************************************************************/
uShort uartFlags = 0;
uInt InitUART1(uInt BaudRate)
{
    U1BRG =  (PBCLK/(16*BaudRate))-1;

    U1ASTAbits.UTXEN = 1;
    U1ASTAbits.URXEN = 1;
    U1MODEbits.ON = 1;  
    return PBCLK/(16*(U1BRG + 1));
}
char WriteCharU1( char c)
{
    //while ( CTS);               // wait for !CTS, clear to send
    while ( U1STAbits.UTXBF);   // wait while Tx buffer full
    U1TXREG = c;
    return c;
} // putU2
char* ReadRX1(char *buffPtr)
{
    serialIndex = 0;
    while (U1STAbits.URXDA) // While data is available in the buffer
    {
        buffPtr[serialIndex++]=U1RXREG;
    }
    buffPtr[serialIndex]=0x00;//*/
    //uart.if = 0; //Clear flag
    return buffPtr;
    
}

void WriteStringU1(char *buffPtr)
{
    //U2TXREG = buffPtr[0];
    //txIndex++;
    while(*buffPtr != 0x00)
    {
        while(U1STAbits.UTXBF);
        U1TXREG = *buffPtr++;
    }
}
void TerminalOutU1(char *buffPtr)
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
void InitUART2(long BaudRate)
{
        
    //int iBaud;
    //gblBaud = BaudRate;
    //10/23/12 As of this date U2 has only run on PIC33
    //PBCLK should automatically change depending on what mcu is being used.

    // configure U2MODE

    // Load a value into Baud Rate Generator.  Example is for 9600.
    // See section 19.3.1 of datasheet.
    //  U2BRG = (37M/(16*9600))-1
    BaudRate = (PBCLK/(16*BaudRate))-1;
    U2BRG = BaudRate;

    IPC7 = 0x4400;	// Mid Range Interrupt Priority level, no urgent reason

    IFS1bits.U2TXIF = 0;	// Clear the Transmit Interrupt Flag
    IEC1bits.U2TXIE = 0;	// Enable/Disable Transmit Interrupts
    IFS1bits.U2RXIF = 0;	// Clear the Recieve Interrupt Flag
    IEC1bits.U2RXIE = 0;	// Enable/Disable Receive Interrupts
    U2STAbits.UTXISEL1 = 1;	//Bit15(13) Int FIRST HALF when last char into TXREG
    U2MODEbits.UARTEN = 1;	// And turn the peripheral on
    U2STAbits.UTXEN = 1;
    U2STAbits.URXISEL1 = 0;	

 }

char* ReadRX2(char *buffPtr)
{
    serialIndex = 0;
    while (U2STAbits.URXDA) // While data is available in the buffer
    {
        buffPtr[serialIndex++]=U2RXREG;
    }
    buffPtr[serialIndex]=0x00;//*/
    //uart.if = 0; //Clear flag
    return buffPtr;
    
}

char* GetCharU2(void)
{

}
void WriteCharU2(char Data)
{
    U2TXREG = Data;
}

//Writes a null terminated series of chars

void WriteStringU2(char *buffPtr)
{
    //U2TXREG = buffPtr[0];
    //txIndex++;
    while(*buffPtr != 0x00)
    {
        while(U2STAbits.UTXBF);
        U2TXREG = *buffPtr++;
    }
}


/*
void __attribute__((interrupt, auto_psv)) _U2TXInterrupt(void)
{

}
void __attribute__((interrupt, auto_psv))_U2RXInterrupt(void)
{
    while (U2STAbits.URXDA) // While data is available in the buffer
    {
        inputBuff_U2_U2[inputIndex++]=U2RXREG;
    }
    inputBuff_U2_U2[inputIndex]=0x00;//
    IFS1bits.U2RXIF = 0;
 
}
*/ 
        
