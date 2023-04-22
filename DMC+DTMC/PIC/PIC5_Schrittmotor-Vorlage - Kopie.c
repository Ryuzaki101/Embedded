// Hochschule Mannheim / Institut für Mikrocomputertechnik und Embedded Systems
//
// Schrittmotorsteuerung (Drehzahl) mit dem PIC 18F452
//
// Dateiname: PIC5_Schrittmotor.c
//
// Beschreibung:
// Motor an Port B angeschlossen:
//    RB0  TOUT_1  Takt       (Jede steigende Flanke = 1 Schritt)
//    RB1  A3      Li/Re      ("1"=Links, "0"=Rechts)
//    RB2  A2      Halb/Full  ("1"=Halbschritt, "0"=Vollschritt)
//    RB3  A1      /Reset     (Konstant auf "1" lassen)
//    RB4  A0      Enable     ("1"=Motor in Betrieb)
//    +5V
//    GND         -> 7 Anschlüsse
//
// Der Analogwert entspricht der Schrittfrequenz mit -511<Wert<+511
// Berechnung des Teilerfaktors aus der Schrittfrequenz
//     Es gilt: Teiler=-32768/Schrittfrequenz
//     sowie: Umdrehungsgeschwindigkeit U=5/4 Schrittfrequenz
//
// Taster RA4 wird zum Umschalten zwischen Halb+Vollschritt verwendet.
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

//Globals
unsigned char TeilerH,TeilerL;
unsigned int Wert,Frequenz,Teiler;
unsigned char Linkslauf;

char leer[]="   \0";
char Rechts[9]="Rechts \0";
char Links [9]="Links  \0";
char EinheitS[10]=" S/Sek  \0";
char EinheitU[10]=" U/Min  \0";

void init (void)
{
// LCD
  lcd_init();           // muss hier stehen, da ADCON0+1 beeinflusst werden
  lcd_clear();          // Vor AD-Wandlungsbeginn, sonst unterbrochen durch AD-Wandler-Int.

// PortB Initialisieren



// Allgemeine Interrupts



// Timer 1 (high priotity) Interrupt-Einstellungen



// AD-Wandler (low priority) Interrupt-Einstellungen



}

#pragma code high_prior_InterruptVector = 0x08  // Timer1: Schritttakt für den Motor

void high_prior_InterruptVector(void)
{
  _asm
    goto high_prior_InterruptHandler
  _endasm
}

#pragma code low_prior_InterruptVector = 0x18  // AD-Wandler

void low_prior_InterruptVector(void)
{
  _asm
    goto low_prior_InterruptHandler
  _endasm
}


#pragma code
#pragma interrupt low_prior_InterruptHandler

void low_prior_InterruptHandler(void)  // AD-Wandler
{
// Vollschritt oder Halbschritt von Taster RA4 --> RB2

// Variablen Wert und Linkslauf berechnen

// LCD-Ausgabe mit Berechnung der Schrittfrequenz + Drehzahl:
  if(Linkslauf)
  {


  }
  else
  {


  }

// Teilerfaktor  Teiler=-32768/Frequenz  berechnen + TeilerH, TeilerL zuweisen

// Timer 1 starten, wenn Frequenz <> 0, sonst Timer 1 stoppen:
  if(Frequenz)
  {

  }
  else

}


#pragma code
#pragma interrupt high_prior_InterruptHandler

void high_prior_InterruptHandler(void)
/* Timer1: Schritttakt für den Motor  sowie Links-, oder Rechtslauf vorgeben
   Wichtig: Timer sofort wieder neu laden, sonst verringerte Schrittfrequenz!
            Schritttakt-Zeit muss > 2 Maschinenzyklen sein! */
{

}


void main (void)
{
  init();
  while(1);
}

