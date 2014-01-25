/*****************************************************************************
 *
 * Basic access to I2C EEPROM 24LC01 located on MikroE PIC32MX4 MMB
 *
 * API is compatible with MCHP PICTail GFX2/3 serial EEPROM support
 *****************************************************************************
 * FileName:        SerialEEPROM.h
 * Dependencies:    Graphics.h
 * Processor:       PIC32
 * Compiler:       	MPLAB C32
 * Linker:          MPLAB LINK32
 * Company:         Microchip Technology Incorporated
 *
 * Software License Agreement
 *
 * Copyright © 2008 Microchip Technology Inc.  All rights reserved.
 * Microchip licenses to you the right to use, modify, copy and distribute
 * Software only when embedded on a Microchip microcontroller or digital
 * signal controller, which is integrated into your product or third party
 * product (pursuant to the sublicense terms in the accompanying license
 * agreement).  
 *
 * You should refer to the license agreement accompanying this Software
 * for additional information regarding your rights and obligations.
 *
 * SOFTWARE AND DOCUMENTATION ARE PROVIDED “AS IS” WITHOUT WARRANTY OF ANY
 * KIND, EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION, ANY WARRANTY
 * OF MERCHANTABILITY, TITLE, NON-INFRINGEMENT AND FITNESS FOR A PARTICULAR
 * PURPOSE. IN NO EVENT SHALL MICROCHIP OR ITS LICENSORS BE LIABLE OR
 * OBLIGATED UNDER CONTRACT, NEGLIGENCE, STRICT LIABILITY, CONTRIBUTION,
 * BREACH OF WARRANTY, OR OTHER LEGAL EQUITABLE THEORY ANY DIRECT OR INDIRECT
 * DAMAGES OR EXPENSES INCLUDING BUT NOT LIMITED TO ANY INCIDENTAL, SPECIAL,
 * INDIRECT, PUNITIVE OR CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA,
 * COST OF PROCUREMENT OF SUBSTITUTE GOODS, TECHNOLOGY, SERVICES, OR ANY
 * CLAIMS BY THIRD PARTIES (INCLUDING BUT NOT LIMITED TO ANY DEFENSE THEREOF),
 * OR OTHER SIMILAR COSTS.
 *
 * Author               Date        Comment
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Lucio Di Jasio       12/08/09	
 *****************************************************************************/

#include <plib.h>
#include "SerialEEPROM.h"


#define PAGESIZE    8               // page size for 24LC01 
#define PAGEMASK    (PAGESIZE-1)
#define BUSFRQ      100000ul          // 100kHz
/************************************************************************
* Function: EEPROMInit()
*                                                                       
* Overview: this function setups the I2C2 interface 
*                                                                       
* Input: none
*                                                                       
* Output: none  
*                                                                       
************************************************************************/
void EEPROMInit()
{  // Configure I2C for 7 bit address mode 
    int delay;
    
    CloseI2C2();
    OpenI2C2( I2C_ON | I2C_IDLE_CON | I2C_7BIT_ADD | I2C_STR_EN, 
            (GetPeripheralClock()/(2*BUSFRQ))-1);

    IdleI2C2();
    
    // approx 1ms delay
    for( delay = 0; delay < (GetPeripheralClock()/5/80000ul); delay++);
        
} // EEPROMInit
 
 
int addressSEE( long add)
// send the address selection command
// repeat if SEE busy 
{
    long cmd;
  
    // 1. form block address and SEE read command
    cmd = (add>>16) & 1;        // extract A16
    cmd <<= 2;                  // move it to b0 position
    cmd |= 0x50;                // select SEE device
    cmd <<= 1;                  // make room for READ bit
        
    // 2. WRITE(!) the Address msb
    // try send command and repeat until ACK is received
    while( 1)
    { 
        StartI2C2(); 
        IdleI2C2();
        
        // send command and address msb(3)
        MasterWriteI2C2( cmd+WRITE_CMD); 
        IdleI2C2();
        
        if (I2C2STATbits.ACKSTAT==0)
            break;
            
        StopI2C2();
        IdleI2C2();
    } // while waiting for ACK

#ifdef USE_LONG_ADDRESS
    // 3. send address MSB, bit 8-15
    MasterWriteI2C2( add>>8); 
    IdleI2C2();
#endif

    // 3. send address LSB, bit 0-7
    MasterWriteI2C2( add); 
    IdleI2C2();

    // 4. exit returning the cmd byte
    return cmd;
} // addressSEE
    
/************************************************************************
* Function: void EEPROMWriteByte()                                           
*                                                                       
* Overview: this function writes a byte to the address specified
*                                                                       
* Input: byte to be written and address
*                                                                       
* Output: none
*                                                                       
************************************************************************/
void EEPROMWriteByte(BYTE data, WORD address)
{
    int cmd; 
    
    // 1. select address
    cmd = addressSEE( address);
         
    // 2. stream data out 
    MasterWriteI2C2( data & 0xFF);  
    IdleI2C2();  


    // 3. terminate the command sequence
    StopI2C2(); 
    IdleI2C2();
    
} // EEPROMWriteByte   
  
  
    
