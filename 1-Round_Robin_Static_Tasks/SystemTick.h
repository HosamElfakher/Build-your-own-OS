#ifndef  SYSTEMTICK_H
#define  SYSTEMTICK_H

/********************************** Includes**************************************/
#include	"stdint.h"
#include  "tm4c123gh6pm.h"

/********************************** Macros**************************************/
#define SystemClcok						80000000UL

/********************************* Function Prototype ***************************/
extern void Systick_Init(void);
extern void Systick_Fire(uint32_t usec);

#endif
