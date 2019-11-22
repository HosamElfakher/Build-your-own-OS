#ifndef SEMPH_H
#define SEMPH_H

/********************************** Includes **************************************/
#include "stdint.h"
#include "list.h"

/********************************** Macros ***************************************/
#define SemphBINkeysNUM					9

/********************************** Variable Declaration *************************/
typedef List			Semph_t;
typedef int8_t 		Semaphore; 


/********************************* Function Prototype ***************************/
extern void Semph_Create(int8_t *key, int8_t Sem);
extern void Semph_Wait(int8_t *key);
extern void Semph_Signal(int8_t *key);
extern void Semph_Destroy(int8_t *key);

#endif
