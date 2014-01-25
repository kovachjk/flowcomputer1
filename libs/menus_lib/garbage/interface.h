/****************************************************************************
*   CREATED BY: 	Stillbright Managment LLC
*					Copyright 2010
*                                                                           
*   FILE:           cinterface.h                                                
*                                                                           
*   DESCRIPTION:    Application for a menu driven user interface using a 4 line character display
*					Defines all the constants and functions necessary
*					to implement the coordination between display and the application        
*                                                                           
*   REVISION:   	v1.000	Aug 20 2010 - Created
					v1,001	Jan 6, 2011 - Added documentation, changed cursor to complex struct     
					
****************************************************************************/

#ifndef _INTERFACE_H //C Stands for charactor display interfaces
#define _INTERFACE_H
#include "statesx.h"
#define STRINGLENGTH 20
#define STRINGLENGTH 80
typedef struct xx
{
	char 	L11[STRINGLENGTH];
	char 	L12[STRINGLENGTH/2];
	char 	L21[STRINGLENGTH];
	char 	L22[STRINGLENGTH/2];
	//char 	L12X;  //Cursor position of where to start Lx2 line;
	//char 	L22X;
	//char 	curPosXY;	
	//float 	*floatVar;
	//int		*intVar;
}structScreen;

typedef struct
{
/*	struct l1
	{
		uChar x1;
		uChar y1;
	}
	struct l2
	{
		uChar x2;
		uChar y2;
	}*/
	char tensUnit;//Specifies which number is being modified
	char value;
}sCursor;
void InitInterface(void);
void CurRight(void);
//When entering a parameter in the RT unit the cursor is plased
//at the left end of the parameter. The CurLeft allows operator 
//to move to the digit of interest.
void CurLeft(void);
void CurUp(void);
void CurDown(void);
void ScrnEnter(void);
void ScrnReturn(void);
void ScrnNext(void);
void ScrnPrev(void);
void DoSplashScreen(void);
void DoConfigInterface(void);
void DoRunInterface(void);
void DisplayScreen(int ScreenNumb);
void IncrementDigit(void);

void ButtonPress(char button);

extern structScreen *myScreen;
#endif
