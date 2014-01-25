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
/***********************************************************************.
    Devices on the SPI bus are managed and controled by the spiBusStruct
    and the SPI_CSLow and SPI_CSHig functions.  By having as many definitions of
 *  data waveforms in the array of spiBusStuct as there are devices on the spi
 *  bus is is possible to have each device #defined as an index into the struct.
 *  That way you can also have each chip select pic defined and assigned to a
 *  switch with the same index as the struct */

typedef struct
{
    uChar cke;
    uChar smp;
    uChar ckp;
    uChar mode16;
}spiBusStruct;

void    SPI1_CSHigh(uChar CSIndex);
void    SPI1_CSLow(uChar CSIndex);
void    SPI1_CSHigh(uChar CSIndex);
void    SPI1_CSLow(uChar CSIndex);
void    ConfigSPI2Bus(uInt16 deviceIndex, uChar Mode16, uChar IE);
void    InitSPI1(void);
void    InitSPI2(void);
uChar   rwSPI1Char(char device, uChar Data);
uChar*  rwSPI1Chars(char device, uChar* Data, uInt16 Number);
uShort rwSPI1Short(char device, uShort Data);
uShort* rwSPI1Short(char device, uShort* Data, uInt16 Number);
uInt16  rwSPI1Int(char device, uInt16 Data);
uInt16* rwSPI1Ints(char device, uInt16* Data, uInt16 Number);
uChar   rwSPI2Char(char device, uChar Data);
uChar*  rwSPI2Chars(char device, uChar* Data, uInt16 Number);
uShort rwSPI2Short(char device, uShort Data);
uShort* rwSPI2Short(char device, uShort* Data, uInt16 Number);
uInt16  rwSPI2Int(char device, uInt16 Data);
uInt16* rwSPI2Ints(char device, uInt16* Data, uInt16 Number);
#endif
