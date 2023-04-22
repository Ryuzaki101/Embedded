/**********************************************************************
 *   Timer API function for NXP LPC2368 Microcontroller on MCB2300 EVBs in EMB Labs
 *   Functions: init_Timer3 and Timer3_ISR
 *   LDK / HS Mannheim
 *   History
 *   2015.05.14  ver 0.01 
 *********************************************************************/
#include <LPC23xx.h>                        /* LPC23xx  register definitions */

unsigned long TimeIntervall=0xffffffff, new_TimeValue = 0, old_TimeValue = 0;
int new_TimeIntervall;
unsigned long CurrentMeasurement = 0x0FFFFFFF;
unsigned long MaxValue = 2^32  -1;

void init_Timer3(void); 
void Timer3_ISR(void)  __irq; 
 
/*****************************************************************************
** Function name:		init_Timer3
**
** Descriptions:		Initialization for Timer 3
**
** parameters:			None
** Returned value:		None
** 
*****************************************************************************/
void init_Timer3(void){
PINSEL1 |= (3 << 16);  // Port0.24 configured as CAP3.1, Timer 3 channel 1
PCONP |= (1<<23); //Timer3 active	
T3PC = 0;      //Initialize prescale register for timer 3 
T3CTCR = 0x4;  //PCLK used for timer 3 counting, 
               //Input capture pin CAP3.1 used for timer 3 
T3CCR = (7 << 3); // Capture on falling edge and rising edge, Interrupt
                  //on channel 1 of timer 3 (T3TC --> T3CR1) 
T3TCR = 0x01; // Start Timer 3 counter
}


 
/*****************************************************************************
** Function name:		Timer3_ISR
**
** Descriptions:		Timer3 interrupt service routine
**
** parameters:			None
** Returned value:		None
** 
*****************************************************************************/
void Timer3_ISR(void)  __irq
{
	new_TimeValue = T3CR1;
	new_TimeIntervall = new_TimeValue - old_TimeValue;
	old_TimeValue = new_TimeValue;
	if (new_TimeIntervall < TimeIntervall)
		TimeIntervall = new_TimeIntervall;
	
	T3IR = 0x20;	
  VICVectAddr = 0;      		

}


