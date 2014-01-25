#include "../menus.h"
#include <plib.h>
#include <stdio.h>
#include <sys/appio.h>


#define NUMSCREENS 3
screenDef *Screen1;
//screenDef Screen1[4];
int currentScreen=0;
const char *test ="hello world";
char choice;
/*   HOW TO BUILD SCREENS
First:  Define prompts that describe all the choices for the user.
Second: Define a fuction call in the munus.h file that is then coded for the
		menu screen
Third: 	Define a screenDef struct with all the parameters described.
*/
//*********************** Screen 8 ************************ 
//*************  Program Selection Screen***************
/*float SetApp(float x)
{
	DBPRINTF("App %i was selected",(int)x);
	return x;
}
*/

/*const char *setAppPrompts[]={" Steam\r"," Chill Water\r"," Gas\r", " Natural Gas\r"," Option 5\r\r"};

const screenDef setApp = {1,4,3,4};//,"test","Select Application\r",&SetApp,(char***)setAppPrompts};


screenDef *Screen1 = &setApp;


// *********************  Input Selection Screen ***********************
const char *inputPrompts[]={"HS Pulse\r","LS Pulse\r","0-5 Volt", "4-20 mA","0-20 mA"};
const screenDef inputType = {1,5,"Selet Input1 Type",&SetApp,(char***)param2Prompts};//,&fParam1(choice)};

const char *param3Prompts[]={"Steam3","Chill Water","Gas", "Natural Gas","Option 5"};
const screenDef param3 = {1,4,"4-20 Configuration",&SetApp,(char***)param3Prompts};//,&fParam1(choice)};

screenDef *Screen[NUMSCREENS] = {&setApp,&inputType,&param3};

void CallFunction(int screenNum)
{
	Screen[screenNum]->sAction(screenNum);	
}
*/
int MenuManager()
{
	//DisplayScreen(currentScreen);
	while(choice != 'x')
	{

	   // Get the choice
	   choice = GetMenuChoice();
		//DBGETC(&choice);

	   // Now act on it.
	   	switch(choice)
	   	{
		   
			case 48:
	      	case 49:
	      	case 50:
	      	case 51:
	      	case 52:
	      	case 53:
	      	case 54:
	      	case 55:
	      	case 56:
	      	case 57:
	      	case 58:	 // This is the standard framework command.
	      		DBPRINTF(" \n");
	      		DBPRINTF("Pressed %c \r",choice);
	      		
				break;
			case 'r':
			case 'R':
			   	ToggleRed();
			   	
				break;
				break;
			case 'b':
			case 'B':
			   	// Back ButtonToggleRed();
			   	
				break;				
			case 'n': //move to next screen
			case 'N':
			   	currentScreen++;
			   	if(currentScreen > NUMSCREENS) currentScreen = 0;
			   	DisplayScreen(currentScreen);
				break;
			case 'n': // move up on level
			case 'N':
			   	ToggleGreen();
				break;
			case 'x':
			case 'X':
			   	return 999;
				break;
			case 'f':
			case 'F':
			 	CallFunction(0);
				break;		   
			default:
				// Enter button;
			return 0;
				break;
		}
	}
}

	
