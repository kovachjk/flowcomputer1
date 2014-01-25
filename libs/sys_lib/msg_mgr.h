/* 
 * File:   errors.h
 * Author: JKovach
 *
 * Created on January 27, 2013, 6:41 AM
 */

#ifndef MSG_MGR_H
#define	MSG_MGR_H

/****************************************************************************
*   CREATED BY: 	Stillbright Managment LLC
*					Copyright 2010
*                                                                           
*   FILE:       msg_mgr.h
*                                                                           
* DESCRIPTION:  List of functions that manages a list of application messages
*               and message events. A list of up to 256 messages can be created.  
*               The index of a message is stored in non-volatile memory along 
*               with a time stamp stored when message events occure .
 *              Date Struct is:
 *
*               Msg String format is:
 *                  mm/dd/yr hr:mm-mn ShortDesc[20]                                    
*                   mn = message number
 * 1/23/13      Created
 *              
				
****************************************************************************/
#include "sysglobals.h"
#include "time_date.h"
#include "mem_mgr.h"

#define MSG_COUNT_ADDRS 9999 //NV mem location for number of msg events
#define MSG_LIST_ADDRS  10000 //Start address to list of address events
#define MSG_EVENT_LENGTH 8 //Num of bytes needed to store in NV memory

#define EmptyMsg 0
#define MBAddressErr 1
#define ADC_Err 2

//Msg zero is a place holder it will never be shown
//if msg index is ever zero, the string will be skipped
const char *EventMessage[] =
{
    "Empty Msg Holder",
    "MB Address Error",
    "ADC Error"
};
/*********************************************************************
* @Descripton Clears the event msg list
* @Param
********************************************************************/

void ResetMsgList();
/**
 * @Descripton 
 *      Saves a indexed reference to an error msg and a date time stamp to MV memory
 * @Param EventNum - uInt that references a text stream from an array of strings
*
********************************************************************/
void LogMsgEvent(uShort EventNum);
/**
 * @Description Builds one string combining all retrieved logged event descriptions.
 *              Does not return date/time stamp
 *              If there are no msgs, returns "No Logged Events", if there are
 *              not enough messages to meet the request, returns a string of
 *              logged events found
 * @param ListStart - Allows paging.
 * @param NumMsgs - Number of msgs to retieve for this page
 * @param sData - Pointer to external char buffer
 * @return  char* of retieved msgs
 */
char* ListMsgEventDesc(uShort ListStart, uShort NumMsgs, char *sData);

/**
 * @Descripton Returns formated string which includes date/time stamp and description
 *       of error.
 *              If there are no msgs, returns "No Logged Events", if there are
 *              not enough messages to meet the request, returns a string of
 *              logged events found
 * @param ListStart - Allows paging.
 * @param NumMsgs - Number of msgs to retieve for this page
 * @param sData - Pointer to external char buffer
 * @return  char* of retieved msgs
 */
char* ListMsgEventAll(uShort ListStart, uShort NumMsgs, char *sData);
/*********************************************************************
* @Descripton   Deletes individual msg event from NV memory.  Repacks the remaining
 *              msg events.
* @Param  EventNum - which event item out of the list to delete.  If
********************************************************************/

void DeleteMsgEvent(uShort EventNumber);

#endif	/* ERRORS_H */

