#include "../modbus.h"

//#include "uart.h"
//#include "adc.h"


//CRC Tables
 const unsigned char hiCRCbyte[] = {
   0x00, 0xc1, 0x81, 0x40, 0x01, 0xc0, 0x80, 0x41, 0x01, 0xc0, 0x80, 0x41, 0x00, 0xc1, 0x81,
   0x40, 0x01, 0xc0, 0x80, 0x41, 0x00, 0xc1, 0x81, 0x40, 0x00, 0xc1, 0x81, 0x40, 0x01, 0xc0,
   0x80, 0x41, 0x01, 0xc0, 0x80, 0x41, 0x00, 0xc1, 0x81, 0x40, 0x00, 0xc1, 0x81, 0x40, 0x01,
   0xc0, 0x80, 0x41, 0x00, 0xc1, 0x81, 0x40, 0x01, 0xc0, 0x80, 0x41, 0x01, 0xc0, 0x80, 0x41,
   0x00, 0xc1, 0x81, 0x40, 0x01, 0xc0, 0x80, 0x41, 0x00, 0xc1, 0x81, 0x40, 0x00, 0xc1, 0x81,
   0x40, 0x01, 0xc0, 0x80, 0x41, 0x00, 0xc1, 0x81, 0x40, 0x01, 0xc0, 0x80, 0x41, 0x01, 0xc0,
   0x80, 0x41, 0x00, 0xc1, 0x81, 0x40, 0x00, 0xc1, 0x81, 0x40, 0x01, 0xc0, 0x80, 0x41, 0x01,
   0xc0, 0x80, 0x41, 0x00, 0xc1, 0x81, 0x40, 0x01, 0xc0, 0x80, 0x41, 0x00, 0xc1, 0x81, 0x40,
   0x00, 0xc1, 0x81, 0x40, 0x01, 0xc0, 0x80, 0x41, 0x01, 0xc0, 0x80, 0x41, 0x00, 0xc1, 0x81,
   0x40, 0x00, 0xc1, 0x81, 0x40, 0x01, 0xc0, 0x80, 0x41, 0x00, 0xc1, 0x81, 0x40, 0x01, 0xc0,
   0x80, 0x41, 0x01, 0xc0, 0x80, 0x41, 0x00, 0xc1, 0x81, 0x40, 0x00, 0xc1, 0x81, 0x40, 0x01,
   0xc0, 0x80, 0x41, 0x01, 0xc0, 0x80, 0x41, 0x00, 0xc1, 0x81, 0x40, 0x01, 0xc0, 0x80, 0x41,
   0x00, 0xc1, 0x81, 0x40, 0x00, 0xc1, 0x81, 0x40, 0x01, 0xc0, 0x80, 0x41, 0x00, 0xc1, 0x81,
   0x40, 0x01, 0xc0, 0x80, 0x41, 0x01, 0xc0, 0x80, 0x41, 0x00, 0xc1, 0x81, 0x40, 0x01, 0xc0,
   0x80, 0x41, 0x00, 0xc1, 0x81, 0x40, 0x00, 0xc1, 0x81, 0x40, 0x01, 0xc0, 0x80, 0x41, 0x01,
   0xc0, 0x80, 0x41, 0x00, 0xc1, 0x81, 0x40, 0x00, 0xc1, 0x81, 0x40, 0x01, 0xc0, 0x80, 0x41,
   0x00, 0xc1, 0x81, 0x40, 0x01, 0xc0, 0x80, 0x41, 0x01, 0xc0, 0x80, 0x41, 0x00, 0xc1, 0x81,
   0x40
} ;

