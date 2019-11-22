#ifndef OS_H
#define OS_H

/********************************** Includes **************************************/
#include "stdint.h"

/********************************** Macros ***************************************/
#define StackSize			100

/********************************** Variable Declaration *************************/
typedef struct tcb
{
	uint32_t *sp;
	struct tcb *next;
	uint32_t    threadstack[StackSize];
	uint32_t    ID;
}TCB;

typedef struct head
{
	TCB *RunTh;
	uint32_t Thread_NUM;
}Head;

/********************************* Function Prototype ***************************/
extern void OS_Init(void);
extern int  Add_Thread(void (*task)(), uint16_t tasknum);
extern int  Remove_Thread(uint16_t tasknum);
extern void OS_Fire(uint32_t ms_period);
extern void Dispatcher(void);
extern void Enter_Critical_Section(void);
extern void Exit_Critical_Section(void);

#endif
