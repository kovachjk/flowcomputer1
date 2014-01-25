
/****************************************************************************
*   CREATED BY: 	Stillbright Managment LLC
*					Copyright 2010
*                                                                           
*   FILE:           Memory.h                                                 
*                                                                           
*   DESCRIPTION:    Routines for the storage and retrieval of data
*                   from varios types of non-volatile memory.  
                    Function automatically handles writes longer than page lengths.
                    Max delay by funciton call is page length in bytes time
                    the SPI2 bus speed of 8 mBits.      
*                                                                           
*   9/10/2010 - Inital layout
*   5/9/2011  -	Added the New parameter.  Differenciated between single data and array data
*   5/14/2011 - Finished WriteEPInt,WriteEPInts,ReadEPInt and ReadEPInts 
*   5/28/2011 - Started changing code to write pages instead of short
*               arrays for eeProm.
 *  3/12/2012 - Put Ramtron on board. 
 *  4/26/1012 - Wrote and retrieved a string from Ramtron memory
 *  4/29/2012 - Created array of structs in the SPI module to store configuration of SPI bus
 *              needed by different devices.  Created functions to configure SPI config
 *              array for different memory devices.
 *  01/03/12 -  Changed to device centric names.
 *  01/27/13 -  Copied this and the source file to archive.  Removed many function
 *              with the intent of only having the ability to read and write
 *              uChars.  All other data types will use conversion routines.
 *
 *              Started adding conversion utilites
 *  TODO'S	Need to validate waiting on status reg to clear
*               to make sure program cannot hang.
 *              Need to standarized error codes
****************************************************************************/

#ifndef _SPI_MEMORY_H
#define _SPI_MEMORY_H
#include "../SYS_LIB/sysglobals.h"
#include "mem_mgr.h"
//#include "mcu_header_file" //defined in main
//#include "states.h"

//*********************  Normalize SPI Ports and Registers *****************
#define NV_SPIBUFF SPI1BUF
#define NV_TXFULL  SPI1STATbits.SPITBF
//**********************  Memory Size Defines *********************
#define MB_MEM_SZ 512 // Number of Registers
#define RT_CHIPSIZE 8192 //
#define EP_CHIPSIZE 32768 // Largest Address before wrap around
//******************* Memory State Machine Defines **************************
#define RT_WREN         6
#define RT_WRITE        2
#define RT_READ         3

#define NV_WEN		6 // Write enable
#define NV_WRITESTATE   1 //Memory in Write State
#define NV_READSTATE 	5 //Memory in Read State
//***************  Chip Status bits
#define NV_READ		3 //Read command
#define NV_WRITE	2 //Write command
#define NV_WDIS		4 // Write disable
//****************** Flash Defines *******************************
#define F_PAGESIZE 	1024 // Write page size of Atmel flash chip
#define F_CHIPSIZE 	8000000 // Largest Address before wrap around
#define F_WBUFFA	0
#define F_WBUFFA	0
#define F_MEM2BUFFA	0
#define F_MEM2BUFFB	0
#define F_BUFFA2MEM	0
#define F_BUFFB2MEM	0
#define F_PAGEERASE	0X81 //1024 or 1056 bytes - 35 mSec max
#define F_BLOCKERASE	0X50 //8,192 or 8,448 bytes - 100 mSec max


//********************* Page Bounderies  *******************
#define EP_PAGESIZE     0X40 //For 25LC256 Microhip eprom
#define	PGM_PAGESIZE    0XFF //
#define	FLSH_PAGESIZE   0XFF
//********************* Pin Assignments for Chip Selects  *******************
// JK 9/14/12 CS pin for NV memory on the Discovery 16 board is RD12 
#define epChipSelect        PORTDbits.RD12
#define fmChipSelect        PORTDbits.RD12
#define csRamtron           PORTCbits.RC2
//********************* SPI Bus Defines
#define spi2DataWidth   SPI2CON1bits.MODE16  //1 = 16bits, 0 = 8bits

