/****************************************************************************
*   CREATED BY: 	Stillbright Managment LLC
*					Copyright 2010
*                                                                           
*   FILE:           mem_mgr.h
*                                                                           
*   DESCRIPTION:    Defines the memory map for storing variables for an application
                    into NV_Memory.  Ramtron will always be available and flash
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
*    5/12/12:    Striped everything out except the offset addresses for different memory
 *              operatations.                                                                           
*   8/20/2010: 	CREATED
    6/26/11:    Created BuildErrorHeader, Added
	        parameter to Build response header.  Started breaking
	        memory address down into different media.
    5/12/12:    Striped everything out except the offset addresses for different memory
 *              operatations.
 * 12/27/12     Separated persistent data routines from MB.  All MB 4000 addresses
 *              will call the persistant data routines in memory_map.h.
 *              Those routines will call the different routines in nv_devices.h
 *              which will write the data to different devices in spi.h.
 *              MB Address 30000 up to 40000  process result variables. While
 *              above 39999 will call persistant variables
 * 1/3/13       Only 30000 to 30199 and 4000 to 40199 numbered register addresses
 *              will be used.  To save nv memory, the 30001 range will be normalized
 *              down to the zero index in memory and the 40001 will be moved down
 *              nv index 500.
 * 01/29/13     Moved all references of MB to MB module.
 *              Defined a structure called cVar, each 6 bytes.
 *              Defined an array of 256 cVar pointers to cVars. Memory
 *              requirements to store the information of the cVars is 1536
 *              bytes.
 *              Defined a memory location that stores the total number
 *              of cVars used as 1538.
				
****************************************************************************/

#ifndef _MEMORY_MAP_H
#define _MEMORY_MAP_H

#include "../SYS_LIB/sysglobals.h"
#include "spi_memory.h"//
//#define MAX





#define typeShort   1
#define typeUShort  2
#define typeInt     3
#define typeUInt    4
#define typeFloat   5

//Structure that holds a void pointer to a variable location and
//a char that discribes  the type of variable that is being modified

typedef union fint
{
    int i;
    float f;
    uChar c[4];
}fiUnion;

typedef struct whatever
{
    fiUnion d; //stands for data
    uChar type;
    uChar index;
}cVar;
typedef struct NVMemory
{
    fiUnion dfltValue;
    fiUnion usrValue;
}nvSysVar;
#define NUMOF_MB_PVARS  3

//*************** Buffer for Reading and Writing to NV Memory ****************
#define NV_BUFFSZ 30 //Set the size of uInt buffer

extern uChar    nvCharBuff[NV_BUFFSZ]; // used to write cVars to nvMemory

extern cVar  u1Baud, unitID, kFactor, lowerAlarm;
/****************************************************************************
*   FUNCTION:   void WriteDefaults2NVMemory(void);                                                                                                           *
*   DESC:       This funtion is call to restore the all configurable vars
 *              to factory defaults                                         
 *   PARAMS:    none                                                         
 *   RETURNS:   nothing         * 
****************************************************************************/
void WriteDefaults2NVMemory(void);
/****************************************************************************
*   FUNCTION:   LoadUserConfiguredValues(void);                                                                                                           *
*   DESC:       This funtion is call at startup to retrieve and load all 
 *              user configured values to their respective variables                                    
 *   PARAMS:    none          
 *   RETURNS:   nothing         * 
****************************************************************************/
void LoadUserConfiguredValues(void);
/****************************************************************************
*   FUNCTION:   AddFloat2MemMgr(cVar *CVar, float DefaultVal);                                                                                                           *
*   DESC:       Used by  LoadNVArrayDefaultValues(void) as a developer
 *              friendly function to show what cVars being used and where in 
 *              the array they are located.
 *   PARAMS:    CVar* - pointer to the cVar being used in the application
 *              float - Default value to be used at initial startup
 *   RETURNS:   nothing         
****************************************************************************/
void AddFloat2MemMgr(cVar *CVar, float DefaultVal);
/****************************************************************************
*   FUNCTION:   AddInt2MemMgr(cVar *CVar, float DefaultVal);                                                                                                           *
*   DESC:       Used by  LoadNVArrayDefaultValues(void) as a developer
 *              friendly function to show what cVars being used and where in
 *              the array they are located.
 *   PARAMS:    CVar* - pointer to the cVar being used in the application
 *              float - Default value to be used at initial startup
 *   RETURNS:   nothing
****************************************************************************/
void AddInt2MemMgr(cVar *CVar, int DefaultVal);
/****************************************************************************
*   FUNCTION:   AddUInt2MemMgr(cVar *CVar, float DefaultVal);                                                                                                           *
*   DESC:       Used by  LoadNVArrayDefaultValues(void) as a developer
 *              friendly function to show what cVars being used and where in
 *              the array they are located.
 *   PARAMS:    CVar* - pointer to the cVar being used in the application
 *              float - Default value to be used at initial startup
 *   RETURNS:   nothing
****************************************************************************/
void AddUInt2MemMgr(cVar *CVar, uInt DefaultVal);
/****************************************************************************
*   FUNCTION:   ChangeVarValue(cVar *CVar);                                                                                                           *
*   DESC:       Used by the menuing and modbus modules to allow the changing of
 *              values
 *
 *   PARAMS:    CVar* - pointer to the cVar being used in the application.  This
 *              value should be changed before sending it to this function
 *   RETURNS:   nothing
****************************************************************************/
int  ChangeNVVarValue(cVar *CVar);

#endif


