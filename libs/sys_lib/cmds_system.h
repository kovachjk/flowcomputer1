/****************************************************************************
*   CREATED BY: 	Stillbright Managment LLC
*					Copyright 2012
*                                                                           
*   FILE:           cmds_system.h                                               
*                                                                           
*   DESCRIPTION:   	Defines enums for opperating the command system as well as
					the enum used to call function used by the user to operate the system.
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

//* ************** COMMAND LIST FOR SYSTEM OPERATION ***************
#define scmd_SETID 			0x0010	// Getting Wavefrm to put in buffer. Used only on auto acquire
#define scmd_SETBAUD		0x0020	// Waveform is ready
#define scmd_DOFFT			0x0040	// Do FFT on whateve wvfm is in buffer
#define scmd_ANALYZWVFM 	0x0080	// Analyze waveform and 

/
#endif