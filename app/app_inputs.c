#include "../app_inputs.h"
#include "../app_includes.h"

static char *meterTypeStrings[] = {"Turbine", "SquareRoot", "Linear", "Exponential"};
uChar meterType = 0;
/**********************************************************************************
                                    SYSTEM INPUTS MANAGMENT
 ***********************************************************************************/
char* ConfigSensors(char* cBuff, char keyPress)
{
    if(keyPress < 0)
    {
        sprintf(cBuff,"!* Config Input Flow As: *!\r\n \
\t1 - Turbine Meter\r\n \
\t2 - Square Root Meter\r\n \
\t3 - Linear Meter\r\n \
\t4 - Exponintial Meter");
        return cBuff;
    }
    if(keyPress == 1)
    {
        SetMenuPage(ConfigSensors);
    }
    if(keyPress ==2)
    {
        SetMenuPage(WiFiConfigDHCP);
    }
    cBuff[0] = 0x00;
    return cBuff;
}

//Called from App_Main
char* FlowMeterConfig(char* cBuff, char keyPress)
{
    if(keyPress < 0)
    {
        sprintf(cBuff,"!** Config Flow Meter **!\r\n \
\t%s Meter \r\n \
\t1 - Change Type\r\n \
\t2 - Config Meter\r\n", meterTypeStrings[meterType]);
        return cBuff;
    }
    if(keyPress == 1)
    {
        SetMenuPage(ChangeFlowMeterType);
    }
    if(keyPress ==2)
    {
        SetMenuPage(ConfigMeter);
    }
    cBuff[0] = 0x00;
    return cBuff;
}


char* ChangeFlowMeterType(char* MenuBuff, char KeyPress )
{
    if(KeyPress < 0)
    {
        sprintf(MenuBuff,"*Change Meter Type *\r\n \
\t1 - Turbine\r\n \
\t2 - Linear\r\n \
\t3 - Square Root\r\n \
\t4 - Exponent\r\n \
\t5 - No Change\r\n ");
        return MenuBuff;
    }  
    if(KeyPress <= 5) meterType = KeyPress;
    SetMenuPage(FlowMeterConfig);

}
char* ConfigMeter(char *MenuBuff, char KeyPress)
{
  if(KeyPress < 0)
    {
        sprintf(MenuBuff," *Change Meter Type *\r\n \
\t1 - Turbine\r\n \
\t2 - Linear\r\n \
\t3 - Square Root\r\n \
\t4 - Exponent\r\n \
\t5 - No Change\r\n ");
        return MenuBuff;
    }
    if(KeyPress <= 5) meterType = KeyPress;
    SetMenuPage(FlowMeterConfig);

}

/**********************************************************************************
                                  PRESSURE METER MANAGMENT SECTION
 ***********************************************************************************/

