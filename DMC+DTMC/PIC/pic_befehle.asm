;****************************************************************
;*	HS Mannheim
;*	Institut für Mikrocomputertechnik/EmbeddedSystems
;*  Filename:
;*	pic_befehle.asm
;*
;*
;*	25.10.2007
;****************************************************************

	list p=18f452	;Prozessor für Assembler auswählen
#include <p18f452.inc>

;bank0 auch geeignet für globale Variablen

Reg_A	EQU	0x000
Reg_B	EQU	0x001
Reg_C	EQU	0x002
Reg_D	EQU	0x003
;bank1
Reg_E	EQU	0x100
Reg_F	EQU	0x101
Reg_G	EQU	0x102
Reg_H	EQU	0x103
summe	EQU	0x104
Reg		EQU	0x180

;bank2

WREG_sichern	EQU	0x200
STATUS_sichern	EQU	0x201
BSR_sichern		EQU	0x202

	ORG 0x00
ResetVect
	GOTO Init 

	ORG 0x08
IntVectHigh
;//No Interrupts Enabled

	ORG 0x18
IntVectLow
;//No Interrupts Enabled

	ORG 0x30
;//Initialisation Code - Placed at some point after IntVect
Init
	BRA main	
;//Main Application Code
main
	MOVLB	1
	INCF	0x80
	INCF	0x70,1,0
	MOVWF	Reg_E
	MOVLW	B'11001111'
	MOVWF	Reg_F
	COMF	Reg_E,0
	MOVWF	Reg_G
	COMF	Reg_A,1,0
	MOVF	Reg_A,0
	ADDWF	Reg_E,1,1
	NEGF	Reg_E	
	MOVF	Reg_G
	ANDWF	Reg_F
	MOVFF	Reg_E,WREG_sichern
;
	MOVLW	0x16
	MOVWF	Reg_A
	MOVLW	0x15		;Reg_B im WREG
	MOVWF	Reg_B
	BCF		STATUS,C
	CPFSGT	Reg_A		;f-w
	SUBFWB	Reg_A,0		;w-(f+c)
	SUBWF	Reg_A,0		;f-w
;
	RLCF	Reg_F
	CLRF	PORTB
	MOVLW	B'11110000'
	MOVWF	TRISB
	MOVF	PORTB,0
	MOVLW	B'10100010'
	MOVWF	PORTB
	MOVLW	B'11000011'
	IORWF	PORTB
	BRA	main
FinishLoop
	END

