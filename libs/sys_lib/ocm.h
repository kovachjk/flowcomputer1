
/**********************************************************************
* © 2007 Microchip Technology Inc.
*
* FileName:        pwm.h
*
*Created 8/15/2009
*© Stillbright Managment LLC 2009
**********************************************************************/
#ifndef __PWC_H__
#define __PWC_H__ 


extern void initTmr2(int CutoffFreq);
extern void initPWM1();
//3db Cutoff Setting
extern void SetCutoffFreq(int Freq);
#endif
