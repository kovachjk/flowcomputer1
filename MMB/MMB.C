/*
** MMB.c 
** 
** MikroE MMB - Support library for configuration and basic peripherals access
**
** Author   	    Date        Rev    Comments
** Lucio Di Jasio	08-Dec-2009	1.0		Updated for GFX lib v2.0
** Lucio Di Jasio   12-Feb-2010 1.1     Added exit() handler
** John Kovach 		11/6/12 Re-Wrote MMBGetKey();
**
*/
#include <stdio.h>
#include "../MMB/MMB.h"
#include "../Microhip/Include/Graphics/Primitive.h"

/*JK Remmed out becauce of:
 * /Volumes/build/xc32/xc32-XC32-release-1.11/XCpp-libs/source/exit.c:(.text.exit+0x0): multiple definition of `exit'
void exit( int e)
{ 
    while(1);
}

// redefine the exception handler for debugging purposes
void _general_exception_handler( unsigned c, unsigned s)
{
    while (1);
} // exception handler
*/

void MMBInit( void)
{
    // 1. disable the JTAG port  
    mJTAGPortEnable( 0);
    
    // 2. Config system for max performance
    //JK SYSTEMConfig( GetSystemClock(), SYS_CFG_WAIT_STATES | SYS_CFG_PCACHE);
   
    // 3. allow vectored interrupts
    INTEnableSystemMultiVectoredInt();   // Interrupt vectoring
    
    // 4. enable joystick input
	AD1PCFG |= 0x000F;   // all PORTB inputs digital
    
    // 5. init LEDs 	
	LD0 = LED_OFF;  // turn all LED off
	LD1 = LED_OFF;  
	LD2 = LED_OFF;
	LD4 = LED_OFF;
	LD0_TRIS = 0;     // make LED outputs
	LD1_TRIS = 0;     // make LED outputs
	LD2_TRIS = 0;     // make LED outputs
	LD4_TRIS = 0;     // make LED outputs
	
    // 6. Display backlight off 
    BL_TRIS_BIT = 0;  // OUTPUT     
    //JK BacklightOff();

} // init MikroEMMB


/* 
** Update all analog inputs
*/
int MMBReadT( void)
{    
    AD1CON1 = 0x00E0;   // auto convert after end of sampling 
    AD1CSSL = 0;        // no scanning required 
    AD1CON2 = 0;        // use MUXA, AVss/AVdd used as Vref+/-
    AD1CON3 = 0x1F0F;   // sample time = 31xTad, Tad = 2xTsys
    AD1CON1SET = 0x8000;// turn on the ADC
    AD1CHSbits.CH0SA = 8;      // select TEMP input channel
    AD1CON1bits.SAMP = 1;       // start sampling
    while (!AD1CON1bits.DONE);  // wait to complete conversion
   return ADC1BUF0;            

} // ReadTemperature


// define the stopwatch function
void MMBStartStopwatch( void)
{   // resets the core timer count
    WriteCoreTimer( 0);
} // start_timer

// returns time lapsed in milliseconds 
// maximum measurable interval 107s (worst case @80MHz)
double MMBReadStopwatch( void)
{
    unsigned int ui;
    
    // get the core timer count
    ui = ReadCoreTimer();
    
    // convert in milliseconds (1 core tick = 2 SYS cycles)
    return ( ui * 2000.0 /GetSystemClock());     
} // read_timer
    
void MMBUARTInit( int baudrate)
{   // initialize UART1 for default stdout redirection
    // optimize baudrate divider for best approximation
    int fpb = GetPeripheralClock();
    int c1 = UART_EN;
    int c2 = UART_TX_ENABLE | UART_RX_ENABLE | UART_EN_CTS_RTS;
    int c3 = fpb/16/baudrate;
    int c4 = fpb/4/baudrate;
    
    // check if /4 gives a better approx
    if ( ( fpb / 16.0 / c3) > ( fpb / 4.0 / c4))
    {   // use the /4 factor
        c3=c4;  
        // select BREGH =1
        c1 |= UART_BRGH_FOUR;
    }
        
	// enable UART1 (RS232) TX 
	OpenUART1( c1, c2, c3-1);	
    //setbuf( stdout, NULL);
    
} // init_UART
  
/*
**
**	Buttons read and debounce
*/

int ReadJoyStick( void)
{   // returns 0..F if keys pressed, 0 = none
    int c = 0;

    if ( !_RA10) // Select
        c |= 16;
    if ( !BTN_A) 
        c |= 8;
    if ( !BTN_B) 
        c |= 4;
    if ( !BTN_C) 
        c |= 2;
    if ( !BTN_D) 
        c |= 1;

    return c;
} // readKEY


int GetJoyStick( void)
{   // wait for a key pressed and debounce
    int i=0, r=0, j=0;
    int c;

    // 1. wait for a key pressed for at least .1sec
    while(r == 0)
    {
	    r = ReadJoyStick();
	    DelayMs( 10);
	}
    do{
		c = ReadJoyStick();
        DelayMs( 10);
        
        if (c > 0) //Another key has been pressed
        {
            if ( c != r)       // if more than one button pressed
            r = c;      // take the new code
            i = 0;    
        }
        else 
            i++;
    } while ( i < 5);
        
    return r;
} // getKEY

