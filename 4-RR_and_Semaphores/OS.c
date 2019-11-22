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
#include <stdlib.h>
#include "OS.h"
#include "SystemTick.h"


/********************************* Function Prototype ***************************/


/********************************* Variable defination **************************/
Head ThreadTCBs;
Head *RunB = &ThreadTCBs;


/*******************************************************************************/

/*
** Function: Add_Thread(void (*task)(), uint16_t tasknum)
**
** Description: 
**						This function is used to allocate thread control block for the and 
**						assign the function will be executed in	that thread.
**						
** Pre-condition: OS is initialized. 
** Post-condition: Thread is initialized and the function is hooked to the thread.

**@param : Call back function that will be executed in the thread. 
**@param : Thread number.
**@return: 1 if the thread block is allocated successfully and 0 otherwise
**
*/
int Add_Thread(void (*task)(), uint16_t tasknum)
{
	TCB *newth;
	newth = (TCB *)malloc(sizeof(TCB));
	if(newth == 0)
		return 0;
	if(RunB->Thread_NUM==0)
	{
		RunB->RunTh = newth;										//Get the address of the new allocated node
		RunB->RunTh->next = newth;						  //Points to itself
	}
	else
	{
		/*This implementation is applicable before firing the OS*/
		int i;
		TCB *tmp = RunB->RunTh;
		/*Loop to get the last NOde*/
		for( i = 0; i < RunB->Thread_NUM-1; i++)
				tmp = tmp->next;
		tmp->next = newth;																//Last node will point to the new allocated one
		newth->next = RunB->RunTh;												//The new allocated node points to the first node
		} 
	newth->sp = &newth->threadstack[StackSize-16];
	newth->threadstack[StackSize-2] = (uint32_t)task;	//load PC with function address
	newth->threadstack[StackSize-1] = 0x01000000;
	newth->ID = tasknum;															//Assign a unique number to each thread	
	RunB->Thread_NUM++;
	return 1;
}

/*
** Function: Remove_Thread(uint16_t tasknum)
**
** Description: 
**						This function is used to remove thread. actually its TCB.
**						
** Pre-condition: Thread is already have been allocated. 
** Post-condition: Thread is moved to trash.

**@param : Thread number.
**@return: 1 if the thread is removed successfully and 0 otherwise
**
*/
int Remove_Thread(uint16_t tasknum)
{
	if(RunB->Thread_NUM==0) 
		return 0;
	else
	{
	  /*This implementation is applicable all the time cuz of using thread ID*/
		int i;
		TCB *tmp = RunB->RunTh;
		/*Loop to get the ID of the NOde*/
		for( i = 0; i < RunB->Thread_NUM; i++)
		{
			if(tmp->ID == tasknum)
			{
				if(i == 0)
				{
					RunB->RunTh = RunB->RunTh->next;						//If this thread is the head one, change head to next one
					 /*If this function is used after firing the OS, SWITCH CONTEXT CODE SHOULD BE HERE*/
					if(RunB->Thread_NUM == 1)										//System has only one thread
					{
						RunB->RunTh = 0;
						free(tmp);
						RunB->Thread_NUM--;
						return 1;
					}
				}
				break;
			}
				tmp = tmp->next;
		}
		if(i == RunB->Thread_NUM)
			return 0;																		// No tasks with this ID
	
		tmp = RunB->RunTh;
		while(--i)
		{
			tmp = tmp->next;													 //Loop to get the node before the intended one.
		}
		TCB *fr = tmp->next;
		tmp->next = tmp->next->next;									//Pass node pointer to the next node
		
		free(fr);														 				  //Deallocate this node 
	}
	RunB->Thread_NUM--;
	return 1;
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
	RunB->RunTh = 0;
	RunB->Thread_NUM = 0;
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
	RunB->RunTh = RunB->RunTh->next;				//Select the ready task								
}

/*
** Function: OS_Suspend()
**
** Description: 
**						This function is forcing the CPU to do the context switching.
**						
** Pre-condition: Operating System is running. 
** Post-condition: Current thread is off and the next ready thread will gain CPU.

**@param : None. 
**@return: None.
**
*/
void OS_Suspend(void)
{
	Enter_Critical_Section();
	SYS_CTRL->INTCTRL.bit.PENDCTSET = 1;
	Exit_Critical_Section();
}

