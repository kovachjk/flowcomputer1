#ifndef _TACHO_H
/****************************************************************************
*          STILLBRIGHT MANAGMENT                *
*                                                                           *
*   FILE:           tacho.h                                              *
*                                                                           *
*   DESCRIPTION:    This file contains the definitions required by and      *
*                   the function prototypes the input and output compairs   *
*                                                                           *
*   REVISION:  0    v1.0                DATE:  SEPT 15, 2009                *
*       Original release.                                                   *
****************************************************************************/

#define _TACH0_H                 // Show that this file has been included

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
          
          
						/*****************************
						**	TACHO Prototypes		***
						*******************************/
//returns resolution  in  x number of parts based on max RPM
uInt16 initIC1Tacho(int PPR, int minRPM, int maxRPM); //How many pulses per rev will there be				
void StopTacho(void);       
extern uInt16	tickBase;	//number of uSeconds in each tick
extern uInt16	numPPR;		//number of pulses per rev
extern uInt16	numTicks;	//number of ticks since last pulse edge
extern float	RPM;		// 
#endif
