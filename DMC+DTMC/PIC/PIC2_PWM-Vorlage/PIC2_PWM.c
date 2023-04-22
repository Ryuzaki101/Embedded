// Hochschule Mannheim / Institut f�r Mikrocomputertechnik und Embedded Systems
//
// Versuch: PIC2  DA-Wandler durch PWM    Dateiname: PIC2_PWM.c
//
// Eine am Analogeingang RA0/AN0 vorgegebene Spannung wird digitalisiert,
// der Wert AnalogIn=xxxx am LCD angezeigt
// und �ber eine Pulsweitenmodulation am Ausgang RC2/CCP1 ausgegeben.
// Das dort angeschlossene RC-Glied macht daraus wieder eine Analogspannung,
// die am Eingang RE2/AN7 eingelesen und als Istwert AnalogOut=yyyy angezeigt wird.
//
// 08.12.2011 (Poh) Kommentare f�r LCD (Prototypen in lcd.h)
// 24.05.2011 (Poh) Configuration Bit Settings, Anpassungen f�r NEUE_PLATINE, Includes im Projektverzeichnis
//
// Name/Gruppe:
//

#pragma config OSC=HS,WDT=OFF,LVP=OFF  // HS Oszillator, Watchdog Timer disabled, Low Voltage Programming

// Define f�r LCD des neuen, gr�nen Demo-Boards:
// #define NEUE_PLATINE  // Achtung: define vor include! Bei altem braunem Demo-Board auskommentieren!
#include "p18f452.h"
#include "lcd.h"         // Enth�lt alle Prototypen f�r das LCD!


void init(void);

unsigned int x = 0, y = 0;
unsigned char Analog_text1[20]="AnalogIn=\0";       // 16 Zeichen pro Zeile
unsigned char Analog_text2[20]="AnalogOut=\0";
unsigned char leer[]          ="                ";

void init()
{
	lcd_init();
	lcd_clear();





}

void main()
{
	init();
	while(1)	{
		while(!ADCON0bits.GO) {		// Warten, bis Wandlung fertig
		// A/D-Converter Kanalauswahl
			//Analog-Kanal 0 einlesen
			if(!ADCON0bits.CHS2 && !ADCON0bits.CHS1 && !ADCON0bits.CHS0)	{
				// Berechnung von x
				// Duty Cycle f�r PWM  einstellen




					// Channel 7 ausw�hlen
			}
			// Analog-Kanal 7 einlesen
			else if(ADCON0bits.CHS2 && ADCON0bits.CHS1 && ADCON0bits.CHS0)	{
				// Berechnung von y



					// Channel 0 ausw�hlen
			}

		// Ausgabe an LCD
			ADCON1=0x0E;		// RA3:RA1 wieder digital I/O f�r LCD
			lcd_gotoxy(1,1);
			lcd_printf(Analog_text1);
			lcd_int(x);
			lcd_printf (leer);
			lcd_gotoxy(2,1);
			lcd_printf(Analog_text2);
			lcd_int(y);
			lcd_printf(leer);
			ADCON1=0x00;		// AAAA AAAA
						// Wandlung starten
		}
	}
}

