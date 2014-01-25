#include "../display.h"
#include "../menus.h"
#include <plib.h>



void DisplayScreen(int ScreenNum)
{
	int x,y;
	//screenDef *s = (screenDef*)&;//=(screenDef*)&param1;
	//Screen[1]=(screenDef*)&param2;
	y = (char)Screen[ScreenNum]->numButtons;
//	DBPRINTF((char*)Screen[ScreenNum]->sTitle);
	for(x=0;x<y;x++)
	{
		
		DBPRINTF("Select %i for " , x+1);
		DBPRINTF((char*)Screen[ScreenNum]->bTitles[x]);//button titles
	}	
	
}

