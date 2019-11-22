/**********************************************************************************
// SystemTick.c
// Runs on TM4C123
// A software component which the heart beat of OS.
// Hossam Elfakher Hassan
// Oct, 2019

 Copyright 2019 by Hossam Elfakher Hassan, hossamalfakher2@gmail.com
    You may use, edit, run or distribute this file
    as long as the above copyright notice remains.
 **********************************************************************************/
 
/********************************** Macros ***************************************/
#include "SystemTick.h"

/********************************** Functions prototype***************************/


/********************************** Functions ************************************/
/*
** Function: Systick_Init()
**
** Description: 
**						This function is used to initilaze system clock.
**						
** Pre-condition: None. 
** Post-condition: System Tick is initilized.

**@param : None
**@return: None
**
*/
void Systick_Init(void)
{	
	SYSTICK->STCTRL_REG.bit.Enable = 0;									// Disable system tick.
	SYS_INT_Priority->SYS_Priority_R2.bit.Tick = 7;			// Set systick interrupt priority into 7
}

/*
** Function: Systick_Fire()
**
** Description: 
**						This function is used to fire system Tick.
**						
** Pre-condition: Number of micro seconds that defines system tick . 
** Post-condition: System Tick is running.

**@param : None
**@return: None
**
*/
void Systick_Fire(uint32_t usec)
{
	usec = ((usec*SystemClcok))/1000000UL;
	SYSTICK->STRELOAD = usec-1;												  // Reload value of system tick.
	SYSTICK->STCTRL_REG.bit.INTEN = 1;									// Enable interrupt.
	SYSTICK->STCTRL_REG.bit.CLKSRC  = 1;								// Main clock is selected
	SYSTICK->STCTRL_REG.bit.Enable = 1;									// Enable system tick.

}
