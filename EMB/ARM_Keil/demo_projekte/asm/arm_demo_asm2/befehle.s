 	AREA arm1, CODE
	INCLUDE LPC2368_asm.inc		; Achtung, Inkludieren nur in einer AREA!

	ENTRY
	EXPORT start
start				   		; Beispiel-Befehle
	LDR R0, =0x12345678 ; 0x0000016C  E59F0024  LDR       R0,[PC,#0x0024]
	MOV	R1, #0x000000FF ; 0x00000170  E3A010FF  MOV       R1,#0x000000FF
	MOV	R2, #0x00000FF0 ; 0x00000174  E3A02EFF  MOV       R2,#0x00000FF0
	MOV	R3, #0x0000FF00 ; 0x00000178  E3A03CFF  MOV       R3,#0x0000FF00
	MOV	R4, #0x000FF000 ; 0x0000017C  E3A04AFF  MOV       R4,#0x000FF000
	MOV	R5, #0x00FF0000 ; 0x00000180  E3A058FF  MOV       R5,#0x00FF0000
	MOV	R6, #0x0FF00000 ; 0x00000184  E3A066FF  MOV       R6,#0x0FF00000
	MOV	R7, #0xFF000000 ; 0x00000188  E3A074FF  MOV       R7,#0xFF000000
	MOV R14,#0x00000014 ; 0x0000018C  E3A0E014  MOV       R14,#0x00000014
	LDR LR, =0xABCDEF01 ; 0x00000190  E59FE004  LDR       R14,[PC,#0x0004]
	; Adr. der Konstanten = Adr. des Befehls + 8 + Offset

halt					; Programmende
	B	halt
	END