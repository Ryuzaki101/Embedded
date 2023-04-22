// Hochschule Mannheim / Institut für Mikrocomputertechnik und Embedded Systems
//
// Versuch: PIC3  Serieller Empfang über UART    Dateiname: PIC3_seriell_rec.c
//
// Asynchroner Serieller Empfang über UART des PIC18F452
// Übertragung einer vom AD-Wandler der Sendeplatine gelieferten
// Hexadezimal-Zahl 0-3FFH, im ASCII-Code beginnend mit dem
// STX=02 Zeichen, also z.B. 3A1H sendet 02 33 41 31 ...
// Die Ausgabe auf dem LCD-Display sollte wie folgt aussehen:
//   ADin = 0x32A
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

unsigned char ad_asc_in[3];
char serin_text[]="ADin = 0x               \0";
unsigned char rx_spalte;
unsigned char rx_zeile=1;
unsigned char empfangspuffer,stx_wurde_empfangen;
int i,empfangs_zaehler;

void init (void)
{
	lcd_init();
	lcd_clear();

	/*serielle Schnittstelle initialisieren*/


}

void main (void)
{
	init();
	lcd_gotoxy(1,1);
	lcd_printf(serin_text);
 	empfangs_zaehler=3;
	stx_wurde_empfangen=0;
					/*Empfangsstart*/

	do	{	while(!PIR1bits.RCIF);
			empfangspuffer=RCREG;
			if (stx_wurde_empfangen)
			{
			}
			if (empfangspuffer==STX)
			{
			}
			PIR1bits.RCIF=0;
		}	while(1);
}

