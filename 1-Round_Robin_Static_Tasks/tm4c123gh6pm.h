/**********************************************************************************
// TM4C123GH6PM.h
// This file is tm4c123 MCU registers map holding only, the needs of the current project
// Hossam Elfakher Hassan
// Oct, 2019

 Copyright 2019 by Hossam Elfakher Hassan, hossamalfakher2@gmail.com
    You may use, edit, run or distribute this file
    as long as the above copyright notice remains.
 **********************************************************************************/
 
#ifndef TM4C123GH6PM_H
#define TM4C123GH6PM_H

#include "stdint.h"

/* ================================================================================ */
/* ================                 SYSTEM CONTROL                 ================ */
/* ================================================================================ */
struct RIS_REG_Bits
{
	uint32_t Reserved0 : 1;
	uint32_t BOR1RIS : 1;
	uint32_t Reserved1 : 1;
	uint32_t MOFRIS: 1;
  uint32_t Reserved2 : 2;
	uint32_t PLLRIS : 1;
	uint32_t USBPLLRIS : 1;
	uint32_t MOSCPUPRIS : 1;
	uint32_t Reserved3 : 1;
	uint32_t VDDARIS : 1;
	uint32_t BOR0RIS : 1;
	uint32_t Reserved4 : 20;
};
union RIS_REG
{
	struct RIS_REG_Bits bit;
	uint32_t all;
};


struct RCC_REG_Bits
{
	uint32_t MOSCDIS :1;
	uint32_t Reserved0 : 3;
	uint32_t OSCSRC : 2;
	uint32_t XTAL : 5;
	uint32_t BYBASS: 1;
	uint32_t Reserved1 : 1;
	uint32_t PWRDN : 1;
	uint32_t Reserved2 : 3;
	uint32_t PWMDIV : 3;
	uint32_t USEPWMDIV : 1;
	uint32_t Reserved3 : 1;
	uint32_t USERSYSDIV : 1;
	uint32_t SYSDIV : 4;
	uint32_t ACG : 1;
	uint32_t Reserved4 : 4; 
};
union RCC_REG
{
	struct RCC_REG_Bits bit;
	uint32_t all;
};


struct RCC2_REG_Bits
{
	uint32_t Reserved0 : 4;
	uint32_t OSCSRC2 : 3;
	uint32_t Reserved1 : 4;
	uint32_t BYBASS2: 1;
  uint32_t Reserved2 : 1;
	uint32_t PWRDN2 : 1;
	uint32_t USBPWMDIV : 1;
	uint32_t Reserved3 : 7;
	uint32_t SYSDIV2LSB : 1;
	uint32_t SYSDIV2 : 6;
	uint32_t Reserved4 : 1;
	uint32_t DIV400 : 1;
	uint32_t USERCC2 : 1;

};
union RCC2_REG
{
	struct RCC2_REG_Bits bit;
	uint32_t all;
};

typedef struct System_CTRL_REGS
{
	union RIS_REG					RIS;
	uint32_t Reserved0;
	uint32_t Reserved1;
	uint32_t Reserved2;
	union RCC_REG				  RCC;
	uint32_t Reserved3;
	uint32_t Reserved4;
	uint32_t Reserved5;
	union RCC2_REG				RCC2;
}System_CTRL_REGS;

/* ================================================================================ */
/* ================                     SYSTICK                    ================ */
/* ================================================================================ */
struct CTRL_Bits{
	uint32_t Enable : 1;
	uint32_t INTEN  : 1;
	uint32_t CLKSRC: 1;
	uint32_t Reserved0:13;
	uint32_t Count  : 1;
	uint32_t Reserved1: 15;	
};

union CNTRL_REG
{
	struct CTRL_Bits bit;
	uint32_t all;
};

typedef struct SysTick_REGs{
	union    CNTRL_REG	   STCTRL_REG;					  /*systick control register*/
	uint32_t STRELOAD;														/*reload register*/
	uint32_t STCURRENT;														/*current tick value*/
}SysTick_REGs;


struct Priority_Reg0_Bits
{
	uint32_t Reserved0 : 5;
	uint32_t MEM : 3;
	
	uint32_t Reserved1 : 5;
	uint32_t Bus : 3;
	
	uint32_t Reserved2 : 5;
	uint32_t Usage : 3;
	
	uint32_t Reserved3 : 8;
};
union Priority_Reg0{
	struct Priority_Reg0_Bits bit;
	uint32_t all;
};

struct Priority_Reg1_Bits
{
	uint32_t Reserved : 29;
	uint32_t SVC : 3;
};
union Priority_Reg1{
	struct Priority_Reg1_Bits bit;
	uint32_t all;
};


struct Priority_Reg2_Bits
{
	uint32_t Reserved0 : 5;
	uint32_t Debug : 3;
	
	uint32_t Reserved1 : 13;
	uint32_t PendSV : 3;
	
	uint32_t Reserved2 : 5;
	uint32_t Tick : 3;
	
};
union Priority_Reg2{
	struct Priority_Reg2_Bits bit;
	uint32_t all;
};

typedef struct SYS_INT_Priority_REGs {
	union    Priority_Reg0	   SYS_Priority_R0;					  
	union    Priority_Reg1	   SYS_Priority_R1;					
	union    Priority_Reg2	   SYS_Priority_R2;				  
	}SYS_INT_Priority_REGs;

	
#define System_Base										0xE000E000
#define System_Control_Base						0x400FE000
	
#define Systick_Offset							  0x0010
#define RCC_Offset									  0x050
#define Sys_INT_Priority_Offset				0x0D18

#define SYSTICK								((volatile SysTick_REGs				   *)(System_Base+Systick_Offset))
#define SYS_INT_Priority			((volatile SYS_INT_Priority_REGs *)(System_Base+Sys_INT_Priority_Offset))
	
#define Run_Clock_CONF				((volatile System_CTRL_REGS		   *)(System_Control_Base+RCC_Offset))

#endif  /* TM4C123GH6PM_H */
