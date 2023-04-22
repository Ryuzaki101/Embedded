/**********************************************************************
 *   UART API function for NXP LPC2368 Microcontroller on MCB2300 EVBs in EMB Labs
 *   Functions: UART0_ISR and UART1_ISR
 *   LDK / HS Mannheim
 *   History
 *   2015.05.14  ver 0.01 
 *********************************************************************/
#include <LPC23xx.h>                        /* LPC23xx  register definitions */
#include <stdio.h>
#include "uart.h"

void UART0_ISR (void) __irq;
void UART1_ISR (void) __irq;
void EXTINT0_Launch_ISR (void) __irq;
void Timer0_for_UART_LCD_ISR(void) __irq;

void UART_Start_SendString(int PortNum, char *TX_String, int NumberChar);

extern char *MyText;

extern void lcd_init (void);
extern void lcd_print (char *string);
extern void set_cursor (unsigned char column, unsigned char line);
extern void lcd_clear (void);

//UART related global variables
 int U0_TX_Running = 0; // 1 if TX running per Interrupt
 int U1_TX_Running = 0;
 int U0_rx_sw_buffer_index, U1_rx_sw_buffer_index; 
 int U0_tx_sw_buffer_index, U1_tx_sw_buffer_index; 
 int U0_TX_NumberOfChar, U1_TX_NumberOfChar;
 int U0_RX_NumberOfChar, U1_RX_NumberOfChar;
 unsigned char UART0_ReceivedBytes[UART0_SW_RX_BUFFER_SIZE];
 unsigned char *LCD_UART0_ReceivedBytes;
 unsigned char UART1_ReceivedBytes[UART1_SW_RX_BUFFER_SIZE];
 unsigned char *LCD_UART1_ReceivedBytes;
 int LCD_Out_Turn;
 int AutoBaud_U0DLL, AutoBaud_U0DLM;
 int AutoBaud_U1DLL, AutoBaud_U1DLM;
 int Selected_TX_UART_PORT = 0;
 int Selected_RX_UART_PORT = 0;
 char *UART_TX_String;

 
/*****************************************************************************
** Function name:		UART0_ISR
**
** Descriptions:		UART0 interrupt service routine
**
** parameters:			None
** Returned value:		None
** 
*****************************************************************************/
void UART0_ISR (void) __irq 
{
   unsigned char  IIR_Content, Dummy;
  
  //After servicing the requested interrupt(s) within a loop, the ISR checks whether
  // a new interrupt (at least) has been requested.
  while (((IIR_Content = U0IIR) & 0x1) == 0  ) {
	switch(IIR_Content & 0x0E){ 
	
      case 0x06: /* Receive Line Status (RLS)*/
	     //At least one RX error has occurred
				// Put your code here if RLS error handling required
         Dummy = U0LSR;  /* Clear the RLS interrupt */
         break;
		 
	  case 0x04: /* Receive Data Available (RDA)  or*/ 
	  case 0x0C: /*Character Time-Out Indicator (CTI) */
	    while (U0LSR & 0x01){
				Dummy = UART_GetChar(0);
				if  ((Dummy == 0x0D) || (Dummy == 0x0A )){  //Carriage return (CR) or New line (NL) 
			    U0_RX_NumberOfChar = U0_rx_sw_buffer_index;
					U0_rx_sw_buffer_index = 0;
					LCD_UART0_ReceivedBytes = &UART0_ReceivedBytes[0];
					LCD_Out_Turn = 0;
				}
        else				
					UART0_ReceivedBytes[U0_rx_sw_buffer_index++] = Dummy;	
		}
		break;
	  
	  case 0x02: 
	    if (U0_TX_Running){
			while (( U0LSR & 0x20) && (U0_tx_sw_buffer_index < U0_TX_NumberOfChar)) {
				Dummy = UART_TX_String[U0_tx_sw_buffer_index++]; 
				UART_PutChar(0, Dummy);
			}
		}		
        if 	(U0_tx_sw_buffer_index == U0_TX_NumberOfChar){
					U0_TX_Running = 0;
					U0IER &= ~(1<<1);
				}
		  break;
				
		default: Dummy++;	
	
	}
	
	if ( IIR_Content & 0x10){  //Check if auto-baud interrupt flag is set
		AutoBaud_U0DLL = U0DLL;
		AutoBaud_U0DLM = U0DLM;
		U0ACR |= (IIR_Content & 0x30); // Clear both auto-baud interrupt flags
	}
	else
		if ( IIR_Content & 0x20)  //Check if auto-baud time-out interrupt flag is set
					U0ACR |= (IIR_Content & 0x20); // Clear auto-baud time-out interrupt flags
 }
 VICVectAddr = 0;
}	  
  
   

