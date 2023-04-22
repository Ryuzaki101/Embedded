#include <LPC23xx.h>							// LPC23xx register definitions
#include <stdio.h>

volatile int tim1, tim2;

void ISRFall(void) __irq;
void ISRRais(void) __irq;	
void init(void);

void init (void) {
 	PINSEL4 |= (1 << 20);						// enable EINT0 on GPIO_2.10
	EXTMODE |= 1;								// edge sensitive mode on EINT0
	EXTPOLAR &= ~1;								// falling edge sensitive
	VICVectAddr14 = (unsigned long) ISRFall;	// set interrupt vector in VIC 0
	VICVectPriority14 = 14;						// use VIC Priority for EINT0 Interrupt
	VICIntEnable = (1 << 14);					// enable EINT0 Interrupt

	T0TCR = 2;									//reset Tmr0
	T0TCR ^= 3;									//enable Tmr0
}

void ISRFall (void) __irq{
	
	tim1 = T0TC;

	VICIntEnable = 0;							// disable EINT0 Interrupt
	EXTPOLAR ^= 1;								// toggle edge sensitive
	VICVectAddr14 = (unsigned long) ISRRais;	// set interrupt vector in VIC 0
	VICIntEnable = (1 << 14);					// enable EINT0 Interrupt
	
	EXTINT |= 0x01;								// clear EINT0 interrupt flag
	VICVectAddr = 0;							// acknowledge Interrupt

}void ISRRais (void) __irq{
	
	tim2 = T0TC;
	tim2 -=tim1;

	VICIntEnable = 0;							// disable EINT0 Interrupt
	EXTPOLAR ^= 1;								// toggle edge sensitive
	VICVectAddr14 = (unsigned long) ISRFall;	// set interrupt vector in VIC 0
	VICIntEnable = (1 << 14);					// enable EINT0 Interrupt
	
	EXTINT |= 0x01;								// clear EINT0 interrupt flag
	VICVectAddr = 0;							// acknowledge Interrupt

//	sprintf("counted: %d" ,4*(tim2/57600000));
	
}




int main(void) {
	init();
	while(1); 
}
