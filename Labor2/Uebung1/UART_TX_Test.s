	AREA UART_TX_Test, CODE, READONLY
	INCLUDE	LPC2368_asm.inc	
    IMPORT UART_init
	IMPORT UART_PutChar
	EXPORT start
	
start
    ;Configure UART 
    LDR  R0, =0x00			;UART_PortNum = (UART0 / UART1)
	LDR  R1, =0x08			;U_DL = (baudrate =112500)
	LDR  R2, =0x03			;UART_Mode (vorgesehener Inhalt UxLCR)
	LDR  R3, =0x47			;(INT_ENABLE << 8) | FIFO_Mode
	BL 	UART_init

	LDR  R0, =0x00			
    LDR  R10, =MyString		
loop
	LDRB  R1, [R10], #1			
	BL 	UART_PutChar
	TST R1, R1
	BEQ Done
	b loop

Done
   B   Done
	
	AREA    String_Block, DATA, READONLY
MyString  DCB  "Life is good.",0
    
	END
	
	
	