/*****************************************************************************
** Function name:		UART1_ISR
**
** Descriptions:		UART1 interrupt service routine
**
** parameters:			None
** Returned value:		None
** 
*****************************************************************************/
void UART1_ISR (void) __irq 
{
   char  IIR_Content, Dummy;
  
  //After servicing the requested interrupt(s) within a loop, the ISR checks whether
  // a new interrupt (at least) has been requested.
  while (((IIR_Content = U1IIR) & 0x1) == 0  ) {
	switch(IIR_Content & 0x0E){ 
	
      case 0x06: /* Receive Line Status (RLS)*/
	     //At least one RX error has occurred
		 // Put your code here if RLS error handling required
         Dummy = U1LSR;  /* Clear the RLS interrupt */
         break;
		 
	  case 0x04: /* Receive Data Available (RDA)  or*/ 
	  case 0x0C: /*Character Time-Out Indicator (CTI) */
	    while (U1LSR & 0x01){
				Dummy = UART_GetChar(1);
				if  ((Dummy == 0x0D) || (Dummy == 0x0A )){  //Carriage return (CR) or New line (NL) 
			    U1_RX_NumberOfChar = U1_rx_sw_buffer_index;
					U1_rx_sw_buffer_index = 0;
					LCD_UART1_ReceivedBytes = &UART1_ReceivedBytes[0];
					LCD_Out_Turn = 0;
				}
        else				
					UART1_ReceivedBytes[U1_rx_sw_buffer_index++] = Dummy;	
		}
		break;
	  
	  case 0x02:  
	    if (U1_TX_Running){
			while (( U1LSR & 0x20) && (U1_tx_sw_buffer_index < U1_TX_NumberOfChar)) {
				Dummy = UART_TX_String[U1_tx_sw_buffer_index++]; 
				UART_PutChar(1, Dummy);		
			}
		}
        if 	(U1_tx_sw_buffer_index == U1_TX_NumberOfChar){
					U1_TX_Running = 0;
					U1IER &= ~(1<<1);
				}
		break;
				
		default: Dummy++;		
	
	}
	
	if ( IIR_Content & 0x100){
		AutoBaud_U1DLL = U1DLL;
		AutoBaud_U1DLM = U1DLM;
		U1IIR = (IIR_Content & 0x300);
	}
	else
		if ( IIR_Content & 0x200)
					U0IIR = (IIR_Content & 0x200);
 }
 VICVectAddr = 0;
}	  
  
   

/*****************************************************************************
** Function name:		EXTINT0_Launch_ISR
**
** Descriptions:	External Interrupt Button to launch a transmission of Characters
**
** parameters:			None
** Returned value:		None
** 
*****************************************************************************/
/* External Interrupt 0 to launch the transmission of characters */
void EXTINT0_Launch_ISR (void) __irq{
    char *tt;
	  int NumberChar;
	

	UART_TX_String = MyText;
	tt = UART_TX_String;
	
	NumberChar = 0;
	while(*tt++) NumberChar++;
	if ( NumberChar > 0)
	   UART_Start_SendString(Selected_TX_UART_PORT, UART_TX_String , NumberChar);
  EXTINT      |= 1 << 0;                            // Clear EINT0 interrupt flag
  VICVectAddr = 0;                            // Acknowledge Interrupt
	
}


