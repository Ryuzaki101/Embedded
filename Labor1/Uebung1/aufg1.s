			AREA aufg1, CODE, READONLY
			INCLUDE LPC2368_asm.inc	
			EXPORT start

start		LDR R0, =FIO2_DIR0		;R0 -> FIO2_DIR0-Block
			LDRB R1, [R0]			;load FIO2_DIR0-Block to R1 
			ORR R1, R1, #0x11		;set Pin2.0 and 2.4 to output in R1 
			STRB R1, [R0]			;writeback R1 to FIO2_DIR0-Block
		
			LDR R0, =FIO2_PIN0		;R0 -> FIO2-PIN0-Block
			LDR R1, =FIO2_PIN1		;R1 -> FIO2-PIN1-Block

polling		LDRB R2, [R1]			;load FIO2_PIN1-Block to R2 
			TST R2, #0x4			;button(Pin2.10) pressed?  
			MOVNE R2, #0x0			;depending on <button ressed>: set <Pin2.0 - Pin2.7 to "low"> or...
			MOVEQ R2, #0x11			;	...Pin2.0 and Pin2.4 to "high" in R2
			STRB R2, [R0]			;store R2 to FIO2-PIN0-Block
			B polling				;do "polling" forever

			END