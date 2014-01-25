/****************************************************************************
*   CREATED BY: 	Stillbright Managment LLC
*					Copyright 2012
*                                                                           
*   FILE:           msg_globals.h                                               
*                                                                           
*   DESCRIPTION:   	Defines enums for messaging and command system for
					both all the command the user would need to configure the 
					the system and/or the application running under the system.
*                                                                           
*   2/16/2012: 	CREATED
	
				
****************************************************************************/

#ifndef _MSG_GLOBALS_H
#define _MSG_GLOBALS_H


//enum Command States
#define	cmds_CHCKRX1		0x0001 // Check to make sure command isn't hung+
#define	cmds_CMDRDY1		0x0002	
#define cmds_MSGRDY1		0x0004 //Enough bytes are in to make a command
#define	cmds_RXCOMPLETE1	0x0010	

#define STRLENGTH		20
#define PROMPTLNGTH 	5

//* ************** COMMAND LIST FOR SYSTEM ***************
#define scmd_SETID 		0x0010	// Getting Wavefrm to put in buffer. Used only on auto acquire
#define scmd_SETBAUD		0x0020	// Waveform is ready
#define scmd_DOFFT			0x0040	// Do FFT on whateve wvfm is in buffer
#define scmd_ANALYZWVFM 	0x0080	// Analyze waveform and 

/* ************** COMMAND LIST FOR APPLICATION ***************
*/
#if defined (APP_VMU)
#define acmd_ACQWVFRM 		0x0010	// Getting Wavefrm to put in buffer. Used only on auto acquire
#define acmd_WVFMRDY		0x0020	// Waveform is ready
#define acmd_DOFFT			0x0040	// Do FFT on whateve wvfm is in buffer
#define acmd_ANALYZWVFM 	0x0080	// Analyze waveform and 
#endif
#endif