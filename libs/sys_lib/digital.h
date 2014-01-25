/****************************************************************************
*   CREATED BY: 	Stillbright Managment LLC
*					Copyright 2010
*                                                                           
*   FILE:           digital.h                                                 
*                                                                           
*   DESCRIPTION:    Defines names for all the digital pins and their 
*					associated functions used by the application          
*                                                                           
*   REVISION:   	v1.000                                                      
*   DATE: 		Sept 3 2010                                                 
****************************************************************************/
#ifndef _DIGITAL_H_
#define _DIGITAL_H_

#include "sysglobals.h"

//********************************* OUTPUTS *****************************
#define LED0 		PORTAbits.RA0
#define LED1 		PORTAbits.RA1
#define LED2 		PORTAbits.RA2
#define LED3 		PORTAbits.RA3
#define LED4 		PORTAbits.RA4

// Communication Defines
#define TXENABLE 	

//EEProm Chip Select Defines
//#define SPI2CS1 	PORTAbits.RA5;



//************************************ INPUTS ***************************
// Pushbutton Defines
#define PB0 		PORTDbits.RD0;
#define PB1 		PORTDbits.RD1;
#define PB2 		PORTDbits.RD2; 
#define PB3 		PORTDbits.RD3; 	


void InitDigitals_Explore16(void);
void InitDigitals_PIC32MX(void);
#endif
