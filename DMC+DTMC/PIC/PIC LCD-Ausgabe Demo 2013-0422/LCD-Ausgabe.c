// Hochschule Mannheim
// Institut für Embedded Systems
// Testprojekt für LCD-Anzeige
//
// Autor: Bernhard Pohlner 14.4.2011
// 24.05.2011 (Poh) Configuration Bit Settings, Anpassungen für NEUE_PLATINE, Includes im Projektverzeichnis

#pragma config OSC=HS,WDT=OFF,LVP=OFF  // HS Oszillator, Watchdog Timer disabled, Low Voltage Programming

// Define für LCD des neuen, grünen Demo-Boards:
// #define NEUE_PLATINE  // Achtung: define vor include! Bei altem braunem Demo-Board auskommentieren!
#include "p18f452.h"
#include "lcd.h"


unsigned int i;
unsigned char Taster[]=    "-> RA4 dr¼cken! ";
unsigned char TextZeile1[]="Erste Zeile>----";
unsigned char TextZeile2[]="1234567890123456";	// 16 Zeichen pro Zeile
unsigned char Leerzeile[]= "                ";

void main (void)
{
	lcd_init();		// LCD und zugehörige Prozessor-Ports initialisieren
	lcd_clear();	// Anzeige löschen

	lcd_printf(Taster);		// Erste Ausgabe vor Tastendruck RA4

	for (i=0;i<200;i++);	// Mindest-Verzögerung zwischen lcd_init() und erstem lcd_gotoxy()
							// wenn gleich zu Anfang RA4 gedrückt gehalten wird.

	while(PORTAbits.RA4);	// Warten bis Taster RA4 gedrückt

	lcd_gotoxy(2,1);		// zweite Zeile zuerst
	lcd_printf(TextZeile2);
	lcd_gotoxy(1,1);		// erste Zeile
	lcd_printf(TextZeile1);

	while(1)
	{
		for(i=0;i<9999;i++)		// Kontinuierliche Ausgabe von inkrementellen Zahlenwerten
		{
			lcd_gotoxy(1,13);	// Zeile 1, Spalte 13
			lcd_int(i);
		}
		lcd_gotoxy(1,13);		// Zeile 1, Spalte 13
		lcd_printf(Leerzeile);	// Leerzeichen schreiben
	}
}
