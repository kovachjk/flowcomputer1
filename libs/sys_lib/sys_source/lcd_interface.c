
#include "../lcd_interface.h"
#include "../TouchScreen.h"
#include <stdio.h>
#include <string.h>

tButton *CurrentTouchPad;

tButton FloatPad[]={
                        {271,110,BTN_W,BTN_H,"-","-",1},
                        {6,155,BTN_W,BTN_H,"5","5",1},
                        {59,155,BTN_W,BTN_H,"6","6",1},
                        {112,155,BTN_W,BTN_H,"7","7",1},
                        {165,155,BTN_W,BTN_H,"8","8",1},
                        {218,155,BTN_W,BTN_H,"9","9",1},
                        {271,155,BTN_W,BTN_H,".",".",1},
                        {6,200,BTN_W,BTN_H,"0","0",1},
                        {59,200,BTN_W,BTN_H,"1","1",1},
                        {112,200,BTN_W,BTN_H,"2","2",1},
                        {165,200,BTN_W,BTN_H,"3","3",1},
                        {218,200,BTN_W,BTN_H,"4","4",1},
                        {271,200,BTN_W,BTN_H,{0x0D,0x00},"RTN",1},
                        {271,65,BTN_W,BTN_H,{0x08,0x00},"BS",0}
							
};

tButton NavigationPad[]={	
                        {271,155,BTN_W,BTN_H,{0x1B,0x00},"ESC",1},
                        {6,200,BTN_W,BTN_H,"1","1",1},
                        {59,200,BTN_W,BTN_H,"2","2",1},
                        {112,200,BTN_W,BTN_H,"3","3",1},
                        {165,200,BTN_W,BTN_H,"4","4",1},
                        {218,200,BTN_W,BTN_H,"5","5",1},
                        {271,200,BTN_W,BTN_H,"6","6",0}
							
};

tButton StartPad[] = {{6,6,308,228,{0x1B,0x00},"",0}};
tButton YesNoPad[]={
                    {49,195,55,BTN_H + 10,"1","Yes",1},
                    {105,195,55,BTN_H + 10,"0","No",0}
    
};
tButton PlusMinusPad[] ={
                        {259,38,55,42,"+","+",1},
                        {259,84,55,42,{0x0D,0x00},"RTN",1},
                        {259,174,55,42,"-","-",0},
};
void CalibrateTouch(void)
{
    short xTouch = -1, xMin = -1, yMin, xMax = -1, yMax;
    char s[25];
    //Capture (0,0) position first
    MakeTouchButton(270,5,"X");
    while(xTouch < 0)
    {
        RunTouchScreen();
        yMin = ADCGetY();
        if(yMin == -1 ) // yResults could be -1
        {
            xMin = ADCGetX();
            {
                if(xMin != -1) //Chances that both are really -1 is remote
                {
                    xTouch = 1; // Accept that yMin is -1
                    xMin = ADCGetX();
                    yMin = ADCGetY();
                }
            }
        }
        else if(yMin != -1)
        {
            xMin = ADCGetX();
            yMin = ADCGetY();
            xTouch = 1; // Accept that yMin is -1
        }
    }

    xTouch = 1;
    sprintf(s,"Coord Min=(%d,%d)\n",xMin,yMin);
    LCDPutString(s);
    //DelayMs(200);    

    while(xTouch > 0)
    {
        RunTouchScreen();
        xTouch = TouchGetX();
    }
    MakeTouchButton(5,200,"X");   
    xTouch = -1;
    while(xTouch < 0)
    {
        RunTouchScreen();
        yMax= TouchGetY();
        if(yMax == -1 ) // yResults could really be -1
        {
            xMax = TouchGetX();
            {
                if(xMax != -1) //Chances
                {
                    xTouch = 1; // Accept that yMin is -1
                    xMin = ADCGetX();
                    yMin = ADCGetY();
                }
            }
        }
        else if(yMax != -1)
        {
            xMax = TouchGetX();
            xMax = ADCGetX();
            yMax = ADCGetY();
            xTouch = 1; // Accept that yMin is -1
        }
    }

    xTouch = 1;
    sprintf(s,"Coords=(%d,%d)\n",xMax,yMax);
    LCDPutString(s);
    // Sreen is divided into 12 sections of which the two previous
    // key presses captured only 10.  To find the zero coords and the 
    // ratio of touch distance to pixals, expand touch distace to full extent
    // by added one of the unincluded sections to the max and subtracting  the other
    // from the min coords
    xTouch = (xMax - xMin)/10;
    xMin -= xTouch;
    xMax += xTouch - 25;
    xTouch = (yMax - yMin)/10;
    yMin -= xTouch;
    yMax += xTouch + 10;
    while(xTouch > 0)
    {
        RunTouchScreen();
        xTouch = TouchGetX();
    }
    
    StoreCalFactors(xMin,xMax,yMin,yMax);
    //StoreCalFactors(100,100,100,100);
    TouchLoadCalibration();
}
void MakeTouchButton(int x, int y, char *lable)
{
    Arc(x,y,x+BTN_W,y+BTN_H,4,5,0xff);
    x += (BTN_W/2) - (FONT_W/2);
    y += (BTN_H/2) - (FONT_H/2);
    OutTextXY(x,y,lable);
}