/*****************************************************************************
** Function name:		UART_Start_SendString
**
** Descriptions: This function sends the first 2 characters per UART and
**               enables UART TX interrupt afterwards   
**
** parameters:			PortNum = 0 (for UART0) or 1 (for UART1)
**                  TX_String = String to be sent
**                  NumberChar 
** Returned value:		None
** 
*****************************************************************************/
void UART_Start_SendString(int PortNum, char *TX_String, int NumberChar){
	volatile unsigned long *UxLSR;
	volatile unsigned long *UxIER;
	char DummyChar;
	
	if (PortNum == 0) //UART0 Selected
		{
			UxLSR = &U0LSR;
			UxIER = &U0IER;
		}
	else
		{
			UxLSR = &U1LSR;
			UxIER = &U1IER;	
		}
	if ( *UxLSR & 0x20 ){
	  if ( NumberChar >= 2) {
			if ( NumberChar > 2){
				*UxIER  |= 0x02;
				NumberChar = NumberChar - 2;
			  if (PortNum){
			     U1_TX_Running  = 1;
					 U1_TX_NumberOfChar = NumberChar+2;
					 U1_tx_sw_buffer_index = 2;
				}
			  else
				{
				   U0_TX_Running  = 1;
					 U0_TX_NumberOfChar = NumberChar+2;
					 U0_tx_sw_buffer_index = 2;
        }
			}	
	    DummyChar = *TX_String;
			TX_String++;
			UART_PutChar(PortNum, DummyChar);
			DummyChar = *TX_String;
			TX_String++;
			UART_PutChar(PortNum, DummyChar);			
		}
	  else
			if ( NumberChar == 1){
			DummyChar = *TX_String;
			*TX_String = 0;
			UART_PutChar(PortNum, DummyChar);			
		}
}		
  	
}


/**********************************************************************
 *   TIMER0 for UART/LCD API function for NXP LPC2368 Microcontroller on MCB2300 EVBs in EMB Labs
 *   Functions: Timer0_for_UART_LCD_ISR
 *   LDK / HS Mannheim
 *   History
 *   2015.05.14  ver 0.01 
 *********************************************************************/
void Timer0_for_UART_LCD_ISR(void) __irq {
	 char Zeile1[16];
	 char Zeile2[16];
	 static unsigned char *LCD_Output_String;
	 static int MaxNumberChar;
	 static int CharCounter, LastTurnCharNumber; 
	 static int LCD_Out_MaxTurns;
   
   if (LCD_Out_Turn == 0) {
		 if (Selected_RX_UART_PORT)  {
      LCD_Output_String = LCD_UART1_ReceivedBytes;
		  MaxNumberChar =  U1_RX_NumberOfChar;
	    }
     else
	   {
      LCD_Output_String = LCD_UART0_ReceivedBytes;
		  MaxNumberChar =  U0_RX_NumberOfChar;
     }      		 
   LCD_Out_MaxTurns = (int) (MaxNumberChar /16);
	 LastTurnCharNumber = MaxNumberChar - 16*LCD_Out_MaxTurns;	 
   }
   if ( LCD_Out_Turn == LCD_Out_MaxTurns ){
       if ( LastTurnCharNumber ){
				for (CharCounter = 0; CharCounter < LastTurnCharNumber; CharCounter++)
               Zeile2[CharCounter] = (char) LCD_Output_String[16*LCD_Out_Turn + CharCounter];	
        for (CharCounter = LastTurnCharNumber; CharCounter < 16; CharCounter++)
               Zeile2[CharCounter] = (char) 0;				 
			 }
			 LCD_Out_Turn = 0;
		 }	 
		else
		{			
			 for (CharCounter = 0; CharCounter < 16; CharCounter++)
               Zeile2[CharCounter] = (char) LCD_Output_String[16*LCD_Out_Turn + CharCounter];	
			 LCD_Out_Turn++ ;
    }         				 
		 
	 lcd_clear();
		sprintf(Zeile1, "UART%d received:", Selected_RX_UART_PORT);
	 lcd_print(Zeile1);
	 set_cursor(0,1);
	 //sprintf(Zeile2);
	 lcd_print(Zeile2);	
  		 
   T0IR = 0x01;	     /* Clear interrupt  */
   //T0TCR = 0x01;		/* start timer */	
   VICVectAddr = 0x1234;      		
}