// 
// Accelerometer 
// 
int MMBAccInit( void)
{
    int w;
    
    // configure SPI port for accelerometer access	
	CloseSPI1();
	OpenSPI1( PRI_PRESCAL_64_1 | SEC_PRESCAL_8_1 | MASTER_ENABLE_ON | CLK_POL_ACTIVE_LOW | SPI_SMP_ON , 
	        SPI_ENABLE);
    SPI1BRG = GetPeripheralClock()/ 4000000 / 4;
    	      
    // enable Accelerometer
    CS_ACC_LAT_BIT = 1;    	      
    CS_ACC_TRIS_BIT = 0;
    DelayMs( 10);
    w = ReadSPI1();             // dummy

    // Read DEVID register (test)
    CS_ACC_LAT_BIT = 0; 
    WriteSPI1( 0x80 | 0x00 );   // read DEVID register
    while( !DataRdySPI1());
    w = ReadSPI1();             // dummy

    WriteSPI1( 0);              // dummy
    while( !DataRdySPI1());
    w = ReadSPI1();             // read DEVID
    CS_ACC_LAT_BIT = 1;
    if ( w != 0xE5) 
        return 0;               // Failed 

    // enable measurement
    CS_ACC_LAT_BIT = 0; 
    WriteSPI1( 0x00 | 0x2D );   // write to POWER_CTL register
    while( !DataRdySPI1());
    w = ReadSPI1();             // dummy
    
    WriteSPI1( 0x08);           // set Measure bit ON
    while( !DataRdySPI1());
    w = ReadSPI1();             // dummy
    CS_ACC_LAT_BIT = 1;
    
    return 1;                   // Success 
} // MMBAccInit


void MMBAccRead( int* x, int* y, int*z)
{
    int w;
    
    // read acceleration values
    CS_ACC_LAT_BIT = 0; 
    WriteSPI1(0xC0 | 0x32 ); // read DataX0/X1/Y0/Y1/Z0/Z1
    while( !DataRdySPI1());
    w = ReadSPI1();          // dummy

    WriteSPI1(0x00);
    while( !DataRdySPI1());
    *x = ReadSPI1();         // read lsb
    WriteSPI1(0x00);
    while( !DataRdySPI1());
    *x |= ReadSPI1()<<8;     // read msb
    if (*x >32767) *x-=65536;

    WriteSPI1(0x00);
    while( !DataRdySPI1());
    *y = ReadSPI1();         // read lsb
    WriteSPI1(0x00);
    while( !DataRdySPI1());
    *y |= ReadSPI1()<<8;     // read msb
    if (*y >32767) *y-=65536;

    WriteSPI1(0x00);
    while( !DataRdySPI1());
    *z = ReadSPI1();         // read lsb
    WriteSPI1(0x00);
    while( !DataRdySPI1());
    *z |= ReadSPI1()<<8;     //read msb
    if (*z >32767) *z-=65536;

    CS_ACC_LAT_BIT = 1;
} // MMBAccRead


void MMBFadeIn( int msTime)
{    // time = total duration of fade-in effect
    //  expressed in ms (100ms minimum)
    int w;
    
    if (msTime<100) msTime = 100;
    OpenTimer2( T2_ON | T2_PS_1_1, 0 );

    // OC3 output is connected to the backlight control
    OpenOC3( OC_ON | OC_PWM_FAULT_PIN_DISABLE | OC_TIMER2_SRC, 0, 0);
    for( w=0; w<65536; w+=65536/100)
    {   // 100 steps
        SetDCOC3PWM( w);
        DelayMs(msTime/100);
    }        
    // Return display BL control to I/O
    CloseOC3();
    CloseTimer2();
    // Full brightness
    BacklightOn();

}   // MMBFadeIn

void MMBFadeOut( int msTime)
{    // time = total duration of fade-out effect
    //  expressed in ms (100ms minimum)
    int w;
    
    if (msTime<100) msTime = 100;
    OpenTimer2( T2_ON | T2_PS_1_1, 0 );
    
    // OC3 output is connected to the backlight control
    OpenOC3( OC_ON | OC_PWM_FAULT_PIN_DISABLE | OC_TIMER2_SRC, 0, 0);
    for( w=65535; w>0; w-=65536/100)
    {   // 100 steps
        SetDCOC3PWM( w);
        DelayMs(msTime/100);
    }        
    // Return display BL control to I/O
    CloseOC3();
    CloseTimer2();
    // Display Backlight Off
    BacklightOff();
}   // MMBFadeOut


void MMBCenterString( int p, char *s)
{  // p  integer offset (lines) above or below center
   // s  string
   // requires InitGraph(), SetFont() and SetColor() before use
   // also MMBFadeIn() or BacklightOn() to appear
    int height, x, y;

    // get string width & height
    height = GetTextHeight( (void *)_font);
    y = GetMaxY()/2 - height/2 + height*p;
    x = (GetMaxX() - GetTextWidth( (void *)s, (void *)_font))/2;
    OutTextXY(  x, y, s);
} // CenterString

 