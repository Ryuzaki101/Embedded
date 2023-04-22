			AREA aufg2, CODE, READONLY
			INCLUDE LPC2368_asm.inc	
			EXPORT start

start		LDR R0, =FIO2_DIR0		;R0 -> FIO2_DIR0-Block
			LDRB R1, [R0]			;load FIO2_DIR0-Block to R1 
			ORR R1, R1, #0xF0		;set <Pin2.4 - Pin2.7> to output in R1 
			STRB R1, [R0]			;writeback R1 to FIO2_DIR0-Block
			
			LDR R0, =FIO2_PIN0		;R0 -> FIO2-PIN0-Block
			LDR R1, =FIO2_PIN1		;R1 -> FIO2-PIN1-Block
			LDRB R2, [R0]			;load FIO2_PIN0-Block to R2

pressed		LDRB R3, [R1]			;load FIO2_PIN1-Block to R3 
			TST R3, #0x4			;button(Pin2.10) pressed?  
			BNE pressed				;

			EOR R2, R2, #0xF0		;toggle <Pin2.4 - Pin2.7> in R2
			STRB R2, [R0]			;store R2 to FIO2-PIN0-Block

released	LDRB R3, [R1]			;load FIO2_PIN1-Block to R3 
			TST R3, #0x4			;button(Pin2.10) released?  
			BEQ released			;

			B pressed				;do "loop" forever

			END