/************************************************************************
* Function: BYTE EEPROMReadByte(WORD address)       
*                                                                       
* Overview: this function reads a byte from the address specified
*                                                                       
* Input: address          
*                                                                       
* Output: data read
*                                                                       
************************************************************************/
BYTE EEPROMReadByte(WORD address)
{
    int cmd, r; 
   
    // 1. select address
    cmd = addressSEE( address);
    
    StopI2C2();
    IdleI2C2();
      
    // 2. read command
    StartI2C2(); IdleI2C2();
    MasterWriteI2C2( cmd+READ_CMD);
    IdleI2C2();

    // 3. stream data in (will continue until NACK is sent)
    r = MasterReadI2C2( );
    
    // 4. terminate read sequence (send NACK then STOP)
    NotAckI2C2(); IdleI2C2();
    StopI2C2(); IdleI2C2();
    
    return r;
} // EEPROMReadByte 


/************************************************************************
* Function: void EEPROMWriteWord(WODR data, WORD address)                                           
*                                                                       
* Overview: this function writes a 16-bit word to the address specified
*                                                                       
* Input: data to be written and address
*                                                                       
* Output: none                                                         
*                                                                       
************************************************************************/
void EEPROMWriteWord(WORD data, WORD address)
{
    int cmd; 
    
    // 1. select address
    cmd = addressSEE( address);
         
    // 2. stream data out 
    MasterWriteI2C2( data & 0xFF);    //LSB
    IdleI2C2();  

    MasterWriteI2C2( data >> 8);      // MSB
    IdleI2C2();  

    // 3. terminate the command sequence
    StopI2C2(); 
    IdleI2C2();
    
} // EEPROMWriteWord
 
  
/************************************************************************
* Function: WORD EEPROMReadWord(WORD address)             
*                                                                       
* Overview: this function reads a 16-bit word from the address specified         
*                                                                       
* Input: address                                                     
*                                                                       
* Output: data read
*                                                                       
************************************************************************/
WORD EEPROMReadWord(WORD address)
{
    int cmd, r; 
   
    // 1. select address
    cmd = addressSEE( address);
    
    StopI2C2();
    IdleI2C2();
      
    // 2. read command
    StartI2C2(); IdleI2C2();
    MasterWriteI2C2( cmd+READ_CMD);
    IdleI2C2();

    // 3. stream data in (will continue until NACK is sent)
    r= MasterReadI2C2( );
    
    AckI2C2(); IdleI2C2();      
    r |= (MasterReadI2C2()<<8);

    // 4. terminate read sequence (send NACK then STOP)
    NotAckI2C2(); IdleI2C2();
    StopI2C2(); IdleI2C2();
    
    return r;
} // EEPROMReadWord 
 
 
/************************************************************************
* Function: EEPROMWriteEnable()                                       
*
* Overview: this function allows writing into EEPROM. Must be called
*           before every write/erase command
*
* Input: none
*            
* Output: none
*
************************************************************************/
void EEPROMWriteEnable() 
{ // empty, there is no WriteEnable/Disable sequence on 24LC01 memories
}    


/************************************************************************
* Function: BYTE EEPROMWriteArray(DWORD address, BYTE* pData, nCount)
*                                                                       
* Overview: this function writes data array at the address specified
*                                                                       
* Input: flash memory address, pointer to the data array, data number
*                                                                       
* Output: return 1 if the operation was successfull
*                                                                     
************************************************************************/
BYTE EEPROMWriteArray(DWORD address, BYTE* pData, WORD nCount)
{
    int cmd, i; 
    
    //  0. repeat in pages
    while ( nCount > 0)
    {
        // 1. select address
        cmd = addressSEE( address);
              
        // 2. (partial) page write 
        do {
            MasterWriteI2C2( *pData++ );       
            IdleI2C2();  
            nCount--;
            address++;
        } while ((( address & PAGEMASK) !=0) && (nCount > 0));
        
        // 3. terminate the command sequence
        StopI2C2(); 
        IdleI2C2();
    } // page repeat
        
    // verify 
    /// TBD
    
    return 1;   // success
} // EEPROMWriteArray


/************************************************************************
* Function: void EEPROMReadArray(WORD address, BYTE* pData, nCount)
*                                                                       
* Overview: this function reads  data into buffer specified
*                                                                       
* Input: flash memory address, pointer to the buffer, data number
*                                                                       
************************************************************************/
void EEPROMReadArray(WORD address, BYTE* pData, WORD nCount)
{
    int cmd, r; 
   
    // 1. select address
    cmd = addressSEE( address);
    
    StopI2C2();
    IdleI2C2();
      
    // 2. read command
    StartI2C2(); IdleI2C2();
    MasterWriteI2C2( cmd+READ_CMD);
    IdleI2C2();
    
    *pData++ = MasterReadI2C2( );    
    nCount--;
    
    // 3. stream data in (will continue until NACK is sent)
    while ( nCount > 0)
    {
        AckI2C2(); IdleI2C2();      
        *pData++ = MasterReadI2C2( );    
        nCount--;
    }
    
    // 4. terminate read sequence (send NACK then STOP)
    NotAckI2C2(); IdleI2C2();
    StopI2C2(); IdleI2C2();
    
} // EEPROMReadArray

