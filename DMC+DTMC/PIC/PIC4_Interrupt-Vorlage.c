// Hochschule Mannheim / Institut für Mikrocomputertechnik und Embedded Systems
//
// Versuch: PIC4  Interrupt    Dateiname: PIC4_Interrupt.c
//
// Beschreibung:
// Es laufen zwei Tasks ab:
// Task 1: Zeituhr mit hoher Priorität: Timer 1 unterbricht jede Sekunde und die Variablen
// Sekunde, Minute und Stunde werden neu berechnet und an der LCD-Anzeige ausgegeben.
// Task 2: Analog-Digital-Wandler mit niederer Priorität: Der AD-Wandler wird ausgelesen
// und an die LCD-Anzeige ausgegeben.
// Format der LCD-Anzeige:
//   1.Zeile: xxSekyyMinzzStd
//   2.Zeile: Analogwert=aaaa
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


void high_prior_InterruptHandler (void);
void low_prior_InterruptHandler (void);


unsigned char Sekunde,Minute,Stunde;
unsigned char ad_low_byte;
unsigned char ad_high_byte;

unsigned char Sekunden_text[20]="Sek\0";
unsigned char Minuten_text[20]="Min\0";
unsigned char Stunden_text[20]="Std\0";
unsigned char Analog_text[20]="Analogwert= \0";


void init (void)
{
	lcd_init();
	lcd_clear();
	// IO PORTS KONFIG
	LATA = 0;
    LATB = 0; 
    LATC = 0;	
	LATD = 0;
	
	TRISA=0b11110001; //RA0 Eingang RA<3:1> Ausgang 
	TRISB=0b11110000; //RB<3:0> Ausgang
	TRISC=0b11111111; //RC<1:0> Eingang
	TRISD=0b11110000; //RD<3:0> Ausgang
	
	
	// TMR1 KONFIG 
	T1CON = 0b10001110 ; // TMR1 Enables Register R/W of TMR1 in one 16 bit operation - prescaler 1:1 - Timer1 Oscillator is enabled - Do not Synchronize - External Clock  - TMR1 off 
	  // Interrupt KONFIG
	RCONbits.IPEN = 1;   // Interrupts Unterschiedliche priorität 
	PIR1bits.TMR1IF = 0; // TMR1 FLAG LÖSCHEN
	PIE1bits.TMR1IE = 1; // TMR1 Interrupt Enable lokal freigeben 
	IPR1bits.TMR1IP = 1; // TMR1 hohe Priorität 
	INTCON.GIEH = 1;     // Interrupts hoher Priorität Global freigeben 
    // ADC KONFIG
	ADCON0 = 0b10000000; // Fosc/32 - Channel 0 - GO=0 - ADC shut off 
	ADCON1 = 0b10001110; // Right Justified - Fosc/32 - AN0 Analog eingang alle andere Digital
	PIR1bits.ADIF = 0;   // ADC Interrupt FLAG löschen 
	PIE1bits.ADIE = 1;   // AD-Wandler Interrupt Enable lokal freigeben 
	IPR1bits.ADIP = 0;       // A/D-Wandler niedriger Priorität
	INTCONbits.GIEL = 1; // Interrupts niedriger Priorität Global freigeben
	// TRM1 und A/D-Wandler STARTEN
	T1CONbits.TMR1ON = 1; 
	ADCON0bits.GO = 1;
	TMR1 = 0x7FFF; 
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
{

// Timer 1 Interrupt-Service Routine
   PIR1bits.TMR1IF = 0; // TMR1 FLAG LÖSCHEN
// Zeit inkrementieren    
   Sekunde++ ;
   if (Sekunde >= 60)
   {
   Minute++ ;
   Sekunde = 0;
   }
   if (Minute >= 60)
   {
   Stunde++ ;
   Minute = 0;
   }
   if (Stunde >= 24)
   {
   Stunde = 0 ;
   } 
 // LCD AUSGABE 
 lcd_gotoxy(1,1);
 lcd_int(Sekunde);
 lcd_printf(Sekunden_text);
 lcd_int(Minute);
 lcd_printf(Mintuen_text);
 lcd_int(Stunde);
 lcd_printf(Stunden_text);
 lcd_printf (leer);
 // TMR1 Initialisieren 
 TMR1 += 0x7FFF;
   }


#pragma code
#pragma interruptlow low_prior_InterruptHandler

void low_prior_InterruptHandler(void)
{
	// A/D-Wandler Interrupt-Service Routine
	PIR1bits.ADIF = 0;   // ADC Interrupt FLAG löschen 
	ad_low_byte = ADRESL;
	ad_high_byte = ADRESH; 
    INTCONbits.GIEH = 0;     // Interrupts Global Auschalten so wird die LCD Ausgabe nicht Unterbrochen 
	// LCD AUSGABE
	lcd_gotoxy(2,1);
    lcd_printf(Analog_text);
	lcd_int(ad_high_byte);
    lcd_int(ad_low_byte);
    lcd_printf(leer);

	
}


void main (void)
{
	init();
	while(1);
}

