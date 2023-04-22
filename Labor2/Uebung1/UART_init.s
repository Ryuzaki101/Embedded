	PRESERVE8
	AREA UART_asm1, CODE
	INCLUDE	LPC2368_asm.inc
	EXPORT 	UART_init
	;Assumption R0 = UART_PortNum, R1 = U_DL , R2 = UART_Mode, R3 = (INT_ENABLE << 8) | FIFO_Mode
	
UART_init
    STMFD   SP!,{R4-R7,R14}
	LDR		R7,=PIN_SEL0   ;PIN_SEL0 needed for both UART0 and UART1 modules
	                       ; PIN_SEL0[5:4] = 01 enable TXD0 (UART0 TXD), PIN_SEL0[7:6] = 01 enable 
						   ; RXD0 ()UART0 RXD), PIN_SEL0[31:30] = 01 enable TXD1 (UART1 TXD)
	LDR 	R4, [R7]
    ;MOV 	R5, #0x3        ;Constant value used to clear two consecutive bits in a register
    MOV		R6, #0x1	    ;Constant binary value (two bits) to be written in PINxSEL Registers	
	ANDS 	R0, R0, #0x01  ;Check if UART_PortNum = R0 = 1
	BEQ 	Config_UART0   ;Go configure UART0 
	
Config_UART1
	BIC		R4, R4, R5, LSL#30  ;Clear bits 31 and 30 in PINSEL0 	
	ORR 	R4, R4, R6, LSL#30  ;Set bit 30 in PINSEL0
	STR		R4, [R7]            ;Store new value of PINSEL0
	LDR		R7, =PIN_SEL1   ;PIN_SEL1[1:0] = 01 enable RXD1 for UART1 RXD1 (UART1 RXD)
	LDR		R4, [R7]        ; 
	ORR 	R5, R6, R6, LSL#1
	BIC		R4, R4, R5      ;Clear bits 1 and 0 in PINSEL1
	ORR 	R4, R4, R6      ;Set bit 0 in PINSEL1 
	STR		R4, [R7]        ;Store new value of PINSEL1 
    LDR     R0, =U1FCR
    STR     R3, [R0]
	LDR		R0, =U1IER      ;Load address of UART1 IER register in R0
    MOV 	R3, R3, LSR#8
	STR     R3, [R0]
    LDR		R0, =U1DLM      ;Load address of UART1 DLM register in R0
	LDR		R3, =U1DLL      ;Load address of UART1 DLL register in R7
    LDR		R4, =U1LCR      ;Load address of UART1 LCR register in R4
	
	B 	U_DL_Config
		
Config_UART0
	BIC     R4, R4, R5, LSL#4    ;Clear bits 4 and 5 in PINSEL0
	BIC		R4, R4, R5, LSL#6    ;Clear bits 6 and 7 in PINSEL0
	ORR  	R4, R4, R6, LSL#4    ;Set bit 4 in PINSEL0
	ORR		R4, R4, R6, LSL#6    ;Set bit 6 in PINSEL0
	STR		R4, [R7]             ;Store new value of PINSEL0
    LDR     R0, =U0FCR
    STR     R3, [R0]
	LDR		R0, =U0IER      ;Load address of UART0 IER register in R0
    MOV 	R3, R3, LSR#8
	STR     R3, [R0]
	LDR		R0, =U0DLM     	;Load address of UART0 DLM register in R0
	LDR		R3, =U0DLL     	;Load address of UART0 DLL register in R7
    LDR		R4, =U0LCR     	;Load address of UART0 LCR register in R4


U_DL_Config
	LDR		R5, [R4]             ;Load content of UxLCR in R5
	ORR 	R5, R5, #0x80        ;Clear Bit 8 in content of UxLCR 
	STR 	R5, [R4]             ;Save UxLCR with DLAB = 1
    MOV		R6, R1, LSL#8        ;Shift DLM Value to bits 7:0
	STR 	R6, [R0]             ;Store DLM value
	STR		R1, [R3]             ;Store DLL value
	EOR		R6, R6, R6           ;Clear content of R6
	ORR     R6, R6, R2           ;Load UART mode from R2
    BIC     R6, R6, #0x80    
 	STR 	R6, [R4]             ;Save UxLCR with DLAB = 0
	
	LDMFD   SP!,{R4-R7, PC}
	
    END	


	
