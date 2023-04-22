#include <LPC23xx.h>															// LPC23xx register definitions
 
void ADC_Config(void); 
void ADC_StartConversion(void);
void Tmr0Init(void);
void ISR_tmr(void) __irq;

volatile float val = 0;

int main(void) {
	ADC_Config(); 
	Tmr0Init();

	while(1);
} 

void ADC_Config(void) {
	FIO0DIR2 &= 0x7F;															// P0.23 input 
	PINSEL1 |= (1<<14);														// enable AD0.0 on GPIO_0.23
	PCONP |= (1<<12); 														// Power Control for Peripheries 
	AD0CR = 0x00200301;														// AD0.0 @3.6 MHZ
}

void ADC_StartConversion(void) {
	AD0CR |= (1<<24 ); 														// START CONVERSION 
	while ((AD0GDR >> 31) == 0);									// CONVERSION STILL ONGOING 
	val = (((AD0DR0>>6)&0x3FF)  * (3.3/1023)); 		// Conversion result -> bit<15:6>
}

void Tmr0Init(void) {

	VICVectAddr4 = (unsigned long) ISR_tmr;			// set interrupt vector for timer
	VICVectPriority4 = 14;											// use VIC Priority for T0IR Interrupt
	VICIntEnable = (1 << 4);										// enable T0IR Interrupt

	T0MCR = 0x03;																// interrupt on T0MR0 match and reset on match 
	T0MR0 = 1440000;														// T0MR0 value for 0,100s
	T0TCR = 0x02;																// reset Tmr0 
	T0TCR ^= 0x03;															// tmr enable
}

void ISR_tmr(void)  __irq {
	ADC_StartConversion ();

	T0IR |= 0x01;															// clear T0IR interrupt flag
	VICVectAddr = 0;													// acknowledge Interrupt
}