const unsigned char lowCRCbyte[] = {
   0x00, 0xc0, 0xc1, 0x01, 0xc3, 0x03, 0x02, 0xc2, 0xc6, 0x06, 0x07, 0xc7, 0x05, 0xc5, 0xc4,
   0x04, 0xcc, 0x0c, 0x0d, 0xcd, 0x0f, 0xcf, 0xce, 0x0e, 0x0a, 0xca, 0xcb, 0x0b, 0xc9, 0x09,
   0x08, 0xc8, 0xd8, 0x18, 0x19, 0xd9, 0x1b, 0xdb, 0xda, 0x1a, 0x1e, 0xde, 0xdf, 0x1f, 0xdd,
   0x1d, 0x1c, 0xdc, 0x14, 0xd4, 0xd5, 0x15, 0xd7, 0x17, 0x16, 0xd6, 0xd2, 0x12, 0x13, 0xd3,
   0x11, 0xd1, 0xd0, 0x10, 0xf0, 0x30, 0x31, 0xf1, 0x33, 0xf3, 0xf2, 0x32, 0x36, 0xf6, 0xf7,
   0x37, 0xf5, 0x35, 0x34, 0xf4, 0x3c, 0xfc, 0xfd, 0x3d, 0xff, 0x3f, 0x3e, 0xfe, 0xfa, 0x3a,
   0x3b, 0xfb, 0x39, 0xf9, 0xf8, 0x38, 0x28, 0xe8, 0xe9, 0x29, 0xeb, 0x2b, 0x2a, 0xea, 0xee,
   0x2e, 0x2f, 0xef, 0x2d, 0xed, 0xec, 0x2c, 0xe4, 0x24, 0x25, 0xe5, 0x27, 0xe7, 0xe6, 0x26,
   0x22, 0xe2, 0xe3, 0x23, 0xe1, 0x21, 0x20, 0xe0, 0xa0, 0x60, 0x61, 0xa1, 0x63, 0xa3, 0xa2,
   0x62, 0x66, 0xa6, 0xa7, 0x67, 0xa5, 0x65, 0x64, 0xa4, 0x6c, 0xac, 0xad, 0x6d, 0xaf, 0x6f,
   0x6e, 0xae, 0xaa, 0x6a, 0x6b, 0xab, 0x69, 0xa9, 0xa8, 0x68, 0x78, 0xb8, 0xb9, 0x79, 0xbb,
   0x7b, 0x7a, 0xba, 0xbe, 0x7e, 0x7f, 0xbf, 0x7d, 0xbd, 0xbc, 0x7c, 0xb4, 0x74, 0x75, 0xb5,
   0x77, 0xb7, 0xb6, 0x76, 0x72, 0xb2, 0xb3, 0x73, 0xb1, 0x71, 0x70, 0xb0, 0x50, 0x90, 0x91,
   0x51, 0x93, 0x53, 0x52, 0x92, 0x96, 0x56, 0x57, 0x97, 0x55, 0x95, 0x94, 0x54, 0x9c, 0x5c,
   0x5d, 0x9d, 0x5f, 0x9f, 0x9e, 0x5e, 0x5a, 0x9a, 0x9b, 0x5b, 0x99, 0x59, 0x58, 0x98, 0x88,
   0x48, 0x49, 0x89, 0x4b, 0x8b, 0x8a, 0x4a, 0x4e, 0x8e, 0x8f, 0x4f, 0x8d, 0x4d, 0x4c, 0x8c,
   0x44, 0x84, 0x85, 0x45, 0x87, 0x47, 0x46, 0x86, 0x82, 0x42, 0x43, 0x83, 0x41, 0x81, 0x80,
   0x40
} ;

/*============================================================================*/

uChar  mbIndex, fIndex,txLength;//uartIndex;
uShort mbCmdIndex= 0;	//used to parse serial command from master
uShort mbCommand = 0 ; //Command from serial port
uShort mbParam1 	= 0; //Param1 from serial port
uShort mbParam2 	= 0;	// Param2 from serial port
uShort sParam3 	= 0;	// Param2 from serial port
uShort sParam4 	= 0;	// Param2 from serial port
uChar  cmdLength = 0;	// Used by CRC to check and append messages
uShort MBMem[10];
uShort MB_Buffer[MB_MEM_SZ];


uShort rxBuffIndex = 0 ;
uChar  lowCRC, highCRC,indexCRC;

