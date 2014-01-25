/****************************************************************************
*   CREATED BY:     Stillbright Managment LLC
*                   Copyright 2012
*                                                                           
*   FILE:           main.c                                                 
*                                                                           
*   DESCRIPTION:    Templet for PIC33
*					        
*                                                                           
*   REVISION    8/20/2010 Created
*               9/9/2012 -  Added a switch to run the application file.
 *              10/22/12 -  Copied this file from FC_33.x folder and converted 
 *                          it to run on PIC33
 *  
****************************************************************************/

 /***************************************************************************
 * Description:
 *			The example code demonstrates using PIC32 core timer, core timer 
 *          interrupt and interrupt service routine to blink LED1 10 times a second.
 *
 * Additional Info: 
 *			Refer to readme.txt
 *
 * Platforms:
 *			PIC32MX Starter Kit DM320001.
 *			PIC32MX USB Starter Kit DM320003.
 *
 * Tools:
 *			1. MPLAB IDE 8.20 or higher
 *			2. MPLAB C Compiler for PIC32 v1.04 or higher
 *			3. General Purpose Starter Kit DM320001 or USB Starter board DM320003
 *			4. USB Cable
 *
 * Debug Print Library: SUPPORTED IN DEBUG MODE ONLY
 *			The Debug Print Library adds user debugging input/output capability
 *          to the MPLAB IDE Starter Kit console window using DBPRINTF, DPUTS,
 *          DBGETC and DBGETS.
 *
 *          To use the Debug Print Library with the PIC32 Starter Kit, do the following:
 *			1. Add '#include "db_utils.h"' to the source code.
 *			   Note: you may need to copy db_utils.h into your working directory or
 *			   specify a path to its location.
 *			   It is located in "<install dir>\PIC32 Starter Kits\Microchip\Include".
 *			2. Add 'db_utils.a' to the library branch of MPLAB IDE project tree.
 *			   It is located in "<install dir>\PIC32 Starter Kits\Microchip\Common"
 *			3. Add "PIC32_STARTER_KIT" macro definition to the project build options
 *			   for the C compiler.
 *			4. Be sure to call DBINIT() first before any other Debug Print Library macros.
 *
 * Starter Board Resources:
 *			LED1 (RED)	= PORTD.RD0
 *			LED2 (YELLOW)	= PORTD.RD1
 *			LED3 (GREEN)	= PORTD.RD2
 *			SW1		= PORTD.RD6  (change notice pin CN15)
 *			SW2		= PORTD.RD7     (change notice pin CN16)
 *			SW3		= PORTD.RD13 (change notice pin CN19)
 *			JTAG.TMS	= PORTA.RA0  (used by debugger)
 *			JTAG.TCK	= PORTA.RA1  (used by debugger)
 *			JTAG.TDO	= PORTA.RA5  (used by debugger)
 *			JTAG.TDI	= PORTA.RA4  (used by debugger)
 *			PGC2		= PORTB.RB6  (used by debugger)
 *			PGD2		= PORTB.RB7  (used by debugger)
 *
 * Starter Board Notes:
 *			1.	There are no pullup resistors on SW1, SW2 or SW3.
 *				To enable the PORTD pullups for SW1, SW2 and SW3, use the following:
 *				CNPUE = (CN15_PULLUP_ENABLE | CN16_PULLUP_ENABLE | CN19_PULLUP_ENABLE);
 *			2.  Do not disable the PIC32MX JTAG.  This will prevent the PIC32MX Starter Kit
 *				debugger(PIC18F4550) from communicating with the PIC32MX device.
 *			3.  Do not configure the SYSTEM CLOCK to operate faster than 80MHz.
 *************************************************************************************
 * Change History:
 * ID			Date            Changes
 * C11842		12/01/2008		Modified for 80MHz operation, Updated comments.
 *************************************************************************************/

// Adds support for PIC32 Peripheral library functions and macros
#include "../LIBS/SYS_LIB/sysglobals.h"
#include "C:/Program Files/Microchip/xc32/v1.20/pic32mx/include/plib.h"
#include "GenericTypeDefs.h"
#include <../include/peripheral/ports.h>
//#include <../include/peripheral/timer.h>
#include "../MMB/MMB.h"

