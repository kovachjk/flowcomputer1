/*********************************************************************
 *
 *	MikroE PIC32MX4 MMB Hardware specific definitions
 *
 *********************************************************************
 *
 * Author               Date		Comment
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Lucio Di Jasio       12/08/09    MikroE PIC32MX4 MMB 
 ********************************************************************/
#ifndef __HARDWARE_PROFILE_H
#define __HARDWARE_PROFILE_H

#define PIC32MX4_MMB    400

    #include "plib.h"

/*********************************************************************
* GetSystemClock() returns system clock frequency.
*
* GetPeripheralClock() returns peripheral clock frequency.
*
********************************************************************/

#define GetSystemClock() 			(80000000ul)

/*********************************************************************
* Macro: #define	GetPeripheralClock() 
*
* Overview: This macro returns the peripheral clock frequency 
*			used in Hertz.
*			* value for PIC32 is <PRE>(GetSystemClock()/(1<<OSCCONbits.PBDIV)) </PRE>
*
********************************************************************/
#define	GetPeripheralClock()		(GetSystemClock()/(1<<OSCCONbits.PBDIV))
/*********************************************************************

/*********************************************************************
* Overview:
*   Graphics Panel on the MikroE- PIC32 MX4 MMB Board 
*                                        
********************************************************************/
#define GRAPHICS_HARDWARE_PLATFORM  PIC32MX4_MMB
#define DISPLAY_CONTROLLER          HX8347D
/*********************************************************************
* Overview: Horizontal and vertical display resolution
*                  (from the glass datasheet).
*********************************************************************/
#define DISP_HOR_RESOLUTION				240
#define DISP_VER_RESOLUTION				320
/*********************************************************************
* Overview: Defines color depth. The 1,2,4,8,16 bit per pixel 
*			color depths are valid.
*
********************************************************************/
#define COLOR_DEPTH						16
#define USE_16BIT_PMP    

/*********************************************************************
* Overview: Image orientation (can be 0, 90, 180, 270 degrees).
*********************************************************************/
#define DISP_ORIENTATION				90

/*********************************************************************
* IOS FOR THE DISPLAY CONTROLLER
*********************************************************************/

// Definitions for reset pin
#define RST_TRIS_BIT        _TRISC1
#define RST_LAT_BIT         _LATC1

// Definitions for RS pin
#define RS_TRIS_BIT         _TRISB15
#define RS_LAT_BIT          _LATB15

// Definitions for CS pin
#define CS_TRIS_BIT         _TRISB14
#define CS_LAT_BIT          _LATB14

// Definitions for Backlight power pin 
#define BL_TRIS_BIT         _TRISD2
#define BL_LAT_BIT          _LATD2


#define BacklightOn()       BL_LAT_BIT = 1
#define BacklightOff()      BL_LAT_BIT = 0


/*********************************************************************
* IOS FOR THE FLASH/EEPROM SPI
*********************************************************************/
/*********************************************************************
* IOS FOR THE TOUCH SCREEN
*********************************************************************/
#define ADC_XPOS        ADC_CH0_POS_SAMPLEA_AN11
#define ADC_YPOS        ADC_CH0_POS_SAMPLEA_AN10

// X port definitions
#define ADPCFG_XPOS     _PCFG13
#define LAT_XNEG        _LATB11
#define LAT_XPOS        _LATB13
#define TRIS_XNEG       _TRISB11
#define TRIS_XPOS       _TRISB13

// Y port definitions
#define ADPCFG_YPOS     AD1PCFGbits.PCFG12
#define LAT_YNEG        _LATB10  
#define LAT_YPOS        _LATB12 
#define TRIS_YNEG       _TRISB10
#define TRIS_YPOS       _TRISB12 


/*********************************************************************
* IOS FOR SERIAL FLASH 
*********************************************************************/
#define CS_FLASH_TRIS_BIT   _TRISC2
#define CS_FLASH_LAT_BIT    _LATC2

/*********************************************************************
* IOS FOR RF MODULE
*********************************************************************/
//#define CS_RF_TRIS_BIT      _TRISD8
//#define CS_RF_LAT_BIT       _LATD8