//write persistant variable from NV memory at MB Location
char WriteSysVarFromMBAddress(uShort MBRegNum)
{
    uShort CurrentRegAddress = 0;
    uShort RegisterIndex = 0;
    while(CurrentRegAddress <= MBRegNum)
    {
        /*
        if(MBRegNum == PersistantMBVars[RegisterIndex].regAddress);
        {
            
            //Go get info from flash
            return 0;
        }
        */
    }

}
//
char ChangeSysVarAtMBAddress(uShort MBRegNum)
{

}
/*
char LoadAllSysVarsFromMBMemory(ModbusSysReg *MBAddressArray)
{

}*/
/*
Modbus Register Addresses 0X0001 - 0X01FF: (511 Registers, 1024 bytes) MCU Memory - Non Persistent
Modbus Register Addresses 0X0200 - 0X7D32: Ramtron(32K chip) Persistent
Modbus Register Addresses 0X7D33 - 0X200000: Atmel 32K Flash memory for files
*/
void LoadTestData()
{
    
	MBMem[0] = 1000;//jk dummy data		
	MBMem[1] = 11;//jk dummy data	
	MBMem[2] = 222;//jk dummy data	
	MBMem[3] = 3333;//jk dummy data
	MBMem[4] = 41444;//jk dummy data
	MBMem[5] = 5555;
	MBMem[6] = 666;				
	MBMem[7] = 777;			
	MBMem[8] = 888;
	MBMem[9] = 999;				
	MBMem[10] = 1010;	

}
/****************************************************************************
*   FUNCTION:       ProcessMBCommand(void)                                   *
*                                                                           *
*   DESCRIPTION:    Looks at the MBBUff char array. Does not extract ID 
 *                  Because that has already been qualified in uart.c.
 *                  Extracts the command and the two parameters if msgState 
 *                  is less than one. Runs the command though a switch, if
 *                  the command does not need more bytes, it will process
 *                  the command otherwise the function returns the number of 
 *                  bytes required.  If ProcessMBCommand is run with msgState
 *                  non-zero, the capture command and the capture parameters
 *                  skipped.  The switch is run and the appropriate command
 *                  extracts the rest of the required bytes and runs the command 
*                                             *
*   PARAMETERS:     cmdBuffer(uChar) - any char buffer but uart.c uses mbBuff
 *                  BytesToFinishCmd(uChar) - if zero, assumes 8 bytes have been
 *                  captured. If not zero, function assumes that the number in
 *                  BytesToFinishCmd + 8 is the number total captured to that
 *                  point and compares that to the number of bytes required
 *                  to implement the command.                                            *
*   
 * WARNING:         The process of extracting and running a MB command is not
 *                  to start with less then 8 bytes.  When msgState is zero,
 *                  the function assumes 8 bytes have been captured.  Any not
 *                  zero number is the number of bytes needed to finish the 
 *                  command, including the CRC check.  If mis-handled, the CRC
 *                  numbers will not end up going to the CRC check.
 *                  to b                                                                         *
*   RETURNS:        Zero if there were enough bytes to implement command, else
 *                  returns the num of bytes to finish command. Returns zero if
 *                  there were eneough bytes to implement command but there was
 *                  an error.  Errors are loged though another module
 *  
 *                  1 if unitID found but in row are found then returns 1 *
*                                                                           *
*   REVISION:  0    v1.0                DATE:  12/10/2012            *
                                                   *
****************************************************************************/
uShort ProcessMBCommand(uChar* CmdBuffer, uChar BytesToFinishCmd, uChar UnitID)
{	
	
    if(BytesToFinishCmd <= 0)
    {
        mbCmdIndex = 1;	//Skip unit ID
	//Log Command
	mbCommand = CmdBuffer[mbCmdIndex++];
	// Log Param1
	mbParam1 =  CmdBuffer[mbCmdIndex++]<<8;
	mbParam1 += CmdBuffer[mbCmdIndex++]&0x00FF;
	// Log Param2
	mbParam2 = CmdBuffer[mbCmdIndex++]<<8;
	mbParam2 += CmdBuffer[mbCmdIndex++]&0x00FF;
	//Start building response
    }
    switch(mbCommand)
    {	
        case 1:

                break;
        case 2:

                break;
        case mbREAD_HOLDINGREGS: //0x03, 3 Reads and returns a number of holding registers
            //Will use either SRAM or Ramtron memory based on address requested
            if(rxCRCCheck(CmdBuffer,MIN_MB_MSG_SZ) == 1)//This command is always 8 bytes including CRC check
            {
                    txLength = 0;
                    CmdBuffer[txLength++] = CmdBuffer[0];//Send Back Unit ID
                    CmdBuffer[txLength++] = CmdBuffer[1];//Send back command
                    CmdBuffer[txLength++] = mbParam2;//Send Back num reg's to read
                    /*
                    if(mbParam1 >= LOWER_NV_MEM_ADDRESS)//Use the ramtron
                    {
                            //Is this read all within the Ramtron ?
                            if(mbParam1 + (mbParam2 * 2) > MAXRAMTRONADDRS)//If not send error
                            {
                                    SendErrorResponse(CmdBuffer,mbBAD_ADDRESS, UnitID); //bad address
                                    return 0;//no need to get more of rxBuff
                            }
                            //txLength += ReadRTChars(mbParam1,mbParam2 * 2, &CmdBuffer[txLength]);
                            TXMODBUS("Return Ramtron",14);
                            //TXMODBUS(CmdBuffer,txLength);
                    }
                    // Does this read stay within the MCU memory?
                    if(mbParam1 + (mbParam2 * 2) > MAXRAMTRONADDRS)//0X7D32(32,050)Num Reg go beyond memory size
                    {
                            SendErrorResponse(CmdBuffer,mbBAD_ADDRESS,UnitID); //bad address
                    }
                    //txLength += ReadMBArray2Chars(mbParam1,mbParam2,&CmdBuffer[txLength]);
                    //txLength = AppendCRC(CmdBuffer, txLength);
                    //TXMODBUS(CmdBuffer, txLength);
                    //TXMODBUS("Return Not Ramtron",17);
                     **/
                     return 0;
            }   
            break;
        case mbWRITE_REGISTER: //0x06 - Write then return single register
            /*
            if((mbParam1 + (mbParam2 * 2)) > MB_MEM_SZ) // Are you requesting more registers than memory
            {
                SendErrorResponse(CmdBuffer,mbBAD_ADDRESS,UnitID); //2 = error code for address not ok
              return 0;              
            }
            else
            {
                    //if(NumBytesCaptured < 8) return 8;//Get remaining bytes
                    mbCmdIndex = 0;
                    if(rxCRCCheck(CmdBuffer, mbParam2 * 2) == 1)
                    {
                            if((mbParam1 + mbParam2) > MB_MEM_SZ)
                            {
                                    CmdBuffer[1] = 83;//Send back error notification
                                    CmdBuffer[2] = 2;// Error in address or quantity of registers
                                    txLength = 3;
                            }
                            else
                            {
                                    MBMem[mbParam1 - 1] = mbParam2;
                                    CmdBuffer[mbCmdIndex] = MBMem[mbParam1 - 1]>>8;
                                    CmdBuffer[mbCmdIndex] = MBMem[mbParam1 - 1] & 0XFF;
                            }
                            txLength = AppendCRC(CmdBuffer, mbCmdIndex);
                            TXMODBUS(CmdBuffer,8); // Just respond with the same message
                    }	//
            }
            */
            break;
        case mbDIAGNOS_SERIAL:

            break;
        case mbWRITE_MULTI_REGS://(0X10)Write Multiple Registers. Return Cmd, Start Addrss, NumRegs
            if(BytesToFinishCmd <= 0)
            {
                //The '9' is for single uChar ByteCount param plus the 8 bytes in the command
                if(mbParam2 > 0 ) return (mbParam2 * 2) + 9;//Num bytes needed to finish msg
            }


            if(rxCRCCheck(CmdBuffer,(mbParam2 * 2) + MIN_MB_MSG_SZ) == 1)
            {
                txLength = rxBuffIndex = 0; //Start prepairing response
                CmdBuffer[txLength++] = CmdBuffer[rxBuffIndex++];//Send Back Unit ID
                CmdBuffer[txLength++] = CmdBuffer[rxBuffIndex++];//Send Back command
                CmdBuffer[txLength++] = CmdBuffer[rxBuffIndex++];//Send High byte of Address
                CmdBuffer[txLength++] = CmdBuffer[rxBuffIndex++];//Send low byte of address
                CmdBuffer[txLength++] = CmdBuffer[rxBuffIndex++];//Send High byte of num regs
                CmdBuffer[txLength++] = CmdBuffer[rxBuffIndex++];//Send low byte of num regs
                /*
                if(mbParam1 >= LOWER_NV_MEM_ADDRESS)//Write to Ramtron
                {
                        if((mbParam1 + (mbParam2 * 2)) > MAXRAMTRONADDRS)//Is the write within RT memory bounds?
                        {
                                //if not send error
                                SendErrorResponse(CmdBuffer,2,UnitID); //bad address
                                return 0;
                        }
                        mbParam1 -= 1; //Internal MB memory is zero indexed
                        rxBuffIndex++;//Skip over byte count
                       // WriteRTChars(mbParam1 - OFFSET2RAMTRON, mbParam2*2, &CmdBuffer[rxBuffIndex]);
                        txLength = AppendCRC(CmdBuffer, txLength);
                        TXMODBUS(CmdBuffer,txLength); // Just respond with the same message
                        return 0;
                }
                if((mbParam1 + (mbParam2 * 2)) > LOWER_NV_MEM_ADDRESS)//Is the write within MBMem memory bounds?
                {
                        //if not send error
                        SendErrorResponse(CmdBuffer, 2,UnitID); //bad address
                        return 0;
                }*/
                //Write to MBMem
                mbParam1 -= 1; //Internal MB memory is zero indexed
                mbParam2 += mbParam1; //Normalize the num of regs to write
                rxBuffIndex++;//Skip over byte count
                while(mbParam1 < mbParam2)
                {/*
                        MBMem[mbParam1] = CmdBuffer[rxBuffIndex++] << 8;
                        MBMem[mbParam1++] += CmdBuffer[rxBuffIndex++];
                  */
                }
                txLength = AppendCRC(CmdBuffer,txLength);
                TXMODBUS(CmdBuffer,txLength); // Just respond with the same message
            }
            return 0;
            break;
        case mbRDWR_MULTI_REGS:
            return 2;
            break;
        case cmdREADINTS: //0x64(100)   Read waveforms
            //ReadInts(WvFmIn1,sParam1);
            break;
        case cmdWRITEINTS://0x66, 102
            //WriteInts(x1,2);
            break;
        case cmdWRITECHARS://0x67, 103
            //Sprintf(txAppBuff,"Param1 is %d, Param2 is %d\n\r",sParam1,sParam2);
            //WriteChars(charData, sParam1);//txAppBuff, strlen(txAppBuff))
            //TransmitInts(x1,2);
            break;
        case cmdRW_WVFM://0x68, 104
                //ReadAIN5(sParam1,sParam2);
                break;
        case 112:
        //	sprintf(txAppBuff,"Param1 is %d, Param2 is %d\n\r",sParam1,sParam2);
            //TransmitChars("HelloJK\n",8);//txAppBuff, strlen(txAppBuff));
            //MachineState != s_RXCMPLETE;
            break;
        case cmdRW_CHARS://0x69, 105

            //ReadChars(charData,sParam1);
            //WriteChars(charData,sParam1);
            //sprintf(txAppBuff,"Param1 is %d, Param2 is %d\n\r",sParam1,sParam2);
            ////WriteChars("HelloJK\n",8);//txAppBuff, strlen(txAppBuff))

            //TransmitInts(x1,2);
            break;
        case cmdRDCHVLT:
                //ReadChannelVoltage(sParam1);
                break;
        default:
                SendErrorResponse(CmdBuffer,1,UnitID); //Command not supported
                return 0;
                break;
    }

    return 0;
}
//Once process Modus command has finished and CRC checks out, 
//then run ImplementModbusCommand() which returns the index to the next
//txBuff location.
// Code saving function used by every command
//7/6/2011 finding that there are enough differences in commands to 
//make the function below unnecessary
uChar BuildResponseHeader(uChar *CmdBuffer, uShort CmdResponse, uChar UnitID)
{
	uChar mbCmdIndex = 0;
	CmdBuffer[mbCmdIndex++] = UnitID;//Send unit ID
	CmdBuffer[mbCmdIndex++] = mbCommand;//Send Command
	CmdBuffer[mbCmdIndex++] = CmdResponse << 8;//Send high byte of response
	CmdBuffer[mbCmdIndex++] = CmdResponse & 0X00FF;//Send low byte of response
	return mbCmdIndex;//returns 4
}