#include "../Microhip/Include/Graphics/DisplayDriver.h"
#include cpuSFRegisters
#include "../LIBS/MENUS_LIB/tMenus.h"
#include "../LIBS/SYS_LIB/uarts.h"
#include "../LIBS/SYS_LIB/systime_date.h"
#include "../LIBS/SYS_LIB/lcd_interface.h"
#include "../LIBS/SYS_LIB/TouchScreen.h"
#include "../app/app_globals.h"
#include "../app/app_main.h"
#include "../LIBS/MODBUS_LIB/modbus.h"



// ****************  Define System Variables **************************
volatile uInt MachineState;

uShort  mSecB4Blink,
        rxResult,
        secTillMenuReset = 30,  //Seconds remaining before UART reverts to idle mode
        mSecTillMBReset = 10,  //mSeconds remaining before UART reverts to idle mode
        secondFlag;
//volatile uInt CommTimeout = 1;  //CommTimeout * 10mSec = Time before rxReset
uInt  errCount = 0, ErrorFlags = 0;         
uInt Indian = 0xA1B2;// Datasheet says PIC33 is Little Indian

//int main(void);
char    touchBusy = 0,
        menuOn, //Menu is on the screen
        rxKey = 0, *tempString ;
/******************************************************************************************
**                                RECEIVE AND TRANSMIT BUFFERS
 * There will be only one TX buffer for each data type.  These will be shared
 * by the different modules.  The idea being that with only a single UART, there can
 * only be one TX event in process at a time                                           **
********************************************************************************************/
uChar   MasterID = DEFAULT_ID;	//= 100
char    uartFlag = 0;


    //**************** ------------------------- *********************
