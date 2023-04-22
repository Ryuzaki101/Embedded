	AREA PutChar_UART, CODE
	INCLUDE	LPC2368_asm.inc
	EXPORT 	UART_PutChar
	;Assumption R0 = UART_PortNum (0 or 1 for EVB MCB2300), R1 = Char to be sent

UART_PutChar
	STMFD   SP!,{R4,R5, LR}
	ANDS 	R0, R0, #0x01  ; Check if UART Port 0 or Port 1 selected
	BEQ 	UART_Port0
UART_Port1
	LDR		R3,=U1LSR     ; UART Port 1 selected
	LDR		R4,=U1THR
Wait_TX1
	LDR 	R5, [R3] ; Content of U1LSR loaded in R3
	ANDS	R5, R5, #2_00100000 ; Test bit 5 of U1LSR
	BEQ 	Wait_TX1
	STR		R1, [R4] ; Write new Char to U1THR since U1THR is empty
	B UART_Tx_Done

UART_Port0
	LDR		R3,=U0LSR    ;UART Port 0 selected
	LDR		R4,=U0THR
Wait_TX0
	LDR 	R5, [R3] ; Content of U0LSR loaded in R5
	ANDS	R5, R5, #2_00100000 ; Test bit 5 of U0LSR
	BEQ 	Wait_TX0
	STR		R1, [R4] ; Write new Char to U1THR since U0THR is empty

UART_Tx_Done
	LDMFD   SP!,{R4,R5, PC}
	;MOV 		R15, R14  ;Return from branch with link

   END
