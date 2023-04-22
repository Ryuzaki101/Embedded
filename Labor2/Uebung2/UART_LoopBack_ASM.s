 ;*   ASM Programm: UART_LoopBack_ASM
 ;*   EMB / HS Mannheim / Gruppennummer:
 ;*    Namen:  
 ;*    SS 2015
 ;*   History
 ;*   2015.05.14  ver 0.01    Preliminary version, first Release
 ;*
;******************************************************************************/
	AREA UART_LoopBack_ASM, CODE, READONLY
	INCLUDE	LPC2368_asm.inc	
	EXPORT start
    IMPORT UART_init
	IMPORT UART_PutChar
	IMPORT UART_GetChar
	
start

    ;Configure UART 
    LDR  R0, =0x00			;UART_PortNum = (UART0 / UART1)
	LDR  R1, =0x08			;U_DL = (baudrate =112500)
	LDR  R2, =0x03			;UART_Mode (vorgesehener Inhalt UxLCR)
	LDR  R3, =0x47			;(INT_ENABLE << 8) | FIFO_Mode
	BL 	UART_init
loop
	LDR		R3,=U0LSR    ;UART Port 0 selected

Wait_RX	
	LDR 	R5, [R3] ; Content of U1LSR loaded in R3
	ANDS	R5, R5, #2_00000001 ; Test bit 0 of U1LSR
	BEQ 	Wait_RX

	BL UART_GetChar

	MOV R1, R0
	MOV R0, #0

	BL UART_PutChar
	b loop

Done
	B   Done

	END
	
	
	