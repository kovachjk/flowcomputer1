/****************************************************************************
   CREATED BY: 	Stillbright Managment LLC
*		Copyright 2012
*
*   FILE:           dac.c
*
*   DESCRIPTION:    Functions for implementing digital to analog
 *                  converters using Texas Instruments DAC7565 IC.
 *                  Once calibrated the DAC will be normalized to mV.
*
*   CREATED:        May 26 2012
*   REVISION:   v0.1 - Define operation and functions
****************************************************************************/

#include "p33fxxxx.h"
#include "../SYS_LIB/sysglobals.h"
#include "dac_ti.h"

void InitDAC(void);
void SetRawOutput(int Value);
void SetDAC2Zero(void);
void SetOffset(float VOM_Reading);
void SetDAC2MaxScale(void);
void SetDAC2MidScale(void);
void SetMultiplier5V(int  VOM_Reading);
void SetMultiplier10V();
//+/-10V
void SetMultiplierBP10V();
