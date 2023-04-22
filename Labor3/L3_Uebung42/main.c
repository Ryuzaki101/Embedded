#include <LPC23xx.h>
#include <stdio.h>
#include <math.h>
#include "emb1_can_labs.h"


extern void lcd_init (void);
extern void lcd_print (char *string);
extern void set_cursor (unsigned char column, unsigned char line);
extern void lcd_clear (void);

void ADC_Config(void); 
void ADC_StartConversion(void);
void Tmr0Init(void);
void ISR_tmr(void) __irq;

CAN_MSG myMessage;
CAN_MSG remMessage;
//CAN_MSG   My_CAN1_RX_message;
//CAN_MSG   My_CAN2_RX_message;

//extern uint32_t CAN1_Counter_RX, CAN2_Counter_RX;
//extern CAN_MSG  CAN1_RX_messages[CAN1_MAX_RX_MSG], CAN2_RX_messages[CAN2_MAX_RX_MSG];


volatile float val = 0;
volatile float oldVal = 0;
char sval[5];
char remSval[5];
char zeile1[16];
char zeile2[16];
int j;



int main() {

	CAN_Init( 1, 0x3DC002);
	CAN_Set_Acceptance_Filter_Mode(ACCF_ON);
	lcd_init();
	lcd_clear();
	ADC_Config();
	Tmr0Init();
	
	myMessage.id = 0x704;
	myMessage.length=5;
	myMessage.frame_format = 0;
	myMessage.frame_type = 0;



	while(1) {
//		CAN_Receive_Message(1, &remMessage);
//		for (j=0 ; j < 5; j++) remSval[j]=remMessage.data[j];
//	
//		set_cursor(0,1);
//		sprintf(zeile2, "AD Remote: %sV", sval);
//		lcd_print(zeile2);
	}
}

void ADC_Config(void) {
	FIO0DIR2 &= 0x7F;														// P0.23 input 
	PINSEL1 |= (1<<14);													// enable AD0.0 on GPIO_0.23
	PCONP |= (1<<12); 													// Power Control for Peripheries 
	AD0CR = 0x00200301;													// AD0.0 @3.6 MHZ
}

void ISR_tmr(void)  __irq {
	ADC_StartConversion ();
	set_cursor(0,0);
	sprintf(zeile1, "AD Local: %1.3fV", val);
	lcd_print(zeile1);
	
	CAN_Receive_Message(1, &remMessage);
	
	for (j=0 ; j < 5; j++) remSval[j]=remMessage.data[j];
	set_cursor(0,1);
	sprintf(zeile2, "AD %#3x: %sV", remMessage.id, remSval);
	lcd_print(zeile2);

	if (fabs(oldVal-val) > 0.5) {
		for (j=0 ; j < 5; j++) myMessage.data[j]=sval[j];
		CAN_Send_Message( 1, &myMessage);
	}

	T0IR |= 0x01;																// clear T0IR interrupt flag
	VICVectAddr = 0;														// acknowledge Interrupt
}

void ADC_StartConversion(void) {

	oldVal = val;
	AD0CR |= (1<<24 ); 													// START CONVERSION 
	while ((AD0GDR >> 31) == 0);								// CONVERSION STILL ONGOING 
	val = (((AD0DR0>>6)&0x3FF)  * (3.30/1023));	// Conversion result -> bit<15:6>
	sprintf(sval, "%1.3f", val);

}

void Tmr0Init(void) {

	VICVectAddr4 = (unsigned long) ISR_tmr;			// set interrupt vector for timer
	VICVectPriority4 = 14;											// use VIC Priority for T0IR Interrupt
	VICIntEnable = (1 << 4);										// enable T0IR Interrupt for AD-Conversion

	T0MCR = 0x03;																// interrupt on T0MR0 match and reset on match 
	T0MR0 = 1440000;														// T0MR0 value for 0,100s
	T0TCR = 0x02;																// reset Tmr0 
	T0TCR ^= 0x03;															// tmr enable
}
