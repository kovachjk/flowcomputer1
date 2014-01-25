#ifndef _MSGMGR_H
#define _MSGMGR_H


//enum Msg States
#define	m_CHCKMSG	0x0001 // Check to make sure msg isn't hung+
#define	m_CMDRDY	0x0002	
#define m_MSGRDY	0x0004 //Enough bytes are in to make a msg
#define	m_RXCMPLETE 0x0010	

#define STRLENGTH		20
#define PROMPTLNGTH 	5


#define UNITID			190
#define BAUDRATE 		191
#define RXTIMEOUT		192 	// Time in mSec before comm reset
#define TACHRATE 		193		// 
#define TACHSOURCE		194		// 0=Interally Generated, 1=PLC writes number to location 193 
#define PPR				195 	// Pulses per revolution for tach

#endif