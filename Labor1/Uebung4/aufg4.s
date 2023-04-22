			AREA aufg4, CODE, READONLY
			INCLUDE LPC2368_asm.inc	
			EXPORT start
				
start		LDR R0, =T0TCR 			;timer control register
			LDRB R1, [R0]			;load T0TCR-Block to R1 
			ORR R1, R1, #0x02		;reset Tmr0  
			STRB R1, [R0]			;writeback R1 to T0TCR-Block
			EOR R1, R1, #0x03		;enable Tmr0  
			STRB R1, [R0]			;writeback R1 to T0TCR-Block

			LDR R0, =T0TC			;R0 -> T0TC-Block
			LDR R1, =FIO2_PIN1		;R1 -> FIO2-PIN1-Block

released	LDRB R4, [R1]			;load FIO2_PIN1-Block to R4 
			TST R4, #0x04			;button(Pin2.10) pressed?  
			BNE released			;
			
			LDR R2, [R0]			;load current value from TC to R2

pressed		LDRB R4, [R1]			;load FIO2_PIN1-Block to R4 
			TST R4, #0x04			;button(Pin2.10) released?  
			BEQ pressed				;

			LDR R3, [R0]			;load newer value from TC to R3
			SUB R3, R3, R2			;R3 = R3-R2 (elapsed time = old time - new time)

			B released				;do "loop" forever

			END