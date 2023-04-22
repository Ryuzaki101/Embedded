;****************************************************************
;*	HS Mannheim
;*	Institut für Mikrocomputertechnik/EmbeddedSystems
;*  Filename:
;*	indirekte_Befehle.asm
;*	Befehle zum Üben
;*
;*	Version: 2.0	Datum: 25.10.2007
;****************************************************************

	list p=18f452	;Prozessor für Assembler auswählen
#include <p18f452.inc>



BANK0 EQU 0x00
BANK1 EQU 0x100
BANK2 EQU 0x200
BANK3 EQU 0x300
BANK4 EQU 0x400
BANK5 EQU 0x500

;//***** Variables *****
;//

;//Bank0
;//Bank1
;//Bank2
;//Bank3
;//Bank4
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
   	BRA main	
;//Main Application Code
main
FinishLoop
;Indirekter Speicherzugriff
   	LFSR FSR0,0x300
next
	CLRF	POSTINC0
  	BTFSS	FSR0H,2
	BRA 	next
	LFSR	FSR1,0x500
	MOVF	INDF1,0  ;(Speicher)-->WREG
	SWAPF	PLUSW1	
	BRA FinishLoop ;//Do.. Forever stops
	END