//char testBuff[] = "JK Hello";
int main()
{
    
    InitSysTime(); //10mSec timout For Clock Timout
    //.//////////////////////// The buffer for the UART is in uart.h///////
    //Buffer for UART1 defined as char U1Buffer[U1_BUFFSZ=128]; in uart.h
    InitUART1(DefaultBAUD);	//UnitID, Baudrate, timout in mSec
    MB_Buffer[0] = 8;
    MB_Buffer[1] = 9;
    MB_Buffer[2] = 10;
    //InitDigitals_PIC32MX();
    LoadNVArrayDefaultValues();
    InitSPI1MemBus();    
    WriteDefaults2NVMemory();
    NVMemory2MBReg(4001,3,MB_Buffer);
    /*///////////////////////////////////////////////////////////////////
     ///////////  char ScreenBuff[128] is defined in tMenus.h /////////
     ///////////////////////////////////////////////////////////////////*/
    InitMenuStartPage(AppMainMenu);//Found in app_main.c

    //InitRamtron();
    //This the comment I added on 1/6/12 to test tortouse 
    MachineState = sys_IDLE; // Start state machine is idle mode
    // Test NV Memory
    WriteStringU1("\x1B[2J\x1B[H Next line should be 'Hello World'\r\n");
    //WriteRTChars(100,12,"Hello World");
    //ReadRTChars(100,12,nvMemBuff);
    RT_WriteChars(0x1111, 12, "Hello Modbus");
    RT_ReadChars(0x1111, 12, nvCharBuff);

    nvCharBuff[13] = NULL;
    
    // End test NV memory 
// TODO 's: add if(uart.IF == 1)
    MMBInit();          // initialize the MikroE MMB board
    LCDInit();
    LCDClear();
    TouchInit();
    EEPROMInit();
    TouchLoadCalibration();   
    
    //MMBFadeIn( 1000);
    BacklightOn();
    SetColor(BRIGHTRED);
    //SetColor(BRIGHTRED);
    WriteStringU1("StillBright Managment LLC");
    LCDCenterString( -0, "StillBright Managment LLC");
    //LCDCenterString( 1, "(Touch 1 For Menu)");
    LCDCenterString( 1, nvCharBuff);
    menuOn = 1;
    MasterID = 1;
    secTillMenuReset = 5;
    BuildTouchPad(StartPad,BRIGHTRED);
    while(1)
    {
        //0x01 0x03 0x4E 0x20 0x00 0x01 0x92 0xE8
        if(U1STAbits.URXDA)
        {
            //Capture results from UART read
            rxResult = ReadU1AsSlave(U1Buffer, rxResult);
            //The UART captured part of a potential MB cmd and
            //is now waiting on the rest of it. The countdown to reset
            //has started.  If no more bytes forthcomming then reset
            if(rxResult == RXMB_WAITING)
            {
                 //MBReset comes from UART.h to allow menus to configure value
                 //Default value is 10 mSec
                 mSecTillMBReset = MSEC_TILL_MB_RESET;
            };
            //The UART has receive one or two ESC chars and is now diverting
            //all RX data to the menu module.  The countdown to reset
            //has started.  If no more bytes forthcomming then reset
            if(rxResult == RXMENU_ACTIVE)//0x0080
            {
                LCDClear();
                secTillMenuReset = SEC_TILL_MENU_RESET;
                tempString = RunMenu(U1Buffer);
                //WriteStringU1(UartBuff);
                WriteTerminalU1(U1Buffer);
                //MachineState |= sys_MENU_ACTIVE;
            };
            //The UART has captured one ESC char, we will wait 2 sec for the next
            if(rxResult == RXMENU_STARTING) secTillMenuReset = 2;
   
        }
        if((MachineState & sys_SCREENTOUCHED) == sys_SCREENTOUCHED)
        {
            LCDClear();
            secTillMenuReset = SEC_TILL_MENU_RESET;
            tempString = GetTouchPress(ScreenBuff);
            tempString = RunMenu(ScreenBuff);
            //if the cmd came in the UART, send back out the UART
            //TODO: Make menu return 1 if there is a response    
            MachineState &= ~ sys_SCREENTOUCHED;
        }
        // sys_CHCKSYSTEM is enabled from systime_date.c in SYS_LIB
        // it is enabled every 1 sec.
        if((MachineState & sys_RUNAPP) == sys_RUNAPP)
        {
            if(!CheckAppStatus(app_CHECK_ALL_ERRORS)) RunAppMain();
            //This flag is set if the UART is in Menu mode
            //if no user interaction after user configured seconds
            //any menus on screen are cleared, a button is built to
            //recall menu and the application is allowed to display results
       
            if(secTillMenuReset > 0)
            {
                secTillMenuReset--;
                if(secTillMenuReset <= 0)
                {
                    //Turn whole screen into a button
                    BuildTouchPad(StartPad,BLACK);
                    LCDClear();
                    rxResult = RX_IDLE;
                    secTillMenuReset = 0;
                    ResetMenu();//Clear the exit menu flag so that menu does not immediately exit on entrance
                    ResetMBU1(U1Buffer);//Put MB back to IDLE mode
                }
            }
            else DisplayAppResults(ScreenBuff);
            MachineState &= ~sys_RUNAPP;
        }
        // sys_CHCKSYSTEM is enabled from systime_date.c in SYS_LIB
        // it is enabled every 1mS
        if((MachineState & sys_CHCKSYSTEM) == sys_CHCKSYSTEM) //Every 1mSec
        {
            if(mSecB4Blink++ >= 125)
            {
                mPORTAToggleBits(BIT_1);
                mSecB4Blink = 0;
            }
            if(mSecTillMBReset > 0)
            {
                mSecTillMBReset--;
                if(mSecTillMBReset <= 0) ResetMBU1(ScreenBuff);
            }
            if(secondFlag != Time.Seconds)
            {
                secondFlag = Time.Seconds;         
                MachineState |= sys_RUNAPP;
            }
            RunTouchScreen();  //Check if screen has been touched
            if(ADCGetX() >= 0)
            {
                if(touchBusy == 0)//Minimize double touch
                {
                    MachineState |= sys_SCREENTOUCHED;
                    touchBusy = 1; //Lockout touch screen until press is finished
                    secTillMenuReset  = 5;
                }             
            }
            else touchBusy = 0;
            MachineState &= ~sys_CHCKSYSTEM;
        }
    }
    return 0;    
};
//Called by RunMenu in tMenus.h
void ExitMenus(void)
{
    BuildTouchPad(StartPad,BLACK);
    LCDClear();
    rxResult = RX_IDLE;
    secTillMenuReset = 0;
    ResetMenu();//Clear the exit menu flag so that menu does not immediately exit on entrance
    ResetMBU1(ScreenBuff);//Put MB back to IDLE mode
}
	/*	

 void __attribute__((interrupt, auto_psv)) _IC1Interrupt(void)
{
	
		PORTD++;
		//PORTD = 4;
		PORTD --;
		//Interrupt Service Routine code goes here         
}
*/	  





