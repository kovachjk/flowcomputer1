//#include "modbus.h"
//#include "p33FJ256GP710.h"
#include "../sysglobals.h"
#include "../spi_memory.h"
#include <plib.h>
//#include "../spi.h"

uShort 	sIndex; // Used in writing arrays to pages, no page is > 256
uInt 	*iNVBuff = 0; //Pointer to hold address to pending signed int array operations
uChar	*cNVBuff = 0; //Pointer to hold address to pending uChar array operations
long 	*lNVBuff = 0; // Pointer to buffer of longs for flash chips
float	*fNVBuff = 0; //Pointer to hold address to pending uDbl array operations
uInt 	nvMemStatus;
long	nextAddress2Write; //Holds the next non volital memory addres to be written
volatile uInt	numberRemaining; //Number of numbers(any type) left to write
//volatile uInt

uChar   mDevice0, mDevice0;// Index to the spiBusDevice array in spi.h



//Must be call first
void InitSPI1MemBus(void)
{
    SPI1CONbits.ON = 0;
    // Initialize SPI1
    SPI1STAT = 0;
    SPI1CON = 0;
    SPI1CONbits.MSTEN   = 1;
    SPI1CONbits.MODE16  = 0;
    SPI1CONbits.CKP     = 1;
    SPI1CONbits.CKE     = 0;
    SPI1CONbits.SMP     = 0;
    SPI1BRG = 15;
    SPI1CONbits.ON      = 1;

    // Set IOs directions for SFLASH SPI

    _TRISC2 = 0;    //U10(Ramtron) Chip select
    _TRISD10 = 0;   //CLK1
    _TRISC4 = 1;    //SDI1
    _TRISD0 = 0;    //SDO1

}
void InitRamtron(void)
{
        //Device settings for Ramtron
    // Initialize SPI1
    //SPI1CONbits.ON = 0;
    ///SPI1CONbits.CKP = 1;
    //SPI1CONbits.CKE = 0;
    //SPI1CONbits.SMP = 0;
    SPI1CON = 0x00008120; //=the above
    SPI1CONbits.MODE16 = 0;
    SPI1BRG = 15;//Different IC might need different speeds
    SPI1CONbits.ON = 1;

    // Set IOs directions for SFLASH SPI
   
    //SPI1CONbits.intEnable = 0;
}


void InitFlash(void)
{
    //Device settings for Flash Memory
    _TRISD12 = 0;
    fmChipSelect = 1;
    SPI1CONbits.CKE = 1;
    SPI1CONbits.CKP = 0;
    SPI1CONbits.MODE16 = 0;
    
}
void InitEProm(void)
{
    //Device settings for EEProm
    _TRISD12 = 0;
    epChipSelect = 1;
    SPI1CONbits.CKE = 1;
    SPI1CONbits.CKP = 0;
    SPI1CONbits.MODE16 = 0;
    //spi2DeviceArray[epDevice].intEnable = 0;
}


uChar SPI1_WR(uChar Data)//Write then read the SPI bus
{	
	
    NV_SPIBUFF = Data;
    while(!SPI1STATbits.SPIRBF); // Watch RX buff to see if TX is finished
    return NV_SPIBUFF;
}
void EP_WriteEnable()
{
    epChipSelect = 0;//Enable Chip
    SPI1_WR(NV_WEN); // Send write enable command
    epChipSelect = 1; //Enable chip to Finish write enable
}
void EP_WriteDisable()
{
    epChipSelect = 0;//Enable Chip
    SPI1_WR(NV_WDIS); // Send write disable command
    epChipSelect = 1; //Enable chip to Finish write enable
}
/*CheckNVMemory is for use with interrupts or DMA */


uInt EP_Status(void)
{
    uChar data = 0;
    fmChipSelect = 0;
    SPI1_WR(NV_READSTATE);
    data = SPI1_WR(0);
    fmChipSelect = 1;
    return data;//Disable Chip
}


