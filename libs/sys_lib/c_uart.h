/****************************************************************************
*   CREATED BY: 	Stillbright Managment LLC
*					Copyright 2010
*                                                                           
*   FILE:           c_uart.h                                                 
*                                                                           
*   DESCRIPTION:    Defines names and functions for the implemation
*					of standard char based read and write functions using serial 
*					port.
*                                                                           
*                                                      
*   Sept 3 2010	-	Created as b_uart.h
*	3/10/2012	-	Changed to c_uart.h Defined new char base function calls            
****************************************************************************/


#ifndef _C_UART_H
#define _C_UART_H

#include    "sysglobals.h"
//#define SERIAL_STRING_SZ    128u
#define INPUT_BUFF_SZ 16u
// The following defines are for the state machine
#define RX1_HasData 0x0001
#define TX1_Busy    Ox0002
#define RX2_HasData 0x0100
#define TX2_Busy    Ox0200
//define ClearTerminal "\x1B[2J\x1B[H"

extern uShort uartFlags;
char *ptrU1Buff;


uInt InitUART1(uInt BaudRate);
char WriteCharU1( char c);
void WriteStringU1(char *buffPtr);
//Send an escape sequence before writing string
void TerminalOutU1(char *buffPtr);
char* ReadRX1(char *buffPtr);//Returns null terminated char array
//ToDo: char* ReadStringRX1(void); //Keeps reading until NULL found

void InitUART2(long BaudRate);
void WriteStringU2(char *buffPtr);
void WriteCharU2(char Data);
char* ReadRX2(char *buffPtr);//Returns null terminated char array
//ToDo: char* ReadStringRX2(void); //Keeps reading until NULL found

#endif
