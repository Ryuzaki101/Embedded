;FH Mannheim, Institut für Mikrocomputertechnik/Embedded Systems
;
;Filename:	timer_1.asm
;
;Beschreibung:
;	Interrupt-Service-Routine zum Toggle von
;	RC2 (Lautsprecher) und Erzeugung einer Frequenz
;	von 646 Hz, wenn Schalter S2 (RA4) gedrückt wird.
;
;Version: 1.0		Datum: 21.12.2004   Krauss
;
	list p=18f452
#include <p18f452.inc>



BANK0 EQU 0x00
BANK1 EQU 0x100
BANK2 EQU 0x200
BANK3 EQU 0x300
BANK4 EQU 0x400
BANK5 EQU 0x500


;//***** Main Program *****

	org 0x00
ResetVect
	GOTO Init

	ORG 0x08
IntVectHigh
;//No Interrupts Enabled

	ORG 0x18
IntVectLow
	GOTO	timer1_isr

	ORG 0x30
;//Initialisation Code - Placed at some point after IntVect
Init
	CLRF	PORTB
	MOVLW	0xf0
	MOVWF	TRISB
	BCF	PORTC,RC2
	BCF	TRISC,RC2	;RC2 ist Ausgang fuer buzzer

	MOVLW	0Xff
	MOVWF	TMR1H
	MOVLW	0Xe7
	MOVWF	TMR1L
	MOVLW	B'10001110'
	MOVWF	T1CON
	BSF		T1CON,TMR1ON

	BCF	PIR1,TMR1IF
	BSF	PIE1,TMR1IE
	BCF	IPR1,TMR1IP
	BSF	RCON,IPEN
	BSF	INTCON,GIEL
	BSF	INTCON,GIEH
	BRA main	
;//Main Application Code
main
FinishLoop
	BRA FinishLoop ;//Do.. Forever stops

timer1_isr
	MOVLW	0Xff
	MOVWF	TMR1H
	MOVLW	0Xe7
	MOVWF	TMR1L

	BTFSC	PORTA,RA4
	BRA	Ende
	MOVLW	0x0f	
	XORWF	PORTB
	BTG	PORTC,RC2
Ende
	
	BCF	PIR1,TMR1IF
	RETFIE
	END

