#ifndef INCL_COMPAIRS_H
/****************************************************************************
*          STILLBRIGHT MANAGMENT                *
*                                                                           *
*   FILE:           compair.h                                              *
*                                                                           *
*   DESCRIPTION:    This file contains the definitions required by and      *
*                   the function prototypes of the input and output compairs   *
*                                                                           *
*   REVISION:  0    v1.0                DATE:  SEPT 15, 2009                *
*       Original release.                                                   *
****************************************************************************/

#define INCL_COMPAIRS_H                 // Show that this file has been included

                        /****************************
                        **  Required Header Files  **
                        ****************************/

                        //  Compiler-supplied Files

#include "p33FJ256GP710.h"                   // Processor-specific definitions (actually
                                        //   a wrapper file that includes the 
                                        //   appropriate processor-specific header
                                        //   based on the selected device)
#include <timer.h>                      // Timer module definitions

                        //  Application-specific Files

#include "globals.h"                    // Platform-independent data definitions

                    /*************************************
                    **  Timer 3 Processing Definitions  **
                    *************************************/

#define BLINK_PERIOD        200         // Number of Timer 3 interrupts per blink
                                        //   state (200 msec)
                                        
                        /**************************
                        **  Function Prototypes  **
                        **************************/
extern unsigned int x;
extern int volatile IC1Hertz; //Time between clock edges

                
extern sClock Time; 
extern uChar CharDelay; // time in 100th of micro second per char
extern volatile uInt16 MachineState;
void   	T3Init(uInt16 Frequency),   // Initialize Timer 3 to specified freq but dosen't start
    	T3Stop(void),					// Stop and Clear T3 Flags and Counter
    	T3Start(void),					// Starts T3 with the value given in T3 Init 	
    	T5Init(void),     			//.UART reset timer
       	T5CharDelay(char nChars),	// T5 timeout delay for up to 560 chars
        T5Stop(void);
                
						/*****************************
						**	Compair Prototypes		***
						*******************************/
void OC5Init(double Hertz); // Pulse Frequency output on Pin 81
void OC5Start(void);
void OC5Stop(void);
void IC1Init(void);//Input Compare 1	
void IC1Start(void);					
void IC1Stop(void);       
#endif