//********************* Memory Operation Defines *******************
// Used by all devices to indicate to memory state machine which device is
// being used and what  operation is currently being implemented
#define NVBUFF_FREE 	0X00
#define EP_MEMORY 	0X0001
#define FM_MEMORY	0X0002
#define PGM_MEMORY 	0X0004
#define INT_WRITING 	0X0010
#define CHAR_WRITING 	0X0020
#define DBL_WRITING 	0X0040
#define STRNG_WRITING	0X0080
//********************* Flash Status Defines *******************
#define FM_NOT_BUSY         0X80
#define FM_BUF2MEM_MISMATCH 0X40
#define FM_MEMSZ_256        0X01
//********************* Flash Size Defines *******************
//**** Operations are base on Atmel AT45DBx41D type chip with buffers
#define FM_CHIPSIZE			0X40000 //32Mb/4MB
#define FM_SECTORSIZE		0XFA00	//64KB
#define FM_BLOCKSIZE		0XFA0	//4KB
#define FM_PAGESIZE			0X200	//512B
//********************* Atmel Flash Operation Defines *******************
#define FM_PAGEERASE		0X81
#define FM_BLOCKERASE		0X5A0
#define FM_SECTORERASE		0X7C
#define FM_READSTAT		0XD7 
#define FM_WRITESTAT1		0X00
#define FM_WEN			0X06 //Write Enable	
#define FM_BUFF1WRITE 		0X84 //Write Buffer 1 memory location
#define FM_BUFF2WRITE 		0X87 //Write Buffer 2 memory location
#define FM_MEM2BUFF1		0X53 //Main memory to buffer 1
#define FM_MEM2BUFF2		0X55 //Main memory to buffer 2
#define FM_BUFF1_2MEM_ERS	0X83 //Buffer 1 to main memory with pre erase
#define FM_BUFF2_2MEM_ERS	0X83 //Buffer 2 to main memory with pre erase		

//******************* Modbus Memory buss managment functions **********************

void InitSPI1MemBus(void); 
void CheckNVMemory(void);
uChar SPI1_WR(uChar Data);
/************************************************************************
            Program Flash memory function calls 
**********************************************************8****************/


uInt PM_WriteChars(uInt Address, uInt numValues, uChar *charArray, char New);
uInt PM_ReadChars(uInt Address, uInt numValues, uChar *charArray);
uInt PM_WriteStrings(uInt Address, uInt numValues, uChar *Strin, char Newg);
uChar* PM_ReadStrings(uInt Address, uInt numValues, uChar *String);

/*******************************************************************
 *                       EEProm Memory Function Prototypes 
 ****************************************************************************/

uInt  EP_Status(void);
void  EP_WriteEnable(void);
void  EP_WriteDisable(void);
uInt  EP_WriteChars(uInt Address, uInt numValues, uChar *charArray, char New);
uInt  EP_ReadChars(uInt Address, uInt numValues, uChar *charArray);


/***************************************************************************
                    Flash Memory Function Prototypes 
*******************************************************************************/
void    InitFMMemBus(); //Sets phase and speed
uInt    FM_Status();
void   	FM_ErasePage(uInt PageNumber);// 256 or 265 bytes
void   	FM_EraseBlock(uInt BlockNumber);// 8 Pages
void   	FM_EraseSector(uInt SectorNumber); //0a = 1 Block, 0b = 31 blocks, all others 32 = blocks
uInt 	FM_WriteChars(uInt Address, uInt numValues, uChar *charArray, char New);
uInt 	FM_ReadChars(uInt Address, uInt numValues, uChar *charArray);


// ***************  Ramtron Memory Function Prototypes ****************
//Does not have page write so doesn't need the new parameter 
uInt    RT_WriteChars(uInt Address, uInt numValues, uChar *charArray);
uInt    RT_ReadChars(uInt Address, uInt numValues, uChar *charArray);
uInt    RT_WriteString(uInt Address, uInt numValues, uChar *String);
uChar*  RT_ReadString(uInt Address, uInt numValues, uChar *String);
#endif

/********************************************************************************
 *                Conversion Utilities
 *****************************************************************************/
uChar* Shorts2Chars(uShort *sData);
uShort* Chars2Shorts(char *cData);