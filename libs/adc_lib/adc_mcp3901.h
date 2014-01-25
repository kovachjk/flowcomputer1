/****************************************************************************
*   CREATED BY:     Stillbright Managment LLC
*                   Copyright 2012
*
*   FILE:          adc_mcp3901.h
*
*   DESCRIPTION:    Function, Structs, and variable to interface and control
 *                  Microchip's MCP3901 dual channel delta-sigma DAC
*
*
*   REVISION    9/24/2012 Created
*               9/9/2012  Added a swith to run the application file.
****************************************************************************/
#ifndef _ADC_MCP3901_h
#define _ADC_MCP3901_h

/********************************
***     Globals		*****
********************************/
struct dac
{
    double  cZero;  //ADC count when input set to zero volts
    double  c5volt; //ADC count when input set to 5Volts
    double  c420mA; //ADC count when input set to 4-20mA
    double  cRaw;   //Last read ADC value
    float   pScale; //Percent of full scale either 4-20 or 5V
};
/********************************
***			Defines		*****
********************************/

/*  ADCInit
 Description: Configures the SPI channel to use MCP3901
 */
void ADCInit(); 
//Sample rate is the Samples per second and should be 2.5 times higher than
// Fmax.  NumSamples = Number of samples before WVFMRDY flag is set.
//AN5 is Pot on Board
void ReadAIN5(int SampleRate, int NumSamples);
//AN4 is Temp Sensor
void ReadAIN4(int SampleRate, int NumSamples);

void ReadChannelVoltage(int Channel);
void TransmitVoltage(void);  //Maybe should be average
/************************************************************
 CONFIGURATION FUNCTIONS
 ***********************************************************/

#endif

