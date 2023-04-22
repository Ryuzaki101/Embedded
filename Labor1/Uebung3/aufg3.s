			AREA aufg3, CODE, READONLY
			INCLUDE LPC2368_asm.inc	
			EXPORT start

start		LDR R0, =FIO2_DIR0		;R0 -> FIO2_DIR0-Block
			LDRB R1, [R0]			;load FIO2_DIR0-Block to R1 
			ORR R1, R1, #0xFF		;set Pin2.0 and 2.7 to output in R1 
			STRB R1, [R0]			;writeback R1 to FIO2_DIR0-Block
		
			LDR R0, =FIO2_PIN0		;R0 -> FIO2-PIN0-Block
			LDR R1, =FIO2_PIN1		;R1 -> FIO2-PIN1-Block
			LDR R2, =0x01			;R2 = 1 (Scrolling bit for LED)
			LDR R3, =0x00			;forward/backward toggle

released	TST R3, #0x0F			;check forward/backward state
			BLEQ forward			
			BLNE backward
			LDRB R4, [R1]			;load FIO2_PIN1-Block to R3 ; 
			TST R4, #0x04			;button(Pin2.10) pressed?  
			BNE released			;

			EOR R3, R3, #0x0F		;toggle R2

pressed		LDRB R4, [R1]			;load FIO2_PIN1-Block to R3
			TST R4, #0x04			;button(Pin2.10) released?  
			BEQ pressed				;
			B released				;do "loop" forever

forward		CMP R2, #0x80
			MOVGT R2, #0x01 
			STRB R2, [R0]
			LSL R2, R2, #0x01
			B timere

backward	CMP R2, #0x01
			MOVLT R2, #0x80 
			STRB R2, [R0]
			LSR R2, R2, #0x01
			B timere

timere		LDR R12, =180000		;
tmrloop		SUBS R12, R12, #0x01	;count down R12 to 0
			BNE tmrloop				;count down R12 to 0
			BX LR

			END