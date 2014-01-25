/****************************************************************************
*   CREATED BY: 	Stillbright Managment LLC
*					Copyright 2010
*                                                                           
*   FILE:           lcd_interface.h                                               
*                                                                           
*   DESCRIPTION:    Defines all the constants and functions necessary
*					to support t_menu on a lcd screen       
*                                                                           
*   REVISIONS:   	v0.00 - 11/1/2012: Created 
	                                        
****************************************************************************/

#ifndef _lcd_interface_h
#define _lcd_interface_h

#include <stdio.h>
//#include "main.c";
#include "../../Microhip/Include/Graphics/Graphics.h"
#include "../../Microhip/Include/Graphics/Primitive.h"
#include "../../MMB/LCDTerminal.h"
#include "../../MMB/SerialEEPROM.h"

#define LCD_WIDTH 320

#define ARC_R1 	4 //R1 and R2 define both the amount of roundness of corner and thickness of line in Arc()
#define ARC_R2	5
#define BTN_OFFSET_W ARC_R2*2 //Offset compensates for the amount of roundness in the Arc() function
#define BTN_OFFSET_H ARC_R1*2
#define BTN_H 	34
#define BTN_W	42
/*
	tButton stuct defines the drawing and pressing of keypads
	Use a tButton array to make different keypads.
*/

typedef struct
{
	short x;
	short y;
	short width;
	short height;
	char  keyPress[3];	//String returned when pressed
	char  lable[5];		//Sring Printed on button
	char  moreKeys;		//As long as this is non zero, the build keyPad will look for more buttons
						//the last button in the tButton array should have this var set to zero.
}tButton;

//FloatPad has all the pads to work with float numbers
extern tButton FloatPad[];
extern tButton AlphaPad[];
extern tButton YesNoPad[];
extern tButton PlusMinusPad[];
extern tButton NavigationPad[];
extern tButton StartPad[];
void CalibrateTouch(void);
void MakeTouchButton(int x, int y, char *lable);
void MakeButtonRow(short x, short y, short l, short h, short num, short row);
void BuildTouchPad(tButton *TouchPad, int Color);
void BuildNavigationPad();

char *GetTouchPress(char *tP);


#endif