uInt EP_WriteChars(uInt Address, uInt numChars, uChar *charArray, char New)
{
    uChar cIndex = 0;
    if((nvMemStatus > 0) && (New == 1)) return 1;//Cannot start new job until I finish old
    numberRemaining = numChars;//Save total number bytes to write
    if((Address + numberRemaining) > EP_CHIPSIZE) return 3; // not enough room for this operation
    while(EP_Status() & 0X01); // Wait for previous write to finish before disabling WEN
    EP_WriteDisable();//This should not be necessary but it stuck on once.
    cIndex = (Address/EP_PAGESIZE) + 1; //What memory page is tha address
    numChars = (EP_PAGESIZE * cIndex) - Address; //How many bytes can I write this page
    if(numberRemaining > numChars)//Do I need to write more than will fit on this page?
    {
            //numChars will write as many bytes as will fit in this page
            numberRemaining -= numChars; //Then save the number of bytes for next write

    }
    else //It all fits, just write number of bytes
    {
            numChars = numberRemaining;
            numberRemaining = 0;
    }
    EP_WriteEnable();
    epChipSelect = 0;//Enable Chip
    SPI1_WR(NV_WRITE);//Send the write command
    SPI1_WR(Address >> 8); //send address high byte
    SPI1_WR(Address & 0x00FE); //send address low byte, byte aligned
    for(cIndex = 0; cIndex < numChars; cIndex++)
    {
            SPI1_WR(charArray[cIndex]);
    }
    epChipSelect = 1;//Disable EP Chip

    if(numberRemaining > 0)//Do I need to come back and write more?
    {
            // Yes, set status and save parameters
            nvMemStatus = EP_MEMORY | CHAR_WRITING; //Set UART state machine.
            MachineState |= sys_RUNNVMEM; //Set System State Machine
            cNVBuff = &charArray[numChars]; //Save nvAddress of buffer to read from
            nextAddress2Write += nextAddress2Write; // Save EEProm Address for next NV write
    }
    else//reset to zero
    {
            nvMemStatus = 0; //Clear State Machine
            cNVBuff = 0;
            nextAddress2Write = 0;
    }
    return 0;
}
uInt EP_ReadChars(uInt Address, uInt numValues, uChar *charArray)
{
	uChar cIndex = 0;	
	if((Address + numValues) > EP_CHIPSIZE) return 3; 
	while(EP_Status() & 0X01); // Wait for previous write to finish before disabling WEN
	EP_WriteDisable();//This should not be necessary but it stuck on once.	EPWriteDisable();s() & 0x01);
	epChipSelect = 0;//Enable Chip
	SPI1_WR(NV_READ);//Send read command
	SPI1_WR(Address >> 8); //send address high byte
	SPI1_WR(Address & 0x00FE); //send address low byte, byte aligned
	for(cIndex = 0;cIndex < numValues; cIndex++)
	{
		charArray[cIndex] = SPI1_WR(0);
	}
	epChipSelect = 1;//Disable Chip
	return 0;	
}

uInt FM_Status()
{
	uChar data = 0;
	fmChipSelect = 0;
	SPI1_WR(NV_READSTATE);
	data = SPI1_WR(0);
	fmChipSelect = 1;
	return data;//Disable Chip
}
void   FM_ErasePage(uInt PageNumber)
{
	
}
void   FM_EraseFMBlock(uInt BlockNumber)
{
	
}
void   FM_EraseFMSector(uInt SectorNumber) //0a = 1 Block, 0b = 31 blocks, all others 32 = blocks
{

}

uInt RT_WriteChars(uInt Address, uInt NumBytes, uChar *Data)
{
    sIndex = 0;
    InitRamtron();
    while(NV_TXFULL); //Make sure we have finished from previous operation   
    //Wait if writing or reading
    if((Address + NumBytes) > RT_CHIPSIZE) return 1;
    csRamtron = 0;//Enable Chip
    SPI1_WR(RT_WREN);
    csRamtron = 1;//Disable Chip
    csRamtron = 0;//Enable Chip
    SPI1_WR(RT_WRITE);//Send the write command(Same for Ramtron)
    //while(NV_TXFULL);
    SPI1_WR(((Address & 0x00070000)>>16));
    SPI1_WR((Address >> 8)); //send address high byte
    SPI1_WR( (Address & 0x000000FE)); //send address low byte, byte aligned
    while(sIndex < NumBytes)
    {
        SPI1_WR(Data[sIndex++]);
        //Data[cIndex++];
    }
    csRamtron = 1;//Disable Chip
    return 0;
}
uInt RT_ReadChars(uInt Address, uInt NumBytes, uChar *Data)
{
    uShort index = 0;
    uChar tempChar = 0;
    while(NV_TXFULL); //Make sure we have finished from previous operation
    csRamtron = 0;//Enable Chip
    SPI1_WR(RT_READ);//Send the write command(Same for Ramtron)
    //while(NV_TXFULL);
    SPI1_WR(((Address & 0x00070000)>>16));
    SPI1_WR((Address >> 8)); //send address high byte
    SPI1_WR( (Address & 0x000000FE)); //send address low byte, byte aligned
    while(index < NumBytes)
    {
       
        tempChar = SPI1_WR(0);
        Data[index++] = tempChar;
    }
    csRamtron = 1;//Disable Chip
    return;    
}