/*********************************************************************
* IOS FOR ACCELEROMETER
*********************************************************************/
#define CS_ACC_TRIS_BIT     _TRISC3
#define CS_ACC_LAT_BIT      _LATC3

/*********************************************************************
* IOS FOR THE Joystick
*********************************************************************/
#define BTN_A       _RB0
#define BTN_B       _RB1
#define BTN_C       _RB2
#define BTN_D       _RB3
#define BTN_CP      _RA10

// joystick switch assignement
#if (DISP_ORIENTATION == 0)     // portrait
// vertical 
#define JOY_SELECT  16
#define JOY_UP      8
#define JOY_RIGHT   4
#define JOY_DOWN    2
#define JOY_LEFT    1

#else                           // landscape
// horizontal
#define JOY_SELECT  16
#define JOY_UP      4
#define JOY_RIGHT   2
#define JOY_DOWN    1
#define JOY_LEFT    8
#endif

/*********************************************************************
* IOS FOR THE LEDs
*********************************************************************/
#define LD0_TRIS    _TRISA0
#define LD1_TRIS    _TRISA1
#define LD2_TRIS    _TRISD9
#define LD4_TRIS    _TRISA9
#define LD0         _LATA0
#define LD1         _LATA1
#define LD2         _LATD9
#define LD4         _LATA9

// LED logic is inverted
#define LED_ON      0
#define LED_OFF     1


/*********************************************************************
* IOS FOR THE SD/MMC CARD INTERFACE
*********************************************************************/

#define USE_SD_INTERFACE_WITH_SPI

    // Registers for the SPI module 
    #define MDD_USE_SPI_1

	// MDD SPI Configuration
	#define SPI_START_CFG_1     (PRI_PRESCAL_64_1 | SEC_PRESCAL_8_1 | MASTER_ENABLE_ON | SPI_CKE_ON | SPI_SMP_ON)
    #define SPI_START_CFG_2     (SPI_ENABLE)

    // Define the SPI frequency
    #define SPI_FREQUENCY			(20000000)


    // Description: SD-SPI Chip Select Output bit
    #define SD_CS               _LATA9
    // Description: SD-SPI Chip Select TRIS bit
    #define SD_CS_TRIS          _TRISA9

    // Description: SD-SPI Card Detect Input bit
    #define SD_CD               _RG7
    // Description: SD-SPI Card Detect TRIS bit
    #define SD_CD_TRIS          _TRISG7

    // Description: SD-SPI Write Protect Check Input bit
    #define SD_WE               _RG6
    // Description: SD-SPI Write Protect Check TRIS bit
    #define SD_WE_TRIS          _TRISG6

    // Description: The main SPI control register
    #define SPICON1             SPI1CON
    // Description: The SPI status register
    #define SPISTAT             SPI1STAT
    // Description: The SPI Buffer
    #define SPIBUF              SPI1BUF
    // Description: The receive buffer full bit in the SPI status register
    #define SPISTAT_RBF         SPI1STATbits.SPIRBF
    // Description: The bitwise define for the SPI control register (i.e. _____bits)
    #define SPICON1bits         SPI1CONbits
    // Description: The bitwise define for the SPI status register (i.e. _____bits)
    #define SPISTATbits         SPI1STATbits
    // Description: The enable bit for the SPI module
    #define SPIENABLE           SPI1CONbits.ON
    // Description: The definition for the SPI baud rate generator register (PIC32)
    #define SPIBRG			    SPI1BRG

    // Tris pins for SCK/SDI/SDO lines

    // Description: The TRIS bit for the SCK pin
    #define SPICLOCK            TRISDbits.TRISD10
    // Description: The TRIS bit for the SDI pin
    #define SPIIN               TRISCbits.TRISC4
    // Description: The TRIS bit for the SDO pin
    #define SPIOUT              TRISDbits.TRISD0
    
    //SPI library functions
    #define putcSPI             putcSPI1
    #define getcSPI             getcSPI1
    #define OpenSPI(config1, config2)   OpenSPI1(config1, config2)

    // Will generate an error if the clock speed is too low to interface to the card
    #if (GetSystemClock() < 100000)
        #error Clock speed must exceed 100 kHz
    #endif


#endif // __HARDWARE_PROFILE_H
