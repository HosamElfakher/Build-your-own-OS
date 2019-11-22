;OS.s
;Runs on TM4C123
;A software low level component that used OS context switxhing.
;Hossam Elfakher Hassan
;Oct, 2019

;Copyright 2019 by Hossam Elfakher Hassan, hossamalfakher2@gmail.com
;	You may use, edit, run or distribute this file
;   as long as the above copyright notice remains.

		AREA |.text|, CODE, READONLY, ALIGN=2
        THUMB
        REQUIRE8
        PRESERVE8
			
		extern RunB        ;current running thread
		export SysTick_Handler
		export OS_Launch
		import Dispatcher
		export Enter_Critical_Section
		export Exit_Critical_Section	

Enter_Critical_Section
	CPSID   I
	BX		LR
	
Exit_Critical_Section
	CPSIE   I
	BX		LR
	

OS_Launch
	CPSID   I
	LDR    R0,=RunB         ;Load base address of RunB pointer
	LDR    R1,[R0]			;RunB->RunTh
	LDR    R1,[R1]			;RunB->RunTh->stack pointer
	LDR    SP, [R1]			;Move the content of thread stack pointer to SP
	POP    {R0-R12}		    ;Moving stack pointer till reach the PC location
	POP    {LR}				;To discard the return address of calling function at that time
	POP    {LR}				;Load Link Register with the content of the Initialized PC adress
	POP    {R5}				;Discard the top of the thread stack
	CPSIE   I
	BX	   LR				;Back to run the first thread

SysTick_Handler
	CPSID   I
	PUSH   {R4-R11}
	LDR    R0,=RunB         ;Load base address of RunB pointer
	LDR    R1,[R0]			;RunB->RunTh
	LDR    R1,[R1]			;RunB->RunTh->stack pointer
	STR    SP, [R1]			;Store stack pointer of the old thread
	PUSH   {R0,LR}
	BL	   Dispatcher		;Get the next SP of ready thread
	POP	   {R0,LR}
	LDR	   R1, [R0]
	LDR    R1, [R1]
	LDR    SP, [R1]
	POP    {R4-R11}			;Retreive registers of the ready run thread.
	CPSIE   I
	BX     LR
	
	ALIGN 
	END
		