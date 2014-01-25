/****************************************************************************
*   CREATED BY: 	Stillbright Managment LLC
*					Copyright 2010
*                                                                           
*   FILE:           sysglobals.h                                                 
*                                                                           
*   DESCRIPTION:    Defines names for all the digital pins and their 
*                   associated functions used by the application.
                    System is built on the philosophy of cooperative multitasking.
                    Different system function as looked at on a scheduled basis.
                    Flags are set either by function calls or interrupts and look at 
                    when the main function is in that state.  
*                                                                           
*   REVISION:       v1.000                                                      
*   Sept 3 2010     Created
    3/16/2012       Modified the system state defines
 *  10/21/2012      Added the use oof pre-processor directives to allow condition complilation.
 *                  What header files to use, difinitions of data types, the configuration bits  
 *                  for settion up clocks as well as timer one and RTC will be defined here.
                                               
****************************************************************************/
#ifndef _globals_h
#define _globals_h
#include "../../Microhip/Include/HardwareProfile.h"



#ifdef  __PIC32MX

    //#define __PIC32MX  // used in HX3347.h
    #define cpuSFRegisters  "C:/Program Files/Microchip/MPLAB C32 Suite/pic32mx/include/proc/p32mx795f512l.h"
    #include cpuSFRegisters

    #define DEFAULT_ID 100
    #define MENUBUFF_SZ 128
    #define OSC_FREQ    (80000000)
    #define SYSCLK  OSC_FREQ/2
    #define PBCLK (OSC_FREQ/(1 << OSCCONbits.PBDIV))
    #define GetOscSpeed()      OSC_FREQ
    #define GetInstructionClock() SYSCLK 
    //#define GetPeripheralClock()  PBCLK
    #define uInt 	unsigned int    //(32 bits)
    #define sInt        int    //(32 bits) signed
    #define uShort      unsigned short  //(16 bits)
    #define sShort      short  //(16 bits)
    #define uChar       unsigned char  //(8 bits)
    #define sChar       char  //(8bits) signed
    //#define BYTE	unsigned char
    #define SEC_TILL_MENU_RESET 15 //Seconds
    #define MSEC_TILL_MB_RESET 10 //mSec
#endif

#ifdef  __dsPIC33__ 

    #if defined(__dsPIC33E__)
	#include <p33Exxxx.h>
        #define cpuSFRegisters  "C:/Program Files/Microchip/MPLAB C32 Suite/pic32mx/include/proc/p32mx795f512l.h"
    #elif defined(__dsPIC33F__)
	#include <p33Fxxxx.h>
        #define cpuSFRegisters  "C:/Program Files/Microchip/MPLAB C32 Suite/pic32mx/include/proc/p32mx795f512l.h"
    #endif
    #include cpuSFRegisters
    #define OSC_FREQ    (80000000)
    #define SYSCLK     OSC_FREQ/2
    #define GetOscSpeed()      OSC_FREQ
    #define GetInstructionClock() SYSCLK
    #define GetPeripheralClock()  SYSCLK
    #define PBCLK SYSCLK
    #define uInt        unsigned long   //(32 bits)
    #define sInt        long //(32 bits) signed
    #define uShort      unsigned int    //(16 bits)
    #define sShort      int    //(16 bits)
    #define cpuSFRegisters  "C:/Program Files/Microchip/MPLAB C32 Suite/pic32mx/include/proc/p32mx795f512l.h"
    
#endif
/******************************************************************************************
                **  Terminal and LCD Cursor and Screen Defines  **
*******************************************************************************************/
#define htESC       0x1B
#define htBS        0x08
#define htCLS       \x1B[2J //Telnet clear screen command
#define htNULLS     0x00 //ending sequence to htcontrol

/******************************************************************************************
                **  Menu System Configuration Defines  **
*******************************************************************************************/

//#define _TMENU_CONNECTION_TCP //TCP Telnet menu system
#define _TMENU_CONNECTION_UART  //Serial Comm menu system
          
/************************************************************************************************
                **  System Timing Parameters  **
 ***********************************************************************************************/

#define DefaultBAUD 57600

/*********************************************************************************************
	             **        System State Defines       **
 ************************************************************************************************/                     
#define sys_IDLE            0x00000000
#define sys_CHCKSYSTEM      0X00000001  // Check system
#define sys_CHCKINPUTS      0X00000020  // Check inputs
#define sys_SPI1_ACTIVE     0x00000040	//Device 1 on SPI1 needs to run or is running
#define sys_SPI2_ACTIVE     0x00000080	//Device 1 on SPI1 needs to run or is running
#define sys_I2C_ACTIVE      0x00000010	//Device 1 on SPI1 needs to run or is running
#define sys_RUNNVMEM        0x00000020 	// Pending NV Memory operation
#define	sys_MENU_ACTIVE     0x00000040	// System stopped menus running configuration
#define sys_U1_ACTIVE       0x00000080	// U1 has interrupted or is busy
#define sys_U2_ACTIVE       0x00000100  // U2 has interrupted or is busy
#define sys_RUNAPP          0x00000200	// Run application scheduler
#define sys_RUNMENU         0x00000400  // If menu is on screen
#define sys_APPGOOD         0x00000800  // Application good to run
#define sys_SCREENTOUCHED   0x00001000
/***********************************************************************************
                        **     Conditional State Defines     **
**********************************************************************************/
//Bits 15-12 are reserved for persisting control of a multistate process
/*********************************************************************************************
**     		System Error Defines                                
** Errors can be broken up into up to four areas or modules each with four errors.  The first
** two are the state machine and the uart. Errors are binary flag so multiple errors can be
** tracked
** The State machine is from 0x0001 to OxOOO8 
** The UART and protocol modules are from 0x001 to 0x008
*********************************************************************************************/


               
/******************************************************************************************
**                                 System Variables	                     	       **
********************************************************************************************/

extern uChar testUChar, MasterID;
extern char  testChar;
extern float testFloat;
//extern long gblFcy; // Used by the time.h and uart_dma.h
extern volatile uShort keyPad; // global variable defining program status
extern int volatile IC1Hertz; //Time between clock edges
extern volatile uInt MachineState, sysErrors;  // Holds Errors for system and peripherals.
//extern sClock Time; 

//void	InitT1(uShort mSecDelay);
void ConfigOscTest();
void InitSysClock(void);
#endif
