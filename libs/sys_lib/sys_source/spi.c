/*  ***************************************************************************
   CREATED BY: 	Stillbright Managment LLC
*					Copyright 2012
*
*   FILE:           spi.c
*
*   DESCRIPTION:    Functions for operating the SPI
*
*   CREATED:		April 19 2012
*   REVISION:   	v0.1 - Define operation and functions
****************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../sysglobals.h"
#include "../spi.h"
#include DefinedCPU
spiBusStruct spi2DeviceArray[4];
uChar spi2DeviceIndex = 0;
/*************** CreateDeviceSPI2 *******************
 *  Description:
 */

void ConfigSPI2Bus(uInt16 deviceIndex, uChar Mode16, uChar IE)
{
    if(deviceIndex != spi2DeviceIndex)
    {
        spi2DeviceIndex = deviceIndex;
        SPI2STATbits.SPIEN = 0; //Enable SPI Module
        SPI2CON1bits.SMP = 0; //Input Data is sampled at the middle of data output time.
        SPI2CON1bits.CKE = spi2DeviceArray[deviceIndex].cke; //Serial output data changes on transition from
        SPI2CON1bits.CKP = spi2DeviceArray[deviceIndex].ckp; //Idle state for clock is a low level;
        SPI2CON1bits.MSTEN = 1; //Master Mode Enabled
        SPI2STATbits.SPIEN = 1; //Enable SPI Module
        //Interrupt Controller Settings
    }
        IFS0bits.SPI1IF = 0; //Clear the Interrupt Flag
        //IEC0bits.SPI1IE = spi2DeviceArray[deviceIndex].intEnable; //Enable the Interrupt
}
void InitSPI1(void)
{
    IFS0bits.SPI1EIF = 0; //Clear the Interrupt Flag
    IEC0bits.SPI1IE = 0; //disable the Interrupt
    // SPI1CON1 Register Settings
    SPI1CON1bits.DISSCK = 0; //Internal Serial Clock is Enabled.
    SPI1CON1bits.DISSDO = 0; //SDOx pin is controlled by the module.
    SPI1CON1bits.MODE16 = 1; //Communication is word-wide (16 bits).
    SPI1CON1bits.SMP = 0; //Input Data is sampled at the middle of data output time.
    SPI1CON1bits.CKE = 0; //Serial output data changes on transition from
    //Idle clock state to active clock state
    SPI1CON1bits.CKP = 1; //Idle state for clock is a low level;
    //active state is a high level
    SPI1CON1bits.MSTEN = 1; //Master Mode Enabled
    SPI1STATbits.SPIEN = 1; //Enable SPI Module
    SPI1BUF = 0x0000; //Write data to be transmitted
    //Interrupt Controller Settings
    IFS0bits.SPI1IF = 0; //Clear the Interrupt Flag
    IEC0bits.SPI1IE = 1; //Enable the Interrupt
    
}
void InitSPI2(void)
{
    IFS2bits.SPI2EIF = 0; //Clear the Interrupt Flag
    IEC2bits.SPI2IE = 0; //disable the Interrupt
    // SPI1CON1 Register Settings
    SPI2CON1bits.DISSCK = 0; //Internal Serial Clock is Enabled.
    SPI2CON1bits.DISSDO = 0; //SDOx pin is controlled by the module.
    SPI2CON1bits.MODE16 = 0; //Communication is word-wide (16 bits).
    SPI2CON1bits.SMP = 0; //Input Data is sampled at the middle of data output time.
    SPI2CON1bits.CKE = 1; //Serial output data changes on transition from
    SPI2CON1bits.CKP = 0; //Idle state for clock is a low level;
    SPI2CON1bits.MSTEN = 1; //Master Mode Enabled
    SPI2STATbits.SPIEN = 1; //Enable SPI Module
    SPI2BUF = 0x0000; //Write data to be transmitted
    //Interrupt Controller Settings
    IFS0bits.SPI1IF = 0; //Clear the Interrupt Flag
    IEC0bits.SPI1IE = 0; //Enable the Interrupt

}
uChar rwSPIChar(char device, uChar Data)
{

}
uChar* rwSPIChars(char device, uChar* Data, uInt16 Number)
{

}
uInt16 rwSPIInt(char device, uInt16 Data)
{

}
uInt16* rwSPIInts(char device, uInt16* Data, uInt16 Number)
{

}
