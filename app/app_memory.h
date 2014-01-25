/****************************************************************************
*   CREATED BY: 	Stillbright Managment LLC
*					Copyright 2010
*                                                                           
*   FILE:           sys_memory.h                                               
*                                                                           
*   DESCRIPTION:    Defines the memory map for storing variables for an application
                    into NV_Memory.  Ramtron will alwasy be avaialable and flash
                    may be used if a large amount of storage is required.

                    A predefined range at the beginning of each type of memory will 
                    be mirrored in both CPU RAM and NV Storage.  Mirrored memory will 
                    use  Ramton.
                    The types of memory will be
                    1. 	Application configuration parameters -  Uses flash if available.
                            Reads at start up and changes only when configuring
                    2.	Application memory - Will use RAM for application results but does
                            not need to be stored across startups.
                    3. 	NV_Application memory - Used to store appliction process
                            results accross start ups.  Trends, graphs, waveforms etc.
                            Words and floats will use Ramtron. Waveforms, files and trends points
                            will use flash.
                    The functions defined here will take an address and length and based upon
                    the user defined memory map will use the appropriate memory.
*                                                                           
*   8/20/2010: 	CREATED
    6/26/11:    Created BuildErrorHeader, Added
	        parameter to Build response header.  Started breaking
	        memory address down into different media.
    5/12/12:    Striped everything out except the offset addresses for different memory
 *              operatations.
				
****************************************************************************/

#ifndef _MEMORY_MAP_H
#define _MEMORY_MAP_H

typedef enum 
{
    nvRamtron,
    nvFlash,
    nvEEProm,
    nvProgamFlash
    
}nvMemType;
//address Numonics for non-volatile system variables
typedef struct xx
{
    nvMemType mem2Use;
    long icMemAddress;
}icAddress;

/*
Memory Map
0x0000 - 0x018E - 0-398 Dec. 200 Modbus int locations, 2 byte boundary
0x0190 - 0x031C - 400-796 Dec. 100 Modbus float locations, 4 byte boundary
0x06A4 - 0x07CF	- 1699-1990 Dec. 300 bytes for 60, 5 char prompts messages
0x07D0 - 0x2EDF - 2000 - 5099 Dec. 5K bytes for 150, 20 char strings on 20 byte boundaries


*/
/******************* Memory Map for Media Type
Modbus registers take two bytes per registers.  All register addresses must correspond to an even byte address in system memory.
Int arrays = register address, Flash and ramtron addresses = (Reg Address - 1) * 2
Modbus Register Addresses 0X0001 - 0X01FF: (511 Registers, 1024 bytes) MCU Memory - Non Persistent
Modbus Register Addresses 0X0200 - 0X7D32: Ramtron(32K chip) Persistent
Modbus Register Addresses 0X7D33 - 0X200000: Atmel 32K Flash memory for files
*/
#define OFFSET2RAMTRON      0X0200 //Beginning address for ramtron.
#define OFFEST2FLASH        0X7D34 //Beginning address for Atmel Flash
#define MAXRAMTRONADDRS     0X7D32 //Upper limit of ramtron memory..
#define MAXFLASHADDRESS     0X2000000 //Upper limit of all MB memories
//**************************** Memory boundaries *******************
#define INTMEMSTRT          0X0000
#define FLOATMEMSTRT        OX00C8
#define PROMTMEMSTRT        0X06A4
#define MSGMEMSTRT          0X0X40
// ************************** Memory object sizes ********************

//icAddrsss NormalizeAddress(long SystemAddress);

#endif

