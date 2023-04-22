 	AREA arm1, CODE
	INCLUDE LPC2368_asm.inc		; Achtung, Inkludieren nur in einer AREA!

	ENTRY
	EXPORT start
start
	MOV	R0, #0xFF000000		; Beispiel-Befehle
	MOV R14,#0x00000014
	LDR LR, =0x12345678

halt						; Programmende
	B	halt
	END