/**********************************************************************************
// APP.c
// Runs on TM4C123
// A software application to prove the use of Cooerative Schedular. 
// Hossam Elfakher Hassan
// Oct, 2019

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
#include "SystemTick.h"
#include "OS.h"

/********************************* Function Prototype ***************************/
void Task1(void);
void Task2(void);
void Task3(void);

/********************************** watch variables ****************************/
//add these vars to logic analyzer window and watch them.
uint32_t TH1,TH2,TH3;
/********************************** main ***************************************/

int main ()
{
	OS_Init();
	/*Function return values are ignored here*/
	Add_Thread(Task1, 0);
	Add_Thread(Task2, 1);
	Add_Thread(Task3, 2);
	//In cooperative schedular, switching time must be equal or greater than the maximum execution time of
	//the longest thread.
	OS_Fire(1);									 
	while(1);
}

/********************************** Task1 ***************************************/
void Task1(void)
{
	uint32_t t1 = 0;
	while(1)
	{
		t1++;
		TH1^=1;
		OS_Suspend();					//Thread will release CPU after the end of its execution.
	}
}


/********************************** Task3 ***************************************/
void Task2(void)
{
	uint32_t t2 = 0;
	while(1)
	{
		t2++;
		TH2^=1;
		OS_Suspend();				//Thread will release CPU after the end of its execution.
	}
}


/********************************** Task3 ***************************************/
void Task3(void)
{
	uint32_t t3 = 0;
	while(1)
	{
		t3++;
		TH3^=1;
		OS_Suspend();				//Thread will release CPU after the end of its execution.
	}
}
