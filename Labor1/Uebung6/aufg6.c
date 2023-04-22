#include <LPC23xx.h>												// LPC23xx register definitions

volatile char dirswtch = 0;									// toggle for direction

void init(void);														// Initialization
void ISRbtn(void) __irq;										// ISR for buttonpress
void ISRtmr(void) __irq;										// ISR for timer 
void init(void);

void init(void) {
	FIO2DIR0 = ~0;														// pin2.0 - 2.7 output
	PINSEL4 |= (1 << 20);											// enable EINT0 on GPIO_2.10
	EXTMODE |= 1;															// edge sensitive mode on EINT0
	EXTPOLAR &= ~1;														// falling edge sensitive

	VICVectAddr14 = (unsigned long) ISRbtn;		// set interrupt vector for buttonpress
	VICVectPriority14 = 14;										// use VIC Priority for EINT0 Interrupt
	VICIntEnable = (1 << 14);									// enable EINT0 Interrupt

	VICVectAddr4 = (unsigned long) ISRtmr;		// set interrupt vector for timer
	VICVectPriority4 = 13;										// use VIC Priority for T0IR Interrupt
	VICIntEnable = (1 << 4);									// enable T0IR Interrupt

	T0MCR = 0x03;															// interrupt on MR0 match and reset on match 
	T0MR0 = 1800000;													// MR0 value for 0,125s
	T0TCR = 0x02;															// tmr reset
	T0TCR ^= 0x03;														// tmr enable

	FIO2PIN0 = 0x01;													// set LED
}

void ISRtmr(void) __irq {
	if (!dirswtch) {													// check direction
		if (FIO2PIN0 >= 0x80) FIO2PIN0 = 0x01;	// check overflow
			else FIO2PIN0 = (FIO2PIN0 << 1);
	} else {																	// direction changed
		if (FIO2PIN0 <= 0x01) FIO2PIN0 = 0x80;	// reset LED on overflow
			else FIO2PIN0 = (FIO2PIN0 >> 1);
	}
	T0IR |= 0x01;															// clear T0IR interrupt flag
	VICVectAddr = 0;													// acknowledge Interrupt
}

void ISRbtn(void) __irq {
	dirswtch ^= 0x01;													// toggle direction
	EXTINT |= 0x03;														// clear EINT0 interrupt flag
	VICVectAddr = 0;													// acknowledge Interrupt
}


int main(void) {
	init();
	while(1);  
}
