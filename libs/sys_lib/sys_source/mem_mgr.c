/**********************************************************************
* © 2009 Stillbright
* Created 10/24/2009
*	
* FileName:        mem_mgr.c
* Purpose:  This module manages applicationa and system variables that are
 *          accesable over Modbus.
* Dependencies:    Other (.h) files if applicable, see below
* 1/3/13 -  Defined structs that used to register valid Modbus registers.
 *          Only 30001 to 30201 and 40001 to 40201 numbered register addresses
 *          will be used.  To save nv memory, the 30001 range will be normalized
 *          down to the zero index in memory and the 40001 will be moved down
 *          nv index 400.
 *
*
**********************************************************************/
#include "../mem_mgr.h"
//This is the list of all configurable and accessable variables used in the system

#define iUnitID 0;
#define iBaud 1;
#define iKFactor 2;

cVar  u1Baud, unitID, kFactor, lowerAlarm;

int test1, test2,test3, test4,test5;
//nvSysVar nvVar;
uChar varType = 0, xIndex = 0;


cVar *cVarPtr[] = {&unitID, &u1Baud, &kFactor, &lowerAlarm}; // For configurable
uChar nvCharBuff[NV_BUFFSZ];
fiUnion tempNVVar;

//void *pVars[3] = {&testUChar, &testChar, &testFloat};
//extern spiStatus cSPI2;



//InitNVM
void LoadNVArrayDefaultValues(void)
{
    u1Baud.type = typeUInt;
    u1Baud.d.i = 1234;
    unitID.type = typeInt;
    unitID.d.i = -1234;
    kFactor.type = typeFloat;
    kFactor.d.f = 1234.5678;

}

int WriteIndexedVariable(uShort MemIndex, double value)
{
    
    varType  = cVarPtr[MemIndex]->type;
    switch(varType)
    {
        case typeInt:
            cVarPtr[MemIndex]->d.i = (int)value;

            break;
        case typeUInt:
            cVarPtr[MemIndex]->d.i = (uInt)value;
            break;
        case typeFloat:
            cVarPtr[MemIndex]->d.f = (float)value;
            break;
    }
}
int ReadIndexedVariable(uShort MemIndex,double Value)
{

}
char WriteNVMemory(uShort RegAddrs,uShort NumRegs, uInt *Data)
{
    int Index = 0;
    
    //Find out if variable to be modified is a float

    for(;Index < NumRegs; Index++)
    {
        nvCharBuff[Index * 2] = Data[Index] >> 8;
        nvCharBuff[(Index * 2) + 1] = Data[Index] & 0x00FF;
    }//MBSTART_NV_MEMSTART moves the index pointer from 4000 down to zero
    //RT_WriteChars(RegAddrs - MBSTART_NV_MEMSTART, NumRegs *2, nvCharBuff);
    
    //Look through all the registed address and see if this is a good one
    //What type of variable is it
    return 2;
}
int NVMemory2MBReg(int RegAddrs, uShort NumRegs, uShort *Data)
{
    test2 = cVarPtr[0]->d.i;
    test1 = cVarPtr[RegAddrs - 4000]->type;
    Data[RegAddrs - 4000] = cVarPtr[RegAddrs - 4000]->type;
    return 2;
}
void AddFloat2MemMgr(cVar *CVar, float DefaultVal)
{

}

void AddInt2MemMgr(cVar *CVar, int DefaultVal)
{
    nvCharBuff[0] = CVar->d.c[0];
    nvCharBuff[1] = CVar->d.c[1];
    nvCharBuff[2] = CVar->d.c[2];
    nvCharBuff[3] = CVar->d.c[3];
}

void AddUInt2MemMgr(cVar *CVar, uInt DefaultVal)
{

}
void WriteDefaults2NVMemory(void)
{

    /*
    sysVar[0].varAddress = &unitID;
    sysVar[0].varType = typeInt;
    sysVar[1].varAddress = &lowerAlarm;
    sysVar[1].varType = typeInt;
    sysVar[2].varAddress = &kFactor;
    sysVar[2].varType = typeFloat;*/
/*
    uInt x = 0;
    for(;x < numVariables; x++)
    {   
        if(sysVar[x].varType == typeFloat)
        {
            tempNVVar.i = (int)sysVar[x].varAddress;
        }
        else
        {         
            tempNVVar.i = (int)sysVar[x].varAddress;
        }
        nvCharBuffer[0] = tempNVVar.c[0];
        nvCharBuffer[1] = tempNVVar.c[1];
        nvCharBuffer[2] = tempNVVar.c[2];
        nvCharBuffer[3] = tempNVVar.c[3];
        Chars2Ramtron(x*4, 4, nvCharBuffer);
    }*/
}

void SetNVMemory2Defaults(uShort Defaults
)
{

}