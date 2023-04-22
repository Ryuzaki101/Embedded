;****************************************************************
;*	HS Mannheim
;*	Institut für Mikrocomputertechnik/EmbeddedSystems
;*	Filename: Befehle.asm
;*	Datum:      08.05.2013  mit Configuration Bits
;*	Vorversion: 25.10.2007
;****************************************************************

	list p=18f452	;Prozessor für Assembler auswählen
#include <p18f452.inc>

	config OSC=HS,WDT=OFF,LVP=OFF ;Configuration Bits - defined in include file
	; HS Oszillator, Watchdog Timer disabled, Low Voltage Programming

BANK0 EQU 0x00
BANK1 EQU 0x100
BANK2 EQU 0x200
BANK3 EQU 0x300
BANK4 EQU 0x400
BANK5 EQU 0x500

;//***** Variables *****
;//

;//Bank0
zeit_1 EQU  0x20
zeit_2 EQU  0x21



;//Bank1
;//Bank2
;//Bank3
zahl_a	EQU	0x300
zahl_b	EQU	0x301
zahl_c	EQU	0x302
;//Bank4
x	EQU	0x400
y	EQU	0x401
z	EQU	0x402
;//Bank5
;//***** Main Program *****

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
	MOVLW 0xf0		
	CLRF	PORTB		;clear output
	MOVWF	TRISB		;setze Pins RB<3:0> als Ausgang
	CLRF	zeit_1	;BSR<3:0>=0000 nach Reset
	CLRF	zeit_2,0	;Access-bank
	BRA main	
;//Main Application Code
main
FinishLoop
	BTFSC 	PORTA,RA4
	BRA FinishLoop
	MOVLW	0x0f
	XORWF	PORTB
;	CALL unterprogramm

;Addition (zahl_a) + (zahl_b) --> zahl_c
;  über BSR-Register (Bank 3)
	MOVLB	3
	MOVLW	0x99
	MOVWF	zahl_a	;w --> zahl_a
	MOVWF	zahl_b	;w --> zahl_b
	MOVF	zahl_a,0,1	;zahl_a --> w
	BSF		STATUS,C
	ADDWFC	zahl_b,0,1	;Summe --> w
	DAW
;Multiplikation (zahl_a) * (zahl_b) --> PRODH:PRODL
;  über BSR-Register (Bank 3)
	MOVLB	3
	MOVLW	0xff
	MOVWF	zahl_a	;w --> zahl_a
	MOVWF	zahl_b	;w --> zahl_b
	MOVF	zahl_a,0,1	;zahl_a --> w
	MULWF	zahl_b,1	;Produkt --> PRODH:PRODL

; x UND /y --> z  
;  über BSR-Register (Bank 4)
	MOVLB	4
	MOVLW	B'11100011'
	MOVWf	x	;w --> x
	MOVLW	B'11100011'
	MOVWF	y	;w --> y
	COMF	y	;/y --> 	
	MOVF	y,0,1
	ANDWF	x,0,1
	MOVWF	z
	
	BRA FinishLoop ;//Do.. Forever stops

unterprogramm
schleife_1
	DECFSZ	zeit_1
	BRA	schleife_1
	DECFSZ	zeit_2
	BRA	schleife_1
   	RETURN

	END

