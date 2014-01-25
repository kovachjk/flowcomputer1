/****************************************************************************
*   CREATED BY: 	Stillbright Managment LLC
*					Copyright 2010
*                                                                           
*   FILE:           menus.h                                                
*                                                                           
*   DESCRIPTION:    Defines all the constants, structs and functions
*					to implement the menus for configuring a device.
					The struct are constructed to be used by both bit mapped
					or character based displays.        
*                                                                           
*   REVISION:   	v1.000                                                      
*   DATE: 			Aug 20 2010                                                 
****************************************************************************/

#ifndef _GINTERFACE_H //G Stands for graphics display interfaces
#define _GINTERFACE_H
//#include "states.h"

//************ SCREEN WIDTH IN CHARS ************
#define STRINGLENGTH 16
// *********** SCREEN TYPES ****************
#define YESNO	 	0
#define NAVAGATE	1 //Navagation Screen
#define PARAMSELECT	2 //Screen that toggles though a list of items
#define SETFLTPARAM	3 //Sreen to enter a float number
#define SETINTPARAM	4 //Sreen to enter a int number
#define SETDATE		5 //Sreen to set date
//************ BUTTON TYPES ******************
#define NOBTN		0
#define ENTERBTN	1
#define	BACKBTN		2
#define INCRMNTBTN	3
#define NEXTBTN		4
//**************  DECADE MARKER *****************
//****	Marks which tens units to increment ******
#define UNITS_THOUSNTH 	.001
#define UNITS_HUNDRTHS 	.01
#define UNITS_TENTHS	.1
#define UNITS_NONE		0
#define UNITS_ONES		1
#define UNITS_TENS		10
#define UNITS_HUNDRS	100
#define UNITS_THOUSND	1000


//Struct for screen defininition
struct xs
{
	char scrnType;
	char numButtons;
	unsigned char nextButton;
	unsigned char backButton;
//	unsigned char *scrnAddresses;//Array of screen addresses based on button pushed, used in navagation
	//char *sTitle; //Screen Title	
	//Function pointer to call when button is pressed or GET is called
	//This used to set and get parameter values
//	float(*sAction)(float); 
//	char ***bTitles; //Button Titles
};
typedef struct xs screenDef;



//void fParam1(float f);

void ButtonPress(char button);

extern screenDef *Screen1;
int MenuManager(void);

#endif
