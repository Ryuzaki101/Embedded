#include <LPC23xx.h>												// LPC23xx register definitions
#include <stdio.h>

extern void lcd_init(void);
extern void lcd_print(char *string);
extern void set_cursor(unsigned char column, unsigned char line);
extern void lcd_clear(void);

volatile char dirswtch = 0;									// toggles for direction
volatile int tim1 = 0, tim2 = 0;

void init(void);														// Initialization
void ISRbtnF(void) __irq;										// ISR for buttonpress falling edge
void ISRbtnR(void) __irq;										// ISR for buttonpress raising edge
void ISRtmrLed(void) __irq;									// ISR for LED timer 
void ISRtmrBtn(void) __irq;									// ISR for Button timer 

void init(void) {
	FIO2DIR0 = ~0;														// pin2.0 - 2.7 output
	PINSEL4 |= (1 << 20);											// enable EINT0 on GPIO_2.10
	EXTMODE |= 1;															// edge sensitive mode on EINT0
	EXTPOLAR &= ~1;														// falling edge sensitive

	VICVectAddr14 = (unsigned long) ISRbtnF;	// set interrupt vector for buttonpress
	VICVectPriority14 = 14;										// use VIC Priority for EINT0 Interrupt
	VICIntEnable = (1 << 14);									// enable EINT0 Interrupt

	VICVectAddr4 = (unsigned long) ISRtmrLed;	// set interrupt vector for timer
	VICVectPriority4 = 12;										// use VIC Priority for T0IR Interrupt
	VICIntEnable = (1 << 4);									// enable T0IR Interrupt

	VICVectAddr5 = (unsigned long) ISRtmrBtn;	// set interrupt vector for timer
	VICVectPriority5 = 13;										// use VIC Priority for T0IR Interrupt
	VICIntEnable = (1 << 5);									// enable T0IR Interrupt
                                                                            // Tmr0 for LED
	T0MCR = 0x03;															// interrupt on T0MR0 match and reset on match 
	T0MR0 = 1800000;													// T0MR0 value for 0,125s
	T0TCR = 0x02;															// reset Tmr0  
                                                                            // Tmr1 for button press
	T1MCR = 0x03;															// interrupt on T1MR0 match and reset on match 
	T1MR0 = 57600000;													// T1MR0 value for 4s
	T1TCR = 0x02;															// reset Tmr1  
}

void ISRtmrLed(void) __irq {
	if (!dirswtch) {													// check direction
		if (FIO2PIN0 >= 0x80) FIO2PIN0 = 0x01;	// check overflow
		else FIO2PIN0 = (FIO2PIN0 << 1);
	} 
	else {																		// direction changed
		if (FIO2PIN0 <= 0x01) FIO2PIN0 = 0x80;	// reset LED on overflow
		else FIO2PIN0 = (FIO2PIN0 >> 1);
	}
	T0IR |= 0x01;															// clear T0IR interrupt flag
	VICVectAddr = 0;													// acknowledge Interrupt
}

void ISRtmrBtn(void) __irq {
	T0TCR ^= 0x03;														// toggle Tmr0EN for LED if pressed >4sec. (4sec * 14.4Mhz = 576000000)
	if (T0TCR & 1) { 
		FIO2PIN0 = 0x01;												// set LED if Tmr0 is enabled
		dirswtch = 0;
		set_cursor(0,1);
		lcd_print("  LEDs ON Left  ");
	}
	else {
		FIO2PIN0 = 0x00;												// else clear LED
		set_cursor(0,1);
		lcd_print("    LEDs OFF    ");
	}
	T1IR |= 0x01;															// clear T0IR interrupt flag
	VICVectAddr = 0;			 										// acknowledge Interrupt
}

void ISRbtnF(void) __irq {
	T1TCR ^= 0x03;													  // toggle Tmr1EN for LED if pressed >4sec. (4sec * 14.4Mhz = 576000000)

	if (T0TCR & 1) { 
		dirswtch ^= 0x01;										// toggle direction for LED if pressed <4sec. 
		if (!dirswtch) {
			set_cursor(0,1);
			lcd_print("  LEDs ON Left  ");
		}
		else {
			set_cursor(0,1);
			lcd_print("  LEDs ON Right ");
		}
	}
	
	VICIntEnable = 0x00;											// disable EINT0 Interrupt
	EXTPOLAR ^= 0x01;													// toggle edge sensitive
	VICVectAddr14 = (unsigned long) ISRbtnR;	// set interrupt vector in VIC 0
	VICIntEnable = (1 << 14);									// enable EINT0 Interrupt

	EXTINT |= 0x01;														// clear EINT0 interrupt flag
	VICVectAddr = 0;													// acknowledge Interrupt
}

void ISRbtnR(void) __irq {
	T1TCR ^= 0x03;														// toggle Tmr1EN for LED if pressed >4sec. (4sec * 14.4Mhz = 576000000)

	VICIntEnable = 0;													// disable EINT0 Interrupt
	EXTPOLAR ^= 1;														// toggle edge sensitive
	VICVectAddr14 = (unsigned long) ISRbtnF;	// set interrupt vector in VIC 0
	VICIntEnable = (1 << 14);									// enable EINT0 Interrupt

	EXTINT |= 0x01;														// clear EINT0 interrupt flag
	VICVectAddr = 0;													// acknowledge Interrupt
}


int main(void) {
	init();
	lcd_init();

	lcd_clear();
	lcd_print("   EMB Lab 1    ");	
	set_cursor(0,1);
	lcd_print("  GPIO / Timer  ");	

	while(1);
}
