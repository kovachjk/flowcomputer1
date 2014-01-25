/****************************************************************************
*   CREATED BY: 	Stillbright Managment LLC
*					Copyright 2010
*                                                                           
*   FILE:           display.h                                                
*                                                                           
*   DESCRIPTION:    Defines all the constants and functions necessary
*					for the display hardware to draw the user screens and 
					create user inputs.  These fuction definitions
					are common for bdisplay.c and cdisplay.c which implement
					the functions for either bitmaped graphical displays or 
					character based displays.
*                                                                           
*   CREATED:   	v0.01  - Aug 20 2010                                                 
****************************************************************************/


typedef struct
{
	unsigned int x1,y1,x2,y2; //Screen Dimensions
	
	
}structScreen;  // Screen Dimensions 

typedef struct
{
	unsigned char x1;
	unsigned char y1;
}structCursor;

struct structButton
{
	char *text;
	unsigned int x;//Origin x
	unsigned int y;//Origin y
	unsigned int h;//Height
	unsigned int w;//Width
	
};

void DisplayScreen(int ScreenNum);
