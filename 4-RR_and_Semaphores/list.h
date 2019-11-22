#ifndef LIST_H
#define LIST_H

/********************************** Includes **************************************/
#include "stdint.h"

/********************************** Macros ***************************************/

/********************************** Variable Declaration *************************/
typedef int8_t*    DataEntry;

typedef struct node
{
  DataEntry data;
  struct node *next;
}ListNode;

typedef struct
{
  ListNode *head;
  uint8_t size;
}List;

/********************************* Function Prototype ***************************/
extern void List_Init(List *ls);
extern int8_t  List_insert(List *ls, uint8_t pos, DataEntry dt);
extern void List_delete(List *ls, uint8_t pos, DataEntry dt);
extern uint8_t *List_Find_Item(List *ls,DataEntry dt);
extern uint8_t List_Find_Item_Pos(List *ls,DataEntry dt);

#endif
