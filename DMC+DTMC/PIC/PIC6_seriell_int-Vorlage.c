// Hochschule Mannheim / Institut für Mikrocomputertechnik und Embedded Systems
//
// Versuch:   PIC6  Serielle Übertragung über UART im Vollduplex-Verfahren
// Dateiname: PIC6_seriell_int.c
//
// Asynchrone Serielle Übertragung im Voll-Duplex - Verfahren
// Beidseitige Übertragung der vom AD-Wandler gelieferten dreistelligen
// Hexadezimal-Zahl 0-3FFH, im ASCII-Code beginnend mit dem
// STX=02 Zeichen, also z.B. 3A1H sendet 02 33 41 31 ...
// gesteuert über den seriellen Sende- und Empfangsinterrupt.
// Der serielle Empfangs-Interrupt hat hohe, der serielle Sende-Interrupt
// und der AD-Wandler haben niedrige Priorität.
// Die Ausgabe auf dem LCD-Display sollte wie folgt aussehen:
//   ADin  = 0x32A
//   ADout = 0x27B
//
// 24.05.2011 (Poh) Configuration Bit Settings, Anpassungen für NEUE_PLATINE, Includes im Projektverzeichnis
//
// Name/Gruppe:
//

#pragma config OSC=HS,WDT=OFF,LVP=OFF  // HS Oszillator, Watchdog Timer disabled, Low Voltage Programming

// Define für LCD des neuen, grünen Demo-Boards:
// #define NEUE_PLATINE  // Achtung: define vor include! Bei altem braunem Demo-Board auskommentieren!
#include "p18f452.h"
#include "lcd.h"


#define STX 02

extern void lcd_printf (const char* message);
extern void lcd_gotoxy (char row,char column);
extern void lcd_clear (void);
extern void lcd_init (void);
extern void lcd_byte (char num);
extern void lcd_int (int num);
extern void lcd_putc (char num);

void high_prior_InterruptHandler (void);
void low_prior_InterruptHandler (void);

unsigned char ad_asc_out[3];
unsigned char ad_asc_in[3];
unsigned char ad_rest;

char serin_text[]="ADin = 0x               \0";
char serout_text[]="ADout= 0x              \0";
unsigned char rx_spalte,tx_spalte;
unsigned char rx_zeile=1;
unsigned char tx_zeile=2;

unsigned int x,y;
unsigned char empfangspuffer,sendepuffer,stx_wurde_empfangen;

int sende_zaehler,empfangs_zaehler;

void init (void)
{
	lcd_init();
	lcd_clear();

/*serielle Schnittstelle initialisieren*/


/*Interrupt Serielle Schnittstelle initialisieren*/


// AD-Wandler-Einstellungen und AD-Interrupt


// Allgemeine Interrupts

}

#pragma code high_prior_InterruptVector = 0x08

void high_prior_InterruptVector(void)
{
	_asm
			goto high_prior_InterruptHandler
	_endasm
}

#pragma code low_prior_InterruptVector = 0x18

void low_prior_InterruptVector(void)
{
	_asm
			goto low_prior_InterruptHandler
	_endasm
}

#pragma code
#pragma interrupt high_prior_InterruptHandler


void high_prior_InterruptHandler(void)
{		empfangspuffer=RCREG;

}

#pragma code
#pragma interrupt low_prior_InterruptHandler


void low_prior_InterruptHandler(void)
{
	if (PIR1bits.ADIF)
	{
	}
	if (PIR1bits.TXIF)
	{

		TXREG=sendepuffer; /*damit automatisch PIR1bits.TXIF=0*/
	}
}


void main (void)
{
	init();
	lcd_gotoxy(1,1);
	lcd_printf(serin_text);
	lcd_gotoxy(2,1);
	lcd_printf(serout_text);
	ADCON0bits.GO=1;	/*Wandlungsstart*/
	rx_spalte=10;
// 	empfangs_zaehler= ;
// 	sende_zaehler= ;
//	stx_wurde_empfangen=;
//  .....						/*Empfangsstart*/
//  .....						/*Sendefreigabe: hier erster Sende-Interrupt, da Sendepuffer TXREG leer!*/
	while(1);
}

