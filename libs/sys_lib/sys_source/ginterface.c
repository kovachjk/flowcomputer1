#include "globals.h"
#include "appglobals.h"
#include "cinterface.h"
#include <stdio.h>

uChar appStatus = 0;  //The run/program state of the application
uChar menuStatus = 0; // locked/enabled state of the application 
uChar buttonPressed = 0;
void ButtonPress(char button)
{
	if(appStatus == RUNMODE)
	{
		if(menuStatus == MENULOCKED)
		{
			if(buttonPressed == ENTERBTN)
			{
				printf("Enter Pressed");
				switch(buttonPressed)
				{
					case BACKBTN:
					
						break;
					case INCRMNTBTN:
					
						break ;
					default:
							buttonPressed = 0;
						break;
				}
			}
		}
		if(menuStatus == NOBTN);
	}
	
}
