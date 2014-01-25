/*  ***************************************************************************
   CREATED BY: 	Stillbright Managment LLC
*					Copyright 2012
*
*   FILE:           spi.h
*
 *  DESCRIPTION:    This spi module is constucted to allow easy implementation
 *                  of multiple devices on the same bus.  After configuring the spi 
 *                  module for different devices, the user will call the four different spi
 *                  rw routines by referencing the index that holds the configuration settings
 *                  for that device.
 *                  User must first choose a name for the device to be on the bus.  The using
 *                  a #define, choose an index not used by another device.  Using that index,
 *                  the user will index to the spiBusStruct in  the spiDeviceArray
 *                  and configure it with the setting necessary for that device.
 * 
 *
 *  CREATED:    April 19 2012
 *  REVISION:   4/29/12 - Created struct to allow the dynamic configuration
 *              of different devices on a SPI bus.  Creadted defines as a central
 *              repository of indexes to bus configs for differnt types of spi
 *              devices.
****************************************************************************/
#ifndef __SPI_H_
#define __SPI_H_
#include "../SYS_LIB/sysglobals.h"
//

// All devices on a SPI bus will be defined here
// to make sure a SPI bus configured in another module is not overwriten
#define rtDevice 0
#define fmDevice 1
#define epDevice 2
/**************spiBusStruct ***************** \
 *  Description: Stores the configuration settings needed
 *  by different devices on the same spi bus.
 *  Create by
 */


typedef struct
{
    uChar cke;
    uChar ckp;
    uChar mode16;
}spiBusStruct;

extern spiBusStruct spi2DeviceArray[4];
void    ConfigSPI2Bus(uInt16 deviceIndex, uChar Mode16, uChar IE);
void    InitSPI1(void);
void    InitSPI2(void);
uChar   rwSPIChar(char device, uChar Data);
uChar*  rwSPIChars(char device, uChar* Data, uInt16 Number);
uInt16  rwSPIInt(char device, uInt16 Data);
uInt16* rwSPIInts(char device, uInt16* Data, uInt16 Number);
#endif
