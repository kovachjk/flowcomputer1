#include "../sys_inputs.h"
a_Input sysInputChannel[3];
uChar sysInputIndex = 0;

char* ConfigSystemInputs(char* cBuff, char keyPress)
{
    if(keyPress < 0)
    {
        sprintf(cBuff,"*! ADC Configuration !*\r\n \
1-Channel 1\r\n \
2-Channel 2\r\n \
3-Channel 3");
        return cBuff;
    }
    if(keyPress >=1 && keyPress <= 3)
    {
        sysInputIndex = keyPress;
        SetMenuPage(ConfigChannel);
    }

    cBuff[0] = 0x00;
    return cBuff;
}


char* ConfigChannel(char* cBuff, char keyPress)
{
    if(keyPress < 0)
    {
        sprintf(cBuff,"!*SysInput Channel %d*!\r\n \
1-Current Settings\r\n \
2-Run Configurator\r\n",sysInputIndex);
        return cBuff;
    }
    if(keyPress == 1)
    {
        SetMenuPage(WiFiConfigMenu);
    }
    if(keyPress ==2)
    {
        SetMenuPage(WiFiConfigDHCP);
    }
    cBuff[0] = 0x00;
    return cBuff;
}