void SendErrorResponse(uChar *CmdBuffer,uChar ErrorCode, uChar UnitID)
{
	mbCmdIndex = 0;
	CmdBuffer[mbCmdIndex] = UnitID;//Send unit ID
	mbCmdIndex++;	
	CmdBuffer[mbCmdIndex] = CmdBuffer[mbCmdIndex]+0X80;//Send Command plus error offset
	mbCmdIndex++;	
	CmdBuffer[mbCmdIndex++] = 0;//Send high byte of starting address
	CmdBuffer[mbCmdIndex++] = ErrorCode;//Send low byte of starting addres
	mbCmdIndex = AppendCRC(CmdBuffer,mbCmdIndex);
	TXMODBUS(CmdBuffer,mbCmdIndex);
}	
/* This is marked for future deletion
void RunPendingCommand()
{
	if(sCommand == 0) return;
	switch(sCommand)
	{		
		case 1:

			break;		
		case 2:

			break;		
		case mbREAD_IREGISTERS: //0x04, 4
			
			break;
		case mbWRITE_REGISTER: //0x06
		
			break;
		default:
			//bad command
			break;
		sCommand = 0;
	}
}

*/
//Takes the current txIndex number and calculate the CRC
// on the array up to that point.
//Returns msLen + 2
uChar AppendCRC(uChar *cmdBuffer, uChar msgLen)
{

	lowCRC = 0xFF ; // high byte of CRC initialized 
	highCRC = 0xFF ; // low byte of CRC initialized
	for(fIndex=0; fIndex<msgLen; fIndex++) /* pass through message buffer */
	{
		indexCRC = lowCRC ^ cmdBuffer[fIndex] ; /* calculate the CRC */
		lowCRC = highCRC ^ hiCRCbyte[indexCRC ] ;
		highCRC = lowCRCbyte[indexCRC];
	}
	cmdBuffer[msgLen++] = lowCRC;
	cmdBuffer[msgLen++] = highCRC;
	return msgLen;
}


