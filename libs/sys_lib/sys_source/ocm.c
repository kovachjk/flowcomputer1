/**********************************************************************
* © 2007 Microchip Technology Inc.
*
* FileName:         ocm.c
 * Description:     Functions for generating a square wave
 *
 *Created 8/15/2009
 *© Stillbright Managment LLC 2009
**********************************************************************/

#include "p33fxxxx.h"
#include "../sysglobals.h"
#include "../ocm.h"

//This function configures OC! for a 50% duty cycle square wave
// based on timer2's frequency
volatile int ocLevel[8];

void initOCM()
{
    // Initialize Output Compare Module
    OC1CONbits.OCM = 0b000; // Disable Output Compare Module
    OC1R = OC2R = OC3R = OC4R = 0; // Write the duty cycle for the first PWM pulse
    OC1RS = OC2RS = OC3RS = OC4RS = 0; // Write the duty cycle for the second PWM pulse
    OC1CONbits.OCTSEL = OC2CONbits.OCTSEL = OC3CONbits.OCTSEL = OC4CONbits.OCTSEL = 0; // Select Timer 2 as output compare time base
    OC1R = OC2R = OC3R = OC4R = 100; // Load the Compare Register Value
    OC1CONbits.OCM = 0b110; // Select the Output Compare mode

    //Init timer to 1KHz
    T2CONbits.TON = 0; // Disable Timer
    T2CONbits.TCS = 0; // Select internal instruction cycle clock
    T2CONbits.TGATE = 0; // Disable Gated Timer mode
    T2CONbits.TCKPS = 0b01; // Select 1:8 Prescaler
    TMR2 = 0x00; // Clear timer register
    PR2 = 4999; //(4999+1)*.2uSec = 1KHz
    IPC1bits.T2IP = 0x01; // Set Timer 2 Interrupt Priority Level
    IFS0bits.T2IF = 0; // Clear Timer 2 Interrupt Flag
    IEC0bits.T2IE = 1; // Enable Timer 2 interrupt
    T2CONbits.TON = 1; // Start Timer
}



void SetOCM_Amplitude(int OCModuleNum, uInt16 mVolts)
{
    //write conversion routine
    ocLevel[OCModuleNum - 1] = mVolts;
}

void __attribute__((__interrupt__, no_auto_psv)) _T2Interrupt( void )
{
    /* Interrupt Service Routine code goes here */
    OC1RS = ocLevel[0]; // Write Duty Cycle value for next PWM cycle
    OC1RS = ocLevel[1];
    OC1RS = ocLevel[2];
    OC1RS = ocLevel[3];
    IFS0bits.T2IF = 0; // Clear Timer 2 interrupt flag
}
