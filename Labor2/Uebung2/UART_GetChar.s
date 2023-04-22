 ;*   Function: U_GetChar
 ;*   EMB / HS Mannheim / Gruppennummer:
 ;*    Namen:  Vamathevan Sujan // Othman Bouiauiauiuiahuihui
 ;*    SS 2015
 ;*   History
 ;*   2015.05.14  ver 0.01    Preliminary version, first Release
 ;*
;******************************************************************************/
	PRESERVE8
 	AREA GetChar_UART, CODE
	INCLUDE	LPC2368_asm.inc
	EXPORT 	UART_GetChar
	;Assumption R0 = PortNum
	
UART_GetChar
    STMFD   SP!,{R4,LR}
    ANDS 	R0, R0, #0x01  ; Check if UART Port 0 or Port 1 selected
	BEQ 	UART_Port0

UART_Port1	
	LDR		R4,=U1RBR
	B write

UART_Port0
	LDR		R4,=U0RBR

write
	LDR		R0, [R4] ; Write new Char to U1THR since U1THR is empty
	LDMFD   SP!,{R4,PC}
   ;MOV 		R15, R14  ;Return from branch with link 	
	
   END