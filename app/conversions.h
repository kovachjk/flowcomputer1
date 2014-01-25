/* 
 * File:   fllow_units.h
 * Author: JKovach
 * Description: Contains base unit definitions and conversion factors.
 *              
 * Revisions:   10/25/12 - Created.
 *              
 */

#ifndef FLLOW_UNITS_H
#define	FLLOW_UNITS_H

static float vConversions[3] = {1,3.5,5.6,};
/********************************************************************************************
                            VOLUME DEFINES
 *All calculated will be in gallons. cConversions will be done when displaying or reporting
 *******************************************************************************************/
#define gal     1 // Base units for volume
#define galIMP  0.83267418463
#define l       3.785411784
#define bbl     0.031746031745
#define bblPetro  0.023809523809
/********************************************************************************************
                            WEIGHT DEFINES
 *All calculated will be in pounds. Conversions will be done when displaying or reporting
 *******************************************************************************************/

/********************************************************************************************
                            TEMP DEFINES
 *All calculated will be in farenheit . Conversions will be done when displaying or reporting
 *******************************************************************************************/
/********************************************************************************************
                            PRESSURE DEFINES
 *All calculated will be in farenheit . Conversions will be done when displaying or reporting
 *******************************************************************************************/


#endif	/* FLLOW_UNITS_H */

