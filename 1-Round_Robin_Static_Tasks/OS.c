/**********************************************************************************
// OS.c
// Runs on TM4C123
// A software component that handle OS operation.
// Hossam Elfakher Hassan
// Oct, 2019

 Copyright 2019 by Hossam Elfakher Hassan, hossamalfakher2@gmail.com
    You may use, edit, run or distribute this file
    as long as the above copyright notice remains.
 **********************************************************************************/
 
/********************************** Includes**************************************/
#include "OS.h"
#include "SystemTick.h"


/********************************* Function Prototype ***************************/
static void TCB_Stack_Init(uint32_t i);

/********************************* Variable defination **************************/
static TCB tcbs[ThreadNum];
TCB *RunTh = &tcbs[0];

/********************************** Functions ***********************************/
/*
** Function: TCB_Stack_Init()
**
** Description: 
**						This function is used to initilaze thread control block.
**						
** Pre-condition: TCB block is defined. 
** Post-condition: TCB block is initialized.

**@param : TCB number that attached to the thread. 
**@return: None
**
*/
static void TCB_Stack_Init(uint32_t i)
{
	tcbs[i].threadstack[StackSize-1] = 0x01000000;           // Thread in thumb mode
	//The remaining registers is not needed to be initialized
}

/*
** Function: Add_Thread(void (*task)(), uint16_t tasknum)
**
** Description: 
**						This function is used to assign the function will be executed in a specific
**						thread.
**						
** Pre-condition: OS is initialized. 
** Post-condition: Thread is initialized and the function is hooked to the thread.

**@param : Call back function that will be executed in the thread. 
**@param : Thread number.
**@return: None
**
*/
void Add_Thread(void (*task)(), uint16_t tasknum)
{
	TCB_Stack_Init(tasknum);
	tcbs[tasknum].sp = &tcbs[tasknum].threadstack[StackSize-16];				//Point to PC location
	tcbs[tasknum].next= &tcbs[(tasknum+1)%ThreadNum];									//point to the next tcb and roll over at the end
	tcbs[tasknum].threadstack[StackSize-2] = (uint32_t)task;					//load PC with function address
}

/*
** Function: OS_Init()
**
** Description: 
**						This function is used to initialize Operating system.
**						
** Pre-condition: System tick is initialized. 
** Post-condition: OS is ready to fired.

**@param : None. 
**@return: None
**
*/
void OS_Init(void)
{
	Enter_Critical_Section();
	Systick_Init();	
	Exit_Critical_Section();
}

/*
** Function: OS_Fire()
**
** Description: 
**						This function for firing Operating system to run.
**						
** Pre-condition: Operating System is initialized. 
** Post-condition: OS is running.

**@param : Period of OS in Millisecond. 
**@return: None.
**
*/
void OS_Fire(uint32_t ms_period)
{
	extern void OS_Launch(void);
	Enter_Critical_Section();
	Systick_Fire(ms_period*1000);													// Convert milli second to mico seconds
	Exit_Critical_Section();
	OS_Launch();
	
}

/*
** Function: Dispatcher()
**
** Description: 
**						This function is used to select the next ready thread to run.
**						
** Pre-condition: Operating System is running. 
** Post-condition: Next ready thread is in run state.

**@param : None. 
**@return: None.
**
*/
void Dispatcher(void)
{
	RunTh = RunTh->next;								//Select the ready task
}

