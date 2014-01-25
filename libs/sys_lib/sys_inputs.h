/* 
 * File:   sys_inputs.h
 * Author: JKovach
 * Description: Variables and functions for managment of physical electical inputs to the
 *              system.
 * Revisions:   10/28/2012 - Created
 */

#ifndef SYS_INPUTS_H
#define	SYS_INPUTS_H
#include "../SYS_LIB/sysglobals.h"
#include "../WIFI_LIB/wifi.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define C1_Mem_Error    0x00000001
#define C1_Set_5V       0x00000002
#define C1_Set_10V      0x00000004

/*Because the unit will switch between different Vrefs when
  operating at different volts there are differnt ADC counts for
  for the ADC.  Struct will be stored in memory.  If memory comes back 
 zero,*/
typedef struct eInputs
{
    float   voltsHigh; 
    uInt    acdCount5V;
    uInt    acdCount10V;
    uInt    adcCount0V;
    float   voltsLow;
    float   adcMultiplier;
    float   percentRange;
}a_Input;
char* ConfigSystemInputs(char* cBuff, char keyPress);
char* ConfigChannel(char* cBuff, char keyPress);
uInt  InitSystemInput(void);
char* ReportSysInputVoltage(char ChannelNum);
char* SetSysInputTo5V(char ChannelNum);
char* SetSysInputTo10V(char ChannelNum);
#endif	/* SYS_INPUTS_H */

