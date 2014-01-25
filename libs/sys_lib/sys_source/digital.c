

#include "../digital.h"
#include "../sysglobals.h"
//#include "../includes/states.h"
#include DefinedCPU
uInt16 RPIN[10], RPOUT[10];

void InitDigitals(void)
{
    LATA = 0xFF00; //Take digital ports away from analog ports
    /* set LED pins (D3-D10/RA0-RA7) as outputs */
    TRISA = 0xFF00;
    PORTA = 0x00;//RD0-RD3 = INPUTS, RD4-RD15 = OUTPUTS
            /* set LEDs (D3-D10/RA0-RA7) drive state low */
    TRISD = 0XFFFF;     //Set all Port D pins as input pins
                    /* set LEDs (D3-D10/RA0-RA7) drive state low */
}

void InitPeripheralPins(uInt16 PICDevice)
{
	
	
}
// Allows writes to the RPINRx and RPORx registers
// Than allow perpheral to be assigned to pins
void IO_Unlock()
{
    // Unlock Registers
    asm volatile("MOV #OSCCON, w1");
    asm volatile("MOV #0x46, w2"); 
    asm volatile("MOV #0x57, w3");
    asm volatile("MOV.b w2, [w1]"); 
    asm volatile("MOV.b w3, [w1]"); 
    asm volatile("BCLR OSCCON,#6"); //Clear IOLOCK bit
}
void IO_Lock()
{
    // Unlock Registers
    asm volatile("MOV #OSCCON, w1");
    asm volatile("MOV #0x46, w2"); 
    asm volatile("MOV #0x57, w3");
    asm volatile("MOV.b w2, [w1]"); 
    asm volatile("MOV.b w3, [w1]"); 
    asm volatile("BSET OSCCON,#6"); //Set IOLOCK bit	
}
