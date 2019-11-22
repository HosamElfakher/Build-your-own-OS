/**********************************************************************************
// APP.c
// Runs on TM4C123
// A software application to prove the use of dynamic Round Rubin Schedular. dynamic means 
// threads can be added or removed at compile time.
*************************Added features*********************************
-Binary semaphores
// Hossam Elfakher Hassan
// NOV, 2019

 Copyright 2019 by Hossam Elfakher Hassan, hossamalfakher2@gmail.com
		You may use, edit, run or distribute this file
    as long as the above copyright notice remains.
 **********************************************************************************/
 /*******************************Note**********************************************
 *A- This version is tested on simulator wheres the logic analyzer is working well.
 *To run it on real hardware follow this steps:
 * 1- open system_TM4C123.c File
 * 2- make this line as #define CLOCK_SETUP 1            ----Line 36
 *
 *B- In this version, Heap is used extensively so it should be updated in startup file
 *   to a reliable value.
 *********************************************************************************/
 
/********************************** Includes **************************************/
#include <stdio.h>
#include "SystemTick.h"
#include "OS.h"
#include "Semph.h"

/********************************* Function Prototype ***************************/
void Task1(void);
void Task2(void);
void Task3(void);
void LCD_Display(void);
void Print(void);
void delayMs(int n);

/********************************** watch variables ****************************/
//add these vars to logic analyzer window and watch them.
uint32_t TH1,TH2,TH3;
/********************************** main ***************************************/
Semaphore LCD, Printer;
int main ()
{
	OS_Init();
	/*Function return values are ignored here*/
	Add_Thread(Task1, 0);
	Add_Thread(Task2, 1);
	Add_Thread(Task3, 2);
	//Create semaphore with make it avialable for first use.
	Semph_Create(&LCD, 1);	
	Semph_Create(&Printer,1);
	
	OS_Fire(1);									// Fire with 1 ms time slice
	while(1);
}

/********************************** Task1 ***************************************/
void Task1(void)
{
	while(1)
	{
		Semph_Wait(&LCD);
		LCD_Display();
		TH1++;
		Semph_Signal(&LCD);
	}
}


/********************************** Task3 ***************************************/
void Task2(void)
{
	while(1)
	{
		Semph_Wait(&LCD);	
		LCD_Display();
		TH2++;
		Semph_Signal(&LCD);
		
	}
}


/********************************** Task3 ***************************************/
void Task3(void)
{
	while(1)
	{
		Semph_Wait(&Printer);	
		LCD_Display();		
		TH3++;
		Semph_Signal(&Printer);
	}
}



/********************************** LCD pseudo Function ***************************************/
void LCD_Display(void)
{
	delayMs(1);
}
/********************************** Printer pseudo Function ***************************************/
void Print(void)
{
	delayMs(3);
}

void delayMs(int n)
{
	int i, j;
	for(i = 0 ; i < n; i++)
		for(j = 0; j < 3180; j++)
		{}  /* do nothing for 1 ms */
}
