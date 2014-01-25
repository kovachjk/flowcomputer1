/****************************************************************************
*   CREATED BY: 	Stillbright Managment LLC
*					Copyright 2010
*                                                                           
*   FILE:           cmds_modbus.h                                               
*                                                                           
*   DESCRIPTION:    Defines all the constants and functions necessary
*					to implement the serial commands used in applicaiton        
*                                                                           
*   REVISIONS:      8/20/2010: Created
	            6/26/2011: Created BuildErrorHeader, Added
	            parameter to Build response header.  Started breaking
	            memory address down into different media.     
 *                  11/30/12:   Stripping out Stillbright commands.  Unifying
 *                  uart buffers
****************************************************************************/
#ifndef _MODBUS_H
#define _MODBUS_H
#include <string.h>
#include "../SYS_LIB/sysglobals.h"
#include "../../LIBS/SYS_LIB/spi_memory.h"
//#include "../../LIBS/SYS_LIB/ME"
//#include "../SYS_LIB/public_vars.h"
#include "../../LIBS/SYS_LIB/uarts.h"
#define	MODBUS		1
#define RIONET 		0
#define	PROTOCOL 	1

//#if PROTOCOL == MODBUS
	//#define RX_MSG_SZ 10	
//#else 
#define MIN_MB_MSG_SZ 8  //Smallest possible Modbus message size 
//#endif
 						/*******************************
                        **       Modbus Command Defines       **
                        *******************************/
                        

  



/******************************************************************/
/*      MODBUS and STILLBRIGHT COMMAND CODES                     */
/******************************************************************/
/*
 * #define MBSTART_LOWERBOUNDS  3980 //The amount subtracted from any mb register address
#define MBSTART_NV_MEMSTART     4000 //REGISTERS THAT CONFIGURE THE HARDWARE
#define MBSTART_UPPERBOUNDS     4050
Modbus Register Addresses 0X0001 - 0X01FF: (511 Registers, 1024 bytes) MCU Memory - Non Persistent
Modbus Register Addresses 0X0200 - 0X7D32: Ramtron(32K chip) Persistent
Modbus Register Addresses 0X7D33 - 0X200000: Atmel 32K Flash memory for files
*/


#define MODBUS_TIMEOUT  10u  //mSecs
//MODBUS COMMANDS
#define mbREAD_COILS               	0x01
#define mbREAD_INPUTS		        0x02 //Read single bit
#define mbREAD_HOLDINGREGS		0x03 //Write Holding Registers
#define mbREAD_INPUTREGS		0x04 //Write Input Registers
#define mbWRITE_COIL               	0x05 //Write singel coil
#define mbWRITE_REGISTER           	0x06
#define mbDIAGNOS_SERIAL		0x08
#define mbWRITE_MULTI_REGS           	0x10 //
#define mbRDWR_MULTI_REGS               0X17
#define mbWRITE_MULT_COIL          	0x0F
/******************************************************************/
/*      MODBUS ERROR CODES                                     */
/******************************************************************/
#define mbBAD_ADDRESS 2

/******************************************************************/
/*      MODBUS ERROR CODES                                     */
/******************************************************************/

#define cmdREADINTS 			0X64		// (100)Receive int waveform serially 
#define cmdREADCHARS			0X65
#define cmdWRITEINTS			0X66
#define cmdWRITECHARS			0X67
#define cmdRW_WVFM 			0x68		// (104)Get and return time Waveform 
#define cmdRW_CHARS			0x69
#define cmdCNFGADC 			0x70 		// Configure Channel number, Fmax, Lines,
#define cmdSETTACH 			0x71		// Configure pluses per rev,   

#define cmdRDCHVLT 					0x72 		// (22)Read Voltage of Parameter 1 as Channel

#define EX_MODBUS_READ_COILS            0x81
#define EX_MODBUS_READ_DISCRETEINPUTS   0x82
#define EX_MODBUS_READ_INPUTREGISTERS   0x84
#define EX_MODBUS_WRITE_COIL            0x85
#define EX_MODBUS_WRITE_REGISTER        0x86


//************************** STRINGS *****************************
//      START AT 30000(0X7530) AND ARE MAX 16 BYTES LONG

//************************ WAVEFORM DATA AND CONTROL *****************************
#define WF1COMMAND	20 //0=None, 1=StartStop, 2=ChangeAmplitue, 3=ConfigType, 4=SaveRunState
#define WF1TYPE		21 //1=SquareWave, 2=ConfigWaveformSeries, 3=Config3Waveforms,4=Triangle
#define WF1FREQ		22 //Base Freq
//if ConfigWaveformSeries(BaseFreq, PARAM1=NumMultiples)
//if Config3Waveforms(BaseFrq, PARAM1 times BaseFreq, PARAM2 time BaseFreq)
#define WF1PARAM1	23 
#define WF1PARAM2	24
#define WF1AMPLTD	25
#define WF1ENABLE	26
#define WF1RUNSTATE	27

#define WF2COMMAND	28
#define WF2TYPE
#define WF2NEW 		29 //Tells state machine to set other parameters
#define WF2FREQ		30 
#define WF2PARAM1	31
#define WF2PARAM2	32
#define WF2ENABLE	33
#define WF2RUNSTATE	34



/*
	ProcessSerialMsg takes the number of bytes captured looks at the command
	sitting in the rxBuff array to see if the number of bytes requied by the 
	command have been satified. If not, it returns the number of bytes requested
	by the command. The number of bytes required is returned before any CRC 
	check is done on the validity of the command.
	If number of bytes is satisfied it returns zero then runs the rxBuff through
	the CRC check to see if everthing is valid. If it is, the command is run a 
	response is generated and loaded into the txBuff, if not then an error sent
 *      to the txBuff
*/
extern uShort MB_Buffer[MB_MEM_SZ];// Temporary working registers for MB Commands

char WriteSysVarAtMBAddres(uShort MBRegNum);
char ChangeSysVarAtMBAddress(uShort MBRegNum);
//char LoadAllSysVarsFromMBMemory(PersistantVars *MBAddressArray);
char SetAllPersistVarsToDefault(void);
uShort ProcessMBCommand(uChar* cmdBuffer, uChar BytesToFinishCmd,uChar UnitID);//process serial message from PLC
/* 	RunPendingCommand izCalled by state machine when time waveforms are requested or
	DSP routines need to be run,  Usually needed by the RioNet protocol.
*/
void    LoadTestData();//Development function for loading test data into MB Memory
void 	RunPendingCommand();
uChar	AppendCRC(uChar *mbCmdBuff, uChar msgLen);//Appends to txBuff, Returns msgLength+2
//Returns 1 or 0 depending on Check of CRC
uChar 	rxCRCCheck(uChar * mbCmdBuff,uShort msgLen);
void 	SendReg(int RegNum);
uChar   BuildResponseHeader(uChar *mbCmdBuff,uShort CmdResponse,uChar UnitID);//returns number of bytes in header;
// Builds header for error message returns
void    SendErrorResponse(uChar *CmdBuff,uChar ErrorCode,uChar UnitID);//returns number of bytes in header;
uChar   ReadMBMemory(uShort StartAddress, uChar NumRegisters,uChar TXLength);
uChar   WriteMBMemory(uShort StartAddress, uChar NumRegisters,uChar TXLength);

void 	SendStrReg(char *Msg, int RegNum);
#endif

