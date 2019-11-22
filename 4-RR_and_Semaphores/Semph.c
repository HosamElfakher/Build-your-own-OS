/**********************************************************************************
// Semph.c
// A software component that handle semaphore operation.
// Hossam Elfakher Hassan
// NOV, 2019

 Copyright 2019 by Hossam Elfakher Hassan, hossamalfakher2@gmail.com
 		You may use, edit, run or distribute this file
    as long as the above copyright notice remains.
 **********************************************************************************/
/********************************** Includes**************************************/
#include "Semph.h"
#include "OS.h"


/********************************* Function Prototype ***************************/


/********************************* Variable defination **************************/
Semph_t SemaphoreBC;


/*******************************************************************************/

/*
** Function: Semph_Binary_Create(int8_t *key, int8_t Semdt)
**
** Description: 
**						This function is used to create semaphore and initialize it.
**						
** Pre-condition: None. 
** Post-condition: semaphore is created and initialized.

**@param : address of semaphore,
**				 initial value.
**@return: None.
**
*/
void Semph_Create(int8_t *key, int8_t Semdt)
{
	static int8_t semInit = 0;
	if(semInit++ == 0)
		List_Init(&SemaphoreBC);
	
	*key = Semdt;
	List_insert(&SemaphoreBC,0,key);							//address of the key to be listed
}

/*
** Function: Semph_Binary_Wait_Spinlock(int8_t *key)
**
** Description: 
**						This function do nothing, it is just waiting till the semaphore being avialable.
**						
** Pre-condition: semaphore is created. 
** Post-condition: semaphore is decremented.

**@param : address of semaphore
**@return: None.
**
*/
void Semph_Wait(int8_t *key)
{
	Enter_Critical_Section();
	uint8_t *ix = List_Find_Item(&SemaphoreBC,key);
	Exit_Critical_Section();
	while(*ix == 0);
	Enter_Critical_Section();
	*key = 0;
	Exit_Critical_Section();
}

/*
** Function: Semph_Binary_Signal(int8_t *key)
**
** Description: 
**						This function is signalling semaphore to be avialable for needs.
**						
** Pre-condition: semaphore is created. 
** Post-condition: semaphore is incremented.

**@param : address of semaphore
**@return: None.
**
*/
void Semph_Signal(int8_t *key)
{
	Enter_Critical_Section();
	*key = 1;	
	Exit_Critical_Section();
}

/*
** Function: Semph_Binary_Destroy(int8_t *key)
**
** Description: 
**						This function destroys the semaphore.
**						
** Pre-condition: semaphore is created. 
** Post-condition: semaphore is destroyed.

**@param : address of semaphore
**@return: None.
**
*/
void Semph_Destroy(int8_t *key)
{
	Enter_Critical_Section();
	List_delete(&SemaphoreBC,List_Find_Item_Pos(&SemaphoreBC,key),key);	
	Exit_Critical_Section();
}
