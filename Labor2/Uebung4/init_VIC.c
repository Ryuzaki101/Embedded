/**********************************************************************
 *   Timer API function for NXP LPC2368 Microcontroller on MCB2300 EVBs in EMB Labs
 *   Functions: init_VIC
 *   Your Name / HS Mannheim
 *   History
 *   2015.05.14  ver 0.01 
 *********************************************************************/
#include <LPC23xx.h>                        /* LPC23xx  register definitions */

// extern Functions Prototypes to be placed here 

void init_VIC(void);
void init_ext_int0 (void);
void  init_Timer0_for_UART(void);
extern void EXTINT0_Launch_ISR (void);
extern void Timer0_for_UART_LCD_ISR(void);
extern void UART0_ISR(void);
extern void UART1_ISR(void);

int ZeitDauer_Sek = 15;

void init_VIC(void){
	VICVectAddr14 = (unsigned long) EXTINT0_Launch_ISR;	// set interrupt vector for buttonpress
	VICVectPriority14 = 13;										// use VIC Priority for EINT0 Interrupt
	VICIntEnable = (1 << 14);									// enable EINT0 Interrupt

	VICVectAddr4 = (unsigned long) Timer0_for_UART_LCD_ISR;	// set interrupt vector for timer
	VICVectPriority4 = 12;										// use VIC Priority for T0IR Interrupt
	VICIntEnable = (1 << 4);									// enable T0IR Interrupt

	VICVectAddr6 = (unsigned long) UART0_ISR;	// set interrupt vector for timer
	VICVectPriority6 = 14;										// use VIC Priority for T0IR Interrupt
	VICIntEnable = (1 << 6);									// enable T0IR Interrupt

	VICVectAddr7 = (unsigned long) UART1_ISR;	// set interrupt vector for timer
	VICVectPriority7 = 14;										// use VIC Priority for T0IR Interrupt
	VICIntEnable = (1 << 7);									// enable T0IR Interrupt
}

/* Initialize the Pin EINT0 (External Interrupt 0 Pin) */
void init_ext_int0 (void) {
	PINSEL4 |= (1 << 20);											// enable EINT0 on GPIO_2.10
	EXTMODE |= 1;															// edge sensitive mode on EINT0
	EXTPOLAR &= ~1;														// falling edge sensitive
}

/**********************************************************************
 *   TIMER0 for UART/LCD API function for NXP LPC2368 Microcontroller on MCB2300 EVBs in EMB Labs
 *   Functions: init_Timer0_for_UART
 *   LDK / HS Mannheim
 *   History
 *   2015.05.14  ver 0.01 
 *********************************************************************/
void  init_Timer0_for_UART(void) {
	
	T0MCR = 0x03;															// interrupt on T0MR0 match and reset on match 
	T0MR0 = 28800000;													// T0MR0 value for 2s
	T0TCR = 0x02;															// reset Tmr0
	T0TCR = 0x01;
}

