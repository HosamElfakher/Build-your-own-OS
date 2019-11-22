/**********************************************************************************
// list.c
// A software component that handle list data structure.
// Hossam Elfakher Hassan
// NOV, 2019

 Copyright 2019 by Hossam Elfakher Hassan, hossamalfakher2@gmail.com
 		You may use, edit, run or distribute this file
    as long as the above copyright notice remains.
 **********************************************************************************/
/********************************** Includes**************************************/
#include <stdlib.h>
#include "list.h"


/********************************* Function Prototype ***************************/
static int8_t  List_empty(List *ls);


/********************************* Variable defination **************************/


/*******************************************************************************/

/*
** Function: List_init(List *ls)
**
** Description: 
**						This function is used to initialize the passed list.
**						
** Pre-condition: None. 
** Post-condition: List is initialized.

**@param : pointer to the list will be served;
**@return: None.
**
*/
void List_Init(List *ls)
{
  ls->size = 0;
  ls->head = NULL;
}

/*
** Function: List_insert(list *ls, DataEntry dt)
**
** Description: 
**						This function is used to add a new item to list.
**						
** Pre-condition: list is created. 
** Post-condition: list is increased by one.

**@param : list will be served,
					 position of the item will be served
					 Data will be added to list.
**@return: 1 if item is added successfully and -1 otherwise.
**
*/
int8_t List_insert(List *ls, uint8_t pos, DataEntry dt)
{
  ListNode *pls, *pltmp;
	pls = (ListNode *)malloc(sizeof(ListNode));
  if(pls)
  {
    pls->data = dt;

    if(ls->head == NULL)
    {
      ls->head = pls;
      pls->next = NULL;
    }
    else
    {
      uint8_t i = 0;
			pos = ls->size;
      for(pltmp = ls->head; i < pos-1; i++ )
         pltmp= pltmp->next;

         pls->next = pltmp->next;
         pltmp->next = pls;

    }

    ls->size++;
    return 1;

	}
	else
		return -1;
}

/*
** Function: *List_Find_Item(list *ls, DataEntry dt)
**
** Description: 
**						This function is used to find an item in the list.
**						
** Pre-condition: list is created. 
** Post-condition: pointer to data will find in the list.

**@param : list will be served,
					 data will be looked for in the list.
**@return: pointer to data that searched on.
**
*/
uint8_t *List_Find_Item(List *ls,DataEntry dt)
{
  ListNode *pls;
  uint8_t i = 0;
  for(pls = ls->head; i < ls->size; i++ )
	{
		if(pls->data ==  dt)
			break;
		pls= pls->next;
	}
  return ((uint8_t *)pls->data);

}

/*
** Function: List_Find_Item_Pos(list *ls, DataEntry dt)
**
** Description: 
**						This function is used to find an item position in the list.
**						
** Pre-condition: list is created. 
** Post-condition: position fo the item that looking for.

**@param : list will be served,
					 data will be looked for in the list.
**@return: position of data that searched on.
**
*/
uint8_t List_Find_Item_Pos(List *ls,DataEntry dt)
{
  ListNode *pls;
  uint8_t i = 0;
  for(pls = ls->head; i < ls->size; i++ )
	{
		if(pls->data == dt)
			break;
		pls= pls->next;
	}
  return (i);

}
/*
** Function: List_delete(List *ls, uint8_t pos, DataEntry dt)
**
** Description: 
**						This function is used to remove an item from list.
**						
** Pre-condition: list is created. 
** Post-condition: list is decreased by one.

**@param : list will be served,
					 position of the element in the list,
					 Data will be removed from the list.
**@return: None.
**
*/
void List_delete(List *ls, uint8_t pos, DataEntry dt)
{
  ListNode *pls, *pltmp;
  if(pos == 0)
  {
    dt = ls->head->data;
		pltmp = ls->head;
		ls->head = ls->head->next;
    free(pltmp);    
  }
  else
  {
    uint8_t i = 0;
    for(pltmp = ls->head; i < pos-1; i++ )
       pltmp= pltmp->next;

       dt = pltmp->next->data;
       pls = pltmp->next->next;
       free(pltmp->next);
       pltmp->next= pls;
  }
  ls->size--;
}

/*
** Function: List_Empty(List *q)
**
** Description: 
**						This function is used to test if list is empty or not.
**						
** Pre-condition: list is created. 
** Post-condition: No change.

**@param : list will be tested. 
**@return: 1 if list is empty and 0 otherwise.
**
*/
int8_t List_empty(List *ls)
{
  return (ls->size == 0);
}

