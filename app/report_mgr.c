#include "../report_mgr.h"


char* ConfigReports(char* cBuff, char keyPress)
{
    if(keyPress < 0)
    {
        sprintf(cBuff,"\x1B[2J\x1B[H !* Config Meters & Sensors *!\r\n \
\t1 - Run Reports\r\n \
\t2 - Config Reports/Date \r\n");
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