void MakeButtonRow(short x, short y, short l, short h, short num, short rows)
{
    short index1,index2,sX,sY,offset, yOffset;
    offset = 10;  //Need to move the button over the width of the arc in Arc()(4th param)
    yOffset = 8;
    sX = x;
    sY = y;
    for(index1 = 0; index1 < rows; index1++)
    {
        for(index2 = 0; index2 < num; index2++)
        {
                Arc(x + ((l + offset) * index2),
                        y + (h + yOffset) *index1,
                        x + ((l + offset)  * index2) + l,
                        y + (h + yOffset) * index1 + h,4,5,0xff);
                        sX = (x + ((l + offset) * index2)) + (l/2) - (FONT_W/2);
                        sY = (y + ((h + yOffset) * index1)) + ((h + yOffset)/2) - (FONT_H/2);
                        //sprintf(numKeyPad[index2].keyPress,"%d",index2*(index1+1));
                        OutTextXY(sX,sY,FloatPad[index2].keyPress);
        }
    }
	
}


void BuildTouchPad(tButton *TouchPad, int Color )
{
    SetColor(Color);
    _cursorX = 0;
    _cursorY = 0;
    if(TouchPad != NULL)
    {
        CurrentTouchPad = TouchPad;
	short index = 0,tX,tY;
	do
	{
            Arc(CurrentTouchPad[index].x,
                   CurrentTouchPad[index].y,
                   CurrentTouchPad[index].x + CurrentTouchPad[index].width,
                   CurrentTouchPad[index].y + CurrentTouchPad[index].height,
                    4,5,
                    0xff);
            //Center and print text
            tX = CurrentTouchPad[index].x + (BTN_W/2) - ((FONT_W*strlen(CurrentTouchPad[index].lable))/2);
            tY = CurrentTouchPad[index].y + (BTN_H/2) - (FONT_H/2);
            OutTextXY(tX,tY,CurrentTouchPad[index].lable);
	}while(CurrentTouchPad[index++].moreKeys);// if moreKey != 0 there are more CurrentKeyPad in the array
    }
}

char* GetTouchPress(char *tP)
{
    short index = 0, xCoord, yCoord;
    xCoord = LCD_WIDTH - TouchGetX() ;
    yCoord = TouchGetY();
    if(CurrentTouchPad != NULL)
    {
	do
	{
            if(xCoord > CurrentTouchPad[index].x)
            {
                if(xCoord < (CurrentTouchPad[index].x + CurrentTouchPad[index].height))
                {
                    if(yCoord > CurrentTouchPad[index].y)
                    {
                        if(yCoord < (CurrentTouchPad[index].y + CurrentTouchPad[index].width))
                        {
                            strcpy(tP,CurrentTouchPad[index].keyPress);
                            //tP = ;
                            return tP;
                        }
                    }
                }
            }
	}while(CurrentTouchPad[index++].moreKeys);// if moreKeys != 0 there are more CurrentKeyPad in the array
    }
    return "";
}