//Check CRC msgLength includes CRC
uChar rxCRCCheck(uChar * mbCmdBuff, uShort msgLength)
{
	lowCRC = 0xFF ; /* high byte of CRC initialized */
	highCRC = 0xFF ; /* low byte of CRC initialized*/
	for(fIndex = 0; fIndex < msgLength-2; fIndex++) //Do not include CRC
	{
		indexCRC = lowCRC ^ mbCmdBuff[fIndex]; /* calculate the CRC */
		lowCRC = highCRC ^ hiCRCbyte[indexCRC] ;
		highCRC = lowCRCbyte[indexCRC];
	}
	if(mbCmdBuff[fIndex++] == lowCRC)
	{
		if(mbCmdBuff[fIndex] == highCRC)
		{
			return 1;	
		}
	}
	return 0;
	
}
void SendReg(int RegNum)
{
	
}
void SendStrReg(char *Msg, int RegNum)
{
	
}
//Reads NumRegisters Modbus register(s) starting at start address 
/*/Returns the number of bytes added to the txBuffer
uChar ReadMCUMemory(uShort StartAddress, uChar NumRegisters, uChar TXLength)
{
	NumRegisters += StartAddress - 1;
	for(mbIndex = StartAddress - 1; mbIndex<NumRegisters; mbIndex++)
	{
		cmdBuffer[TXLength++] = MBMem[mbIndex] >> 8;
		cmdBuffer[TXLength++] = MBMem[mbIndex] & 0X00FF;
	}
	return TXLength;
}
uChar WriteMBMemory(uShort StartAddress, uChar NumRegisters, uChar TXLength)
{
	NumRegisters += StartAddress - 1;
	for(mbIndex = StartAddress - 1; mbIndex<NumRegisters; mbIndex++)
	{
		MBMem[mbIndex] = cmdBuffer[TXLength++] << 8;
		MBMem[mbIndex] += cmdBuffer[TXLength++];
	}
	return TXLength;
}
*/

